#include <assert.h>

#include "MDO.h"
#include "IteratorMDO.h"

#include <exception>
#include <vector>

using namespace std;

bool relatie1(TCheie cheie1, TCheie cheie2) {
	if (cheie1 <= cheie2) {
		return true;
	}
	else {
		return false;
	}
}

void testAll(){
	MDO dictOrd = MDO(relatie1);
	assert(dictOrd.dim() == 0);
	assert(dictOrd.vid());
    dictOrd.adauga(1,2);
    dictOrd.adauga(1,3);
    assert(dictOrd.dim() == 2);
    assert(!dictOrd.vid());
    vector<TValoare> v= dictOrd.cauta(1);
    assert(v.size()==2);
    v= dictOrd.cauta(3);
    assert(v.size()==0);
    IteratorMDO it = dictOrd.iterator();
    it.prim();
    while (it.valid()){
    	TElem e = it.element();
    	it.urmator();
    }
    assert(dictOrd.sterge(1, 2) == true);
    assert(dictOrd.sterge(1, 3) == true);
    assert(dictOrd.sterge(2, 1) == false);
    assert(dictOrd.vid());
}

void testKPasi() {
    MDO dict = MDO(relatie1);

    dict.adauga(1, 10);
    dict.adauga(2, 20);
    dict.adauga(3, 30);
    dict.adauga(4, 40);
    dict.adauga(5, 50);

    IteratorMDO it = dict.iterator();
    it.prim();

    try {
        it.avanseazaKPasi(0);
        assert(false);
    }
    catch (exception&) {
        assert(true);
    }

    try {
        it.avanseazaKPasi(-3);
        assert(false);
    }
    catch (exception&) {
        assert(true);
    }

    it.avanseazaKPasi(2);
    assert(it.valid());
    assert(it.element().first == 3);
    assert(it.element().second == 30);

    it.avanseazaKPasi(1);
    assert(it.valid());
    assert(it.element().first == 4);

    it.avanseazaKPasi(2);
    assert(!it.valid());

    try {
        it.avanseazaKPasi(1);
        assert(false);
    }
    catch (exception&) {
        assert(true);
    }
}