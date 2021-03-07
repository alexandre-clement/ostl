
namespace abacus
{
    template<class scalar_type, index rows, index columns, convertible_to<scalar_type> operand>
    constexpr matrix<scalar_type, rows, columns> operator+(const matrix<scalar_type, rows, columns>& m, operand s)
    {
        matrix<scalar_type, rows, columns> result;
        for (index row = 0; row < rows; ++row)
        {
            for (index column = 0; column < columns; ++column)
            {
                result.at(row, column) = m.at(row, column) + static_cast<scalar_type>(s);
            }
        }
        return result;
    }

    template<class scalar_type, index rows, index columns, convertible_to<scalar_type> operand>
    constexpr matrix<scalar_type, rows, columns> operator-(const matrix<scalar_type, rows, columns>& m, operand s)
    {
        matrix<scalar_type, rows, columns> result;
        for (index row = 0; row < rows; ++row)
        {
            for (index column = 0; column < columns; ++column)
            {
                result.at(row, column) = m.at(row, column) - static_cast<scalar_type>(s);
            }
        }
        return result;
    }

    template<class scalar_type, index rows, index columns, convertible_to<scalar_type> operand>
    constexpr matrix<scalar_type, rows, columns> operator*(const matrix<scalar_type, rows, columns>& m, operand s)
    {
        matrix<scalar_type, rows, columns> result;
        for (index row = 0; row < rows; ++row)
        {
            for (index column = 0; column < columns; ++column)
            {
                result.at(row, column) = m.at(row, column) * static_cast<scalar_type>(s);
            }
        }
        return result;
    }

    template<class scalar_type, index rows, index columns, convertible_to<scalar_type> operand>
    constexpr matrix<scalar_type, rows, columns> operator/(const matrix<scalar_type, rows, columns>& m, operand s)
    {
        if (s == 0)
        {
            throw std::domain_error("division by zero");
        }
        matrix<scalar_type, rows, columns> result;

        for (index row = 0; row < rows; ++row)
        {
            for (index column = 0; column < columns; ++column)
            {
                result.at(row, column) = m.at(row, column) / static_cast<scalar_type>(s);
            }
        }
        return result;
    }
    template<class scalar_type, index rows, index columns, convertible_to<scalar_type> operand>
    constexpr matrix<scalar_type, rows, columns> operator+(operand s, const matrix<scalar_type, rows, columns>& m)
    {
        matrix<scalar_type, rows, columns> result;
        for (index row = 0; row < rows; ++row)
        {
            for (index column = 0; column < columns; ++column)
            {
                result.at(row, column) = static_cast<scalar_type>(s) + m.at(row, column);
            }
        }
        return result;
    }

    template<class scalar_type, index rows, index columns, convertible_to<scalar_type> operand>
    constexpr matrix<scalar_type, rows, columns> operator-(operand s, const matrix<scalar_type, rows, columns>& m)
    {
        matrix<scalar_type, rows, columns> result;
        for (index row = 0; row < rows; ++row)
        {
            for (index column = 0; column < columns; ++column)
            {
                result.at(row, column) = static_cast<scalar_type>(s) - m.at(row, column);
            }
        }
        return result;
    }

    template<class scalar_type, index rows, index columns, convertible_to<scalar_type> operand>
    constexpr matrix<scalar_type, rows, columns> operator*(operand s, const matrix<scalar_type, rows, columns>& m)
    {
        matrix<scalar_type, rows, columns> result;
        for (index row = 0; row < rows; ++row)
        {
            for (index column = 0; column < columns; ++column)
            {
                result.at(row, column) = static_cast<scalar_type>(s) * m.at(row, column);
            }
        }
        return result;
    }

    template<class scalar_type, index rows, index columns, convertible_to<scalar_type> operand>
    constexpr matrix<scalar_type, rows, columns> operator/(operand s, const matrix<scalar_type, rows, columns>& m)
    {
        matrix<scalar_type, rows, columns> result;

        for (index row = 0; row < rows; ++row)
        {
            for (index column = 0; column < columns; ++column)
            {
                if (m.at(row, column) == 0)
                {
                    throw std::domain_error("division by zero");
                }
                result.at(row, column) = static_cast<scalar_type>(s) / m.at(row, column);
            }
        }
        return result;
    }

    template<class _scalar_type, index _rows, index _columns>
    template<convertible_to<_scalar_type> operand>
    constexpr matrix<_scalar_type, _rows, _columns>& matrix<_scalar_type, _rows, _columns>::operator+=(operand s)
    {
        for (index row = 0; row < _rows; ++row)
        {
            for (index column = 0; column < _columns; ++column)
            {
                this->at(row, column) += static_cast<scalar_type>(s);
            }
        }
        return *this;
    }

