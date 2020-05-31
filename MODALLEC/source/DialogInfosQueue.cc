#include "DialogInfosQueue.hh"
#include <qt4/QtGui/QScrollArea>

/**Constructeur
@param f, la file dont il faut afficher les informations
@param parent, le widget parent de la fenêtre de dialogue
**/
DialogInfosQueue::DialogInfosQueue(File * f,QWidget * parent) : QDialog(parent)
{
  try
  {
    if(f == NULL) throw invalid_argument("Constructeur DialogInfosQueue : pointeur File à NULL");
    else
    {
      //Retirer la barre du haut de la boîte de dialogue
      setWindowFlags(Qt::CustomizeWindowHint);
      //Délimiter la taille de la boîte de dialogue
      setMaximumSize(250,300);

      //Initialiser les attributs de la classe
      file = f;
      ordonnancement = new QLabel;
      loiService = new QLabel;
      nbClients = new QLabel;
      nbClientsServis = new QLabel;
      nbClientsPresentes = new QLabel;
      nbClientsPerdus = new QLabel;
      nbServeurs = new QLabel;
      layout = new QVBoxLayout;
      ok = new QPushButton("OK");
      Infos_Clients = new QPushButton("Clients informations");

      //Ajouter les objets à la boîte de rangement
      layout->addWidget(ordonnancement);
      layout->addWidget(loiService);
      layout->addWidget(nbClients);
      layout->addWidget(nbClientsServis);
      layout->addWidget(nbClientsPresentes);
      layout->addWidget(nbClientsPerdus);
      layout->addWidget(nbServeurs);
      layout->addWidget(Infos_Clients);
      layout->addWidget(ok);

      if(f != NULL)
      {
        //Afficher les données contenues dans la file
        setInfoOrdonnancement();
        setInfoLoiService();
        setInfoNbClients();
        setInfoNbClientsServis();
        setInfoNbClientsPresentes();
        setInfoNbClientsPerdus();
        setNbServeurs();
      }

      //Connecter les boutons
      connect(ok,SIGNAL(clicked()),this,SLOT(accept()));
      connect(Infos_Clients,SIGNAL(clicked()),this,SLOT(informations_clients()));

      //Ajouter la boîte de rangement à la boîte de dialogue
      setLayout(layout);

      //Personnaliser la boîte
      setStyleSheet("background-color: #C0C0C0;");
      ordonnancement->setStyleSheet("background-color: #B0C4DE; border-style: inset; border-radius: 1px; border-width: 1px; border-color: darkgrey;");
      loiService->setStyleSheet("background-color: #B0C4DE; border-style: inset; border-radius: 1px; border-width: 1px; border-color: darkgrey;");
      nbClients->setStyleSheet("background-color: #B0C4DE; border-style: inset; border-radius: 1px; border-width: 1px; border-color: darkgrey;");
      nbClientsServis->setStyleSheet("background-color: #B0C4DE; border-style: inset; border-radius: 1px; border-width: 1px; border-color: darkgrey;");
      nbClientsPresentes->setStyleSheet("background-color: #B0C4DE; border-style: inset; border-radius: 1px; border-width: 1px; border-color: darkgrey;");
      nbClientsPerdus->setStyleSheet("background-color: #B0C4DE; border-style: inset; border-radius: 1px; border-width: 1px; border-color: darkgrey;");
      nbServeurs->setStyleSheet("background-color: #B0C4DE; border-style: inset; border-radius: 1px; border-width: 1px; border-color: darkgrey;");
      ok->setStyleSheet(
      "QPushButton:pressed{background-color: darkgrey;}"
      "QPushButton{background-color: #B0C4DE;}"
      );
      Infos_Clients->setStyleSheet(
      "QPushButton:pressed{background-color: darkgrey;}"
      "QPushButton{background-color: #B0C4DE;}"
      );
    }
  }
  catch(string const& chaine){
		cerr << chaine <<endl;
	}
}

