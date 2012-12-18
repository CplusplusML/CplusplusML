#include "ui/qt/inheritance_graphics_item.hh"

namespace CplusplusML
{
  namespace Ui
  {
    namespace Qt
    {
      Inheritance::Inheritance() :
        Link(nullptr)
      {
        this->backHead.setType(LinkHead::Type::SIMPLE_EMPTY);
        this->pen.setStyle(::Qt::SolidLine);
      }
    }
  }
}
