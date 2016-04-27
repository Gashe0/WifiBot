#include "roues.h"

Roues::Roues()
{
    this->left = 0;
    this->right = 0;
    this->forward = true;
    this->backward = false;
    this->speed = 0;
    this->pid = 0;
}

unsigned char Roues::getLeft()
{
    return this->left;
}

unsigned char Roues::getRight()
{
    return this->right;
}

bool Roues::getForward()
{
    return this->forward;
}

bool Roues::getBackward()
{
    return this->backward;
}

unsigned char Roues::getSpeed()
{
    return this->speed;
}

unsigned char Roues::getPID()
{
    return this->pid;
}


void Roues::setLeft(unsigned char v)
{
    if(v > 100)
        v = 100;

    this->left = v;
}

void Roues::setRight(unsigned char v)
{
    if(v > 100)
        v = 100;

    this->right = v;
}

void Roues::setForward(bool b)
{
    this->forward = b;
}

void Roues::setBackward(bool b)
{
    this->backward = b;
}

void Roues::setSpeed(unsigned char s)
{
     if(s > 100)
        s = 100;

    this->speed = s;
}

void Roues::setPID(int p)
{
    this->pid = (p==50) ? 0 : 8;
}

