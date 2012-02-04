
#include <iostream>

#include <list>

#include "ast.hpp"

int main(void)
{
  std::cout << "Begin" << std::endl;

  AST::AST ast;

  ast << AST::Namespace("toto");
  (ast >> AST::Namespace("toto")) << AST::Class("titi");
  (ast >> AST::Namespace("toto")) >> AST::Class("titi");

  // (ast >> AST::Namespace("::")) << AST::Class("toto");

  // {
  // std::vector<AST::Template::Parameter> listparam = { std::make_pair("int", "N") };
  // AST::Template temp(listparam);
  // }
  // {
  // std::list<AST::Template::Parameter> listparam = { std::make_pair("int", "N") };
  // AST::Template temp(listparam);
  // }

  std::cout << "End" << std::endl;
}
