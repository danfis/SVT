#ifndef TEST_WIN_HPP
#define TEST_WIN_HPP

#include <QMainWindow>

class MainWindow : public QMainWindow {
    Q_OBJECT

    void *_obj;

  public:
    MainWindow();

  public slots:
    void printBool(void *obj, bool v);
    void clicked(void *obj);
    void val(void *obj, double val);
    void val3(void *obj, double, double, double);
};

#endif
