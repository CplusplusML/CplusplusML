
#ifndef AST_HPP_
# define AST_HPP_

# include <string>
# include <vector>
# include <utility>

# include <boost/any.hpp>
# include <boost/variant.hpp>

# include <loki/Typelist.h>

# include <boost/shared_ptr.hpp>

using std::shared_ptr;

namespace AST
{
  class AST;
  class Namespace;
  class Class;
  class Value;
  class Template;

  class Template
  {
  public:
    struct Type
    {
      Type()
      {}

      Type(const std::string &name) : _name(name)
      {}

      ~Type()
      {}

    private:
      std::string _name;
    };

    // template <typename T>
    struct TypeNumeric
    {
      TypeNumeric()
      {}

      TypeNumeric(const std::string &name) : _name(name)
      {
	// static_assert(Loki::TL::IndexOf<AuthorizedTemplates::Result, T>::value != -1, "Invalid template parameter");
      }

      ~TypeNumeric()
      {}

    private:
      typedef Loki::TL::MakeTypelist<int, long> AuthorizedNumericTypes;
      std::string _name;
    };

    struct Variadic
    {
      Variadic()
      {}

      Variadic(const std::string &name) : _name(name)
      {}

      ~Variadic()
      {}

    private:
      std::string _name;
    };
  };

  class Templateable
  {
    typedef Loki::TL::MakeTypelist<Template::Type,
				   Template::Variadic,
				   Template::TypeNumeric>
    AuthorizedTemplates;
  public:
    template <typename T, typename ...Rest>
    void Templates(const T &t, const Rest&... rest)
    {
      Templates(t);
      Templates(rest...);
    }

    template <typename T>
    void Templates(const T &t)
    {
      static_assert(Loki::TL::IndexOf<AuthorizedTemplates::Result, T>::value != -1, "Invalid template parameter");
      _templates.push_back(t);
    }

  private:
    std::vector<boost::variant<Template::Type, Template::Variadic, Template::TypeNumeric> > _templates;
  };

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
      static_assert(Loki::TL::IndexOf<typename Element::AuthorizedTypes::Result, C>::value != -1, "Invalid type");

      shared_ptr<C> p(new C(c));
      _elements.push_back(p);
      return (*this);
    }

    template <class C>
    C& Get(const C &c)
    {
      static_assert(Loki::TL::IndexOf<typename Element::AuthorizedTypes::Result, C>::value != -1, "Invalid type");
      for (std::vector<boost::any>::iterator b(_elements.begin()), e(_elements.end()); b != e; ++b)
	{
	  if (b->type() == typeid(shared_ptr<C>) && c.name() == (boost::any_cast<shared_ptr<C> >(*b))->name())
	    {
	      return (*(boost::any_cast<shared_ptr<C> >(*b)));
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
    using BasicElement::Get;
    using BasicElement::name;

    AST(const std::string &name = "") : BasicElement<AST>(name)
    {}
    ~AST()
    {}
  };

  class Class : public BasicElement<Class>, public Templateable
  {
  public:
    // trouver le moyen de faire une iteration sur une type list correspondant
    // aux types de values qu'on pourra avoir, et ensuite les inserer
    // dans l'AuthorizedTypes, a base de Value<TypeValue>
    typedef Loki::TL::MakeTypelist<Class, Value> AuthorizedTypes;

    using BasicElement::operator<<;
    using BasicElement::Get;
    using BasicElement::name;
    using Templateable::Templates;

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

  // a faire
  class Value
  {
  public:
    template <class C>
    Value(const C& c, const std::string &value) : _element(c), _value(value)
    {}

    Value(const std::string &value) : _value(value)
    {}

    ~Value()
    {}

  private:
    boost::any _element;
    std::string _value;
  };

  class Pointer
  {
  public:
    Pointer()
    {}

    ~Pointer()
    {}
  };

}

#endif	// !AST_HPP_
