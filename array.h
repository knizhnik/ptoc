#ifndef __ARRAY_H__
#define __ARRAY_H__


#ifdef __cplusplus

extern "C" char* lpsz(int low, int high, const char* ptr);

#define BETWEEN(down, value, up)  \
                (unsigned(value) - down <= unsigned(up - down))
#define noconst 

#ifndef TURBO_PASCAL

#ifdef _WIN32
#include "malloc.h"
#else
#ifndef __GNUC__ /* use builtin definition of alloca() */
#include "alloca.h"
#endif
#endif

template<class Type>
class conf_array { 
  public:
    const integer low, high; 

    conf_array(integer l, integer h, Type* ptr) 
      : low(l), high(h), buf(ptr) {} 

    conf_array(Type const* ptr); /* intialization with string literal */

    conf_array(Type elem); /* intialization with character literal */

    void copy(void* buf_copy) { 
	memcpy(buf_copy, buf, (high-low+1)*sizeof(Type));
	buf = (Type*)buf_copy;
    }

    Type& operator[](integer index) { 
        assert(BETWEEN(low, index, high));
	return buf[index-low]; 
    }

    integer size() const { return high - low + 1; }

    integer size_in_bytes() const { return (high-low+1)*sizeof(Type); }

    Type* body() { return buf; }
    
    void operator = (conf_array const& src) { 
	assert(low == src.low && high == src.high); 
	memcpy(buf, src.buf, sizeof(Type)*(high-low+1)); 
    }
    void assign(conf_array const& src) { 
	assert(low == src.low && high == src.high); 
	memcpy(buf, src.buf, sizeof(Type)*(high-low+1)); 
    }
    friend char* lpsz(conf_array const& a) { 
	return lpsz(a.low, a.high, (char*)a.buf); 
    }
  protected: 
    Type *buf;  
};

#define copy_conformant_array(a) a.copy(alloca(a.size_in_bytes()))

//#define TEMPLATE_SPEC
#define TEMPLATE_SPEC  template <>

TEMPLATE_SPEC inline conf_array<char>::conf_array(char const* str) 
: low(1), high(strlen(str)), buf((char*)str) {}

TEMPLATE_SPEC inline conf_array<char>::conf_array(char ch) 
: low(1), high(1), buf(&ch) {}

#endif /* not Turbo Pascal */

template<integer low_bound, integer high_bound, class Type>
class array {
  public:    
    Type buf[high_bound-low_bound+1];

    enum array_bounds { 
	low = low_bound, 
	high = high_bound 
    };
    integer size() const { return high_bound - low_bound + 1; }

    Type& operator[](int index) {
	assert(BETWEEN(low_bound, index, high_bound));
	return buf[index-low_bound];
    }
    Type operator[](int index) const {
	assert(BETWEEN(low_bound, index, high_bound));
	return buf[index-low_bound];
    }
 
    Type*       body() { return buf; }
    Type const* body() const { return buf; }

    Type& operator*() { return *buf; }

#ifndef TURBO_PASCAL
    operator conf_array<Type>() const { /* Convert to dynamic_array */
	return conf_array<Type>(low_bound, high_bound, (Type*)buf);
    }      
#endif

    int compare( const Type* ptr) const { 
	return memcmp(buf, ptr, sizeof(buf)); 
    }
    
    boolean operator >  (const array &arr) const { 
	return compare(arr.buf) > 0; 
    }
    boolean operator >= (const array &arr) const { 
	return compare(arr.buf) >= 0; 
    }
    boolean operator <  (const array &arr) const { 
	return compare(arr.buf) < 0; 
    }
    boolean operator <= (const array &arr) const { 
	return compare(arr.buf) <= 0; 
    }
    boolean operator == (const array &arr) const { 
	return compare(arr.buf) == 0; 
    }
    boolean operator != (const array &arr) const { 
	return compare(arr.buf) != 0; 
    }
    
    boolean operator >  (const Type* ptr) const { 
	return compare(ptr) > 0; 
    }
    boolean operator >= (const Type* ptr) const { 
	return compare(ptr) >= 0; 
    }
    boolean operator <  (const Type* ptr) const { 
	return compare(ptr) < 0; 
    }
    boolean operator <= (const Type* ptr) const { 
	return compare(ptr) <= 0; 
    }
    boolean operator == (const Type* ptr) const { 
	return compare(ptr) == 0; 
    }
    boolean operator != (const Type* ptr) const { 
	return compare(ptr) != 0; 
    }
    
