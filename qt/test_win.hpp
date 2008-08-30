#ifndef TEST_WIN_HPP
#define TEST_WIN_HPP

#include "main_window.hpp"

class MainWindow : public Qt::MainWindow {
    Q_OBJECT

    void *_obj;

  public:
    MainWindow();

  public slots:
    void printBool(void *obj, bool v);
    void clicked(void *obj);
    void showObjStyleWidget(void *obj);
    void val(void *obj, double val);
    void val3(void *obj, double, double, double);
};

#endif
