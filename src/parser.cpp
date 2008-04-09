#include <iostream>
#include "parser.hpp"
using namespace std;


#define SKIP_DELIMS \
    for (cur_token = yylex(); \
         cur_token != 0 && cur_token != T_ERROR \
         && cur_token == T_DELIM; \
         cur_token = yylex())

static void parsePoints();
static void parseEdges();
static void parseFaces();
static void parseDelim();
static void parseError();

yylval_t yylval;

int cur_token;

int main(int argc, char *argv[])
{
    SKIP_DELIMS;

    while (cur_token != 0){
        switch (cur_token){
            case T_POINTS:
                parsePoints();
                break;
            case T_EDGES:
                parseEdges();
                break;
            case T_FACES:
                parseFaces();
                break;
            case T_ERROR:
                parseError();
                break;
            case T_DELIM:
                parseDelim();
                break;
            default:
                cout << "Token: " << cur_token << endl;
                cur_token = yylex();
        }
    }
}

static void parsePoints()
{
    float coords[3];
    int i = 0;

    cur_token = yylex();
    while (cur_token == T_FLT_NUM){
        coords[i] = yylval.flt_num;
        i = (i + 1) % 3;

        // three coords already read
        if (i == 0){
            cout << "[ " << coords[0] << " " << coords[1] << " "
                 << coords[2] << " ]" << endl;
        }

        cur_token = yylex();
    }

    if (i != 0){
        cerr << "Some numbers unparsed: ";
        if (i == 1)
            cerr << coords[0] << endl;
        if (i == 2)
            cerr << coords[0] << " " << coords[1] << endl;
    }
}

static void parseEdges()
{
    int nums[2];
    int i = 0;

    cur_token = yylex();
    while (cur_token == T_INT_NUM){
        nums[i] = yylval.int_num;
        i = (i + 1) % 2;

        if (i == 0){
            cout << "[ " << nums[0] << " " << nums[1] << " ]" << endl;
        }

        cur_token = yylex();
    }

    if (i != 0){
        cerr << "Some numbers unparsed: " << nums[0] << endl;
    }
}

static void parseFaces()
{
    cur_token = yylex();
}

static void parseDelim()
{
    SKIP_DELIMS;
}

static void parseError()
{
    char buffer[100];
    int i = 1;
    int line = yylval.lineno;

    buffer[0] = yylval.c;
    while ((cur_token = yylex()) == T_ERROR){
        buffer[i++] = yylval.c;
    }
    buffer[i] = 0;

    cerr << "Unexpected input on line " << line << ": '" << buffer
         << "'" << endl;
}
