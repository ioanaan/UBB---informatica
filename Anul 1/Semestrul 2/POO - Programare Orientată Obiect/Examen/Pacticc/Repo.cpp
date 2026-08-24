#include "Repo.h"
#include <fstream>
#include <sstream>

Repository::Repository(const std::string& filename) : filename(filename) {
    loadFromFile();
}

/* citeste task uri din fis */
void Repository::loadFromFile() {
    std::ifstream f(filename);
    std::string line;
    while (std::getline(f, line)) {
        std::stringstream ss(line);
        std::string idStr, descriere, progStr, stare;
        std::getline(ss, idStr, ',');
        std::getline(ss, descriere, ',');
        std::getline(ss, progStr, ',');
        std::getline(ss, stare, ',');

        std::vector<std::string> programatori;
        std::stringstream ssProg(progStr);
        std::string prog;
        while (std::getline(ssProg, prog, '|'))
            programatori.push_back(prog);

        tasks.push_back(Task(std::stoi(idStr), descriere, programatori, stare));
    }
}

/* salveaza in fis */
void Repository::saveToFile() {
    std::ofstream f(filename);
    for (const auto& t : tasks) {
        f << t.getId() << "," << t.getDescriere() << ",";
        const auto& progs = t.getProgramatori();
        for (int i = 0; i < (int)progs.size(); i++) {
            f << progs[i];
            if (i < (int)progs.size() - 1) f << "|";
        }
        f << "," << t.getStare() << "\n";
    }
}

/* return toate taskurile */
const std::vector<Task>& Repository::getAll() const {
    return tasks;
}

/* adauga task si salveaza */
void Repository::add(const Task& t) {
    tasks.push_back(t);
    saveToFile();
}

/* return nr de taskuri */
size_t Repository::size() const {
    return tasks.size();
}

void Repository::schimbaStare(int id, const std::string& stareNoua) {
    for (auto& t : tasks)
        if (t.getId() == id) {
            t.setStare(stareNoua);
            break;
        }
    saveToFile();
}