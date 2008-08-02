#ifndef _OBJ_H_
#define _OBJ_H_

typedef double svt_point_t[3];
typedef int svt_edge_t[2];
typedef int svt_face_t[3];


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

    struct _svt_obj_t *next;
};
typedef struct _svt_obj_t svt_obj_t;

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
 * This function pushes obj on top of head, so obj will become head.
 */
void svtObjPush(svt_obj_t *obj, svt_obj_t *head);

void svtObjAddPoint(svt_obj_t *, double x, double y, double z);
void svtObjAddEdge(svt_obj_t *, int a, int b);
void svtObjAddFace(svt_obj_t *, int a, int b, int c);

/**
 * Truncate all internaly managed lists to occupy only necessary amount of
 * memory.
 */
void svtObjTruncate(svt_obj_t *);

const svt_point_t *svtObjPoints(svt_obj_t *, int *len);
const svt_edge_t *svtObjEdges(svt_obj_t *, int *len);
const svt_face_t *svtObjFaces(svt_obj_t *, int *len);
#endif
