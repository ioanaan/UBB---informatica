//Problema 15 -> Laborator 2

#include <stdio.h>

int n, p, q;

void meniu()
{
	/*
	Functia afiseaza un meniu pentru a alege optiunea dorita.
	*/

	printf("-Meniu-\n");
	printf("1. Perechi de numere prime gemene\n");
	printf("0. Iesire\n");
	printf("Alege o optiune: ");
}

void citire()
{
	/*
	Functia citeste numarul de perechi de 
	numere prime care se doresc a fi afisate.
	Preconditii: -
	Postconditii: variabila globala n primeste valoarea intreaga introdusa.
	*/

	printf("n = ");
	scanf_s("%d", &n);
}

int e_prim(int d)
{
	/*
	Functia verifica daca un numar este prim sau nu.
	param: d -> numarul care se verifica daca este prim sau nu
	Preconditii: d intreg
	Postconditii: returneaza 1 -> d prim, si 0 altfel
	*/

	if (d < 2)
		return 0;

	for (int i = 2; i <= d / 2; i++)
		if (d % i == 0)
			return 0;
	return 1;
}

int main()
{
	/*
	Functia afiseaza la inceput un meniu pentru a apela fct. citire,
	apoi determina si afiseaza perechile de numere prime gemene.
	*/

	int optiune;

	do
	{
		meniu();

		while (scanf_s("%d", &optiune) != 1)
		{
			printf("Optiune invalida. Introdu un numar: ");
			while (getchar() != '\n')
				continue;
		}

		if (optiune == 1)
		{
			citire();
			int nr_per = 0, p = 3, q = 5;

			printf("Perechile:\n");
			while (nr_per < n)
			{
				if (e_prim(p) && e_prim(q))
				{
					printf("%d %d\n", p, q);
					nr_per++;
				}

				p += 2;
				q += 2;
			}
		}
		else if (optiune == 0)
		{
			printf(".\n");
		}
		else
		{
			printf("Nu-i bun.\n");
		}

	} while (optiune != 0); 

	return 0;
}