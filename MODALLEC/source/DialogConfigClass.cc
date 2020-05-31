#include "DialogConfigClass.hh"

DialogConfigClass::DialogConfigClass(ClasseClient *cc,QWidget *parent) : QDialog(parent)
{
  try{
    if(cc == NULL) throw invalid_argument("Constructeur DialogConfigClass : pointeur ClasseClient à NULL");
    else
    {
      //Retirer la barre du haut sur la boîte de dialogue
      setWindowFlags(Qt::CustomizeWindowHint);

      configRoutageLabel = new QLabel;
      prioriteLabel = new QLabel;
      configRoutage = new QLineEdit;
      priorite = new QSpinBox;
      BoutonOk = new QPushButton("OK");
      BoutonAnnuler = new QPushButton("Annuler");
      Vlayout = new QVBoxLayout;

      priorite->setMinimum(0);

      //Afficher l'ancien routage
      QString oldRout("<strong> Routing : </strong> <br> ");
      QString id;

      for(int i = 0; i< (int)cc->getRoutage().size(); i++){
        //Si il ne s'agit pas du dernier ID du routage
        if(i != (int)cc->getRoutage().size()-1){
          //Transformer l'identifiant en QString
          id.setNum(cc->getRoutage()[i]);
          //Ajouter à la chaîne le numéro de la file
          oldRout += id;
          oldRout += " - ";
        }
        else {
          id.setNum(cc->getRoutage()[i]);
          oldRout += id;
        }
      }

      //Afficher le nom du champ et l'ancien routage
      configRoutageLabel->setText(oldRout);

      //Placer un exemple de routage
      configRoutage->setPlaceholderText("example : 1-2-11-5-7");

      //Afficher l'ancienne priorité
      QString oldPriority("<strong> Priority : </strong> <br>");
      QString nombre;

      //Transformer l'entier en QString
      nombre.setNum(cc->getPriorite());
      oldPriority += nombre;

      prioriteLabel->setText(oldPriority);

      Vlayout->addWidget(configRoutageLabel);
      Vlayout->addWidget(configRoutage);
      Vlayout->addWidget(prioriteLabel);
      Vlayout->addWidget(priorite);
      Vlayout->addWidget(BoutonOk);
      Vlayout->addWidget(BoutonAnnuler);
      setLayout(Vlayout);

      connect(BoutonOk,SIGNAL(clicked()),this,SLOT(accept()));
      connect(BoutonAnnuler,SIGNAL(clicked()),this,SLOT(reject()));

      //Personnaliser la boîte de dialogue
      setStyleSheet("background-color: #C0C0C0;");
      BoutonOk->setStyleSheet(
      "QPushButton:pressed{background-color: darkgrey;}"
      "QPushButton{background-color: #B0C4DE;}"
      );
      BoutonAnnuler->setStyleSheet(
      "QPushButton:pressed{background-color: darkgrey;}"
      "QPushButton{background-color: #B0C4DE;}"
      );
      configRoutage->setStyleSheet("background-color: white;");
      priorite->setStyleSheet("background-color: white;");
    }
  }
  catch(string const& chaine){
		cerr << chaine <<endl;
	}
}

DialogConfigClass::~DialogConfigClass()
{
    delete Vlayout;
    delete configRoutageLabel;
    delete prioriteLabel;
    delete configRoutage;
    delete priorite;
    delete BoutonOk;
    delete BoutonAnnuler;

}

int DialogConfigClass::getPriorite()
{
    return priorite->value();
}

string DialogConfigClass::getRoutage()
{
    return configRoutage->text().toStdString();
}
