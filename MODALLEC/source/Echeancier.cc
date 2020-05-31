#include "Echeancier.hh"

//Constructeur
Echeancier::Echeancier(){
	date_actuelle = 0;
}

//Destructeur
Echeancier::~Echeancier(){

	/*list<Evenement>::iterator it = liste_evenement.begin();
	while(it != liste_evenement.end())
	{
		//Si l'evenement est entrée dans une file
		if((*it).type_evenement == 1)
			delete (*it).client;

		it = liste_evenement.erase(it);
	}*/
}

//Accesseurs
list<Evenement>& Echeancier::getListeEvenement(){
	return liste_evenement;
}

int Echeancier::getDateActuelle(){
	return date_actuelle;
}

void Echeancier::setDateActuelle(const int date)
{
	try
	{
		if(date < 0) throw invalid_argument("ERREUR : date négative passée en argument");
		else
		{
			date_actuelle = date;
		}
	}
	catch(string const& chaine)
	{
		cerr << chaine << endl;
	}
}

//Méthodes

void Echeancier::ajouter_evenement(Evenement& event){
	liste_evenement.push_back(event);
}

Evenement Echeancier::sortir_prochain_evenement(){
	Evenement e;
	//On stocke le premier évènement
	e = liste_evenement.front();
	//Mise à jour la date actuelle avec la date de l'évènement
	date_actuelle = e.date_traitement;
	//On sort l'évènement de la liste des évènements
	liste_evenement.pop_front();
	return e;
}

void Echeancier::supprimer_evenement_file(const int num_file){
	try {
		if(num_file < 0) throw invalid_argument("Echeancier.supprimer_evenement_file : num_file négatif\n");

		list<Evenement>::iterator it = liste_evenement.begin();
		//2ème itérateur pour garder l'avancement du premier itérateur
		list<Evenement>::iterator it2 = it;

		while(it != liste_evenement.end())
		{
			//On parcourt la liste des événenements
			for (it = it2 ; it != liste_evenement.end() ; it++)
			{
				it2 = it;
				if((*it).file_destinee->getIDFile() == num_file)
				{
					//Si l'evenement est entrée dans une file
					if((*it).type_evenement == 1)
					{
						delete (*it).client;
					}
					it2++;
					liste_evenement.erase(it);
					break;
				}
			}
		}
	}
	catch(string const& chaine)
	{
	    cerr << chaine << endl;
	}
}

void Echeancier::supprimer_evenement_serveur(const int num_serveur){
	try {
		if(num_serveur < 0) throw invalid_argument("Echeancier.supprimer_evenement_serveur : num_serveur négatif\n");

		list<Evenement>::iterator it = liste_evenement.begin();
		//2ème itérateur pour garder l'avancement du premier itérateur
		list<Evenement>::iterator it2 = it;
		while(it != liste_evenement.end())
		{
			//On parcoure la liste des événements
			for (it = it2 ; it != liste_evenement.end() ; it++)
			{
				it2 = it;
				if((*it).serveur_destine->getIDServeur() == num_serveur)
				{
					it2++;
					liste_evenement.erase(it);
					break;
				}
			}
		}
	}
	catch(string const& chaine)
	{
	    cerr << chaine << endl;
	}
}

void Echeancier::trier_croissant(){
	//Appelle de la méthode sort() qui va trier la liste des événements en fonction de compare_evenement()
	liste_evenement.sort(compare_evenement());
}

ostream& operator << (ostream& flux, Echeancier const& e){
	flux << "date actuelle : " << e.date_actuelle << endl;

	for(auto event : e.liste_evenement)
	{
		cout<< "Type event :" << event.type_evenement<<endl;
		cout<< "Date :" << event.date_traitement<<endl;

		if(event.client != NULL)cout<< "Client " << event.client->getID_client()<<endl;
		if(event.file_destinee != NULL)cout << "File " << event.file_destinee->getIDFile()<<endl;
		if(event.serveur_destine != NULL)cout << "Serveur "<< event.serveur_destine->getIDServeur() << endl;
		cout << "_______________________________________________" << endl;
	}
	return flux;
}
