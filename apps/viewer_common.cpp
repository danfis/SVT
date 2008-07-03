#ifndef _VIEWER_COMMON_CPP_
#define _VIEWER_COMMON_CPP_

#include "parse_func.h"

static void usage(int argc, char *argv[], const char *oprtstr = 0);

char **args;
int num_args;

#ifdef VIEWER
/**
 * Indicates if some these elements should be coloured
 */
bool colour_points = false;
bool colour_edges = false;
bool colour_faces = false;
#endif /* VIEWER */

enum Options {
    HELP = 100,
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
#ifdef VIEWER
    COLOUR_POINTS,
    COLOUR_EDGES,
    COLOUR_FACES,
#endif /* VIEWER */
    OPTIONS_END
};

static struct option options[] = {
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
#ifdef VIEWER
    { "colour-points", no_argument, NULL, COLOUR_POINTS },
    { "colour-edges",  no_argument, NULL, COLOUR_EDGES },
    { "colour-faces",  no_argument, NULL, COLOUR_FACES },
#endif /* VIEWER */
    { NULL, 0, NULL, 0 }
};

static void usage(int argc, char *argv[], const char *optstr)
{
    if (optstr != 0){
        cout << optstr << endl;
    }

    cout << "Usage: " << argv[0] << " [ Options ] <file.txt" << endl;
    cout << "          or" << endl;
    cout << "       " << argv[0] << " [ Options ] file1.txt file2.txt ..." << endl;
    cout << endl;
    cout << "Options:" << endl;
    cout << "  --help                      Show this help." << endl;
    cout << "  --all-off                   Turn off all objects." << endl;
    cout << "  --points-off                Turn off all points." << endl;
    cout << "  --edges-off                 Turn off all edges." << endl;
    cout << "  --faces-off                 Turn off all faces." << endl;
    cout << endl;
    cout << "  --point-size         float  Set size of points to specified value." << endl;
    cout << "  --edge-width         float  Set width of edges to specified value." << endl;
    cout << endl;
    cout << "  --point-color-red    float  Set color of points to specified value." << endl;
    cout << "  --point-color-green  float  Value must be between 0 and 1." << endl;
    cout << "  --point-color-blue   float" << endl;
    cout << "  --edge-color-red     float  Set color of edges to specified value." << endl;
    cout << "  --edge-color-green   float  Value must be between 0 and 1." << endl;
    cout << "  --edge-color-blue    float" << endl;
    cout << "  --face-color-red     float  Set color of faces to specified value." << endl;
    cout << "  --face-color-green   float  Value must be between 0 and 1." << endl;
    cout << "  --face-color-blue    float" << endl;
#ifdef VIEWER
    cout << endl;
    cout << "  --colour-points             Colour points from different objects by different color." << endl;
    cout << "  --colour-edges              Colour edges from different objects by different color." << endl;
    cout << "  --colour-faces              Colour faces from different objects by different color." << endl;
#endif /* VIEWER */
    exit(-1);
}

#endif
