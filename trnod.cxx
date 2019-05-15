#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

#include "nmtbl.h"
#include "token.h"
#include "trnod.h"
#include "util.h"

static proc_tp* curr_proc = NULL;
static char*    struct_path = "";
static token*   global_func_decl_level;

//-----------------------------------------------------------------------------

void node::force_semicolon()
{
    if (l_tkn->tag == TKN_SEMICOLON) return;

    token* tkn = l_tkn->next_relevant();

    if (tkn->tag != TKN_SEMICOLON)  {
	l_tkn = l_tkn->append(";");
	l_tkn->tag = TKN_SEMICOLON;
    } else {
	l_tkn = tkn;
	while ((tkn = tkn->prev)->cat == CAT_WSPC) {
	    if (tkn->tag != TKN_CMNT) tkn->disable();
	}
    }
}

void node::swallow_semicolon()
{
    token* tkn = l_tkn->next_relevant();

    if (tkn->tag == TKN_SEMICOLON)  {
	tkn->disable();
    }
}


void node::attrib(int) {}

void node::translate(int) {}

#define CONS1(a) this->a = a
#define CONS2(a,b) CONS1(a), this->b = b
#define CONS3(a,b,c) CONS2(a,b), this->c = c
#define CONS4(a,b,c,d) CONS3(a,b,c), this->d = d
#define CONS5(a,b,c,d,e) CONS4(a,b,c,d), this->e = e
#define CONS6(a,b,c,d,e,f) CONS5(a,b,c,d,e), this->f = f
#define CONS7(a,b,c,d,e,f,g) CONS6(a,b,c,d,e,f), this->g = g
#define CONS8(a,b,c,d,e,f,g,i) CONS7(a,b,c,d,e,f,g), this->i = i
#define CONS9(a,b,c,d,e,f,g,i,j) CONS8(a,b,c,d,e,f,g,i), this->j = j
#define CONS10(a,b,c,d,e,f,g,i,j,k) CONS9(a,b,c,d,e,f,g,i,j), this->k = k
#define CONS11(a,b,c,d,e,f,g,i,j,k,l) CONS10(a,b,c,d,e,f,g,i,j,k), this->l = l

//=============================================================================
// Statements
//=============================================================================

import_list_node::import_list_node(token* lpar, token_list* params, token* rpar)
{
    CONS3(lpar, params, rpar);
}

void import_list_node::attrib(int)
{
}

void import_list_node::translate(int)
{
    token::remove(lpar, rpar);
}

program_node::program_node(token* program, token* name,
			   import_list_node* params,
			   token* semi, block_node* block, token* end)
{
    CONS6(program, name, params, semi, block, end);
}

void program_node::attrib(int)
{
    curr_proc = main = new proc_tp;
    main->res_type = &integer_type;
    if (turbo_pascal) {
	b_ring::push(main);
	main->scope = b_ring::global;
	b_ring::top_b_ring = main;
    }
    block->attrib(ctx_program);
}

void program_node::translate(int)
{
    if (program != NULL) {
        token::disable(program, semi);
    }
    end->disable();
    curr_proc = main;
    global_func_decl_level = block->body->t_begin;
    block->translate(ctx_program);
    token* first_stmt = block->body->t_begin->next_relevant();

    if (1/*pio_init*/) {
	block->body->t_begin->prepend("int main(int argc, const char* argv[])\n");
    } else {
	block->body->t_begin->prepend("int main()\n");
    }
    block->body->t_end->prepend("return EXIT_SUCCESS;\n")
	->set_bind(first_stmt);
    main->insert_temporaries(first_stmt);
    if (1/*pio_init*/) {
	first_stmt->prepend("pio_initialize(argc, argv);\n");
    }
}

bool unit_node::interface_part;
char* unit_node::unit_name;

unit_node::unit_node(token* t_unit, token* t_name, token* t_semi,
		     token* t_interface,
		     decl_node* unit_decl, token* t_implementation,
		     decl_node* unit_def, compound_node* initializer,
		     token* t_end, token* t_dot)
{
    CONS10(t_unit, t_name, t_semi, t_interface,
	   unit_decl, t_implementation,
	   unit_def, initializer, t_end, t_dot);
}

void unit_node::attrib(int)
{
    decl_node* dcl;

    unit_tp* type = new unit_tp;
    b_ring::global_b_ring.add(t_name->name, symbol::s_var, type);
    b_ring::push(type);

    type->scope = b_ring::global;
    b_ring::top_b_ring = type;

    for (dcl = unit_decl; dcl != NULL; dcl = dcl->next) {
	dcl->attrib(ctx_module);
    }
    for (dcl = unit_def; dcl != NULL; dcl = dcl->next) {
	dcl->attrib(ctx_module);
    }
    if (initializer) {
	curr_proc = main = new proc_tp;
	initializer->attrib(ctx_program);
    }
}

void unit_node::translate(int)
{
    decl_node* dcl;
    char* unit_name = "";
    if (t_name != NULL) {
	unit_name = t_name->out_text;
	t_unit->set_trans(dprintf("#define __%s_implementation__\n",
				  unit_name));
	token::disable(t_name, t_semi);
    }
    if (t_end) {
	t_end->disable();
    }
    t_dot->disable();
    curr_proc = NULL;

    interface_part = TRUE;
    for (dcl = unit_decl; dcl != NULL; dcl = dcl->next) {
	unit_node::unit_name = unit_name;
	dcl->translate(ctx_module);
    }
    interface_part = FALSE;
    for (dcl = unit_def; dcl != NULL; dcl = dcl->next) {
	unit_node::unit_name = unit_name;
	dcl->translate(ctx_module);
    }

    if (initializer) {
	curr_proc = main;
	global_func_decl_level = initializer->t_begin;
	unit_node::unit_name = unit_name;
	initializer->translate(ctx_program);
	token* first_stmt = initializer->t_begin->next_relevant();

	initializer->t_begin->prepend(
	    dprintf("class unit_%s_initialize {\n"
		    "  public: unit_%s_initialize();\n"
		    "};\n"
		    "static unit_%s_initialize %s_constructor;\n\n"
		    "unit_%s_initialize::unit_%s_initialize() ",
		    unit_name, unit_name, unit_name, unit_name,
		    unit_name, unit_name));

        main->insert_temporaries(first_stmt);
    }
    t_implementation->cat = CAT_WSPC;
    t_interface->cat = CAT_WSPC;
}


module_node::module_node(token* program, token* name,
			 import_list_node* params,
			 token* semi, decl_node* decls, token* t_dot)
{
    CONS6(program, name, params, semi, decls, t_dot);
}

void module_node::attrib(int)
{
    for(decl_node* dcl = decls; dcl != NULL; dcl = dcl->next) {
	dcl->attrib(ctx_module);
    }
}

void module_node::translate(int)
{
    if (program != NULL) {
        token::disable(program, semi);
    }
    if (t_dot != NULL) {
	t_dot->disable();
    }
    for(decl_node* dcl = decls; dcl != NULL; dcl = dcl->next) {
	dcl->translate(ctx_module);
    }
}




block_node::block_node(decl_node* decls, compound_node* body)
{
    CONS2(decls, body);
}

void block_node::attrib(int ctx)
{
    for (decl_node* dcl = decls; dcl != NULL; dcl = dcl->next) {
        dcl->attrib(ctx);
    }
    body->attrib(ctx);
}


void block_node::translate(int ctx)
{
    for( decl_node* dcl = decls; dcl != NULL; dcl = dcl->next ) {
        dcl->translate(ctx);
    }
    body->translate(ctx);
    f_tkn = decls ? decls->f_tkn : body->f_tkn;
    l_tkn = body->l_tkn;
}


bool stmt_node::is_compound() { return FALSE; }


label_node::label_node(token* ident, token* colon, stmt_node* stmt)
{
    CONS3(ident, colon, stmt);
}

void label_node::attrib(int ctx)
{
    stmt->attrib(ctx);
}

void label_node::translate(int ctx)
{
    ident->set_trans(dprintf("L%s", ident->out_text));
    stmt->translate(ctx);
    f_tkn = ident;
    l_tkn = stmt->l_tkn;
}

with_node::with_node(token* t_with, expr_node* ptrs, token* t_do, stmt_node* body)
{
    CONS4(t_with, ptrs, t_do, body);
}


int with_node::nested = 0;

static void push_with_context(b_ring* block, expr_node* ptr, stmt_node* body)
{
    record_tp  *type;
    symbol     *save_with = NULL;
    b_ring     **bpp = NULL;

    ptr->attrib(ctx_value);
    if (ptr->type == NULL) {
	body->attrib(ctx_value);
	return;
    }
    type = (record_tp*)ptr->type->get_typedef();

    if (type->tag == tp_record || type->tag == tp_object) {
	for (bpp = &b_ring::curr_b_ring; *bpp != NULL; bpp = &(*bpp)->outer) {
	    if (*bpp == type) {
		*bpp = (*bpp)->outer;
		break;
	    }
	}
	b_ring::push(type);
        save_with = type->with;

	if (ptr->tag == tn_atom
	    && (((atom_expr_node*)ptr)->var == NULL
		|| ((atom_expr_node*)ptr)->var->ring->scope != b_ring::record))
	{
	    // Variable of unnamed type is used as 'with' expression
	    // Do not create new variable in this case (since it's type will
	    // be incompatible), instead of this substitute original variable
	    type->with = ((atom_expr_node*)ptr)->var;
	} else {
	    nm_entry* with = with_node::nested
		? nm_entry::add(dprintf("with%d",with_node::nested),TKN_IDENT)
		: nm_entry::add("with", TKN_IDENT);
	    type->with = block->add(with, symbol::s_ref, type);
	}
	with_node::nested += 1;
    }
    if (ptr->next) push_with_context(block, ptr->next, body);
    else body->attrib(ctx_value);

    if (type->tag == tp_record || type->tag == tp_object) {
	type->with = save_with;
	with_node::nested -= 1;
    b_ring::pop(type);
	if (bpp != NULL) {
	    type->outer = *bpp;
	    *bpp = type;
	}
    }
}

void with_node::attrib(int)
{
    b_ring *block = new b_ring(b_ring::block);

    b_ring::push(block);
    nested_counter = nested;
    push_with_context(block, ptrs, body);
    b_ring::pop(block);
}



void with_node::translate(int ctx)
{
    token* stmt1;

    body->translate(ctx);
    t_do->disable();

    f_tkn = t_with;
    l_tkn = body->l_tkn;

    if (ptrs->tag == tn_atom && ptrs->next == NULL
	&& (((atom_expr_node*)ptrs)->var == NULL
	    || ((atom_expr_node*)ptrs)->var->ring->scope != b_ring::record))
    {
	token::disable(t_with, t_do);
	t_do->disappear();
	return;
    }
    if (body->is_compound())  {
	t_with->set_trans("{\n");
	body->l_tkn->set_bind(t_with);
	body->f_tkn->disable();
	stmt1 = body->f_tkn->next_relevant();
    } else {
        t_with->set_trans("{");
	l_tkn = body->l_tkn->append("}");
	stmt1 = body->f_tkn;
    }

    for (expr_node *e = ptrs; e != NULL; e = e->next) {
	e->translate(language_c ? ctx_access : ctx_value);

	if (e->tag == tn_atom
	    && (((atom_expr_node*)e)->var == NULL
		|| ((atom_expr_node*)e)->var->ring->scope != b_ring::record))
	{
	    token::disable(e->f_tkn, e->l_tkn);
	    token* comma = e->l_tkn->next_relevant();
	    if (comma->tag == TKN_COMMA) {
		comma->disable();
	    }
	} else if (e->type != NULL) {
	    if (e->type->name == NULL && e->type->tpd != NULL) {
		((record_tpd_node*)e->type->tpd)->assign_name();
	    }
	    e->type->insert_before(e->f_tkn)->set_pos(stmt1);
	    if (language_c) {
		if (nested_counter == 0)  {
		    e->f_tkn->prepend("* with = ");
		} else {
		    e->f_tkn->prepend(dprintf("* with%d = ", nested_counter));
		}
		if (e->tag != tn_address) {
		    e->f_tkn->prepend("&");
		}
	    } else {
		if (nested_counter == 0)  {
		    e->f_tkn->prepend("& with = ");
		} else {
		    e->f_tkn->prepend(dprintf("& with%d = ", nested_counter));
		}
	    }
	    if (e->l_tkn->next_relevant()->tag == TKN_COMMA) {
		e->l_tkn->next_relevant()->set_trans(";\n");
	    } else {
		e->l_tkn->append(";");
	    }
	}
	nested_counter += 1;
    }
    swallow_semicolon();
}

pcall_node::pcall_node(expr_node* fcall)
{
    CONS1(fcall);
}

void pcall_node::attrib(int)
{
    fcall->attrib(ctx_statement);
}

void pcall_node::translate(int)
{
    fcall->translate(ctx_statement);
    f_tkn = fcall->f_tkn;
    l_tkn = fcall->l_tkn;
    force_semicolon();
}


read_node::read_node(token* t_read, expr_group_node* params)
{
    CONS2(t_read, params);
}

void read_node::attrib(int)
{
    if( params ) {
	params->attrib(ctx_lvalue);
    }
}


void read_node::translate(int)
{
    f_tkn = l_tkn = t_read;

    if (language_c) {
        if (params) {
            char const* format = "";
	    char const* newln = (t_read->tag == TKN_READLN) ? "\\n" : "";
	    expr_node *prm = params->expr;

	    l_tkn = params->rpar;

	    if (prm->type->tag == tp_file) {
		prm->translate(ctx_value);
		expr_node* file = prm;
		while ((prm = prm->next) != NULL){
		    prm->translate(ctx_lvalue);
		    if (prm->tag == tn_filevar && language_c) {
			prm->f_tkn->prepend("scopy(")->set_pos(t_read);
		    } else {
			prm->f_tkn->prepend("sread(")->set_pos(t_read);
		    }
		    prm->f_tkn->copy(file->f_tkn, file->l_tkn);
		    prm->f_tkn->prepend(", ");
		    prm->l_tkn->append(")");
		}
		token::disable(t_read, file->l_tkn->next_relevant());
		params->rpar->disable();
		force_semicolon();
		return;
	    }
	    if (prm->type->tag == tp_text) {
		prm->translate(ctx_access);
		if (prm->tag != tn_address) {
		    prm->f_tkn->prepend("&");
		}
		prm = prm->next;
		t_read->set_trans("tread");
	    } else {
		t_read->set_trans("cread");
	    }
	    int n_params = 0;
	    while( prm != NULL ) {
		char fmt = '?';
		prm->translate(ctx_access);
		n_params += 1;
		switch (prm->type->tag) {
		  case tp_dynarray:
		  case tp_array:
		    fmt = 's';
		    ((array_tp*)prm->type->get_typedef())
			->insert_dimensions(prm);
		    break;
		  case tp_real:
		    fmt = 'f';
		    break;
		  case tp_integer:
		    fmt = 'i';
		    break;
		  case tp_char:
		    fmt = 'c';
		    break;
		  case tp_bool:
		    fmt = 'b';
		    break;
		  case tp_range:
		    switch(((range_tp*)prm->type->get_typedef())->size) {
		      case 1: fmt = 'B'; break;
		      case 2: fmt = 'W'; break;
		      case 4: fmt = 'i'; break;
		      default:
			warning(prm->f_tkn, "sizeof range type is %d",
				((range_tp*)prm->type->get_typedef())->size);
		    }
		    break;
		  default:
		    warning(prm->f_tkn, "invalid parameter for read operator");
		}
		format = dprintf("%s%%%c", format, fmt);
		if (fmt != 's' && prm->tag != tn_address) {
		    prm->f_tkn = prm->f_tkn->prepend("&");
		}
		prm = prm->next;
	    }
	    if (params->expr->type->tag == tp_text) {
		params->expr->l_tkn->append(dprintf(", \"%s%s\"",
						    format, newln));
	    } else {
		params->lpar->append(dprintf(
		    n_params ? "\"%s%s\", " : "\"%s%s\"", format, newln));
	    }
	} else if (t_read->tag == TKN_READLN) {
	    t_read->set_trans("cread(\"\\n\")");
	} else {
	    warning(t_read, "read statement with no effect");
	    t_read->disable();
	}

    } else { // C++

	if (params) {
	    l_tkn = params->rpar;
	    params->lpar->disable();
	    params->rpar->disable();

	    expr_node *prm = params->expr;
	    bool newln = (t_read->tag == TKN_READLN);

	    if (prm->type->tag == tp_text || prm->type->tag == tp_file) {
		prm->translate(ctx_value);
		if (prm->next) {
		    prm->l_tkn->next_relevant()->set_trans(" >> ");
		}
		prm->f_tkn->set_pos(t_read);
		t_read->disable();
		prm = prm->next;
	    } else {
		t_read->set_trans("input >> ");
	    }
	    while (prm != NULL) {
		prm->translate(ctx_lvalue);
		if (prm->next != NULL) {
		    prm->l_tkn->next_relevant()->set_trans(" >> ");
		}
		prm = prm->next;
	    }
	    if (newln) {
		l_tkn = l_tkn->append(" >> NL");
	    }
	} else if (t_read->tag == TKN_READLN) {
	    t_read->set_trans("input >> NL");
	} else {
	    warning(t_read, "read statement with no effect");
	    t_read->disable();
	}
    }
    force_semicolon();
}


write_node::write_node(token* t_write, write_list_node* params)
{
    CONS2(t_write, params);
}

void write_node::attrib(int)
{
    if( params ) {
	params->attrib(ctx_value);
    }
}


static char* write_format;
static int   n_write_params;

void write_node::translate(int)
{
    f_tkn = l_tkn = t_write;

    if (language_c) {
        if (params) {
	    write_param_node *prm = params->vals;

	    l_tkn = params->rpar;
	    char const* newln = (t_write->tag == TKN_WRITELN) ? "\\n" : "";
            write_format = NULL;
	    if (prm->type->tag == tp_file) {
		prm->translate(ctx_value);
		expr_node* file = prm;
		while ((prm = (write_param_node*)prm->next) != NULL){
		    prm->translate(ctx_value);
		    prm->f_tkn->prepend("swrite(")->set_pos(t_write);
		    prm->f_tkn->copy(file->f_tkn, file->l_tkn);
		    prm->f_tkn->prepend(", ");
		    prm->l_tkn->append(")");
		}
		token::disable(t_write, file->l_tkn->next_relevant());
		params->rpar->disable();
		force_semicolon();
		return;
	    }
	    if (prm->type->tag == tp_text) {
		prm->translate(ctx_access);
		if (prm->val->tag != tn_address) {
		    prm->f_tkn->prepend("&");
		}
		prm = (write_param_node*)prm->next;
		t_write->set_trans("twrite");
	    } else {
		t_write->set_trans("cwrite");
	    }
	    write_format = "";
	    n_write_params = 0;
	    while( prm != NULL ) {
		prm->translate(ctx_value);
		prm = (write_param_node*)prm->next;
	    }
	    if (params->vals->type->tag == tp_text) {
		params->vals->l_tkn->append(dprintf(", \"%s%s\"",
					      write_format, newln));
	    } else {
		params->lpar->append(dprintf(
		    n_write_params ? "\"%s%s\", " : "\"%s%s\"",
		    write_format, newln));
	    }
	} else if (t_write->tag == TKN_WRITELN) {
	    t_write->set_trans("cwrite(\"\\n\")");
	} else {
	    warning(t_write, "write statement with no effect");
	    t_write->disable();
	}

    } else { // language C++

	if (params) {
	    l_tkn = params->rpar;
	    if (t_write->tag == TKN_STR) { // Turbo Pascal
		write_param_node *prm = params->vals;
		while (prm != NULL) {
		    prm->translate(ctx_toascii);
		    prm = (write_param_node*)prm->next;
		}
	    } else {
		params->lpar->disable();
		params->rpar->disable();

		write_param_node *prm = params->vals;
		bool newln = (t_write->tag == TKN_WRITELN);
		if (prm->type->tag == tp_text || prm->type->tag == tp_file) {
		    prm->translate(ctx_value);
		    if (prm->next) {
			prm->l_tkn->next_relevant()->set_trans( " << ");
		    }
		    prm->f_tkn->set_pos(t_write);
		    t_write->disable();
		    prm = (write_param_node*)prm->next;
		} else {
		    t_write->set_trans("output << ");
		}
		while (prm != NULL) {
		    prm->translate(ctx_value);
		    if (prm->next != NULL) {
			prm->l_tkn->next_relevant()->set_trans(" << ");
		    }
		    prm = (write_param_node*)prm->next;
		}
		if (newln) {
		    l_tkn = l_tkn->append(" << NL");
		}
	    }
	} else if (t_write->tag == TKN_WRITELN) {
	    t_write->set_trans("output << NL");
	} else {
	    warning(t_write, "write statement with no effect");
	    t_write->disable();
	}
    }
    force_semicolon();
}

