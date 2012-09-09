
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
  private:

    /* VISITORS */

    template <typename U>
    struct IsSameVisitor : public boost::static_visitor<bool>
    {

     template <typename T>
     bool operator()(const T &t) const
      {
	return (std::is_same<typename T::element_type, U>::value);
      }

    };

    // temp struct, waiting for better?
    struct PrintVisitor : public boost::static_visitor<void>
    {
      PrintVisitor(std::ostream &o) : o_(o)
      {}

      template <typename T>
      void operator()(const std::shared_ptr<T>& t)
      {
	o_ << *t;
      }

    private:
      std::ostream &o_;
    };

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

    template <class C>
    C& Get(const C &c)
    {
      for (auto &b : _toto)
      	{
	  if (boost::apply_visitor(IsSameVisitor<C>(), b) &&
	      boost::get<std::shared_ptr<C> >(b)->name() == c.name())
	    {
	      return (*(boost::get<std::shared_ptr<C> >(b)));
	    }
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
      PrintVisitor temp(o);
      std::for_each(b._toto.begin(), b._toto.end(),
      		    [&temp](type x){ 
		      boost::apply_visitor(temp, x);
		    });
      return (o);
    }

  private:
    std::string _name;

    typedef typename boost::make_variant_over< typename MakeEachMPLToSharedPtr<typename Traits<Element>::AuthorizedTypes, toSharedPtr>::type >::type type;
    std::vector<type> _toto;
  };

}

#endif	// !BASICELEMENT_HPP_
