#ifndef DEF_DONNEES_CALCULS_RO
#define DEF_DONNEES_CALCULS_RO



#include "DonneesCalculsRF.hh"
#include <iostream>
#include <stdexcept>


using namespace std;

//Structure contenant les dates d'entrées et de sortie dans le réseau pour un client
typedef struct TSClient{
	int numero_client;
	int date_entree;
	int date_sortie;
	int tps_sejour;
}TSClient;



class DonneesCalculsRO : public DonneesCalculsRF {

	private :

		list<mesure> listeNbClientsEntrant ;
		list <mesure> listeNbClientSortant ;
		list <TSClient> listeTSClient;

	public :

		DonneesCalculsRO() ;
		~DonneesCalculsRO();

		list <mesure>& getListeNbClientEntrant();
		list <mesure>& getListeNbClientSortant();
		list <TSClient>& getListeClientEntres();

		//Va ajouter une mesure avec les champs en paramètre à listeNbClientsEntrants
		void ajouterMesuresNbclientsEntrants (const int nb_clients_entres, const int temps) ;
		//Idem pour listeNbClientsSortants
		void ajouterMesureNbClientsSortants (const int nb_clients_sortis, const int temps);
		//AJoute un élément TSClient initialisés avec les champs en paramètres
		void ajouter_element_TSclient(const int IDClient, const int date_entree);
		//Calcul le temps de séjour d'un client en fonction de sa date de sortie et l'affecte au TSClient correspondant
	  void calcul_tps_sejour_client(const int IDClient, const int date_sortie);
		friend ostream& operator << (ostream& flux, DonneesCalculsRO const& d);

};


#endif
