#pragma once
#include "repo.h"

typedef int (*FunctieComparare)(Masina* m1, Masina* m2);

void sortare_generica(ListaMasini* l, FunctieComparare cmpF);