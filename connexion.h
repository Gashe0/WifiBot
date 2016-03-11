#ifndef CONNEXION_H
#define CONNEXION_H

#include <QString>
#include <winsock2.h> //#include <sys/socket.h>
#include <iostream>
#include <QTcpSocket>
#include <QAbstractSocket>


using namespace std;

class Connexion : public QObject
{
    Q_OBJECT
public:
    Connexion(QObject*);
    Connexion(QObject*,QString,QString);

    void doConnect();
    setAdresse(QString);
    setPort(QString);
private:
    QByteArray buf;
    QTcpSocket *socket;
    const char* adresse;
    int port;

    quint16 vitesse;

signals:

public slots:
    void connected();
    void disconnected();
    void bytesWritten(qint64 bytes);
    void readyRead();
};

#endif // CONNEXION_H
