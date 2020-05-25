#include "environnement.h"

using namespace std;

////////////////////////// CLASSE ENVIRONNEMENT ////////////////////////////////////////

Environnement::Environnement(){}

//initialisation des variables statiques
float Environnement::luminosity = 15.0; //kilolux (different des lumens)
float Environnement::temperature = 22.5;
float Environnement::CO2 = 0.0003;
float Environnement::humidity=0.40;


float Environnement::Get_lum(void){	
	return luminosity;
}

float Environnement::Get_CO2(void){	
	return CO2;
}

float Environnement::Get_hum(void){	
	return humidity;
}

float Environnement::Get_temp(void){
	return temperature;
}

void Environnement::Set_lum(float lum){
	luminosity=lum;
}

void Environnement::Set_temp(float temp){
	temperature= temp;
}

void Environnement::Set_CO2(float C){
	CO2=C;
}

void Environnement::Set_hum(float hum){
	humidity=hum;
}


//////////////////////////////// CLASSE PLANTE //////////////////////////////////////////

Plante ::Plante(){
	Energy = 10; 
	MaxEnergy=10;
	MinEnergy=0;
} 
int Plante::NbPlantes=0;

	bool Plante ::IsAlive(){
		bool vivante;
		//plante meurt quand elle froid / chaud + soif + pas de lumiere + pas d'energie

		if (IsThirsty() || NeedsLight() || NeedsHeat()==1 || NeedsHeat()==2 || NeedsMoreCO2()){
			if (Energy<=MinEnergy){ //plante souffre -> moins d'energie
				Energy=0;
				vivante=false;
			}
			else {
				Energy-=1;
				vivante=true;
			}
		}
		
		else if (!IsThirsty() && !NeedsLight() && NeedsHeat()==0 &&! NeedsMoreCO2()){ // tout va bien pour la plante
			if (Energy>=MaxEnergy){
				Energy=10;
			}
			else {
				Energy+=1;
			}
			
			vivante=true;
		}
		return vivante;
	}
	
	
	int Plante::IsThirsty(){ //-> 0 si OK / 1 si soif /2 si trop humide
		int soif;
		if (Environnement::Get_hum() < 0.6){
			soif = 1;
		}
		else if (Environnement::Get_hum() > 0.9)
			soif = 2;
		}
	else {
		soif = 0;
	}
		return soif;
	}
	
	
	bool Plante ::NeedsLight(){ //-> 0 si OK / 1 si pas assez de lumiere
		bool noir;
		if (Environnement::Get_lum() <10){ //kilolux
			noir = true;
		}
		else {
			noir = false;
		}
		return noir;		
	}
	
	
	bool Plante::NeedsMoreCO2(){ //-> 0 si OK / 1 si pas assez de CO2
		bool PasDair;
		if (Environnement::Get_CO2()<0.0003){
			PasDair=true;
		}
		else {
			PasDair=false;
		}
		return PasDair;
	}
	
	
	int Plante::NeedsHeat(){  //-> 0 si OK / 1 si trop chaud / 2 si trop froid
		int chaleur;
		if (Environnement::Get_temp()<15.0){ //trop froid
			chaleur=2;
		}
		else if (Environnement::Get_temp()>25.0){ //trop chaud
			chaleur=1;
		}
		else { // tout va bien :)
			chaleur =0;
		}
		return chaleur;
		
	}
	// 3 cas -> trop chaud / OK / trop froid
	//Si trop chaud -> ventilateur
	//OK -> fait rien
	//Trop froid -> chauffage
	
	/*
	void Plante::Set_lum(float lum){
		luminosity=lum;
	}
	
	void Plante::Set_temp(float temp){
		temperature= temp;
	}
	
	void Plante::Set_CO2(float C){
		CO2=C;
	}
	
	void Plante::Set_hum(float hum){
		humidity=hum;
	}*/
	
	
	
	///////////////////////////// CLASSE MY APPLICATION ///////////////////////////////////////
	
MyApplication::MyApplication(){
	
	//liste de plantes
	//liste d'environnement
}


int MyApplication::main(Plante *plantain){
	int etat; //probleme : un seul entier renvoye alors qu'il y a peut etre plusieurs actions a faire en meme temps
	
	if (!plantain.IsAlive){
		//arreter tous les actionneurs
		etat=0;
	}
	else {
	if (plantain.IsThirsty==1){ // 1 si soif 
		//actionneur Arrosage se met en route
		//fermeture fenetre
		etat=1;
	}
	else if (plantain.IsThirsty==2){ // 2 si trop humide
		//ouverture fenetre
		//arret de l'arrosage
		etat=2;
	}
	if (plantain.NeedsHeat ==1){ //1 si trop chaud
		//actionneur Ventilateur se met en route
		//arret actionneur chauffage
		etat=3;
		
	} 
	else if (plantain.NeedsHeat ==2){ //2 si trop froid
		//actionneur Chauffage se met en route
		//arret ventilateur
		etat=4;
	} 
	if (plantain.NeedsLight){
		//Actionneur lampe se met en route
		etat=5;
	}
	}
	
		
		//Modifier les valeurs d'environnement
    	
	return etat ;
}
