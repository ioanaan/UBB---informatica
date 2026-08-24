#pragma once
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Echipament {
private:
	int cod;
	string categorie, brand, marime;

public:
	Echipament() = default;
	Echipament(int cod, const string& categorie, const string& brand, const string& marime);

	int getCod() const noexcept;
	const string& getCategorie() const noexcept;
	const string& getBrand() const noexcept;
	const string& getMarime() const noexcept;

};