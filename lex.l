%{

#include "token.h"
#include "util.h"

#ifdef _WIN32
#include <io.h>
#define FILE_SEP "\\"
#else
#include <unistd.h>
#define FILE_SEP "/"
#endif

#define yywrap() 1
#define YY_SKIP_YYWRAP 1

#define YY_NO_UNPUT 1

// Some static data definition

static char *file_name;
static int line, pos;    // Token position
extern char *i_path;

struct scan_state {
    int             pos;
    int             line;
    char*           file_name;
    char*           search_path;
    FILE*           input;
    YY_BUFFER_STATE buffer;
};

#define MAX_INCLUDE_DEPTH 256   // Include stack depth
#define MAX_ID_LENGTH     256

class scan_ctx {
  protected:
    scan_state      stack[ MAX_INCLUDE_DEPTH ];
    int             sp;

  public:
    void push();
    void attach(char* name, FILE* in);
    void pop();
    bool empty() { return sp == 0; }
    bool find(char* name) ;
    scan_ctx() { sp = 0; }
};

static scan_ctx scanner;
static int type_or_var_context;


void scanner_input(char *file)
{
    FILE* f = fopen (file, "r");

    if (f == NULL) {
	error("can't open input source file: %s", file);
    }
    scanner.attach(file, f);
}


// Hints for macro functionality (inherited from rtl2c)
static nm_entry *nm = NULL;	       // Token name
static char *text   = NULL;            // Token text if != NULL

static int include_level;

class use_ctx {
  public:
    char* fname;
    use_ctx* next;

    use_ctx(char* name, use_ctx* chain) {
	fname = name;
	next = chain;
    }
};

static use_ctx* use_chain;

#undef  ECHO
#define ECHO

// Token generator function

int tkn (int tag) {
   curr_token = new token(text ? text : strdup(yytext),
			  tag, line, pos, nm);
   nm = NULL; text = NULL;
   for (char *c = yytext; *c != 0; c++) {
       if (*c == '\n') { line++; pos = 0; }
       else if (*c == '\t') { pos += TAB_WIDTH - (pos % TAB_WIDTH); }
       else pos++;
   }
   curr_token->fname = file_name;
   if (include_level > 0) {
       curr_token->attr |= token::from_include_file;
   }
   return 1;
}



// Include file name processing

static char *include_name (char *src) {
    char *t;
    char *name = new char[strlen(src)+8];
    char *dst = name;
    if (strchr(src, '\n') != NULL) {
        line += 1;
        pos = 0;
    }
    while (*src == '\'' || isspace(*src)) src++;        // Skip leading '[ ]
    if ((t = strchr (src, '[')) != NULL) {
#if 0
        int gid, uid, n;
        if (sscanf(t, "[%d,%d]%n", &gid, &uid, &n) == 2) {
            dst += sprintf(dst, "../%03d%03d/", gid, uid);
	    src = t + n;
        }
	else
#endif
	{
	    if ((t = strrchr(src, ']')) != NULL) {
	        src = t+1;
            }
        }
    }
    bool suffix = FALSE;
    while(*src && !isspace(*src) && *src != ';' && *src != '\''
          && *src!='\n' && *src != '}')
    {
        if (*src == '.') suffix = TRUE;
	*dst++ = tolower(*(unsigned char*)src++);
    }
    *dst = 0;
    if (!suffix) strcpy(dst, ".pas");

    if (scanner.find(name)) {
	error(line, pos, file_name, "file %s already included !\n", name);
    }
    return name;
}

static int yyinput(void);

inline int yyinput_file() {
    int ch = yyinput();
    if (ch == '\n') { line++; pos = 0; }
    else if (ch == '\t') { pos += TAB_WIDTH - (pos % TAB_WIDTH); }
    else pos++;
    return ch;
}

static int process_end_of_line_comment() {
    char cmt_buf[1024];
    char* p = cmt_buf;
    int c;
    *p++ = '/';
    *p++ = '/';
    while((c = yyinput_file()) != EOF) {
        if (c == '\n') {
           *p++ = '\n';
           *p = '\0';
           curr_token = new token(NULL, TKN_CMNT, line, pos);
           curr_token->in_text = curr_token->out_text = strdup(cmt_buf);
           return 1;
        } else {
           *p++ = (char)c;
        }
    }
    error(line, pos, file_name, "EOF in comment !\n");
    return -1;
}

static int process_comments() {
    static int cmt_buf_len = 256;
    static char* cmt_buf = new char[cmt_buf_len];
    int c, pc = 0;
    char *p = cmt_buf;
    char cmt_start = *yytext;
    *p++ = '/';
    *p++ = '*';

    curr_token = new token(NULL, TKN_CMNT, line, pos);

    pos += strlen(yytext);

    if (nested_comments) {
	while((c = yyinput_file()) != EOF) {
	    if (c == '/' && pc == '*') c = ' ';
	    if (p == cmt_buf + cmt_buf_len) {
		cmt_buf = (char*)realloc(cmt_buf, 2*cmt_buf_len);
		p = cmt_buf + cmt_buf_len;
		cmt_buf_len *= 2;
	    }
	    if ((cmt_start == '{' && c == '}') ||
		(cmt_start == '(' && c == ')' && pc == '*'))
            {
		size_t len = p - cmt_buf;
		char* cmt_text = new char[len + 3];
		memcpy(cmt_text, cmt_buf, len);
		if (pc != '*') cmt_text[len++] = '*';
		cmt_text[len++] = '/';
		cmt_text[len] = '\0';
                if (turbo_pascal && cmt_text[2] == '$') {
                   *p = '\0';
                   if (strincmp(cmt_text+3, "IFDEF", 5) == 0) {
                      sprintf(cmt_text, "#ifdef %s", cmt_buf+9);
                   } else if (strincmp(cmt_text+3, "ELSE", 4) == 0) {
                      sprintf(cmt_text, "#else");
                   } else if (strincmp(cmt_text+3, "ENDIF", 5) == 0) {
                      sprintf(cmt_text, "#endif");
                   } else if (strincmp(cmt_text+3, "IFNDEF", 6) == 0) {
                      sprintf(cmt_text, "#ifndef %s", cmt_buf+10);
                   } else if (strincmp(cmt_text+3, "DEFINE", 6) == 0) {
                      sprintf(cmt_text, "#define %s", cmt_buf+10);
                   } else if (strincmp(cmt_text+3, "IFOPT", 5) == 0) {
		      int value = 1;
                      char* p = strchr(cmt_text+8, '+');
		      if (p != NULL) *p = '\0';
		      else if ((p = strchr(cmt_text+8, '-')) != NULL) {
			value = 0;
			*p = '\0';
		      }
		      for (p = cmt_buf+8; *p == ' '; p++);
                      sprintf(cmt_text, "#if OPTION_%s == %d",
			      p, value);
                   }
                }
		curr_token->in_text = curr_token->out_text = cmt_text;
		return 1;
	    }
	    *p++ = pc = c;
	}
    } else {
	while((c = yyinput_file()) != EOF) {
	    if (c == '/' && pc == '*') c = ' ';
	    if (p == cmt_buf + cmt_buf_len) {
		cmt_buf = (char*)realloc(cmt_buf, 2*cmt_buf_len);
		p = cmt_buf + cmt_buf_len;
		cmt_buf_len *= 2;
	    }
	    if (c == '}' || (c == ')' && pc == '*')) {
		size_t len = p - cmt_buf;
		char* cmt_text = new char[len + 3];
		memcpy(cmt_text, cmt_buf, len);
		if (pc != '*') cmt_text[len++] = '*';
		cmt_text[len++] = '/';
		cmt_text[len] = '\0';
		curr_token->in_text = curr_token->out_text = cmt_text;
		return 1;
	    }
	    *p++ = pc = c;
	}
    }
    error(line, pos, file_name, "EOF in comment !\n");
    return -1;
}

%}

