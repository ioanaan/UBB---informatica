#pragma once
#include "service.h"

class UI 
{
private:
    Service& service;

    void afiseazaMeniu() const;
    void afiseazaCarti(const MyVector<Carte>& carti) const;

    void handleAdauga();
    void handleSterge();
    void handleModifica();
    void handleCauta();
    void handleFiltreaza();
    void handleSorteaza();

public:
    UI(Service& service) noexcept;
    void run();
};