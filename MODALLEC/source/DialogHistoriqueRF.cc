#include "DialogHistoriqueRF.hh"


DialogHistoriqueRF::DialogHistoriqueRF(HistoriqueRF * h,QWidget * parent) : QDialog(parent){

	try
	{
		if(h == NULL) throw invalid_argument("Constructeur DialogConfigFile : pointeur HistoriqueRF à NULL");
		else
		{
			setWindowFlags(Qt::CustomizeWindowHint);
			setMinimumSize(365,400);
      setMaximumSize(365,400);
		  histo = h;
		  position_historique = 0;
			tps_rep_moy_reseau = new QLabel;
			nb_moy_clients_reseau = new QLabel;
			nb_moy_clients_files = new QLabel;
			tps_attente_moy_files = new QLabel;
			tps_service_moy_files = new QLabel;
			tps_interarrivee_moy_files = new QLabel;
			taux_perte_files = new QLabel;
			taux_utilisation_serveurs = new QLabel;
			date = new QLabel;
			layout_affichage = new QVBoxLayout;
			rangement_scroll = new QVBoxLayout;
			scrollArea = new QScrollArea;
			scrollArea->setWidgetResizable(true);
			fenetre_affichage = new QWidget;
			ok = new QPushButton("OK");
			suivant = new QPushButton("Next");
			precedent = new QPushButton("Previous");

			precedent->setDisabled(true);
			if((histo->getHistorique()).size()<=1)
				suivant->setDisabled(true);

			layout_affichage->addWidget(date);
			layout_affichage->addWidget(tps_rep_moy_reseau);
			layout_affichage->addWidget(nb_moy_clients_reseau);
			layout_affichage->addWidget(nb_moy_clients_files);
			layout_affichage->addWidget(tps_attente_moy_files);
			layout_affichage->addWidget(tps_service_moy_files);
			layout_affichage->addWidget(tps_interarrivee_moy_files);
			layout_affichage->addWidget(taux_perte_files);
			layout_affichage->addWidget(taux_utilisation_serveurs);

			setInfoDate();

		  	if((histo->getHistorique()).size()!=0){
			  	setInfoTpsRepMoyReseau();
				setInfoNbMoyClientsReseau();
				setInfoNbMoyClientsFiles();
				setInfoTpsAttenteMoyFiles();
				setInfoTpsServiceMoyFiles();
				setInfoTpsinterarriveeMoyFiles();
				setInfoTauxPerteFiles();
				setInfoTauxUtilisationServeurs();
			}

		  connect(ok,SIGNAL(clicked()),this,SLOT(accept()));
		  connect(suivant,SIGNAL(clicked()),this,SLOT(perf_suivante()));
		  connect(precedent,SIGNAL(clicked()),this,SLOT(perf_precedent()));

		  fenetre_affichage->setLayout(layout_affichage);
		  scrollArea->setWidget(fenetre_affichage);
		  rangement_scroll->addWidget(scrollArea);
			rangement_scroll->addWidget(precedent);
			rangement_scroll->addWidget(suivant);
			rangement_scroll->addWidget(ok);
		  setLayout(rangement_scroll);

			//Personnaliser la boîte de dialogue
			setStyleSheet("background-color :#C0C0C0;");
      suivant->setStyleSheet("QPushButton{background-color: #B0C4DE;}""QPushButton:pressed{background-color: darkgrey;}");
      precedent->setStyleSheet("QPushButton{background-color: #B0C4DE;}""QPushButton:pressed{background-color: darkgrey;}");
			ok->setStyleSheet("QPushButton{background-color: #B0C4DE;}""QPushButton:pressed{background-color: darkgrey;}");
		}
	}
	catch(string const& chaine){
		cerr << chaine <<endl;
	}
}

DialogHistoriqueRF::~DialogHistoriqueRF(){
	delete tps_rep_moy_reseau;
	delete nb_moy_clients_reseau;
	delete nb_moy_clients_files;
	delete tps_attente_moy_files;
	delete tps_service_moy_files;
	delete tps_interarrivee_moy_files;
	delete taux_perte_files;
	delete taux_utilisation_serveurs;
	delete date;
	delete ok;
	delete suivant;
	delete precedent;
	delete layout_affichage;
	delete fenetre_affichage;
	delete scrollArea;
	delete rangement_scroll;



}

