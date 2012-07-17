
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
    typedef Loki::TL::MakeTypelist<Namespace, Class> AuthorizedTypes;

    using BasicElement::operator<<;
    using BasicElement::Get;
    using BasicElement::name;

    Namespace(const std::string &name) : BasicElement<Namespace>(name)
    {}
    ~Namespace()
    {}
  };
}

#endif	// !NAMESPACE_HPP_
