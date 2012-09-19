#include "object/class.hh"

namespace               Object
{
  Class::Class()
  {
    title_ = "Class";
    typeLabel_->setText("class");
    //    typeLabel_->setPen(QPen(Qt::red));

    updateGraphics();
  }
}
