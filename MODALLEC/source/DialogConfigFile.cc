#include "DialogConfigFile.hh"

/**Constructeur
@param f, la file à configurer
@param parent, le widget parent de la boîte de dialogue
**/
DialogConfigFile::DialogConfigFile(File * f,QWidget * parent) : QDialog(parent)
{
  try
  {
    if(f == NULL) throw invalid_argument("Constructeur DialogConfigFile : pointeur File à NULL");
    else
    {
      //Retirer la barre du haut sur la boîte de dialogue
      setWindowFlags(Qt::CustomizeWindowHint);

      //Initialiser les attributts de la classe
      file_a_config = f;
      layout = new QVBoxLayout;
      LoiArrivee = new QLabel;
      LoiService = new QLabel;
      Ordonnancement = new QLabel;
      TailleMax = new QLabel;
      NbServeurs = new QLabel;
      newLoiArrivee = new QComboBox;
      newLoiService = new QComboBox;
      newOrdonnancement = new QComboBox;
      newTailleMax = new QSpinBox;
      newNbServeurs = new QSpinBox;
      ok = new QPushButton("OK");
      annuler = new QPushButton("Annuler");

      //Ajouter les choix possibles dans les boîtes à choix
      newLoiArrivee->addItem("Poisson");
      newLoiArrivee->addItem("Constant");
      newOrdonnancement->addItem("FIFO");
      newOrdonnancement->addItem("LIFO");
      newOrdonnancement->addItem("Priority");
      newOrdonnancement->addItem("Random");
      newLoiService->addItem("Exponential");
      newLoiService->addItem("Constant");
      newLoiService->addItem("Uniform");

      //Initialiser l'intervalle d'entiers pour les boîtes à choix d'entiers
      newTailleMax->setRange(1,10000);
      newNbServeurs->setRange(1,10);

      //Définir la taille des boutons
      ok->setFixedWidth(width()/2);
      annuler->setFixedWidth(width()/2);

      //Connecter les boutons à leur slot
      connect(ok,SIGNAL(clicked()),this,SLOT(accept()));
      connect(annuler,SIGNAL(clicked()),this,SLOT(reject()));

      //Ajouter les objets à la boîte de rangement de la boîte de dialogue
      layout->addWidget(LoiArrivee);
      layout->addWidget(newLoiArrivee);
      layout->addWidget(LoiService);
      layout->addWidget(newLoiService);
      layout->addWidget(Ordonnancement);
      layout->addWidget(newOrdonnancement);
      layout->addWidget(TailleMax);
      layout->addWidget(newTailleMax);
      layout->addWidget(NbServeurs);
      layout->addWidget(newNbServeurs);
      layout->addWidget(ok);
      layout->addWidget(annuler);

      //Ajouter la boîte de rangement à la boîte de dialogue
      setLayout(layout);

      //Afficher l'ancienne configuration de la file
      QString * arrivee = new QString ("<strong> Arrival distribution : </strong> <br>");
      QString * service = new QString("<strong> Service distribution : </strong> <br>");
      QString * ordo= new QString("<strong> Scheduling : </strong> <br>");
      QString * taille = new QString("<strong>  Maximum size : </strong> <br>");
      QString * nbServeurs = new QString("<strong> Number of servers : </strong> <br>");
      QString * nombre = new QString;

      //Pour la distribution d'arrivée
      if(file_a_config->getDistribution_arrivee()==-1) *arrivee += "Poisson";
      else *arrivee += "Constant";

      LoiArrivee->setText(*arrivee);

      //Pour la loi de service
      if(file_a_config->getLoi_service()==-1) *service += "Exponential";
      else if (file_a_config->getLoi_service()==-2) *service += "Uniform";
      else *service += "Constant";

      LoiService->setText(*service);

      //Pour l'ordonnancement
      if(file_a_config->getOrdonnancement()==1) *ordo += "FIFO";
      else if (file_a_config->getOrdonnancement()==2) *ordo += "LIFO";
      else if (file_a_config->getOrdonnancement()==3) *ordo += "Priority";
      else *ordo += "RANDOM";

      Ordonnancement->setText(*ordo);

      //Pour la taille
      nombre->setNum(file_a_config->getTailleMax());
      *taille += nombre;

      TailleMax->setText(*taille);

      //Pour le nombre de serveurs
      nombre->setNum(file_a_config->getListeServeur().size());
      *nbServeurs += nombre;

      NbServeurs->setText(*nbServeurs);

      //Personnaliser la boîte de dialogue
      setStyleSheet("background-color: #C0C0C0;");
      ok->setStyleSheet(
      "QPushButton:pressed{background-color: darkgrey;}"
      "QPushButton{background-color: #B0C4DE;}"
      );
      annuler->setStyleSheet(
      "QPushButton:pressed{background-color: darkgrey;}"
      "QPushButton{background-color: #B0C4DE;}"
      );
      newLoiArrivee->setStyleSheet("background-color: lightgrey;");
      newLoiService->setStyleSheet("background-color: lightgrey;");
      newOrdonnancement->setStyleSheet("background-color: lightgrey;");
      newTailleMax->setStyleSheet("background-color: lightgrey;");
      newNbServeurs->setStyleSheet("background-color: lightgrey;");

      delete arrivee;
      delete service;
      delete ordo;
      delete nombre;
      delete taille;
      delete nbServeurs;
    }
  }
  catch(string const& chaine){
		cerr << chaine <<endl;
	}
}

/**Destructeur**/
DialogConfigFile::~DialogConfigFile()
{
  delete LoiArrivee;
  delete LoiService;
  delete Ordonnancement;
  delete TailleMax;
  delete NbServeurs;
  delete newLoiArrivee;
  delete newLoiService;
  delete newOrdonnancement;
  delete newTailleMax;
  delete newNbServeurs;
  delete ok;
  delete annuler;
  delete layout;
}

/** Méthode de récupération de la valeur de distribution d'arrivée entrée par l'utilisateur
@return string correspondant à la distribution d'arrivée
**/
string DialogConfigFile::recuperer_valeur_newLoiArrivee()
{
  return newLoiArrivee->currentText().toStdString();
}

/** Méthode de récupération de la valeur de loi de service entrée par l'utilisateur
@return string correspondant à la loi de service
**/
string DialogConfigFile::recuperer_valeur_newLoiService()
{
  return newLoiService->currentText().toStdString();
}

/** Méthode de récupération de l'ordonnancement entrée par l'utilisateur
@return string correspondant à la valeur de l'ordonnancement
**/
string DialogConfigFile::recuperer_valeur_newOrdonnancement()
{
  return newOrdonnancement->currentText().toStdString();
}

/** Méthode de récupération de la valeur de la taille de maximale de la file entrée par l'utilisateur
@return int correspondant à la valeur de la taille maximale de la file
**/
int DialogConfigFile::recuperer_valeur_newTailleMax()
{
  return newTailleMax->value();
}

/** Méthode de récupération de la valeur du nombre de serveurs entrée par l'utilisateur
@return int correspondant à la valeur du nombre de serveurs
**/
int DialogConfigFile::recuperer_valeur_newNbServeurs()
{
  return newNbServeurs->value();
}
