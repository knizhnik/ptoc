#ifndef __SET_H__
#define __SET_H__

#define MAX_SET_CARD  256

#define eos              (MAX_SET_CARD)   /* end of set marker */
#define INTERVAL_MARKER  (MAX_SET_CARD+1) /* interval marker */

#define range(a,b) (a), INTERVAL_MARKER, (b)

typedef unsigned char SetElemType;
typedef integer       SetArrayElemType;
 
#define BITS_PER_WORD (sizeof(SetArrayElemType)*8)
#define ALL_BITS_SET  ((SetArrayElemType)-1)

#ifdef __cplusplus

extern "C" void pascal_set_construct(SetArrayElemType* set_array, 
				     size_t set_card, 
				     int param1, 
				     va_list params);

template<int n>
class set_template {
  public:
    SetArrayElemType setarray[(n + BITS_PER_WORD - 1) / BITS_PER_WORD];

    static set_template of(int param1, ...) {  
	set_template s;
	va_list ap;
	va_start(ap, param1);
	pascal_set_construct(s.setarray, items(s.setarray), param1, ap);
	va_end(ap);
	return s;
    }
    set_template operator +(set_template const& s) const { 
	set_template result;
	for(size_t i = 0; i < items(setarray); i++) { 
	    result.setarray[i] = setarray[i] | s.setarray[i];
	}
	return result;
    }
    set_template operator *(set_template const& s) const { 
	set_template result;
	for(size_t i = 0; i < items(setarray); i++) { 
	    result.setarray[i] = setarray[i] & s.setarray[i];
	}
	return result;
    }
    set_template operator -(set_template const& s) const { 
	set_template result;
	for(size_t i = 0; i < items(setarray); i++) { 
	    result.setarray[i] = setarray[i] & ~s.setarray[i];
	}
	return result;
    }

    boolean operator <=(set_template const& s) const { 
	for(size_t i = 0; i < items(setarray); i++) { 
	    if (setarray[i] & ~s.setarray[i]) return false;
	}
	return true;
    }
    boolean operator >=(set_template const& s) const { 
	for(size_t i = 0; i < items(setarray); i++) { 
	    if (s.setarray[i] & ~setarray[i]) return false;
	}
	return true;
    }
    boolean operator ==(set_template const& s) const { 
	for(size_t i = 0; i < items(setarray); i++) { 
	    if (s.setarray[i] != setarray[i]) return false;
	}
	return true;
    }
    boolean operator !=(set_template const& s) const { 
	for(size_t i = 0; i < items(setarray); i++) { 
	    if (s.setarray[i] != setarray[i]) return true;
	}
	return false;
    }
    boolean has(SetElemType elem) const { 
	return (setarray[(unsigned)elem / BITS_PER_WORD] & 
	       (SetArrayElemType(1) << ((unsigned)elem % BITS_PER_WORD))) != 0;
    } 
};

typedef set_template<MAX_SET_CARD> set;

#define set_of_enum(e) set_template<last_##e>

#else /* language C */

#define SET_LENGTH (MAX_SET_CARD/BITS_PER_WORD)

typedef struct { 
    SetArrayElemType setarray[SET_LENGTH];
} set;

boolean subset(set a, set b);    /* if <a> is subset of <b> */
boolean inset(SetElemType elem, set s);
boolean equivalent(set a, set b); 
set     setof(int elem1, ...);
set     join(set a, set b);
set     difference(set a, set b);
set     intersect(set a, set b);
 
typedef unsigned int   set32;
typedef unsigned short set16;

#define ELEM(e)         (1L << (e))
#define INSET(e,s)      ((ELEM(e) & (s)) != 0)
#define DIFFERENCE(a,b) ((a) & ~(b))
#define	JOIN(a,b)       ((a) | (b))
#define INTERSECT(a,b)  ((a) & (b))
#define SUBSET(a,b)     (((a) & ~(b)) == 0)
#define EQUIVALENT(a,b) ((a) == (b))

#define RANGE(a,b)      (ELEM((a)+1) - ELEM(b))


#endif /* language C */

/*
 * Macros for case ranges
 */
#define RANGE_2(a,b)  a: case b
#define RANGE_3(a,b)  RANGE_2(a,a+1): case b
#define RANGE_4(a,b)  RANGE_3(a,a+2): case b
#define RANGE_5(a,b)  RANGE_4(a,a+3): case b
#define RANGE_6(a,b)  RANGE_5(a,a+4): case b
#define RANGE_7(a,b)  RANGE_6(a,a+5): case b
#define RANGE_8(a,b)  RANGE_7(a,a+6): case b
#define RANGE_9(a,b)  RANGE_8(a,a+7): case b
#define RANGE_10(a,b) RANGE_9(a,a+8): case b
#define RANGE_11(a,b) RANGE_10(a,a+9): case b
#define RANGE_12(a,b) RANGE_11(a,a+10): case b
#define RANGE_13(a,b) RANGE_12(a,a+11): case b
#define RANGE_14(a,b) RANGE_13(a,a+12): case b
#define RANGE_15(a,b) RANGE_14(a,a+13): case b
#define RANGE_16(a,b) RANGE_15(a,a+14): case b
#define RANGE_26(a,b) RANGE_16(a,a+15): case RANGE_10(a+16,b)
#define RANGE_32(a,b) RANGE_16(a,a+15): case RANGE_16(a+16,b)


#endif 