compound_node::compound_node(token* t_begin,  stmt_node* body, token* t_end)
{
    CONS3(t_begin, body, t_end);
}

void compound_node::attrib(int)
{
    for (stmt_node* stmt = body; stmt != NULL; stmt = stmt->next) {
        stmt->attrib(ctx_statement);
    }
}

void compound_node::translate(int)
{
    f_tkn = t_begin;
    l_tkn = t_end;
    for (stmt_node* stmt = body; stmt != NULL; stmt = stmt->next) {
        stmt->translate(ctx_statement);
    }
    t_begin->set_trans("{");
    t_end->set_trans("}");
    swallow_semicolon();
}

bool compound_node::is_compound() { return TRUE; }

assign_node* assign_node::stmt;

assign_node::assign_node(expr_node* lval, token* assign, expr_node* rval)
{
    CONS3(lval, assign, rval);
}

void assign_node::attrib(int)
{
    lval->attrib(ctx_lvalue);
    rval->attrib(lval->type && lval->type->tag == tp_proc
		 ? ctx_procptr : ctx_rvalue);
    if (lval->type && lval->type->tag == tp_set) {
	rval->type = lval->type->get_typedef();
    }
}

void assign_node::translate(int)
{
    stmt = this;
    lval->translate(ctx_lvalue);
    if (lval->tag == tn_filevar) {
	rval->translate(ctx_value);
	f_tkn = lval->f_tkn->prepend("store(");
	token::disable(lval->l_tkn->next, rval->f_tkn->prev);
	lval->l_tkn->append(", ");
	l_tkn = rval->l_tkn->append(")");
	force_semicolon();
	return;
    }
    rval->translate(lval->type && lval->type->tag == tp_proc
		    ? ctx_procptr : ctx_rvalue);

    if (language_c && rval->tag == tn_retarr) {
	// function return array right in assignment destination
	//   lval is moved into function arguments
	f_tkn = rval->f_tkn;
	l_tkn = rval->l_tkn;
	assign->disable();
	force_semicolon();
	return;
    }
    f_tkn = lval->f_tkn;
    l_tkn = rval->l_tkn;
    if (lval->type && (lval->type->tag == tp_array || lval->type->tag == tp_varying_string)) {
	if (language_c) {
	    if (rval->type && rval->type->tag == tp_char) {
		f_tkn = lval->f_tkn->prepend("*");
		assign->set_trans("=");
	    } else {
		token::disable(lval->l_tkn->next, rval->f_tkn->prev);
		lval->l_tkn->append(", ");
		if (lval->is_parameter()) {
		    f_tkn = lval->f_tkn->prepend("memcpy(");
		    if (lval->type->name != NULL) {
			l_tkn = rval->l_tkn->append(dprintf(", sizeof(%s))",
							    lval->type->name));
		    } else {
			l_tkn = rval->l_tkn->append(", ")->append("*sizeof(*");
			((array_tp*)lval->type->get_typedef())->
			    insert_length(l_tkn);
			l_tkn = l_tkn->append("))");
			l_tkn->copy(lval->f_tkn, lval->l_tkn);
		    }
		} else {
		    f_tkn = lval->f_tkn->prepend("arrcpy(");
		    token::disable(lval->l_tkn->next, rval->f_tkn->prev);
		    lval->l_tkn->append(", ");
		    l_tkn = rval->l_tkn->append(")");
		}
	    }
	} else { // language C++
	    if (no_array_assign_operator && rval->type &&
		(rval->type->tag == tp_char || rval->type->tag == tp_string))
	    {
#if 0
		if (rval->type->tag == tp_char) {
		    f_tkn = lval->f_tkn->prepend("*");
		    assign->set_trans("=");
		} else
#endif
		{
		    token::disable(lval->l_tkn->next, rval->f_tkn->prev);
		    lval->l_tkn->append(".assign(");
		    l_tkn = rval->l_tkn->append(")");
		}
	    } else {
		assign->set_trans("=");
	    }
	}
    } else {
	if (assign->tag == TKN_LET) {
	    assign->set_trans("=");
	}
    }
    force_semicolon();
}


goto_node::goto_node(token* t_goto, token* t_label)
{
    CONS2(t_goto, t_label);
}

void goto_node::attrib(int)
{
}

void goto_node::translate(int)
{
    t_label->set_trans(dprintf("L%s", t_label->out_text));
    f_tkn = t_goto;
    l_tkn = t_label;
    force_semicolon();
}

//--------------------------------------------------------------------

case_node::case_node(expr_node* list, token* coln, stmt_node* stmt)
{
    CONS3(list, coln, stmt);
    next = NULL;
}

void case_node::attrib(int ctx)
{
    for (expr_node* e = list; e != NULL; e = e->next) {
	e->attrib(ctx);
    }
    stmt->attrib(ctx);
    if (turbo_pascal) {
	for (stmt_node* st = stmt->next; st != NULL; st = st->next) {
	    st->attrib(ctx);
	}
    }
}

void case_node::translate(int)
{
    if (list == NULL) {
	assert(turbo_pascal ? coln->tag==TKN_ELSE : coln->tag==TKN_OTHERWISE);
        coln->set_trans("default:");
	stmt->translate(ctx_statement);
	if (turbo_pascal) {
	    for (stmt_node* st = stmt->next; st != NULL; st = st->next) {
		st->translate(ctx_statement);
	    }
	}
	f_tkn = coln;
	l_tkn = stmt->l_tkn;

    } else {

	for (expr_node* e = list; e != NULL; e = e->next) {
	    e->translate(ctx_value);
	    e->f_tkn->prepend("case ");
	    e->l_tkn->next_relevant()->set_trans(":");  // replace comma
	}
	stmt->translate(ctx_statement);
	f_tkn = list->f_tkn;
	if (f_tkn->line != stmt->l_tkn->line) {
	    l_tkn = stmt->l_tkn->append("break;");
            l_tkn->set_bind(stmt->l_tkn->get_first_token());
	    stmt->l_tkn->append("\n");
        } else {
	    l_tkn = stmt->l_tkn->append(" break;");
	}
    }
}


switch_node::switch_node(token* t_case, expr_node* expr, token* t_of,
		         case_node* cases, token* t_end)
{
    CONS5(t_case, expr, t_of, cases, t_end);
}

void switch_node::attrib(int)
{
    expr->attrib(ctx_condition);
    for (case_node *c = cases; c != NULL; c = c->next) {
	c->attrib(ctx_statement);
    }
}

void switch_node::translate(int)
{
    f_tkn = t_case;
    l_tkn = t_end;
    expr->translate(ctx_value);
    t_case->set_trans("switch");
    if (expr->tag != tn_group) {
        expr->f_tkn->prepend("(");
        expr->l_tkn->append(")");
    }
    t_of->set_trans("{");
    for (case_node *c = cases; c != NULL; c = c->next) {
        c->translate(ctx_statement);
    }
    t_end->set_trans("}");
    swallow_semicolon();
}

if_node::if_node(token* t_if, expr_node* expr, token* t_then,
		 stmt_node* alt1, token* t_else, stmt_node* alt2)
{
    CONS6(t_if, expr, t_then, alt1, t_else, alt2);
}

void if_node::attrib(int)
{
    expr->attrib(ctx_condition);
    alt1->attrib(ctx_statement);
    if (alt2) {
	alt2->attrib(ctx_statement);
    }
}

void if_node::translate(int)
{
    expr->translate(ctx_condition);
    f_tkn = t_if;
    if (expr->tag != tn_group) {
        expr->f_tkn->prepend("(");
        expr->l_tkn->append(")");
    }
    t_then->disable();
    alt1->translate(ctx_statement);
    l_tkn = alt1->l_tkn;
    if (alt2) {
        alt2->translate(ctx_statement);
	l_tkn = alt2->l_tkn;
    }
}

for_node::for_node(token* t_for, token* t_ident, token* t_asg,
	           expr_node* from, token* t_to, expr_node* till,
	           token* t_do, stmt_node* body)
{
    CONS8(t_for, t_ident, t_asg, from, t_to, till, t_do, body);
}

void for_node::attrib(int)
{
    from->attrib(ctx_value);
    till->attrib(ctx_value);
    body->attrib(ctx_statement);
    var = b_ring::search_cur(t_ident);
}

void for_node::translate(int ctx)
{
    if (var != NULL) {
	var->translate(t_ident);
    }
    t_for->append("(");
    t_asg->set_trans("=");
    from->translate(ctx_value);
    from->l_tkn->append(";");
    t_to->set_trans(t_ident->out_text);
    t_to->append(t_to->name->tag == TKN_TO ? " <=" : " >=");
    till->translate(ctx_value);
    till->l_tkn->append(";");
    if (t_to->name->tag == TKN_TO) {
	if (var && var->type->tag == tp_enum && var->type->name != NULL) {
	    t_do->set_trans(dprintf("%s = succ(%s,%s))",
				    t_ident->out_text, var->type->name,
				    t_ident->out_text));
	} else {
	    t_do->set_trans(dprintf("%s ++)", t_ident->out_text));
	}
    } else {
	if (var && var->type->tag == tp_enum && var->type->name != NULL) {
	    t_do->set_trans(dprintf("%s = pred(%s,%s))",
				    t_ident->out_text, var->type->name,
				    t_ident->out_text));
	} else {
	    t_do->set_trans(dprintf("%s --)", t_ident->out_text));
	}
    }
    body->translate(ctx);
    f_tkn = t_for;
    l_tkn = body->l_tkn;
}

while_node::while_node(token* t_while, expr_node* expr, token* t_do,
	               stmt_node* body)
{
    CONS4(t_while, expr, t_do, body);
}

void while_node::attrib(int ctx)
{
    expr->attrib(ctx_condition);
    body->attrib(ctx);
}

void while_node::translate(int ctx)
{
    expr->translate(ctx_condition);
    if (expr->tag != tn_group) {
        expr->f_tkn->prepend("(");
        expr->l_tkn->append(")");
    }
    t_do->disable();
    body->translate(ctx);
    f_tkn = t_while;
    l_tkn = body->l_tkn;
}

repeat_node::repeat_node(token* t_repeat, stmt_node* body, token* t_until,
			 expr_node*expr)
{
    CONS4(t_repeat, body, t_until, expr) ;
}

void repeat_node::attrib(int ctx)
{
    for (stmt_node *stmt = body; stmt != NULL; stmt = stmt->next) {
        stmt->attrib(ctx);
    }
    expr->attrib(ctx_condition);
}

void repeat_node::translate(int ctx)
{
    bool body_is_block =
	body != NULL && body->is_compound() && body->next == NULL;

    t_repeat->set_trans(body_is_block ? "do" : "do {");
    for (stmt_node *stmt = body; stmt != NULL; stmt = stmt->next) {
        stmt->translate(ctx);
    }
    t_until->set_trans(body_is_block ? "while" : "} while");
    expr->translate(ctx_condition);
    f_tkn = t_repeat;
    l_tkn = expr->l_tkn;
    if (expr->tag != tn_group && expr->tag != tn_atom) {
        expr->f_tkn->prepend("(!(");
        l_tkn = expr->l_tkn->append("))");
    } else {
        expr->f_tkn->prepend("(!");
        l_tkn = expr->l_tkn->append(")");
    }
    force_semicolon();
}

return_node::return_node(token* t_return)
{
    CONS1(t_return);
}

void return_node::attrib(int)
{
}

void return_node::translate(int)
{
    l_tkn = f_tkn = t_return;
    if (curr_proc->is_function()) {
	if (language_c && curr_proc->res_type->tag == tp_array) {
	    l_tkn = t_return->append(dprintf(" (%s*)%s_result",
					     curr_proc->res_type->name,
					     curr_proc->proc_name));
	} else {
	    if (curr_proc->is_constructor || curr_proc->is_destructor) {
		l_tkn = t_return->append(" this");
	    } else {
		l_tkn = t_return->append(dprintf(" %s_result",
						 curr_proc->proc_name));
	    }
	}
    }
    force_semicolon();
}

empty_node::empty_node(token* last)
{
    CONS1(last);
}

void empty_node::attrib(int)
{
    f_tkn = l_tkn = last;
}

void empty_node::translate(int)
{
    token* last = l_tkn;
    token* prev = last->next->prev_relevant();
    if (prev->out_text == NULL || strcmp(prev->out_text, "}") != 0) {
        force_semicolon();
    }
    l_tkn->set_pos(last);
}

//
// Expression level
//


bool expr_node::is_parameter()
{
    symbol *var = ((atom_expr_node*)this)->var;
    return tag == tn_atom
	&& ((var->flags & (symbol::f_val_param|symbol::f_var_param))
	    || (var->ring->scope != b_ring::record
		&& var->ring != curr_proc
		&& var->ring->scope != b_ring::global));
}

atom_expr_node::atom_expr_node(token* tkn) : expr_node(tn_atom)
{
    CONS1(tkn);
}

void atom_expr_node::attrib(int ctx)
{
    if (turbo_pascal && tkn->name->tag == TKN_SELF) {
	assert(proc_def_node::self != NULL);
	type = proc_def_node::self;
	with = proc_def_node::self->with;
	tag = tn_self;
	var = NULL;
    } else if (turbo_pascal && tkn->name->tag == TKN_EXIT) {
	type = &void_type;
    } else if (!turbo_pascal || tkn->name->tag != TKN_ABSTRACT) {
	var = b_ring::search_cur(tkn);
	if (var != NULL) {
	    if (var->type == NULL) {
		warning(tkn, "type of variable '%s' is unknown", tkn->in_text);
		var->type = &void_type;
	    }

	    type = var->type;
	    with = var->ring->with;

	    if (var->flags & symbol::f_const) {
		flags |= tn_is_const;
		value = var->value;
	    }

	    if (type->tag == tp_proc) {
		if (ctx == ctx_lvalue) {
		    if (type == curr_proc) {
			type = curr_proc->res_type;
			if (type == NULL) {
			    error(tkn,"attempt to return value from procedure");
			}
		    }
		} else {
		    if (ctx == ctx_procptr) {
			var->out_name->flags |= nm_entry::recursive;
		    } else if (ctx != ctx_apply) {
			proc_tp* prc = (proc_tp*)type->get_typedef();
			prc->add_caller(curr_proc);
			type = prc->res_type;
			if (language_c && type != NULL && type->tag == tp_array
			    && ctx != ctx_rvalue)
			{
			    temp = curr_proc->add_temp(type);
			}
		    }
		}
	    } else {
		if (var->ring->scope == b_ring::proc && var->ring != curr_proc)
		{
		    if (var->tag == symbol::s_const) {
			if (!(var->flags & symbol::f_static)) {
			    var->flags |= symbol::f_static;
			    var->ring->make_unique(var);
			}
		    } else {
			curr_proc->add_extra_param(var);
		    }
		}
		if (ctx == ctx_lvalarray || ctx == ctx_lvalue) {
		    var->flags |= symbol::f_lvalue;
		}
	    }
	} else {
	    // Let converter work well even with incorrect code
	    warning(tkn, "undefined identifier '%s'", tkn->in_text);
	    type = &void_type;
	    with = NULL;
	}
    }
}

void atom_expr_node::translate(int ctx)
{
    l_tkn = f_tkn = tkn;

    if (turbo_pascal && tkn->name->tag == TKN_SELF) {
	if (ctx == ctx_access) {
	    tkn->set_trans("this");
	} else {
	    tkn->set_trans("(*this)");
	}
	return;
    } else if (turbo_pascal && tkn->name->tag == TKN_EXIT) {
	if (curr_proc && curr_proc->res_type) {
	    if (curr_proc->proc_name != NULL) {
		tkn->set_trans(dprintf("return %s_result",
				       curr_proc->proc_name));
	    } else {
		tkn->set_trans("return 0");
	    }
	} else {
	    tkn->set_trans("return");
	}
	return;
    } else if (turbo_pascal && tkn->name->tag == TKN_ABSTRACT) {
	tkn->set_trans("assert(\"abstract method is called\",false)");
	return;
    }
    if (var != NULL) {
	var->translate(tkn);
        if (var->type == curr_proc && ctx == ctx_lvalue) {

	    tkn->set_trans(dprintf("%s_result", curr_proc->proc_name));

        } else if (var->type->tag == tp_proc) {
	    if (turbo_pascal && tkn->name->tag == TKN_HALT) {
		tkn->set_trans(ctx == ctx_apply ? "exit" : "exit(0)");
		return;
	    }
	    proc_tp* prc = (proc_tp*)var->type->get_typedef();
            if (ctx != ctx_procptr && ctx != ctx_apply && ctx != ctx_lvalue) {
	        token* lpar = tkn->append("(");
		token* t = lpar;
		bool first = TRUE;
		param_spec* prm;

		if (language_c) {
		    for (prm = prc->params;
			 prm != NULL;
			 prm = prm->next)
		    {
			if (!first) {
			    t = t->append(", ");
			}
			first = FALSE;
			if (prm->var->type->tag == tp_file
			    || prm->var->type->tag == tp_text)
			{
			    t = t->append(strcmp(var->in_name->text, "page")
					  ? "input" : "output");
			} else {
			    t = t->append("0");
			}
		    }
		}
                for (prm = prc->extra_params;
	             prm != NULL;
                     prm = prm->next)
                {
		    if (prm->var->flags & symbol::f_static) continue;

		    if (!first) {
			t = t->append(", ");
		    }
		    first = FALSE;

		    if (language_c && prm->var->tag != symbol::s_ref
			&& (prm->var->tag != symbol::s_const
			    || !prm->var->type->is_scalar())
			&& prm->var->ring == curr_proc
			&& !prm->var->type->is_array())
		    {
			t = t->append("&");
		    }
		    t = t->append(prm->var->out_name->text);
                }
                l_tkn = t = t->append(")");
		if (language_c && type != NULL && type->tag == tp_array) {
		    if (!first) {
			t = lpar->append(", ");
		    }
		    if (ctx == ctx_rvalue) {
			f_tkn->set_pos(assign_node::stmt->lval->f_tkn);
			t->move(assign_node::stmt->lval->f_tkn,
				assign_node::stmt->lval->l_tkn);
			tag = tn_retarr;
		    } else {
			t->prepend(temp);
			f_tkn = f_tkn->prepend("*");
		    }
		}
            } // endif not function  pointer
        } else if (var->ring->scope == b_ring::record) {

            if (with != NULL) {
		f_tkn = tkn->prepend(language_c && with->tag == symbol::s_ref
				     ? "->" : ".")
		    ->prepend(with->out_name->text);
	    }

	} else if (language_c &&
		   (!var->type->is_array()
		    && (var->tag != symbol::s_const || !var->type->is_scalar())
		    && (var->tag == symbol::s_ref
			|| (!(var->flags & symbol::f_static)
			    && var->ring->scope != b_ring::record
			    && var->ring != curr_proc
			    && var->ring->scope != b_ring::global))))
	{
	    if (ctx == ctx_access) {
		tag = tn_address;
	    } else if (ctx == ctx_array || ctx == ctx_lvalarray) {
		f_tkn = tkn->prepend("(*");
		l_tkn = tkn->append(")");
	    } else {
		f_tkn = tkn->prepend("*");
	    }
        } else if (ctx == ctx_statement) {
	    l_tkn = tkn->append("()");
        }
    }
}

literal_node::literal_node(token* value_tkn, int tag)
: expr_node(tag, tn_is_literal)
{
    CONS1(value_tkn);
}

integer_node::integer_node(token* value_tkn) : literal_node(value_tkn, tn_intnum)
{
    flags |= tn_is_const;
}

static long btoi(char* s)
{
    long val = 0;
    while (*s == '0' || *s == '1') {
	val = (val << 1) | (*s++ - '0');
    }
    return val;
}

void integer_node::attrib(int)
{
    type = &integer_type;
    char* p = value_tkn->in_text;

    if (p[0] == '0' && (p[1] == 'x' || p[1] == 'X'))
    {
	sscanf(p + 2, "%x", &value);
	radix = 16;
    } else if (turbo_pascal && *p == '$') {
	sscanf(p + 1, "%x", &value);
	radix = 16;
    } else if(*p == '%') {
	value = btoi(p + 1);
	radix = 8;
    } else if(strncmp(p, "2#", 2) == 0) {
	value = btoi(p + 2);
	radix = 8;
    } else if(strncmp(p, "8#", 2) == 0) {
	sscanf(p + 2, "%o", &value);
	radix = 8;
    } else if(strncmp(p, "16#", 3) == 0) {
	sscanf(p + 3, "%x", &value);
	radix = 16;
    } else if(strncmp(p, "10#", 3) == 0) {
	sscanf(p + 3, "%d", &value);
	radix = 10;
    } else {
	int len = strlen(p)-1;
	if (p[len] == 'h' || p[len] == 'H') {
	    sscanf(p, "%x", &value);
	    radix = 16;
	} else if (p[len] == 'b' || p[len] == 'B') {
	    value = btoi(p);
	    radix = 16;
	} else {
	    sscanf(p, "%d", &value);
	    radix = 10;
	}
    }
}

