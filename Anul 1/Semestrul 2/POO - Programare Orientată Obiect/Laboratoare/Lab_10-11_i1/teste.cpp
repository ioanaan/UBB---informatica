#include "teste.h"
#include "service.h"
#include "cos.h"
#include "repoFisier.h"
#include "repoMemorie.h"
#include "repoLab.h"
#include <cassert>
#include <fstream>

namespace {

    void testDomeniu() {
        Carte c{ "Ion", "Rebreanu", "roman", 1920 };
        assert(c.getTitlu() == "Ion");
        assert(c.getAutor() == "Rebreanu");
        assert(c.getGen() == "roman");
        assert(c.getAnAparitie() == 1920);
    }

    void testRepoAdauga() {
        //Repo repo;
        RepoMemorie repo;
        repo.adauga({ "Ion", "Rebreanu", "roman", 1920 });
        assert(repo.getAll().size() == 1);
        assert(repo.getAll().at(0).getTitlu() == "Ion");
    }

    void testRepoSterge() {
        //Repo repo;
        RepoMemorie repo;
        repo.adauga({ "Ion", "Rebreanu", "roman", 1920 });
        repo.adauga({ "Baltagul", "Sadoveanu", "roman", 1930 });
        repo.sterge("Ion");
        assert(repo.getAll().size() == 1);
        assert(repo.getAll().at(0).getTitlu() == "Baltagul");
    }

    void testRepoModifica() {
        RepoMemorie repo;
        repo.adauga({ "Ion", "Rebreanu", "roman", 1920 });
        repo.modifica("Ion", { "Ion nou", "Rebreanu", "roman", 2000 });
        assert(repo.getAll().at(0).getTitlu() == "Ion nou");
    }

    void testRepoCauta() {
        RepoMemorie repo;
        repo.adauga({ "Ion", "Rebreanu", "roman", 1920 });
        const auto& c = repo.cauta("Ion");
        assert(c.getTitlu() == "Ion");
    }

    void testRepoFiltrare() {
        RepoMemorie repo;
        repo.adauga({ "Ion", "Rebreanu", "roman", 1920 });
        repo.adauga({ "Ionel", "Autor", "nuvela", 1950 });
        repo.adauga({ "Baltagul", "Sadoveanu", "roman", 1930 });

        assert(repo.filtreazaDupaTitlu("Ion").size() == 2);
        assert(repo.filtreazaDupaTitlu("xyz").empty());
        assert(repo.filtreazaDupaAn(1920).size() == 1);
        assert(repo.filtreazaDupaAn(2000).empty());
    }

    void testRepoExceptii() {
        RepoMemorie repo;
        repo.adauga({ "Ion", "Rebreanu", "roman", 1920 });

        bool caught = false;
        try { repo.adauga({ "Ion", "Rebreanu", "roman", 1920 }); }
        catch (const DuplicateTitluException&) { caught = true; }
        assert(caught);

        caught = false;
        try { repo.sterge("Inexistent"); }
        catch (const CarteNotFoundException&) { caught = true; }
        assert(caught);

        caught = false;
        try { repo.modifica("Inexistent", { "X", "X", "roman", 1920 }); }
        catch (const CarteNotFoundException&) { caught = true; }
        assert(caught);

        caught = false;
        try { repo.cauta("Inexistent"); }
        catch (const CarteNotFoundException&) { caught = true; }
        assert(caught);
    }

    void testServiceAdauga() {
        RepoMemorie repo;
        Service service{ repo };
        service.adaugaCarte("Ion", "Rebreanu", "roman", 1920);
        assert(service.getCarti().size() == 1);
    }

    void testServiceSterge() {
        RepoMemorie repo;
        Service service{ repo };
        service.adaugaCarte("Ion", "Rebreanu", "roman", 1920);
        service.stergeCarte("Ion");
        assert(service.getCarti().empty());
    }

    void testServiceModifica() {
        RepoMemorie repo;
        Service service{ repo };
        service.adaugaCarte("Ion", "Rebreanu", "roman", 1920);
        service.modificaCarte("Ion", "Ion nou", "Rebreanu", "roman", 2000);
        assert(service.getCarti().at(0).getTitlu() == "Ion nou");
    }

