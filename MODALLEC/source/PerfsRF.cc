#include "PerfsRF.hh"

/**Constructeur
@param date, la date de calcul des performances d'un réseau fermé
**/
PerfsRF :: PerfsRF(const int date){

	try{
		if(date < 0) throw invalid_argument("Constructeur PerfsRF : date négative en paramètre");
		else{
			nb_moyen_clients= 0;
			this->date = date;
		}
	}
	catch(string const& chaine){
       cerr << chaine << endl;
  }
}

/**Constructeur de recopie
@param p, une référence sur un objet de type PerfsRF
**/
PerfsRF :: PerfsRF(PerfsRF const& p){
	nb_moyen_clients = p.nb_moyen_clients;
	date = p.date;
}

/**Destructeur**/
PerfsRF :: ~PerfsRF(){}


/**Méthode de récupération du nombre moyen de clients dans le réseau**/
int PerfsRF :: getNbMoyenClients(){
	return nb_moyen_clients;
}

/**Méthode de récupération de la date de calcul des performances d'un réseau fermé**/
int PerfsRF :: getDate(){
	return date;
}

/**Méthode de calcul du nombre moyen de clients dans le réseau
@param listNbClients, la liste de mesures du nombre de clients dans le réseau à un instant donné**/
void PerfsRF :: calcul_nb_moyen_clients(list <mesure>& listNbClients){

	//Récupérer la somme du nombre de clients des mesures
	float total_clients_reseau = 0;
	//Compter le nombre de mesures
	float nb_mesures = 0;

	//Défiler la liste de mesures
	for(auto i=listNbClients.begin(); i!=listNbClients.end(); i++){
		total_clients_reseau += (*i).valeur;
		nb_mesures += 1;
	}

	//Affecter le résultat du calcul à l'attribut correspondant
	if(nb_mesures != 0) this->nb_moyen_clients = total_clients_reseau/nb_mesures;
	else this->nb_moyen_clients = 0;

}

/**Surcharge de l'opérateur << pour afficher les données d'un objet de la classe
@param flux, le flux de sortie pour l'affichage
@param perfs, l'objet dont les données sont à afficher
**/
ostream& operator <<(ostream& flux , PerfsRF const& perfs){

	flux << "Performances du réseau fermé : " << endl;
	flux << "Date des calculs :" << perfs.date << endl;
	flux << "Nombre moyen de clients : " << perfs.nb_moyen_clients <<endl;

	return flux;
}

/**Surcharge de l'opérateur =
@param p, objet de type PerfsRF à copier
@return une référence correspondant à un objet avec ses attributs copiés de l'objet en paramètre
**/
PerfsRF& PerfsRF::operator = (PerfsRF const& p){

	nb_moyen_clients = p.nb_moyen_clients;
	date = p.date;

	return *this;
}
