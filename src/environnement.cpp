#include "environnement.h"

using namespace std;

////////////////////////// CLASSE ENVIRONNEMENT ////////////////////////////////////////

Environnement::Environnement(){}

//initialisation des variables statiques
float Environnement::luminosity = 15.0; //kilolux (different des lumens)
float Environnement::temperature = 20; //22.000000
float Environnement::CO2 = 0.0003;		//0.000000
float Environnement::humidity=0.70;


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

void Plante::UpdateEnergy(){
	if (IsThirsty()==1 ||IsThirsty()==2 || NeedsLight() || NeedsHeat()==1 || NeedsHeat()==2 || NeedsMoreCO2()){
		if (Energy<=MinEnergy){ //plante souffre -> moins d'energie
			Energy=0;
		}
		else {
			Energy-=1;
			cout<<"Plante : Je vis mais je souffre ! :( ---> energie : "<<Energy<<endl;
		}
	}
	else if (IsThirsty()==0 && !NeedsLight() && NeedsHeat()==0 && !NeedsMoreCO2()){ // tout va bien pour la plante
		
		if (Energy>=MaxEnergy){
			Energy=10;
		}
		else {
			Energy+=1;
		}
		cout<<"Plante : Je vis et je vais bien ! ----> energie : "<<Energy<<endl;
	}
}


	bool Plante ::IsAlive(){
		bool vivante;
		UpdateEnergy();
		if (Energy==0){
			vivante=false; //plante meurt quand elle froid / chaud + soif + pas de lumiere + pas d'energie
			cout<<"Plante : je suis morte :("<<endl;
		}
		else {
			vivante=true;
		}
		return vivante;
	}
	
	
	int Plante::IsThirsty(){ //-> 0 si OK / 1 si soif /2 si trop humide
		int soif;
		if (Environnement::Get_hum() < 0.6){
			soif = 1;
		}
		else if (Environnement::Get_hum() > 0.9){
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
			cout<<"Plante : Je veux du CO2 !"<<endl;
		}
		else {
			PasDair=false;
			cout<<"Plante : J'ai du CO2"<<endl;
		}
		return PasDair;
	}
	
	
	int Plante::NeedsHeat(){  //-> 0 si OK / 1 si trop chaud / 2 si trop froid
		int chaleur;
		if (Environnement::Get_temp()<15.0){ //trop froid
			chaleur=2;
		}
		else if (Environnement::Get_temp()>24.0){ //trop chaud
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
	NbPlantes=0;
	
	//liste de plantes
	//liste d'environnement
}


bool MyApplication::main(Plante *plantain, int *commandTab){
	bool EnVie;
	
	if (!(plantain->IsAlive())){
		//arreter tous les actionneurs
		for(int i=0;i<=4;i++) commandTab[i]=0;
		EnVie=false;
	}
	else {
		EnVie=true;
		if ((plantain->IsThirsty())==1){ 
			cout<<"Plante : J'ai soif"<<endl;
			// 1 si soif 
			//actionneur Arrosage se met en route
			//fermeture fenetre
			commandTab[4]=1;
			commandTab[0]=0;
		}
		else if ((plantain->IsThirsty())==2){ // 2 si trop humide
			cout<<"Plante : J'ai trop d'eau ! :("<<endl;
			//ouverture fenetre
			//arret de l'arrosage
			commandTab[4]=0;
			commandTab[0]=50;
		}
		else if ((plantain->IsThirsty())==0){
			//fermeture fenetre
			//arret arrosage
			commandTab[0]=0;
			commandTab[4]=0;
			cout<<"Plante : J'ai assez d'eau :)"<<endl;
		}
		if ((plantain->NeedsHeat()) ==1){ //1 si trop chaud
			//actionneur Ventilateur se met en route
			//arret actionneur chauffage
			commandTab[2]=10;
			commandTab[1]=0;
			cout<<"Plante : il fait chaud :("<<endl;
		} 
		else if ((plantain->NeedsHeat()) ==2){ //2 si trop froid
			//actionneur Chauffage se met en route
			//arret ventilateur
			commandTab[2]=0;
			commandTab[1]=10;
			cout<<"Plante : il fait froid :("<<endl;
		}
		else if ((plantain->NeedsHeat()) ==0){ //chaleur suffisante
			//arret chauffage et ventilateur
			commandTab[2]=0;
			commandTab[1]=0;
			cout<<"Plante : bonne temperature :D"<<endl;
		}
		if (plantain->NeedsLight()){
			//Actionneur lampe se met en route
			cout<<"Plante : J'ai peur du noir ! :("<<endl;
			commandTab[3]=1;
		}
		if (!(plantain->NeedsLight())){
			//extinction lampe
			commandTab[3]=0;
			cout<<"Plante : vive la lumiere :) "<<endl;
		}
	}
	
	for (int i=0;i<5;i++){
		cout<<commandTab[i]<<" ";
	}
	cout<<endl;
	
	return EnVie;
	//Modifier les valeurs d'environnement

}
