%{
#include<stdio.h>
#include<stdlib.h>

#define SIZE 100

double numbers[SIZE];
char symbols[SIZE];

int nTop = -1;
int sTop = -1;

void storeNumber(double n){ numbers[++nTop] = n; }
void storeSymbol(char ch){ symbols[++sTop] = ch; }

double getNumber(){ return numbers[nTop--]; }
char getSymbol(){ return symbols[sTop--]; }

int priority(char ch){
    if(ch=='+'||ch=='-') return 1;
    if(ch=='*'||ch=='/') return 2;
    return 0;
}

void process(){
    double right = getNumber();
    double left  = getNumber();
    char op = getSymbol();

    double r;

    if(op=='+') r = left + right;
    else if(op=='-') r = left - right;
    else if(op=='*') r = left * right;
    else r = left / right;

    storeNumber(r);
}
%}

%%

[0-9]+(\.[0-9]+)?   { storeNumber(atof(yytext)); }

[+\-*/] {
    while(sTop>=0 && symbols[sTop]!='(' &&
          priority(symbols[sTop]) >= priority(yytext[0]))
    {
        process();
    }

    storeSymbol(yytext[0]);
}

"(" { storeSymbol('('); }

")" {
    while(sTop>=0 && symbols[sTop]!='(')
    {
        process();
    }

    if(sTop>=0 && symbols[sTop]=='(')
        getSymbol();
}

[ \t\r]+ ;

\n {
    while(sTop>=0)
        process();

    if(nTop>=0)
        printf("Result = %.2lf\n", getNumber());

    nTop = sTop = -1;
}

. ;

%%

int yywrap(){ return 1; }

int main(){
    printf("Enter expression:\n");
    yylex();
    return 0;
}