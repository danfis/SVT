#include "main_window.hpp"
using namespace SIM::Coin3D::Quarter;

namespace SVT {

namespace Coin3d {

MainWindow::MainWindow()
    : Qt::MainWindow()
{
    _qw = new QuarterWidget();
    _qw->setSceneGraph(_om.root());

    setCentralWidget(_qw);
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
