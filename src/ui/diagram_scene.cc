#include	<iostream>
#include	<QtGui>

#include	"ui/diagram_scene.hh"

namespace			CplusplusML
{
  void				DiagramScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
  {
    if (mouseEvent->button() != Qt::LeftButton)
      return;

    QGraphicsScene::mousePressEvent(mouseEvent);
  }

  void				DiagramScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
  {
    if (currentMode_ == modeMoveItem)
      QGraphicsScene::mouseMoveEvent(mouseEvent);
  }
}
