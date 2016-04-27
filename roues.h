#ifndef ROUES_H
#define ROUES_H


class Roues
{
public:
    Roues();

    unsigned char getLeft();
    unsigned char getRight();
    bool getForward();
    bool getBackward();
    unsigned char getSpeed();
    unsigned char getPID();

    void setLeft(unsigned char v);
    void setRight(unsigned char v);
    void setForward(bool b);
    void setBackward(bool b);
    void setSpeed(unsigned char s);
    void setPID(int p);

private:

    unsigned char left; // Pourcentage de rotation des roues gauches (diffÃ©rentiel statique).
    unsigned char right; // Pourcentage de rotation des roues droites (diffÃ©rentiel statique).
    bool forward; // Sens de marche : 1 en avant
    bool backward; // 0 en arrière
    unsigned char speed; // Pourcentage de puissance allouÃ©e aux roues.
    unsigned char pid; // PID Ã  50ms = 8 ou 10ms = 0


};

#endif // ROUES_H
