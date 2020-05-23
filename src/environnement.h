#ifndef ENVIRONNEMENT_H
#define ENVIRONNEMENT_H

#include <fstream>
#include <iostream>
#include <thread>
#include <unistd.h>
#include <string.h>
#include "core_simulation.h"
#include "mydevices.h"

class Environnement{
protected :
	static float luminosity;
	static float temperature;
	static float CO2;
	static float humidity;
	
public :
		
	Environnement();
	
	float Get_lum();
	float Get_temp();
	float Get_CO2();
	float Get_hum();
	
	void Set_lum(float lum);
	void Set_temp(float temp);
	void Set_CO2(float C);
	void Set_hum(float hum);

};

class Plante{
protected :
	float luminosity;
	float temperature;
	float CO2;
	float humidity;
	int Energy;
	int MaxEnergy;
	int MinEnergy;
	
public :
	Plante();
	
	bool IsAlive();
	bool IsThirsty();
	bool NeedsLight();
	bool NeedsMoreCO2(); 
	int NeedsHeat();
	
	void Set_lum(float lum);
	void Set_temp(float temp);
	void Set_CO2(float C);
	void Set_hum(float hum);

};










#endif