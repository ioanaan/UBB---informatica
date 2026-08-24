#include "oferta.h"
#include <string.h>

int cmp_pret_crescator(Oferta o1, Oferta o2)
{
    return get_pret(o1) > get_pret(o2);
}

int cmp_pret_descrescator(Oferta o1, Oferta o2) 
{
    return get_pret(o1) < get_pret(o2); 
}

int cmp_dest_crescator(Oferta o1, Oferta o2) 
{
    return strcmp(get_destinatie(o1), get_destinatie(o2)) > 0;
}

int cmp_dest_descrescator(Oferta o1, Oferta o2)
{
    return strcmp(get_destinatie(o1), get_destinatie(o2)) < 0;
}