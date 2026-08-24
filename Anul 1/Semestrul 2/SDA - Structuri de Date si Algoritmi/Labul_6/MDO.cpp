#include "IteratorMDO.h"
#include "MDO.h"
#include <exception>
using namespace std;

int MDO::hash(TCheie c) const {
    return ((c % CP) + CP) % CP;
}

MDO::MDO(Relatie r) {
    rel = r;
    nrPerechi = 0;
    for (int i = 0; i < CP; i++)
        stari[i] = VIDA;
}

// favorabil: theta(1)
// mediu:O(1)
// defavorabil: theta(n) 
void MDO::adauga(TCheie c, TValoare v) {
    int pos = hash(c);
    int primStearsa = -1;

    for (int k = 0; k < CP; k++) {
        int p = (pos + k * k) % CP;

        if (stari[p] == VIDA) {
            int loc = (primStearsa != -1) ? primStearsa : p;
            elems[loc] = TElem(c, v);
            stari[loc] = OCUPATA;
            nrPerechi++;
            return;
        }

        if (stari[p] == STEARSA && primStearsa == -1)
            primStearsa = p;
    }

    if (primStearsa != -1) {
        elems[primStearsa] = TElem(c, v);
        stari[primStearsa] = OCUPATA;
        nrPerechi++;
    }
}

// favorabil: theta(1) 
// mediu: O(n)
// defavorabil: theta(n)
vector<TValoare> MDO::cauta(TCheie c) const {
    vector<TValoare> rez;
    int pos = hash(c);

    for (int k = 0; k < CP; k++) {
        int p = (pos + k * k) % CP;

        if (stari[p] == VIDA) break;

        if (stari[p] == OCUPATA && elems[p].first == c)
            rez.push_back(elems[p].second);
    }
    return rez;
}

// favorabil: theta(1)
// mediu: O(1)
// defavorabil: theta(CP)
bool MDO::sterge(TCheie c, TValoare v) {
    int pos = hash(c);

    for (int k = 0; k < CP; k++) {
        int p = (pos + k * k) % CP;

        if (stari[p] == VIDA) return false;

        if (stari[p] == OCUPATA &&
            elems[p].first == c && elems[p].second == v) {
            stari[p] = STEARSA;
            nrPerechi--;
            return true;
        }
    }
    return false;
}

// theta(1)
int MDO::dim() const {
    return nrPerechi;
}

// theta(1)
bool MDO::vid() const {
    return nrPerechi == 0;
}

// theta(CP + n*log n)
IteratorMDO MDO::iterator() const {
    return IteratorMDO(*this);
}

MDO::~MDO() {}