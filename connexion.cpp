#include "connexion.h"


Connexion::Connexion()
{
    this->socket = new QTcpSocket();
}

Connexion::~Connexion()
{
    delete socket;
}


bool Connexion::connectTo(QString host, int port)
{
    bool connected = true;

    qDebug() << "Demande de connexion :\n Host : " << host << "\nPort : " << port << "\n";

    socket->connectToHost(host, port);

    if(!socket->waitForConnected(5000))
        connected = false;

    return connected;
}

void Connexion::disconnect()
{
    socket->disconnectFromHost();
    delete socket;
}


void Connexion::generateRequest(Roues r)
{
    buf.clear();
    unsigned char fL, fR, char7 = 0;

    if(r.getForward())
    {
        if(r.getBackward())
            char7 = 160+64;
        else
            char7 = 240;
    }
    else
        char7 = 160;

    char7 += r.getPID();

    fL = r.getLeft()*r.getSpeed()/100*2.4;
    fR = r.getRight()*r.getSpeed()/100*2.4;

    buf.append((unsigned char)0xFF);
    buf.append((unsigned char)0x07);

    buf.append(fL);
    buf.append(fL >> 8);
    buf.append(fR);
    buf.append(fR >> 8);
    buf.append(char7);

    quint16 crc = crc16(buf,1);

    buf.append((char)(crc));
    buf.append((char)(crc>>8));

    socket->write(buf);
    socket->flush();
}

QByteArray Connexion::getData()
{
    if(socket->bytesAvailable() >= 21)
        return socket->readAll();
    else
        return QByteArray();
}

quint16 Connexion::crc16(QByteArray byteArray, int pos){
    unsigned char *data = (unsigned char* )byteArray.constData();
    quint16 crc = 0xFFFF;
    quint16 Polynome = 0xA001;
    quint16 Parity = 0;
    for(; pos < byteArray.length(); pos++){
        crc ^= *(data+pos);
        for (unsigned int CptBit = 0; CptBit <= 7 ; CptBit++){
            Parity= crc;
            crc >>= 1;
            if (Parity%2 == true) crc ^= Polynome;
        }
    }
    return crc;
}
