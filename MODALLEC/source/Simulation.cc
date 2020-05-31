#include "Simulation.hh"


//Accesseurs
Reseau* Simulation::getReseau(){
	return reseau;
}
Echeancier& Simulation::getEcheancier(){
	return echeancier;
}
int Simulation::getDureeSimulation(){
	return duree_simulation;
}
int Simulation::getNbClientsTot(){
	return nbClientsTot;
}
int Simulation::getNbFilesTot(){
	return nbFilesTot;
}
int Simulation::getNbClassesTot(){
	return nbClassesTot;
}
int Simulation::getNbServeursTot(){
	return nbServeursTot;
}

//Méthodes
void Simulation::incrementer_nbClientsTot(){
	nbClientsTot++;
}
void Simulation::incrementer_nbFilesTot(){
	nbFilesTot++;
}
void Simulation::incrementer_nbClassesTot(){
	nbClassesTot++;
}
void Simulation::incrementer_nbServeursTot(){
	nbServeursTot++;
}

void Simulation::setDureeSimulation(int duree){
	try
	{
		if(duree < 0 ) throw invalid_argument("Simulation.setDureeSimulation : duree négative");
		duree_simulation = duree;
	}
	catch(string const&  chaine)
	{
		cerr << chaine << endl;
	}
}

void Simulation::setNbClientsTot(int nombre){
	try
	{
		if(nombre < 0) throw invalid_argument("Simulation.setNbClientsTot : nombre négatif");
		else nbClientsTot = nombre;
	}
	catch(string const& chaine)
	{
		cerr << chaine << endl;
	}
}

void Simulation::setNbFilesTot(int nombre){
	try
	{
		if(nombre < 0) throw invalid_argument("Simulation.setNbFilesTot : nombre négatif");
		else nbFilesTot = nombre;
	}
	catch(string const& chaine)
	{
		cerr << chaine << endl;
	}
}

void Simulation::setNbClassesTot(int nombre){
	try
	{
		if(nombre < 0) throw invalid_argument("Simulation.setNbClassesTot : nombre négatif");
		else nbClassesTot = nombre;
	}
	catch(string const& chaine)
	{
		cerr << chaine << endl;
	}
}

void Simulation::setNbServeursTot(int nombre){
	try
	{
		if(nombre < 0) throw invalid_argument("Simulation.setNbServeursTot : nombre négatif");
		else nbServeursTot = nombre;
	}
	catch(string const& chaine)
	{
		cerr << chaine << endl;
	}
}


void Simulation::executer_evenement(){

	//Si l'échéancier n'est pas vide
	if(!echeancier.getListeEvenement().empty())
	{
		//On sort le prochain événement
		Evenement event = echeancier.sortir_prochain_evenement();

		switch (event.type_evenement)
		{
			case 1:{
				EntreeFile(event);
				break;
			}
			case 2:{
				EntreeServeur(event);
				break;
			}
			case 3:{
				SortieServeur(event);
				break;
			}
			default:{
				cout<<"Erreur executer_evenement"<<endl;
				exit(EXIT_FAILURE);
			}
		}
	}
}

void Simulation::EntreeFile(evenement evenement_sorti){

	//On met à jour la date d'entrée du client dans la file à la date actuelle
	evenement_sorti.client->setDateArrivee(evenement_sorti.date_traitement);

	list<File*>::iterator i;
	//On cherche la file associée à l'événement en paramètre
	for(i = getReseau()->getListeFile().begin() ; i != getReseau()->getListeFile().end() ; i++){
		if((*i)->getIDFile() == evenement_sorti.file_destinee->getIDFile()){
			(*i)->ajouter_client(*(evenement_sorti.client));
			break;
		}
	}

	//On crée un événement entre dans le serveur a une date lointaine (duree de simulation * 100)
	Evenement e{2, duree_simulation*100, *i, NULL, evenement_sorti.client};

		list<Serveur*>::iterator it;
		for(it = (*i)->getListeServeur().begin(); it != (*i)->getListeServeur().end() ; it++)
		{
			//Si la file est vide et qu'un serveur n'est pas occupé
			if(((&(*it)->getClient()) == nullptr)
			&& ((*i)->getListeClients().front() == evenement_sorti.client))
			{
				//L'événement sera programmé à la date actuelle et dans un serveur innocupé
				e.serveur_destine = (*it);
				e.date_traitement = echeancier.getDateActuelle();
				break;
			}
		}
		//On ajoute l'événement créé et initialisé à la liste des événements
		echeancier.getListeEvenement().push_front(e);
}


