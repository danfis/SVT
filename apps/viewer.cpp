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
#include <cstdlib>
#include <getopt.h>
#include <Inventor/Qt/SoQt.h>
#include <Inventor/nodes/SoGroup.h>
#include <QApplication>
#include <QStatusBar>
#include <QMainWindow>
using namespace std;

#include "common/settings.hpp"
#include "common/functions.hpp"
#include "common/msg.hpp"
#include "coin3d/coin3d.hpp"
#include "parser/parser.h"
#include "parser/obj.h"

int main(int argc, char *argv[])
{
    char **args;
    int num_args;
    svt_parser_t *parser;
    svt_obj_t *o;
    SVT::Coin3d::Obj *obj;

    args = SVT::Common::settings.setUpFromOptions(argc, argv, &num_args);

    SVT::Coin3d::Coin3d::init("viewer");

    parser = svtParserNew();

    SVT::Common::parseAll(num_args, args, parser);

    o = svtParserObjs(parser, 0);
    while (o != 0){
        obj = new SVT::Coin3d::Obj(o);
        SVT::Common::settings.apply(obj);
        SVT::Coin3d::Coin3d::addObj(obj);

        o = svtObjNext(o);
    }

    svtParserDelete(parser);

    SVT::Coin3d::Coin3d::mainLoop();

    SVT::Coin3d::Coin3d::free();

    return 0;
}
