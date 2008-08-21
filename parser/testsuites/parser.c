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

static void dumpObj(svt_obj_t *obj)
{
    const svt_point_t *points;
    const svt_edge_t *edges;
    const svt_face_t *faces;
    int len, i;

    points = svtObjPoints(obj, &len);
    printf("Points:\n");
    for (i=0; i < len; i++){
        printf("%f %f %f\n", points[i][0], points[i][1], points[i][2]);
    }

    edges = svtObjEdges(obj, &len);
    printf("Edges:\n");
    for (i=0; i < len; i++){
        printf("%d %d\n", edges[i][0], edges[i][1]);
    }

    faces = svtObjFaces(obj, &len);
    printf("Faces:\n");
    for (i=0; i < len; i++){
        printf("%d %d %d\n", faces[i][0], faces[i][1], faces[i][2]);
    }

    printf("==========\n");
}

TEST(ParserParse)
{
    FILE *fin = fopen("obj.txt", "r");
    svt_obj_t *objs;
    int len;

    svtParserSetInput(parser, fin);
    svtParserParse(parser);

    assertEquals(svtParserNumObjs(parser), 2);

    objs = svtParserObjs(parser, &len);
    assertNotEquals(objs, NULL);
    assertEquals(len, 2);

    printf("# obj.txt:\n");
    while (objs != NULL){
        dumpObj(objs);
        objs = svtObjNext(objs);
    }

    fclose(fin);

    fin = fopen("obj2.txt", "r");
    svtParserSetInput(parser, fin);
    svtParserParse(parser);

    assertEquals(svtParserNumObjs(parser), 7);

    objs = svtParserObjsSteal(parser, &len);
    assertNotEquals(objs, NULL);
    assertEquals(len, 7);

    printf("\n\n# obj.tx + obj2.txt:\n");
    while (objs != NULL){
        dumpObj(objs);

        objs = svtObjDelete(objs);
    }

    fclose(fin);
}

TEST(ParserParseHunk)
{
    FILE *fin;
    svt_obj_t *objs;
    int len;

    printf("\n++++++++++++++++\n\n");
    printf("# ParseHunks:\n");

    fin = fopen("obj.txt", "r");
    
    svtParserSetInput(parser, fin);
    svtParserParseBegin(parser);

    len = svtParserParseHunk(parser, 4);
    assertEquals(len, 2);
    assertEquals(len, svtParserNumObjs(parser));

    printf("# obj.txt:\n");
    objs = svtParserObjsSteal(parser, &len);
    assertNotEquals(objs, NULL);
    assertEquals(len, 2);
    while (objs != NULL){
        dumpObj(objs);
        objs = svtObjDelete(objs);
    }

    svtParserParseEnd(parser);

    fclose(fin);


    fin = fopen("obj2.txt", "r");
    
    svtParserSetInput(parser, fin);
    svtParserParseBegin(parser);

    len = svtParserParseHunk(parser, 3);
    assertEquals(len, 3);
    assertEquals(len, svtParserNumObjs(parser));

    printf("# obj2.txt (0, 1, 2):\n");
    objs = svtParserObjsSteal(parser, &len);
    assertNotEquals(objs, NULL);
    assertEquals(len, 3);
    while (objs != NULL){
        dumpObj(objs);
        objs = svtObjDelete(objs);
    }

    len = svtParserParseHunk(parser, 3);
    assertEquals(len, 2);
    assertEquals(len, svtParserNumObjs(parser));

    printf("# obj2.txt (3, 4):\n");
    objs = svtParserObjsSteal(parser, &len);
    assertNotEquals(objs, NULL);
    assertEquals(len, 2);
    while (objs != NULL){
        dumpObj(objs);
        objs = svtObjDelete(objs);
    }

    svtParserParseEnd(parser);

    fclose(fin);
}
