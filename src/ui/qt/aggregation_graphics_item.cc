#include "ui/qt/aggregation_graphics_item.hh"

namespace CplusplusML
{
  namespace Ui
  {
    namespace Qt
    {
      Aggregation::Aggregation() :
        Link(nullptr)
      {
        this->backHead.setType(LinkHead::Type::DIAMOND_EMPTY);
        this->pen.setStyle(::Qt::SolidLine);
      }
    }
  }
}
