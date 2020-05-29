#include "environnement.h"

using namespace std;

////////////////////////// CLASSE ENVIRONNEMENT ////////////////////////////////////////

Environnement::Environnement(){}
Environnement::~Environnement(){}

//initialisation des variables statiques - test1 -> temperature et humidite
int Environnement::luminosity = 15; 
int Environnement::temperature = 50; 
int Environnement::CO2 = 3;
int Environnement::humidity=75;


int Environnement::Get_lum(void){
	return luminosity;
}

int Environnement::Get_CO2(void){
	return CO2;
}

int Environnement::Get_hum(void){
	return humidity;
}

int Environnement::Get_temp(void){
	return temperature;
}

void Environnement::Set_lum(int lum){
	luminosity=lum;
}

void Environnement::Set_temp(int temp){
	temperature= temp;
}

void Environnement::Set_CO2(int C){
	CO2=C;
}

void Environnement::Set_hum(int hum){
	humidity=hum;
}


//////////////////////////////// CLASSE PLANTE //////////////////////////////////////////

int Plante::NbPlantes=0;

Plante ::Plante(){
	Energy = 10;
	MaxEnergy=15;
	MinEnergy=0;
	NbPlantes+=1;
	
	MinEau = MIN_EAU;
	MaxEau = MAX_EAU;
	MinTemp = MIN_TEMP;
	MaxTemp = MAX_TEMP;
	MinLum = MIN_LUM;
	MinCO2 = MIN_CO2;

	cout<<"Une nouvelle plante ! Youpi !"<<endl;
}
Plante ::~Plante(){}

void Plante::UpdateEnergy(int temp, int hum, int lum, int co2, int *TauxHum, int *TauxTemp){
	if (IsThirsty(hum,TauxHum)==1 ||IsThirsty(hum,TauxHum)==2 || NeedsLight(lum) || NeedsHeat(temp,TauxTemp)==1 || NeedsHeat(temp,TauxTemp)==2 || NeedsMoreCO2(co2)){
		if (Energy<=MinEnergy){
			Energy=MinEnergy;
		}
		else {
			Energy-=1;
			cout<<"Plante : Je vis mais je souffre ! :( ---> energie : "<<Energy<<endl;
		}
	}
	else if (IsThirsty(hum,TauxHum)==0 && !NeedsLight(lum) && NeedsHeat(temp,TauxTemp)==0 && !NeedsMoreCO2(co2)){ // tout va bien pour la plante

		if (Energy>=MaxEnergy){
			Energy=MaxEnergy;
		}
		else {
			Energy+=1;
		}
		cout<<"Plante : Je vis et je vais bien ! ----> energie : "<<Energy<<endl;
	}
}


	bool Plante ::IsAlive(int temp, int hum, int lum, int co2, int *TauxHum, int *TauxTemp){
		bool vivante;
		UpdateEnergy(temp, hum, lum, co2, TauxHum, TauxTemp);
		if (Energy==0){
			vivante=false; //plante meurt quand elle froid / chaud + soif + pas de lumiere + pas d'energie
			cout<<"Plante : je suis morte :("<<endl;
		}
		else {
			vivante=true;
		}
		return vivante;
	}


	int Plante::IsThirsty(int hum, int *TauxHum){ //-> 0 si OK / 1 si soif /2 si trop humide
		int soif;
		
		if (hum < MinEau){
			soif = 1;
			*TauxHum=MinEau-hum;
		}
		else if (hum > MaxEau){
			soif = 2;
			*TauxHum=hum-MaxEau;
		}
		else {
			soif = 0;
			*TauxHum=0;
		}
		return soif;
	}


	bool Plante ::NeedsLight(int lum){ //-> 0 si OK / 1 si pas assez de lumiere
		
		bool noir;
		if (lum <MinLum){ //kilolux
			noir = true;
		}
		else {
			noir = false;
		}
		return noir;
	}


	bool Plante::NeedsMoreCO2(int co2){ //-> 0 si OK / 1 si pas assez de CO2
			
		bool PasDair;
		if (co2<MinCO2){
			PasDair=true;
		}
		else {
			PasDair=false;
		}
		return PasDair;
	}


	int Plante::NeedsHeat(int temp, int *TauxTemp){  //-> 0 si OK / 1 si trop chaud / 2 si trop froid
		
		int chaleur;
		if (temp<MinTemp){ //trop froid
			chaleur=2;
			*TauxTemp=MinTemp-temp;
		}
		else if (temp>MaxTemp){ //trop chaud
			chaleur=1;
			*TauxTemp=temp-MaxTemp;
		}
		else { // tout va bien :)
			chaleur =0;
			*TauxTemp=0;
		}
		return chaleur;
	}



	///////////////////////////// CLASSE MY APPLICATION ///////////////////////////////////////

