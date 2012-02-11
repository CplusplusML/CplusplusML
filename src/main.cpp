
#include <iostream>

#include <list>

#include "ast.hpp"

int main(void)
{
  AST::AST ast;

  ast << AST::Namespace("toto");
  ast.Get(AST::Namespace("toto")) << AST::Class("titi");
  ast.Get(AST::Namespace("toto")).Get(AST::Class("titi")) << AST::Value(AST::Class("tata"), "t");
}
