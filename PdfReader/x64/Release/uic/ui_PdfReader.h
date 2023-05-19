/********************************************************************************
** Form generated from reading UI file 'PdfReader.ui'
**
** Created by: Qt User Interface Compiler version 6.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PDFREADER_H
#define UI_PDFREADER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PdfReaderClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *PdfReaderClass)
    {
        if (PdfReaderClass->objectName().isEmpty())
            PdfReaderClass->setObjectName("PdfReaderClass");
        PdfReaderClass->resize(600, 400);
        menuBar = new QMenuBar(PdfReaderClass);
        menuBar->setObjectName("menuBar");
        PdfReaderClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(PdfReaderClass);
        mainToolBar->setObjectName("mainToolBar");
        PdfReaderClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(PdfReaderClass);
        centralWidget->setObjectName("centralWidget");
        PdfReaderClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(PdfReaderClass);
        statusBar->setObjectName("statusBar");
        PdfReaderClass->setStatusBar(statusBar);

        retranslateUi(PdfReaderClass);

        QMetaObject::connectSlotsByName(PdfReaderClass);
    } // setupUi

    void retranslateUi(QMainWindow *PdfReaderClass)
    {
        PdfReaderClass->setWindowTitle(QCoreApplication::translate("PdfReaderClass", "PdfReader", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PdfReaderClass: public Ui_PdfReaderClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PDFREADER_H
