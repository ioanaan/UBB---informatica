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
    static const int CAP_INIT = 10;

    TCheie* chei;
    int* urmChei;
    int* precChei;
    int* primValoare;
    int cpChei;

    TValoare* valori;
    int* urmVal;
    int* precVal;
    int cpVal;

    int primCheie;
    int primLiberChei;
    int primLiberVal;
    int nrPerechi;

    Relatie rel;

    int  alocaChei();
    void dealocaChei(int i);
    int  alocaVal();
    void dealocaVal(int i);

    void redimensioneazaChei();
    void redimensioneazaVal();

public:
    MDO(Relatie r);
    MDO(const MDO& other);
    MDO& operator=(const MDO& other);
    void adauga(TCheie c, TValoare v);
    vector<TValoare> cauta(TCheie c) const;
    bool sterge(TCheie c, TValoare v);
    int dim() const;
    bool vid() const;
    IteratorMDO iterator() const;
    ~MDO();
};