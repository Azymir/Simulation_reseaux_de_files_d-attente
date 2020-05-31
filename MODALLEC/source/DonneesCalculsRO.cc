#include "DonneesCalculsRO.hh"

//Constructeur
DonneesCalculsRO::DonneesCalculsRO(){}

//Destructeur
DonneesCalculsRO::~DonneesCalculsRO(){
	listeNbClientsEntrant.clear();
	listeNbClientSortant.clear();
	listeTSClient.clear();
}

//Accesseurs
list<mesure>& DonneesCalculsRO::getListeNbClientEntrant()
{
	return listeNbClientsEntrant;
}

list<mesure>& DonneesCalculsRO::getListeNbClientSortant()
{
	return listeNbClientsEntrant;
}

list<TSClient>& DonneesCalculsRO::getListeClientEntres()
{
	return listeTSClient;		//changer de nom 
}

//Méthodes
void DonneesCalculsRO::ajouterMesuresNbclientsEntrants (const int nb_clients_entres, const int temps)
{
	try{
		if((nb_clients_entres < 0) || (temps<0)) throw invalid_argument("DonneesCalculsRO.ajouterMesuresNbclientsEntrants : Valeurs négatives\n"); 
		mesure m = {nb_clients_entres, temps};
		listeNbClientsEntrant.push_back(m);
	}
	catch(string const& chaine)
    {
       cerr <<chaine << endl;
    }	
    
}

void DonneesCalculsRO::ajouterMesureNbClientsSortants (const int nb_clients_sortis, const int temps)
{	try{
		if((nb_clients_sortis < 0) || (temps<0)) throw invalid_argument("DonneesCalculsR0.ajouterMesuresNbClientsSortants : Valeurs négatives\n"); 
		mesure m = {nb_clients_sortis, temps};
		listeNbClientSortant.push_back(m);
	}
	catch(string const& chaine)
    {
       cerr << chaine << endl;
    }	
}

void DonneesCalculsRO::ajouter_element_TSclient(const int IDClient, const int date_entree)
{	
	try{
		if((IDClient < 0) || (date_entree < 0)) throw invalid_argument("DonneesCalculsRO.ajouter_element_TSclient : Valeurs négatives\n"); 
		TSClient t{IDClient, date_entree, 0, 0};
		listeTSClient.push_back(t);
	}
	catch(string const& chaine)
    {
       cerr << chaine << endl;
    }	
}

void DonneesCalculsRO::calcul_tps_sejour_client(const int IDClient, const int date_sortie)
{	
	try{
		if((IDClient < 0) || (date_sortie < 0)) throw invalid_argument("DonneesCalculsRO.calcul_tps_sejour_client : Valeurs négatives\n"); 
		
		list<TSClient>::iterator i;
		
		for(i  = listeTSClient.begin() ; i != listeTSClient.end() ; i++)
		{
			if(i->numero_client == IDClient)
			{
				i->date_sortie = date_sortie;
				i->tps_sejour = i->date_sortie - i->date_entree;
			}
		}
	}
	catch(string const& chaine)
    {
       cerr <<chaine << endl;
    }	
}

ostream& operator << (ostream& flux, DonneesCalculsRO const& d)
{
	return flux;
}
