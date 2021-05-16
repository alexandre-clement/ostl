#pragma once

namespace detail
{
    template<class t>
    class property
    {
    public:
        property()
            : property([&]() -> const t& { return m_value; },
              [&](const t& p_value) -> const t& { return m_value = p_value; })
        {
        }

        property(std::function<const t&(t&)> p_getter, std::function<const t&(t&, const t&)> p_setter)
            : property([&, p_getter]() -> const t& { return p_getter(m_value); },
              [&, p_setter](const t& p_value) -> const t& { return p_setter(m_value, p_value); })
        {
        }

        operator const t&() const { return m_getter(); }

        const t& operator=(const t& other) { return m_setter(other); }

        bool operator==(const t& other) const { return static_cast<const t&>(*this) == other; }

    private:
        property(std::function<const t&()> p_getter, std::function<const t&(const t&)> p_setter)
            : m_getter(p_getter)
            , m_setter(p_setter)
            , m_value{}
        {
        }

        t m_value;

        std::function<const t&()> m_getter;
        std::function<const t&(const t&)> m_setter;
    };
}  // namespace detail