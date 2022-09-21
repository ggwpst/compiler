%{
#include "f.tab.h"
#include <stdio.h>
void yyerror(const char *);
%}

%%
[ ]+ {}
"print-num" {return printnum;}
"print-bool" {return printbool;}
"if" {return IF;}
"#t" {
	yylval.ival = 1;
	return bool;
}
"#f" {
	yylval.ival = 0;
	return bool;
}
([+-]?[1-9][0-9]*)|[0] {
	yylval.ival = atoi(yytext);
	return number;
}
"and" {return and;}
"or" {return or;}
"not" {return not;}
"define" {return define;}
"+"|"-"|"*"|"/"|">"|"<"|"="|"("|")" {
    	return yytext[0];
}
"mod" {
	return mod;
}
[a-zA-Z][a-zA-Z0-9-]* {
	yylval.word = strdup(yytext);
	return id;
}
\n {}
. {}

%%