%{
#include "node.h"
%}

%%

file:
    tokenlist {

    };

tokenlist:
    {
    }

%%

void yyerror(const char* s) {
    cerr << s << endl;
}