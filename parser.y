%{

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

%}


%union {
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
}




%token <tok> ARRAY
             BEGIN
             CASE
             CONST
             DO
             DOTS
             ELSE
             END             
             FIL
             FAR
             FOR
             FUNCTION
             GOTO
             IDENT
             ICONST
             IF
             IMPLEMENTATION
             INTERFACE
             LABEL
             LOOPHOLE
             OBJECT
             OF
             ORIGIN
             OTHERWISE
             PACKED
             PROCEDURE
             PROGRAM
             RCONST
             READ
             RECORD
             REPEAT
             RETURN
             SET
             SCONST
             STRING
             THEN
             TO
             TYPE
             UNTIL
             UNIT
             UNIT_END
             VAR
             WHILE
             WITH
             WRITE
             '.'
             ','
             ':'
             ';'
             '('
             ')'
             '['
             ']'
             '^'
             '@'
             SCOPE

%right <tok> LET LETADD LETSUB LETDIV LETMUL LETAND LETOR LETSHL LETSHR
%left <tok>  EQ NE LT LE GT GE IN 
%left <tok>  PLUS MINUS OR XOR BINOR
%left <tok>  MOD DIV DIVR MUL AND SHR SHL BINAND
%right <tok> UPLUS UMINUS NOT ADDRESS BINNOT


%type <toks>    ident_list
%type <toks>    label_list
%type <toks>    qualifiers
%type <tok>     packed
%type <tok>     progend
%type <tok>     otherwise

%type <n_imp>   prog_param_list

%type <n_node>  unit

%type <n_node>  program
%type <n_node>  module
%type <n_node>  translation
%type <n_node>  input_file

%type <n_block> block
%type <n_stmt>  statement
%type <n_stmt>  sequence
%type <n_grp>   actual_params

%type <n_comp>  compoundst

%type <n_wrls>  write_params
%type <n_wrtp>  write_list
%type <n_wrtp>  write_param

%type <n_expr>  expr
%type <n_expr>  simple_expr
%type <n_expr>  primary
%type <n_expr>  constant
%type <n_expr>  record_constant
%type <n_expr>  expr_list
%type <n_expr>  act_param_list
%type <n_expr>  act_param
%type <n_expr>  case_elem
%type <n_expr>  case_elem_list
%type <n_grp>   expr_group

%type <n_field> field_init_list
%type <n_field> field_init_item

%type <n_case>  case_list
%type <n_case>  case_item
%type <n_case>  case_items

%type <n_item>  set_elem_list
%type <n_item>  set_elem

%type <n_decl>  decl_part
%type <n_decl>  unit_decl
%type <n_decl>  unit_spec
%type <n_decl>  unit_decl_list
%type <n_decl>  unit_def_list
%type <n_decl>  decl_part_list
%type <n_decl>  label_decl_part
%type <n_decl>  const_def_part
%type <n_decl>  object_components
%type <n_decl>  object_fields 
%type <n_decl>  object_methods
%type <n_cdef>  const_def_list
%type <n_cdef>  const_def
%type <n_decl>  type_def_part
%type <n_tdef>  type_def_list
%type <n_tdef>  type_def
%type <n_decl>  var_decl_part
%type <n_vdcl>  var_decl_list
%type <n_vdcl>  field_decl_list
%type <n_vdcl>  var_decl
%type <n_vdcl>  param_decl
%type <n_decl>  proc_decl
%type <n_decl>  proc_fwd_decl
%type <n_decl>  proc_spec
%type <n_decl>  proc_def

%type <n_plist> formal_params
%type <n_decl>  formal_param_list
%type <n_decl>  formal_param

