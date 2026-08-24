#pragma once
#include <stack>
#include "MDO.h"


class IteratorMDO{
	friend class MDO;
private:

	//constructorul primeste o referinta catre Container
	//iteratorul va referi primul element din container
	IteratorMDO(const MDO& dictionar);

	//contine o referinta catre containerul pe care il itereaza
	const MDO& dict;

	/* aici e reprezentarea  specifica a iteratorului */
	stack<int> stiva;  // indecsi noduri ABC
	int curent;        // nodul curent (-1 = invalid)
	int valIdx;        // indexul valorii curente in valori[curent]

	// Impinge p si toti descendentii sai stangi in stiva
	void mergeStanga(int p);


public:

		//reseteaza pozitia iteratorului la inceputul containerului
		void prim();

		//muta iteratorul in container
		// arunca exceptie daca iteratorul nu e valid
		void urmator();

		//verifica daca iteratorul e valid (indica un element al containerului)
		bool valid() const;

		//returneaza valoarea elementului din container referit de iterator
		//arunca exceptie daca iteratorul nu e valid
		TElem element() const;
};

