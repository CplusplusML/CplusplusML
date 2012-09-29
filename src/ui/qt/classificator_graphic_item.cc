#include        <iostream> //DEBUG

#include        <QPainter>

#include        "ui/qt/classificator_graphic_item.hh"
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

        int             attrSize = object_->GetAttributes().size();
        int             opeSize = object_->GetOperations().size();
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
        totHeight += attrSize ? (1 + (opeSize ? 1 : 0)) : 0;
        totHeight += (QFontMetrics(font).height() + 2) * (attrSize + opeSize);
        if (attrSize)
          totHeight += 5;
        if (opeSize)
          totHeight += 5;
        totHeight += 5;

        // Compute total width
        font.setPointSize(8);
        totWidth = QFontMetrics(font).width(object_->GetType().c_str()) + 4;
        font.setPointSize(15);
        font.setBold(true);
        tmp = QFontMetrics(font).width(object_->GetName().c_str()) + 4;
        if (tmp > totWidth)
          totWidth = tmp;
        font.setPointSize(10);
        font.setBold(false);

        QFontMetrics fm(font);
        for (Object::Members::Attribute *attr : object_->GetAttributes())
          {
            tmp = fm.width(attr->ToString().c_str()) + 4;
            if (tmp > totWidth)
              totWidth = tmp;
          }
        for (Object::Members::Operation *ope : object_->GetOperations())
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

        int             attrSize = object_->GetAttributes().size();
        int             opeSize = object_->GetOperations().size();
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
        totHeight += attrSize ? (1 + (opeSize ? 1 : 0)) : 0;
        totHeight += (QFontMetrics(font).height() + 2) * (attrSize + opeSize);
        if (attrSize)
          totHeight += 5;
        if (opeSize)
          totHeight += 5;
        totHeight += 5;

        // Compute total width
        font.setPointSize(8);
        totWidth = QFontMetrics(font).width(object_->GetType().c_str()) + 4;
        font.setPointSize(15);
        font.setBold(true);
        tmp = QFontMetrics(font).width(object_->GetName().c_str()) + 4;
        if (tmp > totWidth)
          totWidth = tmp;
        font.setPointSize(10);
        font.setBold(false);

        QFontMetrics fm(font);
        for (Object::Members::Attribute *attr : object_->GetAttributes())
          {
            tmp = fm.width(attr->ToString().c_str()) + 4;
            if (tmp > totWidth)
              totWidth = tmp;
          }
        for (Object::Members::Operation *ope : object_->GetOperations())
          {
            tmp = fm.width(ope->ToString().c_str()) + 4;
            if (tmp > totWidth)
              totWidth = tmp;
          }

        if (totWidth < 120)
          totWidth = 120;

        // Draw Rect
        painter->setPen(QPen(0xc4c4c4));
        painter->setBrush(QBrush(0xfafafa));
        painter->drawRoundedRect(0, 0, totWidth, totHeight, 5, 5);
        totHeight = 0;

        // Draw type
        font.setPointSize(8);
        tmp = QFontMetrics(font).height() + 4;
        totHeight += tmp;
        painter->setPen(QPen(0x494949));
        painter->setFont(font);
        painter->drawText(QRectF(0, 5, totWidth, tmp),
                          ::Qt::AlignHCenter | ::Qt::AlignVCenter,
                          object_->GetType().c_str());

        // Draw name
        font.setPointSize(15);
        font.setBold(true);
        painter->setFont(font);
        tmp = QFontMetrics(font).height() + 4;
        painter->drawText(QRectF(0, totHeight, totWidth, tmp),
                          ::Qt::AlignHCenter | ::Qt::AlignBottom,
                          object_->GetName().c_str());
        totHeight += tmp;

        // Draw attributes
        font.setPointSize(10);
        font.setBold(false);
        painter->setFont(font);
        tmp = QFontMetrics(font).height() + 2;
        totHeight += 5;
        if (attrSize)
          {
            painter->setPen(QPen(0xc4c4c4));
            painter->drawLine(0, totHeight, totWidth, totHeight);
            totHeight += 1;
            painter->setPen(QPen(0x393939));
            for (Object::Members::Attribute *attr : object_->GetAttributes())
              {
                painter->drawText(2, totHeight + tmp - 2,
                                  attr->ToString().c_str());
                totHeight += tmp;
              }
          }
        if (opeSize)
          {
            totHeight += 5;
            painter->setPen(QPen(0xc4c4c4));
            painter->drawLine(0, totHeight, totWidth, totHeight);
            totHeight += 1;
            painter->setPen(QPen(0x393939));
            for (Object::Members::Operation *ope : object_->GetOperations())
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
