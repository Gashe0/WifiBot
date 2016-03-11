#include "connexion.h"


Connexion::Connexion(QObject *parent):
    QObject(parent)
{
}

Connexion::Connexion(QObject *parent,QString adr, QString po):
    QObject(parent)
{
     adresse = adr.toStdString().c_str();
     port = po.toInt();
}

Connexion::setAdresse(QString adr){
    adresse = adr.toStdString().c_str();
}

Connexion::setPort( QString po){
    port = po.toInt();
}

void Connexion::doConnect()
{
     socket = new QTcpSocket(this);

     connect(socket, SIGNAL(connected()),this, SLOT(connected()));
     connect(socket, SIGNAL(disconnected()),this, SLOT(disconnected()));
     connect(socket, SIGNAL(bytesWritten(qint64)),this, SLOT(bytesWritten(qint64)));
     connect(socket, SIGNAL(readyRead()),this, SLOT(readyRead()));


     qDebug() << "connecting...";
         socket->connectToHost(adresse, port);

         if(!socket->waitForConnected(3000))
         {
             qDebug() << "Error: " << socket->errorString();
         }
}

void Connexion::connected()
{
    qDebug() << "connected...";

    buf.clear();
    buf.append((char)0xff);
    buf.append((char)0x07);
    buf.append((char)0x00);
    buf.append((char)0x00);
    buf.append((char)0x00);
    buf.append((char)0x00);

    //avancer
    buf.clear();
    buf.append((char)0xff);
    buf.append((char)0x07);
    buf.append((char)vitesse);
    buf.append((char)0x00);
    buf.append((char)vitesse);
    buf.append((char)0x00);


    socket->write(buf);
    socket->flush();
}

void Connexion::disconnected()
{
    qDebug() << "disconnected...";
}

void Connexion::bytesWritten(qint64 bytes)
{
    qDebug() << bytes << " bytes written...";
}

void Connexion::readyRead()
{
    qDebug() << "reading...";
    qDebug() << socket->readAll();
}
