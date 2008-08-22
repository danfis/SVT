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

#include <cstdlib>
#include <getopt.h>

#include "parser.h"

#include "common.hpp"
#include "settings.hpp"
#include "parse_func.h"

extern svt_parser_t *parser;

enum Options {
    HELP = 'h',
    ALL_OFF,
    POINTS_OFF,
    EDGES_OFF,
    FACES_OFF,
    POINT_SIZE,
    EDGE_WIDTH,
    POINT_COLOR_RED,
    POINT_COLOR_GREEN,
    POINT_COLOR_BLUE,
    EDGE_COLOR_RED,
    EDGE_COLOR_GREEN,
    EDGE_COLOR_BLUE,
    FACE_COLOR_RED,
    FACE_COLOR_GREEN,
    FACE_COLOR_BLUE,
    COLOUR_POINTS,
    COLOUR_EDGES,
    COLOUR_FACES,

#ifdef TO_SVG
    OUTPUT_WIDTH,
    VIEW_BOX_X,
    VIEW_BOX_Y,
    VIEW_BOX_WIDTH,
    VIEW_BOX_HEIGHT,
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
    { "point-color-red", required_argument, NULL, POINT_COLOR_RED },
    { "point-color-green", required_argument, NULL, POINT_COLOR_GREEN },
    { "point-color-blue", required_argument, NULL, POINT_COLOR_BLUE },
    { "edge-color-red", required_argument, NULL, EDGE_COLOR_RED },
    { "edge-color-green", required_argument, NULL, EDGE_COLOR_GREEN },
    { "edge-color-blue", required_argument, NULL, EDGE_COLOR_BLUE },
    { "face-color-red", required_argument, NULL, FACE_COLOR_RED },
    { "face-color-green", required_argument, NULL, FACE_COLOR_GREEN },
    { "face-color-blue", required_argument, NULL, FACE_COLOR_BLUE },
    { "colour-points", no_argument, NULL, COLOUR_POINTS },
    { "colour-edges",  no_argument, NULL, COLOUR_EDGES },
    { "colour-faces",  no_argument, NULL, COLOUR_FACES },

#ifdef TO_SVG
    { "output-width", required_argument, NULL, OUTPUT_WIDTH },
    { "view-box-x", required_argument, NULL, VIEW_BOX_X },
    { "view-box-y", required_argument, NULL, VIEW_BOX_Y },
    { "view-box-width", required_argument, NULL, VIEW_BOX_WIDTH },
    { "view-box-height", required_argument, NULL, VIEW_BOX_HEIGHT },
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
        std::cout << optstr << std::endl;
    }

#ifdef VIEWER
    std::cout << "Usage: " << argv[0] << " [ Options ] <file.txt" << std::endl;
    std::cout << "          or" << std::endl;
    std::cout << "       " << argv[0] << " [ Options ] file1.txt file2.txt ..." << std::endl;
#endif /* VIEWER */

#ifdef VIEWER_LIVE
    std::cout << "Usage: " << argv[0] << " [ Options ] staticobjs1.txt staticobjs2.txt ... <dynobjs.txt" << std::endl;
#endif

    std::cout << std::endl;
    std::cout << "Options:" << std::endl;
    std::cout << "  --help                      Show this help." << std::endl;
    std::cout << "  --all-off                   Turn off all objects." << std::endl;
    std::cout << "  --points-off                Turn off all points." << std::endl;
    std::cout << "  --edges-off                 Turn off all edges." << std::endl;
    std::cout << "  --faces-off                 Turn off all faces." << std::endl;
    std::cout << std::endl;
    std::cout << "  --point-size         float  Set size of points to specified value." << std::endl;
    std::cout << "  --edge-width         float  Set width of edges to specified value." << std::endl;
    std::cout << std::endl;
    std::cout << "  --point-color-red    float  Set color of points to specified value." << std::endl;
    std::cout << "  --point-color-green  float  Value must be between 0 and 1." << std::endl;
    std::cout << "  --point-color-blue   float" << std::endl;
    std::cout << "  --edge-color-red     float  Set color of edges to specified value." << std::endl;
    std::cout << "  --edge-color-green   float  Value must be between 0 and 1." << std::endl;
    std::cout << "  --edge-color-blue    float" << std::endl;
    std::cout << "  --face-color-red     float  Set color of faces to specified value." << std::endl;
    std::cout << "  --face-color-green   float  Value must be between 0 and 1." << std::endl;
    std::cout << "  --face-color-blue    float" << std::endl;
    std::cout << std::endl;
    std::cout << "  --colour-points             Colour points from different objects by different color." << std::endl;
    std::cout << "  --colour-edges              Colour edges from different objects by different color." << std::endl;
    std::cout << "  --colour-faces              Colour faces from different objects by different color." << std::endl;

#ifdef TO_SVG
    std::cout << std::endl;
    std::cout << "  --output-width     int    Width of resulting picture.  Heigh is computed from viewbox." << std::endl;
    std::cout << "  --view-box-x       float  Proportions of viewbox." << std::endl;
    std::cout << "  --view-box-y       float" << std::endl;
    std::cout << "  --view-box-width   float" << std::endl;
    std::cout << "  --view-box-height  float" << std::endl;
    std::cout << "  --precision        int    Set up precision of floating point numbers when priting them out." << std::endl;
