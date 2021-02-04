#include "FonctionsDeBaseMoteur.h"

//#include <Arduino.h>

FonctionsDeBaseMoteur::FonctionsDeBaseMoteur()
{
    //ctor
}

FonctionsDeBaseMoteur::FonctionsDeBaseMoteur(int pinMot1, int pinMot2, int pinMot3, int pinMot4, int pinServo1, int pinServo2, int pinServo3, int pinServo4, int pinMotProf1, int pinMotProf2, int pinMotProf3, int pinMotProf4)
{
    this->pinMot1 = pinMot1;
    this->pinMot2 = pinMot2;
    this->pinMot3 = pinMot3;
    this->pinMot4 = pinMot4;

    this->pinServo1 = pinServo1;
    this->pinServo2 = pinServo2;
    this->pinServo3 = pinServo3;
    this->pinServo4 = pinServo4;

    this->pinMotProf1 = pinMotProf1;
    this->pinMotProf2 = pinMotProf2;
    this->pinMotProf3 = pinMotProf3;
    this->pinMotProf4 = pinMotProf4;

    Moteur1(pinMot1, 1); //Moteur 1 : moteur avant gauche (en se situant derrière le sous-marin)
    Moteur2(pinMot2, 2); //Moteur 2 : moteur avant droit
    Moteur3(pinMot3, 3); //Moteur 3 : moteur arrière gauche
    Moteur4(pinMot4, 4); //Moteur 4 : moteur arrière droit

        //Servos gérant les moteurs de direction
    Servo1(pinServo1, 1); //Servos : même code chiffré que pour les moteurs, correspondance des numéros
    Servo2(pinServo2, 2);
    Servo3(pinServo3, 3);
    Servo4(pinServo4, 4);

        //Moteurs de profondeur
    MoteurProf1(pinMotProf1, 1);
    MoteurProf2(pinMotProf2, 2);
    MoteurProf3(pinMotProf3, 3);
    MoteurProf4(pinMotProf4, 4);

    Entree = 0;
    Sortie = 0;
    Ref = 0;
    Kp = 1;
    Ki = 1;
    Kd = 1;


    V_Kp = 1;//Paramètres correction vitesse
    V_Ki = 1;
    V_Kd = 1;

    Lac_Kp = 1;//Paramètres correction lacet
    Lac_Ki = 1;
    Lac_Kd = 1;

    Rou_Kp = 1;//Paramètres correction roulis
    Rou_Ki = 1;
    Rou_Kd = 1;

    Tan_Kp = 1;//Paramètres correction tangage
    Tan_Ki = 1;
    Tan_Kd = 1;

    P_Kp = 1;//Paramètres correction profondeur
    P_Ki = 1;
    P_Kd = 1;

    Correcteur(&Entree, &Sortie, &Ref, Kp, Ki, Kd, DIRECT);
    Correcteur.SetMode(AUTOMATIC);
}


FonctionsDeBaseMoteur::~FonctionsDeBaseMoteur()
{
    //dtor
}

void FonctionsDeBaseMoteur::Aller(double Speed, bool Sens, double Angle) //Hypothèse : l'angle reçu est compris entre 0° et 360° avec pour référence l'avant
{
    bool Sens2;

    if(Sens==0)
        Sens2=1;
    else
        Sens2=0;

    if(Angle<=45 || Angle>315)
    {
        Moteur1.Rotation(Speed, Sens);
        Moteur2.Rotation(Speed, Sens);
        Moteur3.Rotation(Speed, Sens);
        Moteur4.Rotation(Speed, Sens);
    }

    if(Angle>45 && Angle<=135)
    {
        Moteur1.Rotation(Speed, Sens2);
        Moteur2.Rotation(Speed, Sens);
        Moteur3.Rotation(Speed, Sens);
        Moteur4.Rotation(Speed, Sens2);
    }

    if(Angle>135 && Angle<=225)
    {
        Moteur1.Rotation(Speed, Sens2);
        Moteur2.Rotation(Speed, Sens2);
        Moteur3.Rotation(Speed, Sens2);
        Moteur4.Rotation(Speed, Sens2);
    }

    if(Angle>225 || Angle<=315)
    {
        Moteur1.Rotation(Speed, Sens);
        Moteur2.Rotation(Speed, Sens2);
        Moteur3.Rotation(Speed, Sens2);
        Moteur4.Rotation(Speed, Sens);
    }
}

