#include "CosReadOnlyGUI.h"

CosReadOnlyGUI::CosReadOnlyGUI(Cos& cos, QWidget* parent)
    : QWidget(parent), cos{ cos } {
    cos.addObserver(this);
    setWindowTitle("Cos Read Only");
    resize(400, 400);
}

CosReadOnlyGUI::~CosReadOnlyGUI() {
    cos.removeObserver(this);
}

void CosReadOnlyGUI::update() {
    repaint();  
}

void CosReadOnlyGUI::paintEvent(QPaintEvent* ev) {
    QPainter p(this);

    int n = static_cast<int>(cos.getNrCarti());

    for (int i = 0; i < n; i++) {
        int x = (i % 5) * 70 + 20;
        int y = (i / 5) * 70 + 20;
        p.setBrush(Qt::blue);
        p.drawEllipse(x, y, 50, 50);
    }
}