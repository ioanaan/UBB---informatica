#pragma once
#include "echipament.h"
#include <vector>
#include <iostream>
#include <string>

using namespace std;

class FisierRepo {
private:
	string filename;
	vector<Echipament>echipamente;
	void incarcaDinFisier();
	void salveazaInFisier() const;

public:

	FisierRepo(const string& filename);
	const vector<Echipament>& getAll() const noexcept;

};