void DialogHistoriqueRF::perf_suivante(){
	position_historique += 1;
	int taille = (int) histo->getHistorique().size() - 1;
	if(position_historique == taille)
		suivant->setDisabled(true); //desactiver le bouton suivant si on est dans la dernière page
	setInfoDate();
  	setInfoTpsRepMoyReseau();
	setInfoNbMoyClientsReseau();
	setInfoNbMoyClientsFiles();
	setInfoTpsAttenteMoyFiles();
	setInfoTpsServiceMoyFiles();
	setInfoTpsinterarriveeMoyFiles();
	setInfoTauxPerteFiles();
	setInfoTauxUtilisationServeurs();
	precedent->setDisabled(false);//réactiver le bouton précédent car il existe une perf précédente étant donné qu'on a cliqué sur suivant


}

void DialogHistoriqueRF::perf_precedent(){
	position_historique -= 1;
	suivant->setDisabled(false); //réactiver le bouton suivant car il existe une perf suivante étant donné qu'on a cliqué sur précédente
	if(position_historique == 0)
		precedent->setDisabled(true); //desactiver le bouton précédente si on est dans la première page
	setInfoDate();
  	setInfoTpsRepMoyReseau();
	setInfoNbMoyClientsReseau();
	setInfoNbMoyClientsFiles();
	setInfoTpsAttenteMoyFiles();
	setInfoTpsServiceMoyFiles();
	setInfoTpsinterarriveeMoyFiles();
	setInfoTauxPerteFiles();
	setInfoTauxUtilisationServeurs();

}

void DialogHistoriqueRF::setInfoDate(){
	QString * text = new QString;
	QString * num = new QString;
	if((histo->getHistorique()).size()==0)
	{
		*text += ("<strong> There are no saved performances </strong>");
	}
	else
	{
		*text += ("<strong> Date of measurement : </strong>");
		int cmp = 0;
		list<PerformancesRF>::iterator i;
		for(i = (histo->getHistorique()).begin();i!=((histo->getHistorique()).end());i++)
		{
			if(cmp==position_historique){
				break;
			}
			cmp ++;
		}
		//récupérer l'élément à une position de la liste
	 	num ->setNum((*i).perfReseau->getDate());
		*text += num;
	}

  	date->setText(*text);
  	delete text;
 	delete num;

}

void DialogHistoriqueRF::setInfoTpsRepMoyReseau(){
	QString * text = new QString("<strong> Average response time of each queue : </strong>");
	list<PerformancesRF>::iterator i;
 	QString * num = new QString;

 	int cmp = 0; //compteur pour se retrouver à une certaine position dans la liste
	for(i = (histo->getHistorique()).begin();i!=((histo->getHistorique()).end());i++)
	{
		if(cmp==position_historique){
			break;
		}
		cmp ++;
	}
	//récupérer l'élément à une position de la liste
	list<PerfsFile*>::iterator it;
	for(it = (*i).ListePerfsFiles.begin();it!=(*i).ListePerfsFiles.end();it++)
	{
		*text += "<br> Queue ";
		num ->setNum((*it)->getFile().getIDFile());
		*text += num;
		*text += " : ";
		num ->setNum((*it)->getTpsReponseMoy());
		*text += num;
	}

  	tps_rep_moy_reseau->setText(*text);
  	delete text;
 	delete num;

}

void DialogHistoriqueRF::setInfoNbMoyClientsReseau(){
	QString * text = new QString("<strong> Average number of clients in the network : </strong>");
 	list<PerformancesRF>::iterator i;
 	QString * num = new QString;

 	int cmp = 0; //compteur pour se retrouver à une certaine position dans la liste
	for(i = (histo->getHistorique()).begin();i!=((histo->getHistorique()).end());i++)
	{
		if(cmp==position_historique){
			break;
		}
		cmp ++;
	}
	//récupérer l'élément à une position de la liste
 	num ->setNum((*i).perfReseau->getNbMoyenClients());
	*text += num;

  	nb_moy_clients_reseau->setText(*text);
  	delete text;
 	delete num;

}

void DialogHistoriqueRF::setInfoNbMoyClientsFiles(){
	QString * text = new QString("<strong> Average number of clients for each queue : </strong>");
	list<PerformancesRF>::iterator i;
 	QString * num = new QString;

 	int cmp = 0; //compteur pour se retrouver à une certaine position dans la liste
	for(i = (histo->getHistorique()).begin();i!=((histo->getHistorique()).end());i++)
	{
		if(cmp==position_historique){
			break;
		}
		cmp ++;
	}
	//récupérer l'élément à une position de la liste
	list<PerfsFile*>::iterator it;
	for(it = (*i).ListePerfsFiles.begin();it!=(*i).ListePerfsFiles.end();it++)
	{
		*text += "<br> Queue ";
		num ->setNum((*it)->getFile().getIDFile());
		*text += num;
		*text += " : ";
		num ->setNum((*it)->getNbMoyenClientsFile());
		*text += num;
	}

  	nb_moy_clients_files->setText(*text);
  	delete text;
 	delete num;
}

