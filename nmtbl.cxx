#include "token.h"

nm_entry* nm_entry::nm_table[nm_entry::h_t_size];

//----------------------------------------------------------------//

inline unsigned nm_entry::hash(const char* name)
{
    unsigned h = 0;
    unsigned c;

    while ((c = (unsigned)*name++) != 0) {
        h = (h<<1) + c;
    }

    return h % nm_entry::h_t_size;
}

nm_entry* nm_entry::find(const char* name)
{
    unsigned h;
    nm_entry* ne;
    
    h = hash(name);
    for (ne = nm_table[h]; ne != NULL; ne = ne->next)
    {
        if (strcmp(name, ne->text) == 0)
	    break;
    }

    return ne;
}

nm_entry* nm_entry::add(const char* name, int v_tag)
{
    unsigned  h;
    nm_entry* ne;

    ne = find(name);
    if (ne != NULL)
        return ne;

    h = hash(name);
    ne = new (strlen(name)) nm_entry;
    ne->next = nm_table[h];
    nm_table[h] = ne;
    ne->tag = v_tag;
    ne->flags = 0;
    strcpy(ne->text, name);
    return ne;
}
