/**
 * SVT
 * ----------
 * Copyright (c)2007,2008,2009 Daniel Fiser <danfis (at) danfis (dot) cz>
 *
 *
 * This file is part of SVT
 *
 * SVT is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * SVT is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with SVT. If not, see <http://www.gnu.org/licenses/>.
 */

#include <cstdlib>
#include <cstdio>

#include "functions.hpp"
#include "msg.hpp"
#include "../parser/parse_func.h"

namespace SVT {

namespace Common {

bool parseFloat(const char *str, float *f)
{
    return svtParseFloat(str, f) == 0;
}

bool parseInt(const char *str, int *i)
{
    return svtParseInt(str, i) == 0;
}

bool parseFloatList(const char *str, int len, float *nums)
{
    static char buffer[100];
    const char *c;
    int i;

    c = str;

    for (int j=0; j < len; j++){
        if (j > 0 && *c != ',')
            return false;
        if (j > 0 && *c != 0)
            c++;

        for (i=0; *c != ',' && *c != 0; i++, c++)
            buffer[i] = *c;
        buffer[i] = 0;
        if (i < 1)
            return false;

        if (svtParseFloat(buffer, nums + j) != 0)
            return false;
    }

    if (*c != 0)
        return false;
    return true;
}



void chooseRandomColor(float *r, float *g, float *b)
{
    do {
        *r = drand48();
        *g = drand48();
        *b = drand48();
    } while (*r * *g * *b < 0.01f); // eliminate black dark colors
}

void colorToHex(char str[7], const float colorf[3])
{
    int color[3];
    int n, pos;
    char c;

    color[0] = (int)(255 * colorf[0]);
    color[1] = (int)(255 * colorf[1]);
    color[2] = (int)(255 * colorf[2]);

    pos = 0;
    for (int i=0; i < 3; i++){
        n = color[i] / 16;
        if (n > 9){
            c = 'A' + n - 10;
        }else{
            c = '0' + n;
        }
        str[pos++] = c;

        n = color[i] % 16;
        if (n > 9){
            c = 'A' + n - 10;
        }else{
            c = '0' + n;
        }
        str[pos++] = c;
    }

    str[6] = 0;
}

void parseAll(int argc, char *argv[], svt_parser_t *parser)
{
    if (argc > 0){
        FILE *fin;

        for (int i=0; i < argc; i++){
            std::cerr << "Parsing file " << argv[i] << " ..." << std::endl;
            fin = fopen(argv[i], "r");
            if (fin == NULL){
                ERR("Can't read file " << argv[i]);
                continue;
            }

            svtParserSetInput(parser, fin);

            if (svtParserParse(parser) != 0){
                ERR("Can't parse file " << argv[i]);
            }

            fclose(fin);
        }
    }else{
        if (svtParserParse(parser) != 0){
            ERR("Can't parse input");
        }
    }
}

}

}
