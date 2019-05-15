#include "main.h"

#define CALL_GRAPH_FILE     "call.grp"
#define RECURSIVE_PROC_FILE "recur.prc"

class proc_desc;

class call_spec { 
  public:
    call_spec* next;
    proc_desc* callee;

    call_spec(proc_desc* desc, call_spec* chain) 
    { next = chain; callee = desc; }
};    

#define HASH_TABLE_SIZE 1987 

class proc_desc { 
  protected:
    proc_desc*        next; // collision chain
    static proc_desc* table[ HASH_TABLE_SIZE ];

  public:
    call_spec* chain;
    char*      name;
    
    enum { called=1, recursive=2 };
    int        tag;

    void   call(proc_desc* callee) { chain = new call_spec(callee, chain); } 
    void   closure();

    static proc_desc* add(char* proc_name); 
    static void       analyse();
    static void       output(FILE* f);

    proc_desc(char* proc_name) 
	: chain(NULL), name(strdup(proc_name)), tag(0) {} 
};

proc_desc* proc_desc::table[HASH_TABLE_SIZE];

proc_desc* proc_desc::add(char* name) 
{
    proc_desc* p;
    unsigned h = 0;
    unsigned c;
    char* s = name;
    
    while ((c = (unsigned)*s++) != 0) {
        h = (h<<1) + c;
    }

    int hash_value = h % HASH_TABLE_SIZE;
    for (p = table[hash_value]; p != NULL; p = p->next) { 
	if (strcmp(name, p->name) == 0) return p;
    }
    p = new proc_desc(name);
    p->next = table[hash_value];
    table[hash_value] = p;
    return p;
}    
    
void proc_desc::analyse() { 
    for (int i = 0; i < HASH_TABLE_SIZE; i++ ) { 
	for (proc_desc* p = table[i]; p != NULL; p = p->next) { 
	    p->closure();
	}
    }
}
    
void proc_desc::output(FILE* f) { 
    for (int i = 0; i < HASH_TABLE_SIZE; i++ ) { 
	for (proc_desc* p = table[i]; p != NULL; p = p->next) { 
	    if (p->tag & recursive) { 
		fprintf(f,"%s\n", p->name); 
	    }
	}
    }
}
    
void proc_desc::closure() { 
    if (tag & called) { 
	tag |= recursive; 
    } else { 
	tag |= called; 
	for (call_spec* c = chain; c != NULL; c = c->next) { 
	    c->callee->closure();
	} 
	tag &= ~called;
    }
}
    

int main() { 
    FILE* in = fopen(CALL_GRAPH_FILE, "r");
    FILE* out = fopen(RECURSIVE_PROC_FILE, "w");

    if (in == NULL || out == NULL) { 
	fputs("Error while opening files...\n", stderr);
	return 1;
    }
    char callee[256];
    char caller[256];
    while (fscanf(in, "%s -> %s", caller, callee) == 2) { 
	proc_desc::add(caller)->call(proc_desc::add(callee)); 
    }
    proc_desc::analyse();
    proc_desc::output(out);

    fclose(in);
    fclose(out);
    return 0;
}
	  
	


