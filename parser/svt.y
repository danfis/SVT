%{
#include "svt.h"
#include "svt.parser.h"
#include "svt.lex.h"

void yyerror (YYSTYPE *lval, char const *s)
{
    fprintf (stderr, "%s\n", s);
}

%}

%define api.pure
%parse-param {yyscan_t yyscanner}
%lex-param {yyscan_t yyscanner}

%union {
    float f;
    int i;
    char *s;
    char c;
}

%token T_INT T_FLT
%token T_POINTS
%token T_EDGES
%token T_FACES
%token T_POLY
%token T_POLYLINE
%token T_POLYFACE
%token T_POINT_COLOR
%token T_EDGE_COLOR
%token T_FACE_COLOR
%token T_NAME
%token T_DELIM
%token T_EOL
%token T_ERROR

%start start

%%

start: objects
    | T_DELIM objects
;

objects: object
    | object T_DELIM objects
;

object: sections
;

sections: section
    | sections section
;

section: section_points { printf("section_points\n"); }
    | section_edges { printf("section_edges\n"); }
    | section_faces { printf("section_faces\n"); }
;

section_points: T_POINTS points
    | points
;

points: point
    | points point
;
point: T_FLT T_FLT T_EOL
    | T_FLT T_FLT T_FLT T_EOL
;

section_edges: T_EDGES edges
;

edges: edge
    | edges edge
;

edge: T_INT T_INT
    | T_INT T_INT T_EOL


section_faces: T_FACES faces
;


faces: face
    | faces face
;

face: T_INT T_INT T_INT
    | T_INT T_INT T_INT T_EOL

%%
