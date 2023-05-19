#include "PdfReaderWindow.h"
#include <QtWidgets/QApplication>
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PdfReaderWindow w;
    w.show();
    return a.exec();
}
