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
#include "coin3dtools.hpp"

static void *thStart(void *arg);

int main(int argc, char *argv[])
{
    Viewer *viewer;
    pthread_t th;

    Coin3dTools::init("viewer");

    viewer = Coin3dTools::viewer();
    viewer->setDefaultFacesDiffuseColor(0.2, 0.8, 0.2);
    viewer->setDefaultPointsSwitch(false);
    viewer->setDefaultEdgesSwitch(false);

    pthread_create(&th, 0, thStart, (void *)viewer);

    Coin3dTools::mainLoop();

    //pthread_join(th, 0);
    pthread_kill(th, SIGINT);

    cout << endl;

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
