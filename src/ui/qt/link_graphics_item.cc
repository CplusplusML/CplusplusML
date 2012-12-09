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

      Link::Link(Object::Link* /*linkObject*/)
      {
        Render();
      }

      void Link::Render(void)
      {
        setFlag(QGraphicsItem::ItemIsMovable, true);
        setFlag(QGraphicsItem::ItemIsSelectable, true);
        setFlag(QGraphicsItem::ItemSendsScenePositionChanges, true);
        setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
        setZValue(2.0);

        pen.setStyle(::Qt::DashDotLine);
        pen.setWidth(2);
        pen.setBrush(::Qt::black);
        pen.setCapStyle(::Qt::FlatCap);
        pen.setJoinStyle(::Qt::RoundJoin);

        outlinePen.setStyle(::Qt::SolidLine);
        outlinePen.setCapStyle(::Qt::RoundCap);
        outlinePen.setJoinStyle(::Qt::RoundJoin);
        outlinePen.setWidth(pen.width());
        outlinePen.setBrush(::Qt::green);


        this->headItem = nullptr;
        this->tailItem = nullptr;
        // handles[0] = new GrabHandle(this, &tail);
        // handles[1] = new GrabHandle(this, &head);
        // connect(handles[0], SIGNAL(moved(QPointF, QPointF*)),
        //         this, SLOT(onGrabHandleMove(QPointF, QPointF*)));
        // connect(handles[1], SIGNAL(moved(QPointF, QPointF*)),
        //         this, SLOT(onGrabHandleMove(QPointF, QPointF*)));
        // disableHandles();

        //        connections << new LinkConnection(this);
        //        connections << new LinkConnection(this);
        //        adjustConnections();
      }

      void Link::disableHandles()
      {
        //setZValue(1.0);
        // handles[0]->hide();
        // handles[1]->hide();
      }

      void Link::enableHandles()
      {
        //setZValue(2.0);
        // handles[0]->show();
        // handles[1]->show();
      }

      void Link::adjustConnections()
      {
        int numSegments = connections.size() + 1;
        qreal increment = 1.0 / numSegments;
        qreal currentPos = increment;
        QLineF line = QLineF(tail, head);

        prepareGeometryChange();
        foreach(LinkConnection* connection, connections)
          {
            connection->moveCenter(line.pointAt(currentPos));
            currentPos += increment;
          }
      }

      QVariant Link::itemChange(GraphicsItemChange change, const QVariant &value)
      {
        //  qDebug() << "ITEM CHANGE";
        if (change == QGraphicsItem::ItemSelectedHasChanged)
          {
            bool selected = value.toBool();

            if (selected)
              enableHandles();
            else
              disableHandles();
          }
        return QGraphicsObject::itemChange(change, value);
      }

      void Link::adjustLinkTip()
      {
        const double Pi = std::atan(1.0) * 4;
        qreal arrowSize = 20.0;
        QLineF linkLine = QLineF(tail, head);
        QLineF arrowLine;
        double angle;

        if (this->orientation == LinkOrientation::Vertical)
          {
            angle = Pi / 2.0;
            if (linkLine.dy() < 0)
              angle = -angle;

          }
        else
          {
            angle = Pi;
            if (linkLine.dx() < 0)
              angle = 0;
          }
        QPointF arrowP1 = head + QPointF(sin(angle + Pi / 3) * arrowSize,
                                         cos(angle + Pi / 3) * arrowSize);
        QPointF arrowP2 = head + QPointF(sin(angle + Pi - Pi / 3) * arrowSize,
                                         cos(angle + Pi - Pi / 3) * arrowSize);

        arrowHead.clear();
        arrowHead << head << arrowP1 << arrowP2 << head;
      }

      void Link::paint(QPainter *painter,
                                 const QStyleOptionGraphicsItem */*option*/,
                                 QWidget */*widget*/)
      {
        painter->setRenderHints(QPainter::Antialiasing | QPainter::HighQualityAntialiasing);

        if (false) // When hovered
          {
            painter->setPen(outlinePen);
            painter->drawPath(shape());
          }
        painter->setPen(pen);
        if (this->tailItem && this->headItem)
          {
            QLineF linkLine = QLineF(tail, head);
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
            painter->drawLine(QLineF(p2, head));
            painter->drawPolygon(arrowHead);
          }
        else
          painter->drawLine(QLineF(tail, head));
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
            prect.moveCenter(head);
            painter->drawRect(prect);

            _pen.setBrush(::Qt::blue);
            painter->setPen(_pen);
            prect.moveCenter(tail);
            painter->drawRect(prect);
          }
      }

      QPainterPath Link::shape() const
      {
        QPainterPathStroker stroker;
        QPainterPath path;

        path.moveTo(tail);
        path.lineTo(head);
        path.addPolygon(arrowHead);
        stroker.setWidth(pen.width() * 2);
        stroker.setCapStyle(::Qt::RoundCap);
        stroker.setJoinStyle(::Qt::RoundJoin);
        return stroker.createStroke(path);
      }

      QRectF Link::boundingRect() const
      {
        // qreal extra = (pen.width() + 20.0) / 2.0;

        // return (QRectF(tail, head).normalized().adjusted(-extra, -extra, extra, extra) |
        //         childrenBoundingRect());

        // Not really optimized, but good enough for now
        return (shape().boundingRect());
      }

      void        Link::adjustLink()
      {
        if (this->headItem && this->tailItem)
          {
            prepareGeometryChange();
            QLineF linkLine = QLineF(tailItem->scenePos(), headItem->scenePos());
            QRectF tailItemRect = this->tailItem->boundingRect();
            QRectF headItemRect = this->headItem->boundingRect();

            if ((::abs(linkLine.dy()) - (tailItemRect.height() / 2) - (headItemRect.height() / 2)) > 100.0)
              {
                if (linkLine.dy() > 0)
                  {
                    this->setPos(this->tailItem->scenePos() +
                                 tailItemRect.center() +
                                 QPointF(0, tailItemRect.height() / 2));
                    this->head = this->mapFromItem(this->headItem, headItemRect.center() -
                                                   QPointF(0, headItemRect.height() / 2));
                  }
                else
                  {
                    this->setPos(this->tailItem->scenePos() +
                                 tailItemRect.center() -
                                 QPointF(0, tailItemRect.height() / 2));
                    this->head = this->mapFromItem(this->headItem, headItemRect.center() +
                                                   QPointF(0, headItemRect.height() / 2));
                  }
                orientation = LinkOrientation::Vertical;
              }
            else
              {
                if (linkLine.dx() > 0)
                  {
                    this->setPos(this->tailItem->scenePos() +
                                 tailItemRect.center() +
                                 QPointF(tailItemRect.width() / 2, 0));
                    this->head = this->mapFromItem(this->headItem, headItemRect.center() -
                                                   QPointF(headItemRect.width() / 2, 0));
                  }
                else
                  {
                    this->setPos(this->tailItem->scenePos() +
                                 tailItemRect.center() -
                                 QPointF(tailItemRect.width() / 2, 0));
                    this->head = this->mapFromItem(this->headItem, headItemRect.center() +
                                                   QPointF(headItemRect.width() / 2, 0));
                  }
                orientation = LinkOrientation::Horizontal;
              }
            this->tail = QPointF();
            adjustLinkTip();
          }
      }

      //DEBUG
      bool Link::sceneEvent(QEvent *event)
      {
        bool handled = true;

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
                  this->tail = QPointF();
                  this->head = this->tail + QPointF(1.0, 1.0);
                  qDebug() << "Bounding rect: " << classificator->boundingRect();
                  qDebug() << "Tail position changed: " << this->tail;
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
              this->head = me->pos();
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
