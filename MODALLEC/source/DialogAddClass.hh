#ifndef DIALOGADDCLASS_HH
#define DIALOGADDCLASS_HH

#include <qt4/QtGui/QDialog>
#include <qt4/QtCore/QString>
#include <qt4/QtGui/QComboBox>
#include <qt4/QtGui/QVBoxLayout>
#include <qt4/QtGui/QPushButton>
#include <qt4/QtGui/QLabel>
#include <qt4/QtGui/QLineEdit>
#include <qt4/QtGui/QSpinBox>
#include <string>
using namespace std;


class DialogAddClass : public QDialog
{
    Q_OBJECT

public:
    /* Constructeur prennant en parametre un pointeur Qwidget defini par default a 0 */
    DialogAddClass(QWidget *parent = 0);
    /* Destructeur */
    ~DialogAddClass();
    /* Methode qui renvoie sous forme d'entier la valeur entrer dans le QSpinBox */
    int getPriorite();
    /* Methode qui renvoie sous forme de chaine de caractere le routage entée dans le QLineEdit */
    string getRoutage();

private:
    QVBoxLayout * Vlayout;
    QLabel * TitreRoutage;
    QLabel * TitrePriorite;
    QLineEdit * configRoutage;
    QSpinBox * priorite;
    QPushButton * BoutonOk;
};

#endif // DIALOGADDCLASS_HH
