%option noyywrap

%{

#include <stdio.h>
#include <string.h>

#define YY_DECL int yylex()
#include "parser.tab.h"

int words = 0;
int chars = 0;
int lines = 0;

%}

string		"\""([^\n\"\\]*(\\[.\n])*)*"\"" 
letter      [a-zA-Z]
digit       [0-9]
ID          {letter}({letter}|{digit})*
delim       [ \t\n]
INTEGER 	{digit}+
DECIMAL      {digit}+(\.{digit}+)?(E[+\-]?(digit)+)?
CHARACTER   ["'"]({letter}|{digit})["'"]
/* ws          {delim}+
boolean     [true] */


%%


"/*"    				{
							int c;
							while((c = input()) != 0) {
								if(c == '*') {
									if((c = input()) == '/')
										break;
									else
										unput(c);
								}
							}
						}
						
"int"	{words++; chars += strlen(yytext);
			printf("%s : INT\n", yytext);
			yylval.string = strdup(yytext); 
			return INT;
		}

"char"	{words++; chars += strlen(yytext);
			printf("%s : CHAR\n", yytext);
			yylval.string = strdup(yytext); 
			return CHAR;
		}

"float"	{words++; chars += strlen(yytext);
			printf("%s : FLOAT\n", yytext);
			yylval.string = strdup(yytext); 
			return FLOAT;
		}

"write"	{words++; chars += strlen(yytext);
			printf("%s : WRITE\n", yytext);
			yylval.string = strdup(yytext); 
			return WRITE;
		}

"swrite"	{words++; chars += strlen(yytext);
			printf("%s : SWRITE\n", yytext);
			yylval.string = strdup(yytext); 
			return SWRITE;
		}

"return"	{words++; chars += strlen(yytext);
			printf("%s : RETURN\n", yytext);
			yylval.string = strdup(yytext); 
			return RETURN;
		}

"writeln"	{words++; chars += strlen(yytext);
			printf("%s : WRITELN\n", yytext);
			yylval.string = strdup(yytext); 
			return WRITELN;
		}

"func" 		{words++; chars += strlen(yytext);
			printf("%s : FUNC\n", yytext);
			yylval.string = strdup(yytext); 
			return FUNC;
		}

"if" 		{words++; chars += strlen(yytext);
			printf("%s : IF\n", yytext);
			yylval.string = strdup(yytext); 
			return IF;
		}

"while" 	{words++; chars += strlen(yytext);
			printf("%s : WHILE\n", yytext);
			yylval.string = strdup(yytext); 
			return WHILE;
		}

"else" 		{words++; chars += strlen(yytext);
			printf("%s : ELSE\n", yytext);
			yylval.string = strdup(yytext); 
			return ELSE;
		}

{ID}	{words++; chars += strlen(yytext);
			  printf("%s : IDENTIFIER\n",yytext);
			  yylval.string = strdup(yytext); 
			  return ID;
			}

{INTEGER}   {words++; chars += strlen(yytext);
			  printf("%s : INTEGER\n",yytext);
			  yylval.number = atoi(strdup(yytext)); 
			  return INTEGER;
			}
			
{DECIMAL}		{words++; chars += strlen(yytext);
			  printf("%s : DECIMAL\n",yytext);
			  yylval.floatValue = atof(yytext); 
			  return DECIMAL;
			}

{CHARACTER}		{words++; chars += strlen(yytext);
			  printf("%s : CHARACTER\n",yytext);
			  yylval.character = strdup(yytext); 
			  return CHARACTER;
			}

{string}	{words++; chars += strlen(yytext);
			  printf("%s : string\n",yytext);
			  yylval.character = strdup(yytext); 
			  return STRING;
			}

			
";"		{chars++;
		  //printf("%s : SEMICOLON\n", yytext);
		  yylval.string = strdup(yytext); 
		  return SEMICOLON;
		}
		
"="		{chars++;
		  printf("%s : EQ\n", yytext);
		  yylval.string = strdup(yytext); 
		  return EQ;
		}

"=="		{chars++;
		  printf("%s : LOGICOP\n", yytext);
		  yylval.string = strdup(yytext); 
		  return LOGICOP;
		}
"!="		{chars++;
		  printf("%s : LOGICOP\n", yytext);
		  yylval.string = strdup(yytext); 
		  return LOGICOP;
		}
">"		{chars++;
		  printf("%s : LOGICOP\n", yytext);
		  yylval.string = strdup(yytext); 
		  return LOGICOP;
		}
"<"		{chars++;
		  printf("%s : LOGICOP\n", yytext);
		  yylval.string = strdup(yytext); 
		  return LOGICOP;
		}
"<="		{chars++;
		  printf("%s : LOGICOP\n", yytext);
		  yylval.string = strdup(yytext); 
		  return LOGICOP;
		}
">="		{chars++;
		  printf("%s : LOGICOP\n", yytext);
		  yylval.string = strdup(yytext); 
		  return LOGICOP;
		}



"+"		{chars++;
		  printf("%s : PLUS\n", yytext);
		  yylval.string = strdup(yytext); 
		  return PLUS;
		}

"-"		{chars++;
		  printf("%s : MINUS\n", yytext);
		  yylval.string = strdup(yytext); 
		  return MINUS;
		}

"*"		{chars++;
		  printf("%s : TIMES\n", yytext);
		  yylval.string = strdup(yytext); 
		  return TIMES;
		}

"/"		{chars++;
		  printf("%s : DIVIDE\n", yytext);
		  yylval.string = strdup(yytext); 
		  return DIVIDE;
		}

"["		{chars++;
		  printf("%s : LBRACKET\n", yytext);
		  yylval.string = strdup(yytext); 
		  return LBRACKET;
		}

"]"		{chars++;
		  printf("%s : RBRACKET\n", yytext);
		  yylval.string = strdup(yytext); 
		  return RBRACKET;
		}

"("		{chars++;
		  printf("%s : LPAREN\n", yytext);
		  yylval.string = strdup(yytext); 
		  return LPAREN;
		}

")"		{chars++;
		  printf("%s : RPAREN\n", yytext);
		  yylval.string = strdup(yytext); 
		  return RPAREN;
		}

"{"		{chars++;
		  printf("%s : LCURLY\n", yytext);
		  yylval.string = strdup(yytext); 
		  return LCURLY;
		}

"}"		{chars++;
		  printf("%s : RCURLY\n", yytext);
		  yylval.string = strdup(yytext); 
		  return RCURLY;
		}

[\n]	{lines++; chars=0;}
[ \t]	{chars++;}
.		{chars++;
         printf("%s : Unrecognized symbol at line %d char %d\n", yytext,lines,chars);
		}
		

%%