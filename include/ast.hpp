
#ifndef AST_HPP_
# define AST_HPP_

# include <string>
# include <vector>
# include <utility>

# include <loki/Typelist.h>
# include <loki/static_check.h>

using namespace Loki;

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
  class Class;
  class Namespace;
  class Template;

  template <class T>
  class BasicElement
  {
  protected:
    BasicElement()
    {}

  public:
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
      typedef CompileTimeError<TL::IndexOf<typename T::Result, C>::value != -1> IsAuthorized;
      // if (
      return (*this);
      IsAuthorized invalid_type;
    }

  private:
    std::string _name;
  };


  class AST : BasicElement<TL::MakeTypelist<Namespace, Class> >
  {
    typedef BasicElement<TL::MakeTypelist<Namespace, Class> > Basic;

  public:
    // explicit AST(const std::string &filename)
    // {}

    using Basic::operator<<;

    AST()
    {}

    AST(const std::string &name) : Basic(name)
    {}

    ~AST()
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

  class Class : BasicElement<TL::MakeTypelist<Class> >
  {
    Class();
    typedef BasicElement<TL::MakeTypelist<Class> > Basic;

  public:

    enum Visibility
      {
	PUBLIC,
	PROTECTED,
	PRIVATE
      };


    Class(const std::string &name, const Visibility visibility = PUBLIC) : Basic(name)
    {
    }

    ~Class()
    {
      std::cout << "Destructor" << std::endl;
    }
  };

  class Namespace : BasicElement<TL::MakeTypelist<Class> >
  {
    Namespace();
    typedef BasicElement<TL::MakeTypelist<Class> > Basic;

  public:
    Namespace(const std::string &name) : Basic(name)
    {
      
    }

    ~Namespace()
    {}
  };


}

#endif	// !AST_HPP_
