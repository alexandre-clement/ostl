
namespace abacus
{
    template<class _scalar_type, index _rows, index _columns>
    constexpr matrix<_scalar_type, _rows, _columns>::matrix()
    {
        zero();
    }

    template<class _scalar_type, index _rows, index _columns>
    template<convertible_to<_scalar_type> argument_type>
    constexpr matrix<_scalar_type, _rows, _columns>::matrix(argument_type value) : matrix()
    {
        if constexpr (is_vector())
        {
            for (index i = 0; i < _columns; ++i)
            {
                this->at(i) = static_cast<scalar_type>(value);
            }
        }
        else
        {
            for (index i = 0; i < std::min(_rows, _columns); ++i)
            {
                this->at(i, i) = static_cast<scalar_type>(value);
            }
        }
    }

    template<class _scalar_type, index _rows, index _columns>
    template<convertible_to<_scalar_type> head, convertible_to<_scalar_type> body, convertible_to<_scalar_type>... tail>
    constexpr matrix<_scalar_type, _rows, _columns>::matrix(head h, body b, tail... t)
    {
        initialize(h, b, t...);
    }

    template<class _scalar_type, index _rows, index _columns>
    template<convertible_to<_scalar_type>... initial_values>
    constexpr void matrix<_scalar_type, _rows, _columns>::initialize(initial_values... values)
    {
        initialize<0>(values...);
    }

    template<class _scalar_type, index _rows, index _columns>
    template<index i, convertible_to<_scalar_type>... initial_values>
    constexpr void matrix<_scalar_type, _rows, _columns>::initialize(initial_values...)
    {
        static_assert(i == size(), "mismatched number of arguments");
    }

    template<class _scalar_type, index _rows, index _columns>
    template<index i, convertible_to<_scalar_type> head, convertible_to<_scalar_type>... tail>
    constexpr void matrix<_scalar_type, _rows, _columns>::initialize(head h, tail... t)
    {
        index row = i / _columns, column = i % _columns;
        this->at(row, column) = static_cast<scalar_type>(h);
        initialize<i + 1>(t...);
    }

    template<class _scalar_type, index _rows, index _columns>
    template<convertible_to<_scalar_type> argument_type>
    constexpr matrix<_scalar_type, _rows, _columns>::matrix(const matrix<argument_type, _rows, _columns>& m) : matrix()
    {
        for (index row = 0; row < _rows; ++row)
        {
            for (index column = 0; column < _columns; ++column)
            {
                this->at(row, column) = static_cast<scalar_type>(m.at(row, column));
            }
        }
    }

}  // namespace abacus
