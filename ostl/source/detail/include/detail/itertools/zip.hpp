#pragma once

#include <functional>
#include <iterator>
#include <tuple>
#include <utility>

#include "tuple_transform.hpp"

namespace detail
{
    template<typename... iterators>
    class zip_iterator
    {
    public:
        zip_iterator(std::tuple<iterators...> p_iterators) : m_iterators(std::move(p_iterators)) {}
        zip_iterator(const zip_iterator&) = default;
        zip_iterator(zip_iterator&&) noexcept = default;

        zip_iterator& operator=(const zip_iterator&) = default;
        zip_iterator& operator=(zip_iterator&&) noexcept = default;

        bool operator!=(const zip_iterator& other) const { return m_iterators != other.m_iterators; }

        zip_iterator& operator++()
        {
            tuple_transform([](auto& iter) { ++iter; }, m_iterators);
            return *this;
        }

        decltype(auto) operator*()
        {
            return tuple_transform([](auto& i) -> decltype(auto) { return *i; }, m_iterators);
        }

    private:
        std::tuple<iterators...> m_iterators;
    };

    template<typename... containers>
    class zip
    {
    public:
        using iterator = zip_iterator<decltype(std::begin(std::declval<containers&>()))...>;

        explicit zip(containers&... p_containers) : m_containers(std::forward<containers&>(p_containers)...) {}

        iterator begin()
        {
            return iterator(tuple_transform([](auto& i) { return std::begin(i); }, m_containers));
        }
        iterator end()
        {
            return iterator(tuple_transform([](auto& i) { return std::end(i); }, m_containers));
        }

    private:
        std::tuple<containers&...> m_containers;
    };
}  // namespace detail