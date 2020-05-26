#include "environnement.h"

using namespace std;

////////////////////////// CLASSE ENVIRONNEMENT ////////////////////////////////////////

Environnement::Environnement(){}

//initialisation des variables statiques
float Environnement::luminosity = 7; //kilolux (different des lumens)
float Environnement::temperature = 40; //22.000000
float Environnement::CO2 = 0.0003;		//0.000000
float Environnement::humidity=40;


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

int Plante::NbPlantes=0;

Plante ::Plante(){
	Energy = 10;
	MaxEnergy=10;
	MinEnergy=0;
	NbPlantes+=1;
	cout<<"Une nouvelle plante ! Youpi !"<<endl;
}

void Plante::UpdateEnergy(float temp, float hum, float lum, float co2){
	if (IsThirsty(hum)==1 ||IsThirsty(hum)==2 || NeedsLight(lum) || NeedsHeat(temp)==1 || NeedsHeat(temp)==2 || NeedsMoreCO2(co2)){
		if (Energy<=MinEnergy){ //plante souffre -> moins d'energie
			Energy=0;
		}
		else {
			Energy-=1;
			cout<<"Plante : Je vis mais je souffre ! :( ---> energie : "<<Energy<<endl;
		}
	}
	else if (IsThirsty(hum)==0 && !NeedsLight(lum) && NeedsHeat(temp)==0 && !NeedsMoreCO2(co2)){ // tout va bien pour la plante

		if (Energy>=MaxEnergy){
			Energy=10;
		}
		else {
			Energy+=1;
		}
		cout<<"Plante : Je vis et je vais bien ! ----> energie : "<<Energy<<endl;
	}
}


	bool Plante ::IsAlive(float temp, float hum, float lum, float co2){
		bool vivante;
		UpdateEnergy(temp, hum, lum, co2);
		if (Energy==0){
			vivante=false; //plante meurt quand elle froid / chaud + soif + pas de lumiere + pas d'energie
			cout<<"Plante : je suis morte :("<<endl;
		}
		else {
			vivante=true;
		}
		return vivante;
	}


	int Plante::IsThirsty(float hum){ //-> 0 si OK / 1 si soif /2 si trop humide
		int soif;
		if (hum < 60){
			soif = 1;
		}
		else if (hum > 90){
			soif = 2;
		}
		else {
			soif = 0;
		}
		return soif;
	}


	bool Plante ::NeedsLight(float lum){ //-> 0 si OK / 1 si pas assez de lumiere
		bool noir;
		if (lum <10){ //kilolux
			noir = true;
		}
		else {
			noir = false;
		}
		return noir;
	}


	bool Plante::NeedsMoreCO2(float co2){ //-> 0 si OK / 1 si pas assez de CO2
		bool PasDair;
		if (co2<0.0003){
			PasDair=true;
			cout<<"Plante : Je veux du CO2 !"<<endl;
		}
		else {
			PasDair=false;
			cout<<"Plante : J'ai du CO2"<<endl;
		}
		return PasDair;
	}


	int Plante::NeedsHeat(float temp){  //-> 0 si OK / 1 si trop chaud / 2 si trop froid
		int chaleur;
		if (temp<15.0){ //trop froid
			chaleur=2;
		}
		else if (temp>24.0){ //trop chaud
			chaleur=1;
		}
		else { // tout va bien :)
			chaleur =0;
		}
		return chaleur;

	}



	///////////////////////////// CLASSE MY APPLICATION ///////////////////////////////////////

MyApplication::MyApplication(){
	NbPlantes=0;

	//liste de plantes
	//liste d'environnement
}


bool MyApplication::main(float temp, float hum, float lum, float co2, Plante *plantain, int *commandTab, bool *MemoireLampe){
	bool EnVie;

	if (!(plantain->IsAlive(temp, hum, lum, co2))){
		//arreter tous les actionneurs
		for(int i=0;i<=4;i++) commandTab[i]=0;
		EnVie=false;
	}
	else {
		EnVie=true;
		if ((plantain->IsThirsty(hum))==1){
			cout<<"Plante : J'ai soif"<<endl;
			// 1 si soif
			//actionneur Arrosage se met en route
			//fermeture fenetre
			commandTab[4]=1;
			commandTab[0]=0;
		}
		else if ((plantain->IsThirsty(hum))==2){ // 2 si trop humide
			cout<<"Plante : J'ai trop d'eau ! :("<<endl;
			//ouverture fenetre
			//arret de l'arrosage
			commandTab[4]=0;
			commandTab[0]=50;
		}
		else if ((plantain->IsThirsty(hum))==0){
			//fermeture fenetre
			//arret arrosage
			commandTab[0]=0;
			commandTab[4]=0;
			cout<<"Plante : J'ai assez d'eau :)"<<endl;
		}
		if ((plantain->NeedsHeat(temp)) ==1){ //1 si trop chaud
			//actionneur Ventilateur se met en route
			//arret actionneur chauffage
			commandTab[2]=10;
			commandTab[1]=0;
			cout<<"Plante : il fait chaud :("<<endl;
		}
		else if ((plantain->NeedsHeat(temp)) ==2){ //2 si trop froid
			//actionneur Chauffage se met en route
			//arret ventilateur
			commandTab[2]=0;
			commandTab[1]=10;
			cout<<"Plante : il fait froid :("<<endl;
		}
		else if ((plantain->NeedsHeat(temp)) ==0){ //chaleur suffisante
			//arret chauffage et ventilateur
			commandTab[2]=0;
			commandTab[1]=0;
			cout<<"Plante : bonne temperature :D"<<endl;
		}
		if (plantain->NeedsLight(lum)){
			//Actionneur lampe se met en route
			cout<<"Plante : J'ai peur du noir ! :("<<endl;
			*MemoireLampe=true;
			commandTab[3]=1;

		}
		if (!(plantain->NeedsLight(lum))){ //extinction lampe
			cout<<"Plante : vive la lumiere :) "<<endl;
			if (MemoireLampe){
				commandTab[3]=1;
			}
			else {
				commandTab[3]=0;
			}
		}
	}

	for (int i=0;i<5;i++){
		cout<<commandTab[i]<<" ";
	}
	cout<<endl;

	return EnVie;
	//Modifier les valeurs d'environnement

}
