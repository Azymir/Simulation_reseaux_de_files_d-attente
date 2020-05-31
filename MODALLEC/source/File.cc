#include "File.hh"

//Constructeur
File::File(const int ID, const int abs, const int ord)
{
		ID_file = ID;
		centre.x = abs ;
		centre.y = ord;
		ordonnancement = 1;	//FIFO
		loi_service = -1;	//Exponentielle
		distribution_arrivee = -1;	//Poisson
		taille_max = 10000;			//Peut etre réduire à 100
		nb_clients = 0;
		nb_clients_servis = 0 ;
		nb_clients_presentes = 0;
		tps_service_moyen = 0;
		tps_attente_moyen = 0;
		nb_clients_entres = 0;
		nb_clients_entres_actuel = 0;
		
	try{
		
		if(ID < 0) throw invalid_argument("Constructeur de File : ID négative\n");
		if(abs < 0 || ord < 0) throw invalid_argument("Constructeur de File : abs ou ord négatives\n");
		ID_file = ID ;
		centre.x = abs;
		centre.y = ord;
	}
    catch(string const& chaine)
    {
       cerr << chaine << endl;
    }
}

//Constructeur par recopie
File::File(File& f){
	*this = f;
}

//Destructeur
File::~File(){

	list <Serveur *>::iterator serveur = liste_serveurs.begin();
	//On désalloue chaque serveur de la liste des serveurs
	
	if(liste_serveurs.empty())
	{
		while(serveur != liste_serveurs.end())
		{
			delete *serveur;
			serveur = liste_serveurs.erase(serveur);
		}
	}

	list <Client *>::iterator client = liste_clients.begin();
	//On désalloue chaque client de la liste des clients
	if(liste_clients.empty())
	{
		while(client != liste_clients.end())
		{
			delete *client;
			client = liste_clients.erase(client);
		}
	}
}

//Accesseurs
int File::getIDFile() const{
	return ID_file;
}
int File::getNbClients() const{
	return nb_clients;
}
int File::getTailleMax() const{
	return taille_max;
}
int File::getNbClientsServis() const{
	return nb_clients_servis;
}
int File::getNbClientsPresentes() const{
	return nb_clients_presentes;
}
float File::getTpsServiceMoy() const{
	return tps_service_moyen;
}
float File::getTpsAttenteMoy() const{
	return tps_attente_moyen;
}
int File::getNbClientsEntres() const{
	return nb_clients_entres;
}
int File::getNbClientsEntresActuel() const{
	return nb_clients_entres_actuel;
}
coordonnees File::getCoord() const{
	return centre;
}
int File::getOrdonnancement() const{
	return ordonnancement;
}
int File::getLoi_service() const{
	return loi_service;
}
int File::getDistribution_arrivee() const{
	return distribution_arrivee;
}
list<Client*>& File::getListeClients(){
	return liste_clients;
}
list<Serveur*>& File::getListeServeur(){
	return liste_serveurs;
}

list<mesure>& File::getListeNbClients(){
	return liste_nbClients;
}
list<mesure>& File::getListeNbClientsEntres(){
	return liste_nbClientsEntres;
}

void File::setTailleMax(const int nombre){
	try {
		if(nombre < 0) throw invalid_argument("File.setTailleMax : nombre négatif\n");
		taille_max = nombre;
	}
	catch(string const& chaine)
    {
       cerr << chaine << endl;
    }
}

void File::setOrdonnancement(const int numero){
	try {
		if((numero < 1) || (numero > 4)) throw invalid_argument("File.setOrdonnancement : numero invalide\n");
		else
			{
				ordonnancement = numero;
				//Si on passe à un ordonnancement selon la priorité, on retrie la file selon la priorité
				if(numero == 3){
					trier_priorite_file();
				}
			}
	}
	catch(string const& chaine)
    {
       cerr << chaine << endl;
    }
}

void File::setLoiService(const int numero){
	try {
		if(numero < -2) throw invalid_argument("File.setLoiService : numero invalide\n");
		loi_service = numero;
	}
	catch(string const& chaine)
    {
       cerr << chaine << endl;
    }
}

void File::setDistribution(const int numero){
	try {
		if(numero < -1) throw invalid_argument("File.setDistribution : numero invalide\n");
		distribution_arrivee = numero;
	}
	catch(string const& chaine)
    {
       cerr << chaine << endl;
    }
}

void File::setCoordonnees(coordonnees c){
	try {
		if((c.x < 0) || (c.y < 0)) throw invalid_argument("File.setCoordonnees : coordonnees négatives\n");
		centre = c;
	}
	catch(string const& chaine)
    {
       cerr <<chaine << endl;
    }
}

void File::setNbClientsEntresActuel(const int nombre){
	try {
		if(nombre < 0) throw invalid_argument("File.setNbClientsEntresActuel : nombre négatif\n");
		nb_clients_entres_actuel = nombre;
	}
	catch(string const& chaine)
    {
       cerr << chaine << endl;
    }
}

