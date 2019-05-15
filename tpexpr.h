// Type expressions.

#ifndef __TPEXPR_H__
#define __TPEXPR_H__

#include "bring.h"

enum type_tag {
    tp_void, tp_any, 
    tp_real, tp_double, tp_integer, tp_longint, 
    tp_char, tp_string, tp_varying_string, tp_bool, tp_set, 
    tp_enum, tp_range, tp_proc, tp_array, tp_dynarray, tp_record, tp_ref,
    tp_file, tp_text, tp_fwd_ref, tp_unit, tp_object,
    tp_last	// Not a type really
};
enum type_flags { 
    tp_need_init = 1 /* variable of this type should be initilialized by 0 */
    /* this flag is set if it is file type or contains file variable       */
};

class param_spec : public heap_object { 
  public: 
    param_spec *next; 
    symbol     *var;

    param_spec(symbol* variable) { 
	var = variable, next = NULL; 
    }
}; 

//---------------------------------------------------------------

class tpd_node; 

class tpexpr : public heap_object {
  public:
    int      tag;
    int      flags;
    char     *name;
    tpd_node *tpd; 

    bool is_scalar() { 
        return tag == tp_char || tag == tp_integer 
	    || tag == tp_real || tag == tp_range || tag == tp_enum; 
    }

    token*  insert_before(token *t);     
    virtual tpexpr* get_typedef(); 
    virtual bool is_reference();
    virtual bool is_array();

    tpexpr(int tp_tag, tpd_node* tp_tpd = NULL, char* tp_name = NULL) { 
         tag = tp_tag;
	 tpd = tp_tpd;
	 name = tp_name;
	 flags = 0;
    }
};

class simple_tp : public tpexpr { 
  public:
    tpexpr* alias;
    virtual tpexpr* get_typedef(); 
    virtual bool is_reference();
    virtual bool is_array();
 
    simple_tp(tpexpr* def) : tpexpr(def->tag, def->tpd) { alias = def; }
};


// Node for reference type
class ref_tp : public tpexpr {
  public:
    tpexpr*   base_type;

    virtual bool is_reference();
    ref_tp(tpexpr* tp = NULL, tpd_node* tpd = NULL);
};

class fwd_ref_tp : public ref_tp {
  public:
    token* ident;

    virtual tpexpr* get_typedef(); 
    fwd_ref_tp(token* t);
};

class enum_tp : public tpexpr {
  public:
    int     n_elems;
    char   *max;
    symbol *first;
    symbol *last;

    void   set_enumeration_name(tpexpr* type);

    enum_tp(tpd_node* tpd = NULL) : tpexpr(tp_enum, tpd) { max = NULL; }
    void set_bounds(symbol* name);
};


class range_tp : public tpexpr {
  public:
    char*  min;
    char*  max;
    int    min_value; 
    int    max_value; 
    int    size;  // size of type representing range 
 
    range_tp(tpd_node* tpd = NULL) : tpexpr(tp_range, tpd) {
	min_value = max_value = 0;
        min = max = NULL;
	size = 0;
    }
    void set_bounds(symbol* name);
};

// Node for varying string

// Node for array type

class expr_node;
class proc_tp;

class array_tp : public tpexpr {
  public:
    tpexpr     *elem_type; // type of conmponent
    symbol     *low_var;   // low bound of conformant array
    symbol     *high_var;  // high bound of conformant array
    char       *low;      
    char       *high;  
    expr_node  *low_expr;  
    expr_node  *high_expr;  
    int        base;

    virtual bool   is_array();

    void           set_dim(char *low, char *high, 
			   expr_node *low_expr = NULL, 
			   expr_node *high_expr = NULL);
    void           set_conformant_dim(symbol* slow, 
				      symbol* shigh);
    virtual void   insert_dimensions(expr_node* e, array_tp* conf_arr = NULL,
				    int n = 0);
    void           insert_length(token* t);
    void           insert_bound_params(token* before);
    void           add_proc_param(proc_tp* proc);

    // definition of conmformant array variables
    void insert_bounds_definition(symbol* array, token* before, int n = 0); 

