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

  protected:
    WidgetStack *_obj_widgets;
    QDockWidget *_left_dock, *_right_dock;
    QStatusBar *_status;

  public:
    MainWindow();
    virtual ~MainWindow();

    virtual void addObjWidget(Common::Obj *, int flags = OBJ_WIDGET_ALL);

    virtual void show();

    virtual void showMsgInStatusBarSignal(const QString &msg);

  signals:
    virtual void _showMsgInStatusBarSignal(const QString &msg);
  public slots:
    virtual void showObjStyleWidget(Common::Obj *);
    virtual void showMsgInStatusBar(const QString &msg);
};

} /* Qt */

} /* SVT */

#endif
