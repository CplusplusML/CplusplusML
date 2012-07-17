
#include <iostream>

#include <list>

#include "assed.hpp"

int main(void)
{
  AST::AST ast;

  ast << AST::Namespace("::");
  ast.Get(AST::Namespace("::")) << AST::Class("class1");
  ast.Get(AST::Namespace("::")) << AST::Class("class2") << AST::Class("class42");

  AST::Class &c = ast.Get(AST::Namespace("::")).Get(AST::Class("class1"));

  c << AST::Class("SubClass");

  c << AST::Inheritance(ast.Get(AST::Namespace("::")).Get(AST::Class("class2")));

  //  c.Get(AST::Namespace("Namespace42"));

  // c.Templates(AST::Template::Type("T"), AST::Template::Variadic("vArgs"), AST::Template::TypeNumeric("V"));
  // c << AST::Visibility::PRIVATE << AST::Array(ast.Get(AST::Namespace("::")).Get(AST::Class("class2")), "_tab", 42);
  // c.Get(AST::Array("_tab"));
  //  c << AST::Visibility::PUBLIC << AST::Function("function1");

  std::cout << ast << std::endl;
}
