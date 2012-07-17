
#ifndef VALUE_HPP_
# define VALUE_HPP_

# include <string>
# include <boost/any.hpp>

namespace AST
{

  // a faire
  class Value
  {
  public:
    template <class C>
    Value(const C& c, const std::string &name) : _element(c), _name(name)
    {}

    Value(const std::string &name) : _name(name)
    {}

    ~Value()
    {}

    const std::string& name() const
    {
      return (_name);
    }

  private:
    boost::any _element;
    std::string _name;
  };

}

#endif	// !VALUE_HPP_
