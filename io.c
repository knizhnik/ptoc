#include "ptoc.h"
#include <errno.h>
#include <ctype.h>

#define IO_OK           0
#define IO_ERROR        errno
#define IO_EOF          -1
#define IO_FORMAT_ERROR -2

#define input_error(f) \
     (ferror(f) ? IO_ERROR : feof(f) ? IO_EOF : IO_FORMAT_ERROR)

#define Ok             0

#define TRUNCATE_FILE_ON_REWRITE 1

integer ioresult; /* Turbo Pascal IO operation completion status */

enum file_open_mode { 
    seek_mode   = 0x001,
    append_mode = 0x002,
    rd_mode     = 0x004, 
    wr_mode     = 0x008, 
    rdwr_mode   = 0x00C,
    trunc_mode  = 0x010,
    nocr_mode   = 0x020,
    bin_mode    = 0x040,
    shr_mode    = 0x080,
    wal_mode    = 0x100, 
    dlk_mode    = 0x200, 
    tmp_mode    = 0x400,
    buf_mode    = 0x800
};

struct { 
    char* option;
    int   flag;
} open_mode_decode[] = { 
    { "seek", seek_mode }, 
    { "apd",  append_mode }, 
    { "ro",   rd_mode }, 
    { "rw",   rdwr_mode }, 
    { "nocr", nocr_mode }, 
    { "shr",  shr_mode },
    { "bin",  bin_mode },
    { "dlk",  dlk_mode },
    { "wal",  wal_mode },
    { "temp", tmp_mode },
    { "buff", buf_mode },
    { NULL,   0}
};
 
enum file_state {fs_record_defined = 1, fs_next_pos = 2, fs_ignore_error = 4};


text_descriptor input;
text_descriptor output;

int paramcount;
char const* const* param_array;
boolean directvideo;
void (*exitproc)(void);

static void pio_exit_handler(void)
{
    if (exitproc) { 
	(*exitproc)();
    }
}

void pio_initialize(int argc, char const* argv[]) 
{
    input.desc.f = stdin;
    output.desc.f = stdout;
    paramcount = argc-1;
    param_array = argv;
    atexit(pio_exit_handler);
}

new_line_marker NL;

boolean pio_ignore_error;


static void handle_error(file_descriptor* fd) 
{  
    if (fd->error != IO_OK
	&& !(fd->state & fs_ignore_error) 
	&& !pio_ignore_error)
    {  
        if (fd->error == IO_FORMAT_ERROR) { 
	    fprintf(stderr, "IO: input format error in file '%s'\n", 
		    fd->name ? fd->name : "input");
	} else if (fd->error == IO_EOF) {
	    fprintf(stderr, "IO: access beyond end of file '%s'\n", 
		    fd->name ? fd->name : "input");
	} else { 
	    if (fd->name) { 
		fprintf(stderr, "IO: file '%s' ", fd->name);
		perror("");
	    } else { 
		perror("IO");
	    }
	}
	exit(2);
    }
    if (fd->error != IO_OK && fd->error != IO_FORMAT_ERROR 
	&& fd->error != IO_EOF && fd->f != NULL)
    {
	clearerr(fd->f);
    }
}
								    

static int parse_options(char const* options, 
			 char* new_file_name, 
			 char* extension)
{ 
    int i;
    int mode = 0;
    enum { st_start, st_file_name, st_extension } state = st_start;

    char* np; /* pointer to the end of file name */ 
    char* ep; /* pointer to the end of file extension */
    
    if (options == NULL) return 0;

    np = new_file_name + strlen(new_file_name);
    ep = extension + strlen(extension);

  parse_options:
    while (*options != '\0') { 
	switch(*options) { 
	  case '/':
	    state = st_start;
	    options += 1;
	    for (i = 0; open_mode_decode[i].option != NULL; i++) { 
		char *s = open_mode_decode[i].option;
		const char* p = options;
		while( *s != 0 && *s == tolower(*(unsigned char*)p)) { 
		    s += 1, p += 1; 
		}
		if (*s == 0) { 
		    int flag = open_mode_decode[i].flag;
		    if (flag == tmp_mode) {
			mode |= flag;
			tmpnam(new_file_name);
			np += strlen (new_file_name);
		    } else if(flag == buf_mode) { 
			if (*p == ':') { 
			    while(isdigit(*(unsigned char*)++p)); 
			}
		    } else {
			mode |= flag;
		    }
		    options = p;
		    goto parse_options;
		}
	    }
	    continue;
	  case ' ':
	    options += 1;
	    continue;
	  case '.':
	    if (state == st_start) { 
		state = st_extension;
	    }
	  default:
	    if (state == st_extension) { 
		*ep++ = *options++; 
	    } else { 
		state = st_file_name; 
		*np++ = *options++;
	    }
	}
    }
    *ep = '\0';
    *np = '\0';
    return mode;
}

