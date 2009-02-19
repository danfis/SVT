#ifndef QT_MAIN_WINDOW_HPP
#define QT_MAIN_WINDOW_HPP

#include <QMainWindow>
#include <QDockWidget>
#include <QStatusBar>
#include <QString>

#include "../common/obj.hpp"

#include "obj_widget.hpp"
#include "obj_style_widget.hpp"
#include "widget_stack.hpp"

namespace SVT {

namespace Qt {

class MainWindow : public QMainWindow {
    Q_OBJECT

    WidgetStack *_obj_widgets;
    QDockWidget *_left_dock, *_right_dock;
    QStatusBar *_status;

  public:
    MainWindow();
    virtual ~MainWindow();

    virtual ObjWidget *addObjWidget(Common::Obj *, int flags = OBJ_WIDGET_ALL);

    void show();

    void showMsgInStatusBarSignal(const QString &msg);

  signals:
    void _showMsgInStatusBarSignal(const QString &msg);
  public slots:
    virtual ObjStyleWidget *showObjStyleWidget(Common::Obj *);
    void showMsgInStatusBar(const QString &msg);
};

} /* Qt */

} /* SVT */

#endif
