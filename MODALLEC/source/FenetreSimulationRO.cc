#include "FenetreSimulationRO.hh"
#include <qt4/QtGui/QGraphicsItem>
#include <qt4/QtCore/QEventLoop>

#define LARGEUR_FILE 50
#define LONGUEUR_FILE 100
#define DIAMETRE_SERVEUR 50

/**Constructeur
@param r, l'adresse du réseau à simuler
@param v, l'adresse de la vue affichant graphiquement le réseau
@param parent, l'adresse du widget parent de la fenêtre
**/
FenetreSimulationRO::FenetreSimulationRO(Reseau * r, Vue * v,QWidget * parent) : QWidget(parent),simulation(r,25), fenetre_infos_reseau(r),fenetre_echeancier(&(simulation.getEcheancier()))
{
  try
  {
    if((r == NULL)||(v == NULL)) throw invalid_argument("Constructeur FenetreSimulationRO : pointeur Reseau à NULL et/ou pointeur Vue à NULL");
    else
    {
      //Retirer la barre du haut de la fenêtre
      setWindowFlags(Qt::CustomizeWindowHint);

      //Initialiser les attributs de la classe
      vue = new Vue(this);
      results = new QPushButton("Results");
      history = new QPushButton("History");
      infos_queue = new QPushButton("Infos Queues");
      infos_classes = new QPushButton("Infos Classes");
      change_window = new QPushButton("Switch \nwindow");
      layout_principal = new QGridLayout;
      layout = new QVBoxLayout;
      chrono = new QTime (0,0,0);
      timer_chrono = new QTimer;
      secondes = 0;
      arret = false;

      //Délimiter la taille de la vue
      vue->setFixedSize(v->width(),v->height());

      //Ajouter la scène à la vue
      vue->setScene(v->scene());

      //Espacer les objets dans la boîte de rangement vertical
      layout->setSpacing(20);

      //Ajouter les objets dans la boîte de rangement vertical
      layout->addWidget(&fenetre_echeancier);
      layout->addWidget(&fenetre_infos_reseau);
      layout->addWidget(results);
      layout->addWidget(history);
      layout->addWidget(infos_queue);
      layout->addWidget(infos_classes);
      layout->addWidget(change_window);

      //Ajouter les objets dans la boîte de rangement de la fenêtre
      layout_principal->addLayout(layout,1,5);
      layout_principal->addWidget(vue,0,0,4,5);

      //Ajouter la boîte de rangement à la fenêtre
      setLayout(layout_principal);

      //Connecter les boutons aux slots
      connect (timer_chrono, SIGNAL (timeout()), this, SLOT (chrono_refresh()));
      connect(results,SIGNAL(clicked()),this,SLOT(Results()));
      connect(history,SIGNAL(clicked()),this,SLOT(History()));
      connect(infos_queue,SIGNAL(clicked()),this,SLOT(Infos_Queue()));
      connect(infos_classes,SIGNAL(clicked()),this,SLOT(Infos_Classes()));
      connect(change_window,SIGNAL(clicked()),this,SLOT(hide()));
    }
  }
  catch(string const& chaine){
		cerr << chaine <<endl;
	}

}

/**Destructeur**/
FenetreSimulationRO::~FenetreSimulationRO()
{
  delete results;
  delete infos_queue;
  delete infos_classes;
  delete change_window;
  delete layout;
  //delete vue;
  delete layout_principal;
  delete chrono;
  delete timer_chrono;
}

/**Méthode de récupération de la simulation
@return une référence sur la simulation**/
SimulationRO& FenetreSimulationRO::getSimulation()
{
    return simulation;
}

/**Méthode de récupération de l'historique
@return une référence sur l'historique'*/
HistoriqueRO& FenetreSimulationRO::getHistorique()
{
    return historique;
}

/**Méthode de récupération de la fenêtre d'informations du réseau
@return une réference sur la fenêtre d'informations du réseau**/
FenetreInfosReseau& FenetreSimulationRO::getFenetreInfosReseau(){
  return fenetre_infos_reseau;
}

void FenetreSimulationRO::History()
{
  //Créer la boîte de dialogue de l'historique
  DialogHistoriqueRO * dhRF = new DialogHistoriqueRO(&historique);
  //Ouvrir la boîte de dialogue
  dhRF->exec();
  delete dhRF;
}

