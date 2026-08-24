#include "oferta.h"
#include <assert.h>
#include "utilitare.h"
#include "teste.h"

void test_comparatori()
{
	Oferta o1 = initializeaza(1, "mare", "Grecia", "30.07.2026", 3800);
	Oferta o2 = initializeaza(2, "munte", "Brasov", "10.10.2026", 2600);

	assert(cmp_pret_crescator(o1, o2) == 1);
	assert(cmp_pret_descrescator(o1, o2) == 0);

	assert(cmp_dest_crescator(o1, o2) == 1);
	assert(cmp_dest_descrescator(o1, o2) == 0);

	distruge_oferta(&o1); 
	distruge_oferta(&o2);
}

void ruleaza_teste_utilitare()
{
	test_comparatori();
}