ID           [_\$A-Z][_\$A-Z0-9]*

DIGIT        [0-9]
BINDIGIT     [0-1]
OCTDIGIT     [0-7]
HEXDIGIT     [0-9A-F]

SIGN         [+-]?
EXPONENT     E{SIGN}{DIGIT}+

REAL         {DIGIT}+\.{DIGIT}+{EXPONENT}?|{DIGIT}+{EXPONENT}

ROOT         {DIGIT}\#|{DIGIT}{DIGIT}\#

INTEGER      {DIGIT}+|{ROOT}{HEXDIGIT}+|{BINDIGIT}+B|0x{HEXDIGIT}+|0X{HEXDIGIT}+|{DIGIT}{HEXDIGIT}*H|{DIGIT}{HEXDIGIT}*h|%{BINDIGIT}+

/* the "incl" state is used for picking up the name
 * of an include file
 */
%x incl
%x use

%%

\%include     BEGIN(incl);
\#include     BEGIN(incl);
uses          BEGIN(use); /* Turbo Pascal */

<use>[ \t\n\,]* {  /* skip whitespaces */
    char* p = yytext;
    while(*p != '\0') {
	if (*p++ == '\n') line += 1;
    }
}

<use>\{[^\}]*\} { /* skip comments */
    char* p = yytext;
    while(*p != '\0') {
	if (*p++ == '\n') line += 1;
    }
}