/**Slot calculant et affichant les résultats de performances du réseau**/
void FenetreSimulationRO::Results()
{
  //Récupérer le réseau
  Reseau * R = simulation.getReseau();
  //Récupérer les données du réseau
  DonneesCalculsRO * donnees = &simulation.getDonnes_calculs();
  //Récupérer la date actuelle
  int date_actuelle = simulation.getEcheancier().getDateActuelle();
  //Créer une nouvelle sauvegarde des performances du réseau
  PerfsRO * nouvelPerfRO = new PerfsRO(date_actuelle);

  //Calculer les performances du réseau
  nouvelPerfRO->calcul_debit_sortie(donnees->getListeNbClientSortant());
  nouvelPerfRO->calcul_debit_entree(donnees->getListeNbClientEntrant());
  nouvelPerfRO->calcul_tps_sejour_moyen(donnees->getListeClientEntres());
  nouvelPerfRO->calcul_nb_moyen_clients(donnees->getListeNbClients());
  //Ajouter la sauvegarde à l'historique
  historique.ajouterPerfsReseau(*nouvelPerfRO);

  //Itérer sur la liste des files du réseau
  list<File*> liste_File = R->getListeFile();
  list<File*>::iterator it;
  for (it = liste_File.begin() ; it != liste_File.end() ; it++)
  {
    //Ajouter une sauvegarde des performances de chacune d'elle à l'historique
    historique.ajouterPerfsFile(*(*it),simulation.getDureeSimulation());
  }

  //Afficher les résultats des performances à l'utilisateur
  DialogResultatsRO * drRO = new DialogResultatsRO(&(historique.getHistorique().back()));

  drRO->exec();

  delete drRO;
}

/**Slot affichant l'historique des performances du réseau**/
void FenetreSimulationRO::Infos_Queue()
{
  //Tester si une file a été récupérée
  int flag = 0;

  //Pointeur sur la file à regarder
  File * file_a_consulter = NULL;

  //Créer une fenêtre contenant la vue acceptant les clics
  QDialog * fenetre_vue_cliquable = new QDialog;
  QGridLayout * layout_vue = new QGridLayout;

  //Remettre la position du clic à 0
  vue->remise_a_zero();

  //Enlever la barre du haut de la fenêtre
  fenetre_vue_cliquable->setWindowFlags(Qt::CustomizeWindowHint);

  //Enlever la marge entre le layout et la fenêtre
  layout_vue->setContentsMargins(0,0,0,0);

  //Modifier la taille des objets
  fenetre_vue_cliquable->setFixedSize(vue->width(),vue->height());

  //Ajouter la vue à la boîte de rangement de la boîte de dialogue
  layout_vue->addWidget(vue,1,0);

  //Ajouter la boîte de rangement à la fenêtre
  fenetre_vue_cliquable->setLayout(layout_vue);

  //Connecter la récupération du clic à la fermeture de la vue
  connect(vue,SIGNAL(clicked()),fenetre_vue_cliquable,SLOT(accept()));

  //Ajouter la boîte de dialogue dans la fenêtre de création
  layout_principal->addWidget(fenetre_vue_cliquable,0,0,4,5);

  fenetre_vue_cliquable->show();
  QMessageBox::information(this,"Information", "Please click on a queue to see its information.");
  //Réouvre la fenêtre contenant la vue pour récupérer le clic
  fenetre_vue_cliquable->exec();

  //Vérifier que le clic correspond à une file
  for(auto it_files = simulation.getReseau()->getListeFile().begin(); it_files != simulation.getReseau()->getListeFile().end(); it_files++){
    //Si le clic correspond au limite d'une file
    if((vue->getPosXClic() < (*it_files)->getCoord().x + LONGUEUR_FILE)
    && (vue->getPosXClic() > (*it_files)->getCoord().x - LONGUEUR_FILE/2)
    && (vue->getPosYClic() < (*it_files)->getCoord().y + LARGEUR_FILE/2)
    && (vue->getPosYClic() > (*it_files)->getCoord().y - LARGEUR_FILE/2))
    {
      flag = 1;
      file_a_consulter = *it_files;
      break;
    }
  }

  //Tant que l'utilisateur n'a pas cliqué sur une file
  while(flag == 0)
  {
    fenetre_vue_cliquable->show();
    QMessageBox::warning(this,"Warning", "No queue chosen. Please click on a queue to see its information.");
    //Réouvre la fenêtre contenant la vue pour récupérer le clic
    fenetre_vue_cliquable->exec();

    //Vérifier que le clic correspond à une file
    for(auto it_files = simulation.getReseau()->getListeFile().begin(); it_files != simulation.getReseau()->getListeFile().end(); it_files++){
      if((vue->getPosXClic() < (*it_files)->getCoord().x + LONGUEUR_FILE)
      && (vue->getPosXClic() > (*it_files)->getCoord().x - LONGUEUR_FILE/2)
      && (vue->getPosYClic() < (*it_files)->getCoord().y + LARGEUR_FILE/2)
      && (vue->getPosYClic() > (*it_files)->getCoord().y - LARGEUR_FILE/2))
      {
        flag = 1;
        file_a_consulter = *it_files;
        break;
      }
    }
  }

  //Remettre la vue dans le layout de la fenêtre de création
  layout_principal->addWidget(vue,0,0,4,5);

  //Créer la boîte de dialogue d'affichage des données de la file
  DialogInfosQueue * bdq = new DialogInfosQueue(file_a_consulter);

  //Cacher la barre du haut de la boîte de dialogue
  bdq->setWindowFlags(Qt::CustomizeWindowHint);

  //Mettre la fenêtre à droite de la file
  bdq->move(file_a_consulter->getCoord().x + 180,file_a_consulter->getCoord().y - 100);

  //Ouvrir la boîte de dialogue
  bdq->exec();

  delete bdq;
  delete layout_vue;
  delete fenetre_vue_cliquable;
}