%type <n_tpd>   type
%type <n_tpd>   param_type
%type <n_tpd>   simple_type
%type <n_tpd>   fptr_type
%type <n_tpd>   const_type
%type <n_tpd>   const_array_type
%type <n_tpd>   const_set_type
%type <n_tpd>   array_type
%type <n_tpd>   string_type
%type <n_tpd>   conformant_array_type
%type <n_tpd>   enum_type
%type <n_tpd>   range_type
%type <n_tpd>   pointer_type
%type <n_tpd>   set_type
%type <n_tpd>   record_type
%type <n_tpd>   object_type
%type <n_tpd>   file_type

%type <n_idx>   indices
%type <n_idx>   conformant_indices
%type <n_idx>   conformant_index
%type <n_idx>   index_spec

%type <n_fldls> field_list
%type <n_vdcl> fixed_part
%type <n_varp>  variant_part
%type <n_sel>   selector
%type <n_vari>  variant_list
%type <n_vari>  variant

%start translation

%%

/*
 Grammar section
*/

/*
//=============================================================================
// Program level grammar:
//   program         ::= PROGRAM ident [ '(' parameter_list ')' ] block '.'
//   parameter_list  ::= ident { ',' ident } 
//   block           ::= decl_part_list compoundst
//   decl_part_list  ::= { decl_part } 
//   decl_part       ::= label_decl_part | const_def_part | type_def_part
//                       | var_decl_part | proc_decl | proc_fwd_decl 
//=============================================================================
*/


translation: 
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
input_file { 
    $2->attrib(ctx_program); 
    $2->translate(ctx_program); 
} 

input_file: program | module | unit

program: block '.' { $$ = new program_node(NULL, NULL, NULL, NULL, $1, $2); }
| PROGRAM IDENT prog_param_list ';' block '.'
{ 
    $$ = new program_node($1, $2, $3, $4, $5, $6);
}

progend: { $$ = NULL; } | '.'

module: decl_part_list { $$ = new module_node(NULL, NULL, NULL, NULL, $1, NULL); }
| PROGRAM IDENT prog_param_list ';' decl_part_list progend
{ 
    $$ = new module_node($1, $2, $3, $4, $5, $6);
}


/* Turbo Pascal specific */

unit: UNIT IDENT ';' INTERFACE unit_decl_list IMPLEMENTATION unit_def_list END '.'
    { $$ = new unit_node($1, $2, $3, $4, $5, $6, $7, NULL, $8, $9); }
| UNIT IDENT ';' INTERFACE unit_decl_list IMPLEMENTATION unit_def_list compoundst '.'
    { $$ = new unit_node($1, $2, $3, $4, $5, $6, $7, $8, NULL, $9); }
| INTERFACE unit_decl_list IMPLEMENTATION unit_def_list END '.'
    { $$ = new unit_node(NULL, NULL, NULL, $1, $2, $3, $4, NULL, $5, $6); }
| INTERFACE unit_decl_list IMPLEMENTATION unit_def_list compoundst '.'
    { $$ = new unit_node(NULL, NULL, NULL, $1, $2, $3, $4, $5, NULL, $6); }

unit_def_list: decl_part_list 


prog_param_list: { $$ = NULL; } 
    | '(' ident_list ')' { $$ = new import_list_node($1, $2, $3); }

ident_list: IDENT ',' ident_list { $$ = new token_list($1, $3); }
    | IDENT { $$ = new token_list($1); }

block: decl_part_list compoundst 
{
    $$ = new block_node($1, $2);
}

decl_part_list: { $$ = NULL; } 
    | decl_part decl_part_list { $1->next = $2; $$ = $1; }

decl_part: label_decl_part | const_def_part | type_def_part | var_decl_part 
         | proc_def | proc_fwd_decl | unit_spec

unit_spec: UNIT IDENT ';' INTERFACE unit_decl_list UNIT_END  
    {  $$ = new unit_spec_node($1, $2, $3, $4, $5); }
| INTERFACE unit_decl_list UNIT_END
    {  $$ = new unit_spec_node(NULL, NULL, NULL, $1, $2); }
  

