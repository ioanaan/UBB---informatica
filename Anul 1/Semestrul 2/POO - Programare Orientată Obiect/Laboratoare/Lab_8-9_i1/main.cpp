#define _CRTDBG_MAP_ALLOC
#include "ui.h"
#include "teste.h"
#include <iostream>
#include <crtdbg.h>
using std::cout;

int main() {
    testAll();
    cout << "Testele au rulat cu succes!\n";

    if (_CrtDumpMemoryLeaks() == 1)
        printf("S-au gasit memory leaks\n");
    else
        printf("Nu avem memory leaks\n");

    Repo repo;
    Service service{ repo };
    UI ui{ service };
    ui.run();
    return 0;
}