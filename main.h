#ifndef __MAIN_H__
#define __MAIN_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

#define items(a) (sizeof(a) / sizeof(*(a)))

#define bool int
#ifndef TRUE
  #define TRUE 1
  #define FALSE 0
#endif

#define VERSION "3.50"

// Some declarations 

extern bool language_c; 
extern bool no_array_assign_operator;
extern bool compile_system_library; 
extern bool small_enum;
extern bool unsigned_comparison; 
extern bool nological;
extern bool force_logical;
extern bool turbo_pascal;
extern bool use_c_strings;
extern bool extern_vars;
extern bool preserve_case;
extern bool nested_comments;
extern bool copy_array;
extern bool comment_tags;
extern bool use_namespaces;
extern bool smart_union;
extern bool no_index_decrement;
extern bool ignore_preprocessor_directives;
extern bool hp_pascal;
extern bool do_not_use_enums;
extern char* pascall;
extern char path_sep;

#define CALL_GRAPH_FILE     "call.grp"
#define RECURSIVE_PROC_FILE "recur.prc"
#ifdef PREFIX
#define CONFIG_FILE         PREFIX "/etc/ptoc.cfg"
#else
#define CONFIG_FILE         "ptoc.cfg"
#endif

#ifdef _WIN32
#define PATH_SEP '\\'
#else
#define PATH_SEP '/'
#endif

extern bool  use_call_graph;
extern bool  pio_init;
extern bool  short_set; 
extern FILE* call_graph_file;
bool is_recursive_proc(const char* name); 

void scanner_input(char *file); 

class memory_allocator { 
  private:
    size_t   free;
    char*    ptr;
  public:
    void* alloc(size_t size) { 
	const size_t alloc_quant = 8;
	const size_t alloc_block = 1024*1024;
	
	size = (size + alloc_quant - 1) & ~(alloc_quant - 1);
	if (size > free) { 
	    free = (alloc_block < size) ? size : alloc_block; 
	    ptr = (char*)malloc(free);
	}
	free -= size;
	void* t = (void*)ptr;
	ptr += size;
	return t; 
    }
    memory_allocator() { free = 0; }
};

extern memory_allocator heap;

class heap_object { 
  public: 
    void* operator new(size_t size) { return heap.alloc(size); }
}; 

#endif

