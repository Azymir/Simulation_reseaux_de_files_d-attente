#ifndef DEF_SIMULATIONRF
#define DEF_SIMULATIONRF

#include "Simulation.hh"
#include "DonneesCalculsRF.hh"


class SimulationRF: public Simulation{
	
	private:
		DonneesCalculsRF donnees_calculs;
		
	public:
		//Constructeur
		SimulationRF(Reseau* reseau, const int duree);
		//Destructeur
		~SimulationRF();
		
		//Accesseur
		DonneesCalculsRF& getDonnes_calculs();
		
		//Méthodes
		void routage_clients();
		void distribution_initiale(const int nb_clients_initial);

		
};

#endif
