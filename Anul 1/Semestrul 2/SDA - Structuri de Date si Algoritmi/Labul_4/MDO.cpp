#include "IteratorMDO.h"
#include "MDO.h"
#include <exception>
using namespace std;

static void initSpatiuLiber(int* urm, int start, int cap) {
    for (int i = start; i < cap - 1; i++)
        urm[i] = i + 1;
    urm[cap - 1] = -1;
}

MDO::MDO(Relatie r) {
    rel = r;
    primCheie = -1;
    nrPerechi = 0;

    cpChei = CAP_INIT;
    chei = new TCheie[cpChei];
    urmChei = new int[cpChei];
    precChei = new int[cpChei];
    primValoare = new int[cpChei];
    initSpatiuLiber(urmChei, 0, cpChei);
    primLiberChei = 0;

    cpVal = CAP_INIT;
    valori = new TValoare[cpVal];
    urmVal = new int[cpVal];
    precVal = new int[cpVal];
    initSpatiuLiber(urmVal, 0, cpVal);
    primLiberVal = 0;
}

MDO::MDO(const MDO& o) : rel(o.rel), primCheie(o.primCheie),
primLiberChei(o.primLiberChei), primLiberVal(o.primLiberVal),
nrPerechi(o.nrPerechi), cpChei(o.cpChei), cpVal(o.cpVal) {

    chei = new TCheie[cpChei];
    urmChei = new int[cpChei];
    precChei = new int[cpChei];
    primValoare = new int[cpChei];

    for (int i = 0; i < cpChei; i++) {

        chei[i] = o.chei[i];
        urmChei[i] = o.urmChei[i];
        precChei[i] = o.precChei[i];
        primValoare[i] = o.primValoare[i];
    }

    valori = new TValoare[cpVal];
    urmVal = new int[cpVal];
    precVal = new int[cpVal];

    for (int i = 0; i < cpVal; i++) {

        valori[i] = o.valori[i];
        urmVal[i] = o.urmVal[i];
        precVal[i] = o.precVal[i];
    }
}

MDO& MDO::operator=(const MDO& o) {

    if (this == &o) return *this;
    delete[] chei; delete[] urmChei; delete[] precChei; delete[] primValoare;
    delete[] valori; delete[] urmVal; delete[] precVal;

    rel = o.rel; primCheie = o.primCheie;
    primLiberChei = o.primLiberChei; primLiberVal = o.primLiberVal;
    nrPerechi = o.nrPerechi; cpChei = o.cpChei; cpVal = o.cpVal;

    chei = new TCheie[cpChei];
    urmChei = new int[cpChei];
    precChei = new int[cpChei];
    primValoare = new int[cpChei];

    for (int i = 0; i < cpChei; i++) {

        chei[i] = o.chei[i]; urmChei[i] = o.urmChei[i];
        precChei[i] = o.precChei[i]; primValoare[i] = o.primValoare[i];
    }

    valori = new TValoare[cpVal];
    urmVal = new int[cpVal];
    precVal = new int[cpVal];

    for (int i = 0; i < cpVal; i++) {

        valori[i] = o.valori[i];
        urmVal[i] = o.urmVal[i];
        precVal[i] = o.precVal[i];
    }
    return *this;
}

MDO::~MDO() {
    delete[] chei; delete[] urmChei; delete[] precChei; delete[] primValoare;
    delete[] valori; delete[] urmVal; delete[] precVal;
}

void MDO::redimensioneazaChei() {
    int cpNou = cpChei * 2;

    TCheie* cheiNou = new TCheie[cpNou];
    int* urmCheiNou = new int[cpNou];
    int* precCheiNou = new int[cpNou];
    int* primValoareNou = new int[cpNou];

    for (int i = 0; i < cpChei; i++) {
        cheiNou[i] = chei[i];
        urmCheiNou[i] = urmChei[i];
        precCheiNou[i] = precChei[i];
        primValoareNou[i] = primValoare[i];
    }

    initSpatiuLiber(urmCheiNou, cpChei, cpNou);
    primLiberChei = cpChei;

    delete[] chei; delete[] urmChei; delete[] precChei; delete[] primValoare;

    chei = cheiNou;
    urmChei = urmCheiNou;
    precChei = precCheiNou;
    primValoare = primValoareNou;
    cpChei = cpNou;
}

