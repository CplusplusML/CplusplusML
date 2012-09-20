#include "object/template_param.hh"

namespace               Object
{
  TemplateParam::TemplateParam()
  {
    QPen                pen(Qt::DashDotLine);

    title_ = "Param";
    typeLabel_->setParentItem(0);
    titleRect_->setPen(pen);
    attrRect_->setPen(pen);
    opeRect_->setPen(pen);

    updateGraphics();
  }
}
