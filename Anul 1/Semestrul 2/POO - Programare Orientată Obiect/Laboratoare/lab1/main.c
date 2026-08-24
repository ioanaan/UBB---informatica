#include <stdio.h>

int main()
{
	int n, i;
	double s = 0;
	double numar;

	printf("Introdu numarul:");
	scanf_s("%d", &n);

	for (int i = 0; i < n; i++)
	{

		printf("Introdu numarul:");
		scanf_s("%lf", &numar);
		s = s + numar;

	}

	//printf("Suma numerelor este: %lf", s);
	printf("Suma celor %d numere este: %.2f\n", n, s);

	return 0;

	// Problema 3 !!!
}