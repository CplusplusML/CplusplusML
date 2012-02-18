
#include <iostream>

#include <list>

#include "ast.hpp"

int main(void)
{
  AST::AST ast;

  ast << AST::Namespace("toto");
  ast.Get(AST::Namespace("toto")) << AST::Class("titi");
  ast.Get(AST::Namespace("toto")).Get(AST::Class("titi")) << AST::Value(AST::Class("tata"), "t");

  AST::Class c("class1");
  c.Templates(AST::Template::Type("T"), AST::Template::Variadic("vArgs"), AST::Template::TypeNumeric("V"));
  // c << AST::Pointer(AST::Class("class1"), "_c");
}
