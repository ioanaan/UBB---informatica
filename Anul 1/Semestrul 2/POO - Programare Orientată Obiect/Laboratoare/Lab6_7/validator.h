#pragma once
#include "carte.h"

class ValidationException {
private:
    string mesaj;
public:
    ValidationException(const string& mesaj) : mesaj{ mesaj } {}
    const string& getMesaj() const noexcept { return mesaj; }
};

class Validator {
public:
    void valideazaCarte(const string& titlu, const string& autor,
        const string& gen, int an) const;
    void valideazaIndex(int index, int size) const;
};