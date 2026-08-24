#include "teste.h"
#include "task.h"
#include "repo.h"
#include "service.h"
#include <cassert>
#include <fstream>

/* test constructorul / getterii clasei Task */
void testTask() {
    Task t(1, "Fix bug", { "Ion", "Ana" }, "open");
    assert(t.getId() == 1);
    assert(t.getDescriere() == "Fix bug");
    assert(t.getProgramatori()[0] == "Ion");
    assert(t.getProgramatori()[1] == "Ana");
    assert(t.getStare() == "open");
    assert(t.getProgramatoriStr() == "Ion, Ana");
}

/* test citirea din fisier / stocarea in vector */
void testRepository() {
    std::ofstream f("test_temp.txt");
    f << "1,Fix bug,Ion|Ana,open\n";
    f << "2,Add feature,Mihai,closed\n";
    f.close();

    Repository repo("test_temp.txt");
    assert(repo.size() == 2);
    assert(repo.getAll()[0].getDescriere() == "Fix bug");
    assert(repo.getAll()[1].getStare() == "closed");
}

/* test sortarea / filtrarea / adaugarea */
void testService() {
    std::ofstream f("test_temp.txt");
    f << "1,Fix bug,Ion|Ana,open\n";
    f << "2,Add feature,Mihai,closed\n";
    f << "3,Review,Ion,inprogress\n";
    f.close();

    Repository repo("test_temp.txt");
    Service srv(repo);

    // test sortare dupa stare
    auto sortate = srv.getSortedByStare();
    assert(sortate[0].getStare() == "open");
    assert(sortate[1].getStare() == "inprogress");
    assert(sortate[2].getStare() == "closed");

    // test filtrare dupa programator
    auto filtrate = srv.filtreazaDupaProgramator("Ion");
    assert(filtrate.size() == 2);

    // test adaugare
    srv.adaugaTask(4, "Test task", { "George" }, "open");
    assert(repo.size() == 4);
}

void runAllTests() {
    testTask();
    testRepository();
    testService();
}