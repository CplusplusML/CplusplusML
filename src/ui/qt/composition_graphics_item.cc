#include "ui/qt/composition_graphics_item.hh"

namespace CplusplusML
{
  namespace Ui
  {
    namespace Qt
    {
      Composition::Composition() :
        Link(nullptr)
      {
        this->backHead.setType(LinkHead::Type::DIAMOND_FILLED);
        this->pen.setStyle(::Qt::SolidLine);
      }
    }
  }
}
