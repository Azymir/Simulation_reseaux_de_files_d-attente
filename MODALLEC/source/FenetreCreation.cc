#include "FenetreCreation.hh"
#include <qt4/QtGui/QGraphicsItem>
#include <qt4/QtGui/QDesktopWidget>
#include <qt4/QtGui/QApplication>
#include <iostream>

using namespace std;

#define LARGEUR_FILE 50
#define LONGUEUR_FILE 100
#define DIAMETRE_SERVEUR 50

/**Constructeur**/
FenetreCreation::FenetreCreation():QWidget()
{
  //Retirer la barre du haut de la fenêtre
  setWindowFlags(Qt::CustomizeWindowHint);

  //Délimiter la taille de la fenêtre
  setFixedSize(QApplication::desktop()->width(),QApplication::desktop()->height()-70);

  //Initialiser les attributs
  taille_zoom = 0;
  reseau = new Reseau;
  vue = new Vue(this);
  scene = new QGraphicsScene(0,0,vue->width(),vue->height());
  vue->setScene(scene);
  fenetre_RF = new FenetreSimulationRF(reseau,vue);
  fenetre_RO = new FenetreSimulationRO(reseau,vue);
  infos_reseau = new QLabel("<strong> Number of :<br>Classes :</strong> 1<br> <strong>Queues :</strong> 0 ");
  menu_haut = new QHBoxLayout;
  menu_droite = new QVBoxLayout;
  layout_principal = new QGridLayout;
  menuBarQueue = new QMenuBar;
  menuBarClass = new QMenuBar;
  menuBarFichier = new QMenuBar;
  menuBarPropreReseau = new QMenuBar;
  menuQueue = new QMenu("Queue");
  menuClass = new QMenu("Class");
  menuFichier = new QMenu("File");
  menuPropreReseau = new QMenu("Networks");
  AddQueue = new QAction("Add queue",menuQueue);
  MoveQueue = new QAction("Move queue",menuQueue);
  RemoveQueue = new QAction("Remove queue",menuQueue);
  ConfigureQueue = new QAction("Configure queue",menuQueue);
  AddClass = new QAction("Add class",menuClass);
  RemoveClass = new QAction("Remove class",menuClass);
  ConfigureClass = new QAction("Configure class",menuClass);
  Open = new QAction("Open network",menuFichier);
  Save = new QAction("Save network",menuFichier);
  reseau1 = new QAction("Network 1",menuPropreReseau);
  reseau2 = new QAction("Network 2",menuPropreReseau);
  reseau3 = new QAction("Network 3",menuPropreReseau);
  reseau4 = new QAction("Network 4",menuPropreReseau);
  Pause = new QPushButton("Pause");
  Resume = new QPushButton("Resume");
  Start = new QPushButton("Start");
  Stop = new QPushButton("Stop");
  Reset = new QPushButton("Reset");
  Quit = new QPushButton("Quit");
  changeType = new QPushButton("Change type");
  Zoom_in = new QPushButton("+");
  Zoom_out = new QPushButton("-");
  change_window = new QPushButton("Switch \nwindow");
  voir_routage = new QPushButton("Routing");

  //Personnaliser le label d'information sur le réseau
  infos_reseau->setStyleSheet(
    "background-color: #B0C4DE; border-style: inset; border-width: 2px; border-radius: 10px; border-color: darkgrey; font: bold 14px; min-width: 5em; padding: 6px; font : Serif;"
  );

  //Ajouter la boîte de rangement de tous les objets de la fenêtre à la fenêtre
  setLayout(layout_principal);

  //Ajouter les boîtes de rangement secondaires à la boîte de rangement principal
  layout_principal->addLayout(menu_haut,0,0,1,3);
  layout_principal->addLayout(menu_droite,1,5,1,1);
  layout_principal->addWidget(vue,1,0,4,5);

  //Ajouter les objets aux boîtes secondaires
  menuBarQueue->addMenu(menuQueue);
  menuBarClass->addMenu(menuClass);
  menuBarFichier->addMenu(menuFichier);
  menuBarPropreReseau->addMenu(menuPropreReseau);
  menuQueue->addAction(AddQueue);
  menuQueue->addAction(MoveQueue);
  menuQueue->addAction(RemoveQueue);
  menuQueue->addAction(ConfigureQueue);
  menuClass->addAction(AddClass);
  menuClass->addAction(RemoveClass);
  menuClass->addAction(ConfigureClass);
  menuPropreReseau->addAction(reseau1);
  menuPropreReseau->addAction(reseau2);
  menuPropreReseau->addAction(reseau3);
  menuPropreReseau->addAction(reseau4);
  menuFichier->addAction(Open);
  menuFichier->addAction(Save);
  menu_haut->addWidget(menuBarFichier);
  menu_haut->addWidget(menuBarPropreReseau);
  menu_haut->addWidget(Pause);
  menu_haut->addWidget(Resume);
  menu_haut->addWidget(Start);
  menu_haut->addWidget(Stop);
  menu_haut->addWidget(Reset);
  menu_haut->addWidget(Quit);
  menu_droite->addWidget(infos_reseau);
  menu_droite->addWidget(Zoom_in);
  menu_droite->addWidget(Zoom_out);
  menu_droite->addWidget(menuBarQueue);
  menu_droite->addWidget(menuBarClass);
  menu_droite->addWidget(changeType);
  menu_droite->addWidget(voir_routage);
  menu_droite->addWidget(change_window);

  //Désactiver les boutons inutilisables pendant l'étape de création
  Pause->setDisabled(true);
  Resume->setDisabled(true);
  Stop->setDisabled(true);
  change_window->setDisabled(true);

  //Connecter les boutons à leur slot
 connect(AddQueue,SIGNAL(triggered()),this,SLOT(add_queue()));
 connect(MoveQueue,SIGNAL(triggered()),this,SLOT(move_queue()));
 connect(RemoveQueue,SIGNAL(triggered()),this,SLOT(remove_queue()));
 connect(ConfigureQueue,SIGNAL(triggered()),this,SLOT(configure_queue()));
 connect(AddClass,SIGNAL(triggered()),this,SLOT(add_class()));
 connect(RemoveClass,SIGNAL(triggered()),this,SLOT(supp_class()));
 connect(ConfigureClass,SIGNAL(triggered()),this,SLOT(configurer_classes()));
 connect(reseau1,SIGNAL(triggered()),this,SLOT(charger_reseau1()));
 connect(reseau2,SIGNAL(triggered()),this,SLOT(charger_reseau2()));
 connect(reseau3,SIGNAL(triggered()),this,SLOT(charger_reseau3()));
 connect(reseau4,SIGNAL(triggered()),this,SLOT(charger_reseau4()));
 connect(Open,SIGNAL(triggered()),this,SLOT(open()));
 connect(Save,SIGNAL(triggered()),this,SLOT(save()));
 connect(Pause,SIGNAL(clicked()),this,SLOT(pause()));
 connect(Resume,SIGNAL(clicked()),this,SLOT(resume()));
 connect(Start,SIGNAL(clicked()),this,SLOT(start()));
 connect(Stop,SIGNAL(clicked()),this,SLOT(stop()));
 connect(Reset,SIGNAL(clicked()),this,SLOT(reset()));
 connect(Quit,SIGNAL(clicked()),this,SLOT(quitter()));
 connect(changeType,SIGNAL(clicked()),this,SLOT(changer_type_reseau()));
 connect(Zoom_in,SIGNAL(clicked()),this,SLOT(zoom_in()));
 connect(Zoom_out,SIGNAL(clicked()),this,SLOT(zoom_out()));
 connect(voir_routage,SIGNAL(clicked()),this,SLOT(aff_routage_classe()));

 //Crée la classe de clients de base
 reseau->ajouter_classe(new ClasseClient(0,20));
 //Augmente le nombre total de classes dans la simulation
 fenetre_RF->getSimulation().incrementer_nbClassesTot();
 fenetre_RO->getSimulation().incrementer_nbClassesTot();


}

/**Destructeur**/
FenetreCreation::~FenetreCreation()
{
  delete fenetre_RF;
  delete fenetre_RO;
  delete infos_reseau;
  scene->clear();

  //Supprimer toutes les vues rattachées à la scène
  for(auto vue : scene->views())
  {
    delete vue;
  }

  delete scene;
  delete Pause;
  delete Resume;
  delete Start;
  delete Stop;
  delete Reset;
  delete Quit;
  delete reseau1;
  delete reseau2;
  delete reseau3;
  delete reseau4;
  delete menuPropreReseau;
  delete menuBarPropreReseau;
  delete Open;
  delete Save;
  delete menuFichier;
  delete menuBarFichier;
  delete menu_haut;
  delete changeType;
  delete AddQueue;
  delete MoveQueue;
  delete RemoveQueue;
  delete ConfigureQueue;
  delete menuQueue;
  delete menuBarQueue;
  delete AddClass;
  delete RemoveClass;
  delete ConfigureClass;
  delete menuClass;
  delete menuBarClass;
  delete Zoom_in;
  delete Zoom_out;
  delete change_window;
  delete menu_droite;
  delete layout_principal;

  delete reseau;
}

/**Méthode vérifiant la correspondance entre une position et une file
@param x, l'abscisse de la position
@param y, l'ordonnée de la position
@return 1 si il y a une correspondance, 0 sinon
**/
bool FenetreCreation::verif_pos_clic_file(const int x, const int y)
{
  //Défiler la liste des files du réseau
  for(auto it_files = reseau->getListeFile().begin(); it_files != reseau->getListeFile().end(); it_files++)
  {
    //Vérifier leur coordonnées
    if((x < (*it_files)->getCoord().x + LONGUEUR_FILE)
    && (x > (*it_files)->getCoord().x - LONGUEUR_FILE/2)
    && (y < (*it_files)->getCoord().y + LARGEUR_FILE/2)
    && (y > (*it_files)->getCoord().y - LARGEUR_FILE/2))
    {
      return 1;
    }
  }

  return 0;
}

/**Méthode vérifiant la proximité de la position avec celles des files, de l'entrée et de la sortie
@param x, l'absicsse de la position
@param y, l'ordonnée de la position
@return 1 si il y a une correspondance, 0 sinon
**/
bool FenetreCreation::verif_proximite_clic(const int x, const int y)
{
  //Vérifier que le clic n'est pas égale à une file
  for(auto it_files = reseau->getListeFile().begin(); it_files != reseau->getListeFile().end(); it_files++)
  {
    if((x < (*it_files)->getCoord().x + LONGUEUR_FILE + LONGUEUR_FILE/2)
    && (x > (*it_files)->getCoord().x - LONGUEUR_FILE/2 - LONGUEUR_FILE)
    && (y < (*it_files)->getCoord().y + LARGEUR_FILE)
    && (y > (*it_files)->getCoord().y - LARGEUR_FILE))
    {
      return 1;
    }
  }

  //Vérifier que le clic ne correpsond pas à l'entére ou la sortie
  if(reseau->getTypeReseau() == 1)
  {
    if((((vue->getPosXClic()> scene->width()-(scene->width()-10) - LONGUEUR_FILE) && (vue->getPosXClic() < scene->width()-(scene->width()-10) + 75 + LONGUEUR_FILE/2))
    &&((vue->getPosYClic()> scene->height()/2 - LARGEUR_FILE/2) && (vue->getPosYClic() < scene->height()/2 + 25 + LARGEUR_FILE/2)))
    ||(((vue->getPosXClic()> scene->width()-80 - LONGUEUR_FILE) && (vue->getPosXClic() < scene->width()-80 + 75 + LONGUEUR_FILE/2))
    &&((vue->getPosYClic()> scene->height()/2 - LARGEUR_FILE/2) && (vue->getPosYClic() < scene->height()/2 + 25 + LARGEUR_FILE/2))))
    {
      return 1;
    }
  }

  return 0;
}

