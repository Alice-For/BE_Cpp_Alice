
#include "mydevices.h"
#include "environnement.h"

using namespace std;


//////////////////////////// CLASSE CAPTEUR //////////////////////////////////////////

Capteur ::Capteur():Device(){
	temps=1;
	val=0;
	ptrmem=0;
}
Capteur ::~Capteur(){}
Capteur ::Capteur(int d, int v):Device(), temps(d), val(v){
	ptrmem=0;
}


//////////////////////////// CLASSE CAPTEUR LUMINOSITE //////////////////////////////////////////


AnalogSensorLuminosity::AnalogSensorLuminosity(int d, int v):Capteur(d, v) {
	val_max=100;
	val_min=1;
	cout <<"Capteur luminosite initialise"<<endl;
}

AnalogSensorLuminosity::~AnalogSensorLuminosity(){}


void AnalogSensorLuminosity::run(){
  while(1){
    if(ptrmem!=NULL){
    	int Lumi = Environnement::Get_lum();
		if (Lumi>=val_max){
			*ptrmem=val_max;
			cout <<"Luminosite : valeur max depassee"<<endl;
		}
		else if (Lumi<=val_min){
			*ptrmem=val_min;
			cout <<"Luminosite : valeur min depassee"<<endl;
		}
		else {
			*ptrmem=Lumi;
		}
    }
    sleep(temps);
  }
}


//////////////////////////// CLASSE CAPTEUR TEMPERATURE //////////////////////////////////////////


AnalogSensorTemperature::AnalogSensorTemperature(int d, int v):Capteur(d, v){
	cout <<"Capteur temperature initialise"<<endl;
	val_max=300;
	val_min=-150;
}

AnalogSensorTemperature::~AnalogSensorTemperature(){}

void AnalogSensorTemperature::run(){
  while(1){
    if(ptrmem!=NULL){
    	int tempe = Environnement::Get_temp();
    	if (tempe>=val_max){
    		*ptrmem=val_max;
    		cout <<"Temperature : valeur max depassee"<<endl;
    	}
    	else if (tempe<=val_min){
    		*ptrmem=val_min;
    		cout <<"Temperature : valeur min depassee"<<endl;
    	}
    	else {
    		*ptrmem=tempe;
    	}    	
    }
    sleep(temps);
  }
}


//////////////////////////// CLASSE CAPTEUR HUMIDITE //////////////////////////////////////////


AnalogSensorHumidity::AnalogSensorHumidity (int d, int v):Capteur(d, v){
	cout <<"Capteur humidite initialise"<<endl;
	val_max=100;
	val_min=0;
}

AnalogSensorHumidity::~AnalogSensorHumidity (){}


  void AnalogSensorHumidity::run(){
	  while(1){
	    if(ptrmem!=NULL){
	    	int humi = Environnement::Get_hum();
			if (humi>=val_max){
				*ptrmem=val_max;
				cout <<"Humidite : valeur max depassee"<<endl;
			}
			else if (humi<=val_min){
				*ptrmem=val_min;
				cout <<"Humidite : valeur min depassee"<<endl;
			}
			else {
				*ptrmem=humi;
			}
	    }
	    sleep(temps);
	  }
  }



//////////////////////////// CLASSE CAPTEUR CO2 //////////////////////////////////////////


AnalogSensorCO2::AnalogSensorCO2 (int d, int v):Capteur(d, v){
	cout <<"Capteur CO2 initialise"<<endl;
	val_max=50 ;
	val_min=0;
}

AnalogSensorCO2::~AnalogSensorCO2 (){}


void AnalogSensorCO2::run(){
	  while(1){
	    if(ptrmem!=NULL){
	    	int Co = Environnement::Get_CO2();
			if (Co>=val_max){
				*ptrmem=val_max;
				cout <<"CO2 : valeur max depassee"<<endl;
			}
			else if (Co<=val_min){
				*ptrmem=val_min;
				cout <<"CO2 : valeur min depassee"<<endl;
			}
			else {
				*ptrmem=Co;
			}
	    }
	    sleep(temps);
	  }
}




///////////////////////////// CLASSE ACTIONNEUR //////////////////////////////////////////////

Actionneur ::Actionneur():Device(){
	temps=1;
}

Actionneur ::Actionneur (int d):Device(){
	temps=d;
}
Actionneur ::~Actionneur(){}


/////////////////////////CLASSE LAMPE /////////////////////////////////////////////

Lampe::Lampe(int t):Actionneur(t), state(LOW){
	cout <<"lampe initialisee"<<endl;
}
Lampe::~Lampe(){}

void Lampe::run(){

	while(1){
	  if(ptrmem!=NULL)
	    state=*ptrmem;
	  if (state==LOW){
		  cout << "---- Lampe eteinte ----\n";
	  }
	  else {
		  cout << "---- Lampe allumee ----\n";
		  Environnement::Set_lum(17.0);
	  }
	  sleep(temps);
	  }
}



////////////////////////////CLASSE MOTEUR /////////////////////////////////////////////

