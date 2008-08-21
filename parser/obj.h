#ifndef _OBJ_H_
#define _OBJ_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef float svt_point_t[3];
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

    char *name;
    int name_alloc;

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
void svtObjSetName(svt_obj_t *, const char *name);

/**
 * Truncate all internaly managed lists to occupy only necessary amount of
 * memory.
 */
void svtObjTruncate(svt_obj_t *);

const svt_point_t *svtObjPoints(svt_obj_t *, int *len);
const svt_edge_t *svtObjEdges(svt_obj_t *, int *len);
const svt_face_t *svtObjFaces(svt_obj_t *, int *len);
const char *svtObjName(svt_obj_t *obj);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