unit_decl_list: { $$ = NULL; }
    | unit_decl unit_decl_list { $1->next = $2; $$ = $1; }

unit_decl: label_decl_part | const_def_part | type_def_part | var_decl_part
    | proc_spec | proc_fwd_decl | unit_spec

/*
//=============================================================================
// Statement level grammar
//   statement       ::= compoundst | assignmentst | gotost | switchst | ifst 
//                    | forst | whilest | repeatst | procst | returnst 
//                    | withst | labelst | emtyst | writest | readst
//   sequence        ::= statement { ';' statement }
//   compoundst      ::= BEGIN sequence END
//   assignmentst    ::= expr ':=' expr
//   gotost          ::= GOTO iconst
//   labelst         ::= iconst ':' 
//   switchst        ::= CASE expr OF case_list END
//   case_list       ::= case_list_elem { ';' case-list-elem } [ ';' ] 
//   case_list_elem  ::= expr_list ':' statement | OTHERWISE statement
//   ifst            ::= IF expr THEN statement [ELSE statement]
//   forst           ::= FOR identifier := expr (TO | DOWNTO) expr DO statement
//   repeatst        ::= REPEAT sequence UNTIL expr
//   whilest         ::= WHILE expr DO statement
//   withst          ::= WITH expr_list DO statement
//   procst          ::= ident [ expr_group ]
//   writest         ::= (WRITE | WRITELN) [ write_params ] 
//   readst          ::= (READ | READLN) [ expr_group ] 
//   returnst        ::= RETURN
//   emptyst         ::= 
//=============================================================================
*/

statement: { $$ = new empty_node(curr_token->prev_relevant()); }
    | primary LET expr { $$ = new assign_node($1, $2, $3); }
    | primary LETADD expr { $$ = new assign_node($1, $2, $3); }
    | primary LETSUB expr { $$ = new assign_node($1, $2, $3); }
    | primary LETDIV expr { $$ = new assign_node($1, $2, $3); }
    | primary LETMUL expr { $$ = new assign_node($1, $2, $3); }
    | primary LETAND expr { $$ = new assign_node($1, $2, $3); }
    | primary LETOR  expr { $$ = new assign_node($1, $2, $3); }
    | primary LETSHL expr { $$ = new assign_node($1, $2, $3); }
    | primary LETSHR expr { $$ = new assign_node($1, $2, $3); }
    | GOTO ICONST { $$ = new goto_node($1, $2); }
    | GOTO IDENT { $$ = new goto_node($1, $2); }
    | CASE expr OF case_list END { $$ = new switch_node($1, $2, $3, $4, $5); }
    | IF expr THEN statement { $$ = new if_node($1, $2, $3, $4); } 
    | IF expr THEN statement ELSE statement 
        { $$ = new if_node($1, $2, $3, $4, $5, $6); }
    | FOR IDENT LET expr TO expr DO statement 
        { $$ = new for_node($1, $2, $3, $4, $5, $6, $7, $8); }
    | WHILE expr DO statement { $$ = new while_node($1, $2, $3, $4); }
    | REPEAT sequence UNTIL expr { $$ = new repeat_node($1, $2, $3, $4); }
    | WRITE write_params { $$ = new write_node($1, $2); }
    | READ actual_params { $$ = new read_node($1, $2); }
    | primary { $$ = new pcall_node($1); } 
    | RETURN { $$ = new return_node($1); }
    | WITH expr_list DO statement { $$ = new with_node($1, $2, $3, $4); }
    | ICONST ':' statement { $$ = new label_node($1, $2, $3); }
    | IDENT ':' statement { $$ = new label_node($1, $2, $3); }
    | compoundst { $$ = $1; }
  
compoundst: BEGIN sequence END { $$ = new compound_node($1, $2, $3); }

sequence: statement | statement ';' sequence { $1->next = $3; $$ = $1; }

actual_params: { $$ = NULL; } | expr_group { $$ = $1; }

