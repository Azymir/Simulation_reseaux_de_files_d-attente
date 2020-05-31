#ifndef DIALOG_INFOS_CLASS
#define DIALOG_INFOS_CLASS


#include <qt4/QtGui/QDialog>
#include <qt4/QtGui/QLabel>
#include <qt4/QtGui/QVBoxLayout>
#include <qt4/QtGui/QPushButton>
#include "ClasseClient.hh"


class DialogInfosClass : public QDialog
{
	Q_OBJECT
	private :
	ClasseClient * classe_client;
	QLabel * priorite;
	QLabel * routage;
	QVBoxLayout * layout;
	QPushButton * ok;

	public:
		/* Constructeur prennant en parametre une pointeur ClasseClient qui nous permet de recuperer les informations des Class et aussien parametre un pointeur QWidget parent */
	DialogInfosClass(ClasseClient * cc = NULL,QWidget * parent = NULL);
	/*Destructeur*/
	~DialogInfosClass();
	/* Cette methode permet de renvoyer la priorite des classeclient*/
	void setInfoPriorite();
	/* Cette methode permet de renvoyer le routage des classeclient*/
	void setInfoRoutage();

};

#endif
