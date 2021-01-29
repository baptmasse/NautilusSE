#ifndef SERVOMOTEURS_H
#define SERVOMOTEURS_H

#include <Arduino.h>
#include <Servo.h>

class Servomoteurs
{
    public:
        Servomoteurs();
        Servomoteurs(int ESCpin, int NumeroServo);
        virtual ~Servomoteurs();

        void RotationAngle(double Angle);
        void PositionUrgence();

    protected:

    private:
        int NumeroServo;
        int ESCpin; //pin auxquels sont rattachés les ESC
        Servo servo;
};

#endif // SERVOMOTEURS_H
