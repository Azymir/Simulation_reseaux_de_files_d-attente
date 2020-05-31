#ifndef DEF_SERVEUR
#define DEF_SERVEUR

#include "Client.hh"
#include <iostream>
#include <stdexcept>
#include <list>

using namespace std;

class Client;

class Serveur{
	private:
		int ID_SERVEUR;
		Client* client_actuel;
		int tps_utilisation;

	public:
		//Constructeur
		Serveur(const int ID_SERVEUR);
		//Destructeur
		~Serveur();
		
		//Accesseurs
		int getIDServeur();
		Client& getClient();
		int getTpsUtilisation();
		
		//Fait entrer le client passé en paramètre
		void Entrer_Client(Client* C);
		//Retourne le client dans client_actuel et le passe à nullptr
		Client* Sortir_client();
		//Surcharge de l'opérateur <<
		friend ostream& operator << (ostream& flux, Serveur const& s);
	
};


#endif 
