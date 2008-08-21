#include "cu.h"
#include "../obj.h"
#include <stdio.h>

static svt_obj_t *head, *tail;

TEST(ObjSetUp)
{
    head = tail = NULL;
    svtObjPush(svtObjNew(), &head, &tail);
    svtObjPush(svtObjNew(), &head, &tail);
}

TEST(ObjTearDown)
{
    svt_obj_t *obj;

    svtObjTruncate(tail);

    obj = svtObjDelete(head);
    assertEquals(obj, tail);

    obj = svtObjDelete(obj);
    assertEquals(obj, NULL);
}


TEST(ObjAddElements)
{
    const svt_point_t *points = NULL;
    const svt_edge_t *edges = NULL;
    const svt_face_t *faces = NULL;
    int num;

    svtObjAddPoint(head, 1., 2., 3.);
    svtObjAddPoint(head, 0., 1., 2.);

    points = svtObjPoints(head, &num);
    assertEquals(num, 2);
    assertEquals(points[0][0], 1.);
    assertEquals(points[0][1], 2.);
    assertEquals(points[0][2], 3.);
    assertEquals(points[1][0], 0.);
    assertEquals(points[1][1], 1.);
    assertEquals(points[1][2], 2.);

    points = svtObjPoints(tail, &num);
    assertEquals(num, 0);
    assertEquals(points, NULL);


    svtObjAddEdge(tail, 0, 1);
    svtObjAddEdge(tail, 1, 2);

    edges = svtObjEdges(head, &num);
    assertEquals(num, 0);
    assertEquals(edges, NULL);

    edges = svtObjEdges(tail, &num);
    assertEquals(num, 2);
    assertEquals(edges[0][0], 0);
    assertEquals(edges[0][1], 1);
    assertEquals(edges[1][0], 1);
    assertEquals(edges[1][1], 2);


    svtObjAddFace(head, 0, 1, 2);
    svtObjAddFace(head, 10, 20, 30);

    faces = svtObjFaces(head, &num);
    assertEquals(num, 2);
    assertEquals(faces[0][0], 0);
    assertEquals(faces[0][1], 1);
    assertEquals(faces[0][2], 2);
    assertEquals(faces[1][0], 10);
    assertEquals(faces[1][1], 20);
    assertEquals(faces[1][2], 30);

    faces = svtObjFaces(tail, &num);
    assertEquals(num, 0);
    assertEquals(faces, NULL);
}
