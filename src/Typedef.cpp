
#include "Typedef.hpp"

namespace AST
{
  std::ostream& operator<<(std::ostream &o,
			   const Typedef &t)
  {
    o << "typedef " << t.name_ << " " << t.txt_ << ";";
    return (o);
  }

  Typedef::Typedef(const std::string &name, const std::string &txt) :
    name_(name), txt_(txt)
  {}

  Typedef::~Typedef()
  {}

  const std::string& Typedef::name() const
  {
    return (name_);
  }
}
