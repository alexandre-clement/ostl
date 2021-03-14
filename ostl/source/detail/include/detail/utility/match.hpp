#pragma once

#include <utility>

namespace detail
{
    // simulate a match with operator
    // example usage :
    // match
    // {
    //     [](auto&& arg) { std::cout << arg; },
    //     [](double arg) { std::cout << std::scientific << arg; },
    //     [](bool arg) { std::cout << std::boolalpha << arg; },
    // }.with(e);
    //
    // note : be carefull with clang, one might want to split the declaration of the match object from the `with` call.
    // otherwise, the above example won't compile on clang. it compiles with gcc 10.0 and msvc 19.27.
    // c.f (https://bugs.llvm.org/show_bug.cgi?id=39663)
    template<class... lambdas>
    struct match : lambdas...
    {
        using lambdas::operator()...;

        template<class... args>
        void with(args&&... a)
        {
            this->operator()(std::forward<args>(a)...);
        }
    };

    template<class... lambdas>
    match(lambdas...) -> match<lambdas...>;
}  // namespace detail
