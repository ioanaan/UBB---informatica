#pragma once
#include "repoMemorie.h"

class ActiuneUndo {
public:
    virtual void doUndo() = 0;
    virtual ~ActiuneUndo() = default;
};

class UndoAdauga : public ActiuneUndo {
private:
    Repo& repo;
    Carte carteAdaugata;
public:
    UndoAdauga(Repo& repo, const Carte& carte)
        : repo{ repo }, carteAdaugata{ carte } {
    }
    void doUndo() override {
        repo.sterge(carteAdaugata.getTitlu());
    }
};

class UndoSterge : public ActiuneUndo {
private:
    Repo& repo;
    Carte carteStearsa;
public:
    UndoSterge(Repo& repo, const Carte& carte)
        : repo{ repo }, carteStearsa{ carte } {
    }
    void doUndo() override {
        repo.adauga(carteStearsa);
    }
};

class UndoModifica : public ActiuneUndo {
private:
    Repo& repo;
    Carte carteVeche;
    string titluNou;
public:
    UndoModifica(Repo& repo, const Carte& carteVeche, const string& titluNou)
        : repo{ repo }, carteVeche{ carteVeche }, titluNou{ titluNou } {
    }
    void doUndo() override {
        repo.modifica(titluNou, carteVeche);
    }
};