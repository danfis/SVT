#include <QApplication>
#include <QMainWindow>
#include <iostream>
using namespace std;

#include "obj_widget.hpp"
#include "obj_style_widget.hpp"
#include "test_win.hpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow win;

    win.show();
    app.exec();
}
