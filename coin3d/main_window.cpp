#include <Inventor/SoEventManager.h>

#include "main_window.hpp"
using namespace SIM::Coin3D::Quarter;

namespace SVT {

namespace Coin3d {

MainWindow::MainWindow()
    : Qt::MainWindow()
{
    _config = new ConfigWidget();
    _obj_widgets->push(_config);

    _viewer = new Viewer();
    _viewer->setSceneGraph(_om.root());

    connect(_config, SIGNAL(fitToWin()),
            _viewer, SLOT(viewAll()));

    setCentralWidget(_viewer);
}

MainWindow::~MainWindow()
{
}

void MainWindow::addObj(Obj *o)
{
    _om.add(o);
    addObjWidget(o);
}

}
}
