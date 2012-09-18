
#ifndef TEMPLATE_HPP_
# define TEMPLATE_HPP_

# include <string>
# include <vector>
# include <boost/variant.hpp>

namespace AST
{
  class Templateable;

  namespace Template
  {
    struct Type;
    struct Toto;
    struct TypeNumeric;
    struct Variadic;

    struct Type
    {
      Type()
      {}

      Type(const std::string &name) : _name(name)
      {}

      ~Type()
      {}

      friend std::ostream &operator<<(std::ostream &o, const Type &t)
      {
	o << "class " << t._name;
	return (o);
      }

    private:
      std::string _name;
    };

    // template <typename T>
    struct TypeNumeric
    {
      TypeNumeric()
      {}

      TypeNumeric(const std::string &name) : _name(name)
      {}

      ~TypeNumeric()
      {}

      friend std::ostream &operator<<(std::ostream &o, const TypeNumeric &t)
      {
	// faire de TypeNumeric une template class,
	// et ne pas mettre tout le temps int
	o << "int " << t._name;
	return (o);
      }

    private:
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

      friend std::ostream &operator<<(std::ostream &o, const Variadic &t)
      {
	// faire de TypeNumeric une template class,
	// et ne pas mettre tout le temps int
	o << "typename...  " << t._name;
	return (o);
      }

    private:
      std::string _name;
    };

  }

  class Templateable
  {
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
      _templates.push_back(t);
    }

  private:
    std::vector<boost::variant<Template::Type, Template::Variadic, Template::TypeNumeric, boost::recursive_wrapper<Template::Toto>
			       > > _templates;
    // std::vector<boost::variant<Template::Type> > _templates;

    inline bool isTemplated() const
    {
      return (_templates.size() > 0);
    }

    friend std::ostream &operator<<(std::ostream &o, const Templateable &t)
    {
      if (t.isTemplated())
	{
	  unsigned int first = true;
	  o << "template <";
	  for (auto c: t._templates)
	    {
	      if (!first)
		o << ",";
	      o << c;
	      first = false;
	    }
	  o << ">";
	}
      return (o);
    }

  };

  namespace Template
  {
    struct Toto : public Templateable
    {
      Toto()
      {}

      Toto(const std::string &name) : _name(name)
      {}

      ~Toto()
      {}

      friend std::ostream &operator<<(std::ostream &o, const Toto &t)
      {
	o << static_cast<Templateable>(t) << t._name;
	return (o);
      }

    private:
      std::string _name;      
    };
  }

}

#endif	// !TEMPLATE_HPP_
