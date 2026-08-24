/********************************************************************************
** Form generated from reading UI file 'Lab_1314_i1.ui'
**
** Created by: Qt User Interface Compiler version 6.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LAB_1314_I1_H
#define UI_LAB_1314_I1_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Lab_1314_i1Class
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Lab_1314_i1Class)
    {
        if (Lab_1314_i1Class->objectName().isEmpty())
            Lab_1314_i1Class->setObjectName("Lab_1314_i1Class");
        Lab_1314_i1Class->resize(600, 400);
        menuBar = new QMenuBar(Lab_1314_i1Class);
        menuBar->setObjectName("menuBar");
        Lab_1314_i1Class->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Lab_1314_i1Class);
        mainToolBar->setObjectName("mainToolBar");
        Lab_1314_i1Class->addToolBar(mainToolBar);
        centralWidget = new QWidget(Lab_1314_i1Class);
        centralWidget->setObjectName("centralWidget");
        Lab_1314_i1Class->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(Lab_1314_i1Class);
        statusBar->setObjectName("statusBar");
        Lab_1314_i1Class->setStatusBar(statusBar);

        retranslateUi(Lab_1314_i1Class);

        QMetaObject::connectSlotsByName(Lab_1314_i1Class);
    } // setupUi

    void retranslateUi(QMainWindow *Lab_1314_i1Class)
    {
        Lab_1314_i1Class->setWindowTitle(QCoreApplication::translate("Lab_1314_i1Class", "Lab_1314_i1", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Lab_1314_i1Class: public Ui_Lab_1314_i1Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LAB_1314_I1_H
