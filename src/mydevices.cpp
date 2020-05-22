
#include "mydevices.h"

using namespace std;

//variables d'environnement
int luminosite_environnement=200;
int bouton_app=0;




//////////////////////////// CLASSE CAPTEUR //////////////////////////////////////////

Capteur ::Capteur():Device(){
	alea=0;
	temps=1;
	val=0;
}

Capteur ::Capteur(float a, int d, float v):Device(), alea(a), temps(d), val(v){
	//valeur_lue=0;
}

float Capteur::Get_val(){
	return val;
}

void Capteur::Set_val(float v) {
	val=v;

}

//////////////////////////// CLASSE CAPTEUR LUMINOSITE //////////////////////////////////////////


//ordre des arguments doit etre le meme que dans le .h
AnalogSensorLuminosity::AnalogSensorLuminosity(float a, int d, float v):Capteur(a, d, v) {
	cout <<"Capteur luminosite initialise"<<endl;
}

float AnalogSensorLuminosity::Get_val(){
	float toreturn;
	toreturn = Capteur::Get_val();
	cout <<"Valeur mesure luminosite" <<endl;
	return toreturn;
}

void AnalogSensorLuminosity::run(){
  while(1){
    //alea=1-alea;
    if(ptrmem!=NULL)
      *ptrmem=luminosite_environnement; //+alea;
    sleep(temps);
  }
}
/*
int AnalogSensorLuminosity::LE(){
	int lum=luminosite_environnement;
	return lum;		
}
*/

//////////////////////////// CLASSE CAPTEUR TEMPERATURE //////////////////////////////////////////

//classe AnalogSensorTemperature
AnalogSensorTemperature::AnalogSensorTemperature(float a, int d, float v):Capteur(a, d, v){
	cout <<"Capteur temperature initialise"<<endl;
}

float AnalogSensorTemperature::Get_val(){
	float toreturn;
	toreturn = Capteur::Get_val();
	cout <<"Valeur mesure temperature" <<endl;
	return toreturn;
}

void AnalogSensorTemperature::run(){
  while(1){
    alea=1-alea;
    if(ptrmem!=NULL)
      *ptrmem=val+alea;
    sleep(temps);
  }
}


//////////////////////////// CLASSE CAPTEUR HUMIDITE //////////////////////////////////////////

  //constructeur
AnalogSensorHumidity::AnalogSensorHumidity (float a, int d, float v):Capteur(a, d, v){
	cout <<"Capteur humidite initialise"<<endl;
}

  
float AnalogSensorHumidity::Get_val(){
		float toreturn;
		toreturn = Capteur::Get_val();
		cout <<"Valeur mesure humidite" <<endl;
		return toreturn;
  }
  
  
  void AnalogSensorHumidity::run(){
	  while(1){
	    alea=1-alea;
	    if(ptrmem!=NULL)
	      *ptrmem=val+alea;
	    sleep(temps);
	  }
  }



//////////////////////////// CLASSE CAPTEUR CO2 //////////////////////////////////////////

  //constructeur
AnalogSensorCO2::AnalogSensorCO2 (float a, int d, float v):Capteur(a, d, v){
	cout <<"Capteur CO2 initialise"<<endl;
}


  // thread representant le capteur et permettant de fonctionner independamment de la board
float AnalogSensorCO2::Get_val(){
	float toreturn;
	toreturn = Capteur::Get_val();
	cout <<"Valeur mesure CO2" <<endl;
	return toreturn;
}

void AnalogSensorCO2::run(){
	  while(1){
	    alea=1-alea;
	    if(ptrmem!=NULL)
	      *ptrmem=val+alea;
	    sleep(temps);
	  }
}

///////////////////////////// CLASSE ACTIONNEUR //////////////////////////////////////////////

Actionneur ::Actionneur():Device(){
	temps=1;
	cout <<"Actionneur initialise"<<endl;
}

Actionneur ::Actionneur (int d):Device(){
	temps=d;
	cout <<"Actionneur initialise - constructeur bis" <<endl;
}

/////////////////////////CLASSE LED /////////////////////////////////////////////

LED::LED(int t):Actionneur(), temps(t), state(LOW){
}

void LED::run(){
	
	while(1){
	  if(ptrmem!=NULL)
	    state=*ptrmem;
	  if (state==LOW)
	    cout << "((((eteint))))\n";
	  else
	  cout << "((((allume))))\n";
	  sleep(temps);
	  }
}

  
  float LED::read_lum(){
	  float toreturn = Environnement :: luminosity;
	  float torturn2 = AnalogSensorLuminosity::Get_Val();
	  return toreturn;
  } 
  
  //void LED::set_lum(float v); // a ecrire
  
  void LED::Allumer(){
	  state=HIGH;
  }
  void LED::Eteindre(){
	  state=LOW;
  }
  
  void LED::main(); // a ecrire


