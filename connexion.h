#ifndef CONNEXION_H
#define CONNEXION_H

#include <QString>
#include <winsock2.h> //#include <sys/socket.h>
#include <iostream>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QTimer>


#include "roues.h"


using namespace std;

class Connexion : public QObject
{
    Q_OBJECT
public:
    Connexion();
    ~Connexion();
    bool connectTo(QString host, int port);
    void disconnect();
    void generateRequest(Roues r);
    QByteArray getData();
    quint16 crc16(QByteArray byteArray, int pos);

private:
    QByteArray buf;
    QTcpSocket *socket;
    const char* adresse;
    int port;

};

#endif // CONNEXION_H
