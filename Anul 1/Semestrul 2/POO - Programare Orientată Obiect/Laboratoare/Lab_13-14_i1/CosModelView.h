#pragma once
#include <QWidget>
#include <QListView>
#include <QVBoxLayout>
#include "CosModel.h"

class CosModelView : public QWidget {
private:
    Cos& cos;
    CosModel* model;
    QListView* listView = new QListView;

public:
    CosModelView(Cos& cos, QWidget* parent = nullptr);
};