
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
  class Template;

  class ASTPolicy;
  class ClassPolicy;
  class NamespacePolicy;
  template <class T// , class Container=std::vector<boost::any> 
	    >
  class BasicElement;

  typedef BasicElement<ASTPolicy> AST;
  typedef BasicElement<ClassPolicy> Class;
  typedef BasicElement<NamespacePolicy> Namespace;

  //   template <template<class, class> class C, class T> 
  //   Template(const C<T, std::allocator<T> >


  class ASTPolicy
  {
  protected:
    typedef Loki::TL::MakeTypelist<Namespace, Class> AuthorizedTypes;
    ASTPolicy()
    {}

  public:
    // explicit AST(const std::string &filename)
    // {}


    ~ASTPolicy()
    {}
  };

  class ClassPolicy
  {
  protected:
    typedef Loki::TL::MakeTypelist<Class> AuthorizedTypes;
    ClassPolicy()
    {}

  public:
    enum Visibility
      {
  	PUBLIC,
  	PROTECTED,
  	PRIVATE
      };

    ~ClassPolicy()
    {}
  };

  class NamespacePolicy
  {
  protected:
    NamespacePolicy()
    {}
    typedef Loki::TL::MakeTypelist<Namespace, Class> AuthorizedTypes;

  public:

    ~NamespacePolicy()
    {}
  };

  template <class ElementPolicy// , class Container
	    >
  class BasicElement : public ElementPolicy
  {
  public:
    // using typename ElementPolicy::name;

    BasicElement()
    {
      typedef Loki::CompileTimeError<hasSameType<ElementPolicy, ASTPolicy>::value > CanBeUnnamed;
      return ;
      CanBeUnnamed canBeUnnamed;
    }

    explicit BasicElement(const std::string &name) : _name(name)
    {}

    ~BasicElement()
    {}

    // voir si on peut stocker une collection de types (pas forcement d'objets),
    // et ainsi pouvoir savoir si le type qu'on a recu est dans la collection, sinon faire
    // un static_assert, si possible :D 
    // la collection de types serait initialisee par le constructeur, OU alors en parametre template
    // ex :
    //  . <int, char, long> est la collection
    //  . si `class C` est un int, c'est bon, si c'est un double, c'est pas bon
    template <class C>
    BasicElement& operator<<(const C &c)
    {
      typedef Loki::CompileTimeError<Loki::TL::IndexOf<typename ElementPolicy::AuthorizedTypes::Result, C>::value != -1> IsAuthorized;

      // checker si on a pas une redeclaration
      _elements.push_back(c);
      return (*this);
      IsAuthorized invalid_type;
    }

    template <class C>
    C& operator>>(const C &c)
    {
      typedef Loki::CompileTimeError<Loki::TL::IndexOf<typename ElementPolicy::AuthorizedTypes::Result, C>::value != -1> IsAuthorized;

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

  private:
    std::string _name;
    // Container _elements;
    std::vector<boost::any> _elements;
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
