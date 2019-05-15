/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

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

/* Copy the first part of user declarations.  */
#line 1 "parser.y" /* yacc.c:339  */


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


#line 100 "parser.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "parser.tab.h".  */
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
#line 28 "parser.y" /* yacc.c:355  */

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

#line 259 "parser.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE zzlval;

int zzparse (void);

#endif /* !YY_ZZ_PARSER_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 276 "parser.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
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
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
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
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
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
#define YYLAST   1320

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  93
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  95
/* YYNRULES -- Number of rules.  */
#define YYNRULES  274
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  558

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   337

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
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
static const yytype_uint16 yyrline[] =
{
       0,   262,   262,   262,   286,   286,   286,   288,   289,   294,
     294,   296,   297,   305,   307,   309,   311,   314,   317,   318,
     320,   321,   323,   328,   329,   331,   331,   331,   331,   332,
     332,   332,   334,   336,   340,   341,   343,   343,   343,   343,
     344,   344,   344,   373,   374,   375,   376,   377,   378,   379,
     380,   381,   382,   383,   384,   385,   386,   387,   389,   391,
     393,   394,   395,   396,   397,   398,   399,   400,   401,   402,
     404,   406,   406,   408,   408,   410,   411,   413,   414,   426,
     426,   428,   429,   430,   432,   434,   435,   437,   438,   462,
     463,   464,   465,   466,   467,   468,   470,   471,   472,   473,
     474,   475,   476,   477,   478,   481,   482,   483,   484,   485,
     486,   487,   489,   490,   491,   492,   493,   494,   495,   497,
     498,   500,   502,   504,   506,   507,   509,   510,   511,   512,
     513,   514,   515,   517,   518,   519,   520,   521,   522,   524,
     525,   526,   528,   529,   531,   531,   533,   534,   536,   536,
     539,   543,   544,   546,   549,   552,   552,   554,   555,   556,
     598,   601,   602,   603,   604,   606,   609,   610,   612,   613,
     615,   618,   619,   621,   623,   626,   627,   628,   633,   639,
     641,   642,   646,   648,   653,   655,   659,   661,   665,   667,
     669,   671,   673,   675,   677,   679,   682,   683,   684,   685,
     688,   689,   691,   692,   694,   695,   695,   697,   698,   700,
     700,   706,   706,   706,   706,   706,   706,   707,   707,   707,
     707,   707,   709,   709,   709,   709,   709,   711,   713,   715,
     717,   718,   720,   723,   726,   728,   731,   733,   736,   738,
     740,   742,   745,   747,   750,   752,   753,   755,   758,   759,
     760,   762,   762,   763,   764,   768,   770,   770,   772,   773,
     775,   778,   778,   781,   782,   786,   788,   791,   793,   798,
     799,   802,   803,   804,   806
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ARRAY", "BEGIN", "CASE", "CONST", "DO",
  "DOTS", "ELSE", "END", "FIL", "FAR", "FOR", "FUNCTION", "GOTO", "IDENT",
  "ICONST", "IF", "IMPLEMENTATION", "INTERFACE", "LABEL", "LOOPHOLE",
  "OBJECT", "OF", "ORIGIN", "OTHERWISE", "PACKED", "PROCEDURE", "PROGRAM",
  "RCONST", "READ", "RECORD", "REPEAT", "RETURN", "SET", "SCONST",
  "STRING", "THEN", "TO", "TYPE", "UNTIL", "UNIT", "UNIT_END", "VAR",
  "WHILE", "WITH", "WRITE", "'.'", "','", "':'", "';'", "'('", "')'",
  "'['", "']'", "'^'", "'@'", "SCOPE", "LET", "LETADD", "LETSUB", "LETDIV",
  "LETMUL", "LETAND", "LETOR", "LETSHL", "LETSHR", "EQ", "NE", "LT", "LE",
  "GT", "GE", "IN", "PLUS", "MINUS", "OR", "XOR", "BINOR", "MOD", "DIV",
  "DIVR", "MUL", "AND", "SHR", "SHL", "BINAND", "UPLUS", "UMINUS", "NOT",
  "ADDRESS", "BINNOT", "$accept", "translation", "$@1", "input_file",
  "program", "progend", "module", "unit", "unit_def_list",
  "prog_param_list", "ident_list", "block", "decl_part_list", "decl_part",
  "unit_spec", "unit_decl_list", "unit_decl", "statement", "compoundst",
  "sequence", "actual_params", "write_params", "case_list", "otherwise",
  "case_items", "case_item", "case_elem_list", "case_elem", "expr",
  "simple_expr", "primary", "constant", "set_elem_list", "set_elem",
  "expr_list", "act_param_list", "act_param", "record_constant",
  "field_init_list", "field_init_item", "expr_group", "write_list",
  "write_param", "label_decl_part", "label_list", "const_def_part",
  "const_def_list", "const_def", "type_def_part", "type_def_list",
  "type_def", "var_decl_part", "var_decl_list", "var_decl", "proc_decl",
  "proc_fwd_decl", "proc_spec", "proc_def", "qualifiers", "formal_params",
  "formal_param_list", "formal_param", "param_decl", "param_type", "type",
  "const_type", "fptr_type", "string_type", "simple_type", "array_type",
  "const_array_type", "conformant_array_type", "enum_type", "range_type",
  "pointer_type", "set_type", "const_set_type", "record_type",
  "object_type", "object_components", "object_fields", "field_decl_list",
  "object_methods", "file_type", "packed", "conformant_indices",
  "conformant_index", "indices", "index_spec", "field_list", "fixed_part",
  "variant_part", "selector", "variant_list", "variant", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,    46,    44,
      58,    59,    40,    41,    91,    93,    94,    64,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337
};
# endif

#define YYPACT_NINF -392

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-392)))

