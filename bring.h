
// -*- C++ -*-
// Binding rings (lists actually)
#ifndef __BRING_H__
#define __BRING_H__

#include "main.h"

class b_ring;
class tpexpr;

// Element of binding contour: variable, type or label
class symbol : public heap_object {
  public:
    symbol	*next;
    nm_entry 	*in_name;
    nm_entry    *out_name;        
    char        *path;     // path to component in structure    
    b_ring	*ring;
    enum {
      s_var,    // variable
      s_ref,    // reference 
      s_const,  // constant
      s_type,   // type
      s_proc,   // procedure
      s_label,  // label   
      s_dummy   // dummy symbol, used only to preserve name in namespace 
    };
    int		tag;

    enum {
        f_used 		= 0x01, // 
	f_defined	= 0x02, // 
        f_val_param     = 0x04, // variable is parameter passed by values
        f_var_param     = 0x08, // variable is VAR parameter passsed b
	f_exported      = 0x10, // variable is accessed by nexted function
	f_static        = 0x20, // variable is static
	f_syslib        = 0x40, // symbol from system library        
	f_const         = 0x80, // integer constant is stored in "value"
	f_lvalue        = 0x100 // variable is used as lvalue
    };
    int	        flags;
    int         value;  
    tpexpr	*type;

    void translate(token* t);
};

// Binding contour
class b_ring {
  public:
    b_ring(int scope);

    b_ring	*outer;
    b_ring	*inherite;
    symbol	*syms;
    symbol      *with; // WITH variable for RECORD ring  


    // Kinds of binding contours
    enum {
	block, record, proc, global
    };

    int    scope;

    static b_ring global_b_ring;
    static b_ring *curr_b_ring;
    static b_ring *top_b_ring;

    static bool push(b_ring* r) {
        /*
        if (r->outer != NULL) { 
            r = new b_ring(r->scope);
        }
        */
        for (b_ring* curr = curr_b_ring; curr != NULL; curr = curr->outer) { 
            if (curr == r) { 
                return false;
            }
        }
        r->outer = curr_b_ring;
        curr_b_ring = r;
        return true;
    }

    static bool pop(b_ring* top) {
        if (curr_b_ring == top) { 
            curr_b_ring = top->outer;
            top->outer = NULL;
            return true;
        }
        return false;
    }
    static b_ring* pop() {
        b_ring* top = curr_b_ring;
        curr_b_ring = curr_b_ring->outer;
        top->outer = NULL;
        return top;
    }

    symbol* search(token* t);
    symbol* shallow_search(token* t);
    symbol* add(nm_entry* in_name, nm_entry* out_name, int tag, tpexpr* type);
    symbol* add(nm_entry* in_name, int tag, tpexpr* type) { 
        return add(in_name, in_name, tag, type);
    }
    static symbol* search_cur(token* t) { return curr_b_ring->search(t); }
    static symbol* add_cur(token* t, int tag, tpexpr* type) {
        return 
          curr_b_ring->add(t->name, 
			   (strcmp(t->name->text, t->out_text) == 0) 
			    ? t->name : nm_entry::add(t->out_text, TKN_IDENT), 
			   tag, type);
    }
    static symbol* add_cur(nm_entry* in_nm, nm_entry* out_nm, 
			   int tag, tpexpr* type)
      { return curr_b_ring->add(in_nm, out_nm, tag, type); }

    static symbol* add_cur(nm_entry* nm, int tag, tpexpr* type)
      { return curr_b_ring->add(nm, tag, type); }

    bool find_scope(b_ring* type);

    void make_unique(symbol* s);
    void make_vars_static(); 
};

class rename_item { 
  protected:
    static rename_item* list;

    rename_item* next; 
    nm_entry*    nm_old;
    nm_entry*    nm_new;
    
  public:
    static void add(nm_entry *nm_new, nm_entry *nm_old) {
	rename_item* item = new rename_item;
	item->nm_new = nm_new;
	item->nm_old = nm_old;
	item->next = list;
	list = item;
    }
    static nm_entry* rename(nm_entry* name) { 
	for (rename_item *item = list; item != NULL; item = item->next) { 
	    if (item->nm_old == name) return item->nm_new;
	}
	return name;
    }
};

#endif
