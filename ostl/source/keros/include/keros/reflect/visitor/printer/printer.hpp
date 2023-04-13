#pragma once

#include <functional>
#include <iomanip>
#include <sstream>
#include <string>
#include <type_traits>
#include <utility>

#include <detail/detail.hpp>

namespace keros
{
    class printer
    {
    public:
        using manipulator = std::function<printer&(printer&)>;

        template<class t>
        printer& operator<<(t&& e)
        {
            detail::match matcher{
              [this](auto&& arg) {
                  apply_indent();
                  m_string_result << arg;
              },
              [this](manipulator m) { m(*this); },
              [this](printer& (*f)(printer&) ) { f(*this); },
            };
            matcher.with(std::forward<t>(e));
            return *this;
        }

        printer& indent();

        printer& unindent();

        std::string to_string() const;

        // request that the printer applies the indentation on the next input
        void request_indentation();

    private:
        void apply_indent();

        std::stringstream m_string_result;
        int m_indent = 0;
        bool m_have_to_apply_indent = true;
    };
}  // namespace keros
