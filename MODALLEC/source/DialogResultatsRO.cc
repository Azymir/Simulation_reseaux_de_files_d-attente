#include "DialogResultatsRO.hh"

DialogResultatsRO::DialogResultatsRO(PerformancesRO * perfs, QDialog * parent):QDialog(parent),perfsRO(perfs)
{
  try
  {
    if(perfs == NULL) throw invalid_argument("Constructeur DialogResultatsRO : pointeur PerformancesRO à NULL");
		else
		{
      setMinimumSize(365,400);
      setMaximumSize(365,400);
      setWindowFlags(Qt::CustomizeWindowHint);
      // initialisation des variables QLabel (dynamique)
      debit_entree_reseau = new QLabel;
      debit_sortie_reseau = new QLabel;
      nb_moy_clients_reseau = new QLabel;
      tps_sejour_moy_reseau = new QLabel;
      tps_rep_moy_files = new QLabel;
      nb_moy_client_files = new QLabel;
      tps_attente_moy_files = new QLabel;
      tps_service_moy_files = new QLabel;
      tps_interarrivee_moy_files = new QLabel;
      taux_perte_files = new QLabel;
      taux_utilisation_serveurs = new QLabel;
      layout_affichage = new QVBoxLayout;
      // initialisation pour l'affichage de la scroll bar
      rangement_scroll = new QVBoxLayout;
      fenetre_affichage = new QWidget;
      scrollArea = new QScrollArea;
      scrollArea->setWidgetResizable(true);
      ok = new QPushButton("OK");// le bouton ok pour validé

      // positionnement dans le tableau de l'affichage
      layout_affichage->addWidget(nb_moy_clients_reseau);
      layout_affichage->addWidget(tps_rep_moy_files);
      layout_affichage->addWidget(tps_sejour_moy_reseau);
      layout_affichage->addWidget(debit_entree_reseau);
      layout_affichage->addWidget(debit_sortie_reseau);
      layout_affichage->addWidget(nb_moy_client_files);
      layout_affichage->addWidget(tps_attente_moy_files);
      layout_affichage->addWidget(tps_service_moy_files);
      layout_affichage->addWidget(tps_interarrivee_moy_files);
      layout_affichage->addWidget(taux_perte_files);
      layout_affichage->addWidget(taux_utilisation_serveurs);
      setLayout(layout_affichage);

      // affichage des resulats
      setInfoTpsSejourMoyReseau();
      setInfoDebitEntreeReseau();
      setInfoDebitSortieReseau();
      setInfoTpsRepMoyFiles();
      setInfoNbMoyClientsReseau();
      setInfoNbMoyClientsFiles();
      setInfoTpsAttenteMoyFiles();
      setInfoTpsServiceMoyFiles();
      setInfoTpsinterarriveeMoyFiles();
      setInfoTauxPerteFiles();
      setInfoTauxUtilisationServeurs();

      // le bouton ok pour validé
      connect(ok,SIGNAL(clicked()),this,SLOT(accept()));

      // affichage de la scroll bar
      fenetre_affichage->setLayout(layout_affichage);
      scrollArea->setWidget(fenetre_affichage);
      rangement_scroll->addWidget(scrollArea);
      rangement_scroll->addWidget(ok);
      setLayout(rangement_scroll);

      //Personnaliser la boîte de dialogue
			setStyleSheet("background-color :#C0C0C0;");
			ok->setStyleSheet("QPushButton{background-color: #B0C4DE;}""QPushButton:pressed{background-color: darkgrey;}");
    }
  }
  catch(string const& chaine){
		cerr << chaine <<endl;
	}
}

DialogResultatsRO::~DialogResultatsRO()
{
  delete nb_moy_clients_reseau;
  delete tps_rep_moy_files;
  delete tps_sejour_moy_reseau;
  delete debit_entree_reseau;
  delete debit_sortie_reseau;
  delete nb_moy_client_files;
  delete tps_attente_moy_files;
  delete tps_service_moy_files;
  delete tps_interarrivee_moy_files;
  delete taux_perte_files;
  delete taux_utilisation_serveurs;
  delete ok;
  delete layout_affichage;
  delete fenetre_affichage;
  delete scrollArea;
  delete rangement_scroll;

}

