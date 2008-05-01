#include <iostream>
#include <Inventor/Qt/SoQt.h>
#include <Inventor/nodes/SoGroup.h>
#include <QApplication>
using namespace std;

#include "objdata.hpp"
#include "viewer.hpp"
#include "parser.hpp"
#include "msg.hpp"

void callback(bool pressed, Viewer *viewer, void *cl)
{
    SoSwitch *sw = (SoSwitch *)cl;

    SoDB::writelock();
    viewer->lock();
    if (pressed){
        sw->whichChild = SO_SWITCH_NONE;
    }else{
        sw->whichChild = SO_SWITCH_ALL;
    }
    viewer->unlock();
    SoDB::writeunlock();
}

// Callback that reports whenever the viewer's position changes.
/*
static void cameraChangedCB(void *data, SoSensor *)
{
   SoCamera *viewerCamera = (SoCamera *)data;

   SoDB::writelock();
   SbVec3f cameraPosition = viewerCamera->position.getValue();
   light->location.setValue(cameraPosition * -100);
   SoDB::writeunlock();
}
*/


int main(int argc, char *argv[])
{
    Parser *parser;
    ObjData *data;
    Viewer *viewer;
    QWidget *mainwin;

    mainwin = SoQt::init(argc, argv, argv[0]);

    if (mainwin == NULL){
        ERR("Can't create main window");
        exit(1);
    }

    parser = Parser::instance();
    viewer = new Viewer(mainwin);
    while ((data = parser->parse()) != 0)
        viewer->addObjData(data);

    viewer->show();
    SoQt::show(mainwin);
    SoQt::mainLoop();

    delete mainwin;
    delete viewer;

    return 0;
}
