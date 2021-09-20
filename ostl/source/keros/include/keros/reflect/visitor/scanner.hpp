#pragma once

#include "keros/reflect/model/model.hpp"

namespace keros
{
    template<class derived, complete_model base>
    class scanner;

    template<class derived, template<class...> class pointer, template<class> class... elements>
    class scanner<derived, model<pointer, elements...>> : public model<pointer, elements...>::guest_type
    {
    public:
        using base = model<pointer, elements...>;
        using derived_ref = derived&;

        derived_ref scan(const base& host)
        {
            host.accept(*this);
            return static_cast<derived_ref>(*this);
        }

        template<std::derived_from<base> derived>
        derived_ref scan(const pointer<derived>& host)
        {
            host->accept(*this);
            return static_cast<derived_ref>(*this);
        }

        template<std::derived_from<base> derived>
        derived_ref visit_cast(const derived& host)
        {
            this->visit(host);
            return static_cast<derived_ref>(*this);
        }
    };
}  // namespace keros