void DialogResultatsRO::setInfoTpsSejourMoyReseau()
{
  if(perfsRO != NULL)
  {
    QString * text = new QString("<strong>Average residence time in the network : </strong>");
    QString * num = new QString;
    num->setNum(perfsRO->perfReseau->getTpsSejourMoyen()); // convertion du nombre moyen de client en chaine de caractere
    *text += num; // ajout de la chaine dans le label qu'on affichera
    tps_sejour_moy_reseau->setText(*text);
    delete text;
    delete num;
  }
}

void DialogResultatsRO::setInfoTpsRepMoyFiles()
{
  if(perfsRO != NULL)
  {
    QString * text = new QString("<strong>Average response time per queue : </strong>"); // on crée une chaine de caractere
    QString * num = new QString;  // on initialise une nouvelle chaine qu'on va additionner à la précédente
    list<PerfsFile*>::iterator it;
    for(it = perfsRO->ListePerfsFiles.begin();it!=perfsRO->ListePerfsFiles.end();it++)
    {// on parcourt les performances du Reseau Ferme et on ajoute l'entier a la chaine, c'est le resulat
    	*text += "<br>Queue ";
    	num ->setNum((*it)->getFile().getIDFile());
    	*text += num;
    	*text += " : ";
    	num ->setNum((*it)->getTpsReponseMoy()); // modification d'un entier en un caractere
    	*text += num;
    }
    tps_rep_moy_files->setText(*text);

    delete text;
    delete num;
  }
}

void DialogResultatsRO::setInfoDebitEntreeReseau()
{
  if(perfsRO != NULL)
  {
    QString * text = new QString("<strong>Network input rate : </strong>");
    QString * num = new QString;
    num->setNum(perfsRO->perfReseau->getDebitEntree()); // convertion du nombre moyen de client en chaine de caractere
    *text += num; // ajout de la chaine dans le label qu'on affichera
    debit_entree_reseau->setText(*text);
    delete text;
    delete num;
  }
}
void DialogResultatsRO::setInfoDebitSortieReseau()
{
  if(perfsRO != NULL)
  {
    QString * text = new QString("<strong>Network output rate : </strong>");
    QString * num = new QString;
    num->setNum(perfsRO->perfReseau->getDebitSortie()); // convertion du nombre moyen de client en chaine de caractere
    *text += num; // ajout de la chaine dans le label qu'on affichera
    debit_sortie_reseau->setText(*text);
    delete text;
    delete num;
  }
}

void DialogResultatsRO::setInfoNbMoyClientsReseau()
{
  if(perfsRO != NULL)
  {
    QString * text = new QString("<strong>Average number of clients in the network : </strong>");
    QString * num = new QString;
    num->setNum(perfsRO->perfReseau->getNbMoyenClients()); // convertion du nombre moyen de client en chaine de caractere
    *text += num; // ajout de la chaine dans le label qu'on affichera
    nb_moy_clients_reseau->setText(*text);
    delete text;
    delete num;
  }
}

void DialogResultatsRO::setInfoNbMoyClientsFiles()
{
  if(perfsRO != NULL)
  {
    QString * text = new QString("<strong>Average number of customers per queue : </strong>");
    QString * num = new QString;
    list<PerfsFile*>::iterator it;
    for(it = perfsRO->ListePerfsFiles.begin();it!=perfsRO->ListePerfsFiles.end();it++)
    {
    	*text += "<br>Queue ";
    	num ->setNum((*it)->getFile().getIDFile());
    	*text += num;
    	*text += " : ";
    	num ->setNum((*it)->getNbMoyenClientsFile());
    	*text += num;
    }
    nb_moy_client_files->setText(*text);
    delete text;
    delete num;
  }
}