#define MAX_OPTIONS   1024
#define MAX_FILE_NAME 1024
#define MAX_EXTENSION 8


/*  Ouput: 
 *    -1    if error (file not opened)
 *    size of file (in 512 byte blocks), else
 */
static integer pio_open_status(file_descriptor* fd) 
{ 
    if (fd->f != NULL) { 
	fpos_t pos;
	long   length; 
	fgetpos(fd->f, &pos);
	fseek(fd->f, 0, SEEK_END);
	length = ftell(fd->f);
	fsetpos(fd->f, &pos);
	return (length + 511) / 512; 
    }
    return -1;
}


static void open_file(file_descriptor* fd, const char* file_name, 
		      const char* options, integer* error_code, 
		      int mode, size_t record_size)
		   
{
    char  new_file_name[MAX_FILE_NAME];
    char  suffix[MAX_EXTENSION];
    char* mode_str;
        
    pio_close_file(fd); 

    new_file_name[0] = '\0';
    suffix[0] = '\0';

    mode |= parse_options(options, new_file_name, suffix)
	  | parse_options(file_name, new_file_name, suffix);

    strcat(new_file_name, suffix); 

    if (mode & seek_mode) mode |= rd_mode|wr_mode;

    if (record_size > 1) mode |= bin_mode;

    if (mode & bin_mode) { 
	if ((mode & (append_mode|rd_mode)) == (append_mode|rd_mode)) 
	    mode_str = "ab+";
	else if (mode & append_mode) mode_str = "ab"; 
	else if ((mode & rdwr_mode) == rd_mode) mode_str = "rb";
	else if ((mode & rdwr_mode) == wr_mode) mode_str = "wb";
	else if (mode & trunc_mode) mode_str = "wb+";
	else mode_str = "rb+";
    } else { 
	if ((mode & (append_mode|rd_mode)) == (append_mode|rd_mode)) 
	    mode_str = "a+";
	else if (mode & append_mode) mode_str = "a"; 
	else if ((mode & rdwr_mode) == rd_mode) mode_str = "r";
	else if ((mode & rdwr_mode) == wr_mode) mode_str = "w";
	else if (mode & trunc_mode) mode_str = "w+";
	else mode_str = "r+";
    } 

    fd->mode = mode;
    fd->state &= ~(fs_record_defined|fs_next_pos);
    fd->name = new_file_name;

    fd->f = fopen(new_file_name, mode_str);
    if (mode & tmp_mode) { 
       remove(new_file_name); 
    }
    
    if (fd->f == NULL) { 
	ioresult = fd->error = IO_ERROR;
	if (error_code == NULL) { 
	    handle_error(fd);
	}
	fd->name = NULL;
    } else { 
	ioresult = fd->error = IO_OK;
	fd->name = strdup(new_file_name);
    }
    if (error_code != NULL) { 
	*error_code = pio_open_status(fd); 
    }
}

