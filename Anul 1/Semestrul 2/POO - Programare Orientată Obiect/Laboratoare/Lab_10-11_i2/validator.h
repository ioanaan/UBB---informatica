#pragma once
#include "exceptii.h"
#include <string>
using std::string;

class Validator {
public:
    static void valideaza(const string& titlu, const string& autor,
        const string& gen, int an);
};