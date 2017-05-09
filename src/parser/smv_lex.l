
%{
#include "node.h"
//#include "yacc.tab.h"

%}

%x COMMENT

%%

"--" {  // 匹配注释
    cout << "(comment)" << endl;
    BEGIN   COMMENT;
}

([a-zA-Z]) {    // 匹配标识符
    yylval.m_string = yytext;
    return IDENTIFIER;
}

([0-9]) {   // 匹配整数
    yylval.m_int = stoi(yytext);
    return INTEGER;
}

".." {  // 匹配范围
    yylval.m_string = yytext;
    return RANGE;
}

":" {   // 匹配范围赋值
    yylval.m_string = yytext;
    return RANGEINIT;
}

":=" {  // 匹配变量初始化
    yylval.m_string = yytext;
    return VARINIT;
}

"(" {   // 匹配左括号
    yylval.m_string = yytext;
    return LB;
}

")" {   // 匹配右括号
    yylval.m_string = yytext;
    return RB;
}

";" {   // 匹配分号
    yylval.m_string = yytext;
    return SEMICOLON;
}

[-+*/] {    // 匹配运算符
    yylval.m_string = yytext;
    return OPERATOR;
}

"mod" { // 匹配取余
    yylval.m_string = yytext;
    return MOD;
}

[ \f\r\t\v]+ {  // 匹配空白
    // 忽略
}

[\n] {  // 匹配换行
    // 忽略
}

. { // 匹配任意非\n字符
    yylval.m_char = yytext[0];
    return CHAR;
}

<COMMENT>\n {   // 匹配注释状态下的换行
    BEGIN INITIAL;
}

<COMMENT>. {    // 匹配注释状态下的其他字符
    // 忽略
}

%%

int yywrap(void) {
    cout << "---the file is end");
    return 1;
}

int main() {
    cout << "lex and c++" << endl;
    yylex();
    return 0;
}