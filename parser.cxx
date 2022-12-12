/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1


/* Substitute the variable and function names.  */
#define yyparse         zzparse
#define yylex           zzlex
#define yyerror         zzerror
#define yydebug         zzdebug
#define yynerrs         zznerrs
#define yylval          zzlval
#define yychar          zzchar

/* First part of user prologue.  */
#line 1 "parser.y"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "nmtbl.h"
#include "token.h"
#include "trnod.h"
#include "util.h"
#include "parser.h"

static int zzcnv_table[] = {
#define DEF_TOKEN(mnem, cat, cls, yacc) yacc,
#include "token.dpp"
};

#define YYINITDEPTH 100000

void zzerror(char* text) 
{
    error(curr_token, "syntax error: %s", text); 
}


#line 104 "parser.cxx"

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

#include "parser.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_ARRAY = 3,                      /* ARRAY  */
  YYSYMBOL_BEGIN = 4,                      /* BEGIN  */
  YYSYMBOL_CASE = 5,                       /* CASE  */
  YYSYMBOL_CONST = 6,                      /* CONST  */
  YYSYMBOL_DO = 7,                         /* DO  */
  YYSYMBOL_DOTS = 8,                       /* DOTS  */
  YYSYMBOL_ELSE = 9,                       /* ELSE  */
  YYSYMBOL_END = 10,                       /* END  */
  YYSYMBOL_FIL = 11,                       /* FIL  */
  YYSYMBOL_FAR = 12,                       /* FAR  */
  YYSYMBOL_FOR = 13,                       /* FOR  */
  YYSYMBOL_FUNCTION = 14,                  /* FUNCTION  */
  YYSYMBOL_GOTO = 15,                      /* GOTO  */
  YYSYMBOL_IDENT = 16,                     /* IDENT  */
  YYSYMBOL_ICONST = 17,                    /* ICONST  */
  YYSYMBOL_IF = 18,                        /* IF  */
  YYSYMBOL_IMPLEMENTATION = 19,            /* IMPLEMENTATION  */
  YYSYMBOL_INTERFACE = 20,                 /* INTERFACE  */
  YYSYMBOL_LABEL = 21,                     /* LABEL  */
  YYSYMBOL_LOOPHOLE = 22,                  /* LOOPHOLE  */
  YYSYMBOL_OBJECT = 23,                    /* OBJECT  */
  YYSYMBOL_OF = 24,                        /* OF  */
  YYSYMBOL_ORIGIN = 25,                    /* ORIGIN  */
  YYSYMBOL_OTHERWISE = 26,                 /* OTHERWISE  */
  YYSYMBOL_PACKED = 27,                    /* PACKED  */
  YYSYMBOL_PROCEDURE = 28,                 /* PROCEDURE  */
  YYSYMBOL_PROGRAM = 29,                   /* PROGRAM  */
  YYSYMBOL_RCONST = 30,                    /* RCONST  */
  YYSYMBOL_READ = 31,                      /* READ  */
  YYSYMBOL_RECORD = 32,                    /* RECORD  */
  YYSYMBOL_REPEAT = 33,                    /* REPEAT  */
  YYSYMBOL_RETURN = 34,                    /* RETURN  */
  YYSYMBOL_SET = 35,                       /* SET  */
  YYSYMBOL_SCONST = 36,                    /* SCONST  */
  YYSYMBOL_STRING = 37,                    /* STRING  */
  YYSYMBOL_THEN = 38,                      /* THEN  */
  YYSYMBOL_TO = 39,                        /* TO  */
  YYSYMBOL_TYPE = 40,                      /* TYPE  */
  YYSYMBOL_UNTIL = 41,                     /* UNTIL  */
  YYSYMBOL_UNIT = 42,                      /* UNIT  */
  YYSYMBOL_UNIT_END = 43,                  /* UNIT_END  */
  YYSYMBOL_VAR = 44,                       /* VAR  */
  YYSYMBOL_WHILE = 45,                     /* WHILE  */
  YYSYMBOL_WITH = 46,                      /* WITH  */
  YYSYMBOL_WRITE = 47,                     /* WRITE  */
  YYSYMBOL_48_ = 48,                       /* '.'  */
  YYSYMBOL_49_ = 49,                       /* ','  */
  YYSYMBOL_50_ = 50,                       /* ':'  */
  YYSYMBOL_51_ = 51,                       /* ';'  */
  YYSYMBOL_52_ = 52,                       /* '('  */
  YYSYMBOL_53_ = 53,                       /* ')'  */
  YYSYMBOL_54_ = 54,                       /* '['  */
  YYSYMBOL_55_ = 55,                       /* ']'  */
  YYSYMBOL_56_ = 56,                       /* '^'  */
  YYSYMBOL_57_ = 57,                       /* '@'  */
  YYSYMBOL_SCOPE = 58,                     /* SCOPE  */
  YYSYMBOL_LET = 59,                       /* LET  */
  YYSYMBOL_LETADD = 60,                    /* LETADD  */
  YYSYMBOL_LETSUB = 61,                    /* LETSUB  */
  YYSYMBOL_LETDIV = 62,                    /* LETDIV  */
  YYSYMBOL_LETMUL = 63,                    /* LETMUL  */
  YYSYMBOL_LETAND = 64,                    /* LETAND  */
  YYSYMBOL_LETOR = 65,                     /* LETOR  */
  YYSYMBOL_LETSHL = 66,                    /* LETSHL  */
  YYSYMBOL_LETSHR = 67,                    /* LETSHR  */
  YYSYMBOL_EQ = 68,                        /* EQ  */
  YYSYMBOL_NE = 69,                        /* NE  */
  YYSYMBOL_LT = 70,                        /* LT  */
  YYSYMBOL_LE = 71,                        /* LE  */
  YYSYMBOL_GT = 72,                        /* GT  */
  YYSYMBOL_GE = 73,                        /* GE  */
  YYSYMBOL_IN = 74,                        /* IN  */
  YYSYMBOL_PLUS = 75,                      /* PLUS  */
  YYSYMBOL_MINUS = 76,                     /* MINUS  */
  YYSYMBOL_OR = 77,                        /* OR  */
  YYSYMBOL_XOR = 78,                       /* XOR  */
  YYSYMBOL_BINOR = 79,                     /* BINOR  */
  YYSYMBOL_MOD = 80,                       /* MOD  */
  YYSYMBOL_DIV = 81,                       /* DIV  */
  YYSYMBOL_DIVR = 82,                      /* DIVR  */
  YYSYMBOL_MUL = 83,                       /* MUL  */
  YYSYMBOL_AND = 84,                       /* AND  */
  YYSYMBOL_SHR = 85,                       /* SHR  */
  YYSYMBOL_SHL = 86,                       /* SHL  */
  YYSYMBOL_BINAND = 87,                    /* BINAND  */
  YYSYMBOL_UPLUS = 88,                     /* UPLUS  */
  YYSYMBOL_UMINUS = 89,                    /* UMINUS  */
  YYSYMBOL_NOT = 90,                       /* NOT  */
  YYSYMBOL_ADDRESS = 91,                   /* ADDRESS  */
  YYSYMBOL_BINNOT = 92,                    /* BINNOT  */
  YYSYMBOL_YYACCEPT = 93,                  /* $accept  */
  YYSYMBOL_translation = 94,               /* translation  */
  YYSYMBOL_95_1 = 95,                      /* $@1  */
  YYSYMBOL_input_file = 96,                /* input_file  */
  YYSYMBOL_program = 97,                   /* program  */
  YYSYMBOL_progend = 98,                   /* progend  */
  YYSYMBOL_module = 99,                    /* module  */
  YYSYMBOL_unit = 100,                     /* unit  */
  YYSYMBOL_unit_def_list = 101,            /* unit_def_list  */
  YYSYMBOL_prog_param_list = 102,          /* prog_param_list  */
  YYSYMBOL_ident_list = 103,               /* ident_list  */
  YYSYMBOL_block = 104,                    /* block  */
  YYSYMBOL_decl_part_list = 105,           /* decl_part_list  */
  YYSYMBOL_decl_part = 106,                /* decl_part  */
  YYSYMBOL_unit_spec = 107,                /* unit_spec  */
  YYSYMBOL_unit_decl_list = 108,           /* unit_decl_list  */
  YYSYMBOL_unit_decl = 109,                /* unit_decl  */
  YYSYMBOL_statement = 110,                /* statement  */
  YYSYMBOL_compoundst = 111,               /* compoundst  */
  YYSYMBOL_sequence = 112,                 /* sequence  */
  YYSYMBOL_actual_params = 113,            /* actual_params  */
  YYSYMBOL_write_params = 114,             /* write_params  */
  YYSYMBOL_case_list = 115,                /* case_list  */
  YYSYMBOL_otherwise = 116,                /* otherwise  */
  YYSYMBOL_case_items = 117,               /* case_items  */
  YYSYMBOL_case_item = 118,                /* case_item  */
  YYSYMBOL_case_elem_list = 119,           /* case_elem_list  */
  YYSYMBOL_case_elem = 120,                /* case_elem  */
  YYSYMBOL_expr = 121,                     /* expr  */
  YYSYMBOL_simple_expr = 122,              /* simple_expr  */
  YYSYMBOL_primary = 123,                  /* primary  */
  YYSYMBOL_constant = 124,                 /* constant  */
  YYSYMBOL_set_elem_list = 125,            /* set_elem_list  */
  YYSYMBOL_set_elem = 126,                 /* set_elem  */
  YYSYMBOL_expr_list = 127,                /* expr_list  */
  YYSYMBOL_act_param_list = 128,           /* act_param_list  */
  YYSYMBOL_act_param = 129,                /* act_param  */
  YYSYMBOL_record_constant = 130,          /* record_constant  */
  YYSYMBOL_field_init_list = 131,          /* field_init_list  */
  YYSYMBOL_field_init_item = 132,          /* field_init_item  */
  YYSYMBOL_expr_group = 133,               /* expr_group  */
  YYSYMBOL_write_list = 134,               /* write_list  */
  YYSYMBOL_write_param = 135,              /* write_param  */
  YYSYMBOL_label_decl_part = 136,          /* label_decl_part  */
  YYSYMBOL_label_list = 137,               /* label_list  */
  YYSYMBOL_const_def_part = 138,           /* const_def_part  */
  YYSYMBOL_const_def_list = 139,           /* const_def_list  */
  YYSYMBOL_const_def = 140,                /* const_def  */
  YYSYMBOL_type_def_part = 141,            /* type_def_part  */
  YYSYMBOL_type_def_list = 142,            /* type_def_list  */
  YYSYMBOL_type_def = 143,                 /* type_def  */
  YYSYMBOL_var_decl_part = 144,            /* var_decl_part  */
  YYSYMBOL_var_decl_list = 145,            /* var_decl_list  */
  YYSYMBOL_var_decl = 146,                 /* var_decl  */
  YYSYMBOL_proc_decl = 147,                /* proc_decl  */
  YYSYMBOL_proc_fwd_decl = 148,            /* proc_fwd_decl  */
  YYSYMBOL_proc_spec = 149,                /* proc_spec  */
  YYSYMBOL_proc_def = 150,                 /* proc_def  */
  YYSYMBOL_qualifiers = 151,               /* qualifiers  */
  YYSYMBOL_formal_params = 152,            /* formal_params  */
  YYSYMBOL_formal_param_list = 153,        /* formal_param_list  */
  YYSYMBOL_formal_param = 154,             /* formal_param  */
  YYSYMBOL_param_decl = 155,               /* param_decl  */
  YYSYMBOL_param_type = 156,               /* param_type  */
  YYSYMBOL_type = 157,                     /* type  */
  YYSYMBOL_const_type = 158,               /* const_type  */
  YYSYMBOL_fptr_type = 159,                /* fptr_type  */
  YYSYMBOL_string_type = 160,              /* string_type  */
  YYSYMBOL_simple_type = 161,              /* simple_type  */
  YYSYMBOL_array_type = 162,               /* array_type  */
  YYSYMBOL_const_array_type = 163,         /* const_array_type  */
  YYSYMBOL_conformant_array_type = 164,    /* conformant_array_type  */
  YYSYMBOL_enum_type = 165,                /* enum_type  */
  YYSYMBOL_range_type = 166,               /* range_type  */
  YYSYMBOL_pointer_type = 167,             /* pointer_type  */
  YYSYMBOL_set_type = 168,                 /* set_type  */
  YYSYMBOL_const_set_type = 169,           /* const_set_type  */
  YYSYMBOL_record_type = 170,              /* record_type  */
  YYSYMBOL_object_type = 171,              /* object_type  */
  YYSYMBOL_object_components = 172,        /* object_components  */
  YYSYMBOL_object_fields = 173,            /* object_fields  */
  YYSYMBOL_field_decl_list = 174,          /* field_decl_list  */
  YYSYMBOL_object_methods = 175,           /* object_methods  */
  YYSYMBOL_file_type = 176,                /* file_type  */
  YYSYMBOL_packed = 177,                   /* packed  */
  YYSYMBOL_conformant_indices = 178,       /* conformant_indices  */
  YYSYMBOL_conformant_index = 179,         /* conformant_index  */
  YYSYMBOL_indices = 180,                  /* indices  */
  YYSYMBOL_index_spec = 181,               /* index_spec  */
  YYSYMBOL_field_list = 182,               /* field_list  */
  YYSYMBOL_fixed_part = 183,               /* fixed_part  */
  YYSYMBOL_variant_part = 184,             /* variant_part  */
  YYSYMBOL_selector = 185,                 /* selector  */
  YYSYMBOL_variant_list = 186,             /* variant_list  */
  YYSYMBOL_variant = 187                   /* variant  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




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

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
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
typedef yytype_int16 yy_state_t;

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
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
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

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

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
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1350

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  93
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  95
/* YYNRULES -- Number of rules.  */
#define YYNRULES  273
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  555

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   337


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      52,    53,     2,     2,    49,     2,    48,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    50,    51,
       2,     2,     2,     2,    57,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    54,     2,    55,    56,     2,     2,     2,     2,     2,
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
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   262,   262,   262,   286,   286,   286,   288,   289,   294,
     294,   296,   297,   305,   307,   309,   311,   314,   317,   318,
     320,   321,   323,   328,   329,   331,   331,   331,   331,   332,
     332,   332,   334,   336,   340,   341,   343,   343,   343,   343,
     344,   344,   344,   373,   374,   375,   376,   377,   378,   379,
     380,   381,   382,   383,   384,   385,   386,   387,   389,   391,
     392,   393,   394,   395,   396,   397,   398,   399,   400,   402,
     404,   404,   406,   406,   408,   409,   411,   412,   424,   424,
     426,   427,   428,   430,   432,   433,   435,   436,   460,   461,
     462,   463,   464,   465,   466,   468,   469,   470,   471,   472,
     473,   474,   475,   476,   479,   480,   481,   482,   483,   484,
     485,   487,   488,   489,   490,   491,   492,   493,   495,   496,
     498,   500,   502,   504,   505,   507,   508,   509,   510,   511,
     512,   513,   515,   516,   517,   518,   519,   520,   522,   523,
     524,   526,   527,   529,   529,   531,   532,   534,   534,   537,
     541,   542,   544,   547,   550,   550,   552,   553,   554,   596,
     599,   600,   601,   602,   604,   607,   608,   610,   611,   613,
     616,   617,   619,   621,   624,   625,   626,   631,   637,   639,
     640,   644,   646,   651,   653,   657,   659,   663,   665,   667,
     669,   671,   673,   675,   677,   680,   681,   682,   683,   686,
     687,   689,   690,   692,   693,   693,   695,   696,   698,   698,
     704,   704,   704,   704,   704,   704,   705,   705,   705,   705,
     705,   707,   707,   707,   707,   707,   709,   711,   713,   715,
     716,   718,   721,   724,   726,   729,   731,   734,   736,   738,
     740,   743,   745,   748,   750,   751,   753,   756,   757,   758,
     760,   760,   761,   762,   766,   768,   768,   770,   771,   773,
     776,   776,   779,   780,   784,   786,   789,   791,   796,   797,
     800,   801,   802,   804
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "ARRAY", "BEGIN",
  "CASE", "CONST", "DO", "DOTS", "ELSE", "END", "FIL", "FAR", "FOR",
  "FUNCTION", "GOTO", "IDENT", "ICONST", "IF", "IMPLEMENTATION",
  "INTERFACE", "LABEL", "LOOPHOLE", "OBJECT", "OF", "ORIGIN", "OTHERWISE",
  "PACKED", "PROCEDURE", "PROGRAM", "RCONST", "READ", "RECORD", "REPEAT",
  "RETURN", "SET", "SCONST", "STRING", "THEN", "TO", "TYPE", "UNTIL",
  "UNIT", "UNIT_END", "VAR", "WHILE", "WITH", "WRITE", "'.'", "','", "':'",
  "';'", "'('", "')'", "'['", "']'", "'^'", "'@'", "SCOPE", "LET",
  "LETADD", "LETSUB", "LETDIV", "LETMUL", "LETAND", "LETOR", "LETSHL",
  "LETSHR", "EQ", "NE", "LT", "LE", "GT", "GE", "IN", "PLUS", "MINUS",
  "OR", "XOR", "BINOR", "MOD", "DIV", "DIVR", "MUL", "AND", "SHR", "SHL",
  "BINAND", "UPLUS", "UMINUS", "NOT", "ADDRESS", "BINNOT", "$accept",
  "translation", "$@1", "input_file", "program", "progend", "module",
  "unit", "unit_def_list", "prog_param_list", "ident_list", "block",
  "decl_part_list", "decl_part", "unit_spec", "unit_decl_list",
  "unit_decl", "statement", "compoundst", "sequence", "actual_params",
  "write_params", "case_list", "otherwise", "case_items", "case_item",
  "case_elem_list", "case_elem", "expr", "simple_expr", "primary",
  "constant", "set_elem_list", "set_elem", "expr_list", "act_param_list",
  "act_param", "record_constant", "field_init_list", "field_init_item",
  "expr_group", "write_list", "write_param", "label_decl_part",
  "label_list", "const_def_part", "const_def_list", "const_def",
  "type_def_part", "type_def_list", "type_def", "var_decl_part",
  "var_decl_list", "var_decl", "proc_decl", "proc_fwd_decl", "proc_spec",
  "proc_def", "qualifiers", "formal_params", "formal_param_list",
  "formal_param", "param_decl", "param_type", "type", "const_type",
  "fptr_type", "string_type", "simple_type", "array_type",
  "const_array_type", "conformant_array_type", "enum_type", "range_type",
  "pointer_type", "set_type", "const_set_type", "record_type",
  "object_type", "object_components", "object_fields", "field_decl_list",
  "object_methods", "file_type", "packed", "conformant_indices",
  "conformant_index", "indices", "index_spec", "field_list", "fixed_part",
  "variant_part", "selector", "variant_list", "variant", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-398)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-230)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -398,    24,   927,  -398,     6,    65,  1079,    28,    94,   100,
     107,   112,   116,  -398,  -398,  -398,  -398,    15,   130,  1082,
    -398,  -398,  -398,  -398,  -398,  -398,  -398,   -33,  -398,    97,
     129,   135,  1079,   159,   212,  -398,     8,  1079,  -398,  -398,
    -398,  -398,  -398,  -398,   188,   190,   203,    73,   189,   192,
    -398,   210,   215,     7,   218,  -398,   220,  -398,   971,  -398,
    -398,    90,   762,     6,   261,   455,   110,   228,   227,   241,
     227,   238,  1082,  -398,  -398,    28,    28,  -398,   274,   243,
     279,   246,   668,   107,   278,   762,   279,   668,     3,   762,
     284,   140,   252,   253,   762,   255,  -398,   256,   971,  -398,
    -398,   762,   762,   257,   806,   762,   259,  -398,   294,  1263,
    -398,  -398,  -398,  -398,   263,   247,  -398,  -398,  -398,  -398,
    -398,    45,  -398,  -398,   229,   762,   762,   229,   762,   762,
    1223,  -398,  1283,  -398,   227,   260,   268,   130,   304,   272,
     306,   279,   273,  -398,   275,   276,  -398,   668,   280,   281,
     309,    72,  -398,  -398,  -398,   227,    91,   282,  1082,   227,
     930,   206,   227,   817,   668,   483,  -398,  -398,  -398,  -398,
    -398,  -398,  -398,  -398,  -398,  -398,  -398,  -398,    22,  -398,
    1079,  1059,  -398,  -398,   283,  -398,   842,   267,  -398,  -398,
     971,   971,   535,   668,   762,  -398,  -398,   292,   434,   997,
     329,   762,  -398,   289,   293,   295,   286,   514,   285,   296,
     971,  -398,   326,   762,   762,  -398,   762,   762,   762,   762,
     762,   762,   762,   762,   762,   762,   762,   298,   116,   323,
     184,  -398,   184,  -398,   184,  -398,  -398,   762,   762,   762,
     762,   762,   762,   762,   762,   762,   762,   762,   762,   762,
     762,   762,   762,   762,   762,   762,   762,   762,   762,   762,
     762,   762,   762,   762,   762,   762,   299,  1082,  -398,   227,
     227,  -398,   113,  -398,   110,   302,   668,    12,  1079,   310,
     313,   311,   312,    12,    12,   325,   331,  -398,   316,    11,
     300,   364,   335,    87,    87,   378,    87,  -398,  -398,  -398,
     180,   338,  -398,   762,   341,   368,   372,    19,    93,   116,
     762,   762,  -398,  -398,   971,   348,   345,   762,   971,   762,
     971,  1097,   346,   351,   762,  -398,  -398,   387,   762,  -398,
     762,  -398,  -398,  1223,   352,   355,   353,  1223,  1223,  1223,
    1223,  1223,  1223,  1223,  1223,  1223,  1203,  1223,   737,  -398,
     396,   404,    90,   631,   631,   631,   631,   631,   631,   631,
     287,   287,   287,   287,   287,  -398,  -398,  -398,  -398,  -398,
    -398,  -398,  -398,  1223,  1223,  1223,  1223,  1223,  1223,  1223,
    1223,  1223,   668,   359,   361,  -398,  -398,  -398,  -398,  -398,
     409,  -398,   373,   363,   376,  -398,  -398,  1082,  1082,  -398,
    -398,  -398,  -398,  -398,  -398,  -398,   668,   370,   116,  -398,
    -398,  -398,  -398,  -398,  1223,   737,   668,   668,  1082,  -398,
    -398,  -398,   406,    49,   379,   371,   380,   563,   958,   418,
     762,  -398,  1223,  -398,  -398,  -398,   762,  -398,   762,  1223,
     289,  -398,  1223,  -398,  -398,   762,  -398,  -398,   594,  -398,
     381,   384,  -398,   712,  -398,  -398,   386,  -398,   668,   391,
     395,   397,   398,    12,   399,   400,  -398,   207,  -398,   392,
    -398,  -398,    89,  -398,  -398,  -398,   971,   762,   971,   762,
     762,   762,   971,  1170,  1135,  -398,  -398,   762,   411,   737,
       5,  -398,   428,  1082,  -398,   437,  1082,  -398,  -398,  -398,
    -398,   446,   436,   416,   417,  -398,  -398,  -398,  -398,  1223,
     463,  -398,  -398,   762,  1223,    90,  -398,   668,   762,   420,
     460,   422,   421,   427,  -398,   668,  -398,  -398,   971,  1223,
    -398,  -398,   423,  -398,   429,  -398,   465,   458,   437,  -398,
    -398,  -398,   435,   762,   439,   113,  -398,   116,  -398,   668,
    -398,  -398,   426,  -398,  -398
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int16 yydefact[] =
{
       2,     0,    23,     1,   165,     0,    34,     0,     0,     0,
     170,     0,   174,     3,     4,     5,     6,     0,    11,    23,
      31,    25,    26,    27,    28,    30,    29,     0,   164,     0,
     199,     0,    34,     0,     0,    42,     0,    34,    36,    37,
      38,    39,    41,    40,   162,   160,     0,   199,    18,     0,
     169,     0,     0,    21,     0,   173,   175,     7,    43,    22,
      24,   255,     0,   165,     0,    23,     0,     0,   199,     0,
     199,     0,    23,    33,    35,     0,     0,   159,     0,     0,
       0,     0,   255,   170,     0,     0,     0,   255,   174,     0,
       0,     0,   137,   133,     0,     0,   134,    72,    43,    64,
     135,     0,     0,    74,     0,   138,    70,    68,     0,    63,
     125,   132,   229,   256,   230,     0,   225,   221,   222,   224,
     223,     0,   137,   133,     0,     0,     0,     0,     0,     0,
     167,    88,   118,   166,   199,     0,     0,     0,     0,    21,
       0,     0,   207,   205,     0,   201,   204,   255,     0,     0,
       0,     0,    17,   163,   161,   199,    23,     0,    23,   199,
     137,     0,   199,     0,   255,     0,   172,   220,   219,   210,
     211,   217,   218,   216,   214,   212,   213,   215,     0,   171,
      34,     0,    20,   179,   176,   178,     0,     0,    54,    53,
      43,    43,     0,   255,     0,    62,    73,     0,     0,   143,
       0,     0,    61,   137,     0,     0,   150,   141,     0,   139,
      43,    69,     0,   148,     0,   129,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   174,     0,
     123,   119,   118,   120,   124,   121,   122,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    23,   191,   199,
     199,   203,   255,   200,     0,     0,   255,   185,    34,     0,
       0,     0,     0,   197,   198,     0,     0,    19,     0,     9,
       0,     0,   247,   250,   251,     0,   245,   246,   244,   227,
     137,     0,   237,     0,     0,     0,     0,     0,     0,   174,
      80,     0,    67,    66,    43,     0,     0,     0,    43,     0,
      43,   156,     0,   154,     0,   126,   149,     0,     0,   136,
     138,    71,   128,   147,     0,   145,     0,    44,    45,    46,
      47,    48,    49,    50,    51,    52,     0,   168,     0,   266,
       0,   265,   255,   115,   116,   112,   113,   111,   114,   117,
      89,    90,   108,   110,   109,    91,    93,    94,    92,   104,
     107,   106,   105,    95,    96,    97,    98,    99,   102,   103,
     100,   101,   255,     0,     0,   181,   230,   206,   208,   209,
       0,   202,    23,     0,     0,    15,    16,    23,    23,   195,
     196,   187,   183,     8,    10,    12,   255,     0,   248,   252,
     253,   241,   243,   235,   236,     0,   255,   255,    23,    32,
     180,   177,     0,    76,    81,     0,    84,    86,     0,    56,
       0,   153,    60,    59,   144,    65,     0,    75,     0,   152,
       0,   151,   142,   140,   127,   148,   130,   228,     0,   262,
       0,   260,   240,   255,   264,   239,     0,   194,   255,     0,
       0,     0,     0,   186,     0,     0,   226,     0,   249,     0,
     254,   238,     0,    55,    79,    78,    43,    80,    43,     0,
       0,     0,    43,     0,   157,   155,   146,     0,     0,     0,
     137,   269,     0,    23,   182,     0,    23,   188,   184,   189,
     192,     0,     0,     0,     0,    77,    82,    83,    85,    87,
       0,    57,   131,     0,   263,   255,   261,   255,     0,     0,
       0,     0,   257,     0,   242,   255,    13,    14,    43,   158,
     232,   268,     0,   267,   270,   190,     0,     0,     0,   193,
     231,    58,     0,   271,     0,   255,   258,   174,   272,   255,
     233,   234,     0,   259,   273
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -398,  -398,  -398,  -398,  -398,  -398,  -398,  -398,    68,  -398,
     -43,   -54,     2,  -398,    34,    -6,  -398,  -177,   -15,   -92,
    -398,  -398,  -398,  -398,    16,  -398,    13,  -398,   -55,   124,
     -38,  -398,   164,  -398,  -100,    51,  -398,  -398,   173,  -398,
    -398,    85,  -398,    35,   142,    36,   438,  -398,    46,   441,
    -398,    47,    -3,  -151,  -398,    63,  -149,  -398,  -219,   108,
     251,  -398,   385,  -398,   -51,  -336,  -398,   -56,   -61,  -398,
    -398,   -18,  -398,  -398,  -398,  -398,  -398,   -53,  -398,    61,
    -398,   121,    -8,  -398,   -60,    37,  -398,  -397,  -398,    25,
    -398,  -398,  -398,    31,  -398
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,     1,     2,    13,    14,   405,    15,    16,   151,    81,
      54,    17,   137,    19,    20,    36,    37,   106,   107,   108,
     195,   202,   422,   476,   423,   424,   425,   426,   165,   131,
     132,   110,   208,   209,   204,   334,   335,   111,   205,   206,
     196,   322,   323,    21,    46,    22,    28,    29,    23,    50,
      51,    24,   349,    56,   143,    25,    43,    26,   286,    67,
     144,   145,   146,   387,   166,   115,   167,   168,   169,   170,
     118,   389,   171,   172,   173,   174,   119,   175,   176,   295,
     296,   297,   298,   177,   178,   521,   522,   450,   451,   350,
     351,   454,   492,   533,   534
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     117,   121,   200,    59,    18,   116,   197,   130,   120,    55,
     292,   136,   294,   312,   313,    58,   455,    61,   469,    53,
     109,    60,    27,   142,     3,   304,    69,    72,   283,  -229,
     181,    74,    85,   305,   186,    62,   183,   157,   418,   192,
      35,    38,    39,   182,    44,    45,   198,   199,   227,   199,
     207,    73,    40,    41,   228,   517,    86,   306,   474,   404,
     109,   184,   419,    57,   399,   400,    35,    38,    39,    42,
     284,    35,    38,    39,   152,   475,    58,   228,    40,    41,
     229,    30,   279,    40,    41,   185,   230,   232,   232,   234,
     232,   232,   516,    58,   316,    42,   275,     4,   142,   503,
      42,    31,   285,   282,   288,     5,   112,   283,   199,   112,
      47,    32,     7,   302,   336,    33,    48,   113,   331,     8,
     301,    78,    59,    49,   138,    66,   139,   114,    52,   112,
     386,    10,    53,    34,    58,    12,   280,   429,   140,   199,
     113,   433,   315,   435,   294,   294,   321,   294,    63,   284,
     386,    68,   109,   109,   141,    79,   188,   189,   333,   199,
     289,   337,   338,   339,   340,   341,   342,   343,   344,   345,
     346,   347,   109,   462,   307,    70,   148,    64,   149,   530,
      65,    66,   353,   354,   355,   356,   357,   358,   359,   360,
     361,   362,   363,   364,   365,   366,   367,   368,   369,   370,
     371,   372,   373,   374,   375,   376,   377,   378,   379,   380,
     381,   388,   390,   383,    35,    38,    39,   153,   154,   434,
      31,    31,    53,    53,   293,   393,    40,    41,    71,    86,
     324,   142,   212,   -21,    33,    33,   213,    75,   214,    76,
     215,    80,   266,    42,   462,   122,   123,   420,   414,   231,
     233,    95,   235,   236,    77,   427,   428,   292,   291,    96,
      82,    83,   432,   281,   199,   100,    84,   290,    87,   439,
     299,    88,   394,   442,    59,   207,   109,   134,   147,    66,
     109,   104,   109,   105,    73,   409,   410,   449,   412,   150,
     155,   117,   121,   448,   156,   139,   116,   158,   180,   120,
     187,   507,   190,   191,   211,   511,   421,   193,   194,   201,
     210,   267,    35,    38,    39,   226,   292,   225,   294,   268,
     269,    86,   270,   272,    40,    41,   311,   274,   273,   278,
     276,   456,   277,   317,   309,   287,   320,   327,   461,   324,
     329,    42,   332,   464,   465,   330,   325,   352,   326,   382,
     406,   541,   348,   392,   449,   466,   293,   293,   395,   293,
     448,   396,   397,   398,   403,   470,   471,   249,   250,   251,
     252,   253,   254,   255,   256,   483,   401,   384,   385,     4,
     407,   484,   402,   321,   505,   460,   408,     5,   411,   283,
     333,   413,   416,    32,     7,   415,   417,   430,   431,   437,
     438,     8,   491,   440,   445,   444,   452,   494,   446,   453,
     457,   458,   459,    10,   463,    34,   473,    12,   532,   419,
     152,   478,   427,   467,   427,   509,   510,   482,   449,   479,
     477,   284,   514,   489,   448,   515,   488,   493,   109,   519,
     109,   318,   523,   532,   109,   495,   496,   502,   497,   498,
     499,   500,   518,   520,   117,   121,   524,   504,   529,   116,
     525,     4,   120,   199,   526,   527,   531,   135,   536,     5,
     528,   535,   538,   542,   540,    32,     7,   537,   539,   554,
     543,   544,   545,     8,   550,   390,   472,   547,   199,   549,
     109,   303,   508,   506,   443,    10,   486,    34,   553,    12,
     441,   133,   237,   238,   239,   240,   241,   242,   243,   244,
     245,   246,   247,   248,   249,   250,   251,   252,   253,   254,
     255,   256,   328,   485,   179,   391,   271,   551,   501,   468,
     293,   237,   238,   239,   240,   241,   242,   243,   244,   245,
     246,   247,   248,   249,   250,   251,   252,   253,   254,   255,
     256,   237,   238,   239,   240,   241,   242,   243,   244,   245,
     246,   247,   248,   249,   250,   251,   252,   253,   254,   255,
     256,   480,   552,   314,   548,   546,     0,     0,     0,     0,
       0,     0,   237,   238,   239,   240,   241,   242,   243,   244,
     245,   246,   247,   248,   249,   250,   251,   252,   253,   254,
     255,   256,   487,   237,   238,   239,   240,   241,   242,   243,
     244,   245,   246,   247,   248,   249,   250,   251,   252,   253,
     254,   255,   256,     0,     0,     0,     0,     0,     0,     0,
       0,   237,   238,   239,   240,   241,   242,   243,   244,   245,
     246,   247,   248,   249,   250,   251,   252,   253,   254,   255,
     256,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   237,   238,   239,   240,   241,   242,   243,   244,
     245,   246,   247,   248,   249,   250,   251,   252,   253,   254,
     255,   256,   159,     0,   160,   123,     0,     0,     0,     0,
      95,   161,     0,     0,     0,   113,   162,     0,    96,     0,
       0,     0,     0,     0,   100,   114,   244,   245,   246,   247,
     248,   249,   250,   251,   252,   253,   254,   255,   256,     0,
     163,     0,   105,     0,   164,   124,   159,     0,   490,   123,
       0,     0,     0,     0,    95,   161,     0,     0,     0,   113,
     162,     0,    96,   125,   126,     0,     0,     0,   100,   114,
       0,     0,   127,   160,   123,     0,     0,     0,   128,    95,
     129,     0,     0,     0,   163,     0,   105,    96,   164,   124,
       0,     0,     0,   100,   386,     0,     0,     0,   122,   123,
       0,     0,     0,     0,    95,     0,     0,   125,   126,   104,
       0,   105,    96,     0,   124,     0,   127,     0,   100,     0,
       0,     0,   128,     0,   129,     0,     0,     0,     0,     0,
       0,     0,   125,   126,   104,     0,   105,     0,     0,   124,
       0,   127,   203,   123,     0,     0,     0,   128,    95,   129,
       0,     0,     0,   300,   123,     0,    96,   125,   126,    95,
       0,     0,   100,     0,     0,     0,   127,    96,     0,     0,
       0,     0,   128,   100,   129,     0,     0,     0,   104,     0,
     105,     0,     0,   124,     0,     0,   310,     0,     0,   104,
       0,   105,     0,     0,   124,     0,     0,     0,     0,     0,
       0,   125,   126,     0,     0,     0,     0,     0,     0,     0,
     127,     0,   125,   126,     0,     0,   128,     0,   129,     0,
       0,   127,     0,     0,     0,     0,     0,   128,     0,   129,
     237,   238,   239,   240,   241,   242,   243,   244,   245,   246,
     247,   248,   249,   250,   251,   252,   253,   254,   255,   256,
    -229,     0,     0,     4,  -229,  -229,  -229,     0,     0,     0,
    -229,     5,     0,     0,  -229,     0,     0,     6,     7,  -229,
    -229,  -229,     0,     0,  -229,     8,     9,     0,  -229,     0,
       0,     0,     0,     0,     0,     0,     0,    10,     0,    11,
    -229,    12,  -229,  -229,  -229,    58,    89,     0,     0,  -229,
       0,  -229,     0,  -229,    90,  -229,    91,    92,    93,    94,
       0,     0,     0,    95,     0,     0,     0,   481,     0,     0,
       0,    96,    97,     0,    98,    99,     0,   100,     0,     0,
       0,     0,     0,     0,     0,     0,   101,   102,   103,     0,
       0,     0,     0,   104,     0,   105,   237,   238,   239,   240,
     241,   242,   243,   244,   245,   246,   247,   248,   249,   250,
     251,   252,   253,   254,   255,   256,   319,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   237,   238,   239,   240,   241,
     242,   243,   244,   245,   246,   247,   248,   249,   250,   251,
     252,   253,   254,   255,   256,     4,     0,     0,     4,     0,
       0,     0,     0,    31,     0,     0,     5,     0,     0,    32,
       7,     0,    32,     7,     0,     0,     0,    33,     0,   308,
       8,     0,     0,     0,     0,     0,     0,     0,     0,    10,
       0,    34,    10,    12,    34,     0,    12,   237,   238,   239,
     240,   241,   242,   243,   244,   245,   246,   247,   248,   249,
     250,   251,   252,   253,   254,   255,   256,   436,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   237,   238,   239,   240,   241,
     242,   243,   244,   245,   246,   247,   248,   249,   250,   251,
     252,   253,   254,   255,   256,   513,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   237,   238,   239,   240,   241,   242,   243,
     244,   245,   246,   247,   248,   249,   250,   251,   252,   253,
     254,   255,   256,   512,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   237,   238,
     239,   240,   241,   242,   243,   244,   245,   246,   247,   248,
     249,   250,   251,   252,   253,   254,   255,   256,   447,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   237,   238,   239,   240,   241,   242,   243,   244,   245,
     246,   247,   248,   249,   250,   251,   252,   253,   254,   255,
     256,   237,   238,   239,   240,   241,   242,   243,   244,   245,
     246,   247,   248,   249,   250,   251,   252,   253,   254,   255,
     256,   212,     0,     0,     0,   213,     0,   214,     0,   215,
       0,     0,   216,   217,   218,   219,   220,   221,   222,   223,
     224,   212,     0,     0,     0,   213,     0,   214,     0,   215,
       0,     0,   257,   258,   259,   260,   261,   262,   263,   264,
     265
};

