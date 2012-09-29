#ifndef         _CPLUSPLUSML_UI_QT_MAIN_U_W_H_
# define        _CPLUSPLUSML_UI_QT_MAIN_U_W_H_

# include       <QMainWindow>

# include       "ui_MainWindow.h"
# include       "ui_AboutWindow.h"

# include       "ui/qt/diagram_scene.hh"
# include       "object/basic.hh"

namespace               CplusplusML
{
  namespace             Ui
  {
    namespace           Qt
    {
      class             Main_W : public QMainWindow, ::Ui::MainWindow
      {
        Q_OBJECT

      public:
        Main_W();
        ~Main_W();

      public slots:
        void            About();
        void            WebSite();
        void            Help();
        void            ManageToolbarActions(QAction *action);
        void            SetDefaultAction();

      private:
        QDialog         aboutWindow_;
        QDialog         helpWindow_;
        QDockWidget     *toolbar_;
        DiagramScene    scene_;
      };
    }
  }
}

#endif          // _CPLUSPLUSML_UI_QT_MAIN_U_W_H_
