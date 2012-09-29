#ifndef         _CPLUSPLUSML_UI_QT_DIAGRAM_U_SCENE_HH_
# define        _CPLUSPLUSML_UI_QT_DIAGRAM_U_SCENE_HH_

# include       <QGraphicsScene>
# include       <QGraphicsItem>

# include       "object/basic.hh"

# include       "ui/qt/classificator_property_window.hh"

namespace               CplusplusML
{
  namespace             Ui
  {
    namespace           Qt
    {
      namespace         Object = ::CplusplusML::Object;

      class             DiagramScene: public QGraphicsScene
      {
        Q_OBJECT

      public:
    
        enum            Mode
          {
            modeInsertItem,
            modeMoveItem
          };

        DiagramScene();

        inline void     SetCurrentItem(Object::Type item)
        {
          currentItem_ = item;
        }

        inline Object::Type     GetCurrentItem(void) const
        {
          return (currentItem_);
        }

        inline void			SetMode(Mode mode)
        {
          currentMode_ = mode;
        }

        inline Mode			GetMode(void) const
        {
          return (currentMode_);
        }

      signals:

        void			ItemInserted(QGraphicsItem *item);

      private slots:

        void			ApplyProperties_();
        void			MyItemSelected_();

        // Redefine Qt slot, no coding norm here
      protected:

        void			mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
        void			mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent);
        void			mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
    

      private:

        Object::Type                    currentItem_;
        Mode                            currentMode_;
        ClassificatorPropertyWindow     classificatorProperties_;
      };
    }
  }
}

#endif		// _CPLUSPLUSML_UI_QT_DIAGRAM_U_SCENE_HH_
