
#include <iostream>

#include "assed.hpp"

int main(void)
{
  AST::AST ast;

  ast.Insert(AST::Namespace("Namespace"));
  ast.Get(AST::Namespace("Namespace"))->Insert(AST::Class("Class1"));
  ast.Get(AST::Namespace("Namespace"))->Insert(AST::Class("Class2"));

  auto c = ast.Get(AST::Namespace("Namespace"))->Get(AST::Class("Class1"));

  c->Insert(AST::Class("Class_nested"), AST::Visibility::PUBLIC);

  std::cout << ast << std::endl;
}
