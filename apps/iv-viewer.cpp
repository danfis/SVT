#include <iostream>
#include <Inventor/SoDB.h>
#include <Inventor/Qt/SoQt.h>
#include <Inventor/Qt/viewers/SoQtExaminerViewer.h>
#include <Inventor/nodes/SoCamera.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/sensors/SoFieldSensor.h>
using namespace std;

int main(int argc, char **argv)
{
    SoSeparator *root;
    SoNode *node;

    if (argc < 2) {
        cerr << "Usage: " << argv[0] << "filename [filename [...]]" << endl;
        return -1;
    }

    QWidget *mainwin = SoQt::init(argc, argv, argv[0]);
    if (mainwin == NULL){
        cerr << "Unable to create main window" << endl;
        return -1;
    }

    root = new SoSeparator;
    root->ref();

    SoInput inputFile;
    for (int i=1; i < argc; i++){
        if (inputFile.openFile(argv[i]) == FALSE) {
            cerr << "Could not open file " << argv[i] << endl;
            return -1;
        }
        node = SoDB::readAll(&inputFile);
        root->addChild(node);
    }

    SoQtExaminerViewer *viewer = new SoQtExaminerViewer(mainwin);

    viewer->setSceneGraph(root);
    viewer->setTitle("IV Viewer");
    viewer->show();

    SoQt::show(mainwin);
    SoQt::mainLoop();

    root->unref();
    delete viewer;
}
