#include <string.h>
#include <stdlib.h>

#include "main.h"
#include "nmtbl.h"
#include "token.h"
#include "trnod.h"
#include "util.h"

extern int zzparse();

static void load_predefined() 
{ 
    b_ring::add_cur(nm_entry::add("integer", TKN_IDENT), 
				  symbol::s_type, 
				  &integer_type);
    b_ring::add_cur(nm_entry::add("real", TKN_IDENT), 
				  symbol::s_type, 
				  &real_type);
    b_ring::add_cur(nm_entry::add("boolean", TKN_IDENT), 
				  symbol::s_type, 
				  &bool_type);
    b_ring::add_cur(nm_entry::add("char", TKN_IDENT),
				  symbol::s_type, 
				  &char_type);
    b_ring::add_cur(nm_entry::add("text", TKN_IDENT), 
				  symbol::s_type, 
				  &text_type);
    b_ring::add_cur(nm_entry::add("zero_terminated_string", TKN_IDENT), 
		    nm_entry::add("char*", TKN_IDENT), 
				  symbol::s_type, 
				  &string_type);
    b_ring::add_cur(nm_entry::add("true", TKN_IDENT), 
				  symbol::s_const, 
				  &bool_type);
    b_ring::add_cur(nm_entry::add("false", TKN_IDENT), 
				  symbol::s_const, 
				  &bool_type);
    b_ring::add_cur(nm_entry::add("nil", TKN_IDENT), 
				  symbol::s_const, 
				  &void_type);
    if (hp_pascal) { 
        nm_entry::add("addr", TKN_ADDR);
    }
    if (turbo_pascal) { 
	b_ring::add_cur(nm_entry::add("pointer", TKN_IDENT), 
			symbol::s_type, 
			&pointer_type);
	b_ring::add_cur(nm_entry::add("pchar", TKN_IDENT), 
			symbol::s_type, 
			&string_type);
	b_ring::add_cur(nm_entry::add("longint", TKN_IDENT), 
			symbol::s_type, 
			&longint_type);
	b_ring::add_cur(nm_entry::add("double", TKN_IDENT), 
			symbol::s_type, 
			&double_type);
	b_ring::add_cur(nm_entry::add("untyped_file", TKN_IDENT), 
			symbol::s_type, 
			&text_type);
	nested_comments = TRUE;
    }
}

static void load_keywords() 
{ 
    for (int tag = 0; tag < TKN_LAST; tag ++ )  {
	if (token::token_cat[tag] == CAT_ID ||
	    token::token_cat[tag] == CAT_KWD) 
	{
	    nm_entry::add(token::token_name[tag], tag); 
	}
    }
}

#define MAX_NAME_LEN 1024

static void load_configuration(char* name) { 
    FILE* cfg = fopen(name, "r");
    if (cfg != NULL) { 
	char buf[MAX_NAME_LEN];

	while (fscanf(cfg, "%s", buf) == 1) { 
	    if (strcmp(buf, "#begin(reserved)") == 0) { 
		while (fscanf(cfg, "%s", buf) == 1 
		       && strcmp(buf, "#end(reserved)") != 0) 
		{
		    nm_entry::add(buf, TKN_RESERVED);
                }
	    } else if(strcmp(buf, "#begin(macro)") == 0) { 
		while (fscanf(cfg, "%s", buf) == 1 
		       && strcmp(buf, "#end(macro)") != 0) 
		{
		    nm_entry::add(buf, TKN_IDENT)->flags |= nm_entry::macro;
		}
	    } else if(strcmp(buf, "#begin(library)") == 0) { 
		while (fscanf(cfg, "%s", buf) == 1 
		       && strcmp(buf, "#end(library)") != 0) 
		{
		    b_ring::global_b_ring.add(nm_entry::add(buf, TKN_IDENT),
					      symbol::s_dummy, 
					      NULL);
		}
	    } else if(strcmp(buf, "#begin(rename)") == 0) { 
		while (fscanf(cfg, "%s", buf) == 1 
		       && strcmp(buf, "#end(rename)") != 0) 
		{
		    nm_entry* nm_old = nm_entry::add(buf, TKN_IDENT);
		    fscanf(cfg, "%s", buf);
		    nm_entry* nm_new = nm_entry::add(buf, TKN_IDENT);
		    rename_item::add(nm_new, nm_old);
		}
	    }
	}
	fclose(cfg);
	if (turbo_pascal) { // sizeof is builtin Pascal function
	    nm_entry* nm_sizeof = nm_entry::find("sizeof");
	    if (nm_sizeof) {
		*nm_sizeof->text = 'S';
	    }
	}
    } else { 
	fprintf(stderr, "Can't open configuration file '%s'\n", 
		name);
    }
}


