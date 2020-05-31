#include "FenetreEcheancier.hh"

/**Slot affichant les informations de l'évènement suivant l'évènement actuelle
@param ech, adresse de l'échéancier contenant les informations à afficher
@param parent, widget parent de la fenêtre
**/
FenetreEcheancier::FenetreEcheancier(Echeancier * ech,QWidget * parent):QWidget(parent), echeancier(ech)
{
  try
  {
    if(ech == NULL) throw invalid_argument("Constructeur FenetreEcheancier : pointeur Echeancier à NULL");
    else
    {
      //Retirer la barre du haut de la fenêtre
      setWindowFlags(Qt::CustomizeWindowHint);

      //Délimiter la taille de la fenêtre
      setFixedHeight(200);

      //Initialiser les attributs de la classe
      position_echeancier = 1;
      date_actuelle = new QLabel;
      date_evenement = new QLabel;
      file_concernee = new QLabel;
      serveur_concerne = new QLabel;
      client_concerne = new QLabel;
      rangement_echeancier = new QVBoxLayout;
      suivant = new QPushButton("Previous");
      precedent = new QPushButton("Next");

      //Connecter les boutons à leur slot
      connect(precedent,SIGNAL(clicked()),this,SLOT(evenement_precedent()));
      connect(suivant,SIGNAL(clicked()),this,SLOT(evenement_suivant()));

      //Afficher les données des évènements
      setInfoDate();
      setInfoClient();
      setInfoFile();
      setInfoServeur();
      setDateActuelle();

      //Ajouter les objets à la boîte de rangement de la fenêtre
      rangement_echeancier->addWidget(date_actuelle);
      rangement_echeancier->addWidget(date_evenement);
      rangement_echeancier->addWidget(file_concernee);
      rangement_echeancier->addWidget(serveur_concerne);
      rangement_echeancier->addWidget(client_concerne);
      rangement_echeancier->addWidget(suivant);
      rangement_echeancier->addWidget(precedent);

      //Enlever la marge entre le layout et la fenêtre
      rangement_echeancier->setContentsMargins(0,0,0,0);

      //Ajouter la boîte de rangement à la boîte de dialogue
      setLayout(rangement_echeancier);

      //Personnaliser la fenêtre
      setStyleSheet("background-color :#B0C4DE; border-style: inset; border-radius: 10px; border-width: 1px; border-color: darkgrey;");
      suivant->setStyleSheet("QPushButton:pressed{background-color: darkgrey;}");
      precedent->setStyleSheet("QPushButton:pressed{background-color: darkgrey;}");
    }
  }
  catch(string const& chaine){
		cerr << chaine <<endl;
	}
}

/**Destructeur**/
FenetreEcheancier::~FenetreEcheancier()
{
  delete date_actuelle;
  delete date_evenement;
  delete file_concernee;
  delete serveur_concerne;
  delete client_concerne;
  delete suivant;
  delete precedent;
  delete rangement_echeancier;
}

/**Slot affichant les informations de l'évènement précédent l'évènement actuelle**/
void FenetreEcheancier::evenement_precedent()
{
  //Changer d'évènement uniquement si il existe un évènement précédent
  if(position_echeancier > 1) position_echeancier --;

  //Afficher les données de l'évènement
  setDateActuelle();
  setInfoDate();
  setInfoFile();
  setInfoClient();
  setInfoServeur();

}

/**Slot affichant les informations de l'évènement suivant l'évènement actuelle**/
void FenetreEcheancier::evenement_suivant()
{
  //Changer d'évènement uniquement si il existe un évènement suivant
  if(position_echeancier < (int)echeancier->getListeEvenement().size()) position_echeancier ++;

  //Afficher les données de l'évènement
  setDateActuelle();
  setInfoDate();
  setInfoFile();
  setInfoClient();
  setInfoServeur();
}

/**Méthode d'affichage de la date de l'évènement**/
void FenetreEcheancier::setInfoDate()
{
  //Créer pour initialiser le label d'affichage
  QString * nom_champ = new QString("<strong> Event date : </strong>"),
  *date = new QString,
  *current_date = new QString;

  //Compte le nombre d'événements défilés
  int cmp = 1;

  //Itérer sur la liste d'évènements de l'échéancier
  list<Evenement>::iterator i;

  //Si l'échéancier n'est pas vide
  if(!echeancier->getListeEvenement().empty())
  {
    //Défiler la liste d'évènements
    for(i = echeancier->getListeEvenement().begin(); i!= echeancier->getListeEvenement().end(); i++)
    {
      //Si l'évènement correspond à la position demandée
      if(cmp == position_echeancier) break;
      cmp++;
    }

    if((*i).date_traitement >= 2000) *current_date = "";
    else
    //Récupérer la date de traitement de l'évènement
    current_date->setNum((*i).date_traitement);

    *nom_champ += *current_date;
  }

  //Ajouter le résultat au label
  date_evenement->setText(*nom_champ);

  delete date;
  delete nom_champ;
  delete current_date;
}