void Simulation::EntreeServeur(evenement evenement_sorti){

	//On actualise le temps d'attente des clients dans la file associée à l'événement en paramètre
	evenement_sorti.file_destinee->actualiser_tps_attente_clients(evenement_sorti.date_traitement);

	list<File*>::iterator i;
	//On cherche la file associée à l'événement en paramètre
	for(i = getReseau()->getListeFile().begin() ; i != getReseau()->getListeFile().end() ; i++){
			if((*i)->getIDFile() == evenement_sorti.file_destinee->getIDFile()){
				list<Serveur*>::iterator s;
				//On cherche le serveur associé à l'événement
				for(s = (*i)->getListeServeur().begin(); s != (*i)->getListeServeur().end(); s++){
					if((*s)->getIDServeur() == evenement_sorti.serveur_destine->getIDServeur()){
						//On entre le client dans le serveur
						(*s)->Entrer_Client(evenement_sorti.client);
						//On sort le client de la file
						evenement_sorti.file_destinee->sortir_client();
						break;
					}
				}
				break;
			}
		}

		//On crée un événement de sortie du serveur
		Evenement e{3,
			evenement_sorti.client->getTps_service() + echeancier.getDateActuelle(), //date actuelle + tps service
			evenement_sorti.file_destinee,		//meme file
			 evenement_sorti.serveur_destine, 	//meme serveur
			 evenement_sorti.client};			//meme client


		//On ajoute cet événement à la liste des événements
		echeancier.getListeEvenement().push_back(e);
}

void Simulation::SortieServeur(evenement evenement_sorti){


	list<File*>::iterator i;

	Client* tmp_client ;

	for(i = getReseau()->getListeFile().begin() ; i != getReseau()->getListeFile().end() ; i++){
			if((*i)->getIDFile() == evenement_sorti.file_destinee->getIDFile()){
				list<Serveur*>::iterator s;
				for(s = (*i)->getListeServeur().begin(); s != (*i)->getListeServeur().end(); s++){
					if((*s)->getIDServeur() == evenement_sorti.serveur_destine->getIDServeur()){
						tmp_client = (*s)->Sortir_client();
						getReseau()->ajouter_client_routage(evenement_sorti.client);
						break;
					}
				}
				break;
			}
	}


	//On actualise un événement entrée du serveur avec le premier client de la file si il existe
	if(!evenement_sorti.file_destinee->getListeClients().empty())
	{
		int ID = evenement_sorti.file_destinee->getListeClients().front()->getID_client();

			list<Evenement>::iterator it;
		for(it = echeancier.getListeEvenement().begin() ;
				it != echeancier.getListeEvenement().end() ; it++)
		{
			if(((*it).type_evenement == 2) && ((*it).client->getID_client() == ID))
			{
				(*it).date_traitement = echeancier.getDateActuelle();
				(*it).serveur_destine = evenement_sorti.serveur_destine ;

				break;
			}
		}
	}


}




unsigned long long Simulation::facto(int n) {
	if(n == 0) return 1 ;
	else
		if(n > 0) return n * facto(n-1);

	return -1 ;
}



double Simulation::calcul_proba_poisson(int k, int lambda){
	double tmp =  pow(lambda, k) ;
	tmp *= exp(-lambda);
	tmp /= facto(k);

	//tmp = (λ^k/k!)*e^(-λ)
	return tmp ;
}



int Simulation::calculer_taux_arrivee_poisson(const int lambda){

	int lambda_bis = lambda;

	//Si le lambda récupéré est plus grand que 12
	if(lambda > 12) lambda_bis = 12;

	//Liste de structures Poisson permettant de contenir k et P(X=k)
	list<Poisson> plage_valeurs;

	//On ajoure une structure Poisson contenant lambda et p(X = lambda) dans plage_valeurs
	double P_lambda = calcul_proba_poisson(lambda_bis, lambda_bis);
	Poisson p1{lambda_bis, P_lambda};
	plage_valeurs.push_front(p1);

	//On cherche tout les i < lambda tel que P(X = i) > 0.01
	for(int i = lambda_bis - 1 ; i > 0 ; i--)
	{
		if(calcul_proba_poisson(i,lambda_bis) < 0.01) break ;
		Poisson p{i,calcul_proba_poisson(i,lambda_bis)};
		plage_valeurs.push_front(p);
	}

	//On cherche tout les i > lambda tel que P(X = i) > 0.01
	for(int i = lambda_bis + 1 ; calcul_proba_poisson(i,lambda_bis) > 0.01; i++){
		Poisson p{i,calcul_proba_poisson(i,lambda_bis)};
		plage_valeurs.push_back(p);
	}


	list<Poisson>::iterator it,it2;
	it  = plage_valeurs.begin();
	it2  = plage_valeurs.begin();
	it++;
	for(; it != plage_valeurs.end() ; it++,it2++)
	{		//On ajoute la valeur de la probabilité précédente dans la suivante afin de créer une plage de nombre
			(*it).proba += (*it2).proba;

			if(it2 == plage_valeurs.end()) break;
	}

	//On tire une valeur comprise dans [0,99]
	int random = rand()%100, res = -1 ;
	it = plage_valeurs.begin();

	//Si random est plus grand que la dernière valeur
	if(random > (plage_valeurs).back().proba * 100)
		return (plage_valeurs).back().proba + 1;

	//On compare la valeur random avec tout les attributs "proba * 100" comprises dans plages_valeurs
	//et on les compare avec random, si random est inférieure, on renvoie l'attribut "nombre" associé à l'attribut proba > random
	while(it != plage_valeurs.end())
	{
		res = (*it).nombre ;
		if(random < ((*it).proba * 100)) break;
		it ++;
	}

	if(res == 0) res = 1;
	
	return res;
}
