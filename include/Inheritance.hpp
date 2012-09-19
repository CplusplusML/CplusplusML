
#ifndef INHERITANCE_HPP_
# define INHERITANCE_HPP_

# include "Visibility.hpp"

namespace AST
{
  template <Visibility V>
  class ClassTP;

  class Inheritance
  {
  public:
    template <Visibility V>
    explicit Inheritance(ClassTP<V> &c, Visibility v = Visibility::PRIVATE) :
      _class(&c), _visibility(v)
    {}

    ~Inheritance()
    {}

    Inheritance &operator=(const Inheritance& inh)
    {
      if (this == &inh)
	return (*this);
      _class = inh._class;
      _visibility = inh._visibility;
      return (*this);
    }

    template <Visibility V>
    friend bool operator==(const Inheritance &inh, const ClassTP<V> &c);

    template <Visibility V>
    friend bool operator==(const ClassTP<V> &c, const Inheritance &inh);

  private:
    // CA PUE DU CUL VENER! GO SMART POINTER!
    boost::variant<Struct*, Class*> _class;
    Visibility _visibility;

    struct NameVisitor : public boost::static_visitor<const std::string&>
    {
      template <typename T>
      const std::string& operator()(const T *t) const
      {
	return (t->name());
      }
    };

    friend std::ostream& operator<<(std::ostream &o,
  				    Inheritance inh)
    {
      o << inh._visibility;
      o << " ";
      o << boost::apply_visitor(Inheritance::NameVisitor(), inh._class);
      return (o);
    }
  };
}

#endif	// !INHERITANCE_HPP_