void pio_rewrite_file(file_descriptor* fd,  size_t record_size, 
		      const char* file_name, const char* options, 
		      integer* error_code)
{ 
    if (file_name == NULL) { 
	if (fd == &output.desc) { 
	    /* Oregon Pascal-2 extension */
	    if (error_code) { 
		boolean ignore_error = pio_ignore_error;
		pio_ignore_error = true;
		cwrite("\n");
		pio_ignore_error = ignore_error;		
		*error_code = pio_open_status(fd); 
	    } else { 
		cwrite("\n");
	    }
	} else {
	    if (fd->f == NULL) { 
		char new_file_name[MAX_FILE_NAME];
		int mode = wr_mode|trunc_mode; 
		if (fd->name != NULL) { 
		    strcpy(new_file_name, fd->name);
		} else {
		    mode |= tmp_mode|rd_mode;
		    tmpnam(new_file_name);
		}
		open_file(fd, new_file_name, options, error_code, mode, 
			  record_size); 
	    } else { 
#if TRUNCATE_FILE_ON_REWRITE
		if ((fd->f = freopen(fd->name, (fd->mode & bin_mode) 
				     ? "wb+" : "w+", fd->f)) == NULL)  
#else
		if (fseek(fd->f, 0, 0) != Ok) 
#endif
		{
	            ioresult = fd->error = IO_ERROR;
		    if (error_code == NULL) { 
			handle_error(fd);
		    } else { 
			*error_code = IO_ERROR;
		    }
		} else { 
		    ioresult = fd->error = IO_OK;
		}
	    } 
	}
    } else { 
	open_file(fd, file_name, options, error_code, wr_mode|trunc_mode, 
		  record_size);
    }
} 

#ifndef _WIN32
static int stricmp(char const* a, char const* b)
{
    while (*b != 0) { 
	int diff = tolower(*(unsigned char*)a) - tolower(*(unsigned char*)b);
	if (diff != 0) { 
	    return diff;
	}
	a += 1;
	b += 1;
    }
    return *(unsigned char*)a;
}
#endif

void pio_open_file(file_descriptor* fd, size_t record_size, 
		   const char* file_name, const char* history,
		   integer* error_code)
{
    char const* name = file_name;
    int   mode;
    int   error;
    char  buf[MAX_FILE_NAME];

    if (stricmp(name, "-stdin") == 0) { 
	fd->f = stdin;
	name = "stdin";
	mode = rd_mode;
	goto complete_open;
    }

    if (stricmp(name, "-stdout") == 0) { 
	fd->f = stdout;
	name = "stdout";
	mode = wr_mode;
	goto complete_open;
    }

    if (*name == '^') { 
	int n;
	if (sscanf(name+1, "%d", &n) != 1 || n > paramcount) { 
	    error = file_not_specified;
	    goto handle_error;
	}
	name = param_array[n];
    } else if (*name == '*') { 
	printf("%s", name+1);
	if (scanf("%s", buf) != 1) { 
	    error = file_not_specified;
	    goto handle_error;
	}
	name = buf;
    }  

    if (stricmp(history, "new") == 0) {    
	FILE* f = fopen(name, "r");
	if (f != NULL) { 
	    fclose(f);
	    error = file_already_exists;
	    goto handle_error;
	}
	fd->f = fopen(name, "w+");
	mode = rdwr_mode|trunc_mode;
    } else if (stricmp(history, "old") == 0) {
	fd->f = fopen(name, "r+");
	mode = rdwr_mode;
	if (fd->f == NULL) { 
	    fd->f = fopen(name, "r");
	    mode = rd_mode;
	}
    } else if (stricmp(history, "unknown") == 0) {
	fd->f = fopen(name, "r+");
	mode = rdwr_mode;
	if (fd->f == NULL) { 
	    fd->f = fopen(name, "w+");
	}
    } else { 
	error = invalid_history;
	goto handle_error;
    }
    if (fd->f == NULL) { 
	error = unable_to_open_file;
	goto handle_error;
    }
  complete_open:
    fd->mode = mode;
    fd->state &= ~(fs_record_defined|fs_next_pos);
    fd->name = strdup(name);
    if (error_code != NULL) { 
	*error_code = file_successfully_opened;
    }
    return;

   handle_error:
    if (error_code == NULL) { 
	if (!(fd->state & fs_ignore_error)) { 
	    if (error == file_already_exists) { 
		fprintf(stderr, "open: 'new' history is specified and file "
			"'%s' already exists\n", name);
	    } else { 
		perror("open");
	    }
	    exit(2);
	}
    } else { 
	*error_code = (error == file_already_exists) 
	            ? unable_to_open_file : error;
    }
}



