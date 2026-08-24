#pragma once
#include "service.h"
#include "cos.h"

class UI {
private:
    Service& service;
    Cos cos;

    void afiseazaBiblioteca() const;
    void handleAdauga();
    void handleSterge();
    void handleModifica();
    void handleCauta();
    void handleFiltreaza();
    void handleSorteaza();
    void handlePopuleaza();
    void handleCos();
    void handleCosGoleste();
    void handleCosAdauga();
    void handleCosGenereaza();
    void handleCosExport();
    void afiseazaCos() const;
    void afiseazaMeniu() const;

public:
    UI(Service& service) noexcept : service{ service }, cos{ service } {}
    void run();
};