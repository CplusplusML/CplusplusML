#ifndef _STRUCT_H_
#define _STRUCT_H_

#include "complex.hh"

namespace Object
{
  class Struct : public Complex_
  {
  public:
    Struct() { }
    ~Struct() { }
    char Label_();
  };
}

#endif /* _STRUCT_H_ */