void integer_node::translate(int)
{
    f_tkn = l_tkn = value_tkn;

    switch(radix) {
      case 8:
	value_tkn->set_trans(dprintf("%#o", value));
	break;
      case 10:
	value_tkn->set_trans(dprintf("%d", value));
	break;
      case 16:
	value_tkn->set_trans(dprintf("%#x", value));
	break;
    }
}


real_node::real_node(token* value_tkn) : literal_node(value_tkn, tn_realnum) {}

void real_node::attrib(int)
{
    type = &real_type;
}

void real_node::translate(int)
{
    f_tkn = l_tkn = value_tkn;
}

string_node::string_node(token* value_tkn) : literal_node(value_tkn, tn_string) {}

void string_node::attrib(int)
{
    char *s = value_tkn->out_text;

    if ((s[0] == '\'' && s[1] != '\'' && s[2] == '\'' && s[3] == '\0') ||
       (s[0] == '\'' && s[1] == '\'' && s[2] == '\'' && s[3] == '\'' && s[4] == '\0') ||
	s[0] == '#' && strchr(s+1, '#') == NULL && strchr(s+1, '\'') == NULL)
    {
        type = &char_type;
    } else {
        type = &string_type;
    }
}

void string_node::translate(int ctx)
{
    char *s = value_tkn->out_text;

    f_tkn = l_tkn = value_tkn;

    if (s[0] == '\'' && s[1] != '\'' && s[2] == '\'' && s[3] == '\0') {
        tag = tn_char;
	value = (unsigned char)s[1];
	if (s[1] == '\\') {
	    s[2] = '\\';
	    s[3] = '\'';
	    s[4] = '\0';
	}
    } else if (s[0] == '\'' && s[1] == '\'' && s[2] == '\''
	    && s[3] == '\'' && s[4] == '\0')
    {
        tag = tn_char;
	value = '\'';
	s[1] = '\\';
    } else if (s[0] == '#' && strchr(s+1, '#') == NULL
	       && strchr(s+1, '\'') == NULL)
    {
        tag = tn_char;
	if (s[1] == '$') {
	    sscanf(s+2, "%x\n", &value);
	    value_tkn->set_trans(dprintf("'\\x%x'", value));
	} else {
	    sscanf(s+1, "%d\n", &value);
	    value_tkn->set_trans(dprintf("'\\%o'", value));
	}
    } else {
	if (!language_c && ctx == ctx_record) {
	    char *buf = new char[strlen(s)*4];
	    char ch, *d = buf;
	    *d++ = '{';
	    *d++ = '{';
	    bool in_quotes = FALSE;
	    while((ch = *s++) != '\0') {
		switch(ch) {
		  case '\\':
		    *d++ = '\\';
		    *d++ = '\\';
		    continue;
		  case '\'':
		    if (in_quotes) {
			if (*s == '\'') {
			    if (*(d-1) != '{') *d++ = ',';
			    *d++ = '\'';
			    *d++ = '\\';
			    *d++ = '\'';
			    *d++ = '\'';
			    s += 1;
			}
			in_quotes = FALSE;
		    } else {
			in_quotes = TRUE;
		    }
		    continue;
		  case '#':
		    if (!in_quotes) {
			if (*(d-1) != '{') *d++ = ',';
			if (*s == '$') {
			    *d++ = '0';
			    *d++ = 'x';
			    s += 1;
			    while (ch = *++s, isxdigit((unsigned char)ch)) {
				*d++ = ch;
			    }
			} else {
			    while ((ch = *s++) >= '0' && ch <= '9') {
				*d++ = ch;
			    }
			    s -= 1;
			}
			continue;
		    }
		  default:
		    if (*(d-1) != '{') *d++ = ',';
		    *d++ = '\'';
		    *d++ = ch;
		    *d++ = '\'';
		}
	    }
	    *d++ = '}';
	    *d++ = '}';
	    *d++ = '\0';
	    value_tkn->set_trans(buf);
	    return;
	} else {
	    char *buf = new char[strlen(s)*2 + 1];
	    char ch, *d = buf;
	    bool in_quotes = FALSE;
	    *d++ = '"';
	    while((ch = *s++) != '\0') {
		switch(ch) {
		  case '\\':
		    *d++ = '\\';
		    *d++ = '\\';
		    continue;
		  case '"':
		    *d++ = '\\';
		    *d++= '"';
		    continue;
		  case '\'':
		    if (in_quotes) {
			if (*s == '\'') {
			    *d++ = '\'';
			}
			in_quotes = FALSE;
		    } else {
			in_quotes = TRUE;
		    }
		    continue;
		  case '?':
		    if (s[-1] == '?' &&
			(s[1] == '=' || s[1] == '/' ||
			 (s[1] == '\'' && s[2] == '\'') ||
			 s[1] == '(' || s[1] == ')' || s[1] == '!' ||
			 s[1] == '-' || s[1] == '<' || s[1] == '>'))
		    {
			*d++ = '\\';
                    }
		    *d++ = ch;
		    continue;
		  case '#':
		    if (!in_quotes) {
			int code = 0;
			if (*s == '$') {
			    *d++ = '\\';
			    *d++ = 'x';
			    while (ch = *++s, isxdigit((unsigned char)ch)) {
				*d++ = ch;
			    }
			    continue;
			} else {
			    while ((ch = *s++) >= '0' && ch <= '9') {
				code = code*10 + ch - '0';
			    }
			    s -= 1;
			}
			switch (code) {
			  case '\n':
			    *d++ = '\\';
			    *d++ = 'n';
			    break;
			  case '\t':
			    *d++ = '\\';
			    *d++ = 'n';
			    break;
			  case '\r':
			    *d++ = '\\';
			    *d++ = 'r';
			    break;
			  case '\f':
			    *d++ = '\\';
			    *d++ = 'f';
			    break;
			  case '\b':
			    *d++ = '\\';
			    *d++ = 'b';
			    break;
			  case '\v':
			    *d++ = '\\';
			    *d++ = 'v';
			    break;
			  default:
			    *d++ = '\\';
			    d += sprintf(d, "%o", code);
			}
			continue;
		    }
		  default:
		    *d++ = ch;
		}
	    }
	    *d++ = '"';
	    *d++ = '\0';
	    value_tkn->set_trans(buf);
	}
    }
}

set_elem_node::set_elem_node(expr_node* item)
{
    CONS1(item);
}

void set_elem_node::attrib(int ctx)
{
    item->attrib(ctx);
    type = item->type;
}

void set_elem_node::translate(int ctx)
{
    item->translate(ctx);
    f_tkn = item->f_tkn;
    l_tkn = item->l_tkn;
    if (language_c && short_set && type->tag == tp_enum &&
	((enum_tp*)type->get_typedef())->n_elems <= SHORT_SET_CARD)
    {
	token* t = l_tkn->next_relevant();
	if (t->tag == TKN_COMMA) {
	    t->set_trans("|");
	    if (t->next->tag == TKN_SPACE) t->next->disable();
	    if (t->prev->tag == TKN_SPACE) t->prev->disable();
	}
	f_tkn = f_tkn->prepend("ELEM(");
	l_tkn = l_tkn->append(")");
    }
}

set_range_node::set_range_node(expr_node* low, token* dots, expr_node* high)
{
    CONS3(low, dots, high);
}

void set_range_node::attrib(int ctx)
{
    low->attrib(ctx);
    high->attrib(ctx);
    type = low->type;
}

void set_range_node::translate(int ctx)
{
    low->translate(ctx);
    high->translate(ctx);
    if (language_c && short_set && type->tag == tp_enum &&
	((enum_tp*)type->get_typedef())->n_elems <= SHORT_SET_CARD)
    {
	token* t = low->l_tkn->next_relevant();
	if (t->tag == TKN_COMMA) t->set_trans("|");
	f_tkn = low->f_tkn->prepend("RANGE(");
    } else {
	f_tkn = low->f_tkn->prepend("range(");
    }
    l_tkn = high->l_tkn->append(")");
    dots->set_trans(",");
}

set_node::set_node(token* t_lbr, set_item_node* items, token* t_rbr)
: expr_node(tn_set)
{
    CONS3(t_lbr, items, t_rbr);
}

void set_node::attrib(int)
{
    for (set_item_node* item = items; item != NULL; item = item->next) {
        item->attrib(ctx_value);
    }
    type = new set_tp(items ? items->type : &integer_type);
}

void set_node::translate(int)
{
    f_tkn = t_lbr;
    l_tkn = t_rbr;
    for (set_item_node* item = items; item != NULL; item = item->next) {
	item->translate(ctx_value);
    }
    if (language_c) {
	if (short_set && ((set_tp*)type)->is_short_set()) {
	    if (items) {
		if (items->next != NULL) {
		    t_lbr->set_trans("(");
		    t_rbr->set_trans(")");
		} else {
		    t_lbr->disable();
		    t_rbr->disable();
		}
	    } else {
		t_lbr->set_trans("0");
		t_rbr->disable();
	    }
	    return;
	} else {
	    t_lbr->set_trans("setof(");
	}
    } else {
	if (((set_tp*)type)->elem_type->tag == tp_enum) {
	    assert(((set_tp*)type)->elem_type->name != NULL);
	    t_lbr->set_trans(dprintf("set_of_enum(%s)::of(",
				     ((set_tp*)type)->elem_type->name));
	} else {
	    t_lbr->set_trans("set::of(");
	}
    }
    t_rbr->set_trans(items ? ", eos)" : "eos)");
}

idx_expr_node::idx_expr_node(expr_node* arr, token* t_lbr, expr_node* indices,
		             token* t_rbr)
: expr_node(tn_index)
{
    CONS4(arr, t_lbr, indices, t_rbr);
}

void idx_expr_node::attrib(int ctx)
{
    arr->attrib(ctx == ctx_lvalue ? ctx_lvalarray : ctx_array);
    type = arr->type;

    for(expr_node* e = indices; e != NULL; e = e->next) {
        if (type && type->is_array()) {
	    type = ((array_tp*)type->get_typedef())->elem_type;
	}
        e->attrib(ctx_value);
    }
}

void idx_expr_node::translate(int ctx)
{
    arr->translate(ctx == ctx_lvalue ? ctx_lvalarray : ctx_array);
    f_tkn = arr->f_tkn;
    l_tkn = t_rbr;

    array_tp* arr_type = arr->type ? (array_tp*)arr->type->get_typedef()
	                           : (array_tp*)NULL;

    for (expr_node* e = indices; e != NULL; e = e->next) {
        e->translate(ctx_value);
	token *next = e->l_tkn->next_relevant();

	if (arr_type == NULL || !arr_type->is_array()) {
	    warning(e->f_tkn, "applying index operator to expression of non-array type");
	}
	if (language_c && arr_type && arr_type->is_array()) {
	    if (arr_type->base != 0 && !no_index_decrement) {
		if (arr_type->base != -1 && e->tag == tn_add
		    && ((op_node*)e)->right->is_const_literal())
		{
		    int val = ((op_node*)e)->right->value - arr_type->base;
		    if (val == 0) {
			token::disable(((op_node*)e)->left->l_tkn->next,
				       ((op_node*)e)->right->l_tkn);
		    } else {
			((op_node*)e)->right->f_tkn->set_trans(dprintf("%d", val));
		    }
		}
		else if (arr_type->base != -1 && e->tag == tn_sub
			   && ((op_node*)e)->right->is_const_literal())
		{
		    ((op_node*)e)->right->f_tkn->set_trans(dprintf("%d",
		         ((op_node*)e)->right->value + arr_type->base));
		}
		else if (arr_type->base != -1
			   && (e->tag == tn_add || e->tag == tn_sub)
			   && ((op_node*)e)->left->is_const_literal())
		{
		    ((op_node*)e)->left->f_tkn->set_trans(dprintf("%d",
			((op_node*)e)->left->value - arr_type->base));
		}
		else if (arr_type->base != -1 && e->is_const_literal())
		{
		    e->f_tkn->set_trans(dprintf("%d", e->value - arr_type->base));
		}
		else if (arr_type->low)
		{
		    e->l_tkn->append(dprintf(" - %s", arr_type->low));
		}
		else
		{
		    assert(arr_type->low_expr != NULL);
		    token* next = e->l_tkn->next;
		    next->prepend("-(");
		    next->copy(arr_type->low_expr->f_tkn,
			       arr_type->low_expr->l_tkn);
		    next->prepend(")");
		    e->l_tkn = next->prev;
		}
	    }
	    if (arr_type->elem_type->tag == tp_dynarray) {
		if (arr->tag == tn_index
		    && t_lbr != ((idx_expr_node*)arr)->t_lbr)
		{
		    t_lbr->disable();
		    t_lbr = ((idx_expr_node*)arr)->t_lbr;
		}
		if (t_lbr->next_relevant() != e->l_tkn) {
		    t_lbr->append("(");
		    e->l_tkn->append(")");
		}
		if (e->l_tkn->next != next) {
		    token::disable(e->l_tkn->next, next->prev);
		}
		next->set_trans(dprintf("*(%s-%s+1) + ",
					arr_type->high, arr_type->low));
		arr_type = (array_tp*)arr_type->elem_type->get_typedef();
		continue;
	    } else if (arr_type->tag == tp_dynarray
		       && arr->tag == tn_index
		       && t_lbr != ((idx_expr_node*)arr)->t_lbr)
	    {
		    t_lbr->disable();
		    t_lbr = ((idx_expr_node*)arr)->t_lbr;
	    }

	} else if (arr_type && arr_type->tag == tp_string) {
	    e->l_tkn->append("-1");
	}

	if (arr_type && arr_type->is_array() && arr_type->elem_type->is_array()) {
	    arr_type = (array_tp*)arr_type->elem_type->get_typedef();
	}
	if (e->next != NULL) {
	    assert(next->tag == TKN_COMMA);

	    token::disable(e->l_tkn->next, next->next_relevant()->prev);
	    e->l_tkn->append("][");
	}
    }
}

deref_expr_node::deref_expr_node(expr_node* ptr, token* op)
: expr_node(tn_deref)
{
    CONS2(ptr, op);
}

void deref_expr_node::attrib(int)
{
    ptr->attrib(ctx_array);
    type = ptr->type;
    if (type->is_reference()) {
	type = ((ref_tp*)type->get_typedef())->base_type;
    } else {
	warning(op, "dereferencing not pointer type");
    }
}

void deref_expr_node::translate(int ctx)
{
    ptr->translate(ctx_array);
    f_tkn = ptr->f_tkn;
    l_tkn = op;
    op->disable();
    if (ptr->type != NULL && (ptr->type->tag == tp_file || ptr->type->tag == tp_text)) {
        tag = tn_filevar;
	if (ctx != ctx_lvalue) {
	    if (language_c) {
		ptr->l_tkn->append(")");
		if (ctx == ctx_access) {
		    f_tkn = f_tkn->prepend("currec(");
		    tag = tn_address;
		} else {
		    if (ctx == ctx_array) {
			f_tkn = f_tkn->prepend("(*currec(");
			ptr->l_tkn->append(")");
		    } else {
			f_tkn = f_tkn->prepend("*currec(");
		    }
		}
	    } else { //language C++
		f_tkn = f_tkn->prepend("*");
		if (ctx == ctx_array || ctx == ctx_access) {
		    f_tkn = f_tkn->prepend("(");
		    ptr->l_tkn->append(")");
		}
	    }
	}
    } else {
	if (ctx != ctx_access) {
	    if (type && type->tag != tp_void) { // not Turbo Pascal pointer type
		f_tkn = f_tkn->prepend("*");
		if (ctx == ctx_array || ctx == ctx_lvalarray) {
		    f_tkn = f_tkn->prepend("(");
		    ptr->l_tkn->append(")");
		}
	    }
	} else {
	    tag = tn_address;
	}
	op->disable();
    }
}



access_expr_node::access_expr_node(expr_node* rec, token* pnt, token* field)
  : expr_node(tn_access)
{
    CONS3(rec, pnt, field);
}

void access_expr_node::attrib(int)
{
    rec->attrib(ctx_access);
    if (rec->type != NULL && (rec->type->tag == tp_record || rec->type->tag == tp_object || rec->type->tag == tp_unit)) {
        recfld = ((record_tp*)rec->type->get_typedef())->search(field);
	if (recfld == NULL) {
	    warning(field, "component not found");
	}
    } else {
	warning(field, "unknown record type");
	recfld = NULL;
    }
    if (recfld == NULL) {
	type = &void_type;
    } else {
	type = recfld->type;
    }
}

void access_expr_node::translate(int ctx)
{
    rec->translate(ctx_access);
    f_tkn = rec->f_tkn;
    l_tkn = field;
    if (rec->tag == tn_address || rec->tag == tn_self) {
       pnt->set_trans("->");
    } else if (rec->type != NULL && rec->type->tag == tp_unit) {
       pnt->set_trans("::");
    }
    if (recfld) recfld->translate(field);
    if (turbo_pascal
	&& rec->type != NULL
	&& (rec->type->tag == tp_object || rec->type->tag == tp_unit)
	&& type->tag == tp_proc && ctx != ctx_apply)
    {
	l_tkn = l_tkn->append("()");
    }
}

//---------------------------------------------------------

address_node::address_node(token* t_adr, expr_node* var)
: expr_node(tn_ref)
{
    CONS2(t_adr, var);
}

void address_node::attrib(int)
{
    var->attrib(ctx_lvalue);
    type = new ref_tp(var->type);
}

void address_node::translate(int)
{
	f_tkn = t_adr;
    if (turbo_pascal && var->tag == tn_self) {
       ((atom_expr_node*)var)->tkn->remove();
       l_tkn = f_tkn;
	   f_tkn->set_trans("this");
    } else {
	   var->translate(ctx_lvalue);
       t_adr->set_trans("&");
       l_tkn = var->l_tkn;
    }
}

//---------------------------------------------------------

void case_range_node::attrib(int ctx)
{
    from->attrib(ctx);
    to->attrib(ctx);
    type = from->type;
}

void case_range_node::translate(int ctx)
{
    from->translate(ctx);
    to->translate(ctx);
    if ((from->tag == tn_char || from->tag == tn_intnum) &&
	(to->tag == tn_char || to->tag == tn_intnum))
    {
	int range = to->value - from->value + 1;
	if (range > 1 && (range <= 16 || range == 26 || range == 32))
	{
	    f_tkn = from->f_tkn->prepend(dprintf("RANGE_%d(", range));
	    l_tkn = to->l_tkn->append(")");
	    t_range->set_trans(",");
	    return;
	}
    }
    warning(t_range,"Conversion of case range item is correct only for GCC\n");
    t_range->set_trans(" ... ");
    f_tkn = from->f_tkn;
    l_tkn = to->l_tkn;
}

case_range_node::case_range_node(expr_node* from, token* t_range, expr_node*to)
: expr_node(tn_case_range)
{
    CONS3(from, t_range, to);
}

//----------------------------------------------------------

op_node::op_node(int tag, expr_node* left, token* op, expr_node* right)
: expr_node(tag)
{
    CONS3(left, op, right);
}


void op_node::attrib(int)
{
    if (left) {
	left->parent_tag = tag;
        left->attrib(ctx_value);
	type = left->type;
    }
    if (right) {
	right->parent_tag = tag;
        right->attrib(ctx_value);
	type = right->type;
    }
    if ((unsigned(tag - tn_add) <= tn_div - tn_add) &&
	((left->type && left->type->get_typedef() == &longint_type)
	 || (right->type && right->type->get_typedef() == &longint_type)))
    {
	type = &longint_type;
    }
    if ((left == NULL || (left->flags & tn_is_const)) &&
	(right == NULL || (right->flags & tn_is_const)))
    {
	switch (tag) {
	  case tn_add:
	    value = left->value + right->value;
	    flags |= tn_is_const;
	    break;
	  case tn_sub:
	    value = left->value - right->value;
	    flags |= tn_is_const;
	    break;
	  case tn_plus:
	    value = + right->value;
	    flags |= tn_is_const | (right->flags & tn_is_literal);
	    break;
	  case tn_minus:
	    value = - right->value;
	    flags |= tn_is_const | (right->flags & tn_is_literal);
	    break;
	  case tn_mod:
	    value = left->value % right->value;
	    flags |= tn_is_const;
	    break;
	  case tn_mul:
	    value = left->value * right->value;
	    flags |= tn_is_const;
	    break;
	  case tn_div:
	    value = left->value / right->value;
	    flags |= tn_is_const;
	    break;
	}
    }

    if (tag == tn_divr) {
        type = &real_type;
    } else if (tag >= tn_in && tag <= tn_le) {
        type = &bool_type;
    } else if (left && right && right->type && right->type->tag == tp_set
	       && left->type && left->type->tag == tp_set)
    {
	set_tp* ltype = (set_tp*)left->type->get_typedef();
	set_tp* rtype = (set_tp*)right->type->get_typedef();
	type = (ltype->card() < rtype->card()) ? ltype : rtype;
    } else if (left && right && left->type && right->type &&
	       (left->type->tag == tp_real || right->type->tag == tp_real))
    {
        type = &real_type;
    } else if (left && right && left->type && right->type &&
	       (right->type->tag == tp_string || right->type->tag == tp_char))
    {
        type = &varying_string_type;
    }
}

