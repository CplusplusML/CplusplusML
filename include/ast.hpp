
#ifndef AST_HPP_
# define AST_HPP_

# include <string>
# include <vector>
# include <utility>

#include <boost/any.hpp>

# include <loki/Typelist.h>
# include <loki/static_check.h>

# include <boost/shared_ptr.hpp>

using boost::shared_ptr;

namespace AST
{
  class AST;
  class Namespace;
  class Class;
  class Value;

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

      shared_ptr<C> p(new C(c));
      _elements.push_back(p);
      return (*this);
      IsAuthorized invalid_type;
      (void)invalid_type;
    }

    template <class C>
    C& Get(const C &c)
    {
      typedef Loki::CompileTimeError<Loki::TL::IndexOf<typename Element::AuthorizedTypes::Result, C>::value != -1> IsAuthorized;
      for (std::vector<boost::any>::iterator b(_elements.begin()), e(_elements.end()); b != e; ++b)
	{
	  if (b->type() == typeid(shared_ptr<C>) && c.name() == (boost::any_cast<shared_ptr<C> >(*b))->name())
	    {
	      return (*(boost::any_cast<shared_ptr<C> >(*b)));
	    }
	}
      // revoir la gestion d'erreurs xD
      throw 1;
      IsAuthorized invalid_type;
      (void)invalid_type;
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
    using BasicElement::Get;
    using BasicElement::name;

    AST(const std::string &name = "") : BasicElement<AST>(name)
    {}
    ~AST()
    {}
  };

  class Class : public BasicElement<Class>
  {
  public:
    // trouver le moyen de faire une iteration sur une type list correspondant
    // aux types de values qu'on pourra avoir, et ensuite les inserer
    // dans l'AuthorizedTypes, a base de Value<TypeValue>
    typedef Loki::TL::MakeTypelist<Class, Value> AuthorizedTypes;

    using BasicElement::operator<<;
    using BasicElement::Get;
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
    using BasicElement::Get;
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
      // for (const Parameter &p: collection)
      // 	{
      // 	  std::cout << "first " << p.first << " ; second " << p.second << std::endl;
      // 	}
      std::cout << "End template" << std::endl;
    }

  public:
    ~Template()
    {}
  };

  // a faire
  class Value
  {
  public:
    template <class C>
    Value(const C& c, const std::string &value) : _element(c), _value(value)
    {}

    ~Value()
    {}

  private:
    boost::any _element;
    std::string _value;
  };

}

#endif	// !AST_HPP_
