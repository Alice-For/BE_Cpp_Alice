#include "core_simulation.h"
#include "mydevices.h"
#include "environnement.h"


int main(){
  // creation d'une board
  Board esp8266;
  // achat des senseurs et actionneurs
  AnalogSensorTemperature temperature(DELAY,Environnement::Get_temp());
  //AnalogSensorLuminosity lumiere(DELAY,Environnement::Get_lum());
  AnalogSensorHumidity humidite(DELAY, Environnement::Get_hum());
  //AnalogSensorCO2 dioxyde(DELAY, Environnement::Get_CO2());
  
  MoteurFenetre turbo(DELAY);
  //Chauffage feu(DELAY);			-> ok :)
  //Ventilateur AirFrais(DELAY);	-> ok :)
  //Lampe Loupiote(DELAY);
  Arrosage Tuyau(DELAY);
  
  I2CActuatorScreen screen;
  
  // branchement des capteurs
  esp8266.pin(1,temperature);
  esp8266.pin(0,humidite);
  //esp8266.pin(2,lumiere);
  //esp8266.pin(3,dioxyde);
  
  // branchement des actionneurs
  esp8266.pin(4,turbo);
  //esp8266.pin(5,feu);				-> ok
  //esp8266.pin(6,AirFrais);		-> ok
  //esp8266.pin(7,Loupiote);
  esp8266.pin(8,Tuyau);
  
  esp8266.i2c(1,screen);
  // allumage de la carte
  esp8266.run();
  //Destructeurs a appeler ?
  return 0;
}


