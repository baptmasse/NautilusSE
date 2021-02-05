#include "Moteurs.h"

#include <Arduino.h>

Moteurs::Moteurs()
{
    //ctor
}

Moteurs::~Moteurs()
{
    //dtor
}

Moteurs::Moteurs(int ESCpin, int NumeroMoteur)
{
    this->ESCpin = ESCpin;
    this->NumeroMoteur = NumeroMoteur;

    servo.attach(ESCpin);
    servo.writeMicroseconds(1500);//Arret du moteur
    delay(7000); //Attente de 7 secondes
}

void Moteurs::Rotation(double Speed, bool Sens) //Sens trigo : 0 ; Sens non trigo : 1
{
    //Echelle de 1100 à 1900 ; vitesse nulle de 1468 à 1532

    int MicroSC; // Vitesse convertie

    //Code de conversion de la vitesse de m/s à l'échelle (1100 à 1900)
    //Tension prise en référence : 14 V

    if(Speed!=0)
    {
        if(Sens == 0)
        {
            MicroSC = map(Speed,0,20,1532,1900); //Changement d'échelle de valeur
        }
        else
        {
            MicroSC = map(Speed,0,20,1100,1468);
        }
    }
    else
    {
        MicroSC = 1500;
    }

    servo.writeMicroseconds(MicroSC);
    delay(100);
}

void Moteurs::UrgentStop()
{
    servo.writeMicroseconds(1500);
    delay(100);
}
