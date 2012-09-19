#ifndef		_CPLUSPLUSML_UI_DIAGRAM_SCENE_HH_
# define	_CPLUSPLUSML_UI_DIAGRAM_SCENE_HH_

#include	<QGraphicsScene>
#include	<QGraphicsItem>
#include  <QtGlobal>
#include	"object/basic.hh"

#include	"ui/complex_property_window.hh"

namespace			CplusplusML
{
  class				DiagramScene: public QGraphicsScene
  {
    Q_OBJECT

  public:

    constexpr static qreal maximumScale = 10;

    enum			Mode
      {
        modeInsertItem,
        modeMoveItem
      };

    DiagramScene();

    inline void			setCurrentItem(Object::ObjectType item)
    {
      currentItem_ = item;
    }

    inline Object::ObjectType	getCurrentItem(void) const
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

    inline qreal			getScale(void) const
    {
      return (currentScale_);
    }

    inline void			scaleBy(qreal factor)
    {
      currentScale_ = factor * currentScale_;
      if (currentScale_ >= maximumScale)
        currentScale_ = maximumScale;
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

    qreal       currentScale_;
    Object::ObjectType		currentItem_;
    Mode			currentMode_;
    ComplexPropertyWindow	complexProperties_;
  };
}

#endif		// _CPLUSPLUSML_UI_DIAGRAM_SCENE_HH_