void File::setNbClientsEntres(const int nombre){
	try {
		if(nombre < 0) throw invalid_argument("File.setNbClientsEntres : nombre négatif\n");
		nb_clients_entres = nombre ;
	}
	catch(string const& chaine)
    {
       cerr << chaine << endl;
    }
}

void File::setNbClientsPresentes(const int nombre){
	try {
		if(nombre < 0) throw invalid_argument("File.setNbClientsPresentes : nombre négatif\n");
		nb_clients_presentes = nombre ;
	}
	catch(string const& chaine)
    {
       cerr << chaine << endl;
    }
}
void File::setNbClients(const int nombre){
	try {
		if(nombre < 0) throw invalid_argument("File.setNbClients : nombre négatif\n");
		nb_clients = nombre ;
	}
	catch(string const& chaine)
    {
       cerr << chaine << endl;
    }
}

void File::setTempsAttenteMoyen(float temps){
	try {
		if(temps < 0) throw invalid_argument("File.setTempsAttenteMoyen : temps négatif\n");
		tps_attente_moyen = temps ;
	}
	catch(string const& chaine)
    {
       cerr << chaine << endl;
    }
}

void File::setTempsServiceMoyen(float temps){
	try {
		if(temps < 0) throw invalid_argument("File.setTempsServiceMoyen : temps négatif\n");
		tps_service_moyen = temps;
	}
	catch(string const& chaine)
    {
       cerr << chaine << endl;
    }
}
void File::setNbClientsServis(const int nombre){
	try {
		if(nombre < 0) throw invalid_argument("File.setNbClientsServis : nombre négatif\n");
		nb_clients_servis = nombre ;
	}
	catch(string const& chaine)
    {
       cerr << chaine << endl;
    }
}

//Méthodes

void File::ordonnancer_clients(Client& client){
	switch (ordonnancement)
	{
		case 1:{
			FIFO(client);
			break;
		}
		case 2:{
			LIFO(client);
			break;
		}
		//Ajoute selon la priorité
		case 3:{
			PRIO(client);
			break;
		}
		//Ajoute aléatoirement
		case 4:{
			RANDOM(client);
			break;
		}

		default:{
			printf("Valeur de l'ordonnancement invalide");
			exit(EXIT_FAILURE);
		}
	}
}

void File::FIFO(Client& client){
	liste_clients.push_back(&client);
}
void File::LIFO(Client& client){
	liste_clients.push_front(&client);
}
void File::PRIO(Client& client){
	
	//Si la liste est vide
	if(liste_clients.empty())
	{
		liste_clients.push_front(&client);
	}
	else{
		//Si le client est moins prioritaire que le dernier, on ajoute à la fin
		if(client.getClasse()->getPriorite() >= liste_clients.back()->getClasse()->getPriorite())	
		{
			liste_clients.push_back(&client);
		}
		else
		{
			list<Client*>::iterator i;
			//On itère sur la liste des clients et on compare la priorité avec le client en paramètre
			for(i  = liste_clients.begin() ; i != liste_clients.end() ; i++)
			{
				if(client.getClasse()->getPriorite() < (*i)->getClasse()->getPriorite() )
				{
					liste_clients.insert(i,&client);
					break;
				}
			}
		}
	}
}

void File::RANDOM(Client& client){

	//Si la liste vide
	if(liste_clients.empty())
	{
		liste_clients.push_front(&client);		
	}
	else{
		//On génere une valeur aléatoire correspondant au nombre de fois où l'on passe à l'élément suivant 
		int alea = (rand()%nb_clients);		
		int a = 0;

		list<Client*>::iterator i ;

		for(i = liste_clients.begin() ; i != liste_clients.end(); i++)
		{
			if(a == alea)
			{
				liste_clients.insert(i,&client);
			}
			a++;
		}
	}
}

void File::sortir_client(){ 
	//Mise à jour du temps de service moyen
	calcul_temps_service_moy(liste_clients.front()->getTps_service());
	//Mise à jour du temps d'attente moyen
	calcul_temps_attente_moy(liste_clients.front()->getTps_attente());
	//On retire le premier client de la liste des clients 
	liste_clients.pop_front();
	//On réduit le nombre de clients dans la file
	setNbClients(nb_clients - 1);
	//On augmente le nombre de clients servis
	setNbClientsServis(nb_clients_servis + 1);
}

void File:: ajouter_serveur(Serveur& s){
	liste_serveurs.push_back(&s);
}

void File:: supprimer_serveur(const int ID_serveur){
	try{
		if (ID_serveur < 0) throw invalid_argument("File.supprimer_serveur : ID négatif\n");

		list<Serveur*>::iterator i;
		//On itère sur la liste des serveurs
		for(i = liste_serveurs.begin() ; i != liste_serveurs.end() ; i++){
			if((*i)->getIDServeur() == ID_serveur){
				delete (*i) ;
				liste_serveurs.erase(i);
				break;
			}
		}
		if(liste_serveurs.empty()) throw runtime_error("File.supprimer_serveur : liste_serveurs est vide\n");
	}
	catch(string const& chaine)
    {
       cerr << chaine << endl;
    }
}


