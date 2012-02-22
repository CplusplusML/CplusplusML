
#ifndef AST_HPP_
# define AST_HPP_

# include <string>
# include <vector>
# include <utility>

# include <boost/any.hpp>
# include <boost/variant.hpp>

# include <loki/Typelist.h>

# include <boost/shared_ptr.hpp>

# include <cstdint>

using std::shared_ptr;

namespace AST
{
  class AST;
  class Namespace;
  class Class;
  class Value;
  class Array;
  class Template;

  enum class Visibility
  {
    PRIVATE,
      PROTECTED,
      PUBLIC,
      NotAvailable
  };

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
    template <class C>
    class Member : public C
    {
    public:
      using typename C::name;

      Member() = delete;

      Member(const C& m, Visibility v) : C(m), _visibility(v)
      {}

    private:
      Visibility _visibility;
    };

  public:
    typedef Loki::TL::MakeTypelist<Member<Class>, Class, Member<Value>, Value, Member<Array>, Array> AuthorizedTypes;

    using BasicElement::name;
    using Templateable::Templates;

    Class(const std::string &name, const Visibility default_visibility = Visibility::PRIVATE) : BasicElement<Class>(name), _default_visibility(default_visibility)
    {}

    ~Class()
    {}

    Class& operator<<(const Visibility v)
    {
      _visibility = v;
      // Segfault si on decommente la ligne suivante, sinon tout va bien pour valgrind
      // std::cout << "toto" << std::endl;
    }

    template <class C>
    Class &operator<<(const C& c)
    {
      BasicElement::operator<<(Member<C>(c, _visibility));
      _visibility = _default_visibility;
    }

    template <class C>
    C &Get(const C& c)
    {
      return BasicElement::Get(Member<C>(c, Visibility::NotAvailable));
    }
 0   
  private:
    // ce _default_visibility pue du cul car ne devrait pas etre la (10 classes creees => 10 _default_visibility xD )
    Visibility _default_visibility;
    Visibility _visibility;
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
    Value(const C& c, const std::string &name) : _element(c), _name(name)
    {}

    Value(const std::string &name) : _name(name)
    {}

    ~Value()
    {}

  private:
    boost::any _element;
    std::string _name;
  };

  class Pointer
  {
  public:
    Pointer()
    {}

    ~Pointer()
    {}
  };

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

  class Function : public Templateable
  {
  public:
    using Templateable::Templates;

    Function()
    {}
  };

}

#endif	// !AST_HPP_
