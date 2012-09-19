#include        <iostream> //DEBUG
#include        "object/complex.hh"
#include        "object/dependency.hh"

namespace               Object
{
  using namespace       Members;

  Complex_::Complex_():
    title_("Complex"),
    titleLabel_(new QGraphicsSimpleTextItem("Complex")),
    typeLabel_(new QGraphicsSimpleTextItem("complex")),
    titleRect_(new QGraphicsRectItem),
    attrRect_(new QGraphicsRectItem),
    opeRect_(new QGraphicsRectItem)
  {
    QFont               font;

    //    pen.setWidth(1);
    // Set font of titleLabel;
    font.setPointSize(15);
    font.setFamily("arial");
    font.setBold(true);
    titleLabel_->setFont(font);
    // Set font of typeLabel
    font.setBold(false);
    font.setPointSize(4);

    // Set brush for rects
    titleRect_->setBrush(QColor(250, 250, 250));
    attrRect_->setBrush(QColor(250, 250, 250));
    opeRect_->setBrush(QColor(250, 250, 250));

    titleLabel_->setParentItem(titleRect_);
    typeLabel_->setParentItem(titleRect_);

    // Add all items to group
    addToGroup(titleRect_);
    addToGroup(attrRect_);
    addToGroup(opeRect_);
    setFlag(QGraphicsItem::ItemIsMovable, true);

    for (int i = 0; i < 8; ++i)
      connections.append(new ArrowConnection(this));
  }

  Complex_::~Complex_()
  {
  }

  void Complex_::adjustConnections()
  {
    QRectF borders = boundingRect();

    connections[0]->moveCenter(borders.topLeft());
    connections[1]->moveCenter(borders.topRight());
    connections[2]->moveCenter(borders.bottomLeft());
    connections[3]->moveCenter(borders.bottomRight());
    connections[4]->moveCenter(borders.topLeft() + QPointF(borders.width() / 2, 0));
    connections[5]->moveCenter(borders.bottomLeft() + QPointF(borders.width() / 2, 0));
    connections[6]->moveCenter(borders.topLeft() + QPointF(0, borders.height() / 2));
    connections[7]->moveCenter(borders.topRight() + QPointF(0, borders.height() / 2));
  }
  
  void                  Complex_::updateGraphics(void)
  {
    int                 width;
    int                 titleHeight;
    int                 attrHeight;
    int                 opeHeight;
    int                 ypos;
    static QFont        normalFont;
    static QFont        staticFont;

    staticFont.setUnderline(true);

    // Title
    titleLabel_->setText(title_.c_str());
    width = titleLabel_->boundingRect().width();

    titleHeight = typeLabel_->boundingRect().height() +
      titleLabel_->boundingRect().height() + 6;

    // Remove from group what's gonna be redrawed
    removeFromGroup(titleRect_);
    removeFromGroup(attrRect_);
    removeFromGroup(opeRect_);

    // Update attributes, set parent, update label, width and height
    attrHeight = 0;
    for (Attribute *attr : attributes_)
      {
        attr->label->setParentItem(attrRect_);
        attr->updateLabel();
        if (attr->label->boundingRect().width() > width)
          width = attr->label->boundingRect().width();
        attrHeight += attr->label->boundingRect().height() + 4;
      }

    // Update operations, set parent, update label, width and height
    opeHeight = 0;    
    for (Operation *ope : operations_)
      {
        ope->label->setParentItem(opeRect_);
        ope->updateLabel();
        if (ope->label->boundingRect().width() > width)
          width = ope->label->boundingRect().width();
        opeHeight += ope->label->boundingRect().height() + 4;
      }

    // Add padding
    if (width < 124)
      width = 124;
    width += 4;

    // Update position
    x_ = width / -2;
    y_ = (titleHeight + attrHeight + opeHeight) / -2;

    // Update labels position
    typeLabel_->setPos(x_ + width / 2 - typeLabel_->boundingRect().width() / 2 + 2, y_ + 2);
    titleLabel_->setPos(x_ + width / 2 - titleLabel_->boundingRect().width() / 2 + 2,
                        y_ + typeLabel_->boundingRect().height() + 2);

    // Update rects
    titleRect_->setRect(x_, y_, width, titleHeight);
    attrRect_->setRect(x_, y_ + titleHeight, width, attrHeight);
    opeRect_->setRect(x_, y_ + titleHeight + attrHeight, width, opeHeight);

    // Update labels pos
    ypos = 0;
    for (Attribute *attr : attributes_)
      {
        attr->label->setFont(attr->isStatic ? staticFont : normalFont);
        attr->label->setPos(x_ + 2, y_ + titleHeight + ypos + 2);
        ypos += attr->label->boundingRect().height() + 4;
      }

    ypos = 0;
    for (Operation *ope : operations_)
      {
        ope->label->setFont(ope->isStatic ? staticFont : normalFont);
        ope->label->setPos(x_ + 2, y_ + titleHeight + attrHeight + ypos + 2);
        ypos += ope->label->boundingRect().height() + 4;
      }

    // Add rects again to group
    addToGroup(titleRect_);
    addToGroup(attrRect_);
    addToGroup(opeRect_);

    adjustConnections();
  }

  void                  Complex_::updateFromForm(Ui::ComplexProperty const &ui)
  {
    CplusplusML::MemberListItem   *item;
    Attribute           *attr;
    Operation           *ope;

    // Get informations
    title_ = ui.name->text().toStdString();
    isAbstract_ = ui.isAbstract->checkState();
    isAttrVisible_ = ui.isAttrVisible->checkState();
    isOpeVisible_ = ui.isOpeVisible->checkState();

    // Erase deleted attributes
    for (auto it = attributes_.begin(); it != attributes_.end();)
      {
        if ((*it)->deleted)
          delete *it;
        it = attributes_.erase(it);
      }

    // Erase deleted operations
    for (auto it = operations_.begin(); it != operations_.end();)
      {
        if ((*it)->deleted)
          delete *it;
        it = operations_.erase(it);
      }

    // For each attribute, push it in attr list
    for (int i = 0; i < ui.attrList->count(); ++i)
      {
        item = static_cast<CplusplusML::MemberListItem *>(ui.attrList->item(i));
        attr = item->member_ ? static_cast<Attribute *>(item->member_) : new Attribute;
        *attr = *(static_cast<Attribute *>(item->tmpMember_));
        if (!item->member_)
          item->member_ = attr;
        attributes_.push_back(attr);
      }

    // For each operation, push it in attr list, updateLabel and get width
    for (int i = 0; i < ui.opeList->count(); ++i)
      {
        item = static_cast<CplusplusML::MemberListItem *>(ui.opeList->item(i));
        ope = item->member_ ? static_cast<Operation *>(item->member_) : new Operation;
        *ope = *(static_cast<Operation *>(item->tmpMember_));
        if (!item->member_)
          item->member_ = ope;
        operations_.push_back(ope);
      }

    updateGraphics();
  }
}
