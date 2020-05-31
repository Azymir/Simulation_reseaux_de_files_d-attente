#include <fstream>
#include "lecture_ecriture.hh"


/**Méthode s'occupant de la lecture du fichier contenant les données d'un réseau
  @param reseau, pointeur sur le réseau
  @param nomfic, nom du fichier à lire
  **/
void lecture_fichier_reseau (Reseau * reseau, const string nomfic){

	ifstream fichier(nomfic);  // on ouvre en lecture
	if(fichier.fail()){
                cerr << "Le fichier " << nomfic << " n'existe pas";
                exit(EXIT_FAILURE);
    }

    int cmp = 0; //compteur pour compter la position du mot dans le fichier de lecture
    int id = 0,abs = 0,ord = 0,priorite = 0;
    File * file = NULL;
    ClasseClient * cc = NULL;
    string ligne;
    if (fichier.good())
	{
		string tmp;
		fichier>>tmp;
		if(tmp.compare("Reseau_ferme")==0)
			reseau->setTypeReseau(0);
		if(tmp.compare("Reseau_ouvert")==0)
			reseau->setTypeReseau(1);
		while(fichier.good())
		{
			string tmp;
			fichier>>tmp;
			if(tmp.compare("-")==0)//s'il l'on arrive aux classes du réseau
				break;
			if(cmp%8==0)//id de la file
				id = atoi(tmp.c_str());
			if(cmp%8==1)//abs de la file
				abs = atoi(tmp.c_str());
			if(cmp%8==2)//ord de la file
			{
				ord = atoi(tmp.c_str());
				file = new File(id,abs,ord);
			}
			if(cmp%8==3)//taille_max de la file
			{
				ligne += tmp;
				ligne += "_"; //un espace pour séparer les champs de la file
			}
			if(cmp%8==4)//loi service de la file
			{
				ligne += tmp;
				ligne += "_"; //un espace pour séparer les champs de la file
			}
			if(cmp%8==5)//ordonnnancement de la file
			{
				ligne += tmp;
				ligne += "_"; //un espace pour séparer les champs de la file
			}
			if(cmp%8==6)//distribution arrivée
			{
				ligne += tmp;
				ligne += "_"; //un espace pour séparer les champs de la file
			}
			if(cmp%8==7)//nbre serveurs
			{
				ligne+=tmp;
				lecture_file(file,ligne);
				reseau->ajouter_file(file);
				//delete file;
				ligne = "";
			}
			cmp++;
		}
		cmp = 0;
		int cmp2 = 0;//savoir à quelle classe on se situe
		ligne = "";
		while(fichier.good())//au niveau des classes composant le réseau
		{
			string tmp;
			fichier>>tmp;
			if(tmp.compare("Reseau_monoclasse")==0)//si le réseau est monoclasse
				break;
			if(tmp.compare("fin_classe")==0)
			{
				ligne = ligne.substr(0, ligne.size()-1); //enlever le - de la chaîne pour avoir le format "0-1"
				if(cc != NULL && cmp2>=1)//car la première classe est standard pas la peine de l'ajouter au réseau
				{
					lecture_type(cc,ligne);
					reseau-> ajouter_classe(cc);
					cc = NULL;
				}
				ligne = "";
				cmp=0;
				cmp2++;
			}
			else
			{
				if(cmp==0)
				{
					id = atoi(tmp.c_str());
					cmp++;
				}
				else if(cmp==1)
				{
					priorite = atoi(tmp.c_str());
					cc = new ClasseClient(id,priorite);
					cmp++;
				}
				else if(cmp>1)
				{
					ligne += tmp;
					ligne += "-";
					cmp++;
				}
			}
		}
	}

}

/**Méthode s'occupant de la lecture d'une file écrite dans un string
  @param file, pointeur sur une file
  @param ligne, ligne à lire
  **/
