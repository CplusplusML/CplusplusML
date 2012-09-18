
#include <iostream>

#include "assed.hpp"

int main(void)
{
  AST::AST ast;

  ast.Insert(AST::Namespace("Namespace"));
  std::shared_ptr<AST::Namespace> n = ast.Get(AST::Namespace("Namespace"));
  n->Insert(AST::Class("Class1"));
  n->Insert(AST::Class("Class2"));
  {
    auto c = n->Get(AST::Class("Class1"));

    c->Insert(AST::Class("Class_nested"), AST::Visibility::PUBLIC);

    c->Insert(AST::Temp("i", "int i_"));

    c->Inherit(
	       *n->Get(AST::Class("Class2"))
	       );
  }
  {
    AST::Class bar("Bar");
    bar.Templates(AST::Template::Type("T"));
    n->Insert(bar);

    AST::Template::Template c("C");
    c.Templates(AST::Template::Type("T"));

    AST::Class foo("Foo");
    foo.Templates(c);
    n->Insert(foo);
  }

  {
    AST::Class bar("Bar<int>");
    bar.Templates();
    n->Insert(bar);    
  }

  std::cout << ast << std::endl;
}
