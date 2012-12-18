#include "ui/qt/template_specialization_parameter_graphics_item.hh"

namespace CplusplusML
{
  namespace Ui
  {
    namespace Qt
    {
      TemplateSpecializationParameter::TemplateSpecializationParameter() :
        Link(nullptr)
      {
        this->frontHead.setType(LinkHead::Type::DOUBLE_FILLED);
        this->pen.setStyle(::Qt::DashDotLine);
      }
    }
  }
}