    boolean operator >  (Type elem) const { 
	return compare(&elem) > 0; 
    }
    boolean operator >= (Type elem) const { 
	return compare(&elem) >= 0; 
    }
    boolean operator <  (Type elem) const { 
	return compare(&elem) < 0; 
    }
    boolean operator <= (Type elem) const { 
	return compare(&elem) <= 0; 
    }
    boolean operator == (Type elem) const { 
	return compare(&elem) == 0; 
    }
    boolean operator != (Type elem) const { 
	return compare(&elem) != 0; 
    }

    friend text& operator << (text& t, array a)
    { 
	pio_output_string((text_descriptor*)&t, (char*)a.buf, 
			  high_bound-low_bound+1, NULL); 
	return t; 
    } 

    friend text& operator >> (text& t, array& a)
    {
	pio_input_string((text_descriptor*)&t, (char*)a.buf, 
		     high_bound-low_bound+1, true); 
	return t; 
    } 

    friend format_string<high_bound-low_bound+1> format(array const& a, 
							int width)
    {
	return format_string<high_bound-low_bound+1>((char*)a.buf, width);
    }

#ifndef NO_ARRAY_ASSIGN_OPERATOR
    void operator = (const Type* ptr) { 
	if (sizeof(Type) == 1) { /* array of char */
	    size_t len = strlen((char*)ptr);
	    if (len > sizeof(buf)) {
		memcpy(buf, ptr, sizeof(buf));
	    } else {
		memcpy(buf, ptr, len);
		if (len < sizeof(buf)) { 
		    memset(buf+len, ' ', sizeof(buf) - len);
		}
	    }
	} else { 
	    memcpy(buf, ptr, sizeof(buf));
	}
    }
    void operator = (Type elem) { 
    	buf[0] = elem;
	if (sizeof(Type) == 1 && sizeof(buf) > 1) {
	    memset(buf+1, ' ', sizeof(buf) - 1);
	}
    }
#else   
    void assign(array const& a) { 
	memcpy(buf, a.buf, sizeof(buf));
    }
    void assign(const Type* ptr) { 
	if (sizeof(Type) == 1) { /* array of char */
	    size_t len = strlen((char*)ptr);
	    if (len > sizeof(buf)) {
		memcpy(buf, ptr, sizeof(buf));
	    } else {
		memcpy(buf, ptr, len);
		if (len < sizeof(buf)) { 
		    memset(buf + len, ' ', sizeof(buf) - len);
		}
	    }
	} else { 
	    memcpy(buf, ptr, sizeof(buf));
	}
    }
    void assign(Type elem) { 
    	buf[0] = elem;
	if (sizeof(Type) == 1 && sizeof(buf) > 1) {
	    memset(buf+1, ' ', sizeof(buf) - 1);
	}
    }
#endif   

    /* constructor of array from string */
    static array make(Type const* ptr) { 
	array a;
	if (sizeof(Type) == 1) { /* array of char */
	    size_t len = strlen((char*)ptr);
	    if (len > sizeof(a.buf)) { 			
		memcpy(a.buf, ptr, sizeof(a.buf));
	    } else { 
		memcpy(a.buf, ptr, len);
		if (len < sizeof(a.buf)) { 
		    memset(a.buf + len, ' ', sizeof(a.buf) - len);
		}
	    }
	} else { 
	    memcpy(a.buf, ptr, sizeof(a.buf));
	}
	return a;
    }
#if !defined(__GNUC__) || __GNUC_MINOR__+0 < 8
    static array make(Type elem1, ...) {
	va_list ap;
	int argno = 0;
	array a;
	va_start(ap, elem1);
	a.buf[0] = elem1;
	va_arg(ap, Type);
	while (argno < high_bound-low_bound) { 
	    a.buf[++argno] = va_arg(ap, Type);
	}
	va_end(ap);
	return a;
    }
#else
    /* Bug in GCC 2.8.1 */
    static array make(Type elem1) {
	array a;
	a.buf[0] = elem1;
	return a;
    }
    static array make(Type elem1, Type elem2) {
	array a;
	assert(high_bound-low_bound > 0);
	a.buf[0] = elem1;
	a.buf[1] = elem2;
	return a;
    }
    static array make(Type elem1, Type elem2, Type elem3) {
	array a;
	assert(high_bound-low_bound > 1);
	a.buf[0] = elem1;
	a.buf[1] = elem2;
	a.buf[2] = elem3;
	return a;
    }
    static array make(Type elem1, Type elem2, Type elem3, Type elem4) {
	array a;
	assert(high_bound-low_bound > 2);
	a.buf[0] = elem1;
	a.buf[1] = elem2;
	a.buf[2] = elem3;
	a.buf[3] = elem4;
	return a;
    }
#endif
    friend char* lpsz(array const& a) { 
	return lpsz(low_bound, high_bound, (char*)a.buf); 
    }
};

