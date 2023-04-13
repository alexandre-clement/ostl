#include "keros/reflect/visitor/printer/printer.hpp"

#include "keros/reflect/visitor/printer/manipulator.hpp"

namespace keros
{
    std::string printer::to_string() const { return m_string_result.str(); }

    printer& printer::indent()
    {
        ++m_indent;
        return *this;
    }

    printer& printer::unindent()
    {
        m_indent = std::max(0, m_indent - 1);
        return *this;
    }

    void printer::request_indentation() { m_have_to_apply_indent = true; }

    void printer::apply_indent()
    {
        if (m_have_to_apply_indent)
        {
            m_have_to_apply_indent = false;
            for (int i = 0; i < m_indent; ++i)
            {
                *this << tab;
            }
        }
    }
}  // namespace keros
