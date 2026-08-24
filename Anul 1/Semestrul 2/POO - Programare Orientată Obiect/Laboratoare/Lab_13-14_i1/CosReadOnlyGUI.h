#pragma once
#include <QWidget>
#include <QPainter>
#include "cos.h"

class CosReadOnlyGUI : public QWidget, public Observer {
private:
    Cos& cos;

public:
    CosReadOnlyGUI(Cos& cos, QWidget* parent = nullptr);
    ~CosReadOnlyGUI();

    void update() override;

protected:
    void paintEvent(QPaintEvent* ev) override;
};