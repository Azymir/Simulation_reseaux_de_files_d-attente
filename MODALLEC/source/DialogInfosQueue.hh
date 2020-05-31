#ifndef DIALOGINFOSQUEUE_HH
#define DIALOGINFOSQUEUE_HH

#include <qt4/QtGui/QDialog>
#include <qt4/QtGui/QLabel>
#include <qt4/QtGui/QVBoxLayout>
#include <qt4/QtGui/QPushButton>
#include <qt4/QtCore/QString>
#include "File.hh"

class DialogInfosQueue : public QDialog
{
  Q_OBJECT

  private:
    File * file;
    QLabel * ordonnancement;
    QLabel * loiService;
    QLabel * nbClients;
    QLabel * nbClientsServis;
    QLabel * nbClientsPresentes;
    QLabel * nbClientsPerdus;
    QLabel * nbServeurs;
    QVBoxLayout * layout;
    QPushButton * ok;
    QPushButton * Infos_Clients;

  public slots :
    /**Slot affichant les informations sur les clients de la file*/
    void informations_clients();

  public:
    /**Constructeur
    @param f, la file dont il faut afficher les informations
    @param parent, le widget parent de la fenêtre de dialogue
    **/
    DialogInfosQueue(File * f = NULL,QWidget * parent = NULL);

    /**Destructeur**/
    ~DialogInfosQueue();

    /**Méthode d'affichage de l'ordonnancement de la file**/
    void setInfoOrdonnancement();
    /**Méthode d'affichage de la loi de service de la file**/
    void setInfoLoiService();
    /**Méthode d'affichage du nombre de clients dans la file**/
    void setInfoNbClients();
    /**Méthode d'affichage du nombre de clients servis de la file**/
    void setInfoNbClientsServis();
    /**Méthode d'affichage du nombre de clients s'étant présentés à la file**/
    void setInfoNbClientsPresentes();
    /**Méthode d'affichage du nombre de clients n'étant pas entrés dans la file**/
    void setInfoNbClientsPerdus();
    /**Méthode d'affichage du nombre de serveurs de la file**/
    void setNbServeurs();

};

#endif
