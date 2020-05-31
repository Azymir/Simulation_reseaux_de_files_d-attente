#ifndef DEF_FILE
#define DEF_FILE


#include <stdexcept>
#include "Client.hh"
#include "Serveur.hh"
#include <list>

//Déclaration de la classe Serveur et Client pour empêcher des références croisées
class Serveur;
class Client;

using namespace std;

//Structure contenant des coordonnées pour placer la file sur l'interface
typedef struct coordonnees{
    int x;
    int y;
}coordonnees;


//Structure contenant une valeur à une date, sert aux calculs de performances
typedef struct mesure {
    int valeur;
    int date;
}mesure;


class File{
	private :
	 
		int ID_file;   
		int nb_clients;
		int taille_max;
		int nb_clients_servis;
		int nb_clients_presentes;
		float tps_service_moyen;	
		float tps_attente_moyen;	
		//Nombre de client entrés dans la file durant toute la simulation
		int nb_clients_entres;
		//Nombre de client entrés dans la date actuelle
		int nb_clients_entres_actuel; 
		coordonnees centre;
		int ordonnancement;
		int loi_service;
		int distribution_arrivee;
		//Liste de client
		list<Client*> liste_clients;
		//Liste du nombre de clients
		list <mesure> liste_nbClients;
		//Liste du nombre de clients entrés à la date actuelle
		list <mesure>  liste_nbClientsEntres ;
		//Liste des serveurs
		list<Serveur*>liste_serveurs;
	public :
		
		//Constructeur
		File(const int ID, const int abs, const int ord);
		//Constructeur par recopie 
		File(File& f); 
		//Destructeur
		~File(); 
		
		//Accesseurs
		int getIDFile() const;
		int getNbClients() const;
		int getTailleMax() const;
		int getNbClientsServis() const;
		int getNbClientsPresentes() const;
		float getTpsServiceMoy() const;
		float getTpsAttenteMoy() const;
		int getNbClientsEntres() const;
		int getNbClientsEntresActuel() const;
		coordonnees getCoord() const;
		int getOrdonnancement() const;
		int getLoi_service() const;
		int getDistribution_arrivee() const;
		list<Client*>& getListeClients() ;
		list<Serveur*>& getListeServeur();
		list<mesure>&  getListeNbClients();
		list<mesure>& getListeNbClientsEntres();
		
		void setTailleMax(const int nombre);
		void setOrdonnancement(const int numero);
		void setLoiService(const int numero);
		void setDistribution(const int numero);
		void setCoordonnees(coordonnees c);
		void setNbClientsEntresActuel(const int nombre);
		void setNbClientsEntres(const int nombre);
		void setNbClientsPresentes(const int nombre);
		void setNbClients(const int nombre);
		void setNbClientsServis(const int nombre);
		void setTempsAttenteMoyen(float temps);
		void setTempsServiceMoyen(float temps);
		
		//Va ordonnancer le client dans la file selon l'ordonnancement en appellant la bonne méthode
		void ordonnancer_clients(Client& client);
		
		//Ajoute à la fin 
		void FIFO(Client& client);
		//Ajoute au début
		void LIFO(Client& client);
		//Ajoute en fonction de la priorité
		void PRIO(Client& client);	
		//Place le client dans une position aléatoire
		void RANDOM(Client& client);	
		
		//Si on change l'ordonnancement en priorité, on retrie la file 
		void trier_priorite_file(); 	
		//Sort le premier client de la liste
		void sortir_client(); 	
		//Ajoute un serveur à la liste des serveurs
		void ajouter_serveur(Serveur& s);
		//Supprime le serveur avec son identifiant en paramètre
		void supprimer_serveur(const int ID_serveur);
		//Ajoute le client en paramètre à la liste des clients
		void ajouter_client(Client& client);
		//Ajoute un élément mesure à liste du nombre de client
		void ajouter_mesure_nb_clients_entres(const int nb_clients_entres, const int tps);
		//Ajoute un élément mesure à liste du nombre de clients entrés
		void ajouter_mesure_nb_clients (const int nb_clients, const int tps);
		//Actualise le temps d'attente des clients à la date actuelle
		void actualiser_tps_attente_clients (const int date_actuelle);
		//Actualise le temps d'attente moyen avec le temps d'attente du client entrant dans le serveur 
		void calcul_temps_attente_moy(const int tps_attente_client_entrant_serveur);
		//Actualise le temps de service moyen avec le temps de service du client entrant dans le serveur 
		void calcul_temps_service_moy(const int tps_service_client_entrant_serveur);
		
		//Surcharge de l'opérateur =
		File& operator = (File const& f);
		//Surcharge de l'opérateur <<
		friend ostream& operator << (ostream& flux, File const& f);
	};




#endif
