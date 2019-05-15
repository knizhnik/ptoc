#include "ptoc.h"

void pascal_set_construct(SetArrayElemType* set_array, size_t set_card, 
			  int param1, va_list params)
{
    SetElemType elem = param1;
    boolean interval = false;
    int param = param1;
    size_t i;
    
    for (i = 0; i < set_card; i++) { 
	set_array[i] = 0;
    }

    while (param != eos) {
	if (interval) {
	    size_t low  = elem;
	    size_t high = (SetElemType)param;
	    size_t lowindex  = low / BITS_PER_WORD;
	    size_t highindex = high / BITS_PER_WORD;
    
	    assert(highindex < set_card);

	    if (lowindex == highindex) {
		set_array[lowindex] |= 
		    ((((SetArrayElemType)1 << (high-low)) << 1) - 1) 
					   << (low % BITS_PER_WORD); 
	    } else {
		set_array[lowindex] |=  ALL_BITS_SET << (low % BITS_PER_WORD);
		
		for(i = lowindex+1; i < highindex; i++)
		    set_array[i] = ALL_BITS_SET;
		
		set_array[highindex] |= 
		    (((SetArrayElemType)1 << (high % BITS_PER_WORD)) << 1) - 1;
	    }    
	    interval = false;
	}  else if (param == INTERVAL_MARKER) { 
	    interval = true;
	} else { /* single value */
	    size_t index;
	    elem = param; 
	    index = (size_t)elem / BITS_PER_WORD;
	    assert(index < set_card);
	    set_array[index] |= 
		(SetArrayElemType)1 << ((size_t)elem % BITS_PER_WORD); 
	}
	param = va_arg(params, int);         
    }
}

set join(set a, set b) { 
    set c;
    size_t i;

    for(i = 0; i < SET_LENGTH; i++)
        c.setarray[i] = a.setarray[i] | b.setarray[i];
    return c;
}

set difference(set a, set b) {
    set c;
    size_t i;

    for (i = 0; i < SET_LENGTH; i++)
        c.setarray[i] = a.setarray[i] & ~b.setarray[i];
    return c;      
}

set intersect(set a, set b) { 
    set c;
    size_t i;

    for (i = 0; i < SET_LENGTH; i++)
        c.setarray[i] = a.setarray[i] & b.setarray[i];
    return c;
}

boolean equivalent(set a, set b) { 
    size_t i;

    for (i = 0; i < SET_LENGTH; i++)
         if (a.setarray[i] != b.setarray[i]) return false;
    return true;
}

boolean subset(set a, set b) { 
    size_t i;

    for (i = 0; i < SET_LENGTH; i++)
         if (a.setarray[i] & ~b.setarray[i]) return false;
    return true;
}

boolean inset(SetElemType elem, set s) { 
    return (s.setarray[(size_t)elem / BITS_PER_WORD] & 
	    ((SetArrayElemType)1 << ((size_t)elem % BITS_PER_WORD))) != 0;
}

set setof(int param1,...) {  
    set s = {{0}};
    va_list ap;
    va_start(ap, param1);
    pascal_set_construct(s.setarray, items(s.setarray), param1, ap);
    va_end(ap);
    return s;
}

