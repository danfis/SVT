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

#ifndef _SVT_OBJ_H_
#define _SVT_OBJ_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/** TYPES **/
typedef float svt_point_t[3];
typedef int svt_edge_t[2];
typedef int svt_face_t[3];

struct _svt_polyface_t {
    svt_point_t *points;
    size_t points_len;
    size_t points_alloc;
};
typedef struct _svt_polyface_t svt_polyface_t;

svt_polyface_t *svtPolyfaceNew(void);
void svtPolyfaceDelete(svt_polyface_t *);

size_t svtPolyfaceNumPoints(const svt_polyface_t *pf);

const svt_point_t *svtPolyfacePoints(const svt_polyface_t *pf, size_t *len);

void svtPolyfaceAddPoint(svt_polyface_t *pf, float x, float y, float z);
/** TYPES END **/

#ifndef SVT_OBJ_ALLOC_PORTION
# define SVT_OBJ_ALLOC_PORTION 100
#endif


/**
 * Structure representing one graphical object.
 */
struct _svt_obj_t {
    svt_point_t *points;
    int points_len;
    int points_alloc;

    svt_edge_t *edges;
    int edges_len;
    int edges_alloc;

    svt_face_t *faces;
    int faces_len;
    int faces_alloc;

    svt_polyface_t **polyfaces;
    int polyfaces_len;
    int polyfaces_alloc;

    char *name;
    int name_alloc;

    float *point_color, *edge_color, *face_color;

    struct _svt_obj_t *next;
};
typedef struct _svt_obj_t svt_obj_t;

#define svtObjNext(obj) (obj)->next

#define svtObjNumPoints(obj) (obj)->points_len
#define svtObjNumEdges(obj) (obj)->edges_len
#define svtObjNumFaces(obj) (obj)->faces_len


/**
 * Create and initialize new obj structure.
 */
svt_obj_t *svtObjNew();

/**
 * This function free all allocated memory by given obj structure and
 * returns next obj structure in list.
 */
svt_obj_t *svtObjDelete(svt_obj_t *);

/**
 * This function pushes obj to the end of list which is specified by its
 * head and tail. This function also properly set up head and tail, so the
 * common use of this function should be:
 *      svt_obj_t *head, *tail, *obj;
 *      obj = ...
 *      svtObjPush(obj, &head, &tail);
 */
void svtObjPush(svt_obj_t *obj, svt_obj_t **head, svt_obj_t **tail);

/**
 * Add point to object.
 * Return value is position of new point in list
 */
int svtObjAddPoint(svt_obj_t *, float x, float y, float z);
void svtObjAddEdge(svt_obj_t *, int a, int b);
void svtObjAddFace(svt_obj_t *, int a, int b, int c);
void svtObjAddPolyface(svt_obj_t *o, svt_polyface_t *pf);
void svtObjSetName(svt_obj_t *, const char *name);
void svtObjSetPointColor(svt_obj_t *, float r, float g, float b);
void svtObjSetEdgeColor(svt_obj_t *, float r, float g, float b);
void svtObjSetFaceColor(svt_obj_t *, float r, float g, float b);

/**
 * Truncate all internaly managed lists to occupy only necessary amount of
 * memory.
 */
void svtObjTruncate(svt_obj_t *);

const svt_point_t *svtObjPoints(svt_obj_t *, int *len);
const svt_edge_t *svtObjEdges(svt_obj_t *, int *len);
const svt_face_t *svtObjFaces(svt_obj_t *, int *len);
const svt_polyface_t **svtObjPolyFaces(svt_obj_t *, int *len);
const char *svtObjName(svt_obj_t *obj);

#define svtObjPointColor(o) ((const float *)(o)->point_color)
#define svtObjEdgeColor(o) ((const float *)(o)->edge_color)
#define svtObjFaceColor(o) ((const float *)(o)->face_color)

/**
 * Transform all points from obj using given transform matrix.
 * Transform matrix is indexed by lines.
 */
void svtObjTransformPoints(svt_obj_t *, float transform_matrix[9]);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
