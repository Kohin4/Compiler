%{
#include <stdio.h>
#include <stdlib.h>

int yylex();
void yyerror(const char *s);
%}

%union{
    double fval;
}

%token <fval> NUM
%token EOL

%left '+' '-'
%left '*' '/'
%right UMINUS

%type <fval> expression

%%

program:
        /* empty */
      | program expression EOL
        {
            printf("Answer = %.2lf\n", $2);
        }
      ;

expression:
          expression '+' expression
            {
                $$ = $1 + $3;
            }

        | expression '-' expression
            {
                $$ = $1 - $3;
            }

        | expression '*' expression
            {
                $$ = $1 * $3;
            }

        | expression '/' expression
            {
                $$ = $1 / $3;
            }

        | '-' expression %prec UMINUS
            {
                $$ = -$2;
            }

        | '(' expression ')'
            {
                $$ = $2;
            }

        | NUM
            {
                $$ = $1;
            }
        ;

%%

void yyerror(const char *s)
{
    printf("Invalid Expression: %s\n", s);
}

int main()
{
    printf("Simple Calculator Using Lex and YACC\n");
    printf("Type expression and press Enter:\n");

    yyparse();

    return 0;
}