write_params:  { $$ = NULL; } 
    | '(' write_list ')' { $$ = new write_list_node($1, $2, $3); } 

case_list: case_items
         | case_items otherwise sequence
           { 
	     if ($1 != NULL) { 
	         case_node** cpp;
	         for(cpp = &$1->next; *cpp != NULL; cpp = &(*cpp)->next);
	         *cpp = new case_node(NULL, $2, $3);
		 $$ = $1;
             } else { 		 
	         $$ = new case_node(NULL, $2, $3);
             }
	   }

otherwise: OTHERWISE | ELSE /* Turbo Pascal */

case_items: { $$ = NULL; } 
         | case_item 
         | case_item ';' case_items { $1->next = $3; $$ = $1; }

case_item: case_elem_list ':' statement { $$ = new case_node($1, $2, $3); }

case_elem_list: case_elem 
        | case_elem ',' case_elem_list { $1->next = $3; $$ = $1; }

case_elem: expr { $$ = $1; }
        | expr DOTS expr { $$ = new case_range_node($1, $2, $3); }

/*
//=============================================================================
// Expression level syntax:
//   constant      ::= integer | real | string | set_construct | ident
//   set_elem      ::= expr | expr '..' expr
//   set_construct ::= '[' set_elem { ',' set_elem } ']'
//   expr_group    ::= '(' expr_list ')'
//   expr_list     ::= expr { ',' expr }
//   primary       ::= '(' expr ')' | call_expr  
//                   | deref_expr | idx_expr | access_expr | constant
//   access_expr   ::= expr '.' ident  
//   deref_expr    ::= expr '^'
//   idx_expr      ::= expr '[' expr_list ']'
//   call_expr     ::= expr expr_group
//   binary        ::= expr op expr      
//   unary         ::= op expr 
//   expr          ::= primary | unary | binary 
//   write_list    ::= '(' write_param { ',' write_param } ')'
//   write_param   ::= expr [ ':' constant [ ':' constant ] ] 
//=============================================================================
*/

expr: simple_expr
   | expr PLUS expr { $$ = new op_node(tn_add, $1, $2, $3); } 
   | expr MINUS expr { $$ = new op_node(tn_sub, $1, $2, $3); } 
   | expr MOD expr { $$ = new op_node(tn_mod, $1, $2, $3); } 
   | expr MUL expr { $$ = new op_node(tn_mul, $1, $2, $3); } 
   | expr DIV expr { $$ = new op_node(tn_div, $1, $2, $3); } 
   | expr DIVR expr { $$ = new op_node(tn_divr, $1, $2, $3); } 

   | primary LET expr { $$ = new op_node(tn_let, $1, $2, $3); }
   | primary LETADD expr { $$ = new op_node(tn_letadd, $1, $2, $3); }
   | primary LETSUB expr { $$ = new op_node(tn_letsub, $1, $2, $3); }
   | primary LETDIV expr { $$ = new op_node(tn_letdiv, $1, $2, $3); }
   | primary LETMUL expr { $$ = new op_node(tn_letmul, $1, $2, $3); }
   | primary LETSHL expr { $$ = new op_node(tn_letshl, $1, $2, $3); }
   | primary LETSHR expr { $$ = new op_node(tn_letshr, $1, $2, $3); }
   | primary LETAND expr { $$ = new op_node(tn_letand, $1, $2, $3); }
   | primary LETOR  expr { $$ = new op_node(tn_letor,  $1, $2, $3); }


   | expr AND expr { $$ = new op_node(tn_and, $1, $2, $3); } 
   | expr BINAND expr { $$ = new op_node(tn_binand, $1, $2, $3); } 
   | expr SHL expr { $$ = new op_node(tn_shl, $1, $2, $3); } 
   | expr SHR expr { $$ = new op_node(tn_shr, $1, $2, $3); } 
   | expr OR expr  { $$ = new op_node(tn_or, $1, $2, $3); } 
   | expr BINOR expr  { $$ = new op_node(tn_binor, $1, $2, $3); } 
   | expr XOR expr { $$ = new op_node(tn_xor, $1, $2, $3); } 

   | expr GT expr { $$ = new op_node(tn_gt, $1, $2, $3); } 
   | expr LT expr { $$ = new op_node(tn_lt, $1, $2, $3); } 
   | expr LE expr { $$ = new op_node(tn_le, $1, $2, $3); } 
   | expr GE expr { $$ = new op_node(tn_ge, $1, $2, $3); } 
   | expr EQ expr { $$ = new op_node(tn_eq, $1, $2, $3); } 
   | expr NE expr { $$ = new op_node(tn_ne, $1, $2, $3); } 
   | expr IN expr { $$ = new op_node(tn_in, $1, $2, $3); } 

