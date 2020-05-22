#ifndef ENVIRONNEMENT_H
#define ENVIRONNEMENT_H

#include <fstream>
#include <iostream>
#include <thread>
#include <unistd.h>
#include <string.h>
#include "core_simulation.h"

class Environnement{
	
public :
	float luminosity;
	float temperature;
	float CO2;
	float humidity;
	
	void Get_lum();
	void Get_temp();
	void Get_CO2();
	void Get_hum();
};

class Plante{
public :
	bool IsAlive();
	bool IsThirsty();
	bool NeedsLight();
	bool NeedsMoreCO2(); //et faire une fonction NeedsLessCO2() aussi ?
	bool NeedsHeat(); 	//faire une fonction NeedsFreshness aussi ? Ou alors 3 valeurs retournees ?
}










#endif