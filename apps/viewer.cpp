#include <iostream>
#include <Inventor/Qt/SoQt.h>
#include <Inventor/nodes/SoGroup.h>
#include <QApplication>
using namespace std;

#include "objdata.hpp"
#include "viewer_with_config_dialog.hpp"
#include "parser.hpp"
#include "msg.hpp"

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
    viewer = new ViewerWithConfigDialog(mainwin);
    while ((data = parser->parse()) != 0)
        viewer->addObjData(data);

    viewer->show();
    SoQt::show(mainwin);
    SoQt::mainLoop();

    delete mainwin;
    delete viewer;

    return 0;
}
