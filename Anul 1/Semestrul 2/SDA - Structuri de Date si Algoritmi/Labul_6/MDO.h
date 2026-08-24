#pragma once

#include <vector>

typedef int TCheie;
typedef int TValoare;

#include <utility>
typedef std::pair<TCheie, TValoare> TElem;

using namespace std;

class IteratorMDO;

typedef bool(*Relatie)(TCheie, TCheie);

class MDO {
    friend class IteratorMDO;
private:
    static const int CP = 1009;

    enum Stare { VIDA, OCUPATA, STEARSA };

    TElem   elems[CP]; 
    Stare   stari[CP];

    int nrPerechi;
    Relatie rel;

    int hash(TCheie c) const;

public:
    MDO(Relatie r);
    void adauga(TCheie c, TValoare v);
    vector<TValoare> cauta(TCheie c) const;
    bool sterge(TCheie c, TValoare v);
    int dim() const;
    bool vid() const;
    IteratorMDO iterator() const;
    ~MDO();
};