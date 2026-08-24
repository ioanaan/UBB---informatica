#include "IteratorMDO.h"
#include "MDO.h"
#include <iostream>
#include <vector>

#include <exception>
using namespace std;

//complexitate: theta(n)
MDO::MDO(Relatie r) {
	/* de adaugat */
	rel = r;
	radacina = -1;
	nrPerechi = 0;

	cp = 10;

	chei = new TCheie[cp];
	valori = new vector<TValoare>[cp];
	st = new int[cp];
	dr = new int[cp];

	for (int i = 0; i < cp - 1; i++) {
		st[i] = i + 1;
	}
	st[cp - 1] = -1;
	primLiber = 0;
}

void MDO::redimensioneaza() {
	int nouCp = cp * 2;

	TCheie* cheiNoi = new TCheie[nouCp];
	vector<TValoare>* valoriNoi = new vector<TValoare>[nouCp];
	int* stNoi = new int[nouCp];
	int* drNoi = new int[nouCp];

	for (int i = 0; i < cp; i++) {
		cheiNoi[i] = chei[i];
		valoriNoi[i] = valori[i];
		stNoi[i] = st[i];
		drNoi[i] = dr[i];
	}

	for (int i = cp; i < nouCp - 1; i++) {
		stNoi[i] = i + 1;
	}
	stNoi[nouCp - 1] = -1;

	primLiber = cp;

	delete[] chei;
	delete[] valori;
	delete[] st;
	delete[] dr;

	chei = cheiNoi;
	valori = valoriNoi;
	st = stNoi;
	dr = drNoi;
	cp = nouCp;
}

//complexitate: O(n)
int MDO::aloca() {

	if (primLiber == -1) {
		redimensioneaza();
	}

	int i = primLiber;
	primLiber = st[primLiber];
	return i;
}

//complexitate: O(n)
void MDO::dealoca(int i) {
	valori[i].clear();
	st[i] = primLiber;
	primLiber = i;
}

// favorabil: theta(1) 
// defavorabil: theta(n)
// mediu: O(log n)
int MDO::adaugaRec(int p, TCheie c, TValoare v) {
	if (p == -1) {
		int nou = aloca();
		chei[nou] = c;
		valori[nou].clear();
		valori[nou].push_back(v);
		st[nou] = -1;
		dr[nou] = -1;
		nrPerechi++;
		return nou;
	}

	if (rel(c, chei[p]) && rel(chei[p], c)) {
		valori[p].push_back(v);
		nrPerechi++;
		return p;
	}

	if (rel(c, chei[p])) {
		st[p] = adaugaRec(st[p], c, v);
	}
	else {
		dr[p] = adaugaRec(dr[p], c, v);
	}
	return p;
}

void MDO::adauga(TCheie c, TValoare v) {
	/* de adaugat */
	radacina = adaugaRec(radacina, c, v);
}

// favorabil: theta(1)
// defavorabil: theta(n)
// mediu: O(log n)
vector<TValoare> MDO::cauta(TCheie c) const {
	/* de adaugat */
	int p = radacina;
	while (p != -1) {
		if (rel(c, chei[p]) && rel(chei[p], c))
			return valori[p];
		if (rel(c, chei[p]))
			p = st[p];
		else
			p = dr[p];
	}
	return vector<TValoare>();
}

// favorabil: theta(1)
// defavorabil: theta(n)
// mediu: O(log n)
bool MDO::sterge(TCheie c, TValoare v) {
	/* de adaugat */
	int p = radacina;
	while (p != -1) {
		if (rel(c, chei[p]) && rel(chei[p], c)) break;
		if (rel(c, chei[p])) p = st[p];
		else p = dr[p];
	}

	if (p == -1) return false; 

	for (int i = 0; i < (int)valori[p].size(); i++) {
		if (valori[p][i] == v) {
			valori[p].erase(valori[p].begin() + i);
			nrPerechi--;

			if (valori[p].empty())
				radacina = stergeNod(radacina, c);

			return true;
		}
	}
	return false;
}

//complexitate: O(n)
int MDO::dim() const {
	/* de adaugat */
	return nrPerechi;
}

//complexitate: O(n)
bool MDO::vid() const {
	/* de adaugat */
	return nrPerechi == 0;
}

//complexitate: O(n)
IteratorMDO MDO::iterator() const {
	return IteratorMDO(*this);
}

//complexitate: O(n)
MDO::~MDO() {
	/* de adaugat */
	delete[] chei;
	delete[] valori;
	delete[] st;
	delete[] dr;

}

//complexitate: O(n)
int MDO::minim(int p) const {
	while (st[p] != -1)
		p = st[p];
	return p;
}

//complexitate: O(n)
int MDO::stergeNod(int p, TCheie c) {
	if (p == -1) return -1;

	bool egal = rel(c, chei[p]) && rel(chei[p], c);
	bool inainte = rel(c, chei[p]) && !rel(chei[p], c);

	if (inainte) {
		st[p] = stergeNod(st[p], c);
		return p;
	}
	if (!egal) {
		dr[p] = stergeNod(dr[p], c);
		return p;
	}

	if (st[p] == -1 && dr[p] == -1) {
		dealoca(p);
		return -1;
	}
	if (st[p] == -1) {
		int temp = dr[p];
		dealoca(p);
		return temp;
	}
	if (dr[p] == -1) {
		int temp = st[p];
		dealoca(p);
		return temp;
	}

	int minIdx = minim(dr[p]);
	TCheie minKey = chei[minIdx];
	chei[p] = minKey;
	valori[p] = valori[minIdx];
	dr[p] = stergeNod(dr[p], minKey);
	return p;
}