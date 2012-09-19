#ifndef _ARROW_H_
#define _ARROW_H_

#include "basic.hh"
#include "complex.hh"
#include "arrow_connection.hh"

namespace Object
{
  class GrabHandle : public QGraphicsRectItem
  {
  public:
    GrabHandle(QGraphicsItem* parent);

    void moveCenter(QPointF const& center);
  };

  class ArrowConnection;

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
    ArrowConnection* searchConnection(QPointF const& point);

    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget);
    QPainterPath shape() const;
    QRectF boundingRect() const;

    bool sceneEvent(QEvent* event);
    bool sceneEventFilter(QGraphicsItem *watched,
                          QEvent *event);

  private:
    QPen        pen;
    QPen        outlinePen;
    QPointF     tail;
    QPointF     head;

    GrabHandle*  handles[2];
    GrabHandle*  pressedHandle;

    QList<ArrowConnection*> connections;
    QMap<ArrowConnection*, QPointF*> pointLookup;
    QMap<ArrowConnection*, QPointF*> pointReverseLookup;

  public slots:
    void connectionMoved(ArrowConnection* connection);
  };
}

#endif /* _ARROW_H_ */
