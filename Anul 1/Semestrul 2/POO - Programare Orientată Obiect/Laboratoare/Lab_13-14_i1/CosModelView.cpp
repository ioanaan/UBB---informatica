#include "CosModelView.h"

CosModelView::CosModelView(Cos& cos, QWidget* parent)
    : QWidget(parent), cos{ cos } {

    model = new CosModel(cos, this);
    listView->setModel(model);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(listView);

    setWindowTitle("Cos Model View");
    resize(400, 300);
}