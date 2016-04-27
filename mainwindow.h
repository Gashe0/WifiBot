#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <roues.h>
#include <camera.h>
#include <connexion.h>
#include <capteur.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void newCapteurValue(Capteur);

private slots:
    void stopMoveValues();
    void generationEnvoiTrame();
    void requestForCameraImage();
    void getCameraImage();
    void recupererTrame();
    void capteurAffichage(Capteur);

    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_pressed();
    void on_pushButton_5_pressed();
    void on_pushButton_4_pressed();
    void on_pushButton_6_pressed();
    void on_pushButton_3_released();
    void on_pushButton_5_released();
    void on_pushButton_4_released();
    void on_pushButton_6_released();

    //Bouton Camera
    void on_pushButton_8_pressed();
    void on_pushButton_7_pressed();
    void on_pushButton_10_pressed();
    void on_pushButton_9_pressed();
    void on_pushButton_8_released();
    void on_pushButton_7_released();
    void on_pushButton_10_released();
    void on_pushButton_9_released();

private:
    void setButtonEnable(bool e);
    void setMoveCamera(char v);

    Ui::MainWindow *ui;

    Roues r;
    Camera* c;
    QTimer* timerTrame;
    QTimer* timerCamera;
    Connexion* s;
};

#endif // MAINWINDOW_H
