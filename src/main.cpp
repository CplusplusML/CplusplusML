
#include <iostream>
#include <iomanip>

#include "assed.hpp"

int main(void)
{


  // {
  //   AST::Class n1("toto"), n2("toto");

  //   n1.Templates(AST::Template::Type("T0"));
  //   n2.Templates(AST::Template::Type("T0"));
  //   std::cout << std::boolalpha;
  //   std::cout << (n1 == n2) << std::endl;
  //   return (0);
  // }

  AST::AST ast;

  ast.Insert(AST::Namespace("::"));
  std::shared_ptr<AST::Namespace> n = ast.Get(AST::Namespace("::"));
  n->Insert(AST::Struct("Abidbul"));

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
    AST::Struct Americaine("Americaine");
    Americaine.Specialize(AST::Specialization("<Lol<Americaine>"));
    Americaine.Specialize(AST::Specialization("Abidbul"));

    AST::Template::Template temp("Lol"), anonymous;
    anonymous.Templates(AST::Template::Type(""),
			AST::Template::Type(""));
    temp.Templates(anonymous);
    Americaine.Templates(temp);
    n->Insert(Americaine);
  }
  {
    AST::TemplatedTypedef Californienne("Californienne", "Americaine<NumType<i>, Abidbul>");
    Californienne.Templates(AST::Template::TypeNumeric("i"));
    n->Insert(Californienne);
  }

  std::cout << ast << std::endl;
}