/**Destructeur**/
DialogInfosQueue::~DialogInfosQueue()
{
  delete ok;
  delete Infos_Clients;
  delete ordonnancement;
  delete loiService;
  delete nbClients;
  delete nbClientsServis;
  delete nbClientsPresentes;
  delete nbClientsPerdus;
  delete nbServeurs;
  delete layout;
}

/**Slot affichant les informations sur les clients de la file*/
void DialogInfosQueue::informations_clients()
{
    //Créer la boîte de dialogue affichant les informations des clients
    QDialog * bic = new QDialog;
    //Créer la boîte de rangement du label
    QVBoxLayout * layout = new QVBoxLayout;
    QPushButton * ok = new QPushButton("OK");
    //Créer la zone défilable
    QScrollArea * qArea = new QScrollArea;
    //Créer la fenêtre qui contiendra le label à afficher
    QWidget * fenetre_scroll = new QWidget;
    //Créer la boîte de rangement qui contiendra la zone défilable
    QVBoxLayout * rangement = new QVBoxLayout;
    //Afficher les données des clients sur la boîte de dialogue
    QLabel * donnees_clients = new QLabel;

    //Personnaliser la boîte de dialogue
    bic->setStyleSheet("background-color: #C0C0C0;");
    ok->setStyleSheet(
    "QPushButton:pressed{background-color: darkgrey;}"
    "QPushButton{background-color: #B0C4DE;}"
    );

    //Initialiser le label permettant d'afficher les données des clients
    QString * res = new QString;
    QString * num_client = new QString;
    QString * tps_attente = new QString;
    QString * tps_service = new QString;

    //Retirer la barre du haut de la boîte
    bic->setWindowFlags(Qt::CustomizeWindowHint);
    //Délimiter la taille de la boîte
    bic->setMinimumSize(295,400);
    bic->setMaximumSize(295,400);

    //Délimiter la taille de la fenêtre
    fenetre_scroll->setMinimumSize(255,1000);

    //Taille du bouton OK
    ok->setFixedWidth(240);

    //Ajouter les objets à la boîte de rangement
    layout->addWidget(donnees_clients);

    //Ajouter la boîte de rangement à la boîte de dialogue
    fenetre_scroll->setLayout(layout);

    //Ajouter la fenêtre à la zone défilable
    qArea->setWidget(fenetre_scroll);

    //Ajouter la zone défilable à la boîte de rangement
    rangement->addWidget(qArea);
    rangement->addWidget(ok);

    //Ajouter la boîte de rangement à la boîte de dialogue
    bic->setLayout(rangement);

    //Connecter le bouton
    connect(ok,SIGNAL(clicked()),bic,SLOT(accept()));

    //Pour chaque client de la file
    for(auto i = file->getListeClients().begin(); i!= file->getListeClients().end(); i++)
    {
      //Récupérer le numéro du client
      num_client->setNum((*i)->getID_client());

      //Récupérer le temps d'attente du client
      tps_attente->setNum((*i)->getTps_attente());

      //Récupérer le temps de service du client
      tps_service->setNum((*i)->getTps_service());

      //Concaténer toutes les données
      *res += "<strong> Client </strong>";
      *res += num_client;
      *res += "<br>";
      *res += "        |<strong>Wait time : </strong>";
      *res += tps_attente;
      *res += "<br>";
      *res += "        |<strong>Service time : </strong>";
      *res += tps_service;
      *res += "<br>";
      *res += "<br>";
    }

    //Ajouter les données au label
    donnees_clients->setText(*res);

    //Changer la position de la boîte
    bic->move(x(),y());

    //Ouvrir la boîte de dialogue
    bic->exec();

    delete res;
    delete num_client;
    delete tps_attente;
    delete tps_service;
    delete donnees_clients;
    delete ok;
    delete layout;
    delete bic;
}

