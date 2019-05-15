#ifndef __IO_H__
#define __IO_H__


typedef struct file_descriptor { 
    FILE *f;
    char *name;
#ifdef __VMS
    void *fab;
#endif
    int   error;
    short mode; 
    short state;
} file_descriptor;

typedef struct text_descriptor { 
    file_descriptor desc;
    char            record;
} text_descriptor;



#ifdef __cplusplus
extern "C" { 
#endif

extern boolean pio_ignore_error;

void pio_initialize(int argc, char const* argv[]);

void pio_rewrite_file(file_descriptor* fd, 
		      size_t record_size,
		      const char* file_name, const char* options, 
		      integer* error_code); 

void pio_open_file(file_descriptor* fd, 
		   size_t record_size,
		   const char* file_name, 
		   const char* history, 
		   integer* error_code); 

void pio_reset_file(file_descriptor* fd, 
		    size_t record_size,
		    const char* file_name, const char* options, 
		    integer* error_code); 

void pio_get_record(file_descriptor* fd, void* record, size_t record_size);


void pio_put_record(file_descriptor* fd, void* record, size_t record_size);


void pio_access_record(file_descriptor* fd, void* record, size_t record_size);


void pio_store_record(file_descriptor* fd, void* record, size_t record_size, 
		      void* src);


void pio_read_record(file_descriptor* fd, void* record, size_t record_size, 
		     void* dst);

void pio_write_record(file_descriptor* fd, void* record, size_t record_size,
		  void* src);

void pio_copy_record(file_descriptor* src_fd, void* src_record, 
		     file_descriptor* dst_fd, void* dst_record, 
		     size_t record_size);

boolean pio_check_end_of_file(file_descriptor *fd); 

boolean pio_check_end_of_line(text_descriptor *td); 

integer pio_iostatus(file_descriptor *fd);

boolean pio_ioerror(file_descriptor *fd);

void pio_file_ignore_error(file_descriptor* fd);

void pio_close_file(file_descriptor* fd);

void pio_seek_file(file_descriptor* fd, void* record, size_t record_size, 
	       integer position);

void pio_rename_file(file_descriptor* fd, const char* new_name);

void pio_flush_file(file_descriptor* fd);

void pio_delete_file(file_descriptor* fd);
 
#ifdef __VMS
integer pio_get_file_version(file_descriptor* fd);
#endif


long pio_get_file_size(file_descriptor* fd, size_t record_size);

void pio_input_real(text_descriptor* td, double* val); 

void pio_input_integer(text_descriptor* td, int* val); 

void pio_input_unsigned(text_descriptor* td, unsigned* val); 

void pio_input_long(text_descriptor* td, long* val); 

void pio_input_ulong(text_descriptor* td, unsigned long* val); 

void pio_input_char(text_descriptor* td, char* val); 

int  pio_input_string(text_descriptor* td, char* buf, size_t len, int padding);

void pio_input_newline(text_descriptor* td);


void pio_output_real(text_descriptor* td, double val, const int* width, 
		 const int* prec); 

void pio_output_integer(text_descriptor* td, int val, 
			const int* width); 

void pio_output_unsigned(text_descriptor* td, unsigned val, 
			 const int* width); 

void pio_output_long(text_descriptor* td, long val, 
		     const int* width); 

void pio_output_ulong(text_descriptor* td, unsigned long val, 
		      const int* width); 

void pio_output_char(text_descriptor* td, char val, const int* width); 

void pio_output_boolean(text_descriptor* td, boolean val, 
			const int* width); 

void pio_output_string(text_descriptor* td, const char* buf, size_t len, 
		       const int* width);

void pio_output_newline(text_descriptor* td);

void pio_output_end_of_page(text_descriptor* td);

typedef struct { int dummy; } new_line_marker;
extern new_line_marker NL;

#ifdef __cplusplus

}

//
// Some compilers report error when operator-> returns non-stuctural type
// (for exmaple "char*"). When SPLIT_FILE_CLASS option is defined, "file" class
// is divided into two parts, one of which is used as common base for
// "file of XXX" and "text", and second contains operator-> for access file 
// record.
//
#ifdef SPLIT_FILE_CLASS
#define file file_template
#endif