void FonctionsDeBaseMoteur::Tourner(bool SensDeRotation, double distancePointRotation, double Speed, bool Sens)
{
    //Les distances sont en mètres et les angles en degrés
    //Dans cette fonction, le sous-marin tourne autour d'un point situé à une distance égale des deux moteurs situés du côté duquel le sous-marin tourne
    //On garde une vitesse constante sur les moteurs, on joue seulement sur l'angle des servos (mathématiquement plus simple)
    //Pour SensDeRotation : 0 : tourne à gauche ; 1 : tourne à droite

    double d1 = 0.5; //Distance entre le centre de rotation du servo et l'axe de symétrie du sous-marin allant de l'avant à l'arrière(demi-largeur); à définir
    double d2 = 0.5; //Distance entre le centre de rotation du servo et l'axe de symétrie du sous-marin allant d'un côté à l'autre(demi-longueur); à définir
    double lambda = distancePointRotation;//Distance entre le poinr autour duquel le sous-marin tourne et l'axe de symétrie du sous-marin

    double lambda1 = d1-lambda; //Distance entre le point de rotation et les moteurs situés à l'intérieur de la rotation
    double lambda2 = lambda+d1; //Distance entre le point de rotation et les moteurs situés à l'extérieur de la rotation

    double lim = d1 + tan(45)*d2; //Les moteurs à l'intérieur de la rotation ne peuvent pivoter que de 45° selon la distance à laquelle se trouve le point de rotation
                                //Il faut donc définir une limite au-delà de laquelle leur orientation sera inversée de 180° (ainsi que le sens de rotation des moteurs d'ailleurs)

    double phi1; double phi2; double phi3; double phi4;

    bool Sens2=Sens;

    if(SensDeRotation==0) //Tourne du coté gauche
    {
        if(lambda<=lim)
        {
            phi1 = Signe(lambda1)*Arctan(d1/lambda1);
            phi3 = 180 + Signe(lambda1)*Arctan(d1/lambda1);

            if(Sens==0)
                Sens2=1;
            else
                Sens2=0;
        }

        if(lambda>lim)
        {
            phi1 = 90 + Arctan(d1/lambda1);
            phi3 = 90 - Arctan(d1/lambda1);
        }

        phi2 = -90 + Arctan(d1/lambda2);
        phi4 = -90 - Arctan(d1/lambda2);

        Servo1.RotationAngle(phi1);
        Servo2.RotationAngle(phi2);
        Servo3.RotationAngle(phi3);
        Servo4.RotationAngle(phi4);

        Moteur1.Rotation(Speed, Sens2);
        Moteur2.Rotation(Speed, Sens);
        Moteur3.Rotation(Speed, Sens2);
        Moteur4.Rotation(Speed, Sens);

    }
    else //Tourne du côté droit
    {
        if(lambda<=lim)
        {
            phi2 = -Signe(lambda1)*Arctan(d1/lambda1);
            phi4 = -180 - Signe(lambda1)*Arctan(d1/lambda1);

            if(Sens==0)
                Sens2=1;
            else
                Sens2=0;
        }

        if(lambda>lim)
        {
            phi2 = -90 - Arctan(d1/lambda1);
            phi4 = 90 + Arctan(d1/lambda1);
        }

        phi1 = 90 - Arctan(d1/lambda2);
        phi3 = 90 + Arctan(d1/lambda2);

        Servo1.RotationAngle(phi1);
        Servo2.RotationAngle(phi2);
        Servo3.RotationAngle(phi3);
        Servo4.RotationAngle(phi4);

        Moteur1.Rotation(Speed, Sens);
        Moteur2.Rotation(Speed, Sens2);
        Moteur3.Rotation(Speed, Sens);
        Moteur4.Rotation(Speed, Sens2);

    }

}

void FonctionsDeBaseMoteur::GererProfondeur(double Vitesse, bool Sens)//A modifier
{

}

void FonctionsDeBaseMoteur::GereInclinaison(double AngleTangage, double AngleRoulis)//A modifier
{

}

void FonctionsDeBaseMoteur::Correction(double VitesseConsigne, double VitesseReelle, bool SensVit, bool SensDeRotation, double Cap, double AngleLacet, double AngleTangage, double AngleRoulis, double ProfondeurConsigne, double ProfondeurReelle, double SensProf)
{
    //Correction vitesse
    Ref = VitesseConsigne;
    Entree = VitesseReelle;
    Kp = V_Kp;
    Kd = V_Kd;
    Ki = V_Ki;
    Correcteur.Compute();
    Aller(Sortie, Sens, Cap);


    //Correction lacet
    Ref = Cap;
    Entree = AngleLacet;
    Kp = Lac_Kp;
    Kd = Lac_Kd;
    Ki = Lac_Ki;
    Correcteur.Compute();
    Tourner(SensDeRotation, 1, VitesseConsigne, Sens);

    //Correction roulis
    Ref = 0;
    Entree = AngleRoulis;
    Kp = Rou_Kp;
    Kd = Rou_Kd;
    Ki = Rou_Ki;
    Correcteur.Compute();
    GererInclinaison(0, Sortie);//A completer


    //Correction tangage
    Ref = 0;
    Entree = AngleTangage;
    Kp = Tan_Kp;
    Kd = Tan_Kd;
    Ki = Tan_Ki;
    Correcteur.Compute();
    GererInclinaison(Sortie, 0);//A completer

    //Correction profondeur
    Ref = ProfondeurConsigne;
    Entree = ProfondeurReelle;
    Kp = P_Kp;
    Kd = P_Kd;
    Ki = P_Ki;
    Correcteur.Compute();
    GererProfondeur();//A completer


}

void FonctionsDeBaseMoteur::ArretUrgence()
{
    Moteur1.UrgentStop();
    Moteur2.UrgentStop();
    Moteur3.UrgentStop();
    Moteur4.UrgentStop();

    Servo1.PositionUrgence();
    Servo1.PositionUrgence();
    Servo1.PositionUrgence();
    Servo1.PositionUrgence();

    MoteurProf1.UrgentStop();
    MoteurProf2.UrgentStop();
    MoteurProf3.UrgentStop();
    MoteurProf4.UrgentStop();
}

double FonctionsDeBaseMoteur::Arctan(double x)//Calcul de arctan à l'aide du développement limité usuel
{
    double atan;
    atan=x;
    int n=100;
    for(int i=1;i<n;i++)
    {
        atan = atan + pow(-1,i)*pow(x,(2*i+1))/(2*i+1);
    }
    return atan;
}

double FonctionsDeBaseMoteur::Signe(double x)//Calcul du signe de x
{
    x = x/abs(x);
    return x;
}
