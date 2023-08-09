%{
#include "script_manager.h"
#include <stdio.h>
#include <stdlib.h>

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

%token <str> HEX
%token <str> NUM

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
%token ADD
%token SUB
%token MUL
%token DIV
%token REM

%%

lines: line | lines line;
line: protocal 
    | byteLine 
    | fieldActionLine 
    | ifLine 
    | elseIfLine 
    | elseLine 
    | jumpLine;

protocal: PRO IDENTIFIER COLON  {
                                    set_pro_name($2);
                                    free($2);
                                };

byteLine: IDENTIFIER LBRACKET DOUBLE_QUOTES_STR RBRACKET COLON BYTE LBRACKET mulDivExpr RBRACKET SEMICOLON 
                                                                                                        {
                                                                                                            set_byte_field($1, $3);
                                                                                                            free($1);
                                                                                                            free($3);
                                                                                                        }
                                                                                                        ;

fieldActionLine: IDENTIFIER actions SEMICOLON 
                                            {
                                                set_field_actions($1);
                                                free($1);
                                            }
                                            ;
actions: action 
       | actions action;
action: decodeAction 
      | goneAction;
decodeAction: ACTION DECODE {push_field_action(DECODE);};
goneAction: ACTION GONE {push_field_action(GONE);};

ifLine: IF logicalExpr COLON {set_if_action();};
elseIfLine: ELSEIF logicalExpr COLON;
elseLine: ELSE COLON;

jumpLine: JUMP IDENTIFIER SEMICOLON;

logicalExpr: compareExpr
           | logicalExpr AND compareExpr {set_logic_expr(AND);}
           | logicalExpr OR compareExpr {set_logic_expr(OR);}
           ;

compareExpr: intExpr
           | compareExpr EQ intExpr {set_logic_expr(EQ);}
           | compareExpr NEQ intExpr {set_logic_expr(NEQ);}
           | compareExpr GT intExpr {set_logic_expr(GT);}
           | compareExpr GTE intExpr {set_logic_expr(GTE);}
           | compareExpr LT intExpr {set_logic_expr(LT);}
           | compareExpr LTE intExpr {set_logic_expr(LTE);}
           ;

mulDivExpr: addSubExpr
          | mulDivExpr MUL addSubExpr {merge_params(MUL);}
          | mulDivExpr DIV addSubExpr {merge_params(DIV);}
          ;

addSubExpr: intExpr
          | addSubExpr ADD intExpr {merge_params(ADD);}
          | addSubExpr SUB intExpr {merge_params(SUB);}
          ;

intExpr: HEX 
            {
                char *endPtr;
                struct IntInfo* intInfo = (struct IntInfo*)malloc(sizeof(struct IntInfo));
                intInfo->field = NULL;
                intInfo->value = strtol($1, &endPtr, 16);

                push_int_param (intInfo);

                free($1);
                free(intInfo);
            }
       | NUM 
            {
                char *endPtr;
                struct IntInfo* intInfo = (struct IntInfo*)malloc(sizeof(struct IntInfo));
                intInfo->field = NULL;
                intInfo->value = strtol($1, &endPtr, 10);

                push_int_param (intInfo);

                free($1);
                free(intInfo);
            }
       | IDENTIFIER
            {
                struct IntInfo* intInfo = (struct IntInfo*)malloc(sizeof(struct IntInfo));
                intInfo->field = $1;

                push_int_param (intInfo);

                free($1);
                free(intInfo);
            }
       ;

%%

extern int line_count;

void yyerror(const char* msg) {
    printf("Error: %s line %d\n", msg, line_count);
}
