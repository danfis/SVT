#include "obj.hpp"
#include "config.hpp"
#include "main_window.hpp"


namespace SVT {

namespace Qt2D {

MainWindow::MainWindow()
    : Qt::MainWindow(), _painter(0)
{
    _config = new ConfigWidget();
    _obj_widgets->push(_config);
    _config->setScale(1.);

    _painter = new Painter();

    connect(_config, SIGNAL(scaleChanged(double)),
            _painter, SLOT(setScale(double)));
    connect(_painter, SIGNAL(scaleChanged(double)),
            _config, SLOT(setScale(double)));
    connect(_config, SIGNAL(fitToWin()),
            _painter, SLOT(fitToWin()));

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


}

}
