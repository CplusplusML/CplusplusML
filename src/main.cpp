
#include <iostream>

#include <list>

#include "ast.hpp"

int main(void)
{
  AST::AST ast;			// on cree un AST::AST anonyme, ast

  ast << AST::Namespace("toto"); // on insere le namespace "toto"
  // on insere la classe "titi" dans le namespace "toto"
  (ast >> AST::Namespace("toto")) << AST::Class("titi");
  // on recupere la classe "titi" dans le namespace "toto"
  (ast >> AST::Namespace("toto")) >> AST::Class("titi");
}
