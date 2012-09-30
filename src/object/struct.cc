#include "object/struct.hh"

namespace               CplusplusML
{
  namespace             Object
  {
    // CTOR for Struct object
    Struct::Struct()
    {
      type_ = Type::objectStruct;
      name = typeName = "Struct";
    }
  }
}
