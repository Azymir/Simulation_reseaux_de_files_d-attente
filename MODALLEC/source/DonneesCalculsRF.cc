#include "DonneesCalculsRF.hh"

//Constructeur
DonneesCalculsRF::DonneesCalculsRF(){}
//Destructeur
DonneesCalculsRF::~DonneesCalculsRF(){
	listeNbClients.clear();
}
		
		
//Accesseur
list<mesure>& DonneesCalculsRF::getListeNbClients()
{
	return listeNbClients;
	
}

void DonneesCalculsRF::ajouterMesuresNbclients(const int nb_clients, const int temps)
{
	try{
		if((nb_clients < 0) || (temps < 0)) throw invalid_argument("DonneesCalculsRF.ajouterMesuresNbclients : Valeurs négatives\n"); 
		
		mesure m{nb_clients, temps};
		
		listeNbClients.push_back(m);
	}
	catch(string const& chaine)
	{
	    cerr << chaine << endl;
	}
}

ostream& operator << (ostream& flux, DonneesCalculsRF const& d)
{
	return flux ;	
}
