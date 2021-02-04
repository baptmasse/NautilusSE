#ifndef FONCTIONSDEBASEMOTEUR_H
#define FONCTIONSDEBASEMOTEUR_H

#include "Servomoteurs.h"
#include "Moteurs.h"
//#include <PID_v1.h>

//#include <Arduino.h>


class FonctionsDeBaseMoteur
{
    public:
        FonctionsDeBaseMoteur();
        FonctionsDeBaseMoteur(int pinMot1, int pinMot2, int pinMot3, int pinMot4, int pinServo1, int pinServo2, int pinServo3, int pinServo4, int pinMotProf1, int pinMotProf2, int pinMotProf3, int pinMotProf4);
        virtual ~FonctionsDeBaseMoteur();

        void Aller(double Speed, bool Sens, double Angle);//Permet au sous-marin de se déplacer en ligne droite sur le plan x,y
        void Tourner(bool SensDeRotation, double distancePointRotation, double Speed, bool Sens);//Permet au sous-marin de tourner autour d'un point virtuel
        void GererProfondeur(double Vitesse, bool Sens);
        void GereInclinaison(double AngleTangage, double AngleRoulis);
        void Correction(double VitesseConsigne, double VitesseReelle, bool SensVit, bool SensDeRotation, double Cap, double AngleLacet, double AngleTangage, double AngleRoulis, double ProfondeurConsigne, double ProfondeurReelle, double SensProf);
        void ArretUrgence();

        //Fonctions mathematiques utiles
        double Arctan(double x);
        double Signe(double x);


    protected:

    private:
        int pinMot1; //Pin des moteure de direction
        int pinMot2;
        int pinMot3;
        int pinMot4;

        int pinServo1; //Pin des servos gérant l'orientation des moteurs de direction
        int pinServo2;
        int pinServo3;
        int pinServo4;

        int pinMotProf1; //Pin des moteure de profondeur
        int pinMotProf2;
        int pinMotProf3;
        int pinMotProf4;

        int Id[4];

        //Moteurs de direction
        Moteurs Moteur1(int pinMot1, int Id[0]); //Moteur 1 : moteur avant gauche (en se situant derrière le sous-marin)
        Moteurs Moteur2(int pinMot2, int Id[1]); //Moteur 2 : moteur avant droit
        Moteurs Moteur3(int pinMot3, int Id[2]); //Moteur 3 : moteur arrière gauche
        Moteurs Moteur4(int pinMot4, int Id[3]); //Moteur 4 : moteur arrière droit

        //Servos gérant les moteurs de direction
        Servomoteurs Servo1(int pinServo1, int Id[0]); //Servos : même code chiffré que pour les moteurs, correspondance des numéros
        Servomoteurs Servo2(int pinServo2, int Id[1]);
        Servomoteurs Servo3(int pinServo3, int Id[2]);
        Servomoteurs Servo4(int pinServo4, int Id[3]);

        //Moteurs de profondeur
        Moteurs MoteurProf1(int pinMot1Prof, int Id[0]);
        Moteurs MoteurProf2(int pinMot2Prof, int Id[1]);
        Moteurs MoteurProf3(int pinMot3Prof, int Id[2]);
        Moteurs MoteurProf4(int pinMot4Prof, int Id[3]);


        double Entree;
        double Sortie;
        double Ref;
        double Kp;
        double Ki;
        double Kd;


        double V_Kp;//Paramètres correction vitesse
        double V_Ki;
        double V_Kd;

        double Lac_Kp;//Paramètres correction lacet
        double Lac_Ki;
        double Lac_Kd;

        double Rou_Kp;//Paramètres correction roulis
        double Rou_Ki;
        double Rou_Kd;

        double Tan_Kp;//Paramètres correction tangage
        double Tan_Ki;
        double Tan_Kd;

        double P_Kp;//Paramètres correction profondeur
        double P_Ki;
        double P_Kd;

        PID Correcteur(&Entree, &Sortie, &Ref, Kp, Ki, Kd, DIRECT);
};

#endif // FONCTIONSDEBASEMOTEUR_H
