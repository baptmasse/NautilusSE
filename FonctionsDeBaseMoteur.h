#ifndef FONCTIONSDEBASEMOTEUR_H
#define FONCTIONSDEBASEMOTEUR_H

#include "Servomoteurs.h"
#include "Moteurs.h"
#include <PID_v1.h>

#include <Arduino.h>


class FonctionsDeBaseMoteur
{
    public:
        FonctionsDeBaseMoteur();
        FonctionsDeBaseMoteur(int pinMot1, int pinMot2, int pinMot3, int pinMot4, int pinServo1, int pinServo2, int pinServo3, int pinServo4, int pinMotProf1, int pinMotProf2, int pinMotProf3, int pinMotProf4);
        virtual ~FonctionsDeBaseMoteur();

        void Aller(double Speed, bool Sens, double Angle);//Permet au sous-marin de se d�placer en ligne droite sur le plan x,y
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

        int pinServo1; //Pin des servos g�rant l'orientation des moteurs de direction
        int pinServo2;
        int pinServo3;
        int pinServo4;

        int pinMotProf1; //Pin des moteure de profondeur
        int pinMotProf2;
        int pinMotProf3;
        int pinMotProf4;

        //Moteurs de direction
        Moteurs Moteur1; //Moteur 1 : moteur avant gauche (en se situant derri�re le sous-marin)
        Moteurs Moteur2; //Moteur 2 : moteur avant droit
        Moteurs Moteur3; //Moteur 3 : moteur arri�re gauche
        Moteurs Moteur4; //Moteur 4 : moteur arri�re droit

        //Servos g�rant les moteurs de direction
        Servomoteurs Servo1; //Servos : m�me code chiffr� que pour les moteurs, correspondance des num�ros
        Servomoteurs Servo2;
        Servomoteurs Servo3;
        Servomoteurs Servo4;

        //Moteurs de profondeur
        Moteurs MoteurProf1;
        Moteurs MoteurProf2;
        Moteurs MoteurProf3;
        Moteurs MoteurProf4;


        double Entree;
        double Sortie;
        double Ref;
        double Kp;
        double Ki;
        double Kd;


        double V_Kp;//Param�tres correction vitesse
        double V_Ki;
        double V_Kd;

        double Lac_Kp;//Param�tres correction lacet
        double Lac_Ki;
        double Lac_Kd;

        double Rou_Kp;//Param�tres correction roulis
        double Rou_Ki;
        double Rou_Kd;

        double Tan_Kp;//Param�tres correction tangage
        double Tan_Ki;
        double Tan_Kd;

        double P_Kp;//Param�tres correction profondeur
        double P_Ki;
        double P_Kd;

        PID Correcteur;
};

#endif // FONCTIONSDEBASEMOTEUR_H
