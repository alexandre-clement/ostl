#pragma once

#include <tuple>

namespace detail
{
    template<class... types>
    using pack = std::tuple<types...>;

    enum class qualifier
    {
        const_,
        not_const_
    };

    template<class visitables_pack, qualifier _qualifier = qualifier::not_const_>
    class visitor;

    template<class visited>
    class visitor<pack<visited>, qualifier::not_const_>
    {
    public:
        virtual ~visitor() = default;

        using host_type = visited;
        using host_ref = host_type&;

        virtual void visit(host_ref) = 0;
    };

    template<class visited>
    class visitor<pack<visited>, qualifier::const_>
    {
    public:
        virtual ~visitor() = default;

        using host_type = const visited;
        using host_ref = host_type&;

        virtual void visit(host_ref) = 0;
    };

    template<class head, class... tails, qualifier _qualifier>
    class visitor<pack<head, tails...>, _qualifier>
        : public visitor<pack<head>, _qualifier>
        , public visitor<pack<tails...>, _qualifier>
    {
    public:
        virtual ~visitor() = default;

        using visitor<pack<head>, _qualifier>::visit;
        using visitor<pack<tails...>, _qualifier>::visit;
    };

    template<class visitables_pack, qualifier _qualifier = qualifier::not_const_>
    class visitable;

    template<class visitables_pack>
    class visitable<visitables_pack, qualifier::not_const_>
    {
    public:
        virtual ~visitable() = default;

        using guest_type = visitor<visitables_pack, qualifier::not_const_>;
        using guest_ref = guest_type&;

        virtual void accept(guest_ref) = 0;

        template<class derived>
        static void pay_visit(derived& host, guest_ref guest)
        {
            guest.visit(host);
        }
    };

    template<class visitables_pack>
    class visitable<visitables_pack, qualifier::const_>
    {
    public:
        virtual ~visitable() = default;

        using guest_type = visitor<visitables_pack, qualifier::const_>;
        using guest_ref = guest_type&;

        virtual void accept(guest_ref) const = 0;

        template<class derived>
        static void pay_visit(derived& host, guest_ref guest)
        {
            guest.visit(host);
        }
    };

#define make_visitable                                                                                                 \
public:                                                                                                                \
    void accept(guest_ref guest) const override { return this->pay_visit(*this, guest); }

}  // namespace detail
