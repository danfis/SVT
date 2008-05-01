#include <iostream>
#include "config_dialog.hpp"
#include "coin3dtools.hpp"

MainWindow *Coin3dTools::_mainwin = 0;
QWidget *Coin3dTools::_win = 0;
QStatusBar *Coin3dTools::_status_bar = 0;
Viewer *Coin3dTools::_viewer = 0;

void Coin3dTools::init(const char *title)
{
    _win = SoQt::init(title);
    _mainwin = new MainWindow();
    _status_bar = new QStatusBar;
    
    if (_win == 0 || _mainwin == 0 || _status_bar == 0){
        std::cerr << "Can't initialize windows!" << std::endl;
        exit(-1);
    }

    _mainwin->setStatusBar(_status_bar);
    _mainwin->setCentralWidget(_win);
}


void Coin3dTools::mainLoop()
{
    if (_viewer != 0){
        _viewer->show();

        _mainwin->createConfigDialog(_viewer);
    }
    SoQt::show(_mainwin);
    SoQt::mainLoop();
}

void Coin3dTools::finish()
{
    if (_viewer != 0)
        delete _viewer;
    delete _mainwin;
}

Viewer *Coin3dTools::viewer()
{
    if (_viewer == 0){
        _viewer = new Viewer(_win);
    }

    return _viewer;
}