void lecture_file (File * file, const string ligne){
	int cmp = 0; //compteur pour compter la position du mot dans la ligne de lecture
    string taille_max, loi,ordonnnancement,distrib,nbre_serveurs;
    for(size_t i = 0;i<ligne.length();i++)
    {
    	if(ligne[i]=='_')
    		cmp ++ ;
    	else{
    		if(cmp==0)
    		{
    			taille_max+=ligne[i];
    			file->setTailleMax(atoi(taille_max.c_str()));
    		}
    		if(cmp==1)
    		{
    			loi+=ligne[i];
    			file->setLoiService(atoi(loi.c_str()));
    		}
    		if (cmp==2)
    		{
    			ordonnnancement+=ligne[i];
    			file->setOrdonnancement(atoi(ordonnnancement.c_str()));
    		}
    		if(cmp==3)
    		{
    			distrib+=ligne[i];
    			file->setDistribution(atoi(distrib.c_str()));
    		}
    		if(cmp==4)
    		{
    			nbre_serveurs+=ligne[i];
    			for (int i=0; i<atoi(nbre_serveurs.c_str()); i++){//provisoire
					Serveur *s = new Serveur(i);
					file->ajouter_serveur(*s);
				  }
    		}

    	}
    }
}

/**Méthode s'occupant de la lecture d'une classe client écrite dans un string
  @param cc, pointeur sur une classe client
  @param ligne, ligne à lire
  **/
//en considérant qu'on appelle cette fonction uniquement sur un réseau multiclasse
void lecture_type (ClasseClient* cc, const string ligne){
	cc->definir_routage(ligne);

}

/**Méthode s'occupant de l'écriture d'un reseau dans un fichier
  @param nomfic, nom du fichier dans lequel le réseau est écrit
  @param reseau, reseau dont les caractéristiques sont enregistrées
  **/
void ecriture_fichier_reseau (const string nomfic, Reseau& reseau){
	ofstream * fic = new ofstream(nomfic.c_str());
	if(reseau.getTypeReseau()==0)
		*fic << "Reseau_ferme" << endl;
	else
		*fic << "Reseau_ouvert" << endl;
	ecriture_fichier_file(fic,reseau);
	ecriture_fichier_classe(fic,reseau);
	delete fic;

}

/**Méthode s'occupant de l'écriture des files composant un réseau dans un fichier
  @param fic, pointeur sur le fichier
  @param reseau, reseau dont les files sont enregistrées
  **/
void ecriture_fichier_file (ofstream* fic, Reseau& reseau){

	if(*(fic)){

		list<File*> f = reseau.getListeFile();
		for(auto i = f.begin();i!=f.end();i++){
			*fic << (*i)->getIDFile() << " ";
			*fic << (*i)->getCoord().x << " ";
			*fic << (*i)->getCoord().y << " ";
			*fic << (*i)->getTailleMax() << " ";
			*fic << (*i)->getLoi_service() << " ";
			*fic << (*i)->getOrdonnancement() << " ";
			*fic << (*i)->getDistribution_arrivee() << " ";
			*fic << (*i)->getListeServeur().size() << endl;
		}
		*fic << "-" << endl;
	}
	else{
		cerr << "impossible d'ouvrir le fichier en écriture" << endl;
		exit(EXIT_FAILURE);
	}
}

/**Méthode s'occupant de l'écriture des classes composant un réseau dans un fichier
  @param fic, pointeur sur le fichier
  @param reseau, reseau dont les classes sont enregistrées
  **/
void ecriture_fichier_classe (ofstream* fic, Reseau& reseau){
	if(*(fic)){

		list<ClasseClient*> c = reseau.getListeClasseClient();
		if(c.size()==1)
			*fic << "Reseau_monoclasse" << endl;
		else{
			for(auto i = c.begin();i!=c.end();i++){
				*fic << (*i)->getIDClasseClient() << " ";
				*fic << (*i)->getPriorite() << " ";
				vector<int> f = (*i)->getRoutage();
				for(auto j = f.begin();j<f.end();j++)
					*fic << (*j) << " ";
				*fic << "fin_classe" << endl;
			}
		}
	}
	else{
		cerr << "impossible d'ouvrir le fichier en écriture" << endl;
		exit(EXIT_FAILURE);
	}

}

/**Méthode s'occupant de l'écriture des performances d'un réseau fermé dans un fichier
  @param nomfic, nom du fichier dans lequel les performances sont écrites
  @param h, historique des performances d'un réseau fermé
  **/
