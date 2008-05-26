#ifndef _PARSER_LEXER_COMMON_H_
#define _PARSER_LEXER_COMMON_H_

/* Defined tokens */
#define T_INT_NUM 258
#define T_FLT_NUM 259
#define T_POINTS 260
#define T_EDGES 261
#define T_FACES 262
#define T_DELIM 263
#define T_ERROR 264

typedef struct _yylval_t {
    float flt_num;
    int int_num;
    int lineno;
    char c;
} yylval_t;

extern yylval_t yylval;

extern FILE *yyin;

#endif
