#include <stdio.h>
#include "token.h"

//-------- First we define token dl-list members ----------------//


token* curr_token;

token token::dummy(CAT_SPEC, TKN_DUMMY);  // Initialize token DL-ring

char* const token::token_name[] = { 
#define DEF_TOKEN(m_text, m_cat, m_tag, m_keyword) \
     m_text,
#include "token.dpp"
};

int const token::token_cat[] = { 
#define DEF_TOKEN(m_text, m_cat, m_tag, m_keyword) \
      CAT_##m_cat,
#include "token.dpp"
};

token::token(token& t) 
{ 
    *this = t;
    clone = NULL; 
    t.clone = this;
    if (bind != NULL) bind = bind->clone; 
}

void token::remove() 
{
    prev ->next = next;  
    next->prev = prev;
}

token* token::next_relevant() 
{
    token* t; 
    for (t = next; t->cat == CAT_WSPC; t = t->next); 
    return t;
}

token* token::prev_relevant() 
{
    token* t; 
    for (t = prev; t->cat == CAT_WSPC; t = t->prev); 
    return t;
}

token* token::first_relevant() { return dummy.next_relevant(); }

token* token::last_relevant()  { return dummy.prev_relevant(); }

void   token::remove(token* head, token* tail)
{ 
    head->prev->next = tail->next; 
    tail->next->prev = head->prev; 
} 

void   token::disable(token* head, token* tail)
{ 
    while(TRUE) { 
	if (head->tag != TKN_CMNT && head->tag != TKN_LN) { 
	    head->disable();
        }
	if (head == tail) break;
        head = head->next; 
    }
}

void   token::disappear() 
{ 
    token* t = this;
    do { 
	t->disable();
	t = t->next;
    } while (t->tag == TKN_SPACE || t->tag == TKN_LN);
}    


token* token::get_first_token()
{ 
    token *t;
    for (t = this; t->tag != TKN_LN && t->tag != TKN_DUMMY; t = t->prev);
    return t->next_relevant(); 
}

token* token::copy(token* head, token* tail)
{
    token* first = head;
    while (TRUE) { 
         (new token(*head))->insert_b(this); 
	 if (head == tail) break;
	 head = head->next; 
    }
    first->clone->pos = pos; 
    return first->clone; 
} 

void token::swap(token* left_head, token* left_tail,
		 token* right_head, token* right_tail)
{  
    token* t;

    left_head->prev->next = right_head; 
    left_tail->next->prev = right_tail; 
    right_head->prev->next = left_head; 
    right_tail->next->prev = left_tail; 

    t = right_head->prev; 
    right_head->prev = left_head->prev;
    left_head->prev = t; 
    
    t = right_tail->next;
    right_tail->next = left_tail->next;
    left_tail->next = t; 
}  

token* token::move(token* head, token* tail)
{
    head->prev->next = tail->next; 
    tail->next->prev = head->prev; 
    
    tail->next = this; 
    head->prev = prev; 
    prev->next = head; 
    prev = tail; 
    head->pos = pos; 

    return head;
} 

token* token::move_region(token* head, token* tail)
{
    while (head->prev->cat == CAT_WSPC) { 
	head = head->prev; 
    }
    while (tail->next->cat == CAT_WSPC && tail->next->tag != TKN_LN) {  
        tail = tail->next;
    }
    return move(head, tail);  
} 


//------------------------------------------------------------------------//

void token::input(char *file) 
{
    scanner_input(file); 
    while (yylex() > 0) curr_token->insert_b (&dummy);
    curr_token = NULL; 
}


output_context::output_context(char* file)
{ 
    f = fopen(file, "w"); 
    if (f == NULL) { 
	fprintf(stderr, "Can't open output source file: %s\n", file); 
	exit(1); 
    }
    pos = line = 0; 
    prev_tag = TKN_LN; 
} 


output_context::~output_context() 
{
    if (f != NULL) fclose(f); 
} 

void output_context::output(token* t) 
{  
    static int shift = 0;
    int t_pos;

    if (t->tag == TKN_BEG_SHIFT) { 
        shift = -t->pos;
        return;
    } else if (t->tag == TKN_END_SHIFT) { 
        shift = 0;
	return;
    }
    t_pos = t->bind ? t->bind->pos : t->pos + shift;

    if (t->out_text == NULL || (t->tag == TKN_SPACE && prev_tag == TKN_LN)) { 
	return; 
    }
    if (t_pos > pos && t->tag != TKN_LN && 
	((t->attr & token::fix_pos) || t->tag == TKN_CMNT || 
	 prev_tag == TKN_LN)) 
    { 
	//
	// Set token to specified position
	//
	while (pos < t_pos) { 
	    pos += 1; 
	    putc(' ', f);
	} 
    }	
    t->pos = pos;
    //
    // Separate output '>' symbols 
    //
    if (*t->out_text == '>' && prev_tag == TKN_GT) {
	pos += 1; 
	putc(' ', f);
    }
    // 
    // Ignoring starting (trailing) spaces in generated tokens
    // if there are space tokens before (after) generated token
    //
    char* out = t->out_text;
    int len = strlen(out);

    if (t->cat == CAT_GEN) { 
	if (out[0] == ' ' && (prev_tag == TKN_SPACE || prev_tag == TKN_LN)) { 
	    out += 1; 
            len -= 1;
	}
	if (out[len-1] == ' ' && t->next->tag == TKN_SPACE) { 
	    len -= 1;
        } 
    }
    //
    // Output text
    // 
    prev_tag = t->tag;
    while (-- len >= 0) { 
	switch(*out) { 
	  case '\n':
	    pos = 0;
	    line += 1;
	    prev_tag = TKN_LN;
            break;
          case '\t':
	    pos += TAB_WIDTH - (pos % TAB_WIDTH);
	    prev_tag = TKN_SPACE;
	    break;
          case ' ':
	    prev_tag = TKN_SPACE;
	    pos += 1;
	    break;
	  case '>':
	    prev_tag = TKN_GT;
	    pos += 1;
            break;
	  default:
	    pos += 1;
	    prev_tag = t->tag;
	}
	putc(*out++, f); 	
    }
} 

