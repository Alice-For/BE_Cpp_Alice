#define PIN_HUMIDITE 10
#define PIN_TEMPERATURE 9
#define PIN_LUMIERE 11
#define PIN_CHAUFFAGE 5
#define PIN_VENTILATEUR 6
#define PIN_FENETRE 4
#define PIN_ARROSAGE 8
#define PIN_LAMPE 7



#include <unistd.h>
#include "core_simulation.h"
#include "mydevices.h"
#include "environnement.h"


// la fonction d'initialisation d'arduino
void Board::setup(){
  // on configure la vitesse de la liaison
  Serial.begin(9600);
// on fixe les pin en entree et en sortie en fonction des capteurs/actionneurs mis sur la carte
  pinMode(PIN_TEMPERATURE,INPUT);
  pinMode(PIN_HUMIDITE,INPUT);
  pinMode(PIN_LUMIERE,INPUT);
  //pinMode(3,INPUT);
   
  
  pinMode(PIN_FENETRE,OUTPUT);
  pinMode(PIN_CHAUFFAGE,OUTPUT);
  pinMode(PIN_VENTILATEUR,OUTPUT);
  pinMode(PIN_LAMPE,OUTPUT);
  pinMode(PIN_ARROSAGE,OUTPUT);
  analogWrite(PIN_FENETRE, 0);
  analogWrite(PIN_CHAUFFAGE, 0); //initialiser les actionneurs a 0, sinon ils font n'importe quoi :(
  analogWrite(PIN_VENTILATEUR, 0);
  digitalWrite(PIN_LAMPE, 0);
  digitalWrite(PIN_ARROSAGE, 0);

 
}

// la boucle de controle arduino
void Board::loop(){
	Plante *cactus=new Plante;
	bool Vivant;
	char buf[100], buf3[100], buf2[100]; //buf3[100], buf4[100];
	float val_t, val_h, val_l; //val_c;
	static int cpt=0;
  
	
 for(int i=0;i<100;i++){ 			//a voir si on la garde, pas forcement utile
	 bool *MemoireLampe=new bool ;
	 *MemoireLampe= false;
	  int *CommandTab=new int[5];
	  for (int j=0;j<5;j++){
		  CommandTab[j]=0;
	  }
	  //val_t=Environnement::Get_temp();
	  val_t=analogRead(PIN_TEMPERATURE);
	  val_h=analogRead(PIN_HUMIDITE);
	  val_l=analogRead(PIN_LUMIERE);
    //val_c=analogRead(3);

	  
	  //Affichage valeurs environnement
     
	      
	      sprintf(buf,"temperature %f",val_t); 
	      sprintf(buf2,"luminosite %f",val_l);
	      sprintf(buf3,"humidite %f",val_h);
	      //sprintf(buf4,"CO2 %f",val_c);
	      
	      Serial.println(buf);
	      Serial.println(buf2);
	      Serial.println(buf3);
	      //Serial.println(buf4);

	      
	  if(cpt%5==0){
	          // tous les 5 fois on affiche sur l ecran la temperature
	        sprintf(buf,"Temperature : %f",val_t);
	        bus.write(1,buf,100);
	      }
	      
	      if(cpt%5==1){
	          // tous les 5 fois on affiche sur l ecran l'humidite  
	      	sprintf(buf3,"%f",val_h);
	          bus.write(1,buf3,100);
	       }
	      
	      
	      if(cpt%5==2){
	          // tous les 5 fois on affiche sur l ecran la luminosite  
	      	sprintf(buf2,"%f",val_l);
	          bus.write(1,buf2,100);
	          }
	      
/*
	      
	      if(cpt%5==3){
	          // tous les 5 fois on affiche sur l ecran la luminosite  
	      	sprintf(buf4,"%f",val_c);
	          bus.write(1,buf4,100);
	          }*/
	  
	  
	  //APpliation -> main

    /*
     * CommandTab : tableau d'entiers de la meme taille que le nb de capteurs.
     * CommandTab[0] -> fenetre. 			Valeurs : entre 0 et 50
     * CommandTab[1] -> chauffage			Valeurs : entre 0 et 10
     * CommandTab[2] -> ventilateur			Valeurs : entre 0 et 10
     * CommandTab[3] ->	lampe				Valeurs : 0 ou 1
     * CommandTab[4] ->	arrosage			Valeurs : 0 ou 1
     * */
    
    
    Vivant = MyApplication::main(cactus,CommandTab, MemoireLampe);
    if (!(Vivant)){
    	cout <<"exit la plante, vous n'avez pas la main verte !"<<endl;
    	exit(-1);
    }
    else {
    	
    
    //toujours le meme nombre d'actions -> 1 par actionneur.
    //1 action = soit eteindre l'actionneur, soit l'allumer ("le laisser tel qu'il est" = un de ces deux cas)
    //reste a transmettre la valeur a ecrire
    
    	
    for (int i=0;i<5;i++){
    	cout<<CommandTab[i]<<" ";
    }
    cout<<endl;
    //cout <<"commandeTab[1] : "<<CommandTab[1]<< " et commandTab[2]" <<CommandTab[2]<<endl;
    analogWrite(PIN_FENETRE, CommandTab[0]); 		//fenetre
    analogWrite(PIN_CHAUFFAGE, CommandTab[1]);		//chauffage ->0
    analogWrite(PIN_VENTILATEUR, CommandTab[2]); 	//ventilateur ->10
    analogWrite(PIN_LAMPE, CommandTab[3]); 			//lampe
    digitalWrite(PIN_ARROSAGE, CommandTab[4]);		//arrosage
    
    
    delete CommandTab;
    cpt++;
    sleep(1);

  }
  }

 
  //minuteur arrosage a tester. Si arrive a expiration, arreter l'arrosage
  
  
}