void File::trier_priorite_file(){		
	//On copie la liste des clients dans celle-ci
	list<Client * > tmp_liste = liste_clients;
	//On vide la liste 
	liste_clients.clear();

	while(tmp_liste.empty() == 0)
	{
		Client * c = tmp_liste.back() ;
		tmp_liste.pop_back();
		//On ajoute les clients selon leur priorité
		ordonnancer_clients((*c)) ;
	}

}


void File::ajouter_client(Client& client){
	//On ajoute selon l'ordonnancement
	ordonnancer_clients(client);
	//On attribue un temps de service
	client.calculer_tps_service(loi_service,distribution_arrivee);
	//Augmentation du nombre de clients
	setNbClients(nb_clients + 1);
	//Augmentation du nombre de clients entrés
	setNbClientsEntres(nb_clients_entres + 1);
}

void File::ajouter_mesure_nb_clients_entres(const int nb_clients_entres, const int tps){
	try {
		if(nb_clients_entres < 0 || tps < 0) throw invalid_argument("File.ajouter_mesure_nb_clients_entres : nombre  ou temps négatifs\n");
		mesure tmp = {nb_clients_entres, tps};
		liste_nbClientsEntres.push_back(tmp);
	}
	catch(string const& chaine)
    {
       cerr << chaine << endl;
    }
}

void File::ajouter_mesure_nb_clients (const int nb_clients, const int tps){
	try {
		if(nb_clients < 0 || tps < 0) throw invalid_argument("File.ajouter_mesure_nb_clients : nombre  ou temps négatifs\n");
		mesure tmp = {nb_clients, tps};
		liste_nbClients.push_back(tmp);
	}
	catch(string const& chaine)
    {
       cerr << chaine << endl;
    }
}

void File::actualiser_tps_attente_clients (const int date_actuelle){
	try {
		if(date_actuelle < 0) throw invalid_argument("File.actualiser_tps_attente_clients : date négative\n");
		list<Client*>::iterator i = liste_clients.begin();
		for(; i != liste_clients.end() ; i++){
			(*i)->modifier_tps_attente(date_actuelle);
		}
	}
	catch(string const& chaine)
    {
       cerr << chaine << endl;
    }
}

void File::calcul_temps_attente_moy(const int tps_attente_client_entrant_serveur){
	try {
		if(tps_attente_client_entrant_serveur < 0) throw invalid_argument("File.calcul_temps_attente_moy : temps négatif\n");
		float tmp = ((nb_clients_servis * tps_attente_moyen) + tps_attente_client_entrant_serveur) / (nb_clients_servis+1);
		setTempsAttenteMoyen(tmp);
	}
	catch(string const& chaine)
    {
       cerr << chaine << endl;
    }
}

void File::calcul_temps_service_moy(const int tps_service_client_entrant_serveur){
	try {
		if(tps_service_client_entrant_serveur < 0) throw invalid_argument("File.calcul_temps_sevice_moy : temps négatif\n");
		float tmp = ((nb_clients_servis * tps_service_moyen) + tps_service_client_entrant_serveur) / (nb_clients_servis+1);
		setTempsServiceMoyen(tmp);
	}
	catch(string const& chaine)
    {
       cerr << chaine << endl;
    }
}

File& File::operator=(File const& f){
	ID_file = f.getIDFile();
	centre = f.getCoord();
	ordonnancement = f.getOrdonnancement();
	loi_service = f.getLoi_service();
	distribution_arrivee = f.getDistribution_arrivee();
	taille_max = f.getTailleMax();
	nb_clients = f.getNbClients();
	nb_clients_servis = f.getNbClientsServis();
	nb_clients_presentes = f.getNbClientsPresentes();
	tps_service_moyen = f.getTpsServiceMoy();
	tps_attente_moyen = f.getTpsAttenteMoy();
	nb_clients_entres = f.getNbClientsEntres();
	nb_clients_entres_actuel = f.getNbClientsEntresActuel();

	liste_clients = f.liste_clients;
	liste_nbClients = f.liste_nbClients;
	liste_nbClientsEntres = f.liste_nbClientsEntres;
	liste_serveurs = f.liste_serveurs;
	return *this ;
}


ostream& operator<< (ostream& flux, File const& f){
	flux << "ID file : " << f.ID_file
		<< "\nnombre client : " << f.nb_clients
		<< "\ntaille max : " << f.taille_max
		<< "\nnombre de clients servis : " << f.nb_clients_servis
		<< "\nnombre clients presentes : " << f.nb_clients_presentes
		<< "\ntemps de service moyen : " << f.tps_service_moyen
		<< "\ntemps d'attente moyen : " << f.tps_attente_moyen
		<< "\nnombre de clients entres : " << f.nb_clients_entres
		<< "\nnombre de clients entres actuel : " << f.nb_clients_entres_actuel
		<< "\nordonnancement : " << f.ordonnancement
		<< "\nloi de service : " << f.loi_service
		<< "\ndistribution d'arrivee : " << f.distribution_arrivee
		<< endl;

	return flux;

}
