#include <iostream>
#include <Inventor/Qt/SoQt.h>
#include <Inventor/nodes/SoGroup.h>
#include <QApplication>
#include "pthread.h"
using namespace std;

#include "objdata.hpp"
#include "viewer.hpp"
#include "parser.hpp"
#include "msg.hpp"

static void *thStart(void *arg);

int main(int argc, char *argv[])
{
    Viewer *viewer;
    QWidget *mainwin;
    pthread_t th;

    mainwin = SoQt::init(argc, argv, argv[0]);

    if (mainwin == NULL){
        ERR("Can't create main window");
        exit(1);
    }

    viewer = new Viewer(mainwin);

    pthread_create(&th, 0, thStart, (void *)viewer);

    viewer->show();
    SoQt::show(mainwin);
    SoQt::mainLoop();

    pthread_join(th, 0);

    delete mainwin;
    delete viewer;

    return 0;
}

void *thStart(void *arg)
{
    ObjData *data;
    Viewer *viewer = (Viewer *)arg;
    Parser *parser = Parser::instance();

    sleep(1);

    while ((data = parser->parse()) != 0){
        viewer->clear();
        viewer->addObjData(data);
        viewer->rebuildSceneGraph();
        //usleep(500000);
    }

    return 0;
}
