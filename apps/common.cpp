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
#include "objdata.hpp"
#include "viewer.hpp"
#include "parser.hpp"
#include "coin3dtools.hpp"

#include "common.hpp"

bool colour_points = false;
bool colour_edges = false;
bool colour_faces = false;

char **args = 0;
int num_args = 0;

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
    Parser *parser;
    ObjData *data;
    Viewer *viewer;
    float r, g, b;

    parser = Parser::instance();
    viewer = Coin3dTools::viewer();

    while ((data = parser->parse()) != 0){
        viewer->addObjData(data);

        // colour elemets if requested
        if (colour_points){
            chooseRandomColor(&r, &g, &b);
            data->material_points->diffuseColor.setValue(r, g, b);
        }
        if (colour_edges){
            chooseRandomColor(&r, &g, &b);
            data->material_edges->diffuseColor.setValue(r, g, b);
        }
        if (colour_faces){
            chooseRandomColor(&r, &g, &b);
            data->material_faces->diffuseColor.setValue(r, g, b);
        }
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

