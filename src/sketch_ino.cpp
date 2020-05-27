#define PIN_HUMIDITE 10
#define PIN_TEMPERATURE 9
#define PIN_LUMIERE 11
#define PIN_CO2 12
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
  pinMode(PIN_CO2,INPUT);

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
	char buf[1000];
	int val_t, val_h, val_l, val_c;


 for(int i=0;i<100;i++){ 			//a voir si on la garde, pas forcement utile
	 bool *MemoireLampe=new bool ;
	 *MemoireLampe= false;
	  int *CommandTab=new int[5];
	  for (int j=0;j<5;j++){
		  CommandTab[j]=0;
	  }

	  //recuperation valeurs capteurs
	  val_t=analogRead(PIN_TEMPERATURE);
	  val_h=analogRead(PIN_HUMIDITE);
	  val_l=analogRead(PIN_LUMIERE);
	  val_c=analogRead(PIN_CO2);

	  //Affichage valeurs environnement
	  	  cout<<endl;
	      sprintf(buf," Temperature : %d °C \n           Humidite : %d pour 100 \n           Luminosite : %d kilolux \n           CO2 : %d pour 1 0000",val_t, val_h,val_l, val_c);
	      bus.write(1,buf,1000);

	  //HappySeed -> main

    /*
     * CommandTab : tableau d'entiers de la meme taille que le nb de capteurs.
     * CommandTab[0] -> fenetre. 			Valeurs : entre 0 et 50
     * CommandTab[1] -> chauffage			Valeurs : entre 0 et 10
     * CommandTab[2] -> ventilateur			Valeurs : entre 0 et 10
     * CommandTab[3] ->	lampe				Valeurs : 0 ou 1
     * CommandTab[4] ->	arrosage			Valeurs : 0 ou 1
     * */


    Vivant = HappySeed ::main(val_t, val_h, val_l, val_c, cactus,CommandTab, MemoireLampe);
    if (!(Vivant)){
    	cout <<"Adieu la plante, vous n'avez pas la main verte !"<<endl;
    	exit(-1);
    }
    else {


    //toujours le meme nombre d'actions -> 1 par actionneur.
    //1 action = soit eteindre l'actionneur, soit l'allumer ("le laisser tel qu'il est" = un de ces deux cas)
    //reste a transmettre la valeur a ecrire

    cout <<"Tableau actionneur :";	
    for (int i=0;i<5;i++){
    	cout<<CommandTab[i]<<" ";
    }
    cout<<endl;
    cout <<endl;
    analogWrite(PIN_FENETRE, CommandTab[0]); 		//fenetre
    analogWrite(PIN_CHAUFFAGE, CommandTab[1]);		//chauffage ->0
    analogWrite(PIN_VENTILATEUR, CommandTab[2]); 	//ventilateur ->10
    analogWrite(PIN_LAMPE, CommandTab[3]); 			//lampe
    digitalWrite(PIN_ARROSAGE, CommandTab[4]);		//arrosage

    delete CommandTab;
    sleep(3);

  }
  }


  //minuteur arrosage a tester. Si arrive a expiration, arreter l'arrosage


}


