#include "IteratorColectie.h"
#include "Colectie.h"
#include <exception>


IteratorColectie::IteratorColectie(const Colectie& c): col(c) 
{
	/* de adaugat */
	//complexitate : theta(1)

	nodCurent = col.prim;
	aparitiaCurenta = 1;
}

void IteratorColectie::prim() 
{
	/* de adaugat */
	//complexitate : theta(1)

	nodCurent = col.prim;
	aparitiaCurenta = 1;
}


void IteratorColectie::urmator()
{
	/* de adaugat */
	//complexitate : theta(1)

	if (!valid()) {
		throw std::exception();
	}
	// Daca mai sunt aparitii de returnat din nodul curent, avansam contorul
	if (aparitiaCurenta < nodCurent->frecventa) {
		aparitiaCurenta++;
	}
	else {
		// Am epuizat aparitiile din nodul curent => trecem la urmatorul nod
		nodCurent = nodCurent->urmator;
		aparitiaCurenta = 1;
	}
}


bool IteratorColectie::valid() const 
{
	/* de adaugat */
	//complexitate : theta(1)

	return nodCurent != nullptr;
}



TElem IteratorColectie::element() const 
{
	/* de adaugat */
	//complexitate : theta(1)

	if (!valid()) {
		throw std::exception();
	}
	return nodCurent->element;
}