void pio_reset_file(file_descriptor* fd, size_t record_size, 
		    const char* file_name, const char* options,
		    integer* error_code)
{
    if (file_name == NULL) { 
	ioresult = fd->error = IO_OK;
	if (fd == &input.desc) { 
	    /* Oregon Pascal-2 extension */
	    if (error_code) { 
		boolean ignore_error = pio_ignore_error;
		pio_ignore_error = true;
		cread("\n");
		pio_ignore_error = ignore_error;		
		*error_code = pio_open_status(fd); 
	    } else { 
		cread("\n");
	    }
	} else { 
	    char new_file_name[MAX_FILE_NAME];
	    if (fd->f == NULL) { 
		assert(fd->name != NULL);
		strcpy(new_file_name, fd->name);
		open_file(fd, new_file_name, options, error_code, rd_mode, 
			  record_size);
	    } else { 		
		if (!(fd->mode & rd_mode)) { 
		    strcpy(new_file_name, fd->name);
		    open_file(fd, new_file_name, options, error_code, rd_mode,
			      record_size);
		} else { 
		    if (fseek(fd->f, 0, SEEK_SET) == Ok) { 
			fd->mode |= rd_mode;
			fd->state &= ~(fs_record_defined|fs_next_pos);
		    } else { 
			ioresult = fd->error = IO_ERROR;
			if (error_code == NULL) { 
			    handle_error(fd);
			}
		    }
		}
		if (error_code) { 
		    *error_code = pio_open_status(fd); 
		}
	    }
	} 
    } else { 
	open_file(fd, file_name, options, error_code, rd_mode, record_size); 
    }
} 


void pio_get_record(file_descriptor* fd, void* record, size_t record_size)
{
    ioresult = fd->error = IO_OK;
    if (!(fd->state & fs_next_pos)) { 
	if (fread(record, record_size, 1, fd->f) != 1) { 
	    ioresult = fd->error = input_error(fd->f);
	    handle_error(fd);
	}
    }
    fd->state &= ~(fs_record_defined|fs_next_pos);
}

void pio_put_record(file_descriptor* fd, void* record, size_t record_size)
{
    ioresult = fd->error = IO_OK;
    if (fd->state & fs_record_defined) { 
	if (fd->state & fs_next_pos) { 
	    if (fseek(fd->f, -(long)record_size, SEEK_CUR) != Ok) { 
		ioresult = fd->error = IO_ERROR;
		handle_error(fd);
		return;
	    }
	}
	if (fwrite(record, record_size, 1, fd->f) != 1) { 
	    ioresult = fd->error = IO_ERROR;
	}
    } else {
	if (fseek(fd->f, record_size, SEEK_CUR) != Ok) { 
	    ioresult = fd->error = IO_ERROR;
	}
    }    
    handle_error(fd);
    fd->state &= ~(fs_record_defined|fs_next_pos);
}


void pio_access_record(file_descriptor* fd, void* record, size_t record_size)
{
    ioresult = fd->error = IO_OK;
    if (!(fd->state & fs_record_defined)) { 
	if (fread(record, record_size, 1, fd->f) != 1) { 
	    ioresult = fd->error = input_error(fd->f);
	    handle_error(fd);
	} else { 
	    fd->state |= (fs_record_defined|fs_next_pos);
	}
    }
}

void pio_store_record(file_descriptor* fd, void* record, size_t record_size, 
		  void* src)
{
    memcpy(record, src, record_size);
    fd->state |= fs_record_defined;
}

void pio_copy_record(file_descriptor* src_fd, void* src_record, 
		     file_descriptor* dst_fd, void* dst_record,
		     size_t record_size) 
{
    pio_access_record(src_fd, src_record, record_size);
    if (src_fd->error == IO_OK) { 
	if (src_fd->error == IO_OK) { 
	    pio_store_record(dst_fd, dst_record, record_size, src_record);
	    pio_get_record(src_fd, src_record, record_size);
	}
    }
}

boolean pio_check_end_of_file(file_descriptor *fd)
{
    if (!(fd->state & fs_next_pos)) { 
	int ch = getc(fd->f);
	if (ch == EOF) return true;
	ungetc(ch, fd->f);
    }
    return false;
}