static char* cmp_op[] = { "==", "!=", ">", ">=", "<", "<=" };
static char* rcmp_op[] = { "==", "!=", "<", "<=", ">", ">=" };

#define CMP_OP(c) cmp_op[(c)-tn_eq]
#define RCMP_OP(c) rcmp_op[(c)-tn_eq]

void op_node::translate(int)
{
    f_tkn = l_tkn = op;

    if (right && left && right->type && left->type && right->type->tag == tp_set) {
        if (left->type->tag == tp_set) {
            set_tp* ltype = (set_tp*)left->type->get_typedef();
            set_tp* rtype = (set_tp*)right->type->get_typedef();
            left->type = right->type =
                (ltype->card() < rtype->card()) ? ltype : rtype;
        } else {
            right->type = new set_tp(left->type);
        }
    }

    if (left) {
        left->translate(ctx_value);
        f_tkn = left->f_tkn;
    }
    if (right) {
        right->translate(ctx_value);
        l_tkn = right->l_tkn;
    }
    switch(tag) {
      case tn_mod:
        op->set_trans("%");
        break;
      case tn_div:
        op->set_trans("/");
        break;
      case tn_divr:
        op->set_trans("/");
	if (left->type && left->type->tag != tp_real &&
	    right->type && right->type->tag != tp_real)
        {
	    f_tkn = left->f_tkn->prepend("(real)(");
	    left->l_tkn->append(")");
	}
        break;
      case tn_and:
        op->set_trans((!force_logical && ((left->type && left->type->tag != tp_bool) ||
										  (right->type && right->type->tag != tp_bool) || nological))
					  ? "&" : "&&");
		// no break
      case tn_binand:
		if (parent_tag != tn_group && parent_tag != tn_and) {
			f_tkn = left->f_tkn->prepend("(");
			l_tkn = right->l_tkn->append(")");
		}
	break;
      case tn_xor:
        op->set_trans("^");
	if (parent_tag != tn_group && parent_tag != tn_xor) {
	    f_tkn = left->f_tkn->prepend("(");
	    l_tkn = right->l_tkn->append(")");
	}
	break;
      case tn_let:
	op->set_trans("=");
	break;
      case tn_shr:
	if (parent_tag != tn_group) {
	    f_tkn = left->f_tkn->prepend(left->type &&
			left->type->get_typedef() == &longint_type
			    ? "((unsigned long)" : "((cardinal)");
	    l_tkn = right->l_tkn->append(")");
	} else {
	    f_tkn = left->f_tkn->prepend(left->type &&
			left->type->get_typedef() == &longint_type
			    ? "(unsigned long)" : "(cardinal)");
	}
	op->set_trans(">>");
	break;
      case tn_shl:
	if (parent_tag != tn_group) {
	    f_tkn = left->f_tkn->prepend("(");
	    l_tkn = right->l_tkn->append(")");
	}
	op->set_trans("<<");
	break;
      case tn_or:
	if (parent_tag != tn_group && parent_tag != tn_or) {
	    f_tkn = left->f_tkn->prepend("(");
	    l_tkn = right->l_tkn->append(")");
	}
		// no break
	  case tn_binor:
	op->set_trans((!force_logical && ((left->type && left->type->tag != tp_bool) ||
									  (right->type && right->type->tag != tp_bool) ||
									  nological)) ? "|" : "||");
        break;
      case tn_in:
        token::disable(left->l_tkn->next, right->f_tkn->prev);
	if (language_c) {
            f_tkn = left->f_tkn->prepend(
		        short_set && ((set_tp*)right->type)->is_short_set()
                        ? "INSET(" : "inset(");
	    left->l_tkn->append(", ");
	    l_tkn = right->l_tkn->append(")");
	} else {
	    left->f_tkn->move(right->f_tkn, right->l_tkn);
	    if (right->tag==tn_add || right->tag==tn_sub || right->tag==tn_mul){
		f_tkn = right->f_tkn->prepend("(");
		right->l_tkn->append(")");
	    } else {
		f_tkn = right->f_tkn;
	    }
	    left->f_tkn->prepend(".has(");
	    l_tkn = left->l_tkn->append(")");
	}
        break;
      case tn_add:
      case tn_sub:
      case tn_mul:
        if (left->type && left->type->tag == tp_set) {
	    if (language_c) {
		if (short_set && ((set_tp*)type)->is_short_set()) {
		    f_tkn = left->f_tkn->prepend(tag == tn_add
						 ? "JOIN(" : tag == tn_sub
						 ? "DIFFERENCE("
						 : "INTERSECT(");
		} else {
		    f_tkn = left->f_tkn->prepend(tag == tn_add
						 ? "join(" : tag == tn_sub
						 ? "difference("
						 : "intersect(");
		}
		l_tkn = right->l_tkn->append(")");
		token::disable(left->l_tkn->next, right->f_tkn->prev);
		left->l_tkn->append(", ");
	    }
	} else if (!language_c) {
	    if (left->type
		&& (left->type->tag == tp_string || left->type->tag == tp_char))
	    {
		f_tkn = left->f_tkn->prepend("string(");
		left->l_tkn->append(")");
	    }
	}
	break;
      case tn_eq:
      case tn_ne:
      case tn_gt:
      case tn_ge:
      case tn_lt:
      case tn_le:
	if (unsigned_comparison && left->type && right->type &&
	    (left->type->tag == tp_range || right->type->tag == tp_range ||
	     left->type->tag == tp_enum || right->type->tag == tp_enum))
        {
	    range_tp* ltype = (range_tp*)left->type->get_typedef();
	    range_tp* rtype = (range_tp*)right->type->get_typedef();

	    if (((ltype->tag == tp_range && ltype->min_value >= 0) ||
		 ltype->tag == tp_enum) &&
		((rtype->tag == tp_range && rtype->min_value < 0) ||
		 (rtype->tag == tp_integer && !(right->flags & tn_is_const))))
	    {
		if (rtype->tag == tp_integer) {
		    right->f_tkn->prepend("(cardinal)");
		}
		else if (ltype->tag == tp_enum || rtype->size <= ltype->size)
		{
		    right->f_tkn->prepend(rtype->size == 1 ? "(unsigned char)":
					  rtype->size == 2 ? "(unsigned short)"
					  : "(unsigned)");
		}
	    } else if (((rtype->tag == tp_range && rtype->min_value >= 0) ||
			rtype->tag == tp_enum) &&
		       ((ltype->tag == tp_range && ltype->min_value < 0) ||
			(ltype->tag == tp_integer && !(left->flags & tn_is_const))))
	    {
		if (ltype->tag == tp_integer) {
		    f_tkn = left->f_tkn->prepend("(cardinal)");
		}
                else if (rtype->tag == tp_enum || ltype->size <= rtype->size)
		{
		    f_tkn = left->f_tkn->prepend(
					  ltype->size == 1 ? "(unsigned char)":
					  ltype->size == 2 ? "(unsigned short)"
					  : "(unsigned)");
		}
	    }
	}
	if (language_c && left->type && right->type) {
	    switch(left->type->tag) {
	      case tp_string:
	      case tp_record:
	      case tp_array:
	      case tp_dynarray:
		if (right->type->tag == tp_char) {
		    f_tkn = left->f_tkn->prepend("*");
		} else {
		    token::disable(left->l_tkn->next, right->f_tkn->prev);
		    left->l_tkn->append(", ");
		    if (left->is_parameter()) {
			f_tkn = left->f_tkn->prepend("memcmp(");
			if (left->type->tag == tp_record) {
			    left->f_tkn->prepend("&");
			    right->f_tkn->prepend("&");
			}
			if (left->type->name != NULL) {
			    l_tkn = right->l_tkn->append(
					   dprintf(", sizeof(%s)) %s 0",
					       left->type->name, CMP_OP(tag)));
			} else {
			    l_tkn = right->l_tkn->append(", ")
				                ->append("*sizeof(*");
			    ((array_tp*)left->type->get_typedef())->
				insert_length(l_tkn);
			    l_tkn = l_tkn->append(dprintf(")) %s 0",
							  CMP_OP(tag)));
			    l_tkn->copy(left->f_tkn, left->l_tkn);
			}
		    } else if (left->type->tag == tp_string) {
			token::swap(left->f_tkn, left->l_tkn,
				    right->f_tkn, right->l_tkn);
			f_tkn = right->f_tkn->prepend("arrcmp(");
			l_tkn = left->l_tkn->append(dprintf(") %s 0",
							    RCMP_OP(tag)));
		    } else {
			if (left->type->tag == tp_record) {
			    f_tkn = left->f_tkn->prepend("reccmp(");
			} else {
			    f_tkn = left->f_tkn->prepend("arrcmp(");
			}
			l_tkn = right->l_tkn->append(dprintf(") %s 0",
							     CMP_OP(tag)));
		    }
		    return;
		}
	      case tp_char:
		if (right->type && right->type->is_array()) {
		    right->f_tkn->prepend("*");
		}
		break;
	      case tp_set:
		token::disable(left->l_tkn->next, right->f_tkn->prev);
		left->l_tkn->append(", ");

		if (short_set && left->type && ((set_tp*)left->type)->is_short_set()) {
		    switch (tag) {
		      case tn_eq:
			f_tkn = left->f_tkn->prepend("EQUIVALENT(");
			l_tkn = right->l_tkn->append(")");
			break;
		      case tn_ne:
			f_tkn = left->f_tkn->prepend("!EQUIVALENT(");
			l_tkn = right->l_tkn->append(")");
			break;
		      case tn_le:
			f_tkn = left->f_tkn->prepend("SUBSET(");
			l_tkn = right->l_tkn->append(")");
			break;
		      case tn_ge:
			token::swap(left->f_tkn, left->l_tkn,
				    right->f_tkn, right->l_tkn);
			f_tkn = right->f_tkn->prepend("SUBSET(");
			l_tkn = left->l_tkn->append(")");
			break;
		    }
		} else {
		    switch (tag) {
		      case tn_eq:
			f_tkn = left->f_tkn->prepend("equivalent(");
			l_tkn = right->l_tkn->append(")");
			break;
		      case tn_ne:
			f_tkn = left->f_tkn->prepend("!equivalent(");
			l_tkn = right->l_tkn->append(")");
			break;
		      case tn_le:
			f_tkn = left->f_tkn->prepend("subset(");
			l_tkn = right->l_tkn->append(")");
			break;
		      case tn_ge:
			token::swap(left->f_tkn, left->l_tkn,
				    right->f_tkn, right->l_tkn);
			f_tkn = right->f_tkn->prepend("subset(");
			l_tkn = left->l_tkn->append(")");
			break;
		    }
		}
		return;
	    }
	} else { // language C++
	    if (left->type && right->type
		&& (right->type->tag == tp_array
		 || right->type->tag == tp_varying_string
		 || right->type->tag == tp_dynarray)
		&& (left->type->tag == tp_string
		    || left->type->tag == tp_char))
	    {
		token::swap(left->f_tkn, left->l_tkn,
			    right->f_tkn, right->l_tkn);
		f_tkn = right->f_tkn;
		l_tkn = left->l_tkn;
		op->set_trans(RCMP_OP(tag));
		return;
	    }
	}
	op->set_trans(CMP_OP(tag));
        break;
      case tn_not:
        op->set_trans(force_logical || (right->type && right->type->tag == tp_bool) ? "!" : "~");
        break;
	  case tn_binnot:
		break;
    }
    if ((unsigned(tag - tn_add) <= tn_div - tn_add) && type && type->tag == tp_longint)
    {
	if (left->type && left->type->tag != tp_longint) {
	    f_tkn = f_tkn->prepend("longint(");
	    left->l_tkn->append(")");
	} else if (right->type && right->type->tag != tp_longint) {
	    right->f_tkn->prepend("longint(");
	    l_tkn = l_tkn->append(")");
	}
    }
}

fcall_node::fcall_node(expr_node* fptr, token* lpar, expr_node* args,
		       token* rpar)
: expr_node(tn_fcall)
{
    CONS4(fptr, lpar, args, rpar);
}

void fcall_node::attrib(int ctx)
{
    if (fptr->tag == tn_atom && ((atom_expr_node*)fptr)->tkn->tag != TKN_IDENT)
    {
	if (args) {
	    args->attrib(ctx_value);
	}
        switch (((atom_expr_node*)fptr)->tkn->tag) {
	  case TKN_NEW:
	    type = new ref_tp(args->type);
	    if (turbo_pascal && args->next != NULL) {
            expr_node *arg = args->next;
            if (args->type->is_reference()) {
                tpexpr* bt =
                    ((ref_tp*)args->type->get_typedef())->base_type;
                if (bt->tag == tp_object) {
                    object_tp* obj = (object_tp*)bt->get_typedef();
                    b_ring::push(obj);
                    arg->attrib(ctx_value);
                    arg = arg->next;
                    b_ring::pop(obj);
                }
            }
            while (arg != NULL) {
                arg->attrib(ctx_value);
                arg = arg->next;
            }
	    }
	    break;
	  case TKN_DISPOSE:
	    if (turbo_pascal && args->next != NULL) {
		if (args->type->is_reference()) {
		    tpexpr* bt =
			((ref_tp*)args->type->get_typedef())->base_type;
		    if (bt->tag == tp_object) {
                object_tp* obj = (object_tp*)bt->get_typedef();
                b_ring::push(obj);
                args->next->attrib(ctx_value);
                b_ring::pop(obj);
		    }
		}
	    }
	    break;
	  case TKN_REF:
	    type = new ref_tp(args->type);
	    break;
	  case TKN_PRED:
	    type = args->type;
	    if (args->flags & symbol::f_const) {
		flags |= tn_is_const;
		value = args->value - 1;
	    }
	    break;
	  case TKN_SUCC:
	    type = args->type;
	    if (args->flags & symbol::f_const) {
		flags |= tn_is_const;
		value = args->value + 1;
	    }
	    break;
	  case TKN_HALT:
	    if (turbo_pascal) {
		((atom_expr_node*)fptr)->tkn->set_trans("exit");
	    } else {
		goto normal_call;
	    }
	    //nobreak;
	  default:
	    if (args != NULL) {
		for (expr_node* expr=args->next; expr != NULL; expr=expr->next)
		{
		    expr->attrib(ctx_value);
		}
	    }
	}
	return;
    }
  normal_call:
    fptr->attrib(ctx_apply);
    if (fptr->type != NULL) {
	if (fptr->type->tag == tp_proc) {
	    proc_tp* prc = (proc_tp*)fptr->type->get_typedef();
	    type = prc->res_type;
	    param_spec* p = prc->params;
	    prc->add_caller(curr_proc);

	    for (expr_node* e = args; e != NULL; e = e->next) {
		if (p != NULL) {
		    e->attrib(p->var->type->tag == tp_proc
			      ? ctx_procptr : (p->var->flags & symbol::f_var_param)
			      ? ctx_lvalue : ctx_value);
		    if (p->var->type->tag == tp_set) {
			e->type = p->var->type->get_typedef();
		    }
		    p = p->next;
		} else {
		    e->attrib(ctx_value);
		}
	    }
	    if (language_c && type != NULL && type->tag == tp_array
		&& ctx != ctx_rvalue)
	    {
		temp = curr_proc->add_temp(type);
	    }
	} else { // constant array or record constructor

	    type = fptr->type;
	    int expr_ctx = (type->tag == tp_record || type->tag == tp_object
			    || (type->tag == tp_array
				&& (ctx == ctx_constant || language_c)))
		? ctx_record : ctx_value;

	    if (type->tag != tp_array && type->tag != tp_record && type->tag != tp_object
		&& !(fptr->tag == tn_atom
		     && ((atom_expr_node*)fptr)->var != NULL
		     && ((atom_expr_node*)fptr)->var->tag == symbol::s_type))
	    {
		warning(lpar, "function not defined");
	    }
	    for (expr_node* e = args; e != NULL; e = e->next) {
		e->attrib(expr_ctx);
	    }
	}
    }
}

