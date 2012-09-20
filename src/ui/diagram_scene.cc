#include	<iostream>
#include	<list>
#include	<QtGui>
#include  <QPoint>
#include  <QPointF>

#include	"ui/diagram_scene.hh"

#include	"object/class.hh"
#include	"object/struct.hh"
#include	"object/union.hh"
#include	"object/dependency.hh"

#include	"assed.hpp"


namespace			CplusplusML
{

  DiagramScene::DiagramScene():
    currentScale_(1),
    currentItem_(Object::objectClass),
    currentMode_(modeMoveItem)
  {
    connect(&complexProperties_, SIGNAL(applied()), this, SLOT(applyProperties()));
    connect(this, SIGNAL(selectionChanged()), this, SLOT(myItemSelected()));
  }

  void DiagramScene::SetCenter(const QPointF& centerPoint)
  {
    static int i = 0;
    QGraphicsView* view = views().first();
    QRectF visibleArea = view->mapToScene(view->rect()).boundingRect();
    QRectF sceneBounds = view->sceneRect();
    double boundX = visibleArea.width() / 2.0;
    double boundY = visibleArea.height() / 2.0;
    double boundWidth = sceneBounds.width() - 2.0 * boundX;
    double boundHeight = sceneBounds.height() - 2.0 * boundY;
    QRectF bounds(boundX, boundY, boundWidth, boundHeight);

    if (bounds.contains(centerPoint))
      CurrentCenterPoint = centerPoint;
    else
      if(visibleArea.contains(sceneBounds))
        CurrentCenterPoint = sceneBounds.center();
      else
        CurrentCenterPoint = centerPoint;

    if(centerPoint.x() > bounds.x() + bounds.width())
      CurrentCenterPoint.setX(bounds.x() + bounds.width());
    else if(centerPoint.x() < bounds.x())
      CurrentCenterPoint.setX(bounds.x());

    if(centerPoint.y() > bounds.y() + bounds.height())
      CurrentCenterPoint.setY(bounds.y() + bounds.height());
    else if(centerPoint.y() < bounds.y())
      CurrentCenterPoint.setY(bounds.y());

    ++i;

    printf("LOL %.3f - %.3f\ni = %d\n", CurrentCenterPoint.x(), CurrentCenterPoint.y(), i);
    view->centerOn(CurrentCenterPoint);
    i = 0;
    printf("MEUH %.f - %.f\n", CurrentCenterPoint.x(), CurrentCenterPoint.y());
  }


  void				DiagramScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent)
  {
    Object::Complex_		*complex;

    if (mouseEvent->button() != Qt::LeftButton)
      return;

    if (!selectedItems().empty())
      {
        if ((complex = qgraphicsitem_cast<Object::Complex_ *>(selectedItems().first())))
          complexProperties_.show(complex);
      }

    QGraphicsScene::mouseDoubleClickEvent(mouseEvent);
  }

  void				DiagramScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
  {
    if (mouseEvent->modifiers() == Qt::ControlModifier)
      {
        QGraphicsView* view = views().first();

        LastPanPoint = mouseEvent->scenePos().toPoint();
        view->setCursor(Qt::ArrowCursor);
      }
  }


  void				DiagramScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
  {
    Object::Basic_		*item = NULL;

    if (mouseEvent->button() != Qt::LeftButton)
      return;

    if (mouseEvent->modifiers() == Qt::ControlModifier)
      {
        QGraphicsView*      view = views().first();

        LastPanPoint = mouseEvent->scenePos().toPoint();
        view->setCursor(Qt::OpenHandCursor);
        return ;
      }

    if (currentMode_ == modeInsertItem)
      {
        switch (currentItem_)
          {
          case (Object::objectClass):
            item = new Object::Class();
            break;
          case (Object::objectStruct):
            item = new Object::Struct();
            break;
          case (Object::objectUnion):
            item = new Object::Union();
            break;
            // case (Object::objectDependency):
            //   item = new Object::Dependency();
            //   break;
          default:
            break;
          };
        if (item != NULL)
          {
            item->setFlag(Object::Basic_::ItemIsSelectable, true);
            item->setSelected(true);
            item->setPos(mouseEvent->scenePos());
            addItem(item);
            complexProperties_.show();
          }
      }
    QGraphicsScene::mousePressEvent(mouseEvent);
  }

  void				DiagramScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
  {
    if (mouseEvent->modifiers() == Qt::ControlModifier)
      {
        QGraphicsView*      view = views().first();
        QPointF             delta;

        if (!LastPanPoint.isNull())
          {
            view->setCursor(Qt::ClosedHandCursor);
            delta = view->mapToScene(LastPanPoint) - view->mapToScene(mouseEvent->scenePos().toPoint());
            LastPanPoint = mouseEvent->scenePos().toPoint();

            printf("mouseMoveEvent\n");
            SetCenter(GetCenter() + delta);
          }
      }
    else if (currentMode_ == modeMoveItem)
      QGraphicsScene::mouseMoveEvent(mouseEvent);
  }

  void				DiagramScene::applyProperties()
  {
    Object::Complex_		*complex;

    if (!selectedItems().empty())
      {
        if ((complex = qgraphicsitem_cast<Object::Complex_ *>(selectedItems().first())))
          complex->updateFromForm(complexProperties_);
      }
  }

  void				DiagramScene::myItemSelected()
  {
  }

}