    void testServiceFiltrare() {
        RepoMemorie repo;
        Service service{ repo };
        service.adaugaCarte("Ion", "Rebreanu", "roman", 1920);
        service.adaugaCarte("Ionel", "Autor", "nuvela", 1950);
        service.adaugaCarte("Baltagul", "Sadoveanu", "roman", 1930);

        assert(service.filtreazaDupaTitlu("Ion").size() == 2);
        assert(service.filtreazaDupaAn(1920).size() == 1);
    }

    void testServiceSortare() {
        RepoMemorie repo;
        Service service{ repo };
        service.adaugaCarte("Mara", "Slavici", "roman", 1906);
        service.adaugaCarte("Baltagul", "Sadoveanu", "roman", 1930);
        service.adaugaCarte("Ion", "Rebreanu", "nuvela", 1906);

        auto g1 = service.sorteazaDupaTitlu();
        assert(g1.at(0).getTitlu() == "Baltagul");

        auto g2 = service.sorteazaDupaAutor();
        assert(g2.at(0).getAutor() == "Rebreanu");

        auto g3 = service.sorteazaDupaAnSiGen();
        assert(g3.at(0).getGen() == "nuvela");
    }

    void testServiceValidare() {
        RepoMemorie repo;
        Service service{ repo };

        bool caught = false;
        try { service.adaugaCarte("", "Rebreanu", "roman", 1920); }
        catch (const ValidationException&) { caught = true; }
        assert(caught);

        caught = false;
        try { service.adaugaCarte("Ion", "", "roman", 1920); }
        catch (const ValidationException&) { caught = true; }
        assert(caught);

        caught = false;
        try { service.adaugaCarte("Ion", "Rebreanu", "invalid", 1920); }
        catch (const ValidationException&) { caught = true; }
        assert(caught);

        caught = false;
        try { service.adaugaCarte("Ion", "Rebreanu", "roman", -1); }
        catch (const ValidationException&) { caught = true; }
        assert(caught);
    }

    void testServicePopuleaza() {
        RepoMemorie repo;
        Service service{ repo };
        service.populeazaBiblioteca(10);
        assert(service.getCarti().size() == 10);

        // testeaza si cu n mare
        RepoMemorie repo2;
        Service service2{ repo2 };
        service2.populeazaBiblioteca(50);
        assert(service2.getCarti().size() == 50);
    }

    void testCosAdaugaSiGoleste() {
        RepoMemorie repo;
        Service service{ repo };
        Cos cos{ service };

        service.adaugaCarte("Ion", "Rebreanu", "roman", 1920);
        cos.adauga("Ion");
        assert(cos.getNrCarti() == 1);

        bool caught = false;
        try { cos.adauga("Inexistent"); }
        catch (const CosException&) { caught = true; }
        assert(caught);

        cos.goleste();
        assert(cos.getNrCarti() == 0);
    }

    void testCosGenereaza() {
        RepoMemorie repo;
        Service service{ repo };
        Cos cos{ service };

        bool caught = false;
        try { cos.genereaza(5); }
        catch (const CosException&) { caught = true; }
        assert(caught);

        service.adaugaCarte("Ion", "Rebreanu", "roman", 1920);
        service.adaugaCarte("Baltagul", "Sadoveanu", "roman", 1930);

        cos.genereaza(1);
        assert(cos.getNrCarti() == 1);

        cos.genereaza(10);
        assert(cos.getNrCarti() == 2);
    }

    void testCosExport() {
        RepoMemorie repo;
        Service service{ repo };
        Cos cos{ service };

        service.adaugaCarte("Ion", "Rebreanu", "roman", 1920);
        cos.adauga("Ion");

        cos.exportHTML("test_temp");
        std::ifstream f2("test_temp.html");
        assert(f2.good());
        f2.close();
        std::remove("test_temp.html");

        bool caught = false;
        try { cos.exportHTML("/folder_inexistent/file"); }
        catch (const CosException&) { caught = true; }
        assert(caught);
    }

    void testCosGetters() {
        RepoMemorie repo;
        Service service{ repo };
        Cos cos{ service };

        service.adaugaCarte("Ion", "Rebreanu", "roman", 1920);
        cos.adauga("Ion");

        const auto& v = cos.getCarti();
        assert(v.size() == 1);
        assert(v.at(0).getTitlu() == "Ion");
        assert(cos.getNrCarti() == 1);
    }

