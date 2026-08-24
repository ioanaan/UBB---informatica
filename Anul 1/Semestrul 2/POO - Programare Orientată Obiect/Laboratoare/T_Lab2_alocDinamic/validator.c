#include "validator.h"
#include <string.h>
#include <ctype.h>

int valideaza_categorie(const char* cat) 
{
    if (strcmp(cat, "suv") == 0 ||
        strcmp(cat, "cabrio") == 0 ||
        strcmp(cat, "sedan") == 0 ||
        strcmp(cat, "hatchback") == 0 ||
        strcmp(cat, "break") == 0) 
    {
        return 1;
    }

    return 0;
}

int valideaza_numar(const char* nr) 
{
    int len = (int)strlen(nr);

    if (len < 6 || len > 8) 
        return 0;

    for (int i = len - 3; i < len; i++) 
    {
        if (!isalpha(nr[i])) 
            return 0;
    }

    if (!isalpha(nr[0])) 
        return 0;

    int index_cifre = 1;
    if (isalpha(nr[1])) 
    {
        index_cifre = 2;
    }

    int numar_cifre = 0;
    for (int i = index_cifre; i < len - 3; i++) 
    {
        if (!isdigit(nr[i])) 
            return 0;

        numar_cifre++;
    }

    if (numar_cifre < 2 || numar_cifre > 3) 
        return 0;

    return 1; 
}

int valideaza_masina(Masina m)
{
    if ((int)strlen(m.numar) == 0 || (int)strlen(m.model) == 0 || (int)strlen(m.categorie) == 0)
        return 0;

    if (m.status != 0 && m.status != 1)
        return 0;

    if (valideaza_numar(m.numar) == 0)
        return 0;

    if (valideaza_categorie(m.categorie) == 0)
        return 0;

    return 1;
}