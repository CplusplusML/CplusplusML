
#include <iostream>

#include "assed.hpp"

int main(void)
{
  AST::AST ast;

  ast.Insert(AST::Namespace("Namespace"));
  ast.Get(AST::Namespace("Namespace"))->Insert(AST::Class("Class1"));
  ast.Get(AST::Namespace("Namespace"))->Insert(AST::Class("Class2"));
  {
    auto c = ast.Get(AST::Namespace("Namespace"))->Get(AST::Class("Class1"));

    c->Insert(AST::Class("Class_nested"), AST::Visibility::PUBLIC);

    c->Insert(AST::Temp("i", "int i_"));

    c->Inherit(
	       *ast.Get(AST::Namespace("Namespace"))->Get(AST::Class("Class2"))
	       );
  }
  {
    AST::Class bar("Bar");
    bar.Templates(AST::Template::Type("T"));
    ast.Get(AST::Namespace("Namespace"))->Insert(bar);

    AST::Template::Toto c("C");
    c.Templates(AST::Template::Type("T"));

    AST::Class foo("Foo");
    foo.Templates(c);
    ast.Get(AST::Namespace("Namespace"))->Insert(foo);
  }
  std::cout << ast << std::endl;
}
