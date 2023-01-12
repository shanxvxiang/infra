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

#ifndef YY_CONFIGFILE_HOME_RAYMON_SOLUTION_INFRA_PARSE_CONFIGFILE_BISON_HPP_INCLUDED
# define YY_CONFIGFILE_HOME_RAYMON_SOLUTION_INFRA_PARSE_CONFIGFILE_BISON_HPP_INCLUDED
/* Debug traces.  */
#ifndef CONFIGFILEDEBUG
# if defined YYDEBUG
#if YYDEBUG
#   define CONFIGFILEDEBUG 1
#  else
#   define CONFIGFILEDEBUG 0
#  endif
# else /* ! defined YYDEBUG */
#  define CONFIGFILEDEBUG 0
# endif /* ! defined YYDEBUG */
#endif  /* ! defined CONFIGFILEDEBUG */
#if CONFIGFILEDEBUG
extern int configfiledebug;
#endif

/* Token type.  */
#ifndef CONFIGFILETOKENTYPE
# define CONFIGFILETOKENTYPE
  enum configfiletokentype
  {
    IDENTIFIER = 258,
    INT = 259,
    STRING = 260,
    IPADDRESS = 261
  };
#endif

/* Value type.  */
#if ! defined CONFIGFILESTYPE && ! defined CONFIGFILESTYPE_IS_DECLARED
typedef int CONFIGFILESTYPE;
# define CONFIGFILESTYPE_IS_TRIVIAL 1
# define CONFIGFILESTYPE_IS_DECLARED 1
#endif


extern CONFIGFILESTYPE configfilelval;

int configfileparse (void);

#endif /* !YY_CONFIGFILE_HOME_RAYMON_SOLUTION_INFRA_PARSE_CONFIGFILE_BISON_HPP_INCLUDED  */
