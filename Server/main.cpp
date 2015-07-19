#include <QCoreApplication>

#include "controller.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    qDebug() << "POSJSv2 INIT";
    Controller c;

    return a.exec();
}
