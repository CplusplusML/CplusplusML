#ifndef         _CPLUSPLUSML_UI_QT_DEPENDENCY_GRAPHICS_ITEM_HH_
# define        _CPLUSPLUSML_UI_QT_DEPENDENCY_GRAPHICS_ITEM_HH_

#include "ui/qt/link_graphics_item.hh"

namespace CplusplusML
{
  namespace Ui
  {
    namespace Qt
    {
      namespace Object = ::CplusplusML::Object;

      class Dependency : public Link
      {
      public:
        Dependency();
      };
    }
  }
}

#endif  // !_CPLUSPLUSML_UI_QT_DEPENDENCY_GRAPHICS_ITEM_HH_