    void testExceptii() {
        AppException e1("test");
        assert(std::string(e1.what()) == "test");

        ValidationException e2("validare");
        assert(std::string(e2.what()) == "validare");

        CarteNotFoundException e3("Ion");
        assert(std::string(e3.what()).find("Ion") != std::string::npos);

        DuplicateTitluException e4("Ion");
        assert(std::string(e4.what()).find("Ion") != std::string::npos);

        CosException e5("cos");
        assert(std::string(e5.what()) == "cos");
    }

    void testSetteri() {
        Carte c{ "Ion", "Rebreanu", "roman", 1920 };
        c.setTitlu("Baltagul");
        assert(c.getTitlu() == "Baltagul");
        c.setAutor("Sadoveanu");
        assert(c.getAutor() == "Sadoveanu");
        c.setGen("nuvela");
        assert(c.getGen() == "nuvela");
        c.setAnAparitie(1930);
        assert(c.getAnAparitie() == 1930);
    }

    void testCopyConstructor() {
        Carte c1{ "Ion", "Rebreanu", "roman", 1920 };
        Carte c2{ c1 };
        assert(c2.getTitlu() == "Ion");
        assert(c2.getAutor() == "Rebreanu");
    }

    void testServiceCauta() {
        RepoMemorie repo;
        Service service{ repo };
        service.adaugaCarte("Ion", "Rebreanu", "roman", 1920);

        const Carte& c = service.cautaCarte("Ion");
        assert(c.getTitlu() == "Ion");

        bool caught = false;
        try { service.cautaCarte("Inexistent"); }
        catch (const CarteNotFoundException&) { caught = true; }
        assert(caught);
    }


    //---


    void testUndoAdauga() {
        RepoMemorie repo;
        Service service{ repo };
        service.adaugaCarte("Ion", "Rebreanu", "roman", 1920);
        assert(service.getCarti().size() == 1);

        service.undo();
        assert(service.getCarti().empty());
    }

    void testUndoSterge() {
        RepoMemorie repo;
        Service service{ repo };
        service.adaugaCarte("Ion", "Rebreanu", "roman", 1920);
        service.stergeCarte("Ion");
        assert(service.getCarti().empty());

        service.undo();
        assert(service.getCarti().size() == 1);
        assert(service.getCarti().at(0).getTitlu() == "Ion");
    }

    void testUndoModifica() {
        RepoMemorie repo;
        Service service{ repo };
        service.adaugaCarte("Ion", "Rebreanu", "roman", 1920);
        service.modificaCarte("Ion", "Ion nou", "Rebreanu", "roman", 2000);
        assert(service.getCarti().at(0).getTitlu() == "Ion nou");

        service.undo();
        assert(service.getCarti().at(0).getTitlu() == "Ion");
    }

    void testUndoGol() {
        RepoMemorie repo;
        Service service{ repo };

        bool caught = false;
        try { service.undo(); }
        catch (const AppException&) { caught = true; }
        assert(caught);
    }

    void testRepoFisier() {

        repoFisier repoInexistent("fisier_inexistent_123.txt");
        assert(repoInexistent.getAll().empty());

        const string numeFisier = "test_carti_temp.txt";
        std::ofstream(numeFisier, std::ios::trunc).close();

        {
            repoFisier repo(numeFisier);
            repo.adauga({ "Ion", "Rebreanu", "roman", 1920 });
            repo.adauga({ "Baltagul", "Sadoveanu", "roman", 1930 });
            assert(repo.getAll().size() == 2);
        }

        {
            repoFisier repo2(numeFisier);
            assert(repo2.getAll().size() == 2);
            assert(repo2.getAll().at(0).getTitlu() == "Ion");

            repo2.sterge("Ion");
            assert(repo2.getAll().size() == 1);
        }

        {
            repoFisier repo3(numeFisier);
            assert(repo3.getAll().size() == 1);
            assert(repo3.getAll().at(0).getTitlu() == "Baltagul");

            repo3.modifica("Baltagul", { "Baltagul nou", "Sadoveanu", "roman", 1931 });
        }

        {
            repoFisier repo4(numeFisier);
            assert(repo4.getAll().at(0).getTitlu() == "Baltagul nou");
        }

        std::remove(numeFisier.c_str());
    }

