#include "ui/qt/template_specialization_graphics_item.hh"

namespace CplusplusML
{
  namespace Ui
  {
    namespace Qt
    {
      TemplateSpecialization::TemplateSpecialization() :
        Link(nullptr)
      {
        this->frontHead.setType(LinkHead::Type::SIMPLE_EMPTY);
        this->pen.setStyle(::Qt::DashDotLine);
      }
    }
  }
}
