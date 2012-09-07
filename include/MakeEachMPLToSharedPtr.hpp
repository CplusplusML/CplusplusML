
#ifndef MAKEEACHMPLTOSHAREDPTR_HPP_
# define MAKEEACHMPLTOSHAREDPTR_HPP_

# include <boost/mpl/vector.hpp>
# include <boost/mpl/back.hpp>
# include <boost/mpl/push_front.hpp>
# include <boost/mpl/pop_back.hpp>
# include <boost/mpl/empty.hpp>
# include <memory>

template <typename T>
struct toPlainPtr
{
  typedef T* type;
};

template <typename T>
struct toSharedPtr
{
  typedef typename std::shared_ptr<T> type;
};

// take a MPL:
// take the back, apply the shared_ptr to it, push it front on the new MPL, pop back the old MPL

template <typename T, template <class> class Policy >
struct MakeEachMPLToSharedPtr
{
private:
  template <typename T2, bool B>
  struct Helper
  {
    typedef typename boost::mpl::push_front
    <
      typename MakeEachMPLToSharedPtr<typename boost::mpl::pop_back<T2>::type, Policy>::type,
      typename Policy<
	typename boost::mpl::back<T2>::type >::type
      >::type type;

};

  template <typename T2>
  struct Helper<T2, true>
  {
    typedef T2 type;
  };

  public:
    typedef typename Helper<T, boost::mpl::empty<T>::type::value>::type type;
};

#endif	// !MAKEEACHMPLTOSHAREDPTR_HPP_
