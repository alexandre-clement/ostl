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
      right_hand_side_receiver,
      local_variable,
      unary_expression,
      prefix_increment,
      binary_expression,
      addition,
      less_than,
      for_,
      if_,
      modifier,
      uniform,
      directive,
      version,
      reference,
      variable_reference,
      // declaration
      file,
      function,
      named,
      shader,
      type,
      typed,
      modifiable,
      variable>;
}