template<class T>
class file { 
  public:
    file_descriptor desc;
    T               record;
    
#ifdef TURBO_PASCAL
    friend void assign(file& f, const char* file_name) {
	f.desc.f = NULL;
	f.desc.name = strdup(file_name);
    } 
    friend void BlockRead(file& f, void* buf, word size, word& read) { 
	read = fread(buf, 1, size, f.desc.f);
    }
    friend void BlockWrite(file& f, void const* buf, word size, word& written){
	written = fwrite(buf, 1, size, f.desc.f);
    }
#endif

    

    friend void open(file& f, const char* file_name, const char* history,     
		     integer& error, int buffer = 0)
    {
	pio_open_file(&f.desc, sizeof(T), file_name, history, &error);
    }

    friend void open(file& f, const char* file_name, const char* history)     
    {
	pio_open_file(&f.desc, sizeof(T), file_name, history, NULL);
    }


    friend void rewrite(file& f, const char* file_name, 
			const char* options, 
			integer& error_code) 
    { 
	pio_rewrite_file(&f.desc, sizeof(T), file_name, options, &error_code);
    }

    friend void rewrite(file& f, const char* file_name, const char* options)
    { 
	pio_rewrite_file(&f.desc, sizeof(T), file_name, options, NULL);
    }

    friend void rewrite(file& f) 
    { 
	pio_rewrite_file(&f.desc, sizeof(T), NULL, NULL, NULL);
    }

    friend void rewrite(file& f, const char* file_name) 
    { 
	pio_rewrite_file(&f.desc, sizeof(T), file_name, NULL, NULL);
    }

    friend void reset(file& f, const char* file_name, 
		      const char* options, integer& error_code) 
    { 
	pio_reset_file(&f.desc, sizeof(T), file_name, options, &error_code); 
    }

    friend void reset(file& f, const char* file_name, const char* options) 
    { 
	pio_reset_file(&f.desc, sizeof(T), file_name, options, NULL); 
    }

    friend void reset(file& f, const char* file_name) 
    { 
	pio_reset_file(&f.desc, sizeof(T), file_name, NULL, NULL); 
    }

    friend void reset(file& f) 
    { 
	pio_reset_file(&f.desc, sizeof(T), NULL, NULL, NULL); 
    }

    friend void get(file& f) 
    {
        pio_get_record(&f.desc, (void*)&f.record, sizeof(T)); 
    }

    friend void put(file& f) 
    {
        pio_put_record(&f.desc, (void*)&f.record, sizeof(T));
    }

    friend boolean eof(file& f) 
    {
        return pio_check_end_of_file(&f.desc);
    }

    friend integer iostatus(file& f) 
    {
        return pio_iostatus(&f.desc);
    }

    friend boolean ioerror(file& f) 
    {
        return pio_ioerror(&f.desc); 
    }

    friend void close(file& f) 
    {
        pio_close_file(&f.desc);
    }

    friend void seek(file& f, integer position) 
    {
        pio_seek_file(&f.desc, (void*)&f.record, sizeof(T), position);
    }

    friend void rename(file& f, const char* new_name)
    {
        pio_rename_file(&f.desc, new_name); 
    }

    friend void flush(file& f) 
    {
        pio_flush_file(&f.desc);
    }

    friend void Delete(file& f)
    { 
        pio_delete_file(&f.desc);
    }

    friend long filesize(file& f) 
    { 
	return pio_get_file_size(&f.desc, sizeof(T));
    }
 
    friend void noioerror(file& f) 
    {
        pio_file_ignore_error(&f.desc);
    }

    T& operator*() 
    {
	pio_access_record(&desc, (void*)&record, sizeof(T)); 
	return record; 
    }

#ifndef SPLIT_FILE_CLASS
    T* operator->() 
    {
	pio_access_record(&desc, (void*)&record, sizeof(T)); 
	return &record; 
    }
#endif

    friend void store(file& f, T const& record) 
    { 
	pio_store_record(&f.desc, (void*)&f.record, sizeof(T), (void*)&record);
    }

    file& operator >> (T& x) 
    { 
	pio_read_record(&desc, (void*)&record, sizeof(T), (void*)&x);
	return *this;
    }
    file& operator >> (file const& f) 
    { 
	pio_copy_record(&desc, (void*)&record, 
			(file_descriptor*)&f.desc, (void*)&f.record, 
			sizeof(T));
	return *this;
    }
    file& operator << (T const& x) 
    { 
	pio_write_record(&desc, (void*)&record, sizeof(T), (void*)&x);
	return *this;
    }

