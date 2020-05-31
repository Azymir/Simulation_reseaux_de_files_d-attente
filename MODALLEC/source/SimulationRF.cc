#include "SimulationRF.hh"

//Constructeur
SimulationRF::SimulationRF(Reseau* reseau, const int duree){
	this->reseau = reseau;
	duree_simulation = duree;
	nbClientsTot = 0;
	nbFilesTot = 0;
	nbClassesTot = 0;
	nbServeursTot = 0;
}

//Destructeur
SimulationRF::~SimulationRF(){}

//Accesseur
DonneesCalculsRF& SimulationRF::getDonnes_calculs(){
	return donnees_calculs;
}

//Méthodes
void SimulationRF::routage_clients(){
	int A = reseau->getNbFiles();

	//Garder les clients perdus
	list<Client*> liste_clients_perdus;

	int N = getReseau()->getListeClientARouter().size();

//Pour chaque client multi-classe de l'ensemble des clients à router

	list<Client*>::iterator it = getReseau()->getListeClientARouter().begin();
	//Tant que la fin de la liste n'est pas atteinte
	while(it != getReseau()->getListeClientARouter().end()){
		//Si le routage n'est pas vide
		if((*it)->getClasse()->getRoutage().empty() == 0){
			int num_next_file = (*it)->getClasse()->prochaine_file_routage((*it)->getPositionActuelle());
			File* tmp_f = reseau->chercherFile(num_next_file);

			//Si le nombre de clients + le nombre de clients entrés actuel est inférieur à la capacité de la file
			if((tmp_f->getNbClients() + tmp_f->getNbClientsEntresActuel()) < tmp_f->getTailleMax())
			{

				Evenement event = {1,echeancier.getDateActuelle(),tmp_f,NULL,*it};
				getEcheancier().ajouter_evenement(event);

				//On met a jour la position du client dans son routage
				if((*it)->getPositionActuelle() < (int)((*it)->getClasse()->getRoutage().size()-1))
					(*it)->setPositionActuelle((*it)->getPositionActuelle()+1);
				else
					(*it)->setPositionActuelle(0);

				(*tmp_f).setNbClientsEntresActuel((*tmp_f).getNbClientsEntresActuel()+1);

			}
			else
			{
				liste_clients_perdus.push_back(*it);
			}
			(*tmp_f).setNbClientsPresentes((*tmp_f).getNbClientsPresentes()+1);
			N--;
		}
		it++;
	}

//Pour chaque client monoclasse de l'ensemble des clients à router

	list<Client*>::iterator ite = reseau->getListeClientARouter().begin();
	for(ite = getReseau()->getListeClientARouter().begin() ; ite != getReseau()->getListeClientARouter().end() ; ite++)
	{
		//Si le routage est vide
		if((*ite)->getClasse()->getRoutage().empty() == 1)
		{
			//Tant qu'il y a des clients à router et des files à alimenter
			while(A>0 && N>0)
			{
				list<File*>::iterator ite_f;
				//Pour chaque file dont le taux d'arrivée est imposé
				for(ite_f = getReseau()->getListeFile().begin() ; ite_f != getReseau()->getListeFile().end() ; ite_f++)
				{
					if((*ite_f)->getDistribution_arrivee() != (-1)){
						int tmp = (*ite_f)->getDistribution_arrivee();

						//Si le nombre d'arrivée est supérieur au nombre de clients restants à router
						if(tmp > N) tmp = N;

						while(tmp > 0)
						{
							if((*ite_f)->getNbClients() + (*ite_f)->getNbClientsEntresActuel() < (*ite_f)->getTailleMax())
							{
								Evenement event = {1,echeancier.getDateActuelle(),(*ite_f),NULL,*ite};
								getEcheancier().ajouter_evenement(event);
								(*ite_f)->setNbClientsEntresActuel((*ite_f)->getNbClientsEntresActuel()+1);
							}
								else
								{
									//Ajouter le client à la liste des clients perdus
									liste_clients_perdus.push_back(*ite);
								}
								(*ite_f)->setNbClientsPresentes((*ite_f)->getNbClientsPresentes()+1);
								tmp--;
								N--;
								ite++;
							}
							tmp = 0;
							A--;
						}

					}

//Pour chaque file dont le taux d'arrivée n'est pas imposé
				list<File*>::iterator i_fp;
				for(i_fp = getReseau()->getListeFile().begin() ; i_fp != getReseau()->getListeFile().end() ; i_fp++){
					if((*i_fp)->getDistribution_arrivee() == (-1)){
						//On génère un lambda
						int lambda = N/A;
						//On calcule un taux d'arrivée
						int tmp = calculer_taux_arrivee_poisson(lambda);
						if(tmp > N) tmp = N;
							while(tmp > 0){
								if((*i_fp)->getNbClients() + (*i_fp)->getNbClientsEntresActuel() < (*i_fp)->getTailleMax()){
									Evenement event = {1,echeancier.getDateActuelle(),(*i_fp),NULL,*ite};
									getEcheancier().ajouter_evenement(event);
									(*i_fp)->setNbClientsEntresActuel((*i_fp)->getNbClientsEntresActuel()+1);
								}
								else
								{
									//Ajouter le client à la liste des clients perdus
									liste_clients_perdus.push_back(*ite);
								}
								ite ++;
								tmp--;
								N--;

								//Actualiser données lors du traitement
								(*i_fp)->setNbClientsPresentes((*i_fp)->getNbClientsPresentes()+1); //com
							}

							tmp = 0;
							A--;
						}
					}
				}
			}
		}

	//Supprimer les clients de la liste de routage
	list<Client*>::iterator client = reseau->getListeClientARouter().begin();
	int nbClientsASup = (int)reseau->getListeClientARouter().size()-N;
	if(!reseau->getListeClientARouter().empty())
	{
		while(nbClientsASup > 0)
		{
			client = reseau->getListeClientARouter().erase(client);
			nbClientsASup --;
		}
	}

//S'il reste des clients à supprimer à supprimer et aucune file à alimenter
	if(A==0 && N>0){
		list<Client*>::iterator client = reseau->getListeClientARouter().begin();
		while(client != getReseau()->getListeClientARouter().end()){
			for(list<File*>::iterator i = getReseau()->getListeFile().begin() ; i != getReseau()->getListeFile().end() ; i++){
				(*i)->setNbClientsPresentes((*i)->getNbClientsPresentes()+1);
				if((*i)->getNbClients() + (*i)->getNbClientsEntresActuel() < (*i)->getTailleMax()){
					Evenement event = {1,echeancier.getDateActuelle(),(*i),NULL,*client};
					getEcheancier().ajouter_evenement(event);
					//Actualiser les attributs tq la date d'arrivée (à faire au moment du traitement de l'événement)
					(*i)->setNbClientsEntresActuel((*i)->getNbClientsEntresActuel()+1); //com
				}
				else
				{
					//Ajouter le client à la liste des clients perdus
					liste_clients_perdus.push_back(*client);
				}
				N--;
				client ++;
			}
		}
	}

	//Calculer le nombre de clients dans le réseau
	reseau->setNbClients(reseau->getNbClients() -(int)liste_clients_perdus.size());

	//Vider la liste de routage
	if(!reseau->getListeClientARouter().empty())reseau->vider_liste_routage();

	//Vider la liste de clients perdus
	client = liste_clients_perdus.begin();
	while(client != liste_clients_perdus.end()){
		delete *client;
		client = liste_clients_perdus.erase(client);
	}

	//On remet à 0 le nombre de clients entrés actuel
	for(auto is = getReseau()->getListeFile().begin() ; is != getReseau()->getListeFile().end() ; is++){
		(*is)->setNbClientsEntresActuel(0);
	}
}


