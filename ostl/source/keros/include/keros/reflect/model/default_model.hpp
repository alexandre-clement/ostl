#pragma once

#include "element.hpp"
#include "keros/reflect/code/code.hpp"
#include "keros/reflect/declaration/declaration.hpp"

namespace keros
{
    template<template<class...> class pointer>
    using default_model = model<pointer,
      element,
      // code
      expression,
      // declaration
      function,
      named,
      shader,
      type,
      typed,
      variable>;
}