#include <Inventor/SoEventManager.h>

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
    _viewer->setSceneGraph(_om.root());

    connect(_config, SIGNAL(fitToWin()),
            _viewer, SLOT(viewAll()));
    connect(_config, SIGNAL(bgColorR(double)),
            this, SLOT(setBgColorR(double)));
    connect(_config, SIGNAL(bgColorG(double)),
            this, SLOT(setBgColorG(double)));
    connect(_config, SIGNAL(bgColorB(double)),
            this, SLOT(setBgColorB(double)));

    setCentralWidget(_viewer);

    setBgColor(_bgcolor.redF(), _bgcolor.greenF(), _bgcolor.blueF());
}

MainWindow::~MainWindow()
{
}

void MainWindow::addObj(Obj *o)
{
    _om.add(o);
    addObjWidget(o);
}

void MainWindow::setBgColor(double r, double g, double b)
{
    _bgcolor.setRgbF(r, g, b);
    _viewer->setBackgroundColor(_bgcolor);
    _config->setBgColor(r, g, b);
}

void MainWindow::setBgColorR(double v)
{
    _bgcolor.setRedF(v);
    _viewer->setBackgroundColor(_bgcolor);
}

void MainWindow::setBgColorG(double v)
{
    _bgcolor.setGreenF(v);
    _viewer->setBackgroundColor(_bgcolor);
}

void MainWindow::setBgColorB(double v)
{
    _bgcolor.setBlueF(v);
    _viewer->setBackgroundColor(_bgcolor);
}

}
}
