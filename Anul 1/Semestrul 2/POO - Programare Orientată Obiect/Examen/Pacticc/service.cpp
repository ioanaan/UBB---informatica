#include "service.h"
#include <algorithm>

Service::Service(Repository& repo) : repo(repo) {}

/* returneaza toate task urile*/
const std::vector<Task>& Service::getAll() const {
	return repo.getAll();
}

/* sorteaza dupa stare */
std::vector<Task> Service::getSortedByStare() const {
    std::vector<Task> result = repo.getAll();
    auto prioritate = [](const std::string& stare) {
        if (stare == "open") return 0;
        if (stare == "inprogress") return 1;
        return 2;
        };
    std::sort(result.begin(), result.end(),
        [&](const Task& a, const Task& b) {
            return prioritate(a.getStare()) < prioritate(b.getStare());
        });
    return result;
}

/* filtreaza dupa programator */
std::vector<Task> Service::filtreazaDupaProgramator(const std::string& search) const {
    std::vector<Task> result;
    for (const auto& t : repo.getAll()) {
        for (const auto& p : t.getProgramatori()) {
            if (p.find(search) != std::string::npos) {
                result.push_back(t);
                break;
            }
        }
    }
    return result;
}

/* functie de adauga task */
void Service::adaugaTask(int id, const std::string& descriere, const std::vector<std::string>& programatori, const std::string& stare) {
    repo.add(Task(id, descriere, programatori, stare));
}

/* functie de schimbare stare */
void Service::schimbaStare(int id, const std::string& stareNoua) {
    repo.schimbaStare(id, stareNoua);
}