#include "sort.h"

void sortare_generica(ListaMasini* l, FunctieComparare cmpF)
{
	int i, j;
	for (i = 0; i < l->nr_masini; i++)
	{
		for (j = i + 1; j < l->nr_masini; j++)
		{
			if (cmpF(&l->masini[i], &l->masini[j]) > 0)
			{
				Masina aux = l->masini[i];
				l->masini[i] = l->masini[j];
				l->masini[j] = aux;
			}
		}
	}
}