void fcall_node::translate(int ctx)
{
    l_tkn = rpar;

    if (fptr->tag == tn_atom && ((atom_expr_node*)fptr)->tkn->tag != TKN_IDENT)
    {
	f_tkn = ((atom_expr_node*)fptr)->tkn;

        switch(((atom_expr_node*)fptr)->tkn->tag) {
	  case TKN_NEW:
	    if (language_c) {
		args->translate(ctx_value);
		args->f_tkn->set_pos(f_tkn);
		f_tkn->disable();
		lpar->disable();
		if (args->next != NULL) {
		    token::remove(args->l_tkn->next, rpar->prev);
		}
		if (args->type->is_reference()) {
		    tpexpr* bt=((ref_tp*)args->type->get_typedef())->base_type;
		    assert(bt->name != NULL);

		    rpar->set_trans(dprintf(" = (%s*)%s(%s))",
				    bt->name,
				    (bt->get_typedef()->flags & tp_need_init)
				    ? "calloc(1,sizeof" : "malloc(sizeof",
				    bt->name));
		}
	    } else {
		expr_node* expr = args;
		if (expr != NULL && expr->tag == tn_fcall
		    && expr->type != NULL && expr->type->tag == tp_object)
		{
		    (((fcall_node*)expr)->fptr)->translate(ctx_apply);
		    expr = ((fcall_node*)expr)->args;
		}
		while (expr != NULL) {
		    expr->translate(ctx_value);
		    expr = expr->next;
		}
		if (turbo_pascal) {
		    if (args->type->is_reference()) {
			tpexpr* cls = ((ref_tp*)args->type->get_typedef())->base_type;
			char* cls_name;
			if (cls != NULL && cls->name != NULL) {
			    cls_name = cls->name;
			} else {
			    cls_name = args->type->name;
			}
			if (ctx == ctx_rvalue) {
			    if (args->next != NULL) {
				token::remove(lpar, args->next->f_tkn->prev);
				f_tkn->set_trans(dprintf("(new %s)->",
							 cls_name));
				rpar->disable();
			    } else {
				token::remove(lpar, rpar);
				l_tkn = f_tkn;
				f_tkn->set_trans(dprintf("new %s", cls_name));
			    }
			} else {
			    args->f_tkn->set_pos(f_tkn);
			    f_tkn->disable();
			    lpar->disable();
			    if (args->next != NULL) {
				token::disable(args->l_tkn->next,
					       args->next->f_tkn->prev);
				args->l_tkn->append(dprintf(" = (new %s)->",
							    cls_name));
				rpar->disable();
			    } else {
				token::disable(args->l_tkn->next, rpar);
				args->l_tkn->append(dprintf(" = new %s",
							    cls_name));
			    }
			}
		    } else {
			lpar->set_trans(" ");
			rpar->disable();
			warning(f_tkn, "Unknown type for new operator\n");
		    }
		} else {
		    args->f_tkn->set_pos(f_tkn);
		    f_tkn->disable();
		    lpar->disable();
		    if (args->next != NULL) {
			token::remove(args->l_tkn->next, rpar->prev);
		    }
		    rpar->set_trans(" = new ");
		    if (args->type->is_reference()) {
			tpexpr* bt=((ref_tp*)args->type->get_typedef())->base_type;
			assert(bt->name != NULL);
			l_tkn = rpar->append(bt->name);
		    }
		}
	    }
	    break;
	  case TKN_DISPOSE:
	    args->translate(ctx_value);
	    if (language_c) {
		f_tkn->set_trans("free");
	    } else {
		f_tkn->set_trans("delete ");
		lpar->disable();
		rpar->disable();
		if (turbo_pascal) {
		    if (args->next) {
			args->next->translate(ctx_value);
			token::remove(args->l_tkn->next, args->next->f_tkn->prev);
			args->l_tkn->append("->");
		    }
		}
	    }
	    break;
	  case TKN_REF:
	    args->translate(ctx_lvalue);
	    f_tkn->set_trans("&");
	    lpar->disable();
	    rpar->disable();
	    break;
	  case TKN_PRED:
	  case TKN_SUCC:
	    assert(args->type->name != NULL);
	    args->translate(ctx_rvalue);
	    lpar->append(dprintf("%s,", args->type->name));
	    break;
	  case TKN_INC:
	    args->translate(ctx_lvalue);
	    token::disable(f_tkn, lpar);
	    args->f_tkn->set_pos(f_tkn);
	    if (args->next) {
		args->next->translate(ctx_rvalue);
		token::disable(args->l_tkn->next, args->next->f_tkn->prev);
		args = args->next;
		args->f_tkn->prepend(" += ");
	    } else {
		args->l_tkn->append(" += 1");
	    }
	    rpar->disable();
	    break;
	  case TKN_DEC:
	    args->translate(ctx_lvalue);
	    args->f_tkn->set_pos(f_tkn);
	    token::disable(f_tkn, lpar);
	    if (args->next) {
		args->next->translate(ctx_rvalue);
		token::disable(args->l_tkn->next, args->next->f_tkn->prev);
		args = args->next;
		args->f_tkn->prepend(" -= ");
	    } else {
		args->l_tkn->append(" -= 1");
	    }
	    rpar->disable();
	    break;
	}
	return;
    }

    fptr->translate(ctx_apply);
    f_tkn = fptr->f_tkn;
    l_tkn = rpar;

    if (fptr->type && fptr->type->tag == tp_proc) {
	proc_tp* prc = (proc_tp*)fptr->type->get_typedef();
        param_spec* p = prc->params;
	tpexpr* prev_param_type = NULL;

        for (expr_node* e = args; e != NULL; e = e->next) {
	    if (p != NULL) {
                e->translate(p->var->type->tag == tp_proc ? ctx_procptr
			     : (language_c && p->var->tag == symbol::s_ref)
			     ? ctx_access : ctx_value);
		if (p->var->type->is_array() && e->type != NULL && e->type->tag == tp_char) {
		    if (e->tag == tn_char) {
			char* s = ((string_node*)e)->value_tkn->out_text;
			if (*s == '\'') {
			    *s = '"';
			    s += strlen(s) - 1;
			    *s = '"';
			}
			e->type = &string_type;
		    } else {
			if (!turbo_pascal) {
			    warning(e->f_tkn, "assignment of charater constant to array");
			}
		    }
		}
		if (p->var->type->tag == tp_string) {
		    if (e->type->tag == tp_array || e->type->tag == tp_dynarray)
		    {
			e->f_tkn->prepend("lpsz(");
			if (language_c) {
			    ((array_tp*)e->type->get_typedef())
				->insert_dimensions(e);
			}
			e->l_tkn->append(")");
		    }
		} else if (p->var->type->tag == tp_array
			   && !language_c && prc->is_extern_c
			   && (e->type->tag == tp_array
			       || e->type->tag == tp_dynarray))
		{
		    e->l_tkn->append(".body()");
		} else {
		    if (language_c) {
			if (p->var->type->tag == tp_dynarray) {
			    if (prev_param_type != p->var->type) {
				if (!e->type->is_array())
				{
				    warning(e->f_tkn, "passing non-aray object"
					    " as conformant array parameter");
				} else {
				    // push on stack bounds of array
				    if (e->type->tag == tp_string) {
					e->f_tkn->prepend("array(");
					e->l_tkn->append(")");
				    } else {
					((array_tp*)e->type->get_typedef())->
					    insert_dimensions(e, (array_tp*)
					        p->var->type->get_typedef());
				    }
				}
				prev_param_type = p->var->type;
			    }
			} else if (p->var->tag == symbol::s_ref
				   && e->tag != tn_address)
			{
			    e->f_tkn->prepend("&");
			}
		    } else { // language C++
			if (!prc->is_extern_c
			    && p->var->type->tag == tp_array
			    && e->type->tag == tp_string)
			{
			    if (p->var->type->name == NULL) {
				e->f_tkn->prepend("as_array(");
				e->l_tkn->append(")");
			    } else {
				e->f_tkn->prepend(dprintf("as(%s,",
							  p->var->type->name));
				e->l_tkn->append(")");
			    }
			} else if (p->var->type->tag == tp_any
				   || (p->var->tag == symbol::s_ref
				       && prc->is_extern_c))
                        {
			    e->f_tkn->prepend("&");
			}
		    }
		}
		p = p->next;
            } else {
                e->translate(ctx_value);
            }
        }
	if (language_c) {
	    // push default values of skipped parameters
	    while (p != NULL) {
		rpar->prepend(", 0");
		p = p->next;
	    }
	    if (type != NULL && type->tag == tp_array) {
		if (ctx == ctx_rvalue) {
		    f_tkn->set_pos(assign_node::stmt->lval->f_tkn);
		    lpar->append(", ")->move(assign_node::stmt->lval->f_tkn,
					     assign_node::stmt->lval->l_tkn);
		    tag = tn_retarr;
		} else {
		    lpar->append(dprintf("%s, ", temp));
		    f_tkn = f_tkn->prepend("*");
		}
	    }
	}

        token* rest = rpar->prev_relevant();

        for (param_spec* prm = prc->extra_params;
	     prm != NULL;
	     prm = prm->next)
        {
	    if (prm->var->flags & symbol::f_static) continue;

	    rest = rest->append(", ");
	    if (language_c && prm->var->tag != symbol::s_ref
		&& (prm->var->tag != symbol::s_const
		    || !prm->var->type->is_scalar())
		&& prm->var->ring == curr_proc
		&& !prm->var->type->is_array())
	    {
		rest = rest->append("&");
	    }
	    rest = rest->append(prm->var->out_name->text);
        }

    } else if (type != NULL && (type->tag == tp_record || type->tag == tp_object
	       || (type->tag == tp_array
		   && (language_c || ctx == ctx_constant))))
    {
	if (hp_pascal) {
	    if (language_c) {
		f_tkn = fptr->f_tkn->prepend("(");
		fptr->l_tkn->append("*)");
	    }
	} else {
	    token::remove(fptr->f_tkn, fptr->l_tkn);
	    f_tkn = lpar;
	    if (language_c || type->tag == tp_record || type->tag == tp_object) {
		lpar->set_trans("{");
		rpar->set_trans("}");
	    } else {
		if (args->tag != tn_string || args->next != NULL) {
		    lpar->set_trans("{{");
		    rpar->set_trans("}}");
		}
	    }
	    for (expr_node* e = args; e != NULL; e = e->next) {
		e->translate(ctx_record);
	    }
	    if (ctx != ctx_constant) {
		assert(type->name != NULL);

		static int n_const;
		token *t = lpar->prev;
		char* const_name = dprintf("%s_const%d", type->name, ++n_const);

		assert(global_func_decl_level != NULL);

		global_func_decl_level->move(lpar, rpar);
		lpar->prepend(dprintf("const %s %s = ", type->name, const_name));
		rpar->append(";\n\n");

		f_tkn = l_tkn = t->append(const_name);
	    }
	}
    } else { // undefined function call
	if (fptr->type && fptr->type->tag >= tp_any &&
	    (fptr->type->tag < tp_proc || fptr->type->tag == tp_ref || fptr->type->tag == tp_fwd_ref))
	{
	    // type conversion
	    f_tkn = fptr->f_tkn->prepend("(");
	    fptr->l_tkn->append(")");
	}
	for (expr_node* e = args; e != NULL; e = e->next) {
	    e->translate(ctx_value);
	}
	if (!language_c && type != NULL && type->tag == tp_array) {
	    fptr->l_tkn->append("::make");
	}
    }
}


skipped_node::skipped_node(token* comma) : expr_node(tn_skip)
{
    this->comma = comma;
}

void skipped_node::attrib(int)
{
    type = &void_type;
}

void skipped_node::translate(int)
{
    l_tkn = f_tkn = comma->append(" 0");
}


loophole_node::loophole_node(token* t_loophole, token* t_lpar, tpd_node* tpd,
			     token* t_comma, expr_node *expr, token* t_rpar)
  : expr_node(tn_loophole)
{
    CONS6(t_loophole, t_lpar, tpd, t_comma, expr, t_rpar);
}

void loophole_node::attrib(int ctx)
{
    tpd->attrib(ctx);
    expr->attrib(ctx_access);
    type = tpd->type;
}

void loophole_node::translate(int ctx)
{
    f_tkn = t_lpar;
    l_tkn = t_rpar;
    tpd->translate(ctx);
    expr->translate(ctx_access);
    t_loophole->disable();
    if (expr->tag == tn_address) {
	tpd->l_tkn->append("*)");
	f_tkn = f_tkn->prepend("*");
    }
    else if (language_c && tpd->type->tag == tp_integer
	    && expr->type->tag == tp_set
	    && (!short_set || !((set_tp*)expr->type->get_typedef())->is_short_set()))
    {
	token::disable(t_lpar, tpd->l_tkn);
	expr->l_tkn->append(".setarray[0]");
    }
    else
    {
	tpd->l_tkn->append(")");
    }
    t_rpar->disable();
    t_comma->disable();
}


field_init_node::field_init_node(token* t_field,token* t_coln,expr_node* value)
{
    CONS3(t_field, t_coln, value);
    next = NULL;
}

void field_init_node::attrib(tpexpr* record_type)
{
    int ctx = ctx_constant;
    if (record_type != NULL && record_type->tag != tp_void) {
	symbol* s = ((record_tp*)record_type)->shallow_search(t_field);
	if (s == NULL) {
	    warning(t_field, "Field '%s' is not found in record %s\n",
		    t_field->in_text,
		    record_type->name ? record_type->name : "");
	} else {
	    value->type = s->type;
	    ctx = s->type->tag == tp_record || s->type->tag == tp_object ? ctx_record
		: s->type->is_array() ? ctx_array : ctx_constant;
	}
    }
    value->attrib(ctx);
}

void field_init_node::translate(int)
{
    value->translate(ctx_constant);
    f_tkn = value->f_tkn;
    l_tkn = value->l_tkn;
    token::disable(t_field, f_tkn->prev);
    token* sep = l_tkn->next_relevant();
    if (sep->tag == TKN_SEMICOLON) {
	sep->set_trans(",");
    }
}

record_constant_node::record_constant_node(token* lpar, field_init_node* flist,
					   token* rpar)
: expr_node(tn_record_const)
{
    CONS3(lpar, flist, rpar);
}

void record_constant_node::attrib(int)
{
    tpexpr* record_type = type;
    if (record_type != NULL && (record_type->tag == tp_record || record_type->tag == tp_object)) {
	record_type = record_type->get_typedef();
    }
    for (field_init_node* val = flist; val != NULL; val = val->next) {
	val->attrib(record_type);
    }
}

void record_constant_node::translate(int ctx)
{
    f_tkn = lpar;
    l_tkn = rpar;
    lpar->set_trans("{");
    rpar->set_trans("}");
    for (field_init_node* val = flist; val != NULL; val = val->next) {
	val->translate(ctx);
    }
}


expr_group_node::expr_group_node(token* lpar, expr_node* expr, token* rpar)
: expr_node(tn_group)
{
    CONS3(lpar, expr, rpar);
}

static expr_node* aggregate_constant(expr_node* expr, symbol* component)
{
    if (component != NULL) {
	if (component->next != NULL) {
	    expr = aggregate_constant(expr, component->next);
	}
    }
    if (expr != NULL) {
	int ctx = ctx_constant;
	if (component != NULL && component->type != NULL) {
	    expr->type = component->type;
	    ctx = component->type->tag == tp_record || component->type->tag == tp_object ? ctx_record
		: component->type->is_array() ? ctx_array : ctx_constant;
	}
	expr->attrib(ctx);
	return expr->next;
    }
    return NULL;
}

void expr_group_node::attrib(int ctx)
{
    this->ctx = ctx;
    if (type != NULL) {
	if (type->tag == tp_record || type->tag == tp_object) {
	    for (expr_node* e = aggregate_constant(expr,
				    ((record_tp*)type->get_typedef())->syms);
		 e != NULL;
		 e = e->next)
	    {
		e->attrib(ctx_constant);
	    }
	    return;
	} else if (type->is_array()) {
	    tpexpr* elem_type = ((array_tp*)type->get_typedef())->elem_type;
	    ctx = (elem_type->tag == tp_record || elem_type->tag == tp_object) ? ctx_record
		: (elem_type->is_array()) ? ctx_array : ctx_constant;
	    for(expr_node* e = expr; e != NULL; e = e->next) {
		e->type = elem_type;
		e->attrib(ctx);
	    }
	    return;
	}
    }
    for(expr_node* e = expr; e != NULL; e = e->next) {
	e->attrib(ctx);
    }
    type = expr->type;
}


void expr_group_node::translate(int)
{
    f_tkn = lpar;
    l_tkn = rpar;
    if (ctx == ctx_record || (language_c && ctx == ctx_array)) {
	// constructor of record
        lpar->set_trans("{");
        rpar->set_trans("}");
    } else if (!language_c && ctx == ctx_array) {
        lpar->set_trans("{{");
        rpar->set_trans("}}");
    }
    for (expr_node* e = expr; e != NULL; e = e->next) {
        e->translate(ctx_constant);
    }
}


write_list_node::write_list_node(token* lpar, write_param_node* vals,
				 token* rpar)
{
    CONS3(lpar, vals, rpar);
}

void write_list_node::attrib(int)
{
    for(expr_node* prm = vals; prm != NULL; prm = prm->next)
    {
        prm->attrib(ctx_value);
    }
}


void write_list_node::translate(int)
{
    f_tkn = lpar;
    l_tkn = rpar;

    for(expr_node* prm = vals; prm != NULL; prm = prm->next)
    {
        prm->translate(ctx_value);
    }
}


write_param_node::write_param_node(expr_node* val,
		     token* t_coln1, expr_node* width,
		     token* t_coln2, expr_node* prec)
: expr_node(tn_wrp)
{
    CONS5(val, t_coln1, width, t_coln2, prec);
}

void write_param_node::attrib(int ctx)
{

    val->attrib(ctx);
    type = val->type;
    if (width) {
	width->attrib(ctx_value);
	if (prec) {
	    prec->attrib(ctx_value);
        }
    }
}

static char* make_fmt_string(char* src) {
    char buf[65536];
    char* dst = buf;
    if (strcmp(src, "'\"'") == 0) return "\\\"";
    src += 1; // skip '"'
    while (*src != '\0') {
	if (*src == '%') *dst++ = '%';
	*dst++ = *src++;
    }
    *--dst = '\0'; // skip '"'
    assert(dst < buf + sizeof(buf));
    return strdup(buf);
}

void write_param_node::translate(int ctx)
{
    val->translate(ctx);
    f_tkn = val->f_tkn;
    l_tkn = val->l_tkn;

    if (language_c) {

	if (write_format == NULL) return;
	n_write_params += 1;

	char fmt = '?';
	switch(val->type->tag) {
	  case tp_string:
	    if (width == NULL && val->tag == tn_string) {
		write_format = dprintf("%s%s", write_format,
		    make_fmt_string(((string_node*)val)->value_tkn->out_text));
		token* prev = f_tkn->prev_relevant();
		if (prev->tag == TKN_COMMA) {
		    prev = prev->prev_relevant();
		    token::disable(prev->next, l_tkn);
		} else {
		    token* next = l_tkn->next_relevant();
		    if (next->tag == TKN_COMMA) {
			next = next->next_relevant();
		    }
		    token::disable(f_tkn, next->prev);
		}
		n_write_params -= 1;
		return;
	    }
#if 1
	    fmt = 'z';
#else
	    fmt = 's';
	    f_tkn = val->f_tkn->prepend("array(");
	    val->l_tkn->append(")");
#endif
	    break;
	  case tp_array:
	    fmt = 's';
	    ((array_tp*)val->type->get_typedef())->insert_dimensions(val);
	    break;
	  case tp_char:
	    if (width == NULL && val->tag == tn_char) {
		write_format = dprintf("%s%s", write_format,
		    make_fmt_string(((string_node*)val)->value_tkn->out_text));
		token* prev = f_tkn->prev_relevant();
		if (prev->tag == TKN_COMMA) {
		    prev = prev->prev_relevant();
		    token::disable(prev->next, l_tkn);
		} else {
		    token* next = l_tkn->next_relevant();
		    if (next->tag == TKN_COMMA) {
			next = next->next_relevant();
		    }
		    token::disable(f_tkn, next->prev);
		}
		n_write_params -= 1;
		return;
	    }
	    fmt = 'c';
	    break;
	  case tp_bool:
	    fmt = 'b';
	    break;
	  case tp_integer:
	  case tp_range:
	    fmt = 'i';
	    break;
	  case tp_real:
	    fmt = 'f';
	    break;
	  default:
	    warning(val->f_tkn, "invalid parameter for write operator");
	}
	if (width) {
	    width->translate(ctx_value);
	    t_coln1->set_trans(",");
	    if (prec) {
		prec->translate(ctx_value);
		if (width->is_const_literal() && prec->is_const_literal()) {
		    write_format = dprintf("%s%%%d.%d%c", write_format,
					   width->value, prec->value, fmt);
		    token::disable(val->l_tkn->next, prec->l_tkn);
		} else {
		    t_coln2->set_trans(",");
		    write_format = dprintf("%s%%*.*%c", write_format, fmt);
		}
	    } else {
		if (width->is_const_literal()) {
		    write_format = dprintf("%s%%%d%c", write_format,
					   width->value, fmt);
		    token::disable(val->l_tkn->next, width->l_tkn);
		} else {
		    write_format = dprintf("%s%%*%c", write_format, fmt);
		}
	    }
	} else {
	    write_format = dprintf("%s%%%c", write_format, fmt);
	}

    } else { // language C++

	if (ctx == ctx_toascii) {
	    if (width) {
		width->translate(ctx_value);
		t_coln1->set_trans(",");
		l_tkn = width->l_tkn;
		if (prec) {
		    prec->translate(ctx_value);
		    t_coln2->set_trans(",");
		    l_tkn = prec->l_tkn;
		}
	    }
	} else {
	    if (val->type->tag == tp_bool) {
		f_tkn = val->f_tkn->prepend("btos(");
		l_tkn = val->l_tkn->append(")");
	    }
	    if (width) {
		width->translate(ctx_value);
		f_tkn = f_tkn->prepend("format(");
		t_coln1->set_trans(",");
		if (prec) {
		    t_coln2->set_trans(",");
		    prec->translate(ctx_value);
		    l_tkn = prec->l_tkn->append(")");
		} else {
		    l_tkn = width->l_tkn->append(")");
		}
	    }
	}
    }
}


//
// Declaration
//

label_decl_part_node::label_decl_part_node(token* t_label,
					   token_list* labels,
					   token* t_semi)
{
    CONS3(t_label, labels, t_semi);
}

void label_decl_part_node::attrib(int)
{
}

void label_decl_part_node::translate(int)
{
    token::remove(t_label, t_semi);
}

const_def_node* const_def_node::enumeration;

const_def_node::const_def_node(token* ident, token* equal,
			       expr_node* constant)
{
    CONS3(ident, equal, constant);
}

void const_def_node::attrib(int)
{
    constant->attrib(ctx_constant);
    sym = b_ring::add_cur(ident, symbol::s_const, constant->type);
    if (constant->flags & tn_is_const) {
	sym->flags |= symbol::f_const;
	sym->value = constant->value;
    }
    if (language_c && (sym->type->tag == tp_integer
		       || sym->type->tag == tp_char
		       || sym->type->tag == tp_set))
    {
	sym->out_name->flags |= nm_entry::macro;
    }
}

void const_def_node::translate(int)
{
    constant->translate(ctx_constant);
    if (curr_proc && curr_proc->make_all_constants_global
	&& !(sym->flags & symbol::f_static))
    {
	curr_proc->make_unique(sym);
    }
    sym->translate(ident);
    l_tkn = constant->l_tkn;
    token::disable(ident->next, constant->f_tkn->prev);
    if (language_c && (sym->type->tag == tp_integer
		       || sym->type->tag == tp_bool
		       || sym->type->tag == tp_char
		       || sym->type->tag == tp_set))
    {
	if (!do_not_use_enums && !(sym->flags & symbol::f_static) &&
	    (sym->type->tag == tp_integer ||  sym->type->tag == tp_bool))
	{
	    if (enumeration == NULL || (sym->flags & symbol::f_static)) {
		f_tkn = ident->prepend("enum { ");
		f_tkn->pos = curr_proc == NULL ? 0 : ident->pos;
	    } else {
		enumeration->l_tkn->set_trans(",");
		enumeration->l_tkn->prev_relevant()->disable();
	    }
	    equal->set_trans(" = ");
	    enumeration = this;
	    l_tkn = constant->l_tkn->append("}");
	    force_semicolon();
	} else {
	    enumeration = NULL;
	    token* t;
	    f_tkn = ident->prepend("#define ");
	    f_tkn->pos = 0;
	    equal->set_trans(" ");
	    if (curr_proc) {
		curr_proc->add_define(sym);
	    }
	    for (t = f_tkn->prev;
		 t->cat == CAT_WSPC && t->tag != TKN_LN;
		 t = t->prev);

	    if (t->tag != TKN_LN) {
		f_tkn = f_tkn->prepend("\n");
		f_tkn->tag = TKN_LN;
	    }
	    t = l_tkn->next_relevant();
	    if (t->tag == TKN_SEMICOLON) {
		t->set_trans("\n");
		t->tag = TKN_LN;
	    }
	}
    } else {
	f_tkn = ident->prepend(language_c ? "static const " : "const ");
	enumeration = NULL;
	if (constant->type->tag == tp_string) {
	    ident->prepend("char ");
	    ident->append("[]");
	} else {
	    constant->type->insert_before(ident);
	    ident->prepend(" ");
        }
	equal->set_trans(" = ");
	force_semicolon();
    }
    if (sym->flags & symbol::f_static) {
	assert(global_func_decl_level != NULL);
	global_func_decl_level->move_region(f_tkn, l_tkn);
	global_func_decl_level->prepend("\n");
	(new token(NULL, TKN_BEG_SHIFT, f_tkn->line, f_tkn->pos))
	    ->insert_b(f_tkn);
	(new token((char*)0, TKN_END_SHIFT))->insert_a(l_tkn);
    }
}

