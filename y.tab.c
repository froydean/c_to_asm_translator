/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parser.yacc"

	#include<iostream>
	#include <string.h>
	#include <vector>
	#include <stack>
	
	extern int yylineno;
	extern int yylex();
	bool num_error = 0;
	
	bool label_need = false;

	//char * operato = {0x00};
	std::string operato;
	
	std::string unary_operator;
	std::string cmp_op;
	std::string cmp_op_n;
	
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
		if (op == "CMP_OR") return 2;
		if (op == "CMP_AND") return 3;
		if (op == "OR") return 4;
		if (op == "XOR") return 5;
		if (op == "AND") return 6;
		if (op == "JE" || op == "JNE") return 7;
		if (op == "JGE" || op == "JLE" || op == "JG" || op == "JL" ) return 8;
		if (op == "PUSHL" || op == "PUSHR") return 9;
		if (op == "ADD" || op == "SUB") return 10;
		if (op == "DIV" || op == "MULT" || op == "MOD") return 11;
		return 0;
	}

	bool is_operator(std::string cur) {
		if (cur == "ADD" || cur == "SUB" || cur == "DIV" || cur == "MULT") return true;
		if (cur == "MOD" || cur == "AND" || cur == "XOR" || cur == "OR") return true;
		if (cur == "PUSHL" || cur == "PUSHR") return true;
		if (cur == "CMP_OR" || cur == "CMP_AND") return true;
		if (cur == "JE" || cur == "JNE") return true;
		if (cur == "JGE" || cur == "JLE" || cur == "JG" || cur == "JL" ) return true;
		if (strncmp(cur.c_str(),"INC",3) == 0 || strncmp(cur.c_str(),"DEC",3) == 0) return true;
		return false;
	}
	
	 std::string opposite_un_oper(std::string cur){
	 	//note
	 	if (cur == "CMP_OR") return "CMP_OR";
		if (cur == "CMP_AND") return "CMP_AND";
		
		if (cur == "JE") return "JNE";
		if (cur == "JNE") return "JE";
		if (cur == "JGE") return "JL";
		if (cur == "JLE") return "JG";
		if (cur == "JG") return "JLE";
		if (cur == "JL") return "JGE";

		return "none";
	}

	void convert_to_ppn() {
	
		//p();
	
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
			std::string tmp21 = opposite_un_oper(*i);
			if (tmp21 != "none"){
				if (tmp21 == "CMP_AND"){
					std::cout<<"CMP [stack_top], 1"<< std::endl<< "JL .L" << label_counter<<std::endl << "POP"<<std::endl;
					std::cout<<"CMP [stack_top], 1"<< std::endl<< "JL .L" << label_counter++<<std::endl <<"POP"<<std::endl;
					std::cout << "PUSH 1" << std::endl <<"JMP .L" << label_counter << std::endl;
					std::cout<<".L" <<label_counter-1<<std::endl << "PUSH 0" <<std::endl;
					std::cout<<".L" <<label_counter++ <<std::endl;
				}
				else if (tmp21 == "CMP_OR"){
					std::cout<<"CMP [stack_top], 1"<< std::endl<< "JGE .L" << label_counter++<<std::endl <<"POP"<<std::endl;
					std::cout<<"CMP [stack_top], 1"<< std::endl<< "JL .L" << label_counter++<<std::endl <<"POP"<<std::endl;
					std::cout<<".L" <<label_counter-2<<std::endl << "PUSH 1" <<std::endl <<"JMP .L" << label_counter << std::endl;
					std::cout<<".L" <<label_counter-1 << std::endl << "PUSH 0" <<std::endl;
					std::cout<<".L" <<label_counter++ << std::endl;
				}
				else{
					std::cout<< tmp21 << " .L" <<label_counter++<<std::endl;
					std::cout<<"PUSH 1"<<std::endl<<"JMP .L" <<label_counter++<<std::endl;
					std::cout<<".L" <<label_counter-2<<std::endl << "PUSH 0" <<std::endl;
					std::cout<<".L" <<label_counter-1 << std::endl;
				}
				continue;
			}
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
		//cmp_op.clear();
		//cmp_op_n.clear();
		
		//label_counter
		label_need = false;
	}
	
	void print_lol(){
		std::cout<<"CMP [stack_top], 1"<< std::endl<< "JL .L" << label_counter++ << std::endl;
	}


