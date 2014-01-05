#include <QActionGroup>
#include <QAction>

#include "ui/main_window.h"
#include "ui/diagram_item.h"

namespace     cplusplusml {
  namespace   ui {

    /*
      Constructor of MainWindow, initialize the User Interface.
    */
    MainWindow::MainWindow() {

      setupUi(this);
      diagram_scene_ = new DiagramScene(this);

      /*
        Create the action group holding all toolbar's actions.
      */
      QActionGroup *action_group = new QActionGroup(toolbar);
      action_group->setExclusive(true);
      connect(
        action_group,
        SIGNAL(triggered(QAction *)),
        this,
        SLOT(ToolbarActionTriggered(QAction *))
      );

      action_group->addAction(action_cursor);
      action_group->addAction(action_class);
      action_group->addAction(action_struct);
      action_group->addAction(action_union);
      action_group->addAction(action_enum);
      action_group->addAction(action_namespace);
      action_group->addAction(action_inheritance);
      action_group->addAction(action_composition);
      action_group->addAction(action_aggregation);
      action_group->addAction(action_dependency);

      action_cursor->setChecked(true);

      toolbar->addActions(action_group->actions());
      toolbar->insertSeparator(action_namespace);
      toolbar->insertSeparator(action_inheritance);
    }

    /*
      Destructor of MainWindow, do nothing
    */
    MainWindow::~MainWindow() {

    }

    /*
      When the button exit from the file menu is triggered,
      close the main window.
    */
    void      MainWindow::on_action_exit_triggered() {
      close();
    }

    /*
      When the close event is triggered, ask for the user to save
      unsaved documents.
      Arguments:
      QCloseEvent event: closing event
    */
    void    MainWindow::closeEvent(QCloseEvent *event) {
      event->accept();
    }

    /*
      Set the scene mode from triggered action.
      Argument:
      QAction* action: action triggered
    */
    void    MainWindow::ToolbarActionTriggered(QAction* action) {
      static const std::map<QAction*, DiagramItem::Type> item_action_map = {
        {action_class, DiagramItem::item_class},
        {action_struct, DiagramItem::item_struct},
        {action_enum, DiagramItem::item_enum},
        {action_union, DiagramItem::item_union},
        {action_namespace, DiagramItem::item_namespace},
        {action_typedef, DiagramItem::item_typedef},
        {action_aggregation, DiagramItem::item_aggregation},
        {action_dependency, DiagramItem::item_dependency},
        {action_composition, DiagramItem::item_composition},
        {action_inheritance, DiagramItem::item_inheritance},
        {action_free_function, DiagramItem::item_free_function},
        {action_template, DiagramItem::item_template},
        {action_library, DiagramItem::item_library}
      };

      if (action == action_cursor) {
        diagram_scene_->SetMode(DiagramScene::mode_select);
        diagram_scene_->SetItem(DiagramItem::item_cursor);
      }
      else {
        diagram_scene_->SetMode(DiagramScene::mode_insert_item);
        diagram_scene_->SetItem(item_action_map.find(action)->second);
      }
    }

  }
}
