#pragma once
#include "service.h"
#include "cos.h"
#include "repoFisier.h"
#include "repoLab.h"
#include <memory>

class UI {
private:
    std::unique_ptr<Repo> repo;
    std::unique_ptr<Service> service;
    std::unique_ptr<Cos> cos;

    void alegeStorare();
    void afiseazaBiblioteca() const;
    void handleAdauga();
    void handleSterge();
    void handleModifica();
    void handleCauta();
    void handleFiltreaza();
    void handleSorteaza();
    void handlePopuleaza();
    void handleUndo();
    void handleCos();
    void handleCosGoleste();
    void handleCosAdauga();
    void handleCosGenereaza();
    void handleCosExport();
    void afiseazaCos() const;
    void afiseazaMeniu() const;

public:
    UI() = default;
    void run();
};