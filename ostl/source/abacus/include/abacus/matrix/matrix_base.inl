namespace abacus
{
    template<class _scalar_type, index rows, index columns, template<class, index, index> class vector>
    constexpr typename array<_scalar_type, rows, columns, vector>::scalar_ref
      array<_scalar_type, rows, columns, vector>::at(index row, index column)
    {
        return data.at(row).at(column);
    }

    template<class _scalar_type, index rows, index columns, template<class, index, index> class vector>
    constexpr typename array<_scalar_type, rows, columns, vector>::scalar_const_ref
      array<_scalar_type, rows, columns, vector>::at(index row, index column) const
    {
        return data.at(row).at(column);
    }

    template<class _scalar_type, index rows, index columns, template<class, index, index> class vector>
    constexpr vector<_scalar_type, 1, columns>& array<_scalar_type, rows, columns, vector>::row(index r)
    {
        return data.at(r);
    }

    template<class _scalar_type, index columns, template<class, index, index> class vector>
    constexpr typename array<_scalar_type, 1, columns, vector>::scalar_ref
      array<_scalar_type, 1, columns, vector>::at(index row, index column)
    {
        if (row == 0)
        {
            return data.at(column);
        }
        throw std::out_of_range("");
    }

    template<class _scalar_type, index columns, template<class, index, index> class vector>
    constexpr typename array<_scalar_type, 1, columns, vector>::scalar_const_ref
      array<_scalar_type, 1, columns, vector>::at(index row, index column) const
    {
        if (row == 0)
        {
            return data.at(column);
        }
        throw std::out_of_range("");
    }

    template<class scalar_type, index rows, index columns, template<class, index, index> class vector>
    constexpr vector<scalar_type, 1, columns>& base<scalar_type, rows, columns, vector>::row(index r)
    {
        return data.row(r);
    }

    template<class scalar_type, index rows, index columns, template<class, index, index> class vector>
    constexpr typename base<scalar_type, rows, columns, vector>::scalar_ref
      base<scalar_type, rows, columns, vector>::at(index r, index c)
    {
        return data.at(r, c);
    }

    template<class scalar_type, index rows, index columns, template<class, index, index> class vector>
    constexpr typename base<scalar_type, rows, columns, vector>::scalar_const_ref
      base<scalar_type, rows, columns, vector>::at(index r, index c) const
    {
        return data.at(r, c);
    }

    template<class scalar_type, template<class, index, index> class vector>
    constexpr typename base<scalar_type, 1, 2, vector>::scalar_ref base<scalar_type, 1, 2, vector>::at(index c)
    {
        if (c == 0)
        {
            return x;
        }
        else if (c == 1)
        {
            return y;
        }
        throw std::out_of_range("");
    }

    template<class scalar_type, template<class, index, index> class vector>
    constexpr typename base<scalar_type, 1, 2, vector>::scalar_const_ref
      base<scalar_type, 1, 2, vector>::at(index c) const
    {
        if (c == 0)
        {
            return x;
        }
        else if (c == 1)
        {
            return y;
        }
        throw std::out_of_range("");
    }

    template<class scalar_type, template<class, index, index> class vector>
    constexpr typename base<scalar_type, 1, 2, vector>::scalar_ref base<scalar_type, 1, 2, vector>::at(index r, index c)
    {
        if (r == 0)
        {
            if (c == 0)
            {
                return x;
            }
            else if (c == 1)
            {
                return y;
            }
        }
        throw std::out_of_range("");
    }

    template<class scalar_type, template<class, index, index> class vector>
    constexpr typename base<scalar_type, 1, 2, vector>::scalar_const_ref
      base<scalar_type, 1, 2, vector>::at(index r, index c) const
    {
        if (r == 0)
        {
            if (c == 0)
            {
                return x;
            }
            else if (c == 1)
            {
                return y;
            }
        }
        throw std::out_of_range("");
    }

    template<class scalar_type, template<class, index, index> class vector>
    constexpr typename base<scalar_type, 1, 3, vector>::scalar_ref base<scalar_type, 1, 3, vector>::at(index c)
    {
        if (c == 0)
        {
            return x;
        }
        else if (c == 1)
        {
            return y;
        }
        else if (c == 2)
        {
            return z;
        }
        throw std::out_of_range("");
    }

    template<class scalar_type, template<class, index, index> class vector>
    constexpr typename base<scalar_type, 1, 3, vector>::scalar_const_ref
      base<scalar_type, 1, 3, vector>::at(index c) const
    {
        if (c == 0)
        {
            return x;
        }
        else if (c == 1)
        {
            return y;
        }
        else if (c == 2)
        {
            return z;
        }
        throw std::out_of_range("");
    }

    template<class scalar_type, template<class, index, index> class vector>
    constexpr typename base<scalar_type, 1, 3, vector>::scalar_ref base<scalar_type, 1, 3, vector>::at(index r, index c)
    {
        if (r == 0)
        {
            if (c == 0)
            {
                return x;
            }
            else if (c == 1)
            {
                return y;
            }
            else if (c == 2)
            {
                return z;
            }
        }
        throw std::out_of_range("");
    }

    template<class scalar_type, template<class, index, index> class vector>
    constexpr typename base<scalar_type, 1, 3, vector>::scalar_const_ref
      base<scalar_type, 1, 3, vector>::at(index r, index c) const
    {
        if (r == 0)
        {
            if (c == 0)
            {
                return x;
            }
            else if (c == 1)
            {
                return y;
            }
            else if (c == 2)
            {
                return z;
            }
        }
        throw std::out_of_range("");
    }

    template<class scalar_type, template<class, index, index> class vector>
    constexpr typename base<scalar_type, 1, 4, vector>::scalar_ref base<scalar_type, 1, 4, vector>::at(index c)
    {
        if (c == 0)
        {
            return x;
        }
        else if (c == 1)
        {
            return y;
        }
        else if (c == 2)
        {
            return z;
        }
        else if (c == 3)
        {
            return w;
        }
        throw std::out_of_range("");
    }

    template<class scalar_type, template<class, index, index> class vector>
    constexpr typename base<scalar_type, 1, 4, vector>::scalar_const_ref
      base<scalar_type, 1, 4, vector>::at(index c) const
    {
        if (c == 0)
        {
            return x;
        }
        else if (c == 1)
        {
            return y;
        }
        else if (c == 2)
        {
            return z;
        }
        else if (c == 3)
        {
            return w;
        }
        throw std::out_of_range("");
    }

    template<class scalar_type, template<class, index, index> class vector>
    constexpr typename base<scalar_type, 1, 4, vector>::scalar_ref base<scalar_type, 1, 4, vector>::at(index r, index c)
    {
        if (r == 0)
        {
            if (c == 0)
            {
                return x;
            }
            else if (c == 1)
            {
                return y;
            }
            else if (c == 2)
            {
                return z;
            }
            else if (c == 3)
            {
                return w;
            }
        }
        throw std::out_of_range("");
    }

    template<class scalar_type, template<class, index, index> class vector>
    constexpr typename base<scalar_type, 1, 4, vector>::scalar_const_ref
      base<scalar_type, 1, 4, vector>::at(index r, index c) const
    {
        if (r == 0)
        {
            if (c == 0)
            {
                return x;
            }
            else if (c == 1)
            {
                return y;
            }
            else if (c == 2)
            {
                return z;
            }
            else if (c == 3)
            {
                return w;
            }
        }
        throw std::out_of_range("");
    }
}  // namespace abacus
