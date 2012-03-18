
#ifndef AST_HPP_
# define AST_HPP_

# include <loki/Typelist.h>

# include "BasicElement.hpp"
# include "Class.hpp"

namespace AST
{
  class AST : public BasicElement<AST>
  {
  public:
    typedef Loki::TL::MakeTypelist<Namespace, Class> AuthorizedTypes;

    using BasicElement::operator<<;
    using BasicElement::Get;
    using BasicElement::name;

    AST(const std::string &name = "") : BasicElement<AST>(name)
    {}
    ~AST()
    {}
  };
}

#endif	// !AST_HPP_
