
#ifndef BASICELEMENT_HPP_
# define BASICELEMENT_HPP_

# include <vector>
# include <string>
# include <memory>
# include <boost/any.hpp>
# include <boost/variant.hpp>

using std::shared_ptr;

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
      shared_ptr<CACA> p4(new CACA(c));
      _toto.push_back(p4);
      return (*this);
    }

  private:
    struct GetVisitor : public boost::static_visitor<const std::string&>
    {
      template <typename T>
      const std::string& operator()(const T &t) const
      {
	return (t.name());
      }
    };

  public:
    template <class C>
    C& Get(const C &c)
    {
      for (auto &b : _toto)
      	{
	  if (b->type() == typeid(C) && boost::apply_visitor(GetVisitor(), *b) == c.name())
	    {
	      return (boost::get<C>(*b));
	    }
	}
      // revoir la gestion d'erreurs xD
      throw 1;
      (void)_toto.push_back(shared_ptr<CACA>(new CACA(c)));
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
      std::for_each(b._toto.begin(), b._toto.end(),
		    [&o](shared_ptr<BasicElement<Element>::CACA> x){ o << (*x); });
      return (o);
    }

  private:
    std::string _name;
    //    std::vector<boost::any> _elements;

    typedef typename Traits<Element>::AuthorizedTypes types;
    // pas super propre, vaudrait mieux un traits qui transforme une sequence de types MPL par une sequence de shared_ptr de chaque type, Redpist va raler s'il voit ca xD
    typedef typename boost::make_variant_over< types >::type CACA;
    std::vector<shared_ptr < CACA > > _toto;
  };

}

#endif	// !BASICELEMENT_HPP_