    friend boolean file_is_opened(file const& f) 
    { 
	return f.desc.f != NULL; 
    }

    file() { desc.f = NULL; desc.name = NULL; }
    ~file() { pio_close_file(&desc); }
};

class text;

extern "C" text input, output;

class text : public file<char> { 
  public:
    friend boolean eof()  
    { 
        return pio_check_end_of_file(&input.desc);
    }
    friend boolean eoln(text& t) 
    {
        return pio_check_end_of_line((text_descriptor*)&t);
    }
    friend boolean eoln() 
    {
        return pio_check_end_of_line((text_descriptor*)&input);
    }

    text& operator >> (float& x) 
    {
	double tmp;
	pio_input_real((text_descriptor*)this, &tmp);
	x = (float)tmp;
	return *this;
    } 

    text& operator >> (double& x) 
    {
	pio_input_real((text_descriptor*)this, &x);
	return *this;
    } 

    text& operator >> (int& x) 
    {
	pio_input_integer((text_descriptor*)this, &x);
	return *this;
    } 

    text& operator >> (unsigned& x) 
    {
	pio_input_unsigned((text_descriptor*)this, &x);
	return *this;
    } 

    text& operator >> (long& x) 
    {
	pio_input_long((text_descriptor*)this, &x);
	return *this;
    } 

    text& operator >> (unsigned long& x) 
    {
	pio_input_ulong((text_descriptor*)this, &x);
	return *this;
    } 

    text& operator >> (short& x) 
    {
	int tmp;
	pio_input_integer((text_descriptor*)this, &tmp);
	x = (short)tmp;
	return *this;
    } 

    text& operator >> (unsigned short& x) 
    {
	int tmp;
	pio_input_integer((text_descriptor*)this, &tmp);
	x = (unsigned short)tmp;
	return *this;
    } 

    text& operator >> (unsigned char& x) 
    {
	int tmp;
	pio_input_integer((text_descriptor*)this, &tmp);
	x = (unsigned char)tmp;
	return *this;
    } 

    text& operator >> (signed char& x) 
    {
	int tmp;
	pio_input_integer((text_descriptor*)this, &tmp);
	x = (signed char)tmp;
	return *this;
    } 

    text& operator >> (char& x) 
    { 
	pio_input_char((text_descriptor*)this, &x);
	return *this; 
    }

    text& operator >> (new_line_marker&) 
    { 
	pio_input_newline((text_descriptor*)this);
	return *this; 
    }

    text& operator << (double x) 
    {
	pio_output_real((text_descriptor*)this, x, NULL, NULL);
	return *this;
    } 

    text& operator << (long x) 
    {
	pio_output_long((text_descriptor*)this, x, NULL);
	return *this;
    } 

    text& operator << (unsigned long x) 
    {
	pio_output_ulong((text_descriptor*)this, x, NULL);
	return *this;
    } 

    text& operator << (int x) 
    {
	pio_output_integer((text_descriptor*)this, x, NULL);
	return *this;
    } 

    text& operator << (unsigned x) 
    {
	pio_output_unsigned((text_descriptor*)this, x, NULL);
	return *this;
    } 

    friend char* btos(boolean val) // convert boolean to ascii string
    {
	return (char*)(val ? " TRUE" : "FALSE"); 
    }

    text& operator << (char x) 
    {
	pio_output_char((text_descriptor*)this, x, NULL);
	return *this;
    } 

    text& operator << (unsigned char x) 
    {
	pio_output_char((text_descriptor*)this, x, NULL);
	return *this;
    } 

    text& operator << (const char* x) 
    {
	pio_output_string((text_descriptor*)this, x, strlen(x), NULL);
	return *this;
    } 

    text& operator << (new_line_marker&) 
    { 
	pio_output_newline((text_descriptor*)this);
	return *this; 
    }

    friend void page(text& t) 
    {
        pio_output_end_of_page((text_descriptor*)&t);
    }
    friend void page() 
    {
        pio_output_end_of_page((text_descriptor*)&output);
    }
};


