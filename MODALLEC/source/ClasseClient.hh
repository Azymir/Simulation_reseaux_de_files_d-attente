#ifndef DEF_CLASSECLIENT
#define DEF_CLASSECLIENT

#include <vector> 
#include <iostream>
#include "File.hh"
#include <string>
#include <stdexcept> 
#include <regex>


using namespace std;

//Déclaration de la classe File pour empêcher des références croisées
class File;

class ClasseClient{

	private:
		int IDClasseClient;
		//Liste contenant le routage
		vector <int> routage;
		int priorite;
		int nbClients;

	public:
		//Constructeur
		ClasseClient(const int ID, const int priorite);
		//Destructeur
		~ClasseClient();
		
		//Accesseurs
		int getIDClasseClient();
		int getNbClients();
		vector <int> getRoutage();
		int getPriorite();
		void setPriorite(const int numero);
		void setNbClients(const int nombre);
		
		//Supprime les files ayant pour ID IDfile
		void supprimer_file_routage(const int IDfile);
		//Définit le routage sous la forme d'un string (1-2-3 , où 1,2,3 sont les identifiants de 3 files)
		void definir_routage(const string newRoutage);
		//Renvoie l'identifiant de la file à la position actuelle
		int trouver_file(const int pos_actuelle);
		//Renvoie la prochaine file par rapport à la position actuelle
		int prochaine_file_routage(const int pos_precedente);
		//Surcharge de l'opérateur <<
		friend ostream& operator << (ostream &flux, ClasseClient const& cc);

};

#endif
