#ifndef         _ARROW_CONNECTION_H_
# define        _ARROW_CONNECTION_H_

#include "arrow.hh"

namespace Object
{
  class Arrow_;

  class ArrowConnection : public QGraphicsObject
  {
    Q_OBJECT

  public:
    ArrowConnection(QGraphicsItem* parent, int size = 6);

    bool sceneEvent(QEvent* event);
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget);
    virtual QRectF boundingRect() const;

    QPointF center() const;
    void moveCenter(QPointF const& center);

  signals:
    void moved(ArrowConnection*);
    void hovered(ArrowConnection*);

  private:
    QRectF              rect;
  };
}

#endif  // !_ARROW_CONNECTION_H_