#line 323 "y.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    NUMBER = 258,
    VAR = 259,
    IF = 260,
    ELSE = 261,
    WHILE = 262,
    RETURN = 263,
    PRINT = 264,
    ADD_EQ = 265,
    SUB_EQ = 266,
    MULT_EQ = 267,
    DIV_EQ = 268,
    MOD_EQ = 269,
    MORE_EQ = 270,
    LESS_EQ = 271,
    NOT_EQUAL = 272,
    EQUAL_DOUBLE = 273,
    PUSHL_EQ = 274,
    PUSHR_EQ = 275,
    PUSHL = 276,
    PUSHR = 277,
    MORE = 278,
    LESS = 279,
    XOR_EQ = 280,
    OR_EQ = 281,
    AND_EQ = 282,
    AND = 283,
    OR = 284,
    AND_SINGLE = 285,
    MINUS = 286,
    SEMICOLON = 287,
    EQUAL = 288,
    PLUS = 289,
    MULT = 290,
    DIV = 291,
    NOT = 292,
    MOD = 293,
    XOR = 294,
    OR_SINGLE = 295,
    INC = 296,
    DEC = 297
  };
#endif
/* Tokens.  */
#define NUMBER 258
#define VAR 259
#define IF 260
#define ELSE 261
#define WHILE 262
#define RETURN 263
#define PRINT 264
#define ADD_EQ 265
#define SUB_EQ 266
#define MULT_EQ 267
#define DIV_EQ 268
#define MOD_EQ 269
#define MORE_EQ 270
#define LESS_EQ 271
#define NOT_EQUAL 272
#define EQUAL_DOUBLE 273
#define PUSHL_EQ 274
#define PUSHR_EQ 275
#define PUSHL 276
#define PUSHR 277
#define MORE 278
#define LESS 279
#define XOR_EQ 280
#define OR_EQ 281
#define AND_EQ 282
#define AND 283
#define OR 284
#define AND_SINGLE 285
#define MINUS 286
#define SEMICOLON 287
#define EQUAL 288
#define PLUS 289
#define MULT 290
#define DIV 291
#define NOT 292
#define MOD 293
#define XOR 294
#define OR_SINGLE 295
#define INC 296
#define DEC 297

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 254 "parser.yacc"

	char * string;

#line 463 "y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */



#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))

/* Stored state numbers (used for stacks). */
typedef yytype_int8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   185

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  47
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  21
/* YYNRULES -- Number of rules.  */
#define YYNRULES  66
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  95

#define YYUNDEFTOK  2
#define YYMAXUTOK   297


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      43,    44,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    45,     2,    46,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   282,   282,   283,   286,   287,   288,   289,   290,   291,
     292,   297,   300,   302,   303,   304,   305,   306,   307,   308,
     309,   310,   310,   314,   317,   318,   337,   338,   341,   342,
     345,   345,   345,   349,   349,   349,   354,   355,   356,   357,
     358,   359,   360,   361,   362,   363,   364,   369,   370,   371,
     372,   373,   374,   375,   376,   381,   382,   383,   384,   385,
     386,   387,   388,   389,   390,   395,   396
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "NUMBER", "VAR", "IF", "ELSE", "WHILE",
  "RETURN", "PRINT", "ADD_EQ", "SUB_EQ", "MULT_EQ", "DIV_EQ", "MOD_EQ",
  "MORE_EQ", "LESS_EQ", "NOT_EQUAL", "EQUAL_DOUBLE", "PUSHL_EQ",
  "PUSHR_EQ", "PUSHL", "PUSHR", "MORE", "LESS", "XOR_EQ", "OR_EQ",
  "AND_EQ", "AND", "OR", "AND_SINGLE", "MINUS", "SEMICOLON", "EQUAL",
  "PLUS", "MULT", "DIV", "NOT", "MOD", "XOR", "OR_SINGLE", "INC", "DEC",
  "'('", "')'", "'{'", "'}'", "$accept", "commands", "command",
  "assignment", "expr2", "expr", "$@1", "print", "ret", "body", "else",
  "if", "$@2", "$@3", "while", "$@4", "$@5", "assign_operator",
  "comparison_operator", "bin_opertr", "unary_opertr", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,    40,    41,   123,   125
};
# endif