/**Slot mettant en pause la simulation**/
void FenetreCreation::pause()
{
  if(reseau->getTypeReseau()==0) fenetre_RF->pause();
  else fenetre_RO->pause();

  //Désactiver le bouton
  Pause->setDisabled(true);

  //Réactiver les boutons
  menuBarQueue->setDisabled(false);
  menuBarClass->setDisabled(false);
  Zoom_in->setDisabled(false);
  Zoom_out->setDisabled(false);
  Resume->setDisabled(false);
  voir_routage->setDisabled(false);

  //Déasctiver certains menus
  ConfigureQueue->setDisabled(true);
  ConfigureClass->setDisabled(true);
  RemoveClass->setDisabled(true);
  RemoveQueue->setDisabled(true);
  //Réafficher le réseau
  afficher_reseau();
}

/**Slot lançant la simulation**/
void FenetreCreation::start()
{
  if(reseau->getNbFiles()>0)
  {
    //Rendre le bouton utilisable
    change_window->setDisabled(false);

    //Demande de la durée de simulation à l'utilisateur
    bool ok;
    int duree = QInputDialog::getInt(this,"Simulation's period","Please enter the simulation's period desired : ",20,20,100,1,&ok);

    if(ok){

      //Active les boutons
      Stop->setDisabled(false);
      Pause->setDisabled(false);

      //Désactiver les autres boutons
      Start->setDisabled(true);
      Reset->setDisabled(true);
      Quit->setDisabled(true);
      menuBarPropreReseau->setDisabled(true);
      menuBarFichier->setDisabled(true);
      menuBarClass->setDisabled(true);
      menuBarQueue->setDisabled(true);
      changeType->setDisabled(true);
      Zoom_in->setDisabled(true);
      Zoom_out->setDisabled(true);
      voir_routage->setDisabled(true);

      //Si le réseau est fermé
      if(reseau->getTypeReseau()==0)
      {
        //Attribuer la durée de simulation
        fenetre_RF->getSimulation().setDureeSimulation(duree);

        //Mettre à jour la fenêtre d'informations du réseau
        fenetre_RF->getFenetreInfosReseau().setInfoNbClientsActuel();
        fenetre_RF->getFenetreInfosReseau().setInfoNbClientsPasses();
        fenetre_RF->getFenetreInfosReseau().setInfoNbClasses();
        fenetre_RF->getFenetreInfosReseau().setInfoNbClientsClasse();
        fenetre_RF->getFenetreInfosReseau().setInfoTypeReseau();

        //Connecte le clic du bouton avec l'affichage de la fenêtre de simulation au-dessus de la fenêtre de création
        connect(change_window,SIGNAL(clicked()),fenetre_RF,SLOT(show()));

        fenetre_RF->afficher_compteur_clients();

        //Fixe la taille de la fenêtre de simulation
        fenetre_RF->setFixedSize(QApplication::desktop()->width(),QApplication::desktop()->height()-70);

        //Demander le nombre de clients à entrer
		    int nbClientsInitial = QInputDialog::getInt(this,"Number of clients for the simulation ","Please enter the number of clients desired for the simulation : ",5,5,100,1,&ok);

        if(ok)
        {
    			//Lancer le chrono pour la simulation
    			fenetre_RF->start_chrono();
    			fenetre_RF->executer_simulation(nbClientsInitial);
    		}

      }
      //Si le réseau est ouvert
      else
      {
        //Attribuer la durée de simulation
        fenetre_RO->getSimulation().setDureeSimulation(duree);

        //Mettre à jour la fenêtre d'informations du réseau
        fenetre_RO->getFenetreInfosReseau().setInfoNbClientsActuel();
        fenetre_RO->getFenetreInfosReseau().setInfoNbClientsPasses();
        fenetre_RO->getFenetreInfosReseau().setInfoNbClasses();
        fenetre_RO->getFenetreInfosReseau().setInfoNbClientsClasse();
        fenetre_RO->getFenetreInfosReseau().setInfoTypeReseau();

        //Connecte le clic du bouton avec l'affichage de la fenêtre de simulation au-dessus de la fenêtre de création
        connect(change_window,SIGNAL(clicked()),fenetre_RO,SLOT(show()));

        fenetre_RO->afficher_compteur_clients();

        //Fixe la taille de la fenêtre de simulation
        fenetre_RO->setFixedSize(QApplication::desktop()->width(),QApplication::desktop()->height()-70);

        //Demander le nombre de clients à entrer
        int nbClientsInitial = QInputDialog::getInt(this,"Number of clients for the simulation","Please enter the number of clients desired for the simulation : ",5,5,100,1,&ok);

        if(ok)
        {
    			//Lancer le chrono pour la simulation
    			fenetre_RO->start_chrono();
    			fenetre_RO->executer_simulation(nbClientsInitial);
    		}
      }
    }
  }

  //Affiche un message d'erreur
  else QMessageBox::warning(this,"", "The network is incomplete");
}

/**Slot arrêtant la simulation**/
void FenetreCreation::stop()
{
  if(reseau->getTypeReseau()==0)
  {
    fenetre_RF->stop();

  }
  else
  {
    fenetre_RO->stop();
  }

  //Désactiver les boutons
  Stop->setDisabled(true);
  Resume->setDisabled(true);
  Pause->setDisabled(true);
  change_window->setDisabled(true);

  //Réactiver les boutons
  Start->setDisabled(false);
  Reset->setDisabled(false);
  Quit->setDisabled(false);
  menuBarPropreReseau->setDisabled(false);
  menuBarFichier->setDisabled(false);
  menuBarQueue->setDisabled(false);
  menuBarClass->setDisabled(false);
  changeType->setDisabled(false);
  Zoom_in->setDisabled(false);
  Zoom_out->setDisabled(false);
  voir_routage->setDisabled(false);
  ConfigureQueue->setDisabled(false);
  ConfigureClass->setDisabled(false);
  RemoveClass->setDisabled(false);
  RemoveQueue->setDisabled(false);
  AddQueue->setDisabled(false);

  int reponse = QMessageBox::question(this, "Save Performances",
    "Do you want saving performances from the network ?", QMessageBox::Yes | QMessageBox::No);

  if (reponse == QMessageBox::Yes)
  {
       QFileDialog * f = new QFileDialog;
       QString fileName = f->getSaveFileName(this,
        tr("Save Performances"), "",
        tr("prf(*.prf);;All Files (*)"));
       string nomfic = fileName.toStdString();
       if(nomfic[nomfic.size()-1]!='f' && nomfic[nomfic.size()-2]!='r'
          && nomfic[nomfic.size()-3]!='p' && nomfic[nomfic.size()-4]!='.')
       {
        nomfic += ".prf";
        }

       if (fileName.isEmpty())
        return;
       else {

        if(reseau->getTypeReseau()==0)
        {
           ecriture_fichier_performancesRF(nomfic,fenetre_RF->getHistorique());//ajouter getHistorique() dans fenetreSimulationRF
        }
        else
        {
          ecriture_fichier_performancesRO(nomfic,fenetre_RO->getHistorique());//ajouter getHistorique() dans fenetreSimulationRO
        }
    }
  }

  int reponse2 = QMessageBox::question(this, "Save Network",
    "Do you want saving your network ?", QMessageBox::Yes | QMessageBox::No);

  if (reponse2 == QMessageBox::Yes)
  {
       QFileDialog * f = new QFileDialog;
       QString fileName = f->getSaveFileName(this,
        tr("Save Performances"), "",
        tr("nt(*.nt)"));
       string nomfic = fileName.toStdString();
       if(nomfic[nomfic.size()-1]!='t'
          && nomfic[nomfic.size()-2]!='n' && nomfic[nomfic.size()-3]!='.')
         nomfic += ".nt";

       if (fileName.isEmpty())
        return;
       else {
        ecriture_fichier_reseau(nomfic,*reseau);
        delete f;
        }
  }

  //Supprimer tous les éléments sur la scène
  scene->clear();

  //Supprimer le réseau
  Reseau * r = reseau;
  delete r;

  //Supprimer les deux fenêtres de simulation
  FenetreSimulationRF * frf = fenetre_RF;
  FenetreSimulationRO * fro = fenetre_RO;
  delete frf;
  delete fro;

  //Créer des objets supprimés
  reseau = new Reseau;
  fenetre_RF = new FenetreSimulationRF(reseau,vue);
  fenetre_RO = new FenetreSimulationRO(reseau,vue);

  //Créer la classe de clients de base
  reseau->ajouter_classe(new ClasseClient(0,20));

  //Augmenter le nombre total de classes dans la simulation
  fenetre_RF->getSimulation().incrementer_nbClassesTot();
  fenetre_RO->getSimulation().incrementer_nbClassesTot();

  //Réafficher le réseau
  afficher_reseau();
}

/**Slot relançant la simulation**/
void FenetreCreation::resume()
{
  if(reseau->getTypeReseau()==0)
  {
    fenetre_RF->resume();
    fenetre_RF->afficher_compteur_clients();
    fenetre_RF->show();
  }
  else
  {
    fenetre_RO->resume();
    fenetre_RO->afficher_compteur_clients();
    fenetre_RO->show();
  }

  //Activer la pause
  Pause->setDisabled(false);

  //Déasctiver les boutons
  menuBarPropreReseau->setDisabled(true);
  menuBarFichier->setDisabled(true);
  menuBarClass->setDisabled(true);
  menuBarQueue->setDisabled(true);
  changeType->setDisabled(true);
  Zoom_in->setDisabled(true);
  Zoom_out->setDisabled(true);
  Resume->setDisabled(true);
  voir_routage->setDisabled(true);
}

/**Slot relançant la simulation après une pause**/
void FenetreCreation::reset()
{
  //Supprimer tous les éléments sur la scène
  scene->clear();

  //Supprimer le réseau
  Reseau * r = reseau;
  delete r;

  //Supprimer les deux fenêtres de simulation
  FenetreSimulationRF * frf = fenetre_RF;
  FenetreSimulationRO * fro = fenetre_RO;
  delete frf;
  delete fro;

  //Créer des objets supprimés
  reseau = new Reseau;
  fenetre_RF = new FenetreSimulationRF(reseau,vue);
  fenetre_RO = new FenetreSimulationRO(reseau,vue);

  //Créer la classe de clients de base
  reseau->ajouter_classe(new ClasseClient(0,20));

  //Augmenter le nombre total de classes dans la simulation
  fenetre_RF->getSimulation().incrementer_nbClassesTot();
  fenetre_RO->getSimulation().incrementer_nbClassesTot();
}

