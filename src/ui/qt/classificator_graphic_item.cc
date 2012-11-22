#include        <iostream> //DEBUG

#include        <QPainter>

#include        "ui/qt/classificator_graphic_item.hh"
#include        "object/meta_classificator.hh"
#include        "object/members.hh"

using namespace std; //DEBUG

namespace               CplusplusML
{
  namespace             Ui
  {
    namespace           Qt
    {
      namespace         Object = ::CplusplusML::Object;

      QRectF            Classificator::boundingRect() const
      {
        QFont           font = QFont("Sans", 8);

        int             attrSize = object_->attributes.size();
        int             opeSize = object_->operations.size();
        int             totHeight;
        int             totWidth;
        int             tmp;
        
        // Compute total height;
        totHeight = QFontMetrics(font).height() + 4;
        font.setPointSize(15);
        font.setBold(true);
        totHeight += QFontMetrics(font).height() + 4;
        font.setPointSize(10);
        font.setBold(false);
        totHeight += (attrSize && object_->isAttrVisible) ?
          (1 + ((opeSize && object_->isOpeVisible) ? 1 : 0)) : 0;
        if (object_->isAttrVisible)
          totHeight += (QFontMetrics(font).height() + 2) * attrSize;
        if (object_->isOpeVisible)
          totHeight += (QFontMetrics(font).height() + 2) * opeSize;
        if (attrSize && object_->isAttrVisible)
          totHeight += 5;
        if (opeSize && object_->isOpeVisible)
          totHeight += 5;
        totHeight += 5;

        // Compute total width
        font.setPointSize(8);
        totWidth = QFontMetrics(font).width(object_->typeName.c_str()) + 4;
        font.setPointSize(15);
        font.setBold(true);
        tmp = QFontMetrics(font).width(object_->name.c_str()) + 4;
        if (tmp > totWidth)
          totWidth = tmp;
        font.setPointSize(10);
        font.setBold(false);

        QFontMetrics fm(font);
        if (object_->isAttrVisible)
          for (Object::Members::Attribute *attr : object_->attributes)
            {
              tmp = fm.width(attr->ToString().c_str()) + 4;
              if (tmp > totWidth)
                totWidth = tmp;
            }
        if (object_->isOpeVisible)
          for (Object::Members::Operation *ope : object_->operations)
            {
              tmp = fm.width(ope->ToString().c_str()) + 4;
              if (tmp > totWidth)
                totWidth = tmp;
            }

        if (totWidth < 120)
          totWidth = 120;

        return QRectF(0, 0, totWidth, totHeight);
      }

      void              Classificator::paint(QPainter *painter,
                                             const QStyleOptionGraphicsItem *,
                                             QWidget *)
      {
        QFont           font = QFont("Sans", 8);
        QPen            pen = painter->pen();

        int             attrSize = object_->attributes.size();
        int             opeSize = object_->operations.size();
        int             totHeight;
        int             totWidth;
        int             tmp;
        ::Qt::PenStyle  penStyle = ::Qt::SolidLine;
        
        if (object_->GetType() == Object::Type::objectMetaClassificator)
          penStyle = ::Qt::DashDotLine;

        pen.setStyle(penStyle);
        pen.setColor(0xb4b4b4);
        // Compute total height;
        totHeight = QFontMetrics(font).height() + 4;
        font.setPointSize(15);
        font.setBold(true);
        totHeight += QFontMetrics(font).height() + 4;
        font.setPointSize(10);
        font.setBold(false);
        totHeight += (attrSize && object_->isAttrVisible) ?
          (1 + ((opeSize && object_->isOpeVisible) ? 1 : 0)) : 0;
        if (object_->isAttrVisible)
          totHeight += (QFontMetrics(font).height() + 2) * attrSize;
        if (object_->isOpeVisible)
          totHeight += (QFontMetrics(font).height() + 2) * opeSize;
        if (attrSize && object_->isAttrVisible)
          totHeight += 5;
        if (opeSize && object_->isOpeVisible)
          totHeight += 5;
        totHeight += 5;

        // Compute total width
        font.setPointSize(8);
        totWidth = QFontMetrics(font).width(object_->typeName.c_str()) + 4;
        font.setPointSize(15);
        font.setBold(true);
        tmp = QFontMetrics(font).width(object_->name.c_str()) + 4;
        if (tmp > totWidth)
          totWidth = tmp;
        font.setPointSize(10);
        font.setBold(false);

        QFontMetrics fm(font);
        if (object_->isAttrVisible)
          for (Object::Members::Attribute *attr : object_->attributes)
            {
              tmp = fm.width(attr->ToString().c_str()) + 4;
              if (tmp > totWidth)
                totWidth = tmp;
            }
        if (object_->isOpeVisible)
          for (Object::Members::Operation *ope : object_->operations)
            {
              tmp = fm.width(ope->ToString().c_str()) + 4;
              if (tmp > totWidth)
                totWidth = tmp;
            }

        if (totWidth < 120)
          totWidth = 120;

        // Draw Rect
        painter->setPen(pen);
        painter->setBrush(QBrush(0xfafafa));
        painter->drawRoundedRect(0, 0, totWidth, totHeight, 5, 5);
        totHeight = 0;

        // Draw type
        font.setPointSize(8);
        tmp = QFontMetrics(font).height() + 4;
        totHeight += tmp;
        painter->setPen(QPen(0x696969));
        painter->setFont(font);
        painter->drawText(QRectF(0, 5, totWidth, tmp),
                          ::Qt::AlignHCenter | ::Qt::AlignVCenter,
                          object_->typeName.c_str());

        // Draw name
        font.setPointSize(15);
        font.setBold(true);
        painter->setFont(font);
        painter->setPen(QPen(0x494949));
        tmp = QFontMetrics(font).height() + 4;
        painter->drawText(QRectF(0, totHeight, totWidth, tmp),
                          ::Qt::AlignHCenter | ::Qt::AlignBottom,
                          object_->name.c_str());
        totHeight += tmp;

        // Draw attributes
        font.setPointSize(10);
        font.setBold(false);
        painter->setFont(font);
        tmp = QFontMetrics(font).height() + 2;
        if (object_->isAttrVisible)
          if (attrSize)
            {
              totHeight += 5;
              painter->setPen(pen);
              painter->drawLine(0, totHeight, totWidth, totHeight);
              totHeight += 1;
              painter->setPen(QPen(0x393939));
              for (Object::Members::Attribute *attr : object_->attributes)
                {
                  painter->drawText(2, totHeight + tmp - 2,
                                    attr->ToString().c_str());
                  totHeight += tmp;
                }
            }
        if (object_->isOpeVisible)
          if (opeSize)
            {
              totHeight += 5;
              painter->setPen(pen);
              painter->drawLine(0, totHeight, totWidth, totHeight);
              totHeight += 1;
              painter->setPen(QPen(0x393939));
              for (Object::Members::Operation *ope : object_->operations)
                {
                  painter->drawText(2, totHeight + tmp - 2,
                                    ope->ToString().c_str());
                  totHeight += tmp;
                }
            }
      }
    }
  }
}