#endif

    exit(-1);
}

char **processOptions(int argc, char *argv[], int *len)
{
    int c, option_index;
    float f;
    int i;
    char **args;

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
                if (parseFloat(optarg, &f) != 0)
                    usage(argc, argv, "Error: option \"--point-size\" require"
                                      " float argument");
                Settings::point_size = f;
                break;
            case EDGE_WIDTH:
                if (parseFloat(optarg, &f) != 0)
                    usage(argc, argv, "Error: option \"--edge-width\" require"
                                      " float argument");
                Settings::edge_width = f;
                break;
            case POINT_COLOR_RED:
                if (parseFloat(optarg, &f) != 0)
                    usage(argc, argv, "Error: option \"--point-color-red\""
                                      " require float argument.");
                if (f > 1)
                    usage(argc, argv, "Error: color can be define only"
                                      " between 0 and 1");
                Settings::point_color[0] = f;
                break;
            case POINT_COLOR_GREEN:
                if (parseFloat(optarg, &f) != 0)
                    usage(argc, argv, "Error: option \"--point-color-green\""
                                      " require float argument.");
                if (f > 1)
                    usage(argc, argv, "Error: color can be define only"
                                      " between 0 and 1");
                Settings::point_color[1] = f;
                break;
            case POINT_COLOR_BLUE:
                if (parseFloat(optarg, &f) != 0)
                    usage(argc, argv, "Error: option \"--point-color-blue\""
                                      " require float argument.");
                if (f > 1)
                    usage(argc, argv, "Error: color can be define only"
                                      " between 0 and 1");
                Settings::point_color[2] = f;
                break;
            case EDGE_COLOR_RED:
                if (parseFloat(optarg, &f) != 0)
                    usage(argc, argv, "Error: option \"--edge-color-red\""
                                      " require float argument.");
                if (f > 1)
                    usage(argc, argv, "Error: color can be define only"
                                      " between 0 and 1");
                Settings::edge_color[0] = f;
                break;
            case EDGE_COLOR_GREEN:
                if (parseFloat(optarg, &f) != 0)
                    usage(argc, argv, "Error: option \"--edge-color-green\""
                                      " require float argument.");
                if (f > 1)
                    usage(argc, argv, "Error: color can be define only"
                                      " between 0 and 1");
                Settings::edge_color[1] = f;
                break;
            case EDGE_COLOR_BLUE:
                if (parseFloat(optarg, &f) != 0)
                    usage(argc, argv, "Error: option \"--edge-color-blue\""
                                      " require float argument.");
                if (f > 1)
                    usage(argc, argv, "Error: color can be define only"
                                      " between 0 and 1");
                Settings::edge_color[2] = f;
                break;
            case FACE_COLOR_RED:
                if (parseFloat(optarg, &f) != 0)
                    usage(argc, argv, "Error: option \"--face-color-red\""
                                      " require float argument.");
                if (f > 1)
                    usage(argc, argv, "Error: color can be define only"
                                      " between 0 and 1");
                Settings::face_color[0] = f;
                break;
            case FACE_COLOR_GREEN:
                if (parseFloat(optarg, &f) != 0)
                    usage(argc, argv, "Error: option \"--face-color-green\""
                                      " require float argument.");
                if (f > 1)
                    usage(argc, argv, "Error: color can be define only"
                                      " between 0 and 1");
                Settings::face_color[1] = f;
                break;
            case FACE_COLOR_BLUE:
                if (parseFloat(optarg, &f) != 0)
                    usage(argc, argv, "Error: option \"--face-color-blue\""
                                      " require float argument.");
                if (f > 1)
                    usage(argc, argv, "Error: color can be define only"
                                      " between 0 and 1");
                Settings::face_color[2] = f;
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
                if (parseInt(optarg, &i) != 0)
                    usage(argc, argv, "Error: option \"--output-width\""
                                      " requires int argument.");
                Settings::svg_width = i;
                break;
            case VIEW_BOX_X:
                if (parseFloat(optarg, &f) != 0)
                    usage(argc, argv, "Error: option \"--view-box-x\""
                                      " requires float argument.");
                Settings::svg_view_box_enabled = true;
                Settings::svg_view_box[0] = f;
                break;
            case VIEW_BOX_Y:
                if (parseFloat(optarg, &f) != 0)
                    usage(argc, argv, "Error: option \"--view-box-y\""
                                      " requires float argument.");
                Settings::svg_view_box_enabled = true;
                Settings::svg_view_box[1] = f;
                break;
            case VIEW_BOX_WIDTH:
                if (parseFloat(optarg, &f) != 0)
                    usage(argc, argv, "Error: option \"--view-box-width\""
                                      " requires float argument.");
                Settings::svg_view_box_enabled = true;
                Settings::svg_view_box[2] = f;
                break;
            case VIEW_BOX_HEIGHT:
                if (parseFloat(optarg, &f) != 0)
                    usage(argc, argv, "Error: option \"--view-box-height\""
                                      " requires float argument.");
                Settings::svg_view_box_enabled = true;
                Settings::svg_view_box[3] = f;
                break;
            case PRECISION:
                if (parseInt(optarg, &i) != 0)
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