boolean pio_check_end_of_line(text_descriptor *td)
{
    if (!(td->desc.state & fs_record_defined)) { 
	int ch = getc(td->desc.f);
	if (ch == EOF) { 
	   return true;
	}
	td->record = ch;
	td->desc.state |= (fs_record_defined|fs_next_pos);
    }
    return td->record == '\n';
}

void pio_close_file(file_descriptor* fd)
{
    if (fd->f != NULL) { 
	if (fclose(fd->f) < 0) { 
	    ioresult = fd->error = IO_ERROR;
	    handle_error(fd);
	}
	fd->f = NULL; 
    }
    if (fd->name != NULL) { 
	free(fd->name); 
	fd->name = NULL; 
    }
}

void pio_seek_file(file_descriptor* fd, void *record, size_t record_size,
		   integer position)
{
    ioresult = fd->error = IO_OK;
    if (fseek(fd->f, (position-1)*record_size, SEEK_SET) != Ok) { 
	ioresult = fd->error = IO_ERROR;
        handle_error(fd);
    } else { 
	fd->state &= ~(fs_record_defined|fs_next_pos);
    }
}

long pio_get_file_size(file_descriptor* fd, size_t record_size) 
{
    fpos_t pos;
    long size;
    fgetpos(fd->f, &pos);
    fseek(fd->f, 0, SEEK_END);
    size = ftell(fd->f);
    fsetpos(fd->f, &pos);
    return size / record_size;
}


#undef rename

void pio_rename_file(file_descriptor* fd, const char* new_name)
{
    if (fd->f != NULL) { 
	fclose(fd->f);
	fd->f = NULL;
    }
    assert(fd->name != NULL); 
    ioresult = fd->error = IO_OK;
    if (*new_name == '.') {
	char *s = strrchr(fd->name, '.');
	char *name_with_ext;
	if (s == NULL) { 
	    s = fd->name + strlen(fd->name); 
	}
	name_with_ext = (char*)malloc(s+1-fd->name + strlen(new_name));
	sprintf(name_with_ext, "%.*s%s", (int)(s - fd->name),
		                         fd->name, new_name);
	if (rename(fd->name, name_with_ext) != Ok) { 
	    ioresult = fd->error = IO_ERROR;
	    handle_error(fd);
	    return;
	}
	free(fd->name);
	fd->name = name_with_ext;
    } else { 
	if (rename(fd->name, new_name) != Ok) { 
	    ioresult = fd->error = IO_ERROR;
	    handle_error(fd);
	    return;
	}
	free(fd->name);
	fd->name = strdup(new_name); 
    }
}

void pio_flush_file(file_descriptor* fd)
{
    fflush(fd->f);
}

void pio_delete_file(file_descriptor* fd)
{
    ioresult = fd->error = IO_OK;
    if (fd->f != NULL) { 
	fclose(fd->f);
	fd->f = NULL;
    }
    if (fd->name != NULL) {
	if (remove(fd->name) != Ok) { 
	    ioresult = fd->error = IO_ERROR;
	    handle_error(fd);
	} else { 
	    free(fd->name);
	    fd->name = NULL;
	}
    }
}
 
void pio_read_record(file_descriptor* fd, void* record, size_t record_size, 
		 void* dst)
{ 
    pio_access_record(fd, record, record_size);
    if (fd->error == IO_OK) {
	memcpy(dst, record, record_size);
	pio_get_record(fd, record, record_size);
    }
}

void pio_write_record(file_descriptor* fd, void* record, size_t record_size,
		  void* src)
{
    memcpy(record, src, record_size);
    fd->state |= fs_record_defined;
    pio_put_record(fd, record, record_size);
}


/*
 * Text input functions
 */

#define preinput(td) \
    if (td->desc.state & fs_next_pos) { \
	ungetc(td->record, td->desc.f); \
        td->desc.state &= ~(fs_record_defined|fs_next_pos); \
    }

void pio_input_real(text_descriptor* td, double* val)
{
    preinput(td);
    td->desc.error = ioresult = IO_OK;
    if (fscanf(td->desc.f, "%lf", val) != 1) { 
	td->desc.error = ioresult = input_error(td->desc.f);
	handle_error(&td->desc);
    }
}

