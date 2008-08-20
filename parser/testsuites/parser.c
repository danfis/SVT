#include "cu.h"
#include "../parser.h"

static svt_parser_t *parser;

TEST(ParserSetUp)
{
    parser = svtParserNew();
}

TEST(ParserTearDown)
{
    svtParserDelete(parser);
}


TEST(ParserParse)
{
    FILE *fin = fopen("obj.txt", "r");
    svt_obj_t *objs;
    int len, i;
    const svt_point_t *points;
    const svt_edge_t *edges;
    const svt_face_t *faces;

    svtParserSetInput(parser, fin);
    svtParserParse(parser);

    assertEquals(svtParserNumObjs(parser), 2);

    objs = svtParserObjs(parser, NULL);
    points = svtObjPoints(objs, &len);
    printf("Points:\n");
    for (i=0; i < len; i++){
        printf("%f %f %f\n", points[i][0], points[i][1], points[i][2]);
    }

    edges = svtObjEdges(objs, &len);
    printf("Edges:\n");
    for (i=0; i < len; i++){
        printf("%d %d\n", edges[i][0], edges[i][1]);
    }

    faces = svtObjFaces(objs, &len);
    printf("Faces:\n");
    for (i=0; i < len; i++){
        printf("%d %d %d\n", faces[i][0], faces[i][1], faces[i][2]);
    }

    printf("==========\n");

    objs = svtObjNext(objs);
    points = svtObjPoints(objs, &len);
    printf("Points:\n");
    for (i=0; i < len; i++){
        printf("%f %f %f\n", points[i][0], points[i][1], points[i][2]);
    }

    edges = svtObjEdges(objs, &len);
    printf("Edges:\n");
    for (i=0; i < len; i++){
        printf("%d %d\n", edges[i][0], edges[i][1]);
    }

    faces = svtObjFaces(objs, &len);
    printf("Faces:\n");
    for (i=0; i < len; i++){
        printf("%d %d %d\n", faces[i][0], faces[i][1], faces[i][2]);
    }

    fclose(fin);
}