void ecriture_fichier_performancesRF (const string nomfic, HistoriqueRF& h){
	ofstream * fic = new ofstream(nomfic.c_str());
	list<PerformancesRF> p = h.getHistorique();
	for(auto i = p.begin(); i!=p.end(); i++){
		*fic << "Date: " << (*i).perfReseau->getDate() << endl;
		*fic << "Average clients of the network: " << (*i).perfReseau->getNbMoyenClients() << endl;
		list <PerfsFile*> lpf = (*i).ListePerfsFiles;
		*fic << "Number of queues: " << lpf.size() << endl;
		*fic << endl;
		for (auto j = lpf.begin(); j!= lpf.end(); j++){
			*fic << "ID of queue: " << (*j)->getFile().getIDFile() << " ";
			*fic << "Average clients: " << (*j)->getNbMoyenClientsFile() << " ";
			*fic << "Average waiting time: " << (*j)->getTpsAttenteMoy () << " ";
			*fic << "Average service time: " << (*j)->getTpsServiceMoy () << " ";
			*fic << "Average response time: " << (*j)->getTpsReponseMoy () << endl << "	";
			*fic << "Average interarrival time: " << (*j)->getTpsinterarriveeMoy () << " ";
			*fic << "Loss rate: " << (*j)->getTauxPerte() << endl << "	";
			list<PerfServeur> lps= (*j)->getListeResPerfServeur();
			*fic << "Number of servers: " << lps.size() << endl << "	";
			for (auto k = lps.begin(); k!= lps.end(); k++){
				*fic << "ID of server: " << (*k).numero_serveur << " ";
				*fic << "Use rate: " << (*k).taux_utilisation << endl << "	";
			}
			*fic << endl;
		}
		*fic << endl;

	}

	delete fic;

}


/**Méthode s'occupant de l'écriture des performances d'un réseau ouvert dans un fichier
  @param nomfic, nom du fichier dans lequel les performances sont écrites
  @param h, historique des performances d'un réseau ouvert
  **/
void ecriture_fichier_performancesRO (const string nomfic, HistoriqueRO & h){
	ofstream * fic = new ofstream(nomfic.c_str());
	list<PerformancesRO> p = h.getHistorique();
	for(auto i = p.begin(); i!=p.end(); i++){
		*fic << "Date: " << (*i).perfReseau->getDate() << endl;
		*fic << "Average clients of the network: " << (*i).perfReseau->getNbMoyenClients() << endl;
		*fic << "Input rate: " << (*i).perfReseau->getDebitEntree() << endl;
		*fic << "Output rate: " << (*i).perfReseau->getDebitSortie() << endl;
		*fic << "Average residence time: " << (*i).perfReseau->getTpsSejourMoyen() << endl;
		list <PerfsFile*> lpf = (*i).ListePerfsFiles;
		*fic << "Number of queues: " << lpf.size() << endl;
		*fic << endl;
		for (auto j = lpf.begin(); j!= lpf.end(); j++){
			*fic << "ID of queue: " << (*j)->getFile().getIDFile() << " ";
			*fic << "Average clients: " << (*j)->getNbMoyenClientsFile() << " ";
			*fic << "Average waiting time: " << (*j)->getTpsAttenteMoy () << " ";
			*fic << "Average service time: " << (*j)->getTpsServiceMoy () << " ";
			*fic << "Average response time: " << (*j)->getTpsReponseMoy () << endl << "	";
			*fic << "Average interarrival time: " << (*j)->getTpsinterarriveeMoy () << " ";
			*fic << "Loss rate: " << (*j)->getTauxPerte() << endl << "	";
			list<PerfServeur> lps= (*j)->getListeResPerfServeur();
			*fic << "Number of servers: " << lps.size() << endl << endl << "	";
			for (auto k = lps.begin(); k!= lps.end(); k++){
				*fic << "ID of server: " << (*k).numero_serveur << " ";
				*fic << "Use rate: " << (*k).taux_utilisation << endl << "	";
			}
			*fic << endl;
		}
		*fic << endl;

	}

	delete fic;

}
