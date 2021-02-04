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

        void Rotation(double Speed, bool Sens); //Vitesse entr�e en m/s, sens : 1 pour avancer, 0 pour reculer (par rapport � l'avant du sous-marin)
        void UrgentStop();


    protected:

    private:
        int NumeroMoteur;
        int ESCpin; //pin auxquels sont rattach�s les ESC
        Servo servo;

};

#endif // MOTEURS_H

