
#ifndef AST_HPP_
# define AST_HPP_

# include <string>
# include <vector>
# include <utility>

#include <boost/any.hpp>

# include <loki/Typelist.h>
# include <loki/static_check.h>

template <class T, class U>
struct hasSameType
{
  enum { value = false };
};

template <class T>
struct hasSameType<T, T>
{
  enum { value = true };
};

namespace AST
{
  class AST;
  class Namespace;
  class Class;

  template <class Element>
  class BasicElement
  {
  public:
    BasicElement(const std::string &name = "") : _name(name)
    {}

    ~BasicElement()
    {}

    template <class C>
    BasicElement& operator<<(const C &c)
    {
      typedef Loki::CompileTimeError<Loki::TL::IndexOf<typename Element::AuthorizedTypes::Result, C>::value != -1> IsAuthorized;

      _elements.push_back(c);
      return (*this);
      IsAuthorized invalid_type;
    }

    template <class C>
    C& operator>>(const C &c)
    {
      typedef Loki::CompileTimeError<Loki::TL::IndexOf<typename Element::AuthorizedTypes::Result, C>::value != -1> IsAuthorized;

      for (boost::any &p: _elements)
	{
	  if (p.type() == typeid(C) && c.name() == (boost::any_cast<C>(p)).name())
	    {
	      return (boost::any_cast<C&>(_elements[0]));
	    }
	}
      // revoir la gestion d'erreurs xD
      throw 1;
    }

    const std::string &name() const
    {
      return (_name);
    }

    void name(const std::string &name)
    {
      _name = name;
    }

    // template <class C>
    // bool canAdd(const C& c)
    // {
    //   return (Loki::TL::IndexOf<typename Element::AuthorizedTypes::Result, C>::value != -1);
    // }

    // template <class C>
    // bool canAdd(void)
    // {
    //   return (Loki::TL::IndexOf<typename Element::AuthorizedTypes::Result, C>::value != -1);
    // }

  private:
    std::string _name;
    std::vector<boost::any> _elements;
  };

  class AST : public BasicElement<AST>
  {
  public:
    typedef Loki::TL::MakeTypelist<Namespace, Class> AuthorizedTypes;

    using BasicElement::operator<<;
    using BasicElement::operator>>;
    using BasicElement::name;

    AST(const std::string &name = "") : BasicElement<AST>(name)
    {}
    ~AST()
    {}
  };

  class Class : public BasicElement<Class>
  {
  public:
    typedef Loki::TL::MakeTypelist<Class> AuthorizedTypes;

    using BasicElement::operator<<;
    using BasicElement::operator>>;
    using BasicElement::name;

    enum Visibility
      {
  	PUBLIC,
  	PROTECTED,
  	PRIVATE
      };

    Class(const std::string &name) : BasicElement<Class>(name)
    {}

    ~Class()
    {}
  };

  class Namespace : public BasicElement<Namespace>
  {
  public:
    typedef Loki::TL::MakeTypelist<Namespace, Class> AuthorizedTypes;

    using BasicElement::operator<<;
    using BasicElement::operator>>;
    using BasicElement::name;

    Namespace(const std::string &name) : BasicElement<Namespace>(name)
    {}
    ~Namespace()
    {}
  };

  class Template
  {
    typedef std::pair<std::string, std::string> Parameter;
  public:

  public:
    template <template<class, class> class C, class T> 
    Template(const C<T, std::allocator<T> >
  	     &collection)
    {
      std::cout << "Begin template" << std::endl;
      for (const Parameter &p: collection)
  	{
  	  std::cout << "first " << p.first << " ; second " << p.second << std::endl;
  	}
      std::cout << "End template" << std::endl;
    }

  public:
    ~Template()
    {}
  };

}

#endif	// !AST_HPP_
