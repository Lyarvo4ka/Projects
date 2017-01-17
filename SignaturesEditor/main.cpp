#include "signatureseditor.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SignaturesEditor w;
    w.show();
    return a.exec();
}
