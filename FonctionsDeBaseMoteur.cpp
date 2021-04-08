#include "FonctionsDeBaseMoteur.h"

//#include <Arduino.h>

FonctionsDeBaseMoteur::FonctionsDeBaseMoteur() : Correcteur(&Entree, &Sortie, &Ref, Kp, Ki, Kd, DIRECT)
{
    //ctor
}

FonctionsDeBaseMoteur::~FonctionsDeBaseMoteur()
{
    delete Centrale_Inertielle;
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
    
    else if(Angle>45 && Angle<=135)
    {
        Moteur1.Rotation(Speed, Sens2);
        Moteur2.Rotation(Speed, Sens);
        Moteur3.Rotation(Speed, Sens);
        Moteur4.Rotation(Speed, Sens2);
    }

    else if(Angle>135 && Angle<=225)
    {
        Moteur1.Rotation(Speed, Sens2);
        Moteur2.Rotation(Speed, Sens2);
        Moteur3.Rotation(Speed, Sens2);
        Moteur4.Rotation(Speed, Sens2);
    }

    else if(Angle>225 || Angle<=315)
    {
        Moteur1.Rotation(Speed, Sens);
        Moteur2.Rotation(Speed, Sens2);
        Moteur3.Rotation(Speed, Sens2);
        Moteur4.Rotation(Speed, Sens);
    }
}

void FonctionsDeBaseMoteur::Tourner(bool SensDeRotation, double distancePointRotation, double Speed, bool Sens)
{

}

void FonctionsDeBaseMoteur::GererVitesseProfondeur(double Vitesse, bool Sens)//Fonction dont la pertinence est à discuter (dépend  des caractéristiques des moteurs de profondeur)
{

}

void FonctionsDeBaseMoteur::GererPositionProfondeur(double ConsigneProfondeur, double ProfondeurReelle)
{
    //Lecture de la profondeur ici ou à un niveau supérieur

    if(ConsigneProfondeur<ProfondeurReelle)
    {
        MoteurProf1.Rotation(1,0); //Sens et vitesse tout à fait arbitraire, à régler! Le sous-marin est censé descendre dans ce cas de figure
        MoteurProf1.Rotation(1,0);
        MoteurProf1.Rotation(1,0);
        MoteurProf1.Rotation(1,0);
    }

    if(ConsigneProfondeur>ProfondeurReelle)
    {
        MoteurProf1.Rotation(1,1); //Sens et vitesse tout à fait arbitraire, à régler! Le sous-marin est censé monter dans ce cas de figure
        MoteurProf1.Rotation(1,1);
        MoteurProf1.Rotation(1,1);
        MoteurProf1.Rotation(1,1);
    }
}

void FonctionsDeBaseMoteur::GererInclinaison(double AngleTangage, double AngleRoulis, double VitesseProf)//A modifier
{
    double psi = AngleTangage; //Angle de consigne de roulis
    double phi = AngleRoulis; //Angle de consigne de tangage
    double vit = VitesseProf; //Vitesse de consigne donnée auparavant aux moteurs de profondeur

    double Vit1; //Vitesse de consigne donnée aux moteurs 1,2,3 et 4 calculée à partir de psi, phi et vit
    double Vit2;
    double Vit3;
    double Vit4;

    Vit1 = ; // a completer

    if(AngleTangage != -1) //Si on veut modifier l'angle de tangage
    {
        if(AngleTangageR<AngleTangage)
        {
            if(AngleTangageR>90) //sens trigo
            {
                dif=AngleTangage-AngleTangageR;

            }
            else if(AngleTangage<90) //sens trigo
            {
                dif=AngleTangage-AngleTangageR;

            }
            else //sens horaire
            {
                dif=360-AngleTangageR;

            }
        }
        else
        {
           if(AngleTangageR<180) //sens horaire
            {
                dif=AngleTangageR-AngleTangage;

            }
            else if(AngleTangage>180) //sens horaire
            {
                dif=AngleTangageR-AngleTangage;

            }
            else if(AngleTangage!=AngleTangageR) //sens trigo
            {
                dif=AngleTangage;

            }
        }
    }

    if(AngleRoulis!=-1) //Si on veut modifier l'angle de roulis
    {
        if(AngleRoulisR<AngleRoulis)
        {
            if(AngleRoulisR>180) //sens trigo
            {
                dif=AngleRoulis-AngleRoulisR;

            }
            else if(AngleRoulis<180) //sens trigo
            {
                dif=AngleRoulis-AngleRoulisR;

            }
            else //sens horaire
            {
                dif=180-AngleRoulisR;

            }
        }
        else
        {
           if(AngleRoulisR<180) //sens horaire
            {
                dif=AngleRoulisR-AngleRoulis;

            }
            else if(AngleRoulis<180) //sens horaire
            {
                dif=AngleRoulisR-AngleRoulis;

            }
            else if(AngleRoulis!=AngleRoulisR) //sens trigo
            {
                dif=AngleRoulis;
            }
        }
    }
}

void FonctionsDeBaseMoteur::Correction(double VitesseConsigne, double VitesseReelle, bool SensVit, bool SensDeRotation, double Cap, double ProfondeurConsigne, double ProfondeurReelle, bool SensProf)
{
    Correcteur.SetMode(AUTOMATIC); //Initialisation du correcteur

    //Relevé des données de la centrale inertielle

    //Variation des angles
    double AngleLacet = (Centrale_Inertielle->stcGyro.w[0])/32768*180;
    double AngleRoulis = (Centrale_Inertielle->stcGyro.w[1])/32768*180;
    double AngleTangage = (Centrale_Inertielle->stcGyro.w[2])/32768*180;

    //Variation

    //Correction vitesse
    Ref = VitesseConsigne;
    Entree = VitesseReelle;
    Kp = V_Kp;
    Kd = V_Kd;
    Ki = V_Ki;
    Correcteur.Compute();
    Aller(Sortie, SensVit, Cap);


    //Correction lacet
    Ref = Cap;
    Entree = AngleLacet;
    Kp = Lac_Kp;
    Kd = Lac_Kd;
    Ki = Lac_Ki;
    Correcteur.Compute();
    Tourner(SensDeRotation, 1, VitesseConsigne, SensDeRotation);

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
    GererPositionProfondeur(ProfondeurConsigne, ProfondeurReelle);//A completer


}

void FonctionsDeBaseMoteur::ArretUrgence()
{
    Moteur1.UrgentStop();
    Moteur2.UrgentStop();
    Moteur3.UrgentStop();
    Moteur4.UrgentStop();

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

double FonctionsDeBaseMoteur::MethodeDeSimpson(double t1, double t2, double a1, double a2)
{
    double I;

    double x1 = a1;
    double x2 = (a1+a2)/2;
    double x3 = a2;

    double w1 = (a2-a1)/6;
    double w2 = 2*(a2-a1)/3;
    double w3 = (a2-a1)/6;

    I = x1*w1 + x2*w2 + x3*w3;

    return I;
}
