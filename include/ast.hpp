
#ifndef AST_HPP_
# define AST_HPP_

# include <string>
# include <vector>
# include <utility>

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
  template <class T>
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

  template <class ElementPolicy>
  class BasicElement : public ElementPolicy
  {
  public:
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

      return (*this);
      IsAuthorized invalid_type;
    }

    // template <class C>
    // C& operator>>(const C &c)
    // {
    //   typedef Loki::CompileTimeError<TL::IndexOf<typename T::Result, C>::value != -1> IsAuthorized;

    //   std::cout << C.name() << std::endl;
    //   return (C);
    //   IsAuthorized invalid_type;
    // }

  private:
    std::string _name;
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
