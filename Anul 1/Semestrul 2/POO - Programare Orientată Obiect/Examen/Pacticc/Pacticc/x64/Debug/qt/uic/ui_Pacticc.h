/********************************************************************************
** Form generated from reading UI file 'Pacticc.ui'
**
** Created by: Qt User Interface Compiler version 6.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PACTICC_H
#define UI_PACTICC_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PacticcClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *PacticcClass)
    {
        if (PacticcClass->objectName().isEmpty())
            PacticcClass->setObjectName("PacticcClass");
        PacticcClass->resize(600, 400);
        menuBar = new QMenuBar(PacticcClass);
        menuBar->setObjectName("menuBar");
        PacticcClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(PacticcClass);
        mainToolBar->setObjectName("mainToolBar");
        PacticcClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(PacticcClass);
        centralWidget->setObjectName("centralWidget");
        PacticcClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(PacticcClass);
        statusBar->setObjectName("statusBar");
        PacticcClass->setStatusBar(statusBar);

        retranslateUi(PacticcClass);

        QMetaObject::connectSlotsByName(PacticcClass);
    } // setupUi

    void retranslateUi(QMainWindow *PacticcClass)
    {
        PacticcClass->setWindowTitle(QCoreApplication::translate("PacticcClass", "Pacticc", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PacticcClass: public Ui_PacticcClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PACTICC_H