    array_tp(tpexpr* tp = NULL, tpd_node* tpd = NULL);
};

class string_tp : public array_tp { 
  public: 
    virtual void  insert_dimensions(expr_node *e, array_tp*, int);
    string_tp();
};

class varying_string_tp : public array_tp { 
  public: 
    varying_string_tp();
};

#define MAX_SET_CARD   256
#define SHORT_SET_CARD 32

class set_tp : public tpexpr { 
  public: 
    tpexpr* elem_type;
    bool is_short_set() { return card() <= SHORT_SET_CARD; }
    unsigned card() { return elem_type->tag == tp_enum 
			  ? ((enum_tp*)elem_type->get_typedef())->n_elems
			  : MAX_SET_CARD; 
    }
    set_tp(tpexpr* etype = NULL) : tpexpr(tp_set, NULL, "set") {
	elem_type = etype; 
    }
};

class file_tp : public ref_tp { 
  public: 
    file_tp(tpexpr* record_type = NULL, tpd_node* tpd = NULL) 
    : ref_tp(record_type, tpd)
      { tag = tp_file; flags |= tp_need_init; }
};

class text_tp : public file_tp { 
  public: 
    text_tp();
};

// Node for record type
class record_tp : public tpexpr, public b_ring {
  public:
    void calc_flags(); 
    record_tp(tpd_node *tpd = NULL) 
	: tpexpr(tp_record, tpd), b_ring(b_ring::record)
  {}
};

class unit_tp : public record_tp { 
  public: 
    unit_tp(tpd_node *tpd = NULL) : record_tp(tpd) { 
	tag = tp_unit;
    } 
};

class object_tp : public record_tp { 
  public: 
    symbol* class_name;
    object_tp(tpd_node *tpd, object_tp* super = NULL); 
};

class proc_tp; 

class caller_spec : public heap_object { 
  public:
    caller_spec *next; 
    proc_tp     *caller;

    caller_spec(proc_tp *func) { caller = func, next = NULL; } 
};


class define_spec : public heap_object { 
  public: 
    define_spec *next;
    symbol      *sym;

    define_spec(symbol* defsym, define_spec* chain) { 
	sym = defsym;
	next = chain; 
    }
};

class proc_fwd_decl_node; 

class temp_spec : public heap_object {
  public: 
    tpexpr*    type; 
    temp_spec* next;
    
    temp_spec(tpexpr* tp) { type = tp; next = NULL; } 
};


// Node for procedure type
class proc_tp : public tpexpr, public b_ring {
  public:
    tpexpr         *res_type;
    param_spec     *params;
    param_spec     *last; 
    param_spec     *extra_params; 
    char           *proc_name;          

    define_spec    *define_list;  // list of macros defined in procedure

    temp_spec      *temp_list;    // list of temporary variable 
    temp_spec      *last_temp;    // generated for procedure
    int            n_temp;
    int            n_subproc;
    int            make_all_constants_global;
    bool           is_extern_c;
    bool           is_constructor;
    bool           is_destructor;

    proc_fwd_decl_node *forward;
     
    caller_spec    *callers;    

    bool is_function_pointer() { return proc_name == NULL; }

    void add_define(symbol* v);
    void undefine(token* after);

    void add_param(symbol *v); 
    void add_extra_param(symbol *v);
    void add_caller(proc_tp* func);
    void declare_conformant_array_bounds(token* before);  

    char* add_temp(tpexpr* type);
    void  insert_temporaries(token* before);

    bool is_function() { return res_type != NULL; }

    proc_tp(tpexpr* rtype = NULL, tpd_node *tpd = NULL); 
};

extern tpexpr    integer_type;
extern tpexpr    real_type;
extern tpexpr    double_type;
extern tpexpr    longint_type;
extern tpexpr    char_type;
extern tpexpr    void_type;
extern tpexpr    any_type;
extern tpexpr    bool_type;
extern set_tp    set_type;
extern string_tp string_type;
extern text_tp   text_type;
extern ref_tp    pointer_type;
extern varying_string_tp varying_string_type;

#endif
