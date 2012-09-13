
#include <iostream>

#include "assed.hpp"

int main(void)
{
  AST::AST ast;

  ast.Insert(AST::Namespace("::"));
  ast.Get(AST::Namespace("::"))->Insert(AST::Class("class1"));
  ast.Get(AST::Namespace("::"))->Insert(AST::Class("class2"));

  std::cout << ast << std::endl;
}