/**Slot zoomant sur la vue**/
void FenetreCreation::zoom_in()
{
  if(taille_zoom < 10)
  {
    vue->scale(1.1,1.1);
    taille_zoom += 1;
  }
}

/**Slot dézoomant sur la vue**/
void FenetreCreation::zoom_out()
{
  if(taille_zoom > -3)
  {
    vue->scale(0.9,0.9);
    taille_zoom -= 1;
  }
}

/**Slot ajoutant une station**/
void FenetreCreation::add_queue()
{
  //Remise à zéro de la position récupérée par le clic de la souris
  vue->remise_a_zero();

  //Remettre la vue à sa taille initiale
  vue->fitInView(0,0,vue->width(),vue->height());

  //Création d'une fenêtre contenant la vue acceptant les clics
  QDialog * fenetre_vue_cliquable = new QDialog;
  QGridLayout * layout_vue = new QGridLayout;

  //Enlever la barre du haut de la fenêtre
  fenetre_vue_cliquable->setWindowFlags(Qt::CustomizeWindowHint);

  //Enlever la marge entre le layout et la fenêtre
  layout_vue->setContentsMargins(0,0,0,0);

  //Modifications de la taille des objets
  fenetre_vue_cliquable->setFixedSize(vue->width(),vue->height());

  //Ajout de la vue à la boîte de rangement de la boîte de dialogue
  layout_vue->addWidget(vue,1,0);

  //Ajout de la boîte de rangement à la fenêtre
  fenetre_vue_cliquable->setLayout(layout_vue);

  //Connecter la récupération du clic à la fermeture de la vue
  connect(vue,SIGNAL(clicked()),fenetre_vue_cliquable,SLOT(accept()));

  //Si la simulation n'est pas en marche
  if((fenetre_RO->getSimulation().getEcheancier().getListeEvenement().empty())&&(fenetre_RF->getSimulation().getEcheancier().getListeEvenement().empty()))
  {
    //Désactiver les autres boutons
     Start->setDisabled(true);
     Reset->setDisabled(true);
     Quit->setDisabled(true);
     menuBarPropreReseau->setDisabled(true);
     menuBarFichier->setDisabled(true);
     menuBarClass->setDisabled(true);
     menuBarQueue->setDisabled(true);
     changeType->setDisabled(true);
     Zoom_in->setDisabled(true);
     Zoom_out->setDisabled(true);
     voir_routage->setDisabled(true);
   }


  //Ajouter la boîte de dialogue dans la fenêtre de création
  layout_principal->addWidget(fenetre_vue_cliquable,1,0,4,5);

  //Tant que l'utilisateur n'a pas cliqué sur la vue
  while((vue->getPosXClic()==0) && (vue->getPosYClic()==0))
  {

    fenetre_vue_cliquable->show();
    QMessageBox::information(this,"", "Please click where you want to place a queue.");
    //Réouvre la fenêtre contenant la vue pour récupérer le clic
    fenetre_vue_cliquable->exec();
  }

  //Si les coordonnées du clic correspondent à une file, à l'entrée ou la sortie
  while(verif_proximite_clic(vue->getPosXClic(), vue->getPosYClic()))
  {
      fenetre_vue_cliquable->show();
      QMessageBox::information(this,"", "Too closed. Please click on a new location.");
      //Réouvre la fenêtre contenant la vue pour récupérer le clic
      fenetre_vue_cliquable->exec();
  }


  //Garder les coordonnées du clic
  int x = vue->getPosXClic(),y = vue->getPosYClic();

  //Créer une file
  File* f = new File(fenetre_RF->getSimulation().getNbFilesTot(),x,y);

  //Créer un serveur
  Serveur * s = new Serveur(fenetre_RF->getSimulation().getNbServeursTot());

  //Ajouter un serveur à cette file
  f->ajouter_serveur(*s);

  //Incrémenter les compteurs pour les identifiants
  fenetre_RF->getSimulation().incrementer_nbFilesTot();
  fenetre_RO->getSimulation().incrementer_nbFilesTot();
  fenetre_RF->getSimulation().incrementer_nbServeursTot();
  fenetre_RO->getSimulation().incrementer_nbServeursTot();

  //Ajouter la file au réseau
  reseau->ajouter_file(f);

  //Mettre à jour l'affichage de la scène
  afficher_reseau();

  //Remettre la vue dans le layout de la fenêtre de création
  layout_principal->addWidget(vue,1,0,4,5);

  //Si la simulation n'est pas en marche
  if((fenetre_RO->getSimulation().getEcheancier().getListeEvenement().empty())&&(fenetre_RF->getSimulation().getEcheancier().getListeEvenement().empty()))
  {
    //Réactiver les boutons cachés
    Start->setDisabled(false);
    Reset->setDisabled(false);
    Quit->setDisabled(false);
    menuBarPropreReseau->setDisabled(false);
    menuBarFichier->setDisabled(false);
    menuBarClass->setDisabled(false);
    menuBarQueue->setDisabled(false);
    changeType->setDisabled(false);
    Zoom_in->setDisabled(false);
    Zoom_out->setDisabled(false);
    voir_routage->setDisabled(false);
  }

  //Suppression des objets alloués dynamiquement
  delete layout_vue;
  delete fenetre_vue_cliquable;
}

/**Slot modifiant la position d'une station**/
void FenetreCreation::move_queue()
{
  if(reseau->getNbFiles()==0)
  {
    QMessageBox::warning(this,"", "There is no queue on this network.");
  }
  else
  {

    //Remettre la vue à sa taille initiale
    vue->fitInView(0,0,vue->width(),vue->height());

    //Remise à zéro de la position récupérée par le clic de la souris
    vue->remise_a_zero();

    File * file_a_modifier = NULL;

    //Utilisé pour donner des nouvelles coordonnées à la file
    coordonnees new_coord;

    //Création d'une fenêtre contenant la vue acceptant les clics
    QDialog * fenetre_vue_cliquable = new QDialog;
    QGridLayout * layout_vue = new QGridLayout;

    //Enlever la barre du haut de la fenêtre
    fenetre_vue_cliquable->setWindowFlags(Qt::CustomizeWindowHint);

    //Enlever la marge entre le layout et la fenêtre
    layout_vue->setContentsMargins(0,0,0,0);

    //Modifications de la taille des objets
    fenetre_vue_cliquable->setFixedSize(vue->width(),vue->height());

    //Ajout de la vue à la boîte de rangement de la boîte de dialogue
    layout_vue->addWidget(vue,1,0);

    //Ajout de la boîte de rangement à la fenêtre
    fenetre_vue_cliquable->setLayout(layout_vue);

    //Connecter la récupération du clic à la fermeture de la vue
    connect(vue,SIGNAL(clicked()),fenetre_vue_cliquable,SLOT(accept()));

    //Si la simulation n'est pas en marche
    if((fenetre_RO->getSimulation().getEcheancier().getListeEvenement().empty())&&(fenetre_RF->getSimulation().getEcheancier().getListeEvenement().empty()))
    {
      //Désactiver les autres boutons
       Start->setDisabled(true);
       Reset->setDisabled(true);
       Quit->setDisabled(true);
       menuBarPropreReseau->setDisabled(true);
       menuBarFichier->setDisabled(true);
       menuBarClass->setDisabled(true);
       menuBarQueue->setDisabled(true);
       changeType->setDisabled(true);
       Zoom_in->setDisabled(true);
       Zoom_out->setDisabled(true);
       voir_routage->setDisabled(true);
    }

    //Ajouter la boîte de dialogue dans la fenêtre de création
    layout_principal->addWidget(fenetre_vue_cliquable,1,0,4,4);

    //Récupérer les coordonnées de la file à déplacer
    fenetre_vue_cliquable->show();
    QMessageBox::information(fenetre_vue_cliquable,"", "Please click on a queue to move it.");
    fenetre_vue_cliquable->exec();

    //Si les coordonnées du clic ne correspondent pas à une file
    while(!verif_pos_clic_file(vue->getPosXClic(), vue->getPosYClic()))
    {
        fenetre_vue_cliquable->show();
        QMessageBox::information(this,"", "No queue chosen. Please click on a queue to move it.");
        //Réouvre la fenêtre contenant la vue pour récupérer le clic
        fenetre_vue_cliquable->exec();
    }

    //Récupérer la file dont il faut modifier les coordonnées
    for(auto it_files = reseau->getListeFile().begin(); it_files != reseau->getListeFile().end(); it_files++){
      if((vue->getPosXClic() < (*it_files)->getCoord().x + LONGUEUR_FILE)
      && (vue->getPosXClic() > (*it_files)->getCoord().x - LONGUEUR_FILE/2)
      && (vue->getPosYClic() < (*it_files)->getCoord().y + LARGEUR_FILE/2)
      && (vue->getPosYClic() > (*it_files)->getCoord().y - LARGEUR_FILE/2))
      {
        file_a_modifier = *it_files;
        break;
      }
    }

    //Récupérer les coordonnées du nouvel emplacement de la file
    fenetre_vue_cliquable->show();
    QMessageBox::information(fenetre_vue_cliquable,"", "Please click on a new location for the queue.");
    fenetre_vue_cliquable->exec();

    if(reseau->getTypeReseau() == 0)
    {
      //Si la nouvelle localisation correspond à une file
      while(verif_pos_clic_file(vue->getPosXClic(), vue->getPosYClic()))
      {
        fenetre_vue_cliquable->show();
        QMessageBox::information(this,"", "No location chosen. Please click on a new location for the queue.");
        //Réouvre la fenêtre contenant la vue pour récupérer le clic
        fenetre_vue_cliquable->exec();
      }
    }
    else
    {
      //Si la nouvelle localisation correspond à une file, à l'entrée ou à la sortie
      while((verif_pos_clic_file(vue->getPosXClic(), vue->getPosYClic()))
      ||(((vue->getPosXClic()> scene->width()-(scene->width()-10)) && (vue->getPosXClic() < scene->width()-(scene->width()-10) + 75))
      &&((vue->getPosYClic()> scene->height()/2) && (vue->getPosYClic() < scene->height()/2 + 25)))
      ||(((vue->getPosXClic()> scene->width()-80) && (vue->getPosXClic() < scene->width()-80 + 75))
      &&((vue->getPosYClic()> scene->height()/2) && (vue->getPosYClic() < scene->height()/2 + 25))))
      {
        fenetre_vue_cliquable->show();
        QMessageBox::information(this,"", "No location chosen. Please click on a new location for the queue.");
        //Réouvre la fenêtre contenant la vue pour récupérer le clic
        fenetre_vue_cliquable->exec();
      }
    }

    //Mettre à jour les coordonnées de la file
    new_coord.x = vue->getPosXClic();
    new_coord.y = vue->getPosYClic();

    file_a_modifier->setCoordonnees(new_coord);

    //Mettre à jour l'affichage du réseau
    afficher_reseau();

    //Remettre la vue dans le layout de la fenêtre de création
    layout_principal->addWidget(vue,1,0,4,5);

    //Si la simulation n'est pas en marche
    if((fenetre_RO->getSimulation().getEcheancier().getListeEvenement().empty())&&(fenetre_RF->getSimulation().getEcheancier().getListeEvenement().empty()))
    {
      //Réactiver les boutons cachés
      Start->setDisabled(false);
      Reset->setDisabled(false);
      Quit->setDisabled(false);
      menuBarPropreReseau->setDisabled(false);
      menuBarFichier->setDisabled(false);
      menuBarClass->setDisabled(false);
      menuBarQueue->setDisabled(false);
      changeType->setDisabled(false);
      Zoom_in->setDisabled(false);
      Zoom_out->setDisabled(false);
      voir_routage->setDisabled(false);
    }

    //Suppression des objets alloués dynamiquement
    delete layout_vue;
    delete fenetre_vue_cliquable;
  }
}

