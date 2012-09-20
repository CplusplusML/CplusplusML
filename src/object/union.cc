#include "object/union.hh"

namespace               Object
{
  Union::Union()
  {
    title_ = "Union";
    typeLabel_->setText("Union");
    //    typeLabel_->setPen(QPen(Qt::blue));

    updateGraphics();
  }
}
