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

    overload(glsl_exporter, file) {}

    overload(glsl_exporter, function)
    {
        this->out << host.typeof->name << ' ' << host.name << this->parenthesis() << new_line
                  << this->braces(std::array<element<base>, 0>()) << new_line;
    }
}  // namespace keros
