
#include <iostream>

#include "assed.hpp"

namespace AST
{
  Inheritance::Inheritance(Class &c, Visibility v) :
    _class(&c), _visibility(v)
  {}

  Inheritance::~Inheritance()
  {}

  std::ostream& operator<<(std::ostream &o,
			   Inheritance inh)
  {
    o << inh._visibility;
    o << " " << inh._class->name();  
  }

  bool operator==(const Class &c, const Inheritance &inh)
  {
    return (inh == c);
  }

  bool operator==(const Inheritance &inh, const Class &c)
  {
    return (inh._class->name() == c.name());
  }

}