HappySeed::HappySeed(){
	NbPlantes=0;

	//liste de plantes
	//liste d'environnement
}


bool HappySeed ::main(int temp, int hum, int lum, int co2, int *TauxHum, int *TauxTemp, Plante *plantain, int *commandTab, bool *MemoireLampe){

	bool EnVie;
	cout<<endl;

	if (!(plantain->IsAlive(temp, hum, lum, co2, TauxHum, TauxTemp))){
		//arreter tous les actionneurs
		for(int i=0;i<=4;i++) commandTab[i]=0;
		EnVie=false;
	}
	else {
		EnVie=true;
		if ((plantain->IsThirsty(hum, TauxHum))==1){
			cout<<"Plante : J'ai soif :("<<endl;
			// 1 si soif. Etat binaire -> on n'utilise pas TauxHum
			//actionneur Arrosage se met en route et fermeture fenetre
			commandTab[4]=1;
			commandTab[0]=0;
		}
		else if ((plantain->IsThirsty(hum, TauxHum))==2){ // 2 si trop humide
			cout<<"Plante : J'ai trop d'eau ! :("<<endl;
			commandTab[4]=0;
			int ctrl_fenetre;
			//ouverture fenetre et arret de l'arrosage
			//Taux hum : distance à la température de "confort" de la plante, en valeur absolue
			/*Fonction à décrire devrait être du type 
			50       ________
			        /
			       /
			      /
			0____/
			    0    val de Taux_hum (ici 20)
			*/
			
			if ((*TauxHum)>=20)
				ctrl_fenetre=50;
			else if ((*TauxHum)<=0)
				ctrl_fenetre=0; //cas qui ne devrait pas arriver si tout va bien, mais who knows
			else 
				ctrl_fenetre=(int)(50*(*TauxHum)/20);
			
			commandTab[0]=ctrl_fenetre;
		}
		else if ((plantain->IsThirsty(hum, TauxHum))==0){
			//fermeture fenetre
			//arret arrosage
			commandTab[0]=0;
			commandTab[4]=0;
			cout<<"Plante : J'ai assez d'eau :)"<<endl;
		}
		if ((plantain->NeedsHeat(temp, TauxTemp)) ==1){ //1 si trop chaud
			//actionneur Ventilateur se met en route
			//arret actionneur chauffage
			commandTab[1]=0;
			cout<<"Plante : il fait chaud :("<<endl;
			int ctrl_ventilo;
			
			//Taux temp : distance à la température de "confort" de la plante, en valeur absolue
			/*Fonction à décrire devrait être du type 
			10       ________
					/
				   /
				  /
			0____/
				0    val de Taux_hum (ici 20)
			*/
			
			if ((*TauxTemp)>=10)
				ctrl_ventilo=10;
			else if ((*TauxTemp)<=0)
				ctrl_ventilo=0; //cas qui ne devrait pas arriver si tout va bien, mais who knows
			else 
				ctrl_ventilo=(int)(*TauxTemp);
			
			commandTab[2]=ctrl_ventilo;
		}
		
		else if ((plantain->NeedsHeat(temp, TauxTemp)) ==2){ //2 si trop froid
			//actionneur Chauffage se met en route et arret ventilateur
			commandTab[2]=0;
			cout<<"Plante : il fait froid :("<<endl;
			int ctrl_chauffage;
						
			//Taux temp : distance à la température de "confort" de la plante, en valeur absolue
			/*Fonction à décrire devrait être du type 
			10       ________
					/
				   /
				  /
			0____/
				0    val de Taux_temp (ici 10)
			*/
			
			if ((*TauxTemp)>=10)
				ctrl_chauffage=10;
			else if ((*TauxTemp)<=0)
				ctrl_chauffage=0; //cas qui ne devrait pas arriver si tout va bien, mais who knows
			else 
				ctrl_chauffage=(int)(*TauxTemp);
			
			commandTab[1]=ctrl_chauffage;

			
		}
		else if ((plantain->NeedsHeat(temp, TauxTemp)) ==0){ //chaleur suffisante
			//arret chauffage et ventilateur
			commandTab[2]=0;
			commandTab[1]=0;
			cout<<"Plante : bonne temperature :)"<<endl;
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
		if (plantain->NeedsMoreCO2(co2)){
			cout<<"Plante : Je veux du CO2 ! :("<<endl;
		}
		else {
			cout<<"Plante : J'ai du CO2 :)"<<endl;
		}
	}

	/*for (int i=0;i<5;i++){
		cout<<commandTab[i]<<" ";
	}
	cout<<endl;*/
	cout<<"***************"<<endl;
	cout<<endl;

	return EnVie;
}
