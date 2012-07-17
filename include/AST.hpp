
#ifndef AST_HPP_
# define AST_HPP_

# include <boost/mpl/vector.hpp>
# include <loki/Typelist.h>

# include "BasicElement.hpp"
# include "Class.hpp"

namespace AST
{
  class AST;

  template <>
  struct Traits<AST>
  {
    typedef boost::mpl::vector<Namespace> AuthorizedTypes;
  };

  class AST : public BasicElement<AST>
  {
  public:
    typedef Loki::TL::MakeTypelist<Namespace> AuthorizedTypes;

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
