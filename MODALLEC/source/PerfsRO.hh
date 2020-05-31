#ifndef PERFSRO_HH
#define PERFSRO_HH

#include "PerfsRF.hh"
#include "DonneesCalculsRO.hh"
#include <ostream>

using namespace std;


class PerfsRO : public PerfsRF{

	private:
		int debit_entree;
		int debit_sortie;
		float tps_sejour_moyen;

	public:
		/**Constructeur
		@param date, la date de calcul des performances d'un réseau ouvert
		**/
		PerfsRO (const int date);
		/**Constructeur de recopie
		@param p, l'objet à copier
		**/
		PerfsRO (PerfsRO const& p);
		/**Destructeur**/
		~PerfsRO();
		/**Méthode de récupération du débit d'entrée du réseau**/
		int getDebitEntree();
		/**Méthode de récupération du débit de sortie du réseau**/
		int getDebitSortie();
		/**Méthode de récupération du temps de séjour moyen**/
		float getTpsSejourMoyen();
		/**Méthode de calcul du temps séjour moyen
		@param ListeTSClient, la liste des temps de séjour des clients dans le réseau
		**/
		void calcul_tps_sejour_moyen (list <TSClient>& ListeTSClient);
		/**Méthode de calcul du débit d'entrée du réseau
		@param ListeNbClientEntrant, la liste de mesures du nombre de clients entrés dans le réseau
		**/
		void calcul_debit_entree (list <mesure>& ListeNbClientEntrant);
		/**Méthode de calcul du débit sortant
		@param ListeNbClientSortant, la liste de mesures du nombre de clients sortants dans le réseau
		**/
		void calcul_debit_sortie (list <mesure>& ListeNbClientSortant);
		/**Surcharge de l'opérateur <<
		@param flux, flux de sortie de l'affichage
		@param perfs, objet PerfsRO dont les données sont à afficher
		**/
		friend ostream& operator <<(ostream& flux , PerfsRO const& perfs) ;
		/**Surcharge de l'opérateur =
		@param p, l'objet PerfsRO à copier
		@return une référence sur un objet PerfsRO avec ses attributs initialisés aux attributs de l'objet en paramètre
		**/
		PerfsRO& operator = ( PerfsRO const& p ) ;
	};

#endif