#define YYTABLE_NINF -231

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -392,    18,   257,  -392,    66,    68,   896,    94,    86,    99,
     104,   121,   133,  -392,  -392,  -392,  -392,   -20,   144,  1072,
    -392,  -392,  -392,  -392,  -392,  -392,  -392,    12,  -392,   105,
     284,   134,   896,   139,   159,  -392,    10,   896,  -392,  -392,
    -392,  -392,  -392,  -392,   127,   164,   163,    24,   165,   153,
    -392,   172,   176,     7,   179,  -392,   183,  -392,   942,  -392,
    -392,   204,   733,    66,   214,   373,   107,   185,   190,   202,
     190,   199,  1072,  -392,  -392,    94,    94,  -392,   235,   203,
     243,   215,   639,   104,   247,   733,   243,   639,     0,   733,
     258,   114,   231,   233,   733,   232,  -392,   236,   942,  -392,
    -392,   733,   733,   237,   777,   733,   239,  -392,   285,  1042,
    -392,  -392,  -392,  -392,   246,   240,  -392,  -392,  -392,  -392,
    -392,    19,  -392,  -392,   216,   733,   733,   216,   733,   733,
    1213,  -392,  1253,  -392,   190,   253,   254,   144,   294,   264,
     301,   243,   269,  -392,   273,   271,  -392,   639,   277,   283,
     308,    23,  -392,  -392,  -392,   190,   309,   286,  1072,   190,
     901,    91,   190,   788,   639,   485,  -392,  -392,  -392,  -392,
    -392,  -392,  -392,  -392,  -392,  -392,  -392,  -392,   125,  -392,
     896,  1049,  -392,  -392,   291,  -392,   813,   288,  -392,  -392,
     942,   942,   929,   639,   733,  -392,  -392,   302,   434,   990,
     337,   733,  -392,   298,   299,   305,   310,   514,   314,   315,
     942,  -392,   347,   733,   733,  -392,   733,   733,   733,   733,
     733,   733,   733,   733,   733,   733,   733,   317,   133,   349,
     255,  -392,   255,  -392,   255,  -392,  -392,   733,   733,   733,
     733,   733,   733,   733,   733,   733,   733,   733,   733,   733,
     733,   733,   733,   733,   733,   733,   733,   733,   733,   733,
     733,   733,   733,   733,   733,   733,   324,  1072,  -392,   190,
     190,  -392,   212,  -392,   107,   327,   639,     5,   896,   332,
     338,   341,   344,     5,     5,   346,   348,  -392,   355,    13,
     354,   389,   357,    89,    89,   396,    89,  -392,  -392,  -392,
     128,   358,  -392,   733,   362,   385,   386,    90,    22,   133,
     733,   733,  -392,  -392,   942,   363,   365,   733,   942,   733,
     942,  1087,   366,   372,   733,  -392,  -392,   407,   733,  -392,
     733,  -392,  -392,  1213,   374,   379,   375,  1213,  1213,  1213,
    1213,  1213,  1213,  1213,  1213,  1213,  1193,  1213,   708,  -392,
     421,   427,   204,   602,   602,   602,   602,   602,   602,   602,
     367,   367,   367,   367,   367,  -392,  -392,  -392,  -392,  -392,
    -392,  -392,  -392,  1213,  1213,  1213,  1213,  1213,  1213,  1213,
    1213,  1213,   639,   383,   387,  -392,  -392,  -392,  -392,  -392,
     433,  -392,   356,   392,   412,  -392,  -392,  1072,  1072,  -392,
    -392,  -392,  -392,  -392,  -392,  -392,   639,   405,   133,  -392,
    -392,  -392,  -392,  -392,  1213,   708,   639,   639,  1072,  -392,
    -392,  -392,   453,    72,   413,   416,   418,   543,   951,    16,
     733,  -392,  1213,  -392,  -392,  -392,   733,  -392,   733,  1213,
     298,  -392,  1213,  -392,  -392,   733,  -392,  -392,   565,  -392,
     414,   422,  -392,   683,  -392,  -392,   423,  -392,   639,   419,
     426,   428,   429,     5,   430,   431,  -392,    27,  -392,   417,
    -392,  -392,   108,  -392,  -392,  -392,   942,   733,   942,   733,
     733,   733,   942,   469,  1160,  1125,  -392,  -392,   733,   459,
     708,    -5,  -392,   460,  1072,  -392,   470,  1072,  -392,  -392,
    -392,  -392,   475,   465,   442,   446,  -392,  -392,  -392,  -392,
    1213,   463,  -392,   942,  -392,   733,  1213,   204,  -392,   639,
     733,   444,   488,   443,   448,   449,  -392,   639,  -392,  -392,
     942,  -392,  1213,  -392,  -392,   447,  -392,   472,  -392,   508,
     501,   470,  -392,  -392,  -392,   474,   733,   477,   212,  -392,
     133,  -392,   639,  -392,  -392,   476,  -392,  -392
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       2,     0,    23,     1,   166,     0,    34,     0,     0,     0,
     171,     0,   175,     3,     4,     5,     6,     0,    11,    23,
      31,    25,    26,    27,    28,    30,    29,     0,   165,     0,
     200,     0,    34,     0,     0,    42,     0,    34,    36,    37,
      38,    39,    41,    40,   163,   161,     0,   200,    18,     0,
     170,     0,     0,    21,     0,   174,   176,     7,    43,    22,
      24,   256,     0,   166,     0,    23,     0,     0,   200,     0,
     200,     0,    23,    33,    35,     0,     0,   160,     0,     0,
       0,     0,   256,   171,     0,     0,     0,   256,   175,     0,
       0,     0,   138,   134,     0,     0,   135,    73,    43,    65,
     136,     0,     0,    75,     0,   139,    71,    69,     0,    64,
     126,   133,   230,   257,   231,     0,   226,   222,   223,   225,
     224,     0,   138,   134,     0,     0,     0,     0,     0,     0,
     168,    89,   119,   167,   200,     0,     0,     0,     0,    21,
       0,     0,   208,   206,     0,   202,   205,   256,     0,     0,
       0,     0,    17,   164,   162,   200,    23,     0,    23,   200,
     138,     0,   200,     0,   256,     0,   173,   221,   220,   211,
     212,   218,   219,   217,   215,   213,   214,   216,     0,   172,
      34,     0,    20,   180,   177,   179,     0,     0,    54,    53,
      43,    43,     0,   256,     0,    63,    74,     0,     0,   144,
       0,     0,    62,   138,     0,     0,   151,   142,     0,   140,
      43,    70,     0,   149,     0,   130,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   175,     0,
     124,   120,   119,   121,   125,   122,   123,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    23,   192,   200,
     200,   204,   256,   201,     0,     0,   256,   186,    34,     0,
       0,     0,     0,   198,   199,     0,     0,    19,     0,     9,
       0,     0,   248,   251,   252,     0,   246,   247,   245,   228,
     138,     0,   238,     0,     0,     0,     0,     0,     0,   175,
      81,     0,    68,    67,    43,     0,     0,     0,    43,     0,
      43,   157,     0,   155,     0,   127,   150,     0,     0,   137,
     139,    72,   129,   148,     0,   146,     0,    44,    45,    46,
      47,    48,    49,    50,    51,    52,     0,   169,     0,   267,
       0,   266,   256,   116,   117,   113,   114,   112,   115,   118,
      90,    91,   109,   111,   110,    92,    94,    95,    93,   105,
     108,   107,   106,    96,    97,    98,    99,   100,   103,   104,
     101,   102,   256,     0,     0,   182,   231,   207,   209,   210,
       0,   203,    23,     0,     0,    15,    16,    23,    23,   196,
     197,   188,   184,     8,    10,    12,   256,     0,   249,   253,
     254,   242,   244,   236,   237,     0,   256,   256,    23,    32,
     181,   178,     0,    77,    82,     0,    85,    87,     0,    56,
       0,   154,    61,    60,   145,    66,     0,    76,     0,   153,
       0,   152,   143,   141,   128,   149,   131,   229,     0,   263,
       0,   261,   241,   256,   265,   240,     0,   195,   256,     0,
       0,     0,     0,   187,     0,     0,   227,     0,   250,     0,
     255,   239,     0,    55,    80,    79,    43,    81,    43,     0,
       0,     0,    43,     0,     0,   158,   156,   147,     0,     0,
       0,   138,   270,     0,    23,   183,     0,    23,   189,   185,
     190,   193,     0,     0,     0,     0,    78,    83,    84,    86,
      88,     0,    57,    43,   132,     0,   264,   256,   262,   256,
       0,     0,     0,     0,   258,     0,   243,   256,    13,    14,
      43,    58,   159,   233,   269,     0,   268,   271,   191,     0,
       0,     0,   194,   232,    59,     0,   272,     0,   256,   259,
     175,   273,   256,   234,   235,     0,   260,   274
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -392,  -392,  -392,  -392,  -392,  -392,  -392,  -392,   110,  -392,
      -9,   -52,    21,  -392,    36,    -6,  -392,  -180,   -10,   -94,
    -392,  -392,  -392,  -392,    75,  -392,    96,  -392,   -55,   132,
     -38,  -392,   244,  -392,  -100,   131,  -392,  -392,   250,  -392,
    -392,   140,  -392,    38,    49,    42,   516,  -392,    46,   497,
    -392,    60,    -3,  -155,  -392,    63,  -149,  -392,  -219,   -33,
     307,  -392,   461,  -392,   -51,  -337,  -392,   -58,   -61,  -392,
    -392,    55,  -392,  -392,  -392,  -392,  -392,   -56,  -392,   137,
    -392,   197,    95,  -392,   -60,    65,  -392,  -391,  -392,    57,
    -392,  -392,  -392,    62,  -392
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,    13,    14,   405,    15,    16,   151,    81,
      54,    17,   137,    19,    20,    36,    37,   106,   107,   108,
     195,   202,   422,   476,   423,   424,   425,   426,   165,   131,
     132,   110,   208,   209,   204,   334,   335,   111,   205,   206,
     196,   322,   323,    21,    46,    22,    28,    29,    23,    50,
      51,    24,   349,    56,   143,    25,    43,    26,   286,    67,
     144,   145,   146,   387,   166,   115,   167,   168,   169,   170,
     118,   389,   171,   172,   173,   174,   119,   175,   176,   295,
     296,   297,   298,   177,   178,   523,   524,   450,   451,   350,
     351,   454,   493,   536,   537
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     117,   121,   200,   116,   197,   120,   292,   130,    59,    55,
     312,   313,   294,   136,    79,   455,    53,    58,     3,  -230,
     109,   283,   227,    18,   469,   482,    69,    58,    57,    72,
     181,    74,    85,   279,   186,   148,   183,   149,   112,   192,
      60,    31,    35,    53,    38,   519,   198,   199,    39,   199,
     207,   228,    40,    73,   229,    33,    86,   142,   184,   386,
     109,   404,    61,   284,   399,   400,    41,   483,    35,    42,
      38,   157,    78,    35,    39,    38,    66,   182,    40,    39,
      62,   474,    27,    40,    30,   185,   230,   232,   232,   234,
     232,   232,    41,   152,   316,    42,   275,    41,   475,   518,
      42,   266,    47,    31,   285,    31,   288,    53,   199,   418,
      44,    45,    58,   302,   336,    48,   331,    33,   504,    33,
      49,   138,   281,   139,   153,   154,   290,    59,   304,   299,
     188,   189,   142,   419,   429,   140,   305,    52,   433,   199,
     435,   280,   315,   291,   294,   294,   321,   294,    58,    53,
      68,   141,   109,   109,   301,    70,    63,   228,   333,   199,
     306,   337,   338,   339,   340,   341,   342,   343,   344,   345,
     346,   347,   109,   462,   307,    71,    75,    86,   324,   289,
     533,   -21,   353,   354,   355,   356,   357,   358,   359,   360,
     361,   362,   363,   364,   365,   366,   367,   368,   369,   370,
     371,   372,   373,   374,   375,   376,   377,   378,   379,   380,
     381,   388,   390,    76,    77,   383,    35,    80,    38,   434,
     112,    82,    39,    83,   293,   393,    40,    84,   112,    87,
     134,   113,   122,   123,    88,   147,   384,   385,    95,   113,
      41,   114,    66,    42,   462,    73,    96,   420,   414,   386,
     150,   155,   100,   292,   156,   427,   428,   231,   233,   139,
     235,   236,   432,     4,   199,   142,   158,   180,   104,   439,
     105,     5,   394,   442,   187,   207,   109,     6,     7,    59,
     109,   190,   109,   191,   193,     8,     9,   449,   194,   201,
     210,   117,   121,   448,   116,   211,   120,    10,   508,    11,
     225,    12,   512,   212,   267,   268,   421,   213,   226,   214,
     269,   215,   292,    86,    35,     4,    38,   270,   294,   272,
      39,   282,   274,     5,    40,   283,   273,   276,   278,    32,
       7,   456,    64,   531,   277,    65,    66,     8,    41,   287,
     461,    42,   309,   317,   320,   464,   465,   311,   324,    10,
     544,    34,   325,    12,   449,   466,   293,   293,   326,   293,
     448,   327,     4,   332,   330,   470,   471,   284,   460,   329,
       5,   348,   283,   352,   382,   484,    32,     7,   392,     4,
     395,   485,   506,   321,     8,   135,   396,     5,   409,   410,
     333,   412,   397,    32,     7,   398,    10,   401,    34,   402,
      12,     8,   492,   403,   406,   407,   411,   495,   408,   416,
     417,   413,   430,    10,   284,    34,   415,    12,   431,   437,
     535,   438,   427,   440,   427,   510,   511,   444,   445,   449,
     446,   452,   453,   516,   457,   448,   459,   458,   109,   152,
     109,   318,   521,   463,   109,   525,   535,   249,   250,   251,
     252,   253,   254,   255,   256,   419,   117,   121,   467,   116,
     532,   120,   505,   473,   477,   199,   478,   479,   534,   489,
     530,   490,   503,   496,   494,   109,   543,   497,   513,   498,
     499,   500,   501,   517,   520,   526,   522,   553,   390,   527,
     528,   199,   109,   303,   529,   538,   539,   545,   540,   541,
     542,   556,   237,   238,   239,   240,   241,   242,   243,   244,
     245,   246,   247,   248,   249,   250,   251,   252,   253,   254,
     255,   256,   328,   546,   547,   548,   550,   552,   472,   557,
     293,   237,   238,   239,   240,   241,   242,   243,   244,   245,
     246,   247,   248,   249,   250,   251,   252,   253,   254,   255,
     256,   480,   507,   237,   238,   239,   240,   241,   242,   243,
     244,   245,   246,   247,   248,   249,   250,   251,   252,   253,
     254,   255,   256,   488,   443,   509,   487,   441,   486,   133,
     179,   391,   237,   238,   239,   240,   241,   242,   243,   244,
     245,   246,   247,   248,   249,   250,   251,   252,   253,   254,
     255,   256,   271,   554,   502,   468,   549,   555,   551,     0,
       0,   237,   238,   239,   240,   241,   242,   243,   244,   245,
     246,   247,   248,   249,   250,   251,   252,   253,   254,   255,
     256,     0,     0,   237,   238,   239,   240,   241,   242,   243,
     244,   245,   246,   247,   248,   249,   250,   251,   252,   253,
     254,   255,   256,   159,     0,   160,   123,     0,     0,     0,
       0,    95,   161,     0,     0,     0,   113,   162,     0,    96,
       0,     0,     0,     0,     0,   100,   114,   244,   245,   246,
     247,   248,   249,   250,   251,   252,   253,   254,   255,   256,
       0,   163,     0,   105,     0,   164,   124,   159,     0,   491,
     123,     0,     0,     0,     0,    95,   161,     0,     0,     0,
     113,   162,     0,    96,   125,   126,     0,     0,     0,   100,
     114,     0,     0,   127,   160,   123,     0,     0,     0,   128,
      95,   129,     0,     0,     0,   163,     0,   105,    96,   164,
     124,     0,     0,     0,   100,   386,     0,     0,     0,   122,
     123,     0,     0,     0,     0,    95,     0,     0,   125,   126,
     104,     0,   105,    96,     0,   124,     0,   127,     0,   100,
       0,     0,     0,   128,     0,   129,     0,     0,     0,     0,
       0,     0,     0,   125,   126,   104,     0,   105,     0,     0,
     124,     0,   127,   203,   123,     0,     0,     0,   128,    95,
     129,     0,     0,     0,   300,   123,     0,    96,   125,   126,
      95,     0,     0,   100,     0,     0,     0,   127,    96,     0,
       0,     0,     0,   128,   100,   129,     0,     0,     0,   104,
       0,   105,     0,     0,   124,     0,     0,   310,     0,     0,
     104,     0,   105,     0,     0,   124,     0,     0,     0,     0,
       0,     0,   125,   126,     0,     0,     0,     0,     0,     0,
       0,   127,     0,   125,   126,     0,     0,   128,     0,   129,
       0,     0,   127,     0,     0,     0,     0,     0,   128,     0,
     129,   237,   238,   239,   240,   241,   242,   243,   244,   245,
     246,   247,   248,   249,   250,   251,   252,   253,   254,   255,
     256,  -230,     4,     0,     0,  -230,  -230,  -230,     0,     0,
      31,  -230,     0,     0,     0,  -230,    32,     7,     0,     0,
    -230,  -230,  -230,     0,    33,  -230,     0,     0,     0,  -230,
       0,     0,     0,     0,     0,     0,    10,     0,    34,     0,
      12,  -230,     0,  -230,  -230,  -230,    58,    89,     0,     0,
    -230,     0,  -230,     0,  -230,    90,  -230,    91,    92,    93,
      94,     0,     0,     0,    95,     0,     0,   314,     0,     0,
       0,     0,    96,    97,     0,    98,    99,     0,   100,     0,
       0,     0,     0,     0,     0,     0,     0,   101,   102,   103,
     481,     0,     0,     0,   104,     0,   105,   237,   238,   239,
     240,   241,   242,   243,   244,   245,   246,   247,   248,   249,
     250,   251,   252,   253,   254,   255,   256,     0,     0,   237,
     238,   239,   240,   241,   242,   243,   244,   245,   246,   247,
     248,   249,   250,   251,   252,   253,   254,   255,   256,   319,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   237,   238,
     239,   240,   241,   242,   243,   244,   245,   246,   247,   248,
     249,   250,   251,   252,   253,   254,   255,   256,     4,     0,
       0,     0,     0,     0,     0,     0,     5,     0,     0,     0,
     212,     0,    32,     7,   213,     0,   214,     0,   215,   308,
       8,   216,   217,   218,   219,   220,   221,   222,   223,   224,
       0,     0,    10,     0,    34,     0,    12,   237,   238,   239,
     240,   241,   242,   243,   244,   245,   246,   247,   248,   249,
     250,   251,   252,   253,   254,   255,   256,   436,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   237,   238,   239,   240,   241,
     242,   243,   244,   245,   246,   247,   248,   249,   250,   251,
     252,   253,   254,   255,   256,   515,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   237,   238,   239,   240,   241,   242,   243,
     244,   245,   246,   247,   248,   249,   250,   251,   252,   253,
     254,   255,   256,   514,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   237,   238,
     239,   240,   241,   242,   243,   244,   245,   246,   247,   248,
     249,   250,   251,   252,   253,   254,   255,   256,   447,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   237,   238,   239,   240,   241,   242,   243,   244,   245,
     246,   247,   248,   249,   250,   251,   252,   253,   254,   255,
     256,   237,   238,   239,   240,   241,   242,   243,   244,   245,
     246,   247,   248,   249,   250,   251,   252,   253,   254,   255,
     256,   212,     0,     0,     0,   213,     0,   214,     0,   215,
       0,     0,   257,   258,   259,   260,   261,   262,   263,   264,
     265
};