void pio_input_integer(text_descriptor* td, int* val)
{
    preinput(td);
    td->desc.error = ioresult = IO_OK;
    if (fscanf(td->desc.f, "%d", val) != 1) { 
	td->desc.error = ioresult = input_error(td->desc.f);
	handle_error(&td->desc);
    }
}

void pio_input_unsigned(text_descriptor* td, unsigned* val)
{
    preinput(td);
    td->desc.error = ioresult = IO_OK;
    if (fscanf(td->desc.f, "%u", val) != 1) { 
	td->desc.error = ioresult = input_error(td->desc.f);
	handle_error(&td->desc);
    }
}

void pio_input_long(text_descriptor* td, long* val)
{
    preinput(td);
    td->desc.error = ioresult = IO_OK;
    if (fscanf(td->desc.f, "%ld", val) != 1) { 
	td->desc.error = ioresult = input_error(td->desc.f);
	handle_error(&td->desc);
    }
}

void pio_input_ulong(text_descriptor* td, unsigned long* val)
{
    preinput(td);
    td->desc.error = ioresult = IO_OK;
    if (fscanf(td->desc.f, "%lu", val) != 1) { 
	td->desc.error = ioresult = input_error(td->desc.f);
	handle_error(&td->desc);
    }
}

void pio_input_char(text_descriptor* td, char* val)
{
    if (!(td->desc.state & fs_next_pos)) { 
	int ch = getc(td->desc.f);
	if (ch == EOF) { 
	    td->desc.error = ioresult = IO_EOF;
	    handle_error(&td->desc);
	    return;
	}
	td->record = ch;
    }
    if (td->record == '\n') td->record = ' ';
    *val = td->record;
    td->desc.state &= ~(fs_record_defined|fs_next_pos);
}

int pio_input_string(text_descriptor* td, char* dst, size_t len, int padding)
{
    int ch = (td->desc.state & fs_next_pos) ? td->record : getc(td->desc.f); 
    size_t n = 0;

    while (n < len && ch != EOF && ch != '\n') {
	*dst++ = ch;
	ch = getc(td->desc.f);
	n += 1;
    }
    if (padding) { 
	while (n < len) { 
	    *dst++ = ' ';
	    n += 1;
	}
    }
    td->record = ch;
    if (ch != EOF) { 
	td->desc.state |= (fs_record_defined|fs_next_pos);
        td->desc.error = ioresult = IO_OK; 
    } else { 
        td->desc.error = ioresult = IO_EOF; 
	handle_error(&td->desc);
    }
    return n;
}

void pio_input_newline(text_descriptor* td)
{
   int ch = (td->desc.state & fs_next_pos) ? td->record : getc(td->desc.f); 
   while(ch != EOF && ch != '\n') { 
       ch = getc(td->desc.f);
   }
   td->desc.state &= ~(fs_record_defined|fs_next_pos);
   td->desc.error = ioresult = (ch == EOF) ? IO_EOF : IO_OK;
   handle_error(&td->desc);
}

/*
 * Text output functions
 */

#define postoutput(td) (td->desc.state &= ~(fs_record_defined|fs_next_pos),  \
			td->desc.error=ferror(td->desc.f) ? IO_ERROR : IO_OK,\
			handle_error(&td->desc))

void pio_output_end_of_page(text_descriptor* td)
{
    putc('\f', td->desc.f);
    postoutput(td);
}

void pio_output_real(text_descriptor* td, double val, const int* width, 
		 const int* prec)
{
    if (prec == NULL && width == NULL) { 
	fprintf(td->desc.f, "% G", val);
    } else if (prec != NULL && width != NULL) { 
	if (*prec < 0) {  
	    fprintf(td->desc.f, "%*.*E", *width, -*prec, val);
	} else { 
	    fprintf(td->desc.f, "%*.*f", *width, *prec, val);
	}
    } else { 
	fprintf(td->desc.f, "%*E", *width, val);
    }
    postoutput(td);
}

