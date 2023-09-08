%{
	#include<iostream>
	#include <string.h>
	#include <vector>
	#include <stack>
	
	extern int yylineno;
	extern int yylex();
	bool num_error = 0;

	char * operato = {0x00};

	std::vector <std::string> express;

	std::vector <std::string> express_ppn;
	std::stack <std::string> stack_t;
	
	void p(){
		for (auto i = express.begin(); i != express.end(); ++i){
			std::cout<< *i << std::endl;
		}
		std::cout<<"ban"<<std::endl;
	}
	
	void ex_push_back(char *s){
		std::string tmp(s);
		express.push_back(tmp);
	}


	void yyerror(char *s)
	{
		std::cout << "SYNTAX ERROR: " << s << ", line " << yylineno << std::endl;
		num_error = 1;
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
	
	
	int prior(std::string op) {
		if (op == "(") return 1;
		if (op == "OR") return 2;
		if (op == "XOR") return 3;
		if (op == "AND") return 4;
		if (op == "PUSHL" || op == "PUSHR") return 5;
		if (op == "ADD" || op == "SUB") return 6;
		if (op == "DIV" || op == "MULT") return 7;
		return 0;
	}

	bool is_operator(std::string cur) {
		if (cur == "ADD" || cur == "SUB" || cur == "DIV" || cur == "MULT") return true;
		if (cur == "MOD" || cur == "AND" || cur == "XOR" || cur == "OR") return true;
		if (cur == "PUSHL" || cur == "PUSHR") return true;
		if (cur == "INC" || cur == "DEC") return true;
		return false;
	}

	void convert_to_ppn() {

		for (int i = 0; i < express.size(); i++) {
		
			std::string cur_s = express[i];
		
			/*std::string tmp_postfix;

			
			
			if (cur_s == "++" or cur_s == "--"){
				//prefix
				if (!is_operator(express[i+1]) && express[i+1] != "(" && express[i+1]) != ")"){ //if var or number
					if (cur_s == "++"){
						express_ppn.push_back("INC");
					}
					else {
						express_ppn.push_back("DEC");
					}
					
				}
				//postfix
				else{
				//new
					tmp_postfix = cur_s;
				}
				continue;
			}*/
			
			if (!is_operator(cur_s) && cur_s != "(" && cur_s != ")") { //if var or number
				express_ppn.push_back(cur_s);
				continue;
			}
			

			if (cur_s == "(") {
				stack_t.push(cur_s);
				continue;
			}
			if (is_operator(cur_s)) {

				while (!stack_t.empty() && prior(cur_s) <= prior(stack_t.top())) {
					std::string tmp = stack_t.top();
					stack_t.pop();
					express_ppn.push_back(tmp);
				}
				if (stack_t.empty() || prior(cur_s) > prior(stack_t.top())) { //why only top
					stack_t.push(cur_s);
				}
				continue;
			}
			if (cur_s == ")") {
				std::string tmp = stack_t.top();
				stack_t.pop();
				while (tmp != "(") {
					express_ppn.push_back(tmp);
					tmp = stack_t.top();
					stack_t.pop();
				}
				continue;
			}
		}
		while (!stack_t.empty()) {
			std::string tmp = stack_t.top();
			stack_t.pop();
			express_ppn.push_back(tmp);
		}
	}


	void print_expr(){
		//vector "express" to reverse polish notation
		convert_to_ppn();
		
		//print each element "ab+" as "push a push b add"
		
		for (auto i = express_ppn.begin(); i != express_ppn.end(); ++i) {
			if (is_operator(*i)){
				std::cout<<*i<<std::endl;
			}
			else { 	
				std::cout<<"PUSH "<<*i << std::endl;
			}
		}
		
		
	}



%}

%union {
	char * string;
}

%token <string> NUMBER VAR INC DEC

%destructor {free($$);} VAR
%destructor {free($$);} NUMBER
%destructor {free($$);} INC
%destructor {free($$);} DEC

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

expr: 
	expr bin_opertr expr 
	| INC VAR {express.push_back($1); express.push_back($2); }
	| DEC VAR {express.push_back($1); express.push_back($2); }
	| VAR INC {express.push_back($1); express.push_back($2); }
	| VAR DEC {express.push_back($1); express.push_back($2); }
	| VAR {ex_push_back($1);}
	| NUMBER {ex_push_back($1);}
	| '(' {express.push_back("(");} expr ')' {express.push_back(")");}
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
		MINUS {express.push_back("SUB");}
		| PLUS {express.push_back("ADD");}
		| MULT {express.push_back("MULT");}
		| DIV {express.push_back("DIV");}
		| MOD {express.push_back("MOD");}
		| XOR {express.push_back("XOR");}
		| OR_SINGLE {express.push_back("OR");}
		| AND_SINGLE {express.push_back("AND");}
		| PUSHL {express.push_back("PUSHL");}
		| PUSHR {express.push_back("PUSHR");}
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
