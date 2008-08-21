#include <string.h>

#include "obj.h"
#include "utils.h"

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

    obj->name = NULL;

    obj->next = NULL;

    return obj;
}

svt_obj_t *svtObjDelete(svt_obj_t *obj)
{
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

const char *svtObjName(svt_obj_t *obj)
{
    return obj->name;
}
