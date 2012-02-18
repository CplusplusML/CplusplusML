
#include <iostream>

#include <list>

#include "ast.hpp"

int main(void)
{
  AST::AST ast;

  ast << AST::Namespace("::");
  ast.Get(AST::Namespace("::")) << AST::Class("class1");
  AST::Class &c = ast.Get(AST::Namespace("::")).Get(AST::Class("class1"));
  c.Templates(AST::Template::Type("T"), AST::Template::Variadic("vArgs"), AST::Template::TypeNumeric("V"));
  // c << AST::Pointer(AST::Class("class1"), "_c");
  ast.Get(AST::Namespace("::")) << AST::Class("class2");
  c << AST::Array(ast.Get(AST::Namespace("::")).Get(AST::Class("class2")), "_tab", 42);

  std::cout <<
    ast.Get(AST::Namespace("::")).Get(AST::Class("class1")).Get(AST::Array("_tab")).getSize()
	    << std::endl;
}
