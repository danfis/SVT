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
#include <QApplication>
#include <QStatusBar>
#include <QMainWindow>
using namespace std;

#include "common.hpp"
#include "common/msg.hpp"
#include "parser/parser.h"
#include "parser/obj.h"
#include "qt2d/main_window.hpp"

svt_parser_t *parser;

int main(int argc, char *argv[])
{
    char **args;
    int num_args;
    svt_parser_t *parser;
    svt_obj_t *o;
    SVT::Qt2D::Obj *obj;

    args = processOptions(argc, argv, &num_args);

    QApplication app(argc, argv);
    SVT::Qt2D::MainWindow mw;

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

            if (svtParserParse(parser) != 0){
                ERR("Can't parse file " << args[i]);
            }

            fclose(fin);
        }
    }else{
        if (svtParserParse(parser) != 0){
            ERR("Can't parse input");
        }
    }

    o = svtParserObjs(parser, 0);
    while (o != 0){
        obj = new SVT::Qt2D::Obj(o);
        applyDefaultSettings(obj);
        mw.addObj(obj);

        o = svtObjNext(o);
    }

    svtParserDelete(parser);


    mw.show();
    mw.scaleToWindow();

    app.exec();

    return 0;
}