Moteur::Moteur(int d):Actionneur(d){
	speed=0;
	position=0;
}


//virtual void Moteur::run()=0; //fonction virtuelle pure
Moteur::~Moteur(){}

/////////////////////////////CLASSE VENTILATEUR //////////////////////////////////////////////////
//Ici la position n'est pas pertinente,on ne regarde que la vitesse

void Ventilateur ::run(){

while(1){
	  if(ptrmem!=NULL){
			if (*ptrmem<max_speed){
				speed=*ptrmem;
			}
			else {
				speed=max_speed;
			}
	  }

	  if (speed==0){
		  cout << "---- Ventilateur eteint ----\n";
	  }

	  else {
		  int temp = Environnement::Get_temp();
		  cout << "---- Ventilateur allume ----\n";
		  cout<<"---- Ventilateur vitesse "<< speed <<" ----\n";
		  Environnement::Set_temp(temp-(int)(speed/2));
	  }
	  sleep(temps);
	  }

}


Ventilateur ::Ventilateur(int d): Moteur(d){
	cout <<"ventilateur initialise"<<endl;
	max_speed=10;
}


Ventilateur ::~Ventilateur(){}



/////////////////////////////CLASSE CHAUFFAGE //////////////////////////////////////////////////


Chauffage::Chauffage(int d): Moteur(d){
	cout <<"chauffage initialise"<<endl;
	max_speed=10;
}

Chauffage::~Chauffage(){}

void Chauffage ::run(){
	
	while(1){
	  if(ptrmem!=NULL){
		if (*ptrmem<max_speed){
				speed=*ptrmem;
			}
			else {
				speed=max_speed;
			}
	  }
	  if (speed==0) {
		  cout << "---- Chauffage eteint ----\n";
	  }
	  else {
		  int temp = Environnement::Get_temp();
		  cout << "---- Chauffage allume ----\n";
		  cout<<"---- Chauffage : vitesse "<< speed << " ----\n"<<endl;
		  Environnement::Set_temp(temp+(int)(speed/2));
	  }
	  sleep(temps);
	  }
}



/////////////////////////////CLASSE OUVERTURE FENETRE //////////////////////////////////////////////////
//Ici la vitesse n'est pas pertinente,on ne regarde que la position

MoteurFenetre::MoteurFenetre(int d):Moteur(d){
	cout <<"moteur fenetre initialise"<<endl;
	max_pos=50;
}

MoteurFenetre::~MoteurFenetre(){}

void MoteurFenetre::run(){
	while(1){
	  if(ptrmem!=NULL){
			if (*ptrmem<max_pos){
				position=*ptrmem;
			}
			else {position=max_pos;
			}    
	  }
		
	  if (position==0){
		  cout << "---- Fenetre fermee ----\n";
	  }
	  else {
		  int hum= Environnement::Get_hum();
		  cout << "---- Fenetre ouverte ----\n";
		  cout<<"---- Angle fenetre "<< position << " ----\n"<<endl;
		  Environnement::Set_hum(hum-(int)(position/5));
	  }
	  sleep(temps);
	}

}

//Fonctions qui ne sont pas utiles au final
/*
	void MoteurFenetre::Write_pos(int p){
		position=p;
	}


	void MoteurFenetre::Ouvrir_fenetre(){
		int pos=0;
	for (pos = 0; pos <= 50; pos += 1) // goes from 0 degrees to 180 degrees in steps of 1 degree
	{
		Write_pos(pos); // tell servo to go to position in variable 'pos'
		sleep(1);
		}
	}


	void MoteurFenetre::Fermer_fenetre(){
		int pos=50;
		for (pos = 50; pos >= 0; pos -= 1)
		{
			Write_pos(pos); // tell servo to go to position in variable 'pos'
			sleep(1);
		}
	}
*/

	///////////////////////////CLASSE ARROSAGE //////////////////////////////////////////


Arrosage::Arrosage(int d):Actionneur(d){
	cout <<"arrosage initialise"<<endl;
}

Arrosage::~Arrosage(){}

void Arrosage::run(){
	while(1){
	  if(ptrmem!=NULL)
		state=*ptrmem;
	  if (state==LOW){
		cout << "---- Arrosage eteint ----\n";
	  }

	  else {
		  cout << "---- Arrosage allume ----\n";
		  Environnement::Set_hum(Environnement::Get_hum()+10);
	  }
	  sleep(temps);
	}
}



///////////////////////////////////// CLASSE ECRAN /////////////////////////////////////////////


// classe I2CActuatorScreen
I2CActuatorScreen::I2CActuatorScreen ():Device(){
  }
I2CActuatorScreen::~I2CActuatorScreen (){}

void I2CActuatorScreen::run(){
  while(1){
    if ( (i2cbus!=NULL)&&!(i2cbus->isEmptyRegister(i2caddr))){
      Device::i2cbus->requestFrom(i2caddr, buf, I2C_BUFFER_SIZE);
      cout << "---screen :"<< buf << endl;
    }
    sleep(1);
    }
}

