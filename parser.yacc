%{
	#include<iostream>
	#include <string.h>
	#include <vector>
	extern int yylineno;
	extern int yylex();
	bool num_error = 0;
	
	char * operato = {0x00};
	//char * bin_operato = {0x00};
	
	std::string print_oper(std::string operr);
	
	/*
	std::string hehe(std::string ope){
		if (strcmp(ope.c_str(), "mult")==0)return "SUB";
		return "ADD";
	}
	
	void p(){
		std::vector <std::string> bracket_vars;
		bracket_vars.push_back("div");
		bracket_vars.push_back("mult");
		std::cout << bracket_vars[1]<< std::endl;
		std::cout << hehe(bracket_vars[0])<< std::endl;
		printf("%s\n", bracket_vars[0].c_str());
	}
	*/

	std::vector <std::string> all_vars_in_expr;
	std::vector <std::string> all_opers_in_expr;
	std::vector <std::string> bracket_vars; //queue () vars
	std::vector <std::string> bracket_opers; //queue () opers
	std::vector <std::string> mult_vars; //queue * / vars
	std::vector <std::string> mult_opers; //queue * / opers
	std::vector <std::string> plus_vars; //queue + - vars
	std::vector <std::string> plus_opers;//queue + - opers
	
	void queue_distrib(){
		//TO DO distribution
		
		int k = 0; //pointer through queue of vars
		for (int i = 0; i < all_opers_in_expr.size(); i++){
		
			std::string tmp1 = all_vars_in_expr[k];
			std::string tmp2 = all_vars_in_expr[k+1];
			k += 2;
			
			//add more than */+- and also ++ think about it
			if (all_opers_in_expr[i] == "mult" || all_opers_in_expr[i] == "div"){
				mult_opers.push_back(all_opers_in_expr[i]);
				mult_vars.push_back(tmp1);
				mult_vars.push_back(tmp2);
			}
			
			if (all_opers_in_expr[i] == "minus" || all_opers_in_expr[i] == "plus"){
				plus_opers.push_back(all_opers_in_expr[i]);
				plus_vars.push_back(tmp1);
				plus_vars.push_back(tmp2);
			}
		}
	}
	
	void print_expr(){
	
		queue_distrib();
		
		int k = 0; //pointer through queue of vars
		
		for (int i = 0; i < bracket_opers.size(); i++){
			printf("PUSH %s\nPUSH %s\n", bracket_vars[k].c_str(), bracket_vars[k+1].c_str());
			std::cout << print_oper(bracket_opers[i])<< std::endl;
			k+=2;
		}
		
		k = 0;
		for (int i = 0; i < mult_opers.size(); i++){
			printf("PUSH %s\nPUSH %s\n", mult_vars[k].c_str(), mult_vars[k+1].c_str());
			std::cout << print_oper(mult_opers[i])<< std::endl;
			k+=2;
		}
		
		k = 0;
		for (int i = 0; i < plus_opers.size(); i++){
			printf("PUSH %s\nPUSH %s\n", plus_vars[k].c_str(), plus_vars[k+1].c_str());
			std::cout << print_oper(plus_opers[i])<< std::endl;
			k+=2;
		}
		//mb clear all expr queues
		for (int i = 0; i < all_opers_in_expr.size(); i++){
			std::cout<<all_opers_in_expr[i]<<std::endl;
		}
		for (int i = 0; i < all_vars_in_expr.size(); i++){
			std::cout<<all_vars_in_expr[i]<<std::endl;
		}
		
	}
	
	
	void yyerror(char *s)
	{
		std::cout << "SYNTAX ERROR: " << s << ", line " << yylineno << std::endl;
		num_error = 1;
	}
	
	std::string /*void*/ print_oper(std::string operr){ //extra, could be just div immidiately SUB instead minus
		const char * bin_operato = operr.c_str(); 
		if (strcmp(bin_operato, "minus") == 0){/*printf("SUB\n");*/ return "SUB";}
		else if (strcmp(bin_operato, "plus") == 0){return "ADD";}
		else if (strcmp(bin_operato, "mult") == 0){return "MULT";}
		else if (strcmp(bin_operato, "div") == 0){return "DIV";}
		else if (strcmp(bin_operato, "mod") == 0){return "MOD";}
		else if (strcmp(bin_operato, "xor") == 0){return "XOR";}
		else if (strcmp(bin_operato, "or_single") == 0){return "OR_BIT";}
		else if (strcmp(bin_operato, "and_single") == 0){return "AND_BIT";}
		else if (strcmp(bin_operato, "pushl") == 0){return "PUSHL";}
		else if (strcmp(bin_operato, "pushr") == 0){return "PUSHR";}
	}
	
	void print_equal(char *s){ 
		if (strcmp(operato, "equal") == 0){}
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
		VAR assign_operator expr {print_expr(); print_equal($1); printf("POP %s\n", $1); /*p();*/}
		;
/*
expr1:
	expr {printf("HELLO\n");}
	;

*/
expr: 
	expr bin_opertr expr /*{print_oper();}*/
	| unary_opertr VAR
	| VAR unary_opertr {printf("PUSH %s\n", $1);}
	| VAR /*{printf("PUSH [%s]\n", $1);}*/ {all_vars_in_expr.push_back($1);}
	| NUMBER /*{printf("PUSH %s\n", $1);}*/ {all_vars_in_expr.push_back($1);}
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
		MINUS {all_opers_in_expr.push_back("minus");}
		| PLUS {all_opers_in_expr.push_back("plus");}
		| MULT {all_opers_in_expr.push_back("mult");}
		| DIV {all_opers_in_expr.push_back("div");}
		| MOD {all_opers_in_expr.push_back("mod");}
		| XOR {all_opers_in_expr.push_back("xor");}
		| OR_SINGLE {all_opers_in_expr.push_back("or_single");}
		| AND_SINGLE {all_opers_in_expr.push_back("and_single");}
		| PUSHL {all_opers_in_expr.push_back("pushl");}
		| PUSHR {all_opers_in_expr.push_back("pushr");}
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
