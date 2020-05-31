#include "PerfsFile.hh"

/**Constructeur
@param f, la file dont les performances sont à calculer
@param date, la date de calcul des performances
**/
PerfsFile :: PerfsFile (File& f, const int date):file(&f){

	try{
		if(date < 0) throw invalid_argument ("Constructeur PerfsFile : date négative en paramètre");
		else
		{
			cout << file;
			this->date= date;
			nb_moyen_clients_file= 0;
			tps_attente_moyen= 0.0;
			tps_service_moyen= 0.0;
			tps_reponse_moyen= 0.0;
			tps_interarrivee_moyen= 0.0;
			taux_perte= 0.0;
		}
	}
	catch(string const& chaine){
		cerr << chaine <<endl;
	}
}

/**Constructeur de recopie
@param perfs, l'objet PerfsFile à acheter
**/
PerfsFile :: PerfsFile (PerfsFile& perfs):file(perfs.file){
	date = perfs.date;
	nb_moyen_clients_file= perfs.nb_moyen_clients_file ;
	tps_attente_moyen= perfs.tps_attente_moyen;
	tps_service_moyen= perfs.tps_service_moyen;
	tps_reponse_moyen= perfs.tps_reponse_moyen;
	ListeResPerfServeur= perfs.ListeResPerfServeur;
	tps_interarrivee_moyen = perfs.tps_interarrivee_moyen;
	taux_perte= perfs.taux_perte;
}

/**Destructeur**/
PerfsFile :: ~PerfsFile(){

	//Supprimer les emplacements alloués pour la liste
	ListeResPerfServeur.clear();
}

/**Méthode de récupérattion de la date de calcul des performances
@return un entier correspondant à la date
**/
int PerfsFile :: getDate (){
	return date;
}

/**Méthode de récupération de la file dont les performances sont calculées
@return une référence sur la file
**/
File& PerfsFile :: getFile (){
	return *file;
}

/**Méthode de récupération du nombre moyen de clients dans la file
@return un entier correspondant au nombre moyen de clients dans la file
**/
int PerfsFile :: getNbMoyenClientsFile (){
	return nb_moyen_clients_file;
}

/**Méthode de récupération du temps attente moyen dans la file
@return un flottant correspondant au temps d'attente
**/
float PerfsFile :: getTpsAttenteMoy (){
	return tps_attente_moyen;
}

/**Méthode de récupération du temps de service moyen dans la file
@return un flottant correspondant au temps de service
**/
float PerfsFile :: getTpsServiceMoy (){
	return tps_service_moyen;
}

/**Méthode de récupération du temps de réponse moyen de la file
@return un flottant correspondant au temps de réponse moyen
**/
float PerfsFile :: getTpsReponseMoy (){
	return tps_reponse_moyen;
}

/**Méthode de récupération de la liste de performances des serveurs de la file
@return une référence sur cette liste
**/
list <PerfServeur>& PerfsFile :: getListeResPerfServeur (){
	return ListeResPerfServeur;
}

/**Méthode de récupération du temps d'inter-arrivée moyen de la file
@return un flottant correspondant à ce temps d'inter-arrivée moyen
**/
float PerfsFile :: getTpsinterarriveeMoy (){
	return tps_interarrivee_moyen;
}

/**Méthode de récupération du taux de perte de la file
@return un entier correspondant au taux de perte
**/
float PerfsFile :: getTauxPerte (){
	return taux_perte;
}

/**Méthode de calcul du nombre moyen de clients dans la file**/
void PerfsFile ::  calcul_nb_moyen_clients_file(){

	//Créer pour sommer le nombre de clients des mesures enregistrées
	int tot_clients_file = 0;
	//Compter le nombre de mesures
	int nb_mesures = 0;

	//Défiler la liste de mesures
	for(auto i = file->getListeNbClients().begin(); i!=file->getListeNbClients().end(); i++){
		tot_clients_file += (*i).valeur;
		nb_mesures += 1;
	}

	//Effectuer le calcul si le nombre de mesures est supérieur à 0
	if(nb_mesures > 0)
		nb_moyen_clients_file = tot_clients_file/nb_mesures;
	else
		nb_moyen_clients_file = 0;

}

/**Méthode de calcul du temps d'attente moyen dans la file**/
void PerfsFile :: calcul_tps_attente_moyen (){
	tps_attente_moyen = (float) file->getTpsAttenteMoy();
}

