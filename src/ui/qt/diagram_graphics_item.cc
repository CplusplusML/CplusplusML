#include <QGraphicsScene>
#include <QKeyEvent>

#include "ui/qt/diagram_graphics_item.hh"

#include <QDebug>

namespace CplusplusML
{
  namespace Ui
  {
    namespace Qt
    {
      DiagramGraphicsItem::DiagramGraphicsItem()
      {
      }

      DiagramGraphicsItem::DiagramGraphicsItem(QGraphicsItem* parent) :
        QGraphicsObject(parent)
      {
      }

      DiagramGraphicsItem::~DiagramGraphicsItem()
      {
        emit removed();
      }

      void DiagramGraphicsItem::keyReleaseEvent(QKeyEvent* event)
      {
        qDebug() << "DiagramGraphicsItem::keyReleaseEvent";
        switch (event->key())
          {
          case ::Qt::Key_Delete:
            delete this;
            event->accept();
            break;
          default:
            event->ignore();
            break;
          }
      }
    }
  }
}
