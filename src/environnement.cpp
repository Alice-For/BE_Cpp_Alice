#include "environnement.h"

using namespace std;

Environnement::Environnement(){
	luminosity=200.0;
	temperature =22.5;
	CO2 = 0.0003;
	humidity = 0.40; // sol = terre
}

float Environnement::Get_lum(){	
	return luminosity;
}

float Environnement::Get_CO2(){	
	return CO2;
}

float Environnement::Get_hum(){	
	return humidity;
}

float Environnement::Get_temp(){
	return temperature;
}
