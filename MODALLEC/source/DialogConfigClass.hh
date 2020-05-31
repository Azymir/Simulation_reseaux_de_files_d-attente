#ifndef DIALOGCONFIGCLASS_HH
#define DIALOGCONFIGCLASS_HH

#include <qt4/QtGui/QDialog>
#include <qt4/QtGui/QVBoxLayout>
#include <qt4/QtGui/QPushButton>
#include <qt4/QtGui/QLabel>
#include <qt4/QtGui/QLineEdit>
#include <qt4/QtGui/QSpinBox>
#include <qt4/QtCore/QString>
#include <string>
#include "ClasseClient.hh"

using namespace std;

class DialogConfigClass : public QDialog
{
    Q_OBJECT
private:
    ClasseClient *cc;
    QVBoxLayout * Vlayout;
    QLabel * configRoutageLabel;
    QLabel * prioriteLabel;
    QLineEdit * configRoutage;
    QSpinBox * priorite;
    QPushButton * BoutonOk;
    QPushButton * BoutonAnnuler;
public:
  /* Constructeur prennant en parametre la ClasseClient definie a NULL par default et un pointeur */
    DialogConfigClass(ClasseClient *cc = NULL,QWidget *parent = 0);
    /* Destructeur */
    ~DialogConfigClass();
    /* Methode qui renvoie sous forme d'entier la valeur entrer dans le QSpinBox */
    int getPriorite();
    /* Methode qui renvoie sous forme de chaine de caractere le routage entée dans le QLineEdit */
    string getRoutage();
};

#endif // DIALOGCONFIGCLASS_H
