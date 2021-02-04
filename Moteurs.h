#ifndef MOTEURS_H
#define MOTEURS_H

//#include <Arduino.h>
//#include <Servo.h>

class Moteurs
{
    public:
        Moteurs();
        Moteurs(int ESCpin, int NumeroMoteur);
        virtual ~Moteurs();

        void Rotation(double Speed, bool Sens); //Vitesse entrée en m/s, sens : 1 pour avancer, 0 pour reculer (par rapport à l'avant du sous-marin)
        void UrgentStop();


    protected:

    private:
        int NumeroMoteur;
        int ESCpin; //pin auxquels sont rattachés les ESC
        Servo servo;

};

#endif // MOTEURS_H