/**Slot supprimant une station**/
void FenetreCreation::remove_queue()
{
  //si 0 stations sont présentes dans le réseau
  if(reseau->getNbFiles()==0){
      QMessageBox::warning(this,"", "There is no queue on this network.");
  }
  else{

    //Remise à zéro de la position récupérée par le clic de la souris
    vue->remise_a_zero();

    //Remettre la vue à sa taille initiale
    vue->fitInView(0,0,vue->width(),vue->height());

    File * file_a_supprimer = NULL;

    //Création d'une fenêtre contenant la vue acceptant les clics
    QDialog * fenetre_vue_cliquable = new QDialog;
    QGridLayout * layout_vue = new QGridLayout;

    //Enlever la barre du haut de la fenêtre
    fenetre_vue_cliquable->setWindowFlags(Qt::CustomizeWindowHint);

    //Enlever la marge entre le layout et la fenêtre
    layout_vue->setContentsMargins(0,0,0,0);

    //Modifications de la taille des objets
    fenetre_vue_cliquable->setFixedSize(vue->width(),vue->height());

    //Ajout de la vue à la boîte de rangement de la boîte de dialogue
    layout_vue->addWidget(vue,1,0);

    //Ajout de la boîte de rangement à la fenêtre
    fenetre_vue_cliquable->setLayout(layout_vue);

    //Connecter la récupération du clic à la fermeture de la vue
    connect(vue,SIGNAL(clicked()),fenetre_vue_cliquable,SLOT(accept()));

    //Si la simulation n'est pas en marche
    if((fenetre_RO->getSimulation().getEcheancier().getListeEvenement().empty())&&(fenetre_RF->getSimulation().getEcheancier().getListeEvenement().empty()))
    {
      //Désactiver les autres boutons
       Pause->setDisabled(true);
       Resume->setDisabled(true);
       Start->setDisabled(true);
       Stop->setDisabled(true);
       Reset->setDisabled(true);
       Quit->setDisabled(true);
       menuBarPropreReseau->setDisabled(true);
       menuBarFichier->setDisabled(true);
       menuBarClass->setDisabled(true);
       menuBarQueue->setDisabled(true);
       changeType->setDisabled(true);
       Zoom_in->setDisabled(true);
       Zoom_out->setDisabled(true);
       voir_routage->setDisabled(true);
     }


    //Ajouter la boîte de dialogue dans la fenêtre de création
    layout_principal->addWidget(fenetre_vue_cliquable,1,0,4,5);

    //Récupérer les coordonnées de la file à déplacer
    fenetre_vue_cliquable->show();
    QMessageBox::information(fenetre_vue_cliquable,"", "Please click on a queue to remove it.");
    fenetre_vue_cliquable->exec();

      //Si les coordonnées du clic ne correspondent pas à une file
      while(!verif_pos_clic_file(vue->getPosXClic(), vue->getPosYClic()))
      {
          fenetre_vue_cliquable->show();
          QMessageBox::information(this,"", "No queue chosen. Please click on a queue to remove it.");
          //Réouvre la fenêtre contenant la vue pour récupérer le clic
          fenetre_vue_cliquable->exec();
      }

    //Récupérer la file dont il faut modifier les coordonnées
    for(auto it_files = reseau->getListeFile().begin(); it_files != reseau->getListeFile().end(); it_files++){
      if((vue->getPosXClic() < (*it_files)->getCoord().x + LONGUEUR_FILE)
      && (vue->getPosXClic() > (*it_files)->getCoord().x - LONGUEUR_FILE/2)
      && (vue->getPosYClic() < (*it_files)->getCoord().y + LARGEUR_FILE/2)
      && (vue->getPosYClic() > (*it_files)->getCoord().y - LARGEUR_FILE/2))
      {
        file_a_supprimer = *it_files;
        break;
      }
    }

    //Supprimer les événements de la file dans l'échéancier
    if(reseau->getTypeReseau()==0)
      fenetre_RF->getSimulation().getEcheancier().supprimer_evenement_file(file_a_supprimer->getIDFile());
    else
      fenetre_RO->getSimulation().getEcheancier().supprimer_evenement_file(file_a_supprimer->getIDFile());

    //Supprimer la file du routage
    for(auto i = reseau->getListeClasseClient().begin();i!= reseau->getListeClasseClient().end();i++)
    {
      (*i)->supprimer_file_routage(file_a_supprimer->getIDFile());
    }

    //Retirer la file du réseau
    reseau->supprimer_file(file_a_supprimer->getIDFile());

    //Mettre à jour l'affichage du réseau
    afficher_reseau();

    //Remettre la vue dans le layout de la fenêtre de création
    layout_principal->addWidget(vue,1,0,4,5);

    //Si la simulation n'est pas en marche
    if((fenetre_RO->getSimulation().getEcheancier().getListeEvenement().empty())&&(fenetre_RF->getSimulation().getEcheancier().getListeEvenement().empty()))
    {
      //Réactiver les boutons cachés
      Start->setDisabled(false);
      Reset->setDisabled(false);
      Quit->setDisabled(false);
      menuBarPropreReseau->setDisabled(false);
      menuBarFichier->setDisabled(false);
      menuBarClass->setDisabled(false);
      menuBarQueue->setDisabled(false);
      changeType->setDisabled(false);
      Zoom_in->setDisabled(false);
      Zoom_out->setDisabled(false);
      voir_routage->setDisabled(false);
    }

    //Suppression des objets alloués dynamiquement
    delete layout_vue;
    delete fenetre_vue_cliquable;
  }
}

