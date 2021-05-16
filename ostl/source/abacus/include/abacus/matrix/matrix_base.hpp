#pragma once

#include <array>
#include <compare>
#include <concepts>
#include <stdexcept>
#include <type_traits>

namespace abacus
{
    using index = std::size_t;

    template<class t, class scalar_type>
    concept convertible_to = std::is_convertible_v<t, scalar_type>;

    template<class _scalar_type, index rows, index columns, template<class, index, index> class vector>
    class array
    {
    public:
        using scalar_type = _scalar_type;
        using scalar_ref = scalar_type&;
        using scalar_const_ref = const scalar_type&;

        constexpr array() = default;
        constexpr array(const array&) = default;
        constexpr array(array&&) noexcept = default;
        constexpr array& operator=(const array&) = default;
        constexpr array& operator=(array&&) noexcept = default;
        ~array() = default;

        constexpr bool operator==(const array&) const = default;

        constexpr scalar_ref at(index, index);
        constexpr scalar_const_ref at(index, index) const;

        constexpr vector<scalar_type, 1, columns>& row(index);

    private:
        using storage = std::array<vector<scalar_type, 1, columns>, rows>;

        storage data;
    };

    template<class _scalar_type, index columns, template<class, index, index> class vector>
    class array<_scalar_type, 1, columns, vector>
    {
    public:
        using scalar_type = _scalar_type;
        using scalar_ref = scalar_type&;
        using scalar_const_ref = const scalar_type&;

        constexpr array() = default;
        constexpr array(const array&) = default;
        constexpr array(array&&) noexcept = default;
        constexpr array& operator=(const array&) = default;
        constexpr array& operator=(array&&) noexcept = default;
        ~array() = default;

        constexpr bool operator==(const array&) const = default;

        constexpr scalar_ref at(index, index);
        constexpr scalar_const_ref at(index, index) const;

    private:
        using storage = std::array<scalar_type, columns>;

        storage data;
    };

    template<class scalar_type, index rows, index columns, template<class, index, index> class vector>
    class base
    {
    public:
        using scalar_ref = scalar_type&;
        using scalar_const_ref = const scalar_type&;

        constexpr base() = default;
        constexpr base(const base&) = default;
        constexpr base(base&&) noexcept = default;
        constexpr base& operator=(const base&) = default;
        constexpr base& operator=(base&&) noexcept = default;
        ~base() = default;

        constexpr bool operator==(const base&) const = default;

        constexpr vector<scalar_type, 1, columns>& row(index r);

        constexpr scalar_ref at(index, index);
        constexpr scalar_const_ref at(index, index) const;

        using storage = array<scalar_type, rows, columns, vector>;

        storage data;
    };

    template<class scalar_type, template<class, index, index> class vector>
    class base<scalar_type, 1, 2, vector>
    {
    public:
        using scalar_ref = scalar_type&;
        using scalar_const_ref = const scalar_type&;

        constexpr base() = default;
        constexpr base(const base&) = default;
        constexpr base(base&&) noexcept = default;
        constexpr base& operator=(const base&) = default;
        constexpr base& operator=(base&&) noexcept = default;
        ~base() = default;

        constexpr bool operator==(const base& b) const = default;

        constexpr scalar_ref at(index);
        constexpr scalar_const_ref at(index) const;

        constexpr scalar_ref at(index, index);
        constexpr scalar_const_ref at(index, index) const;

        scalar_type x, y;

#if defined(_MSC_VER) || defined(__clang__)
    #define swizzle(name, ...)                                                                                         \
        vector<scalar_type, 1, 2> _##name() const { return vector<scalar_type, 1, 2>(__VA_ARGS__); }                   \
        __declspec(property(get = _##name)) vector<scalar_type, 1, 2> name;

        swizzle(xx, x, x) swizzle(xy, x, y) swizzle(yx, y, x) swizzle(yy, y, y)
#endif
    };

#ifdef abacus_matrix_type_aligned
    #define vec3_alignment alignas(sizeof(scalar_type) * 4)
#else
    #define vec3_alignment
#endif

    template<class scalar_type, template<class, index, index> class vector>
    class vec3_alignment base<scalar_type, 1, 3, vector>
    {
    public:
        using scalar_ref = scalar_type&;
        using scalar_const_ref = const scalar_type&;

        constexpr base() = default;
        constexpr base(const base&) = default;
        constexpr base(base&&) noexcept = default;
        constexpr base& operator=(const base&) = default;
        constexpr base& operator=(base&&) noexcept = default;
        ~base() = default;

        constexpr bool operator==(const base& b) const = default;

        constexpr scalar_ref at(index);
        constexpr scalar_const_ref at(index) const;

        constexpr scalar_ref at(index, index);
        constexpr scalar_const_ref at(index, index) const;

        scalar_type x, y, z;
    };

#undef vec3_alignment

    template<class scalar_type, template<class, index, index> class vector>
    class base<scalar_type, 1, 4, vector>
    {
    public:
        using scalar_ref = scalar_type&;
        using scalar_const_ref = const scalar_type&;

        constexpr base() = default;
        constexpr base(const base&) = default;
        constexpr base(base&&) noexcept = default;
        constexpr base& operator=(const base&) = default;
        constexpr base& operator=(base&&) noexcept = default;
        ~base() = default;

        constexpr bool operator==(const base& b) const = default;

        constexpr scalar_ref at(index);
        constexpr scalar_const_ref at(index) const;

        constexpr scalar_ref at(index, index);
        constexpr scalar_const_ref at(index, index) const;

        scalar_type x, y, z, w;
    };
}  // namespace abacus

#include "matrix_base.inl"
