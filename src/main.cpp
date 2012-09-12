
#include <iostream>

#include "assed.hpp"

int main(void)
{
  AST::AST ast;

  // rvalue, on s'en branle, on fait un new avec,
  // on l'assigne a un shared_ptr dans le std::vector
  ast << AST::Namespace("::");

  return (0);

  // on veut recuperer une reference au-dit Namespace
  // cependant, si jamais ast est detruit, on veut
  // quand meme avoir une reference namespc valide
  // le coup d'utiliser des references, et bien ca pue
  // du cul, surtout que derriere c'est gere par des
  // shared_ptr et qu'on doit en profiter !
  AST::Namespace &namespc = ast.Get(AST::Namespace("::"));
}


 /*
  ast.Get(AST::Namespace("::")) << AST::Class("class1");
  ast.Get(AST::Namespace("::")) << AST::Class("class2") << AST::Class("class42");

  std::cout << ast << std::endl;

  AST::Class &c = ast.Get(AST::Namespace("::")).Get(AST::Class("class1"));

  c << AST::Class("SubClass");

  c << AST::Inheritance(ast.Get(AST::Namespace("::")).Get(AST::Class("class2")));
*/

  //  c.Get(AST::Namespace("Namespace42"));

  // c.Templates(AST::Template::Type("T"), AST::Template::Variadic("vArgs"), AST::Template::TypeNumeric("V"));
  // c << AST::Visibility::PRIVATE << AST::Array(ast.Get(AST::Namespace("::")).Get(AST::Class("class2")), "_tab", 42);
  // c.Get(AST::Array("_tab"));
  //  c << AST::Visibility::PUBLIC << AST::Function("function1");
