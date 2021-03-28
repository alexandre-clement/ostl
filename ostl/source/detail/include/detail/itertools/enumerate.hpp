#pragma once

#include <cstdarg>
#include <cstddef>
#include <tuple>
#include <utility>

namespace detail
{
    using size = std::size_t;

    template<class iterable_t>
    class enumerate
    {
    public:
        using iterable_type = iterable_t;

        struct iterator
        {
            using iterator_type = decltype(std::begin(std::declval<iterable_type>()));

            size index;
            iterator_type iter;

            bool operator!=(const iterator& other) const { return iter != other.iter; }
            iterator& operator++()
            {
                ++index;
                ++iter;
                return *this;
            }
            auto operator*() const { return std::tie(index, *iter); }
        };

        enumerate(const iterable_type& p_iterable) : iterable(p_iterable) {}
        enumerate(iterable_type&& p_iterable) : iterable(std::move(std::forward<iterable_type>(p_iterable))) {}
        enumerate(const enumerate& e) : iterable(e.iterable) {}
        ~enumerate() = default;

        iterator begin() { return iterator{0, std::begin(iterable)}; }
        iterator end() { return iterator{0, std::end(iterable)}; }

        iterable_type iterable;
    };
}  // namespace detail