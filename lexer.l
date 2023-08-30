%{
	#include <iostream>
	#include "y.tab.h"
	void yyerror(char *s);
	
	void unexpected_char_handler(char c)
	{
		std::cout << "SYNTAX ERROR: Unexpected character \"" << c << "\", line: " << yylineno << std::endl;
		exit(1);
	}

%}

/*line counting on for error highlight*/
%option yylineno
/*stop analyze after eof*/
%option noyywrap


/*
missed specific characters: <> [] # . ~ ~= comments &(other) *(other) , (other key words)
*/

%%


"if" 						return IF;
"else" 					return ELSE;
"while" 					return WHILE;
"return"					return RETURN;
"print"					return PRINT;

"++" 						return INC;
"--"						return DEC;

"+="						return ADD_EQ;
"-="						return SUB_EQ;
"*="						return MULT_EQ;
"/="						return DIV_EQ;
"%="						return MOD_EQ;

">="						return MORE_EQ;
"<=" 						return LESS_EQ;
"!=" 						return NOT_EQUAL;
"=="						return EQUAL_DOUBLE;

"<<="						return PUSHL_EQ;
">>="						return PUSHR_EQ;

"<<"						return PUSHL;
">>"						return PUSHR;
">"                         			return MORE;
"<"                         			return LESS;


"^="						return XOR_EQ;
"|="						return OR_EQ;
"&="						return AND_EQ;

"&&"						return AND;
"||"						return OR;

"&"						return AND_SINGLE;
"-"						return MINUS;
";"						return SEMICOLON;
"="						return EQUAL;
"+"						return PLUS;
"*"						return MULT;
"/"						return DIV;
"!"						return NOT;
"%"						return MOD;
"^"						return XOR;
"|"						return OR_SINGLE;

[ \t\r\n]+ 					;
[0-9]+						return NUMBER;
[a-zA-Z_][a-zA-Z0-9_]*				{yylval.string = strdup(yytext); return VAR;}
[{}()]						return *yytext;

.						unexpected_char_handler(*yytext);

%%

