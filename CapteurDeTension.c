int VoltageArduino; //Tension de sortie captée par la carte arduino --> nombre entre 0 et 1023
int Vcc=5; //tension d'alimentation de l'arduino (ATTENTION : 5 * Vccmax >= VBatterie)
int Vbatterie; // tension réelle de la batterie
int R1= 7.5; //valeur de la résistance 1
int R2= 30;
int factor= (R1+R2)/R1; //pont diviseur de tension qui donne Vbatterie=factor*VoltageArduino
 
void setup ()
{
  Serial.begin (9600);
}
void loop ()
{
  VoltageArduino= analogRead (0); //lecture de la valeur de la tension de sortie captée par le port 0 de la carte Arduino--> nombre entre 0 et 1023
  VoltageArduino= (VoltageArduino/1023)*Vcc; //conversion de la valeur en tension comprise entre 0 et 5
  Vbatterie=factor*VoltageArduino; // pont diviseur de tension
    Serial.println ("Voltage: ");
  Serial.println (Vbatterie); // affichage
  delay (1000);
}
