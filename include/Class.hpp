
#ifndef CLASS_HPP_
# define CLASS_HPP_

# include "BasicElement.hpp"
# include "Value.hpp"
# include "Array.hpp"
# include "Template.hpp"
# include "Function.hpp"
# include "Visibility.hpp"
# include "Inheritance.hpp"
# include "Temp.hpp"

namespace AST
{
  enum class Constness { CONST };

  enum class Staticness { STATIC };

  template <class C>
  class Member : public C
  {
  public:
    using typename C::name;

    Member() = delete;

    explicit Member(const C& m, Visibility v) : C(m), _visibility(v)
    {}

    friend std::ostream& operator<<(std::ostream &o,
				    const Member &m)
    {
      o << m._visibility << ":" << std::endl;
      o << (static_cast<C>(m));
      return (o);
    }

  private:
    Visibility _visibility;
  };

  class Class;

  template <>
  struct Traits<Class>
  {
    typedef boost::mpl::vector<Member<Function>, Member<Class>, Member<Value>, Value, Member<Array>, Array, Member<Temp>
      > AuthorizedTypes;
  };

  class Class : public BasicElement<Class>, public Templateable
  {
  public:
    using BasicElement::name;
    using Templateable::Templates;

    Class(const std::string &name) : BasicElement<Class>(name)
    {}

    ~Class()
    {}

    void Inherit(const Inheritance &i)
    {
      _inheritance.push_back(i);
    }

    template <class C>
    void Insert(const C& c, const Visibility v = Visibility::PRIVATE)
    {
      BasicElement::Insert(Member<C>(c, v));
    }

    template <class C>
    std::shared_ptr<C> Get(const C& c)
    {
      return BasicElement::Get(Member<C>(c, Visibility::NotAvailable));
    }

    friend std::ostream& operator<<(std::ostream &o,
				    const Class &c)
    {
      o << "class " << c.name();
      if (c._inheritance.size() > 0)
	{
	  o << " : ";
	  bool b = false;
	  for (const auto &x : c._inheritance)
	    {
	      if (b)
		o << ", ";
	      else
		b = true;
	      o << x;
	    }
	}
      o << std::endl;
      o << "{" << std::endl;
      o << static_cast<BasicElement<Class> >(c);
      o << "};" << std::endl;
      return (o);
    }
   
  private:
    std::vector<Inheritance> _inheritance;
  };

}

#endif	// !CLASS_HPP_
