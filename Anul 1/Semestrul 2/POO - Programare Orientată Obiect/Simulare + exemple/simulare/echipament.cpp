#include "echipament.h"

Echipament::Echipament(int cod, const string& categorie, const string& brand, const string& marime) :
	cod{ cod }, categorie{ categorie }, brand{ brand }, marime{ marime } {}

int Echipament::getCod() const noexcept { return cod; }

const string& Echipament::getCategorie() const noexcept { return categorie; }
const string& Echipament::getBrand() const noexcept { return brand;  }
const string& Echipament::getMarime() const noexcept { return marime;  }