char *i_path;
char *input_file;
char *output_file;
char *output_suf;
char *prog_path;
bool  output_not_existed_hdr;
bool  no_array_assign_operator;
bool  language_c;
bool  compile_system_library;
bool  pio_init;
bool  use_call_graph;
bool  short_set; 
bool  unsigned_comparison;
bool  small_enum; 
bool  nological;
bool  force_logical;
bool  turbo_pascal;
bool  use_c_strings;
bool  extern_vars;
bool  preserve_case;
bool  nested_comments;
bool  copy_array;
bool  comment_tags;
bool  use_namespaces;
bool  smart_union;
bool  no_index_decrement;
bool  ignore_preprocessor_directives;
bool  hp_pascal;
bool  do_not_use_enums;
char* pascall;
char path_sep;

FILE *call_graph_file;

static void scan_opt (int argc, char **argv) {
    int i;
    unsigned j;
    bool found;

    static struct opt_str {
	bool *flag;
	char **value;
	char *str;
        char *defval; 
	char *comment;
    } opt[] = {

//      Add command options to this table:

	{ NULL, &i_path, "-I", ".", 
#ifdef _WIN32
	  "Include path (semicolon separated directory list)" },
#else
	  "Include path (colon separated directory list)" },
#endif
	{ NULL, &input_file, "-in", NULL, 
	  "Input pascal file" },
	{ NULL, &output_file, "-out", NULL, 
	  "Output C/C++ file" },
	{ NULL, &output_suf, "-suf", ".cxx",
	  "Output C/C++ file suffix" },
	{ &language_c, NULL, "-c", NULL,
	  "Translate into ANSI C" },
	{ &no_array_assign_operator, NULL, "-assign", NULL,
	  "Do not use assignment operators for array" },
	{ &use_call_graph, NULL, "-analyze", NULL,
	  "Analyze call graph to find non-recursive functions" },
	{ &short_set, NULL, "-intset", NULL,
	  "Use integer types for short sets of enumerations" },
	{ &pio_init, NULL, "-init", NULL,
	  "Call pio_initialize() function from main()" },
	{ &small_enum, NULL, "-smallenum", NULL,
	  "Use for enumerated types as small bytes as possible" },
	{ &unsigned_comparison, NULL, "-unsigned", NULL,
	  "Generate correct code for sign/unsigned comparisons" },
	{ &output_not_existed_hdr, NULL, "-h", NULL,
	  "Output only not existed header files" },
	{ &turbo_pascal, NULL, "-turbo", NULL,
	  "Convert Turbo Pascal" },
	{ &hp_pascal, NULL, "-hp", NULL,
	  "Convert HP64000 Pascal" },
	{ &use_c_strings, NULL, "-cstring", NULL,
	  "Use char* type for string fields in records and arrays" },
	{ &nological, NULL, "-nological", NULL,
	  "Use | and & instead of || and && for boolean operations" },
	{ &force_logical, NULL, "-logical", NULL,
	  "Use || and && for all types" },
	{ &extern_vars, NULL, "-extern", NULL,
	  "Declare all variables from included files as \"EXTERN\"" },
	{ &preserve_case, NULL, "-preserve", NULL,
	  "Preserve case of identifiers" },
	{ &nested_comments, NULL, "-nested", NULL,
	  "Nested comments: (* {} *)" },
	{ &copy_array, NULL, "-copy", NULL,
	  "Always make a copy of array passed by value" },
	{ &comment_tags, NULL, "-comment_tags", NULL,
	  "Place in comments tags of Pascal variant records" },
	{ &smart_union, NULL, "-smartunion", NULL,
	  "Convert variant records with empty fixed part to unions" },
	{ &use_namespaces, NULL, "-namespace", NULL,
	  "Place Turbo Pascal units in separate namespaces" },
	{ &no_index_decrement, NULL, "-0based", NULL,
	  "Assume all arrays are zero based" },
	{ &ignore_preprocessor_directives, NULL, "-ignore_directives", NULL,
	  "Ignore all lines started with '$' character" },
	{ &do_not_use_enums, NULL, "-no_enums", NULL,
	  "Do not use enums for integer constants" },
	{ NULL, &pascall, "-pascall", "",
	  "Specify modifier (pascal,WINAPI...) for converted functions" }

    };
    for (j = 0; j < (sizeof(opt)/sizeof(opt_str)); j++) {
	if (opt[j].value != NULL) { 
 	    *opt[j].value = opt[j].defval;
        }
	if (opt[j].flag != NULL) { 
	    *(opt[j].flag) = FALSE; // Switch off flags
        }
    }
    for (i = 1; i < argc; i++) { // Skipping program name
	if (argv[i][0] != '-') { 
	    if (input_file != NULL) { 
		fprintf(stderr, "Only one input file name is accepted\n");
		goto Help;
	    }
	    input_file = argv[i];
	    continue;
	}
	found = FALSE;
	for (j = 0; j < (sizeof(opt)/sizeof(opt_str)); j++) {
	    if (strcmp (opt[j].str, argv[i]) == 0) { 
		if (opt[j].flag != NULL) { 
	            *(opt[j].flag) = TRUE;
                } 
		if (opt[j].value != NULL) { 
		    i++; 
		    if (i >= argc) {
			fprintf(stderr, "Value for option '%s' is not specified\n", opt[j].str);
			goto Help;
		    }
		    *opt[j].value = argv[i];
		}
		found = TRUE;
		break;
	    }
	}
	if (!found) { 
 	  Help:
	    fprintf (stderr, "Pascal to C/C++ converter. Version "VERSION"\n"
			     "Available options are:\n");

	    for (j = 0; j < (sizeof(opt)/sizeof(opt_str)); j++ ) {
		if (opt[j].defval != NULL) { 
		    char buf[256];
		    sprintf(buf, "%s [%s]", opt[j].str, opt[j].defval);
            assert(strlen(buf) < sizeof(buf));
		    fprintf(stderr, "\t%-12s", buf); 
 		} else { 
		    fprintf(stderr, "\t%-12s", opt[j].str); 
		}
	   	fprintf(stderr, "%s\n", opt[j].comment); 
	    }
	    exit (1);
	}
	pio_init = TRUE;
    }
    if (input_file == NULL) { 
	goto Help;
    }
