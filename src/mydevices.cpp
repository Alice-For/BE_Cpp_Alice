
#include "mydevices.h"

using namespace std;

int luminosite_environnement=200;
int bouton_app=0;

//capteur de luminosite
//declaration de val et temps doit etre dans le meme ordre que dans le .h
AnalogSensorLuminosity::AnalogSensorLuminosity(int d, int t):Device(), val(t), temps(d) {
	
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



//classe AnalogSensorTemperature
AnalogSensorTemperature::AnalogSensorTemperature(int d,int  t):Device(),val(t),temps(d){
  alea=1;
}

void AnalogSensorTemperature::run(){
  while(1){
    alea=1-alea;
    if(ptrmem!=NULL)
      *ptrmem=val+alea;
    sleep(temps);
  }
}

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



