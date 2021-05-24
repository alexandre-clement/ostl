#pragma once

#include "named.hpp"
#include "typed.hpp"

namespace keros
{
    template<complete_model base>
    class function
        : public named<base>
        , public typed<base>
    {
    public:
        template<derived_from<type<base>> derived>
        function(std::string p_name, derived p_return_type) : named<base>(std::move(p_name))
                                                            , typed<base>(p_return_type)
        {
        }
        function(const function&) = default;
        function(function&&) noexcept = default;
        function& operator=(const function&) = default;
        function& operator=(function&&) noexcept = default;
        ~function() = default;

        using guest_ref = typename base::guest_ref;

        make_visitable
    };
}  // namespace keros