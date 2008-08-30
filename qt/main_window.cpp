#include "main_window.hpp"


#include "main_window.moc"


namespace Qt {

MainWindow::MainWindow()
{
    _obj_widgets = new WidgetStack;

    _left_dock = new QDockWidget;
    _left_dock->setAllowedAreas(Qt::LeftDockWidgetArea);
    _left_dock->setFeatures(QDockWidget::DockWidgetFloatable
                            | QDockWidget::DockWidgetMovable);
    _left_dock->setWidget(_obj_widgets);
    addDockWidget(Qt::LeftDockWidgetArea, _left_dock, Qt::Vertical);

    _right_dock = 0;

    _status = new QStatusBar;
    setStatusBar(_status);
}

MainWindow::~MainWindow()
{
    delete _obj_widgets;
}

void MainWindow::addObjWidget(ObjWidget *w)
{
    _obj_widgets->push(w);
}

void MainWindow::show()
{
    _obj_widgets->finish();
    QMainWindow::show();
}

void MainWindow::showObjStyleWidget(ObjStyleWidget *w)
{
    if (_right_dock != 0
        && dockWidgetArea(_right_dock) != Qt::NoDockWidgetArea){
        delete _right_dock;
    }

    _right_dock = new QDockWidget;
    _right_dock->setAllowedAreas(Qt::RightDockWidgetArea);
    _right_dock->setFeatures(QDockWidget::DockWidgetFloatable
                             | QDockWidget::DockWidgetMovable
                             | QDockWidget::DockWidgetClosable);
    _right_dock->setWidget(w);
    addDockWidget(Qt::RightDockWidgetArea, _right_dock, Qt::Vertical);
}

void MainWindow::showMsgInStatusBar(QString &msg)
{
    _status->showMessage(msg);
}

}
