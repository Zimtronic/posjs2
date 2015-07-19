#include "connection.h"
#include "tcpserver.h"

Connection::Connection(qintptr socketDescriptor, QObject *parent, TCPServer *ptr) :
    QObject(parent)
{
    this->serverPtr = ptr;

    socket = new QTcpSocket();
    if(!socket->setSocketDescriptor(socketDescriptor))
    {
        state = Disconnected;
        // something's wrong, we just emit a signal
        //        emit error(socket->error());
        //        return;
    }
    else
    {
        qDebug() << socketDescriptor << " New connection from" << socket->peerAddress();
        state = Connected;

        connect(socket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
        connect(socket, SIGNAL(disconnected()), this, SLOT(onDisconnected()));

        if(this->serverPtr->getPosdriver())
        {
            connect((QObject*)this->serverPtr->getPosdriver()->getBarcodeScannerInstance(), SIGNAL(packetRead(QString)), this, SLOT(sendBarcode(QString)));
            connect((QObject*)this->serverPtr->getPosdriver()->getMagneticScannerInstance(), SIGNAL(packetRead(QString)), this, SLOT(sendMagneticCode(QString)));
        }
    }
}

Connection::~Connection()
{
    socket->deleteLater();
}

void Connection::sendPacket(QString data)
{
    if(state == Connected)
    {
        qDebug() << "sendPacket --> " << data;
        socket->write(data.toStdString().c_str());
    }
}

void Connection::onReadyRead()
{
    QByteArray data = socket->readAll();

    QString aux = data;

    while (aux.indexOf("</end>") != -1)
    {
        int index = aux.indexOf("</end>");

        for (int i = 0; i < index; ++i)
        {
            command.append(aux.at(i));
        }
        this->onCommandArrived(command);
        command.clear();

        QString newS = aux;
        aux.clear();

        for (int i = index + 6; i < newS.length(); ++i)
        {
            aux.append(newS.at(i));
        }
    }
}

void Connection::onDisconnected()
{
    state = Disconnected;
    serverPtr->garbageCollector();
    socket->deleteLater();
    qDebug() <<"onDisconnected";
}

void Connection::sendBarcode(QString data)
{
    sendPacket("B"+data+"\n");
}

void Connection::sendMagneticCode(QString data)
{
    sendPacket("M"+data+"\n");
}

void Connection::onCommandArrived(QString command)
{
    qDebug() << "onCommandArrived: " << command;
    if((int)command[0].toLatin1() == 10)
    {
        command = command.right(command.length() - 1);
    }
    if(this->serverPtr->getPosdriver())
    {
        this->serverPtr->getPosdriver()->processESCPOSPrinterASCIICommand(command);
    }
    command.clear();
}

ConnectionState Connection::getState() const
{
    return state;
}

void Connection::setState(const ConnectionState &value)
{
    state = value;
}
