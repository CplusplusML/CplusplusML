
#ifndef ARRAY_HPP_
# define ARRAY_HPP_

# include <string>
# include <cstdint>
# include <boost/any.hpp>

namespace AST
{
  class Array
  {
  public:
    template <class C>
    Array(const C&c, const std::string &name, const size_t size) : // _element(size),
      _name(name),
      _size(size),
      _type(c)
    {}

    Array(const std::string &name) : _name(name)
    {}

    Array(const Array& cpy) : _name(cpy._name), _size(cpy._size), _type(cpy._type)
    {}

    ~Array()
    {}

    size_t getSize(void) const
    {
      return (_size);
    }

    bool operator==(const Array& cmp) const
    {
      return (_name == cmp._name);
    }

    const std::string &name() const
    {
      return (_name);
    }

    // const C& getType(void) const
    // {
    //   return (_type);
    // }

  private:
    // std::vector<C> _element;
    std::string _name;
    size_t _size;
    boost::any _type;
  };

}

#endif	// !ARRAY_HPP_
