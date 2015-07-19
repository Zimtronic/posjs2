#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QTcpServer>
#include <QList>

#include "posdriverinterface.h"

class Connection;

class TCPServer : public QTcpServer
{
public:
    TCPServer(QObject *parent = 0);
    void garbageCollector();

    POSDriverInterface *getPosdriver() const;

public slots:
    void publishPacket(QString packet);

protected:
    void incomingConnection(qintptr socketDescriptor);

private:
    QList<Connection*> connections;

    void loadDriver();
    POSDriverInterface *posdriver;
};

#endif // TCPSERVER_H