#ifdef SPLIT_FILE_CLASS
#undef file
template<class T>
class file : public file_template<T> {
  public:
    T* operator->() 
    {
	pio_access_record(&desc, (void*)&record, sizeof(T)); 
	return &record; 
    }
};
#endif

#ifdef TURBO_PASCAL
typedef text untyped_file;
#endif

template<int size>
class format_string { 
  private:
    char*   buf; 
    int     width;
    
  public:
    friend text& operator << (text& t, format_string const& fs) { 
	pio_output_string((text_descriptor*)&t, fs.buf, size, &fs.width); 
	return t; 
    }
    format_string(const char* str_buf, int str_width) { 
        buf = (char*)str_buf;
	width = str_width;
    }
};

#ifdef TURBO_PASCAL
class format_varying_string { 
  private:
    char    buf[256]; 
    int     size;
    int     width;
    
  public:
    friend text& operator << (text& t, format_varying_string const& fs) { 
	pio_output_string((text_descriptor*)&t, fs.buf, fs.size, &fs.width); 
	return t; 
    }
    format_varying_string(const char* str_buf, int str_size, int str_width) { 
	memcpy(buf, str_buf, str_size);
	size = str_size;
	width = str_width;
    }
};
#endif

class format_real { 
  private:
    real    val;
    int     width;
    
  public:
    friend text& operator << (text &t, format_real const& fr) { 
	pio_output_real((text_descriptor*)&t, fr.val, &fr.width, NULL);
	return t;
    }
    format_real(real real_val, int real_width) { 
	val = real_val;
	width = real_width;
    }
};

inline format_real format(real val, int width) { 
    return format_real(val, width); 
}


class format_real_wp { 
  private:
    real    val;
    int     width;
    int     prec;
    
  public:
    friend text& operator << (text &t, format_real_wp const& fr) { 
	pio_output_real((text_descriptor*)&t, fr.val, &fr.width, &fr.prec);
	return t;
    }
    format_real_wp(real real_val, int real_width, int real_prec) { 
	val = real_val;
	prec = real_prec;
	width = real_width;
    }
};

inline format_real_wp format(real val, int width, int prec) { 
    return format_real_wp(val, width, prec); 
}

class format_integer { 
  private:
    int val;
    int width;
    
  public:
    friend text& operator << (text &t, format_integer const& fi) { 
	pio_output_integer((text_descriptor*)&t, fi.val, &fi.width);
	return t;
    }
    format_integer(int int_val, int int_width) { 
	val = int_val;
	width = int_width;
    }
};

inline format_integer format(int val, int width) { 
    return format_integer(val, width); 
}


class format_unsigned { 
  private:
    unsigned val;
    int     width;
    
  public:
    friend text& operator << (text &t, format_unsigned const& fi) { 
	pio_output_unsigned((text_descriptor*)&t, fi.val, &fi.width);
	return t;
    }
    format_unsigned(unsigned unsigned_val, int unsigned_width) { 
	val = unsigned_val;
	width = unsigned_width;
    }
};

inline format_unsigned format(unsigned val, int width) { 
    return format_unsigned(val, width); 
}


class format_long { 
  private:
    long val;
    int  width;
    
  public:
    friend text& operator << (text &t, format_long const& fi) { 
	pio_output_long((text_descriptor*)&t, fi.val, &fi.width);
	return t;
    }
    format_long(long long_val, int long_width) { 
	val = long_val;
	width = long_width;
    }
};

inline format_long format(long val, int width) { 
    return format_long(val, width); 
}


class format_ulong { 
  private:
    unsigned long val;
    int           width;
    
  public:
    friend text& operator << (text &t, format_ulong const& fi) { 
	pio_output_ulong((text_descriptor*)&t, fi.val, &fi.width);
	return t;
    }
    format_ulong(unsigned long ulong_val, int ulong_width) { 
	val = ulong_val;
	width = ulong_width;
    }
};

inline format_ulong format(unsigned long val, int width) { 
    return format_ulong(val, width); 
}



class format_lpsz { 
  private:
    const char* val;
    int         width;
    
  public:
    friend text& operator << (text &t, format_lpsz const& fs) { 
	pio_output_string((text_descriptor*)&t, fs.val, strlen(fs.val), 
			  &fs.width);
	return t;
    }
    format_lpsz(const char* lpsz_val, int lpsz_width) { 
	val = lpsz_val;
	width = lpsz_width;
    }
};

