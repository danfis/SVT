#ifndef _MAIN_WINDOW_HPP_
#define _MAIN_WINDOW_HPP_

#include <QMainWindow>
#include <QDockWidget>
#include "config_dialog.hpp"
#include "viewer.hpp"

class MainWindow : public QMainWindow {
    Q_OBJECT

    ConfigDialog *_config_dialog;
    QDockWidget *_right_dock;

  public:
    MainWindow(QWidget *parent = 0, Qt::WindowFlags flags = 0);
    ~MainWindow();

    void createConfigDialog(Viewer *viewer);

  public slots:
    void showInRightDock(QWidget *widg, const char *title = "");
};

#endif
