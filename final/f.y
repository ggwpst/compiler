%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int yylex(void);
void yyerror(char *);
int count = 0;
struct idval{
    char *name;
    int val;
};
struct idval idv[100];
int i;
int test = -1;
%}

%union{
    int ival;
    char *word;
}
%token<ival>number   

%token<ival>bool 

%token<word>id

%token printnum printbool IF define mod and or not

%type<ival>expn num_op plus adds minus multiply muls divide modulus
print_stmt def_stmt stmt if_exp test_exp then_exp else_exp

%type<ival>expb boolval equal equals greater smaller 
logical_op and_op or_op not_op ands ors

%type<word>variable
%%
line: stmts
stmts: 
    | stmts stmt 
;
stmt: expn 
    | expb
    | print_stmt
    | def_stmt
;
print_stmt: '(' printnum expn ')' {if(test == -1) printf("%d\n",$3); else if(test == 0) printf("#f\n"); else if(test == 1) printf("#t\n");}
    | '(' printbool expb ')'      {if($3==1) printf("#t\n"); else printf("#f\n");}
;

expn:   number 
    |   variable    {
		for(i = 0;i < count;i++){
        		if(strcmp($1,idv[i].name)==0){
            			$$ = idv[i].val;
			}
    		}
	}
    |   num_op
    |   if_exp
;
expb:   boolval
    |   logical_op
;

boolval: bool   {$$ = $1;}
;
num_op: plus 
    |   minus 
    |   multiply 
    |   divide 
    |   modulus 
    |   greater 
    |   smaller 
    |   equal 
;
plus: '(' '+' expn adds ')'      {$$ = $3 + $4;test=-1;}
;
adds: expn adds    {$$ = $1 + $2;}
    | expn         {$$ = $1;}
;
minus: '(' '-' expn expn ')'     {$$ = $3 - $4;test=-1;}
;
multiply: '(' '*' expn muls ')'  {$$ = $3 * $4;test=-1;}
;
muls: expn muls    {$$ = $1 * $2;}
    | expn         {$$ = $1;}
; 
divide: '(' '/' expn expn ')'    {$$ = $3 / $4;test=-1;}
;
modulus: '(' mod expn expn ')'   {$$ = $3 % $4;test=-1;}
; 
greater: '(' '>' expn expn ')'   {
			if($3 > $4) {
				$$ = 1; 
				test = 1;
			}
			else {
				$$ =  0;
				test = 0;
			}
}
;
smaller: '(' '<' expn expn ')'   {
			if($3 < $4) {
				$$ = 1; 
				test = 1;
			}
			else {
				$$ =  0;
				test = 0;
			}
}
;
equal: '(' '=' expn equals ')'     {if($3 == $4 && test == 1) $$ = 1; else $$ =  0;}
;
equals: expn equals    {
			if($1 == $2 && test == 1){
				$$ = $1;
				test = 1;
			}
			else{
				test = 0;
				$$ = 0;
			}
		}
    | expn         {$$ = $1;test = 1;}
; 
logical_op: and_op
    | or_op
    | not_op
;
and_op: '(' and expb ands ')'    {if($3==1&&$4==1) $$ = 1; else $$ = 0;}
		|'(' and expn ands ')'    {if($3==1&&$4==1) $$ = 1; else $$ = 0;}
;
ands: expb ands    {if($1==1&&$2==1) $$ = 1; else $$ = 0;}
	|expn ands    {if($1==1&&$2==1) $$ = 1; else $$ = 0;}
        | expb         {$$ = $1;}
	| expn         {$$ = $1;}
;
or_op: '(' or expb ors ')'       {if($3==0&&$4==0) $$ = 0; else $$ = 1;}
	| '(' or expn ors ')'       {if($3==0&&$4==0) $$ = 0; else $$ = 1;}
;
ors:  expb ors     {if($1==0&&$2==0) $$ = 0; else $$ = 1;}
	|expn ors   {if($1==0&&$2==0) $$ = 0; else $$ = 1;}
        | expb         {$$ = $1;}
	| expn         {$$ = $1;}
;
not_op: '(' not expb ')'         {if($3==0) $$ = 1; else $$ = 0;}
	|'(' not expn ')'            {if($3==0) $$ = 1; else $$ = 0;}
;
if_exp: '(' IF test_exp then_exp else_exp ')' {if($3==1) $$ = $4; else $$ = $5;test=-1;}
;
test_exp: expn
    | expb
;
then_exp: expn
    | expb
;
else_exp: expn
    | expb
;
def_stmt: '(' define id expn ')'  {idv[count].name=$3; idv[count].val = $4; count++;}
;
variable: id   
;
%%
void yyerror(char *s) {
    fprintf(stderr, "%s\n", s);
}
int main(void) {
    yyparse();
    return 0;
}