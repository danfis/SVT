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
#include <cstring>
using namespace std;

#include "common/msg.hpp"
#include "common/settings.hpp"
#include "common/functions.hpp"
#include "parser/parser.h"
#include "parser/obj.h"
#include "qt2d/main_window.hpp"
#include "coin3d/coin3d.hpp"

int main2d(int argc, char *argv[]);
int main3d(int argc, char *argv[]);
int mainToSVG(int argc, char *argv[]);



enum Type {
    VIEWER2D,
    VIEWER3D,
    TO_SVG
};

static int cmpend(const char *a, const char *b);

int main(int argc, char *argv[])
{
    Type type = VIEWER2D;

    for (int i=1; i < argc; i++){
        if (strcmp(argv[i], "--2d") == 0){
            type = VIEWER2D;
            break;
        }else if (strcmp(argv[i], "--3d") == 0){
            type = VIEWER3D;
            break;
        }else if (strcmp(argv[i], "--to-svg") == 0){
            type = TO_SVG;
            break;
        }
    }

    if (cmpend(argv[0], "svt-viewer-2d") == 0){
        type = VIEWER2D;
    }else if (cmpend(argv[0], "svt-viewer-3d") == 0){
        type = VIEWER3D;
    }else if (cmpend(argv[0], "svt-to-svg") == 0){
        type = TO_SVG;
    }

    std::cerr << "AVRG[0]: " << argv[0] << std::endl;

    if (type == VIEWER2D){
        return main2d(argc, argv);
    }else if (type == VIEWER3D){
        return main3d(argc, argv);
    }else if (type == TO_SVG){
        return mainToSVG(argc, argv);
    }

    return main3d(argc, argv);
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
