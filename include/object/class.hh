#ifndef         _CPLUSPLUSML_OBJECT_CLASS_HH_
# define        _CPLUSPLUSML_OBJECT_CLASS_HH_

# include       "classificator.hh"

namespace               CplusplusML
{
  namespace             Object
  {
    // Class object
    class               Class : public Classificator
    {
    public:
      Class();
      ~Class() { }
    };
  }
}

#endif // _CPLUSPLUSML_OBJECT_CLASS_HH_
