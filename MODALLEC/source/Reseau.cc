#include "Reseau.hh"

//Constructeur
Reseau::Reseau(){
		type_reseau = 0;
		nb_clients = 0;
		nb_clients_passes = 0;
		nb_files = 0;
		nb_classes = 0;
}

//Destructeur
Reseau::~Reseau(){

	list <File *>::iterator file = liste_File.begin();
	//On désalloue chaque file de la liste des files
	
	if(liste_File.empty())
	{
		while(file != liste_File.end())
		{
			delete *file;
			file = liste_File.erase(file);
		}
	}

	list <Client *>::iterator client = liste_ClientARouter.begin();

	//On désalloue chaque client de la liste des clients à router
	if(liste_ClientARouter.empty())
	{
		while(client != liste_ClientARouter.end())
		{
			delete *client;
			client = liste_ClientARouter.erase(client);
		}
	}

	list <ClasseClient *>::iterator classe_client = liste_ClasseClient.begin();

	//On désalloue chaque classe de la liste des classes
	if(liste_ClasseClient.empty()){
		while(classe_client != liste_ClasseClient.end())
		{
			delete *classe_client;
			classe_client = liste_ClasseClient.erase(classe_client);
		}
	}
}


//Accesseurs
int Reseau::getTypeReseau(){
	return type_reseau;
}

int Reseau::getNbFiles(){
	return nb_files;
}

int Reseau::getNbClasses(){
	return nb_classes;
}

int Reseau::getNbClients(){
	return nb_clients;
}

int Reseau::getNbClientsPasses(){
	return nb_clients_passes;
}

list<File*>& Reseau::getListeFile(){
	return liste_File;
}

list<Client*>& Reseau::getListeClientARouter(){
	return liste_ClientARouter;
}

list<ClasseClient*>& Reseau::getListeClasseClient(){
	return liste_ClasseClient;
}

void Reseau::setNbClients(const int nombre){
	try{
		if(nombre < 0) throw invalid_argument("Reseau.setNbClients : nombre négatif\n");
		nb_clients = nombre;
	}
	catch(string const& chaine)
	{
	    cerr << chaine << endl;
	}
}

void Reseau::setNbClientsPasses(const int nombre){
	try{
		if(nombre < 0) throw invalid_argument("Reseau.setNbClientsPasses : nombre négatif\n");
		nb_clients_passes = nombre;
	}
	catch(string const& chaine)
	{
	    cerr <<chaine << endl;
	}
}

void Reseau::setTypeReseau(const int type){
	try{
		if(type != 0 && type != 1) throw invalid_argument("Reseau.setTypeReseau : nombre négatif\n");
		type_reseau = type;
	}
	catch(string const& chaine)
	{
	    cerr << chaine << endl;
	}
}


//Méthodes

void Reseau::ajouter_file(File* f){
	liste_File.push_back(f);
	nb_files++;
}

void Reseau::ajouter_client_routage(Client* client){
	if(!client->getClasse()->getRoutage().empty()) liste_ClientARouter.push_front(client);
	else liste_ClientARouter.push_back(client);
}

void Reseau::supprimer_file(const int ID_file){
	try {
		if(ID_file < 0) throw invalid_argument("Reseau.supprimer_file : ID_File négatif\n");
		list<File*>::iterator it;
		//On parcourt la liste des files
	    for (it = liste_File.begin() ; it != liste_File.end() ; it++){
			if((*it)->getIDFile() == ID_file){
					delete (*it);
					liste_File.erase(it);
					break;
			}
		}
		nb_files--;
	}
	catch(string const& chaine)
	{
	    cerr << chaine << endl;
	}
}

void Reseau::vider_liste_routage(){
	liste_ClientARouter.clear();
}

void Reseau::ajouter_classe(ClasseClient* classe){
	liste_ClasseClient.push_back(classe);
	nb_classes++;
}

void Reseau::supprimer_classe(const int ID_classe){
	try {
		if(ID_classe < 0) throw invalid_argument("Reseau.supprimer_classe : ID négatif\n");
		list<ClasseClient*>::iterator it;
		//On parcourt la liste des classes
	    for (it = liste_ClasseClient.begin() ; it != liste_ClasseClient.end() ; it++){
			if((*it)->getIDClasseClient() == ID_classe){
					delete (*it);
					liste_ClasseClient.erase(it);
					break;
			}
		}
		nb_classes--;
	}
	catch(string const& chaine)
	{
	    cerr << chaine << endl;
	}
}



File * Reseau::chercherFile(int IDFile){
	list<File*>::iterator it;
	//On parcourt la liste des files
	for (it = liste_File.begin() ; it != liste_File.end() ; it++){
		if((*it)->getIDFile() == IDFile){
				return (*it);
		}
	}
	return NULL;
}


ostream& operator << (ostream& flux, Reseau const& r){
flux << "type reseau : " << r.type_reseau
	 << "\nnombre client : " << r.nb_clients
	 << "\nnombre clients passes : " << r.nb_clients_passes
	 << "\nnombre files : " << r.nb_files
	 << "\nnombre de classe : " << r.nb_classes << endl;

return flux;
}
