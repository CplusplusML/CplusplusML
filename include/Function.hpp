
#ifndef FUNCTION_HPP_
# define FUNCTION_HPP_

# include "Template.hpp"

namespace AST
{
  class Function : public Templateable
  {
  public:
    using Templateable::Templates;

    template <class C>
    Function(const C&c, const std::string &name) :
      _name(name),
      _type(c)
    {}

    Function(const std::string &name) : _name(name)
    {}

    const std::string &name() const
    {
      return (_name);
    }

  private:
    // std::vector<C> _element;
    std::string _name;
    boost::any _type;
  };
}

#endif	// !FUNCTION_HPP_
