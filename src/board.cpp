#include "core_simulation.h"
#include "mydevices.h"
#include "environnement.h"

#define PIN_HUMIDITE 10
#define PIN_TEMPERATURE 9
#define PIN_LUMIERE 11
#define PIN_CO2 12
#define PIN_CHAUFFAGE 5
#define PIN_VENTILATEUR 6
#define PIN_FENETRE 4
#define PIN_ARROSAGE 8
#define PIN_LAMPE 7


int main(){
  // creation d'une board
  Board esp8266;
  // achat des senseurs et actionneurs
  AnalogSensorTemperature temperature(DELAY,Environnement::Get_temp());
  AnalogSensorLuminosity lumiere(DELAY,Environnement::Get_lum());
  AnalogSensorHumidity humidite(DELAY, Environnement::Get_hum());
  AnalogSensorCO2 dioxyde(DELAY, Environnement::Get_CO2());
  
  MoteurFenetre turbo(DELAY);
  Chauffage feu(DELAY);			//-> ok :)
  Ventilateur AirFrais(DELAY);	//-> ok :)
  Lampe Loupiote(DELAY);
  Arrosage Tuyau(DELAY);
  
  I2CActuatorScreen screen;
  
  // branchement des capteurs
  esp8266.pin(PIN_TEMPERATURE,temperature);
  esp8266.pin(PIN_HUMIDITE,humidite);
  esp8266.pin(PIN_LUMIERE,lumiere);
  esp8266.pin(PIN_CO2,dioxyde);
  
  // branchement des actionneurs
  esp8266.pin(PIN_FENETRE,turbo);
  esp8266.pin(PIN_CHAUFFAGE,feu);		//		-> ok
  esp8266.pin(PIN_VENTILATEUR,AirFrais);	//	-> ok
  esp8266.pin(PIN_LAMPE,Loupiote);
  esp8266.pin(PIN_ARROSAGE,Tuyau);
  
 
  esp8266.i2c(1,screen);
  // allumage de la carte
  
  esp8266.run();
  //Destructeurs a appeler ?
  return 0;
}


