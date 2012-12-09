#ifndef         _CPLUSPLUSML_OBJECT_DEPENDENCY_HH_
# define        _CPLUSPLUSML_OBJECT_DEPENDENCY_HH_

# include       <string>

# include       "link.hh"

namespace                       CplusplusML
{
  namespace                     Object
  {
    class                       Dependency : public Link
    {
    public:
      Dependency();
      virtual ~Dependency() {}
    };
  }
}

#endif // _CPLUSPLUSML_OBJECT_DEPENDENCY_HH_
