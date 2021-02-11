//Ceci est un code test pour vérifier le fonctionnement du capteur
//Les seules parties nécessaire au code sont les accès I2C XX.pressure() /xx.temperature / xx.depth()
//L'acceseur d'altitude n'est pas nécessaire pour des raisons évidentes
//


#include <MS5837.h>
#include <Wire.h>


MS5837 baro;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); //Initialise la console a 9600 bauds

  Serial.println("Init.");

  Wire.begin(); // initialise le process I2C

  while (!baro.init())
  {
    Serial.println("Init baromètre échouée");
  }

  baro.setModel(MS5837::MS5837_02BA); // Mettre le modèle ici (en l'occurence ici le bar 02
  baro.setFluidDensity(1029); // Densité pour de l'eau salée, 997 pour de l'eau douce
}

void loop() {
  // put your main code here, to run repeatedly:

  baro.read();

  Serial.print("Pressure: "); 
  Serial.print(baro.pressure()); 
  Serial.println(" mbar");
  
  Serial.print("Temperature: "); 
  Serial.print(baro.temperature()); 
  Serial.println(" deg C");
  
  Serial.print("Depth: "); 
  Serial.print(baro.depth()); 
  Serial.println(" m");
  
  Serial.print("Altitude: "); 
  Serial.print(baro.altitude()); 
  Serial.println(" m above mean sea level");

  delay(1000);
}
