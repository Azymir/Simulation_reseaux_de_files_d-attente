#include "Vue.hh"

using namespace std;

/**Constructeur
@param parent, un pointeur sur le widget parent de la vue
**/
Vue::Vue(QWidget * parent):QGraphicsView(parent){

	if(parent != NULL) setFixedSize(parent->width()-165,parent->height()-70);
	else setFixedSize(600,600);

	pos_clic.x = 0;
	pos_clic.y = 0;
}

/**Destructeur**/
Vue::~Vue(){}

/**Méthode de récupération de la position d'un clic sur la vue
@param event, un pointeur sur un évènement de la souris
**/
void Vue::mousePressEvent(QMouseEvent *event){

	QGraphicsView::mousePressEvent(event);
	pos_clic.x = event->x();
	pos_clic.y = event->y();
	emit clicked();
}

/**Méthode de récupération de l'abscisse du clic**/
int Vue::getPosXClic(){
	return pos_clic.x;
}

/**Méthode de récupération de l'ordonnée du clic**/
int Vue::getPosYClic(){
	return pos_clic.y;
}

/**Méthode remettant les coordonnées du clic à 0**/
void Vue::remise_a_zero()
{
	pos_clic.x = 0;
	pos_clic.y = 0;
}
