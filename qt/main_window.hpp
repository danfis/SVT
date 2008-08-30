#ifndef QT_MAIN_WINDOW_HPP
#define QT_MAIN_WINDOW_HPP

#include <QMainWindow>
#include <QDockWidget>
#include <QStatusBar>
#include <QString>

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

    void addObjWidget(ObjWidget *);

    void show();

  public slots:
    void showObjStyleWidget(ObjStyleWidget *);
    void showMsgInStatusBar(QString &msg);
};

} /* Qt */

} /* SVT */

#endif
