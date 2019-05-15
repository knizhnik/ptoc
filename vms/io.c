#include "ptoc.h"
#include <errno.h>
#include <ctype.h>

#define UPCASE_INPUT 1

#ifdef __VMS
#include <rms.h>
#include <ssdef.h>
#endif
#define IO_OK           0
#define IO_ERROR        errno
#define IO_EOF          -1
#define IO_FORMAT_ERROR -2

#define input_error(f) \
     (ferror(f) ? IO_ERROR : feof(f) ? IO_EOF : IO_FORMAT_ERROR)

#define Ok             0

enum file_open_mode { 
    seek_mode   = 0x001,
    append_mode = 0x002,
    rd_mode     = 0x004, 
    wr_mode     = 0x008, 
    rdwr_mode   = 0x00C,
    trunc_mode  = 0x010,
    nocr_mode   = 0x020,
    cr_mode     = 0x040,
    shr_mode    = 0x080,
    wal_mode    = 0x100, 
    dlk_mode    = 0x200, 
    tmp_mode    = 0x400,
    buf_mode    = 0x800
};

struct { 
    char* rsx_option;
    char* vms_option; 
    int   flag;
} open_mode_decode[] = { 
    { "seek", NULL, seek_mode }, 
    { "apd",  NULL, append_mode }, 
    { "ro",   NULL, rd_mode }, 
    { "rw",   NULL, rdwr_mode }, 
    { "cr",   NULL, cr_mode }, 
    { "nocr", "ctx=bin", nocr_mode }, 
    { "shr",  "shr=upd", shr_mode },
    { "dlk",  NULL, dlk_mode },
    { "wal",  NULL, wal_mode },
    { "temp", NULL, tmp_mode },
    { "buff", NULL, buf_mode },
    { NULL,   NULL, 0}
};
 
enum file_state {fs_record_defined = 1, fs_next_pos = 2, fs_ignore_error = 4};


#ifdef __VMS
text_descriptor input;
text_descriptor output;

void pio_initialize() 
{ 
#ifdef UPCASE_INPUT
    input.desc.f = fopen("sys$input", "r", "rop=cvt");
#else
    input.desc.f = stdin; 
#endif
    output.desc.f = stdout; 
}

static char* strdup(const char* src) 
{ 
    char* dup = (char*)malloc(strlen(src)+1);
    strcpy(dup, src);
    return dup;
}

#else

text_descriptor input  = { { stdin } };
text_descriptor output = { { stdout } };

void pio_initialize() {}
#endif

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
		fprintf(stderr, "IO: file '%s'", fd->name);
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
								    
#define MAX_OPTIONS   32
#define MAX_FILE_NAME 1024
#define MAX_EXTENSION 256


