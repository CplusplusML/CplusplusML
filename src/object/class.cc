#include "object/class.hh"

namespace               CplusplusML
{
  namespace             Object
  {
    // CTOR for Class object
    Class::Class()
    {
      type_ = Type::objectClass;
      name = typeName = "Class";
    }
  }
}
