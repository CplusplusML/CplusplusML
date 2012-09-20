
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

  {
    AST::Typedef i("int", "Integer");

    std::cout << "// Simple Example 1:" << std::endl << i << std::endl;
  }

  {
    AST::Class w("Wolf"), h("Head");
    w.Insert(h, AST::Visibility::PUBLIC);

    std::cout << "// Simple Example 2:" << std::endl << w << std::endl;
  }

  {
    AST::Class w("Wolf"), h("Head");
    w.Insert(h, AST::Visibility::PUBLIC);

    std::cout << "// Simple Example 2:" << std::endl << w << std::endl;
  }

  {
    AST::Class w("Wolf");
    AST::Typedef p("std::list<Wolf>", "Pack");
    w.Insert(p, AST::Visibility::PUBLIC);

    std::cout << "// Simple Example 3:" << std::endl << w << std::endl;
  }

  {
    AST::Struct c("Commonplace");
    c.Templates(AST::Template::Type("T"));
    AST::Typedef t("T", "Type");
    c.Insert(t);

    std::cout << "// Simple Example 4:" << std::endl << c << std::endl;
  }

  {
    AST::Class crtp("CRTP"), commonplace("Commonplace");
    crtp.Templates(AST::Template::Type("T"));
    std::shared_ptr<AST::Class> temp(new AST::Class(crtp));
    temp->Specialize(AST::Specialization("Commonplace"));
    commonplace.Inherit(AST::Inheritance(temp, AST::Visibility::PUBLIC));

    std::cout << "// Simple Example 5:" << std::endl
	      << crtp << std::endl
	      << commonplace << std::endl;
  }

  return (0);

  /*
  // example 2

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
  */
}
