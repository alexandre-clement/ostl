#include "keros/reflect/visitor/printer/manipulator.hpp"

namespace keros
{
    printer& new_line(printer& p)
    {
        p << '\n';
        p.request_indentation();
        return p;
    }

    printer& space(printer& p) { return p << ' '; }

    printer& tab(printer& p) { return p << "    "; }

    printer& indent(printer& p)
    {
        p.indent();
        return p;
    }

    printer& unindent(printer& p)
    {
        p.unindent();
        return p;
    }
}  // namespace keros
