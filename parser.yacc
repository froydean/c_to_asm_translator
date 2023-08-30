%{
	#include<iostream>
	#include <string.h>
	extern int yylineno;
	extern int yylex();
	bool num_error = 0;
	
	char * operato = {0x00};
	
	void yyerror(char *s)
	{
		std::cout << "SYNTAX ERROR: " << s << ", line " << yylineno << std::endl;
		num_error = 1;
	}
	
	void print_equal(char *s){ 
		if (strcmp(operato, "equal") == 0){printf("%s\n", s);}
		else if (strcmp(operato, "add_eq") == 0){printf("PUSH [%s]\nADD\n", s);}
		else if (strcmp(operato, "sub_eq") == 0){printf("PUSH [%s]\nSUB\n", s);}
		else if (strcmp(operato, "mult_eq") == 0){printf("PUSH [%s]\nMULT\n", s);}
		else if (strcmp(operato, "div_eq") == 0){printf("PUSH [%s]\nDIV\n", s);}
		else if (strcmp(operato, "mod_eq") == 0){printf("PUSH [%s]\nMOD\n", s);}
		else if (strcmp(operato, "pushl_eq") == 0){printf("PUSH [%s]\nPUSHL\n", s);}
		else if (strcmp(operato, "pushr_eq") == 0){printf("PUSH [%s]\nPUSHR\n", s);}
		else if (strcmp(operato, "xor_eq") == 0){printf("PUSH [%s]\nXOR\n", s);}
		else if (strcmp(operato, "or_eq") == 0){printf("PUSH [%s]\nOR\n", s);}
		else if (strcmp(operato, "and_eq") == 0){printf("PUSH [%s]\nAND\n", s);}
	}
	
	
	
%}

%union {
	char * string;
}

%token <string> NUMBER VAR

%destructor {free($$);} VAR
%destructor {free($$);} NUMBER

%start command

%token IF ELSE WHILE RETURN PRINT INC DEC ADD_EQ SUB_EQ MULT_EQ DIV_EQ MOD_EQ MORE_EQ LESS_EQ NOT_EQUAL EQUAL_DOUBLE PUSHL_EQ PUSHR_EQ PUSHL PUSHR MORE LESS XOR_EQ OR_EQ AND_EQ AND OR AND_SINGLE MINUS SEMICOLON EQUAL PLUS MULT DIV NOT MOD XOR OR_SINGLE //NUMBER VAR



/*
Specific of this compilater:
	"a+b;" "a!=b;" etc. "a=b=c;" is not okay, only "VAR <some kind of  = > EXPR"
	command also should be without bra
	bool_condition do not support assignments as "(a=3)" "(b &= a)" "!a = 3" etc as right condition
	"!" without bracets relates to the first operand only (bool_condition)
		p.s. may contain mistakes in this("!") moment
	"print" has madeup format
	"return" can be without bra
	reduce-reduce in da house
*/

%%

command:
		assignment SEMICOLON 
		| unary_opertr VAR SEMICOLON
		| VAR unary_opertr SEMICOLON
		| print SEMICOLON
		| ret SEMICOLON
		| if
		| while
		| command command
		;

assignment:
		VAR assign_operator expr {print_equal($1); printf("POP %s\n", $1);}
		;


expr:
	expr bin_opertr expr
	| unary_opertr VAR
	| VAR unary_opertr {printf("PUSH %s\n", $1);}
	| VAR {printf("PUSH [%s]\n", $1);}
	| NUMBER {printf("PUSH %s\n", $1);}
	| '(' expr ')'
	;

print:
            PRINT '(' expr ')';

ret:
            RETURN expr;

//no need to be count operators after missing brackets bc it still right to syntax
if:    IF '(' bool_condition ')' '{' command '}' 
            | IF '(' bool_condition ')' '{' command '}' ELSE '{' command '}'
            | IF '(' bool_condition ')' '{' command '}' ELSE command
            | IF '(' bool_condition ')' command ELSE '{' command '}'
            | IF '(' bool_condition ')' '{' command '}' ELSE if
            | IF '(' bool_condition ')'  command
            | IF '(' bool_condition ')'  command ELSE command
            | IF '(' bool_condition ')'  command ELSE if
            ;


while: WHILE '(' bool_condition ')' '{' command '}' 
            | WHILE '(' bool_condition ')' command  
            ;

bool_condition:
		expr
		| NOT expr
		| assignment
		| NOT '(' assignment ')'
		| expr comparison_operator expr
		| bool_condition AND bool_condition
		| bool_condition OR bool_condition
		| bool_condition comparison_operator bool_condition
		| '(' bool_condition ')'
		;

assign_operator:
/*"="	"+="	"-="	"*="	"/="	"%="	"<<="	">>="	"^="	"|="	"&="*/
			EQUAL {operato = "equal\0";}
			| ADD_EQ {operato = "add_eq\0";}
			| SUB_EQ {operato = "sub_eq\0";}
			| MULT_EQ {operato = "mult_eq\0";}
			| DIV_EQ {operato = "div_eq\0";}
			| MOD_EQ {operato = "mod_eq\0";}
			| PUSHL_EQ {operato = "pushl_eq\0";}
			| PUSHR_EQ {operato = "pushr_eq\0";}
			| XOR_EQ {operato = "xor_eq\0";}
			| OR_EQ {operato = "or_eq\0";}
			| AND_EQ {operato = "and_eq\0";}
			;

comparison_operator:
/*">="	"<="	"!="	"=="	">"	"<"*/
			EQUAL_DOUBLE
			| NOT_EQUAL
			| MORE_EQ
			| LESS_EQ
			| LESS
			| MORE
			;

bin_opertr:
/*"+"	"*"	"/"	"%"	"^"	"|"	"-"	"&"	">>"	"<<"*/
		MINUS
		| PLUS
		| MULT
		| DIV
		| MOD
		| XOR
		| OR_SINGLE
		| AND_SINGLE
		| PUSHL
		| PUSHR
		;

unary_opertr:
/*"++"	"--"*/
		INC
		|DEC
		;

%%




int main() 
{
	yyparse();
	if(num_error==0)
		printf("OK\n");
}
