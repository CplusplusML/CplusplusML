
#ifndef BASICELEMENT_HPP_
# define BASICELEMENT_HPP_

# include <vector>
# include <string>
# include <memory>
# include <type_traits>
# include <boost/any.hpp>
# include <boost/variant.hpp>

# include "MakeEachMPLToSharedPtr.hpp"

namespace AST
{
  template <class Element>
  class BasicElement
  {
  public:
    BasicElement(const std::string &name = "") : _name(name)
    {}

    ~BasicElement()
    {}

    template <class C>
    BasicElement& operator<<(const C &c)
    {
      _toto.push_back(std::shared_ptr<C>(new C(c)));
      return (*this);
    }

  private:
    template <typename U>
    struct GetVisitor : public boost::static_visitor<// bool
    const std::string&
						     >
    {
      // template <typename T>
      // bool operator()(const T &t) const
      // {
      // 	if (std::is_same<T, U> && t.name() == 
      // }

      template <typename T>
      const std::string& operator()(const T &t) const
      {
      	return (t->name());
      }


    };

  public:
    template <class C>
    C& Get(const C &c)
    {
      for (auto &b : _toto)
      	{
	  // on a un boost variant de shared_ptr
	  // on veut donc apply visitor sur des visitor qui prennent des shared_ptr et qui forward a la version nue !

	  // if (boost::apply_visitor(GetVisitor<std::shared_ptr<C> >(), b))
	  //   {
	  //     return (*(boost::get<std::shared_ptr<C>(b)));
	  //   }

	  // if (b->type() == typeid(C) && boost::apply_visitor(GetVisitor(), *b) == c.name())
	  //   {
	  //     return (boost::get<C>(*b));
	  //   }
	}
      // revoir la gestion d'erreurs xD
      throw 1;
      (void)_toto.push_back(std::shared_ptr<C>(new C(c)));
    }

    const std::string &name() const
    {
      return (_name);
    }

    void name(const std::string &name)
    {
      _name = name;
    }

    friend std::ostream& operator<<(std::ostream &o,
				    const BasicElement<Element>& b)
    {
      // std::for_each(b._toto.begin(), b._toto.end(),
      // 		    [&o](std::shared_ptr<BasicElement<Element>::CACA> x){ o << (*x); });
      return (o);
    }

  private:
    std::string _name;
    //    std::vector<boost::any> _elements;

    typedef typename Traits<Element>::AuthorizedTypes types;
    typedef typename boost::make_variant_over< typename MakeEachMPLToSharedPtr<types, toSharedPtr>::type >::type CACA;
    std::vector<CACA> _toto;
  };

}

#endif	// !BASICELEMENT_HPP_
