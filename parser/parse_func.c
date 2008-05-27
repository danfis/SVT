#include <math.h>
#include "parse_func.h"

int parseFloat(const char *str, float *val)
{
    char c = *str;
    float fract;
    float mult;
    int negative = 0;
    int num;

    *val = 0.0;

    /* process sign */
    if (c == '-'){
        negative = 1;
        c = *++str;
    }else if (c == '+')
        c = *++str;

    /* process initial digits */
    while (c != 0){
        /* skip to next part */
        if (c == '.' || c == 'e' || c == 'E')
            break;

        /* not number -> invalid string */
        if (c < 48 || c > 57)
            return -1;

        *val = *val * 10 + c - 48;
        c = *++str;
    }

    /* process decimal part */
    if (c == '.'){
        c = *++str;
        mult = 0.1;
        fract = 0.f;
        while (c != 0){
            /* skip to next part */
            if (c == 'e' || c == 'E')
                break;

            /* no digit -> invalid string */
            if (c < 48 || c > 57)
                return -1;

            fract = fract + mult*(c - 48);
            mult *= 0.1;
            c = *++str;
        }
        *val += fract;
    }

    /* apply negative flag */
    if (negative)
        *val = *val * -1.f;
    

    /* process exponent part */
    if (c == 'e' || c == 'E'){
        c = *++str;
        negative = 0;
        num = 0;

        if (c == '-'){
            negative = 1;
            c = *++str;
        }else if (c == '+')
            c = *++str;

        while (c != 0){
            if (c < 48 || c > 57)
                return -1;

            num = num * 10 + (c - 48);
            c = *++str;
        }

        if (negative)
            num *= -1;

        if (num != 0){
            mult = powf(10.f, num);
            *val *= mult;
        }
    }

    return 0;
}


int parseInt(const char *str, int *val)
{
    char c = *str;

    *val = 0;

    while (c != 0){
        if (c < 48 || c > 57)
            return -1;
        *val = *val * 10 + (c - 48);
        c = *++str;
    }

    return 0;
}
