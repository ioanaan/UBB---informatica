#include "cos.h"
#include <fstream>
#include <random>
#include <algorithm>

void Cos::goleste() noexcept {
    carti.clear();
}

void Cos::adauga(const string& titlu) {
    const auto& stoc = service.getCarti();
    auto it = std::find_if(stoc.begin(), stoc.end(), [&titlu](const Carte& c) noexcept {
        return c.getTitlu() == titlu;
        });
    if (it == stoc.end())
        throw CosException("Nu exista nicio carte cu titlul \"" + titlu + "\" in biblioteca!");
    carti.push_back(*it);
}

void Cos::genereaza(size_t n) {
    auto copie = service.getCarti();
    if (copie.empty())
        throw CosException("Biblioteca este goala! Nu se pot genera carti pentru cos.");
    if (n > copie.size())
        n = copie.size();

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(copie.begin(), copie.end(), g);

    carti.clear();
    for (size_t i = 0; i < n; ++i)
        carti.push_back(copie.at(i));
}

const vector<Carte>& Cos::getCarti() const noexcept {
    return carti;
}

size_t Cos::getNrCarti() const noexcept {
    return carti.size();
}

void Cos::exportCSV(const string& numeFisier) const {
    std::ofstream f(numeFisier + ".csv");
    if (!f.is_open())
        throw CosException("Nu s-a putut crea fisierul: " + numeFisier + ".csv");

    f << "Nr,Titlu,Autor,Gen,An aparitie\n";
    int nr = 1;
    for (const auto& c : carti) {
        f << nr << "," << c.getTitlu() << "," << c.getAutor() << ","
            << c.getGen() << "," << c.getAnAparitie() << "\n";
        nr++;
    }
}

void Cos::exportHTML(const string& numeFisier) const {
    std::ofstream f(numeFisier + ".html");
    if (!f.is_open())
        throw CosException("Nu s-a putut crea fisierul: " + numeFisier + ".html");

    f << "<!DOCTYPE html>\n<html lang=\"ro\">\n<head>\n";
    f << "  <meta charset=\"UTF-8\">\n";
    f << "  <title>Cos Inchirieri - Biblioteca</title>\n";
    f << "  <style>\n";
    f << "    body { font-family: Georgia, serif; background-color: #f9f6f0; margin: 40px; }\n";
    f << "    h1 { color: #4a3728; text-align: center; }\n";
    f << "    p { text-align: center; color: #6b4f3a; }\n";
    f << "    table { border-collapse: collapse; width: 80%; margin: 20px auto; }\n";
    f << "    th { background-color: #7b4f2e; color: white; padding: 10px; text-align: left; }\n";
    f << "    td { padding: 8px; border-bottom: 1px solid #c9a97a; }\n";
    f << "    tr:nth-child(even) { background-color: #f0e6d3; }\n";
    f << "    tr:hover { background-color: #d4b896; }\n";
    f << "  </style>\n";
    f << "</head>\n<body>\n";
    f << "  <h1>Cos Inchirieri Biblioteca</h1>\n";
    f << "  <p>Total carti: <strong>" << carti.size() << "</strong></p>\n";
    f << "  <table>\n";
    f << "    <tr><th>Nr</th><th>Titlu</th><th>Autor</th><th>Gen</th><th>An aparitie</th></tr>\n";
    int nr = 1;
    for (const auto& c : carti) {
        f << "    <tr><td>" << nr << "</td><td>" << c.getTitlu() << "</td><td>"
            << c.getAutor() << "</td><td>" << c.getGen() << "</td><td>"
            << c.getAnAparitie() << "</td></tr>\n";
        nr++;
    }
    f << "  </table>\n</body>\n</html>\n";
}