<use>[_a-z0-9A-Z]+ {
                  /* got the include file name */
    char *fname = dprintf("%s.pas", yytext);
    for (char* p = fname; *p != '\0'; p++) *p = tolower(*p);

    use_ctx* up;
    for (up = use_chain;
	 up != NULL && strcmp(fname, up->fname) != 0;
	 up = up->next);

    if (up == NULL) {
        char *xname;
        FILE *in = NULL;
        char *try_dir, *next_dir;
        int dir_length;

	for (try_dir = i_path; try_dir != NULL; try_dir = next_dir) {
	    if ((next_dir = strchr (try_dir, path_sep)) != NULL ) {
		dir_length = next_dir - try_dir;
		next_dir++;
	    } else {
		dir_length = strlen (try_dir);
	    }
	    xname = dprintf ("%.*s" FILE_SEP "%s", dir_length, try_dir, fname);
	    if ((in = fopen(xname, "r")) != NULL) {
		use_chain = new use_ctx(fname, use_chain);
		curr_token = new token(xname, TKN_PUSH_UNIT);
		curr_token->out_text = fname;
		include_level += 1;
		BEGIN(INITIAL);     // To leave include state
		scanner.push();
		scanner.attach(xname, in);
		return 1;
	    }
	}
	warning(line, pos, file_name, "can't include file %s", fname);
        curr_token = new token(dprintf("/*#include \"%s.h\"*/\n", yytext),
	                       TKN_CMNT, line, pos);
    } else {
        curr_token = new token(dprintf("#include \"%s.h\"\n", yytext),
	                       TKN_CMNT, line, pos);
    }
    return 1;
}
<use>; {
    BEGIN(INITIAL);     // To leave include state
}


<use>.  {
    error(line, pos, file_name, "unrecognized token: %s\n",
		yytext);
}




<incl>[ \t\n]* {  /* eat the whitespace */
    char* p = yytext;
    while(*p != '\0') {
	if (*p++ == '\n') line += 1;
    }
}
<incl>[^\;\n]+\;* {
                  /* got the include file name */
    BEGIN(INITIAL);     // To leave include state

    char *fname = include_name (yytext);
    char *xname;
    FILE *in = NULL;
    char *try_dir, *next_dir;
    int dir_length;

    for (try_dir = i_path; try_dir != NULL; try_dir = next_dir) {
	if ((next_dir = strchr (try_dir, path_sep)) != NULL ) {
	    dir_length = next_dir - try_dir;
	    next_dir++;
	} else {
	    dir_length = strlen (try_dir);
	}
	xname = dprintf ("%.*s" FILE_SEP "%s", dir_length, try_dir, fname);
	if ((in = fopen(xname, "r")) != NULL) {
	    include_level += 1;
	    scanner.push();
	    scanner.attach(xname, in);
	    curr_token = new token(xname, TKN_PUSH_FILE);
	    curr_token->out_text = fname;
	    return 1;
	}
    }
    warning(line, pos, file_name, "can't include file %s", fname);
    curr_token = new token(dprintf("/*#include \"%s\"*/", fname),
	                   TKN_CMNT, line, pos);
    return 1;
}

<incl>.  {
    error(line, pos, file_name, "unrecognized token: %s\n",
		yytext);
}

