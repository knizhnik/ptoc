#include <string.h>

#include "nmtbl.h"
#include "token.h"
#include "trnod.h"
#include "util.h"

tpexpr void_type(tp_void, NULL, "void");
tpexpr any_type(tp_any, NULL, "void*");
tpexpr integer_type(tp_integer, NULL, "integer");
tpexpr longint_type(tp_longint, NULL, "longint");
tpexpr real_type(tp_real, NULL, "real");
tpexpr double_type(tp_real, NULL, "double");
tpexpr char_type(tp_char, NULL, "char");
tpexpr bool_type(tp_bool, NULL, "boolean");
ref_tp pointer_type(&void_type); 
string_tp string_type;
varying_string_tp varying_string_type;
text_tp text_type;


//---------------------------------------------------------------------

token *tpexpr::insert_before(token *t)
{ 
    return (name != NULL) 
        ? t->prepend(name) 
        : t->copy(tpd->f_tkn, tpd->l_tkn);
}


tpexpr* tpexpr::get_typedef() { return this; }

bool tpexpr::is_reference() { return FALSE; }

bool tpexpr::is_array() { return FALSE; }

//---------------------------------------------------------------------

tpexpr* simple_tp::get_typedef() { return alias->get_typedef(); }

bool simple_tp::is_reference() { return alias->is_reference(); }
bool simple_tp::is_array()     { return alias->is_array(); }

//---------------------------------------------------------------------

ref_tp::ref_tp(tpexpr* tp, tpd_node* tpd) 
: tpexpr(tp_ref, tpd), base_type(tp) 
{
  if (tp != NULL && tp->name != NULL) { 
	name = dprintf("%s*", tp->name); 
    } 
}

bool ref_tp::is_reference() { return TRUE; }

//---------------------------------------------------------------------

fwd_ref_tp::fwd_ref_tp(token* t) 
{
    tag = tp_fwd_ref; 
    ident = t;
    name = dprintf("struct %s*", t->out_text); 
}


tpexpr* fwd_ref_tp::get_typedef() 
{
    if (tag == tp_fwd_ref) { 
        symbol *sym = b_ring::search_cur(ident);
        if (sym != NULL) {
            base_type = sym->type;
	    tag = tp_ref;
        }
    }
    return this;
}

//---------------------------------------------------------------------

void enum_tp::set_bounds(symbol* var)
{ 
    max = dprintf("last_%s", var->out_name->text); 
}
   

void enum_tp::set_enumeration_name(tpexpr* type) 
{
    symbol* sym = last; 
    do { 
	sym->type = type;
	if (sym == first) break;
	sym = sym->next;
    } while (TRUE);
}
    

//---------------------------------------------------------------------

void range_tp::set_bounds(symbol* var)
{ 
    max = dprintf("max_%s", var->out_name->text); 
    min = dprintf("min_%s", var->out_name->text);
}
   
//---------------------------------------------------------------------

array_tp::array_tp(tpexpr* tp, tpd_node* tpd) 
: tpexpr(tp_array, tpd), elem_type(tp)
{
    flags |= tp->get_typedef()->flags & tp_need_init;
    low = high = NULL;
    low_expr = high_expr = NULL;
    base = -1;
}

bool array_tp::is_array() { return TRUE; }

void array_tp::insert_bounds_definition(symbol* array, token* block, int n)
{ 
    if (elem_type->tag == tp_dynarray || n > 0) n += 1;

    block->prepend(dprintf("const int %s = %s.%s%.0d;\n", 
			   low, array->out_name->text, "low", n)); 
    block->prepend(dprintf("const int %s = %s.%s%.0d;\n", 
			   high, array->out_name->text, "high", n)); 

    if (elem_type->tag == tp_dynarray) { 
	((array_tp*)elem_type->get_typedef())->
	    insert_bounds_definition(array, block, n);
    }
}

void array_tp::set_dim(char *low, char *high, 
		       expr_node *low_expr, expr_node *high_expr)
{
    this->low = low;
    this->high = high;
    this->low_expr = low_expr;
    this->high_expr = high_expr;
    
    if (low != NULL && strcmp(low, "0") == 0) { 
	base = 0;
    } else if (low_expr != NULL && low_expr->is_const_literal())  { 
	base = low_expr->value;
    }
}

void array_tp::set_conformant_dim(symbol* low_sym, symbol* high_sym)
{ 
    low_var = low_sym;
    high_var = high_sym;
    low = low_sym->out_name->text; 
    high = high_sym->out_name->text; 
    low_expr = high_expr = NULL;
    tag = tp_dynarray;
}

