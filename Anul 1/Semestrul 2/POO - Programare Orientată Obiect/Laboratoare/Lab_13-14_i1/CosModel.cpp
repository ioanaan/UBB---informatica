#include "CosModel.h"

CosModel::CosModel(Cos& cos, QObject* parent)
    : QAbstractListModel(parent), cos{ cos } {
    cos.addObserver(this);
}

CosModel::~CosModel() {
    cos.removeObserver(this);
}

int CosModel::rowCount(const QModelIndex& parent) const {
    return static_cast<int>(cos.getNrCarti());
}

QVariant CosModel::data(const QModelIndex& index, int role) const {
    if (!index.isValid()) return QVariant();

    const Carte& c = cos.getCarti().at(index.row());

    if (role == Qt::DisplayRole) {
        return QString::fromStdString(
            c.getTitlu() + " | " + c.getAutor() +
            " | " + c.getGen() + " | " +
            std::to_string(c.getAnAparitie())
        );
    }
    return QVariant();
}

void CosModel::update() {
    emit layoutAboutToBeChanged();
    emit layoutChanged();
}