static const yytype_int16 yycheck[] =
{
      61,    61,   102,    61,    98,    61,   161,    62,    18,    12,
     190,   191,   161,    65,    47,   352,    16,     4,     0,    24,
      58,    16,     3,     2,   415,     9,    32,     4,    48,    19,
      85,    37,    25,    10,    89,    68,    87,    70,    16,    94,
      19,    14,     6,    16,     6,    50,   101,   102,     6,   104,
     105,    32,     6,    43,    35,    28,    49,    66,    58,    37,
      98,    48,    50,    58,   283,   284,     6,    51,    32,     6,
      32,    80,    48,    37,    32,    37,    52,    86,    32,    37,
      68,     9,    16,    37,    16,    88,   124,   125,   126,   127,
     128,   129,    32,    72,   194,    32,   147,    37,    26,   490,
      37,   134,    16,    14,   156,    14,   158,    16,   163,    19,
      16,    17,     4,   164,   214,    16,   210,    28,    10,    28,
      16,    14,   155,    16,    75,    76,   159,   137,     3,   162,
      16,    17,   141,    43,   314,    28,    11,    16,   318,   194,
     320,   151,   193,    52,   293,   294,   201,   296,     4,    16,
      16,    44,   190,   191,   163,    16,    51,    32,   213,   214,
      35,   216,   217,   218,   219,   220,   221,   222,   223,   224,
     225,   226,   210,   392,   180,    16,    49,    49,    50,   158,
     517,    53,   237,   238,   239,   240,   241,   242,   243,   244,
     245,   246,   247,   248,   249,   250,   251,   252,   253,   254,
     255,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   272,   272,    49,    51,   267,   180,    52,   180,   319,
      16,    68,   180,    51,   161,   276,   180,    51,    16,    50,
      16,    27,    16,    17,    51,    50,   269,   270,    22,    27,
     180,    37,    52,   180,   463,    43,    30,   308,   303,    37,
      51,    16,    36,   408,    51,   310,   311,   125,   126,    16,
     128,   129,   317,     6,   319,   274,    51,    20,    52,   324,
      54,    14,   278,   328,    16,   330,   314,    20,    21,   289,
     318,    50,   320,    50,    52,    28,    29,   348,    52,    52,
      51,   352,   352,   348,   352,    10,   352,    40,   478,    42,
      54,    44,   482,    48,    51,    51,   309,    52,    68,    54,
      16,    56,   467,    49,   278,     6,   278,    16,   467,    50,
     278,    12,    51,    14,   278,    16,    53,    50,    20,    20,
      21,   382,    48,   513,    51,    51,    52,    28,   278,    53,
     392,   278,    51,    41,     7,   397,   398,    59,    50,    40,
     530,    42,    53,    44,   415,   406,   293,   294,    53,   296,
     415,    51,     6,    16,    49,   416,   417,    58,    12,    55,
      14,    54,    16,    24,    50,   430,    20,    21,    51,     6,
      48,   436,   476,   438,    28,    12,    48,    14,   293,   294,
     445,   296,    51,    20,    21,    51,    40,    51,    42,    51,
      44,    28,   453,    48,    50,    16,    10,   458,    51,    24,
      24,    53,    49,    40,    58,    42,    54,    44,    53,    53,
     520,    49,   477,    16,   479,   480,   481,    53,    49,   490,
      55,    10,     5,   488,    51,   490,     3,    50,   476,   418,
     478,     7,   494,    51,   482,   497,   546,    80,    81,    82,
      83,    84,    85,    86,    87,    43,   517,   517,    53,   517,
     515,   517,   472,    10,    51,   520,    50,    49,   519,    55,
       7,    49,    55,    54,    51,   513,   527,    51,     9,    51,
      51,    51,    51,    24,    24,    10,    16,   548,   548,    24,
      48,   546,   530,     8,    48,    51,     8,    50,    55,    51,
      51,   552,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,     8,    51,    16,    24,    52,    50,   418,    53,
     467,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,     8,   477,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,     8,   330,   479,   445,   327,   438,    63,
      83,   274,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,   141,   548,   467,   408,   541,   550,   546,    -1,
      -1,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    -1,    -1,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    14,    -1,    16,    17,    -1,    -1,    -1,
      -1,    22,    23,    -1,    -1,    -1,    27,    28,    -1,    30,
      -1,    -1,    -1,    -1,    -1,    36,    37,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      -1,    52,    -1,    54,    -1,    56,    57,    14,    -1,    16,
      17,    -1,    -1,    -1,    -1,    22,    23,    -1,    -1,    -1,
      27,    28,    -1,    30,    75,    76,    -1,    -1,    -1,    36,
      37,    -1,    -1,    84,    16,    17,    -1,    -1,    -1,    90,
      22,    92,    -1,    -1,    -1,    52,    -1,    54,    30,    56,
      57,    -1,    -1,    -1,    36,    37,    -1,    -1,    -1,    16,
      17,    -1,    -1,    -1,    -1,    22,    -1,    -1,    75,    76,
      52,    -1,    54,    30,    -1,    57,    -1,    84,    -1,    36,
      -1,    -1,    -1,    90,    -1,    92,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    75,    76,    52,    -1,    54,    -1,    -1,
      57,    -1,    84,    16,    17,    -1,    -1,    -1,    90,    22,
      92,    -1,    -1,    -1,    16,    17,    -1,    30,    75,    76,
      22,    -1,    -1,    36,    -1,    -1,    -1,    84,    30,    -1,
      -1,    -1,    -1,    90,    36,    92,    -1,    -1,    -1,    52,
      -1,    54,    -1,    -1,    57,    -1,    -1,    24,    -1,    -1,
      52,    -1,    54,    -1,    -1,    57,    -1,    -1,    -1,    -1,
      -1,    -1,    75,    76,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    84,    -1,    75,    76,    -1,    -1,    90,    -1,    92,
      -1,    -1,    84,    -1,    -1,    -1,    -1,    -1,    90,    -1,
      92,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,     0,     6,    -1,    -1,     4,     5,     6,    -1,    -1,
      14,    10,    -1,    -1,    -1,    14,    20,    21,    -1,    -1,
      19,    20,    21,    -1,    28,    24,    -1,    -1,    -1,    28,
      -1,    -1,    -1,    -1,    -1,    -1,    40,    -1,    42,    -1,
      44,    40,    -1,    42,    43,    44,     4,     5,    -1,    -1,
      49,    -1,    51,    -1,    53,    13,    55,    15,    16,    17,
      18,    -1,    -1,    -1,    22,    -1,    -1,    38,    -1,    -1,
      -1,    -1,    30,    31,    -1,    33,    34,    -1,    36,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    45,    46,    47,
      39,    -1,    -1,    -1,    52,    -1,    54,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    -1,    -1,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    49,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,     6,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    14,    -1,    -1,    -1,
      48,    -1,    20,    21,    52,    -1,    54,    -1,    56,    50,
      28,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      -1,    -1,    40,    -1,    42,    -1,    44,    68,    69,    70,
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
      67
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
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
       8,    39,     9,    51,   121,   121,   134,   128,     8,    55,
      49,    16,   157,   185,    51,   157,    54,    51,    51,    51,
      51,    51,   172,    55,    10,   111,   112,   117,   110,   119,
     121,   121,   110,     9,    53,    50,   121,    24,   180,    50,
      24,   104,    16,   178,   179,   104,    10,    24,    48,    48,
       7,   110,   121,   158,   157,   127,   186,   187,    51,     8,
      55,    51,    51,   157,   110,    50,    51,    16,    24,   178,
      52,   186,    50,   161,   164,   182,   157,    53
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    93,    95,    94,    96,    96,    96,    97,    97,    98,
      98,    99,    99,   100,   100,   100,   100,   101,   102,   102,
     103,   103,   104,   105,   105,   106,   106,   106,   106,   106,
     106,   106,   107,   107,   108,   108,   109,   109,   109,   109,
     109,   109,   109,   110,   110,   110,   110,   110,   110,   110,
     110,   110,   110,   110,   110,   110,   110,   110,   110,   110,
     110,   110,   110,   110,   110,   110,   110,   110,   110,   110,
     111,   112,   112,   113,   113,   114,   114,   115,   115,   116,
     116,   117,   117,   117,   118,   119,   119,   120,   120,   121,
     121,   121,   121,   121,   121,   121,   121,   121,   121,   121,
     121,   121,   121,   121,   121,   121,   121,   121,   121,   121,
     121,   121,   121,   121,   121,   121,   121,   121,   121,   122,
     122,   122,   122,   122,   122,   122,   123,   123,   123,   123,
     123,   123,   123,   124,   124,   124,   124,   124,   124,   125,
     125,   125,   126,   126,   127,   127,   128,   128,   129,   129,
     130,   131,   131,   132,   133,   134,   134,   135,   135,   135,
     136,   137,   137,   137,   137,   138,   139,   139,   140,   140,
     141,   142,   142,   143,   144,   145,   145,   145,   145,   145,
     146,   146,   147,   147,   148,   148,   149,   149,   150,   150,
     150,   150,   150,   150,   150,   150,   151,   151,   151,   151,
     152,   152,   153,   153,   154,   154,   154,   155,   155,   156,
     156,   157,   157,   157,   157,   157,   157,   157,   157,   157,
     157,   157,   158,   158,   158,   158,   158,   159,   159,   160,
     161,   161,   162,   163,   164,   164,   165,   166,   167,   168,
     169,   170,   171,   171,   172,   172,   172,   173,   174,   174,
     174,   175,   175,   175,   175,   176,   177,   177,   178,   178,
     179,   180,   180,   181,   181,   182,   182,   183,   184,   185,
     185,   186,   186,   186,   187
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     1,     1,     1,     2,     6,     0,
       1,     1,     6,     9,     9,     6,     6,     1,     0,     3,
       3,     1,     2,     0,     2,     1,     1,     1,     1,     1,
       1,     1,     6,     3,     0,     2,     1,     1,     1,     1,
       1,     1,     1,     0,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     2,     2,     5,     4,     6,     7,     8,
       4,     4,     2,     2,     1,     1,     4,     3,     3,     1,
       3,     1,     3,     0,     1,     0,     3,     1,     3,     1,
       1,     0,     1,     3,     3,     1,     3,     1,     3,     1,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     1,
       2,     2,     2,     2,     2,     2,     1,     3,     4,     3,
       2,     4,     6,     1,     1,     1,     1,     3,     1,     0,
       1,     3,     1,     3,     1,     3,     1,     3,     1,     0,
       3,     1,     3,     3,     3,     1,     3,     1,     3,     5,
       3,     1,     3,     1,     3,     2,     0,     3,     3,     5,
       2,     0,     3,     3,     2,     0,     1,     3,     5,     3,
       3,     5,     3,     5,     6,     8,     4,     6,     6,     8,
       8,    10,     5,     8,    10,     7,     2,     2,     1,     1,
       0,     3,     1,     3,     2,     1,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     4,     2,     4,
       1,     1,     7,     7,     7,     7,     3,     3,     2,     4,
       4,     4,     3,     6,     2,     1,     1,     1,     1,     2,
       3,     1,     1,     2,     2,     4,     0,     1,     1,     3,
       5,     1,     3,     1,     3,     2,     1,     1,     4,     3,
       1,     1,     2,     3,     5
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
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
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
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
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
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
            /* Fall through.  */
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

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
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
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

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
      int yyn = yypact[*yyssp];
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
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
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
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
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
          yyp++;
          yyformat++;
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
  YYUSE (yytype);
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
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

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
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
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
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
| yyreduce -- Do a reduction.  |
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
        case 2:
#line 262 "parser.y" /* yacc.c:1646  */
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
#line 1934 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 281 "parser.y" /* yacc.c:1646  */
    { 
    (yyvsp[0].n_node)->attrib(ctx_program); 
    (yyvsp[0].n_node)->translate(ctx_program); 
}
#line 1943 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 288 "parser.y" /* yacc.c:1646  */
    { (yyval.n_node) = new program_node(NULL, NULL, NULL, NULL, (yyvsp[-1].n_block), (yyvsp[0].tok)); }
#line 1949 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 290 "parser.y" /* yacc.c:1646  */
    { 
    (yyval.n_node) = new program_node((yyvsp[-5].tok), (yyvsp[-4].tok), (yyvsp[-3].n_imp), (yyvsp[-2].tok), (yyvsp[-1].n_block), (yyvsp[0].tok));
}
#line 1957 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 294 "parser.y" /* yacc.c:1646  */
    { (yyval.tok) = NULL; }
#line 1963 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 296 "parser.y" /* yacc.c:1646  */
    { (yyval.n_node) = new module_node(NULL, NULL, NULL, NULL, (yyvsp[0].n_decl), NULL); }
#line 1969 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 298 "parser.y" /* yacc.c:1646  */
    { 
    (yyval.n_node) = new module_node((yyvsp[-5].tok), (yyvsp[-4].tok), (yyvsp[-3].n_imp), (yyvsp[-2].tok), (yyvsp[-1].n_decl), (yyvsp[0].tok));
}
#line 1977 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 306 "parser.y" /* yacc.c:1646  */
    { (yyval.n_node) = new unit_node((yyvsp[-8].tok), (yyvsp[-7].tok), (yyvsp[-6].tok), (yyvsp[-5].tok), (yyvsp[-4].n_decl), (yyvsp[-3].tok), (yyvsp[-2].n_decl), NULL, (yyvsp[-1].tok), (yyvsp[0].tok)); }
#line 1983 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 308 "parser.y" /* yacc.c:1646  */
    { (yyval.n_node) = new unit_node((yyvsp[-8].tok), (yyvsp[-7].tok), (yyvsp[-6].tok), (yyvsp[-5].tok), (yyvsp[-4].n_decl), (yyvsp[-3].tok), (yyvsp[-2].n_decl), (yyvsp[-1].n_comp), NULL, (yyvsp[0].tok)); }
#line 1989 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 310 "parser.y" /* yacc.c:1646  */
    { (yyval.n_node) = new unit_node(NULL, NULL, NULL, (yyvsp[-5].tok), (yyvsp[-4].n_decl), (yyvsp[-3].tok), (yyvsp[-2].n_decl), NULL, (yyvsp[-1].tok), (yyvsp[0].tok)); }
#line 1995 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 312 "parser.y" /* yacc.c:1646  */
    { (yyval.n_node) = new unit_node(NULL, NULL, NULL, (yyvsp[-5].tok), (yyvsp[-4].n_decl), (yyvsp[-3].tok), (yyvsp[-2].n_decl), (yyvsp[-1].n_comp), NULL, (yyvsp[0].tok)); }
#line 2001 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 317 "parser.y" /* yacc.c:1646  */
    { (yyval.n_imp) = NULL; }
#line 2007 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 318 "parser.y" /* yacc.c:1646  */
    { (yyval.n_imp) = new import_list_node((yyvsp[-2].tok), (yyvsp[-1].toks), (yyvsp[0].tok)); }
#line 2013 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 320 "parser.y" /* yacc.c:1646  */
    { (yyval.toks) = new token_list((yyvsp[-2].tok), (yyvsp[0].toks)); }
#line 2019 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 321 "parser.y" /* yacc.c:1646  */
    { (yyval.toks) = new token_list((yyvsp[0].tok)); }
#line 2025 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 324 "parser.y" /* yacc.c:1646  */
    {
    (yyval.n_block) = new block_node((yyvsp[-1].n_decl), (yyvsp[0].n_comp));
}
#line 2033 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 328 "parser.y" /* yacc.c:1646  */
    { (yyval.n_decl) = NULL; }
#line 2039 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 329 "parser.y" /* yacc.c:1646  */
    { (yyvsp[-1].n_decl)->next = (yyvsp[0].n_decl); (yyval.n_decl) = (yyvsp[-1].n_decl); }
#line 2045 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 335 "parser.y" /* yacc.c:1646  */
    {  (yyval.n_decl) = new unit_spec_node((yyvsp[-5].tok), (yyvsp[-4].tok), (yyvsp[-3].tok), (yyvsp[-2].tok), (yyvsp[-1].n_decl)); }
#line 2051 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 337 "parser.y" /* yacc.c:1646  */
    {  (yyval.n_decl) = new unit_spec_node(NULL, NULL, NULL, (yyvsp[-2].tok), (yyvsp[-1].n_decl)); }
#line 2057 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 340 "parser.y" /* yacc.c:1646  */
    { (yyval.n_decl) = NULL; }
#line 2063 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 341 "parser.y" /* yacc.c:1646  */
    { (yyvsp[-1].n_decl)->next = (yyvsp[0].n_decl); (yyval.n_decl) = (yyvsp[-1].n_decl); }
#line 2069 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 373 "parser.y" /* yacc.c:1646  */
    { (yyval.n_stmt) = new empty_node(curr_token->prev_relevant()); }
#line 2075 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 374 "parser.y" /* yacc.c:1646  */
    { (yyval.n_stmt) = new assign_node((yyvsp[-2].n_expr), (yyvsp[-1].tok), (yyvsp[0].n_expr)); }
#line 2081 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 375 "parser.y" /* yacc.c:1646  */
    { (yyval.n_stmt) = new assign_node((yyvsp[-2].n_expr), (yyvsp[-1].tok), (yyvsp[0].n_expr)); }
#line 2087 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 376 "parser.y" /* yacc.c:1646  */
    { (yyval.n_stmt) = new assign_node((yyvsp[-2].n_expr), (yyvsp[-1].tok), (yyvsp[0].n_expr)); }
#line 2093 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 377 "parser.y" /* yacc.c:1646  */
    { (yyval.n_stmt) = new assign_node((yyvsp[-2].n_expr), (yyvsp[-1].tok), (yyvsp[0].n_expr)); }
#line 2099 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 378 "parser.y" /* yacc.c:1646  */
    { (yyval.n_stmt) = new assign_node((yyvsp[-2].n_expr), (yyvsp[-1].tok), (yyvsp[0].n_expr)); }
#line 2105 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 379 "parser.y" /* yacc.c:1646  */
    { (yyval.n_stmt) = new assign_node((yyvsp[-2].n_expr), (yyvsp[-1].tok), (yyvsp[0].n_expr)); }
#line 2111 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 380 "parser.y" /* yacc.c:1646  */
    { (yyval.n_stmt) = new assign_node((yyvsp[-2].n_expr), (yyvsp[-1].tok), (yyvsp[0].n_expr)); }
#line 2117 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 381 "parser.y" /* yacc.c:1646  */
    { (yyval.n_stmt) = new assign_node((yyvsp[-2].n_expr), (yyvsp[-1].tok), (yyvsp[0].n_expr)); }
#line 2123 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 382 "parser.y" /* yacc.c:1646  */
    { (yyval.n_stmt) = new assign_node((yyvsp[-2].n_expr), (yyvsp[-1].tok), (yyvsp[0].n_expr)); }
#line 2129 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 383 "parser.y" /* yacc.c:1646  */
    { (yyval.n_stmt) = new goto_node((yyvsp[-1].tok), (yyvsp[0].tok)); }
#line 2135 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 384 "parser.y" /* yacc.c:1646  */
    { (yyval.n_stmt) = new goto_node((yyvsp[-1].tok), (yyvsp[0].tok)); }
#line 2141 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 385 "parser.y" /* yacc.c:1646  */
    { (yyval.n_stmt) = new switch_node((yyvsp[-4].tok), (yyvsp[-3].n_expr), (yyvsp[-2].tok), (yyvsp[-1].n_case), (yyvsp[0].tok)); }
#line 2147 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 386 "parser.y" /* yacc.c:1646  */
    { (yyval.n_stmt) = new if_node((yyvsp[-3].tok), (yyvsp[-2].n_expr), (yyvsp[-1].tok), (yyvsp[0].n_stmt)); }
#line 2153 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 388 "parser.y" /* yacc.c:1646  */
    { (yyval.n_stmt) = new if_node((yyvsp[-5].tok), (yyvsp[-4].n_expr), (yyvsp[-3].tok), (yyvsp[-2].n_stmt), (yyvsp[-1].tok), (yyvsp[0].n_stmt)); }
#line 2159 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 390 "parser.y" /* yacc.c:1646  */
    { (yyval.n_stmt) = new if_node((yyvsp[-6].tok), (yyvsp[-5].n_expr), (yyvsp[-4].tok), (yyvsp[-3].n_stmt), (yyvsp[-1].tok), (yyvsp[0].n_stmt)); }
#line 2165 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 392 "parser.y" /* yacc.c:1646  */
    { (yyval.n_stmt) = new for_node((yyvsp[-7].tok), (yyvsp[-6].tok), (yyvsp[-5].tok), (yyvsp[-4].n_expr), (yyvsp[-3].tok), (yyvsp[-2].n_expr), (yyvsp[-1].tok), (yyvsp[0].n_stmt)); }
#line 2171 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 393 "parser.y" /* yacc.c:1646  */
    { (yyval.n_stmt) = new while_node((yyvsp[-3].tok), (yyvsp[-2].n_expr), (yyvsp[-1].tok), (yyvsp[0].n_stmt)); }
#line 2177 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 394 "parser.y" /* yacc.c:1646  */
    { (yyval.n_stmt) = new repeat_node((yyvsp[-3].tok), (yyvsp[-2].n_stmt), (yyvsp[-1].tok), (yyvsp[0].n_expr)); }
#line 2183 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 395 "parser.y" /* yacc.c:1646  */
    { (yyval.n_stmt) = new write_node((yyvsp[-1].tok), (yyvsp[0].n_wrls)); }
#line 2189 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 396 "parser.y" /* yacc.c:1646  */
    { (yyval.n_stmt) = new read_node((yyvsp[-1].tok), (yyvsp[0].n_grp)); }
#line 2195 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 397 "parser.y" /* yacc.c:1646  */
    { (yyval.n_stmt) = new pcall_node((yyvsp[0].n_expr)); }
#line 2201 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 398 "parser.y" /* yacc.c:1646  */
    { (yyval.n_stmt) = new return_node((yyvsp[0].tok)); }
#line 2207 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 399 "parser.y" /* yacc.c:1646  */
    { (yyval.n_stmt) = new with_node((yyvsp[-3].tok), (yyvsp[-2].n_expr), (yyvsp[-1].tok), (yyvsp[0].n_stmt)); }
#line 2213 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 400 "parser.y" /* yacc.c:1646  */
    { (yyval.n_stmt) = new label_node((yyvsp[-2].tok), (yyvsp[-1].tok), (yyvsp[0].n_stmt)); }
#line 2219 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 401 "parser.y" /* yacc.c:1646  */
    { (yyval.n_stmt) = new label_node((yyvsp[-2].tok), (yyvsp[-1].tok), (yyvsp[0].n_stmt)); }
#line 2225 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 402 "parser.y" /* yacc.c:1646  */
    { (yyval.n_stmt) = (yyvsp[0].n_comp); }
#line 2231 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 404 "parser.y" /* yacc.c:1646  */
    { (yyval.n_comp) = new compound_node((yyvsp[-2].tok), (yyvsp[-1].n_stmt), (yyvsp[0].tok)); }
#line 2237 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 406 "parser.y" /* yacc.c:1646  */
    { (yyvsp[-2].n_stmt)->next = (yyvsp[0].n_stmt); (yyval.n_stmt) = (yyvsp[-2].n_stmt); }
#line 2243 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 408 "parser.y" /* yacc.c:1646  */
    { (yyval.n_grp) = NULL; }
#line 2249 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 408 "parser.y" /* yacc.c:1646  */
    { (yyval.n_grp) = (yyvsp[0].n_grp); }
#line 2255 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 410 "parser.y" /* yacc.c:1646  */
    { (yyval.n_wrls) = NULL; }
#line 2261 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 411 "parser.y" /* yacc.c:1646  */
    { (yyval.n_wrls) = new write_list_node((yyvsp[-2].tok), (yyvsp[-1].n_wrtp), (yyvsp[0].tok)); }
#line 2267 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 415 "parser.y" /* yacc.c:1646  */
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
#line 2282 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 428 "parser.y" /* yacc.c:1646  */
    { (yyval.n_case) = NULL; }
#line 2288 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 430 "parser.y" /* yacc.c:1646  */
    { (yyvsp[-2].n_case)->next = (yyvsp[0].n_case); (yyval.n_case) = (yyvsp[-2].n_case); }
#line 2294 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 432 "parser.y" /* yacc.c:1646  */
    { (yyval.n_case) = new case_node((yyvsp[-2].n_expr), (yyvsp[-1].tok), (yyvsp[0].n_stmt)); }
#line 2300 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 435 "parser.y" /* yacc.c:1646  */
    { (yyvsp[-2].n_expr)->next = (yyvsp[0].n_expr); (yyval.n_expr) = (yyvsp[-2].n_expr); }
#line 2306 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 437 "parser.y" /* yacc.c:1646  */
    { (yyval.n_expr) = (yyvsp[0].n_expr); }
#line 2312 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 438 "parser.y" /* yacc.c:1646  */
    { (yyval.n_expr) = new case_range_node((yyvsp[-2].n_expr), (yyvsp[-1].tok), (yyvsp[0].n_expr)); }
#line 2318 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 463 "parser.y" /* yacc.c:1646  */
    { (yyval.n_expr) = new op_node(tn_add, (yyvsp[-2].n_expr), (yyvsp[-1].tok), (yyvsp[0].n_expr)); }
#line 2324 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 464 "parser.y" /* yacc.c:1646  */
    { (yyval.n_expr) = new op_node(tn_sub, (yyvsp[-2].n_expr), (yyvsp[-1].tok), (yyvsp[0].n_expr)); }
#line 2330 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 465 "parser.y" /* yacc.c:1646  */
    { (yyval.n_expr) = new op_node(tn_mod, (yyvsp[-2].n_expr), (yyvsp[-1].tok), (yyvsp[0].n_expr)); }
#line 2336 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 466 "parser.y" /* yacc.c:1646  */
    { (yyval.n_expr) = new op_node(tn_mul, (yyvsp[-2].n_expr), (yyvsp[-1].tok), (yyvsp[0].n_expr)); }
#line 2342 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 467 "parser.y" /* yacc.c:1646  */
    { (yyval.n_expr) = new op_node(tn_div, (yyvsp[-2].n_expr), (yyvsp[-1].tok), (yyvsp[0].n_expr)); }
#line 2348 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 468 "parser.y" /* yacc.c:1646  */
    { (yyval.n_expr) = new op_node(tn_divr, (yyvsp[-2].n_expr), (yyvsp[-1].tok), (yyvsp[0].n_expr)); }
#line 2354 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 470 "parser.y" /* yacc.c:1646  */
    { (yyval.n_expr) = new op_node(tn_let, (yyvsp[-2].n_expr), (yyvsp[-1].tok), (yyvsp[0].n_expr)); }
#line 2360 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 471 "parser.y" /* yacc.c:1646  */
    { (yyval.n_expr) = new op_node(tn_letadd, (yyvsp[-2].n_expr), (yyvsp[-1].tok), (yyvsp[0].n_expr)); }
#line 2366 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 98:
#line 472 "parser.y" /* yacc.c:1646  */
    { (yyval.n_expr) = new op_node(tn_letsub, (yyvsp[-2].n_expr), (yyvsp[-1].tok), (yyvsp[0].n_expr)); }
#line 2372 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 99:
#line 473 "parser.y" /* yacc.c:1646  */
    { (yyval.n_expr) = new op_node(tn_letdiv, (yyvsp[-2].n_expr), (yyvsp[-1].tok), (yyvsp[0].n_expr)); }
#line 2378 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 100:
#line 474 "parser.y" /* yacc.c:1646  */
    { (yyval.n_expr) = new op_node(tn_letmul, (yyvsp[-2].n_expr), (yyvsp[-1].tok), (yyvsp[0].n_expr)); }
#line 2384 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 101:
#line 475 "parser.y" /* yacc.c:1646  */
    { (yyval.n_expr) = new op_node(tn_letshl, (yyvsp[-2].n_expr), (yyvsp[-1].tok), (yyvsp[0].n_expr)); }
#line 2390 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 102:
#line 476 "parser.y" /* yacc.c:1646  */
    { (yyval.n_expr) = new op_node(tn_letshr, (yyvsp[-2].n_expr), (yyvsp[-1].tok), (yyvsp[0].n_expr)); }
#line 2396 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 103:
#line 477 "parser.y" /* yacc.c:1646  */
    { (yyval.n_expr) = new op_node(tn_letand, (yyvsp[-2].n_expr), (yyvsp[-1].tok), (yyvsp[0].n_expr)); }
#line 2402 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 104:
#line 478 "parser.y" /* yacc.c:1646  */
    { (yyval.n_expr) = new op_node(tn_letor,  (yyvsp[-2].n_expr), (yyvsp[-1].tok), (yyvsp[0].n_expr)); }
#line 2408 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 105:
#line 481 "parser.y" /* yacc.c:1646  */
    { (yyval.n_expr) = new op_node(tn_and, (yyvsp[-2].n_expr), (yyvsp[-1].tok), (yyvsp[0].n_expr)); }
#line 2414 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 106:
#line 482 "parser.y" /* yacc.c:1646  */
    { (yyval.n_expr) = new op_node(tn_binand, (yyvsp[-2].n_expr), (yyvsp[-1].tok), (yyvsp[0].n_expr)); }
#line 2420 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 107:
#line 483 "parser.y" /* yacc.c:1646  */
    { (yyval.n_expr) = new op_node(tn_shl, (yyvsp[-2].n_expr), (yyvsp[-1].tok), (yyvsp[0].n_expr)); }
#line 2426 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 108:
#line 484 "parser.y" /* yacc.c:1646  */
    { (yyval.n_expr) = new op_node(tn_shr, (yyvsp[-2].n_expr), (yyvsp[-1].tok), (yyvsp[0].n_expr)); }
#line 2432 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 109:
#line 485 "parser.y" /* yacc.c:1646  */
    { (yyval.n_expr) = new op_node(tn_or, (yyvsp[-2].n_expr), (yyvsp[-1].tok), (yyvsp[0].n_expr)); }
#line 2438 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 110:
#line 486 "parser.y" /* yacc.c:1646  */
    { (yyval.n_expr) = new op_node(tn_binor, (yyvsp[-2].n_expr), (yyvsp[-1].tok), (yyvsp[0].n_expr)); }
#line 2444 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 111:
#line 487 "parser.y" /* yacc.c:1646  */
    { (yyval.n_expr) = new op_node(tn_xor, (yyvsp[-2].n_expr), (yyvsp[-1].tok), (yyvsp[0].n_expr)); }
#line 2450 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 112:
#line 489 "parser.y" /* yacc.c:1646  */
    { (yyval.n_expr) = new op_node(tn_gt, (yyvsp[-2].n_expr), (yyvsp[-1].tok), (yyvsp[0].n_expr)); }
#line 2456 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 113:
#line 490 "parser.y" /* yacc.c:1646  */
    { (yyval.n_expr) = new op_node(tn_lt, (yyvsp[-2].n_expr), (yyvsp[-1].tok), (yyvsp[0].n_expr)); }
#line 2462 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 114:
#line 491 "parser.y" /* yacc.c:1646  */
    { (yyval.n_expr) = new op_node(tn_le, (yyvsp[-2].n_expr), (yyvsp[-1].tok), (yyvsp[0].n_expr)); }
#line 2468 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 115:
#line 492 "parser.y" /* yacc.c:1646  */
    { (yyval.n_expr) = new op_node(tn_ge, (yyvsp[-2].n_expr), (yyvsp[-1].tok), (yyvsp[0].n_expr)); }
#line 2474 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 116:
#line 493 "parser.y" /* yacc.c:1646  */
    { (yyval.n_expr) = new op_node(tn_eq, (yyvsp[-2].n_expr), (yyvsp[-1].tok), (yyvsp[0].n_expr)); }
#line 2480 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 117:
#line 494 "parser.y" /* yacc.c:1646  */
    { (yyval.n_expr) = new op_node(tn_ne, (yyvsp[-2].n_expr), (yyvsp[-1].tok), (yyvsp[0].n_expr)); }
#line 2486 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 118:
#line 495 "parser.y" /* yacc.c:1646  */
    { (yyval.n_expr) = new op_node(tn_in, (yyvsp[-2].n_expr), (yyvsp[-1].tok), (yyvsp[0].n_expr)); }
#line 2492 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 120:
#line 498 "parser.y" /* yacc.c:1646  */
    {
     (yyval.n_expr) = new op_node(tn_plus, NULL, (yyvsp[-1].tok), (yyvsp[0].n_expr)); }
#line 2499 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 121:
#line 501 "parser.y" /* yacc.c:1646  */
    { (yyval.n_expr) = new op_node(tn_minus, NULL, (yyvsp[-1].tok), (yyvsp[0].n_expr)); }
#line 2505 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 122:
#line 503 "parser.y" /* yacc.c:1646  */
    { (yyval.n_expr) = new op_node(tn_not, NULL, (yyvsp[-1].tok), (yyvsp[0].n_expr)); }
#line 2511 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 123:
#line 505 "parser.y" /* yacc.c:1646  */
    { (yyval.n_expr) = new op_node(tn_binnot, NULL, (yyvsp[-1].tok), (yyvsp[0].n_expr)); }
#line 2517 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 124:
#line 506 "parser.y" /* yacc.c:1646  */
    { (yyval.n_expr) = new address_node((yyvsp[-1].tok), (yyvsp[0].n_expr)); }
#line 2523 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 125:
#line 507 "parser.y" /* yacc.c:1646  */
    { (yyval.n_expr) = new address_node((yyvsp[-1].tok), (yyvsp[0].n_expr)); }
#line 2529 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 127:
#line 510 "parser.y" /* yacc.c:1646  */
    { (yyval.n_expr) = new expr_group_node((yyvsp[-2].tok), (yyvsp[-1].n_expr), (yyvsp[0].tok)); }
#line 2535 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 128:
#line 511 "parser.y" /* yacc.c:1646  */
    { (yyval.n_expr) = new fcall_node((yyvsp[-3].n_expr), (yyvsp[-2].tok), (yyvsp[-1].n_expr), (yyvsp[0].tok)); }
#line 2541 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 129:
#line 512 "parser.y" /* yacc.c:1646  */
    { (yyval.n_expr) = new access_expr_node((yyvsp[-2].n_expr), (yyvsp[-1].tok), (yyvsp[0].tok)); }
#line 2547 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 130:
#line 513 "parser.y" /* yacc.c:1646  */
    { (yyval.n_expr) = new deref_expr_node((yyvsp[-1].n_expr), (yyvsp[0].tok)); }
#line 2553 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 131:
#line 514 "parser.y" /* yacc.c:1646  */
    { (yyval.n_expr) = new idx_expr_node((yyvsp[-3].n_expr), (yyvsp[-2].tok), (yyvsp[-1].n_expr), (yyvsp[0].tok)); }
#line 2559 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 132:
#line 515 "parser.y" /* yacc.c:1646  */
    { (yyval.n_expr) = new loophole_node((yyvsp[-5].tok), (yyvsp[-4].tok), (yyvsp[-3].n_tpd), (yyvsp[-2].tok), (yyvsp[-1].n_expr), (yyvsp[0].tok)); }
#line 2565 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 134:
#line 518 "parser.y" /* yacc.c:1646  */
    { (yyval.n_expr) = new integer_node((yyvsp[0].tok)); }
#line 2571 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 135:
#line 519 "parser.y" /* yacc.c:1646  */
    { (yyval.n_expr) = new real_node((yyvsp[0].tok)); }
#line 2577 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 136:
#line 520 "parser.y" /* yacc.c:1646  */
    { (yyval.n_expr) = new string_node((yyvsp[0].tok)); }
#line 2583 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 137:
#line 521 "parser.y" /* yacc.c:1646  */
    { (yyval.n_expr) = new set_node((yyvsp[-2].tok), (yyvsp[-1].n_item), (yyvsp[0].tok)); }
#line 2589 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 138:
#line 522 "parser.y" /* yacc.c:1646  */
    { (yyval.n_expr) = new atom_expr_node((yyvsp[0].tok)); }
#line 2595 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 139:
#line 524 "parser.y" /* yacc.c:1646  */
    { (yyval.n_item) = NULL; }
#line 2601 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 141:
#line 526 "parser.y" /* yacc.c:1646  */
    { (yyvsp[-2].n_item)->next = (yyvsp[0].n_item); (yyval.n_item) = (yyvsp[-2].n_item); }
#line 2607 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 142:
#line 528 "parser.y" /* yacc.c:1646  */
    { (yyval.n_item) = new set_elem_node((yyvsp[0].n_expr)); }
#line 2613 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 143:
#line 529 "parser.y" /* yacc.c:1646  */
    { (yyval.n_item) = new set_range_node((yyvsp[-2].n_expr), (yyvsp[-1].tok), (yyvsp[0].n_expr)); }
#line 2619 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 145:
#line 531 "parser.y" /* yacc.c:1646  */
    { (yyvsp[-2].n_expr)->next = (yyvsp[0].n_expr); (yyval.n_expr) = (yyvsp[-2].n_expr); }
#line 2625 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 147:
#line 534 "parser.y" /* yacc.c:1646  */
    { (yyvsp[-2].n_expr)->next = (yyvsp[0].n_expr); (yyval.n_expr) = (yyvsp[-2].n_expr); }
#line 2631 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 149:
#line 536 "parser.y" /* yacc.c:1646  */
    { (yyval.n_expr) = new skipped_node(curr_token->prev_relevant()); }
#line 2637 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 150:
#line 539 "parser.y" /* yacc.c:1646  */
    { 
    (yyval.n_expr) = new record_constant_node((yyvsp[-2].tok), (yyvsp[-1].n_field), (yyvsp[0].tok)); 
}
#line 2645 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 151:
#line 543 "parser.y" /* yacc.c:1646  */
    { (yyval.n_field) = (yyvsp[0].n_field); }
#line 2651 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 152:
#line 544 "parser.y" /* yacc.c:1646  */
    { (yyvsp[-2].n_field)->next = (yyvsp[0].n_field); (yyval.n_field) = (yyvsp[-2].n_field); }
#line 2657 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 153:
#line 546 "parser.y" /* yacc.c:1646  */
    { (yyval.n_field) = new field_init_node((yyvsp[-2].tok), (yyvsp[-1].tok), (yyvsp[0].n_expr)); }
#line 2663 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 154:
#line 549 "parser.y" /* yacc.c:1646  */
    { (yyval.n_grp) = new expr_group_node((yyvsp[-2].tok), (yyvsp[-1].n_expr), (yyvsp[0].tok)); }
#line 2669 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 156:
#line 552 "parser.y" /* yacc.c:1646  */
    { (yyvsp[-2].n_wrtp)->next = (yyvsp[0].n_wrtp); (yyval.n_wrtp) = (yyvsp[-2].n_wrtp); }
#line 2675 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 157:
#line 554 "parser.y" /* yacc.c:1646  */
    { (yyval.n_wrtp) = new write_param_node((yyvsp[0].n_expr)); }
#line 2681 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 158:
#line 555 "parser.y" /* yacc.c:1646  */
    { (yyval.n_wrtp) = new write_param_node((yyvsp[-2].n_expr), (yyvsp[-1].tok), (yyvsp[0].n_expr)); }
#line 2687 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 159:
#line 556 "parser.y" /* yacc.c:1646  */
    { (yyval.n_wrtp) = new write_param_node((yyvsp[-4].n_expr), (yyvsp[-3].tok), (yyvsp[-2].n_expr), (yyvsp[-1].tok), (yyvsp[0].n_expr)); }
#line 2693 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 160:
#line 599 "parser.y" /* yacc.c:1646  */
    { (yyval.n_decl) = new label_decl_part_node((yyvsp[-2].tok), (yyvsp[-1].toks), (yyvsp[0].tok)); }
#line 2699 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 161:
#line 601 "parser.y" /* yacc.c:1646  */
    { (yyval.toks) = new token_list((yyvsp[0].tok)); }
#line 2705 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 162:
#line 602 "parser.y" /* yacc.c:1646  */
    { (yyval.toks) = new token_list((yyvsp[-2].tok), (yyvsp[0].toks)); }
#line 2711 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 163:
#line 603 "parser.y" /* yacc.c:1646  */
    { (yyval.toks) = new token_list((yyvsp[0].tok)); }
#line 2717 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 164:
#line 604 "parser.y" /* yacc.c:1646  */
    { (yyval.toks) = new token_list((yyvsp[-2].tok), (yyvsp[0].toks)); }
#line 2723 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 165:
#line 607 "parser.y" /* yacc.c:1646  */
    { (yyval.n_decl) = new const_def_part_node((yyvsp[-1].tok), (yyvsp[0].n_cdef)); }
#line 2729 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 166:
#line 609 "parser.y" /* yacc.c:1646  */
    { (yyval.n_cdef) = NULL; }
#line 2735 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 167:
#line 610 "parser.y" /* yacc.c:1646  */
    { (yyvsp[-2].n_cdef)->next = (yyvsp[0].n_cdef); (yyval.n_cdef) = (yyvsp[-2].n_cdef); }
#line 2741 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 168:
#line 612 "parser.y" /* yacc.c:1646  */
    { (yyval.n_cdef) = new const_def_node((yyvsp[-2].tok), (yyvsp[-1].tok), (yyvsp[0].n_expr)); }
#line 2747 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 169:
#line 613 "parser.y" /* yacc.c:1646  */
    { (yyval.n_cdef) = new typed_const_def_node((yyvsp[-4].tok), (yyvsp[-3].tok), (yyvsp[-2].n_tpd), (yyvsp[-1].tok), (yyvsp[0].n_expr)); }
#line 2753 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 170:
#line 616 "parser.y" /* yacc.c:1646  */
    { (yyval.n_decl) = new type_def_part_node((yyvsp[-1].tok), (yyvsp[0].n_tdef)); }
#line 2759 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 171:
#line 618 "parser.y" /* yacc.c:1646  */
    { (yyval.n_tdef) = NULL; }
#line 2765 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 172:
#line 619 "parser.y" /* yacc.c:1646  */
    { (yyvsp[-2].n_tdef)->next = (yyvsp[0].n_tdef); (yyval.n_tdef) = (yyvsp[-2].n_tdef); }
#line 2771 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 173:
#line 621 "parser.y" /* yacc.c:1646  */
    { (yyval.n_tdef) = new type_def_node((yyvsp[-2].tok), (yyvsp[-1].tok), (yyvsp[0].n_tpd)); }
#line 2777 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 174:
#line 624 "parser.y" /* yacc.c:1646  */
    { (yyval.n_decl) = new var_decl_part_node((yyvsp[-1].tok), (yyvsp[0].n_vdcl)); }
#line 2783 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 175:
#line 626 "parser.y" /* yacc.c:1646  */
    { (yyval.n_vdcl) = NULL; }
#line 2789 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 177:
#line 629 "parser.y" /* yacc.c:1646  */
    { 
	 (yyvsp[-2].n_vdcl)->scope = (yyvsp[0].tok);
	 (yyvsp[0].tok)->disable();
       }
#line 2798 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 178:
#line 634 "parser.y" /* yacc.c:1646  */
    { 
	 (yyvsp[-4].n_vdcl)->scope = (yyvsp[-2].tok);
	 token::remove((yyvsp[-2].tok), (yyvsp[-1].tok));	    
	 (yyvsp[-4].n_vdcl)->next = (yyvsp[0].n_vdcl); (yyval.n_vdcl) = (yyvsp[-4].n_vdcl); 
       }
#line 2808 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 179:
#line 639 "parser.y" /* yacc.c:1646  */
    { (yyvsp[-2].n_vdcl)->next = (yyvsp[0].n_vdcl); (yyval.n_vdcl) = (yyvsp[-2].n_vdcl); }
#line 2814 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 180:
#line 641 "parser.y" /* yacc.c:1646  */
    { (yyval.n_vdcl) = new var_decl_node((yyvsp[-2].toks), (yyvsp[-1].tok), (yyvsp[0].n_tpd)); }
#line 2820 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 181:
#line 643 "parser.y" /* yacc.c:1646  */
    { (yyval.n_vdcl) = (var_decl_node*)new var_origin_decl_node((yyvsp[-4].tok), (yyvsp[-3].tok), (yyvsp[-2].n_expr), (yyvsp[-1].tok), (yyvsp[0].n_tpd)); }
#line 2826 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 182:
#line 647 "parser.y" /* yacc.c:1646  */
    { (yyval.n_decl) = new proc_decl_node((yyvsp[-2].tok), (yyvsp[-1].tok), (yyvsp[0].n_plist)); }
#line 2832 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 183:
#line 649 "parser.y" /* yacc.c:1646  */
    { (yyval.n_decl) = new proc_decl_node((yyvsp[-4].tok), (yyvsp[-3].tok), (yyvsp[-2].n_plist), (yyvsp[-1].tok), (yyvsp[0].n_tpd)); }
#line 2838 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 184:
#line 654 "parser.y" /* yacc.c:1646  */
    { (yyval.n_decl) = new proc_fwd_decl_node((yyvsp[-5].tok), (yyvsp[-4].tok), (yyvsp[-3].n_plist), NULL, NULL, (yyvsp[-2].tok), (yyvsp[-1].toks), (yyvsp[0].tok)); }
#line 2844 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 185:
#line 656 "parser.y" /* yacc.c:1646  */
    { (yyval.n_decl) = new proc_fwd_decl_node((yyvsp[-7].tok), (yyvsp[-6].tok), (yyvsp[-5].n_plist), (yyvsp[-4].tok), (yyvsp[-3].n_tpd), (yyvsp[-2].tok), (yyvsp[-1].toks), (yyvsp[0].tok)); }
#line 2850 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 186:
#line 660 "parser.y" /* yacc.c:1646  */
    { (yyval.n_decl) = new proc_fwd_decl_node((yyvsp[-3].tok), (yyvsp[-2].tok), (yyvsp[-1].n_plist), NULL, NULL, (yyvsp[0].tok)); }
#line 2856 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 187:
#line 662 "parser.y" /* yacc.c:1646  */
    { (yyval.n_decl) = new proc_fwd_decl_node((yyvsp[-5].tok), (yyvsp[-4].tok), (yyvsp[-3].n_plist), (yyvsp[-2].tok), (yyvsp[-1].n_tpd), (yyvsp[0].tok)); }
#line 2862 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 188:
#line 666 "parser.y" /* yacc.c:1646  */
    { (yyval.n_decl) = new proc_def_node((yyvsp[-5].tok), NULL, NULL, (yyvsp[-4].tok), (yyvsp[-3].n_plist), NULL, NULL, (yyvsp[-2].tok), NULL, NULL, (yyvsp[-1].n_block), (yyvsp[0].tok)); }
#line 2868 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 189:
#line 668 "parser.y" /* yacc.c:1646  */
    { (yyval.n_decl) = new proc_def_node((yyvsp[-7].tok), NULL, NULL, (yyvsp[-6].tok), (yyvsp[-5].n_plist), (yyvsp[-4].tok), (yyvsp[-3].n_tpd), (yyvsp[-2].tok), NULL, NULL, (yyvsp[-1].n_block), (yyvsp[0].tok)); }
#line 2874 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 190:
#line 670 "parser.y" /* yacc.c:1646  */
    { (yyval.n_decl) = new proc_def_node((yyvsp[-7].tok), (yyvsp[-6].tok), (yyvsp[-5].tok), (yyvsp[-4].tok), (yyvsp[-3].n_plist), NULL, NULL, (yyvsp[-2].tok), NULL, NULL, (yyvsp[-1].n_block), (yyvsp[0].tok)); }
#line 2880 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 191:
#line 672 "parser.y" /* yacc.c:1646  */
    { (yyval.n_decl) = new proc_def_node((yyvsp[-9].tok), (yyvsp[-8].tok), (yyvsp[-7].tok), (yyvsp[-6].tok), (yyvsp[-5].n_plist), (yyvsp[-4].tok), (yyvsp[-3].n_tpd), (yyvsp[-2].tok), NULL, NULL, (yyvsp[-1].n_block), (yyvsp[0].tok)); }
#line 2886 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 192:
#line 674 "parser.y" /* yacc.c:1646  */
    { (yyval.n_decl) = new proc_def_node((yyvsp[-4].tok), NULL, NULL, (yyvsp[-3].tok), NULL, NULL, NULL, (yyvsp[-2].tok), NULL, NULL, (yyvsp[-1].n_block), (yyvsp[0].tok)); }
#line 2892 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 193:
#line 676 "parser.y" /* yacc.c:1646  */
    { (yyval.n_decl) = new proc_def_node((yyvsp[-7].tok), NULL, NULL, (yyvsp[-6].tok), (yyvsp[-5].n_plist), NULL, NULL, (yyvsp[-4].tok), (yyvsp[-3].tok), (yyvsp[-2].tok), (yyvsp[-1].n_block), (yyvsp[0].tok)); }
#line 2898 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 194:
#line 678 "parser.y" /* yacc.c:1646  */
    { (yyval.n_decl) = new proc_def_node((yyvsp[-9].tok), NULL, NULL, (yyvsp[-8].tok), (yyvsp[-7].n_plist), (yyvsp[-6].tok), (yyvsp[-5].n_tpd), (yyvsp[-4].tok), (yyvsp[-3].tok), (yyvsp[-2].tok), (yyvsp[-1].n_block), (yyvsp[0].tok)); }
#line 2904 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 195:
#line 680 "parser.y" /* yacc.c:1646  */
    { (yyval.n_decl) = new proc_def_node((yyvsp[-6].tok), NULL, NULL, (yyvsp[-5].tok), NULL, NULL, NULL, (yyvsp[-4].tok), (yyvsp[-3].tok), (yyvsp[-2].tok), (yyvsp[-1].n_block), (yyvsp[0].tok)); }
#line 2910 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 196:
#line 682 "parser.y" /* yacc.c:1646  */
    { (yyval.toks) = new token_list((yyvsp[-1].tok), (yyvsp[0].toks)); }
#line 2916 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 197:
#line 683 "parser.y" /* yacc.c:1646  */
    { (yyval.toks) = new token_list((yyvsp[-1].tok), (yyvsp[0].toks)); }
#line 2922 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 198:
#line 684 "parser.y" /* yacc.c:1646  */
    { (yyval.toks) = new token_list((yyvsp[0].tok)); }
#line 2928 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 199:
#line 685 "parser.y" /* yacc.c:1646  */
    { (yyval.toks) = new token_list((yyvsp[0].tok)); }
#line 2934 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 200:
#line 688 "parser.y" /* yacc.c:1646  */
    { (yyval.n_plist) = NULL; }
#line 2940 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 201:
#line 689 "parser.y" /* yacc.c:1646  */
    { (yyval.n_plist) = new param_list_node((yyvsp[-2].tok), (yyvsp[-1].n_decl), (yyvsp[0].tok)); }
#line 2946 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 203:
#line 692 "parser.y" /* yacc.c:1646  */
    { (yyvsp[-2].n_decl)->next = (yyvsp[0].n_decl); (yyval.n_decl) = (yyvsp[-2].n_decl); }
#line 2952 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 204:
#line 694 "parser.y" /* yacc.c:1646  */
    { (yyval.n_decl) = new var_decl_part_node((yyvsp[-1].tok), (yyvsp[0].n_vdcl)); }
#line 2958 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 205:
#line 695 "parser.y" /* yacc.c:1646  */
    { (yyval.n_decl) = (yyvsp[0].n_vdcl); }
#line 2964 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 207:
#line 697 "parser.y" /* yacc.c:1646  */
    { (yyval.n_vdcl) = new var_decl_node((yyvsp[-2].toks), (yyvsp[-1].tok), (yyvsp[0].n_tpd)); }
#line 2970 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 208:
#line 698 "parser.y" /* yacc.c:1646  */
    { (yyval.n_vdcl) = new var_decl_node((yyvsp[0].toks), NULL, NULL); }
#line 2976 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 227:
#line 712 "parser.y" /* yacc.c:1646  */
    { (yyval.n_tpd) = new fptr_tpd_node((yyvsp[-3].tok), (yyvsp[-2].n_plist), (yyvsp[-1].tok), (yyvsp[0].n_tpd)); }
#line 2982 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 228:
#line 713 "parser.y" /* yacc.c:1646  */
    { (yyval.n_tpd) = new fptr_tpd_node((yyvsp[-1].tok), (yyvsp[0].n_plist)); }
#line 2988 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 229:
#line 715 "parser.y" /* yacc.c:1646  */
    { (yyval.n_tpd) = new varying_tpd_node((yyvsp[-3].tok), (yyvsp[-2].tok), (yyvsp[-1].n_expr), (yyvsp[0].tok)); }
#line 2994 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 230:
#line 717 "parser.y" /* yacc.c:1646  */
    { (yyval.n_tpd) = new simple_tpd_node((yyvsp[0].tok)); }
#line 3000 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 231:
#line 718 "parser.y" /* yacc.c:1646  */
    { (yyval.n_tpd) = new string_tpd_node((yyvsp[0].tok)); }
#line 3006 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 232:
#line 721 "parser.y" /* yacc.c:1646  */
    { (yyval.n_tpd) = new array_tpd_node((yyvsp[-6].tok), (yyvsp[-5].tok), (yyvsp[-4].tok), (yyvsp[-3].n_idx), (yyvsp[-2].tok), (yyvsp[-1].tok), (yyvsp[0].n_tpd)); }
#line 3012 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 233:
#line 724 "parser.y" /* yacc.c:1646  */
    { (yyval.n_tpd) = new array_tpd_node((yyvsp[-6].tok), (yyvsp[-5].tok), (yyvsp[-4].tok), (yyvsp[-3].n_idx), (yyvsp[-2].tok), (yyvsp[-1].tok), (yyvsp[0].n_tpd)); }
#line 3018 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 234:
#line 727 "parser.y" /* yacc.c:1646  */
    { (yyval.n_tpd) = new array_tpd_node((yyvsp[-6].tok), (yyvsp[-5].tok), (yyvsp[-4].tok), (yyvsp[-3].n_idx), (yyvsp[-2].tok), (yyvsp[-1].tok), (yyvsp[0].n_tpd)); }
#line 3024 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 235:
#line 729 "parser.y" /* yacc.c:1646  */
    { (yyval.n_tpd) = new array_tpd_node((yyvsp[-6].tok), (yyvsp[-5].tok), (yyvsp[-4].tok), (yyvsp[-3].n_idx), (yyvsp[-2].tok), (yyvsp[-1].tok), (yyvsp[0].n_tpd)); }
#line 3030 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 236:
#line 731 "parser.y" /* yacc.c:1646  */
    { (yyval.n_tpd) = new enum_tpd_node((yyvsp[-2].tok), (yyvsp[-1].toks), (yyvsp[0].tok)); }
#line 3036 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 237:
#line 734 "parser.y" /* yacc.c:1646  */
    { (yyval.n_tpd) = new range_tpd_node((yyvsp[-2].n_expr), (yyvsp[-1].tok), (yyvsp[0].n_expr)); }
#line 3042 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 238:
#line 736 "parser.y" /* yacc.c:1646  */
    { (yyval.n_tpd) = new ptr_tpd_node((yyvsp[-1].tok), (yyvsp[0].n_tpd)); }
#line 3048 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 239:
#line 738 "parser.y" /* yacc.c:1646  */
    { (yyval.n_tpd) = new set_tpd_node((yyvsp[-3].tok), (yyvsp[-2].tok), (yyvsp[-1].tok), (yyvsp[0].n_tpd)); }
#line 3054 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 240:
#line 740 "parser.y" /* yacc.c:1646  */
    { (yyval.n_tpd) = new set_tpd_node((yyvsp[-3].tok), (yyvsp[-2].tok), (yyvsp[-1].tok), (yyvsp[0].n_tpd)); }
#line 3060 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 241:
#line 743 "parser.y" /* yacc.c:1646  */
    { (yyval.n_tpd) = new record_tpd_node((yyvsp[-3].tok), (yyvsp[-2].tok), (yyvsp[-1].n_fldls), (yyvsp[0].tok)); }
#line 3066 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 242:
#line 746 "parser.y" /* yacc.c:1646  */
    { (yyval.n_tpd) = new object_tpd_node((yyvsp[-2].tok), NULL, NULL, NULL, (yyvsp[-1].n_decl), (yyvsp[0].tok)); }
#line 3072 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 243:
#line 748 "parser.y" /* yacc.c:1646  */
    { (yyval.n_tpd) = new object_tpd_node((yyvsp[-5].tok), (yyvsp[-4].tok), (yyvsp[-3].tok), (yyvsp[-2].tok), (yyvsp[-1].n_decl), (yyvsp[0].tok)); }
#line 3078 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 244:
#line 751 "parser.y" /* yacc.c:1646  */
    { (yyvsp[-1].n_decl)->next = (yyvsp[0].n_decl); (yyval.n_decl) = (yyvsp[-1].n_decl); }
#line 3084 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 247:
#line 756 "parser.y" /* yacc.c:1646  */
    { (yyval.n_decl) = new var_decl_part_node(NULL, (yyvsp[0].n_vdcl)); }
#line 3090 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 249:
#line 759 "parser.y" /* yacc.c:1646  */
    { (yyval.n_vdcl) = (yyvsp[-1].n_vdcl); }
#line 3096 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 250:
#line 760 "parser.y" /* yacc.c:1646  */
    { (yyvsp[-2].n_vdcl)->next = (yyvsp[0].n_vdcl); (yyval.n_vdcl) = (yyvsp[-2].n_vdcl); }
#line 3102 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 253:
#line 763 "parser.y" /* yacc.c:1646  */
    { (yyvsp[-1].n_decl)->next = (yyvsp[0].n_decl); (yyval.n_decl) = (yyvsp[-1].n_decl); }
#line 3108 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 254:
#line 764 "parser.y" /* yacc.c:1646  */
    { (yyvsp[-1].n_decl)->next = (yyvsp[0].n_decl); (yyval.n_decl) = (yyvsp[-1].n_decl); }
#line 3114 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 255:
#line 768 "parser.y" /* yacc.c:1646  */
    { (yyval.n_tpd) = new file_tpd_node((yyvsp[-3].tok), (yyvsp[-2].tok), (yyvsp[-1].tok), (yyvsp[0].n_tpd)); }
#line 3120 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 256:
#line 770 "parser.y" /* yacc.c:1646  */
    { (yyval.tok) = NULL; }
#line 3126 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 259:
#line 773 "parser.y" /* yacc.c:1646  */
    { (yyvsp[-2].n_idx)->next = (yyvsp[0].n_idx); (yyval.n_idx) = (yyvsp[-2].n_idx); }
#line 3132 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 260:
#line 776 "parser.y" /* yacc.c:1646  */
    { (yyval.n_idx) = new conformant_index_node((yyvsp[-4].tok), (yyvsp[-3].tok), (yyvsp[-2].tok), (yyvsp[-1].tok), (yyvsp[0].n_tpd)); }
#line 3138 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 262:
#line 779 "parser.y" /* yacc.c:1646  */
    { (yyvsp[-2].n_idx)->next = (yyvsp[0].n_idx); (yyval.n_idx) = (yyvsp[-2].n_idx); }
#line 3144 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 263:
#line 781 "parser.y" /* yacc.c:1646  */
    { (yyval.n_idx) = new type_index_node((yyvsp[0].n_tpd)); }
#line 3150 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 264:
#line 782 "parser.y" /* yacc.c:1646  */
    { (yyval.n_idx) = new range_index_node((yyvsp[-2].n_expr), (yyvsp[-1].tok), (yyvsp[0].n_expr)); }
#line 3156 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 265:
#line 787 "parser.y" /* yacc.c:1646  */
    { (yyval.n_fldls) = new field_list_node((yyvsp[-1].n_vdcl), (yyvsp[0].n_varp)); }
#line 3162 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 266:
#line 789 "parser.y" /* yacc.c:1646  */
    { (yyval.n_fldls) = new field_list_node((yyvsp[0].n_vdcl)); }
#line 3168 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 268:
#line 794 "parser.y" /* yacc.c:1646  */
    { 
    (yyval.n_varp) = new variant_part_node((yyvsp[-3].tok), (yyvsp[-2].n_sel), (yyvsp[-1].tok), (yyvsp[0].n_vari)); 
}
#line 3176 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 269:
#line 798 "parser.y" /* yacc.c:1646  */
    { (yyval.n_sel) = new selector_node((yyvsp[-2].tok), (yyvsp[-1].tok), (yyvsp[0].n_tpd)); }
#line 3182 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 270:
#line 799 "parser.y" /* yacc.c:1646  */
    { (yyval.n_sel) = new selector_node(NULL, NULL, (yyvsp[0].n_tpd)); }
#line 3188 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 272:
#line 803 "parser.y" /* yacc.c:1646  */
    { (yyval.n_vari) = (yyvsp[-1].n_vari); }
#line 3194 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 273:
#line 804 "parser.y" /* yacc.c:1646  */
    { (yyvsp[-2].n_vari)->next = (yyvsp[0].n_vari); (yyval.n_vari) = (yyvsp[-2].n_vari); }
#line 3200 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 274:
#line 807 "parser.y" /* yacc.c:1646  */
    { 
    (yyval.n_vari) = new variant_node((yyvsp[-4].n_expr), (yyvsp[-3].tok), (yyvsp[-2].tok), (yyvsp[-1].n_fldls), (yyvsp[0].tok)); 
}
#line 3208 "parser.tab.c" /* yacc.c:1646  */
    break;


#line 3212 "parser.tab.c" /* yacc.c:1646  */
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

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

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
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

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
                  yystos[*yyssp], yyvsp);
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
#line 811 "parser.y" /* yacc.c:1906  */


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