/**Slot affichant les informations de la classe demandée**/
void FenetreSimulationRO::Infos_Classes()
{
  //Récupérer la classe à regarder
  ClasseClient * classe_a_consulter = NULL;

  //Utiliser pour savoir si l'utilisateur a cliqué sur ok
  bool ok;

  //Créer et remplir la liste des identifiants de classes
  QStringList * list_ID = new QStringList;
  QString * id_classe = new QString;

  //Récupérer l'identifiant des classes de client du réseau
  for(auto classe : simulation.getReseau()->getListeClasseClient())
  {
      id_classe->setNum(classe->getIDClasseClient());
      *list_ID << *id_classe;
  }

  //Récupérer l'identifiant de la classe à supprimer
  *id_classe = QInputDialog::getItem(this, "ClassID", "Choose the ID of a class : ",*list_ID,0,true,&ok);

  //Si l'utilisateur à clicr sur OK
  if(ok){
    //Récupérer l'identifiant sous forme d'entier
    int ID = id_classe->toInt();

    //Récupérer la classe correspondant à l'identifiant
    for(auto it_classe = simulation.getReseau()->getListeClasseClient().begin(); it_classe != simulation.getReseau()->getListeClasseClient().end(); it_classe++)
    {
      if((*it_classe)->getIDClasseClient() == ID)
      {
        classe_a_consulter = (*it_classe);
        break;
      }
    }

    //Créer de la boîte de dialogue
    DialogInfosClass * bdc = new DialogInfosClass(classe_a_consulter);

    //Retirer la barre du haut de la boîte de dialogue
    bdc->setWindowFlags(Qt::CustomizeWindowHint);

    //Centrer la boîte de dialogue par rapport à la fenêtre de simulation
    bdc->move(width()/2-100,height()/2-100);

    //Ouvrir la boîte de dialogue
    bdc->exec();


    delete bdc;
  }

  delete list_ID;
  delete id_classe;
}

/**Slot mettant à jour le chronomètre**/
void FenetreSimulationRO::chrono_refresh()
{
   *chrono = chrono->addSecs(1);
   secondes = secondes + 1;


   if(secondes == 2)
   {
     *chrono = chrono->addSecs(-secondes);
   	 secondes = 0;
   }
}

/**Méthode de lancement du chronomètre**/
void FenetreSimulationRO::start_chrono()
{
  //Lancer le chronomètre
  timer_chrono->start(2000);
}

/**Méthode relançant la simulation**/
void FenetreSimulationRO::resume(){
  timer_chrono->start(2000);
}

/**Méthode mettant en pause la simualtion**/
void FenetreSimulationRO::pause(){
  timer_chrono->stop();
}

/**Méthode arrêtant la simulation**/
void FenetreSimulationRO::stop(){

  simulation.getEcheancier().setDateActuelle(simulation.getEcheancier().getDateActuelle()+10);
  arret = true;
}

