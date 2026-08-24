#include "Validator.h"

void Validator::valideazaCarte(const string& titlu, const string& autor,
    const string& gen, int an) const
{
    string erori = "";

    if (titlu.empty())
        erori += "Titlul nu poate fi gol!\n";
    if (autor.empty())
        erori += "Autorul nu poate fi gol!\n";
    if (gen != "roman" && gen != "nuvela" &&
        gen != "poezie" && gen != "drama")
        erori += "Genul trebuie sa fie: roman, nuvela, poezie sau drama!\n";
    if (an <= 0)
        erori += "Anul trebuie sa fie pozitiv!\n";

    if (!erori.empty())
        throw ValidationException(erori);
}

void Validator::valideazaIndex(int index, int size) const
{
    if (index < 0 || index >= size)
        throw ValidationException("Index invalid\n");
}