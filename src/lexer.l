%{
#include <stdlib.h>
#include "y.tab.h"
%}

DIGIT [0-9]
NONZERO [1-9]
ZERO "0"
MINUS "-"
DOT "."
WHITESPACE [ \t\n]
COMMENT "#"
DELIM [-=+]

%s points edges faces
%%
<points>{MINUS}?{NONZERO}{DIGIT}*{DOT}?{DIGIT}* {
    yylval.flt_num = atof(yytext);
    printf("T_FLT_NUM: detected float: '%s' -> %f\n", yytext, atof(yytext));
    return T_FLT_NUM;
                                        }
<points>{MINUS}?{ZERO}{DOT}? {
    yylval.flt_num = atof(yytext);
    printf("T_FLT_NUM: detected float: '%s' -> %f\n", yytext, atof(yytext));
    return T_FLT_NUM;
                     }
<points>{MINUS}?{ZERO}{DOT}{DIGIT}* {
    yylval.flt_num = atof(yytext);
    printf("T_FLT_NUM: detected float: '%s' -> %f\n", yytext, atof(yytext));
    return T_FLT_NUM;
                            }

<edges,faces>{NONZERO}{DIGIT}* {
    yylval.int_num = atoi(yytext);
    printf("T_INT_NUM: detected num '%s' -> %d\n", yytext, atoi(yytext));
    return T_INT_NUM;
}
<edges,faces>{ZERO} {
    yylval.int_num = atoi(yytext);
    printf("T_INT_NUM: detected zero\n");
    return T_INT_NUM;
}

{WHITESPACE}+ {
    printf("detected whitespace: '%s'\n", yytext);
              }

{COMMENT}[^\n]*\n {
    printf("detected comment: '%s'\n", yytext);
                }

[Pp][Oo][Ii][Nn][Tt][Ss]: {
    BEGIN(points);
    printf("T_POINTS: detected Points delimiter: '%s'\n", yytext);
    return T_POINTS;
                            }
[Ee][Dd][Gg][Ee][Ss]: {
    BEGIN(edges);
    printf("T_EDGES: detected Edges delimiter: '%s'\n", yytext);
    return T_EDGES;
                      }
[Ff][Aa][Cc][Ee][Ss]: {
    BEGIN(faces);
    printf("T_FACES: detected Faces delimiter: '%s'\n", yytext);
    return T_FACES;
                      }

{DELIM}+\n {
    BEGIN(INITIAL);
    printf("T_DELIM: detected delimiter: '%s'\n", yytext);
    return T_DELIM;
}
. {
    printf("T_ERROR: Unknown input: '%s'!\n", yytext);
    return T_ERROR;
  }
%%

