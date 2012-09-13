
#ifndef CLASS_HPP_
# define CLASS_HPP_

# include "BasicElement.hpp"
# include "Value.hpp"
# include "Array.hpp"
# include "Template.hpp"
# include "Function.hpp"
# include "Visibility.hpp"
# include "Inheritance.hpp"

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
      o << "/* Member */" << std::endl;
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
    typedef boost::mpl::vector<Member<Function>, Member<Class>, Member<Value>, Value, Member<Array>, Array
      > AuthorizedTypes;
  };

  class Class : public BasicElement<Class>, public Templateable
  {
  public:
    using BasicElement::name;
    using Templateable::Templates;

    Class(const std::string &name, const Visibility default_visibility = Visibility::PRIVATE) : BasicElement<Class>(name), _default_visibility(default_visibility)
    {}

    ~Class()
    {}

    void setVisibility(const Visibility v)
    {
      _visibility = v;
      // Segfault si on decommente la ligne suivante, sinon tout va bien pour valgrind
      // std::cout << "toto" << std::endl;
      //      return (*this);
    }

    Class &operator<<(const Inheritance &inh)
    {
      _inheritance.push_back(inh);
      return (*this);
    }

    template <class C>
    void Insert(const C& c)
    {
      BasicElement::Insert(Member<C>(c, _visibility));
      _visibility = _default_visibility;
    }

    template <class C>
    C &Get(const C& c)
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
    // ce _default_visibility pue du cul car ne devrait pas etre la (10 classes creees => 10 _default_visibility xD )
    Visibility _default_visibility;
    Visibility _visibility;
    std::vector<Inheritance> _inheritance;
  };

}

#endif	// !CLASS_HPP_