/**Méthode d'affichage du client participant à l'évènement*/
void FenetreEcheancier::setInfoClient()
{
  //Créer pour initialiser le label d'affichage
  QString * nom_champ = new QString("<strong>Customer :</strong> "),
  *num_client = new QString;

  //Compter le nombre d'évènements défilés
  int cmp = 1;

  //Itérer sur la liste d'évènements
  list<Evenement>::iterator i;

  //Si la liste n'est pas vide
  if(!echeancier->getListeEvenement().empty())
  {
    //Défiler la liste d'évènements
    for(i = echeancier->getListeEvenement().begin(); i!= echeancier->getListeEvenement().end(); i++)
    {
      //Arrêter de defiler la liste si la position de l'évènement correspond
      if(cmp == position_echeancier) break;
      cmp++;
    }

    //Récupérer le numéro du client
    num_client->setNum((*i).client->getID_client());
    *nom_champ += *num_client;
  }

  //Ajouter le résultat au label
  client_concerne->setText(*nom_champ);

  delete nom_champ;
  delete num_client;
}

/**Méthode d'affichage de la file participant à l'évènement**/
void FenetreEcheancier::setInfoFile()
{
  //Créer pour initialiser le label d'affichage
  QString * nom_champ = new QString("<strong>Queue : </strong>"),
  *num_file = new QString;

  //Compter le nombre d'évènements défilés
  int cmp = 1;

  //Itérer sur la liste d'évènement
  list<Evenement>::iterator i;

  //Si l'échéancier n'est pas vide
  if(!echeancier->getListeEvenement().empty()){

    //Défiler la liste d'évènements
    for(i = echeancier->getListeEvenement().begin(); i!= echeancier->getListeEvenement().end(); i++)
    {
      //Arrêter de defiler la liste si la position de l'évènement correspond
      if(cmp == position_echeancier) break;
      cmp++;
    }

    //Récupérer le numéro de la file concernée
    num_file->setNum((*i).file_destinee->getIDFile());
    *nom_champ += *num_file;
  }

  //Ajouter le résultat au label
  file_concernee->setText(*nom_champ);

  delete nom_champ;
  delete num_file;
}

/**Méthode d'affichage du serveur participant à l'évènement**/
void FenetreEcheancier::setInfoServeur()
{
  //Créer pour initialiser le label d'affichage
  QString * nom_champ = new QString("<strong>Server : </strong>"),
  *num_serveur = new QString;

  //Compter le nombre d'évènements à défiler
  int cmp = 1;

  //Itérer sur la liste d'évènements
  list<Evenement>::iterator i;

  //Si la liste d'évènements n'est pas vide
  if(!echeancier->getListeEvenement().empty())
  {
    //Défiler la liste d'évènements
    for(i = echeancier->getListeEvenement().begin(); i!= echeancier->getListeEvenement().end(); i++)
    {
      //Arrêter de defiler la liste si la position de l'évènement correspond
      if(cmp == position_echeancier) break;
      cmp++;
    }

    //Récupérer le numéro du serveur concerné
    if((*i).serveur_destine != NULL)
    {
		num_serveur->setNum((*i).serveur_destine->getIDServeur());
		*nom_champ += *num_serveur;
	}
	else
    {
		*nom_champ += "";
	}
  }

  //Ajouter le résultat au label
  serveur_concerne->setText(*nom_champ);

  delete nom_champ;
  delete num_serveur;
}

/**Méthode d'affichage de la date actuelle se trouve l'échéancier**/
void FenetreEcheancier::setDateActuelle()
{
  //Créer pour initialiser le label d'affichage
  QString * nom_champ = new QString("<strong>Current date : </strong>"),
  * current_date = new QString;

  //Si la liste d'évènements n'est pas vide
  if(!echeancier->getListeEvenement().empty())
  {
    //Récupérer le date actuelle de l'horloge
    current_date->setNum(echeancier->getDateActuelle());
    *nom_champ += *current_date;
  }

  //Ajouter le résultat au label
  date_actuelle->setText(*nom_champ);


  delete nom_champ;
  delete current_date;
}

/**Méthode remettant à jour l'évènement actuelle par rapport à la position 0 dans l'échéancier*/
void FenetreEcheancier::maj_position()
{
  position_echeancier = 1;

  //Afficher les données de l'évènement
  setDateActuelle();
  setInfoDate();
  setInfoFile();
  setInfoClient();
  setInfoServeur();
}
