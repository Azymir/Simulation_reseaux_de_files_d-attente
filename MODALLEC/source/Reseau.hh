#ifndef DEF_RESEAU
#define DEF_RESEAU

#include "File.hh"
#include "ClasseClient.hh"
#include <iostream>
#include <stdexcept>
#include <list>
#include <iterator>


using namespace std;

class Reseau{

	private : 
		//0 pour fermé, 1 pour ouvert
		int type_reseau;
		int nb_clients;
		int nb_clients_passes;
		int nb_files;
		int nb_classes;
		//Liste des files
		list<File*> liste_File;
		//Liste des classes
		list<ClasseClient*> liste_ClasseClient;
		//Liste des clients à router pendant le routage
		list<Client*> liste_ClientARouter;
		
	public :
		//Constructeur
		Reseau();
		//Destructeur
		~Reseau();
		
		//Accesseurs
		int getTypeReseau();
		int getNbFiles();
		int getNbClasses();
		int getNbClients();
		int getNbClientsPasses();
		list<File*>& getListeFile();
		list<Client*>& getListeClientARouter();
		list<ClasseClient*>& getListeClasseClient();

		void setNbClients (const int nombre);
		void setNbClientsPasses(const int nombre);
		void setTypeReseau(const int type);
	
		//Retourne la file par son identifiant
		File * chercherFile(int IDFile);
		//Ajoute la file en paramètre à liste des files
		void ajouter_file(File* f);
		//Ajoute le client en paramètre à liste des client à router
		void ajouter_client_routage(Client* client);
		//Supprime la file ayant pour identifiant la valeur en paramètre
		void supprimer_file(const int ID_file);
		//Supprime tout les éléments de la liste de routage
		void vider_liste_routage();
		//Ajoute une classe à la liste des classes
		void ajouter_classe(ClasseClient* classe);
		//Supprime la classe ayant pour identifiant la valeur en paramètres
		void supprimer_classe(const int ID_classe);
		//Surcharge de l'opérateur <<
		friend ostream& operator << (ostream& flux, Reseau const& r);

};

#endif
