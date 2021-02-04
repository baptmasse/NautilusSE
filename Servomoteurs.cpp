#include "Servomoteurs.h"

//#include <Arduino.h>

Servomoteurs::Servomoteurs()
{
    //ctor
}

Servomoteurs::Servomoteurs(int ESCpin, int NumeroServo)
{
    this->ESCpin = ESCpin;
    this->NumeroServo = NumeroServo;

    servo.attach(ESCpin);
    servo.writeMicroseconds(1500);//Arret du moteur
    delay(7000); //Attente de 7 secondes
}

Servomoteurs::~Servomoteurs()
{
    //dtor
}

void Servomoteurs::RotationAngle(double Angle)
{
    switch(NumeroServo)
    {
        case 1 : servo.write(Angle + 45);
                break;

        case 2 : servo.write(Angle + 135);
                break;

        case 3 : servo.write(Angle - 45);
                break;

        case 4 : servo.write(Angle + 225);
                break;
    }

    servo.write(Angle); //Angle compris entre 0 et 180
    delay(10);
}

void Servomoteurs::PositionUrgence()
{
    servo.write(90);
    delay(10);
}
