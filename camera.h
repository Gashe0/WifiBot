#ifndef CAMERA_H
#define CAMERA_H

#include <QTcpSocket>
#include <QTimer>
#include <QObject>
#include <QPixmap>

#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QUrl>

class Camera: public QObject
{
    Q_OBJECT

public:
    explicit Camera();
    explicit Camera(QString host);
    ~Camera();

    void setMove(char v);

    void start();

     QPixmap getPixmap();
    void setPositionHC(int p);
    void changePosition();
    int getPositionHC();

    static const QString G;
    static const QString D;
    static const QString H;
    static const QString B;
    static const QString SUP;

public slots:
    void cameraError(QNetworkReply::NetworkError);
    void cameraSaveImg();

private:

    QString move;


    QTcpSocket* s;
    QString host;
    QPixmap img;

    bool error;
};
#endif // CAMERA_H
