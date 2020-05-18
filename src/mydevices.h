#ifndef MYDEVICES_H
#define MYDEVICES_H

#include <fstream>
#include <iostream>
#include <thread>
#include <unistd.h>
#include <string.h>
#include "core_simulation.h"

//int global luminosite_environnement=LUM;

//////////////////////////// CLASSE CAPTEUR //////////////////////////////////////////
class Capteur : public Device{
public :
	Capteur();
	Capteur(float a, int d, float v);
	float Get_val();
	void Set_val(float v) ; //sorte de reset


protected :
	float valeur_lue ; //valeur lue par le capteur
	float alea ; //ecart entre les differentes valeurs mesurees
	int delai ; //temps ecoule entre deux mesures

	//valeurs statiques avec les valeurs de l'environnement ?

};
//////////////////////////// CLASSE CAPTEUR DE LUMINOSITE //////////////////////////////////////////
class AnalogSensorLuminosity: public Capteur {
public :
	AnalogSensorLuminosity(float a, int d, float v);
	//int static luminosite_environnement;
	float Get_val();
	
	virtual void run();
			
	
};
//int AnalogSensorLuminosity::luminosite_environnement=LUM;


//////////////////////////// CLASSE CAPTEUR TEMPERATURE //////////////////////////////////////////
class AnalogSensorTemperature: public Capteur {
  
public:
  //constructeur
  AnalogSensorTemperature(float a, int d, float v);
  float Get_val();
  // thread representant le capteur et permettant de fonctionner independamment de la board
  virtual void run();
};


//////////////////////////// CLASSE CAPTEUR TEMPERATURE //////////////////////////////////////////
class AnalogSensorHumidity: public Capteur {

public:
  //constructeur
  AnalogSensorHumidity (float a, int d, float v);
  // thread representant le capteur et permettant de fonctionner independamment de la board
  float Get_val();
  virtual void run();
};








// exemple d'actionneur digital : une led, ne pas oublier d'heriter de Device
class DigitalActuatorLED: public Device {
private:
  // etat de la LED
  int state;
  // temps entre 2 affichage de l etat de la led
  int temps;
  
public:
    // initialisation du temps de rafraichiisement
  DigitalActuatorLED(int t);
  // thread representant l'actionneur et permettant de fonctionner independamment de la board
  virtual void run();
};

//LED intelligente (fille de LED ?)
class IntelligentDigitalActuatorLED: public Device{
private:
  // etat de la LED
  int state;
  // temps entre 2 affichage de l etat de la led
  int temps;
  
public:
    // initialisation du temps de rafraichiisement
  IntelligentDigitalActuatorLED(int t);
  // thread representant l'actionneur et permettant de fonctionner independamment de la board
  virtual void run();
	
};


// exemple d'actionneur sur le bus I2C permettant d'echanger des tableaux de caracteres : un ecran, ne pas oublier d'heriter de Device
class I2CActuatorScreen : public Device{
protected:
    // memorise l'affichage de l'ecran
  char buf[I2C_BUFFER_SIZE];
  
public:
  // constructeur
  I2CActuatorScreen ();
  // thread representant le capteur et permettant de fonctionner independamment de la board
  virtual void run();
};

//Bouton exterieur
class ExternalDigitalSensorButton: public Device {
	
public :
	ExternalDigitalSensorButton();
	
	int DetectButton();
	
	void run();
	
};


#endif