void array_tp::insert_dimensions(expr_node* e, array_tp* conf_arr, int n)
{
    token *t = e->f_tkn; 

    if (low == NULL) { 
	assert(low_expr != NULL);
	t->copy(low_expr->f_tkn, low_expr->l_tkn);
    } else { 
	t->prepend(low);
    }
    t->prepend(", ");
    if (!e->is_parameter() && (base == 0 || base == 1)) {
	t->prepend(dprintf("items(%.*s", n, "****************"));
	t->copy(e->f_tkn, e->l_tkn);
	t->prepend(base == 0 ? ")-1" : ")");
    } else { 
	if (high == NULL) { 
	    assert(high_expr != NULL);
	    t->copy(high_expr->f_tkn, high_expr->l_tkn);
	} else { 
	    t->prepend(high);
	}
    }
    t->prepend(", ");

    if (conf_arr && conf_arr->elem_type->tag == tp_dynarray) {
	if (elem_type->tag != tp_array) { 
	    warning(e->f_tkn, "array is incompatible with conformant scheme");
	} else {  
	    ((array_tp*)elem_type->get_typedef())->
		insert_dimensions(e, (array_tp*)conf_arr->elem_type, n + 1);
	}
	if (tag != tp_dynarray) { 
	    e->f_tkn->prepend("*");
	}
    } 
}


void array_tp::insert_length(token* before) 
{
    if (base == 0 || no_index_decrement) { 
	if (high != NULL) { 
	    before->prepend(dprintf("(%s+1)", high));
	} else {
	    assert(high_expr != NULL);
	    if (high_expr->is_const_literal()) { 
		before->prepend(dprintf("%d", high_expr->value + 1));
	    } else { 
		before->prepend("(");
		before->copy(high_expr->f_tkn, high_expr->l_tkn);
		before->prepend("+1)");
	    }
	}
    } else if (base == 1) { 
	if (high != NULL) { 
	    before->prepend(high);
	} else {
	    assert(high_expr != NULL);
	    before->copy(high_expr->f_tkn, high_expr->l_tkn);
	}
    } else { 
	if (high != NULL && low != NULL) {
	    before->prepend(dprintf("(%s-%s+1)", high, low));
	} else { 
	    assert(high_expr != NULL && low_expr != NULL);
	    before->prepend("((");
	    before->copy(high_expr->f_tkn, high_expr->l_tkn);
	    before->prepend(")-(");
	    before->copy(low_expr->f_tkn, low_expr->l_tkn);
	    before->prepend(")+1)");
	}
    }
    if (elem_type->tag == tp_dynarray) { 
	((array_tp*)elem_type)->insert_bound_params(before);
    }
}

void array_tp::insert_bound_params(token* before) 
{ 
    assert(low != NULL && high != NULL);
    before->prepend(dprintf("const integer %s, const integer %s, ",
			    low, high));
    if (elem_type->tag == tp_dynarray) { 
	((array_tp*)elem_type)->insert_bound_params(before);
    }
}

void array_tp::add_proc_param(proc_tp* proc) 
{
    proc->add_extra_param(low_var);
    proc->add_extra_param(high_var);
    if (elem_type->tag == tp_dynarray) { 
	((array_tp*)elem_type)->add_proc_param(proc);
    }
} 

//---------------------------------------------------------------------

text_tp::text_tp() : file_tp(&char_type) { 
    tag = tp_text; 
    name = "text";
}

//---------------------------------------------------------------------

void record_tp::calc_flags()
{
    for (symbol *sym = syms; sym != NULL; sym = sym->next) {
	flags |= sym->type->get_typedef()->flags;
    }
}
    
//---------------------------------------------------------------------


object_tp::object_tp(tpd_node *tpd, object_tp* super) : record_tp(tpd)
{ 
    tag = tp_object;
    class_name = NULL;
    inherite = super;
} 



//---------------------------------------------------------------------

string_tp::string_tp() : array_tp(&char_type)  
{
    tag = tp_string;
    base = 1;
    low = "1";
    name = "char*";
}

void string_tp::insert_dimensions(expr_node* e, array_tp* conf_arr, int n)
{
    e->f_tkn->prepend("array(");
    e->l_tkn->append(")");
}

//---------------------------------------------------------------------

varying_string_tp::varying_string_tp() : array_tp(&char_type)  
{
    tag = tp_varying_string;
    base = 1;
    low = "1";
    name = "string";
}

//---------------------------------------------------------------------

