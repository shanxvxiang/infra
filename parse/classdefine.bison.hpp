/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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

#ifndef YY_CLASSDEFINE_HOME_RAYMON_SOLUTION_INFRA_PARSE_CLASSDEFINE_BISON_HPP_INCLUDED
# define YY_CLASSDEFINE_HOME_RAYMON_SOLUTION_INFRA_PARSE_CLASSDEFINE_BISON_HPP_INCLUDED
/* Debug traces.  */
#ifndef CLASSDEFINEDEBUG
# if defined YYDEBUG
#if YYDEBUG
#   define CLASSDEFINEDEBUG 1
#  else
#   define CLASSDEFINEDEBUG 0
#  endif
# else /* ! defined YYDEBUG */
#  define CLASSDEFINEDEBUG 0
# endif /* ! defined YYDEBUG */
#endif  /* ! defined CLASSDEFINEDEBUG */
#if CLASSDEFINEDEBUG
extern int classdefinedebug;
#endif

/* Token type.  */
#ifndef CLASSDEFINETOKENTYPE
# define CLASSDEFINETOKENTYPE
  enum classdefinetokentype
  {
    K_CLASS = 258,
    K_INHERIT = 259,
    K_AGGREGATION = 260,
    K_UNIQUE = 261,
    K_ESSENTIAL = 262,
    K_ATTRIBUTE = 263,
    T_STRING = 264,
    T_INT = 265,
    T_PERCENT = 266,
    T_MONEY = 267,
    T_HASH = 268,
    T_TIME = 269,
    D_IDENTIFIER = 270,
    D_STRING = 271
  };
#endif

/* Value type.  */
#if ! defined CLASSDEFINESTYPE && ! defined CLASSDEFINESTYPE_IS_DECLARED
typedef int CLASSDEFINESTYPE;
# define CLASSDEFINESTYPE_IS_TRIVIAL 1
# define CLASSDEFINESTYPE_IS_DECLARED 1
#endif


extern CLASSDEFINESTYPE classdefinelval;

int classdefineparse (void);

#endif /* !YY_CLASSDEFINE_HOME_RAYMON_SOLUTION_INFRA_PARSE_CLASSDEFINE_BISON_HPP_INCLUDED  */
