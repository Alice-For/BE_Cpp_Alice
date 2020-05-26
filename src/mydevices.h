#ifndef MYDEVICES_H
#define MYDEVICES_H

#include <fstream>
#include <iostream>
#include <thread>
#include <unistd.h>
#include <string.h>
#include "core_simulation.h"
#include "environnement.h"



//////////////////////////// CLASSE CAPTEUR //////////////////////////////////////////
class Capteur : public Device{

protected :
	//float alea ; //ecart entre les differentes valeurs mesurees
	int temps ; //temps ecoule entre deux mesures
	int val ; //valeur lue par le capteur
	int val_max;
	int val_min;

	
public :
	Capteur();
	Capteur(int d, int v);

};
//////////////////////////// CLASSE CAPTEUR DE LUMINOSITE //////////////////////////////////////////
class AnalogSensorLuminosity: public Capteur {
public :
	AnalogSensorLuminosity(int d, int v);

	virtual void run();
};



//////////////////////////// CLASSE CAPTEUR TEMPERATURE //////////////////////////////////////////
class AnalogSensorTemperature: public Capteur {
  
public:
  //constructeur
  AnalogSensorTemperature(int d, int v);
  virtual void run();
};


//////////////////////////// CLASSE CAPTEUR HUMIDITE //////////////////////////////////////////
class AnalogSensorHumidity: public Capteur {

public:
  //constructeur
  AnalogSensorHumidity (int d, int v);
  virtual void run();
};


//////////////////////////// CLASSE CAPTEUR CO2 //////////////////////////////////////////
class AnalogSensorCO2: public Capteur {

public:
  //constructeur
  AnalogSensorCO2 (int d, int v);
  // thread representant le capteur et permettant de fonctionner independamment de la board
  virtual void run();
};




////////////////////////////CLASSE ACTIONNEUR ///////////////////////////////////////////////
class Actionneur : public Device {
protected :
	
	int temps;
	
public :
	Actionneur();
	Actionneur (int d);
};

////////////////////////////CLASSE ARROSAGE////////////////////////////////////////
class Arrosage: public Actionneur{
private :
	int state;
public :
	Arrosage(int d);
	virtual void run();
	
};


////////////////////////////CLASSE LAMPE /////////////////////////////////////////////
class Lampe: public Actionneur {
private:
  // etat de la LED
  int state;

  
public:
    // initialisation du temps de rafraichissement
  Lampe (int t);
  // thread representant l'actionneur et permettant de fonctionner independamment de la board
  virtual void run();
  
  void Allumer();
  void Eteindre();
};

////////////////////////////CLASSE MOTEUR /////////////////////////////////////////////
class Moteur: public Actionneur{
protected :
	int max_speed;
	int min_speed=0;
	int max_pos;
	int min_pos=0;
	int speed;
	int position;
	
public :
	Moteur(int d);
	virtual void run()=0;
	int read_speed();
	int read_position();
	
};


/////////////////////////////CLASSE VENTILATEUR //////////////////////////////////////////////////
//Ici la position n'est pas pertinente,on ne regarde que la vitesse
class Ventilateur : public Moteur{
public :
	virtual void run();
	Ventilateur(int d);
	void Write_speed(int sp);
};


/////////////////////////////CLASSE CHAUFFAGE //////////////////////////////////////////////////
//Ici la position n'est pas pertinente,on ne regarde que la vitesse
class Chauffage : public Moteur{
public :
	virtual void run();
	Chauffage(int d);
	void Write_speed(int sp);
};



/////////////////////////////CLASSE OUVERTURE FENETRE //////////////////////////////////////////////////
//Ici la vitesse n'est pas pertinente,on ne regarde que la position
class MoteurFenetre : public Moteur{
public :
	MoteurFenetre(int d);
	
	virtual void run();
	
	void Write_pos(int p);
	void Ouvrir_fenetre();
	void Fermer_fenetre();
};



////////////////////////////EXEMPLES D'ACTUATORS /////////////////////////////////////////////
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
