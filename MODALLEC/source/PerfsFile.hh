#ifndef PERFSFILE_HH
#define PERFSFILE_HH

#include "File.hh"
#include <ostream>
#include <stdexcept>

using namespace std;

/**Structure pour sauvegarder le taux d'utilisation des serveurs de la file**/
typedef struct PerfServeur {
	int numero_serveur;
	float taux_utilisation;
}PerfServeur;


class PerfsFile{
	private:
		File * file;			
		int date;
		int nb_moyen_clients_file;
		float tps_attente_moyen;
		float tps_service_moyen;
		float tps_reponse_moyen;
		list <PerfServeur> ListeResPerfServeur;
		float tps_interarrivee_moyen;
		float taux_perte; //A ajouter au compte-rendu

	public:
		/**Constructeur
		@param f, la file dont les performances sont à calculer
		@param date, la date de calcul des performances
		**/
		PerfsFile (File& f, const int date);
		/**Constructeur de recopie
		@param perfs, l'objet PerfsFile à acheter
		**/
		PerfsFile (PerfsFile& perfs); //Plus de const car problème avec le constructeur de recopie de File
		/**Destructeur**/
		~PerfsFile();
		/**Méthode de récupérattion de la date de calcul des performances
		@return un entier correspondant à la date
		**/
		int getDate ();
		/**Méthode de récupération de la file dont les performances sont calculées
		@return une référence sur la file
		**/
		File& getFile ();
		/**Méthode de récupération du nombre moyen de clients dans la file
		@return un entier correspondant au nombre moyen de clients dans la file
		**/
		int getNbMoyenClientsFile ();
		/**Méthode de récupération du temps attente moyen dans la file
		@return un flottant correspondant au temps d'attente
		**/
		float getTpsAttenteMoy ();
		/**Méthode de récupération du temps de service moyen dans la file
		@return un flottant correspondant au temps de service
		**/
		float getTpsServiceMoy ();
		/**Méthode de récupération du temps de réponse moyen de la file
		@return un flottant correspondant au temps de réponse moyen
		**/
		float getTpsReponseMoy ();
		/**Méthode de récupération de la liste de performances des serveurs de la file
		@return une référence sur cette liste
		**/
		list <PerfServeur>& getListeResPerfServeur ();

		/**Méthode de récupération du temps d'inter-arrivée moyen de la file
		@return un flottant correspondant à ce temps d'inter-arrivée moyen
		**/
		float getTpsinterarriveeMoy ();

		/**Méthode de récupération du taux de perte de la file
		@return un entier correspondant au taux de perte
		**/
		float getTauxPerte ();	//A ajouter au compte-rendu

		/**Méthode de calcul du nombre moyen de clients dans la file**/
		void calcul_nb_moyen_clients_file ();
		/**Méthode de calcul du temps d'attente moyen dans la file**/
		void calcul_tps_attente_moyen ();
		/**Méthode de calcul de temps de service moyen dans la file**/
		void calcul_tps_service_moyen ();
		/**Méthode de calcul du temps de réponse moyen de la file**/
		void calcul_tps_reponse_moyen ();
		/**Méthode de calcul du taux d'utilisation des serveurs de la file
		@param duree_simulation, la duree de la simulation
		**/
		void calcul_taux_utilisation_serveurs (const int duree_simulation);
		/**Méthode de calcul du temps d'inter-arrivée moyen**/
		void calcul_tps_interarrivee_moyen ();
		/**Méthode de calcul du taux de perte de la file**/
		void calcul_taux_perte ();
		/**Surcharge de l'opérateur <<
		@param flux, le flux de sortie pour l'affichage
		@param perfs, l'objet PerfsFile à afficher
		**/
		friend ostream& operator <<(ostream& flux , PerfsFile const& perfs) ;
		/**Surcharge de l'opérateur =
		@param p, un objet PerfsFile dont les attributs sont à copier
		@return une référence sur l'objet avec ses attributs
		modifiés avec ceux de l'objet passé en paramètre
		**/
		PerfsFile& operator = ( PerfsFile const& p) ;


};

#endif
