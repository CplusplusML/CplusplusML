
#ifndef BASICELEMENT_HPP_
# define BASICELEMENT_HPP_

# include <utility>
# include <loki/Typelist.h>

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
      static_assert(Loki::TL::IndexOf<typename Element::AuthorizedTypes::Result, C>::value != -1, "Invalid type");

      shared_ptr<C> p(new C(c));
      _elements.push_back(p);
      return (*this);
    }

    template <class C>
    C& Get(const C &c)
    {
      static_assert(Loki::TL::IndexOf<typename Element::AuthorizedTypes::Result, C>::value != -1, "Invalid type");
      for (std::vector<boost::any>::iterator b(_elements.begin()), e(_elements.end()); b != e; ++b)
	{
	  if (b->type() == typeid(shared_ptr<C>) && c.name() == (boost::any_cast<shared_ptr<C> >(*b))->name())
	    {
	      return (*(boost::any_cast<shared_ptr<C> >(*b)));
	    }
	}
      // revoir la gestion d'erreurs xD
      throw 1;
    }

    const std::string &name() const
    {
      return (_name);
    }

    void name(const std::string &name)
    {
      _name = name;
    }

    // template <class C>
    // bool canAdd(const C& c)
    // {
    //   return (Loki::TL::IndexOf<typename Element::AuthorizedTypes::Result, C>::value != -1);
    // }

    // template <class C>
    // bool canAdd(void)
    // {
    //   return (Loki::TL::IndexOf<typename Element::AuthorizedTypes::Result, C>::value != -1);
    // }

  private:
    std::string _name;
    std::vector<boost::any> _elements;
  };

}

#endif	// !BASICELEMENT_HPP_
