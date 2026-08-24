#pragma once
#include <string>
#include <iostream>
#include <cassert>

using namespace std;


class Rochie 
{
private:
	int cod;
	string denumire, marime;
	double pret;
	bool disponibila;
	
public: 
	Rochie(int cod, const string& denumire, 
		const string& marime, double pret, bool disponibila);

	int getCod() const noexcept;
	const string& getDenumire() const noexcept;
	const string& getMarime() const noexcept;
	double getPret() const noexcept;
	bool getDisponibila() const noexcept;

	void setDisponibila(bool dispo) noexcept;

	Rochie() = default;
};