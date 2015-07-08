#ifndef COLLECTOR_H
#define COLLECTOR_H

#include <QObject>
#include <QTimer>

#include "tcpserver.h"

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject *parent = 0);

signals:

public slots:
    void onTimeOut();

private:
    TCPServer *server;
    QTimer *timer;
};

#endif // COLLECTOR_H