simple_expr: primary
   | PLUS simple_expr %prec UPLUS {
     $$ = new op_node(tn_plus, NULL, $1, $2); }
   | MINUS simple_expr %prec UMINUS 
     { $$ = new op_node(tn_minus, NULL, $1, $2); }
   | NOT simple_expr 
     { $$ = new op_node(tn_not, NULL, $1, $2); }
   | BINNOT simple_expr 
     { $$ = new op_node(tn_binnot, NULL, $1, $2); }
   | '@' primary { $$ = new address_node($1, $2); }
   | AND primary %prec ADDRESS { $$ = new address_node($1, $2); }
 
primary: constant 
   | '(' expr_list ')' { $$ = new expr_group_node($1, $2, $3); }
   | primary '(' act_param_list ')' { $$ = new fcall_node($1, $2, $3, $4); }
   | primary '.' IDENT { $$ = new access_expr_node($1, $2, $3); }
   | primary '^' { $$ = new deref_expr_node($1, $2); }
   | primary '[' expr_list ']' { $$ = new idx_expr_node($1, $2, $3, $4); }
   | LOOPHOLE '(' type ',' expr ')' { $$ = new loophole_node($1, $2, $3, $4, $5, $6); }

constant: record_constant
        | ICONST { $$ = new integer_node($1); }
        | RCONST { $$ = new real_node($1); } 
        | SCONST { $$ = new string_node($1); }
        | '[' set_elem_list ']' { $$ = new set_node($1, $2, $3); }
        | IDENT { $$ = new atom_expr_node($1); }

set_elem_list: { $$ = NULL; } 
             | set_elem 
             | set_elem ',' set_elem_list { $1->next = $3; $$ = $1; }

set_elem: expr { $$ = new set_elem_node($1); }
        | expr DOTS expr { $$ = new set_range_node($1, $2, $3); }

expr_list: expr | expr ',' expr_list { $1->next = $3; $$ = $1; }

act_param_list: act_param 
    | act_param ',' act_param_list { $1->next = $3; $$ = $1; }

act_param: expr | { $$ = new skipped_node(curr_token->prev_relevant()); }


record_constant: '(' field_init_list ')' { 
    $$ = new record_constant_node($1, $2, $3); 
}

field_init_list: field_init_item { $$ = $1; }
    | field_init_item ';' field_init_list { $1->next = $3; $$ = $1; }
   
field_init_item: IDENT ':' expr { $$ = new field_init_node($1, $2, $3); }


expr_group: '(' expr_list ')' { $$ = new expr_group_node($1, $2, $3); }


write_list: write_param | write_param ',' write_list { $1->next = $3; $$ = $1; }

write_param: expr  { $$ = new write_param_node($1); }
    | expr ':' expr { $$ = new write_param_node($1, $2, $3); }
    | expr ':' expr ':' expr { $$ = new write_param_node($1, $2, $3, $4, $5); }


