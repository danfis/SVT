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

#include "common.hpp"
#include "common_coin.hpp"

#include "common/objdata.hpp"
#include "common/viewer.hpp"
#include "common/msg.hpp"
#include "common/coin3dtools.hpp"
#include "parser/parser.h"

void chooseRandomColor(float *r, float *g, float *b);
void parseObjData();

svt_parser_t *parser;

int main(int argc, char *argv[])
{
    Viewer *viewer;
    char **args;
    int num_args;

    args = processOptions(argc, argv, &num_args);

    Coin3dTools::init("viewer");
    viewer = Coin3dTools::viewer();

    applySettings(viewer);

    parser = svtParserNew();

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
    }else{
        parseObjData();
    }

    svtParserDelete(parser);

    Coin3dTools::mainLoop();

    return 0;
}