void pio_output_integer(text_descriptor* td, int val, const int* width)
{
    if (width == NULL) { 
	fprintf(td->desc.f, "%7d", val);
    } else if(*width < 0) { 
	fprintf(td->desc.f, "%*o", -*width, val);
    } else { 
	fprintf(td->desc.f, "%*d", *width, val);
    }
    postoutput(td);
}

void pio_output_long(text_descriptor* td, long val, const int* width)
{
    if (width == NULL) { 
	fprintf(td->desc.f, "%7ld", val);
    } else if(*width < 0) { 
	fprintf(td->desc.f, "%*lo", -*width, val);
    } else { 
	fprintf(td->desc.f, "%*ld", *width, val);
    }
    postoutput(td);
}

void pio_output_unsigned(text_descriptor* td, unsigned val, const int* width)
{
    if (width == NULL) { 
	fprintf(td->desc.f, "%7u", val);
    } else if(*width < 0) { 
	fprintf(td->desc.f, "%*o", -*width, val);
    } else { 
	fprintf(td->desc.f, "%*u", *width, val);
    }
    postoutput(td);
}

void pio_output_ulong(text_descriptor* td, unsigned long val, const int* width)
{
    if (width == NULL) { 
	fprintf(td->desc.f, "%7lu", val);
    } else if(*width < 0) { 
	fprintf(td->desc.f, "%*lo", -*width, val);
    } else { 
	fprintf(td->desc.f, "%*lu", *width, val);
    }
    postoutput(td);
}

void pio_output_char(text_descriptor* td, char val, const int* width)
{
    if (width == NULL) { 
	fprintf(td->desc.f, "%c", val);
    } else { 
	fprintf(td->desc.f, "%*c", *width, val);
    }
    postoutput(td);
}

void pio_output_boolean(text_descriptor* td, boolean val, const int* width)
{
    if (width == NULL) { 
	fprintf(td->desc.f, val ? " TRUE" : "FALSE");
    } else {  
	fprintf(td->desc.f, "%*s", *width, val ? "TRUE" : "FALSE");
    }
    postoutput(td);
}

void pio_output_string(text_descriptor* td, const char* buf, size_t len, 
		   const int* width)
{
    if (width == NULL) { 
	fprintf(td->desc.f, "%.*s", (int)len, buf);
    } else if ((size_t)*width >= len) {
        fprintf(td->desc.f, "%*.*s", *width, (int)len, buf);
    } else { 
	fprintf(td->desc.f, "%.*s", *width, buf);
    }
    postoutput(td);
}

void pio_output_newline(text_descriptor* td)
{
    putc('\n', td->desc.f);
    postoutput(td);
}


static void format_read(text_descriptor* td, char* fmt, va_list ap) 
{ 
    td->desc.error = ioresult = IO_OK;

    while(*fmt != '\0' && td->desc.error == IO_OK) {
	if (*fmt++ == '%') {
	    switch (*fmt++) { 
	      case 'i':
		{ integer* ptr = va_arg(ap, integer*);
		  int tmp;
		  pio_input_integer(td, &tmp);
		  *ptr = tmp;
                }
		continue;
	      case 'f':
		{ real* ptr = va_arg(ap, real*);
		  double tmp;
		  pio_input_real(td, &tmp);
		  *ptr = (real)tmp;
                }
		continue;
	      case 'c':
		{ char* ptr = va_arg(ap, char*);
		  pio_input_char(td, ptr);
		}
		continue;
	      case 'B':
		{ int tmp;
		  pio_input_integer(td, &tmp);
		  *va_arg(ap, char*) = tmp;
		}
		continue;
	      case 'W':
		{ int tmp;
		  pio_input_integer(td, &tmp);
		  *va_arg(ap, short*) = tmp;
		}
		continue;
	      case 's':
		{ int  low  = va_arg(ap, int);
		  int  high = va_arg(ap, int);
		  char *ptr = va_arg(ap, char*);
		  pio_input_string(td, ptr, high-low+1, true);
		}
		continue;
	    }	
	} 
	if (*(fmt-1) == '\n') { 
	    pio_input_newline(td);
	} else { 
	    /*extension: pascal converter never generate such format strings*/
	    int ch = (td->desc.state & fs_next_pos) ? td->record 
		                                    : getc(td->desc.f);
	    td->desc.state &= ~(fs_record_defined|fs_next_pos);
	    if (ch != *(unsigned char*)(fmt-1)) { 
		td->desc.error = ioresult = IO_FORMAT_ERROR; 
		handle_error(&td->desc);
	    }
	}
    }
}

		
enum { const_prec=1, var_prec=2, const_width=4, var_width=8 };

