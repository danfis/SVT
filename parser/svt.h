#ifndef _SVT_SVT_H_
#define _SVT_SVT_H_

#define YY_BUFSIZE 1000

struct _svt_yylval_t {
    float flt_num;
    int int_num;
    int lineno;
    char c;
    char buffer[YY_BUFSIZE];
};
typedef struct _svt_yylval_t svt_yylval_t;

#endif
