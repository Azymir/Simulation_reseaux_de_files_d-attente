#include "HistoriqueRO.hh"
#include <qt4/QtGui/QDialog>
#include <qt4/QtGui/QLabel>
#include <qt4/QtGui/QVBoxLayout>
#include <qt4/QtGui/QPushButton>
#include <qt4/QtGui/QScrollArea>
#include <qt4/QtCore/QString>

class DialogHistoriqueRO : public QDialog
{
	Q_OBJECT

	private :
	HistoriqueRO * histo;
	int position_historique;
	QLabel * tps_rep_moy_reseau;
	QLabel * nb_moy_clients_reseau;
	QLabel * nb_moy_clients_files;
	QLabel * tps_attente_moy_files;
	QLabel * tps_service_moy_files;
	QLabel * tps_interarrivee_moy_files;
	QLabel * taux_perte_files;
	QLabel * taux_utilisation_serveurs;
	QLabel * tps_sejour_moy_reseau;
	QLabel * debit_entree_reseau;
	QLabel * debit_sortie_reseau;
	QLabel * date;
	QVBoxLayout * layout_affichage;
	QVBoxLayout * rangement_scroll;
	QScrollArea * scrollArea;
	QWidget * fenetre_affichage;
	QPushButton * ok;
	QPushButton * suivant;
	QPushButton * precedent;

	public slots:

	void perf_suivante();
	void perf_precedent();

	public:
    /* Constructeur prennant en parametre un pointeur vers h de type HistoriqueRO et un pointeur vers le parent QWidget defini par default a NULL et 0*/
	DialogHistoriqueRO(HistoriqueRO * h = NULL,QWidget * parent = NULL);
	/* Destructeur */
	~DialogHistoriqueRO();
	 /* Méthode de récupération de la date de la mesure */
	void setInfoDate();
	/* Méthode de récupération du temps moyen de réponse de chaque file du réseau*/
	void setInfoTpsRepMoyReseau();
	/* Méthode de récupération du nombre moyen de clients dans le réseau*/
	void setInfoNbMoyClientsReseau();
	/* Méthode de récupération du nombre moyen de clients par file*/
	void setInfoNbMoyClientsFiles();
	/* Méthode de récupération du temps moyen d'attente par file*/
	void setInfoTpsAttenteMoyFiles();
	/* Méthode de récupération du temps de service moyen par file*/
	void setInfoTpsServiceMoyFiles();
	/* Méthode de récupération d'interarrivée moyen par file*/
	void setInfoTpsinterarriveeMoyFiles();
	/* Méthode de récupération du taux de perte par file*/
	void setInfoTauxPerteFiles();
	/* Méthode de récupération du taux d'utilisation de chaque serveur*/
	void setInfoTauxUtilisationServeurs();
	/*Méthode de récupération du temps de séjour moyen dans le réseau*/
	void setInfoTpsSejourMoyReseau();
	/*Méthode de récupération du débit d'entrée du réseau*/
	void setInfoDebitEntreeReseau();
	/*Méthode de récupération du débit de sortie du réseau*/
	void setInfoDebitSortieReseau();
};
