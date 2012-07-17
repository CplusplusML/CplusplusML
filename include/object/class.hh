#ifndef _CLASS_H_
#define _CLASS_H_

#include "complex.hh"

namespace Object
{
  class Class : public Complex_
  {
  public:
    Class() { }
    ~Class() { }
    char Label_();
  };
}

#endif /* _CLASS_H_ */
