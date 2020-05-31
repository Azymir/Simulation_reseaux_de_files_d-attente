#ifndef VUE_HH
#define VUE_HH

#include <qt4/QtGui/QGraphicsView>
#include <qt4/QtGui/QMouseEvent>
#include <iostream>
#include "File.hh"

class Vue : public QGraphicsView
{

  Q_OBJECT

private :
  coordonnees pos_clic;

signals :
                                                                                //A expliquer dans le comtpe-rendu
  /**Signal d'un clic**/
  void clicked();

public :

  /**Constructeur
  @param parent, un pointeur sur le widget parent de la vue
  **/
  Vue(QWidget * parent = NULL);

  /**Destructeur**/
  ~Vue();

  /**Méthode de récupération de la position d'un clic sur la vue
  @param event, un pointeur sur un évènement de la souris
  **/
  void mousePressEvent(QMouseEvent *event);

  /**Méthode de récupération de l'abscisse du clic**/
  int getPosXClic();

  /**Méthode de récupération de l'ordonnée du clic**/
  int getPosYClic();

  /**Méthode remettant les coordonnées du clic à 0**/
  void remise_a_zero();                                                         //A ajouter au compte-rendu

};

#endif