#define YYPACT_NINF (-85)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -85,     2,   -85,    63,   -29,   -85,    27,   -25,   -85,   -85,
     -85,   -13,   -12,    -4,   -85,   -85,    23,   -85,   -85,   -85,
     -85,   -85,   -85,   -85,   -85,   -85,   -85,   -85,    27,    -3,
      27,   -11,   -85,   -37,    30,    31,   -85,   145,    27,   -85,
     -85,   -85,     4,   145,   -85,    -7,   145,    27,   -85,   -85,
     -85,   -85,    27,   -85,   -85,   -85,   -85,   -85,   -85,   -85,
     -85,   -85,   -85,   -85,   -85,   -85,   -85,   -85,   -85,   -85,
     -85,    27,    27,    85,   -85,   -85,    -6,   115,   145,   145,
     -85,    17,   -85,   -85,   -85,   -85,   -85,    17,     8,    33,
     -85,   -85,    17,   -85,   -85
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       2,     0,     1,     0,     0,    33,    25,     0,    65,    66,
       3,     0,     0,     0,     9,    10,     0,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    36,     0,     0,
       0,     0,    20,    19,     0,     0,    21,    24,     0,     4,
       7,     8,     0,    11,     6,     0,    12,     0,    17,    18,
      15,    16,     0,    49,    50,    48,    47,    63,    64,    52,
      51,    53,    54,    62,    55,    56,    57,    58,    59,    60,
      61,     0,     0,     0,     5,    30,     0,     0,    14,    13,
      23,     0,    34,    22,     2,    27,    31,     0,     0,    28,
      35,    26,     0,    32,    29
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -85,   -44,    -1,   -85,    -2,    -5,   -85,   -85,   -85,   -84,
     -85,   -85,   -85,   -85,   -85,   -85,   -85,   -85,   -85,   -85,
      38
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     1,    85,    11,    45,    46,    52,    12,    13,    86,
      93,    14,    81,    89,    15,    31,    87,    28,    71,    72,
      16
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      10,    37,     2,    90,    48,    49,     3,     4,    94,     5,
       6,     7,     3,     4,    30,     5,     6,     7,    38,    39,
      40,     3,     4,    43,     5,     6,     7,    42,    41,    44,
      32,    33,    47,    73,    50,    51,    74,    75,    82,    92,
      88,    29,     0,     8,     9,    76,     0,    77,     0,     8,
       9,     0,     0,     0,    91,     0,     0,     0,     8,     9,
       0,     0,    84,     0,     0,     0,    78,    79,    34,    35,
      36,     0,     0,    17,    18,    19,    20,    21,     0,     0,
       0,     0,    22,    23,     0,     0,     0,    10,    24,    25,
      26,     0,     0,     0,     0,     0,    27,     0,     0,     0,
      53,    54,    55,    56,     8,     9,    57,    58,    59,    60,
       0,     0,     0,    61,    62,    63,    64,     0,     0,    65,
      66,    67,     0,    68,    69,    70,     0,     0,     0,    80,
      53,    54,    55,    56,     0,     0,    57,    58,    59,    60,
       0,     0,     0,    61,    62,    63,    64,     0,     0,    65,
      66,    67,     0,    68,    69,    70,     0,     0,     0,    83,
      53,    54,    55,    56,     0,     0,    57,    58,    59,    60,
       0,     0,     0,    61,    62,    63,    64,     0,     0,    65,
      66,    67,     0,    68,    69,    70
};

