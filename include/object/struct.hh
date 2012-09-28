#ifndef         _CPLUSPLUSML_OBJECT_STRUCT_HH_
# define        _CPLUSPLUSML_OBJECT_STRUCT_HH_

# include       "classificator.hh"

namespace               CplusplusML
{
  namespace             Object
  {
    // Structure object
    class               Struct : public Classificator
    {
    public:
      Struct();
      ~Struct() { }
    };
  }
}

#endif // _CPLUSPLUSML_OBJECT_STRUCT_HH_
