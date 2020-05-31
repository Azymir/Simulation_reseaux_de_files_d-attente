#ifndef FENETRESIMULATIONRO_HH
#define FENETRESIMULATIONRO_HH

#include <qt4/QtGui/QWidget>
#include <qt4/QtGui/QPushButton>
#include <qt4/QtCore/QTimer>
#include <qt4/QtCore/QTime>
#include <qt4/QtGui/QInputDialog>
#include <qt4/QtGui/QMessageBox>
#include <qt4/QtGui/QVBoxLayout>
#include <qt4/QtGui/QGridLayout> //Ajouté pour ranger la fenêtre
#include "FenetreEcheancier.hh"
#include "FenetreInfosReseau.hh"
#include "Vue.hh"
#include "DialogResultatsRO.hh"
#include "DialogHistoriqueRO.hh"
#include "DialogInfosClass.hh"
#include "DialogInfosQueue.hh"
#include "lecture_ecriture.hh"
#include "SimulationRO.hh" //A ajouter au rapport

class FenetreSimulationRO : public QWidget
{
  Q_OBJECT

  private:
    SimulationRO simulation;
    HistoriqueRO historique; //A expliquer dans le compte-rendu
    FenetreInfosReseau fenetre_infos_reseau;
    FenetreEcheancier fenetre_echeancier;
    Vue * vue;
    QPushButton * results;
    QPushButton * history;
    QPushButton * infos_queue;
    QPushButton * infos_classes;
    //Switche de la fenêtre de simulation vers la fenêtre de création
    QPushButton * change_window;
    QGridLayout * layout_principal;
    QVBoxLayout * layout;
    QTime * chrono;
    QTimer * timer_chrono;
    int secondes;
    bool arret;

  public slots:
  /**Slot calculant et affichant les résultats de performances du réseau**/
  void Results();
  /**Slot affichant l'historique des performances du réseau**/
  void History();
  /**Slot affichant les informations de la station cliquée**/
  void Infos_Queue();
  /**Slot affichant les informations de la classe demandée**/
  void Infos_Classes();
  /**Slot mettant à jour le chronomètre**/
  void chrono_refresh();

  public:
  /**Constructeur
  @param r, l'adresse du réseau à simuler
  @param v, l'adresse de la vue affichant graphiquement le réseau
  @param parent, l'adresse du widget parent de la fenêtre
  **/
  FenetreSimulationRO(Reseau * r = NULL, Vue * v = NULL,QWidget * parent = NULL); //Ajouter le paramètre Reseau
  /**Destructeur**/
  ~FenetreSimulationRO();
  /**Méthode de récupération de la simulation
  @return une référence sur la simulation**/
  SimulationRO& getSimulation();                                              //A expliquer dans le compte-rendu
  /**Méthode de récupération de l'historique
  @return une référence sur l'historique'*/
  HistoriqueRO& getHistorique();
  /**Méthode de récupération de la fenêtre d'informations du réseau
  @return une réference sur la fenêtre d'informations du réseau**/
  FenetreInfosReseau& getFenetreInfosReseau();
  /**Méthode d'affichage graphique du nombre de clients**/
  void afficher_compteur_clients();
  /**Méthode de lancement du chronomètre**/
  void start_chrono();
  /**Méthode relançant la simulation**/
  void resume();
  /**Méthode mettant en pause la simualtion**/
  void pause();
  /**Méthode arrêtant la simulation**/
  void stop();
  /**Méthode exécutant la simulation
  @param nbClientsInitial, le nombre de clients à créer pour le début de la simualtion**/
  void executer_simulation(const int nbClientsInitial);

  };

  #endif
