#include "tcpserver.h"
#include "connection.h"
#include "drivers/escposprinter.h"
#include "drivers/linuxusb.h"
#include "drivers/generichidscanner.h"

TCPServer::TCPServer(QObject *parent) :
    QTcpServer(parent)
{
    int port = 8888;

    if(!this->listen(QHostAddress::Any, port))
    {
        qDebug() << "Could not start server";
    }
    else
    {
        qDebug() << "Listening to port " << this->serverPort() << "...";

        printer = new ESCPOSPrinter();
        transport = new LinuxUSB();
        printer->setTransport(transport);

        hidBarcode = new GenericHIDScanner();
        hidBarcode->start();

        hidMagnetic = new GenericHIDScanner();
        hidMagnetic->setIdProduct(0x0001);
        hidMagnetic->setIdVendor(0x0801);
        hidMagnetic->start();
    }
}

void TCPServer::incomingConnection(qintptr socketDescriptor)
{
    Connection *conn = new Connection(socketDescriptor, 0, this);
    conn->setHidBarcode(hidBarcode);
    conn->setHidMagnetic(hidMagnetic);
    conn->setPrinter(printer);
    connections.append(conn);
}

void TCPServer::garbageCollector()
{
    qDebug() << "garbageCollector";
    for (int i = 0; i < connections.length(); ++i)
    {
        if(connections.at(i)->getState() == Disconnected)
        {
            qDebug() << "Disconnected....";
            Connection* c = connections.at(i);
            connections.removeAt(i);
            c->disconnect();
            delete c;
        }
    }
}

void TCPServer::publishPacket(QString packet)
{
    for (int i = 0; i < connections.length(); ++i)
    {
        connections.at(i)->sendPacket(packet);
    }
}
