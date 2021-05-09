#pragma once

#include "printer.hpp"

namespace keros
{
    printer& new_line(printer&);

    printer& space(printer&);

    printer& tab(printer&);

    printer& indent(printer&);

    printer& unindent(printer&);
}  // namespace keros
