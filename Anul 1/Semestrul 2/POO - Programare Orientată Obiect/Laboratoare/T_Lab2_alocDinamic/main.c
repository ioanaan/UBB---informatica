#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "Ui.h"
#include "teste.h"

int main()
{
    ruleaza_toate_testele();

    if (_CrtDumpMemoryLeaks())
    {
        printf("exista memory leak\n");
    }
    else
    {
        printf("nu exista memory leak\n");
    }

    start();

    return 0;
}