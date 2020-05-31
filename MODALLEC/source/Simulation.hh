#ifndef DEF_SIMULATION
#define DEF_SIMULATION

#include <stdexcept>
#include "Echeancier.hh"
#include "Reseau.hh"

//Structure contenant une valeur et sa probabilité, proba correspond à P(X = nombre) selon la loi de poisson 
typedef struct Poisson{
	int nombre;
	double proba;
}Poisson;

class Simulation{
    protected:
    	Reseau* reseau;
    	//L'échéancier contient la liste des événements et la date actuelle
    	Echeancier echeancier;
    	int duree_simulation;
    	
    	//Compteurs
    	int nbClientsTot;
    	int nbFilesTot;
    	int nbClassesTot;
    	int nbServeursTot;
    	
    public:
		//Accesseurs
    	Reseau* getReseau();
    	Echeancier& getEcheancier();
    	int getDureeSimulation();
    	int getNbClientsTot();
    	int getNbFilesTot();
    	int getNbClassesTot();
    	int getNbServeursTot();
    	void setDureeSimulation(int duree);
    	void setNbClientsTot(int nombre);	
    	void setNbFilesTot(int nombre);	
    	void setNbClassesTot(int nombre);	
    	void setNbServeursTot(int nombre);

		//Méthodes
        void incrementer_nbClientsTot();
        void incrementer_nbFilesTot();
        void incrementer_nbClassesTot();
        void incrementer_nbServeursTot();
        //Exécute le prochain événement selon son type
    	void executer_evenement();
    	//Effectue un événement d'entrée dans une file
    	void EntreeFile(evenement evenement_sorti);
    	//Effectue un événement d'entrée dans un serveur
    	void EntreeServeur(evenement evenement_sorti);
    	//Effectue un événement de sortie dans un serveur
    	void SortieServeur(evenement evenement_sorti);
    	
    	//Cette méthode crée les événement d'entrée dans une file pour chaque client dans la liste de routage du réseau en attribut
    	//Elle est virtuelle pure car elle est différente dans les SimualtionRF et SimulationRO et sera redéfinie
    	virtual void routage_clients() = 0;
    	
    	//Cette méthode crée un nombre de clients équivalent à celui en paramètre puis crée des événements d'entrée dans une file pour ces clients
    	//Elle est virtuelle pure car elle est différente dans les SimualtionRF et SimulationRO et sera redéfinie
    	virtual void distribution_initiale(const int nb_clients_initial) = 0;
    	
    	//Calcule factorielle de n (!n)
    	unsigned long long facto(int n);		
    	//Calcule P(X = k) = (λ^k / k!) * e^(-λ)	
		double calcul_proba_poisson(int k, int lambda);
		//Renvoie un nombre tiré aléatoirement en fonction d'un taux d'arrivée moyen λ (lambda)
    	int calculer_taux_arrivee_poisson(const int lambda);
};

#endif
