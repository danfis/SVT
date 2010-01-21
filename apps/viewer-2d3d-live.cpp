/**
 * SVT
 * ----------
 * Copyright (c)2007,2008,2009 Daniel Fiser <danfis (at) danfis (dot) cz>
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
#include <QApplication>
#include <Quarter/Quarter.h>
using namespace std;
using namespace SIM::Coin3D::Quarter;

#include "common/settings.hpp"
#include "common/functions.hpp"
#include "common/msg.hpp"
#include "coin3d/main_window.hpp"
#include "parser/parser.h"
#include "parser/obj.h"

svt_parser_t *parser;
pthread_t th;
struct _th_data_t {
    int end;
    pthread_mutex_t lock;
} th_data = { 0, PTHREAD_MUTEX_INITIALIZER };

void startDyn(SVT::Coin3d::MainWindow *mw);
void stopDyn();

int main2d3dLive(int argc, char *argv[], char *args[], int num_args, bool disable_rotation)
{
    svt_obj_t *o;
    SVT::Coin3d::Obj *obj;

    QApplication app(argc, argv);
    Quarter::init();

    SVT::Coin3d::MainWindow mw;
    if (disable_rotation)
        mw.viewer()->disableRotation();

    mw.applySettings(SVT::Common::settings);

    parser = svtParserNew();

    SVT::Common::parseCmd(num_args, args, parser);

    o = svtParserObjs(parser, 0);
    while (o != 0){
        obj = new SVT::Coin3d::Obj(o);
        obj->applySettings(SVT::Common::settings);
        mw.addObj(obj);

        o = svtObjNext(o);
    }

    startDyn(&mw);

    mw.show();
    app.exec();

    stopDyn();

    svtParserDelete(parser);

    return 0;
}

int end()
{
    int end;

    pthread_mutex_lock(&th_data.lock);
    end = th_data.end;
    pthread_mutex_unlock(&th_data.lock);

    return end;
}

void setEnd(int val)
{
    pthread_mutex_lock(&th_data.lock);
    th_data.end = val;
    pthread_mutex_unlock(&th_data.lock);
}

void *thStart(void *a)
{
    SVT::Coin3d::MainWindow *mw = (SVT::Coin3d::MainWindow *)a;
    svt_obj_t *o;
    SVT::Coin3d::Obj *obj;
    int len, counter, frame;
    int hunks = SVT::Common::settings.hunksize;
    struct timespec sleeptime;
    struct timespec delay;

    // set up sleeptime
    SVT::Common::fromMSToTimespec(SVT::Common::settings.sleeptime, &sleeptime);
    SVT::Common::fromMSToTimespec(SVT::Common::settings.delay, &delay);

    nanosleep(&delay, NULL);

    svtParserClear(parser);
    svtParserSetInput(parser, stdin);
    svtParserParseBegin(parser);

    counter = 1;
    frame = 1;

    while (svtParserParseHunk(parser, hunks) > 0){
        if (end())
            break;

        mw->clearObjsDyn();
        fprintf(stderr, "\n");

        fprintf(stderr, "frame %06d: Added object ", frame++);
        o = svtParserObjsSteal(parser, &len);
        while (o != NULL){
            obj = new SVT::Coin3d::Obj(o);
            obj->applySettings(SVT::Common::settings);
            mw->addObjDyn(obj);

            fprintf(stderr, "#%d, ", counter++);
            o = svtObjDelete(o);
        }

        nanosleep(&sleeptime, NULL);
    }

    fprintf(stderr, "\n");

    return NULL;
}

void startDyn(SVT::Coin3d::MainWindow *mw)
{
    pthread_create(&th, NULL, thStart, (void *)mw);
}

void stopDyn()
{
    setEnd(1);
    pthread_join(th, NULL);

    svtParserParseEnd(parser);
}
