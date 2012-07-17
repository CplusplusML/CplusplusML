
#include "assed.hpp"

namespace AST
{
  std::ostream& operator<<(std::ostream &o,
			   const AST &ast)
  {
    o << "/* AST Begin */" << std::endl;
    o << static_cast<BasicElement<AST> >(ast);
    return (o);
  }
}
