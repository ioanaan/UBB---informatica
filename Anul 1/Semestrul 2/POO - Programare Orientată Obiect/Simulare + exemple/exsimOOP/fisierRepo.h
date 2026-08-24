#pragma once
#include "rochie.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class FisierRepo
{
private:
	string filename;
	vector<Rochie>rochii;

	void incarcaDinFisier();
	void salveazaInFisier() const;

public:
	const vector<Rochie>& getAll() const noexcept;
	void modifica(int cod);

	FisierRepo(const string& filename);
};