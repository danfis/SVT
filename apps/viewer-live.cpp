#include <iostream>
#include <getopt.h>
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

#define VIEWER_LIVE

#include "viewer_common.cpp"

static void *thStart(void *arg);
static void thParse(Viewer *viewer, long *frame);

int main(int argc, char *argv[])
{
    Viewer *viewer;
    pthread_t th;

    Coin3dTools::init("viewer");

    viewer = Coin3dTools::viewer();

#include "viewer_common_main.cpp"

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
    Viewer *viewer = (Viewer *)arg;
    Parser *parser = Parser::instance();

    if (args != 0){
        for (int i=0; i < num_args; i++){
            cerr << "Parsing file " << args[i] << " ..." << endl;
            if (!parser->setInput(args[i])){
                ERR("Can't read file " << args[i]);
                continue;
            }

            thParse(viewer, &frame);
        }
    }else{
        thParse(viewer, &frame);
    }

    return 0;
}

void thParse(Viewer *viewer, long *frame)
{
    ObjData *data;
    Parser *parser = Parser::instance();

    while ((data = parser->parse()) != 0){
        cout << " Frame " << *frame << ", "
            << data->numPoints() << " points, "
            << data->numEdges() << " edges, "
            << data->numFaces() << " faces" << "\r";
        cout.flush();

        viewer->clear();
        viewer->addDynObjData(data);
        viewer->rebuildSceneGraph();
        //usleep(50000);

        (*frame)++;
    }
}