////////////////////////////CLASSE MOTEUR /////////////////////////////////////////////

	Moteur ::Moteur(int d):Actionneur(d){
		speed=0;
		position=0;
		cout <<"moteur initialise"<<endl;
		
	} 
	
	int Moteur :: read_speed(){
		return speed;		//0 -> arrete ET 10 -> vitesse max
	} 
	int Moteur :: read_position(){
		return position;	//0 position de base = 360 degres. 
	} 
	



/////////////////////////////CLASSE VENTILATEUR //////////////////////////////////////////////////
//Ici la position n'est pas pertinente,on ne regarde que la vitesse

	void Ventilateur ::run(){

	while(1){
		  if(ptrmem!=NULL)
			speed=*ptrmem;
		  if (speed==0)
			cout << "---- Ventilateur eteint -----\n";
		  else
		  cout << "---- Ventilateur allume-------\n";
		  cout<<"---- Ventilateur vitesse "<< speed << endl;
		  sleep(temps);
		  }

	} 
	Ventilateur ::Ventilateur(int d): Moteur(d){
		cout <<"ventilateur initialise"<<endl;
	} 
	
	
	void Ventilateur ::Write_speed(int sp){
		speed = sp;
		//a faire plus tard : fonction de saisie au clavier
	} 
	void Ventilateur ::main(){} // a ecrire



/////////////////////////////CLASSE CHAUFFAGE //////////////////////////////////////////////////
	
	void Chauffage ::run(){
		

	while(1){
		  if(ptrmem!=NULL)
			speed=*ptrmem;
		  if (speed==0)
			cout << "---- Chauffage eteint -----\n";
		  else
		  cout << "---- Chauffage allume-------\n";
		  cout<<"---- Chauffage : vitesse "<< speed << endl;
		  sleep(temps);
		  }	
	}
	
	Chauffage::Chauffage()(int d): Moteur(d){
		cout <<"chauffage initialise"<<endl;
	} 
	
	void Chauffage ::Write_speed(int sp){
		speed=sp;
	} 
	void Chauffage ::main(){} // a ecrire
	

/////////////////////////////CLASSE ARROSAGE //////////////////////////////////////////////////
//Ici la vitesse n'est pas pertinente,on ne regarde que la position

	void Arrosage::run(){} // a ecrire
	Arrosage::Arrosage(){} // a ecrire
	void Arrosage::Write_pos(int sp){} // a ecrire
	void Arrosage ::main(){} // a ecrire



/////////////////////////////CLASSE OUVERTURE FENETRE //////////////////////////////////////////////////
//Ici la vitesse n'est pas pertinente,on ne regarde que la position

	void Moteur_Fenetre::run(){} // a ecrire
	Moteur_Fenetre::Moteur_Fenetre(){} // a ecrire
	void Moteur_Fenetre::Write_pos(int sp){} // a ecrire
	void Moteur_Fenetre ::main(){} // a ecrire







/////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////// CLASSE ACTIONNEUR LED //////////////////////////////////////////

//classe DigitalActuatorLED
DigitalActuatorLED::DigitalActuatorLED(int t):Device(),state(LOW),temps(t){
}

void DigitalActuatorLED::run(){
  while(1){
    if(ptrmem!=NULL)
      state=*ptrmem;
    if (state==LOW)
      cout << "((((eteint))))\n";
    else
    cout << "((((allume))))\n";
    sleep(temps);
    }
}

//////////////////////////// CLASSE ACTIONNEUR LED INTELLIGENTE //////////////////////////////////////////

//classe IntelligentDigitalActuatorLED
IntelligentDigitalActuatorLED::IntelligentDigitalActuatorLED(int t):Device(),state(LOW),temps(t){
}

void IntelligentDigitalActuatorLED::run(){
	//AnalogSensorLuminosity truc(DELAY,LUM);
	  while(1){
	    if(ptrmem!=NULL)
	      state=*ptrmem;
	    if (state==LOW){
	      cout << "((((eteint))))\n";
	      luminosite_environnement=200;
	    }
	    
	    else {
	    cout << "((((allume))))\n";
	    luminosite_environnement=250;
	    }
	    
	    sleep(temps);
	    }
	
	
}




// classe I2CActuatorScreen
I2CActuatorScreen::I2CActuatorScreen ():Device(){
  }

void I2CActuatorScreen::run(){
  while(1){
    if ( (i2cbus!=NULL)&&!(i2cbus->isEmptyRegister(i2caddr))){
      Device::i2cbus->requestFrom(i2caddr, buf, I2C_BUFFER_SIZE);
      cout << "---screen :"<< buf << endl;
    }
    sleep(1);
    }
}

ExternalDigitalSensorButton::ExternalDigitalSensorButton():Device(){}

int ExternalDigitalSensorButton :: DetectButton(){
	int appui;
	
	if(ifstream("on.txt")){
		appui = 1;
	}
	else {
		appui=0;
	}
	return appui;
}

void ExternalDigitalSensorButton ::run(){
	while(1){
		bouton_app= DetectButton();
		
		
	}
}