#ifndef FENETREECHEANCIER_HH
#define FENETREECHEANCIER_HH

#include <qt4/QtGui/QVBoxLayout>
#include <qt4/QtGui/QPushButton>
#include <qt4/QtGui/QLabel>
#include <qt4/QtGui/QWidget>
#include <qt4/QtCore/QString>
#include "Echeancier.hh"

class FenetreEcheancier : public QWidget
{
  Q_OBJECT

  private :
    Echeancier * echeancier;
    int position_echeancier;
    QLabel * date_actuelle;
    QLabel * date_evenement;
    QLabel * file_concernee;
    QLabel * serveur_concerne;
    QLabel * client_concerne;
    QVBoxLayout * rangement_echeancier;
    QPushButton * suivant;
    QPushButton * precedent;

  public slots :
    /**Slot affichant les informations de l'évènement précédent l'évènement actuelle**/
    void evenement_precedent();
    /**Slot affichant les informations de l'évènement suivant l'évènement actuelle**/
    void evenement_suivant();

  public :
    /**Slot affichant les informations de l'évènement suivant l'évènement actuelle
    @param ech, adresse de l'échéancier contenant les informations à afficher
    @param parent, widget parent de la fenêtre
    **/
    FenetreEcheancier(Echeancier * ech = NULL,QWidget * parent = NULL);

    /**Destructeur**/
    ~FenetreEcheancier();

    /**Méthode d'affichage de la date de l'évènement**/
    void setInfoDate();
    /**Méthode d'affichage du client participant à l'évènement*/
    void setInfoClient();
    /**Méthode d'affichage de la file participant à l'évènement**/
    void setInfoFile();
    /**Méthode d'affichage du serveur participant à l'évènement**/
    void setInfoServeur();
    /**Méthode d'affichage de la date actuelle se trouve l'échéancier**/
    void setDateActuelle();
    /**Méthode remettant à jour l'évènement actuelle par rapport à la position 0 dans l'échéancier*/
    void maj_position();

};
#endif