/**Méthode d'affichage de l'ordonnancement de la file**/
void DialogInfosQueue::setInfoOrdonnancement()
{
    //Créer pour récupérer le nom de l'ordonnancement de la file
    QString * ordo = new QString("<strong>Scheduling : </strong>");

    //Récupérer l'ordonnancement
    if(file->getOrdonnancement()==1)
      *ordo += "FIFO";
    else if(file->getOrdonnancement()==2)
      *ordo += "LIFO";
    else if(file->getOrdonnancement()==3)
      *ordo += "Priority";
    else
        *ordo+= "RANDOM";

    //Ajouter le résultat au label
    ordonnancement->setText(*ordo);

    delete ordo;
}

/**Méthode d'affichage de la loi de service de la file**/
void DialogInfosQueue::setInfoLoiService()
{
  //Créer pour récupérer le nom de la loi de service
  QString * service = new QString("<strong>Service distribution : </strong>");

  //Récupérer la loi de service
  if(file->getLoi_service()==-1)
    *service += "Exponential";
  else if(file->getLoi_service()==-2)
    *service += "Uniform";
  else
    *service += "Constant";

  //Ajouter le résultat au label correspondant
  loiService->setText(*service);

  delete service;
}

/**Méthode d'affichage du nombre de clients dans la file**/
void DialogInfosQueue::setInfoNbClients()
{
    //Créer pour récupérer le nombre de clients
    QString * nb_clients = new QString;
    QString * champ = new QString;

    //Récupérer le nombre de clients
    *champ += "<strong>Number of clients : </strong>";
    nb_clients->setNum(file->getNbClients());
    *champ += *nb_clients;

    //Ajouter le résultat au label
    nbClients->setText(*champ);

    delete nb_clients;
    delete champ;
}

/**Méthode d'affichage du nombre de clients servis de la file**/
void DialogInfosQueue::setInfoNbClientsServis()
{
  //Créer pour récupérer le nombre de clients servis
  QString * nb_clients_servis = new QString;
  QString * champ = new QString;

  //Récupérer le nombre de clients servis
  *champ += "<strong>Number of clients served : </strong>";
  nb_clients_servis->setNum(file->getNbClientsServis());
  *champ += *nb_clients_servis;

  //Ajouter le résultat au label
  nbClientsServis->setText(*champ);

  delete nb_clients_servis;
  delete champ;
}

/**Méthode d'affichage du nombre de clients s'étant présentés à la file**/
void DialogInfosQueue::setInfoNbClientsPresentes()
{
  //Créer pour récupérer le nombre de clients présentés
  QString * nb_clients_presentes = new QString;
  QString * champ = new QString;

  //Récupérer le nombre de clients présentés
  *champ += "<strong>Number of clients presented : </strong>";
  nb_clients_presentes->setNum(file->getNbClientsPresentes());
  *champ += *nb_clients_presentes;

  //Ajouter le résultat au label
  nbClientsPresentes->setText(*champ);

  delete nb_clients_presentes;
  delete champ;
}
/**Méthode d'affichage du nombre de clients n'étant pas entrés dans la file**/

void DialogInfosQueue::setInfoNbClientsPerdus()
{
  //Créer pour récupérer le nombre de clients perdus
  QString * nb_clients_perdus = new QString;
  QString * champ = new QString;

  //Récupérer le nombre de clients perdus
  *champ += "<strong>Number of clients lost : </strong>";
  nb_clients_perdus->setNum(file->getNbClientsPresentes()-file->getNbClientsEntres());
  *champ += *nb_clients_perdus;

  //Ajouter le résultat au label
  nbClientsPerdus->setText(*champ);

  delete nb_clients_perdus;
  delete champ;
}

/**Méthode d'affichage du nombre de serveurs de la file**/
void DialogInfosQueue::setNbServeurs()
{
  //Créer pour récupérer le nombre de serveurs
  QString * nb_serveurs = new QString;
  QString * champ = new QString;

  //Récupérer le nombre de serveurs
  *champ += "<strong>Number of servers : </strong>";
  nb_serveurs->setNum(file->getListeServeur().size());
  *champ += *nb_serveurs;

  //Ajouter le résultat au label
  nbServeurs->setText(*champ);

  delete nb_serveurs;
  delete champ;
}