/*
//=============================================================================
// Declaration syntax:
//   label_decl_part  ::= [ LABEL ident { ',' ident } ';' ]
//   const_def_part   ::= [ CONST const_def ';' { const_def ';' } ]
//   type_def_part    ::= [ TYPE type_def ';' { type_def ';' } ] 
//   var_decl_part    ::= [ VAR var_decls ';' ] 
//   proc_fwd_decl    ::= proc_decl ';' ident ';' 
//   proc_decl        ::= (PROCEDURE | FUNCTION) ident [ formal_params ] [ ':' type ]
//   proc_def         ::= proc_decl ';' body ';'
//   formal_params    ::= '(' formal_param { ';' formal_param } ')'
//   formal_param     ::= VAR var_decl | var_decl | proc_decl 
//   const_def        ::= ident '=' expr
//   type_def         ::= ident '=' type
//   var_decls        ::= var_decl { ';' var_decl } 
//   var_decl         ::= ident { ',' ident } ':' type 
//   type             ::= simple_type | array_type | record_type | set_type | 
//                        file_type | pointer_type | subrange_type | enum_type
//   subrange_type    ::= '[' expr '..' expr ']'
//   enum_type        ::= '(' expr { ',' expr } ')'
//   pointer_type     ::= '^' type
//   file_type        ::= FILE OF type_denoter
//   set_type         ::= SET OF type_denoter
//   record_type      ::= RECORD field_list END 
//   field_list       ::= [ (fixed_part [';' variant_part] | variant_part) [;] ] 
//   fixed_part       ::= var_decls
//   variant_part     ::= CASE selector OF 
//                        variant { ';' variant }
//   selector         ::= [ tag_field ':' ] tag_type
//   variant          ::= constant { ',' constant } ':' '(' field_list ')'
//   simple_type      ::= ident
//   array_type       ::= ARRAY '[' index ']' OF type
//   index            ::= conformant_index | fixed_index
//   conformant_index ::= var_decls 
//   fixed_index      ::= range { ',' range }
//   range            ::= expr '..' expr | type
//=============================================================================
*/

label_decl_part: LABEL label_list ';' 
    { $$ = new label_decl_part_node($1, $2, $3); }

label_list: ICONST { $$ = new token_list($1); } 
          | ICONST ',' label_list { $$ = new token_list($1, $3); }
          | IDENT { $$ = new token_list($1); } 
          | IDENT ',' label_list { $$ = new token_list($1, $3); }

const_def_part: CONST const_def_list  
    { $$ = new const_def_part_node($1, $2); } 

const_def_list: { $$ = NULL; } 
    | const_def ';' const_def_list { $1->next = $3; $$ = $1; }

const_def: IDENT EQ expr { $$ = new const_def_node($1, $2, $3); }
| IDENT ':' const_type EQ expr { $$ = new typed_const_def_node($1, $2, $3, $4, $5); }

type_def_part: TYPE type_def_list  
    { $$ = new type_def_part_node($1, $2); }

type_def_list: { $$ = NULL; }
    | type_def ';' type_def_list { $1->next = $3; $$ = $1; }

type_def: IDENT EQ type { $$ = new type_def_node($1, $2, $3); }

var_decl_part: VAR var_decl_list 
     { $$ = new var_decl_part_node($1, $2); }

var_decl_list: { $$ = NULL; }
     | var_decl
     | var_decl ';' SCOPE 
       { 
	 $1->scope = $3;
	 $3->disable();
       }
     | var_decl ';' SCOPE ';' var_decl_list 
       { 
	 $1->scope = $3;
	 token::remove($3, $4);	    
	 $1->next = $5; $$ = $1; 
       }
     | var_decl ';' var_decl_list { $1->next = $3; $$ = $1; }

var_decl: ident_list ':' type { $$ = new var_decl_node($1, $2, $3); }
     | IDENT ORIGIN expr ':' simple_type 
       { $$ = (var_decl_node*)new var_origin_decl_node($1, $2, $3, $4, $5); }

