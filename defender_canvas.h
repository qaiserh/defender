/* File: defender_canvas.h
   Authors: Joe Polin, Jeremy Benson, Hamza Qaiser
   Desc: Header file for defender game canvas
*/

#ifndef DEFENDER_CANVAS_H_
#define DEFENDER_CANVAS_H_

#include <QtGui>

struct node {
  int x_position;
  int y_position;
  int angle;
  int size;
  node *next;
  node *prev;
};

class DefenderCanvas : public QWidget
{
  Q_OBJECT

  public:
    DefenderCanvas(QWidget* parent); // contructor

  signals:
    void needsButtonChange(QString str);
    void needsTimerUpdate(QString str);
    void needsScoreUpdate(QString str);

  public slots: // Slots that everyone can access
    void buttonPress();
    void resetGame();
    void showTime();
    void showHelp();
    void updateScore();
  

  protected:
    void paintEvent(QPaintEvent* event);
    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);
  

  private slots: // Qt slots internal to the canvas
    void timerTicked();
  

  private: // functions internal to canvas
    void reset();

  enum State { BEFORE_PLAY, PLAYING, PAUSED, WON, LOST } state;

//  QPainter p;
  QTimer* timer;
  QTime* gameClock;
  QTime* gameWait;
  int idle;
  int secElapsed;

  /**************  Shooter Variables ******************/

  // coordinates of player
  int playerX;
  int playerY; // Won't change

  // Shooter size
  static const int SHOOTER_WIDTH = 60;
  static const int SHOOTER_HEIGHT = 70;

  // Angle of player (0 degrees is straight, and use right hand frame)
  int playerTheta;

  // Movement of player
  int transX; // -1 for left, 1 for right, 0 for still
  int transY; // -1 for down, 1 for up, 0 for still
  int rotate; // 1 for counter-clockwise, -1 for clockwise, 0 for neither
  static const int maxRotate = 60; // Maximum magnitude of rotation (intial is theta = 0)
  static const int rockDia = 40;
  static const int bulletDia = 4;
  
  // scoring
  int destroyed;
  int score;

//Bullets and rocks are stored in linked lists.
  node *bullets;
  node *rocks;

  //Count to decide frequency of asteroids AKA AWESOME LEVEL SYSTEM.
  int level;

  /************* Constants for gameplay ****************/

  static const int WIDTH = 600;
  static const int HEIGHT = 600;

};

#endif
