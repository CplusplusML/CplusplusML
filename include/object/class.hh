#ifndef         _CPLUSPLUSML_OBJECT_CLASS_H_
# define        _CPLUSPLUSML_OBJECT_CLASS_H_

# include       "complex.hh"

namespace               Object
{
  class                 Class : public Complex_
  {
  public:
    Class();
    ~Class() { }
  };
}

#endif // _CPLUSPLUSML_OBJECT_CLASS_H_
