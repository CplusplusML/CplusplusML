
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
    explicit Inheritance(std::shared_ptr<ClassTP<V> > c, Visibility v = Visibility::PRIVATE) :
      _class(c), _visibility(v)
    {}

    ~Inheritance()
    {}

    // Inheritance &operator=(const Inheritance& inh)
    // {
    //   if (this == &inh)
    // 	return (*this);
    //   _class = inh._class;
    //   _visibility = inh._visibility;
    //   return (*this);
    // }

    // template <Visibility V>
    // friend bool operator==(const Inheritance &inh, const ClassTP<V> &c);

    // template <Visibility V>
    // friend bool operator==(const ClassTP<V> &c, const Inheritance &inh);

  private:
    // CA PUE DU CUL VENER! GO SMART POINTER!
    boost::variant<std::shared_ptr<Struct>, std::shared_ptr<Class> > _class;
    Visibility _visibility;

    struct PrintNameVisitor : public boost::static_visitor<void>
    {
      PrintNameVisitor(std::ostream &o) : o_(o)
      {}

      template <typename T>
      void operator()(const std::shared_ptr<T> t) const
      {
	o_ << t->name();
	o_ << static_cast<Specializeable>(*t);
      }

    private:
      std::ostream &o_;
    };

    friend std::ostream& operator<<(std::ostream &o,
  				    Inheritance inh)
    {
      PrintNameVisitor p(o);
      o << inh._visibility;
      o << " ";
      boost::apply_visitor(p, inh._class);
      return (o);
    }
  };
}

#endif	// !INHERITANCE_HPP_