    template<class _scalar_type, index _rows, index _columns>
    template<convertible_to<_scalar_type> operand>
    constexpr matrix<_scalar_type, _rows, _columns>& matrix<_scalar_type, _rows, _columns>::operator-=(operand s)
    {
        for (index row = 0; row < _rows; ++row)
        {
            for (index column = 0; column < _columns; ++column)
            {
                this->at(row, column) -= static_cast<scalar_type>(s);
            }
        }
        return *this;
    }

    template<class _scalar_type, index _rows, index _columns>
    template<convertible_to<_scalar_type> operand>
    constexpr matrix<_scalar_type, _rows, _columns>& matrix<_scalar_type, _rows, _columns>::operator*=(operand s)
    {
        for (index row = 0; row < _rows; ++row)
        {
            for (index column = 0; column < _columns; ++column)
            {
                this->at(row, column) *= static_cast<scalar_type>(s);
            }
        }
        return *this;
    }

    template<class _scalar_type, index _rows, index _columns>
    template<convertible_to<_scalar_type> operand>
    constexpr matrix<_scalar_type, _rows, _columns>& matrix<_scalar_type, _rows, _columns>::operator/=(operand s)
    {
        if (s == 0)
        {
            throw std::domain_error("division by zero");
        }
        for (index row = 0; row < _rows; ++row)
        {
            for (index column = 0; column < _columns; ++column)
            {
                this->at(row, column) /= static_cast<scalar_type>(s);
            }
        }
        return *this;
    }

    template<class scalar_type, index rows, index columns>
    constexpr matrix<scalar_type, rows, columns>
      operator+(const matrix<scalar_type, rows, columns>& a, const matrix<scalar_type, rows, columns>& b)
    {
        matrix<scalar_type, rows, columns> result;
        for (index row = 0; row < rows; ++row)
        {
            for (index column = 0; column < columns; ++column)
            {
                result.at(row, column) = a.at(row, column) + b.at(row, column);
            }
        }
        return result;
    }

    template<class scalar_type, index rows, index columns>
    constexpr matrix<scalar_type, rows, columns>
      operator-(const matrix<scalar_type, rows, columns>& a, const matrix<scalar_type, rows, columns>& b)
    {
        matrix<scalar_type, rows, columns> result;
        for (index row = 0; row < rows; ++row)
        {
            for (index column = 0; column < columns; ++column)
            {
                result.at(row, column) = a.at(row, column) - b.at(row, column);
            }
        }
        return result;
    }

    template<class scalar_type, index columns>
    constexpr matrix<scalar_type, 1, columns>
      operator*(const matrix<scalar_type, 1, columns>& a, const matrix<scalar_type, 1, columns>& b)
    {
        matrix<scalar_type, 1, columns> result;
        for (index column = 0; column < columns; ++column)
        {
            result.at(0, column) = a.at(0, column) * b.at(0, column);
        }
        return result;
    }

    template<class scalar_type, index rows, index columns, index result_columns>
    constexpr matrix<scalar_type, rows, result_columns>
      operator*(const matrix<scalar_type, rows, columns>& a, const matrix<scalar_type, columns, result_columns>& b)
    {
        matrix<scalar_type, rows, result_columns> result;
        for (index row = 0; row < rows; ++row)
        {
            for (index column = 0; column < result_columns; ++column)
            {
                for (index k = 0; k < columns; k++)
                {
                    result.at(row, column) += a.at(row, k) * b.at(k, column);
                }
            }
        }
        return result;
    }

    template<class _scalar_type, index _rows, index _columns>
    constexpr matrix<_scalar_type, _rows, _columns>&
      matrix<_scalar_type, _rows, _columns>::operator+=(const matrix& other)
    {
        for (index row = 0; row < _rows; ++row)
        {
            for (index column = 0; column < _columns; ++column)
            {
                this->at(row, column) += other.at(row, column);
            }
        }
        return *this;
    }

    template<class _scalar_type, index _rows, index _columns>
    constexpr matrix<_scalar_type, _rows, _columns>&
      matrix<_scalar_type, _rows, _columns>::operator-=(const matrix& other)
    {
        for (index row = 0; row < _rows; ++row)
        {
            for (index column = 0; column < _columns; ++column)
            {
                this->at(row, column) -= other.at(row, column);
            }
        }
        return *this;
    }

    template<class _scalar_type, index _rows, index _columns>
    constexpr matrix<_scalar_type, _rows, _columns>& matrix<_scalar_type, _rows, _columns>::operator*=(
      std::conditional_t<is_vector() || is_square_matrix(), const matrix&, sfinae> other)
    {
        if constexpr (is_vector())
        {
            for (index column = 0; column < _columns; ++column)
            {
                this->at(column) *= other.at(column);
            }
        }
        else if constexpr (is_square_matrix())
        {
            matrix temp(*this);
            zero();
            for (index row = 0; row < _rows; ++row)
            {
                for (index column = 0; column < _columns; ++column)
                {
                    for (index k = 0; k < _columns; k++)
                    {
                        this->at(row, column) += temp.at(row, k) * other.at(k, column);
                    }
                }
            }
        }
        return *this;
    }
}  // namespace abacus
