#include "SimulationRO.hh"

//Constructeur
SimulationRO::SimulationRO(Reseau* reseau, int duree){
	this->reseau = reseau;
	duree_simulation = duree;
	nbClientsTot = 0;
	nbFilesTot = 0;
	nbClassesTot = 0;
	nbServeursTot = 0;
}

//Destructeur
SimulationRO::~SimulationRO(){}

//Accesseur
DonneesCalculsRO& SimulationRO::getDonnes_calculs(){
	return donnees_calculs;
}

//Méthodes
void SimulationRO::distribution_initiale(const int nb_clients_initial)
{
	int A = reseau->getNbFiles();
	int T = nb_clients_initial;

	//Liste qui va contenir les clients à supprimer
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

		//Ajouter tmp à l'ensemble des clients entrés dans le réseau	
		TSClient ts{nbClientsTot + 1, echeancier.getDateActuelle(), 0, 0};
		donnees_calculs.getListeClientEntres().push_back(ts);

		getReseau()->ajouter_client_routage(tmp);
		T--;
	}
	
	int N = getReseau()->getListeClientARouter().size();

//Pour chaque client multi-classe de l'ensemble des clients à router
	list<Client*>::iterator it = getReseau()->getListeClientARouter().begin();
	//Tant que la fin de la liste n'est pas atteinte
	while(it != getReseau()->getListeClientARouter().end())
	{
		//Si le routage n'est pas vide
		if((*it)->getClasse()->getRoutage().empty() == 0)
		{	
			int num_next_file = (*it)->getClasse()->trouver_file((*it)->getPositionActuelle());
			File* tmp_f = reseau->chercherFile(num_next_file);	
			
			//Si le nombre de clients + le nombre de clients entrés actuel est inférieur à la capacité de la file
			if(tmp_f->getNbClients() + (*tmp_f).getNbClientsEntresActuel() < tmp_f->getTailleMax()){
				Evenement event = {1,0,tmp_f,NULL,*it};
				getEcheancier().ajouter_evenement(event);
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
			//Tant qu'il y a des clients à router et des files à alimenter
			while(A>0 && N>0){
				list<File*>::iterator ite_f;
				//Pour chaque file dont le taux d'arrivée est imposé
				for(ite_f = getReseau()->getListeFile().begin() ; ite_f != getReseau()->getListeFile().end() ; ite_f++){
					if((*ite_f)->getDistribution_arrivee() != (-1)){
							int tmp = (*ite_f)->getDistribution_arrivee();
							//Si le nombre d'arrivée est supérieure au nombre de clients restants à router
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
				//Si la distribution d'arrivée est aléatoire
					if((*i_fp)->getDistribution_arrivee() == (-1)){
							int lambda = N/A;
							//On génère un nombre de clients en fonction de lambda
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
								(*i_fp)->setNbClientsPresentes((*i_fp)->getNbClientsPresentes()+1); 
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
	int nbClientsASup = nb_clients_initial - N ;

	while(nbClientsASup > 0)
	{
		client = reseau->getListeClientARouter().erase(client);
		nbClientsASup --;
	}

				
//Tant qu'il y a des clients à router et des files à alimenter
	if(A==0 && N>0){
		list<Client*>::iterator client = reseau->getListeClientARouter().begin();
		while(client != getReseau()->getListeClientARouter().end()){
			for(list<File*>::iterator i = getReseau()->getListeFile().begin() ; i != getReseau()->getListeFile().end() ; i++){
				(*i)->setNbClientsPresentes((*i)->getNbClientsPresentes()+1); 

				if((*i)->getNbClients() + (*i)->getNbClientsEntresActuel() < (*i)->getTailleMax()){
					Evenement event = {1,0,(*i),NULL,*client};
					getEcheancier().ajouter_evenement(event);
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
	list<TSClient>::iterator iter;

	client = liste_clients_perdus.begin();

	while(client != liste_clients_perdus.end()){
		//Mettre à jour le temps de séjour du client
		for(iter = donnees_calculs.getListeClientEntres().begin() ; iter != donnees_calculs.getListeClientEntres().end() ; iter++)
		{
			if((*client)->getID_client() == (*iter).numero_client)
			{
				(*iter).date_sortie = echeancier.getDateActuelle();
				(*iter).tps_sejour = (*iter).date_sortie - (*iter).date_entree;
				break;
			}
		}

		delete *client;
		client = liste_clients_perdus.erase(client);
	}

	//On remet à 0 le nombre de clients entrés actuel
	for(auto is = getReseau()->getListeFile().begin() ; is != getReseau()->getListeFile().end() ; is++)
	{
		(*is)->setNbClientsEntresActuel(0);
	}
}

void SimulationRO::routage_clients(){
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
			if(tmp_f->getNbClients() + tmp_f->getNbClientsEntresActuel() < tmp_f->getTailleMax()){
				Evenement event = {1,echeancier.getDateActuelle(),tmp_f,NULL,*it};
				getEcheancier().ajouter_evenement(event);
				
				if((*it)->getPositionActuelle() < (int)((*it)->getClasse()->getRoutage().size()-1))
					(*it)->setPositionActuelle((*it)->getPositionActuelle()+1);
				else (*it)->setPositionActuelle(0);

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
			//Tant qu'il y a des clients à router et des files à alimenter
			while(A>0 && N>0){
				list<File*>::iterator ite_f;
				//Pour chaque file dont le taux d'arrivée est imposé
				for(ite_f = getReseau()->getListeFile().begin() ; ite_f != getReseau()->getListeFile().end() ; ite_f++){
					if((*ite_f)->getDistribution_arrivee() != (-1)){
							int tmp = (*ite_f)->getDistribution_arrivee();
							//Si le nombre d'arrivée est supérieure au nombre de clients restants à router
							if(tmp > N) tmp = N;
							while(tmp > 0){
								if((*ite_f)->getNbClients() + (*ite_f)->getNbClientsEntresActuel() < (*ite_f)->getTailleMax()){
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
								(*i_fp)->setNbClientsPresentes((*i_fp)->getNbClientsPresentes()+1); 
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

					
//Si il reste des clients à router et que toutes les files sont alimentés
	if(A==0 && N>0){
		list<Client*>::iterator client = reseau->getListeClientARouter().begin();
		while(client != getReseau()->getListeClientARouter().end()){
			for(list<File*>::iterator i = getReseau()->getListeFile().begin() ; i != getReseau()->getListeFile().end() ; i++){
	
				(*i)->setNbClientsPresentes((*i)->getNbClientsPresentes()+1);

				if((*i)->getNbClients() + (*i)->getNbClientsEntresActuel() < (*i)->getTailleMax()){
					Evenement event = {1,echeancier.getDateActuelle(),(*i),NULL,*client};
					getEcheancier().ajouter_evenement(event);
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
	reseau->setNbClients(reseau->getNbClients() -(int)liste_clients_perdus.size());

	//Vider la liste de routage
	if(!reseau->getListeClientARouter().empty())reseau->vider_liste_routage();

	//Vider la liste de clients perdus
	list<TSClient>::iterator iter;

	client = liste_clients_perdus.begin();

	while(client != liste_clients_perdus.end()){
		//Mettre à jour le temps de séjour du client
		for(iter = donnees_calculs.getListeClientEntres().begin() ; iter != donnees_calculs.getListeClientEntres().end() ; iter++)
		{
			if((*client)->getID_client() == (*iter).numero_client)
			{
				(*iter).date_sortie = echeancier.getDateActuelle();
				(*iter).tps_sejour = (*iter).date_sortie - (*iter).date_entree;
				break;
			}
		}

		delete *client;
		client = liste_clients_perdus.erase(client);
	}

	//On remet à 0 le nombre de clients entrés actuel
	for(auto is = getReseau()->getListeFile().begin() ; is != getReseau()->getListeFile().end() ; is++){
		(*is)->setNbClientsEntresActuel(0);
	}
}

void SimulationRO::entrer_clients_reseau(){
	int IN = 0;
	//Sert à mettre à jour le nombre de clients entrant dans le réseau
	int cmp_clients = 0 ;

	list<File*>::iterator i ;
	
	//Récupérer le nombre de clients à entrer pour satisfaire les distributions constantes et uniformes
	for(i = reseau->getListeFile().begin() ; i != reseau->getListeFile().end() ; i++)
	{
		if((*i)->getDistribution_arrivee() > 0)
			IN += (*i)->getDistribution_arrivee();
	}
	
	cmp_clients += IN;
	ClasseClient * classe = reseau->getListeClasseClient().front();

	while(IN > 0)
	{
		for(auto file : reseau->getListeFile())
		{
			if(file->getDistribution_arrivee() != -1)
			{
				int tmp = file->getDistribution_arrivee();
				while(tmp > 0){
					Client * c = new Client(nbClientsTot,classe);
					incrementer_nbClientsTot();
					reseau->setNbClientsPasses(getReseau()->getNbClientsPasses()+1);
					reseau->setNbClients(getReseau()->getNbClients()+1);
					donnees_calculs.ajouter_element_TSclient(c->getID_client(), echeancier.getDateActuelle());
					reseau->ajouter_client_routage(c);
					tmp--;
					IN--;
				}
			}
		}
	}

	IN = rand()%7 + 1 ; 		
	cmp_clients += IN;
	//On affecte à IN une valeur aléatoire de client à faire rentrer
	while(IN > 0){
		ClasseClient * classe_tmp ;
		int classe_random = rand()%reseau->getListeClasseClient().size();
		
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
		//On actualise les données du réseau
		incrementer_nbClientsTot();
		reseau->setNbClientsPasses(getReseau()->getNbClientsPasses()+1);
		reseau->setNbClients(getReseau()->getNbClients()+1);
		donnees_calculs.ajouter_element_TSclient(tmp->getID_client(), echeancier.getDateActuelle());
		
		reseau->ajouter_client_routage(tmp);
		IN--;
	}
	
	//Ajouter une nouvelle mesure à la liste du nombre de clients entrants
	donnees_calculs.ajouterMesuresNbclientsEntrants(cmp_clients,echeancier.getDateActuelle());
}

void SimulationRO::sortir_clients_reseau(){

	int OUT = 0 ;
	//Connaître le nombre de clients de classe 0 à sortir
	OUT = rand()%7 + 1 ;		//Pour l'instant entre 1 et 7

	//Sortir les clients multi-classes
	list<Client *>::iterator client = reseau->getListeClientARouter().begin();
	while(client != reseau->getListeClientARouter().end())
	{
		//Si il s'agit d'un client multi-classe
		if(!(*client)->getClasse()->getRoutage().empty())
		{
			//Si il est à la fin de son routage
			if(((*client)->getPositionActuelle())==((*client)->getClasse()->getRoutage().size()-1))
			{
				//Mettre à jour son temps de séjour
				donnees_calculs.calcul_tps_sejour_client((*client)->getID_client(),echeancier.getDateActuelle());

				//Supprimer le client
				delete *client;
				client = reseau->getListeClientARouter().erase(client);
				reseau->setNbClients(reseau->getNbClients()-1);
			}
			else client ++;
		}
		else client ++;
	}

	//Sortir les clients de classe 0
	client = reseau->getListeClientARouter().begin();
	while((client != reseau->getListeClientARouter().end()) && (OUT > 0))
	{
		//Si il s'agit d'un client mono-classe
		if((*client)->getClasse()->getRoutage().empty())
		{
				//Mettre à jour son temps de séjour
				donnees_calculs.calcul_tps_sejour_client((*client)->getID_client(),echeancier.getDateActuelle());

				//Supprimer le client
				delete *client;
				client = reseau->getListeClientARouter().erase(client);
				reseau->setNbClients(reseau->getNbClients()-1);
				OUT --;
		}
		else client ++;
	}

	donnees_calculs.ajouterMesureNbClientsSortants(OUT,echeancier.getDateActuelle());
}
