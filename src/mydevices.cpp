
#include "mydevices.h"
#include "environnement.h"

using namespace std;

//variables d'environnement
/*float luminosity=15.0; //kilolux (different des lumens)
float temperature =22.5;
float CO2 = 0.0003;
float humidity = 0.40;*/



//////////////////////////// CLASSE CAPTEUR //////////////////////////////////////////

Capteur ::Capteur():Device(){
	//alea=0;
	temps=1;
	val=0;
}

Capteur ::Capteur(int d, float v):Device(), temps(d), val(v){
}

/*
float Capteur::Get_val(){
	return val;
}

void Capteur::Set_val(float v) {
	val=v;

}*/


//////////////////////////// CLASSE CAPTEUR LUMINOSITE //////////////////////////////////////////


//ordre des arguments doit etre le meme que dans le .h
AnalogSensorLuminosity::AnalogSensorLuminosity(int d, float v):Capteur(d, v) {
	cout <<"Capteur luminosite initialise"<<endl;
}

/*
float AnalogSensorLuminosity::Get_val(){
	float toreturn;
	toreturn = Capteur::Get_val();
	cout <<"Valeur mesure luminosite" <<endl;
	return toreturn;
}*/

void AnalogSensorLuminosity::run(){
  while(1){
    if(ptrmem!=NULL)
      *ptrmem=Environnement::Get_lum();
    sleep(temps);
  }
}


//////////////////////////// CLASSE CAPTEUR TEMPERATURE //////////////////////////////////////////

//classe AnalogSensorTemperature
AnalogSensorTemperature::AnalogSensorTemperature(int d, float v):Capteur(d, v){
	cout <<"Capteur temperature initialise"<<endl;
}

/*
float AnalogSensorTemperature::Get_val(){
	float toreturn;
	toreturn = Capteur::Get_val();
	cout <<"Valeur mesure temperature" <<endl;
	return toreturn;
}*/

void AnalogSensorTemperature::run(){
  while(1){
    if(ptrmem!=NULL)
      *ptrmem=Environnement::Get_temp();
    sleep(temps);
  }
}


//////////////////////////// CLASSE CAPTEUR HUMIDITE //////////////////////////////////////////

  //constructeur
AnalogSensorHumidity::AnalogSensorHumidity (int d, float v):Capteur(d, v){
	cout <<"Capteur humidite initialise"<<endl;
}

/*  
float AnalogSensorHumidity::Get_val(){
		float toreturn;
		toreturn = Capteur::Get_val();
		cout <<"Valeur mesure humidite" <<endl;
		return toreturn;
  }*/
  
  
  void AnalogSensorHumidity::run(){
	  while(1){
	    if(ptrmem!=NULL)
	      *ptrmem=Environnement::Get_hum();;
	    sleep(temps);
	  }
  }



//////////////////////////// CLASSE CAPTEUR CO2 //////////////////////////////////////////

  //constructeur
AnalogSensorCO2::AnalogSensorCO2 (int d, float v):Capteur(d, v){
	cout <<"Capteur CO2 initialise"<<endl;
}

/*
float AnalogSensorCO2::Get_val(){
	float toreturn;
	toreturn = Capteur::Get_val();
	cout <<"Valeur mesure CO2" <<endl;
	return toreturn;
}*/

void AnalogSensorCO2::run(){
	  while(1){
	    if(ptrmem!=NULL)
	      *ptrmem=Environnement::Get_CO2();;
	    sleep(temps);
	  }
}




///////////////////////////// CLASSE ACTIONNEUR //////////////////////////////////////////////

Actionneur ::Actionneur():Device(){
	temps=1;
	//cout <<"Actionneur initialise"<<endl;
}

Actionneur ::Actionneur (int d):Device(){
	temps=d;
	//cout <<"Actionneur initialise - constructeur bis" <<endl;
}
///////////////////////////CLASSE ARROSAGE //////////////////////////////////////////


	Arrosage::Arrosage(int d):Actionneur(d){
	}
	
	void Arrosage::run(){
		while(1){
		  if(ptrmem!=NULL)
		    state=*ptrmem;
		  if (state==LOW){
		    cout << "----- Arrosage eteint ------\n";
		    Environnement::Set_hum(0.4);
		  }
		  		  
		  else {
			  cout << "----- Arrosage allume ------\n";
			  Environnement::Set_hum(0.6);
		  }
		  sleep(temps);
		  }
	}
	//void set_humidite(float hum){}
	
	/*
	float Arrosage::read_humidite(){
		//AnalogSensorHumidity hum = new AnalogSensorHumidity(0.0, 1, 0.4);
		float toreturn = Environnement :: humidity;
		//float toreturn2 = hum.Get_val();
		return toreturn;		
	}*/
	
	int Arrosage::main(){
		return 0;
	}
	