inline format_lpsz format(const char* val, int width) { 
    return format_lpsz(val, width); 
}


class format_char { 
  private:
    char    val;
    int     width;
    
  public:
    friend text& operator << (text &t, format_char const& fc) { 
	pio_output_char((text_descriptor*)&t, fc.val, &fc.width);
	return t;
    }
    format_char(char char_val, int char_width) { 
	val = char_val;
	width = char_width;
    }
};

inline format_char format(char val, int width) { 
    return format_char(val, width); 
}


#else 

#define file(type) struct {  \
  file_descriptor desc;      \
  type record;               \
}                   
 
typedef text_descriptor text;

extern text input, output;

#define VOID_FILE     {{0}}

#define rewrite(file_variable, file_name, options, error_code)  \
        pio_rewrite_file(&(file_variable).desc, \
			 sizeof((file_variable).record), \
			 file_name, options, error_code)

#define reset(file_variable, file_name, options, error_code) \
        pio_reset_file(&(file_variable).desc, \
		       sizeof((file_variable).record), \
		       file_name, options, error_code)

#define get(file_variable) \
        pio_get_record(&(file_variable).desc, (void*)&(file_variable).record, \
		       sizeof((file_variable).record))

#define put(file_variable) \
        pio_put_record(&(file_variable).desc, (void*)&(file_variable).record, \
		       sizeof((file_variable).record))

#define sread(file_variable, value)  \
        pio_read_record(&(file_variable).desc, (void*)&(file_variable).record,\
			sizeof((file_variable).record), (void*)&(value)) 

#define scopy(src_file, dst_file)  \
        pio_copy_record(&(src_file).desc, (void*)&(src_file).record,\
			&(dst_file).desc, (void*)&(dst_file).record,\
			sizeof((src_file).record))

#define swrite(file_variable, value) \
        pio_write_record(&(file_variable).desc,(void*)&(file_variable).record,\
			 sizeof((file_variable).record), (void*)&(value)) 

#define currec(file_variable) \
        (pio_access_record(&(file_variable).desc, \
			   (void*)&(file_variable).record, \
			   sizeof((file_variable).record)), \
	 &(file_variable).record)   

#define store(file_variable, value) \
        pio_store_record(&(file_variable).desc, \
			 (void*)&(file_variable).record, \
			 sizeof((file_variable).record), (void*)&(value)) 

#define eof(file_variable) \
        pio_check_end_of_file(&(file_variable).desc)

#define iostatus(file_variable) \
        pio_iostatus(&(file_variable).desc)

#define ioerror(file_variable) \
        pio_ioerror(&(file_variable).desc)


#define close(file_variable) \
        pio_close_file(&(file_variable).desc)

#define seek(file_variable, position) \
        pio_seek_file(&(file_variable).desc, (void*)&(file_variable).record, \
		      sizeof((file_variable).record), position)

#define rename(file_variable, new_name) \
        pio_rename_file(&(file_variable).desc, new_name)

#define flush(file_variable) \
        pio_flush_file(&(file_variable).desc)

#define Delete(file_variable) \
        pio_delete_file(&(file_variable).desc)

#define noioerror(file_variable) \
        pio_file_ignore_error(&(file_variable).desc)

#ifdef __VMS
#define get_file_version(file_variable) \
       pio_get_file_version(&(file_variable).desc)
#endif


#define file_is_opened(file_variable)  ((file_variable).desc.f != NULL)


#define page(text_variable) \
        pio_output_end_of_page(&text_variable)

#define eoln(text_variable) \
        pio_check_end_of_line(&text_variable)


void tread(text* text_file, char* format_string, ...);

void twrite(text* text_file, char* format_string, ...);

void cread(char* format_string, ...);

void cwrite(char* format_string, ...);

#endif

#ifdef TURBO_PASCAL 
extern "C" integer ioresult;
#define ioResult ioresult
#endif

/*
 * Codes returned by Sun Pascal open()
 */
enum open_file_errors { 
   file_successfully_opened = 0,
   file_not_specified       = 1,
   unable_to_open_file      = 2,
   invalid_history          = 3,
   file_already_exists      = 4
};


#endif


