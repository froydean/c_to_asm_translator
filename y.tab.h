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
    INC = 260,
    DEC = 261,
    IF = 262,
    ELSE = 263,
    WHILE = 264,
    RETURN = 265,
    PRINT = 266,
    ADD_EQ = 267,
    SUB_EQ = 268,
    MULT_EQ = 269,
    DIV_EQ = 270,
    MOD_EQ = 271,
    MORE_EQ = 272,
    LESS_EQ = 273,
    NOT_EQUAL = 274,
    EQUAL_DOUBLE = 275,
    PUSHL_EQ = 276,
    PUSHR_EQ = 277,
    PUSHL = 278,
    PUSHR = 279,
    MORE = 280,
    LESS = 281,
    XOR_EQ = 282,
    OR_EQ = 283,
    AND_EQ = 284,
    AND = 285,
    OR = 286,
    AND_SINGLE = 287,
    MINUS = 288,
    SEMICOLON = 289,
    EQUAL = 290,
    PLUS = 291,
    MULT = 292,
    DIV = 293,
    NOT = 294,
    MOD = 295,
    XOR = 296,
    OR_SINGLE = 297
  };
#endif
/* Tokens.  */
#define NUMBER 258
#define VAR 259
#define INC 260
#define DEC 261
#define IF 262
#define ELSE 263
#define WHILE 264
#define RETURN 265
#define PRINT 266
#define ADD_EQ 267
#define SUB_EQ 268
#define MULT_EQ 269
#define DIV_EQ 270
#define MOD_EQ 271
#define MORE_EQ 272
#define LESS_EQ 273
#define NOT_EQUAL 274
#define EQUAL_DOUBLE 275
#define PUSHL_EQ 276
#define PUSHR_EQ 277
#define PUSHL 278
#define PUSHR 279
#define MORE 280
#define LESS 281
#define XOR_EQ 282
#define OR_EQ 283
#define AND_EQ 284
#define AND 285
#define OR 286
#define AND_SINGLE 287
#define MINUS 288
#define SEMICOLON 289
#define EQUAL 290
#define PLUS 291
#define MULT 292
#define DIV 293
#define NOT 294
#define MOD 295
#define XOR 296
#define OR_SINGLE 297

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 49 "parser.yacc"

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
