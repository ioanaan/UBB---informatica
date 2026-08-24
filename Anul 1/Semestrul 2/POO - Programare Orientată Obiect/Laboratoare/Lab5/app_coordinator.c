#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include "consola.h"
#include "teste.h"
#include <stdio.h>

int main()
{
	ruleaza_toate_testele();
	if (_CrtDumpMemoryLeaks() == 1)
		printf("S-a gasit Memory Leaks.\n");
	else
		printf("Nu s-a gasit Memory Leaks.\n");
	run();
	
	return 0;
}