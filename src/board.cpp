#include "core_simulation.h"
#include "mydevices.h"


int main(){
  // creation d'une board
  Board esp8266;
  // achat des senseurs et actionneurs
  AnalogSensorTemperature temperature(0.0,DELAY,TEMP);
  AnalogSensorLuminosity lumiere(0.0,DELAY,LUM);
  DigitalActuatorLED led1(DELAY);
  ExternalDigitalSensorButton bouton;
  IntelligentDigitalActuatorLED led2(DELAY);
  I2CActuatorScreen screen;
  
  // branchement des capteurs actionneurs
  esp8266.pin(1,temperature);
  esp8266.pin(0,led1);
  esp8266.i2c(1,screen);
  esp8266.pin(2,lumiere);
  esp8266.pin(3,led2);
  esp8266.pin(4,bouton);
  
  // allumage de la carte
  esp8266.run();
  return 0;
}


