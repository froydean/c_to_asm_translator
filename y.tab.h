/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

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
#line 260 "parser.yacc"

	char * string;

#line 145 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
