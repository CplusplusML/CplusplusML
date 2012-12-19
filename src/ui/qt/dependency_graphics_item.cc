#include "ui/qt/dependency_graphics_item.hh"

namespace CplusplusML
{
  namespace Ui
  {
    namespace Qt
    {
      Dependency::Dependency() :
        Link(nullptr)
      {
        this->frontHead.setType(LinkHead::Type::SMALL_TIP);
        this->pen.setStyle(::Qt::DotLine);
      }
    }
  }
}