proc_tp::proc_tp(tpexpr* rtype, tpd_node* tpd) 
: tpexpr(tp_proc, tpd), b_ring(b_ring::proc)
{ 
    params = last = NULL;
    extra_params = NULL; 
    callers = NULL; 	
    res_type = rtype;
    forward = NULL; 
    proc_name = NULL; 
    define_list = NULL;
    last_temp = temp_list = NULL;
    n_temp = 0;
    n_subproc = 0;
    make_all_constants_global = FALSE;
    is_extern_c = FALSE;
    is_constructor = FALSE;
    is_destructor = FALSE;
}

void proc_tp::add_param(symbol *var) 
{ 
    if (last == NULL) { 
        params = last = new param_spec(var); 
    } else { 
        last = last->next = new param_spec(var); 
    }
}   

void proc_tp::add_extra_param(symbol *var) 
{ 
    param_spec **pp, *p;
  
    if (var->ring == this) return; 

    if (var->ring->scope == b_ring::proc && var->type
	&& !var->type->is_scalar() && var->type->get_typedef() == var->type) 
    { 
	((proc_tp*)var->ring)->make_all_constants_global = TRUE;
    }

    if (language_c && var->type->tag == tp_dynarray) { 
	((array_tp*)var->type)->add_proc_param(this);
    }
    for (pp = &extra_params; (p = *pp) != NULL; pp = &p->next) { 
        if (p->var == var) return; 
    }
    *pp = new param_spec(var);
    var->flags |= symbol::f_exported;

    for (caller_spec *f = callers; f != NULL; f = f->next) { 
         f->caller->add_extra_param(var); 
    } 
} 

void proc_tp::add_caller(proc_tp* f) 
{ 
    caller_spec *cp, **cpp;
   
    if (f == this || f == NULL || proc_name == NULL) return;

    for (cpp = &callers; (cp = *cpp) != NULL; cpp = &cp->next) { 
        if (cp->caller == f) return; 
    }  
    *cpp = new caller_spec(f); 
    if (use_call_graph && call_graph_file != NULL && f->proc_name != NULL) { 
	fprintf(call_graph_file, "%s -> %s\n", f->proc_name, proc_name);  
    }
    for (param_spec *p = extra_params; p != NULL; p = p->next) { 
        f->add_extra_param(p->var); 
    }
}    
   
 
void proc_tp::declare_conformant_array_bounds(token* section)
{
    param_spec* prm;
    tpexpr*     prev_type = NULL;

    for (prm = params; prm != NULL; prm = prm->next) { 
        if (prm->var->type->tag == tp_dynarray) { 
	    if (prm->var->type != prev_type) {  
		((array_tp*)prm->var->type)->insert_bounds_definition
		    (prm->var, section); 
		prev_type = prm->var->type;
	    }
	    if ((prm->var->flags & symbol::f_val_param)
		&& (copy_array || (prm->var->flags & symbol::f_lvalue))) 
	    { 
		section->prepend(dprintf("copy_conformant_array(%s);\n", 
					 prm->var->out_name->text));
	    }
        }
    }
    for (prm = extra_params; prm != NULL; prm = prm->next) { 
        if (prm->var->type->tag == tp_dynarray) { 
	    if (prm->var->type != prev_type) {  
		((array_tp*)prm->var->type)->insert_bounds_definition
		    (prm->var, section); 
		prev_type = prm->var->type;
	    }
	    if ((prm->var->flags & symbol::f_val_param)
		&& (copy_array || (prm->var->flags & symbol::f_lvalue))) 
	    { 
		section->prepend(dprintf("copy_conformant_array(%s);\n", 
					 prm->var->out_name->text));
	    }
	}
    }
}  

void proc_tp::add_define(symbol* s) 
{ 
    define_list = new define_spec(s, define_list);
}

void proc_tp::undefine(token* t) 
{
    if (define_list != NULL) {
	t = t->append("\n\n");
    }
    for (define_spec* def = define_list; def != NULL; def = def->next) { 
	t = t->append(dprintf("#undef %s\n", def->sym->out_name->text));
    }
}

char* proc_tp::add_temp(tpexpr* type) 
{ 
    if (last_temp == NULL) { 
	temp_list = last_temp = new temp_spec(type);
    } else { 
	last_temp = last_temp->next = new temp_spec(type);
    }
    return dprintf("temp%d", ++n_temp);
}

void proc_tp::insert_temporaries(token* t) 
{ 
    int n = 0;
    for (temp_spec* ts = temp_list; ts != NULL; ts = ts->next) { 
	assert(ts->type->name != NULL);
	t->prepend(dprintf("%s temp%d;\n", ts->type->name, ++n)); 
    }
}
