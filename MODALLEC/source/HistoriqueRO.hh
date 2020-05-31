#ifndef HISTORIQUERO_HH
#define HISTORIQUERO_HH

#include <iostream>
#include <list>
#include "PerfsRO.hh"
#include "PerfsFile.hh"

using namespace std;

/**Structure de sauvegarde des performances d'un réseau fermé à une date donnée**/
typedef struct performancesRO{
	PerfsRO* perfReseau;
	list <PerfsFile*> ListePerfsFiles;
}PerformancesRO;

class HistoriqueRO{
	private:
		list <PerformancesRO> historique;

	public:
		/**Constructeur**/
		HistoriqueRO ();
		/**Destructeur**/
		~HistoriqueRO();
		/**Méthode de récupération de la liste contenant l'historique
		@return une référence sur cette liste
		**/
		list <PerformancesRO>& getHistorique ();
		/**Méthode d'ajout d'un élément dans la liste en initialisant le champ ajouterPerfsReseau
		@param pr, l'objet PerfsRO à garder
		**/
		void ajouterPerfsReseau (PerfsRO& pR);
		/**Méthode d'ajout des performances d'une file à l'historique
		@param f, la file dont il faut garde les performances
		@param duree_simulation, la durée de la simulation
		**/
		void ajouterPerfsFile (File& f,const int duree_simulation);									
		/**Surcharge de l'opérateur <<
		@param flux, le flux de sortie pour l'affichage
		@param H, l'objet HistoriqueRF à afficher
		**/
		friend ostream& operator <<(ostream& flux , HistoriqueRO const& H) ;


};

#endif