proc_decl: 
      PROCEDURE IDENT formal_params  
               { $$ = new proc_decl_node($1, $2, $3); } 
    | FUNCTION IDENT formal_params ':' type 
               { $$ = new proc_decl_node($1, $2, $3, $4, $5); } 
    

proc_fwd_decl: 
      PROCEDURE IDENT formal_params ';' qualifiers ';' 
        { $$ = new proc_fwd_decl_node($1, $2, $3, NULL, NULL, $4, $5, $6); } 
    | FUNCTION IDENT formal_params ':' type ';' qualifiers ';' 
        { $$ = new proc_fwd_decl_node($1, $2, $3, $4, $5, $6, $7, $8); } 

proc_spec: 
      PROCEDURE IDENT formal_params ';'
        { $$ = new proc_fwd_decl_node($1, $2, $3, NULL, NULL, $4); } 
    | FUNCTION IDENT formal_params ':' type ';'
        { $$ = new proc_fwd_decl_node($1, $2, $3, $4, $5, $6); } 

proc_def: 
      PROCEDURE IDENT formal_params ';' block ';' 
               { $$ = new proc_def_node($1, NULL, NULL, $2, $3, NULL, NULL, $4, NULL, NULL, $5, $6); } 
    | FUNCTION IDENT formal_params ':' type ';' block ';' 
               { $$ = new proc_def_node($1, NULL, NULL, $2, $3, $4, $5, $6, NULL, NULL, $7, $8); } 
    | PROCEDURE IDENT '.' IDENT formal_params ';' block ';' 
               { $$ = new proc_def_node($1, $2, $3, $4, $5, NULL, NULL, $6, NULL, NULL, $7, $8); } 
    | FUNCTION IDENT '.' IDENT formal_params ':' type ';' block ';' 
               { $$ = new proc_def_node($1, $2, $3, $4, $5, $6, $7, $8, NULL, NULL, $9, $10); } 
    | FUNCTION IDENT ';' block ';' 
               { $$ = new proc_def_node($1, NULL, NULL, $2, NULL, NULL, NULL, $3, NULL, NULL, $4, $5); } 
    | PROCEDURE IDENT formal_params ';' FAR ';' block ';' 
               { $$ = new proc_def_node($1, NULL, NULL, $2, $3, NULL, NULL, $4, $5, $6, $7, $8); } 
    | FUNCTION IDENT formal_params ':' type ';' FAR ';' block ';' 
               { $$ = new proc_def_node($1, NULL, NULL, $2, $3, $4, $5, $6, $7, $8, $9, $10); } 
    | FUNCTION IDENT ';' FAR ';' block ';' 
               { $$ = new proc_def_node($1, NULL, NULL, $2, NULL, NULL, NULL, $3, $4, $5, $6, $7); } 

qualifiers: IDENT qualifiers { $$ = new token_list($1, $2); }
    | SCOPE qualifiers { $$ = new token_list($1, $2); }
    | IDENT { $$ = new token_list($1); }
    | SCOPE { $$ = new token_list($1); }


formal_params: { $$ = NULL; } 
    | '(' formal_param_list ')' { $$ = new param_list_node($1, $2, $3); }

formal_param_list: formal_param 
    | formal_param ';' formal_param_list { $1->next = $3; $$ = $1; }

formal_param: VAR param_decl { $$ = new var_decl_part_node($1, $2); }
    | param_decl { $$ = $1; } | proc_decl

param_decl: ident_list ':' param_type { $$ = new var_decl_node($1, $2, $3); }
    | ident_list { $$ = new var_decl_node($1, NULL, NULL); }

param_type: simple_type | conformant_array_type



/* Types definition */ 

type: simple_type | array_type | record_type | object_type | set_type | file_type 
    | pointer_type | enum_type | range_type | string_type | fptr_type

const_type: simple_type | const_array_type | record_type | const_set_type | string_type

