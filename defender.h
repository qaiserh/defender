/* File: defender.h
   Author: Joe Polin, Jeremy Benson, Hamza Qaiser
   Desc.: Header file for defender game
*/

#ifndef DEFENDER_H_
#define DEFENDER_H_

#include <QtGui>

// Define class for canvas
class DefenderCanvas;


// Set up class for window
class Defender : public QWidget
{
  Q_OBJECT

  public:
    Defender(); // Call constructor in defender.cpp

  private slots:
  // allow other objects (like the PongCanvas) to change the button text
    void changeButtonText(QString str);
    void updateTimer(QString str);
    void updateScore(QString str);

  private:
  // Canvas
    DefenderCanvas* canvas;
    QPushButton* helpButton;
    QPushButton* controlButton;
    QPushButton* resetButton;
  
    QLCDNumber* clockDisplay;
    QLCDNumber* scoreDisplay;
  
    QFrame* canvasFrame;
     
};

#endif