/**Méthode exécutant la simulation
@param nbClientsInitial, le nombre de clients à créer pour le début de la simualtion**/
void FenetreSimulationRO::executer_simulation(const int nbClientsInitial)
{
  try{
      if(nbClientsInitial < 0) throw ("Méthode executer_simulation : entier nbClientsInitial négatif");
      else{

        QEventLoop * loop = new QEventLoop;
        connect(timer_chrono,SIGNAL(timeout()),loop,SLOT(quit()));

        Echeancier * echeancier = &simulation.getEcheancier();

        //Compter le nombre d'évènements
        int cmpEvent = 0;

        //Lance la distribution initiale
        simulation.distribution_initiale(nbClientsInitial);

        //Mettre à jour la liste de mesures du nombre de clients dans le réseau
        simulation.getDonnes_calculs().ajouterMesuresNbclients(nbClientsInitial,0);

        //Mettre à jour les compteurs au-dessus des files
        afficher_compteur_clients();

        //Afficher le premier évènement
        fenetre_echeancier.setInfoDate();
		    fenetre_echeancier.setInfoClient();
		    fenetre_echeancier.setInfoFile();
		    fenetre_echeancier.setInfoServeur();
		    fenetre_echeancier.setDateActuelle();

        //Mettre à jour les informations du réseau
        fenetre_infos_reseau.setInfoNbClientsActuel();
        fenetre_infos_reseau.setInfoNbClientsPasses();
        fenetre_infos_reseau.setInfoNbClasses();
        fenetre_infos_reseau.setInfoNbClientsClasse();

        //Tant que la date de l'horloge ne correspond pas à la durée de simulation et que l'échéancier n'est pas vide
        while(((echeancier->getDateActuelle() )< simulation.getDureeSimulation())
        && (!echeancier->getListeEvenement().empty()))
        {
          /*cout << "EVENEMENT EXECUTE" << endl;
          cout << "Client n° "<<echeancier->getListeEvenement().front().client->getID_client() << endl;
          cout << "Temps de service : "<<echeancier->getListeEvenement().front().client->getTps_service() << endl;
          cout << "File n° "<<echeancier->getListeEvenement().front().file_destinee->getIDFile() << endl;
          if(echeancier->getListeEvenement().front().serveur_destine != NULL)cout << "Serveur n° "<<echeancier->getListeEvenement().front().serveur_destine->getIDServeur() << endl;*/

          //Si l'échéancier n'est pas vide
          if(!echeancier->getListeEvenement().empty())
          {
            //Si la date du prochain évènement est supérieure à la date de simulation donnée par l'utilisateur
            if(echeancier->getListeEvenement().front().date_traitement > simulation.getDureeSimulation()) break;

        		//Exécuter l'échéancier

            //Compter un évènement
            if(echeancier->getListeEvenement().front().type_evenement == 3) cmpEvent += 1;

            //Mise à jour de l'évènement 0 dans l'échéancier
            fenetre_echeancier.maj_position();

            //Exécuter le prochain évènement
            simulation.executer_evenement();

            //Trier l'échéancier
            echeancier->trier_croissant();

            //Mise à jour de la date actuelle
            fenetre_echeancier.setDateActuelle();

            //Mettre à jour les informations du réseau
            fenetre_infos_reseau.setInfoNbClientsActuel();
            fenetre_infos_reseau.setInfoNbClientsPasses();
            fenetre_infos_reseau.setInfoNbClasses();
            fenetre_infos_reseau.setInfoNbClientsClasse();

            //Mettre à jour les données pour le calcul des performances du réseau
            simulation.getDonnes_calculs().ajouterMesuresNbclients(simulation.getReseau()->getNbClients(), echeancier->getDateActuelle());

            //Ajouter une mesure à la liste du nombre de clients dans chaque file et une mesure à la liste du nombre de clients entrés dans la file
            for(auto file : simulation.getReseau()->getListeFile())
            {
      			  file->ajouter_mesure_nb_clients(file->getNbClients(),echeancier->getDateActuelle());
              file->ajouter_mesure_nb_clients_entres(file->getNbClientsEntres(),echeancier->getDateActuelle());
      		  }

            if(cmpEvent == 3)
            {
          		//Faire le routage des clients
              simulation.entrer_clients_reseau();
              simulation.sortir_clients_reseau();
          		//Router les clients dans le réseau
              simulation.routage_clients();

              //Trier l'échéancier
              echeancier->trier_croissant();

              //Mettre à jour les informations du réseau
              fenetre_infos_reseau.setInfoNbClientsActuel();
              fenetre_infos_reseau.setInfoNbClientsPasses();
              fenetre_infos_reseau.setInfoNbClasses();
              fenetre_infos_reseau.setInfoNbClientsClasse();

              cmpEvent = 0;
            }

            //Mettre à jour les compteurs au-dessus des files
        		afficher_compteur_clients();

            loop->exec();

            if(arret == true) break;
          }

        }

          //Afficher un message de fin
          QMessageBox::information(NULL,"", "The simulation is finished.");

          delete loop;
      }
  }
  catch(string const& chaine){
		cerr << chaine <<endl;
	}
}