/* macro for construction array from string */
#define as_array(s)  array<1,sizeof(s)-1,char>::make(s)

#define as(type, str) array<type::low, type::high, char>::make(str)



#ifdef TURBO_PASCAL

inline int length(const char* str) { return strlen(str); }

#ifndef MAX_STRING_SIZE
#define MAX_STRING_SIZE 255
#endif

class varying_string_header { 
  protected: 
#if MAX_STRING_SIZE <= 255
    unsigned char len; 
#else
    unsigned int  len; 
#endif
  public:
    char* get_body() const { return (char*)(&len + 1); }

    friend integer length(const varying_string_header& str) { 
	return str.len; 
    }
    integer length() const { 
	return len;
    }
    friend void set_length(varying_string_header& str, integer new_length) { 
	str.len = new_length;
    }
    void set_length(integer new_length) { 
	len = new_length;
    }
    void to_array(char* dst_buf, size_t dst_buf_size) const { 
	size_t size = length(); 
	if (size > dst_buf_size) { 
	    size = dst_buf_size;
	}
	memcpy(dst_buf, get_body(), size);
	if (size < dst_buf_size) {
	    dst_buf[size] = '\0';
	}
    }

    char& operator*() { return *get_body(); }

    int compare(const char* str) const { 
	size_t right_len = strlen(str);
	size_t left_len = length();
	size_t min_len = left_len < right_len ? left_len : right_len;
	int diff = memcmp(get_body(), str, min_len);
	return diff == 0 ? left_len - right_len : diff; 
    }
    int compare(const varying_string_header& str) const { 
	size_t left_len = length();
	size_t right_len = str.length();
	size_t min_len = left_len < right_len ? left_len : right_len;
	int diff = memcmp(get_body(), str.get_body(), min_len);
	return diff == 0 ? left_len - right_len : diff; 
    }
    int compare(char ch) const { 
	unsigned len = length();
	return len == 0 ? -(unsigned char)ch : ch == *get_body()
	    ? len - 1 
	    : (unsigned char)ch - (unsigned char)*get_body();
    }

    boolean operator >  (const varying_string_header& str) const { 
	return compare(str) > 0; 
    }
    boolean operator >= (const varying_string_header& str) const { 
	return compare(str) >= 0; 
    }
    boolean operator < (const varying_string_header& str) const { 
	return compare(str) < 0; 
    }
    boolean operator <= (const varying_string_header& str) const { 
	return compare(str) <= 0; 
    }
    boolean operator == (const varying_string_header& str) const { 
	return compare(str) == 0; 
    }
    boolean operator != (const varying_string_header& str) const { 
	return compare(str) != 0; 
    }
    
    boolean operator >  (const char* ptr) const { 
	return compare(ptr) > 0; 
    }
    boolean operator >= (const char* ptr) const { 
	return compare(ptr) >= 0; 
    }
    boolean operator < (const char* ptr) const { 
	return compare(ptr) < 0; 
    }
    boolean operator <= (const char* ptr) const { 
	return compare(ptr) <= 0; 
    }
    boolean operator == (const char* ptr) const { 
	return compare(ptr) == 0; 
    }
    boolean operator != (const char* ptr) const { 
	return compare(ptr) != 0; 
    }
    
    boolean operator >  (char ch) const { 
	return compare(ch) > 0; 
    }
    boolean operator >= (char ch) const { 
	return compare(ch) >= 0; 
    }
    boolean operator < (char ch) const { 
	return compare(ch) < 0; 
    }
    boolean operator <= (char ch) const { 
	return compare(ch) <= 0; 
    }
    boolean operator == (char ch) const { 
	return compare(ch) == 0; 
    }
    boolean operator != (char ch) const { 
	return compare(ch) != 0; 
    }
    
