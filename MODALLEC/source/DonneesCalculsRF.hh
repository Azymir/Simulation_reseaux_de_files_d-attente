#ifndef DEF_DONNEES_CALCULS_RF
#define DEF_DONNEES_CALCULS_RF

#include "File.hh"
#include <ostream>
#include <stdexcept>

using namespace std;



class DonneesCalculsRF{

	protected:
		list<mesure> listeNbClients; 

	public :
		DonneesCalculsRF() ;
		~DonneesCalculsRF() ;
		
		list<mesure>& getListeNbClients(); 
		//Ajoute un élément mesure à la liste listeNbClients
		void ajouterMesuresNbclients(const int nb_clients, const int temps) ;
		friend ostream& operator << (ostream& flux, DonneesCalculsRF const& d);
	 
};

#endif
