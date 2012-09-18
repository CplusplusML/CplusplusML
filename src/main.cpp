
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

  c->Insert(AST::Temp("i", "int i_"));

  c->Inherit(
	     *ast.Get(AST::Namespace("Namespace"))->Get(AST::Class("Class2"))
	     );

  std::cout << ast << std::endl;
}
