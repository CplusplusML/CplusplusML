#include "object/struct.hh"

namespace               Object
{
  Struct::Struct()
  {
    title_ = "Struct";
    typeLabel_->setText("struct");
    // typeLabel_->setPen(QPen(Qt::green));

    updateGraphics();
  }
}
