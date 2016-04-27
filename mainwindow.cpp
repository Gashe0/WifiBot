#include "mainwindow.h"
#include "connexion.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    timerTrame = new QTimer(this);
    timerCamera = new QTimer(this);

    r = Roues();

    s = new Connexion();

    connect(timerTrame, SIGNAL(timeout()), this, SLOT(generationEnvoiTrame()));
    connect(timerTrame, SIGNAL(timeout()), this, SLOT(recupererTrame()));

    connect(this, SIGNAL(newCapteurValue(Capteur)), this, SLOT(capteurAffichage(Capteur)));

    connect(timerCamera, SIGNAL(timeout()), this, SLOT(requestForCameraImage()));
    connect(timerCamera, SIGNAL(timeout()), this, SLOT(getCameraImage()));

    // Pour contrer le bug de setupUI de qt...
    //ui->dw_sensor->setUI();
    //this->tabifyDockWidget(ui->dw_sensor, ui->dw_connection);



}

MainWindow::~MainWindow()
{
    delete s;
    delete ui;
}

void MainWindow::stopMoveValues()
{
    r.setLeft(0);
    r.setRight(0);
    r.setSpeed(0);
}
void MainWindow::setMoveCamera(char v)
{
    if(v != '0')
    {
        c->setMove(v);
        c->start();
    }
}

void MainWindow::generationEnvoiTrame()
{
    //qDebug() << "\nGénération de trame avec pour paramètres :\n\tDifférentiel:\n\t\tLeft % : " << roues.getLeft() << "\n\t\tRight % : " << roues.getRight() << "\nSpeed % : " << roues.getSpeed()  << "\n\tSens : " << roues.getForward() << "\n\t";
    s->generateRequest(r);
}

void MainWindow::capteurAffichage(Capteur c){

    ui->lcdNumber_8->display(c.getOdoL());
    ui->lcdNumber_9->display(c.getOdoR());
    ui->lcdNumber_2->display(c.getSpeedL());
    ui->lcdNumber_3->display(c.getSpeedR());
    ui->lcdNumber_4->display(c.getADC1());
    ui->lcdNumber_5->display(c.getADC1());
    ui->lcdNumber_6->display(c.getADC3());
    ui->lcdNumber_7->display(c.getADC4());

}

void MainWindow::recupererTrame()
{
    Capteur c;
    QByteArray bu = s->getData();

        if(bu.size() > 17)
        {
            quint32 odoL,odoR;
            qint16 speedL,speedR;
            quint8 battery,adc0,adc1,adc3,adc4,current,version;

            // Left
            speedL = bu.at(0)+(bu.at(1)<<8);
            battery = bu.at(2);
            adc4 = bu.at(3);
            adc3 = bu.at(4);
            odoL = bu.at(5)+(bu.at(6)<<8)+(bu.at(7)<<16)+(bu.at(8)<<24);

            // Right
            speedR = bu.at(9)+(bu.at(10)<<8);
            adc0 = bu.at(11);
            adc1 = bu.at(12);
            odoR = bu.at(13)+(bu.at(14)<<8)+(bu.at(15)<<16)+(bu.at(16)<<24);
            current = bu.at(17);
            version = bu.at(18);

            // MAJ de la progresse BAR. ON suppose que la batterie est déchargée à 11.7 V
            c = Capteur(odoL, odoR, speedL, speedR, battery, adc0, adc1, adc3, adc4, current, version);

            if(c.getBattery() == 18){
                ui->progressBar->hide();
                ui->label_4->setText("Batterie en Charge");
            }else{
                ui->progressBar->setValue((c.getBattery()*100/13));
                ui->label_4->setText("Batterie :");
            }

            //ui->statusBar->showMessage("Etat de la batterie : "+QString().setNum(s.getBattery())+" V");
            //ui->statusBar->findChild<QProgressBar*>()->setValue((s.getBattery()-11.7)*100);


            emit newCapteurValue(c);
        }

}

void MainWindow::requestForCameraImage()
{
    const QUrl url = QUrl("http://"+ui->textEdit->toPlainText()+":8080/?action=snapshot&n=7");
    const QNetworkRequest requete(url);

    QNetworkAccessManager *m = new QNetworkAccessManager;
    QNetworkReply *req = m->get(requete);

    connect(req, SIGNAL(error(QNetworkReply::NetworkError)), c, SLOT(cameraError(QNetworkReply::NetworkError)));
    connect(req, SIGNAL(finished()), c, SLOT(cameraSaveImg()));

}

void MainWindow::getCameraImage()
{
    ui->l_camera->setPixmap(c->getPixmap());
}

void MainWindow::on_pushButton_clicked()//Connexion
{
    s->connectTo(ui->textEdit->toPlainText(),ui->textEdit_2->toPlainText().toInt(0,10));
    //ui->webView->load(QUrl(QString("http://"+ui->textEdit->toPlainText()+":8080/?action=snapshot&n=7")));
    c = new Camera(ui->textEdit->toPlainText());
    timerTrame->start(50);
    timerCamera->start(100);
}

void MainWindow::on_pushButton_2_clicked()//Deconnexion
{
    s->disconnect();
    cout<<"Déconnecté";
}

void MainWindow::on_pushButton_3_pressed()//Avance
{
    r.setBackward(0);
    r.setForward(1);
    r.setLeft(100);
    r.setRight(100);
    r.setSpeed(200);

    s->generateRequest(r);
}

void MainWindow::on_pushButton_5_pressed()//Droite
{
    r.setBackward(0);
    r.setForward(1);
    r.setLeft(200);
    r.setRight(0);
    r.setSpeed(200);

    s->generateRequest(r);
}

void MainWindow::on_pushButton_4_pressed()//Reculer
{
    r.setBackward(1);
    r.setForward(0);
    r.setLeft(100);
    r.setRight(100);
    r.setSpeed(200);

    s->generateRequest(r);
}

void MainWindow::on_pushButton_6_pressed()//Gauche
{
    r.setBackward(0);
    r.setForward(1);
    r.setLeft(0);
    r.setRight(200);
    r.setSpeed(200);

    s->generateRequest(r);
}

void MainWindow::on_pushButton_3_released()//Avance
{
    this->stopMoveValues();
}

void MainWindow::on_pushButton_5_released()//Droite
{
    this->stopMoveValues();
}

void MainWindow::on_pushButton_4_released()//Reculer
{
    this->stopMoveValues();
}

void MainWindow::on_pushButton_6_released()//Gauche
{
    this->stopMoveValues();
}

void MainWindow::on_pushButton_8_pressed()//CAM MONTER
{
    this->setMoveCamera('H');
}

void MainWindow::on_pushButton_7_pressed()//CAM DROITE
{
    this->setMoveCamera('D');
}

void MainWindow::on_pushButton_10_pressed()//CAM GAUCHE
{
    this->setMoveCamera('G');
}

void MainWindow::on_pushButton_9_pressed()//CAM DESCENDRE
{
    this->setMoveCamera('B');
}


void MainWindow::on_pushButton_8_released()
{
    this->setMoveCamera('0');
}

void MainWindow::on_pushButton_7_released()
{
    this->setMoveCamera('0');
}

void MainWindow::on_pushButton_10_released()
{
    this->setMoveCamera('0');
}

void MainWindow::on_pushButton_9_released()
{
    this->setMoveCamera('0');
}

