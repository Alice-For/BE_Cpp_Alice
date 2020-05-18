
#include "mydevices.h"

using namespace std;

int luminosite_environnement=200;
int bouton_app=0;




//////////////////////////// CLASSE CAPTEUR //////////////////////////////////////////

Capteur ::Capteur():Device(){
	alea=0;
	delai=1;
	valeur_lue=0;
}

Capteur ::Capteur(float a, int d, float v):Device(), alea(a), delai(d), valeur_lue(v){
	//valeur_lue=0;
}

float Capteur::Get_val(){
	return valeur_lue;
}

void Capteur ::Set_val(float v) {
	valeur_lue=v;

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