typed_const_def_node::typed_const_def_node(token* ident, token* coln,
					   tpd_node* tpd,
					   token* equal, expr_node* constant)
: const_def_node(ident, equal, constant)
{
    CONS2(coln, tpd);
}

void typed_const_def_node::attrib(int)
{
    tpd->attrib(ctx_constant);
    constant->type = tpd->type;
    constant->attrib(tpd->type->tag == tp_array
		     ? ctx_array : tpd->type->tag == tp_record || tpd->type->tag == tp_object
		     ? ctx_record : ctx_constant);

    sym = b_ring::add_cur(ident, symbol::s_const, constant->type);
    if (constant->flags & tn_is_const) {
	sym->flags |= symbol::f_const;
	sym->value = constant->value;
    }
}

void typed_const_def_node::translate(int)
{
    constant->translate(ctx_constant);
    tpd->translate(ctx_constant);
    if (curr_proc && curr_proc->make_all_constants_global
	&& !(sym->flags & symbol::f_static))
    {
	curr_proc->make_unique(sym);
    }
    sym->translate(ident);
    l_tkn = constant->l_tkn;
    f_tkn = ident->prepend(" ")->move(tpd->f_tkn, tpd->l_tkn)->prepend("const ");
    token::disable(ident->next, constant->f_tkn->prev);
    equal->set_trans(" = ");
    force_semicolon();

    if (sym->flags & symbol::f_static) {
	assert(global_func_decl_level != NULL);
	global_func_decl_level->move_region(f_tkn, l_tkn);
	global_func_decl_level->prepend("\n");
	(new token(NULL, TKN_BEG_SHIFT, f_tkn->line, f_tkn->pos))
	    ->insert_b(f_tkn);
	(new token((char*)0, TKN_END_SHIFT))->insert_a(l_tkn);
    }
}

const_def_part_node::const_def_part_node(token* t_const, const_def_node* list)
{
    CONS2(t_const, list);
}

void const_def_part_node::attrib(int ctx)
{
    for (decl_node* def = list; def != NULL; def = def->next) {
        def->attrib(ctx);
    }
}

void const_def_part_node::translate(int ctx)
{
    f_tkn = l_tkn = t_const;
    const_def_node::enumeration = NULL;
    for (decl_node* def = list; def != NULL; def = def->next) {
        def->translate(ctx);
	l_tkn = def->l_tkn;
    }
    t_const->disappear();
    if (ctx == ctx_block && curr_proc->make_all_constants_global) {
	// make type definition global
        global_func_decl_level->move_region(f_tkn, l_tkn);
	global_func_decl_level->prepend("\n\n");
        (new token(NULL, TKN_BEG_SHIFT, f_tkn->line,
		   f_tkn->next_relevant()->pos))->insert_b(f_tkn);
	(new token((char*)0, TKN_END_SHIFT))->insert_a(l_tkn);
    }
    if (ctx == ctx_module || ctx == ctx_program) {
        (new token((char*)0, TKN_BEG_SHIFT, f_tkn->line,
		   f_tkn->next_relevant()->pos))->insert_b(f_tkn);
        (new token((char*)0, TKN_END_SHIFT))->insert_a(l_tkn);
    }
}

type_def_node::type_def_node(token* ident, token* equal, tpd_node* tpd)
{
    CONS3(ident, equal, tpd);
}

void type_def_node::attrib(int ctx)
{
    tpd->attrib(ctx);
    tpexpr* type = new simple_tp(tpd->type);
    sym = b_ring::add_cur(ident, symbol::s_type, type);
    type->name = sym->out_name->text;

    switch (tpd->tag) {
      case tpd_node::tpd_enum:
        ((enum_tp*)tpd->type)->set_bounds(sym);
        ((enum_tp*)tpd->type)->set_enumeration_name(type);
	break;
      case tpd_node::tpd_range:
        ((range_tp*)tpd->type)->set_bounds(sym);
	break;
      case tpd_node::tpd_object:
        ((object_tp*)tpd->type)->class_name = sym;
    }
}

void type_def_node::translate(int ctx)
{
    tpd->translate(ctx);
    sym->translate(ident);
    f_tkn = ident;
    l_tkn = tpd->l_tkn;
    token::disable(ident->next, tpd->f_tkn->prev);

    if (language_c && tpd->tag == tpd_node::tpd_array) {
	tpd_node* eltd = ((array_tpd_node*)tpd)->eltd;
        f_tkn = ident->prepend("typedef ");
	ident->move(eltd->f_tkn, eltd->l_tkn);
        ident->prepend(" ");
    } else if (small_enum && tpd->tag == tpd_node::tpd_enum) {
	int n_elems = ((enum_tp*)tpd->type)->n_elems;
	ident->set_trans(dprintf("typedef %s %s;\n",
			       n_elems < 0x100 ? "unsigned char" :
			       n_elems < 0x10000 ? "unsigned short" :
			       "unsigned", ident->out_text));
	((enum_tpd_node*)tpd)->f_tkn->set_bind(ident);
    } else if (!language_c && tpd->tag == tpd_node::tpd_enum) {
	ident->append(" ");
	f_tkn = ident->prepend("enum ");
	((enum_tpd_node*)tpd)->f_tkn->disable();
    } else if (tpd->tag == tpd_node::tpd_object) {
	tpd->f_tkn->append(ident->out_text);
	tpd->f_tkn->set_pos(ident);
	ident->disappear();
     } else if (tpd->tag == tpd_node::tpd_record) {
	record_tpd_node* rec_tpd = (record_tpd_node*)tpd;
	if (language_c) {
	    rec_tpd->t_record->set_trans(dprintf("typedef %s%s ",
						 rec_tpd->t_record->out_text,
						 ident->out_text));
	    l_tkn = l_tkn->append(" ")->append(ident->out_text);
	} else {
	    rec_tpd->t_record->set_trans(dprintf("%s%s ",
						 rec_tpd->t_record->out_text,
						 ident->out_text));
	}
	rec_tpd->t_record->set_pos(ident);
	ident->disappear();
    } else if (tpd->tag == tpd_node::tpd_proc) {
	fptr_tpd_node* fptr = (fptr_tpd_node*)tpd;
	fptr->t_params->prepend(dprintf("(*%s)", ident->out_text));
	ident->set_trans("typedef ");
    } else {
	ident->append(" ");
        l_tkn = l_tkn->append(" ")->append(ident->out_text);
        ident->set_trans("typedef");
    }
    force_semicolon();
}


type_def_part_node::type_def_part_node(token* t_type, type_def_node* types)
{
    CONS2(t_type, types);
}

void type_def_part_node::attrib(int ctx)
{
    for (decl_node* tpd = types; tpd != NULL; tpd = tpd->next) {
	tpd->attrib(ctx);
    }
    if (ctx == ctx_block && curr_proc) {
	curr_proc->make_all_constants_global = TRUE;
    }
}

void type_def_part_node::translate(int ctx)
{
    f_tkn = l_tkn = t_type;
    t_type->disappear();
    for (decl_node* tpd = types; tpd != NULL; tpd = tpd->next) {
	tpd->translate(ctx);
	l_tkn = tpd->l_tkn;
    }
    if (ctx == ctx_block) {
	// make type definition global
        global_func_decl_level->move_region(f_tkn, l_tkn);
	global_func_decl_level->prepend("\n\n");
        (new token(NULL, TKN_BEG_SHIFT, f_tkn->line,
		   f_tkn->next_relevant()->pos))->insert_b(f_tkn);
	(new token((char*)0, TKN_END_SHIFT))->insert_a(l_tkn);
    } else {
        (new token((char*)0, TKN_BEG_SHIFT, f_tkn->line,
		   f_tkn->next_relevant()->pos))->insert_b(f_tkn);
	(new token((char*)0, TKN_END_SHIFT))->insert_a(l_tkn);
    }
}

unit_spec_node::unit_spec_node(token* t_unit, token* t_name, token* t_semi,
			       token* t_interface, decl_node* decls)
{
    CONS5(t_unit, t_name, t_semi, t_interface, decls);
}

void unit_spec_node::attrib(int ctx)
{
    unit_tp* type = new unit_tp;
    b_ring::global_b_ring.add(t_name->name, symbol::s_var, type);
    b_ring* outer = b_ring::pop();

    b_ring::push(type);

    for (decl_node* dcl = decls; dcl != NULL; dcl = dcl->next) {
        dcl->attrib(ctx);
    }
    b_ring::push(outer);
}

void unit_spec_node::translate(int ctx)
{
    for (decl_node* dcl = decls; dcl != NULL; dcl = dcl->next) {
	dcl->translate(ctx);
	l_tkn = dcl->l_tkn;
    }
}


var_decl_node::var_decl_node(token_list* vars, token* coln, tpd_node* tpd)
{
    CONS3(vars, coln, tpd);
    scope = NULL;
}

void var_decl_node::attrib(int ctx)
{
    tpexpr* tp;
    if (tpd != NULL) {
	tpd->attrib(ctx);
	tp = tpd->type;
	if (tp == NULL) {
	    warning(coln, "type is unknown");
	    tpd->type = tp = &any_type;
	}
    } else {
	tp = &any_type;
    }

    for (token_list* tkn = vars; tkn != NULL; tkn = tkn->next) {
	int prm_class = symbol::s_var;
	if (language_c) {
	    if (tp->tag == tp_array || tp->tag == tp_dynarray) {
		if (ctx == ctx_valpar) {
		    prm_class = symbol::s_const;
		}
	    } else {
		if (ctx == ctx_varpar) {
		    prm_class = symbol::s_ref;
		}
	    }
	} else if (ctx == ctx_varpar && tp->tag != tp_array
		   && tp->tag != tp_string && curr_proc->is_extern_c)
        {
	    prm_class = symbol::s_ref;
	}

	tkn->var = b_ring::add_cur(tkn->ident, prm_class, tp);
	if (ctx == ctx_varpar) {
	    tkn->var->flags |= symbol::f_var_param;
	}
	else if (ctx == ctx_valpar) {
	    tkn->var->flags |= symbol::f_val_param;
	}
	if (*struct_path) {
	   tkn->var->path = struct_path;
	}
	if (ctx == ctx_valpar || ctx == ctx_varpar) {
	    curr_proc->add_param(tkn->var);
	}
    }
}

static token* var_decl_coln; // align formal parameters of procedures

void  var_decl_node::translate(int ctx)
{
    tpexpr* tp;
    if (tpd != NULL) {
	tpd->translate(ctx);
	tp = tpd->type;
    } else {
	tp = &any_type;
    }
    f_tkn = vars->ident;
    l_tkn = coln ? coln : f_tkn;

    if (coln != NULL) {
	token::disable(coln->prev_relevant()->next, tpd->f_tkn->prev);
    }
    if (ctx == ctx_valpar || ctx == ctx_varpar) {
	if (language_c && tp->tag == tp_dynarray) {
	    token *t = vars->ident->prev;
	    ((array_tp*)tp->get_typedef())->
		insert_bound_params(vars->ident);
	    if (var_decl_coln) {
	        t->next->set_bind(var_decl_coln);
	    }
	}
        for (token_list* tkn = vars; tkn != NULL; tkn = tkn->next) {
	    token *t;
	    tkn->var->translate(tkn->ident);
	    if (language_c) {
		if (tpd != NULL) {
		    if (tpd->tag == tpd_node::tpd_array) {
			tpd_node* eltd = ((array_tpd_node*)tpd)->eltd;
			t = tkn->ident->copy(eltd->f_tkn, eltd->l_tkn);
			if (tp->tag == tp_dynarray) {
			    tkn->ident->prepend(ctx == ctx_varpar
						? "* " : " const* ");
			} else {
			    tkn->ident->prepend(ctx == ctx_varpar
						? " " : "  const ");
			    tkn->ident->next->copy(tpd->f_tkn, tpd->l_tkn);
			}
		    } else {
			t = tkn->ident->prepend(ctx == ctx_varpar
						? tp->tag == tp_array || tp->tag == tp_string ? " " : "* "
						: tp->tag == tp_array ? " const " : " ")->
			    copy(tpd->f_tkn, tpd->l_tkn);
		    }
		} else {
		    t = tkn->ident->prepend("void* ");
		}
	    } else { // C++
		if (tpd == NULL) {
		    t = tkn->ident->prepend("void* ");
		} else {
		    char* modifier = " ";
		    if (ctx == ctx_varpar) {
			if (tp->tag != tp_dynarray && tp->tag != tp_string) {
			    if (curr_proc->is_extern_c) {
				if (tp->tag != tp_array) {
				    modifier = "* ";
				}
			    } else {
				modifier = "& ";
			    }
			}
		    }
		    t = tkn->ident->prepend(modifier);
		    if (curr_proc->is_extern_c && tp->tag == tp_array) {
			char* param_type_name =
			    ((array_tp*)tp->get_typedef())->elem_type->name;
			t->prepend(dprintf("%s* ", param_type_name
					   ? param_type_name : "void"));
		    } else {
			t->copy(tpd->f_tkn, tpd->l_tkn);
		    }
		}
	    }
	    if (var_decl_coln) {
	        t->set_bind(var_decl_coln);
	    } else {
	        t->set_pos(tkn->ident);
            }
	    if (tkn == vars) {
		f_tkn = t;
            }
        }
	if (tpd != NULL) {
	    token::remove(tpd->f_tkn, tpd->l_tkn);
	}
	if (language_c && tpd != NULL && tpd->tag == tpd_node::tpd_array) {
	    tpd_node* eltd = ((array_tpd_node*)tpd)->eltd;
	    token::remove(eltd->f_tkn, eltd->l_tkn);
	}
        if (l_tkn->next_relevant()->tag == TKN_SEMICOLON) {
            l_tkn->next_relevant()->set_trans(",");
        }

    } else {
	bool is_static = FALSE;
	for (token_list* tkn = vars; tkn != NULL; tkn = tkn->next) {
	    if (tkn->var->out_name != tkn->ident->name) {
		tkn->ident->set_trans(tkn->var->out_name->text);
	    }
	    if (language_c && ctx != ctx_record
		&& (tp->get_typedef()->flags & tp_need_init))
	    {
		// initialize file structure
		tkn->ident->append(
		    (tp->tag == tp_file || tp->tag == tp_text)
		    ? " = VOID_FILE" : " = {0}");
	    }
	    if (tkn->var->flags & symbol::f_static) {
		is_static = TRUE;
	    }
	}
	if (language_c && tpd->tag == tpd_node::tpd_array) {
	    tpd_node* eltd = ((array_tpd_node*)tpd)->eltd;
	    f_tkn = f_tkn->prepend(" ");
	    f_tkn = f_tkn->move(eltd->f_tkn, eltd->l_tkn);
	    for (token_list* tkn = vars; tkn != NULL; tkn = tkn->next) {
		tkn->ident->next->copy(tpd->f_tkn, tpd->l_tkn);
	    }
	    token::remove(tpd->f_tkn, tpd->l_tkn);
	} else {
	    if (language_c && tpd->tag == tpd_node::tpd_ref) {
		for (token_list* tkn = vars->next; tkn != NULL; tkn=tkn->next){
		    tkn->ident->prepend("*");
		}
	    }
	    f_tkn = f_tkn->prepend(" ");
	    f_tkn = f_tkn->move(tpd->f_tkn, tpd->l_tkn);
	}
	if (ctx != ctx_record  && ctx != ctx_object
	    && (unit_node::interface_part
		|| (extern_vars
		    && coln != NULL
		    && (coln->attr & token::from_include_file))))
        {
	    f_tkn = f_tkn->prepend("EXTERN ");
	} else if (scope != NULL) {
	    f_tkn = f_tkn->prepend(scope->tag == TKN_EXTERNAL ? "extern " :
				   scope->tag == TKN_STATIC ? "static " : "");
	}
        force_semicolon();
	if (is_static) {
	    assert(global_func_decl_level != NULL);
	    for (token_list* tkn = vars; tkn != NULL; tkn = tkn->next) {
		if (!(tkn->var->flags & symbol::f_static)) {
		    tkn->var->flags |= symbol::f_static;
		    tkn->var->ring->make_unique(tkn->var);
		    tkn->var->translate(tkn->ident);
		}
	    }
	    f_tkn = f_tkn->prepend("static ");
	    global_func_decl_level->move_region(f_tkn, l_tkn);
	    global_func_decl_level->prepend("\n");
	    (new token(NULL, TKN_BEG_SHIFT, f_tkn->line, f_tkn->pos))
		->insert_b(f_tkn);
	    (new token((char*)0, TKN_END_SHIFT))->insert_a(l_tkn);
	}
    }
}

var_decl_part_node::var_decl_part_node(token* t_var, var_decl_node* vars)
{
    CONS2(t_var, vars);
}

void var_decl_part_node::attrib(int ctx)
{
    for (decl_node* var = vars; var != NULL; var = var->next) {
        var->attrib(ctx == ctx_valpar ? (int)ctx_varpar : ctx);
    }
}

void var_decl_part_node::translate(int ctx)
{
    f_tkn = l_tkn = t_var;
    for (decl_node* var = vars; var != NULL; var = var->next) {
        var->translate(ctx == ctx_valpar ? (int)ctx_varpar : ctx);
	l_tkn = var->l_tkn;
    }
    if (t_var) {
	t_var->disappear();
    } else {
	f_tkn = vars->f_tkn;
    }
    //    token::disable(t_var, t_var->next_relevant()->prev);
    if (ctx == ctx_module || ctx == ctx_program) {
        (new token((char*)0, TKN_BEG_SHIFT, f_tkn->line,
		   f_tkn->next_relevant()->pos))->insert_b(f_tkn);
        (new token((char*)0, TKN_END_SHIFT))->insert_a(l_tkn);
	if (unit_node::interface_part) {
	    f_tkn = f_tkn->prepend(dprintf("\n#ifdef __%s_implementation__\n"
					   "#undef EXTERN\n"
					   "#define EXTERN\n"
					   "#endif\n\n",
					   unit_node::unit_name));
	    l_tkn = l_tkn->append("\n#undef EXTERN\n"
				  "#define EXTERN extern\n");
	}
    }
}


var_origin_decl_node::var_origin_decl_node(token* t_ident,
					   token* t_origin, expr_node *addr,
					   token* t_colon, tpd_node *tpd)
{
    CONS5(t_ident, t_origin, addr, t_colon, tpd);
}


void var_origin_decl_node::attrib(int ctx)
{
    tpd->attrib(ctx);
    type = tpd->type;
    sym = b_ring::add_cur(t_ident,
			  language_c ? symbol::s_ref : symbol::s_var, type);
    addr->attrib(ctx_value);
}

void var_origin_decl_node::translate(int ctx)
{
    tpd->translate(ctx);
    sym->translate(t_ident);
    addr->translate(ctx_value);
    l_tkn = addr->l_tkn;
    assert(type->name != NULL);
    f_tkn = t_ident->prepend(type->name);
    if (language_c) {
	t_ident->prepend("* ");
	t_origin->set_trans(dprintf(" = (%s*)", type->name));
    } else {
	t_ident->prepend("& ");
	t_origin->set_trans(dprintf(" = *(%s*)", type->name));
    }
    token::disable(l_tkn->next, tpd->l_tkn);
    force_semicolon();
    if (sym->flags & symbol::f_static) {
	assert(global_func_decl_level != NULL);
	f_tkn = f_tkn->prepend("static ");
	global_func_decl_level->move_region(f_tkn, l_tkn);
	global_func_decl_level->prepend("\n\n");
	(new token(NULL, TKN_BEG_SHIFT, f_tkn->line, f_tkn->pos))
	    ->insert_b(f_tkn);
	(new token((char*)0, TKN_END_SHIFT))->insert_a(l_tkn);
    } else {
	if (ctx == ctx_module || ctx == ctx_program) {
	    (new token((char*)0, TKN_BEG_SHIFT, f_tkn->line,
		       f_tkn->next_relevant()->pos))->insert_b(f_tkn);
	    (new token((char*)0, TKN_END_SHIFT))->insert_a(l_tkn);
	}
    }
}