\{\$I[ \t]*[a-zA-Z0-9\.]+[ \t]*\} {
    char *fname = include_name (yytext+3);
    char *xname;
    FILE *in = NULL;
    char *try_dir, *next_dir;
    int dir_length;

    for (try_dir = i_path; try_dir != NULL; try_dir = next_dir) {
	if ((next_dir = strchr (try_dir, path_sep)) != NULL ) {
	    dir_length = next_dir - try_dir;
	    next_dir++;
	} else {
	    dir_length = strlen (try_dir);
	}
	xname = dprintf ("%.*s" FILE_SEP "%s", dir_length, try_dir, fname);
	if ((in = fopen(xname, "r")) != NULL) {
	    include_level += 1;
	    scanner.push();
	    scanner.attach(xname, in);
	    curr_token = new token(xname, TKN_PUSH_FILE);
	    curr_token->out_text = fname;
	    return 1;
	}
    }
    warning(line, pos, file_name, "can't include file %s", fname);
    curr_token = new token(dprintf("/*#include \"%s\"*/", fname),
	                   TKN_CMNT, line, pos);
    return 1;
}

<<EOF>>      {
    if (scanner.empty()) {
	return -1;  // MAGIC ! (< 0 means end of files)
    } else {
	scanner.pop();
	include_level -= 1;
	curr_token =  new token((char*)NULL, TKN_POP_FILE);
	return 1;
    }
}

"//"        { return process_end_of_line_comment(); }
"(*"        { return process_comments(); }
"{*"        { return process_comments(); }
"{"         { return process_comments(); }

"("         { return tkn(TKN_LPAR); }
")"         { return tkn(TKN_RPAR); }
"(."        { text = "["; return tkn(TKN_LBR);  }
".)"        { text = "]"; return tkn(TKN_RBR);  }
"["         { return tkn(TKN_LBR);  }
"]"         { return tkn(TKN_RBR);  }
"*"         { return tkn(TKN_MUL);  }
"+"         { return tkn(TKN_PLUS); }
"-"         { return tkn(TKN_MINUS);}
">>"        { return tkn(TKN_C_SHR); }
"<<"        { return tkn(TKN_C_SHL);}
"&"         { return tkn(TKN_C_AND);}
"|"         { return tkn(TKN_C_OR);}
"*="        { return tkn(TKN_LETMUL);  }
"+="        { return tkn(TKN_LETADD); }
"-="        { return tkn(TKN_LETSUB);}
">>="       { return tkn(TKN_LETSHR); }
"<<="       { return tkn(TKN_LETSHL);}
"&="        { return tkn(TKN_LETAND);}
"|="        { return tkn(TKN_LETOR);}
"/="        { return tkn(TKN_LETDIV);}
"~"         { return tkn(TKN_C_NOT);}
","         { return tkn(TKN_COMMA);}
"."         { return tkn(TKN_DOT);  }
".."        { return tkn(TKN_DOTS); }
"/"         { return tkn(TKN_DIVR);  }
"@"         { return turbo_pascal ? tkn(TKN_ADDR) : tkn(TKN_HEAP); }
"^"         { if (turbo_pascal && !type_or_var_context
		  && curr_token->tag != TKN_HEAP
                  && curr_token->tag != TKN_RBR && curr_token->tag != TKN_RPAR
		  && curr_token->tag != TKN_REF
		  && curr_token->tag != TKN_IDENT
		  && curr_token->cat != CAT_ID)
               {
		   text = dprintf("#%d", yyinput() & 31);
		   return tkn(TKN_SCONST);
              }
	      return tkn(TKN_HEAP);
            }
":="        { return tkn(TKN_LET);  }
":"         { return tkn(TKN_COLON);}
";"         { return tkn(TKN_SEMICOLON); }
"<="        { return tkn(TKN_LE);  }
">="        { return tkn(TKN_GE);  }
"<"         { return tkn(TKN_LT);  }
">"         { return tkn(TKN_GT);  }
"="         { return tkn(TKN_EQ);  }
"<>"        { return tkn(TKN_NE);  }


{REAL}       { return tkn(TKN_RCONST); }
{INTEGER}    { return tkn(TKN_ICONST);  }

