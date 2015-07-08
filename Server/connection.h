#ifndef CONNECTION_H
#define CONNECTION_H

#include <QObject>
#include <QTcpSocket>

enum ConnectionState {
    Disconnected,
    Connected,
    ReadyForUse
};

class ITicketPrinter;
class ITransport;
class GenericHIDScanner;
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

    ITicketPrinter *getPrinter() const;
    void setPrinter(ITicketPrinter *value);

    GenericHIDScanner *getHidBarcode() const;
    void setHidBarcode(GenericHIDScanner *value);

    GenericHIDScanner *getHidMagnetic() const;
    void setHidMagnetic(GenericHIDScanner *value);

signals:

public slots:
    void onReadyRead();
    void onDisconnected();
    void sendBarcode(QString data);
    void sendMagneticCode(QString data);

private:
    QTcpSocket *socket;
    ConnectionState state;

    ITicketPrinter *printer;
    GenericHIDScanner *hidBarcode;
    GenericHIDScanner *hidMagnetic;

    TCPServer *serverPtr;

    QString command;
    void onCommandArrived(QString command);
};

#endif // CONNECTION_H
