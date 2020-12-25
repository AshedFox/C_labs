%option noyywrap

%{
#include<stdio.h>
#include <string.h>
FILE *yyin, *yyout;
%}

%%


[^\n]/\<		ECHO; fprintf(yyout,"\n");
\>/[^\n]		ECHO; fprintf(yyout,"\n");

%%

int main() {
    yyin = fopen("html_doc.txt", "r");
    yyout = fopen("output.txt", "w");
    yylex();

    fclose(yyin);
    fclose(yyout);

    return 0;
}
