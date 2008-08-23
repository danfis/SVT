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

#define TO_SVG

#include <iostream>
#include <cstdlib>
#include <float.h>
using namespace std;

#include "common.hpp"
#include "settings.hpp"
#include "parser/parser.h"
#include "common/msg.hpp"

static void toSvg(svt_obj_t *objs);
static void printPoint(const svt_point_t point,
                       float colorf[3],
                       ostream &);
static void printEdge(const svt_point_t from,
                      const svt_point_t to,
                      float colorf[3],
                      ostream &);
static void printFace(const svt_point_t p1,
                      const svt_point_t p2,
                      const svt_point_t p3,
                      float colorf[3],
                      ostream &);

static void size(svt_obj_t *objs,
                 int *width, int *height, float view_box[4]);


svt_parser_t *parser;

int main(int argc, char *argv[])
{
    char **args;
    int num_args;
    int len;
    svt_obj_t *objs;

    args = processOptions(argc, argv, &num_args);

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
            svtParserParse(parser);

            fclose(fin);
        }
    }else{
        svtParserParse(parser);
    }

    objs = svtParserObjs(parser, &len);
    if (len > 0)
        toSvg(objs);


    svtParserDelete(parser);
    return 0;
}

void toSvg(svt_obj_t *objs)
{
    ostream &out = cout;
    const svt_point_t *points;
    const svt_edge_t *edges;
    const svt_face_t *faces;
    int points_len, edges_len, faces_len;
    float colorf[3];
    float *col;
    char color[7];
    int width, height;
    float view_box[4];

    size(objs, &width, &height, view_box);

    out.precision(Settings::svg_precision);
    out.setf(ios::fixed);

    // header:
    out << "<?xml version=\"1.0\" standalone=\"no\"?>" << endl;
    out << "<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\" " << endl
        << "    \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">"
        << endl;

    out << "<svg"
        << " width=\"" << width << "px\""
        << " height=\"" << height << "px\""
        << " viewBox=\"" << view_box[0] << " " << view_box[1] << " "
                         << view_box[2] << " " << view_box[3] << "\""
        << endl
        << "       xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">" << endl;

    // background:
    colorToHex(color, Settings::svg_bg_color);
    out << "<rect"
        << " x=\"" << view_box[0] << "\""
        << " y=\"" << view_box[1] << "\""
        << " width=\"" << view_box[2] << "\""
        << " height=\"" << view_box[3] << "\""
        << " fill=\"#" << color << "\""
        << " stroke=\"none\" />" << endl << endl;


    // body:
    for (int i=0; objs != NULL; i++){
        points = svtObjPoints(objs, &points_len);
        edges = svtObjEdges(objs, &edges_len);
        faces = svtObjFaces(objs, &faces_len);

        out << "<g id=\"" << i << "\">" << endl;

        // FACES:
        if (!Settings::faces_off){
            col = Settings::face_color;
            if (Settings::colour_faces){
                chooseRandomColor(colorf, colorf + 1, colorf + 2);
                col = colorf;
            }

            for (int i=0; i < faces_len; i++){
                if (faces[i][0] < points_len
                    && faces[i][1] < points_len
                    && faces[i][2] < points_len){
                    printFace(points[faces[i][0]],
                              points[faces[i][1]],
                              points[faces[i][2]],
                              col,
                              cout);
                }
            }
        }

        // EDGES:
        if (!Settings::edges_off){
            col = Settings::edge_color;
            if (Settings::colour_edges){
                chooseRandomColor(colorf, colorf + 1, colorf + 2);
                col = colorf;
            }

            for (int i=0; i < edges_len; i++){
                if (edges[i][0] < points_len && edges[i][1] < points_len){
                    printEdge(points[edges[i][0]],
                              points[edges[i][1]],
                              col,
                              cout);
                }
            }
        }

        // POINTS:
        if (!Settings::points_off){
            col = Settings::point_color;
            if (Settings::colour_points){
                chooseRandomColor(colorf, colorf + 1, colorf + 2);
                col = colorf;
            }

            for (int i=0; i < points_len; i++){
                printPoint(points[i], col, out);
            }
        }

        out << "</g>" << endl;
        objs = svtObjNext(objs);
    }

    // footer:
    out << "</svg>" << endl;
}

void printPoint(const svt_point_t point,
                float colorf[3],
                ostream &out)
{
    float x, y, move;
    char color[7];

    x = point[0];
    y = point[1];

    move = Settings::point_size / 2;
    x -= move;
    y -= move;

    colorToHex(color, colorf);

    out << "\t<rect x=\"" << x << "\" y=\"" << y << "\""
        << " width=\"" << Settings::point_size << "\""
        << " height=\"" << Settings::point_size << "\""
        << " fill=\"#" << color << "\""
        << " stroke=\"none\" />" << endl;

}

void printEdge(const svt_point_t from,
               const svt_point_t to,
               float colorf[3],
               ostream &out)
{
    float x1, y1, x2, y2;
    char color[7];

    x1 = from[0];
    y1 = from[1];
    x2 = to[0];
    y2 = to[1];

    colorToHex(color, colorf);

    out << "\t<line x1=\"" << x1 << "\" y1=\"" << y1 << "\""
        << " x2=\"" << x2 << "\" y2=\"" << y2 << "\""
        << " stroke=\"#" << color << "\""
        << " stroke-width=\"" << Settings::edge_width << "\" />"
        << endl;
}


void printFace(const svt_point_t p1,
               const svt_point_t p2,
               const svt_point_t p3,
               float colorf[3],
               ostream &out)
{
    float x1, y1, x2, y2, x3, y3;
    char color[7];

    x1 = p1[0];
    y1 = p1[1];
    x2 = p2[0];
    y2 = p2[1];
    x3 = p3[0];
    y3 = p3[1];

    colorToHex(color, colorf);

    out << "\t<polygon"
        << " points=\"" << x1 << "," << y1 << " "
                        << x2 << "," << y2 << " "
                        << x3 << "," << y3 << "\""
        << " fill=\"#" << color << "\""
        << " stroke=\"none\" />"
        << endl;
}



void size(svt_obj_t *objs,
          int *width, int *height, float view_box[4])
{
    if (Settings::svg_view_box_enabled){
        view_box[0] = Settings::svg_view_box[0];
        view_box[1] = Settings::svg_view_box[1];
        view_box[2] = Settings::svg_view_box[2];
        view_box[3] = Settings::svg_view_box[3];
    }else{
        // compute viewbox from points:
        const svt_point_t *points;
        int len;
        float bottomleft[2], topright[2];

        bottomleft[0] = bottomleft[1] = 1000000.;
        topright[0] = topright[1] = -1000000.;
        while (objs != NULL){
            points = svtObjPoints(objs, &len);

            for (int i=0; i < len; i++){
                if (points[i][0] < bottomleft[0])
                    bottomleft[0] = points[i][0];
                if (points[i][0] > topright[0])
                    topright[0] = points[i][0];
                if (points[i][1] < bottomleft[1])
                    bottomleft[1] = points[i][1];
                if (points[i][1] > topright[1])
                    topright[1] = points[i][1];
            }

            objs = svtObjNext(objs);
        }

        view_box[0] = bottomleft[0];
        view_box[1] = bottomleft[1];
        view_box[2] = topright[0] - bottomleft[0];
        view_box[3] = topright[1] - bottomleft[1];
    }

    *width = Settings::svg_width;
    *height = (int)(((float)*width / view_box[2]) * view_box[3]);
}
