%{
	#include<iostream>
	#include <string.h>
	#include <vector>
	#include <stack>
	
	extern int yylineno;
	extern int yylex();
	bool num_error = 0;

	//char * operato = {0x00};
	std::string operato;
	
	std::string unary_operator;
	
	int label_counter = 0;

	std::vector <std::string> express;

	std::vector <std::string> express_ppn;
	std::stack <std::string> stack_t;
	
	void p(){
		std::cout<<"ban"<<std::endl;
		for (auto i = express.begin(); i != express.end(); ++i){
			std::cout<< *i << std::endl;
		}
		std::cout<<"ban"<<std::endl;
	}
	
	void ex_push_back(char *s){
		std::string tmp(s);
		express.push_back(tmp);
	}


	void yyerror(std::string s)
	{
		std::cout << "SYNTAX ERROR: " << s << ", line " << yylineno << std::endl;
		num_error = 1;
	}

	void print_equal(char *s){ 
		if (operato == "equal"){}
		else if (operato == "add_eq") {std::cout << "PUSH " << s <<std::endl << "ADD" <<std::endl;}
		else if (operato == "sub_eq") {std::cout << "PUSH " << s <<std::endl << "SUB"<<std::endl;}
		else if (operato == "mult_eq") {std::cout << "PUSH " << s <<std::endl << "MULT"<<std::endl;}
		else if (operato == "div_eq") {std::cout << "PUSH " << s <<std::endl << "DIV"<<std::endl;}
		else if (operato == "mod_eq") {std::cout << "PUSH " << s <<std::endl << "MOD"<<std::endl;}
		else if (operato == "pushl_eq") {std::cout << "PUSH " << s <<std::endl << "PUSHL"<<std::endl;}
		else if (operato == "pushr_eq") {std::cout << "PUSH " << s <<std::endl << "PUSHR"<<std::endl;}
		else if (operato == "xor_eq") {std::cout << "PUSH " << s <<std::endl << "XOR"<<std::endl;}
		else if (operato == "or_eq") {std::cout << "PUSH " << s <<std::endl << "OR"<<std::endl;}
		else if (operato == "and_eq") {std::cout << "PUSH " << s <<std::endl << "AND"<<std::endl;}
	}
	
	
	int prior(std::string op) {
		if (op == "(") return 1;
		if (op == "OR") return 2;
		if (op == "XOR") return 3;
		if (op == "AND") return 4;
		if (op == "PUSHL" || op == "PUSHR") return 5;
		if (op == "ADD" || op == "SUB") return 6;
		if (op == "DIV" || op == "MULT" || op == "MOD") return 7;
		return 0;
	}

	bool is_operator(std::string cur) {
		if (cur == "ADD" || cur == "SUB" || cur == "DIV" || cur == "MULT") return true;
		if (cur == "MOD" || cur == "AND" || cur == "XOR" || cur == "OR") return true;
		if (cur == "PUSHL" || cur == "PUSHR") return true;
		if (strncmp(cur.c_str(),"INC",3) == 0 || strncmp(cur.c_str(),"DEC",3) == 0) return true;
		return false;
	}

	void convert_to_ppn() {
	
		std::string tmp_postfix;

		for (int i = 0; i < express.size(); i++) {
		
			std::string cur_s = express[i];			
			
			if (cur_s == "INC" or cur_s == "DEC"){
				//prefix
				if ( i != express.size() -1 && !is_operator(express[i+1]) && express[i+1] != "(" && express[i+1] != ")"){ //if var or number
					if (cur_s == "INC"){
						std::string tmp = "INC " + express[i+1];
						express_ppn.push_back(tmp);
					}
					else{
						std::string tmp = "DEC " + express[i+1];
						express_ppn.push_back(tmp);
					}
					continue;
				}
				else{
					if (cur_s == "INC") {
						tmp_postfix = "INC " + express[i-1];
						//std::cout<< "debug :"<<tmp_postfix << std:: endl;
						continue;
					}
					if (cur_s == "DEC") {
						tmp_postfix = "DEC " + express[i-1];
						continue;
					}
				}
			}
			
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
					if (!stack_t.empty() && (strncmp(stack_t.top().c_str(),"INC",3) == 0 || strncmp(stack_t.top().c_str(),"INC",3) == 0)) {
						tmp = stack_t.top();
						stack_t.pop();
						express_ppn.push_back(tmp);
					}	
				}
				if (stack_t.empty() || prior(cur_s) > prior(stack_t.top())) { //why only top
					if (!tmp_postfix.empty()) {
						stack_t.push(tmp_postfix);
					}
					tmp_postfix.clear();
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
	
	void clear_all(){
		operato.clear();
		unary_operator.clear();
		express.clear();
		express_ppn.clear();
		
		//label_counter
	}



%}

%union {
	char * string;
}

%token <string> NUMBER VAR

%destructor {free($$);} VAR
%destructor {free($$);} NUMBER
//%destructor {free($$);} INC
//%destructor {free($$);} DEC

%start command

%token IF ELSE WHILE RETURN PRINT ADD_EQ SUB_EQ MULT_EQ DIV_EQ MOD_EQ MORE_EQ LESS_EQ NOT_EQUAL EQUAL_DOUBLE PUSHL_EQ PUSHR_EQ PUSHL PUSHR MORE LESS XOR_EQ OR_EQ AND_EQ AND OR AND_SINGLE MINUS SEMICOLON EQUAL PLUS MULT DIV NOT MOD XOR OR_SINGLE INC DEC //NUMBER VAR


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
		assignment SEMICOLON {clear_all();}
		| unary_opertr VAR SEMICOLON {std::cout << unary_operator << " " << $2 << std::endl; clear_all();}
		| VAR unary_opertr SEMICOLON {std::cout << unary_operator << " " << $1 << std::endl;  clear_all();}
		| print SEMICOLON {clear_all();}
		| ret SEMICOLON {clear_all();}
		| if{clear_all();}
		| while{clear_all();}
		| command command
		;

assignment:
		VAR assign_operator expr {print_expr(); print_equal($1); printf("POP %s\n", $1);}
		;

expr: 
	expr bin_opertr expr 
	| INC VAR {express.push_back("INC"); express.push_back($2); }
	| DEC VAR {express.push_back("DEC"); express.push_back($2); }
	| VAR INC {express.push_back($1); express.push_back("INC"); }
	| VAR DEC {express.push_back($1); express.push_back("DEC"); }
	| VAR {ex_push_back($1);}
	| NUMBER {ex_push_back($1);}
	| '(' {express.push_back("(");} expr ')' {express.push_back(")");}
	;

print:
            PRINT '(' expr ')' {print_expr(); printf("PRINT\n");} //PRINT - prints top of the stack
            ;
ret:
            RETURN expr {print_expr(); printf("RET\n");} //RET - returns top of the stack
            |RETURN {printf("RET\n");}
            ;

//no need to be count operators after missing brackets bc it still right to syntax
if:    IF '(' bool_condition ')' '{' command '}' 
            | IF '(' bool_condition ')' '{' command '}' ELSE '{' command '}'
            | IF '(' bool_condition ')' '{' command '}' ELSE command
            | IF '(' bool_condition ')' command ELSE '{' command '}'
            //| IF '(' bool_condition ')' '{' command '}' ELSE if
            | IF '(' bool_condition ')'  command
            | IF '(' bool_condition ')'  command ELSE command
            //| IF '(' bool_condition ')'  command ELSE if
            ;

while: 
            WHILE '(' bool_condition ')' '{' command '}'
            | WHILE '('  bool_condition  ')' command
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
			EQUAL {operato = "equal";}
			| ADD_EQ {operato = "add_eq";}
			| SUB_EQ {operato = "sub_eq";}
			| MULT_EQ {operato = "mult_eq";}
			| DIV_EQ {operato = "div_eq";}
			| MOD_EQ {operato = "mod_eq";}
			| PUSHL_EQ {operato = "pushl_eq";}
			| PUSHR_EQ {operato = "pushr_eq";}
			| XOR_EQ {operato = "xor_eq";}
			| OR_EQ {operato = "or_eq";}
			| AND_EQ {operato = "and_eq";}
			;

comparison_operator:
/*">="	"<="	"!="	"=="	">"	"<"*/
			EQUAL_DOUBLE {express.push_back("JE");}
			| NOT_EQUAL {express.push_back("JNE");}
			| MORE_EQ {express.push_back("JGE");}
			| LESS_EQ {express.push_back("JLE");}
			| LESS {express.push_back("JL");}
			| MORE {express.push_back("JG");}
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
		INC {unary_operator = "INC";}
		|DEC {unary_operator ="DEC";}
		;

%%




int main() 
{
	yyparse();
	if(num_error==0)
		printf("OK\n");
}
