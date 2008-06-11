#include <iostream>
#include <cstdlib>
#include <getopt.h>
#include <Inventor/Qt/SoQt.h>
#include <Inventor/nodes/SoGroup.h>
#include <QApplication>
#include <QStatusBar>
#include <QMainWindow>
using namespace std;

#include "objdata.hpp"
#include "viewer.hpp"
#include "parser.hpp"
#include "msg.hpp"
#include "coin3dtools.hpp"

#define VIEWER

#include "viewer_common.cpp"

void chooseRandomColor(float *r, float *g, float *b);
void parseObjData();

int main(int argc, char *argv[])
{
    Parser *parser;
    Viewer *viewer;

    Coin3dTools::init("viewer");
    viewer = Coin3dTools::viewer();

#include "viewer_common_main.cpp"

    parser = Parser::instance();

    if (args != 0){
        for (int i=0; i < num_args; i++){
            cerr << "Parsing file " << args[i] << " ..." << endl;
            if (!parser->setInput(args[i])){
                ERR("Can't read file " << args[i]);
                continue;
            }

            parseObjData();
        }
    }else{
        parseObjData();
    }

    Coin3dTools::mainLoop();

    return 0;
}


void chooseRandomColor(float *r, float *g, float *b)
{
    do {
        *r = drand48();
        *g = drand48();
        *b = drand48();
    } while (*r * *g * *b < 0.01f); // eliminate black dark colors
}

void parseObjData()
{
    Parser *parser;
    ObjData *data;
    Viewer *viewer;
    float r, g, b;

    parser = Parser::instance();
    viewer = Coin3dTools::viewer();

    while ((data = parser->parse()) != 0){
        viewer->addObjData(data);

        // colour elemets if requested
        if (colour_points){
            chooseRandomColor(&r, &g, &b);
            data->material_points->diffuseColor.setValue(r, g, b);
        }
        if (colour_edges){
            chooseRandomColor(&r, &g, &b);
            data->material_edges->diffuseColor.setValue(r, g, b);
        }
        if (colour_faces){
            chooseRandomColor(&r, &g, &b);
            data->material_faces->diffuseColor.setValue(r, g, b);
        }
    }
}
