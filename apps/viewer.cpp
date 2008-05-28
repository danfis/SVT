#include <iostream>
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


#include "viewer_common.cpp"

int main(int argc, char *argv[])
{
    Parser *parser;
    ObjData *data;
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

            while ((data = parser->parse()) != 0)
                viewer->addObjData(data);
        }
    }else{
        while ((data = parser->parse()) != 0)
            viewer->addObjData(data);
    }

    Coin3dTools::mainLoop();

    return 0;
}
