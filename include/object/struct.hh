#ifndef         _CPLUSPLUSML_OBJECT_STRUCT_H_
# define        _CPLUSPLUSML_OBJECT_STRUCT_H_

# include       "complex.hh"

namespace               Object
{
  class                 Struct : public Complex_
  {
  public:
    Struct();
    ~Struct() { }
  };
}

#endif // _CPLUSPLUSML_OBJECT_STRUCT_H_
