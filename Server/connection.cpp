#include "connection.h"
#include "drivers/escposprinter.h"
#include "drivers/generichidscanner.h"
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
        qDebug() << socketDescriptor << " new connection";
        state = Connected;

        connect(socket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
        connect(socket, SIGNAL(disconnected()), this, SLOT(onDisconnected()));
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
    qDebug() <<"onReadyRead";
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

    qDebug() << " Data in: " << data;
}

void Connection::onDisconnected()
{
    state = Disconnected;
    serverPtr->garbageCollector();
    socket->deleteLater();
    qDebug() <<"onDisconnected";
}

GenericHIDScanner *Connection::getHidMagnetic() const
{
    return hidMagnetic;
}

void Connection::setHidMagnetic(GenericHIDScanner *value)
{
    hidMagnetic = value;
    connect(hidMagnetic, SIGNAL(packetRead(QString)), this, SLOT(sendMagneticCode(QString)));
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
    QString d;
    QStringList l;

    switch ((int)command[0].toLatin1())
    {
        case 'i':
            printer->init();
            break;
        case '0':
            printer->printRawText(command.right(command.length()-1));
            break;
        case '1':
            printer->cutPaper(command[1] == '1');
            break;
        case '2':
            printer->sendPulseToCashDrawer(int(command[1].toLatin1() - 48));
            break;
        case '3':
            d = command.right(command.length()-1);
            l = d.split(':');
            if (l.length() == 5)
            {
                printer->setTextProperties(l.at(0).toInt(), l.at(1).toInt(),
                                           l.at(2).toInt(), l.at(3).toInt(),
                                           l.at(4).toInt());
            }
            break;
        case '4':
            d = command.right(command.length()-1);
            printer->feedControl(d.toInt());
            break;
        case '5':
            printer->init();
            break;
        case '6':
            printer->init();
            break;
        case '7':
            printer->init();
            break;
        case '8':
            printer->init();
            break;
        default:
            qDebug() << "default: " << (int)command[0].toLatin1();
            break;
    }

    command.clear();
}

GenericHIDScanner *Connection::getHidBarcode() const
{
    return hidBarcode;
}

void Connection::setHidBarcode(GenericHIDScanner *value)
{
    hidBarcode = value;
    connect(hidBarcode, SIGNAL(packetRead(QString)), this, SLOT(sendBarcode(QString)));
}

ITicketPrinter *Connection::getPrinter() const
{
    return printer;
}

void Connection::setPrinter(ITicketPrinter *value)
{
    printer = value;
}

ConnectionState Connection::getState() const
{
    return state;
}

void Connection::setState(const ConnectionState &value)
{
    state = value;
}