    void testRepoLab() {
        // cu probabilitate 0 - nu arunca niciodata exceptie
        RepoLab repo(0.0);
        repo.adauga({ "Ion", "Rebreanu", "roman", 1920 });
        repo.adauga({ "Baltagul", "Sadoveanu", "roman", 1930 });
        assert(repo.getAll().size() == 2);

        const auto& c = repo.cauta("Ion");
        assert(c.getTitlu() == "Ion");

        auto filt = repo.filtreazaDupaTitlu("Ion");
        assert(filt.size() == 2);

        auto filtAn = repo.filtreazaDupaAn(1920);
        assert(filtAn.size() == 1);

        repo.modifica("Ion", { "Ion nou", "Rebreanu", "roman", 2000 });
        assert(repo.getAll().at(0).getTitlu() == "Ion nou"
            || repo.getAll().at(1).getTitlu() == "Ion nou");

        repo.sterge("Baltagul");
        assert(repo.getAll().size() == 1);

        bool caught = false;
        try { repo.adauga({ "Ion nou", "X", "roman", 1920 }); }
        catch (const DuplicateTitluException&) { caught = true; }
        assert(caught);

        caught = false;
        try { repo.sterge("Inexistent"); }
        catch (const CarteNotFoundException&) { caught = true; }
        assert(caught);

        caught = false;
        try { repo.modifica("Inexistent", { "X", "X", "roman", 1920 }); }
        catch (const CarteNotFoundException&) { caught = true; }
        assert(caught);

        caught = false;
        try { repo.cauta("Inexistent"); }
        catch (const CarteNotFoundException&) { caught = true; }
        assert(caught);

        // cu probabilitate 1 - arunca intotdeauna exceptie
        RepoLab repoSigur(1.0);
        caught = false;
        try { repoSigur.adauga({ "Ion", "Rebreanu", "roman", 1920 }); }
        catch (const RepoLabException&) { caught = true; }
        assert(caught);

        caught = false;
        try { repoSigur.sterge("Ion"); }
        catch (const RepoLabException&) { caught = true; }
        assert(caught);

        caught = false;
        try { repoSigur.modifica("Ion", { "X", "X", "roman", 1920 }); }
        catch (const RepoLabException&) { caught = true; }
        assert(caught);

        caught = false;
        try { repoSigur.getAll(); }
        catch (const RepoLabException&) { caught = true; }
        assert(caught);

        caught = false;
        try { repoSigur.cauta("Ion"); }
        catch (const RepoLabException&) { caught = true; }
        assert(caught);

        caught = false;
        try { repoSigur.filtreazaDupaTitlu("Ion"); }
        catch (const RepoLabException&) { caught = true; }
        assert(caught);

        caught = false;
        try { repoSigur.filtreazaDupaAn(1920); }
        catch (const RepoLabException&) { caught = true; }
        assert(caught);
    }

    void testRepoMemorie() {
        RepoMemorie repo;
        repo.adauga({ "Ion", "Rebreanu", "roman", 1920 });
        assert(repo.getAll().size() == 1);

        bool caught = false;
        try { repo.adauga({ "Ion", "Rebreanu", "roman", 1920 }); }
        catch (const DuplicateTitluException&) { caught = true; }
        assert(caught);
    }

} // namespace

void testAll() {
    testDomeniu();
    testRepoAdauga();
    testRepoSterge();
    testRepoModifica();
    testRepoCauta();
    testRepoFiltrare();
    testRepoExceptii();
    testServiceAdauga();
    testServiceSterge();
    testServiceModifica();
    testServiceFiltrare();
    testServiceSortare();
    testServiceValidare();
    testServicePopuleaza();
    testCosAdaugaSiGoleste();
    testCosGenereaza();
    testCosExport();
    testCosGetters();
    testExceptii();
    testSetteri();
    testCopyConstructor();
    testServiceCauta();
    testUndoAdauga();
    testUndoSterge();
    testUndoModifica();
    testUndoGol();
    testRepoFisier();
}