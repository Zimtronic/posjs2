#ifndef CONNECTION_H
#define CONNECTION_H

#include <QObject>
#include <QTcpSocket>

enum ConnectionState {
    Disconnected,
    Connected,
    ReadyForUse
};

class TCPServer;

class Connection : public QObject
{
    Q_OBJECT
public:
    explicit Connection(qintptr socketDescriptor, QObject *parent = 0, TCPServer *ptr = 0);
    ~Connection();

    void sendPacket(QString data);

    ConnectionState getState() const;
    void setState(const ConnectionState &value);

public slots:
    void onReadyRead();
    void onDisconnected();
    void sendBarcode(QString data);
    void sendMagneticCode(QString data);

private:
    QTcpSocket *socket;
    ConnectionState state;

    TCPServer *serverPtr;

    QString command;
    void onCommandArrived(QString command);
};

#endif // CONNECTION_H
