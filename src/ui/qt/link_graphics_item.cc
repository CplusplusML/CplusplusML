#include <cmath>

#include <QDebug>

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QKeyEvent>

// Booh !
#include "ui/qt/classificator_graphic_item.hh"

#include "ui/qt/link_graphics_item.hh"
#include "ui/qt/link_connection_graphics_item.hh"

namespace CplusplusML
{
  namespace Ui
  {
    namespace Qt
    {
      namespace Object = ::CplusplusML::Object;

      Link::Link(Object::Link* /*linkObject*/) :
        path(QPointF(0, 0))
      {
        this->headItem = nullptr;
        this->tailItem = nullptr;
        this->hovered = false;
        this->setFlag(QGraphicsItem::ItemIsSelectable, true);
        this->setFlag(QGraphicsItem::ItemIsFocusable, true);
        this->setZValue(2.0);

        this->pen.setStyle(::Qt::SolidLine);
        this->pen.setWidth(1);
        this->pen.setBrush(::Qt::black);
        this->pen.setCapStyle(::Qt::FlatCap);
        this->pen.setJoinStyle(::Qt::RoundJoin);

        this->outlinePen.setStyle(::Qt::SolidLine);
        this->outlinePen.setCapStyle(::Qt::RoundCap);
        this->outlinePen.setJoinStyle(::Qt::RoundJoin);
        this->outlinePen.setWidth(pen.width());
        this->outlinePen.setBrush(::Qt::blue);

        this->path.lineTo(QPointF(5, 5));

        this->frontHead.setParentItem(this);
        this->backHead.setParentItem(this);
      }

      QLineF Link::firstPathLine()
      {
        QPainterPath::Element const& e0 = this->path.elementAt(0);
        QPainterPath::Element const& e1 = this->path.elementAt(1);

        Q_ASSERT(e1.isLineTo() == true);
        return (QLineF(e0, e1));
      }

      QLineF Link::lastPathLine()
      {
        Q_ASSERT(this->path);

        QPainterPath::Element const& e0 = this->path.elementAt(this->path.elementCount() - 2);
        QPainterPath::Element const& e1 = this->path.elementAt(this->path.elementCount() - 1);

        Q_ASSERT(e1.isLineTo() == true);
        return (QLineF(e0, e1));
      }

      double    Link::angle()
      {
        QLineF linkLine = QLineF(tailItem->scenePos(), headItem->scenePos());
        double angle = std::acos(linkLine.dx() / linkLine.length());

        if (linkLine.dy() < 0)
          angle = (2.0 * M_PI) - angle;
        return angle;
      }

