#include "object/template_param.hh"

namespace               CplusplusML
{
  namespace             Object
  {
    // CTOR/DTORS
    TemplateParam::TemplateParam()
    {
      type_ = Type::objectTemplate;
      name = typeName = "Param";
    }
  }
}
