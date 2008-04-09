#include <iostream>
#include <Inventor/Qt/SoQt.h>
#include <Inventor/nodes/SoGroup.h>
using namespace std;

#include "objdata.hpp"
#include "viewer.hpp"
#include "parser.hpp"
#include "msg.hpp"

void callback(bool pressed, GSRM::Viewer *viewer, void *cl)
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
    SoNode *root;
    QWidget *mainwin;
    GSRM::Viewer *viewer;

    SoDB::init();

    parser = Parser::instance();
    data = parser->parse();

    mainwin = SoQt::init(argc, argv, argv[0]);
    if (mainwin == NULL){
        ERR("Can't create main window");
        exit(1);
    }

    root = data->root();

    viewer = new GSRM::Viewer(mainwin);
    viewer->setSceneGraph(root);

    data->addButtons(*viewer);
    /*
    sw = new SoSwitch;
    sw->whichChild = SO_SWITCH_ALL;
    //viewer->addToggleButton(callback, sw);
    root->addChild(sw);
    setCoords(sw);

    sw = new SoSwitch;
    sw->whichChild = SO_SWITCH_ALL;
    viewer->addToggleButton(callback, sw);
    root->addChild(sw);
    setVertices(sw);

    sw = new SoSwitch;
    sw->whichChild = SO_SWITCH_ALL;
    viewer->addToggleButton(callback, sw);
    root->addChild(sw);
    setEdges(sw);

    sw = new SoSwitch;
    sw->whichChild = SO_SWITCH_ALL;
    viewer->addToggleButton(callback, sw);
    root->addChild(sw);
    setFaces(sw, viewer);
    */

    viewer->show();


    // Pop up the main window.
    SoQt::show(mainwin);
    SoQt::mainLoop();

    delete data;

    return 0;
}
