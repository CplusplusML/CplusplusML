
#ifndef NAMESPACE_HPP_
# define NAMESPACE_HPP_

# include <boost/mpl/vector.hpp>

# include "BasicElement.hpp"
# include "Class.hpp"

namespace AST
{
  class Namespace;

  template <>
  struct Traits<Namespace>
  {
    typedef boost::mpl::vector<Namespace, Class> AuthorizedTypes;
  };

  class Namespace : public BasicElement<Namespace>
  {
  public:
    Namespace(const std::string &name) : BasicElement<Namespace>(name)
    {}
    ~Namespace()
    {}

    friend std::ostream& operator<<(std::ostream &o,
				    const Namespace &n)
    {
      if (n.name() != "::")
	{
	  o << "namespace " << n.name() << std::endl;
	  o << "{" << std::endl;
	  o << static_cast<BasicElement<Namespace> >(n);
	  o << "}" << std::endl;
	}
      else
	{
	  o << static_cast<BasicElement<Namespace> >(n);	  
	}
      return (o);
    }
  };
}

#endif	// !NAMESPACE_HPP_