static const yytype_int8 yycheck[] =
{
       1,     6,     0,    87,    41,    42,     4,     5,    92,     7,
       8,     9,     4,     5,    43,     7,     8,     9,    43,    32,
      32,     4,     5,    28,     7,     8,     9,     4,    32,    32,
       3,     4,    43,    38,     4,     4,    32,    44,    44,     6,
      84,     3,    -1,    41,    42,    47,    -1,    52,    -1,    41,
      42,    -1,    -1,    -1,    46,    -1,    -1,    -1,    41,    42,
      -1,    -1,    45,    -1,    -1,    -1,    71,    72,    41,    42,
      43,    -1,    -1,    10,    11,    12,    13,    14,    -1,    -1,
      -1,    -1,    19,    20,    -1,    -1,    -1,    88,    25,    26,
      27,    -1,    -1,    -1,    -1,    -1,    33,    -1,    -1,    -1,
      15,    16,    17,    18,    41,    42,    21,    22,    23,    24,
      -1,    -1,    -1,    28,    29,    30,    31,    -1,    -1,    34,
      35,    36,    -1,    38,    39,    40,    -1,    -1,    -1,    44,
      15,    16,    17,    18,    -1,    -1,    21,    22,    23,    24,
      -1,    -1,    -1,    28,    29,    30,    31,    -1,    -1,    34,
      35,    36,    -1,    38,    39,    40,    -1,    -1,    -1,    44,
      15,    16,    17,    18,    -1,    -1,    21,    22,    23,    24,
      -1,    -1,    -1,    28,    29,    30,    31,    -1,    -1,    34,
      35,    36,    -1,    38,    39,    40
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    48,     0,     4,     5,     7,     8,     9,    41,    42,
      49,    50,    54,    55,    58,    61,    67,    10,    11,    12,
      13,    14,    19,    20,    25,    26,    27,    33,    64,    67,
      43,    62,     3,     4,    41,    42,    43,    52,    43,    32,
      32,    32,     4,    52,    32,    51,    52,    43,    41,    42,
       4,     4,    53,    15,    16,    17,    18,    21,    22,    23,
      24,    28,    29,    30,    31,    34,    35,    36,    38,    39,
      40,    65,    66,    52,    32,    44,    51,    52,    52,    52,
      44,    59,    44,    44,    45,    49,    56,    63,    48,    60,
      56,    46,     6,    57,    56
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    47,    48,    48,    49,    49,    49,    49,    49,    49,
      49,    50,    51,    52,    52,    52,    52,    52,    52,    52,
      52,    53,    52,    54,    55,    55,    56,    56,    57,    57,
      59,    60,    58,    62,    63,    61,    64,    64,    64,    64,
      64,    64,    64,    64,    64,    64,    64,    65,    65,    65,
      65,    65,    65,    65,    65,    66,    66,    66,    66,    66,
      66,    66,    66,    66,    66,    67,    67
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     2,     3,     3,     2,     2,     1,
       1,     3,     1,     3,     3,     2,     2,     2,     2,     1,
       1,     0,     4,     4,     2,     1,     3,     1,     0,     2,
       0,     0,     8,     0,     0,     7,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  switch (yytype)
    {
    case 3: /* NUMBER  */
#line 261 "parser.yacc"
            {free(((*yyvaluep).string));}
#line 1466 "y.tab.c"
        break;

    case 4: /* VAR  */
#line 260 "parser.yacc"
            {free(((*yyvaluep).string));}
#line 1472 "y.tab.c"
        break;

      default:
        break;
    }
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 4:
#line 286 "parser.yacc"
                                     {clear_all();}
#line 1742 "y.tab.c"
    break;

  case 5:
#line 287 "parser.yacc"
                                             {std::cout << unary_operator << " " << (yyvsp[-1].string) << std::endl; clear_all();}
#line 1748 "y.tab.c"
    break;

  case 6:
#line 288 "parser.yacc"
                                             {std::cout << unary_operator << " " << (yyvsp[-2].string) << std::endl;  clear_all();}
#line 1754 "y.tab.c"
    break;

  case 7:
#line 289 "parser.yacc"
                                  {clear_all();}
#line 1760 "y.tab.c"
    break;

  case 8:
#line 290 "parser.yacc"
                                {clear_all();}
#line 1766 "y.tab.c"
    break;

  case 9:
#line 291 "parser.yacc"
                     {clear_all();}
#line 1772 "y.tab.c"
    break;

  case 10:
#line 292 "parser.yacc"
                        {clear_all();}
#line 1778 "y.tab.c"
    break;

  case 11:
#line 297 "parser.yacc"
                                         { print_expr(); print_equal((yyvsp[-2].string)); printf("POP %s\n", (yyvsp[-2].string));}
#line 1784 "y.tab.c"
    break;

  case 12:
#line 300 "parser.yacc"
             {print_expr(); clear_all();}
#line 1790 "y.tab.c"
    break;

  case 15:
#line 304 "parser.yacc"
                  {express.push_back("INC"); express.push_back((yyvsp[0].string)); }
#line 1796 "y.tab.c"
    break;

  case 16:
#line 305 "parser.yacc"
                  {express.push_back("DEC"); express.push_back((yyvsp[0].string)); }
#line 1802 "y.tab.c"
    break;

  case 17:
#line 306 "parser.yacc"
                  {express.push_back((yyvsp[-1].string)); express.push_back("INC"); }
#line 1808 "y.tab.c"
    break;

  case 18:
#line 307 "parser.yacc"
                  {express.push_back((yyvsp[-1].string)); express.push_back("DEC"); }
#line 1814 "y.tab.c"
    break;

  case 19:
#line 308 "parser.yacc"
              {ex_push_back((yyvsp[0].string));}
#line 1820 "y.tab.c"
    break;

  case 20:
#line 309 "parser.yacc"
                 {ex_push_back((yyvsp[0].string));}
#line 1826 "y.tab.c"
    break;

  case 21:
#line 310 "parser.yacc"
              {express.push_back("(");}
#line 1832 "y.tab.c"
    break;

  case 22:
#line 310 "parser.yacc"
                                                 {express.push_back(")");}
#line 1838 "y.tab.c"
    break;

  case 23:
#line 314 "parser.yacc"
                               {print_expr(); printf("PRINT\n");}
#line 1844 "y.tab.c"
    break;

  case 24:
#line 317 "parser.yacc"
                        {print_expr(); printf("RET\n");}
#line 1850 "y.tab.c"
    break;

  case 25:
#line 318 "parser.yacc"
                    {printf("RET\n");}
#line 1856 "y.tab.c"
    break;

  case 30:
#line 345 "parser.yacc"
                         {print_lol();}
#line 1862 "y.tab.c"
    break;

  case 31:
#line 345 "parser.yacc"
                                             {std::cout << "JMP .L"<< label_counter<< std::endl << ".L" << label_counter-1 << std::endl;}
#line 1868 "y.tab.c"
    break;

  case 32:
#line 345 "parser.yacc"
                                                                                                                                               {std::cout << ".L" << label_counter++ << std::endl;}
#line 1874 "y.tab.c"
    break;

  case 33:
#line 349 "parser.yacc"
              {std::cout << ".L" << label_counter++ << std::endl;}
#line 1880 "y.tab.c"
    break;

  case 34:
#line 349 "parser.yacc"
                                                                                 {print_lol();}
#line 1886 "y.tab.c"
    break;

  case 35:
#line 349 "parser.yacc"
                                                                                                     {std::cout << "JMP .L" <<label_counter-4 << std::endl<<".L" << label_counter-1 << std::endl;}
#line 1892 "y.tab.c"
    break;

  case 36:
#line 354 "parser.yacc"
                              {operato = "equal";}
#line 1898 "y.tab.c"
    break;

  case 37:
#line 355 "parser.yacc"
                                 {operato = "add_eq";}
#line 1904 "y.tab.c"
    break;

  case 38:
#line 356 "parser.yacc"
                                 {operato = "sub_eq";}
#line 1910 "y.tab.c"
    break;

  case 39:
#line 357 "parser.yacc"
                                  {operato = "mult_eq";}
#line 1916 "y.tab.c"
    break;

  case 40:
#line 358 "parser.yacc"
                                 {operato = "div_eq";}
#line 1922 "y.tab.c"
    break;

  case 41:
#line 359 "parser.yacc"
                                 {operato = "mod_eq";}
#line 1928 "y.tab.c"
    break;

  case 42:
#line 360 "parser.yacc"
                                   {operato = "pushl_eq";}
#line 1934 "y.tab.c"
    break;

  case 43:
#line 361 "parser.yacc"
                                   {operato = "pushr_eq";}
#line 1940 "y.tab.c"
    break;

  case 44:
#line 362 "parser.yacc"
                                 {operato = "xor_eq";}
#line 1946 "y.tab.c"
    break;

  case 45:
#line 363 "parser.yacc"
                                {operato = "or_eq";}
#line 1952 "y.tab.c"
    break;

  case 46:
#line 364 "parser.yacc"
                                 {operato = "and_eq";}
#line 1958 "y.tab.c"
    break;

  case 47:
#line 369 "parser.yacc"
                                     {express.push_back("JE");}
#line 1964 "y.tab.c"
    break;

  case 48:
#line 370 "parser.yacc"
                                    {express.push_back("JNE");}
#line 1970 "y.tab.c"
    break;

  case 49:
#line 371 "parser.yacc"
                                  {express.push_back("JGE");}
#line 1976 "y.tab.c"
    break;

  case 50:
#line 372 "parser.yacc"
                                  {express.push_back("JLE");}
#line 1982 "y.tab.c"
    break;

  case 51:
#line 373 "parser.yacc"
                               {express.push_back("JL");}
#line 1988 "y.tab.c"
    break;

  case 52:
#line 374 "parser.yacc"
                               {express.push_back("JG");}
#line 1994 "y.tab.c"
    break;

  case 53:
#line 375 "parser.yacc"
                              {express.push_back("CMP_AND");}
#line 2000 "y.tab.c"
    break;

  case 54:
#line 376 "parser.yacc"
                             {express.push_back("CMP_OR");}
#line 2006 "y.tab.c"
    break;

  case 55:
#line 381 "parser.yacc"
                      {express.push_back("SUB");}
#line 2012 "y.tab.c"
    break;

  case 56:
#line 382 "parser.yacc"
                       {express.push_back("ADD");}
#line 2018 "y.tab.c"
    break;

  case 57:
#line 383 "parser.yacc"
                       {express.push_back("MULT");}
#line 2024 "y.tab.c"
    break;

  case 58:
#line 384 "parser.yacc"
                      {express.push_back("DIV");}
#line 2030 "y.tab.c"
    break;

  case 59:
#line 385 "parser.yacc"
                      {express.push_back("MOD");}
#line 2036 "y.tab.c"
    break;

  case 60:
#line 386 "parser.yacc"
                      {express.push_back("XOR");}
#line 2042 "y.tab.c"
    break;

  case 61:
#line 387 "parser.yacc"
                            {express.push_back("OR");}
#line 2048 "y.tab.c"
    break;

  case 62:
#line 388 "parser.yacc"
                             {express.push_back("AND");}
#line 2054 "y.tab.c"
    break;

  case 63:
#line 389 "parser.yacc"
                        {express.push_back("PUSHL");}
#line 2060 "y.tab.c"
    break;

  case 64:
#line 390 "parser.yacc"
                        {express.push_back("PUSHR");}
#line 2066 "y.tab.c"
    break;

  case 65:
#line 395 "parser.yacc"
                    {unary_operator = "INC";}
#line 2072 "y.tab.c"
    break;

  case 66:
#line 396 "parser.yacc"
                     {unary_operator ="DEC";}
#line 2078 "y.tab.c"
    break;


#line 2082 "y.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[+*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 399 "parser.yacc"





int main() 
{
	yyparse();
	if(num_error==0)
		printf("OK\n");
}