#ifdef _WIN32
    char* p = strrchr(argv[0], '\\');
    prog_path = (p != NULL) ? dprintf("%.*s", p + 1 - argv[0], argv[0]) : (char*)""; 
    path_sep = ';';
#else
#ifdef __EMX__
    char* p = strrchr(_fnslashify(argv[0]), '/');
    prog_path = (p != NULL) ? dprintf("%.*s", p + 1 - argv[0], argv[0]) : (char*)""; 
#else
    char* p = strrchr(argv[0], '/');
    prog_path = (p != NULL) ? dprintf("%.*s", p + 1 - argv[0], argv[0]) : (char*)""; 
#endif
    path_sep = ':';
#endif
    i_path = dprintf("%s%c%s", i_path, path_sep, prog_path);
}

int main(int argc, char* argv[]) 
{ 
    scan_opt (argc, argv);

    if (input_file == NULL) { 
	fputs("Input file was not specified\n", stderr);
        exit(1); 
    } 
    if (output_file == NULL) { 
	char* ext = strrchr(input_file, '.');
        int file_name_len = ext ? ext - input_file : strlen(input_file); 
	if (language_c) output_suf = ".c";
	output_file = dprintf("%.*s%s", file_name_len, input_file, output_suf);  
    } 
    load_predefined(); 
    load_keywords();
    load_configuration(dprintf("%s%s", prog_path, CONFIG_FILE));

    if (hp_pascal) { 
        nested_comments = 1;
        ignore_preprocessor_directives = 1;
    }
    if (use_call_graph) { 
	call_graph_file = fopen(CALL_GRAPH_FILE, "a");
	FILE* f = fopen(RECURSIVE_PROC_FILE, "r");
	if (f != NULL) { 
	    char name[256];
	    while (fscanf(f, "%s", name) == 1) { 
            assert(strlen(name) < sizeof(name));
            nm_entry::add(name, TKN_IDENT)->flags |= nm_entry::recursive;
	    }
	    fclose(f);
	}
    }

    compile_system_library = TRUE;
#ifdef PREFIX
    token::input(turbo_pascal 
		 ? PREFIX "/share/ptoc/tptoc.pas" 
		 : PREFIX "/share/ptoc/ptoc.pas")); 
#else
    token::input(dprintf("%s%s", prog_path, 
 			 turbo_pascal ? "tptoc.pas" : "ptoc.pas")); 
#endif
    zzparse(); 

    compile_system_library = FALSE;
    token::reset();
    token::input(input_file); 
    zzparse(); 

    token::output(output_file);

    if (call_graph_file) { 
	fclose(call_graph_file);
    }
    return 0; 
}


