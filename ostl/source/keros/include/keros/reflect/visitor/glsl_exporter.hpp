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

    overload(glsl_exporter, type) { this->out << host.name << space; }

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

    overload(glsl_exporter, for_)
    {
        this->out << "for (";
        this->scan(host.initializer);
        this->out << ';' << space;
        this->scan(host.halt_condition);
        this->out << ';' << space;
        this->scan(host.increment);
        this->out << ')' << new_line << '{' << new_line << indent;

        this->out << unindent << '}';
    }

    overload(glsl_exporter, unary_expression) { this->scan(host.operand); }

    overload(glsl_exporter, prefix_increment)
    {
        this->out << "++";
        this->visit_cast<unary_expression<base>>(host);
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
        this->out << space << '+' << space;
        this->scan(host.right);
    }

    overload(glsl_exporter, less_than)
    {
        this->scan(host.left);
        this->out << space << '<' << space;
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

    overload(glsl_exporter, variable)
    {
        for (const auto& e : host.modifiers)
        {
            this->scan(e);
        }
        this->scan(host.typeof);
        this->out << host.name;
    }

    overload(glsl_exporter, right_hand_side_receiver)
    {
        this->out << space << '=' << space;
        this->scan(host.right_hand_side);
    }

    overload(glsl_exporter, local_variable)
    {
        this->visit_cast<variable<base>>(host);
        this->visit_cast<right_hand_side_receiver<base>>(host);
    }

    overload(glsl_exporter, uniform) { this->out << "uniform" << space; }

    overload(glsl_exporter, reference) { this->out << host.name; }

    overload(glsl_exporter, variable_reference) { this->visit_cast<reference<base>>(host); }

    template<class host>
    std::string to_glsl(const host& h)
    {
        return glsl_exporter<base_of<host>>().scan(h).result();
    }
}  // namespace keros
