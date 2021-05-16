#include <iostream>

namespace abacus
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

    template<class _scalar_type, index _rows, index _columns>
    std::ostream& operator<<(std::ostream& os, const matrix<_scalar_type, _rows, _columns>& m)
    {
        if constexpr (_rows == 1)
        {
            os << "vec" << _columns << '(';
            for (index column = 0; column < _columns - 1; ++column)
            {
                os << m.at(column) << ", ";
            }
            os << m.at(_columns - 1) << ')';
        }
        else
        {
            os << "mat" << _rows << 'x' << _columns << "(\n    ";
            for (index row = 0; row < _rows - 1; ++row)
            {
                for (index column = 0; column < _columns - 1; ++column)
                {
                    os << m.at(row, column) << ", ";
                }
                os << m.at(row, _columns - 1) << "\n    ";
            }
            for (index column = 0; column < _columns - 1; ++column)
            {
                os << m.at(_rows - 1, column) << ", ";
            }
            os << m.at(_rows - 1, _columns - 1) << "\n)\n";
        }
        return os;
    }
}  // namespace abacus
