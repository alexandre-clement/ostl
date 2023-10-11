#pragma once

#include <iostream>
#include <string>

#include <detail/detail.hpp>

#include "keros/reflect/model/utility.hpp"
#include "meta_visitor.hpp"
#include "printer/manipulator.hpp"
#include "printer/printer.hpp"

namespace keros
{
    // this visitor exports the element as a std::string formatted for glsl
    make_visitor(glsl_exporter)
    {
    public:
        std::string result() const { return out.to_string(); }

    protected:
        template<class... operands>
        printer::manipulator parenthesis(operands && ... p_operands)
        {
            return [&](printer& p) -> printer& {
                p << '(';
                [[maybe_unused]] detail::match matcher = {[&](auto&& any) { this->out << any; },
                  [&]<class operand>(const apply_pointer_to<base, operand>& op) { this->scan(op); }};
                (matcher.with(p_operands), ...);
                return p << ')';
            };
        }

        template<detail::iterable derived>
        printer::manipulator braces(const derived& p_iterable)
        {
            return [&](printer& p) -> printer& {
                p << '{' << new_line << indent;
                for (const auto& e : p_iterable)
                {
                    this->scan(e);
                    this->out << new_line;
                }
                return p << unindent << '}';
            };
        }

        printer out;
    };

    overload(glsl_exporter, element) {}

    overload(glsl_exporter, function)
    {
        this->out << host.typeof->name << space << host.name << this->parenthesis() << new_line;
        this->scan(host.body);
        this->out << new_line;
    }

    overload(glsl_exporter, shader)
    {
        for (const auto& e : host.named_elements)
        {
            this->scan(e);
            this->out << new_line;
        }
    }

    overload(glsl_exporter, code_block)
    {
        this->out << '{' << new_line << indent;
        for (const auto& e : host.statements)
        {
            this->scan(e);
            this->out << new_line;
        }
        this->out << unindent << '}';
    }

    overload(glsl_exporter, binary_expression)
    {
        this->scan(host.left);
        this->out << space;
        this->scan(host.right);
    }

    overload(glsl_exporter, addition)
    {
        this->scan(host.left);
        this->out << '+';
        this->scan(host.right);
    }

    overload(glsl_exporter, literal) { this->out << host.value; }

    overload(glsl_exporter, file)
    {
        for (const auto& e : host.directives)
        {
            this->scan(e);
        }
        this->out << new_line;
        for (const auto& e : host.functions)
        {
            this->scan(e);
            this->out << new_line;
        }
    }

    overload(glsl_exporter, directive) { this->out << '#'; }

    overload(glsl_exporter, version) { this->out << "#version" << space << host.value << new_line; }

    template<class host>
    std::string to_glsl(const host& h)
    {
        return glsl_exporter<base_of<host>>().scan(h).result();
    }
}  // namespace keros