static void format_write(text_descriptor* td, char* fmt, va_list ap) 
{
    td->desc.error = ioresult = IO_OK;
    while(*fmt != '\0' && td->desc.error == IO_OK) { 
	if (*fmt++ == '%') {
	    int prec, width;
	    int format = 0;

	    if (fmt[0] == '*') { 
		format |= var_width;
		fmt += 1;
		if (fmt[0] == '.' &&  fmt[1] == '*') { 
		    format |= var_prec;
		    fmt += 2;
		}
	    } else { 
		int pos;
		if (sscanf(fmt, "%d.%d%n", &width, &prec, &pos) == 2) { 
		    format = const_width|const_prec;
		    fmt += pos;
		} else if (sscanf(fmt, "%d%n", &width, &pos) == 1) {
		    format = const_width;
		    fmt += pos;
		}		    
	    }
	    switch (*fmt++) { 
	      case 'i':
		{ int val = va_arg(ap, int);
		  if (format & var_width) width = va_arg(ap, int);
		  pio_output_integer(td, val, 
				     (format & (const_width|var_width))
				     ? &width : NULL);
		}
		continue;
	      case 'f':
		{ real val = (real)va_arg(ap, double);
		  if (format & var_width) { 
		      width = va_arg(ap, int);
		      if (format & var_prec) { 
			  prec = va_arg(ap, int);
		      }
		  }
		  pio_output_real(td, val, 
				  (format & (const_width|var_width)) 
				      ? &width : NULL, 
				  (format & (const_prec|var_prec))  
		           	      ? &prec : NULL);
		}
		continue;
	      case 's':
		{ int  low  = va_arg(ap, int);
		  int  high = va_arg(ap, int);
		  char *val = va_arg(ap, char*); 
		  if (format & var_width) width = va_arg(ap, int);
		  pio_output_string(td, val, high-low+1, 
				    (format & (const_width|var_width))
				        ? &width : NULL);
		}
		continue;
	      case 'z':
		{ char *val = va_arg(ap, char*); 
		  if (format & var_width) width = va_arg(ap, int);
		  pio_output_string(td, val, strlen(val), 
				    (format & (const_width|var_width))
				        ? &width : NULL);
		}
		continue;
	      case 'c':
		{ char val = (char)va_arg(ap, int); 
		  if (format & var_width) width = va_arg(ap, int);
		  pio_output_char(td, val, (format & (const_width|var_width))
				           ? &width : NULL);
		}
		continue;
	      case 'b':
		{ boolean val = (boolean)va_arg(ap, int); 
		  if (format & var_width) width = va_arg(ap, int);
		  pio_output_boolean(td, val, (format&(const_width|var_width))
				              ? &width : NULL);
		}
		continue;
	    }
	}
	putc(*(fmt-1), td->desc.f);
	postoutput(td);
    }
}


void cread(char* fmt, ...) 
{
    va_list ap;
    va_start(ap, fmt);

    format_read(&input, fmt, ap);

    va_end(ap);
}

void tread(text_descriptor* td, char* fmt, ...) 
{
    va_list ap;
    va_start(ap, fmt);

    format_read(td, fmt, ap);

    va_end(ap);
}

void cwrite(char* fmt, ...) 
{
    va_list ap;
    va_start(ap, fmt);

    format_write(&output, fmt, ap);

    va_end(ap);
}

void twrite(text_descriptor* td, char* fmt, ...) 
{
    va_list ap;
    va_start(ap, fmt);

    format_write(td, fmt, ap);

    va_end(ap);
}
    
void pio_file_ignore_error(file_descriptor* fd) 
{
    fd->state |= fs_ignore_error;
}

boolean pio_ioerror(file_descriptor* fd) 
{
    return fd->error != IO_OK;
}

integer pio_iostatus(file_descriptor* fd) 
{
    return fd->error;
}


