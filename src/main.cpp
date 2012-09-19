
#include <iostream>

#include "assed.hpp"

int main(void)
{
  AST::AST ast;

  ast.Insert(AST::Namespace("::"));
  std::shared_ptr<AST::Namespace> n = ast.Get(AST::Namespace("::"));
  n->Insert(AST::Struct("Abidbul"));

  if (0)
    {
      AST::Class c("Bar");
      c.Inherit(AST::Inheritance(
      				 *(n->Get(AST::Struct("Abidbul"))),
      				   AST::Visibility::PRIVATE
      				 ));
      n->Insert(c);
      std::cout << ast << std::endl;
      return (0);
    }

  {
    AST::Struct NumType("NumType");
    NumType.Templates(AST::Template::TypeNumeric("i"));
    n->Insert(NumType);
  }
  {
    AST::Struct Americaine("Americaine");
    Americaine.Templates(AST::Template::Type("T0"), AST::Template::Type("T1"));
    n->Insert(Americaine);
  }
  {
    AST::Struct Americaine("Americaine<T0, Abidbul>");
    Americaine.Templates(AST::Template::Type("T0"));
    n->Insert(Americaine);
  }
  {
    AST::Struct Americaine("Americaine<NumType<i>, Abidbul>");
    Americaine.Templates(AST::Template::TypeNumeric("i"));
    n->Insert(Americaine);
  }
  {
    AST::Struct Americaine("Americaine<Lol<Americaine>, Abidbul>");
    AST::Template::Template temp("Lol"), anonymous;
    anonymous.Templates(AST::Template::Type(""),
			AST::Template::Type(""));
    temp.Templates(anonymous);
    Americaine.Templates(temp);
    n->Insert(Americaine);
  }

  std::cout << ast << std::endl;
}