/**Slot configurant une station**/
void FenetreCreation::configure_queue()
{
  if(reseau->getNbFiles()==0)
  {
    QMessageBox::warning(this,"", "There is no queue on this network.");
  }
  else
  {

    //Remettre la vue à sa taille initiale
    vue->fitInView(0,0,vue->width(),vue->height());

    //Remise à zéro de la position récupérée par le clic de la souris
    vue->remise_a_zero();

    //Itérateur sur la liste de files
    list<File*>:: iterator it_files;

    //Résultat de la fermeture de la fenêtre
    bool res_clic;

    //Création d'une fenêtre contenant la vue acceptant les clics
    QDialog * fenetre_vue_cliquable = new QDialog;
    QGridLayout * layout_vue = new QGridLayout;

    //Enlever la barre du haut de la fenêtre
    fenetre_vue_cliquable->setWindowFlags(Qt::CustomizeWindowHint);

    //Enlever la marge entre le layout et la fenêtre
    layout_vue->setContentsMargins(0,0,0,0);

    //Modifications de la taille des objets
    fenetre_vue_cliquable->setFixedSize(vue->width(),vue->height());

    //Ajout de la vue à la boîte de rangement de la boîte de dialogue
    layout_vue->addWidget(vue,1,0);

    //Ajout de la boîte de rangement à la fenêtre
    fenetre_vue_cliquable->setLayout(layout_vue);

    //Connecter la récupération du clic à la fermeture de la vue
    connect(vue,SIGNAL(clicked()),fenetre_vue_cliquable,SLOT(accept()));

    //Si la simulation n'est pas en marche
    if((fenetre_RO->getSimulation().getEcheancier().getListeEvenement().empty())&&(fenetre_RF->getSimulation().getEcheancier().getListeEvenement().empty()))
    {
      //Désactiver les autres boutons
       Start->setDisabled(true);
       Reset->setDisabled(true);
       Quit->setDisabled(true);
       menuBarPropreReseau->setDisabled(true);
       menuBarFichier->setDisabled(true);
       menuBarClass->setDisabled(true);
       menuBarQueue->setDisabled(true);
       changeType->setDisabled(true);
       Zoom_in->setDisabled(true);
       Zoom_out->setDisabled(true);
       voir_routage->setDisabled(true);
    }


    //Ajouter la boîte de dialogue dans la fenêtre de création
    layout_principal->addWidget(fenetre_vue_cliquable,1,0,4,5);

    fenetre_vue_cliquable->show();
    QMessageBox::information(this,"", "Please click on a queue to configure it.");
    fenetre_vue_cliquable->exec();

    //Tant que l'utilisateur n'a pas cliqué sur une file
    while(!verif_pos_clic_file(vue->getPosXClic(), vue->getPosYClic()))
    {
      fenetre_vue_cliquable->show();
      QMessageBox::information(this,"", "No queue chosen. Please click on a queue to configure it.");
      //Réouvre la fenêtre contenant la vue pour récupérer le clic
      fenetre_vue_cliquable->exec();
    }

    //ICI chercher la file correspondante dans le réseau
    for(it_files = reseau->getListeFile().begin(); it_files != reseau->getListeFile().end(); it_files++)
    {
      if((vue->getPosXClic() < (*it_files)->getCoord().x + LONGUEUR_FILE)
      && (vue->getPosXClic() > (*it_files)->getCoord().x - LONGUEUR_FILE/2)
      && (vue->getPosYClic() < (*it_files)->getCoord().y + LARGEUR_FILE/2)
      && (vue->getPosYClic() > (*it_files)->getCoord().y - LARGEUR_FILE/2))
      {
        break;
      }
    }

     //Remettre la vue dans le layout de la fenêtre de création
     layout_principal->addWidget(vue,1,0,4,5);

     //Si la simulation n'est pas en marche
     if((fenetre_RO->getSimulation().getEcheancier().getListeEvenement().empty())&&(fenetre_RF->getSimulation().getEcheancier().getListeEvenement().empty()))
     {
       //Réactiver les boutons cachés
       Start->setDisabled(false);
       Reset->setDisabled(false);
       Quit->setDisabled(false);
       menuBarPropreReseau->setDisabled(false);
       menuBarFichier->setDisabled(false);
       menuBarClass->setDisabled(false);
       menuBarQueue->setDisabled(false);
       changeType->setDisabled(false);
       Zoom_in->setDisabled(false);
       Zoom_out->setDisabled(false);
       voir_routage->setDisabled(false);
     }

    //Création de la boîte de dialogue permettant de paramétrer la file en question
    DialogConfigFile * bcf = new DialogConfigFile(*it_files);

    //Rendre modale la fenêtre
    bcf->setModal(true);

    //Mettre la fenêtre à droite de la file
    bcf->move((*it_files)->getCoord().x + 180,(*it_files)->getCoord().y - 100);

    //Ouverture de la boître
    res_clic = bcf->exec();

    //Si l'utilisateur a cliqué sur le bouton OK
    if(res_clic == 1)
    {

      //Modification de la taille maximale de la file dans la file en question
      (*it_files)->setTailleMax (bcf->recuperer_valeur_newTailleMax());

      //Modification de l'ordonnancement de la file dans la file en question
      if(bcf->recuperer_valeur_newOrdonnancement()=="FIFO")
      {
        (*it_files)->setOrdonnancement(1);
      }
      else if(bcf->recuperer_valeur_newOrdonnancement()=="LIFO")
      {
        (*it_files)->setOrdonnancement(2);
      }
      else if(bcf->recuperer_valeur_newOrdonnancement()=="Priority")
      {
        (*it_files)->setOrdonnancement(3);
      }
      else if(bcf->recuperer_valeur_newOrdonnancement()=="Random")
      {
        (*it_files)->setOrdonnancement(4);
      }
      //Modification de la loi de service de la file dans la file en question
      if(bcf->recuperer_valeur_newLoiService()=="Exponential")
      {
        (*it_files)->setLoiService(-1);
      }
      else if(bcf->recuperer_valeur_newLoiService()=="Uniform")
      {
        (*it_files)->setLoiService(-2);
      }
      else if(bcf->recuperer_valeur_newLoiService()=="Constant")
      {

        //Création d'une boîte de dialogue demande le temps de service que souhaite l'utilisateur
        bool ok;
        int tps_service = QInputDialog::getInt(this,"Service Time", "Choose the desired service time :",1,1,15,1,&ok);

        //Si l'utilisateur a cliqué sur le bouton OK, affecte la valeur entrée par l'utilisateur
        if(ok)(*it_files)->setLoiService(tps_service);
        //Sinon donne une valeur par défaut
        else (*it_files)->setLoiService(5);

      }
      //Modification de la distribution d'arrivée de la file en question
      if(bcf->recuperer_valeur_newLoiArrivee()=="Poisson")
      {
        (*it_files)->setDistribution(-1);
      }
      else if(bcf->recuperer_valeur_newLoiArrivee()=="Constant")
      {
        //Création de la boîte de dialogue demandant le nombre d'arrivées moyen dans la file
        bool ok;
        int nbArrivees = QInputDialog::getInt(this,"Arrivals", "Choose the number of arrivals desired : ",1,1,20,1,&ok);

        //Si l'utilisateur a cliqué sur le bouton OK, affecte la valeur entrée par l'utilisateur
        if(ok) (*it_files)->setDistribution(nbArrivees);
        //Sinon donne une valeur par défaut
        else (*it_files)->setDistribution(5);
      }

      //Modifications du nombre de serveurs
      //Si le nombre entré par l'utilisateur est différent de celui actuel
      if((int)(*it_files)->getListeServeur().size() != bcf->recuperer_valeur_newNbServeurs())
      {
        //Si le nombre entré par l'utilisateur est supérieur à celui actuel
        if((int)(*it_files)->getListeServeur().size() < bcf->recuperer_valeur_newNbServeurs())
        {
          //Calcul du nombre de serveurs à ajouter
          int nb_serveurs_a_ajouter = bcf->recuperer_valeur_newNbServeurs()-(int)(*it_files)->getListeServeur().size();

          //Tant que le nombre de serveurs à ajouter n'a pas été atteint
          while(nb_serveurs_a_ajouter > 0)
          {
              //Concaténation du numéro de la file avec le nombre de serveurs actuel pour créer un nouvel ID
              (*it_files)->ajouter_serveur(*new Serveur(fenetre_RF->getSimulation().getNbServeursTot()));
              fenetre_RF->getSimulation().incrementer_nbServeursTot();
              fenetre_RO->getSimulation().incrementer_nbServeursTot();

              nb_serveurs_a_ajouter --;
          }
        }
        //Si le nombre entré par l'utilisateur est inférieur à celui actuel
        else if((int)(*it_files)->getListeServeur().size() > bcf->recuperer_valeur_newNbServeurs())
        {
          //Calcul du nombre de serveurs à supprimer
          int nb_serveurs_a_supprimer = (int)(*it_files)->getListeServeur().size() - bcf->recuperer_valeur_newNbServeurs();

          //Tant que le nombre de serveurs à supprimer n'est pas atteint
          while(nb_serveurs_a_supprimer > 0)
          {
              //Supprime le dernier serveur de la liste
              (*it_files)->supprimer_serveur((*it_files)->getListeServeur().back()->getIDServeur());
              nb_serveurs_a_supprimer --;
          }
        }
      }
      delete bcf;
    }

    //Remettre la vue dans le layout de la fenêtre de création
    layout_principal->addWidget(vue,1,0,4,5);

    //Si la simulation n'est pas en marche
    if((fenetre_RO->getSimulation().getEcheancier().getListeEvenement().empty())&&(fenetre_RF->getSimulation().getEcheancier().getListeEvenement().empty()))
    {
      //Réactiver les boutons cachés
      Start->setDisabled(false);
      Reset->setDisabled(false);
      Quit->setDisabled(false);
      menuBarPropreReseau->setDisabled(false);
      menuBarFichier->setDisabled(false);
      menuBarClass->setDisabled(false);
      menuBarQueue->setDisabled(false);
      changeType->setDisabled(false);
      Zoom_in->setDisabled(false);
      Zoom_out->setDisabled(false);
      voir_routage->setDisabled(false);
    }

    //Suppression des objets alloués dynamiquement
    delete layout_vue;
    delete fenetre_vue_cliquable;
  }
}

/**Slot ajoutant une classe de clients**/
void FenetreCreation::add_class()
{
  //Ajout d'un classe si il est possible de définir un routage (2 files minimum)
  if(reseau->getNbFiles() >= 1)
  {
    //Crée la fenêtre de configuration de la nouvelle classe
    DialogAddClass * dac = new DialogAddClass;

    //Placer la boîte au centre de la fenêtre de création
    dac->move(width()/2-100,height()/2-100);

    //Si la simulation n'est pas en marche
    if((fenetre_RO->getSimulation().getEcheancier().getListeEvenement().empty())&&(fenetre_RF->getSimulation().getEcheancier().getListeEvenement().empty()))
    {
      //Désactiver les autres boutons
       Start->setDisabled(true);
       Reset->setDisabled(true);
       Quit->setDisabled(true);
       menuBarPropreReseau->setDisabled(true);
       menuBarFichier->setDisabled(true);
       menuBarClass->setDisabled(true);
       menuBarQueue->setDisabled(true);
       changeType->setDisabled(true);
       Zoom_in->setDisabled(true);
       Zoom_out->setDisabled(true);
       voir_routage->setDisabled(true);
     }

    //Mise en forme de l'expression régulière de la chaîne
    //std::regex er("([[:digit:]].*)((\\-)[[:digit:]]).*");
    std::regex er("([[:digit:]]+)((\\-)[[:digit:]]+).*");

    QMessageBox::information(this,"Information", "Configure the class.");

    //Ouvre la boîte de dialogue pour configurer la classe
    dac->exec();

    //Récupère le routage
    string routage = dac->getRoutage();

    //Tester si la chaîne rentrée par l'utilisateur correspond à l'expression régulière
    while(!(std::regex_match (routage,er))){
        QMessageBox::warning(this,"Warning", "Invalid routing");
        //Ouvre la boîte de dialogue pour configurer la classe
        dac->exec();
        routage = dac->getRoutage();
    }

    //Vérifier que les chiffres/nombres correspondent à des files
    int j = 0;
    string tmp = "";
    int valide = 0;
    int correspondance_file = 0;

    //Pacourir la chaîne récupérée
    while(valide == 0)
    {
      //Récupérer un nombre/chiffre
      while((routage[j] != '-')&&(j < (int)routage.length()))
      {
        tmp += routage[j];
        j++;
      }

      //Signifie que le parcours de la chaîne n'est pas fini et que le caractère - a été croisé
      if(j < (int)routage.length()) j++;



      //Vérifier que cela correspond à une file
      for(auto file : reseau->getListeFile())
      {
        if(tmp.compare(to_string(file->getIDFile()))==0)
        {
          correspondance_file = 1;
          break;
        }
      }

      //Fin de la chaîne atteinte et correspondance du nombre/chiffre avec une file
       if((j == (int)routage.length())&&(correspondance_file == 1))
       {
         valide = 1;
       }

      //Demander à nouveau àl'utilisateur d'entrer un routage
      if(correspondance_file == 0)
      {
        QMessageBox::warning(this,"Warning", "Invalid routing");

        //Ouvre la boîte de dialogue pour configurer la classe
        dac->exec();

        //Récupérer la chaîne correspondant au routage
        routage = dac->getRoutage();

        //Tester si la chaîne rentrée par l'utilisateur correspond à l'expression régulière
        while(!(std::regex_match (routage,er))){
            QMessageBox::warning(this,"Warning", "Invalid routing");
            //Ouvre la boîte de dialogue pour configurer la classe
            dac->exec();
            routage = dac->getRoutage();
        }

        j = 0;
      }
      //Prouver que le nombre testé correspond à une file
      else correspondance_file = 0;

      tmp = "";
    }

    //Crée la classe à ajouter au réseau
    ClasseClient * ClassA = new ClasseClient(fenetre_RF->getSimulation().getNbClassesTot(),dac->getPriorite());
    //Défini le routage de la classe
    ClassA->definir_routage(dac->getRoutage());

    //Ajout de la classe au réseau
    reseau->ajouter_classe(ClassA);

    //Augmente le nombre total de classes dans la simulation
    fenetre_RF->getSimulation().incrementer_nbClassesTot();
    fenetre_RO->getSimulation().incrementer_nbClassesTot();


    //Afficher le réseau
    afficher_reseau();

    //Si la simulation n'est pas en marche
    if((fenetre_RO->getSimulation().getEcheancier().getListeEvenement().empty())&&(fenetre_RF->getSimulation().getEcheancier().getListeEvenement().empty()))
    {
      //Réactiver les boutons cachés
      Start->setDisabled(false);
      Reset->setDisabled(false);
      Quit->setDisabled(false);
      menuBarPropreReseau->setDisabled(false);
      menuBarFichier->setDisabled(false);
      menuBarClass->setDisabled(false);
      menuBarQueue->setDisabled(false);
      changeType->setDisabled(false);
      Zoom_in->setDisabled(false);
      Zoom_out->setDisabled(false);
      voir_routage->setDisabled(false);
    }

    delete dac;
  }
  else QMessageBox::warning(this,"Attention", "Not enough queues.");
}

