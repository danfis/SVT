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

#include <string.h>

#include "obj.h"
#include "utils.h"

/** POLYFACE **/
svt_polyface_t *svtPolyfaceNew(void)
{
    svt_polyface_t *pf;

    pf = ALLOC(svt_polyface_t);

    pf->points = ALLOC_ARR(int, 10);
    pf->points_len = 0;
    pf->points_alloc = 10;

    return pf;
}

void svtPolyfaceDelete(svt_polyface_t *pf)
{
    if (pf->points != NULL)
        free(pf->points);
    free(pf);
}

void svtPolyfaceAddPoint(svt_polyface_t *pf, int pointpos)
{
    if (pf->points_len >= pf->points_alloc){
        pf->points_alloc *= 2;
        pf->points = REALLOC_ARR(int, pf->points, pf->points_alloc);
    }

    pf->points[pf->points_len] = pointpos;
    pf->points_len++;
}

size_t svtPolyfaceNumPoints(const svt_polyface_t *pf)
{
    return pf->points_len;
}

const int *svtPolyfacePoints(const svt_polyface_t *pf, size_t *len)
{
    *len = pf->points_len;
    return (const int *)pf->points;
}
/** POLYFACE END **/



svt_obj_t *svtObjNew()
{
    svt_obj_t *obj = ALLOC(svt_obj_t);

    obj->points = NULL;
    obj->points_len = 0;
    obj->points_alloc = 0;

    obj->edges = NULL;
    obj->edges_len = 0;
    obj->edges_alloc = 0;

    obj->faces = NULL;
    obj->faces_len = 0;
    obj->faces_alloc = 0;

    obj->polyfaces = NULL;
    obj->polyfaces_len = 0;
    obj->polyfaces_alloc = 0;

    obj->name = NULL;

    obj->point_color = obj->edge_color = obj->face_color = NULL;
    obj->points_off = obj->edges_off = obj->faces_off = -1;
    obj->point_size = -1.f;

    obj->next = NULL;

    return obj;
}

svt_obj_t *svtObjDelete(svt_obj_t *obj)
{
    int i;
    svt_obj_t *next;

    next = obj->next;

    if (obj->points != NULL)
        free(obj->points);
    if (obj->edges != NULL)
        free(obj->edges);
    if (obj->faces != NULL)
        free(obj->faces);
    if (obj->name != NULL)
        free(obj->name);
    if (obj->point_color != NULL)
        free(obj->point_color);
    if (obj->edge_color != NULL)
        free(obj->edge_color);
    if (obj->face_color != NULL)
        free(obj->face_color);

    for (i=0; i < obj->polyfaces_len; i++){
        svtPolyfaceDelete(obj->polyfaces[i]);
    }
    free(obj->polyfaces);

    free(obj);

    return next;
}

void svtObjPush(svt_obj_t *obj, svt_obj_t **head, svt_obj_t **tail)
{
    obj->next = NULL;
    if (*head == NULL || *tail == NULL){
        *head = *tail = obj;
    }else{
        (*tail)->next = obj;
        *tail = obj;
    }
}

int svtObjAddPoint(svt_obj_t *obj, float x, float y, float z)
{
    if (obj->points_len >= obj->points_alloc){
        obj->points_alloc += SVT_OBJ_ALLOC_PORTION;
        obj->points = REALLOC_ARR(svt_point_t, obj->points, obj->points_alloc);
    }
    obj->points[obj->points_len][0] = x;
    obj->points[obj->points_len][1] = y;
    obj->points[obj->points_len][2] = z;
    return obj->points_len++;
}

void svtObjAddEdge(svt_obj_t *obj, int a, int b)
{
    if (obj->edges_len >= obj->edges_alloc){
        obj->edges_alloc += SVT_OBJ_ALLOC_PORTION;
        obj->edges = REALLOC_ARR(svt_edge_t, obj->edges, obj->edges_alloc);
    }
    obj->edges[obj->edges_len][0] = a;
    obj->edges[obj->edges_len][1] = b;
    obj->edges_len++;
}

void svtObjAddFace(svt_obj_t *obj, int a, int b, int c)
{
    if (obj->faces_len >= obj->faces_alloc){
        obj->faces_alloc += SVT_OBJ_ALLOC_PORTION;
        obj->faces = REALLOC_ARR(svt_face_t, obj->faces, obj->faces_alloc);
    }
    obj->faces[obj->faces_len][0] = a;
    obj->faces[obj->faces_len][1] = b;
    obj->faces[obj->faces_len][2] = c;
    obj->faces_len++;
}

