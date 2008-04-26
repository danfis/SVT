#include <iostream>
#include <Inventor/Qt/SoQt.h>
#include <Inventor/nodes/SoGroup.h>
#include <QApplication>
#include "pthread.h"
#include "signal.h"
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
    viewer->setDefaultFacesDiffuseColor(0.2, 0.8, 0.2);
    viewer->setDefaultPointsSwitch(false);
    viewer->setDefaultEdgesSwitch(false);

    pthread_create(&th, 0, thStart, (void *)viewer);

    viewer->show();
    SoQt::show(mainwin);
    SoQt::mainLoop();

    //pthread_join(th, 0);
    pthread_kill(th, SIGINT);

    cout << endl;

    delete mainwin;
    delete viewer;

    return 0;
}

void *thStart(void *arg)
{
    long frame = 1;
    ObjData *data;
    Viewer *viewer = (Viewer *)arg;
    Parser *parser = Parser::instance();

    while ((data = parser->parse()) != 0){
        cout << " Frame " << frame << ", "
             << data->numPoints() << " points, "
             << data->numEdges() << " edges, "
             << data->numFaces() << " faces" << "\r";
        cout.flush();

        viewer->clear();
        viewer->addDynObjData(data);
        viewer->rebuildSceneGraph();
        //usleep(50000);

        frame++;
    }

    return 0;
}
