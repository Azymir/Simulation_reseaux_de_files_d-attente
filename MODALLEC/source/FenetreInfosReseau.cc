#include "FenetreInfosReseau.hh"

/**Constructeur
@param r, l'adresse du réseau dont les données sont à afficher
@param parent, le widget parent de la fenêtre
**/
FenetreInfosReseau::FenetreInfosReseau(Reseau * r, QWidget * parent):QWidget(parent)
{
  try
  {
    if(r == NULL) throw invalid_argument("Constructeur FenetreInfosReseau : pointeur Reseau à NULL");
    else
    {
      //Retirer la barre du haut de la fenêtre
      setWindowFlags(Qt::CustomizeWindowHint);

      //Initialiser les attributs de la classe
      reseau = r;
      rangement = new QVBoxLayout;
      nbClientsActuel = new QLabel;
      nbClientsPasses = new QLabel;
      nbClasses = new QLabel;
      nbClientsClasse = new QLabel;
      typeReseau = new QLabel;
      rangement_scroll = new QVBoxLayout;
      scrollArea = new QScrollArea;
      fenetre_affichage = new QWidget;

      //Délimiter la taille de la fenêtre défilable
      fenetre_affichage->setMinimumHeight(300);
      fenetre_affichage->setMaximumHeight(300);

      //Délimtier la fenêtre d'informations sur le réseau
      setMinimumHeight(300);
      setMaximumHeight(300);

      //Afficher les données du réseau
      setInfoNbClientsActuel();
      setInfoNbClientsPasses();
      setInfoNbClasses();
      setInfoNbClientsClasse();
      setInfoTypeReseau();

      //Ajouter les objets à la boîte de rangement
      rangement->addWidget(typeReseau);
      rangement->addWidget(nbClientsActuel);
      rangement->addWidget(nbClientsPasses);
      rangement->addWidget(nbClasses);
      rangement->addWidget(nbClientsClasse);

      //Enlever la marge entre le layout et la fenêtre
      rangement->setContentsMargins(2,0,0,0);

      //Ajouter la boîte de rangement à la fenêtre qui sera défilable
      fenetre_affichage->setLayout(rangement);

      //Ajouter la fenêtre dans la zone défilable
      scrollArea->setWidget(fenetre_affichage);

      //Ajouter la zone à une boîte de rangement
      rangement_scroll->addWidget(scrollArea);

      //Ajouter la boîte de rangement à la fenêtre
      setLayout(rangement_scroll);

      //Personnaliser la fenêtre
      nbClientsActuel->setStyleSheet("background-color: #B0C4DE; border-style: inset; border-radius: 1px; border-width: 1px; border-color: darkgrey;");
      nbClientsPasses->setStyleSheet("background-color: #B0C4DE; border-style: inset; border-radius: 1px; border-width: 1px; border-color: darkgrey;");
      nbClasses->setStyleSheet("background-color: #B0C4DE; border-style: inset; border-radius: 1px; border-width: 1px; border-color: darkgrey;");
      nbClientsClasse->setStyleSheet("background-color: #B0C4DE; border-style: inset; border-radius: 1px; border-width: 1px; border-color: darkgrey;");
      typeReseau->setStyleSheet("background-color: #B0C4DE; border-style: inset; border-radius: 1px; border-width: 1px; border-color: darkgrey;");
      scrollArea->setStyleSheet("background-color: #C0C0C0;");
    }
  }
  catch(string const& chaine){
		cerr << chaine <<endl;
	}

}

/**Destructeur**/
FenetreInfosReseau::~FenetreInfosReseau()
{
  delete nbClientsActuel;
  delete nbClientsPasses;
  delete nbClasses;
  delete nbClientsClasse;
  delete typeReseau;
  delete rangement;
  delete fenetre_affichage;
  delete scrollArea;
  delete rangement_scroll;
}

/**Méthode d'affichage du nombre de clients actuellement dans le réseau**/
void FenetreInfosReseau::setInfoNbClientsActuel()
{
  //Créer pour initialiser le label d'affichage
  QString * nom_champ = new QString("<strong> Number of <br> clients : </strong>");
  QString * nombre = new QString();

  //Récupérer le nombre de clients du réseau
  nombre->setNum(reseau->getNbClients());
  *nom_champ += *nombre;

  //Ajouter le résultat au label
  nbClientsActuel->setText(*nom_champ);

  delete nom_champ;
  delete nombre;
}

/**Méthode d'affichage du nombre de clients passés dans le réseau**/
void FenetreInfosReseau::setInfoNbClientsPasses()
{
  //Créer pour initialiser le label d'affichage
  QString * nom_champ = new QString("<strong>Number of <br> past clients : </strong> <br>");
  QString * nombre = new QString;

  //Récupérer le nombre de clients passés dans le réseau
  nombre->setNum(reseau->getNbClientsPasses());
  *nom_champ += *nombre;

  //Ajouter le résultat au label
  nbClientsPasses->setText(*nom_champ);

  delete nom_champ;
  delete nombre;
}

/**Méthode d'affichage du nombre de classes dans le réseau**/
void FenetreInfosReseau::setInfoNbClasses()
{
  //Créer pour initialiser le label d'affichage
  QString * nom_champ = new QString("<strong>Number of <br> classes : </strong>");
  QString * nombre = new QString;

  //Récupérer le nombre de classes
  nombre->setNum(reseau->getNbClasses());
  *nom_champ += *nombre;

  //Ajouter le résultat au label
  nbClasses->setText(*nom_champ);

  delete nom_champ;
  delete nombre;
}

/**Méthode d'affichage du nombre de clients par classe dans le réseau**/
void FenetreInfosReseau::setInfoNbClientsClasse()
{
  //Créer pour initialiser le label d'affichage
  QString * nom_champ = new QString("<strong>Number of <br> clients by <br> class :</strong> <br>");
  QString * donnees_classes = new QString
  ,* donnee_classe = new QString
  ,* nbClients = new QString
  ,* text_classe = new QString;

  //Conceténer l'ensemble des données des classes du réseau
  for(auto i = reseau->getListeClasseClient().begin(); i!=reseau->getListeClasseClient().end(); i++)
  {
    //Récupérer les données de la classe

    //Récupérer le numéro de la classe
    donnee_classe->setNum((*i)->getIDClasseClient());
    //Récupérer le nombre de clients de la classe
    nbClients->setNum((*i)->getNbClients());
    *text_classe ="Class ";
    *donnees_classes += *text_classe;
    *donnees_classes += *donnee_classe;
    *text_classe =" : ";
    *donnees_classes += *text_classe;
    *donnees_classes += *nbClients;
    *donnees_classes += "<br>";
  }

  *nom_champ += donnees_classes;

  //Ajouter le résultat au label
  nbClientsClasse->setText(*nom_champ);

  delete nom_champ;
  delete donnees_classes;
  delete donnee_classe;
  delete nbClients;
  delete text_classe;
}

/**Méthode d'affichage du type du réseau**/
void FenetreInfosReseau::setInfoTypeReseau()
{
  //Créer pour initialiser le label
  QString * nom_champ = new QString("<strong> Network type : </strong> <br>");

  //Récupérer le type du réseau correspondant
  if(reseau->getTypeReseau()==0)
    *nom_champ += "Closed";
  else
    *nom_champ += "Opened";

  //Ajouter le résultat au label
  typeReseau->setText(*nom_champ);

  delete nom_champ;
}