/**Slot supprimeant une classe de client**/
void FenetreCreation::supp_class()
{
  if(reseau->getNbClasses()<2)
  {
    QMessageBox::information(this,"Warning", "No classes to delete");
  }
  else
  {
    if((!fenetre_RO->isVisible())&&(!fenetre_RF->isVisible()))
    {
      //Désactiver les autres boutons
       Start->setDisabled(true);
       Stop->setDisabled(true);
       Quit->setDisabled(true);
       menuBarPropreReseau->setDisabled(true);
       menuBarFichier->setDisabled(true);
       menuBarClass->setDisabled(true);
       menuBarQueue->setDisabled(true);
       changeType->setDisabled(true);
       Zoom_in->setDisabled(true);
       Zoom_out->setDisabled(true);
       voir_routage->setDisabled(true);
     }

     //Créer et remplir la liste des identifiants de classes
     QStringList * list_ID = new QStringList;
     QString * id_classe = new QString;

     for(auto classe : reseau->getListeClasseClient())
     {
       if(classe->getIDClasseClient() != 0)
       {
         id_classe->setNum(classe->getIDClasseClient());
         *list_ID << *id_classe;
       }
     }

    //Récupère l'identifiant de la classe à supprimer
    bool ok;

    *id_classe = QInputDialog::getItem(this, "ClassID", "Choose the ID of a class : ",*list_ID,0,true,&ok);

    if(ok){
      //Récupère l'identifiant sous forme d'entier
      int ID = id_classe->toInt();

      //Supprime les clients appartenant à cette classe

      //Supprimer les évènements correspondant aux clients supprimés
      if(reseau->getTypeReseau() == 0)
      {
        //Parcourir la liste des évènements et supprimer les évènements
        //correspondant à un client ayant une classe avec l'identifiant ID
        list<Evenement>::iterator event = fenetre_RF->getSimulation().getEcheancier().getListeEvenement().begin();

        while(event != fenetre_RF->getSimulation().getEcheancier().getListeEvenement().end())
        {
          if((*event).client->getClasse()->getIDClasseClient()==ID)
          {
            event = fenetre_RF->getSimulation().getEcheancier().getListeEvenement().erase(event);
          }
          else event ++;
        }
      }
      else{
        //Parcourir la liste des évènements et supprimer les évènements
        //correspondant à un client ayant une classe avec l'identifiant ID
        list<Evenement>::iterator event = fenetre_RO->getSimulation().getEcheancier().getListeEvenement().begin();

        while(event != fenetre_RO->getSimulation().getEcheancier().getListeEvenement().end())
        {
          if((*event).client->getClasse()->getIDClasseClient()==ID)
          {
            event = fenetre_RO->getSimulation().getEcheancier().getListeEvenement().erase(event);
          }
          else event ++;
        }

      }

      list <Client *>::iterator client;

      //Vérifie chaque file
      for(auto file : reseau->getListeFile())
      {
        //Supprime tous les objets Client dont l'identifiant de la classe est égale à ID
        client = file->getListeClients().begin();

      	while(client != file->getListeClients().end())
      	{
      		delete *client;
      		client = file->getListeClients().erase(client);
          //Mettre à jour le nombre de clients dans le réseau
          reseau->setNbClients(reseau->getNbClients()-1);
      	}
      }


      //Supprime la classe du réseau
      reseau->supprimer_classe(ID);
    }

    //Si la simulation n'est pas en marche
    if((fenetre_RO->getSimulation().getEcheancier().getListeEvenement().empty())&&(fenetre_RF->getSimulation().getEcheancier().getListeEvenement().empty()))
    {
      //Réactiver les boutons cachés
      Start->setDisabled(false);
      Reset->setDisabled(false);
      Quit->setDisabled(false);
      menuBarPropreReseau->setDisabled(false);
      menuBarFichier->setDisabled(false);
      menuBarClass->setDisabled(false);
      menuBarQueue->setDisabled(false);
      changeType->setDisabled(false);
      Zoom_in->setDisabled(false);
      Zoom_out->setDisabled(false);
      voir_routage->setDisabled(false);
    }

    //Afficher le réseau
    afficher_reseau();

    delete id_classe;
    delete list_ID;
  }
}

/**Slot configurant une classe de clients**/
void FenetreCreation::configurer_classes()
{
  if(reseau->getNbClasses() < 2)
  {
    QMessageBox::warning(NULL,"Attention", "No classes to configure.");
  }
  else
  {
    //Si la simulation n'est pas en marche
    if((fenetre_RO->getSimulation().getEcheancier().getListeEvenement().empty())&&(fenetre_RF->getSimulation().getEcheancier().getListeEvenement().empty()))
    {
      //Désactiver les autres boutons
       Start->setDisabled(true);
       Reset->setDisabled(true);
       Quit->setDisabled(true);
       menuBarPropreReseau->setDisabled(true);
       menuBarFichier->setDisabled(true);
       menuBarClass->setDisabled(true);
       menuBarQueue->setDisabled(true);
       changeType->setDisabled(true);
       Zoom_in->setDisabled(true);
       Zoom_out->setDisabled(true);
       voir_routage->setDisabled(true);
     }

    //Crée la boîte de dialogue de configuration d'une classe
    DialogConfigClass *dcc;

    //Utilisé pour récupérer la classe
    ClasseClient * classe_a_config = NULL;

    //Utilisé pour savoir si l'utilisateur a cliqué sur ok
    bool ok;

    //Mise en forme de l'expression régulière de la chaîne
    //std::regex er("([[:digit:]].+)((\\-)[[:digit:]]).*");
    std::regex er("([[:digit:]]+)((\\-)[[:digit:]]+).*");

    //Demande de l'identifiant de la classe à modifier

    //Créer et remplir la liste des identifiants de classes
    QStringList * list_ID = new QStringList;
    QString * id_classe = new QString;

    for(auto classe : reseau->getListeClasseClient())
    {
      if(classe->getIDClasseClient() != 0)
      {
        id_classe->setNum(classe->getIDClasseClient());
        *list_ID << *id_classe;
      }
    }

    //Récupère l'identifiant de la classe à configurer
    *id_classe = QInputDialog::getItem(this, "ClassID", "Choose the ID of a class : ",*list_ID,0,true,&ok);

    if(ok){
      //Récupère l'identifiant sous forme d'entier
      int ID = id_classe->toInt();

      //Recherche de la classe correspondant à l'identifiant
      for(auto it = reseau->getListeClasseClient().begin(); it != reseau->getListeClasseClient().end(); it++)
      {
        if((*it)->getIDClasseClient() == ID)
        {
          classe_a_config = (*it);
          break;
        }
      }

      //Ouvre la boîte de configuration de la file
      dcc = new DialogConfigClass(classe_a_config);
      //Placer la boîte de configuration au milieu de la fenêtre
      dcc->move(width()/2-100,height()/2-100);

      bool clic = dcc->exec();

      if(clic == 1)
      {
        //Récupère le routage
        string routage = dcc->getRoutage();

        //Tester si la chaîne rentrée par l'utilisateur correspond à l'expression régulière
        while(!(std::regex_match (routage,er))){
            QMessageBox::warning(this,"Warning", "Invalid routing");
            //Ouvre la boîte de dialogue pour configurer la classe
            dcc->exec();
            routage = dcc->getRoutage();
        }

        //Vérifier que les chiffres/nombres correspondent à des files
        int j = 0;
        string tmp = "";
        int valide = 0;
        int correspondance_file = 0;

        //Pacourir la chaîne récupérée
        while(valide == 0)
        {
          //Récupérer un nombre/chiffre
          while((routage[j] != '-')&&(j < (int)routage.length()))
          {
            tmp += routage[j];
            j++;
          }

          //Signifie que le parcours de la chaîne n'est pas fini et que le caractère - a été croisé
          if(j < (int)routage.length()) j++;

          //Vérifier que cela correspond à une file
          for(auto file : reseau->getListeFile())
          {
            if(tmp.compare(to_string(file->getIDFile()))==0)
            {
              correspondance_file = 1;
              break;
            }
          }

          //Fin de la chaîne atteinte et correspondance du nombre/chiffre avec une file
           if((j == (int)routage.length())&&(correspondance_file == 1)) valide = 1;

          //Demander à nouveau àl'utilisateur d'entrer un routage
          if(correspondance_file == 0)
          {
            QMessageBox::warning(this,"Warning", "Invalid routing");

            //Ouvre la boîte de dialogue pour configurer la classe
            dcc->exec();

            //Récupérer la chaîne correspondant au routage
            routage = dcc->getRoutage();

            //Tester si la chaîne rentrée par l'utilisateur correspond à l'expression régulière
            while(!(std::regex_match (routage,er))){
                QMessageBox::warning(this,"Warning", "Invalid routing");
                //Ouvre la boîte de dialogue pour configurer la classe
                dcc->exec();
                routage = dcc->getRoutage();
            }

            j = 0;
          }
          //Prouver que le nombre testé correspond à une file
          else correspondance_file = 0;

          tmp = "";
        }

        //Modifier les caractéristiques de la classe avec ceux récupérés
        classe_a_config->setPriorite(dcc->getPriorite());
        classe_a_config->definir_routage(dcc->getRoutage());
      }

      delete dcc;
    }

    //Afficher le réseau
    afficher_reseau();

    //Si la simulation n'est pas en marche
    if((fenetre_RO->getSimulation().getEcheancier().getListeEvenement().empty())&&(fenetre_RF->getSimulation().getEcheancier().getListeEvenement().empty()))
    {
      //Réactiver les boutons cachés
      Start->setDisabled(false);
      Reset->setDisabled(false);
      Quit->setDisabled(false);
      menuBarPropreReseau->setDisabled(false);
      menuBarFichier->setDisabled(false);
      menuBarClass->setDisabled(false);
      menuBarQueue->setDisabled(false);
      changeType->setDisabled(false);
      Zoom_in->setDisabled(false);
      Zoom_out->setDisabled(false);
      voir_routage->setDisabled(false);
    }

    delete list_ID;
    delete id_classe;
  }
}

/**Slot chargeant un réseau à partir d'un fichier**/
void FenetreCreation::open()
{
  QFileDialog * f = new QFileDialog;
    QString fileName = f->getOpenFileName(this,
        tr("Open Network File"), "",
        tr("Network File (*.nt)"));


    if (fileName.isEmpty())
        return;
    else {
          reset();
          //reseau = new Reseau;
		      string nom_fic = fileName.toStdString();
          lecture_fichier_reseau(reseau,nom_fic);
           int dernier_id = reseau->getListeFile().back()->getIDFile();//penser également à ajouter les serveurs
          for(int i=0;i<=dernier_id;i++){
               //Incrémenter les compteurs pour les identifiants
              fenetre_RF->getSimulation().incrementer_nbFilesTot();
              fenetre_RO->getSimulation().incrementer_nbFilesTot();
              fenetre_RF->getSimulation().incrementer_nbServeursTot();
              fenetre_RO->getSimulation().incrementer_nbServeursTot();
          }
          int dernier_id_classe = reseau->getListeClasseClient().back()->getIDClasseClient();
          for(int i=0;i<dernier_id_classe;i++){
               //Incrémenter les compteurs pour les identifiants
              fenetre_RF->getSimulation().incrementer_nbClassesTot();
              fenetre_RO->getSimulation().incrementer_nbClassesTot();
          }

        afficher_reseau();
    }

}


