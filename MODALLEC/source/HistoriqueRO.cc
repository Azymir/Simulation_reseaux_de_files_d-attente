#include "HistoriqueRO.hh"
#include <stdexcept>

/**Constructeur**/
HistoriqueRO :: HistoriqueRO(){}

/**Destructeur**/
HistoriqueRO :: ~HistoriqueRO(){

	list<PerformancesRO>::iterator i = historique.begin();
	list<PerfsFile *>::iterator j;

	//Défiler la liste de l'historique
	while(i != historique.end())
	{
		delete (*i).perfReseau;

		j = (*i).ListePerfsFiles.begin();
		
		//Défiler la liste de performances des files
		while(j != (*i).ListePerfsFiles.end())
		{
			delete (*j);
			j = (*i).ListePerfsFiles.erase(j);
			cout << "OK delete PerfsFile" << endl;
		}

		i = historique.erase(i);
	}

}

/**Méthode de récupération de la liste contenant l'historique
@return une référence sur cette liste
**/
list <PerformancesRO>& HistoriqueRO :: getHistorique () {
	return historique;
}

/**Méthode d'ajout d'un élément dans la liste en initialisant le champ ajouterPerfsReseau
@param pr, l'objet PerfsRO à garder
**/
void HistoriqueRO :: ajouterPerfsReseau (PerfsRO& pR){

	//Créer un nouvel élément
	PerformancesRO p;

	//Intiialiser le champ perfReseau
	p.perfReseau = &pR;

	//Ajouter cet élément à l'historique
	historique.push_back(p);

}

/**Méthode d'ajout des performances d'une file à l'historique
@param f, la file dont il faut garde les performances
@param duree_simulation, la durée de la simulation
**/
void HistoriqueRO :: ajouterPerfsFile (File& f, const int duree_simulation){

	try{
		if(duree_simulation < 0) throw invalid_argument ("Méthode ajouterPerfsFile : durée négative en paramètre");
		else
		{
			int date_actuelle = historique.back().perfReseau->getDate();

			//Créer pour garder les perfomances de la file passée en paramètre
			PerfsFile * nouvellePerfsFile = new PerfsFile(f,date_actuelle);

			//Calculer les performances de la file
			nouvellePerfsFile->calcul_nb_moyen_clients_file ();
			nouvellePerfsFile->calcul_tps_attente_moyen();
			nouvellePerfsFile->calcul_tps_service_moyen ();
			nouvellePerfsFile->calcul_tps_reponse_moyen ();
			nouvellePerfsFile->calcul_taux_utilisation_serveurs(duree_simulation);
			nouvellePerfsFile->calcul_tps_interarrivee_moyen ();
			nouvellePerfsFile->calcul_taux_perte ();

			//Ajouter la sauvegarde à la liste du dernier élément de l'historique
			historique.back().ListePerfsFiles.push_back(nouvellePerfsFile);
		}
	}
	catch(string const& chaine){
		cerr << chaine <<endl;
	}

}

/**Surcharge de l'opérateur <<
@param flux, le flux de sortie pour l'affichage
@param H, l'objet HistoriqueRO à afficher
**/
ostream& operator <<(ostream& flux , HistoriqueRO const& H){
	flux << "==========Historique :==========" << endl;

	for(auto elemHisto : H.historique)
	{
		flux << *elemHisto.perfReseau << endl;

		for(auto Fperf : elemHisto.ListePerfsFiles)
		{
			flux << "N° file : " << Fperf->getFile().getIDFile() << endl;
			flux << *Fperf;
		}
	}

	return flux;
}
