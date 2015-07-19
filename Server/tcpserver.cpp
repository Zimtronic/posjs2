#include "tcpserver.h"
#include "connection.h"

#include <QDir>
#include <QPluginLoader>

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
        qDebug() << "Server listening on port: " << this->serverPort();

        loadDriver();
    }
}

void TCPServer::loadDriver()
{
    QPluginLoader pluginLoader("libposjs.so");
    pluginLoader.load();
    QObject *plugin = pluginLoader.instance();

    posdriver = qobject_cast<POSDriverInterface*>(plugin);

    if(posdriver)
    {
        qDebug() << "libposjs OK...!!!";
    }
    else
    {
        qDebug() << "libposjs not found...!!!";
    }
}

POSDriverInterface *TCPServer::getPosdriver() const
{
    return posdriver;
}

void TCPServer::incomingConnection(qintptr socketDescriptor)
{
    Connection *conn = new Connection(socketDescriptor, 0, this);
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