extern bool output_not_existed_hdr;

static token* print_rec (char *file, token *t, bool unit_spec) {
    output_context ctx(file);	
    char *ip1, *ip2;
    char *inc_file = NULL;
    FILE*  f;
    token* nt;
    int    tag;
    bool   def_vars = FALSE;
    bool   interface_module = FALSE;
    bool   unit_implementation = FALSE;
    bool   in_namespace = false;
    int file_name_len = 0;

    printf ("Output file %s\n", file);

    if (t->prev->tag == TKN_DUMMY) { 
	fputs("#include \"ptoc.h\"\n\n", ctx.file());
    } else if (unit_spec) { 
	file_name_len = strrchr(file, '.') - file;
	fprintf(ctx.file(), "#ifndef __%.*s_h__\n#define __%.*s_h__\n", 
		file_name_len, file, file_name_len, file);
	interface_module = TRUE;
    }
    for (; (tag = t->tag) != TKN_DUMMY; t = t->next) {
        switch (tag) {
	  case TKN_INTERFACE:
	    ip1 = strrchr(file, '.');
	    inc_file = ip1 ? dprintf("%.*s.h", ip1 - file, file)
		           : dprintf("%s.h", inc_file, file);
            fprintf(ctx.file(), "#include \"%s\"\n", inc_file);
	    t = print_rec(inc_file, t->next, TRUE);
            if (t->tag == TKN_IMPLEMENTATION && use_namespaces) { 
                file_name_len = strrchr(file, '.') - file;
                fprintf(ctx.file(), "\nnamespace %.*s {\n", file_name_len, file);
                unit_implementation = TRUE;
            }                
	    continue;
          case TKN_PUSH_FILE:
          case TKN_PUSH_UNIT:
            ip1 = strrchr(t->in_text, '.');
            ip2 = strrchr(t->out_text, '.');
            assert (ip1 != NULL && ip2 != NULL);
	    def_vars = FALSE;
	    if (extern_vars && !turbo_pascal 
		&& strcmp(ip2, ".var") == 0
		&& strncmp(t->out_text, file, ip2-t->out_text+1) == 0)
	    {
		def_vars = TRUE;
	    } 
	    if (strcmp(ip1, ".pas") == 0) { 
                strcpy(ip1, ".h");
		strcpy(ip2, ".h");
            } else { 
		*ip1 = '_'; 
		*ip2 = '_'; 
		strcat(ip1, ".h");
		strcat(ip2, ".h");
	    }
	    if (tag == TKN_PUSH_UNIT) { 
		fprintf(ctx.file(), "#include \"%s\"\n", t->out_text);
	    } else { 
		fprintf(ctx.file(), "#include \"%s\"", t->out_text);
	    }
	    inc_file = t->in_text;
	    f = NULL;
	    if (tag == TKN_PUSH_UNIT 
		|| (output_not_existed_hdr 
		    && (f = fopen(inc_file, "r")) != NULL)) 
	    {
		int nested = 1;
		if (f) fclose(f);
		do {
		    t = t->next;
		    if (t->tag == TKN_POP_FILE)  nested -= 1;
		    if (t->tag == TKN_PUSH_FILE) nested += 1;
		    if (t->tag == TKN_PUSH_UNIT) nested += 1;
		    if (t->tag == TKN_UNIT_END)  nested -= 1;
		} while(nested);
            } else { 
		t = print_rec(inc_file, t->next, FALSE);
	    }
	    if (tag != TKN_PUSH_UNIT) { 
		for (nt = t->next; 
		     nt != NULL && nt->cat == CAT_WSPC &&
		     (nt->tag == TKN_SPACE || nt->tag == TKN_CMNT);
		     nt = nt->next);
		if (nt && nt->tag != TKN_LN) { 
		    fputc('\n', ctx.file());
		}
	    }
            continue;
          case TKN_IMPLEMENTATION:
          case TKN_UNIT_END:
          case TKN_POP_FILE:
	    if (interface_module) { 
		if (!unit_spec && use_namespaces) { 
		    fprintf(ctx.file(), "}\nusing namespace %.*s;\n", 
			    file_name_len, file);
		}
		fprintf(ctx.file(), "#endif\n");
	    }
            return t;
          default:
            if (t->tag > TKN_CMNT && unit_spec && use_namespaces) {             
                fprintf(ctx.file(), "namespace %.*s {\n", file_name_len, file);
                unit_spec = false;
            }
            ctx.output(t);
        }
    }
    if (unit_implementation) {
        fprintf(ctx.file(), "}\n");
    }
    return NULL; // end of main file
}

void token::output (char *file) 
{
    print_rec(file, dummy.next, FALSE);
}


