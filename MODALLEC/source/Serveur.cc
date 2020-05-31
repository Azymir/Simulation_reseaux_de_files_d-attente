#include "Serveur.hh"

//Constructeur
Serveur::Serveur(const int ID_SERVEUR):ID_SERVEUR(ID_SERVEUR), client_actuel(nullptr), tps_utilisation(0){
	try{
		if(ID_SERVEUR < 0) throw invalid_argument("Constructeur de Serveur : ID ou Tps ou client négatif\n");
	}
    catch(string const& chaine)
    {
       cerr << chaine << endl;
    }
}

//Destructeur
Serveur::~Serveur(){
	if (client_actuel != nullptr) {delete client_actuel;}
}

//Accesseurs
int Serveur::getIDServeur(){
	return ID_SERVEUR;
}
Client& Serveur::getClient(){
	return *client_actuel;
}
int Serveur::getTpsUtilisation(){
	return tps_utilisation;
}

//Méthodes
void Serveur::Entrer_Client(Client* C){
	client_actuel = C;
	//On ajoute le temps de service du client au temps d'utilisation du serveur
	tps_utilisation += C->getTps_service();
}

Client* Serveur::Sortir_client(){
	try
	{
		if(client_actuel == nullptr) throw runtime_error("Serveur.Sortir_client : client_actuel est vide\n");
		else
		{
			Client* tmp = client_actuel;
			client_actuel = nullptr;
			return tmp;
		}
	}
	catch(string const& chaine)
	{
	    cerr << chaine << endl;
	}
	return nullptr;	
}

ostream& operator << (ostream& flux, Serveur const& s){
	flux <<"ID du serveur :"<<s.ID_SERVEUR 
		 <<"\ntps_utilisation :"<<s.tps_utilisation;
	
	if(s.client_actuel != nullptr)
		flux<<"\nID du client actuel :"<<s.client_actuel->getID_client();
		
	flux<<endl;
	return flux;
}


