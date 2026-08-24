#pragma once
#include "MDO.h"

class IteratorMDO {
    friend class MDO;
private:
    IteratorMDO(const MDO& dictionar);
    const MDO& dict;

    int iCheie;
    int iVal;

public:
    void prim();
    void urmator();
    bool valid() const;
    TElem element() const;
    void AvanseazaKPasi(int k);
};
