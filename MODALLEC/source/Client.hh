#ifndef DEF_CLIENT
#define DEF_CLIENT

#include <iostream>
#include <cmath>
#include "File.hh"
#include "ClasseClient.hh"
#include <stdexcept>

using namespace std;

//Déclaration de la classe File et ClasseClient pour empêcher des références croisées
class ClasseClient;
class File;

class Client{

	private :
	
		int ID_client ;
		ClasseClient * classe;
		int tps_service ;
		int tps_attente ;
		//Correspond à sa position dans le routage
		int pos_actuel_routage;
		//Date à laquelle le client est entré dans la file actuelle
		int date_arrivee_file;

	public :
		//Constructeur
		Client(const int ID, ClasseClient * c);
		//Destructeur
		~Client();
		
		//Accesseurs
		int getID_client();
		int getTps_attente();
		int getTps_service();
		ClasseClient* getClasse();
		int getFileActuelle();
		int getDateArriveeFile();
		int getPositionActuelle();
		void setDateArrivee(const int newDate);
		void setPositionActuelle(const int numero);
		
		//Surcharge de l'opérateur <<
		friend ostream& operator << (ostream &flux, Client const& c );
		//Va actualiser le temps d'attente en fonction de la date actuelle et de sa date d'arrivée dans la file
		void modifier_tps_attente(const int date_actuelle);
		//Va calculer le temps de service du client quand il rentre dans la file en fonction des caractéristiques de la file
		void calculer_tps_service(int loi_service, int distribution_arrivee);

};
#endif
