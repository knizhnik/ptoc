/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
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
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_ZZ_PARSER_H_INCLUDED
# define YY_ZZ_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int zzdebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    ARRAY = 258,                   /* ARRAY  */
    BEGIN = 259,                   /* BEGIN  */
    CASE = 260,                    /* CASE  */
    CONST = 261,                   /* CONST  */
    DO = 262,                      /* DO  */
    DOTS = 263,                    /* DOTS  */
    ELSE = 264,                    /* ELSE  */
    END = 265,                     /* END  */
    FIL = 266,                     /* FIL  */
    FAR = 267,                     /* FAR  */
    FOR = 268,                     /* FOR  */
    FUNCTION = 269,                /* FUNCTION  */
    GOTO = 270,                    /* GOTO  */
    IDENT = 271,                   /* IDENT  */
    ICONST = 272,                  /* ICONST  */
    IF = 273,                      /* IF  */
    IMPLEMENTATION = 274,          /* IMPLEMENTATION  */
    INTERFACE = 275,               /* INTERFACE  */
    LABEL = 276,                   /* LABEL  */
    LOOPHOLE = 277,                /* LOOPHOLE  */
    OBJECT = 278,                  /* OBJECT  */
    OF = 279,                      /* OF  */
    ORIGIN = 280,                  /* ORIGIN  */
    OTHERWISE = 281,               /* OTHERWISE  */
    PACKED = 282,                  /* PACKED  */
    PROCEDURE = 283,               /* PROCEDURE  */
    PROGRAM = 284,                 /* PROGRAM  */
    RCONST = 285,                  /* RCONST  */
    READ = 286,                    /* READ  */
    RECORD = 287,                  /* RECORD  */
    REPEAT = 288,                  /* REPEAT  */
    RETURN = 289,                  /* RETURN  */
    SET = 290,                     /* SET  */
    SCONST = 291,                  /* SCONST  */
    STRING = 292,                  /* STRING  */
    THEN = 293,                    /* THEN  */
    TO = 294,                      /* TO  */
    TYPE = 295,                    /* TYPE  */
    UNTIL = 296,                   /* UNTIL  */
    UNIT = 297,                    /* UNIT  */
    UNIT_END = 298,                /* UNIT_END  */
    VAR = 299,                     /* VAR  */
    WHILE = 300,                   /* WHILE  */
    WITH = 301,                    /* WITH  */
    WRITE = 302,                   /* WRITE  */
    SCOPE = 303,                   /* SCOPE  */
    LET = 304,                     /* LET  */
    LETADD = 305,                  /* LETADD  */
    LETSUB = 306,                  /* LETSUB  */
    LETDIV = 307,                  /* LETDIV  */
    LETMUL = 308,                  /* LETMUL  */
    LETAND = 309,                  /* LETAND  */
    LETOR = 310,                   /* LETOR  */
    LETSHL = 311,                  /* LETSHL  */
    LETSHR = 312,                  /* LETSHR  */
    EQ = 313,                      /* EQ  */
    NE = 314,                      /* NE  */
    LT = 315,                      /* LT  */
    LE = 316,                      /* LE  */
    GT = 317,                      /* GT  */
    GE = 318,                      /* GE  */
    IN = 319,                      /* IN  */
    PLUS = 320,                    /* PLUS  */
    MINUS = 321,                   /* MINUS  */
    OR = 322,                      /* OR  */
    XOR = 323,                     /* XOR  */
    BINOR = 324,                   /* BINOR  */
    MOD = 325,                     /* MOD  */
    DIV = 326,                     /* DIV  */
    DIVR = 327,                    /* DIVR  */
    MUL = 328,                     /* MUL  */
    AND = 329,                     /* AND  */
    SHR = 330,                     /* SHR  */
    SHL = 331,                     /* SHL  */
    BINAND = 332,                  /* BINAND  */
    UPLUS = 333,                   /* UPLUS  */
    UMINUS = 334,                  /* UMINUS  */
    NOT = 335,                     /* NOT  */
    ADDRESS = 336,                 /* ADDRESS  */
    BINNOT = 337                   /* BINNOT  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 28 "parser.y"

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

#line 182 "parser.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE zzlval;


int zzparse (void);


#endif /* !YY_ZZ_PARSER_H_INCLUDED  */