param_list_node::param_list_node(token* lpar, decl_node* params, token* rpar)
{
    CONS3(lpar, params, rpar);
}

void param_list_node::attrib(int)
{
    for (decl_node* dcl = params; dcl != NULL; dcl = dcl->next) {
        dcl->attrib(ctx_valpar);
    }
}

void param_list_node::translate(int)
{
    f_tkn = lpar;
    l_tkn = rpar;

    for (decl_node* dcl = params; dcl != NULL; dcl = dcl->next) {
        dcl->translate(ctx_valpar);
	if (var_decl_coln == NULL) {
	    var_decl_coln = dcl->f_tkn->prev->next_relevant();
        }
    }
    var_decl_coln = NULL;
}


// Class proc_decl_node is used for procedure formal parameter declaration

proc_decl_node::proc_decl_node(token* t_proc, token* t_ident,
			       param_list_node* params,
			       token* t_coln, tpd_node* ret_type)
{
    CONS5(t_proc, t_ident, params, t_coln, ret_type);
}

void proc_decl_node::attrib(int ctx)
{
    if (ret_type) ret_type->attrib(ctx);

    type = new proc_tp(ret_type ? ret_type->type : (tpexpr*)NULL, (tpd_node*)this);
    var = b_ring::add_cur(t_ident, symbol::s_var, type);
    type->proc_name = var->out_name->text;
    curr_proc->add_param(var);
    if (params) {
        proc_tp* save_proc = curr_proc;
        curr_proc = type;
        b_ring::push(type);
        params->attrib(ctx);
        b_ring::pop(type);
        curr_proc = save_proc;
    }
}

void proc_decl_node::insert_return_type() {
    if (ret_type) {
        ret_type->translate(ctx_block);
	assert(ret_type->type->name != NULL);
	if (language_c && ret_type->type->tag == tp_array) {
	    t_proc->set_trans(dprintf("%s*", ret_type->type->name));
	    var->flags |= symbol::f_var_param;
	} else {
	    t_proc->set_trans(ret_type->type->name);
	}
	token::disable(t_coln->prev_relevant()->next, ret_type->l_tkn);
    } else {
	if (type->is_constructor || type->is_destructor) {
	    if (var != NULL) {
		t_proc->set_trans(dprintf("%s*", ((object_tp*)var->ring)->
					  class_name->out_name->text));
	    }
	} else {
	    t_proc->set_trans("void");
	}
    }
    if (*pascall) {
	t_proc->append(pascall);
	t_proc->append(" ");
    }
}

void proc_decl_node::insert_params() {
    token* rest = NULL;
    bool first = FALSE;
    if (params) {
        proc_tp* save_proc = curr_proc;
	curr_proc = type;
        params->translate(ctx_block);
	curr_proc = save_proc;
	rest = params->rpar;
    } else {
        rest = t_ident->append("(")->append(")");
	first = TRUE;
    }
    if (language_c && type->res_type != NULL
	&& type->res_type->tag == tp_array)
    {
	if (params) {
	    params->lpar->append(dprintf("%s %s_result, ",
					 type->res_type->name,
					 type->proc_name));
	} else {
	    rest->prepend(dprintf("%s %s_result",
				   type->res_type->name, type->proc_name));
	}
	first = FALSE;
    }
    for (param_spec* p = type->extra_params; p != NULL; p = p->next) {

	if (p->var->flags & symbol::f_static) continue;

	if (!first) {
     	    rest->prepend(", ");
	}
	first = FALSE;
	if (language_c) {
	    if (p->var->type->tag == tp_array) {
		array_tpd_node* atp = (array_tpd_node*)p->var->type->tpd;
		rest->copy(atp->eltd->f_tkn, atp->eltd->l_tkn);
		rest->prepend(dprintf(p->var->tag == symbol::s_const
				      ? " const %s" : " %s",
				      p->var->out_name->text));
		rest->copy(atp->f_tkn, atp->l_tkn);
	    } else if (p->var->type->tag == tp_dynarray) {
		array_tpd_node* atp = (array_tpd_node*)p->var->type->tpd;
		rest->copy(atp->eltd->f_tkn, atp->eltd->l_tkn);
		rest->prepend(dprintf(p->var->tag == symbol::s_const
				      ? " const* %s" : "* %s",
				      p->var->out_name->text));
	    } else {
		p->var->type->insert_before(rest);
		if (p->var->tag == symbol::s_const) {
		    if (p->var->type->is_scalar()
			|| p->var->type->tag == tp_string)
		    {
			rest->prepend(dprintf(" const %s",
					      p->var->out_name->text));
		    } else {
			rest->prepend(dprintf(" const* %s",
					      p->var->out_name->text));
		    }
		} else {
		    rest->prepend(dprintf("* %s", p->var->out_name->text));
		}
	    }
	} else {
	    p->var->type->insert_before(rest);
	    if (p->var->tag == symbol::s_const) {
		if (p->var->type->is_scalar()) {
		    rest->prepend(dprintf(" const %s",
					  p->var->out_name->text));
		} else {
		    rest->prepend(dprintf(" const& %s",
					  p->var->out_name->text));
		}
	    } else {
		rest->prepend(dprintf("& %s", p->var->out_name->text));
	    }
	}
    }
}


void proc_decl_node::translate(int)
{
    f_tkn = t_proc;

    insert_return_type();
    t_ident->set_trans(dprintf("(*%s)", var->out_name->text));
    insert_params();
    l_tkn = params ? params->l_tkn : t_ident->next->next;

    if (l_tkn->next_relevant()->tag == TKN_SEMICOLON) {
        l_tkn->next_relevant()->set_trans(",");
    }
}

proc_fwd_decl_node::proc_fwd_decl_node
   (token* t_proc, token* t_ident, param_list_node* params, token* t_coln,
    tpd_node* ret_type, token* t_semi1, token_list* qualifiers, token* t_semi2)
: proc_decl_node(t_proc, t_ident, params, t_coln, ret_type)
{
    CONS3(t_semi1, qualifiers, t_semi2);
}

void proc_fwd_decl_node::attrib(int ctx)
{
    if (ret_type) {
	ret_type->attrib(ctx);
    }
    type = new proc_tp(ret_type ? ret_type->type : (tpexpr*)NULL);
    type->forward = this;

    if (turbo_pascal) {
	if (t_proc->tag == TKN_CONSTRUCTOR) {
	    type->is_constructor = TRUE;
	} else if (t_proc->tag == TKN_DESTRUCTOR) {
	    type->is_destructor = TRUE;
	}
    }
    is_external = FALSE;
    is_static = FALSE;
    is_virtual = FALSE;
    for (token_list* t = qualifiers; t != NULL; t = t->next) {
	if (t->ident->tag == TKN_EXTERNAL) {
	    is_external = TRUE;
	} else if (t->ident->tag == TKN_STATIC) {
	    is_static = TRUE;
	} else if (t->ident->tag == TKN_VIRTUAL) {
	    is_virtual = TRUE;
	} else if (t->ident->tag == TKN_C) {
	    type->is_extern_c = TRUE;
	}
    }

    if ((var = b_ring::search_cur(t_ident)) == NULL || var->type == NULL
	|| var->type->tag != tp_proc || var->ring != b_ring::curr_b_ring
	|| (var->flags & symbol::f_syslib))
    {
	var = b_ring::add_cur(t_ident, symbol::s_proc, type);
    } else {
	var->type = type;
    }
    type->proc_name = var->out_name->text;

    if (params) {
        proc_tp* save_proc = curr_proc;
        curr_proc = type;
        b_ring::push(type);
        params->attrib(ctx);
        b_ring::pop(type);
        curr_proc = save_proc;
    }
}

void proc_fwd_decl_node::translate(int)
{
    f_tkn = t_proc;
    l_tkn = t_semi1;

    insert_return_type();
    if (qualifiers) {
	if (is_external) {
	    f_tkn = f_tkn->prepend(type->is_extern_c && !language_c
				   ? "extern \"C\" " : "extern ");
	} else if (is_static) {
	    f_tkn = f_tkn->prepend("static ");
	} else if (is_virtual) {
	    f_tkn = f_tkn->prepend("virtual ");
	}
    }
    var->translate(t_ident);
    insert_params();
    if (qualifiers) {
	token::remove(qualifiers->ident, t_semi2);
    }
}


object_tp* proc_def_node::self;

proc_def_node::proc_def_node
  (token* t_proc, token* t_class, token* t_dot, token* t_ident, param_list_node* params, token* t_coln,
   tpd_node* ret_type, token* t_semi1, token* t_attrib, token* t_semi2,
   block_node* block, token* t_semi3)
: proc_decl_node(t_proc, t_ident, params, t_coln, ret_type)
{
    CONS7(t_class, t_dot, t_semi1, t_attrib, t_semi2, block, t_semi3);
    use_forward = FALSE;
    s_self = NULL;
    self = NULL;
}

void proc_def_node::attrib(int ctx)
{
    if (ret_type) {
	ret_type->attrib(ctx);
    }
    type = new proc_tp(ret_type ? ret_type->type : (tpexpr*)NULL);

    if (t_class != NULL) { // class method
	s_self = b_ring::search_cur(t_class);
	if (s_self == NULL) {
	    warning(t_class, "Class %s is not defined\n", t_class->out_text);
	} else {
	    self = (object_tp*)s_self->type->get_typedef();
	    var = self->search(t_ident);
	    if (var == NULL || var->type->tag != tp_proc) {
		warning(t_class, "Method %s not found in class %s\n",
			t_ident->out_text, t_class->out_text);
		var = self->add(t_ident->name, symbol::s_proc, type);
	    } else {
		type = (proc_tp*)var->type;
	    }
	    b_ring::push(self);
	}
    } else {
	if ((var = b_ring::search_cur(t_ident)) == NULL || var->type == NULL
	    || var->type->tag != tp_proc || var->ring != b_ring::curr_b_ring
	    || (var->flags & symbol::f_syslib))
	{
	    var = b_ring::add_cur(t_ident, symbol::s_proc, type);
	}
	else
	{
	    if (((proc_tp*)var->type)->forward != NULL
		&& params == NULL && ret_type == NULL)
	    {
		use_forward = TRUE;
		type = (proc_tp*)var->type;
	    } else {
		var->type = type;
	    }
	}
    }
    if (var != NULL) {
	type->proc_name = var->out_name->text;
    }
    b_ring::push(type);
    proc_tp* save_proc = curr_proc;
    curr_proc = type;
    if (params) params->attrib(ctx);
    block->attrib(ctx_block);
    if (save_proc) {
	save_proc->n_subproc += curr_proc->n_subproc + 1;
    }
    curr_proc = save_proc;

    b_ring::pop(type);
    if (t_class && self) {
	b_ring::pop(self);
	self = NULL;
    }
}

void proc_def_node::translate(int ctx)
{
    f_tkn = t_proc;
    l_tkn = t_semi3;
    int is_recursive = var->out_name->flags & nm_entry::recursive;

    proc_tp* save_proc = curr_proc;
    curr_proc = type;

    if (t_attrib != NULL) {
	token::remove(t_attrib, t_semi2);
    }

    if (use_forward) {
        f_tkn = t_proc->copy(type->forward->f_tkn,
			     type->forward->t_semi1->prev);
	token::remove(t_proc, t_semi1->prev);
    } else {
	insert_return_type();
        var->translate(t_ident);
	insert_params();
    }
    t_semi3->disable();
    if (s_self) {
	s_self->translate(t_class);
    }
    if (t_dot) {
	t_dot->set_trans("::");
    }
    if (ctx != ctx_block) {
	global_func_decl_level = f_tkn;
	if (type->n_subproc > 0 && t_class == NULL) { // make forward declaration
	    f_tkn->copy(f_tkn, t_semi1);
	    f_tkn->prepend("\n");
	}
    } else {
	f_tkn = f_tkn->prepend("static ");
	if (type->n_subproc > 0) { // make forward declaration
	    global_func_decl_level->copy(f_tkn, t_semi1);
	    global_func_decl_level->prepend("\n");
	}
    }
    if (var->ring->scope == b_ring::global && use_call_graph && !is_recursive){
	type->make_vars_static();
    }

    block->translate(ctx_block);

    t_semi1->disable();
    token* first_stmt = t_semi1->next_relevant();
    token* lbr = block->body->t_begin;
    if (first_stmt != block->body->t_begin) {
	lbr = first_stmt->prepend("{\n");
	lbr->set_pos(block->body->t_begin);
	block->body->t_begin->disable();
    }
    block->body->t_end->set_bind(lbr);


    if (language_c) {
	type->undefine(block->body->t_end->prev_relevant());
    }
    first_stmt = block->body->t_begin->next_relevant();

    type->insert_temporaries(first_stmt);

    if (!language_c) {
	type->declare_conformant_array_bounds(first_stmt);
    }
    if (type->res_type != NULL)
    {
	if( language_c && type->res_type->tag == tp_array) {
	    block->body->t_end->prepend(dprintf("return (%s*)%s_result;\n",
						type->res_type->name,
						type->proc_name))
		->set_bind(first_stmt);
	} else {
	    first_stmt->prepend(dprintf("%s %s_result;\n",
				     type->res_type->name, type->proc_name));
	    block->body->t_end->prepend(dprintf("return %s_result;\n",
						type->proc_name))
		->set_bind(first_stmt);
	}
    } else if (type->is_constructor || type->is_destructor) {
	block->body->t_end->prepend("return this;\n")->set_bind(first_stmt);
    }
    curr_proc = save_proc;
    if (ctx == ctx_block)
    {
        global_func_decl_level->move_region(f_tkn, l_tkn);
	global_func_decl_level->prepend("\n\n");
        (new token((char*)0, TKN_BEG_SHIFT, f_tkn->line, f_tkn->pos))->
	  insert_b(f_tkn);
	(new token((char*)0, TKN_END_SHIFT))->insert_a(l_tkn);
    }
}

//
// Type declaration node
//


simple_tpd_node::simple_tpd_node(token* tkn) : tpd_node(tpd_simple)
{
    this->tkn = tkn;
}

void simple_tpd_node::attrib(int ctx)
{
    sym = b_ring::search_cur(tkn);
    if (sym == NULL) {
        if (ctx == ctx_reftyp) {
            type = new fwd_ref_tp(tkn);
	} else {
 	    warning(tkn, "unknown type");
	    type = &void_type;
        }
    } else {
	type = sym->type;
    }
}


void simple_tpd_node::translate(int ctx)
{
    l_tkn = f_tkn = tkn;
    if (sym != NULL) {
	sym->translate(tkn);
    } else {
	if (ctx == ctx_reftyp) {
	    f_tkn = tkn->prepend("struct ");
        }
    }
}

fptr_tpd_node::fptr_tpd_node(token* t_proc, param_list_node* params,
			     token* t_coln, tpd_node* ret_type)
: tpd_node(tpd_proc)
{
    CONS4(t_proc, params, t_coln, ret_type);
}


void fptr_tpd_node::attrib(int ctx)
{
    if (ret_type) {
        ret_type->attrib(ctx);
    }
    type = new proc_tp(ret_type ? ret_type->type : (tpexpr*)NULL);
    if (params) {
        proc_tp* save_proc = curr_proc;
	curr_proc = (proc_tp*)type;
	b_ring::push(curr_proc);
	params->attrib(ctx);
	b_ring::pop(curr_proc);
	curr_proc = save_proc;
    }
}

void fptr_tpd_node::translate(int)
{
    f_tkn = t_proc;
    if (ret_type) {
        ret_type->translate(ctx_block);
	assert(ret_type->type->name != NULL);
	t_proc->set_trans(ret_type->type->name);
	token::disable(t_coln->prev_relevant()->next, ret_type->l_tkn);
    } else {
        t_proc->set_trans("void");
    }
    if (*pascall) {
	t_proc->append(pascall);
	t_proc->append(" ");
    }
    if (params) {
        proc_tp* save_proc = curr_proc;
	curr_proc = (proc_tp*)type;
        params->translate(ctx_block);
	curr_proc = save_proc;
	l_tkn = params->rpar;
	t_params = params->lpar;
    } else {
        t_params = l_tkn = t_proc->append("()");
    }
}


enum_tpd_node::enum_tpd_node(token* lpar, token_list* items, token* rpar)
: tpd_node(tpd_enum)
{
    CONS3(lpar, items, rpar);
}

void enum_tpd_node::attrib(int)
{
    int n = 0;
    type = new enum_tp(this);
    for (token_list* t = items; t != NULL; t = t->next) {
        ((enum_tp*)type)->last = t->var = b_ring::add_cur(t->ident,
							  symbol::s_const,
							  &integer_type);
	t->var->value = n++;
	t->var->flags |= symbol::f_const;
	if (b_ring::curr_b_ring->scope != b_ring::global) {
	    t->var->flags |= symbol::f_static;
	    t->var->ring->make_unique(t->var);
	}
    }
    ((enum_tp*)type)->n_elems = n;
    ((enum_tp*)type)->first = items->var;
}


void enum_tpd_node::translate(int)
{
    f_tkn = lpar->prepend("enum ");
    l_tkn = rpar;
    for (token_list* t = items; t != NULL; t = t->next) {
        t->var->translate(t->ident);
	t->ident->attr |= token::fix_pos;
    }
    lpar->set_trans("{");
    rpar->set_trans("}");

    if (((enum_tp*)type)->max != NULL) {
        rpar->prepend(", ");
        rpar->prepend(((enum_tp*)type)->max);
    }
}

range_tpd_node::range_tpd_node(expr_node* low, token* dots, expr_node* high)
: tpd_node(tpd_range)
{
    CONS3(low, dots, high);
}

void range_tpd_node::attrib(int)
{
    low->attrib(ctx_value);
    high->attrib(ctx_value);
    range_tp* rtp = new range_tp(this);
    long min_value = INT_MIN, max_value = INT_MAX;

    if (low->flags & tn_is_const) {
	min_value = low->value;
    }
    if (high->flags & tn_is_const) {
	max_value = high->value;
    }
    if (!(low->flags & high->flags & tn_is_const)) {
	warning(dots, "unable to calculate bounds for range type");
    }
    rtp->min_value = min_value;
    rtp->max_value = max_value;

    if (min_value >= 0 && max_value <= 255)  {
	rtp->name = "unsigned char";
	rtp->size = 1;
    } else if(min_value >= -128 && max_value <= 127) {
	rtp->name = "signed char";
	rtp->size = 1;
    } else if(min_value >= 0 && max_value <= USHRT_MAX) {
	rtp->name = "unsigned short";
	rtp->size = 2;
    } else if(min_value >= SHRT_MIN && max_value <= SHRT_MAX) {
	rtp->name = "short";
	rtp->size = 2;
    } else if(min_value >= 0 && (unsigned long)max_value <= UINT_MAX) {
	rtp->name = "unsigned";
	rtp->size = 4;
    } else if(min_value >= INT_MIN && max_value <= INT_MAX) {
	rtp->name = "int";
	rtp->size = 4;
    } else {
	rtp->name = "integer";
	rtp->size = 4;
    }
    type = rtp;
}


void range_tpd_node::translate(int)
{
    low->translate(ctx_value);
    high->translate(ctx_value);

    token* first = low->f_tkn->get_first_token();

    f_tkn = l_tkn = low->f_tkn->prepend(type->name);
    if (((range_tp*)type)->min != NULL) {
	if (language_c) {
	    low->f_tkn->prepend(dprintf("\n#define %s ",
					((range_tp*)type)->min));
	    dots->disable();
	    high->f_tkn->prepend(dprintf("\n#define %s ",
					((range_tp*)type)->max));
	    token* next = high->l_tkn->next_relevant();
	    if (next->tag == TKN_SEMICOLON) {
		next->set_trans("\n");
	    } else {
		high->l_tkn->append("\n");
	    }
	} else {
	    low->f_tkn->prepend("\n");
	    low->f_tkn->prepend("const int ")->set_pos(first);
	    low->f_tkn->prepend(((range_tp*)type)->min);
	    low->f_tkn->prepend(" = ");
	    low->l_tkn->append(";");
	    dots->disable();
	    high->f_tkn->prepend("\n");
	    high->f_tkn->prepend("const int ")->set_pos(first);
	    high->f_tkn->prepend(((range_tp*)type)->max);
	    high->f_tkn->prepend(" = ");
	    token* next = high->l_tkn->next_relevant();
	    if (next->tag != TKN_SEMICOLON) {
		next = high->l_tkn->append(";");
		next->tag = TKN_SEMICOLON;
	    }
	}
    } else {
	token::remove(low->f_tkn, high->l_tkn);
    }
}


