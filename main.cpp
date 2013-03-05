/* File: main.cpp
   Authors: Joe Polin, Jeremy Benson, Hamza Qaiser
   Desc.: Main file to start up defender
*/

#include <QtGui>
#include "defender.h"

int main(int argc, char** argv)
{
  // Start application
  QApplication game(argc, argv);
  
  // Construct game and show it
  Defender defender;
  defender.show();

  return game.exec();
}
