
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
    AST(const std::string &name = "") : BasicElement<AST>(name)
    {}
    ~AST()
    {}

    friend std::ostream& operator<<(std::ostream &o,
				    const AST &ast);
  };

}

#endif	// !AST_HPP_
