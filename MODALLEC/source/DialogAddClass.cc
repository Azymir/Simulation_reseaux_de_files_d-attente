#include "DialogAddClass.hh"

DialogAddClass::DialogAddClass(QWidget *parent) :
    QDialog(parent)
{
  //Retirer la barre du haut sur la boîte de dialogue
  setWindowFlags(Qt::CustomizeWindowHint);

    TitreRoutage = new QLabel("<strong> Routing : </strong>");
    TitrePriorite = new QLabel("<strong> Priority : </strong>");
    configRoutage = new QLineEdit;
    priorite = new QSpinBox;
    BoutonOk = new QPushButton("OK");

    configRoutage->setPlaceholderText("example : 1-2-11-5-7");
    priorite->setRange(0,9);

    //affichage de l'odre des label et edit
    Vlayout = new QVBoxLayout;
    Vlayout->addWidget(TitreRoutage);
    Vlayout->addWidget(configRoutage);
    Vlayout->addWidget(TitrePriorite);
    Vlayout->addWidget(priorite);
    Vlayout->addWidget(BoutonOk);
    setLayout(Vlayout);


    connect(BoutonOk,SIGNAL(clicked()),this,SLOT(accept()));

    //Personnaliser la boîte
    setStyleSheet("background-color: #C0C0C0;");
    BoutonOk->setStyleSheet(
    "QPushButton:pressed{background-color: darkgrey;}"
    "QPushButton{background-color: #B0C4DE;}"
    );
    configRoutage->setStyleSheet("background-color: white;");
    priorite->setStyleSheet("background-color: white;");
}

DialogAddClass::~DialogAddClass()
{
    delete Vlayout;
    delete TitreRoutage;
    delete TitrePriorite;
    delete configRoutage;
    delete priorite;
    delete BoutonOk;
}

int DialogAddClass::getPriorite()
{//renvoie l'entier entré sur la boite de dialogue
    return priorite->value();
}

string DialogAddClass::getRoutage()
{//renvoie la chaine de caractere entrée sur la boite de dialogue
    return configRoutage->text().toStdString();
}
