
#ifndef CLASS_HPP_
# define CLASS_HPP_

# include "Visibility.hpp"

namespace AST
{

template <Visibility V>
class ClassTP;

typedef ClassTP<Visibility::PUBLIC> Struct;
typedef ClassTP<Visibility::PRIVATE> Class;

}

# include "BasicElement.hpp"
# include "Value.hpp"
# include "Array.hpp"
# include "Template.hpp"
# include "Function.hpp"
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

  template <typename T>
  struct Prefix;

  template <Visibility V>
  class ClassTP : public BasicElement<ClassTP<V> >, public Templateable
  {
  public:
    typedef BasicElement<ClassTP<V> > BasicElementType;
    using BasicElementType::name;
    using Templateable::Templates;

    ClassTP(const std::string &name) : BasicElementType(name)
    {}

    ~ClassTP()
    {}

    void Inherit(const Inheritance &i)
    {
      _inheritance.push_back(i);
    }

    template <class C>
    void Insert(const C& c, const Visibility v = V)
    {
      BasicElementType::Insert(Member<C>(c, v));
    }

    template <class C>
    std::shared_ptr<C> Get(const C& c)
    {
      return BasicElementType::Get(Member<C>(c, Visibility::NotAvailable));
    }

    friend std::ostream& operator<<(std::ostream &o,
				    const ClassTP<V> &c)
    {
      o << static_cast<Templateable>(c) << std::endl;
      o << Prefix<ClassTP<V> >::prefix() << ' ' << c.name();
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
      o << static_cast<BasicElementType>(c);
      o << "};" << std::endl;
      return (o);
    }
   
  private:
    std::vector<Inheritance> _inheritance;
  };

  template <>
  struct Traits<Class>
  {
    typedef boost::mpl::vector<Member<Function>, Member<Class>, Member<Value>, Value, Member<Array>, Array, Member<Temp>, Member<Struct>
      > AuthorizedTypes;
  };

  template <>
  struct Traits<Struct>
  {
    typedef boost::mpl::vector<Member<Function>, Member<Class>, Member<Value>, Value, Member<Array>, Array, Member<Temp>, Member<Struct>
      > AuthorizedTypes;
  };

  template <>
  struct Prefix<Struct>
  {
    static const char* prefix()
    {
      return ("struct");
    }
  };

  template <>
  struct Prefix<Class>
  {
    static const char* prefix()
    {
      return ("class");
    }
  };

}

#endif	// !CLASS_HPP_
