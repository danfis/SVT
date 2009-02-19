#include "main_window.hpp"


#include "main_window.moc"

namespace SVT {

namespace Qt {

MainWindow::MainWindow()
{
    _obj_widgets = new WidgetStack;

    _left_dock = new QDockWidget;
    _left_dock->setAllowedAreas(::Qt::LeftDockWidgetArea);
    _left_dock->setFeatures(QDockWidget::DockWidgetFloatable
                            | QDockWidget::DockWidgetMovable);
    _left_dock->setWidget(_obj_widgets);
    addDockWidget(::Qt::LeftDockWidgetArea, _left_dock, ::Qt::Vertical);

    _right_dock = 0;

    _status = new QStatusBar;
    setStatusBar(_status);

    connect(this, SIGNAL(_showMsgInStatusBarSignal(const QString &)),
            _status, SLOT(showMessage(const QString &)));

    resize(800, 600);
}

MainWindow::~MainWindow()
{
    delete _obj_widgets;
}

ObjWidget *MainWindow::addObjWidget(Common::Obj *obj, int flags)
{
    ObjWidget *o = new ObjWidget(obj, flags);
    _obj_widgets->push(o);

    connect(o, SIGNAL(config(Common::Obj *)),
            this, SLOT(showObjStyleWidget(Common::Obj *)));

    return o;
}

void MainWindow::show()
{
    _obj_widgets->finish();
    QMainWindow::show();
}

void MainWindow::showMsgInStatusBarSignal(const QString &msg)
{
    emit _showMsgInStatusBarSignal(msg);
}

ObjStyleWidget *MainWindow::showObjStyleWidget(Common::Obj *obj)
{
    ObjStyleWidget *osw = new ObjStyleWidget(obj);

    if (_right_dock != 0
        && dockWidgetArea(_right_dock) != ::Qt::NoDockWidgetArea){
        delete _right_dock;
    }

    _right_dock = new QDockWidget;
    _right_dock->setAllowedAreas(::Qt::RightDockWidgetArea);
    _right_dock->setFeatures(QDockWidget::DockWidgetFloatable
                             | QDockWidget::DockWidgetMovable
                             | QDockWidget::DockWidgetClosable);
    _right_dock->setWidget(osw);
    addDockWidget(::Qt::RightDockWidgetArea, _right_dock, ::Qt::Vertical);

    return osw;
}

void MainWindow::showMsgInStatusBar(const QString &msg)
{
    _status->showMessage(msg);
}

} /* Qt */

} /* SVT */
