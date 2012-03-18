
#ifndef CLASS_HPP_
# define CLASS_HPP_

# include <loki/Typelist.h>

# include "BasicElement.hpp"
# include "Value.hpp"
# include "Array.hpp"
# include "Template.hpp"

namespace AST
{
  enum class Visibility
  {
    PRIVATE,
      PROTECTED,
      PUBLIC,
      NotAvailable
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
   
  private:
    // ce _default_visibility pue du cul car ne devrait pas etre la (10 classes creees => 10 _default_visibility xD )
    Visibility _default_visibility;
    Visibility _visibility;
  };

}

#endif	// !CLASS_HPP_
