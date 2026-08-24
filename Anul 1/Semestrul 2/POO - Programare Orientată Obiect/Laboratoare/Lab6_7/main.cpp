#include <crtdbg.h>

#include "ui.h"
#include "teste.h"

int main() 
{
    testAll();

    if (_CrtDumpMemoryLeaks() == 1)
        printf("S-au gasit Memory Leaks.\n");
    else
        printf("Nu s-au gasit Memory Leaks.\n");

    Repo repo;
    Service service{ repo };
    UI ui{ service };
    ui.run();
    return 0;
}