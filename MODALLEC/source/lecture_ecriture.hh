#include "Reseau.hh"
#include <fstream>
#include "HistoriqueRO.hh"
#include "HistoriqueRF.hh"
#include <string>
#include <stdexcept>

using namespace std;


/**Méthode s'occupant de la lecture du fichier contenant les données d'un réseau
  @param reseau, pointeur sur le réseau
  @param nomfic, nom du fichier à lire
  **/
void lecture_fichier_reseau (Reseau * reseau, const string nomfic);
/**Méthode s'occupant de la lecture d'une file écrite dans un string
  @param file, pointeur sur une file
  @param ligne, ligne à lire
  **/
void lecture_file (File * file, const string ligne);
/**Méthode s'occupant de la lecture d'une classe client écrite dans un string
  @param cc, pointeur sur une classe client
  @param ligne, ligne à lire
  **/
void lecture_type (ClasseClient* cc, const string ligne);
/**Méthode s'occupant de l'écriture d'un reseau dans un fichier
  @param nomfic, nom du fichier dans lequel le réseau est écrit
  @param reseau, reseau dont les caractéristiques sont enregistrées
  **/
void ecriture_fichier_reseau (const string nomfic, Reseau& reseau);
/**Méthode s'occupant de l'écriture des files composant un réseau dans un fichier
  @param fic, pointeur sur le fichier
  @param reseau, reseau dont les files sont enregistrées
  **/
void ecriture_fichier_file (ofstream* fic, Reseau& reseau);
/**Méthode s'occupant de l'écriture des classes composant un réseau dans un fichier
  @param fic, pointeur sur le fichier
  @param reseau, reseau dont les classes sont enregistrées
  **/
void ecriture_fichier_classe (ofstream* fic, Reseau& reseau);
/**Méthode s'occupant de l'écriture des performances d'un réseau fermé dans un fichier
  @param nomfic, nom du fichier dans lequel les performances sont écrites
  @param h, historique des performances d'un réseau fermé
  **/
void ecriture_fichier_performancesRF (const string nomfic, HistoriqueRF& h);
/**Méthode s'occupant de l'écriture des performances d'un réseau ouvert dans un fichier
  @param nomfic, nom du fichier dans lequel les performances sont écrites
  @param h, historique des performances d'un réseau ouvert
  **/
void ecriture_fichier_performancesRO (const string nomfic, HistoriqueRO & h);
