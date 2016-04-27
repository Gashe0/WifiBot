#include "camera.h"


// Initialisation des constantes
const QString Camera::G = QString("/?action=command&dest=0&plugin=0&id=10094852&group=1&value=200");
const QString Camera::D = QString("/?action=command&dest=0&plugin=0&id=10094852&group=1&value=-200");
const QString Camera::B = QString("/?action=command&dest=0&plugin=0&id=10094853&group=1&value=200");
const QString Camera::H = QString("/?action=command&dest=0&plugin=0&id=10094853&group=1&value=-200");
const QString Camera::SUP = QString("/?action=command&dest=0&plugin=0&id=168062211&group=1&value=3");


Camera::Camera()
{
    host = "127.0.0.1";
    error = false;
    img = QPixmap();

}

Camera::Camera(QString host)
{
    this->host = host;
    this->s = new QTcpSocket();
    move = this->SUP;
    error = false;
    img = QPixmap();

}

Camera::~Camera()
{
    delete s;
}

void Camera::setMove(char v)
{
    switch(v)
    {
    case 'H':
        move = this->H;
    break;
    case 'G':
        move = this->G;
    break;
    case 'D':
        move = this->D;
    break;
    case 'B':
        move = this->B;
    break;
    default:
        move = this->SUP;
    break;
    }
}


void Camera::start()
{
    s->connectToHost(this->host, 8080);
    if(s->waitForConnected(200))
    {

        QString get = "GET "+this->move+" HTTP/1.0\r\n";
        QString host = "Host: "+this->host+"\r\n";
        QString end="\r\n";

        s->write(get.toStdString().c_str());
        s->write(host.toStdString().c_str());
        s->write(end.toStdString().c_str());

        s->disconnectFromHost();
    }

}


QPixmap Camera::getPixmap()
{
    return img;
}

void Camera::cameraError(QNetworkReply::NetworkError e)
{
    error = true;

    img = QPixmap(":/camera/img/cameraError.png");
}

void Camera::cameraSaveImg()
{
    if(!error)
    {
        QNetworkReply *r = qobject_cast<QNetworkReply*>(sender());
        img = QPixmap();
        img.loadFromData(r->readAll(), "JPG");
        r->deleteLater();
    }
}

