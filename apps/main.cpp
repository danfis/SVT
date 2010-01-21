/**
 * SVT
 * ----------
 * Copyright (c)2007,2008,2009,2010 Daniel Fiser <danfis (at) danfis (dot) cz>
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
#include <cstring>
using namespace std;

#include "common/msg.hpp"
#include "common/settings.hpp"
#include "common/functions.hpp"
#include "parser/parser.h"
#include "parser/obj.h"

int main2d3d(int argc, char *argv[], svt_parser_t *parser, bool disable_rotation);
int main2d3dLive(int argc, char *argv[], char *args[], int num_args, bool disable_rotation);
int mainToSVG(int argc, char *argv[], svt_parser_t *parser);

static int main2d(int argc, char *argv[], svt_parser_t *parser)
    { return main2d3d(argc, argv, parser, true); }
static int main3d(int argc, char *argv[], svt_parser_t *parser)
    { return main2d3d(argc, argv, parser, false); }

static int main2dLive(int argc, char *argv[], char *args[], int num_args)
    { return main2d3dLive(argc, argv, args, num_args, true); }
static int main3dLive(int argc, char *argv[], char *args[], int num_args)
    { return main2d3dLive(argc, argv, args, num_args, false); }


enum Type {
    NONE,
    VIEWER2D,
    VIEWER3D,
    VIEWER2DLIVE,
    VIEWER3DLIVE,
    TO_SVG
};

static int cmpend(const char *a, const char *b);

int main(int argc, char *argv[])
{
    Type type = NONE;
    svt_parser_t *parser;
    char **args;
    int num_args;

    args = SVT::Common::settings.setUpFromOptions(argc, argv, &num_args);

    switch (SVT::Common::settings.type){
        case SVT::Common::Settings::TYPE_VIEWER2D:
            type = VIEWER2D;
            break;
        case SVT::Common::Settings::TYPE_VIEWER3D:
            type = VIEWER3D;
            break;
        case SVT::Common::Settings::TYPE_VIEWER2DLIVE:
            type = VIEWER2DLIVE;
            break;
        case SVT::Common::Settings::TYPE_VIEWER3DLIVE:
            type = VIEWER3DLIVE;
            break;
        case SVT::Common::Settings::TYPE_TO_SVG:
            type = TO_SVG;
            break;
        default:
            type = NONE;
            break;
    }

    if (cmpend(argv[0], "svt-viewer-2d") == 0){
        type = VIEWER2D;
    }else if (cmpend(argv[0], "svt-viewer-3d") == 0){
        type = VIEWER3D;
    }else if (cmpend(argv[0], "svt-viewer-2d-live") == 0){
        type = VIEWER2DLIVE;
    }else if (cmpend(argv[0], "svt-viewer-3d-live") == 0){
        type = VIEWER3DLIVE;
    }else if (cmpend(argv[0], "svt-to-svg") == 0){
        type = TO_SVG;
    }


    if (type == VIEWER2DLIVE){
        return main2dLive(argc, argv, args, num_args);
    }else if (type == VIEWER3DLIVE){
        return main3dLive(argc, argv, args, num_args);
    }else{
        parser = svtParserNew();
        SVT::Common::parseAll(num_args, args, parser);

        if (type == NONE){
            if (svtParserHas3DPoints(parser)){
                main3d(argc, argv, parser);
            }else{
                main2d(argc, argv, parser);
            }
        }else if (type == VIEWER2D){
            main2d(argc, argv, parser);
        }else if (type == VIEWER3D){
            main3d(argc, argv, parser);
        }else if (type == TO_SVG){
            return mainToSVG(argc, argv, parser);
        }

        svtParserDelete(parser);
    }

    return 0;
}


static int cmpend(const char *a, const char *b)
{
    int lena = strlen(a);
    int lenb = strlen(b);

    if (lena == lenb){
        return strcmp(a, b);
    }else if (lena > lenb){
        return strcmp(a + (lena - lenb), b);
    }else{
        return strcmp(a, b + (lenb - lena));
    }
}
