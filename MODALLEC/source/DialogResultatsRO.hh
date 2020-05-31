#ifndef DIALOGRESULTATSRO_HH
#define DIALOGRESULTATSRO_HH

#include <qt4/QtGui/QDialog>
#include <qt4/QtGui/QVBoxLayout>
#include <qt4/QtGui/QPushButton>
#include <qt4/QtGui/QLabel>
#include <qt4/QtGui/QScrollArea>
#include <qt4/QtCore/QString>
#include "HistoriqueRO.hh"

class DialogResultatsRO : public QDialog
{
    Q_OBJECT

private:
    PerformancesRO * perfsRO;
    QLabel * nb_moy_clients_reseau;
    QLabel * tps_sejour_moy_reseau;
    QLabel * tps_rep_moy_files;
    QLabel * debit_entree_reseau;
    QLabel * debit_sortie_reseau;
    QLabel * nb_moy_client_files;
    QLabel * tps_attente_moy_files;
    QLabel * tps_service_moy_files;
    QLabel * tps_interarrivee_moy_files;
    QLabel * taux_perte_files;
    QLabel * taux_utilisation_serveurs;
    QVBoxLayout * layout_affichage;
    QVBoxLayout * rangement_scroll;
    QScrollArea * scrollArea;
    QWidget * fenetre_affichage;
    QPushButton * ok;

public:
    /* Constructeur prennant en parametre un pointeur vers la structure PerformancesRO et un pointeur vers le parent QDialog defini par default a NULL et 0*/
    DialogResultatsRO(PerformancesRO * perfs = NULL, QDialog * parent = 0);
    /* Destructeur */
    ~DialogResultatsRO();
    void setInfoTpsRepMoyFiles();
    /* Méthode de récupération du nombre moyen du reseau */
    void setInfoTpsSejourMoyReseau();
    /* Méthode de récupération du temps de séjour moyen du réseau */
    void setInfoNbMoyClientsReseau();
    /* Méthode de récupération du nombre de debit entré dans le reseau */
    void setInfoDebitEntreeReseau();
    /* Méthode de récupération du nombre de debit sortie dans le reseau */
    void setInfoDebitSortieReseau();
    /* Méthode de récupération du nombre moyens de chaque file presente dans le réseau */
    void setInfoNbMoyClientsFiles();
    /* Méthode de récupération des temps de attentes moyens de chaque file presente dans le réseau */
    void setInfoTpsAttenteMoyFiles();
    /* Méthode de récupération des temps de services moyens de chaque file presente dans le réseau */
    void setInfoTpsServiceMoyFiles();
    /* Méthode de récupération des temps inter-arrivés moyens de chaque file presente dans le réseau */
    void setInfoTpsinterarriveeMoyFiles();
    /* Méthode de récupération des taux de pertes de chaque file presente dans le réseau */
    void setInfoTauxPerteFiles();
    /* Méthode de récupération des taux d'utilisations de chaque Serveur presente dans le réseau */
    void setInfoTauxUtilisationServeurs();

};

#endif // DIALOGRESULTATSRO_HH
