#include "Client.hh"

//Constructeur
Client::Client(const int ID, ClasseClient * c){
	try {
		if(ID < 0) throw invalid_argument("Constructeur de Client : ID négatif");
		else{
			ID_client = ID;
			tps_service = 0 ;
			tps_attente = 0;
			pos_actuel_routage = 0 ;
			date_arrivee_file = 0;
			classe = c;
			classe->setNbClients(classe->getNbClients()+1);
		}
	}
	catch(string const& chaine)
    {
       cerr << chaine << endl;
    }
}

//Destructeur
Client::~Client(){
	if(classe != NULL) classe->setNbClients(classe->getNbClients()-1);
}

//Accesseurs
int Client::getID_client(){
	return ID_client;
}
int Client::getTps_attente(){
	return tps_attente;
}
int Client::getTps_service(){
	return tps_service;
}
ClasseClient* Client::getClasse(){
	return classe;
}
int Client::getFileActuelle(){
	return classe->trouver_file(pos_actuel_routage);
}
int Client::getPositionActuelle()
{
	return pos_actuel_routage;
}

int Client::getDateArriveeFile(){
	return date_arrivee_file;
}

void Client::setDateArrivee(const int newDate){
	try {
		if(newDate < 0) throw invalid_argument("Client.setDateArrivee : newDate négatif");
		else
		date_arrivee_file = newDate;
	}
	catch(string const& chaine)
    {
       cerr << chaine << endl;
    }
}

void Client::setPositionActuelle(const int numero){
	try {
		if(numero < 0) throw invalid_argument("Client.setPositionActuelle : numero négatif");
		else
		pos_actuel_routage = numero;
	}
	catch(string const& chaine)
    {
       cerr << chaine << endl;
    }
}


//Méthodes
ostream& operator << (ostream &flux, Client const& c ){
	flux << "ID : " << c.ID_client
		<< "\ntemps de service : " << c.tps_service
		<< "\ntemps d'attente : " << c.tps_attente
		<< "\nposition actuelle du routage : " << c.pos_actuel_routage
		<< "\ndate d'arrivee de la file : " << c.date_arrivee_file
		<< endl;
	return flux;
}

void Client::modifier_tps_attente(const int date_actuelle){
	try {
		//On calcule le temps d'attente seulement si la date_actuelle est supérieure ou égale à la date d'arrivée de la file
		if(date_actuelle >= date_arrivee_file){
			tps_attente = date_actuelle - date_arrivee_file ;
		}
		//On lance une exception si la condition n'est pas vérifiée
		else throw std::invalid_argument("Client.modifier_tps_attente : Erreur date_actuelle");
	}
	catch(string const& chaine)
    {
       cerr << chaine << endl;
    }
}


void Client::calculer_tps_service(int loi_service, int distribution_arrivee){
	try
	{
		if(loi_service < -2) 
			throw invalid_argument("Client.calculer_tps_service : loi_service < -2" );
		if ((distribution_arrivee < -1) || (distribution_arrivee == 0))
			throw invalid_argument("Client.calculer_tps_service : distribution_arrivee < -1 ou = à 0" );

		switch(loi_service){
			//Si loi exponentielle
			case -1:
			{
				double u = 1.0;
				
				//On génère une valeur aléatoire entre 0 et 1 exclus
				while((u == 0.0) || (u == 1.0))
				{
					u = ((double) rand() / (RAND_MAX)); 	
				 }
				double lambda ;

				if(distribution_arrivee == -1)
					lambda = (rand() % 10)+1;			
				else
					lambda = distribution_arrivee;
					
				double c = (-1/lambda)* 10 * log(u) ;	

				//On fait un cast pour garder la partie entière
				int v = (int) c;
				//Si la valeur est inférieure à 1, on attribue 1
				if(v == 0) v=1;		
				tps_service = v;
				break;
			}
			//Si loi uniforme
			case-2:
			{
				tps_service = rand()%10 +1;
				break;
			}
			//Si la loi de service est constante
			default:
			{
				tps_service = loi_service;
			}
		}
	}
	catch(string const& chaine){
		cerr << chaine << endl;
	}
}