      void        Link::adjustLink()
      {
        if (this->headItem && this->tailItem)
          {
            prepareGeometryChange();
            QRectF tailItemRect = this->tailItem->boundingRect();
            QRectF headItemRect = this->headItem->boundingRect();
            QPointF newPos = this->tailItem->scenePos() + this->tailItem->boundingRect().center();
            QPointF head = headItemRect.center();
            double angle = this->angle();
            double arrowHeadAngle;

            //            QPointF origin = QPointF(0, 0);
            QPointF headOffset;
            QPointF tailOffset;

            if (angle > (7.0 * M_PI) / 4.0 || angle < M_PI / 4)
              {
                tailOffset =  QPointF(tailItemRect.width() / 2, 0);
                headOffset = QPointF(-headItemRect.width() / 2, 0);
                orientation = LinkOrientation::Horizontal;
                arrowHeadAngle = 0;
              }
            else if (angle < (3.0 * M_PI) / 4.0)
              {
                tailOffset = QPointF(0, tailItemRect.height() / 2);
                headOffset = QPointF(0, -headItemRect.height() / 2);
                orientation = LinkOrientation::Vertical;
                arrowHeadAngle = M_PI / 2;
              }
            else if (angle < (5.0 * M_PI) / 4.0)
              {
                tailOffset = QPointF(-tailItemRect.width() / 2, 0);
                headOffset = QPointF(tailItemRect.width() / 2, 0);
                orientation = LinkOrientation::Horizontal;
                arrowHeadAngle = M_PI;
              }
            else
              {
                tailOffset = QPointF(0, -tailItemRect.height() / 2);
                headOffset = QPointF(0, headItemRect.height() / 2);
                orientation = LinkOrientation::Vertical;
                arrowHeadAngle = 3.0 * M_PI / 2;
              }
            newPos += tailOffset;
            head += headOffset;

            this->setPos(newPos);
            head = this->mapFromItem(this->headItem, head);

            QPointF     p1;
            QPointF     p2;

            if (orientation == LinkOrientation::Vertical)
              {
                p1 = QPointF(0, head.y() / 2);
                p2 = p1 + QPointF(head.x(), 0);
              }
            else
              {
                p1 = QPointF(head.x() / 2, 0);
                p2 = p1 + QPointF(0, head.y());
              }
            this->path = QPainterPath(QPointF(0, 0));
            this->path.lineTo(p1);
            this->path.lineTo(p2);
            this->path.lineTo(head);

            frontHead.setAngle(M_PI + arrowHeadAngle);
            frontHead.setSize(this->pen.width());
            frontHead.setOrigin(head);

            backHead.setAngle(arrowHeadAngle);
            backHead.setSize(this->pen.width());
            backHead.setOrigin(QPointF(0, 0));

            {
              static const int borderSize = 2;
              QString tailText = "private";
              //              QFont f("Helvetica", 10);
              QFont f;
              QFontMetrics fm(f);
              QLineF tailVector(QPointF(0, 0), tailOffset);
              QPointF baseLine;
              qreal rectOffset;

              this->tailTextRect = fm.boundingRect(tailText);
              this->tailTextRect.setWidth(this->tailTextRect.width() + borderSize * 2);
              this->tailTextRect.setHeight(this->tailTextRect.height() + borderSize * 2);

              rectOffset = std::abs(tailOffset.x() != 0 ? tailTextRect.width() / 2 : tailTextRect.height() / 2);
              if (!this->backHead.boundingRect().isNull())
                {
                  QRectF bRect = this->backHead.boundingRect();

                  rectOffset += std::max(bRect.width(), bRect.height());
                  qDebug() << "backHead.bRect(): " << this->backHead.boundingRect();
                }
              qDebug() << "rectOffset: " << rectOffset;
              //(tailVector.unitVector().p2() * (tailTextRect.width() / 2))
              this->tailTextRect.moveCenter(tailVector.unitVector().p2() * (rectOffset + 3));
              baseLine = this->tailTextRect.bottomLeft() +
                QPointF((this->tailTextRect.width() - fm.width(tailText)) / 2, -(fm.descent() + borderSize));
              qDebug() << "tailTextRect: " << tailTextRect;
              qDebug() << "baseLine: " << baseLine;
              this->tailTextPath = QPainterPath();
              this->tailTextPath.setFillRule(::Qt::WindingFill);
              //              this->tailTextPath.addRect(tailTextRect);
              this->tailTextPath.addText(baseLine, f, tailText);
              this->tailTextPath.closeSubpath();

              qDebug() << "fm.width: " << fm.width(tailText);
            }
          }
      }

      void Link::paint(QPainter *painter,
                                 const QStyleOptionGraphicsItem */*option*/,
                                 QWidget */*widget*/)
      {
        painter->setRenderHints(QPainter::Antialiasing | QPainter::HighQualityAntialiasing | QPainter::TextAntialiasing);
        //        painter->setRenderHints(QPainter::Antialiasing | QPainter::HighQualityAntialiasing);

        if (this->isSelected())
          {
            painter->setPen(outlinePen);
            painter->drawPath(shape());
          }
        painter->setPen(this->pen);
        painter->drawPath(this->path);

        {
          QPen _pen;

          painter->fillRect(this->tailTextRect, ::Qt::white);

          _pen.setStyle(::Qt::DotLine);
          _pen.setWidth(1);
          _pen.setColor(::Qt::black);
          painter->setPen(_pen);
          painter->drawRect(this->tailTextRect);

          _pen.setStyle(::Qt::SolidLine);
          painter->setPen(_pen);
          painter->drawPath(this->tailTextPath);
        }

        if (false) // When debugging =D
          {
            QPen _pen;
            _pen.setStyle(::Qt::DotLine);
            _pen.setWidth(0);
            _pen.setBrush(::Qt::magenta);
            painter->setPen(_pen);
            painter->drawRect(boundingRect());
          }
        if (false) // When debugging =D
          {
            QRectF prect(0, 0, 20, 20);
            QPen _pen;
            _pen.setStyle(::Qt::SolidLine);
            _pen.setWidth(2);
            _pen.setBrush(::Qt::red);
            painter->setPen(_pen);
            prect.moveCenter(this->lastPathLine().p2());
            painter->drawRect(prect);

            _pen.setBrush(::Qt::blue);
            painter->setPen(_pen);
            prect.moveCenter(this->firstPathLine().p1());
            painter->drawRect(prect);
          }
      }