/////////////////////////CLASSE LAMPE /////////////////////////////////////////////

Lampe::Lampe(int t):Actionneur(t), state(LOW){
}

void Lampe::run(){
	
	while(1){
	  if(ptrmem!=NULL)
	    state=*ptrmem;
	  if (state==LOW){
		  cout << "((((eteint))))\n";
		  Environnement::Set_lum(15.0);;
	  }
	  else {
		  cout << "((((allume))))\n";
		  Environnement::Set_lum(17.0);
	  }
	  sleep(temps);
	  }
}

  
  /*float Lampe::read_lum(){
	  float toreturn = Environnement :: luminosity;
	  //float toreturn2 = AnalogSensorLuminosity::Get_val();
	  return toreturn;
  }*/
  
  //void LED::set_lum(float v); // a ecrire
  
  void Lampe::Allumer(){
	  state=HIGH;
  }
  void Lampe::Eteindre(){
	  state=LOW;
  }
  
  int Lampe::main(){
	  return 0;
  } // a ecrire


////////////////////////////CLASSE MOTEUR /////////////////////////////////////////////

Moteur::Moteur(int d):Actionneur(d){
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
	
	//virtual void Moteur::run()=0; //fonction virtuelle pure


/////////////////////////////CLASSE VENTILATEUR //////////////////////////////////////////////////
//Ici la position n'est pas pertinente,on ne regarde que la vitesse

	void Ventilateur ::run(){

	while(1){
		  if(ptrmem!=NULL)
			speed=*ptrmem;
		  if (speed==0){
			  cout << "---- Ventilateur eteint -----\n";
			  Environnement::Set_temp(22.5);
		  }
					  
		  else {
			  cout << "---- Ventilateur allume-------\n";
			  cout<<"---- Ventilateur vitesse "<< speed << endl;
			  Environnement::Set_temp(21.0);
		  }
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
	int Ventilateur ::main(){
		return 0;
	} // a ecrire



/////////////////////////////CLASSE CHAUFFAGE //////////////////////////////////////////////////
	
	void Chauffage ::run(){
		

	while(1){
		  if(ptrmem!=NULL)
			speed=*ptrmem;
		  if (speed==0) {
			  cout << "---- Chauffage eteint -----\n";
			  Environnement::Set_temp(22.5);
		  }
		  else {
			  cout << "---- Chauffage allume-------\n";
			  cout<<"---- Chauffage : vitesse "<< speed << endl;
			  Environnement::Set_temp(25);	  
		  }
		  sleep(temps);
		  }	
	}
	
	Chauffage::Chauffage(int d): Moteur(d){
		cout <<"chauffage initialise"<<endl;
	} 
	
	void Chauffage ::Write_speed(int sp){
		speed=sp;
	} 
	int Chauffage ::main(){
		return 0;
	} // a ecrire
	


/////////////////////////////CLASSE OUVERTURE FENETRE //////////////////////////////////////////////////
//Ici la vitesse n'est pas pertinente,on ne regarde que la position

	MoteurFenetre::MoteurFenetre(int d):Moteur(d){} 
	
	void MoteurFenetre::run(){
		while(1){
		  if(ptrmem!=NULL)
			position=*ptrmem;
		  if (position==0){
			  cout << "---- Fenetre fermee -----\n";
			  Environnement::Set_hum(0.4);
		  }
		  else {
			  cout << "---- Fenetre ouverte-------\n";
			  cout<<"---- Angle fenetre "<< position << endl;
			  Environnement::Set_hum(0.3);
		  }
		  sleep(temps);
		}
		
	}
	
	
	
	void MoteurFenetre::Write_pos(int p){
		position=p;
	} 
	
	
	int MoteurFenetre ::main(){
		return 0;
	} // a ecrire

	
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
	      //luminosity=200;
	    }
	    
	    else {
	    cout << "((((allume))))\n";
	    //luminosity=250;
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
			
		
	}
}