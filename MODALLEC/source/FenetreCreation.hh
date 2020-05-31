#ifndef FENETRECREATION_HH
#define FENETRECREATION_HH

#include <qt4/QtGui/QWidget>
#include <qt4/QtGui/QMenu>
#include <qt4/QtGui/QAction>
#include <qt4/QtGui/QHBoxLayout>
#include <qt4/QtGui/QPushButton>
#include <qt4/QtGui/QMessageBox>
#include <qt4/QtGui/QInputDialog>
#include <qt4/QtGui/QFileDialog>
#include <qt4/QtGui/QMenuBar>
#include <qt4/QtGui/QGridLayout>
#include "Reseau.hh"
#include "Vue.hh"
#include "DialogConfigFile.hh"
#include "DialogConfigClass.hh"
#include "DialogAddClass.hh"
#include "FenetreSimulationRF.hh"
#include "FenetreSimulationRO.hh"
#include "lecture_ecriture.hh"
#include <stdexcept>



class FenetreCreation : public QWidget
{
  Q_OBJECT

  private :

  Reseau * reseau;
  QGraphicsScene * scene;
  FenetreSimulationRF * fenetre_RF ;
  FenetreSimulationRO * fenetre_RO ;
  QLabel * infos_reseau;
  Vue * vue;
  QGridLayout * layout_principal;
  QHBoxLayout * menu_haut;
  QVBoxLayout * menu_droite;
  QMenuBar * menuBarFichier;
  QMenuBar * menuBarPropreReseau;
  QMenuBar * menuBarClass;
  QMenuBar * menuBarQueue;
  QMenu * menuFichier ;
  QAction * Open;
  QAction * Save;
  QMenu * menuQueue;
  QAction * AddQueue;
  QAction * MoveQueue;
  QAction * RemoveQueue;
  QAction * ConfigureQueue;
  QMenu * menuClass;
  QAction * AddClass;
  QAction * RemoveClass;
  QAction * ConfigureClass;
  QMenu * menuPropreReseau ;
  QAction * reseau1;
  QAction * reseau2;
  QAction * reseau3;
  QAction * reseau4;
  QPushButton * Pause;
  QPushButton * Resume;
  QPushButton * Start;
  QPushButton * Stop;
  QPushButton * Reset;
  QPushButton * Zoom_in;
  QPushButton * Zoom_out;
  QPushButton * Quit;
  QPushButton * changeType;
  QPushButton * change_window;                                                  //Switcher entre la fenêtre de création et la fenêtre de simulation
  QPushButton * voir_routage;                                                   //Afficher le routage d'une classe
  int taille_zoom;
  
  /**Méthode vérifiant la correspondance entre une position et une file
  @param x, l'abscisse de la position
  @param y, l'ordonnée de la position
  @return 1 si il y a une correspondance, 0 sinon
  **/
  bool verif_pos_clic_file(const int x, const int y);

  /**Méthode vérifiant la proximité de la position avec celles des files, de l'entrée et de la sortie
  @param x, l'absicsse de la position
  @param y, l'ordonnée de la position
  @return 1 si il y a une correspondance, 0 sinon
  **/
  bool verif_proximite_clic(const int x, const int y);


  public slots :
  /**Slot mettant en pause la simulation**/
  void pause();
  /**Slot lançant la simulation**/
  void start();
  /**Slot arrêtant la simulation**/
  void stop();
  /**Slot relançant la simulation**/
  void resume();
  /**Slot relançant la simulation après une pause**/
  void reset();
  /**Slot zoomant sur la vue**/
  void zoom_in();
  /**Slot dézoomant sur la vue**/
  void zoom_out();
  /**Slot ajoutant une station**/
  void add_queue();
  /**Slot modifiant la position d'une station**/
  void move_queue();
  /**Slot supprimant une station**/
  void remove_queue();
  /**Slot configurant une station**/
  void configure_queue();
  /**Slot ajoutant une classe de clients**/
  void add_class();
  /**Slot supprimeant une classe de client**/
  void supp_class();
  /**Slot configurant une classe de clients**/
  void configurer_classes();
  /**Slot chargeant un réseau à partir d'un fichier**/
  void open();
  /**Slot sauvegardant un réseau dans un fichier**/
  void save();
  /**Slot fermant l'application**/
  void quitter();
  /**Slot changeant le type du réseau**/
  void changer_type_reseau();
  /**Slots chargeant un réseau déjà défini**/
  void charger_reseau1();
  void charger_reseau2();
  void charger_reseau3();
  void charger_reseau4();
  /**Slot affichant le routage d'une classe**/
  void aff_routage_classe();

  public :
  /**Constructeur**/
  FenetreCreation();
  /**Destructeur**/
  ~FenetreCreation();
  /**Méthode affichant graphiquement le réseau**/
  void afficher_reseau();
  /**Méthode d'affichage du routage d'une classe
  @param cc, une référence sur la classe de client dont le routage doit être afficher
  **/
  void afficher_routage_classe(ClasseClient& cc);
  /**Méthode d'affichage d'une file
  @param coordonnees, les coordonnées de la file à dessiner
  **/
  void afficher_file(coordonnees centre_dessin);
  /**Méthode d'affichage de l'entrée/Sortie**/
  void afficher_entree_sortie();

};

#endif