      QPainterPath Link::shape() const
      {
        QPainterPathStroker stroker;
        QPainterPath path = this->path;

        path.addPath(frontHead.shape());
        path.addPath(backHead.shape());
        path.addRect(tailTextRect);
        path.addPath(tailTextPath);
        stroker.setWidth(pen.width() * 2);
        stroker.setCapStyle(::Qt::RoundCap);
        stroker.setJoinStyle(::Qt::RoundJoin);
        return stroker.createStroke(path);
      }

      QRectF Link::boundingRect() const
      {
        // Not really optimized, but good enough for now
        return (shape().boundingRect());
      }

      //DEBUG
      bool Link::sceneEvent(QEvent *event)
      {
        bool handled = true;

        qDebug() << "Link::sceneEvent - type: " << event->type();
        switch (event->type())
          {
          case QEvent::GraphicsSceneMousePress:
            qDebug() << "Link::sceneEvent: QEvent::GraphicsSceneMousePress";
            if (this->tailItem == nullptr)
              {
                QGraphicsSceneMouseEvent *me = static_cast<QGraphicsSceneMouseEvent*>(event);
                Classificator* classificator = this->searchSceneItem<Classificator>(me->scenePos());

                if (classificator != nullptr)
                  {
                    qDebug() << "Classificator found: " << classificator;
                    QPointF center = classificator->scenePos() + classificator->boundingRect().center();

                    this->tailItem = classificator;
                    this->setPos(center);
                    this->path = QPainterPath(QPointF(0, 0));
                    this->path.lineTo(QPointF(1.0, 1.0));
                    qDebug() << "Bounding rect: " << classificator->boundingRect();
                    qDebug() << "Path changed: " << this->path;
                    adjustLink();
                  }
                else
                  delete this;
              }
            else
              handled = false;
            break;
          case QEvent::GraphicsSceneMouseRelease:
            qDebug() << "Link::sceneEvent: QEvent::GraphicsSceneMouseRelease";
            if (this->headItem == nullptr)
              {
                QGraphicsSceneMouseEvent *me = static_cast<QGraphicsSceneMouseEvent*>(event);
                Classificator* classificator = this->searchSceneItem<Classificator>(me->scenePos());

                if (classificator != nullptr)
                  {
                    this->headItem = classificator;
                    this->setZValue(0.0);
                    adjustLink();
                    connect(tailItem, SIGNAL(moved()),
                            this, SLOT(itemMoved()));
                    connect(headItem, SIGNAL(moved()),
                            this, SLOT(itemMoved()));
                    connect(tailItem, SIGNAL(removed()),
                            this, SLOT(itemRemoved()));
                    connect(headItem, SIGNAL(removed()),
                            this, SLOT(itemRemoved()));
                  }
                else
                  delete this;
              }
            break;
          case QEvent::GraphicsSceneMouseMove:
            qDebug() << "Link::sceneEvent: QEvent::GraphicsSceneMouseMove";
            if (this->headItem == nullptr)
              {
                QGraphicsSceneMouseEvent *me = static_cast<QGraphicsSceneMouseEvent*>(event);

                prepareGeometryChange();
                this->path = QPainterPath(QPointF(0, 0));
                this->path.lineTo(me->pos());
              }
            break;
          default:
            handled = false;
            break;
          }
        qDebug() << "event handled: " << handled;
        return handled || QGraphicsObject::sceneEvent(event);
      }

      bool Link::eventFilter(QObject *obj, QEvent *ev)
      {
        //  qDebug() << "GLOBAL EVENT: " << ev << " - OBJ: " << obj;
        return QObject::eventFilter(obj, ev);
      }

      template <class T>
      T* Link::searchSceneItem(QPointF const& pos)
      {
        QList<QGraphicsItem*> hoveredItems = scene()->items(pos);

        hoveredItems.removeAll(this);
        foreach(QGraphicsItem* item, hoveredItems)
          {
            T* tItem = dynamic_cast<T*>(item);

            if (tItem)
              return tItem;
          }
        return nullptr;
      }

      void      Link::itemMoved()
      {
        this->adjustLink();
      }

      void      Link::itemRemoved()
      {
        qDebug() << "Classificator removed: Removing self";
        delete this;
      }
    }
  }
}
