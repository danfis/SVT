%{
#include <stdio.h>
%}

%union {
    int int_num;
    float flt_num;
}

%token <int_num> T_INT_NUM
%token <flt_num> T_FLT_NUM
%token T_POINTS
%token T_EDGES
%token T_FACES
%token T_DELIM
%token T_ERROR

%start data
%%

data: T_DELIM
    | T_DELIM data
    | section
    | section data

section: section_points
    | section_edges
    | section_faces

section_points: T_POINTS
    | T_POINTS section_points_numbers
section_points_numbers: T_FLT_NUM T_FLT_NUM T_FLT_NUM { printf("[%f, %f, %f]\n", $1, $2, $3); }
    | T_FLT_NUM T_FLT_NUM T_FLT_NUM section_points_numbers { printf("[%f, %f, %f]\n", $1, $2, $3); }

section_edges: T_EDGES
    | T_EDGES section_edges_numbers
section_edges_numbers: T_INT_NUM T_INT_NUM
    | T_INT_NUM T_INT_NUM section_edges_numbers

section_faces: T_FACES
    | T_FACES section_faces_numbers
section_faces_numbers: T_INT_NUM T_INT_NUM T_INT_NUM
    | T_INT_NUM T_INT_NUM T_INT_NUM section_faces_numbers

%%

int main()
{
    yyparse();
}

int yyerror(char *s)
{
    fprintf(stderr, "ERROR: %s\n", s);
    return 0;
}

#include "lex.yy.c"
