
#include <iostream>
#include "Temp.hpp"

namespace AST
{
  Temp::Temp(const std::string &name, const std::string &txt) : name_(name), txt_(txt)
  {}

  Temp::~Temp()
  {}

  const std::string& Temp::name() const
  {
    return (name_);
  }

  std::ostream& operator<<(std::ostream &o,
			   const Temp &v)
  {
    o << v.txt_ << ';' << std::endl;
    return (o);
  }
}
