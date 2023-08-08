%{
#include "parser.tab.h"
int start_space_count = 0;
int line_count = 0;
%}

%option outfile="lex.c"

%%
^[ ]+                           {
                                    start_space_count = yyleng;
                                    if (yyleng % 4)
                                    {
                                        fprintf(stderr, "error start space num at line: %d\n", line_count);
                                        exit(-1);
                                    }
                                }
"\n"                            {
                                    start_space_count = 0;
                                    line_count++;
                                }

"pro"                           {return PRO;}
"byte"                          {return BYTE;}
"decode"                        {return DECODE;}
"gone"                          {return GONE;}
"if"                            {return IF;}
"elseif"                        {return ELSEIF;}
"else"                          {return ELSE;}
"jump"                          {return JUMP;}

[a-zA-Z_][a-zA-Z0-9]*           {
                                    yylval.str = strndup(yytext, yyleng);
                                    return IDENTIFIER;
                                }
0x[0-9a-fA-F]+                  {return HEX;}
[0-9]+                          {return NUM;};

"("                             {return LBRACKET;}
")"                             {return RBRACKET;}
":"                             {return COLON;}
";"                             {return SEMICOLON;}
\"[^\"]*\"                      {yylval.str = strndup(yytext, yyleng); return DOUBLE_QUOTES_STR;}
"->"                            {return ACTION;}
"=="                            {return EQ;}
"!="                            {return NEQ;}
">"                             {return GT;}
">="                            {return GTE;}
"<"                             {return LT;}
"<="                            {return LTE;}
"&&"                            {return AND;}
"||"                            {return OR;}
"!"                             {return NOT;}


[ \t\r]+

#[^\n]*

%%

int yywrap() {
    return 1;
}
