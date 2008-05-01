#include "main_window.hpp"

#include "main_window.moc"

MainWindow::MainWindow(QWidget *parent, Qt::WindowFlags flags)
    : QMainWindow(parent, flags),
      _config_dialog(0), _right_dock(0)
{
    setDockOptions(QMainWindow::AnimatedDocks |
                   QMainWindow::AllowNestedDocks |
                   QMainWindow::AllowTabbedDocks);


    resize(800, 600);
}

MainWindow::~MainWindow()
{
    if (_config_dialog != 0)
        delete _config_dialog;
}

void MainWindow::createConfigDialog(Viewer *viewer)
{
    if (_config_dialog != 0)
        delete _config_dialog;

    _config_dialog = new ConfigDialog(viewer);

    QDockWidget *config_dock = new QDockWidget("Config");
    config_dock->setAllowedAreas(Qt::LeftDockWidgetArea);
    config_dock->setFeatures(QDockWidget::DockWidgetMovable |
                             QDockWidget::DockWidgetFloatable);
    config_dock->setWidget(_config_dialog);

    addDockWidget(Qt::LeftDockWidgetArea, config_dock);

    connect(_config_dialog, SIGNAL(showWidget(QWidget *)),
            this, SLOT(showInRightDock(QWidget *)));
}

void MainWindow::showInRightDock(QWidget *widg, const char *title)
{
    if (_right_dock != 0){
        removeDockWidget(_right_dock);
        delete _right_dock;
        _right_dock = 0;
    }

    _right_dock = new QDockWidget(title);
    _right_dock->setAllowedAreas(Qt::RightDockWidgetArea);
    _right_dock->setFeatures(QDockWidget::DockWidgetClosable |
                             QDockWidget::DockWidgetMovable |
                             QDockWidget::DockWidgetFloatable);
    _right_dock->setWidget(widg);

    addDockWidget(Qt::RightDockWidgetArea, _right_dock);
}