void DialogResultatsRO::setInfoTpsAttenteMoyFiles()
{
  if(perfsRO != NULL)
  {
    QString * text = new QString("<strong>Average waiting time per queue : </strong>");
    QString * num = new QString;
    list<PerfsFile*>::iterator it;
    for(it = perfsRO->ListePerfsFiles.begin();it!=perfsRO->ListePerfsFiles.end();it++)
    {
    	*text += "<br>Queue ";
    	num ->setNum((*it)->getFile().getIDFile());
    	*text += num;
    	*text += " : ";
    	num ->setNum((*it)->getTpsAttenteMoy());
    	*text += num;
    }
    tps_attente_moy_files->setText(*text);
    delete text;
    delete num;
  }
}

void DialogResultatsRO::setInfoTpsServiceMoyFiles()
{
  if(perfsRO != NULL)
  {
    QString * text = new QString("<strong>Average service time per queue : </strong>");
    QString * num = new QString;
    list<PerfsFile*>::iterator it;
    for(it = perfsRO->ListePerfsFiles.begin();it!=perfsRO->ListePerfsFiles.end();it++)
    {
    	*text += "<br>Queue ";
    	num ->setNum((*it)->getFile().getIDFile());
    	*text += num;
    	*text += " : ";
    	num ->setNum((*it)->getTpsServiceMoy());
    	*text += num;
    }
    tps_service_moy_files->setText(*text);
    delete text;
    delete num;
  }
}

void DialogResultatsRO::setInfoTpsinterarriveeMoyFiles()
{
  if(perfsRO != NULL)
  {
    QString * text = new QString("<strong>Average inter-arrival time per queue : </strong>");
    QString * num = new QString;
    list<PerfsFile*>::iterator it;
    for(it = perfsRO->ListePerfsFiles.begin();it!=perfsRO->ListePerfsFiles.end();it++)
    {
    	*text += "<br>Queue ";
    	num ->setNum((*it)->getFile().getIDFile());
    	*text += num;
    	*text += " : ";
    	num ->setNum((*it)->getTpsinterarriveeMoy());
    	*text += num;
    }
    tps_interarrivee_moy_files->setText(*text);
    delete text;
    delete num;
  }
}

void DialogResultatsRO::setInfoTauxPerteFiles()
{
  if(perfsRO != NULL)
  {
    QString * text = new QString("<strong>Loss rate per queue : </strong>");
    QString * num = new QString;
    list<PerfsFile*>::iterator it;
    for(it = perfsRO->ListePerfsFiles.begin();it!=perfsRO->ListePerfsFiles.end();it++)
    {
    	*text += "<br>Queue ";
    	num ->setNum((*it)->getFile().getIDFile());
    	*text += num;
    	*text += " : ";
    	num ->setNum((*it)->getTauxPerte());
    	*text += num;
    }
    taux_perte_files->setText(*text);
    delete text;
    delete num;
  }
}

void DialogResultatsRO::setInfoTauxUtilisationServeurs()
{
  if(perfsRO != NULL)
  {
    QString * text = new QString("<strong>Average inter-arrival time per queue : </strong>");
    QString * num = new QString;
    list<PerfsFile*>::iterator it;
    for(it = perfsRO->ListePerfsFiles.begin();it!=perfsRO->ListePerfsFiles.end();it++)
    {
      *text += "<br>Queue ";
  		num ->setNum((*it)->getFile().getIDFile());
  		*text += num;
  		*text += " : ";
  		list<PerfServeur>::iterator iserveur;
  		for(iserveur = ((*it)->getListeResPerfServeur()).begin();iserveur!=((*it)->getListeResPerfServeur()).end();iserveur++)
  		{
  			*text += "<br>  Server ";
  			num ->setNum((*iserveur).numero_serveur);
  			*text += num;
  			*text += " : ";
  			num ->setNum((*iserveur).taux_utilisation);
  			*text += num;
  		}
    }
    taux_utilisation_serveurs->setText(*text);
    delete text;
    delete num;
  }
}