/**Méthode de calcul de temps de service moyen dans la file**/
void PerfsFile :: calcul_tps_service_moyen (){
	tps_service_moyen = (float) file->getTpsServiceMoy();
}

/**Méthode de calcul du temps de réponse moyen de la file**/
void PerfsFile :: calcul_tps_reponse_moyen (){
	tps_reponse_moyen = (float) file->getTpsServiceMoy()+file->getTpsAttenteMoy();
}

/**Méthode de calcul du taux d'utilisation des serveurs de la file
@param duree_simulation, la duree de la simulation
**/
void PerfsFile :: calcul_taux_utilisation_serveurs (const int duree_simulation){

	try{
		if(duree_simulation <= 0) throw invalid_argument ("Méthode calcul_taux_utilisation_serveurs : durée nulle ou négative en paramètre");
		else
		{

			float duree = (float) duree_simulation;
			PerfServeur p;

			//Défiler la liste des serveurs
			for(auto i = file->getListeServeur().begin(); i != file->getListeServeur().end(); i++)
			{
				//Insérer le nouvel élément dans la liste de performances des serveurs
				p.numero_serveur = (*i)->getIDServeur();
				p.taux_utilisation = (*i)->getTpsUtilisation()/duree;

				ListeResPerfServeur.push_back(p);
			}
		}
	}
	catch(string const& chaine){
		cerr << chaine <<endl;
	}
}

/**Méthode de calcul du temps d'inter-arrivée moyen**/
void  PerfsFile :: calcul_tps_interarrivee_moyen (){

	//Créer pour sommer les temps d'inter-arrivée enregistrés
	float total_tps_interarrivee = 0.0;
	//Compter le nombre de mesures
	float nb_mesures = 0.0;

	//Défiler la liste de mesures
	for (auto i=file->getListeNbClientsEntres().begin(); i!= file->getListeNbClientsEntres().end(); i++){
		total_tps_interarrivee += (*i).valeur;
		nb_mesures += 1.0;
	}

	//Faire la calcul si la liste de mesures n'est pas vide
	if(nb_mesures!=0.0)
		tps_interarrivee_moyen = total_tps_interarrivee/nb_mesures ;
	else
		tps_interarrivee_moyen = 0.0;
}

/**Méthode de calcul du taux de perte de la file**/
void PerfsFile :: calcul_taux_perte (){

	float nP= (float)this->file->getNbClientsPresentes();
	float nE= (float)this->file->getNbClientsEntres();

	cout << "nP : " <<  nP << endl;
	cout << "nE : " <<nE << endl;

	if(nP!=0)
		taux_perte = (nP - nE)/nP;
	else
		taux_perte = 0.0;
}

/**Surcharge de l'opérateur <<
@param flux, le flux de sortie pour l'affichage
@param perfs, l'objet PerfsFile à afficher
**/
ostream& operator <<(ostream& flux , PerfsFile const& perfs)
{
	flux << "Performances de la file n°" << perfs.file->getIDFile()<<endl;
	flux << "Date de calcul :" <<endl;
	flux<< " Nombre moyen de clients : " << perfs.nb_moyen_clients_file << endl;
	flux << "Temps d'attente moyen :" << perfs.tps_attente_moyen << endl;
	flux << "Temps de service moyen :" << perfs.tps_service_moyen << endl;
	flux << "Temps d'inter-arrivée moyen :" << perfs.tps_interarrivee_moyen << endl;
	flux << "Taux de perte :" << perfs.taux_perte << endl;
	flux << "Taux d'utilisation par serveur :" << endl;

	for(auto Sperf : perfs.ListeResPerfServeur){
		flux << "N° serveur : " << Sperf.numero_serveur << "-" << Sperf.taux_utilisation << endl;
	}

	return flux;
}

PerfsFile& PerfsFile::operator = (PerfsFile const& p)
{
	file= p.file;
	date= p.date;
	nb_moyen_clients_file= p.nb_moyen_clients_file ;
	tps_attente_moyen= p.tps_attente_moyen;
	tps_service_moyen= p.tps_service_moyen;
	tps_reponse_moyen= p.tps_reponse_moyen;
	ListeResPerfServeur = p.ListeResPerfServeur;
	tps_interarrivee_moyen= p.tps_interarrivee_moyen;
	taux_perte= p.taux_perte;

	return *this;
}
