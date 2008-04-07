#include <iostream>
#include <vector>
#include <Inventor/Qt/SoQt.h>
#include <Inventor/SoInput.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoSwitch.h>
using namespace std;

#include "viewer.hpp"
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

int main(int argc, char **argv)
{
    SoSeparator *root, *tmp;
    SoSwitch *sw;
    vector<SoSwitch *> parts;
    QWidget *mainwin;
    GSRM::Viewer *myViewer;
    SoInput inputFile;
    int len;

    if (argc < 2) {
        ERR("Usage: " << argv[0] << " filename [filename [ ... ] ]");
        exit(1);
    }

    mainwin = SoQt::init(argc, argv, argv[0]);
    if (mainwin == NULL){
        ERR("Can't create main window");
        exit(1);
    }

    root = new SoSeparator;
    root->ref();
    for (int i=1; i < argc; i++){
        if (inputFile.openFile(argv[i]) == FALSE) {
            ERR("Could not open file " << argv[i]);
            exit(1);
        }

        sw = new SoSwitch;
        tmp = SoDB::readAll(&inputFile);
        sw->addChild(tmp);
        sw->whichChild = SO_SWITCH_ALL;
        root->addChild(sw);
        parts.push_back(sw);

    }

    myViewer = new GSRM::Viewer(mainwin);
    myViewer->setSceneGraph(root);
    myViewer->setTitle(".inv viewer");

    len = parts.size();
    for (int i=0; i < len; i++){
        myViewer->addToggleButton(callback, parts[i]);
    }
    myViewer->show();

    SoQt::show(mainwin);
    SoQt::mainLoop();

    root->unref();
}