    friend text& operator << (text& t, varying_string_header const& str)
    { 
	pio_output_string((text_descriptor*)&t, str.get_body(), 
			  str.length(), NULL); 
	return t; 
    } 

    friend format_varying_string format(varying_string_header const& str, 
					int width)
    {
	return format_varying_string(str.get_body(), str.length(), width);
    }
};


template<size_t max_size>
class varying_string : public varying_string_header { 
  public: 
    char body[max_size];
    typedef varying_string<MAX_STRING_SIZE> string; 

#define STRING_FETCH_OPERATOR(index_type, modifier) \
    char modifier& operator[](index_type index) modifier { \
	assert(size_t(index) <= max_size); \
	return body[index-1]; \
    }
    STRING_FETCH_OPERATOR(char, noconst);
    STRING_FETCH_OPERATOR(char, const);
    STRING_FETCH_OPERATOR(unsigned char, noconst);
    STRING_FETCH_OPERATOR(unsigned char, const);
    STRING_FETCH_OPERATOR(short, noconst);
    STRING_FETCH_OPERATOR(short, const);
    STRING_FETCH_OPERATOR(unsigned short, noconst);
    STRING_FETCH_OPERATOR(unsigned short, const);
    STRING_FETCH_OPERATOR(int, noconst);
    STRING_FETCH_OPERATOR(int, const);
    STRING_FETCH_OPERATOR(unsigned, noconst);
    STRING_FETCH_OPERATOR(unsigned, const);
#undef STRING_FETCH_OPERTATOR 

    operator char const*() const { 
	size_t len = length();
	if (len < max_size) { 
	    *((char*)body + len) = '\0';
	    return body;
	} else { 
	    return lpsz(1, len, body);
	}
    }

    friend text& operator >> (text& t, varying_string& str)
    {
	str.set_length(pio_input_string((text_descriptor*)&t, str.get_body(), 
					max_size, false));
	return t; 
    } 

    void operator = (const char* str) { 
	size_t len = strlen(str);
	if (len > max_size) len = max_size;
	memcpy(body, str, len);
	set_length(len);
    }
    void operator = (char elem) { 
	body[0] = elem;
	set_length(1);
    }
    void operator = (const varying_string_header& str) { 
	size_t len = str.length();
	if (len > max_size) len = max_size;
	memcpy(body, str.get_body(), len);
	set_length(len);
    }

    void operator = (const varying_string& str) { 
	size_t len = str.length();
	if (len > max_size) len = max_size;
	memcpy(body, str.get_body(), len);
	set_length(len);
    }

    string operator + (const varying_string_header& str) const;

    string operator + (const char* str) const;

    string operator + (char ch) const;

    string operator + (unsigned char ch) const; 

    string operator + (new_line_marker&) const; 

    varying_string(const varying_string_header& str) { 
	size_t len = str.length();
	if (len > max_size) len = max_size;
	memcpy(body, str.get_body(), len);
	set_length(len);
    }	
    varying_string(const char* str) {
	size_t len = strlen(str);
	if (len > max_size) len = max_size;
	memcpy(body, str, len);
	set_length(len);
    }
    varying_string(char ch) {
	if (max_size >= 1) { 
	    set_length(1);
	    body[0] = ch;
	}
    }
    varying_string() { 	
	set_length(0);
    }
};

typedef varying_string<MAX_STRING_SIZE> string;


template<size_t max_size>
inline string varying_string<max_size>::operator + 
(const varying_string_header& str) const 
{ 
    string result;
    size_t left_len = length();    
    size_t right_len = str.length();
    memcpy(&result.body, body, left_len);
    size_t append_len = MAX_STRING_SIZE - left_len < right_len 
	? MAX_STRING_SIZE - left_len : right_len;
    memcpy(&result.body[left_len], str.get_body(), append_len);
    result.set_length(left_len + append_len);
    return result;
}

template<size_t max_size>
inline string varying_string<max_size>::operator + (const char* str) const 
{ 
    string result;
    size_t left_len = length();    
    size_t right_len = strlen(str);
    memcpy(result.body, body, left_len);
    size_t append_len = MAX_STRING_SIZE - left_len < right_len 
	? MAX_STRING_SIZE - left_len : right_len;
    memcpy(&result.body[left_len], str, append_len);
    result.set_length(left_len + append_len);
    return result;
}

