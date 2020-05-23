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
	
	static float Get_lum(void);
	static float Get_temp(void);
	static float Get_CO2(void);
	static float Get_hum(void);
	
	static void Set_lum(float lum);
	static void Set_temp(float temp);
	static void Set_CO2(float C);
	static void Set_hum(float hum);

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


class MyApplication{
public :
	MyApplication();
	int main();
};







#endif