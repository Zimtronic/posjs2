#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QTcpServer>
#include <QList>

class Connection;

class ITicketPrinter;
class ITransport;
class GenericHIDScanner;

class TCPServer : public QTcpServer
{
public:
    TCPServer(QObject *parent = 0);
     void garbageCollector();

public slots:
    void publishPacket(QString packet);

protected:
    void incomingConnection(qintptr socketDescriptor);

private:
    QList<Connection*> connections;

    ITicketPrinter *printer;
    ITransport * transport;
    GenericHIDScanner *hidBarcode;
    GenericHIDScanner *hidMagnetic;
};

#endif // TCPSERVER_H
