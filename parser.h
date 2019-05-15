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

#ifndef YY_ZZ_PARSER_TAB_H_INCLUDED
# define YY_ZZ_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int zzdebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    ARRAY = 258,
    BEGIN = 259,
    CASE = 260,
    CONST = 261,
    DO = 262,
    DOTS = 263,
    ELSE = 264,
    END = 265,
    FIL = 266,
    FAR = 267,
    FOR = 268,
    FUNCTION = 269,
    GOTO = 270,
    IDENT = 271,
    ICONST = 272,
    IF = 273,
    IMPLEMENTATION = 274,
    INTERFACE = 275,
    LABEL = 276,
    LOOPHOLE = 277,
    OBJECT = 278,
    OF = 279,
    ORIGIN = 280,
    OTHERWISE = 281,
    PACKED = 282,
    PROCEDURE = 283,
    PROGRAM = 284,
    RCONST = 285,
    READ = 286,
    RECORD = 287,
    REPEAT = 288,
    RETURN = 289,
    SET = 290,
    SCONST = 291,
    STRING = 292,
    THEN = 293,
    TO = 294,
    TYPE = 295,
    UNTIL = 296,
    UNIT = 297,
    UNIT_END = 298,
    VAR = 299,
    WHILE = 300,
    WITH = 301,
    WRITE = 302,
    SCOPE = 303,
    LET = 304,
    LETADD = 305,
    LETSUB = 306,
    LETDIV = 307,
    LETMUL = 308,
    LETAND = 309,
    LETOR = 310,
    LETSHL = 311,
    LETSHR = 312,
    EQ = 313,
    NE = 314,
    LT = 315,
    LE = 316,
    GT = 317,
    GE = 318,
    IN = 319,
    PLUS = 320,
    MINUS = 321,
    OR = 322,
    XOR = 323,
    BINOR = 324,
    MOD = 325,
    DIV = 326,
    DIVR = 327,
    MUL = 328,
    AND = 329,
    SHR = 330,
    SHL = 331,
    BINAND = 332,
    UPLUS = 333,
    UMINUS = 334,
    NOT = 335,
    ADDRESS = 336,
    BINNOT = 337
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 28 "parser.y" /* yacc.c:1909  */

    token                *tok;

    token_list           *toks; 

    node                 *n_node;
    tpd_node             *n_tpd;
    block_node           *n_block; 
    stmt_node            *n_stmt; 
    decl_node            *n_decl; 
    expr_node            *n_expr; 
    expr_group_node      *n_grp; 

    write_param_node     *n_wrtp; 
    write_list_node      *n_wrls; 
    case_node            *n_case; 
    set_item_node        *n_item; 

    const_def_node       *n_cdef; 
    type_def_node        *n_tdef; 
    var_decl_node        *n_vdcl; 

    field_init_node      *n_field;
    
    param_list_node      *n_plist; 
    idx_node             *n_idx; 

    field_list_node      *n_fldls;
    variant_part_node    *n_varp;
    selector_node        *n_sel; 
    variant_node         *n_vari;
    compound_node        *n_comp;
   
    import_list_node     *n_imp; 

#line 173 "parser.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE zzlval;

int zzparse (void);

#endif /* !YY_ZZ_PARSER_TAB_H_INCLUDED  */
