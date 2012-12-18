#include "ui/qt/template_parameter_graphics_item.hh"

namespace CplusplusML
{
  namespace Ui
  {
    namespace Qt
    {
      TemplateParameter::TemplateParameter() :
        Link(nullptr)
      {
        this->frontHead.setType(LinkHead::Type::SIMPLE_FILLED);
        this->pen.setStyle(::Qt::DashDotLine);
      }
    }
  }
}
