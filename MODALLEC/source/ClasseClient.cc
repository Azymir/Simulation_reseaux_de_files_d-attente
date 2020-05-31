#include "ClasseClient.hh"

//Constructeur
ClasseClient::ClasseClient(const int ID, const int priorite){
	try{
		if( (ID < 0) || (priorite < 0)) throw invalid_argument("Constructeur de ClasseClient : Priorité ou ID négatif\n");
		IDClasseClient = ID ;
		setPriorite(priorite);
		nbClients = 0 ;

	}
    catch(string const& chaine)
	{
       cerr << chaine << endl;
	}
}

//Destructeur
ClasseClient::~ClasseClient(){
	routage.clear();
}


//Accesseurs
int ClasseClient::getIDClasseClient(){
	return IDClasseClient ;
}

int ClasseClient::getNbClients(){
	return nbClients ;
}

vector <int> ClasseClient::getRoutage(){
	return routage ;
}
int ClasseClient::getPriorite(){
	return priorite;
}

void ClasseClient::setPriorite(const int numero){
	try{
		if(numero < 0) throw invalid_argument("ClasseClient.setPriorite : numero négative\n");
		priorite = numero;
	}
	catch(string const& chaine)
	{
	    cerr << chaine << endl;
	}

}
void ClasseClient::setNbClients(const int nombre){
	try{
		if(nombre < 0) throw invalid_argument("ClasseClient.setNbClients : ID négatif\n");
		nbClients = nombre;
	}
	catch(string const& chaine)
	{
	    cerr << chaine << endl;
	}
}


//Méthodes


void ClasseClient::supprimer_file_routage(const int IDfile){
	try{
		if(IDfile < 0) throw invalid_argument("ClasseClient.supprimer_file_routage : IDfile négatif\n"); //plus petit ID à 0
		int i = 0;
		vector<int>::iterator it = routage.begin();
		//On parcourt la liste de routage
		while(it != routage.end())
		{
			for ( ; it != routage.end() ; ++it)
			{
				if(*it == IDfile)
				{
					routage.erase(routage.cbegin() + i);	//Supprime l'élément à la position begin + i
					break;
				}
				i++;
			}

		}
	}
	catch(string const& chaine)
	{
	    cerr << chaine << endl;
	}
}



void ClasseClient::definir_routage(const string newRoutage){
	try
	{
		if(!routage.empty()) routage.clear();
		//On définit une expression régulière pour tester le format du string en paramètre
		std::regex er("([[:digit:]]+)((\\-)[[:digit:]]+).*");

		int stock1 = 0;
		std::string stock2 = "";
		if(std::regex_match (newRoutage,er)){
			for(long unsigned int i = 0; i < newRoutage.size() ; i++){
				//Si le caractère est un chiffre
				if(newRoutage.at(i) != '-'){
					stock2 = stock2 + newRoutage.at(i);
				}
				//Si c'est un tiret
				else{
					stock1 = std::stoi(stock2);
					stock2.assign("");
					//On ajoute le numéro au routage
					routage.push_back(stock1);
				}
			}
		stock1 = std::stoi(stock2);
		routage.push_back(stock1);
		}
		else throw std::invalid_argument("ClasseClient.definir_routage : Erreur format routage");
	}
	catch(string const& chaine)
	{
	    cerr << chaine << endl;
	}
}

int ClasseClient::trouver_file(const int pos_actuelle){
	try
	{
		size_t i = (size_t)pos_actuelle;	
		if((i < 0) || (i > routage.size())) throw invalid_argument("ClasseClient.trouver_file : pos_actuelle invalide \n");
	}
	catch(string const& chaine)
	{
	    cerr << chaine << endl;
	}
	//On retourne la valeur à la position actuelle
	return routage.at(pos_actuelle);
}

int ClasseClient::prochaine_file_routage(const int pos_precedente){
	try{
		long unsigned int tmp = pos_precedente + 1;
		
		if((tmp <= routage.size()) && (tmp > 0)){
			//Si la file atteint la fin du routage
			if(tmp == routage.size()) 
			//Retourne le routage à la position 0
				return routage.at(0);
			//Sinon retourne le routage à la position suivante
			else return routage.at(tmp);
		}
		else throw std::runtime_error("ClasseClient.prochaine_file_routage : Erreur routage.size()");
	}
	catch(string const& chaine)
	{
	    cerr << chaine << endl;
	}
	return -1; 
}

ostream& operator << (ostream &flux, ClasseClient const& cc){
	flux << "Identifiant : " << cc.IDClasseClient 
		 <<"\nNombre de client :"<<cc.nbClients
		 <<"\nPriorité de la classe :"<<cc.priorite<<endl;
	return flux;
}
