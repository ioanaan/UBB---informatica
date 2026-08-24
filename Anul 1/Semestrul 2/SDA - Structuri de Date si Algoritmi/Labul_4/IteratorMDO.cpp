#include "IteratorMDO.h"
#include "MDO.h"
#include <exception>

using namespace std;

IteratorMDO::IteratorMDO(const MDO& d) : dict(d) {
    iCheie = dict.primCheie;
    iVal = (iCheie != -1) ? dict.primValoare[iCheie] : -1;
}

void IteratorMDO::prim() {
    iCheie = dict.primCheie;
    iVal = (iCheie != -1) ? dict.primValoare[iCheie] : -1;
}

void IteratorMDO::urmator() {
    if (!valid()) throw exception();

    iVal = dict.urmVal[iVal];

    if (iVal == -1) {
        iCheie = dict.urmChei[iCheie];
        if (iCheie != -1)
            iVal = dict.primValoare[iCheie];
    }
}

bool IteratorMDO::valid() const {
    return iCheie != -1 && iVal != -1;
}

TElem IteratorMDO::element() const {
    if (!valid()) throw exception();
    return TElem(dict.chei[iCheie], dict.valori[iVal]);
}

void IteratorMDO::AvanseazaKPasi(int k) {
    if (k <= 0)   throw exception();
    if (!valid()) throw exception();

    while (k > 0 && valid()) {
        urmator();
        k++;
    }
}