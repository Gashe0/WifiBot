#include "capteur.h"

Capteur::Capteur()
{

}

Capteur::Capteur(quint32 odoL, quint32 odoR, qint16 speedL, qint16 speedR, quint8 battery, quint8 adc0, quint8 adc1, quint8 adc3, quint8 adc4, quint8 current, quint8 version)
{
    float tickper =  20.0f;

    this->odoL = ((float) odoL);// /TICKPERMETER;
    this->odoR = ((float) odoR);// /TICKPERMETER;

    this->speedL = ((float) speedL);//*tickper/TICKPERMETER;
    this->speedR = ((float) speedR);//*tickper/TICKPERMETER;

    this->battery = (float) battery*BATTERYCURRENTRATIO;
    this->adc0 = (float) adc0;//*ADCRATIO;
    this->adc1 = (float) adc1;//*ADCRATIO;
    this->adc3 = (float) adc3;//*ADCRATIO;
    this->adc4 = (float) adc4;//*ADCRATIO;

    this->current = (float) current*BATTERYCURRENTRATIO;
    this->version = version;
}

Capteur::~Capteur()
{

}

float Capteur::getOdoL()
{
    return this->odoL;
}

float Capteur::getOdoR()
{
    return this->odoR;
}

float Capteur::getSpeedL()
{
    return this->speedL;
}

float Capteur::getSpeedR()
{
    return this->speedR;
}

float Capteur::getBattery()
{
    return this->battery;
}

float Capteur::getADC0()
{
    return this->adc0;
}
float Capteur::getADC1()
{
    return this->adc1;
}
float Capteur::getADC3()
{
    return this->adc3;
}
float Capteur::getADC4()
{
    return this->adc4;
}

float Capteur::getCurrent()
{
    return this->current;
}

quint8 Capteur::getVersion()
{
    return this->version;
}
