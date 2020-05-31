#ifndef DEF_SIMULATIONRO
#define DEF_SIMULATIONRO

#include "Simulation.hh"
#include "DonneesCalculsRO.hh"


class SimulationRO: public Simulation{
	private:
		DonneesCalculsRO donnees_calculs;
	public:
		//Constructeur
		SimulationRO(Reseau* reseau, int duree);
		//Destructeur
		~SimulationRO();
		//Accesseur
		DonneesCalculsRO& getDonnes_calculs();
		//Méthodes
		void routage_clients();
		void distribution_initiale(const int nb_clients_initial);
		void entrer_clients_reseau();																								
		void sortir_clients_reseau();																							

};

#endif
