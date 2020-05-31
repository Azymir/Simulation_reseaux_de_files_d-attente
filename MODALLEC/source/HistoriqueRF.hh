#ifndef HISTORIQUERF_HH
#define HISTORIQUERF_HH

#include <iostream>
#include <list>
#include "PerfsRF.hh"
#include "PerfsFile.hh"

using namespace std;

/**Structure de sauvegarde des performances d'un réseau fermé à une date donnée**/
struct performancesRF{
	PerfsRF* perfReseau;
	list <PerfsFile*> ListePerfsFiles; //Ajout d'une étoile car pas de constructeur par défaut pour PerfsFile
};

typedef struct performancesRF PerformancesRF;

class HistoriqueRF{
	private:
		list <PerformancesRF> historique;

	public:
		/**Constructeur**/
		HistoriqueRF ();
		/**Destructeur**/
		~HistoriqueRF();
		/**Méthode de récupération de la liste contenant l'historique
		@return une référence sur cette liste
		**/
		list <PerformancesRF>& getHistorique ();
		/**Méthode d'ajout d'un élément dans la liste en initialisant le champ ajouterPerfsReseau
		@param pr, l'objet PerfsRF à garder
		**/
		void ajouterPerfsReseau (PerfsRF& pR);
		/**Méthode d'ajout des performances d'une file à l'historique
		@param f, la file dont il faut garde les performances
		@param duree_simulation, la durée de la simulation
		**/
		void ajouterPerfsFile (File& f,const int duree_simulation);									//Ajout de la durée de simulation pour le calcul du taux d'utilisation pour chaque serveur
		/**Surcharge de l'opérateur <<
		@param flux, le flux de sortie pour l'affichage
		@param H, l'objet HistoriqueRF à afficher
		**/
		friend ostream& operator <<(ostream& flux , HistoriqueRF const& H) ;


};

#endif
