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
#include <cstdlib>
#include <getopt.h>

#include "common.hpp"
#include "settings.hpp"

#include "parser/parser.h"
#include "common/msg.hpp"


extern svt_parser_t *parser;

enum Options {
    HELP = 'h',
    ALL_OFF,
    POINTS_OFF,
    EDGES_OFF,
    FACES_OFF,
    POINT_SIZE,
    EDGE_WIDTH,
    POINT_COLOR,
    EDGE_COLOR,
    FACE_COLOR,
    COLOUR_POINTS,
    COLOUR_EDGES,
    COLOUR_FACES,

#ifdef TO_SVG
    OUTPUT_WIDTH,
    VIEW_BOX,
    PRECISION,
#endif

    OPTIONS_END
};


struct option options[] = {
    { "help", no_argument, NULL, HELP },
    { "all-off", no_argument, NULL, ALL_OFF },
    { "points-off", no_argument, NULL, POINTS_OFF },
    { "edges-off", no_argument, NULL, EDGES_OFF },
    { "faces-off", no_argument, NULL, FACES_OFF },
    { "point-size", required_argument, NULL, POINT_SIZE },
    { "edge-width", required_argument, NULL, EDGE_WIDTH },
    { "point-color", required_argument, NULL, POINT_COLOR },
    { "edge-color", required_argument, NULL, EDGE_COLOR },
    { "face-color", required_argument, NULL, FACE_COLOR },
    { "colour-points", no_argument, NULL, COLOUR_POINTS },
    { "colour-edges",  no_argument, NULL, COLOUR_EDGES },
    { "colour-faces",  no_argument, NULL, COLOUR_FACES },

#ifdef TO_SVG
    { "output-width", required_argument, NULL, OUTPUT_WIDTH },
    { "view-box", required_argument, NULL, VIEW_BOX },
    { "precision", required_argument, NULL, PRECISION },
#endif

    { NULL, 0, NULL, 0 }
};

void chooseRandomColor(float *r, float *g, float *b)
{
    do {
        *r = drand48();
        *g = drand48();
        *b = drand48();
    } while (*r * *g * *b < 0.01f); // eliminate black dark colors
}


void usage(int argc, char *argv[], const char *optstr)
{
    if (optstr != 0){
        std::cerr << optstr << std::endl;
    }

#ifdef VIEWER
    std::cerr << "Usage: " << argv[0] << " [ Options ] <file.txt" << std::endl;
    std::cerr << "          or" << std::endl;
    std::cerr << "       " << argv[0] << " [ Options ] file1.txt file2.txt ..." << std::endl;
#endif /* VIEWER */

#ifdef VIEWER_LIVE
    std::cerr << "Usage: " << argv[0] << " [ Options ] staticobjs1.txt staticobjs2.txt ... <dynobjs.txt" << std::endl;
#endif

    std::cerr << std::endl;
    std::cerr << "Options:" << std::endl;
    std::cerr << "  --help                      Show this help." << std::endl;
    std::cerr << "  --all-off                   Turn off all objects." << std::endl;
    std::cerr << "  --points-off                Turn off all points." << std::endl;
    std::cerr << "  --edges-off                 Turn off all edges." << std::endl;
    std::cerr << "  --faces-off                 Turn off all faces." << std::endl;
    std::cerr << std::endl;
    std::cerr << "  --point-size         float  Set size of points to specified value." << std::endl;
    std::cerr << "  --edge-width         float  Set width of edges to specified value." << std::endl;
    std::cerr << std::endl;
    std::cerr << "  --point-color        float,float,float  Set color of points." << std::endl;
    std::cerr << "  --edge-color         float,float,float  Set color of edges." << std::endl;
    std::cerr << "  --face-color         float,float,float  Set color of faces." << std::endl;
    std::cerr << "  --point-color-red    float  Set color of points to specified value." << std::endl;
    std::cerr << "  --point-color-green  float  Value must be between 0 and 1." << std::endl;
    std::cerr << "  --point-color-blue   float" << std::endl;
    std::cerr << "  --edge-color-red     float  Set color of edges to specified value." << std::endl;
    std::cerr << "  --edge-color-green   float  Value must be between 0 and 1." << std::endl;
    std::cerr << "  --edge-color-blue    float" << std::endl;
    std::cerr << "  --face-color-red     float  Set color of faces to specified value." << std::endl;
    std::cerr << "  --face-color-green   float  Value must be between 0 and 1." << std::endl;
    std::cerr << "  --face-color-blue    float" << std::endl;
    std::cerr << std::endl;
    std::cerr << "  --colour-points             Colour points from different objects by different color." << std::endl;
    std::cerr << "  --colour-edges              Colour edges from different objects by different color." << std::endl;
    std::cerr << "  --colour-faces              Colour faces from different objects by different color." << std::endl;

#ifdef TO_SVG
    std::cerr << std::endl;
    std::cerr << "  --output-width int    Width of resulting picture.  Heigh is computed from viewbox." << std::endl;
    std::cerr << "  --view-box     float,float,float,float  Proportions of viewbox." << std::endl;
    std::cerr << "                                          Parameters are: x, y, width, height" << std::endl;
    std::cerr << "  --precision    int    Set up precision of floating point numbers when priting them out." << std::endl;
#endif

    exit(-1);
}

