#include "IteratorMDO.h"
#include "MDO.h"

void IteratorMDO::mergeStanga(int p) {
	while (p != -1) {
		stiva.push(p);
		p = dict.st[p];
	}
}

//O(n)
IteratorMDO::IteratorMDO(const MDO& d) : dict(d){
	/* de adaugat */
	curent = -1;
	valIdx = 0;
	mergeStanga(dict.radacina);
	if (!stiva.empty())
		curent = stiva.top();
}

//O(n)
void IteratorMDO::prim(){
	/* de adaugat */
	while (!stiva.empty()) stiva.pop();
	curent = -1;
	valIdx = 0;
	mergeStanga(dict.radacina);
	if (!stiva.empty())
		curent = stiva.top();
}

//theta(n)
void IteratorMDO::urmator(){
	/* de adaugat */
	if (!valid()) throw exception();

	valIdx++;
	if (valIdx < (int)dict.valori[curent].size()) {
		return;
	}

	valIdx = 0;
	stiva.pop();

	mergeStanga(dict.dr[curent]);

	if (!stiva.empty())
		curent = stiva.top();
	else
		curent = -1; 
}

//theta(1)
bool IteratorMDO::valid() const{
	/* de adaugat */
	return curent != -1;
}

//theta(1)
TElem IteratorMDO::element() const{
	/* de adaugat */
	if (!valid()) throw exception();
	return TElem(dict.chei[curent], dict.valori[curent][valIdx]);
}


