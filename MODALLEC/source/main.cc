#include <qt4/QtGui/QApplication>
#include "FenetreCreation.hh"
#include <time.h>

int main(int argc, char *argv[]) {

  srand(time(NULL));

  QApplication app(argc,argv);
  FenetreCreation fc;

  app.setStyleSheet
  ("QPushButton{background-color: #B0C4DE; border-style: inset; border-width: 2px; border-radius: 10px; border-color: darkgrey; font: bold 14px; min-width: 5em; padding: 6px; font : Serif;}"
   "QPushButton:pressed{background-color: darkgrey;}"
   "FenetreCreation{background-color: #C0C0C0;}"
   "FenetreSimulationRF{background-color: #C0C0C0;}"
   "FenetreSimulationRO{background-color: #C0C0C0;}"
   "QMenuBar{background-color: #B0C4DE; border-style: inset; border-width: 2px; border-radius: 10px; border-color: darkgrey; font: bold 14px; min-width: 4.5em; font : Serif;}"
   "QMenuBar::item {background: transparent; font : Serif;}"
   "QMenu{background-color: #B0C4DE; border-style: inset; border-width: 2px; border-radius: 10px; border-color: darkgrey; font: bold 14px; min-width: 3em; padding: 6px; font : Serif;}"
 );
  fc.show();
  return app.exec();

}
