#include <Inventor/SoEventManager.h>

#include "common/msg.hpp"
#include "main_window.hpp"
using namespace SIM::Coin3D::Quarter;

#include "main_window.moc"


namespace SVT {

namespace Coin3d {

MainWindow::MainWindow()
    : Qt::MainWindow()
{
    _config = new Qt::ConfigWidget();
    _obj_widgets->push(_config);

    _viewer = new Viewer();

    connect(_config, SIGNAL(fitToWin()),
            _viewer, SLOT(viewAll()));
    connect(_config, SIGNAL(bgColorR(double)),
            _viewer, SLOT(setBgColorR(double)));
    connect(_config, SIGNAL(bgColorG(double)),
            _viewer, SLOT(setBgColorG(double)));
    connect(_config, SIGNAL(bgColorB(double)),
            _viewer, SLOT(setBgColorB(double)));

    setCentralWidget(_viewer);
}

MainWindow::~MainWindow()
{
}

void MainWindow::addObj(Obj *o)
{
    _viewer->addObj(o);
    addObjWidget(o);
}

void MainWindow::addObjDyn(Obj *o)
{
    _viewer->addObjDyn(o);
}

void MainWindow::clearObjsDyn()
{
    _viewer->clearObjsDyn();
}

void MainWindow::show()
{
    Qt::MainWindow::show();

    _viewer->viewAll();
    _viewer->updateLight();
}

void MainWindow::applySettings(const Common::Settings &s)
{
    _viewer->setBgColor(s.bg_color[0], s.bg_color[1], s.bg_color[2]);
    _config->setBgColor(s.bg_color[0], s.bg_color[1], s.bg_color[2]);
}

}

}
