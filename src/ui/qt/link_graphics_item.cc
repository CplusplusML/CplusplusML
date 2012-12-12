#include <cmath>

#include <QDebug>

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>

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
        this->setFlags(0);
        this->setZValue(2.0);

        this->pen.setStyle(::Qt::DashDotLine);
        this->pen.setWidth(2);
        this->pen.setBrush(::Qt::black);
        this->pen.setCapStyle(::Qt::FlatCap);
        this->pen.setJoinStyle(::Qt::RoundJoin);

        this->outlinePen.setStyle(::Qt::SolidLine);
        this->outlinePen.setCapStyle(::Qt::RoundCap);
        this->outlinePen.setJoinStyle(::Qt::RoundJoin);
        this->outlinePen.setWidth(pen.width());
        this->outlinePen.setBrush(::Qt::green);

        this->path.lineTo(QPointF(5, 5));
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

      void Link::adjustLinkTip()
      {

        // QLineF arrowLine;
        // double angle;

        // if (this->orientation == LinkOrientation::Vertical)
        //   {
        //     angle = M_PI / 2.0;
        //     if (this->lastPathLine().dy() < 0)
        //       angle = -angle;
        //   }
        // else
        //   {
        //     angle = M_PI;
        //     if (this->lastPathLine().dx() < 0)
        //       angle = 0;
        //   }


      }

      double    Link::angle()
      {
        QLineF linkLine = QLineF(tailItem->scenePos(), headItem->scenePos());
        double angle = std::acos(std::abs(linkLine.dx()) / linkLine.length());

        if (linkLine.dx() < 0)
          angle = M_PI - angle;
        if (linkLine.dy() > 0)
          angle = (2 * M_PI) - angle;
        qDebug() << "Angle: " << angle;
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

            if (angle > (7.0 * M_PI) / 4.0 || angle < M_PI / 4)
              {
                newPos += QPointF(tailItemRect.width() / 2, 0);
                head -= QPointF(headItemRect.width() / 2, 0);
                orientation = LinkOrientation::Horizontal;
                arrowHeadAngle = M_PI;
              }
            else if (angle < (3.0 * M_PI) / 4.0)
              {
                newPos -= QPointF(0, tailItemRect.height() / 2);
                head += QPointF(0, headItemRect.height() / 2);
                orientation = LinkOrientation::Vertical;
                arrowHeadAngle = (3.0 * M_PI) / 2.0;
              }
            else if (angle < (5.0 * M_PI) / 4.0)
              {
                newPos -= QPointF(tailItemRect.width() / 2, 0);
                head += QPointF(headItemRect.width() / 2, 0);
                orientation = LinkOrientation::Horizontal;
                arrowHeadAngle = 0;
              }
            else
              {
                newPos += QPointF(0, tailItemRect.height() / 2);
                head -= QPointF(0, headItemRect.height() / 2);
                orientation = LinkOrientation::Vertical;
                arrowHeadAngle = M_PI / 2;
              }
            this->setPos(newPos);
            head = this->mapFromItem(this->headItem, head);
            qDebug() << "newPos: " << newPos;

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
            {
              qreal const arrowTipSize = 20.0;
              QPointF endPoint = this->lastPathLine().p2();
              QPointF arrowP1 = endPoint + QPointF(sin(arrowHeadAngle + M_PI / 3) * arrowTipSize,
                                                   cos(arrowHeadAngle + M_PI / 3) * arrowTipSize);
              QPointF arrowP2 = endPoint + QPointF(sin(arrowHeadAngle + M_PI - M_PI / 3) * arrowTipSize,
                                                   cos(arrowHeadAngle + M_PI - M_PI / 3) * arrowTipSize);

              this->arrowHead.clear();
              this->arrowHead << endPoint << arrowP1 << arrowP2 << endPoint;
            }
          }
      }

      void Link::paint(QPainter *painter,
                                 const QStyleOptionGraphicsItem */*option*/,
                                 QWidget */*widget*/)
      {
        //        qDebug() << "PAINT - path: " << this->path;
        painter->setRenderHints(QPainter::Antialiasing | QPainter::HighQualityAntialiasing);

        if (this->hovered) // When hovered
          {
            painter->setPen(outlinePen);
            painter->drawPath(shape());
          }
        painter->setPen(pen);
        /*        if (this->tailItem && this->headItem)
                  {*/
            /*            QLineF linkLine = QLineF(tail, head);
            // Put all this crap in a QPainterPath/QPolygon or something
            QPointF p1;
            QPointF p2;

            if (this->orientation == LinkOrientation::Vertical)
              {
                p1 = tail + QPointF(0, linkLine.dy() / 2);
                p2 = p1 + QPointF(linkLine.dx(), 0);
              }
            else
              {
                p1 = tail + QPointF(linkLine.dx() / 2, 0);
                p2 = p1 + QPointF(0, linkLine.dy());
              }
            painter->drawLine(QLineF(tail, p1));
            painter->drawLine(QLineF(p1, p2));
            painter->drawLine(QLineF(p2, head));*/
            painter->drawPath(path);
            if (this->tailItem && this->headItem)
              painter->drawPolygon(arrowHead);
            /*          }
        else
        painter->drawLine(QLineF(tail, head));*/
        if (true) // When debugging =D
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

        path.addPolygon(arrowHead);
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
            break;
          case QEvent::GraphicsSceneMouseRelease:
            qDebug() << "Link::sceneEvent: QEvent::GraphicsSceneMouseRelease";
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
                }
              else
                delete this;
            }
            break;
          case QEvent::GraphicsSceneMouseMove:
            qDebug() << "Link::sceneEvent: QEvent::GraphicsSceneMouseMove";
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
        return handled;
        //        return QGraphicsObject::sceneEvent(ev);
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
    }
  }
}
