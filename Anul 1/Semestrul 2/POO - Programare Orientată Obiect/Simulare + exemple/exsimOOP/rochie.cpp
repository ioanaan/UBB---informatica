#include "rochie.h"

Rochie::Rochie(int cod, const string& denumire,
	const string& marime, double pret, bool disponibila)
	: cod{ cod }, denumire{ denumire }, marime{ marime }, pret{ pret }, disponibila{ disponibila } {
}

int Rochie::getCod() const noexcept { return cod; }
const string& Rochie::getDenumire() const noexcept { return denumire; }
const string& Rochie::getMarime() const noexcept { return marime; }
double Rochie::getPret() const noexcept { return pret; }
bool Rochie::getDisponibila() const noexcept { return disponibila; }

void Rochie::setDisponibila(bool dispo) noexcept { disponibila = dispo; }