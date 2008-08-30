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
    connect(obj, SIGNAL(onOff(void *, bool)),
            this, SLOT(printBool(void *, bool)));
    connect(obj, SIGNAL(config(void *)),
            this, SLOT(clicked(void *)));
    connect(obj, SIGNAL(config(void *)),
            this, SLOT(showObjStyleWidget(void *)));
    addObjWidget(obj);

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
    connect(obj, SIGNAL(onOff(void *, bool)),
            this, SLOT(printBool(void *, bool)));
    connect(obj, SIGNAL(config(void *)),
            this, SLOT(clicked(void *)));
    addObjWidget(obj);

    stack->finish();
    layout->addWidget(stack);

    w->setLayout(layout);
    setCentralWidget(w);
}

void MainWindow::printBool(void *obj, bool v)
{
    QString msg = QString("%1 : %2 - %3")
                    .arg((long)_obj)
                    .arg((long)obj)
                    .arg(v);

    showMsgInStatusBar(msg);
}

void MainWindow::clicked(void *obj)
{
    QString msg = QString("%1 : %2 clicked")
                    .arg((long)_obj)
                    .arg((long)obj);

    showMsgInStatusBar(msg);
}

void MainWindow::showObjStyleWidget(void *o)
{
    Qt::ObjStyleWidget *obj = new Qt::ObjStyleWidget(o);
    obj->setPointSize(2.5);
    obj->setEdgeOnOff(false);

    Qt::MainWindow::showObjStyleWidget(obj);
}

void MainWindow::val(void *obj, double val)
{
    QString msg = QString("%1 :%2 %3")
                    .arg((long)_obj)
                    .arg((long)obj)
                    .arg(val);

    showMsgInStatusBar(msg);
}

void MainWindow::val3(void *obj, double a, double b, double c)
{
    QString msg = QString("%1 :%2 %3 %4 %5")
                    .arg((long)_obj)
                    .arg((long)obj)
                    .arg(a)
                    .arg(b)
                    .arg(c);

    showMsgInStatusBar(msg);
}
