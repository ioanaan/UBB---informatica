#pragma once
#include <QAbstractListModel>
#include "cos.h"

class CosModel : public QAbstractListModel, public Observer {
private:
    Cos& cos;

public:
    CosModel(Cos& cos, QObject* parent = nullptr);
    ~CosModel();

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

    // observer
    void update() override;
};