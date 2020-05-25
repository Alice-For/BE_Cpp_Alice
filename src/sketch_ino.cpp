#define NBCAPTEUR 2

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
  //pinMode(0,INPUT);
  //pinMode(2,INPUT);
  //pinMode(3,INPUT);
  
  //pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  //pinMode(7,OUTPUT);
  //pinMode(8,OUTPUT);
  //analogWrite(4, 0);
  analogWrite(5, 0); //initialiser les actionneurs a 0, sinon ils font n'importe quoi :(
  analogWrite(6, 0);
  //digitalWrite(7, 0);
  //digitalWrite(8, 0);
  //Ecran ??
}

// la boucle de controle arduino
void Board::loop(){
	Plante *cactus=new Plante;
	bool Vivant;
	char buf[100]; //buf2[100], buf3[100], buf4[100];
	float val_t; // val_h, val_l, val_c;
	static int cpt=0;
	analogWrite(5, 0); //initialiser les actionneurs a 0, sinon ils font n'importe quoi :(
	analogWrite(6, 0);
  
  for(int i=0;i<10;i++){
	  int NbCmd=NBCAPTEUR; //nb de capteurs  fixer a la main
	  int *CommandTab=new int[5];
	  
	  val_t=analogRead(1);
    //Environnement::Set_temp(val_t);
    //val_h=analogRead(0);
    //val_l=analogRead(2);
    //val_c=analogRead(3);
    

    /*
     * CommandTab : tableau d'entiers de la meme taille que le nb de capteurs.
     * CommandTab[0] -> fenetre. 			Valeurs : entre 0 et 50
     * CommandTab[1] -> chauffage			Valeurs : entre 0 et 10
     * CommandTab[2] -> ventilateur			Valeurs : entre 0 et 10
     * CommandTab[3] ->	lampe				Valeurs : 0 ou 1
     * CommandTab[4] ->	arrosage			Valeurs : 0 ou 1
     * */
    
    
    Vivant = MyApplication::main(cactus,CommandTab, NbCmd);
    if (!(Vivant)){
    	cout <<"exit la plante, vous n'avez pas la main verte !"<<endl;
    	exit(-1);
    }
    else {
    
    //toujours le meme nombre d'actions -> 1 par actionneur.
    //1 action = soit eteindre l'actionneur, soit l'allumer ("le laisser tel qu'il est" = un de ces deux cas)
    //reste a transmettre la valeur a ecrire
    
    //for (int j=4;j<7;j++) : quand tous les capteurs sont en place
    //analogWrite(j, commandTab[j-4]);
    for (int j=4;j<7;j++){ //partie ecriture analogique
    	analogWrite(j, CommandTab[j-4]);
    }
    
    digitalWrite(7, CommandTab[3]); //partie ecriture numerique
    digitalWrite(8, CommandTab[4]);
    
     
    delete CommandTab;
    
    //Partie affichage
    
    
    sprintf(buf,"temperature %f",val_t); //temp doit augmenter avec le chauffage
    //sprintf(buf2,"luminosite %f",val_l);
    //sprintf(buf3,"humidite %f",val_h);
    //sprintf(buf4,"CO2 %f",val_c);
    
    Serial.println(buf);
    //Serial.println(buf2);
    //Serial.println(buf3);
    //Serial.println(buf4);
    
    
    if(cpt%5==0){
        // tous les 5 fois on affiche sur l ecran la temperature
      sprintf(buf,"Temperature : %f",val_t);
      bus.write(1,buf,100);
    }
    
    /*
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
        }*/
    
    cpt++;
    sleep(3);
  }
  }

  
  
  //minuteur arrosage a tester. Si arrive a expiration, arreter l'arrosage
  
  
}


