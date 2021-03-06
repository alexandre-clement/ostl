
namespace heron
{
    template<class _scalar_type, index _rows, index _columns>
    constexpr index matrix<_scalar_type, _rows, _columns>::rows() const
    {
        return _rows;
    }

    template<class _scalar_type, index _rows, index _columns>
    constexpr index matrix<_scalar_type, _rows, _columns>::columns() const
    {
        return _columns;
    }

    template<class _scalar_type, index _rows, index _columns>
    constexpr matrix<_scalar_type, _rows, _columns>& matrix<_scalar_type, _rows, _columns>::zero()
    {
        for (index row = 0; row < _rows; ++row)
        {
            for (index column = 0; column < _columns; ++column)
            {
                this->at(row, column) = scalar_type();
            }
        }
        return *this;
    }

    template<class _scalar_type, index _rows, index _columns>
    constexpr index matrix<_scalar_type, _rows, _columns>::size()
    {
        return _rows * _columns;
    }

    template<class _scalar_type, index _rows, index _columns>
    constexpr bool matrix<_scalar_type, _rows, _columns>::is_vector()
    {
        return _rows == 1;
    }

    template<class _scalar_type, index _rows, index _columns>
    constexpr bool matrix<_scalar_type, _rows, _columns>::is_square_matrix()
    {
        return _rows == _columns;
    }
}  // namespace heron
