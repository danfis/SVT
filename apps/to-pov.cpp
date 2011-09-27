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
#include <iomanip>
#include <cstdlib>
#include <float.h>
using namespace std;

#include "common/msg.hpp"
#include "common/settings.hpp"
#include "common/functions.hpp"
#include "parser/parser.h"
#include "parser/obj.h"

using SVT::Common::settings;
using SVT::Common::colorToHex;
using SVT::Common::chooseRandomColor;

static void toPov(svt_obj_t *objs);
static void printPoint(const svt_point_t point,
                       ostream &);
static void printEdge(const svt_point_t from,
                      const svt_point_t to,
                      ostream &);
static void printFace(const svt_point_t p1,
                      const svt_point_t p2,
                      const svt_point_t p3,
                      ostream &);

int mainToPov(int argc, char *argv[], svt_parser_t *parser)
{
    int len;
    svt_obj_t *o;

    o = svtParserObjs(parser, &len);
    if (len > 0)
        toPov(o);

    return 0;
}

static void objToPov(int i, svt_obj_t *o, ostream &out)
{
    const svt_point_t *points;
    const svt_edge_t *edges;
    const svt_face_t *faces;
    const float *col;
    float colorf[3];
    int points_len, edges_len, faces_len;

    points = svtObjPoints(o, &points_len);
    edges = svtObjEdges(o, &edges_len);
    faces = svtObjFaces(o, &faces_len);

    if (!settings.faces_off && svtObjFacesOff(o) != 1 && faces_len > 0){
        col = settings.face_color;
        if (settings.colour_faces){
            chooseRandomColor(colorf, colorf + 1, colorf + 2);
            col = colorf;
        }else if (svtObjFaceColor(o) != NULL){
            col = svtObjFaceColor(o);
        }

        out << "mesh {" << endl;
        for (int i=0; i < faces_len; i++){
            if (faces[i][0] < points_len
                    && faces[i][1] < points_len
                    && faces[i][2] < points_len){
                printFace(points[faces[i][0]],
                          points[faces[i][1]],
                          points[faces[i][2]],
                          out);
            }
        }

        out << "pigment { color rgb <" << col[0] << ", " << col[1] << ", " << col[2] << "> }" << endl;
        out << "}" << endl;
    }

    if (!settings.edges_off && svtObjEdgesOff(o) != 1 && edges_len > 0){
        col = settings.edge_color;
        if (settings.colour_edges){
            chooseRandomColor(colorf, colorf + 1, colorf + 2);
            col = colorf;
        }else if (svtObjEdgeColor(o) != NULL){
            col = svtObjEdgeColor(o);
        }

        for (int i=0; i < edges_len; i++){
            if (edges[i][0] < points_len && edges[i][1] < points_len){
                printEdge(points[edges[i][0]],
                          points[edges[i][1]],
                          cout);
            }
        }
    }

    if (!settings.points_off && svtObjPointsOff(o) != 1 && points_len > 0){
        col = settings.point_color;
        if (settings.colour_points){
            chooseRandomColor(colorf, colorf + 1, colorf + 2);
            col = colorf;
        }else if (svtObjPointColor(o) != NULL){
            col = svtObjPointColor(o);
        }

        for (int i=0; i < points_len; i++){
            printPoint(points[i], out);
        }
    }
}

void toPov(svt_obj_t *objs)
{
    ostream &out = cout;
    /*
    svt_obj_t *objs2;
    float transform_matrix[9] =
        { 1.f, 0.f, 0.f,
          0.f, -1.f, 0.f,
          0.f, 0.f, 1.f };

    // first transform points to fit to svg coordinate system:
    objs2 = objs;
    while (objs2 != NULL){
        svtObjTransformPoints(objs2, transform_matrix);
        objs2 = svtObjNext(objs2);
    }
    */

    out << "#include \"colors.inc\"" << endl;
	out << "camera {\n";
	out << "\tlocation <6,-6,4>\n";
	out << "\tsky <0,0,1>\n";
	out << "\tlook_at <1,0,3>\n";
	out << "}\n";
	out << "light_source { <20,-5,20> color White }\n";
	out << "light_source { <-20,-5,20> color White }\n";
	out << "light_source { <0,-15,10> color White }\n";
    for (int i=0; objs != NULL; i++, objs = svtObjNext(objs)){
        objToPov(i, objs, out);
    }
}

void printPoint(const svt_point_t point,
                ostream &out)
{
    /* TODO
    float x, y, move;
    char color[7];

    x = point[0];
    y = point[1];

    move = settings.point_size / 2;
    x -= move;
    y -= move;

    colorToHex(color, colorf);

    out << "\t<rect x=\"" << x << "\" y=\"" << y << "\""
        << " width=\"" << settings.point_size << "\""
        << " height=\"" << settings.point_size << "\""
        << " fill=\"#" << color << "\""
        << " stroke=\"none\" />" << endl;
    */
}

void printEdge(const svt_point_t from,
               const svt_point_t to,
               ostream &out)
{
    /* TODO
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
        << " stroke-width=\"" << settings.edge_width << "\" />"
        << endl;
    */
}


void printFace(const svt_point_t p1,
               const svt_point_t p2,
               const svt_point_t p3,
               ostream &out)
{
    out << "triangle { ";
    out << "<" << p1[0] << ", " << p1[2] << ", " << p1[1] << ">, ";
    out << "<" << p2[0] << ", " << p2[2] << ", " << p2[1] << ">, ";
    out << "<" << p3[0] << ", " << p3[2] << ", " << p3[1] << "> ";
    out << " }" << endl;
}
