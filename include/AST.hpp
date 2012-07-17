
#ifndef AST_HPP_
# define AST_HPP_

# include <boost/mpl/vector.hpp>

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
    using BasicElement::operator<<;
    using BasicElement::Get;
    using BasicElement::name;

    AST(const std::string &name = "") : BasicElement<AST>(name)
    {}
    ~AST()
    {}

    friend std::ostream& operator<<(std::ostream &o,
				    const AST &ast);
  };

  std::ostream& operator<<(std::ostream &o,
			   const AST &ast)
  {
    o << "/* AST Begin */" << std::endl;
    o << static_cast<BasicElement<AST> >(ast);
    return (o);
  }

}

#endif	// !AST_HPP_
