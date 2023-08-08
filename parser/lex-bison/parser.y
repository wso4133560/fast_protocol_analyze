%{
#include <stdio.h>
void yyerror(const char* msg);
int yylex(void);
%}

%union {
    char* str;
}

%token PRO
%token BYTE
%token DECODE
%token GONE
%token IF
%token ELSEIF
%token ELSE
%token JUMP

%token <str> IDENTIFIER

%token HEX
%token NUM

%token LBRACKET
%token RBRACKET
%token COLON
%token SEMICOLON
%token <str> DOUBLE_QUOTES_STR
%token ACTION
%token EQ
%token NEQ
%token GT
%token GTE
%token LT
%token LTE
%token AND
%token OR
%token NOT

%%

lines: line | lines line;
line: protocal 
    | byteLine 
    | fieldActionLine 
    | ifLine 
    | elseIfLine 
    | elseLine 
    | jumpLine;

protocal: PRO IDENTIFIER COLON {printf("%s\n", $2);};

byteLine: IDENTIFIER LBRACKET DOUBLE_QUOTES_STR RBRACKET COLON BYTE LBRACKET intExpr RBRACKET SEMICOLON {printf("%s, %s\n", $1, $3);};

fieldActionLine: IDENTIFIER actions SEMICOLON;
actions: action 
       | actions action;
action: decodeAction 
      | goneAction;
decodeAction: ACTION DECODE;
goneAction: ACTION GONE;

ifLine: IF logicalExpr COLON;
elseIfLine: ELSEIF logicalExpr COLON;
elseLine: ELSE COLON;

jumpLine: JUMP IDENTIFIER SEMICOLON;

logicalExpr: compareExpr
           | logicalExpr AND compareExpr
           | logicalExpr OR compareExpr
           ;

compareExpr: intExpr
           | compareExpr EQ intExpr
           | compareExpr NEQ intExpr
           | compareExpr GT intExpr
           | compareExpr GTE intExpr
           | compareExpr LT intExpr
           | compareExpr LTE intExpr
           ;

intExpr: HEX
       | NUM
       | IDENTIFIER;

%%

extern int line_count;

void yyerror(const char* msg) {
    printf("Error: %s line %d\n", msg, line_count);
}
