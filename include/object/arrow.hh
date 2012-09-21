#ifndef _ARROW_H_
#define _ARROW_H_

#include "basic.hh"
#include "complex.hh"
#include "arrow_connection.hh"

namespace Object
{
  class ArrowConnection;

  class GrabHandle : public QObject, public QGraphicsRectItem
  {
    Q_OBJECT

  public:
    GrabHandle(QGraphicsItem* parent, QPointF* boundPoint);

    bool sceneEvent(QEvent *event);
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget);

    void moveCenter(QPointF const& center);
    ArrowConnection* searchConnection(QPointF const& point);

  signals:
    void moved(QPointF const& newPos, QPointF* boundPoint);

  public slots:
    void connectionMoved(ArrowConnection* connection);

  private:
    QPointF* boundPoint;
    ArrowConnection* currentConnection;
  };

  class Arrow_ : public QGraphicsObject
  {
    Q_OBJECT

  public:
    Arrow_();

    virtual ~Arrow_() { }

    void Render(void);

    void adjustHandles();
    void disableHandles();
    void enableHandles();

    void adjustConnections();
    void adjustArrowTip();

    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget);
    QPainterPath shape() const;
    QRectF boundingRect() const;

    //DEBUG
    bool sceneEvent(QEvent *event);
    bool eventFilter(QObject* obj, QEvent *event);
    //    bool sceneEventFilter(QObject *obj, QEvent *ev);

  public slots:
    void        onGrabHandleMove(QPointF const& newPos, QPointF* boundPoint);

  private:
    QPen        pen;
    QPen        outlinePen;
    QPointF     tail;
    QPointF     head;
    QPolygonF   arrowHead;

    GrabHandle*  handles[2];

    QList<ArrowConnection*> connections;
  };
}

#endif /* _ARROW_H_ */
