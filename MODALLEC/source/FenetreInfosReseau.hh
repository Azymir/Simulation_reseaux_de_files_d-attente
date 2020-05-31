#ifndef FENETREINFOSRESEAU_HH
#define FENETREINFOSRESEAU_HH

#include <qt4/QtGui/QWidget>
#include <qt4/QtGui/QVBoxLayout>
#include <qt4/QtGui/QLabel>
#include <qt4/QtGui/QScrollArea>                                                //A expliquer dans le compte-rendu
#include <qt4/QtCore/QString>
#include "Reseau.hh"

class FenetreInfosReseau : public QWidget
{
  private:
    Reseau * reseau;
    QVBoxLayout * rangement;
    QLabel * nbClientsActuel;
    QLabel * nbClientsPasses;
    QLabel * nbClasses;
    QLabel * nbClientsClasse;
    QLabel * typeReseau;
    //Créer une barre de défilement dans la fenêtre
    QVBoxLayout * rangement_scroll;                                             
    QScrollArea * scrollArea;
    QWidget * fenetre_affichage;

  public:
    /**Constructeur
    @param r, l'adresse du réseau dont les données sont à afficher
    @param parent, le widget parent de la fenêtre
    **/
    FenetreInfosReseau(Reseau * r = NULL, QWidget * parent = NULL);
    /**Destructeur**/
    ~FenetreInfosReseau();
    /**Méthode d'affichage du nombre de clients actuellement dans le réseau**/
    void setInfoNbClientsActuel();
    /**Méthode d'affichage du nombre de clients passés dans le réseau**/
    void setInfoNbClientsPasses();
    /**Méthode d'affichage du nombre de classes dans le réseau**/
    void setInfoNbClasses();
    /**Méthode d'affichage du nombre de clients par classe du réseau**/
    void setInfoNbClientsClasse();
    /**Méthode d'affichage du type du réseau**/
    void setInfoTypeReseau();
};

#endif