void MDO::redimensioneazaVal() {
    int cpNou = cpVal * 2;

    TValoare* valoriNou = new TValoare[cpNou];
    int* urmValNou = new int[cpNou];
    int* precValNou = new int[cpNou];

    for (int i = 0; i < cpVal; i++) {
        valoriNou[i] = valori[i];
        urmValNou[i] = urmVal[i];
        precValNou[i] = precVal[i];
    }

    initSpatiuLiber(urmValNou, cpVal, cpNou);
    primLiberVal = cpVal;

    delete[] valori; delete[] urmVal; delete[] precVal;

    valori = valoriNou;
    urmVal = urmValNou;
    precVal = precValNou;
    cpVal = cpNou;
}

int MDO::alocaChei() {
    if (primLiberChei == -1)
        redimensioneazaChei(); 
    int i = primLiberChei;
    primLiberChei = urmChei[primLiberChei];
    return i;
}

void MDO::dealocaChei(int i) {
    urmChei[i] = primLiberChei;
    primLiberChei = i;
}

int MDO::alocaVal() {
    if (primLiberVal == -1)
        redimensioneazaVal();
    int i = primLiberVal;
    primLiberVal = urmVal[primLiberVal];
    return i;
}

void MDO::dealocaVal(int i) {
    urmVal[i] = primLiberVal;
    primLiberVal = i;
}

// favorabil: theta(1) 
// defavorabil: theta(n) 
// mediu: O(n/2)
void MDO::adauga(TCheie c, TValoare v) {
    int iCheie = primCheie;
    int precInd = -1;

    while (iCheie != -1 && rel(chei[iCheie], c) && chei[iCheie] != c) {
        precInd = iCheie;
        iCheie = urmChei[iCheie];
    }

    if (iCheie != -1 && chei[iCheie] == c) {
        int iVal = alocaVal();
        valori[iVal] = v;
        urmVal[iVal] = -1;
        precVal[iVal] = -1;

        int primV = primValoare[iCheie];
        urmVal[iVal] = primV;
        if (primV != -1)
            precVal[primV] = iVal;
        primValoare[iCheie] = iVal;
    }
    else {
        int nodNou = alocaChei();
        chei[nodNou] = c;
        primValoare[nodNou] = -1;

        int iVal = alocaVal();
        valori[iVal] = v;
        urmVal[iVal] = -1;
        precVal[iVal] = -1;
        primValoare[nodNou] = iVal;

        urmChei[nodNou] = iCheie;
        precChei[nodNou] = precInd;

        if (precInd == -1)
            primCheie = nodNou;
        else
            urmChei[precInd] = nodNou;

        if (iCheie != -1)
            precChei[iCheie] = nodNou;
    }

    nrPerechi++;
}

// favorabil:   theta(1) 
// defavorabil: theta(n+k) 
// mediu: O(n/2)
vector<TValoare> MDO::cauta(TCheie c) const {
    vector<TValoare> rezultat;

    int iCheie = primCheie;
    while (iCheie != -1) {
        if (chei[iCheie] == c) {
            int iVal = primValoare[iCheie];
            while (iVal != -1) {
                rezultat.push_back(valori[iVal]);
                iVal = urmVal[iVal];
            }
            return rezultat;
        }
        iCheie = urmChei[iCheie];
    }
    return rezultat;
}

// favorabil: theta(1) 
// defavorabil: theta(n+k)
// mediu: O(n/2 + k/2)
bool MDO::sterge(TCheie c, TValoare v) {
    int iCheie = primCheie;
    while (iCheie != -1 && chei[iCheie] != c)
        iCheie = urmChei[iCheie];

    if (iCheie == -1) return false;

    int iVal = primValoare[iCheie];
    while (iVal != -1 && valori[iVal] != v)
        iVal = urmVal[iVal];

    if (iVal == -1) return false;

    int precV = precVal[iVal];
    int urmV = urmVal[iVal];

    if (precV == -1)
        primValoare[iCheie] = urmV;
    else
        urmVal[precV] = urmV;

    if (urmV != -1)
        precVal[urmV] = precV;

    dealocaVal(iVal);
    nrPerechi--;

    if (primValoare[iCheie] == -1) {
        int precC = precChei[iCheie];
        int urmC = urmChei[iCheie];

        if (precC == -1)
            primCheie = urmC;
        else
            urmChei[precC] = urmC;

        if (urmC != -1)
            precChei[urmC] = precC;

        dealocaChei(iCheie);
    }

    return true;
}

// theta(1)
int MDO::dim() const { return nrPerechi; }

// theta(1)
bool MDO::vid() const { return nrPerechi == 0; }

// theta(1)
IteratorMDO MDO::iterator() const { return IteratorMDO(*this); }