#include "DialogInfosClass.hh"

DialogInfosClass::DialogInfosClass(ClasseClient * cc,QWidget * parent) : QDialog(parent)
{
  try
  {
    /* Constructeur prennant en parametre une pointeur ClasseClient qui nous permet de recuperer
    les informations des ClasseClient */
    if(cc == NULL) throw invalid_argument("Constructeur DialogConfigFile : pointeur ClasseClient à NULL");
    else
    {
      setWindowFlags(Qt::CustomizeWindowHint);
      setMaximumSize(250,300);
      classe_client = cc;
      priorite = new QLabel;
      routage = new QLabel;
      layout = new QVBoxLayout;
      ok = new QPushButton("OK");
      layout->addWidget(priorite);
      layout->addWidget(routage);
      layout->addWidget(ok);

      setInfoPriorite();
      setInfoRoutage();

      connect(ok,SIGNAL(clicked()),this,SLOT(accept()));

      setLayout(layout);

      //Personnaliser la boîte de dialogue
      setStyleSheet("background-color: #C0C0C0;");
      priorite->setStyleSheet("background-color: #B0C4DE; border-style: inset; border-radius: 1px; border-width: 1px; border-color: darkgrey;");
      routage->setStyleSheet("background-color: #B0C4DE; border-style: inset; border-radius: 1px; border-width: 1px; border-color: darkgrey;");
      ok->setStyleSheet(
      "QPushButton:pressed{background-color: darkgrey;}"
      "QPushButton{background-color: #B0C4DE;}"
      );
    }
  }
  catch(string const& chaine){
		cerr << chaine <<endl;
	}
}

/* Destructeur */
DialogInfosClass::~DialogInfosClass(){
	delete priorite;
	delete routage;
	delete ok;
	delete layout;

}

void DialogInfosClass::setInfoPriorite(){// on renvoie la priorité de la ClasseClient en string
	QString * priorite_classe = new QString("<strong> Priority : </strong>");// Initialiser le string text
  QString * num_priorite = new QString;// Initialiser le string num_priorite
  num_priorite->setNum(classe_client->getPriorite());// transformer un entier en un string
	*priorite_classe += num_priorite;//ajouter le string au text

  priorite->setText(*priorite_classe);// renvoyer la phrase
  delete priorite_classe;
  delete num_priorite;

}

void DialogInfosClass::setInfoRoutage(){
	QString * Routage = new QString("<strong> Routing : </strong>"); // Initialiser un QString qu'on va renvoyer

  if(classe_client->getRoutage().empty())
  {// si la classe est vide on renvoei rien
    *Routage += "No routing";
    routage->setText(*Routage);
  }
  else
  {// si la classe remplit alors on parcour la structure pour recuperer les informations
    QString * id_file = new QString;// Initialiser le string id_file
    std::vector<int> id_files = classe_client->getRoutage();// Initialiser la liste
    std::vector<int>::iterator it_files;// iterator permettant de ce deplacer dans la liste

    for(it_files = id_files.begin();it_files<id_files.end();++it_files){
        *Routage += "- File ";
        id_file->setNum(*it_files); // transformer un entier en un string
        *Routage += id_file;//ajouter le string au text
        *Routage += ("\n");
    }

    routage->setText(*Routage);// renvoyer la phrase
    delete id_file;
  }
  delete Routage;
}
