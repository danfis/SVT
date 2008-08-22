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

#include "objdata.hpp"
#include "viewer.hpp"
#include "parser.h"
#include "coin3dtools.hpp"

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

void parseObjData()
{
    svt_obj_t *objs;
    ObjData *data;
    Viewer *viewer;
    float r, g, b;

    viewer = Coin3dTools::viewer();

    if (svtParserParse(parser) != 0){
        ERR("Can't parse input");
        return;
    }

    objs = svtParserObjsSteal(parser, NULL);
    while (objs != NULL){
        data = new ObjData(objs);
        viewer->addObjData(data);

        // colour elemets if requested
        if (Settings::colour_points){
            chooseRandomColor(&r, &g, &b);
            data->material_points->diffuseColor.setValue(r, g, b);
        }
        if (Settings::colour_edges){
            chooseRandomColor(&r, &g, &b);
            data->material_edges->diffuseColor.setValue(r, g, b);
        }
        if (Settings::colour_faces){
            chooseRandomColor(&r, &g, &b);
            data->material_faces->diffuseColor.setValue(r, g, b);
        }

        objs = svtObjDelete(objs);
    }
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
    exit(-1);
}

char **processOptions(int argc, char *argv[], int *len)
{
    int c, option_index;
    float f;
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

void applySettings(Viewer *viewer)
{
    viewer->setDefaultSwitch(!Settings::all_off);
    viewer->setDefaultPointsSwitch(!Settings::points_off);
    viewer->setDefaultEdgesSwitch(!Settings::edges_off);
    viewer->setDefaultFacesSwitch(!Settings::faces_off);

    viewer->setDefaultPointSize(Settings::point_size);
    viewer->setDefaultLineWidth(Settings::edge_width);

    viewer->setDefaultPointsDiffuseColorRed(Settings::point_color[0]);
    viewer->setDefaultPointsDiffuseColorGreen(Settings::point_color[1]);
    viewer->setDefaultPointsDiffuseColorBlue(Settings::point_color[2]);
    viewer->setDefaultEdgesDiffuseColorRed(Settings::edge_color[0]);
    viewer->setDefaultEdgesDiffuseColorGreen(Settings::edge_color[1]);
    viewer->setDefaultEdgesDiffuseColorBlue(Settings::edge_color[2]);
    viewer->setDefaultFacesDiffuseColorRed(Settings::face_color[0]);
    viewer->setDefaultFacesDiffuseColorGreen(Settings::face_color[1]);
    viewer->setDefaultFacesDiffuseColorBlue(Settings::face_color[2]);
}
