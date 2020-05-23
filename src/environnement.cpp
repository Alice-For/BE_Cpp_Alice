#include "environnement.h"

using namespace std;

////////////////////////// CLASSE ENVIRONNEMENT ////////////////////////////////////////

Environnement::Environnement(){
	luminosity=15.0; //kilolux (different des lumens)
	temperature =22.5;
	CO2 = 0.0003;
	humidity = 0.40; // sol = terre
}

float Environnement::Get_lum(){	
	return luminosity;
}

float Environnement::Get_CO2(){	
	return CO2;
}

float Environnement::Get_hum(){	
	return humidity;
}

float Environnement::Get_temp(){
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
	
	
	bool Plante::IsThirsty(){ //-> 0 si OK / 1 si soif
		bool soif;
		if (humidity < 0.6){
			soif = true;
		}
		else {
			soif = false;
		}
		return soif;
	}
	
	
	bool Plante ::NeedsLight(){ //-> 0 si OK / 1 si pas assez de lumiere
		bool noir;
		if (luminosity <10){ //kilolux
			noir = true;
		}
		else {
			noir = false;
		}
		return noir;		
	}
	
	
	bool Plante::NeedsMoreCO2(){ //-> 0 si OK / 1 si pas assez de CO2
		bool PasDair;
		if (CO2<0.0003){
			PasDair=true;
		}
		else {
			PasDair=false;
		}
		return PasDair;
	}
	
	
	int Plante::NeedsHeat(){  //-> 0 si OK / 1 si trop chaud / 2 si trop froid
		int chaleur;
		if (temperature<15.0){ //trop froid
			chaleur=2;
		}
		else if (temperature>25.0){ //trop chaud
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
	}
	
	
	
	///////////////////////////// CLASSE MY APPLICATION ///////////////////////////////////////
	
MyApplication::MyApplication(){
	
	//liste de plantes
	//liste d'environnement
}


int MyApplication::main(){
	
	
   /* appartement.Set_lum(val_l);
    appartement.Set_temp(val_t);
    appartement.Set_CO2(val_c);
    appartement.Set_hum(val_h);
    
	cactus.Set_lum(val_l);
    cactus.Set_temp(val_t);
    cactus.Set_CO2(val_c);
    cactus.Set_hum(val_h);*/
    
   // if (cactus.IsThirsty){
    	//Lampe -> allumer ou eteindre
		//Arrosage -> allumer ou eteindre
		//etc
		
		//Modifier les valeurs d'environnement
    	
	return 0;
}
