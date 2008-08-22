/**
 * SVT
 * ----------
 * Copyright (c)2007,2008 Daniel Fiser <danfis (at) danfis (dot) cz>
 *
 *
 * This file is part of SVT
 *
 * SVT is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * SVT is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with SVT. If not, see <http://www.gnu.org/licenses/>.
 */


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
