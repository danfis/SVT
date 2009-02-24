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
#include <QStatusBar>
#include <QMainWindow>
using namespace std;

#include "common/msg.hpp"
#include "common/settings.hpp"
#include "common/functions.hpp"
#include "parser/parser.h"
#include "parser/obj.h"
#include "qt2d/main_window.hpp"


static void changeDefaultSettings();

int main(int argc, char *argv[])
{
    char **args;
    int num_args;
    svt_parser_t *parser;
    svt_obj_t *o;
    SVT::Qt2D::Obj *obj;

    changeDefaultSettings();

    args = SVT::Common::settings.setUpFromOptions(argc, argv, &num_args);

    QApplication app(argc, argv);
    SVT::Qt2D::MainWindow mw;

    parser = svtParserNew();

    SVT::Common::parseAll(num_args, args, parser);

    o = svtParserObjs(parser, 0);
    while (o != 0){
        obj = new SVT::Qt2D::Obj(o);
        SVT::Common::settings.apply(obj);
        mw.addObj(obj);

        o = svtObjNext(o);
    }

    svtParserDelete(parser);


    mw.show();
    app.exec();

    return 0;
}

static void changeDefaultSettings()
{
    SVT::Common::settings.point_color[0] = 0.;
    SVT::Common::settings.point_color[1] = 0.;
    SVT::Common::settings.point_color[2] = 0.;
}