/**Slot sauvegardant un réseau dans un fichier**/
void FenetreCreation::save()
{
	QFileDialog * f = new QFileDialog;
    QString fileName = f->getSaveFileName(this,
        tr("Save File Network"), "",
        tr("Network File (*.nt);;All Files ()"));

    string nom_fic = fileName.toStdString();

	if((nom_fic[nom_fic.size()-1] != 't')&&(nom_fic[nom_fic.size()-2] !='n')&&(nom_fic[nom_fic.size()-3] !='.'))
	     nom_fic+= ".nt";

  if (fileName.isEmpty())
        return;
  else
	   ecriture_fichier_reseau(nom_fic,*reseau);
}

/**Slot fermant l'application**/
void FenetreCreation::quitter()
{
  if(reseau->getTypeReseau()==0) fenetre_RF->close();
  else fenetre_RO->close();
  this->close();
}

/**Slot changeant le type du réseau**/
void FenetreCreation::changer_type_reseau()
{
  if(reseau->getTypeReseau()==0) reseau->setTypeReseau(1);
  else reseau->setTypeReseau(0);

  afficher_reseau();
}

/**Slots chargeant un réseau déjà défini**/
void FenetreCreation::charger_reseau1()
{
  //Effacer l'ancien réseau
  reset();

  lecture_fichier_reseau(reseau,".reseau1.nt");
   int dernier_id = reseau->getListeFile().back()->getIDFile();//penser également à ajouter les serveurs
  for(int i=0;i<=dernier_id;i++){
       //Incrémenter les compteurs pour les identifiants
      fenetre_RF->getSimulation().incrementer_nbFilesTot();
      fenetre_RO->getSimulation().incrementer_nbFilesTot();
      fenetre_RF->getSimulation().incrementer_nbServeursTot();
      fenetre_RO->getSimulation().incrementer_nbServeursTot();
  }
  int dernier_id_classe = reseau->getListeClasseClient().back()->getIDClasseClient();
  for(int i=0;i<dernier_id_classe;i++){
       //Incrémenter les compteurs pour les identifiants
      fenetre_RF->getSimulation().incrementer_nbClassesTot();
      fenetre_RO->getSimulation().incrementer_nbClassesTot();
  }

  afficher_reseau();
}

void FenetreCreation::charger_reseau2()
{
  //Effacer l'ancien réseau
  reset();

  lecture_fichier_reseau(reseau,".reseau2.nt");
   int dernier_id = reseau->getListeFile().back()->getIDFile();//penser également à ajouter les serveurs
  for(int i=0;i<=dernier_id;i++){
       //Incrémenter les compteurs pour les identifiants
      fenetre_RF->getSimulation().incrementer_nbFilesTot();
      fenetre_RO->getSimulation().incrementer_nbFilesTot();
      fenetre_RF->getSimulation().incrementer_nbServeursTot();
      fenetre_RO->getSimulation().incrementer_nbServeursTot();
  }
  int dernier_id_classe = reseau->getListeClasseClient().back()->getIDClasseClient();
  for(int i=0;i<dernier_id_classe;i++){
       //Incrémenter les compteurs pour les identifiants
      fenetre_RF->getSimulation().incrementer_nbClassesTot();
      fenetre_RO->getSimulation().incrementer_nbClassesTot();
  }

  afficher_reseau();
}

void FenetreCreation::charger_reseau3()
{
  //Effacer l'ancien réseau
  reset();

  lecture_fichier_reseau(reseau,".reseau3.nt");
   int dernier_id = reseau->getListeFile().back()->getIDFile();//penser également à ajouter les serveurs
  for(int i=0;i<=dernier_id;i++){
       //Incrémenter les compteurs pour les identifiants
      fenetre_RF->getSimulation().incrementer_nbFilesTot();
      fenetre_RO->getSimulation().incrementer_nbFilesTot();
      fenetre_RF->getSimulation().incrementer_nbServeursTot();
      fenetre_RO->getSimulation().incrementer_nbServeursTot();
  }
  int dernier_id_classe = reseau->getListeClasseClient().back()->getIDClasseClient();
  for(int i=0;i<dernier_id_classe;i++){
       //Incrémenter les compteurs pour les identifiants
      fenetre_RF->getSimulation().incrementer_nbClassesTot();
      fenetre_RO->getSimulation().incrementer_nbClassesTot();
  }

  afficher_reseau();
}

void FenetreCreation::charger_reseau4()
{
  //Effacer l'ancien réseau
  reset();

  lecture_fichier_reseau(reseau,".reseau4.nt");
   int dernier_id = reseau->getListeFile().back()->getIDFile();//penser également à ajouter les serveurs
  for(int i=0;i<=dernier_id;i++){
       //Incrémenter les compteurs pour les identifiants
      fenetre_RF->getSimulation().incrementer_nbFilesTot();
      fenetre_RO->getSimulation().incrementer_nbFilesTot();
      fenetre_RF->getSimulation().incrementer_nbServeursTot();
      fenetre_RO->getSimulation().incrementer_nbServeursTot();
  }
  int dernier_id_classe = reseau->getListeClasseClient().back()->getIDClasseClient();
  for(int i=0;i<dernier_id_classe;i++){
       //Incrémenter les compteurs pour les identifiants
      fenetre_RF->getSimulation().incrementer_nbClassesTot();
      fenetre_RO->getSimulation().incrementer_nbClassesTot();
  }

  afficher_reseau();
}

/**Slot affichant le routage d'une classe**/
void FenetreCreation::aff_routage_classe()
{
  if(reseau->getNbClasses()>1){
    //Récupère la classe à afficher
    ClasseClient * classe_a_afficher = NULL;

    //Utilisé pour savoir si l'utilisateur a cliqué sur ok
    bool ok;

    //Créer et remplir la liste des identifiants de classes
    QStringList * list_ID = new QStringList;
    QString * id_classe = new QString;

    for(auto classe : reseau->getListeClasseClient())
    {
      if(classe->getIDClasseClient() != 0)
      {
        id_classe->setNum(classe->getIDClasseClient());
        *list_ID << *id_classe;
      }
    }

    //Récupère l'identifiant de la classe à supprimer
    *id_classe = QInputDialog::getItem(this, "ClassID", "Choose the ID of a class : ",*list_ID,0,true,&ok);

    if(ok){
      //Récupère l'identifiant sous forme d'entier
      int ID = id_classe->toInt();

      //Recherche de la classe correspondant à l'identifiant
      for(auto it = reseau->getListeClasseClient().begin(); it != reseau->getListeClasseClient().end(); it++)
      {
        if((*it)->getIDClasseClient() == ID)
        {
          classe_a_afficher = (*it);
          break;
        }
      }

      afficher_reseau();
      afficher_routage_classe(*classe_a_afficher);
    }

    delete list_ID;
    delete id_classe;
  }else QMessageBox::information(this,"Information", "No routing to see.");
}

/**Méthode affichant graphiquement le réseau**/
void FenetreCreation::afficher_reseau()
{
  //Efface les objets se trouvant sur la scène
  scene->clear();

  //Afficher l'entrée et la sortie
  afficher_entree_sortie();

  //Parcourt la liste des files pour les afficher
  for(auto it_files = reseau->getListeFile().begin(); it_files != reseau->getListeFile().end(); it_files++)
  {
    afficher_file((*it_files)->getCoord());
  }

  //Mettre à jour le nombre de classes dans le réseau
  QString * nb_classes = new QString, * nb_files = new QString;

  //Assigne les valeurs
  nb_classes->setNum(reseau->getNbClasses());
  nb_files->setNum(reseau->getNbFiles());

  infos_reseau->setText("<strong> Number of :<br>Classes : </strong>" + *nb_classes+ "<strong><br>Queues : </strong>" + *nb_files);

  delete nb_classes;
  delete nb_files;

}

