/* File: destroyer.cpp
   Author: Joe Polin, Jeremy Benson, Hamza Qaiser
   Desc: Defines the destroyer game
*/

#include <QtGui>
#include "defender.h"
#include "defender_canvas.h"

Defender::Defender()
{
  setWindowTitle("Defender Game");

  // Make Layout of whole GUI
  QVBoxLayout* mainLayout = new QVBoxLayout(this);

  // Add title image to layout:
  QLabel* titleLabel = new QLabel();
  titleLabel -> setPixmap(QPixmap("defenderlogo.png"));
  mainLayout -> addWidget(titleLabel);

  // Center the title image
  titleLabel -> setAlignment(Qt::AlignHCenter);


  /********* CANVAS ***************/
  canvas = new DefenderCanvas(this);

  // Give canvas color
////  QPalette canvasPal(palette());
////  canvasPal.setColor(QPalette::Background, Qt::black);
  canvas -> setAutoFillBackground(true);
//  canvas -> setPalette(canvasPal);
  canvas -> setObjectName("gameCanvas");

  // Add it to the layout
  mainLayout -> addWidget(canvas);

  /******* Bottom Layout **********/
  QHBoxLayout* bottomLayout = new QHBoxLayout();

  /******** BUTTONS **************/ 
//  helpButton = new QPushButton("Help", this);  
//  helpButton -> setObjectName("help"); // For styling
  controlButton = new QPushButton("Start", this);
  controlButton -> setObjectName("control"); // Styling
  resetButton = new QPushButton("Reset", this);
  resetButton -> setObjectName("Reset"); // For styling

  // Add buttons to layout
//  bottomLayout -> addWidget(helpButton, 0, Qt::AlignLeft);
  bottomLayout -> addWidget(controlButton, 1, Qt::AlignCenter);

  /******* Display Score  *******/
  QHBoxLayout* scoreLayout = new QHBoxLayout();
  scoreDisplay = new QLCDNumber(this);
  
  
  QLabel* scoreLabel = new QLabel();
  scoreLabel -> setText("Score");
  
  scoreDisplay -> setSegmentStyle(QLCDNumber::Flat);
  scoreDisplay -> resize(40, 10);
  scoreDisplay -> setObjectName("score");
  
  scoreLayout -> addWidget(scoreLabel);
  scoreLayout -> addWidget(scoreDisplay);
  bottomLayout -> addLayout(scoreLayout);
  
  
  /******* Display Timer  *******/
  clockDisplay = new QLCDNumber(this);
  QHBoxLayout* clockLayout = new QHBoxLayout();
  
  QLabel* clockLabel = new QLabel();
  clockLabel -> setText("Time");
  
  clockDisplay -> setSegmentStyle(QLCDNumber::Flat);
  clockDisplay -> resize(40, 10);
  clockDisplay -> setObjectName("clock");
  
  clockLayout -> addWidget(clockLabel);
  clockLayout -> addWidget(clockDisplay);
  bottomLayout -> addLayout(clockLayout);

  // A few last details with the layouts
  mainLayout -> addLayout(bottomLayout);
  mainLayout -> addWidget(resetButton);
  setLayout(mainLayout);
  
  // the button directly controls the canvas
  connect(controlButton, SIGNAL(clicked()), canvas, SLOT(buttonPress()));
  connect(resetButton, SIGNAL(clicked()), canvas, SLOT(resetGame()));
  connect(clockDisplay, SIGNAL(timeout()), this, SLOT(showTime()));
//  connect(helpButton, SIGNAL(clicked()), canvas, SLOT(showHelp()));
  
  // the canvas can control the button
  connect(canvas, SIGNAL(needsButtonChange(QString)),
          this, SLOT(changeButtonText(QString)));
  connect(canvas, SIGNAL(needsTimerUpdate(QString)),
          this, SLOT(updateTimer(QString)));
  connect(canvas, SIGNAL(needsScoreUpdate(QString)),
          this, SLOT(updateScore(QString)));
}

void Defender::changeButtonText(QString str)
{
  controlButton -> setText(str);
}

void Defender::updateTimer(QString str)
{
  clockDisplay -> display(str);
}

void Defender::updateScore(QString str)
{
  scoreDisplay -> display(str);
}
