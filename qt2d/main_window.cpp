#include "obj.hpp"
#include "main_window.hpp"


namespace SVT {

namespace Qt2D {

MainWindow::MainWindow()
    : Qt::MainWindow(), _painter(0)
{
    _painter = new Painter();

    setCentralWidget(_painter);
}

MainWindow::~MainWindow()
{
    std::list<Obj *>::iterator it, it_end;

    if (_painter != 0)
        delete _painter;

    it = _objs.begin();
    it_end = _objs.end();
    for (; it != it_end; ++it){
        delete *it;
    }
    
}

void MainWindow::addObj(Obj *o)
{
    addObjWidget(o);
    _painter->addObj(o);

    _objs.push_back(o);
}

Qt::ObjStyleWidget *MainWindow::showObjStyleWidget(Common::Obj *o)
{
    Qt::ObjStyleWidget *osw = Qt::MainWindow::showObjStyleWidget(o);


    connect(osw, SIGNAL(pointSize(Common::Obj *, double)),
            _painter, SLOT(repaint(Common::Obj *)));
    connect(osw, SIGNAL(pointColor(Common::Obj *, double, double, double)),
            _painter, SLOT(repaint(Common::Obj *)));
    connect(osw, SIGNAL(pointOnOff(Common::Obj *, bool)),
            _painter, SLOT(repaint(Common::Obj *)));

    connect(osw, SIGNAL(edgeWidth(Common::Obj *, double)),
            _painter, SLOT(repaint(Common::Obj *)));
    connect(osw, SIGNAL(edgeColor(Common::Obj *, double, double, double)),
            _painter, SLOT(repaint(Common::Obj *)));
    connect(osw, SIGNAL(edgeOnOff(Common::Obj *, bool)),
            _painter, SLOT(repaint(Common::Obj *)));

    connect(osw, SIGNAL(faceColor(Common::Obj *, double, double, double)),
            _painter, SLOT(repaint(Common::Obj *)));
    connect(osw, SIGNAL(faceOnOff(Common::Obj *, bool)),
            _painter, SLOT(repaint(Common::Obj *)));

    return osw;
}


Qt::ObjWidget *MainWindow::addObjWidget(Common::Obj *o, int flags)
{
    Qt::ObjWidget *ow = Qt::MainWindow::addObjWidget(o, flags);

    connect(ow, SIGNAL(onOff(Common::Obj *, bool)),
            _painter, SLOT(repaint(Common::Obj *)));

    return ow;
}

}

}
