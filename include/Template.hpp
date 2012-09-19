
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
    struct Template;
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

  struct Specialization
  {
    Specialization(const std::string &s) : _str(s)
    {}

    ~Specialization()
    {}

    friend std::ostream &operator<<(std::ostream &o, const Specialization& s)
    {
      o << s._str;
      return (o);
    }

  private:
    std::string _str;
  };

  class Specializeable
  {
  public:
    Specializeable() : _specialized(false)
    {}

    ~Specializeable()
    {}

    template <typename ...Rest>
    void Specialize(const Specialization &s, const Rest&... rest)
    {
      Specialize(s);
      Specialize(rest...);
    }

    void Specialize(const Specialization &s)
    {
      _specializations.push_back(s);
    }

    void Specialize()
    {
      _specialized = true;
    }

  private:
    inline bool isSpecialized() const
    {
      return (_specializations.size() > 0 || _specialized == true);
    }

    friend std::ostream &operator<<(std::ostream &o, const Specializeable &t)
    {
      if (t.isSpecialized())
	{
	  unsigned int first = true;
	  o << "<";
	  for (auto c: t._specializations)
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

    bool _specialized;
    std::vector<Specialization> _specializations;
  };

  class Templateable
  {
  public:
    Templateable() : _templated(false)
    {}

    ~Templateable()
    {}

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

    void Templates()
    {
      _templated = true;
    }

  private:
    std::vector<boost::variant<Template::Type, Template::Variadic, Template::TypeNumeric, boost::recursive_wrapper<Template::Template>
			       > > _templates;

    bool _templated;
    // std::vector<boost::variant<Template::Type> > _templates;

    inline bool isTemplated() const
    {
      return (_templates.size() > 0 || _templated == true);
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
    struct Template : public Templateable
    {
      Template()
      {}

      Template(const std::string &name) : _name(name)
      {}

      ~Template()
      {}

      friend std::ostream &operator<<(std::ostream &o, const Template &t)
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