template<size_t max_size>
inline string varying_string<max_size>::operator + (char ch) const 
{ 
    string result;
    size_t len = length();    
    memcpy(result.body, body, len);
    if (len < MAX_STRING_SIZE) { 
	result.body[len] = ch;
	result.set_length(len+1);
    } else { 
	result.set_length(len);
    }
    return result;
}

template<size_t max_size>
inline string varying_string<max_size>::operator + (unsigned char ch) const 
{ 
    string result;
    size_t len = length();    
    memcpy(result.body, body, len);
    if (len < MAX_STRING_SIZE) { 
	result.body[len] = ch;
	result.set_length(len+1);
    } else { 
	result.set_length(len);
    }
    return result;
}

template<size_t max_size>
inline string varying_string<max_size>::operator + (new_line_marker&) const 
{ 
    string result;
    size_t len = length();    
    memcpy(result.body, body, len);
    if (len < MAX_STRING_SIZE) { 
	result.body[len] = '\n';
	result.set_length(len+1);
    } else { 
	result.set_length(len);
    }
    return result;
}


template<size_t max_size>
inline void str(int val, varying_string<max_size>& s) { 
    s.set_length(sprintf(s.body, "%d", val));
}

template<size_t max_size>
inline void str(long val, varying_string<max_size>& s) { 
    s.set_length(sprintf(s.body, "%ld", val));
}

template<size_t max_size>
inline void str(unsigned val, varying_string<max_size>& s) { 
    s.set_length(sprintf(s.body, "%u", val));
}

template<size_t max_size>
inline void str(unsigned long val, varying_string<max_size>& s) { 
    s.set_length(sprintf(s.body, "%lu", val));
}

template<size_t max_size>
inline void str(int val, int width, varying_string<max_size>& s) { 
    s.set_length(sprintf(s.body, "%*d", width, val));
}

template<size_t max_size>
inline void str(unsigned val, int width, varying_string<max_size>& s) { 
    s.set_length(sprintf(s.body, "%*u", width, val));
}

template<size_t max_size>
inline void str(long val, int width, varying_string<max_size>& s) { 
    s.set_length(sprintf(s.body, "%*ld", width, val));
}

template<size_t max_size>
inline void str(unsigned long val, int width, varying_string<max_size>& s) { 
    s.set_length(sprintf(s.body, "%*lu", width, val));
}

template<size_t max_size>
inline void str(double val, varying_string<max_size>& s) { 
    s.set_length(sprintf(s.body, "% G", val));
}

template<size_t max_size>
inline void str(double val, int width, varying_string<max_size>& s) { 
    s.set_length(sprintf(s.body, "%*E", width, val));
}

template<size_t max_size>
inline void str(double val, int width, int prec, varying_string<max_size>& s) {
    s.set_length(sprintf(s.body, "%*.*f", width, prec, val));
}

inline string copy(varying_string_header const& str, integer p, integer n) 
{ 
    string result;
    size_t len = str.length();
    result.set_length(0);
    if (size_t(p-1) < len) { 
	size_t count = size_t(p-1+n) <= len ? size_t(n) : len - p + 1;
	memcpy(result.body, str.get_body() + p - 1, count);
	result.set_length(count);
    }
    return result;
}

inline string copy(char const* str, integer p, integer n) 
{ 
    string result;
    size_t len = strlen(str);
    result.set_length(len);
    if (size_t(p-1) < len) { 
	size_t count = size_t(p+n) <= len ? size_t(n) : len - p + 1;
	memcpy(result.body, str + p - 1, count);
	result.set_length(count);
    }
    return result;
}

template<size_t max_size>
inline void insert(string const&             ins, 
		   varying_string<max_size>& str, 
		   int                       pos)
{ 
    size_t len = str.length();
    size_t inslen = ins.length();
    assert(pos > 0 && pos <= len+1 && size_t(inslen+len) < sizeof str);
    char* dst = str.get_body();
    memmove(dst+pos-1+inslen, dst+pos-1, len - pos + 1);
    memcpy(dst+pos-1, ins.body, inslen);
    str.set_length(len + inslen);
}

inline integer pos(string const& q, string const& z) 
{ 
    int   q_len = q.length();
    int   z_len = z.length();
    char* q_ptr = q.get_body();
    char* z_ptr = z.get_body();
    int pos = 0;
    while (z_len - pos >= q_len) { 
	int i;
	for (i = 0; i < q_len && z_ptr[pos+i] == q_ptr[i]; i++);
	if (i == q_len) { 
	    return pos+1;
	}
	pos += 1;
    } 
    return 0;
}

