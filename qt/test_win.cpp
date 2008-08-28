#include <iostream>
using namespace std;

#include "test_win.hpp"
#include "obj_widget.hpp"
#include "obj_style_widget.hpp"
#include "widget_stack.hpp"

#include "test_win.moc"

MainWindow::MainWindow()
    : _obj((void *)1000)
{
    Qt::ObjWidget *obj;
    Qt::ObjStyleWidget *objs;
    QWidget *w = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout;
    Qt::WidgetStack *stack = new Qt::WidgetStack;

    obj = new Qt::ObjWidget(_obj);
    stack->push(obj);
    connect(obj, SIGNAL(onOff(void *, bool)),
            this, SLOT(printBool(void *, bool)));
    connect(obj, SIGNAL(config(void *)),
            this, SLOT(clicked(void *)));

    objs = new Qt::ObjStyleWidget(_obj);
    stack->push(objs);
    objs->setPointColor(0.1, 0.1, 0.1);
    connect(objs, SIGNAL(pointOnOff(void *, bool)),
            this, SLOT(printBool(void *, bool)));
    connect(objs, SIGNAL(pointSize(void *, double)),
            this, SLOT(val(void *, double)));
    connect(objs, SIGNAL(edgeOnOff(void *, bool)),
            this, SLOT(printBool(void *, bool)));
    connect(objs, SIGNAL(edgeColorRed(void *, double)),
            this, SLOT(val(void *, double)));
    connect(objs, SIGNAL(faceOnOff(void *, bool)),
            this, SLOT(printBool(void *, bool)));
    connect(objs, SIGNAL(faceColor(void *, double, double, double)),
            this, SLOT(val3(void *, double, double, double)));

    obj = new Qt::ObjWidget(_obj,
                    Qt::OBJ_WIDGET_NAME | Qt::OBJ_WIDGET_CONFIG);
    obj->setName("Default style");
    stack->push(obj);
    connect(obj, SIGNAL(onOff(void *, bool)),
            this, SLOT(printBool(void *, bool)));
    connect(obj, SIGNAL(config(void *)),
            this, SLOT(clicked(void *)));

    stack->finish();
    layout->addWidget(stack);

    w->setLayout(layout);
    setCentralWidget(w);
}

void MainWindow::printBool(void *obj, bool v)
{
    cout << (long)_obj << ": " << (long)obj << " - " << v << endl;
}

void MainWindow::clicked(void *obj)
{
    cout << (long)_obj << ": " << (long)obj << " clicked" << endl;
}

void MainWindow::val(void *obj, double val)
{
    cout << (long)_obj << ": " << (long)obj << " " << val << endl;
}

void MainWindow::val3(void *obj, double a, double b, double c)
{
    cout << (long)_obj << ": " << (long)obj << " " << a << " " << b << " "
         << c << endl;
}
