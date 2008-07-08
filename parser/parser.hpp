/**
 * Coin3dTools
 * ------------
 * Copyright (c)2007 Daniel Fiser <danfis (at) danfis (dot) cz>
 *
 *
 * This file is part of Coin3dTools
 *
 * Coin3dTools is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Coin3dTools is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Coin3dTools.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _PARSER_HPP_
#define _PARSER_HPP_

#include <stdio.h>
#include "parser_lexer_common.h"
#include "objdata.hpp"

extern "C" {
    int yylex(void);
}


class Parser {
  private:
    int _cur_token;
    ObjData *_cur_obj;
    bool _parsed;
    FILE *_input;

    void _parsePoints();
    void _parsePoints2d();
    void _parseEdges();
    void _parseFaces();
    void _parseName();
    void _parseDelim();
    void _parseError();

    Parser() : _cur_token(-1), _cur_obj(0), _input(stdin){}
    ~Parser();
  public:
    static Parser *instance();

    bool setInput(const char *filename = 0);
    ObjData *parse();
};
#endif
