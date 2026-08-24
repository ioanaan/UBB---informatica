#include "teste.h"
#include <stdio.h>

void ruleaza_toate_testele()
{
	ruleaza_teste_domain();
	ruleaza_teste_repo();
	ruleaza_teste_service();
	ruleaza_teste_utilitare();
	printf("Au rulat toate testele.\n");
}