fptr_type: FUNCTION formal_params ':' type
    { $$ = new fptr_tpd_node($1, $2, $3, $4); }
    | PROCEDURE formal_params { $$ = new fptr_tpd_node($1, $2); }

string_type: STRING '[' expr ']' { $$ = new varying_tpd_node($1, $2, $3, $4); }

simple_type: IDENT { $$ = new simple_tpd_node($1); } 
    | STRING { $$ = new string_tpd_node($1); }

array_type: packed ARRAY '[' indices ']' OF type 
    { $$ = new array_tpd_node($1, $2, $3, $4, $5, $6, $7); }

const_array_type: packed ARRAY '[' indices ']' OF const_type 
    { $$ = new array_tpd_node($1, $2, $3, $4, $5, $6, $7); }

conformant_array_type: packed ARRAY '[' conformant_indices ']' OF simple_type 
         { $$ = new array_tpd_node($1, $2, $3, $4, $5, $6, $7); }
    | packed ARRAY '[' conformant_indices ']' OF conformant_array_type 
         { $$ = new array_tpd_node($1, $2, $3, $4, $5, $6, $7); }

enum_type: '(' ident_list ')' { $$ = new enum_tpd_node($1, $2, $3); }

range_type: expr DOTS expr 
    { $$ = new range_tpd_node($1, $2, $3); } 

pointer_type: '^' type { $$ = new ptr_tpd_node($1, $2); }

set_type: packed SET OF type { $$ = new set_tpd_node($1, $2, $3, $4); }

const_set_type: packed SET OF const_type { $$ = new set_tpd_node($1, $2, $3, $4); }

record_type: packed RECORD field_list END 
    { $$ = new record_tpd_node($1, $2, $3, $4); }

object_type: OBJECT object_components END
    { $$ = new object_tpd_node($1, NULL, NULL, NULL, $2, $3); }
| OBJECT '(' IDENT ')' object_components END
    { $$ = new object_tpd_node($1, $2, $3, $4, $5, $6); }

object_components: object_fields object_methods
    { $1->next = $2; $$ = $1; } 
  | object_methods
  | object_fields

object_fields: field_decl_list 
    { $$ = new var_decl_part_node(NULL, $1); }

field_decl_list: var_decl
     | var_decl ';' { $$ = $1; }
     | var_decl ';' field_decl_list { $1->next = $3; $$ = $1; }

object_methods: proc_fwd_decl | proc_spec
  | proc_fwd_decl object_methods { $1->next = $2; $$ = $1; }
  | proc_spec object_methods { $1->next = $2; $$ = $1; }
  


file_type: packed FIL OF type { $$ = new file_tpd_node($1, $2, $3, $4); }

packed: { $$ = NULL; } | PACKED 

conformant_indices: conformant_index
    | conformant_index ';' conformant_indices { $1->next = $3; $$ = $1; }

conformant_index: IDENT DOTS IDENT ':' type 
    { $$ = new conformant_index_node($1, $2, $3, $4, $5); }

indices: index_spec | index_spec ',' indices 
    { $1->next = $3; $$ = $1; }

index_spec: simple_type { $$ = new type_index_node($1); }
    | expr DOTS expr { $$ = new range_index_node($1, $2, $3); }


field_list: 
    fixed_part variant_part     
        { $$ = new field_list_node($1, $2); }
    | fixed_part                   
        { $$ = new field_list_node($1); }

fixed_part: var_decl_list

variant_part: CASE selector OF variant_list 
{ 
    $$ = new variant_part_node($1, $2, $3, $4); 
}

selector: IDENT ':' type { $$ = new selector_node($1, $2, $3); }
        | type { $$ = new selector_node(NULL, NULL, $1); }


variant_list: variant
        | variant ';' { $$ = $1; }
        | variant ';' variant_list { $1->next = $3; $$ = $1; }

variant: expr_list ':' '(' field_list ')' 
{ 
    $$ = new variant_node($1, $2, $3, $4, $5); 
}

%%

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


