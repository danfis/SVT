#ifndef _LEXER_H_
#define _LEXER_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Defined tokens */
#define T_INT_NUM 258
#define T_FLT_NUM 259
#define T_POINTS 260
#define T_EDGES 261
#define T_FACES 262
#define T_DELIM 263
#define T_ERROR 264
#define T_POINTS2D 265
#define T_NAME 267

#define YY_BUFSIZE 1000

struct _svt_yylval_t {
    float flt_num;
    int int_num;
    int lineno;
    char c;
    char buffer[YY_BUFSIZE];
};
typedef struct _svt_yylval_t svt_yylval_t;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
