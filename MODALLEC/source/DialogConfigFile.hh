#ifndef DIALOGCONFIGFILE_HH
#define DIALOGCONFIGFILE_HH

#include <qt4/QtGui/QDialog>
#include <qt4/QtGui/QSpinBox>
#include <qt4/QtGui/QComboBox>
#include <qt4/QtGui/QPushButton>
#include <qt4/QtGui/QLabel>
#include <qt4/QtGui/QVBoxLayout>
#include <qt4/QtCore/QString>
#include <string>
#include "File.hh"

using namespace std;

class DialogConfigFile : public QDialog {

private:

  File * file_a_config;
  QVBoxLayout * layout;
  QLabel *LoiArrivee;
  QLabel *LoiService;
  QLabel *Ordonnancement;
  QLabel *TailleMax;
  QLabel *NbServeurs;
  QComboBox *newLoiArrivee;
  QComboBox *newLoiService;
  QComboBox *newOrdonnancement;
  QSpinBox *newTailleMax;
  QSpinBox *newNbServeurs;
  QPushButton *ok;
  QPushButton *annuler;

public:

  /**Constructeur
  @param f, la file à configurer
  @param parent, le widget parent de la boîte de dialogue
  **/
  DialogConfigFile(File * f=NULL,QWidget * parent = NULL);

  /**Destructeur**/
  ~DialogConfigFile();

  /** Méthode de récupération de la valeur de distribution d'arrivée entrée par l'utilisateur
  @return string correspondant à la distribution d'arrivée
  **/
  string recuperer_valeur_newLoiArrivee();

  /** Méthode de récupération de la valeur de loi de service entrée par l'utilisateur
  @return string correspondant à la loi de service
  **/
  string recuperer_valeur_newLoiService();

  /** Méthode de récupération de l'ordonnancement entrée par l'utilisateur
  @return string correspondant à la valeur de l'ordonnancement
  **/
  string recuperer_valeur_newOrdonnancement();

  /** Méthode de récupération de la valeur de la taille de maximale de la file entrée par l'utilisateur
  @return int correspondant à la valeur de la taille maximale de la file
  **/
  int recuperer_valeur_newTailleMax();

  /** Méthode de récupération de la valeur du nombre de serveurs entrée par l'utilisateur
  @return int correspondant à la valeur du nombre de serveurs
  **/
  int recuperer_valeur_newNbServeurs();

};

#endif
