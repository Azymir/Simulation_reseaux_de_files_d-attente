#ifndef PERFSRF_HH
#define PERFSRF_HH

#include "DonneesCalculsRF.hh"
#include <ostream>
#include <stdexcept>
#include <list>

using namespace std;

class PerfsRF{

	protected:
		int nb_moyen_clients;
		int date;

	public:
		/**Constructeur
		@param date, la date de calcul des performances d'un réseau fermé
		**/
		PerfsRF(const int date);
		/**Constructeur de recopie
		@param p, une référence sur un objet de type PerfsRF
		**/
		PerfsRF(PerfsRF const& p);
		/**Destructeur**/
		~PerfsRF();
		/**Méthode de récupération du nombre moyen de clients dans le réseau**/
		int getNbMoyenClients();
		/**Méthode de récupération de la date de calcul des performances d'un réseau fermé**/
		int getDate();
		/**Méthode de calcul du nombre moyen de clients dans le réseau
		@param listNbClients, la liste de mesures du nombre de clients dans le réseau à un instant donné**/
		void calcul_nb_moyen_clients(list <mesure>& listNbClients);
		/**Surcharge de l'opérateur << pour afficher les données d'un objet de la classe
		@param flux, le flux de sortie pour l'affichage
		@param perfs, l'objet dont les données sont à afficher
		**/
		friend ostream& operator <<(ostream& flux , PerfsRF const& perfs) ;
		/**Surcharge de l'opérateur =
		@param p, objet de type PerfsRF à copier
		@return une référence correspondant à un objet avec ses attributs copiés de l'objet en paramètre
		**/
		PerfsRF& operator = (PerfsRF const& p);
};

#endif
