
#include <iostream>
#include "Visibility.hpp"

namespace AST
{
  std::ostream &operator<<(std::ostream &o, AST::Visibility v)
  {
    switch (v)
      {
      case AST::Visibility::PRIVATE:
	o << "private";
	break;
      case AST::Visibility::PROTECTED:
	o << "protected";
	break;
      case AST::Visibility::PUBLIC:
	o << "public";
	break;
      default:
	break;
      }
    return (o);
  }
}
