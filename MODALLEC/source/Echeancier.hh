#ifndef DEF_ECHEANCIER
#define DEF_ECHEANCIER

#include <iostream>
#include "File.hh"
#include <list>
#include <stdexcept>

using namespace std;

//Structure correspondant à un événement avec ses caractéristiques
typedef struct evenement
{
	int type_evenement;
	int date_traitement;
	File* file_destinee;
	Serveur* serveur_destine;
	Client* client;
} Evenement;

//Structure contenant un boolean qui sert à la fonction de tri des événements
struct compare_evenement{
    bool operator()(const Evenement &E1, const Evenement &E2)
    {
       return E1.date_traitement < E2.date_traitement;
    }
};

class Echeancier{

	private :
		//Liste des événements
		list <Evenement> liste_evenement;
		//Date actuelle
		int date_actuelle;

	public :
		//Constructeur
		Echeancier();
		//Destructeur
		~Echeancier();

		//Accesseurs
		list <Evenement>& getListeEvenement();
		int getDateActuelle();
		void setDateActuelle(const int date);

		//Méthodes

		//Ajouter un événement
		void ajouter_evenement(Evenement& event);
		//Renvoie du prochain événement et mise à jour de l'horloge à la date du prochain événement
		Evenement sortir_prochain_evenement();
		//Supprime tout les événements relatifs à la file ayant pour ID num_file
		void supprimer_evenement_file(const int num_file);
		//Supprime tout les événements relatifs au serveur ayant pour ID num_serveur
		void supprimer_evenement_serveur(const int num_serveur);
		//Tri les événements dans l'ordre croissant de leur date de traitement
		void trier_croissant();
		//Surcharge de l'opérateur <<
		friend ostream& operator << (ostream& flux, Echeancier const& e);
};

#endif