/**Méthode d'affichage graphique du nombre de clients**/
void FenetreSimulationRO::afficher_compteur_clients()
{
  //Récupérer le réseau simulé
  Reseau * reseau = simulation.getReseau();

  //Récupérer la scène
  QGraphicsScene * scene = vue->scene();

  //Colorer les compteurs
  QPen pen(QColor(178,34,34),0);

  //Récupérer les coordonnées de la file pour affihcer son compteur
  coordonnees coord_file;
  //Récupérer le nombre de clients sous forme de string
  QString * cmp = new QString;

  //Recupérer l'identifiant de la file concernée
  int ID = 0;
  QString * id = new QString;

  //Efface les objets se trouvant sur la scène
  scene->clear();

  //Afficher l'entrée
  QRect entree(0,0,70,25);
  scene->addRect(entree)->setPos(scene->width()-(scene->width()-10),scene->height()/2);
  scene->addText("Entry")->setPos(scene->width()-(scene->width()-22),scene->height()/2);

  //Afficher la sortie
  QRect sortie(0,0,70,25);
  scene->addRect(sortie)->setPos(scene->width()-80,scene->height()/2);
  scene->addText("Exit")->setPos(scene->width()-64,scene->height()/2);

  //Parcourt la liste des files pour les afficher et afficher leur compteur
  for(auto it_files = reseau->getListeFile().begin(); it_files != reseau->getListeFile().end(); it_files++)
  {
    //Récupère les coordonnées de la file
    coord_file = (*it_files)->getCoord();

    //Ajoute le rectangle représentant le compteur
    (scene->addRect(0,0,LARGEUR_FILE-10,LARGEUR_FILE/2,pen))->setPos(coord_file.x+10,coord_file.y-LARGEUR_FILE);

    //Récupère le nombre de clients dans la file
    cmp->setNum((*it_files)->getNbClients());

    //Colorer le texte
    QGraphicsTextItem * txt = vue->scene()->addText(*cmp);
    txt->setDefaultTextColor(Qt::red);

    //Ajoute le nombre de clients dans la file au compteur
    if((*it_files)->getNbClients() < 10) txt->setPos((coord_file.x+10)+(LARGEUR_FILE-10)/3,coord_file.y-LARGEUR_FILE);
    else if((*it_files)->getNbClients() < 100) txt->setPos((coord_file.x+10)+(LARGEUR_FILE-10)/5,coord_file.y-LARGEUR_FILE);
    else txt->setPos((coord_file.x+10)+(LARGEUR_FILE-10)/7,coord_file.y-LARGEUR_FILE);


    //Dessiner la station
    QRect rectangle(0,0, LONGUEUR_FILE, LARGEUR_FILE);
    scene->addRect(rectangle)->setPos(coord_file.x-LONGUEUR_FILE/2,coord_file.y-LARGEUR_FILE/2);
    scene->addEllipse(0,0,LARGEUR_FILE, LARGEUR_FILE)->setPos(coord_file.x+LONGUEUR_FILE/2, coord_file.y-LARGEUR_FILE/2);

    //Ajoute le rectangle représentant le numéro de la file
    scene->addRect(0,0,LARGEUR_FILE-10,LARGEUR_FILE/2)->setPos(coord_file.x-LARGEUR_FILE,coord_file.y-LARGEUR_FILE);

    //Récupérer l'identifiant de la file
    ID = (*it_files)->getIDFile();

    //Transforme en string
    id->setNum(ID);

    //Ajoute le numéro de la file
    QGraphicsTextItem * texte = scene->addText(*id);
    if(ID < 10) texte->setPos((coord_file.x-LARGEUR_FILE)+(LARGEUR_FILE-10)/3,coord_file.y-LARGEUR_FILE);
    else if(ID < 100) texte->setPos((coord_file.x-LARGEUR_FILE)+(LARGEUR_FILE-10)/5,coord_file.y-LARGEUR_FILE);
    else texte->setPos((coord_file.x-LARGEUR_FILE)+(LARGEUR_FILE-10)/7,coord_file.y-LARGEUR_FILE);

    //Donner une couleur au texte
    texte->setDefaultTextColor(Qt::blue);

  }


  delete id;
  delete cmp;
}
