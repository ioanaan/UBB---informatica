//Problema 3 -> Laborator 1 - Tema

#include <stdio.h>

int n, v[100];

void meniu()
{
	/*
	Functia afiseaza meniul.
	*/

	printf("\n--- Meniu ---\n");
	printf("1. Genereaza partitiile unui numar\n");
	printf("0. Iesire\n");
	printf("Alege o optiune: ");
}

void citire()
{
	/* 
	Functia citire() citeste de la tastatura numarul n, 
	care reprezinta suma pentru care se cauta combinatiile.
	Preonditii: n > 0
	Postconditii: n este un numar intreg pozitiv
	*/

	printf("Introdu un numar: ");
	scanf_s("%d", &n);
}

void afisare(int p)
{
	/*
	Functia afiseaza pe ecran combinatia curenta, 
	care este stocata in vectorul v.
	param: p -> numarul de elemente din combinatia curenta
	*/

	for (int i = 1; i <= p; i++)
		printf("%d ", v[i]);
	printf("\n");
}

void back(int p, int s)
{
	/*
	Functia back() este o functie recursiva care genereaza 
	partitiile lui n.
	param: p -> numarul de elemente din combinatia curenta
	param: s -> suma elementelor din combinatia curenta
	*/

	if (p == 1)
		for (int i = v[p - 1]; i <= n / 2; i++)
		{
			v[p] = i;
			if (s + i == n)
				afisare(p);
			else back(p + 1, s + i);
		}

	else {

		v[p] = v[p - 1] + 1;

		if (s + v[p] == n)
			afisare(p);
		else if (s + v[p] < n)
			back(p + 1, s + v[p]);

	}
}

int main()
{
	/*
	Functia main() ofera un meniu interactiv pentru a apela operatia de
	generare a partitiilor lui n de cate ori doreste utilizatorul.
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

			v[0] = 1;
			printf("Partitiile:\n");
			back(1, 0);
		}
		else if (optiune == 0)
		{
			printf(".\n");
		}
		else
		{
			printf("Nu-i bun\n");
		}

	} while (optiune != 0);

	return 0;
}