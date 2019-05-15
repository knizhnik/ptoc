#ifndef __TOKEN_H__
#define __TOKEN_H__

#include "main.h"
#include "nmtbl.h"
#include "dprintf.h"

class token;
extern int   yylex();
extern char  *yytext;
extern int   yyleng;
extern token *curr_token;  

#define TAB_WIDTH 8


// Token definitions
enum lex_token {                
#define DEF_TOKEN(o,c,t,k) t,
#include "token.dpp"
  TKN_LAST 
}; 

// Special token TAGs < 0 !!!

enum category {
    CAT_ID,
    CAT_STR,
    CAT_NUM,
    CAT_KWD,
    CAT_WSPC,
    CAT_PUT,
    CAT_SPEC,  
    CAT_GEN
};

class token : public heap_object {
  public:

  // First we define dl-list members
    token  *prev, *next;
    static token  dummy;	// Begin of MAIN token list

    static int   const token_cat[];
    static char* const token_name[]; 

    static char* resolve_name_conflict(char* str);

    token(int v_cat, int v_tag) 
    { 
	next = prev = this;
	cat = v_cat;
	tag = v_tag;
	fname = NULL;
	clone = bind = NULL;
    }
    token(char const* v_text, int v_tag = TKN_GEN, int v_line = 0, int v_pos = 0,
	  nm_entry *nm = NULL) 
    { 
        line = v_line;
	attr = 0;
        pos = v_pos;
        tag = v_tag;
	cat = token_cat[v_tag];
        out_text = in_text = (char*)v_text; 
        fname = NULL;
        name = nm;
	clone = bind = NULL;
    }	    
    token(token& t); 	    

    enum token_attributes { 
	fix_pos = 1, 
	from_include_file = 2 
    }; 

    unsigned char  cat;		// Token category
    unsigned char  attr;        // Attribute of token
    unsigned short tag;		// Exact token code
    unsigned short pos;		// Pos. within the line of token start
    unsigned short line;	// Line number where token was found

    nm_entry*   name;           // Corresponded name entry (!=NULL for ID)

    char*       in_text;        // Input text representation of token
    char*       out_text;	// Output text representation of token

    char*       fname;          // Token file name
 
    token*      bind;           // token position of which is taken 	    
    token*      clone;          // cloned token 
    

    token* insert_b(token* t) { // insert token before (returns this)
        next = t; prev = t->prev;   
        return t->prev = t->prev->next = this;
    }
    token* insert_a(token* t) { // insert token after (returns this)
        prev = t; next = t->next;
        return t->next = t->next->prev = this;
    }
    void   remove();            // remove token from DL-ring
    static void remove(token* head, token* tail); 
    static void disable(token* head, token* tail); 

    token* get_first_token(); // get first relevant token at line 

    token* prepend(char const* s) { 
        token* t = new token(s);
	t->pos = pos;
        return t->insert_b(this);			    
    }
    token* append(char const* s) {
	return (new token(s))->insert_a(this);
    }
    void   disable() { 
	if (cat != CAT_WSPC || tag < TKN_GEN) { 
	    cat = CAT_WSPC; tag = TKN_GEN; out_text = NULL; 
	}
    }
    void   disappear(); // disable token with all white spaces after it

    void   set_pos(token* t) { pos = t->pos; } 

    void   set_bind(token* t) { bind = t; } 

    token* copy(token* from, token* till); // copy list of tokens before 
					   // this token, return pointer to 
                                           // image of 'from' token 
    token* move(token* from, token* till); // move list of tokens before this 
					   // token, return pointer to from
    token* move_region(token* head, token* tail); 
                                           // move region (together with 
					   // comments and white spaces)
    static void swap(token* left_head, token* left_tail, 
		     token* right_head, token* right_tail); 


    token* next_relevant();
    token* prev_relevant();
    static token* first_relevant();
    static token* last_relevant();

    void   set_trans (char const* str) {
        cat = CAT_GEN;	
        out_text = (char*)str;
    }    

    static void input(char *file);
    static void output(char *file);

    static void reset() { dummy.next = dummy.prev = &dummy; curr_token = NULL; }
};

class output_context { 
  private:
    FILE* f; 
    int   pos; 
    int   line;  
    int   prev_tag; 

  public:
    FILE* file() { return f; }
 
    void output(token* t); 
    output_context(char* file_name);
    ~output_context(); 
}; 

#endif