/**Méthode d'affichage du routage d'une classe
@param cc, une référence sur la classe de client dont le routage doit être afficher
**/
void FenetreCreation::afficher_routage_classe(ClasseClient& cc)
{
  vector<int> routage = cc.getRoutage();
  coordonnees coord_fp, coord_fa;
  int cmp = 0,milieu = 0,num_classe = cc.getIDClasseClient();
  QPen pen(QColor(178,34,34),0);



  //Parcourt de la liste de routage de la classe cc
  for(int i = 0; i< (int)routage.size(); i++)
  {
    //Si la première file du routage a été atteint et que le réseau est ouvert
    if(cmp==0)
    {
      if(reseau->getTypeReseau()==1)
      {
        for(auto ite_file = reseau->getListeFile().begin();ite_file != reseau->getListeFile().end(); ite_file++)
        {
          //Si l'identifiant de la file dans la liste correspond à l'identifiant de la file précédente dans le routage
          if((*ite_file)->getIDFile() == routage.at(0))
          {
            scene->addLine(scene->width()-(scene->width()-10)+70,(scene->height()/2+25/2),scene->width()-(scene->width()-10)+80,(scene->height()/2+25/2),pen);
            scene->addLine(scene->width()-(scene->width()-10)+80,(scene->height()/2+25/2),scene->width()-(scene->width()-10)+80,(*ite_file)->getCoord().y,pen);
            scene->addLine(scene->width()-(scene->width()-10)+80,(*ite_file)->getCoord().y,(*ite_file)->getCoord().x-LONGUEUR_FILE/2,(*ite_file)->getCoord().y,pen);
            break;
          }
        }
      }
    }
    //Si la dernière file du routage a été atteint
    if(cmp == (int)routage.size()-1)
    {
      if(reseau->getTypeReseau()==1)
      {
        for(auto ite_file = reseau->getListeFile().begin();ite_file != reseau->getListeFile().end(); ite_file++)
        {
          //Si l'identifiant de la file dans la liste correspond à l'identifiant de la file précédente dans le routage
          if((*ite_file)->getIDFile() == routage.at(routage.size()-1))
          {
            scene->addLine(scene->width()-80,(scene->height()/2+25/2),scene->width()-90,(scene->height()/2+25/2),pen);
            scene->addLine(scene->width()-90,(scene->height()/2+25/2),scene->width()-90,(*ite_file)->getCoord().y,pen);
            scene->addLine(scene->width()-90,(*ite_file)->getCoord().y,(*ite_file)->getCoord().x+LONGUEUR_FILE,(*ite_file)->getCoord().y,pen);
            break;
          }
        }
      }

    }
    //Si la deuxième file du routage a été atteint
    if (cmp>0)
    {
      //Recherche des coordonnées de la file précédente dans la liste des files du réseau
      for(auto ite_file = reseau->getListeFile().begin();ite_file != reseau->getListeFile().end(); ite_file++)
      {
        //Si l'identifiant de la file dans la liste correspond à l'identifiant de la file précédente dans le routage
        if((*ite_file)->getIDFile() == routage.at(i-1))
        {
          //Récupère ses coordonnées
          coord_fp = (*ite_file)->getCoord();
          break;
        }
      }

      //De même avec la file actuelle du routage
      for(auto ite_file = reseau->getListeFile().begin();ite_file != reseau->getListeFile().end(); ite_file++)
      {
        if((*ite_file)->getIDFile() == routage.at(i))
        {
          coord_fa = (*ite_file)->getCoord();
          break;
        }
      }

      //Calcule le milieu entre les deux files
      milieu = (coord_fa.x+coord_fp.x)/2;

      //Si les deux files correspondent à la même file
      if((coord_fp.x == coord_fa.x)&&(coord_fp.y == coord_fa.y))
      {
        scene->addLine((coord_fp.x - (LONGUEUR_FILE/2 -num_classe)),coord_fp.y-(LARGEUR_FILE/2),coord_fp.x - (LONGUEUR_FILE/2 -num_classe),coord_fp.y-(LARGEUR_FILE+num_classe),pen);
        scene->addLine(coord_fp.x - (LONGUEUR_FILE/2 -num_classe),coord_fp.y-(LARGEUR_FILE+num_classe),coord_fa.x + (LONGUEUR_FILE/2 -num_classe),coord_fa.y-(LARGEUR_FILE+num_classe),pen);
        scene->addLine(coord_fa.x + (LONGUEUR_FILE/2 -num_classe),coord_fa.y-(LARGEUR_FILE/2),coord_fa.x + (LONGUEUR_FILE/2 - num_classe),coord_fa.y-(LARGEUR_FILE+num_classe),pen);
      }
      //Si les deux files sont alignés horizontalement et que la file précédente se trouve à gauche de la file actuelle
      else if((coord_fp.x < coord_fa.x)&&(coord_fp.y == coord_fa.y))
      {
        if(num_classe%2 == 0) scene->addLine(coord_fp.x +LONGUEUR_FILE,coord_fp.y+num_classe,coord_fa.x-LONGUEUR_FILE/2,coord_fa.y+num_classe,pen);
        else scene->addLine(coord_fp.x +LONGUEUR_FILE,coord_fp.y-num_classe,coord_fa.x-LONGUEUR_FILE/2,coord_fa.y-num_classe,pen);
      }
      //Si les deux files sont alignés horizontalement et que la file précédente se trouve à droite de la file actuelle
      else if((coord_fp.x > coord_fa.x)&&(coord_fp.y == coord_fa.y))
      {
        if(num_classe%2 == 0) scene->addLine(coord_fa.x +LONGUEUR_FILE,coord_fa.y+num_classe,coord_fp.x-LONGUEUR_FILE/2,coord_fp.y+num_classe,pen);
        else scene->addLine(coord_fa.x +LONGUEUR_FILE,coord_fa.y-num_classe,coord_fp.x-LONGUEUR_FILE/2,coord_fp.y-num_classe,pen);
      }
      //Si les deux files sont alignés verticalement et que la file précédente se trouve au-dessus de la file actuelle
      else if((coord_fp.x == coord_fa.x)&&(coord_fp.y < coord_fa.y))
      {
        if(num_classe%2 == 0) scene->addLine(coord_fp.x+num_classe,coord_fp.y+LARGEUR_FILE/2,coord_fa.x+num_classe,coord_fa.y-LARGEUR_FILE/2,pen);
        else scene->addLine(coord_fp.x-num_classe,coord_fp.y+LARGEUR_FILE/2,coord_fa.x-num_classe,coord_fa.y-LARGEUR_FILE/2,pen);
      }
      //Si les deux files sont alignés verticalement et que la file précédente se trouve en-dessous de la file actuelle
      else if((coord_fp.x == coord_fa.x)&&(coord_fp.y > coord_fa.y))
      {
        if(num_classe%2 == 0) scene->addLine(coord_fa.x+num_classe,coord_fa.y+LARGEUR_FILE/2,coord_fp.x+num_classe,coord_fp.y-LARGEUR_FILE/2,pen);
        else scene->addLine(coord_fa.x-num_classe,coord_fa.y+LARGEUR_FILE/2,coord_fp.x-num_classe,coord_fp.y-LARGEUR_FILE/2,pen);
      }
      //Si les deux files ne sont pas alignés verticalement et que la file précédente se trouve en-dessous de la file actuelle
      else if(((coord_fp.x < coord_fa.x)&&(coord_fp.y > coord_fa.y))||((coord_fp.x > coord_fa.x)&&(coord_fp.y > coord_fa.y)))
      {
        if(num_classe%2 == 0)
        {
          scene->addLine(coord_fa.x+num_classe,coord_fa.y+LARGEUR_FILE/2,coord_fa.x+num_classe,coord_fa.y+LARGEUR_FILE,pen);
          scene->addLine(coord_fa.x+num_classe,coord_fa.y+LARGEUR_FILE,milieu+num_classe,coord_fa.y+LARGEUR_FILE,pen);
          scene->addLine(milieu+num_classe,coord_fa.y+LARGEUR_FILE,milieu+num_classe,coord_fp.y-LARGEUR_FILE,pen);
          scene->addLine(milieu+num_classe,coord_fp.y-LARGEUR_FILE,coord_fp.x+num_classe,coord_fp.y-LARGEUR_FILE,pen);
          scene->addLine(coord_fp.x+num_classe,coord_fp.y-LARGEUR_FILE,coord_fp.x+num_classe,coord_fp.y-LARGEUR_FILE/2,pen);
        }
        else
        {
          scene->addLine(coord_fa.x-num_classe,coord_fa.y+LARGEUR_FILE/2,coord_fa.x-num_classe,coord_fa.y+LARGEUR_FILE,pen);
          scene->addLine(coord_fa.x-num_classe,coord_fa.y+LARGEUR_FILE,milieu-num_classe,coord_fa.y+LARGEUR_FILE,pen);
          scene->addLine(milieu-num_classe,coord_fa.y+LARGEUR_FILE,milieu-num_classe,coord_fp.y-LARGEUR_FILE,pen);
          scene->addLine(milieu-num_classe,coord_fp.y-LARGEUR_FILE,coord_fp.x-num_classe,coord_fp.y-LARGEUR_FILE,pen);
          scene->addLine(coord_fp.x-num_classe,coord_fp.y-LARGEUR_FILE,coord_fp.x-num_classe,coord_fp.y-LARGEUR_FILE/2,pen);
        }
      }
      //Si les deux files ne sont pas alignés verticalement et que la file précédente se trouve au-dessus de la file actuelle
      else if(((coord_fp.x < coord_fa.x)&&(coord_fp.y < coord_fa.y))||((coord_fp.x > coord_fa.x)&&(coord_fp.y < coord_fa.y)))
      {
        if(num_classe%2 == 0)
        {
          scene->addLine(coord_fp.x+num_classe,coord_fp.y+LARGEUR_FILE/2,coord_fp.x+num_classe,coord_fp.y+LARGEUR_FILE,pen);
          scene->addLine(coord_fp.x+num_classe,coord_fp.y+LARGEUR_FILE,milieu+num_classe,coord_fp.y+LARGEUR_FILE,pen);
          scene->addLine(milieu+num_classe,coord_fp.y+LARGEUR_FILE,milieu+num_classe,coord_fa.y-LARGEUR_FILE,pen);
          scene->addLine(milieu+num_classe,coord_fa.y-LARGEUR_FILE,coord_fa.x+num_classe,coord_fa.y-LARGEUR_FILE,pen);
          scene->addLine(coord_fa.x+num_classe,coord_fa.y-LARGEUR_FILE,coord_fa.x+num_classe,coord_fa.y-LARGEUR_FILE/2,pen);
        }
        else
        {
          scene->addLine(coord_fp.x-num_classe,coord_fp.y+LARGEUR_FILE/2,coord_fp.x-num_classe,coord_fp.y+LARGEUR_FILE,pen);
          scene->addLine(coord_fp.x-num_classe,coord_fp.y+LARGEUR_FILE,milieu-num_classe,coord_fp.y+LARGEUR_FILE,pen);
          scene->addLine(milieu-num_classe,coord_fp.y+LARGEUR_FILE,milieu-num_classe,coord_fa.y-LARGEUR_FILE,pen);
          scene->addLine(milieu-num_classe,coord_fa.y-LARGEUR_FILE,coord_fa.x-num_classe,coord_fa.y-LARGEUR_FILE,pen);
          scene->addLine(coord_fa.x-num_classe,coord_fa.y-LARGEUR_FILE,coord_fa.x-num_classe,coord_fa.y-LARGEUR_FILE/2,pen);
        }
      }
    }

    cmp++;
  }
}

/**Méthode d'affichage d'une file
@param coordonnees, les coordonnées de la file à dessiner
**/
void FenetreCreation::afficher_file(coordonnees centre_dessin)
{
  //Dessiner la station
  QRect rectangle(0,0, LONGUEUR_FILE, LARGEUR_FILE);
  scene->addRect(rectangle)->setPos(centre_dessin.x-LONGUEUR_FILE/2,centre_dessin.y-LARGEUR_FILE/2);
  scene->addEllipse(0,0,LARGEUR_FILE, LARGEUR_FILE)->setPos(centre_dessin.x+LONGUEUR_FILE/2, centre_dessin.y-LARGEUR_FILE/2);

  //Ajoute le rectangle représentant le numéro de la file
  scene->addRect(0,0,LARGEUR_FILE-10,LARGEUR_FILE/2)->setPos(centre_dessin.x-LARGEUR_FILE,centre_dessin.y-LARGEUR_FILE);

  //Recherche de la file correspondant aux coordonnées
  int ID = 0;
  QString * id = new QString;

  for(auto file : reseau->getListeFile())
  {
    if((file->getCoord().x == centre_dessin.x)&&(file->getCoord().y == centre_dessin.y))
    {
      ID = file->getIDFile();
      break;
    }
  }
  //Transforme en string
  id->setNum(ID);

  //Ajoute le numéro de la file
  QGraphicsTextItem * texte = scene->addText(*id);
  if(ID < 10) texte->setPos((centre_dessin.x-LARGEUR_FILE)+(LARGEUR_FILE-10)/3,centre_dessin.y-LARGEUR_FILE);
  else if(ID < 100) texte->setPos((centre_dessin.x-LARGEUR_FILE)+(LARGEUR_FILE-10)/5,centre_dessin.y-LARGEUR_FILE);
  else texte->setPos((centre_dessin.x-LARGEUR_FILE)+(LARGEUR_FILE-10)/7,centre_dessin.y-LARGEUR_FILE);
  texte->setDefaultTextColor(Qt::blue);

  delete id;
}

/**Méthode d'affichage de l'entrée/Sortie**/
void FenetreCreation::afficher_entree_sortie()
{
  if(reseau->getTypeReseau() == 1)
  {
    //Afficher l'entrée
    QRect entree(0,0,70,25);
    scene->addRect(entree)->setPos(scene->width()-(scene->width()-10),scene->height()/2);
    scene->addText("Entry")->setPos(scene->width()-(scene->width()-22),scene->height()/2);

    //Afficher la sortie
    QRect sortie(0,0,70,25);
    scene->addRect(sortie)->setPos(scene->width()-80,scene->height()/2);
    scene->addText("Exit")->setPos(scene->width()-64,scene->height()/2);
  }

}