void svtObjAddPolyface(svt_obj_t *obj, svt_polyface_t *pf)
{
    if (obj->polyfaces_len >= obj->polyfaces_alloc){
        obj->polyfaces_alloc += SVT_OBJ_ALLOC_PORTION;
        obj->polyfaces = REALLOC_ARR(svt_polyface_t *, obj->polyfaces,
                                     obj->polyfaces_alloc);
    }

    obj->polyfaces[obj->polyfaces_len] = pf;
    obj->polyfaces_len++;
}

void svtObjSetName(svt_obj_t *obj, const char *name)
{
    int len = strlen(name);

    if (obj->name == NULL){
        obj->name = ALLOC_ARR(char, len);
        obj->name_alloc = len;
    }

    if (obj->name_alloc > len){
        strncpy(obj->name, name, len);
        obj->name[len] = 0;
    }else{
        obj->name = REALLOC_ARR(char, obj->name, len + 1);
        obj->name_alloc = len + 1;
        strncpy(obj->name, name, len);
        obj->name[len] = 0;
    }
}

void svtObjTruncate(svt_obj_t *obj)
{
    obj->points = REALLOC_ARR(svt_point_t, obj->points, obj->points_len);
    obj->points_alloc = obj->points_len;

    obj->edges = REALLOC_ARR(svt_edge_t, obj->edges, obj->edges_len);
    obj->edges_alloc = obj->edges_len;

    obj->faces = REALLOC_ARR(svt_face_t, obj->faces, obj->faces_len);
    obj->faces_alloc = obj->faces_len;
}

const svt_point_t *svtObjPoints(svt_obj_t *obj, int *len)
{
    *len = obj->points_len;
    return (const svt_point_t *)obj->points;
}

const svt_edge_t *svtObjEdges(svt_obj_t *obj, int *len)
{
    *len = obj->edges_len;
    return (const svt_edge_t *)obj->edges;
}

const svt_face_t *svtObjFaces(svt_obj_t *obj, int *len)
{
    *len = obj->faces_len;
    return (const svt_face_t *)obj->faces;
}

const svt_polyface_t **svtObjPolyfaces(svt_obj_t *obj, int *len)
{
    *len = obj->polyfaces_len;
    return (const svt_polyface_t **)obj->polyfaces;
}

const char *svtObjName(svt_obj_t *obj)
{
    return obj->name;
}

void svtObjTransformPoints(svt_obj_t *obj, float m[9])
{
    int i;
    float v[3];

    for (i=0; i < obj->points_len; i++){
        v[0] = (obj->points[i][0] * m[0]) +
               (obj->points[i][1] * m[1]) +
               m[2];
        v[1] = (obj->points[i][0] * m[3]) +
               (obj->points[i][1] * m[4]) +
               m[5];
        v[2] = (obj->points[i][0] * m[6]) +
               (obj->points[i][1] * m[7]) +
               m[8];

        v[0] /= v[2];
        v[1] /= v[2];

        obj->points[i][0] = v[0];
        obj->points[i][1] = v[1];
    }
}

void svtObjSetPointColor(svt_obj_t *o, float r, float g, float b)
{
    if (o->point_color == NULL)
        o->point_color = ALLOC_ARR(float, 3);

    o->point_color[0] = r;
    o->point_color[1] = g;
    o->point_color[2] = b;
}

void svtObjSetEdgeColor(svt_obj_t *o, float r, float g, float b)
{
    if (o->edge_color == NULL)
        o->edge_color = ALLOC_ARR(float, 3);

    o->edge_color[0] = r;
    o->edge_color[1] = g;
    o->edge_color[2] = b;
}

void svtObjSetFaceColor(svt_obj_t *o, float r, float g, float b)
{
    if (o->face_color == NULL)
        o->face_color = ALLOC_ARR(float, 3);

    o->face_color[0] = r;
    o->face_color[1] = g;
    o->face_color[2] = b;
}

void svtObjSetPointSize(svt_obj_t *o, float s)
{
    o->point_size = s;
}

void svtObjSetPointsOff(svt_obj_t *o, int off)
{
    o->points_off = off;
}
void svtObjSetEdgesOff(svt_obj_t *o, int off)
{
    o->edges_off = off;
}
void svtObjSetFacesOff(svt_obj_t *o, int off)
{
    o->faces_off = off;
}
