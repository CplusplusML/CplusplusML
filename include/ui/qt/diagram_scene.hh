#ifndef		_CPLUSPLUSML_UI_QT_DIAGRAM_U_SCENE_HH_
# define	_CPLUSPLUSML_UI_QT_DIAGRAM_U_SCENE_HH_

#include	<QGraphicsScene>
#include	<QGraphicsItem>

#include	"object/basic.hh"

#include	"ui/qt/classificator_property_window.hh"

namespace			CplusplusML
{
  class				DiagramScene: public QGraphicsScene
  {
    Q_OBJECT

  public:
    
    enum			Mode
      {
        modeInsertItem,
        modeMoveItem
      };

    DiagramScene();

    inline void			setCurrentItem(Object::Type item)
    {
      currentItem_ = item;
    }

    inline Object::Type	getCurrentItem(void) const
    {
      return (currentItem_);
    }

    inline void			setMode(Mode mode)
    {
      currentMode_ = mode;
    }

    inline Mode			getMode(void) const
    {
      return (currentMode_);
    }

  signals:

    void			itemInserted(QGraphicsItem *item);

  private slots:

    void			applyProperties();
    void			myItemSelected();

  protected:

    void			mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void			mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void			mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
    

  private:

    Object::Type		currentItem_;
    Mode			currentMode_;
    ClassificatorPropertyWindow	classificatorProperties_;
  };
}

#endif		// _CPLUSPLUSML_UI_QT_DIAGRAM_U_SCENE_HH_