{ID}         {
               char lc_buf[MAX_ID_LENGTH];
	       char *src = yytext, *dst = lc_buf;
	       if (*yytext == '$') {
                   if (turbo_pascal) { /* hexademical number */
  	               return tkn(TKN_ICONST);
                   } else if (ignore_preprocessor_directives) {
                       int c;
                       char cmt_buffer[1024];
                       int i = sprintf(cmt_buffer, "/*%s", yytext);
                       curr_token = new token(NULL, TKN_CMNT, line, pos);
                       pos += strlen(yytext);
 	               while((c = yyinput_file()) != EOF && c != '\n') {
                             if (i == (int)sizeof(cmt_buffer)-4) {
                                 error(line, pos, file_name, "Preprocessor directive too long\n");
                             } else {
                                 cmt_buffer[i++] = (char)c;
                             }
                        }
                        cmt_buffer[i++] = '*';
                        cmt_buffer[i++] = '/';
                        cmt_buffer[i++] = '\n';
                        cmt_buffer[i++] = '\0';
               		char* cmt_text = new char[i];
		        memcpy(cmt_text, cmt_buffer, i);
                        curr_token->in_text = curr_token->out_text = cmt_text;
                        return 1;
                   }
 	       }
	       do {
	           *dst++ = tolower(*(unsigned char*)src);
	       } while (*src++);
	       nm = nm_entry::add(lc_buf, TKN_IDENT);
	       int tag = nm->tag;

	       if (turbo_pascal) {
	           if (tag == TKN_TYPE || tag == TKN_VAR) {
		       type_or_var_context = TRUE;
	           } else if (tag == TKN_BEGIN || tag == TKN_CONST) {
		       type_or_var_context = FALSE;
		   } else if (tag == TKN_IMPLEMENTATION) {
		       if (include_level > 0)  {
		           scanner.pop();
		           include_level -= 1;
			   BEGIN(use);
			   curr_token = new token((char*)NULL, TKN_UNIT_END);
                           return 1;
                       } else {
		           return tkn(TKN_IMPLEMENTATION);
                       }
		   } else if (tag == TKN_INTERFACE) {
                       if (use_chain == NULL) {
                           use_chain = new use_ctx(file_name, NULL);
                       }
		       tkn(TKN_INTERFACE);
		       return 1;
		   }
               }
	       if (tag == TKN_RESERVED) {
	           text = dprintf("%s_", lc_buf);
	           nm = nm_entry::add(text, TKN_IDENT);
	           tag = TKN_IDENT;
	       } else if (!preserve_case || tag != TKN_IDENT) {
	           text = strdup(lc_buf);
	       }
	       return tkn(tag);
             }


(\#[0-9]+|\#\$[0-9a-fA-F]+|\'([^\']|\'\')*\')+ { return tkn(TKN_SCONST); }

[ \t\f]+     { return tkn(TKN_SPACE); }

[\n]         { return tkn(TKN_LN); }

.            {
                error(line, pos, file_name, "unrecognized token: %s\n",
		      yytext);
             }

%%

void scan_ctx::push() {
    assert(sp < MAX_INCLUDE_DEPTH);
    stack[sp].file_name = file_name;
    stack[sp].buffer = YY_CURRENT_BUFFER;
    stack[sp].search_path = i_path;
    stack[sp].pos = pos;
    stack[sp].line = line;
    stack[sp].input = yyin;
    sp += 1;
}


void scan_ctx::attach(char* name, FILE* in) {
    pos = 0;
    line = 1;
    file_name = name;
    yyin = in;
    char* base_name = strrchr(name, PATH_SEP);
    if (base_name != NULL) {
	i_path = dprintf("%.*s%c%s", base_name-name, name, path_sep, i_path);
    }
    yy_switch_to_buffer(yy_create_buffer(yyin, YY_BUF_SIZE));
}

void scan_ctx::pop() {
    assert(sp > 0);
    sp -= 1;
    pos = stack[sp].pos;
    line = stack[sp].line;
    file_name = stack[sp].file_name;
    fclose(yyin);
    yyin = stack[sp].input;
    i_path = stack[sp].search_path;
    yy_switch_to_buffer(stack[sp].buffer);
}

bool scan_ctx::find(char* name) {
    for (int i = 0; i < sp; i ++ ) {
	if (strcmp(stack[i].file_name, name) == 0) {
	    return TRUE;
	}
    }
    return FALSE;
}

