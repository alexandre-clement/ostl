#pragma once

#include "matrix_base.hpp"

namespace abacus
{
    // hack class to be able to create a sfinea method for matrix
    // see matrix::operator*=
    class sfinae
    {
    public:
        sfinae() = delete;
    };

    template<class _scalar_type, index _rows, index _columns>
    class matrix : public base<_scalar_type, _rows, _columns, matrix>
    {
    public:
        using base_type = base<_scalar_type, _rows, _columns, matrix>;

        using scalar_type = _scalar_type;
        using scalar_ref = scalar_type&;
        using scalar_const_ref = const scalar_type&;

        using type = matrix<scalar_type, _rows, _columns>;
        using type_ref = type&;
        using type_const_ref = const matrix<scalar_type, _rows, _columns>&;
        using transpose_type = matrix<scalar_type, _columns, _rows>;

        constexpr matrix();
        template<convertible_to<_scalar_type> argument_type>
        constexpr explicit matrix(argument_type);
        template<
          convertible_to<_scalar_type> head,
          convertible_to<_scalar_type> body,
          convertible_to<_scalar_type>... tail>
        constexpr matrix(head, body, tail...);
        constexpr matrix(const matrix&) = default;
        template<convertible_to<_scalar_type> argument_type>
        constexpr explicit matrix(const matrix<argument_type, _rows, _columns>&);
        constexpr matrix(matrix&&) noexcept = default;
        constexpr matrix& operator=(const matrix&) = default;
        constexpr matrix& operator=(matrix&&) noexcept = default;
        ~matrix() = default;

        constexpr static index size();
        constexpr static bool is_vector();
        constexpr static bool is_square_matrix();

        constexpr index rows() const;
        constexpr index columns() const;

        constexpr bool operator==(const matrix&) const = default;

        template<convertible_to<_scalar_type> operand>
        constexpr matrix& operator+=(operand);

        template<convertible_to<_scalar_type> operand>
        constexpr matrix& operator-=(operand);

        template<convertible_to<_scalar_type> operand>
        constexpr matrix& operator*=(operand);

        template<convertible_to<_scalar_type> operand>
        constexpr matrix& operator/=(operand);

        constexpr matrix& operator+=(const matrix&);
        constexpr matrix& operator-=(const matrix&);

        constexpr matrix& operator*=(std::conditional_t<is_vector() || is_square_matrix(), const matrix&, sfinae>);

        constexpr matrix& zero();

    private:
        template<convertible_to<_scalar_type>... initial_values>
        constexpr void initialize(initial_values...);

        template<index i, convertible_to<_scalar_type>... initial_values>
        constexpr void initialize(initial_values...);

        template<index i, convertible_to<_scalar_type> head, convertible_to<_scalar_type>... tail>
        constexpr void initialize(head, tail...);
    };

    using vec2 = matrix<float, 1, 2>;
    using vec3 = matrix<float, 1, 3>;
    using vec4 = matrix<float, 1, 4>;

    using mat2x2 = matrix<float, 2, 2>;
    using mat2x3 = matrix<float, 2, 3>;
    using mat2x4 = matrix<float, 2, 4>;
    using mat2 = mat2x2;

    using mat3x2 = matrix<float, 3, 2>;
    using mat3x3 = matrix<float, 3, 3>;
    using mat3x4 = matrix<float, 3, 4>;
    using mat3 = mat3x3;

    using mat4x2 = matrix<float, 4, 2>;
    using mat4x3 = matrix<float, 4, 3>;
    using mat4x4 = matrix<float, 4, 4>;
    using mat4 = mat4x4;
}  // namespace abacus

#include "matrix.inl"
