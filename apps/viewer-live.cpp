/**
 * Coin3dTools
 * ------------
 * Copyright (c)2007 Daniel Fiser <danfis (at) danfis (dot) cz>
 *
 *
 * This file is part of Coin3dTools
 *
 * Coin3dTools is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Coin3dTools is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Coin3dTools.  If not, see <http://www.gnu.org/licenses/>.
 */

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
#include "parser.h"
#include "msg.hpp"
#include "coin3dtools.hpp"
#include "common.hpp"

static void *thStart(void *arg);
static void thParse(Viewer *viewer, long *frame);

svt_parser_t *parser;

int main(int argc, char *argv[])
{
    Viewer *viewer;
    pthread_t th;

    Coin3dTools::init("viewer");

    viewer = Coin3dTools::viewer();

#include "viewer_common_main.cpp"
    parser = svtParserNew();

    // first parse static objects
    if (args != 0){
        FILE *fin;

        for (int i=0; i < num_args; i++){
            cerr << "Parsing file " << args[i] << " ..." << endl;

            fin = fopen(args[i], "r");
            if (fin == NULL){
                ERR("Can't read file " << args[i]);
                continue;
            }

            svtParserSetInput(parser, fin);

            parseObjData();

            fclose(fin);
        }
    }

    // start reading thread
    pthread_create(&th, 0, thStart, (void *)viewer);

    Coin3dTools::mainLoop();

    //pthread_join(th, 0);
    pthread_kill(th, SIGINT);

    cout << endl;

    svtParserDelete(parser);

    return 0;
}

void *thStart(void *arg)
{
    long frame = 1;
    Viewer *viewer = (Viewer *)arg;
    Parser *parser = Parser::instance();

    parser->setInput(0);// set input to stdin

    thParse(viewer, &frame);

    return 0;
}

void thParse(Viewer *viewer, long *frame)
{
    ObjData *data;
    Parser *parser = Parser::instance();
    QString msg_template, msg;

    msg_template = QString("Frame %1, %2 points %3 edges %4 faces");
    while ((data = parser->parse()) != 0){
        msg = msg_template
                .arg(*frame, 5)
                .arg(data->numPoints(), 8)
                .arg(data->numEdges(), 8)
                .arg(data->numFaces(), 8);
        Coin3dTools::showMessageInStatusBar(msg);

        viewer->clear();
        viewer->addDynObjData(data);
        viewer->rebuildSceneGraph();
        //usleep(50000);

        (*frame)++;
    }
}

