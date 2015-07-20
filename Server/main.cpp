#include <QApplication>

#include "controller.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Q_INIT_RESOURCE(resource);

    qDebug() << "POSJSv2 INIT";
    Controller c;

    return a.exec();
}
