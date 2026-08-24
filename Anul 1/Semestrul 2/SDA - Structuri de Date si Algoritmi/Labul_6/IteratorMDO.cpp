#include "IteratorMDO.h"
#include "MDO.h"
#include <algorithm>
#include <exception>
using namespace std;

void IteratorMDO::construieste() {
    sortate.clear();

    for (int i = 0; i < MDO::CP; i++) {
        if (dict.stari[i] == MDO::OCUPATA)
            sortate.push_back(dict.elems[i]);
    }

    Relatie r = dict.rel;
    sort(sortate.begin(), sortate.end(),
        [r](const TElem& a, const TElem& b) {
            return r(a.first, b.first) && !r(b.first, a.first);
        }
    );
}

IteratorMDO::IteratorMDO(const MDO& d) : dict(d) {
    construieste();
    curent = 0;
}

// theta(CP + n*log n)
void IteratorMDO::prim() {
    construieste();
    curent = 0;
}

// theta(1)
void IteratorMDO::urmator() {
    if (!valid()) throw exception();
    curent++;
}

// theta(1)
bool IteratorMDO::valid() const {
    return curent < (int)sortate.size();
}

// theta(1)
TElem IteratorMDO::element() const {
    if (!valid()) throw exception();
    return sortate[curent];
}

// theta(1)
void IteratorMDO::avanseazaKPasi(int k) {
    if (k <= 0)   throw exception();
    if (!valid()) throw exception();
    curent += k;
}