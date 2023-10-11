#pragma once

#include "element.hpp"
#include "keros/reflect/code/code.hpp"
#include "keros/reflect/declaration/declaration.hpp"

namespace keros
{
    template<template<class...> class pointer>
    using metamodel = model<pointer,
      element,
      // code
      code_element,
      statement,
      statement_list,
      code_block,
      expression,
      literal,
      binary_expression,
      addition,
      for_,
      if_,
      directive,
      version,
      // declaration
      file,
      function,
      named,
      shader,
      type,
      typed,
      variable>;
}