char **processOptions(int argc, char *argv[], int *len)
{
    int c, option_index;
    float f;
    int i;
    char **args;
    float fl[4];

    while ((c = getopt_long(argc, argv, "h", options, &option_index)) != -1){
        switch (c){
            case HELP:
                usage(argc, argv);
                break;
            case ALL_OFF:
                Settings::all_off = true;
                break;
            case POINTS_OFF:
                Settings::points_off = true;
                break;
            case EDGES_OFF:
                Settings::edges_off = true;
                break;
            case FACES_OFF:
                Settings::faces_off = true;
                break;
            case POINT_SIZE:
                if (!parseFloat(optarg, &f))
                    usage(argc, argv, "Error: option \"--point-size\" require"
                                      " float argument");
                Settings::point_size = f;
                break;
            case EDGE_WIDTH:
                if (!parseFloat(optarg, &f))
                    usage(argc, argv, "Error: option \"--edge-width\" require"
                                      " float argument");
                Settings::edge_width = f;
                break;
            case POINT_COLOR:
                if (!parseFloatList(optarg, 3, fl))
                    usage(argc, argv, "Error: option \"--point-color\""
                                      " requires triplet of floats as argument.");
                Settings::point_color[0] = fl[0];
                Settings::point_color[1] = fl[1];
                Settings::point_color[2] = fl[2];
                break;
            case EDGE_COLOR:
                if (!parseFloatList(optarg, 3, fl))
                    usage(argc, argv, "Error: option \"--edge-color\""
                                      " requires triplet of floats as argument.");
                Settings::edge_color[0] = fl[0];
                Settings::edge_color[1] = fl[1];
                Settings::edge_color[2] = fl[2];
                break;
            case FACE_COLOR:
                if (!parseFloatList(optarg, 3, fl))
                    usage(argc, argv, "Error: option \"--face-color\""
                                      " requires triplet of floats as argument.");
                Settings::face_color[0] = fl[0];
                Settings::face_color[1] = fl[1];
                Settings::face_color[2] = fl[2];
                break;
            case COLOUR_POINTS:
                Settings::colour_points = true;
                break;
            case COLOUR_EDGES:
                Settings::colour_edges = true;
                break;
            case COLOUR_FACES:
                Settings::colour_faces = true;
                break;

#ifdef TO_SVG
            case OUTPUT_WIDTH:
                if (!parseInt(optarg, &i))
                    usage(argc, argv, "Error: option \"--output-width\""
                                      " requires int argument.");
                Settings::svg_width = i;
                break;
            case VIEW_BOX:
                if (!parseFloatList(optarg, 4, fl))
                    usage(argc, argv, "Error: option \"--view-box\""
                                      " requires four floats as argument.");
                Settings::svg_view_box_enabled = true;
                Settings::svg_view_box[0] = fl[0];
                Settings::svg_view_box[1] = fl[1];
                Settings::svg_view_box[2] = fl[2];
                Settings::svg_view_box[3] = fl[3];
                break;
            case PRECISION:
                if (!parseInt(optarg, &i))
                    usage(argc, argv, "Error: option \"--precision\""
                                      " requires int argument.");
                Settings::svg_precision = i;
                break;
#endif
            default:
                usage(argc, argv);
        }
    }

    if (argc - optind > 0){
        args = argv + optind;
        *len = argc - optind;
    }else{
        args = 0;
        *len = 0;
    }

    return args;
}


void colorToHex(char str[7], float colorf[3])
{
    int color[3];
    int n, pos;
    char c;

    color[0] = (int)(255 * colorf[0]);
    color[1] = (int)(255 * colorf[1]);
    color[2] = (int)(255 * colorf[2]);

    pos = 0;
    for (int i=0; i < 3; i++){
        n = color[i] / 16;
        if (n > 9){
            c = 'A' + n - 10;
        }else{
            c = '0' + n;
        }
        str[pos++] = c;

        n = color[i] % 16;
        if (n > 9){
            c = 'A' + n - 10;
        }else{
            c = '0' + n;
        }
        str[pos++] = c;
    }

    str[6] = 0;
}

bool parseFloat(const char *str, float *f)
{
    return svtParseFloat(str, f) == 0;
}

bool parseInt(const char *str, int *i)
{
    return svtParseInt(str, i) == 0;
}

bool parseFloatList(const char *str, int len, float *nums)
{
    static char buffer[100];
    const char *c;
    int i;

    c = str;

    for (int j=0; j < len; j++){
        if (j > 0 && *c != ',')
            return false;
        if (j > 0 && *c != 0)
            c++;

        for (i=0; *c != ',' && *c != 0; i++, c++)
            buffer[i] = *c;
        buffer[i] = 0;
        if (i < 1)
            return false;

        if (svtParseFloat(buffer, nums + j) != 0)
            return false;
    }

    if (*c != 0)
        return false;
    return true;
}
