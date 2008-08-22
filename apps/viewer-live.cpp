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
#include <getopt.h>
#include <Inventor/Qt/SoQt.h>
#include <Inventor/nodes/SoGroup.h>
#include <QApplication>
#include "pthread.h"
#include "signal.h"
using namespace std;

#include "common.hpp"
#include "common_coin.hpp"

#include "common/objdata.hpp"
#include "common/viewer.hpp"
#include "common/msg.hpp"
#include "common/coin3dtools.hpp"
#include "parser/parser.h"

#define READER_HUNKS 5

static void *thViewer(void *arg);
static void *thReader(void *arg);

svt_parser_t *parser;
Viewer *viewer;

useconds_t sleep_time = 50000;

svt_obj_t *objs = NULL, *objs_buf = NULL;
pthread_mutex_t lock_rq = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lock_objs = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lock_end = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lock_wakeup = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lock_wakeup2 = PTHREAD_MUTEX_INITIALIZER;
int rq = -1;
int end = 0;

int main(int argc, char *argv[])
{
    pthread_t th[2];
    char **args;
    int num_args;

    args = processOptions(argc, argv, &num_args);

    Coin3dTools::init("viewer");
    viewer = Coin3dTools::viewer();

    applySettings(viewer);

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
    pthread_create(th + 0, 0, thReader, NULL);
    pthread_create(th + 1, 0, thViewer, (void *)viewer);

    Coin3dTools::mainLoop();

    pthread_mutex_lock(&lock_end);
    end = 1;
    pthread_mutex_unlock(&lock_end);
    pthread_mutex_unlock(&lock_wakeup);
    pthread_mutex_unlock(&lock_wakeup2);
    pthread_join(th[1], 0);
    pthread_join(th[0], 0);

    cout << endl;

    svtParserDelete(parser);

    return 0;
}

void *thViewer(void *arg)
{
    long frame = 1;
    QString msg_template = QString("Frame %1, %2 points %3 edges %4 faces");
    QString msg;

    pthread_mutex_lock(&lock_wakeup);

    while (true){
        pthread_mutex_lock(&lock_end);
        if (end == 1){
            pthread_mutex_unlock(&lock_end);
            pthread_exit(NULL);
        }
        pthread_mutex_unlock(&lock_end);

        usleep(sleep_time);

        if (objs == NULL){
            pthread_mutex_lock(&lock_rq);
            rq = 1;
            pthread_mutex_unlock(&lock_wakeup2);
            pthread_mutex_unlock(&lock_rq);
            pthread_mutex_lock(&lock_wakeup);

            pthread_mutex_lock(&lock_objs);
            objs = objs_buf;
            objs_buf = NULL;
            pthread_mutex_unlock(&lock_objs);
        }else{
            // show message
            msg = msg_template
                    .arg(frame, 5)
                    .arg(svtObjNumPoints(objs), 8)
                    .arg(svtObjNumEdges(objs), 8)
                    .arg(svtObjNumFaces(objs), 8);
            Coin3dTools::showMessageInStatusBar(msg);
            frame++;

            // set up object
            viewer->clear();
            viewer->addDynObjData(new ObjData(objs));
            viewer->rebuildSceneGraph();

            // shift list of objects
            objs = svtObjDelete(objs);
        }
    }

    return NULL;
}

void *thReader(void *arg)
{
    int request;
    bool parse = true;

    pthread_mutex_lock(&lock_wakeup2);

    svtParserSetInput(parser, stdin);

    if (svtParserParseBegin(parser) != 0){
        pthread_mutex_lock(&lock_end);
        end = 1;
        pthread_mutex_unlock(&lock_end);
        pthread_exit(NULL);
    }
    
    while (true){
        pthread_mutex_lock(&lock_end);
        // should I exit?
        if (end == 1){
            pthread_mutex_unlock(&lock_end);
            pthread_exit(NULL);
        }
        pthread_mutex_unlock(&lock_end);

        // parse next hunk of objects
        if (parse && svtParserParseHunk(parser, READER_HUNKS) <= 0)
            parse = false;
        if (!parse){
            pthread_mutex_lock(&lock_wakeup2);
        }

        pthread_mutex_lock(&lock_rq);
        // recognise request
        request = rq;
        // and reset rq
        rq = -1;
        pthread_mutex_unlock(&lock_rq);

        if (request == 1){
            pthread_mutex_lock(&lock_objs);

            // delete unused objects
            if (objs_buf != NULL)
                while (objs_buf != NULL)
                    objs_buf = svtObjDelete(objs_buf);

            // take objects from parser
            objs_buf = svtParserObjsSteal(parser, NULL);

            pthread_mutex_unlock(&lock_objs);

            // wake up viewer thread
            pthread_mutex_unlock(&lock_wakeup);
        }
    }

    return NULL;
}

