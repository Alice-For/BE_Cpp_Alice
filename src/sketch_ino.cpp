#include <unistd.h>
#include "core_simulation.h"
#include "mydevices.h"
#include "environnement.h"

// la fonction d'initialisation d'arduino
void Board::setup(){
  // on configure la vitesse de la liaison
  Serial.begin(9600);
// on fixe les pin en entree et en sortie en fonction des capteurs/actionneurs mis sur la carte
  pinMode(1,INPUT);
  pinMode(0,INPUT);
  pinMode(2,INPUT);
  pinMode(3,INPUT);
  
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  
  //Ecran ??
}

// la boucle de controle arduino
void Board::loop(){
	Environnement appartement ;
	Plante cactus;
  char buf[100], buf2[100], buf3[100], buf4[100];
  float val_t, val_h, val_l, val_c;
  static int cpt=0;
  //static int bascule=0;
  
  int i=0;
  for(i=0;i<10;i++){
    // lecture sur la pin 1 : capteur de temperature
    val_t=analogRead(1);
    val_h=analogRead(0);
    val_l=analogRead(2);
    val_c=analogRead(3);
    
    sprintf(buf,"temperature %f",val_t);
    sprintf(buf2,"luminosite %f",val_l);
    sprintf(buf3,"humidite %f",val_h);
    sprintf(buf4,"CO2 %f",val_c);
    
    Serial.println(buf);
    Serial.println(buf2);
    Serial.println(buf3);
    Serial.println(buf4);
    
    appartement.Set_lum(val_l);
    appartement.Set_temp(val_t);
    appartement.Set_CO2(val_c);
    appartement.Set_hum(val_h);
    
	cactus.Set_lum(val_l);
    cactus.Set_temp(val_t);
    cactus.Set_CO2(val_c);
    cactus.Set_hum(val_h);
    
    if(cpt%5==0){
        // tous les 5 fois on affiche sur l ecran la temperature
      sprintf(buf,"%f",val_t);
      bus.write(1,buf,100);
    }
    
    
    if(cpt%5==1){
        // tous les 5 fois on affiche sur l ecran la luminosite  
    	sprintf(buf2,"%f",val_l);
        bus.write(1,buf2,100);
        }
    
    if(cpt%5==2){
        // tous les 5 fois on affiche sur l ecran la luminosite  
    	sprintf(buf3,"%f",val_h);
        bus.write(1,buf3,100);
        }
    
    if(cpt%5==3){
        // tous les 5 fois on affiche sur l ecran la luminosite  
    	sprintf(buf4,"%f",val_c);
        bus.write(1,buf4,100);
        }
    
    cpt++;
    sleep(1);
  }

  
  
  //minuteur arrosage a tester. Si arrive a expiration, arreter l'arrosage
  

  

  
/*  if(boutton.DetectButton()) {
	  digitalWrite(3,HIGH);
	  cout <<"LED on"<<endl;
  }
  else{
    digitalWrite(3,LOW);
    cout<<"LED off"<<endl;
  }*/

  
}


