#ifndef ENVIRONNEMENT_H
#define ENVIRONNEMENT_H

#include <fstream>
#include <iostream>
#include <thread>
#include <unistd.h>
#include <string.h>
#include <list>
#include "core_simulation.h"
#include "mydevices.h"


class Environnement{
protected :
	static int luminosity;
	static int temperature;
	static int CO2;
	static int humidity;

public :

	Environnement();
	~Environnement();

	static int Get_lum(void);
	static int Get_temp(void);
	static int Get_CO2(void);
	static int Get_hum(void);

	static void Set_lum(int lum);
	static void Set_temp(int temp);
	static void Set_CO2(int C);
	static void Set_hum(int hum);

};

class Plante{
protected :


	int Energy;
	int MaxEnergy;
	int MinEnergy;
	int static NbPlantes;

public :
	Plante();
	~Plante();
	void UpdateEnergy(int temp, int hum, int lum, int co2);
	bool IsAlive(int temp, int hum, int lum, int co2);
	int IsThirsty(int hum);
	bool NeedsLight(int lum);
	bool NeedsMoreCO2(int co2);
	int NeedsHeat(int temp);

};


class HappySeed{

public :
	int NbPlantes ;
	//fonction pour ajouter de nouvelles plantes ? Avec une liste ?
	HappySeed();
	static bool main(int temp, int hum, int lum, int co2, Plante *plantain, int *commandTab, bool *MemoireLampe);
};

#endif
