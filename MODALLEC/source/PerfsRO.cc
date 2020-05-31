#include "PerfsRO.hh"

/**Constructeur
@param date, la date de calcul des performances d'un réseau ouvert
**/
PerfsRO :: PerfsRO (const int date) : PerfsRF(date){
	try{
		if(date < 0) throw invalid_argument("Constructeur PerfsRF : date négative en paramètre");
		else{
			debit_entree= 0;
			debit_sortie= 0;
			tps_sejour_moyen = 0.0;
		}
	}
	catch(string const& chaine){
		cerr << chaine << endl;
	}
}

/**Constructeur de recopie
@param p, l'objet à copier
**/
PerfsRO :: PerfsRO (PerfsRO const& p) : PerfsRF(p){
	debit_entree= p.debit_entree;
	debit_sortie= p.debit_sortie;
	tps_sejour_moyen = p.tps_sejour_moyen;
}

/**Destructeur**/
PerfsRO :: ~PerfsRO(){}

/**Méthode de récupération du débit d'entrée du réseau**/
int PerfsRO :: getDebitEntree(){
	return debit_entree;
}

/**Méthode de récupération du débit de sortie du réseau**/
int PerfsRO :: getDebitSortie(){
	return debit_sortie;
}

/**Méthode de récupération du temps de séjour moyen**/
float PerfsRO :: getTpsSejourMoyen(){
	return tps_sejour_moyen;
}

/**Méthode de calcul du temps séjour moyen
@param ListeTSClient, la liste des temps de séjour des clients dans le réseau
**/
void PerfsRO :: calcul_tps_sejour_moyen (list <TSClient>& ListeTSClient ){

	//Créer pour sommer les temps de séjour se trouvant dans les éléments de la liste en paramètre
	float tot_temps_sejour = 0;
	//Créer pour sommer le nombre de mesures dans la liste
	float nb_clients_sortis = 0;

	//Pour chaque mesure de la liste
	for (auto i= ListeTSClient.begin(); i != ListeTSClient.end(); i++){
		tot_temps_sejour += (*i).tps_sejour;
		nb_clients_sortis += 1;
	}

	//Affecter le résultat du calcul à l'attribut correspondant
	if(nb_clients_sortis != 0) this->tps_sejour_moyen = tot_temps_sejour/nb_clients_sortis;
	else this->tps_sejour_moyen = 0;
}

/**Méthode de calcul du débit d'entrée du réseau
@param ListeNbClientEntrant, la liste de mesures du nombre de clients entrés dans le réseau
**/
void PerfsRO :: calcul_debit_entree (list <mesure>& ListeNbClientEntrant){

	//Créer pour sommer le nombre de clients entrés des éléments de la liste en paramètre
	int total_clients = 0;
	//Créer pour compter le nombre de mesures dans la liste
	int nb_mesures = 0;

	//Pour chaque mesure de la liste
	for (auto i= ListeNbClientEntrant.begin(); i!= ListeNbClientEntrant.end(); i++){
		total_clients += (*i).valeur;
		nb_mesures += 1;
	}

	//Affecter le résultat du calcul à l'attribut correspondant
	if(nb_mesures != 0) this->debit_entree = total_clients/nb_mesures;
	else this->debit_entree = 0;

}

/**Méthode de calcul du débit sortant
@param ListeNbClientSortant, la liste de mesures du nombre de clients sortants dans le réseau
**/
void PerfsRO :: calcul_debit_sortie (list <mesure>& ListeNbClientSortant){

	//Créer pour sommer le nombre de clients sortants des éléments de la liste en paramètre
	int total_clients = 0;
	//Créer pour compter le nombre de mesures dans la liste
	int nb_mesures = 0;

	//Pour chaque mesure de la liste
	for (auto i= ListeNbClientSortant.begin(); i != ListeNbClientSortant.end(); i++){
		total_clients += (*i).valeur;
		nb_mesures += 1;
	}

	//Affecter le résultat du calcul à l'attribut correspondant
	if(nb_mesures != 0) this->debit_sortie= total_clients/nb_mesures;
	else this->debit_sortie = 0;
}

/**Surcharge de l'opérateur <<
@param flux, flux de sortie de l'affichage
@param perfs, objet PerfsRO dont les données sont à afficher
**/
ostream& operator <<(ostream& flux , PerfsRO const& perfs){

	flux << "Performances du réseau fermé : " << endl;
	flux << "Date des calculs :" << perfs.date << endl;
	flux << "Nombre moyen de clients : " << perfs.nb_moyen_clients <<endl;
	flux << "Débit d'entrée : " << perfs.debit_entree <<endl;
	flux << "Débit de sortie : " << perfs.debit_sortie <<endl;

	return flux;
}

/**Surcharge de l'opérateur =
@param p, l'objet PerfsRO à copier
@return une référence sur un objet PerfsRO avec ses attributs initialisés aux attributs de l'objet en paramètre
**/
PerfsRO& PerfsRO::operator = ( PerfsRO const& p ){
	date = p.date;
	nb_moyen_clients = p.nb_moyen_clients;
	debit_entree= p.debit_entree;
	debit_sortie= p.debit_sortie;
	tps_sejour_moyen = p.tps_sejour_moyen;

	return *this;
}
