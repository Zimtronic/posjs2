#include "controller.h"

Controller::Controller(QObject *parent) :
    QObject(parent)
{
    server = new TCPServer();
    timer = new QTimer(this);
    //connect(timer, SIGNAL(timeout()), this, SLOT(onTimeOut()));
    //timer->start(100);
}

void Controller::onTimeOut()
{
    server->publishPacket("hola mundo cruel");
}