static const yytype_int16 yycheck[] =
{
      61,    61,   102,    18,     2,    61,    98,    62,    61,    12,
     161,    65,   161,   190,   191,     4,   352,    50,   415,    16,
      58,    19,    16,    66,     0,     3,    32,    19,    16,    24,
      85,    37,    25,    11,    89,    68,    87,    80,    19,    94,
       6,     6,     6,    86,    16,    17,   101,   102,     3,   104,
     105,    43,     6,     6,    32,    50,    49,    35,     9,    48,
      98,    58,    43,    48,   283,   284,    32,    32,    32,     6,
      58,    37,    37,    37,    72,    26,     4,    32,    32,    32,
      35,    16,    10,    37,    37,    88,   124,   125,   126,   127,
     128,   129,   489,     4,   194,    32,   147,     6,   141,    10,
      37,    14,   156,    12,   158,    14,    16,    16,   163,    16,
      16,    20,    21,   164,   214,    28,    16,    27,   210,    28,
     163,    48,   137,    16,    14,    52,    16,    37,    16,    16,
      37,    40,    16,    42,     4,    44,   151,   314,    28,   194,
      27,   318,   193,   320,   293,   294,   201,   296,    51,    58,
      37,    16,   190,   191,    44,    47,    16,    17,   213,   214,
     158,   216,   217,   218,   219,   220,   221,   222,   223,   224,
     225,   226,   210,   392,   180,    16,    68,    48,    70,   515,
      51,    52,   237,   238,   239,   240,   241,   242,   243,   244,
     245,   246,   247,   248,   249,   250,   251,   252,   253,   254,
     255,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   272,   272,   267,   180,   180,   180,    75,    76,   319,
      14,    14,    16,    16,   161,   276,   180,   180,    16,    49,
      50,   274,    48,    53,    28,    28,    52,    49,    54,    49,
      56,    52,   134,   180,   463,    16,    17,   308,   303,   125,
     126,    22,   128,   129,    51,   310,   311,   408,    52,    30,
      68,    51,   317,   155,   319,    36,    51,   159,    50,   324,
     162,    51,   278,   328,   289,   330,   314,    16,    50,    52,
     318,    52,   320,    54,    43,   293,   294,   348,   296,    51,
      16,   352,   352,   348,    51,    16,   352,    51,    20,   352,
      16,   478,    50,    50,    10,   482,   309,    52,    52,    52,
      51,    51,   278,   278,   278,    68,   467,    54,   467,    51,
      16,    49,    16,    50,   278,   278,    59,    51,    53,    20,
      50,   382,    51,    41,    51,    53,     7,    51,   392,    50,
      55,   278,    16,   397,   398,    49,    53,    24,    53,    50,
      50,   528,    54,    51,   415,   406,   293,   294,    48,   296,
     415,    48,    51,    51,    48,   416,   417,    80,    81,    82,
      83,    84,    85,    86,    87,   430,    51,   269,   270,     6,
      16,   436,    51,   438,   476,    12,    51,    14,    10,    16,
     445,    53,    24,    20,    21,    54,    24,    49,    53,    53,
      49,    28,   453,    16,    49,    53,    10,   458,    55,     5,
      51,    50,     3,    40,    51,    42,    10,    44,   518,    43,
     418,    50,   477,    53,   479,   480,   481,     9,   489,    49,
      51,    58,   487,    49,   489,    24,    55,    51,   476,   493,
     478,     7,   496,   543,   482,    54,    51,    55,    51,    51,
      51,    51,    24,    16,   515,   515,    10,   472,   513,   515,
      24,     6,   515,   518,    48,    48,   517,    12,     8,    14,
       7,    51,    51,    50,   525,    20,    21,    55,    51,    53,
      51,    16,    24,    28,   545,   545,   418,    52,   543,    50,
     528,     8,   479,   477,   330,    40,   445,    42,   549,    44,
     327,    63,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,     8,   438,    83,   274,   141,   545,   467,   408,
     467,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,     8,   547,    38,   543,   538,    -1,    -1,    -1,    -1,
      -1,    -1,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,     8,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    14,    -1,    16,    17,    -1,    -1,    -1,    -1,
      22,    23,    -1,    -1,    -1,    27,    28,    -1,    30,    -1,
      -1,    -1,    -1,    -1,    36,    37,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    -1,
      52,    -1,    54,    -1,    56,    57,    14,    -1,    16,    17,
      -1,    -1,    -1,    -1,    22,    23,    -1,    -1,    -1,    27,
      28,    -1,    30,    75,    76,    -1,    -1,    -1,    36,    37,
      -1,    -1,    84,    16,    17,    -1,    -1,    -1,    90,    22,
      92,    -1,    -1,    -1,    52,    -1,    54,    30,    56,    57,
      -1,    -1,    -1,    36,    37,    -1,    -1,    -1,    16,    17,
      -1,    -1,    -1,    -1,    22,    -1,    -1,    75,    76,    52,
      -1,    54,    30,    -1,    57,    -1,    84,    -1,    36,    -1,
      -1,    -1,    90,    -1,    92,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    75,    76,    52,    -1,    54,    -1,    -1,    57,
      -1,    84,    16,    17,    -1,    -1,    -1,    90,    22,    92,
      -1,    -1,    -1,    16,    17,    -1,    30,    75,    76,    22,
      -1,    -1,    36,    -1,    -1,    -1,    84,    30,    -1,    -1,
      -1,    -1,    90,    36,    92,    -1,    -1,    -1,    52,    -1,
      54,    -1,    -1,    57,    -1,    -1,    24,    -1,    -1,    52,
      -1,    54,    -1,    -1,    57,    -1,    -1,    -1,    -1,    -1,
      -1,    75,    76,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      84,    -1,    75,    76,    -1,    -1,    90,    -1,    92,    -1,
      -1,    84,    -1,    -1,    -1,    -1,    -1,    90,    -1,    92,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
       0,    -1,    -1,     6,     4,     5,     6,    -1,    -1,    -1,
      10,    14,    -1,    -1,    14,    -1,    -1,    20,    21,    19,
      20,    21,    -1,    -1,    24,    28,    29,    -1,    28,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    40,    -1,    42,
      40,    44,    42,    43,    44,     4,     5,    -1,    -1,    49,
      -1,    51,    -1,    53,    13,    55,    15,    16,    17,    18,
      -1,    -1,    -1,    22,    -1,    -1,    -1,    39,    -1,    -1,
      -1,    30,    31,    -1,    33,    34,    -1,    36,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    45,    46,    47,    -1,
      -1,    -1,    -1,    52,    -1,    54,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    49,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,     6,    -1,    -1,     6,    -1,
      -1,    -1,    -1,    14,    -1,    -1,    14,    -1,    -1,    20,
      21,    -1,    20,    21,    -1,    -1,    -1,    28,    -1,    50,
      28,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    40,
      -1,    42,    40,    44,    42,    -1,    44,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    50,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    50,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    53,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    55,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    48,    -1,    -1,    -1,    52,    -1,    54,    -1,    56,
      -1,    -1,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    48,    -1,    -1,    -1,    52,    -1,    54,    -1,    56,
      -1,    -1,    59,    60,    61,    62,    63,    64,    65,    66,
      67
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    94,    95,     0,     6,    14,    20,    21,    28,    29,
      40,    42,    44,    96,    97,    99,   100,   104,   105,   106,
     107,   136,   138,   141,   144,   148,   150,    16,   139,   140,
      16,    14,    20,    28,    42,   107,   108,   109,   136,   138,
     141,   144,   148,   149,    16,    17,   137,    16,    16,    16,
     142,   143,    16,    16,   103,   145,   146,    48,     4,   111,
     105,    50,    68,    51,    48,    51,    52,   152,    16,   108,
      16,    16,    19,    43,   108,    49,    49,    51,    48,   152,
      52,   102,    68,    51,    51,    25,    49,    50,    51,     5,
      13,    15,    16,    17,    18,    22,    30,    31,    33,    34,
      36,    45,    46,    47,    52,    54,   110,   111,   112,   123,
     124,   130,    16,    27,    37,   158,   160,   161,   163,   169,
     170,   177,    16,    17,    57,    75,    76,    84,    90,    92,
     121,   122,   123,   139,    16,    12,   104,   105,    14,    16,
      28,    44,   103,   147,   153,   154,   155,    50,   152,   152,
      51,   101,   105,   137,   137,    16,    51,   103,    51,    14,
      16,    23,    28,    52,    56,   121,   157,   159,   160,   161,
     162,   165,   166,   167,   168,   170,   171,   176,   177,   142,
      20,   121,   103,   157,    58,   145,   121,    16,    16,    17,
      50,    50,   121,    52,    52,   113,   133,   112,   121,   121,
     127,    52,   114,    16,   127,   131,   132,   121,   125,   126,
      51,    10,    48,    52,    54,    56,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    54,    68,     3,    32,    35,
     123,   122,   123,   122,   123,   122,   122,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    59,    60,    61,
      62,    63,    64,    65,    66,    67,   152,    51,    51,    16,
      16,   155,    50,    53,    51,   157,    50,    51,    20,    10,
     111,   152,    12,    16,    58,   104,   151,    53,   104,   105,
     152,    52,   146,   148,   149,   172,   173,   174,   175,   152,
      16,   103,   157,     8,     3,    11,    35,   108,    50,    51,
      24,    59,   110,   110,    38,   157,   127,    41,     7,    49,
       7,   121,   134,   135,    50,    53,    53,    51,     8,    55,
      49,   112,    16,   121,   128,   129,   127,   121,   121,   121,
     121,   121,   121,   121,   121,   121,   121,   121,    54,   145,
     182,   183,    24,   121,   121,   121,   121,   121,   121,   121,
     121,   121,   121,   121,   121,   121,   121,   121,   121,   121,
     121,   121,   121,   121,   121,   121,   121,   121,   121,   121,
     121,   121,    50,   104,   152,   152,    37,   156,   161,   164,
     177,   153,    51,   157,   108,    48,    48,    51,    51,   151,
     151,    51,    51,    48,    48,    98,    50,    16,    51,   175,
     175,    10,   175,    53,   121,    54,    24,    24,    19,    43,
     161,   145,   115,   117,   118,   119,   120,   121,   121,   110,
      49,    53,   121,   110,   127,   110,    50,    53,    49,   121,
      16,   131,   121,   125,    53,    49,    55,    55,   121,   161,
     180,   181,    10,     5,   184,   158,   157,    51,    50,     3,
      12,   104,   151,    51,   104,   104,   157,    53,   174,   180,
     157,   157,   101,    10,     9,    26,   116,    51,    50,    49,
       8,    39,     9,   121,   121,   134,   128,     8,    55,    49,
      16,   157,   185,    51,   157,    54,    51,    51,    51,    51,
      51,   172,    55,    10,   111,   112,   117,   110,   119,   121,
     121,   110,    53,    50,   121,    24,   180,    50,    24,   104,
      16,   178,   179,   104,    10,    24,    48,    48,     7,   121,
     158,   157,   127,   186,   187,    51,     8,    55,    51,    51,
     157,   110,    50,    51,    16,    24,   178,    52,   186,    50,
     161,   164,   182,   157,    53
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    93,    95,    94,    96,    96,    96,    97,    97,    98,
      98,    99,    99,   100,   100,   100,   100,   101,   102,   102,
     103,   103,   104,   105,   105,   106,   106,   106,   106,   106,
     106,   106,   107,   107,   108,   108,   109,   109,   109,   109,
     109,   109,   109,   110,   110,   110,   110,   110,   110,   110,
     110,   110,   110,   110,   110,   110,   110,   110,   110,   110,
     110,   110,   110,   110,   110,   110,   110,   110,   110,   111,
     112,   112,   113,   113,   114,   114,   115,   115,   116,   116,
     117,   117,   117,   118,   119,   119,   120,   120,   121,   121,
     121,   121,   121,   121,   121,   121,   121,   121,   121,   121,
     121,   121,   121,   121,   121,   121,   121,   121,   121,   121,
     121,   121,   121,   121,   121,   121,   121,   121,   122,   122,
     122,   122,   122,   122,   122,   123,   123,   123,   123,   123,
     123,   123,   124,   124,   124,   124,   124,   124,   125,   125,
     125,   126,   126,   127,   127,   128,   128,   129,   129,   130,
     131,   131,   132,   133,   134,   134,   135,   135,   135,   136,
     137,   137,   137,   137,   138,   139,   139,   140,   140,   141,
     142,   142,   143,   144,   145,   145,   145,   145,   145,   146,
     146,   147,   147,   148,   148,   149,   149,   150,   150,   150,
     150,   150,   150,   150,   150,   151,   151,   151,   151,   152,
     152,   153,   153,   154,   154,   154,   155,   155,   156,   156,
     157,   157,   157,   157,   157,   157,   157,   157,   157,   157,
     157,   158,   158,   158,   158,   158,   159,   159,   160,   161,
     161,   162,   163,   164,   164,   165,   166,   167,   168,   169,
     170,   171,   171,   172,   172,   172,   173,   174,   174,   174,
     175,   175,   175,   175,   176,   177,   177,   178,   178,   179,
     180,   180,   181,   181,   182,   182,   183,   184,   185,   185,
     186,   186,   186,   187
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     1,     1,     1,     2,     6,     0,
       1,     1,     6,     9,     9,     6,     6,     1,     0,     3,
       3,     1,     2,     0,     2,     1,     1,     1,     1,     1,
       1,     1,     6,     3,     0,     2,     1,     1,     1,     1,
       1,     1,     1,     0,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     2,     2,     5,     4,     6,     8,     4,
       4,     2,     2,     1,     1,     4,     3,     3,     1,     3,
       1,     3,     0,     1,     0,     3,     1,     3,     1,     1,
       0,     1,     3,     3,     1,     3,     1,     3,     1,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     1,     2,
       2,     2,     2,     2,     2,     1,     3,     4,     3,     2,
       4,     6,     1,     1,     1,     1,     3,     1,     0,     1,
       3,     1,     3,     1,     3,     1,     3,     1,     0,     3,
       1,     3,     3,     3,     1,     3,     1,     3,     5,     3,
       1,     3,     1,     3,     2,     0,     3,     3,     5,     2,
       0,     3,     3,     2,     0,     1,     3,     5,     3,     3,
       5,     3,     5,     6,     8,     4,     6,     6,     8,     8,
      10,     5,     8,    10,     7,     2,     2,     1,     1,     0,
       3,     1,     3,     2,     1,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     4,     2,     4,     1,
       1,     7,     7,     7,     7,     3,     3,     2,     4,     4,
       4,     3,     6,     2,     1,     1,     1,     1,     2,     3,
       1,     1,     2,     2,     4,     0,     1,     1,     3,     5,
       1,     3,     1,     3,     2,     1,     1,     4,     3,     1,
       1,     2,     3,     5
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


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

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


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




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
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
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
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
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
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
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

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
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
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
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
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
  case 2: /* $@1: %empty  */
#line 262 "parser.y"
{
  if (turbo_pascal) { 
    zzcnv_table[TKN_STRING] = STRING;
    zzcnv_table[TKN_STR] = WRITE;
    zzcnv_table[TKN_SHL] = SHL;
    zzcnv_table[TKN_SHR] = SHR;
    zzcnv_table[TKN_XOR] = XOR;
    zzcnv_table[TKN_UNIT] = UNIT;
    zzcnv_table[TKN_FAR] = FAR;
    zzcnv_table[TKN_IMPLEMENTATION] = IMPLEMENTATION;
    zzcnv_table[TKN_INTERFACE] = INTERFACE;

    zzcnv_table[TKN_OBJECT] = OBJECT;
    zzcnv_table[TKN_CONSTRUCTOR] = PROCEDURE;
    zzcnv_table[TKN_DESTRUCTOR] = PROCEDURE;
  } else { 
    zzcnv_table[TKN_ORIGIN] = ORIGIN;
  }      
}
#line 1855 "parser.cxx"
    break;

  case 3: /* translation: $@1 input_file  */
#line 281 "parser.y"
           { 
    (yyvsp[0].n_node)->attrib(ctx_program); 
    (yyvsp[0].n_node)->translate(ctx_program); 
}
#line 1864 "parser.cxx"
    break;

  case 7: /* program: block '.'  */
#line 288 "parser.y"
                   { (yyval.n_node) = new program_node(NULL, NULL, NULL, NULL, (yyvsp[-1].n_block), (yyvsp[0].tok)); }
#line 1870 "parser.cxx"
    break;

  case 8: /* program: PROGRAM IDENT prog_param_list ';' block '.'  */
#line 290 "parser.y"
{ 
    (yyval.n_node) = new program_node((yyvsp[-5].tok), (yyvsp[-4].tok), (yyvsp[-3].n_imp), (yyvsp[-2].tok), (yyvsp[-1].n_block), (yyvsp[0].tok));
}
#line 1878 "parser.cxx"
    break;

  case 9: /* progend: %empty  */
#line 294 "parser.y"
         { (yyval.tok) = NULL; }
#line 1884 "parser.cxx"
    break;

  case 11: /* module: decl_part_list  */
#line 296 "parser.y"
                       { (yyval.n_node) = new module_node(NULL, NULL, NULL, NULL, (yyvsp[0].n_decl), NULL); }
#line 1890 "parser.cxx"
    break;

  case 12: /* module: PROGRAM IDENT prog_param_list ';' decl_part_list progend  */
#line 298 "parser.y"
{ 
    (yyval.n_node) = new module_node((yyvsp[-5].tok), (yyvsp[-4].tok), (yyvsp[-3].n_imp), (yyvsp[-2].tok), (yyvsp[-1].n_decl), (yyvsp[0].tok));
}
#line 1898 "parser.cxx"
    break;

  case 13: /* unit: UNIT IDENT ';' INTERFACE unit_decl_list IMPLEMENTATION unit_def_list END '.'  */
#line 306 "parser.y"
    { (yyval.n_node) = new unit_node((yyvsp[-8].tok), (yyvsp[-7].tok), (yyvsp[-6].tok), (yyvsp[-5].tok), (yyvsp[-4].n_decl), (yyvsp[-3].tok), (yyvsp[-2].n_decl), NULL, (yyvsp[-1].tok), (yyvsp[0].tok)); }
#line 1904 "parser.cxx"
    break;

  case 14: /* unit: UNIT IDENT ';' INTERFACE unit_decl_list IMPLEMENTATION unit_def_list compoundst '.'  */
#line 308 "parser.y"
    { (yyval.n_node) = new unit_node((yyvsp[-8].tok), (yyvsp[-7].tok), (yyvsp[-6].tok), (yyvsp[-5].tok), (yyvsp[-4].n_decl), (yyvsp[-3].tok), (yyvsp[-2].n_decl), (yyvsp[-1].n_comp), NULL, (yyvsp[0].tok)); }
#line 1910 "parser.cxx"
    break;

  case 15: /* unit: INTERFACE unit_decl_list IMPLEMENTATION unit_def_list END '.'  */
#line 310 "parser.y"
    { (yyval.n_node) = new unit_node(NULL, NULL, NULL, (yyvsp[-5].tok), (yyvsp[-4].n_decl), (yyvsp[-3].tok), (yyvsp[-2].n_decl), NULL, (yyvsp[-1].tok), (yyvsp[0].tok)); }
#line 1916 "parser.cxx"
    break;

  case 16: /* unit: INTERFACE unit_decl_list IMPLEMENTATION unit_def_list compoundst '.'  */
#line 312 "parser.y"
    { (yyval.n_node) = new unit_node(NULL, NULL, NULL, (yyvsp[-5].tok), (yyvsp[-4].n_decl), (yyvsp[-3].tok), (yyvsp[-2].n_decl), (yyvsp[-1].n_comp), NULL, (yyvsp[0].tok)); }
#line 1922 "parser.cxx"
    break;

  case 18: /* prog_param_list: %empty  */
#line 317 "parser.y"
                 { (yyval.n_imp) = NULL; }
#line 1928 "parser.cxx"
    break;

  case 19: /* prog_param_list: '(' ident_list ')'  */
#line 318 "parser.y"
                         { (yyval.n_imp) = new import_list_node((yyvsp[-2].tok), (yyvsp[-1].toks), (yyvsp[0].tok)); }
#line 1934 "parser.cxx"
    break;

  case 20: /* ident_list: IDENT ',' ident_list  */
#line 320 "parser.y"
                                 { (yyval.toks) = new token_list((yyvsp[-2].tok), (yyvsp[0].toks)); }
#line 1940 "parser.cxx"
    break;

  case 21: /* ident_list: IDENT  */
#line 321 "parser.y"
            { (yyval.toks) = new token_list((yyvsp[0].tok)); }
#line 1946 "parser.cxx"
    break;

  case 22: /* block: decl_part_list compoundst  */
#line 324 "parser.y"
{
    (yyval.n_block) = new block_node((yyvsp[-1].n_decl), (yyvsp[0].n_comp));
}
#line 1954 "parser.cxx"
    break;

  case 23: /* decl_part_list: %empty  */
#line 328 "parser.y"
                { (yyval.n_decl) = NULL; }
#line 1960 "parser.cxx"
    break;

  case 24: /* decl_part_list: decl_part decl_part_list  */
#line 329 "parser.y"
                               { (yyvsp[-1].n_decl)->next = (yyvsp[0].n_decl); (yyval.n_decl) = (yyvsp[-1].n_decl); }
#line 1966 "parser.cxx"
    break;

  case 32: /* unit_spec: UNIT IDENT ';' INTERFACE unit_decl_list UNIT_END  */
#line 335 "parser.y"
    {  (yyval.n_decl) = new unit_spec_node((yyvsp[-5].tok), (yyvsp[-4].tok), (yyvsp[-3].tok), (yyvsp[-2].tok), (yyvsp[-1].n_decl)); }
#line 1972 "parser.cxx"
    break;

  case 33: /* unit_spec: INTERFACE unit_decl_list UNIT_END  */
#line 337 "parser.y"
    {  (yyval.n_decl) = new unit_spec_node(NULL, NULL, NULL, (yyvsp[-2].tok), (yyvsp[-1].n_decl)); }
#line 1978 "parser.cxx"
    break;

  case 34: /* unit_decl_list: %empty  */
#line 340 "parser.y"
                { (yyval.n_decl) = NULL; }
#line 1984 "parser.cxx"
    break;

  case 35: /* unit_decl_list: unit_decl unit_decl_list  */
#line 341 "parser.y"
                               { (yyvsp[-1].n_decl)->next = (yyvsp[0].n_decl); (yyval.n_decl) = (yyvsp[-1].n_decl); }
#line 1990 "parser.cxx"
    break;

  case 43: /* statement: %empty  */
#line 373 "parser.y"
           { (yyval.n_stmt) = new empty_node(curr_token->prev_relevant()); }
#line 1996 "parser.cxx"
    break;

  case 44: /* statement: primary LET expr  */
#line 374 "parser.y"
                       { (yyval.n_stmt) = new assign_node((yyvsp[-2].n_expr), (yyvsp[-1].tok), (yyvsp[0].n_expr)); }
#line 2002 "parser.cxx"
    break;

  case 45: /* statement: primary LETADD expr  */
#line 375 "parser.y"
                          { (yyval.n_stmt) = new assign_node((yyvsp[-2].n_expr), (yyvsp[-1].tok), (yyvsp[0].n_expr)); }
#line 2008 "parser.cxx"
    break;

  case 46: /* statement: primary LETSUB expr  */
#line 376 "parser.y"
                          { (yyval.n_stmt) = new assign_node((yyvsp[-2].n_expr), (yyvsp[-1].tok), (yyvsp[0].n_expr)); }
#line 2014 "parser.cxx"
    break;

  case 47: /* statement: primary LETDIV expr  */
#line 377 "parser.y"
                          { (yyval.n_stmt) = new assign_node((yyvsp[-2].n_expr), (yyvsp[-1].tok), (yyvsp[0].n_expr)); }
#line 2020 "parser.cxx"
    break;

  case 48: /* statement: primary LETMUL expr  */
#line 378 "parser.y"
                          { (yyval.n_stmt) = new assign_node((yyvsp[-2].n_expr), (yyvsp[-1].tok), (yyvsp[0].n_expr)); }
#line 2026 "parser.cxx"
    break;

  case 49: /* statement: primary LETAND expr  */
#line 379 "parser.y"
                          { (yyval.n_stmt) = new assign_node((yyvsp[-2].n_expr), (yyvsp[-1].tok), (yyvsp[0].n_expr)); }
#line 2032 "parser.cxx"
    break;

  case 50: /* statement: primary LETOR expr  */
#line 380 "parser.y"
                          { (yyval.n_stmt) = new assign_node((yyvsp[-2].n_expr), (yyvsp[-1].tok), (yyvsp[0].n_expr)); }
#line 2038 "parser.cxx"
    break;

  case 51: /* statement: primary LETSHL expr  */
#line 381 "parser.y"
                          { (yyval.n_stmt) = new assign_node((yyvsp[-2].n_expr), (yyvsp[-1].tok), (yyvsp[0].n_expr)); }
#line 2044 "parser.cxx"
    break;

  case 52: /* statement: primary LETSHR expr  */
#line 382 "parser.y"
                          { (yyval.n_stmt) = new assign_node((yyvsp[-2].n_expr), (yyvsp[-1].tok), (yyvsp[0].n_expr)); }
#line 2050 "parser.cxx"
    break;

  case 53: /* statement: GOTO ICONST  */
#line 383 "parser.y"
                  { (yyval.n_stmt) = new goto_node((yyvsp[-1].tok), (yyvsp[0].tok)); }
#line 2056 "parser.cxx"
    break;

  case 54: /* statement: GOTO IDENT  */
#line 384 "parser.y"
                 { (yyval.n_stmt) = new goto_node((yyvsp[-1].tok), (yyvsp[0].tok)); }
#line 2062 "parser.cxx"
    break;

  case 55: /* statement: CASE expr OF case_list END  */
#line 385 "parser.y"
                                 { (yyval.n_stmt) = new switch_node((yyvsp[-4].tok), (yyvsp[-3].n_expr), (yyvsp[-2].tok), (yyvsp[-1].n_case), (yyvsp[0].tok)); }
#line 2068 "parser.cxx"
    break;

  case 56: /* statement: IF expr THEN statement  */
#line 386 "parser.y"
                             { (yyval.n_stmt) = new if_node((yyvsp[-3].tok), (yyvsp[-2].n_expr), (yyvsp[-1].tok), (yyvsp[0].n_stmt)); }
#line 2074 "parser.cxx"
    break;

  case 57: /* statement: IF expr THEN statement ELSE statement  */
#line 388 "parser.y"
        { (yyval.n_stmt) = new if_node((yyvsp[-5].tok), (yyvsp[-4].n_expr), (yyvsp[-3].tok), (yyvsp[-2].n_stmt), (yyvsp[-1].tok), (yyvsp[0].n_stmt)); }
#line 2080 "parser.cxx"
    break;

  case 58: /* statement: FOR IDENT LET expr TO expr DO statement  */
#line 390 "parser.y"
        { (yyval.n_stmt) = new for_node((yyvsp[-7].tok), (yyvsp[-6].tok), (yyvsp[-5].tok), (yyvsp[-4].n_expr), (yyvsp[-3].tok), (yyvsp[-2].n_expr), (yyvsp[-1].tok), (yyvsp[0].n_stmt)); }
#line 2086 "parser.cxx"
    break;

  case 59: /* statement: WHILE expr DO statement  */
#line 391 "parser.y"
                              { (yyval.n_stmt) = new while_node((yyvsp[-3].tok), (yyvsp[-2].n_expr), (yyvsp[-1].tok), (yyvsp[0].n_stmt)); }
#line 2092 "parser.cxx"
    break;

  case 60: /* statement: REPEAT sequence UNTIL expr  */
#line 392 "parser.y"
                                 { (yyval.n_stmt) = new repeat_node((yyvsp[-3].tok), (yyvsp[-2].n_stmt), (yyvsp[-1].tok), (yyvsp[0].n_expr)); }
#line 2098 "parser.cxx"
    break;

  case 61: /* statement: WRITE write_params  */
#line 393 "parser.y"
                         { (yyval.n_stmt) = new write_node((yyvsp[-1].tok), (yyvsp[0].n_wrls)); }
#line 2104 "parser.cxx"
    break;

  case 62: /* statement: READ actual_params  */
#line 394 "parser.y"
                         { (yyval.n_stmt) = new read_node((yyvsp[-1].tok), (yyvsp[0].n_grp)); }
#line 2110 "parser.cxx"
    break;

  case 63: /* statement: primary  */
#line 395 "parser.y"
              { (yyval.n_stmt) = new pcall_node((yyvsp[0].n_expr)); }
#line 2116 "parser.cxx"
    break;

  case 64: /* statement: RETURN  */
#line 396 "parser.y"
             { (yyval.n_stmt) = new return_node((yyvsp[0].tok)); }
#line 2122 "parser.cxx"
    break;

  case 65: /* statement: WITH expr_list DO statement  */
#line 397 "parser.y"
                                  { (yyval.n_stmt) = new with_node((yyvsp[-3].tok), (yyvsp[-2].n_expr), (yyvsp[-1].tok), (yyvsp[0].n_stmt)); }
#line 2128 "parser.cxx"
    break;

  case 66: /* statement: ICONST ':' statement  */
#line 398 "parser.y"
                           { (yyval.n_stmt) = new label_node((yyvsp[-2].tok), (yyvsp[-1].tok), (yyvsp[0].n_stmt)); }
#line 2134 "parser.cxx"
    break;

  case 67: /* statement: IDENT ':' statement  */
#line 399 "parser.y"
                          { (yyval.n_stmt) = new label_node((yyvsp[-2].tok), (yyvsp[-1].tok), (yyvsp[0].n_stmt)); }
#line 2140 "parser.cxx"
    break;

  case 68: /* statement: compoundst  */
#line 400 "parser.y"
                 { (yyval.n_stmt) = (yyvsp[0].n_comp); }
#line 2146 "parser.cxx"
    break;

  case 69: /* compoundst: BEGIN sequence END  */
#line 402 "parser.y"
                               { (yyval.n_comp) = new compound_node((yyvsp[-2].tok), (yyvsp[-1].n_stmt), (yyvsp[0].tok)); }
#line 2152 "parser.cxx"
    break;

  case 71: /* sequence: statement ';' sequence  */
#line 404 "parser.y"
                                             { (yyvsp[-2].n_stmt)->next = (yyvsp[0].n_stmt); (yyval.n_stmt) = (yyvsp[-2].n_stmt); }
#line 2158 "parser.cxx"
    break;

  case 72: /* actual_params: %empty  */
#line 406 "parser.y"
               { (yyval.n_grp) = NULL; }
#line 2164 "parser.cxx"
    break;

  case 73: /* actual_params: expr_group  */
#line 406 "parser.y"
                                           { (yyval.n_grp) = (yyvsp[0].n_grp); }
#line 2170 "parser.cxx"
    break;

  case 74: /* write_params: %empty  */
#line 408 "parser.y"
               { (yyval.n_wrls) = NULL; }
#line 2176 "parser.cxx"
    break;

  case 75: /* write_params: '(' write_list ')'  */
#line 409 "parser.y"
                         { (yyval.n_wrls) = new write_list_node((yyvsp[-2].tok), (yyvsp[-1].n_wrtp), (yyvsp[0].tok)); }
#line 2182 "parser.cxx"
    break;

  case 77: /* case_list: case_items otherwise sequence  */
#line 413 "parser.y"
           { 
	     if ((yyvsp[-2].n_case) != NULL) { 
	         case_node** cpp;
	         for(cpp = &(yyvsp[-2].n_case)->next; *cpp != NULL; cpp = &(*cpp)->next);
	         *cpp = new case_node(NULL, (yyvsp[-1].tok), (yyvsp[0].n_stmt));
		 (yyval.n_case) = (yyvsp[-2].n_case);
             } else { 		 
	         (yyval.n_case) = new case_node(NULL, (yyvsp[-1].tok), (yyvsp[0].n_stmt));
             }
	   }
#line 2197 "parser.cxx"
    break;

  case 80: /* case_items: %empty  */
#line 426 "parser.y"
            { (yyval.n_case) = NULL; }
#line 2203 "parser.cxx"
    break;

  case 82: /* case_items: case_item ';' case_items  */
#line 428 "parser.y"
                                    { (yyvsp[-2].n_case)->next = (yyvsp[0].n_case); (yyval.n_case) = (yyvsp[-2].n_case); }
#line 2209 "parser.cxx"
    break;

  case 83: /* case_item: case_elem_list ':' statement  */
#line 430 "parser.y"
                                        { (yyval.n_case) = new case_node((yyvsp[-2].n_expr), (yyvsp[-1].tok), (yyvsp[0].n_stmt)); }
#line 2215 "parser.cxx"
    break;

  case 85: /* case_elem_list: case_elem ',' case_elem_list  */
#line 433 "parser.y"
                                       { (yyvsp[-2].n_expr)->next = (yyvsp[0].n_expr); (yyval.n_expr) = (yyvsp[-2].n_expr); }
#line 2221 "parser.cxx"
    break;

  case 86: /* case_elem: expr  */
#line 435 "parser.y"
                { (yyval.n_expr) = (yyvsp[0].n_expr); }
#line 2227 "parser.cxx"
    break;

  case 87: /* case_elem: expr DOTS expr  */
#line 436 "parser.y"
                         { (yyval.n_expr) = new case_range_node((yyvsp[-2].n_expr), (yyvsp[-1].tok), (yyvsp[0].n_expr)); }
#line 2233 "parser.cxx"
    break;

  case 89: /* expr: expr PLUS expr  */
#line 461 "parser.y"
                    { (yyval.n_expr) = new op_node(tn_add, (yyvsp[-2].n_expr), (yyvsp[-1].tok), (yyvsp[0].n_expr)); }
#line 2239 "parser.cxx"
    break;

  case 90: /* expr: expr MINUS expr  */
#line 462 "parser.y"
                     { (yyval.n_expr) = new op_node(tn_sub, (yyvsp[-2].n_expr), (yyvsp[-1].tok), (yyvsp[0].n_expr)); }
#line 2245 "parser.cxx"
    break;

  case 91: /* expr: expr MOD expr  */
#line 463 "parser.y"
                   { (yyval.n_expr) = new op_node(tn_mod, (yyvsp[-2].n_expr), (yyvsp[-1].tok), (yyvsp[0].n_expr)); }
#line 2251 "parser.cxx"
    break;

  case 92: /* expr: expr MUL expr  */
#line 464 "parser.y"
                   { (yyval.n_expr) = new op_node(tn_mul, (yyvsp[-2].n_expr), (yyvsp[-1].tok), (yyvsp[0].n_expr)); }
#line 2257 "parser.cxx"
    break;

  case 93: /* expr: expr DIV expr  */
#line 465 "parser.y"
                   { (yyval.n_expr) = new op_node(tn_div, (yyvsp[-2].n_expr), (yyvsp[-1].tok), (yyvsp[0].n_expr)); }
#line 2263 "parser.cxx"
    break;

  case 94: /* expr: expr DIVR expr  */
#line 466 "parser.y"
                    { (yyval.n_expr) = new op_node(tn_divr, (yyvsp[-2].n_expr), (yyvsp[-1].tok), (yyvsp[0].n_expr)); }
#line 2269 "parser.cxx"
    break;

  case 95: /* expr: primary LET expr  */
#line 468 "parser.y"
                      { (yyval.n_expr) = new op_node(tn_let, (yyvsp[-2].n_expr), (yyvsp[-1].tok), (yyvsp[0].n_expr)); }
#line 2275 "parser.cxx"
    break;

  case 96: /* expr: primary LETADD expr  */
#line 469 "parser.y"
                         { (yyval.n_expr) = new op_node(tn_letadd, (yyvsp[-2].n_expr), (yyvsp[-1].tok), (yyvsp[0].n_expr)); }
#line 2281 "parser.cxx"
    break;

  case 97: /* expr: primary LETSUB expr  */
#line 470 "parser.y"
                         { (yyval.n_expr) = new op_node(tn_letsub, (yyvsp[-2].n_expr), (yyvsp[-1].tok), (yyvsp[0].n_expr)); }
#line 2287 "parser.cxx"
    break;

  case 98: /* expr: primary LETDIV expr  */
#line 471 "parser.y"
                         { (yyval.n_expr) = new op_node(tn_letdiv, (yyvsp[-2].n_expr), (yyvsp[-1].tok), (yyvsp[0].n_expr)); }
#line 2293 "parser.cxx"
    break;

  case 99: /* expr: primary LETMUL expr  */
#line 472 "parser.y"
                         { (yyval.n_expr) = new op_node(tn_letmul, (yyvsp[-2].n_expr), (yyvsp[-1].tok), (yyvsp[0].n_expr)); }
#line 2299 "parser.cxx"
    break;

  case 100: /* expr: primary LETSHL expr  */
#line 473 "parser.y"
                         { (yyval.n_expr) = new op_node(tn_letshl, (yyvsp[-2].n_expr), (yyvsp[-1].tok), (yyvsp[0].n_expr)); }
#line 2305 "parser.cxx"
    break;

  case 101: /* expr: primary LETSHR expr  */
#line 474 "parser.y"
                         { (yyval.n_expr) = new op_node(tn_letshr, (yyvsp[-2].n_expr), (yyvsp[-1].tok), (yyvsp[0].n_expr)); }
#line 2311 "parser.cxx"
    break;

  case 102: /* expr: primary LETAND expr  */
#line 475 "parser.y"
                         { (yyval.n_expr) = new op_node(tn_letand, (yyvsp[-2].n_expr), (yyvsp[-1].tok), (yyvsp[0].n_expr)); }
#line 2317 "parser.cxx"
    break;

  case 103: /* expr: primary LETOR expr  */
#line 476 "parser.y"
                         { (yyval.n_expr) = new op_node(tn_letor,  (yyvsp[-2].n_expr), (yyvsp[-1].tok), (yyvsp[0].n_expr)); }
#line 2323 "parser.cxx"
    break;

  case 104: /* expr: expr AND expr  */
#line 479 "parser.y"
                   { (yyval.n_expr) = new op_node(tn_and, (yyvsp[-2].n_expr), (yyvsp[-1].tok), (yyvsp[0].n_expr)); }
#line 2329 "parser.cxx"
    break;

  case 105: /* expr: expr BINAND expr  */
#line 480 "parser.y"
                      { (yyval.n_expr) = new op_node(tn_binand, (yyvsp[-2].n_expr), (yyvsp[-1].tok), (yyvsp[0].n_expr)); }
#line 2335 "parser.cxx"
    break;

  case 106: /* expr: expr SHL expr  */
#line 481 "parser.y"
                   { (yyval.n_expr) = new op_node(tn_shl, (yyvsp[-2].n_expr), (yyvsp[-1].tok), (yyvsp[0].n_expr)); }
#line 2341 "parser.cxx"
    break;

  case 107: /* expr: expr SHR expr  */
#line 482 "parser.y"
                   { (yyval.n_expr) = new op_node(tn_shr, (yyvsp[-2].n_expr), (yyvsp[-1].tok), (yyvsp[0].n_expr)); }
#line 2347 "parser.cxx"
    break;

  case 108: /* expr: expr OR expr  */
#line 483 "parser.y"
                   { (yyval.n_expr) = new op_node(tn_or, (yyvsp[-2].n_expr), (yyvsp[-1].tok), (yyvsp[0].n_expr)); }
#line 2353 "parser.cxx"
    break;

  case 109: /* expr: expr BINOR expr  */
#line 484 "parser.y"
                      { (yyval.n_expr) = new op_node(tn_binor, (yyvsp[-2].n_expr), (yyvsp[-1].tok), (yyvsp[0].n_expr)); }
#line 2359 "parser.cxx"
    break;

  case 110: /* expr: expr XOR expr  */
#line 485 "parser.y"
                   { (yyval.n_expr) = new op_node(tn_xor, (yyvsp[-2].n_expr), (yyvsp[-1].tok), (yyvsp[0].n_expr)); }
#line 2365 "parser.cxx"
    break;

  case 111: /* expr: expr GT expr  */
#line 487 "parser.y"
                  { (yyval.n_expr) = new op_node(tn_gt, (yyvsp[-2].n_expr), (yyvsp[-1].tok), (yyvsp[0].n_expr)); }
#line 2371 "parser.cxx"
    break;

  case 112: /* expr: expr LT expr  */
#line 488 "parser.y"
                  { (yyval.n_expr) = new op_node(tn_lt, (yyvsp[-2].n_expr), (yyvsp[-1].tok), (yyvsp[0].n_expr)); }
#line 2377 "parser.cxx"
    break;

  case 113: /* expr: expr LE expr  */
#line 489 "parser.y"
                  { (yyval.n_expr) = new op_node(tn_le, (yyvsp[-2].n_expr), (yyvsp[-1].tok), (yyvsp[0].n_expr)); }
#line 2383 "parser.cxx"
    break;

  case 114: /* expr: expr GE expr  */
#line 490 "parser.y"
                  { (yyval.n_expr) = new op_node(tn_ge, (yyvsp[-2].n_expr), (yyvsp[-1].tok), (yyvsp[0].n_expr)); }
#line 2389 "parser.cxx"
    break;

  case 115: /* expr: expr EQ expr  */
#line 491 "parser.y"
                  { (yyval.n_expr) = new op_node(tn_eq, (yyvsp[-2].n_expr), (yyvsp[-1].tok), (yyvsp[0].n_expr)); }
#line 2395 "parser.cxx"
    break;

  case 116: /* expr: expr NE expr  */
#line 492 "parser.y"
                  { (yyval.n_expr) = new op_node(tn_ne, (yyvsp[-2].n_expr), (yyvsp[-1].tok), (yyvsp[0].n_expr)); }
#line 2401 "parser.cxx"
    break;

  case 117: /* expr: expr IN expr  */
#line 493 "parser.y"
                  { (yyval.n_expr) = new op_node(tn_in, (yyvsp[-2].n_expr), (yyvsp[-1].tok), (yyvsp[0].n_expr)); }
#line 2407 "parser.cxx"
    break;

  case 119: /* simple_expr: PLUS simple_expr  */
#line 496 "parser.y"
                                  {
     (yyval.n_expr) = new op_node(tn_plus, NULL, (yyvsp[-1].tok), (yyvsp[0].n_expr)); }
#line 2414 "parser.cxx"
    break;

  case 120: /* simple_expr: MINUS simple_expr  */
#line 499 "parser.y"
     { (yyval.n_expr) = new op_node(tn_minus, NULL, (yyvsp[-1].tok), (yyvsp[0].n_expr)); }
#line 2420 "parser.cxx"
    break;

  case 121: /* simple_expr: NOT simple_expr  */
#line 501 "parser.y"
     { (yyval.n_expr) = new op_node(tn_not, NULL, (yyvsp[-1].tok), (yyvsp[0].n_expr)); }
#line 2426 "parser.cxx"
    break;

  case 122: /* simple_expr: BINNOT simple_expr  */
#line 503 "parser.y"
     { (yyval.n_expr) = new op_node(tn_binnot, NULL, (yyvsp[-1].tok), (yyvsp[0].n_expr)); }
#line 2432 "parser.cxx"
    break;

  case 123: /* simple_expr: '@' primary  */
#line 504 "parser.y"
                 { (yyval.n_expr) = new address_node((yyvsp[-1].tok), (yyvsp[0].n_expr)); }
#line 2438 "parser.cxx"
    break;

  case 124: /* simple_expr: AND primary  */
#line 505 "parser.y"
                               { (yyval.n_expr) = new address_node((yyvsp[-1].tok), (yyvsp[0].n_expr)); }
#line 2444 "parser.cxx"
    break;

  case 126: /* primary: '(' expr_list ')'  */
#line 508 "parser.y"
                       { (yyval.n_expr) = new expr_group_node((yyvsp[-2].tok), (yyvsp[-1].n_expr), (yyvsp[0].tok)); }
#line 2450 "parser.cxx"
    break;

  case 127: /* primary: primary '(' act_param_list ')'  */
#line 509 "parser.y"
                                    { (yyval.n_expr) = new fcall_node((yyvsp[-3].n_expr), (yyvsp[-2].tok), (yyvsp[-1].n_expr), (yyvsp[0].tok)); }
#line 2456 "parser.cxx"
    break;

  case 128: /* primary: primary '.' IDENT  */
#line 510 "parser.y"
                       { (yyval.n_expr) = new access_expr_node((yyvsp[-2].n_expr), (yyvsp[-1].tok), (yyvsp[0].tok)); }
#line 2462 "parser.cxx"
    break;

  case 129: /* primary: primary '^'  */
#line 511 "parser.y"
                 { (yyval.n_expr) = new deref_expr_node((yyvsp[-1].n_expr), (yyvsp[0].tok)); }
#line 2468 "parser.cxx"
    break;

  case 130: /* primary: primary '[' expr_list ']'  */
#line 512 "parser.y"
                               { (yyval.n_expr) = new idx_expr_node((yyvsp[-3].n_expr), (yyvsp[-2].tok), (yyvsp[-1].n_expr), (yyvsp[0].tok)); }
#line 2474 "parser.cxx"
    break;

  case 131: /* primary: LOOPHOLE '(' type ',' expr ')'  */
#line 513 "parser.y"
                                    { (yyval.n_expr) = new loophole_node((yyvsp[-5].tok), (yyvsp[-4].tok), (yyvsp[-3].n_tpd), (yyvsp[-2].tok), (yyvsp[-1].n_expr), (yyvsp[0].tok)); }
#line 2480 "parser.cxx"
    break;

  case 133: /* constant: ICONST  */
#line 516 "parser.y"
                 { (yyval.n_expr) = new integer_node((yyvsp[0].tok)); }
#line 2486 "parser.cxx"
    break;

  case 134: /* constant: RCONST  */
#line 517 "parser.y"
                 { (yyval.n_expr) = new real_node((yyvsp[0].tok)); }
#line 2492 "parser.cxx"
    break;

  case 135: /* constant: SCONST  */
#line 518 "parser.y"
                 { (yyval.n_expr) = new string_node((yyvsp[0].tok)); }
#line 2498 "parser.cxx"
    break;

  case 136: /* constant: '[' set_elem_list ']'  */
#line 519 "parser.y"
                                { (yyval.n_expr) = new set_node((yyvsp[-2].tok), (yyvsp[-1].n_item), (yyvsp[0].tok)); }
#line 2504 "parser.cxx"
    break;

  case 137: /* constant: IDENT  */
#line 520 "parser.y"
                { (yyval.n_expr) = new atom_expr_node((yyvsp[0].tok)); }
#line 2510 "parser.cxx"
    break;

  case 138: /* set_elem_list: %empty  */
#line 522 "parser.y"
               { (yyval.n_item) = NULL; }
#line 2516 "parser.cxx"
    break;

  case 140: /* set_elem_list: set_elem ',' set_elem_list  */
#line 524 "parser.y"
                                          { (yyvsp[-2].n_item)->next = (yyvsp[0].n_item); (yyval.n_item) = (yyvsp[-2].n_item); }
#line 2522 "parser.cxx"
    break;

  case 141: /* set_elem: expr  */
#line 526 "parser.y"
               { (yyval.n_item) = new set_elem_node((yyvsp[0].n_expr)); }
#line 2528 "parser.cxx"
    break;

  case 142: /* set_elem: expr DOTS expr  */
#line 527 "parser.y"
                         { (yyval.n_item) = new set_range_node((yyvsp[-2].n_expr), (yyvsp[-1].tok), (yyvsp[0].n_expr)); }
#line 2534 "parser.cxx"
    break;

  case 144: /* expr_list: expr ',' expr_list  */
#line 529 "parser.y"
                                     { (yyvsp[-2].n_expr)->next = (yyvsp[0].n_expr); (yyval.n_expr) = (yyvsp[-2].n_expr); }
#line 2540 "parser.cxx"
    break;

  case 146: /* act_param_list: act_param ',' act_param_list  */
#line 532 "parser.y"
                                   { (yyvsp[-2].n_expr)->next = (yyvsp[0].n_expr); (yyval.n_expr) = (yyvsp[-2].n_expr); }
#line 2546 "parser.cxx"
    break;

  case 148: /* act_param: %empty  */
#line 534 "parser.y"
                  { (yyval.n_expr) = new skipped_node(curr_token->prev_relevant()); }
#line 2552 "parser.cxx"
    break;

  case 149: /* record_constant: '(' field_init_list ')'  */
#line 537 "parser.y"
                                         { 
    (yyval.n_expr) = new record_constant_node((yyvsp[-2].tok), (yyvsp[-1].n_field), (yyvsp[0].tok)); 
}
#line 2560 "parser.cxx"
    break;

  case 150: /* field_init_list: field_init_item  */
#line 541 "parser.y"
                                 { (yyval.n_field) = (yyvsp[0].n_field); }
#line 2566 "parser.cxx"
    break;

  case 151: /* field_init_list: field_init_item ';' field_init_list  */
#line 542 "parser.y"
                                          { (yyvsp[-2].n_field)->next = (yyvsp[0].n_field); (yyval.n_field) = (yyvsp[-2].n_field); }
#line 2572 "parser.cxx"
    break;

  case 152: /* field_init_item: IDENT ':' expr  */
#line 544 "parser.y"
                                { (yyval.n_field) = new field_init_node((yyvsp[-2].tok), (yyvsp[-1].tok), (yyvsp[0].n_expr)); }
#line 2578 "parser.cxx"
    break;

  case 153: /* expr_group: '(' expr_list ')'  */
#line 547 "parser.y"
                              { (yyval.n_grp) = new expr_group_node((yyvsp[-2].tok), (yyvsp[-1].n_expr), (yyvsp[0].tok)); }
#line 2584 "parser.cxx"
    break;

  case 155: /* write_list: write_param ',' write_list  */
#line 550 "parser.y"
                                                     { (yyvsp[-2].n_wrtp)->next = (yyvsp[0].n_wrtp); (yyval.n_wrtp) = (yyvsp[-2].n_wrtp); }
#line 2590 "parser.cxx"
    break;

  case 156: /* write_param: expr  */
#line 552 "parser.y"
                   { (yyval.n_wrtp) = new write_param_node((yyvsp[0].n_expr)); }
#line 2596 "parser.cxx"
    break;

  case 157: /* write_param: expr ':' expr  */
#line 553 "parser.y"
                    { (yyval.n_wrtp) = new write_param_node((yyvsp[-2].n_expr), (yyvsp[-1].tok), (yyvsp[0].n_expr)); }
#line 2602 "parser.cxx"
    break;

  case 158: /* write_param: expr ':' expr ':' expr  */
#line 554 "parser.y"
                             { (yyval.n_wrtp) = new write_param_node((yyvsp[-4].n_expr), (yyvsp[-3].tok), (yyvsp[-2].n_expr), (yyvsp[-1].tok), (yyvsp[0].n_expr)); }
#line 2608 "parser.cxx"
    break;

  case 159: /* label_decl_part: LABEL label_list ';'  */
#line 597 "parser.y"
    { (yyval.n_decl) = new label_decl_part_node((yyvsp[-2].tok), (yyvsp[-1].toks), (yyvsp[0].tok)); }
#line 2614 "parser.cxx"
    break;

  case 160: /* label_list: ICONST  */
#line 599 "parser.y"
                   { (yyval.toks) = new token_list((yyvsp[0].tok)); }
#line 2620 "parser.cxx"
    break;

  case 161: /* label_list: ICONST ',' label_list  */
#line 600 "parser.y"
                                  { (yyval.toks) = new token_list((yyvsp[-2].tok), (yyvsp[0].toks)); }
#line 2626 "parser.cxx"
    break;

  case 162: /* label_list: IDENT  */
#line 601 "parser.y"
                  { (yyval.toks) = new token_list((yyvsp[0].tok)); }
#line 2632 "parser.cxx"
    break;

  case 163: /* label_list: IDENT ',' label_list  */
#line 602 "parser.y"
                                 { (yyval.toks) = new token_list((yyvsp[-2].tok), (yyvsp[0].toks)); }
#line 2638 "parser.cxx"
    break;

  case 164: /* const_def_part: CONST const_def_list  */
#line 605 "parser.y"
    { (yyval.n_decl) = new const_def_part_node((yyvsp[-1].tok), (yyvsp[0].n_cdef)); }
#line 2644 "parser.cxx"
    break;

  case 165: /* const_def_list: %empty  */
#line 607 "parser.y"
                { (yyval.n_cdef) = NULL; }
#line 2650 "parser.cxx"
    break;

  case 166: /* const_def_list: const_def ';' const_def_list  */
#line 608 "parser.y"
                                   { (yyvsp[-2].n_cdef)->next = (yyvsp[0].n_cdef); (yyval.n_cdef) = (yyvsp[-2].n_cdef); }
#line 2656 "parser.cxx"
    break;

  case 167: /* const_def: IDENT EQ expr  */
#line 610 "parser.y"
                         { (yyval.n_cdef) = new const_def_node((yyvsp[-2].tok), (yyvsp[-1].tok), (yyvsp[0].n_expr)); }
#line 2662 "parser.cxx"
    break;

  case 168: /* const_def: IDENT ':' const_type EQ expr  */
#line 611 "parser.y"
                               { (yyval.n_cdef) = new typed_const_def_node((yyvsp[-4].tok), (yyvsp[-3].tok), (yyvsp[-2].n_tpd), (yyvsp[-1].tok), (yyvsp[0].n_expr)); }
#line 2668 "parser.cxx"
    break;

  case 169: /* type_def_part: TYPE type_def_list  */
#line 614 "parser.y"
    { (yyval.n_decl) = new type_def_part_node((yyvsp[-1].tok), (yyvsp[0].n_tdef)); }
#line 2674 "parser.cxx"
    break;

  case 170: /* type_def_list: %empty  */
#line 616 "parser.y"
               { (yyval.n_tdef) = NULL; }
#line 2680 "parser.cxx"
    break;

  case 171: /* type_def_list: type_def ';' type_def_list  */
#line 617 "parser.y"
                                 { (yyvsp[-2].n_tdef)->next = (yyvsp[0].n_tdef); (yyval.n_tdef) = (yyvsp[-2].n_tdef); }
#line 2686 "parser.cxx"
    break;

  case 172: /* type_def: IDENT EQ type  */
#line 619 "parser.y"
                        { (yyval.n_tdef) = new type_def_node((yyvsp[-2].tok), (yyvsp[-1].tok), (yyvsp[0].n_tpd)); }
#line 2692 "parser.cxx"
    break;

  case 173: /* var_decl_part: VAR var_decl_list  */
#line 622 "parser.y"
     { (yyval.n_decl) = new var_decl_part_node((yyvsp[-1].tok), (yyvsp[0].n_vdcl)); }
#line 2698 "parser.cxx"
    break;

  case 174: /* var_decl_list: %empty  */
#line 624 "parser.y"
               { (yyval.n_vdcl) = NULL; }
#line 2704 "parser.cxx"
    break;

  case 176: /* var_decl_list: var_decl ';' SCOPE  */
#line 627 "parser.y"
       { 
	 (yyvsp[-2].n_vdcl)->scope = (yyvsp[0].tok);
	 (yyvsp[0].tok)->disable();
       }
#line 2713 "parser.cxx"
    break;

  case 177: /* var_decl_list: var_decl ';' SCOPE ';' var_decl_list  */
#line 632 "parser.y"
       { 
	 (yyvsp[-4].n_vdcl)->scope = (yyvsp[-2].tok);
	 token::remove((yyvsp[-2].tok), (yyvsp[-1].tok));	    
	 (yyvsp[-4].n_vdcl)->next = (yyvsp[0].n_vdcl); (yyval.n_vdcl) = (yyvsp[-4].n_vdcl); 
       }
#line 2723 "parser.cxx"
    break;

  case 178: /* var_decl_list: var_decl ';' var_decl_list  */
#line 637 "parser.y"
                                  { (yyvsp[-2].n_vdcl)->next = (yyvsp[0].n_vdcl); (yyval.n_vdcl) = (yyvsp[-2].n_vdcl); }
#line 2729 "parser.cxx"
    break;

  case 179: /* var_decl: ident_list ':' type  */
#line 639 "parser.y"
                              { (yyval.n_vdcl) = new var_decl_node((yyvsp[-2].toks), (yyvsp[-1].tok), (yyvsp[0].n_tpd)); }
#line 2735 "parser.cxx"
    break;

  case 180: /* var_decl: IDENT ORIGIN expr ':' simple_type  */
#line 641 "parser.y"
       { (yyval.n_vdcl) = (var_decl_node*)new var_origin_decl_node((yyvsp[-4].tok), (yyvsp[-3].tok), (yyvsp[-2].n_expr), (yyvsp[-1].tok), (yyvsp[0].n_tpd)); }
#line 2741 "parser.cxx"
    break;

  case 181: /* proc_decl: PROCEDURE IDENT formal_params  */
#line 645 "parser.y"
               { (yyval.n_decl) = new proc_decl_node((yyvsp[-2].tok), (yyvsp[-1].tok), (yyvsp[0].n_plist)); }
#line 2747 "parser.cxx"
    break;

  case 182: /* proc_decl: FUNCTION IDENT formal_params ':' type  */
#line 647 "parser.y"
               { (yyval.n_decl) = new proc_decl_node((yyvsp[-4].tok), (yyvsp[-3].tok), (yyvsp[-2].n_plist), (yyvsp[-1].tok), (yyvsp[0].n_tpd)); }
#line 2753 "parser.cxx"
    break;

  case 183: /* proc_fwd_decl: PROCEDURE IDENT formal_params ';' qualifiers ';'  */
#line 652 "parser.y"
        { (yyval.n_decl) = new proc_fwd_decl_node((yyvsp[-5].tok), (yyvsp[-4].tok), (yyvsp[-3].n_plist), NULL, NULL, (yyvsp[-2].tok), (yyvsp[-1].toks), (yyvsp[0].tok)); }
#line 2759 "parser.cxx"
    break;

  case 184: /* proc_fwd_decl: FUNCTION IDENT formal_params ':' type ';' qualifiers ';'  */
#line 654 "parser.y"
        { (yyval.n_decl) = new proc_fwd_decl_node((yyvsp[-7].tok), (yyvsp[-6].tok), (yyvsp[-5].n_plist), (yyvsp[-4].tok), (yyvsp[-3].n_tpd), (yyvsp[-2].tok), (yyvsp[-1].toks), (yyvsp[0].tok)); }
#line 2765 "parser.cxx"
    break;

  case 185: /* proc_spec: PROCEDURE IDENT formal_params ';'  */
#line 658 "parser.y"
        { (yyval.n_decl) = new proc_fwd_decl_node((yyvsp[-3].tok), (yyvsp[-2].tok), (yyvsp[-1].n_plist), NULL, NULL, (yyvsp[0].tok)); }
#line 2771 "parser.cxx"
    break;

  case 186: /* proc_spec: FUNCTION IDENT formal_params ':' type ';'  */
#line 660 "parser.y"
        { (yyval.n_decl) = new proc_fwd_decl_node((yyvsp[-5].tok), (yyvsp[-4].tok), (yyvsp[-3].n_plist), (yyvsp[-2].tok), (yyvsp[-1].n_tpd), (yyvsp[0].tok)); }
#line 2777 "parser.cxx"
    break;

  case 187: /* proc_def: PROCEDURE IDENT formal_params ';' block ';'  */
#line 664 "parser.y"
               { (yyval.n_decl) = new proc_def_node((yyvsp[-5].tok), NULL, NULL, (yyvsp[-4].tok), (yyvsp[-3].n_plist), NULL, NULL, (yyvsp[-2].tok), NULL, NULL, (yyvsp[-1].n_block), (yyvsp[0].tok)); }
#line 2783 "parser.cxx"
    break;

  case 188: /* proc_def: FUNCTION IDENT formal_params ':' type ';' block ';'  */
#line 666 "parser.y"
               { (yyval.n_decl) = new proc_def_node((yyvsp[-7].tok), NULL, NULL, (yyvsp[-6].tok), (yyvsp[-5].n_plist), (yyvsp[-4].tok), (yyvsp[-3].n_tpd), (yyvsp[-2].tok), NULL, NULL, (yyvsp[-1].n_block), (yyvsp[0].tok)); }
#line 2789 "parser.cxx"
    break;

  case 189: /* proc_def: PROCEDURE IDENT '.' IDENT formal_params ';' block ';'  */
#line 668 "parser.y"
               { (yyval.n_decl) = new proc_def_node((yyvsp[-7].tok), (yyvsp[-6].tok), (yyvsp[-5].tok), (yyvsp[-4].tok), (yyvsp[-3].n_plist), NULL, NULL, (yyvsp[-2].tok), NULL, NULL, (yyvsp[-1].n_block), (yyvsp[0].tok)); }
#line 2795 "parser.cxx"
    break;

  case 190: /* proc_def: FUNCTION IDENT '.' IDENT formal_params ':' type ';' block ';'  */
#line 670 "parser.y"
               { (yyval.n_decl) = new proc_def_node((yyvsp[-9].tok), (yyvsp[-8].tok), (yyvsp[-7].tok), (yyvsp[-6].tok), (yyvsp[-5].n_plist), (yyvsp[-4].tok), (yyvsp[-3].n_tpd), (yyvsp[-2].tok), NULL, NULL, (yyvsp[-1].n_block), (yyvsp[0].tok)); }
#line 2801 "parser.cxx"
    break;

  case 191: /* proc_def: FUNCTION IDENT ';' block ';'  */
#line 672 "parser.y"
               { (yyval.n_decl) = new proc_def_node((yyvsp[-4].tok), NULL, NULL, (yyvsp[-3].tok), NULL, NULL, NULL, (yyvsp[-2].tok), NULL, NULL, (yyvsp[-1].n_block), (yyvsp[0].tok)); }
#line 2807 "parser.cxx"
    break;

  case 192: /* proc_def: PROCEDURE IDENT formal_params ';' FAR ';' block ';'  */
#line 674 "parser.y"
               { (yyval.n_decl) = new proc_def_node((yyvsp[-7].tok), NULL, NULL, (yyvsp[-6].tok), (yyvsp[-5].n_plist), NULL, NULL, (yyvsp[-4].tok), (yyvsp[-3].tok), (yyvsp[-2].tok), (yyvsp[-1].n_block), (yyvsp[0].tok)); }
#line 2813 "parser.cxx"
    break;

  case 193: /* proc_def: FUNCTION IDENT formal_params ':' type ';' FAR ';' block ';'  */
#line 676 "parser.y"
               { (yyval.n_decl) = new proc_def_node((yyvsp[-9].tok), NULL, NULL, (yyvsp[-8].tok), (yyvsp[-7].n_plist), (yyvsp[-6].tok), (yyvsp[-5].n_tpd), (yyvsp[-4].tok), (yyvsp[-3].tok), (yyvsp[-2].tok), (yyvsp[-1].n_block), (yyvsp[0].tok)); }
#line 2819 "parser.cxx"
    break;

  case 194: /* proc_def: FUNCTION IDENT ';' FAR ';' block ';'  */
#line 678 "parser.y"
               { (yyval.n_decl) = new proc_def_node((yyvsp[-6].tok), NULL, NULL, (yyvsp[-5].tok), NULL, NULL, NULL, (yyvsp[-4].tok), (yyvsp[-3].tok), (yyvsp[-2].tok), (yyvsp[-1].n_block), (yyvsp[0].tok)); }
#line 2825 "parser.cxx"
    break;

  case 195: /* qualifiers: IDENT qualifiers  */
#line 680 "parser.y"
                             { (yyval.toks) = new token_list((yyvsp[-1].tok), (yyvsp[0].toks)); }
#line 2831 "parser.cxx"
    break;

  case 196: /* qualifiers: SCOPE qualifiers  */
#line 681 "parser.y"
                       { (yyval.toks) = new token_list((yyvsp[-1].tok), (yyvsp[0].toks)); }
#line 2837 "parser.cxx"
    break;

  case 197: /* qualifiers: IDENT  */
#line 682 "parser.y"
            { (yyval.toks) = new token_list((yyvsp[0].tok)); }
#line 2843 "parser.cxx"
    break;

  case 198: /* qualifiers: SCOPE  */
#line 683 "parser.y"
            { (yyval.toks) = new token_list((yyvsp[0].tok)); }
#line 2849 "parser.cxx"
    break;

  case 199: /* formal_params: %empty  */
#line 686 "parser.y"
               { (yyval.n_plist) = NULL; }
#line 2855 "parser.cxx"
    break;

  case 200: /* formal_params: '(' formal_param_list ')'  */
#line 687 "parser.y"
                                { (yyval.n_plist) = new param_list_node((yyvsp[-2].tok), (yyvsp[-1].n_decl), (yyvsp[0].tok)); }
#line 2861 "parser.cxx"
    break;

  case 202: /* formal_param_list: formal_param ';' formal_param_list  */
#line 690 "parser.y"
                                         { (yyvsp[-2].n_decl)->next = (yyvsp[0].n_decl); (yyval.n_decl) = (yyvsp[-2].n_decl); }
#line 2867 "parser.cxx"
    break;

  case 203: /* formal_param: VAR param_decl  */
#line 692 "parser.y"
                             { (yyval.n_decl) = new var_decl_part_node((yyvsp[-1].tok), (yyvsp[0].n_vdcl)); }
#line 2873 "parser.cxx"
    break;

  case 204: /* formal_param: param_decl  */
#line 693 "parser.y"
                 { (yyval.n_decl) = (yyvsp[0].n_vdcl); }
#line 2879 "parser.cxx"
    break;

  case 206: /* param_decl: ident_list ':' param_type  */
#line 695 "parser.y"
                                      { (yyval.n_vdcl) = new var_decl_node((yyvsp[-2].toks), (yyvsp[-1].tok), (yyvsp[0].n_tpd)); }
#line 2885 "parser.cxx"
    break;

  case 207: /* param_decl: ident_list  */
#line 696 "parser.y"
                 { (yyval.n_vdcl) = new var_decl_node((yyvsp[0].toks), NULL, NULL); }
#line 2891 "parser.cxx"
    break;

  case 226: /* fptr_type: FUNCTION formal_params ':' type  */
#line 710 "parser.y"
    { (yyval.n_tpd) = new fptr_tpd_node((yyvsp[-3].tok), (yyvsp[-2].n_plist), (yyvsp[-1].tok), (yyvsp[0].n_tpd)); }
#line 2897 "parser.cxx"
    break;

  case 227: /* fptr_type: PROCEDURE formal_params  */
#line 711 "parser.y"
                              { (yyval.n_tpd) = new fptr_tpd_node((yyvsp[-1].tok), (yyvsp[0].n_plist)); }
#line 2903 "parser.cxx"
    break;

  case 228: /* string_type: STRING '[' expr ']'  */
#line 713 "parser.y"
                                 { (yyval.n_tpd) = new varying_tpd_node((yyvsp[-3].tok), (yyvsp[-2].tok), (yyvsp[-1].n_expr), (yyvsp[0].tok)); }
#line 2909 "parser.cxx"
    break;

  case 229: /* simple_type: IDENT  */
#line 715 "parser.y"
                   { (yyval.n_tpd) = new simple_tpd_node((yyvsp[0].tok)); }
#line 2915 "parser.cxx"
    break;

  case 230: /* simple_type: STRING  */
#line 716 "parser.y"
             { (yyval.n_tpd) = new string_tpd_node((yyvsp[0].tok)); }
#line 2921 "parser.cxx"
    break;

  case 231: /* array_type: packed ARRAY '[' indices ']' OF type  */
#line 719 "parser.y"
    { (yyval.n_tpd) = new array_tpd_node((yyvsp[-6].tok), (yyvsp[-5].tok), (yyvsp[-4].tok), (yyvsp[-3].n_idx), (yyvsp[-2].tok), (yyvsp[-1].tok), (yyvsp[0].n_tpd)); }
#line 2927 "parser.cxx"
    break;

  case 232: /* const_array_type: packed ARRAY '[' indices ']' OF const_type  */
#line 722 "parser.y"
    { (yyval.n_tpd) = new array_tpd_node((yyvsp[-6].tok), (yyvsp[-5].tok), (yyvsp[-4].tok), (yyvsp[-3].n_idx), (yyvsp[-2].tok), (yyvsp[-1].tok), (yyvsp[0].n_tpd)); }
#line 2933 "parser.cxx"
    break;

  case 233: /* conformant_array_type: packed ARRAY '[' conformant_indices ']' OF simple_type  */
#line 725 "parser.y"
         { (yyval.n_tpd) = new array_tpd_node((yyvsp[-6].tok), (yyvsp[-5].tok), (yyvsp[-4].tok), (yyvsp[-3].n_idx), (yyvsp[-2].tok), (yyvsp[-1].tok), (yyvsp[0].n_tpd)); }
#line 2939 "parser.cxx"
    break;

  case 234: /* conformant_array_type: packed ARRAY '[' conformant_indices ']' OF conformant_array_type  */
#line 727 "parser.y"
         { (yyval.n_tpd) = new array_tpd_node((yyvsp[-6].tok), (yyvsp[-5].tok), (yyvsp[-4].tok), (yyvsp[-3].n_idx), (yyvsp[-2].tok), (yyvsp[-1].tok), (yyvsp[0].n_tpd)); }
#line 2945 "parser.cxx"
    break;

  case 235: /* enum_type: '(' ident_list ')'  */
#line 729 "parser.y"
                              { (yyval.n_tpd) = new enum_tpd_node((yyvsp[-2].tok), (yyvsp[-1].toks), (yyvsp[0].tok)); }
#line 2951 "parser.cxx"
    break;

  case 236: /* range_type: expr DOTS expr  */
#line 732 "parser.y"
    { (yyval.n_tpd) = new range_tpd_node((yyvsp[-2].n_expr), (yyvsp[-1].tok), (yyvsp[0].n_expr)); }
#line 2957 "parser.cxx"
    break;

  case 237: /* pointer_type: '^' type  */
#line 734 "parser.y"
                       { (yyval.n_tpd) = new ptr_tpd_node((yyvsp[-1].tok), (yyvsp[0].n_tpd)); }
#line 2963 "parser.cxx"
    break;

  case 238: /* set_type: packed SET OF type  */
#line 736 "parser.y"
                             { (yyval.n_tpd) = new set_tpd_node((yyvsp[-3].tok), (yyvsp[-2].tok), (yyvsp[-1].tok), (yyvsp[0].n_tpd)); }
#line 2969 "parser.cxx"
    break;

  case 239: /* const_set_type: packed SET OF const_type  */
#line 738 "parser.y"
                                         { (yyval.n_tpd) = new set_tpd_node((yyvsp[-3].tok), (yyvsp[-2].tok), (yyvsp[-1].tok), (yyvsp[0].n_tpd)); }
#line 2975 "parser.cxx"
    break;

  case 240: /* record_type: packed RECORD field_list END  */
#line 741 "parser.y"
    { (yyval.n_tpd) = new record_tpd_node((yyvsp[-3].tok), (yyvsp[-2].tok), (yyvsp[-1].n_fldls), (yyvsp[0].tok)); }
#line 2981 "parser.cxx"
    break;

  case 241: /* object_type: OBJECT object_components END  */
#line 744 "parser.y"
    { (yyval.n_tpd) = new object_tpd_node((yyvsp[-2].tok), NULL, NULL, NULL, (yyvsp[-1].n_decl), (yyvsp[0].tok)); }
#line 2987 "parser.cxx"
    break;

  case 242: /* object_type: OBJECT '(' IDENT ')' object_components END  */
#line 746 "parser.y"
    { (yyval.n_tpd) = new object_tpd_node((yyvsp[-5].tok), (yyvsp[-4].tok), (yyvsp[-3].tok), (yyvsp[-2].tok), (yyvsp[-1].n_decl), (yyvsp[0].tok)); }
#line 2993 "parser.cxx"
    break;

  case 243: /* object_components: object_fields object_methods  */
#line 749 "parser.y"
    { (yyvsp[-1].n_decl)->next = (yyvsp[0].n_decl); (yyval.n_decl) = (yyvsp[-1].n_decl); }
#line 2999 "parser.cxx"
    break;

  case 246: /* object_fields: field_decl_list  */
#line 754 "parser.y"
    { (yyval.n_decl) = new var_decl_part_node(NULL, (yyvsp[0].n_vdcl)); }
#line 3005 "parser.cxx"
    break;

  case 248: /* field_decl_list: var_decl ';'  */
#line 757 "parser.y"
                    { (yyval.n_vdcl) = (yyvsp[-1].n_vdcl); }
#line 3011 "parser.cxx"
    break;

  case 249: /* field_decl_list: var_decl ';' field_decl_list  */
#line 758 "parser.y"
                                    { (yyvsp[-2].n_vdcl)->next = (yyvsp[0].n_vdcl); (yyval.n_vdcl) = (yyvsp[-2].n_vdcl); }
#line 3017 "parser.cxx"
    break;

  case 252: /* object_methods: proc_fwd_decl object_methods  */
#line 761 "parser.y"
                                 { (yyvsp[-1].n_decl)->next = (yyvsp[0].n_decl); (yyval.n_decl) = (yyvsp[-1].n_decl); }
#line 3023 "parser.cxx"
    break;

  case 253: /* object_methods: proc_spec object_methods  */
#line 762 "parser.y"
                             { (yyvsp[-1].n_decl)->next = (yyvsp[0].n_decl); (yyval.n_decl) = (yyvsp[-1].n_decl); }
#line 3029 "parser.cxx"
    break;

  case 254: /* file_type: packed FIL OF type  */
#line 766 "parser.y"
                              { (yyval.n_tpd) = new file_tpd_node((yyvsp[-3].tok), (yyvsp[-2].tok), (yyvsp[-1].tok), (yyvsp[0].n_tpd)); }
#line 3035 "parser.cxx"
    break;

  case 255: /* packed: %empty  */
#line 768 "parser.y"
        { (yyval.tok) = NULL; }
#line 3041 "parser.cxx"
    break;

  case 258: /* conformant_indices: conformant_index ';' conformant_indices  */
#line 771 "parser.y"
                                              { (yyvsp[-2].n_idx)->next = (yyvsp[0].n_idx); (yyval.n_idx) = (yyvsp[-2].n_idx); }
#line 3047 "parser.cxx"
    break;

  case 259: /* conformant_index: IDENT DOTS IDENT ':' type  */
#line 774 "parser.y"
    { (yyval.n_idx) = new conformant_index_node((yyvsp[-4].tok), (yyvsp[-3].tok), (yyvsp[-2].tok), (yyvsp[-1].tok), (yyvsp[0].n_tpd)); }
#line 3053 "parser.cxx"
    break;

  case 261: /* indices: index_spec ',' indices  */
#line 777 "parser.y"
    { (yyvsp[-2].n_idx)->next = (yyvsp[0].n_idx); (yyval.n_idx) = (yyvsp[-2].n_idx); }
#line 3059 "parser.cxx"
    break;

  case 262: /* index_spec: simple_type  */
#line 779 "parser.y"
                        { (yyval.n_idx) = new type_index_node((yyvsp[0].n_tpd)); }
#line 3065 "parser.cxx"
    break;

  case 263: /* index_spec: expr DOTS expr  */
#line 780 "parser.y"
                     { (yyval.n_idx) = new range_index_node((yyvsp[-2].n_expr), (yyvsp[-1].tok), (yyvsp[0].n_expr)); }
#line 3071 "parser.cxx"
    break;

  case 264: /* field_list: fixed_part variant_part  */
#line 785 "parser.y"
        { (yyval.n_fldls) = new field_list_node((yyvsp[-1].n_vdcl), (yyvsp[0].n_varp)); }
#line 3077 "parser.cxx"
    break;

  case 265: /* field_list: fixed_part  */
#line 787 "parser.y"
        { (yyval.n_fldls) = new field_list_node((yyvsp[0].n_vdcl)); }
#line 3083 "parser.cxx"
    break;

  case 267: /* variant_part: CASE selector OF variant_list  */
#line 792 "parser.y"
{ 
    (yyval.n_varp) = new variant_part_node((yyvsp[-3].tok), (yyvsp[-2].n_sel), (yyvsp[-1].tok), (yyvsp[0].n_vari)); 
}
#line 3091 "parser.cxx"
    break;

  case 268: /* selector: IDENT ':' type  */
#line 796 "parser.y"
                         { (yyval.n_sel) = new selector_node((yyvsp[-2].tok), (yyvsp[-1].tok), (yyvsp[0].n_tpd)); }
#line 3097 "parser.cxx"
    break;

  case 269: /* selector: type  */
#line 797 "parser.y"
               { (yyval.n_sel) = new selector_node(NULL, NULL, (yyvsp[0].n_tpd)); }
#line 3103 "parser.cxx"
    break;

  case 271: /* variant_list: variant ';'  */
#line 801 "parser.y"
                      { (yyval.n_vari) = (yyvsp[-1].n_vari); }
#line 3109 "parser.cxx"
    break;

  case 272: /* variant_list: variant ';' variant_list  */
#line 802 "parser.y"
                                   { (yyvsp[-2].n_vari)->next = (yyvsp[0].n_vari); (yyval.n_vari) = (yyvsp[-2].n_vari); }
#line 3115 "parser.cxx"
    break;

  case 273: /* variant: expr_list ':' '(' field_list ')'  */
#line 805 "parser.y"
{ 
    (yyval.n_vari) = new variant_node((yyvsp[-4].n_expr), (yyvsp[-3].tok), (yyvsp[-2].tok), (yyvsp[-1].n_fldls), (yyvsp[0].tok)); 
}
#line 3123 "parser.cxx"
    break;


#line 3127 "parser.cxx"

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

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
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
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
  ++yynerrs;

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

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
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
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 809 "parser.y"


int zzlex() { 
    curr_token = curr_token ? curr_token->next_relevant() 
	                    : token::first_relevant(); 
    if (curr_token->tag == TKN_SCONST) { 
        while (curr_token->next != NULL && curr_token->next->tag == TKN_SCONST)
        {
	    curr_token->in_text = curr_token->out_text = 
	      dprintf("%s%s", curr_token->in_text, curr_token->next->in_text);
	    curr_token->next->remove();
	}
    } else if (turbo_pascal && curr_token->tag == TKN_FILE 
	       && curr_token->next_relevant()->tag != TKN_OF) 
    {
	curr_token->tag = TKN_IDENT;
	curr_token->in_text = curr_token->out_text = "untyped_file";
	curr_token->name = nm_entry::find("untyped_file");
    }
    zzlval.tok = curr_token;
    return zzcnv_table[curr_token->tag];
}