static array_tp* curr_array = NULL;

type_index_node::type_index_node(tpd_node* tpd)
{
    this->tpd = tpd;
}

void type_index_node::attrib(int ctx)
{
    tpd->attrib(ctx);
    assert(tpd->tag == tpd_node::tpd_simple);
}

void type_index_node::translate(int)
{
    f_tkn = l_tkn = ((simple_tpd_node*)tpd)->tkn;
    tpexpr* type = tpd->type->get_typedef();

    if (language_c) {
	switch(type->tag) {
	  case tp_bool:
	    f_tkn->set_trans("2");
	    curr_array->set_dim("0", "1");
	    break;
	  case tp_range:
	    { range_tp* range = (range_tp*)type->get_typedef();
  	      if (no_index_decrement) {
		  f_tkn->set_trans(dprintf("%s+1", range->max));
	      } else {
		  f_tkn->set_trans(dprintf("%s-%s+1", range->max, range->min));
	      }
	      curr_array->set_dim(range->min, range->max);
	    }
	    break;
	  case tp_char:
	    f_tkn->set_trans("256");
	    curr_array->set_dim(" -128", "127");
	    break;
	  case tp_enum:
	    f_tkn->set_trans(((enum_tp*)type->get_typedef())->max);
	    curr_array->set_dim("0", dprintf("%s-1",
				       ((enum_tp*)type->get_typedef())->max));
	    break;
	  default:
	    warning(f_tkn, "Illegal type of index");
	}
    } else {
	switch(type->tag) {
	  case tp_bool:
	    f_tkn->set_trans("false,true");
	    break;
	  case tp_char:
	    f_tkn->set_trans("-128,127");
	    break;
	  case tp_range:
	    f_tkn->set_trans(dprintf("%s,%s",
				     ((range_tp*)type->get_typedef())->min,
				     ((range_tp*)type->get_typedef())->max));
	    break;
	  case tp_enum:
	    f_tkn->set_trans(dprintf("0,%s",
				     ((enum_tp*)type->get_typedef())->max));
	    break;
	  default:
	    warning(f_tkn, "Illegal type of index");
	}
    }

}

range_index_node::range_index_node(expr_node *low, token* dots,
				   expr_node* high)
{
    CONS3(low, dots, high);
}

void range_index_node::attrib(int)
{
    low->attrib(ctx_value);
    high->attrib(ctx_value);
}

void range_index_node::translate(int)
{
    low->translate(ctx_value);
    high->translate(ctx_value);
    f_tkn = low->f_tkn;
    l_tkn = high->l_tkn;

    if (language_c) {
	curr_array->set_dim(NULL, NULL, low, high);
	if (no_index_decrement) {
	    token::remove(low->f_tkn, high->f_tkn->prev);
	    l_tkn = high->l_tkn->append("+1");
	    return;
	}
	if (low->is_const_literal()) {
	    if (low->value == 1) {
		token::remove(low->f_tkn, high->f_tkn->prev);
		return;
	    }
	    if (high->is_const_literal()) {
		token::remove(low->f_tkn, high->f_tkn->prev);
		high->f_tkn->set_trans(dprintf("%d", high->value - low->value + 1));
		return;
	    }
	}
	token::swap(low->f_tkn, low->l_tkn, high->f_tkn, high->l_tkn);
	dots->set_trans("-");
	f_tkn = high->f_tkn;
	l_tkn = low->l_tkn->append("+1");
    } else { // language C++
	dots->set_trans(",");
    }
}

conformant_index_node::conformant_index_node(token *low, token *dots,
				             token *high, token *coln,
		                             tpd_node* tpd)
{
    CONS5(low, dots, high, coln, tpd);
}

void conformant_index_node::attrib(int)
{
    symbol *l = b_ring::add_cur(low, symbol::s_const, &integer_type);
    symbol *h = b_ring::add_cur(high, symbol::s_const, &integer_type);
    l->flags |= symbol::f_val_param;
    h->flags |= symbol::f_val_param;
    curr_array->set_conformant_dim(l, h);
}

void conformant_index_node::translate(int)
{

    // last and first tokens are not calculated here since it is not possible
    // (and not necessary)
}

array_tpd_node::array_tpd_node(token *t_packed, token *t_array,
                               token* t_lbr, idx_node *indices,
 			       token* t_rbr, token* t_of, tpd_node *eltd)
: tpd_node(tpd_array)
{
    CONS7(t_packed, t_array, t_lbr, indices, t_rbr, t_of, eltd);
}

void array_tpd_node::set_indices_attrib(idx_node* idx)
{
    if (idx->next) {
	set_indices_attrib(idx->next);
    }
    type = curr_array = new array_tp(type, this);
    idx->attrib(ctx_component);
}

void array_tpd_node::attrib(int)
{
    eltd->attrib(ctx_component);
    type = eltd->type;
    set_indices_attrib(indices);
}

void array_tpd_node::translate(int ctx)
{
    f_tkn = t_array;

    if (t_packed) {
	t_packed->disable();
    }
    eltd->translate(ctx_component);

    if (language_c) {
	token::disable(t_array, t_lbr->prev);
	token::disable(t_rbr->next, eltd->f_tkn->prev);
	f_tkn = t_lbr;
	l_tkn = t_rbr;
	if (eltd->tag == tpd_array) {
	    l_tkn = eltd->l_tkn;
	    eltd = ((array_tpd_node*)eltd)->eltd;
	}
	if (type->tag == tp_dynarray) {
	    token::remove(t_lbr, t_rbr);
	    f_tkn = eltd->f_tkn;
	    l_tkn = eltd->l_tkn;
	} else {
	    curr_array = (array_tp*)type;

	    for (idx_node* idx = indices; idx != NULL; idx = idx->next) {
		idx->translate(ctx);
		if (idx->next) {
		    token* comma = idx->l_tkn->next_relevant();
		    assert(comma->tag == TKN_COMMA);
		    token::disable(idx->l_tkn->next,
				   comma->next_relevant()->prev);
		    idx->l_tkn->append("][");
		    curr_array = (array_tp*)curr_array->elem_type;
		}
	    }
	}
    } else { // C++
	if (type->tag == tp_dynarray) {

	    if (eltd->type->tag == tp_dynarray) {
		array_tpd_node* atp = (array_tpd_node*)eltd;
		eltd = atp->eltd;
		t_of = atp->t_of;
		t_array->set_trans("conf_matrix");
	    } else {
		t_array->set_trans(indices->next == NULL
				   ? "conf_array" : "conf_matrix");
	    }
	    token::disable(t_array->next, eltd->f_tkn->prev);
	    eltd->f_tkn->prepend("<");
	    l_tkn = eltd->l_tkn->append(">");

	} else {

	    for (idx_node* idx = indices; idx != NULL; idx = idx->next) {
		idx->translate(ctx_component);
	    }
	    t_lbr->set_trans("<");
	    t_rbr->set_trans(",");
	    if (t_array->next != t_lbr) {
		token::disable(t_array->next, t_lbr->prev);
	    }
	    if (indices->next == NULL && eltd->tag == tpd_array && !((array_tp*)eltd->type)->elem_type->is_array()) {
		token::disable(t_rbr->next, ((array_tpd_node*)eltd)->t_lbr);
		t_array->set_trans("matrix");
		l_tkn = eltd->l_tkn;
	    } else {
		if (indices->next != NULL && indices->next->next == NULL) {
		    t_array->set_trans("matrix");
		}
		token::disable(t_rbr->next, eltd->f_tkn->prev);
		l_tkn = eltd->l_tkn->append(">");
	    }
	}
    }
}

//-------------------------------------------------------------------

varying_tpd_node::varying_tpd_node(token *t_string,
				   token* t_lbr, expr_node *size,
				   token* t_rbr)
: tpd_node(tpd_string)
{
    if (language_c) {
	error(t_string,"Varying string are supported only for C++ conversion");
    }
    CONS4(t_string, t_lbr, size, t_rbr);
}

void varying_tpd_node::attrib(int ctx)
{
    size->attrib(ctx_component);
    if (use_c_strings && (ctx == ctx_record || ctx == ctx_component)) {
	type = &string_type;
    } else {
	type = &varying_string_type;
    }
}

void varying_tpd_node::translate(int)
{
    f_tkn = t_string;
    l_tkn = t_rbr;
    if (type->tag == tp_string) {
	t_string->set_trans("asciiz");
	token::disable(t_lbr, t_rbr);
    } else {
	size->translate(ctx_component);
	t_lbr->set_trans("<");
	t_rbr->set_trans(">");
	t_string->set_trans("varying_string");
    }
}
//-------------------------------------------------------------------

string_tpd_node::string_tpd_node(token *t_string) : tpd_node(tpd_string)
{
    if (language_c) {
	error(t_string,"Varying string are supported only for C++ conversion");
    }
    CONS1(t_string);
}

void string_tpd_node::attrib(int ctx)
{
    if (use_c_strings && (ctx == ctx_record || ctx == ctx_component)) {
	type = &string_type;
    } else {
	type = &varying_string_type;
    }
}

void string_tpd_node::translate(int)
{
    f_tkn = l_tkn = t_string;
    if (type->tag == tp_string) {
	f_tkn->set_trans("asciiz");
    }
}

//----------------------------------------------------------------------

ptr_tpd_node::ptr_tpd_node(token* tkn_ref, tpd_node* tpd)
: tpd_node(tpd_ref)
{
    CONS2(tkn_ref, tpd);
}

void ptr_tpd_node::attrib(int)
{
    tpd->attrib(ctx_reftyp);
    type = (tpd->type->tag == tp_fwd_ref)
	? tpd->type : new ref_tp(tpd->type, this);
}

void ptr_tpd_node::translate(int)
{
    tkn_ref->disable();
    tpd->translate(ctx_reftyp);
    f_tkn = tpd->f_tkn;
    l_tkn = tpd->l_tkn->append("*");
}

variant_node::variant_node(expr_node* tag_list, token* t_coln,
			  token* t_lpar, field_list_node* fields,
			  token* t_rpar)
{
    CONS5(tag_list, t_coln, t_lpar, fields, t_rpar);
    next = NULL;
}

int variant_node::number;

void variant_node::attrib(int ctx)
{
    tag_list->attrib(ctx);

    if (fields->is_single()) {
	fields->attrib(ctx);
    } else {
	char* save_path = struct_path;
	number += 1;
        if (tag_list->tag == tn_atom) {
	    token* tag = ((atom_expr_node*)tag_list)->tkn;
	    struct_name = isdigit(tag->out_text[0])
	        ? dprintf("s%s", tag->out_text)
		: dprintf("s_%s", tag->out_text);
	} else {
	    struct_name = dprintf("s%d", number);
        }
	struct_path = dprintf("%s%s.", struct_path, struct_name);
	fields->attrib(ctx);
	struct_path = save_path;
    }
}

void variant_node::translate(int ctx)
{
    tag_list->translate(ctx);
    f_tkn = t_lpar;
    l_tkn = t_rpar;
    fields->translate(ctx);

    if (fields->is_single()) {
	token* t = t_lpar->next_relevant();
	t_lpar->disable();
	t_rpar->disable();
	if (t->line == tag_list->f_tkn->line) {
	    t->set_pos(tag_list->f_tkn);
        }
	swallow_semicolon();
    } else {
	t_lpar->set_trans("struct {");
	t_rpar->set_trans(dprintf("} %s", struct_name));
	if (t_lpar->line == tag_list->f_tkn->line) {
	    t_lpar->set_pos(tag_list->f_tkn);
	}
	force_semicolon();
    }
    if (comment_tags) {
	tag_list->f_tkn->prepend("/*");
	t_lpar->prepend("*/");
    } else {
	token::disable(tag_list->f_tkn, t_lpar->prev);
    }
}



selector_node::selector_node(token* tag_field, token* coln,
			     tpd_node* tag_type)
{
    CONS3(tag_field, coln, tag_type);
    var = NULL;
}

variant_part_node::variant_part_node(token* t_case, selector_node* selector,
				     token* t_of, variant_node* variants)
{
    CONS4(t_case, selector, t_of, variants);
}

void variant_part_node::attrib(int ctx)
{
    selector->tag_type->attrib(ctx);
    if (selector->tag_field != NULL) {
	selector->var = b_ring::add_cur(selector->tag_field,
					symbol::s_var,
					selector->tag_type->type);
	if (*struct_path) {
	    selector->var->path = struct_path;
	}
    }
    if (language_c && ctx != ctx_union) {
	char* save_path = struct_path;
	struct_path = dprintf("%su.", struct_path);
	for (variant_node* vp = variants; vp != NULL; vp = vp->next) {
	    vp->attrib(ctx);
	}
	struct_path = save_path;
    } else {
	for (variant_node* vp = variants; vp != NULL; vp = vp->next) {
	    vp->attrib(ctx);
	}
    }
}

void variant_part_node::translate(int ctx)
{
    f_tkn = t_case;
    l_tkn = t_of;
    for (variant_node* vp = variants; vp != NULL; vp = vp->next) {
	vp->translate(ctx);
	l_tkn = vp->l_tkn;
    }

    selector->tag_type->translate(ctx);

    if (selector->tag_field != NULL) {
	assert(selector->tag_type->type->name != NULL);
	t_case->set_trans(selector->tag_type->type->name);
	if (selector->tag_field->next != t_of) {
	    token::disable(selector->tag_field->next, t_of->prev);
	}
	selector->tag_field->append(";\n");
	t_of->set_trans("union {");
	t_of->set_bind(t_case);
    } else {
	t_case->set_trans("union ");
	t_case->append("{");
	token::disable(t_case->next->next, t_of);
    }
    l_tkn = l_tkn->append("\n");
    if (language_c && ctx != ctx_union) {
	l_tkn = l_tkn->append("} u");
    } else {
	l_tkn = l_tkn->append("}");
    }
    l_tkn->set_bind(t_case);
    if (ctx != ctx_union) {
	force_semicolon();
    }
}

field_list_node::field_list_node(var_decl_node* fix_part,
				 variant_part_node* var_part)
{
    CONS2(fix_part, var_part);
}

int field_list_node::is_single()
{
    return (var_part == NULL && (fix_part == NULL ||
	(fix_part->vars->next == NULL && fix_part->next == NULL)));
}

void field_list_node::attrib(int)
{
    ctx = (smart_union && fix_part == NULL && var_part != NULL
	   && var_part->selector->tag_field == NULL)
	? ctx_union : ctx_record;

    for (decl_node *dcl = fix_part; dcl != NULL; dcl = dcl->next) {
	dcl->attrib(ctx);
    }
    if (var_part) {
	int save_number = variant_node::number;
	variant_node::number = 0;
	var_part->attrib(ctx);
	variant_node::number = save_number;
    }
}

void field_list_node::translate(int)
{
    f_tkn = l_tkn = NULL;

    for (decl_node *dcl = fix_part; dcl != NULL; dcl = dcl->next) {
	dcl->translate(ctx);
	if (f_tkn == NULL) f_tkn = dcl->f_tkn;
	l_tkn = dcl->l_tkn;
    }
    if (var_part) {
	var_part->translate(ctx);
	if (f_tkn == NULL) f_tkn = var_part->f_tkn;
	l_tkn = var_part->l_tkn;
    }
    if (l_tkn != NULL) {
	force_semicolon();
    }
}

object_tpd_node::object_tpd_node(token* t_object,
				 token* t_lbr, token* t_superclass, token* t_rbr,
				 decl_node* fields, token* t_end)
: tpd_node(tpd_object)
{
    CONS6(t_object, t_lbr, t_superclass, t_rbr, fields, t_end);
}

void object_tpd_node::attrib(int)
{
    if (t_superclass != NULL) {
	super = b_ring::search_cur(t_superclass);
	if (super == NULL) {
	    warning("Base class %s not defined\n", t_superclass->out_text);
	    type = new object_tp(this);
	} else {
	    type = new object_tp(this, (object_tp*)super->type->get_typedef());
	}
    } else {
	type = new object_tp(this);
    }
    b_ring::push((object_tp*)type);
    for (decl_node* dcl = fields; dcl != NULL; dcl = dcl->next) {
	dcl->attrib(ctx_object);
    }
    b_ring::pop((object_tp*)type);
}

void object_tpd_node::translate(int)
{
    f_tkn = t_object;
    l_tkn = t_end;
    if (t_superclass != NULL) {
	if (super) {
	    super->translate(t_superclass);
	}
	t_lbr->set_trans(" : public ");
	t_rbr->set_trans(" {\n");
	t_rbr->append("public:")->set_bind(t_object);
    } else {
	t_object->append(" {\n")->append("public:")->set_bind(t_object);
    }

    for (decl_node* dcl = fields; dcl != NULL; dcl = dcl->next) {
	dcl->translate(ctx_object);
    }
    t_object->set_trans("class ");
    t_end->set_trans("}");
    t_end->set_bind(t_object);
}


record_tpd_node::record_tpd_node(token* t_packed, token* t_record,
				 field_list_node* fields, token* t_end)
: tpd_node(tpd_record)
{
    CONS4(t_packed, t_record, fields, t_end);
}

void record_tpd_node::attrib(int ctx)
{
    type = new record_tp(this);
    static record_tpd_node* cur_outer;
    outer = cur_outer;
    cur_outer = this;
    char* save_path = struct_path;
    struct_path = "";
    b_ring::push((record_tp*)type);
    fields->attrib(ctx);
    ((record_tp*)type)->calc_flags();
    b_ring::pop((record_tp*)type);
    struct_path = save_path;
    cur_outer = outer;
}

void record_tpd_node::translate(int ctx)
{
    fields->translate(ctx);
    f_tkn = t_record;
    l_tkn = t_end;
    if (smart_union && fields->fix_part == NULL && fields->var_part != NULL
	&& fields->var_part->selector->tag_field == NULL)
    {
	fields->var_part->t_case->set_pos(t_record);
        t_record->disappear();
	t_end->disappear();
	swallow_semicolon();
	f_tkn = t_record = fields->var_part->t_case;
	l_tkn = t_end = fields->var_part->l_tkn;
    } else {
	t_record->set_trans("struct ");
	t_record->append("{");
	t_end->set_trans("}");
	t_end->set_bind(t_record);
    }

    if (t_packed) {
      	t_packed->disable();
    }
}


void record_tpd_node::assign_name()
{
    static int anonymous_struct_counter = 0;

    assert(tag == tpd_record || tag == tpd_object);

    char* name = dprintf("A%d", ++anonymous_struct_counter);
    t_record->append(dprintf("%s ", name));

    if (language_c) {
	type->name = dprintf("%s%s", t_record->out_text, name);
    } else {
	if (tag == tpd_record && outer != NULL) {
	    if (outer->type->name == NULL) {
		outer->assign_name();
	    }
	    type->name = dprintf("%s::%s", outer->type->name, name);
	} else {
	    type->name = name;
	}
    }
}

file_tpd_node::file_tpd_node(token* t_packed, token* t_file, token* t_of, tpd_node* recordtp)
: tpd_node(tpd_file)
{
    CONS4(t_packed, t_file, t_of, recordtp);
}

void file_tpd_node::attrib(int ctx)
{
    recordtp->attrib(ctx);
    type = new file_tp(recordtp->type, this);
}

void file_tpd_node::translate(int ctx)
{
    recordtp->translate(ctx);
    f_tkn = t_file;
    token::disable(t_file->next, recordtp->f_tkn->prev);

    if (t_packed) {
       	t_packed->disable();
    }
    if (language_c) {
	recordtp->f_tkn->prepend("(");
	l_tkn = recordtp->l_tkn->append(")");
    } else {
	recordtp->f_tkn->prepend("<");
	l_tkn = recordtp->l_tkn->append(">");
    }
}


set_tpd_node::set_tpd_node(token* t_packed, token* t_set, token* t_of,
			   tpd_node* elemtp)
: tpd_node(tpd_set)
{
    CONS4(t_packed, t_set, t_of, elemtp);
}

void set_tpd_node::attrib(int ctx)
{
    elemtp->attrib(ctx);
    type = new set_tp(elemtp->type);
}

void set_tpd_node::translate(int ctx)
{
    elemtp->translate(ctx);
    l_tkn = f_tkn = t_set;
    if (t_packed) {
	t_packed->disable();
    }
    if (!language_c  && elemtp->type->tag == tp_enum) {
	t_set->set_trans("set_of_enum(");
	token::disable(t_set->next, elemtp->f_tkn->prev);
	l_tkn = elemtp->l_tkn->append(")");
    } else {
	if (language_c && short_set) {
	    int card = ((set_tp*)type)->card();
	    if (card <= 16) t_set->set_trans("set16");
	    else if (card <= 32) t_set->set_trans("set32");
	}
	token::disable(t_set->next, elemtp->l_tkn);
    }
}