void SimulationRF::distribution_initiale(const int nb_clients_initial){
	int A = reseau->getNbFiles();
	int T = nb_clients_initial;

	//Garder les clients perdus
	list<Client*> liste_clients_perdus;

	//On crée un nombre de clients équivalent à T
	while(T>0){
		ClasseClient * classe_tmp ;

		//Valeurs comprises entre [0,..,nbClassesTot - 1]  classe = classe a la position classe_random
		int classe_random = rand()%reseau->getListeClasseClient().size() ;

		int cmp = 0 ;	//Compteur
		for(list<ClasseClient *>::iterator ItClasse = reseau->getListeClasseClient().begin()
		; ItClasse != reseau->getListeClasseClient().end() ; ItClasse++ ){
				if(cmp == classe_random)
				{
					classe_tmp = (*ItClasse);
					break;
				}
				cmp++;
			}
		Client* tmp = new Client(getNbClientsTot()+1,classe_tmp);

		incrementer_nbClientsTot();
		getReseau()->setNbClientsPasses(getReseau()->getNbClientsPasses()+1);
		//On ajoute le client à la liste de routage
		getReseau()->ajouter_client_routage(tmp);
		T--;
	}


	int N = getReseau()->getListeClientARouter().size();

//Pour chaque client multi-classe de l'ensemble des clients à router
	list<Client*>::iterator it = getReseau()->getListeClientARouter().begin();
	//Tant que la fin de la liste n'est pas atteinte
	while(it != getReseau()->getListeClientARouter().end()){
		//Si le routage n'est pas vide
		if((*it)->getClasse()->getRoutage().empty() == 0){
			int num_next_file = (*it)->getClasse()->trouver_file((*it)->getPositionActuelle());
			File* tmp_f = reseau->chercherFile(num_next_file);
			if(tmp_f->getNbClients() + (*tmp_f).getNbClientsEntresActuel() < tmp_f->getTailleMax()){
				Evenement event = {1,0,tmp_f,NULL,*it};
				getEcheancier().ajouter_evenement(event);

				//Actualiser données lors du traitement
				(*tmp_f).setNbClientsEntresActuel((*tmp_f).getNbClientsEntresActuel()+1);
			}
			else
			{
				//Ajouter l'adresse du client à la liste des clients perdus
				liste_clients_perdus.push_back(*it);
			}

			//Actualiser données lors du traitement
			(*tmp_f).setNbClientsPresentes((*tmp_f).getNbClientsPresentes()+1);
			N--;
		}
		it++;
	}

//Pour chaque client monoclasse de l'ensemble des clients à router

	list<Client*>::iterator ite = reseau->getListeClientARouter().begin();
	for(ite = getReseau()->getListeClientARouter().begin() ; ite != getReseau()->getListeClientARouter().end() ; ite++){
		//Si le routage ne contient rien
		if((*ite)->getClasse()->getRoutage().empty() == 1){
			//Si il reste des clients à router et des files à alimenter
			while(A>0 && N>0){
				list<File*>::iterator ite_f;
				//Pour chaque file dont le taux d'arrivée est imposé
				for(ite_f = getReseau()->getListeFile().begin() ; ite_f != getReseau()->getListeFile().end() ; ite_f++){
					if((*ite_f)->getDistribution_arrivee() != (-1)){
							int tmp = (*ite_f)->getDistribution_arrivee();

							//Si le nombre d'arrivée est supérieur au nombre de clients restants à router
							if(tmp > N) tmp = N;

							while(tmp > 0){
								if((*ite_f)->getNbClients() + (*ite_f)->getNbClientsEntresActuel() < (*ite_f)->getTailleMax()){
									Evenement event = {1,0,(*ite_f),NULL,*ite};
									getEcheancier().ajouter_evenement(event);
									(*ite_f)->setNbClientsEntresActuel((*ite_f)->getNbClientsEntresActuel()+1);
								}
								else
								{
									//Ajouter le client à la liste des clients perdus
									liste_clients_perdus.push_back(*ite);
								}
								(*ite_f)->setNbClientsPresentes((*ite_f)->getNbClientsPresentes()+1);
								tmp--;
								N--;
								ite++;
							}
							tmp = 0;
							A--;
						}
					}
				//Pour chaque file dont le taux d'arrivée n'est pas imposé
				list<File*>::iterator i_fp;
				for(i_fp = getReseau()->getListeFile().begin() ; i_fp != getReseau()->getListeFile().end() ; i_fp++){
					if((*i_fp)->getDistribution_arrivee() == (-1)){

							int lambda = N/A;
							//On calcule un nombre de client à faire rentrer
							int tmp = calculer_taux_arrivee_poisson(lambda);
	
							if(tmp > N) tmp = N;

							while(tmp > 0){
								if((*i_fp)->getNbClients() + (*i_fp)->getNbClientsEntresActuel() < (*i_fp)->getTailleMax()){
									Evenement event = {1,0,(*i_fp),NULL,*ite};
									getEcheancier().ajouter_evenement(event);
									(*i_fp)->setNbClientsEntresActuel((*i_fp)->getNbClientsEntresActuel()+1);
								}
								else
								{
									//Ajouter le client à la liste des clients perdus
									liste_clients_perdus.push_back(*ite);
								}
								ite ++;
								tmp--;
								N--;
								//Actualiser données lors du traitement
								(*i_fp)->setNbClientsPresentes((*i_fp)->getNbClientsPresentes()+1); //com
							}
							tmp = 0;
							A--;
						}
					}
				}
			}
		}

	//Supprimer les clients de la liste de routage
	list<Client*>::iterator client = reseau->getListeClientARouter().begin();
	int nbClientsASup = nb_clients_initial-N;

	while(nbClientsASup > 0)
	{
		client = reseau->getListeClientARouter().erase(client);
		nbClientsASup --;
	}

//Si il reste des clients à router et que toutes les files sont alimentées
	if(A==0 && N>0){
		list<Client*>::iterator client = reseau->getListeClientARouter().begin();
		while(client != getReseau()->getListeClientARouter().end()){
			for(list<File*>::iterator i = getReseau()->getListeFile().begin() ; i != getReseau()->getListeFile().end() ; i++){
				(*i)->setNbClientsPresentes((*i)->getNbClientsPresentes()+1);
				if((*i)->getNbClients() + (*i)->getNbClientsEntresActuel() < (*i)->getTailleMax()){
					Evenement event = {1,0,(*i),NULL,*client};
					getEcheancier().ajouter_evenement(event);
					//Actualiser les attributs tq la date d'arrivée (à faire au moment du traitement de l'événement)
					(*i)->setNbClientsEntresActuel((*i)->getNbClientsEntresActuel()+1);
				}
				else
				{
					//Ajouter le client à la liste des clients perdus
					liste_clients_perdus.push_back(*client);
				}
				N--;
				client ++;
			}
		}
	}
	//Calculer le nombre de clients dans le réseau
	reseau->setNbClients(nb_clients_initial -(int)liste_clients_perdus.size());

	//Vider la liste de routage
	if(!reseau->getListeClientARouter().empty())reseau->vider_liste_routage();

	//Vider la liste de clients perdus
	client = liste_clients_perdus.begin();
	while(client != liste_clients_perdus.end()){
		delete *client;
		client = liste_clients_perdus.erase(client);
	}

	//On remet à 0 le nombre de clients entrés actuel
	for(auto is = getReseau()->getListeFile().begin() ; is != getReseau()->getListeFile().end() ; is++){
		(*is)->setNbClientsEntresActuel(0);
	}
}