template<size_t max_size>
inline void Delete(varying_string<max_size>& s, integer index, integer count)
{
    integer len = s.length();
    assert(index > 0 && count >= 0);
    if (index + count > len) { 
	count = len - index + 1;
    }
    char* str = s.get_body();
    memcpy(str+index-1, str+index-1+count, len-index-count+1);
    s.set_length(len - count);
}

inline void val(string const& str, integer& val, integer& c)
{
    int x, n;
    if (sscanf(str.body, "%d%n", &x, &n) == 1) { 
	val = x;
	c = (n == str.length()) ? 0 : n+1;
    } else { 
	c = 1;
    }
}

inline void val(string const& str, real& val, integer& c)
{
    double x;
    int    n;
    if (sscanf(str.body, "%lf%n", &x, &n) == 1) { 
	val = (real)x;
	c = (n == str.length()) ? 0 : n+1;
    } else { 
	c = 1;
    }
}

#else /* ANSI PASCAL */

template<class Type>
class conf_matrix {
  public:     
    const integer low1, high1, low2, high2;

    conf_matrix(integer l1, integer h1, integer l2, integer h2, Type* ptr)
      : low1(l1), high1(h1), low2(l2), high2(h2), buf(ptr) {}

    void copy(void* buf_copy) { 
	memcpy(buf_copy, buf, (high1-low1+1) * (high2-low2+1) * sizeof(Type));
	buf = (Type*)buf_copy;
    }

    conf_array<Type> operator[](integer index) {
        assert(BETWEEN(low1, index, high1)); 
        return conf_array<Type>(low2, high2, 
				buf+(index-low1)*(high2-low2+1)); 
    }

    void operator =(conf_matrix const& src) {
        assert(low1 == src.low1 && high1 == src.high1 &&
               low2 == src.low2 && high2 == src.high2);
	memcpy(buf, src.buf, size_in_bytes());
    }
    void assign(conf_matrix const& src) {
        assert(low1 == src.low1 && high1 == src.high1 &&
               low2 == src.low2 && high2 == src.high2);
	memcpy(buf, src.buf, size_in_bytes());
    }
    
    integer size()  const { 
	return (high1 - low1 + 1) * (high2 - low2 + 1); 
    }
    integer size_in_bytes() const { 
	return (high1 - low1 + 1) * (high2 - low2 + 1) * sizeof(Type); 
    }

    Type* body() { return buf; }
  protected:
    Type* buf;
}; 


#endif /* ANSI Pascal */
    
/*
 * Class matrix describes buf with fixed bounds.
 */

template<integer low_1,integer high_1,integer low_2,integer high_2,class Type>
class matrix { 
  public:
    array<low_2,high_2,Type> buf[high_1-low_1+1];

    array<low_2,high_2,Type>& operator[](integer index) {
	assert(BETWEEN(low_1, index, high_1)); 
	return buf[index-low_1]; 
    }

    array<low_2,high_2,Type> const& operator[](integer index) const {
	assert(BETWEEN(low_1, index, high_1)); 
	return buf[index-low_1]; 
    }

#ifndef TURBO_PASCAL
    operator conf_matrix<Type>() const {
        return conf_matrix<Type>(low_1, high_1, low_2, high_2, (Type*)buf);
    }
#endif

    enum matrix_bounds { 
	low1  = low_1, 
	high1 = high_1, 
	low2  = low_2, 
	high2 = high_2 
    };

    integer size()  const { return (high_1-low_1+1)*(high_2-low_2+1); }

    Type* body() { return (Type*)buf; }
    Type const* body() const { return (Type const*)buf; }

#ifndef NO_ARRAY_ASSIGN_OPERATOR
    void operator = (matrix const& m) {
	memcpy(buf, m.buf, sizeof(buf));
    }
#else	
    void assign(matrix const& m) { 
	memcpy(buf, m.buf, sizeof(buf));
    }
#endif
}; 

#else /* language C */

extern char* lpsz(int low, int high, const char* ptr);

/*
 * macro for passing string as a function parameter together with bounds
 */
#define array(s)  1, sizeof(s)-1, (s)  

#define reccmp(a,b) memcmp(&a, &b, sizeof(a))
#define arrcmp(a,b) memcmp(a, b, sizeof(a))
#define arrcpy(a,b) memcpy(a, b, sizeof(a))

#endif


#endif 