void DialogHistoriqueRF::setInfoTpsAttenteMoyFiles(){
	QString * text = new QString("<strong> Average wait time of each queue : </strong>");
 	list<PerformancesRF>::iterator i;
 	QString * num = new QString;

 	int cmp = 0; //compteur pour se retrouver à une certaine position dans la liste
	for(i = (histo->getHistorique()).begin();i!=((histo->getHistorique()).end());i++)
	{
		if(cmp==position_historique){
			break;
		}
		cmp ++;
	}
	//récupérer l'élément à une position de la liste
	list<PerfsFile*>::iterator it;
	for(it = (*i).ListePerfsFiles.begin();it!=(*i).ListePerfsFiles.end();it++)
	{
		*text += "<br> Queue ";
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

void DialogHistoriqueRF::setInfoTpsServiceMoyFiles(){
	QString * text = new QString("<strong> Average service time of each queue : </strong>");
	list<PerformancesRF>::iterator i;
 	QString * num = new QString;

 	int cmp = 0; //compteur pour se retrouver à une certaine position dans la liste
	for(i = (histo->getHistorique()).begin();i!=((histo->getHistorique()).end());i++)
	{
		if(cmp==position_historique){
			break;
		}
		cmp ++;
	}
	//récupérer l'élément à une position de la liste
	list<PerfsFile*>::iterator it;
	for(it = (*i).ListePerfsFiles.begin();it!=(*i).ListePerfsFiles.end();it++)
	{
		*text += "<br> Queue ";
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

void DialogHistoriqueRF::setInfoTpsinterarriveeMoyFiles(){
	QString * text = new QString("<strong> Average arrival time of each queue : </strong>");
 	list<PerformancesRF>::iterator i;
 	QString * num = new QString;

 	int cmp = 0; //compteur pour se retrouver à une certaine position dans la liste
	for(i = (histo->getHistorique()).begin();i!=((histo->getHistorique()).end());i++)
	{
		if(cmp==position_historique){
			break;
		}
		cmp ++;
	}
	//récupérer l'élément à une position de la liste
	list<PerfsFile*>::iterator it;
	for(it = (*i).ListePerfsFiles.begin();it!=(*i).ListePerfsFiles.end();it++)
	{
		*text += "<br> Queue ";
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

void DialogHistoriqueRF::setInfoTauxPerteFiles(){
	QString * text = new QString("<strong> Loss rate of each queue : </strong>");
 	list<PerformancesRF>::iterator i;
 	QString * num = new QString;

 	int cmp = 0; //compteur pour se retrouver à une certaine position dans la liste
	for(i = (histo->getHistorique()).begin();i!=((histo->getHistorique()).end());i++)
	{
		if(cmp==position_historique){
			break;
		}
		cmp ++;
	}
	//récupérer l'élément à une position de la liste
	list<PerfsFile*>::iterator it;
	for(it = (*i).ListePerfsFiles.begin();it!=(*i).ListePerfsFiles.end();it++)
	{
		*text += "<br> Queue ";
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

void DialogHistoriqueRF::setInfoTauxUtilisationServeurs(){
	QString * text = new QString("<strong> Utilization rate of each server : </strong>");
	list<PerformancesRF>::iterator i;
 	QString * num = new QString;

 	int cmp = 0; //compteur pour se retrouver à une certaine position dans la liste
	for(i = (histo->getHistorique()).begin();i!=((histo->getHistorique()).end());i++)
	{
		if(cmp==position_historique){
			break;
		}
		cmp ++;
	}
	//récupérer l'élément à une position de la liste
	list<PerfsFile*>::iterator it;//itérateur sur les files
	for(it = (*i).ListePerfsFiles.begin();it!=(*i).ListePerfsFiles.end();it++)
	{
		*text += "<br> Queue ";
		num ->setNum((*it)->getFile().getIDFile());
		*text += num;
		*text += " : ";
		list<PerfServeur>::iterator iserveur;//itérateur sur les serveurs composant les files
		for(iserveur = ((*it)->getListeResPerfServeur()).begin();iserveur!=((*it)->getListeResPerfServeur()).end();iserveur++)
		{
			*text += "<br>     Server ";
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