static int parse_options(char    const* options, 
			 char*   new_file_name, 
			 char*** new_options,
			 char*   extension)
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
	    for (i = 0; open_mode_decode[i].rsx_option != NULL; i++) { 
		char *s = open_mode_decode[i].rsx_option;
		const char* p = options;
		while( *s != 0 && *s == tolower(*p)) { s += 1, p += 1; }
		if (*s == 0) { 
		    int flag = open_mode_decode[i].flag;
		    if (flag == tmp_mode) {
			tmpnam(new_file_name);
			mode |= flag;
			np += strlen (new_file_name);
		    } else if(flag == buf_mode) { 
			if (*p == ':') { 
			    while(isdigit(*++p)); 
			}
		    } else {
			mode |= flag;
			if (open_mode_decode[i].vms_option != NULL) { 
			    *(*new_options)++ = open_mode_decode[i].vms_option;
			}
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
	  case ';':
	    if (state == st_start) { 
		state = st_extension;
	    }
	  default:
	    if (state == st_extension) { 
		*ep++ = *options++; 
		assert(extension - ep < MAX_EXTENSION);
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

#ifdef __VMS
integer pio_get_file_version(file_descriptor* fd) 
{
    int vers = 0;
    char* s; 
    assert(fd->name != NULL);
    s = strrchr(fd->name, ';');
    assert(s != NULL);
    sscanf(s+1, "%d", &vers);
    return vers;
}

static int acc_callback(file_descriptor* fd, struct FAB* fab, struct RAB* rab) 
{ 
   fd->fab = fab;
   return SS$_NORMAL;
} 

static FILE* pio_fopen(const char* name, const char* mode, 
		       char** option, int n_options, 
		       file_descriptor* fd)
{ 
    assert(n_options < 8);
    switch(n_options) {  
      case 0:
	return fopen(name, mode, "acc", acc_callback, fd);
      case 1:
	return fopen(name, mode, option[0], "acc", acc_callback, fd);
      case 2: 
	return fopen(name, mode, option[0], option[1], 
		     "acc", acc_callback, fd);
      case 3:
	return fopen(name, mode, option[0], option[1], option[2],
		     "acc", acc_callback, fd);
      case 4: 
	return fopen(name, mode, option[0], option[1], option[2], option[3], 
		     "acc", acc_callback, fd);
      case 5:
	return fopen(name, mode, option[0], option[1], option[2], option[3],
		     option[4], "acc", acc_callback, fd);
      case 6: 
	return fopen(name, mode, option[0], option[1], option[2], option[3],
		     option[4], option[5], "acc", acc_callback, fd);
      case 7:
	return fopen(name, mode, option[0], option[1], option[2], option[3],
		     option[4], option[5], option[6], "acc", acc_callback, fd);
      case 8:
	return fopen(name, mode, option[0], option[1], option[2], option[3],
		     option[4], option[5], option[6], option[7], "acc", 
		     acc_callback, fd);
    }
}
#endif


/*  Ouput: 
 *    -1    if error (file not opened)
 *    size of file (in 512 byte blocks), else
 */
static integer pio_open_status(file_descriptor* fd) 
{ 
#ifdef __VMS
    return fd->f ? ((struct FAB*)fd->fab)->fab$l_alq : -1;
#else
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
#endif
}


static void pio_open_file(file_descriptor* fd, const char* file_name, 
			  const char* options, integer* error_code, 
			  int   mode, size_t record_size)
		   
{
    char    new_file_name[MAX_FILE_NAME];
    char*   new_options[MAX_OPTIONS];
    char**  option_ptr = new_options; 
    char    suffix[MAX_EXTENSION];
    char    record_spec[16];
    char*   mode_str;
    char*   vers_ptr;

    pio_close_file(fd); 

    new_file_name[0] = '\0';
    suffix[0] = '\0';

    mode |= parse_options(options, new_file_name, &option_ptr, suffix)
	  | parse_options(file_name, new_file_name, &option_ptr, suffix);

    strcat(new_file_name, suffix); 

    /* fuzzy logic */ 
    if (mode & seek_mode) mode |= rd_mode | wr_mode; 

    if (record_size > 1) { 
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

#ifdef __VMS
    /* name of file is assigned by acc_callback */

    
    /* delete file if mode_str == 'w*' and manual version present */
    if (mode_str[0] == 'w')
    {
	vers_ptr = strrchr (new_file_name, ';');
	if (vers_ptr)
	{
	    int vers;

	    assert (sscanf (vers_ptr+1, "%d", &vers) == 1);
	    if (vers > 0)
	    {
		remove (new_file_name);  /* FIXME: check status */
	    }
	}
    }
    if (record_size != 1 && !(fd->mode & cr_mode)) { 
	sprintf(record_spec, "mrs=%d", record_size);
	*option_ptr++ = "rfm=fix"; 
	*option_ptr++ = record_spec;
    }
#ifdef UPCASE_INPUT
    if (fd == &input.desc) {
	*option_ptr++ = "rop=cvt"; 
    } 
#endif   
    if (mode & tmp_mode) { 
        *option_ptr++ = "fop=tmd";
    }
    fd->f = pio_fopen(new_file_name, mode_str, new_options, 
		      option_ptr - new_options, fd);

    if (fd->f == NULL && (vers_ptr = strstr(new_file_name, ";-")) != NULL)
    { 
       *vers_ptr = '\0';
       fd->f = pio_fopen(new_file_name, mode_str, new_options, 
			 option_ptr - new_options, fd);
    }     

    if (fd->f != NULL) {
       int len = ((struct FAB*)fd->fab)->fab$l_nam->nam$b_rsl;
       memcpy(new_file_name, ((struct FAB*)fd->fab)->fab$l_nam->nam$l_rsa,len);
       new_file_name[len] = '\0';
    }
#else
    fd->f = fopen(new_file_name, mode_str);
    if (mode & tmp_mode) {
        remove(new_file_name);
    }
#endif
    
    if (fd->f == NULL) { 
	fd->error = IO_ERROR;
	if (error_code == NULL) { 
	    handle_error(fd);
	}
	fd->name = NULL;
    } else { 
	fd->error = IO_OK;
	fd->name = strdup(new_file_name);
    }
    if (error_code != NULL) { 
	*error_code = pio_open_status(fd); 
    }
}

void pio_rewrite_file(file_descriptor* fd, size_t record_size, 
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
	    char new_file_name[MAX_FILE_NAME];
            int mode = wr_mode|trunc_mode;
            if (fd->f == NULL || !(fd->mode & tmp_mode)) {
                if (fd->name != NULL) {
                    strcpy(new_file_name, fd->name);
                } else {
                    mode |= tmp_mode|rd_mode;
                    tmpnam(new_file_name);
                }
                pio_open_file(fd, new_file_name, options, error_code,
                              mode, record_size);
            } else {
                if (fseek(fd->f, 0, 0) != Ok) {
                    fd->error = IO_ERROR;
                    if (error_code == NULL) {
                        handle_error(fd);
                    } else {
                        *error_code = IO_ERROR;
                    }
                }
            }
	}
    } else { 
	pio_open_file(fd, file_name, options, error_code, 
		      wr_mode|trunc_mode, record_size); 
    }
} 

void pio_reset_file(file_descriptor* fd, size_t record_size, 
		    const char* file_name, const char* options, 
		    integer* error_code)
{

    if (file_name == NULL) { 
	fd->error = IO_OK;
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
	    assert(fd->f != NULL);
	    if (!(fd->mode & rd_mode)) { 
		char new_file_name[MAX_FILE_NAME];
		strcpy(new_file_name, fd->name);
		pio_open_file(fd, new_file_name, options, error_code, 
			      rd_mode, record_size);
	    } else { 
		if (fseek(fd->f, 0, SEEK_SET) == Ok) { 
		    fd->mode |= rd_mode;
		    fd->state &= ~(fs_record_defined|fs_next_pos);
		} else { 
		    fd->error = IO_ERROR;
		    if (error_code == NULL) { 
			handle_error(fd);
		    }
		}
		if (error_code != NULL) { 
		    *error_code = pio_open_status(fd); 
		}
	    }
	} 
    } else { 
	pio_open_file(fd, file_name, options, error_code, rd_mode,
		      record_size); 
    }
} 


#define MAX_RECORD_SIZE 4096

void pio_get_record(file_descriptor* fd, void* record, size_t record_size)
{
    fd->error = IO_OK;
    if (!(fd->state & fs_next_pos)) { 
	if (fd->mode & cr_mode) { 
	    char buffer[MAX_RECORD_SIZE];
	    int  len;

	    if (fgets(buffer, sizeof buffer, fd->f) == NULL) { 
		fd->error = input_error(fd->f);
		handle_error(fd);
	    } else { 
		len = strlen(buffer);
		if (len == 0 || buffer[len-1] != '\n') { 
		    fd->error = IO_FORMAT_ERROR; 
		    handle_error(fd);
		} else { 
		    memcpy(record, buffer, 
			   (len >= record_size) ? record_size : len-1);
		}
	    }
	} else { 
	    if (fread(record, record_size, 1, fd->f) != 1) { 
		fd->error = input_error(fd->f);
		handle_error(fd);
	    }
	}
    }
    fd->state &= ~(fs_record_defined|fs_next_pos);
}

void pio_put_record(file_descriptor* fd, void* record, size_t record_size)
{
    int file_record_size = record_size;
    if (record_size != 1 && !(fd->mode & cr_mode)) { 
	file_record_size = (file_record_size + 1) & ~1;
    } 
    fd->error = IO_OK;
    if (fd->state & fs_record_defined) { 
	if (fd->state & fs_next_pos) { 
	    if (fseek(fd->f, -file_record_size, SEEK_CUR) != Ok) { 
		fd->error = IO_ERROR;
		handle_error(fd);
		return;
	    }
	}
	if (fwrite(record, record_size, 1, fd->f) != 1) { 
	    fd->error = IO_ERROR;
	}
    } else {
	if (fseek(fd->f, file_record_size, SEEK_CUR) != Ok) { 
	    fd->error = IO_ERROR;
	}
    }    
    handle_error(fd);
    fd->state &= ~(fs_record_defined|fs_next_pos);
}


void pio_access_record(file_descriptor* fd, void* record, size_t record_size)
{
    fd->error = IO_OK;
    if (!(fd->state & fs_record_defined)) { 
	if (fd->mode & cr_mode) { 
	    char buffer[MAX_RECORD_SIZE];
	    int  len;

	    if (fgets(buffer, sizeof buffer, fd->f) != NULL) { 
		len = strlen(buffer);
		if (len == 0 || buffer[len-1] != '\n') { 
		    fd->error = IO_FORMAT_ERROR; 
		    handle_error(fd);
		    return;
		}
		memcpy(record, buffer, (len >= record_size) 
		       ? record_size : len-1);
	    } else { 
#ifdef NO_WRITE_ACCESS  /* this can happend if record is accessed for writing */	    
		fd->error = input_error(fd->f);
		handle_error(fd);
#else
		fd->state |= fs_record_defined;
#endif
		return;
	    }
	} else { 
	    if (fread(record, record_size, 1, fd->f) != 1) { 
#ifdef NO_WRITE_ACCESS  /* this can happend if record is accessed for writing */	    
		fd->error = input_error(fd->f);
		handle_error(fd);
#else
		fd->state |= fs_record_defined;
#endif
		return;
	    }
	} 
	fd->state |= (fs_record_defined|fs_next_pos);
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
	    fd->error = IO_ERROR;
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
    int file_record_size = record_size;
    if (record_size != 1 && !(fd->mode & cr_mode)) { 
	file_record_size = (file_record_size + 1) & ~1;
    }
    fd->error = IO_OK;
    if (fseek(fd->f, (position-1)*file_record_size, SEEK_SET) != Ok) { 
	fd->error = IO_ERROR;
        handle_error(fd);
    } else { 
	fd->state &= ~(fs_record_defined|fs_next_pos);
    }
}

#undef rename

void pio_rename_file(file_descriptor* fd, const char* new_name)
{
    if (fd->f != NULL) { 
	fclose(fd->f);
	fd->f = NULL;
    }
    assert(fd->name != NULL); 
    fd->error = IO_OK;
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
	    fd->error = IO_ERROR;
	    handle_error(fd);
	    return;
	}
	free(fd->name);
	fd->name = name_with_ext;
    } else { 
	if (rename(fd->name, new_name) != Ok) { 
	    fd->error = IO_ERROR;
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
    fd->error = IO_OK;
    if (fd->f != NULL) { 
	fclose(fd->f);
	fd->f = NULL;
    }
    if (fd->name != NULL) {
	if (remove(fd->name) != Ok) { 
	    fd->error = IO_ERROR;
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

void pio_input_real(text_descriptor* td, real* val)
{
    char c;
    double tmp;
    preinput(td);
    td->desc.error = IO_OK;

    /* comma is valid separator */
    if (fscanf(td->desc.f, "%c", &c) == 1 && c != ',') { 
	ungetc (c, td->desc.f);
    }

    if (fscanf(td->desc.f, "%lf", &tmp) != 1) { 
	td->desc.error = input_error(td->desc.f);
	handle_error(&td->desc);
    }
    *val = tmp;
}

void pio_input_integer(text_descriptor* td, integer* val)
{
    int tmp;
    char c;
    preinput(td);
    td->desc.error = IO_OK;

    /* comma is valid separator */
    if (fscanf(td->desc.f, "%c", &c) == 1 && c != ',') { 
	ungetc (c, td->desc.f);
    }

    if (fscanf(td->desc.f, "%d", &tmp) != 1) { 
	td->desc.error = input_error(td->desc.f);
	handle_error(&td->desc);
    }
    *val = tmp;
}

void pio_input_char(text_descriptor* td, char* val)
{
    if (!(td->desc.state & fs_next_pos)) { 
	int ch = getc(td->desc.f);
	if (ch == EOF) { 
	    td->desc.error = IO_EOF;
	    handle_error(&td->desc);
	    return;
	}
	td->record = ch;
    }
    if (td->record == '\n') td->record = ' ';
    *val = td->record;
    td->desc.state &= ~(fs_record_defined|fs_next_pos);
}

void pio_input_string(text_descriptor* td, char* dst, size_t len)
{
    int ch = (td->desc.state & fs_next_pos) ? td->record : getc(td->desc.f); 

    while (len != 0 && ch != EOF && ch != '\n') {
	*dst++ = ch;
	ch = getc(td->desc.f);
	len -= 1;
    }
    while (len != 0) { 
	*dst++ = ' ';
	len -= 1;
    }
    td->record = ch;
    if (ch != EOF) { 
	td->desc.state |= (fs_record_defined|fs_next_pos);
        td->desc.error = IO_OK; 
    } else { 
        td->desc.error = IO_EOF; 
	handle_error(&td->desc);
    }
}

void pio_input_newline(text_descriptor* td)
{
   int ch = (td->desc.state & fs_next_pos) ? td->record : getc(td->desc.f); 
   while(ch != EOF && ch != '\n') { 
       ch = getc(td->desc.f);
   }
   td->desc.state &= ~(fs_record_defined|fs_next_pos);
   td->desc.error = (ch == EOF) ? IO_EOF : IO_OK;
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

void pio_output_real(text_descriptor* td, real val, const int* width, 
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
	fprintf(td->desc.f, "% .*E", *width, val);
    }
    postoutput(td);
}

void pio_output_integer(text_descriptor* td, integer val, const int* width)
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
    } else if (*width >= len) { 
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
    td->desc.error = IO_OK;

    while(*fmt != '\0' && td->desc.error == IO_OK) {
	if (*fmt++ == '%') {
	    switch (*fmt++) { 
	      case 'i':
		{ integer* ptr = va_arg(ap, integer*);
		  pio_input_integer(td, ptr);
                }
		continue;
	      case 'f':
		{ real* ptr = va_arg(ap, real*);
		  pio_input_real(td, ptr);
                }
		continue;
	      case 'c':
		{ char* ptr = va_arg(ap, char*);
		  pio_input_char(td, ptr);
		}
		continue;
	      case 'B':
		{ integer tmp;
		  pio_input_integer(td, &tmp);
		  *va_arg(ap, char*) = tmp;
		}
		continue;
	      case 'W':
		{ integer tmp;
		  pio_input_integer(td, &tmp);
		  *va_arg(ap, short*) = tmp;
		}
		continue;
	      case 's':
		{ int  low  = va_arg(ap, int);
		  int  high = va_arg(ap, int);
		  char *ptr = va_arg(ap, char*);
		  pio_input_string(td, ptr, high-low+1);
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
		td->desc.error = IO_FORMAT_ERROR; 
		handle_error(&td->desc);
	    }
	}
    }
}

		
enum { const_prec=1, var_prec=2, const_width=4, var_width=8 };

static void format_write(text_descriptor* td, char* fmt, va_list ap) 
{
    td->desc.error = IO_OK;
    while(*fmt != '\0' && td->desc.error == IO_OK) { 
	if (*fmt++ == '%') {
	    int prec;
	    int width;
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
		{ real val = va_arg(ap, real);
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
		{ char val = va_arg(ap, char); 
		  if (format & var_width) width = va_arg(ap, int);
		  pio_output_char(td, val, (format & (const_width|var_width))
				           ? &width : NULL);
		}
		continue;
	      case 'b':
		{ boolean val = va_arg(ap, boolean); 
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
