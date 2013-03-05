/* File: defender_canvas.cpp
   Authors: Joe Polin, Jeremy Benson, Hamza Qaiser
   Desc.: This is where all the behavior is determined.
*/

#include <QtGui>
#include "defender_canvas.h"
#include <sstream>
#include <cmath>
#include <iostream>
#include "randomness.cpp"

#define PI 3.14159265


DefenderCanvas::DefenderCanvas(QWidget* parent)
  : QWidget(parent) // Constructs DefenderCanvas and its parent
{
  // Start the timer
  timer = new QTimer(this);
  timer -> setInterval(5); // 5 ms increments
  connect(timer, SIGNAL(timeout()), this, SLOT(timerTicked()));
  
  // game clock
  gameClock = new QTime();
  gameWait = new QTime();
  
  // set background image
  QPalette palette;
//  palette.setBrush(this -> backgroundRole(), QBrush(QPixmap("spacebackground.jpg")));
  palette.setBrush(this -> backgroundRole(), QBrush(QPixmap("planet.jpg")));
  this -> setPalette(palette);
  setFixedSize(WIDTH, HEIGHT);
  
  // display instructions at start
  showHelp();
  
  // Initialize linked list of bullets and rocks
  bullets = NULL;
  rocks = NULL;

  //Initialize level
  level = 0;
  
  // Begin in state "BEFORE_PLAY"
  state = BEFORE_PLAY;

  reset();
}

/********** Reset *************/
void DefenderCanvas::reset()
// Call before starting game
{
  // reset score and number of asteroids destroyed
  // score = # asteroids destroyed + time alive
  // the higher, the better
  score = 0;
  destroyed = 0;

  // Initial player conditions
  playerX = WIDTH/2;
  playerY = HEIGHT - 1.5*SHOOTER_HEIGHT;
  playerTheta = 0;
  
  transX = 0;
  transY = 0;
  rotate = 0;

  timer -> stop();

  bullets = NULL;
  rocks = NULL;
  level = 0;
  
  update();
}

void DefenderCanvas::showTime()
{
  secElapsed =  (gameClock -> elapsed())/1000 - idle/1000;
  std::stringstream sec;
  sec << secElapsed;
  needsTimerUpdate(*(new QString(sec.str().c_str())));

}

void DefenderCanvas::showHelp()
{
  QPainter p(this);
  p.setPen(QPen(Qt::white));
  p.drawText(QRect(0, 0, WIDTH, HEIGHT- 20), Qt::AlignCenter, "Welcome to Defender!");
  p.drawText(QRect(0, 20, WIDTH, HEIGHT-20), Qt::AlignCenter, "These are the instructions:");
  p.drawText(QRect(0, 40, WIDTH, HEIGHT-20), Qt::AlignCenter, "Left and Right keys move you horizontally");
  p.drawText(QRect(0, 60, WIDTH, HEIGHT-20), Qt::AlignCenter, "Z and X keys rotate you left and right, respectively");
  p.drawText(QRect(0, 80, WIDTH, HEIGHT-20), Qt::AlignCenter, "'S' to start, 'P' to pause, and 'R' to reset");
  p.drawText(QRect(0, 100, WIDTH, HEIGHT-20), Qt::AlignCenter, "Enjoy!");
}

void DefenderCanvas::updateScore()
{
  std::stringstream s;
  s << destroyed;
  needsScoreUpdate(*(new QString(s.str().c_str())));
  
}

/********** Paint event *************/
void DefenderCanvas::paintEvent(QPaintEvent*)
// Render screen
{
  // Put border around screen
  QPainter p(this);
  p.setPen(QPen(Qt::black));
  p.drawRect(0, 0, WIDTH - 1, HEIGHT - 1);

  // Draw Shooter
  QPixmap shooter("starfox.gif");
  p.translate(playerX, playerY); // Move origin to position
  p.rotate(playerTheta); // Rotate
  p.drawPixmap(-SHOOTER_WIDTH/2, -SHOOTER_HEIGHT/2, SHOOTER_WIDTH, SHOOTER_HEIGHT, shooter); // Plot

  //Draw bullets
  p.setPen(QPen(Qt::green));
  p.setBrush(Qt::green);

  node *current = bullets;
  
  // Need to unrotate and untranslate pen before drawing bullets
  p.rotate(-playerTheta); // Rotate
  p.translate(-playerX, -playerY); // Move origin to position

  while(current != NULL) {
    // Draw this bullet
    p.drawEllipse(current -> x_position, current -> y_position, bulletDia, bulletDia);
    // on to the next one!
    current = current -> next;
  }

  node *curr = rocks;

  while(curr != NULL) {
    p.setPen(QColor(255, 0, 0, 150));
//    p.setBrush(Qt::darkGray);
    QPixmap asteroid("purpleasteroid.png");
//    p.drawEllipse(curr -> x_position, curr -> y_position, rockDia, rockDia);
    p.drawPixmap(curr -> x_position, curr -> y_position, curr -> size, curr -> size, asteroid);
    curr = curr -> next;
  }
  
  // show that the user lost, if necessary
  if (state == BEFORE_PLAY) {
    p.setPen(QPen(Qt::white));
    p.drawText(QRect(0, 0, WIDTH, HEIGHT- 20), Qt::AlignCenter, "Welcome to Defender!");
    p.drawText(QRect(0, 20, WIDTH, HEIGHT-20), Qt::AlignCenter, "These are the instructions:");
    p.drawText(QRect(0, 40, WIDTH, HEIGHT-20), Qt::AlignCenter, "Left and Right keys move you horizontally");
    p.drawText(QRect(0, 60, WIDTH, HEIGHT-20), Qt::AlignCenter, "'Z' and 'X' keys rotate you left and right, respectively");
    p.drawText(QRect(0, 80, WIDTH, HEIGHT-20), Qt::AlignCenter, "'S' to start, 'P' to pause, and 'R' to reset");
    p.drawText(QRect(0, 100, WIDTH, HEIGHT-20), Qt::AlignCenter, "Spacebar to shoot lasers and destroy the astroids");
    p.drawText(QRect(0, 120, WIDTH, HEIGHT-20), Qt::AlignCenter, "Enjoy!");
//    showHelp();
  }
  else if(state == WON) {
    // this will draw the text centered in the play area
    p.drawText(QRect(0, 0, WIDTH, HEIGHT), Qt::AlignCenter, "You won!");
  }
  else if (state == LOST) {
    std::stringstream s;
    s << destroyed + secElapsed;
    p.setPen(QPen(Qt::white));
    p.drawText(QRect(0, 0, WIDTH, HEIGHT), Qt::AlignCenter, "Game over!");
    p.drawText(QRect(-10, 20, WIDTH, HEIGHT), Qt::AlignCenter, "Your score:");
    p.drawText(QRect(50, 20, WIDTH, HEIGHT), Qt::AlignCenter, s.str().c_str());
  }
  
}

/********** Reset button *************/
void DefenderCanvas::resetGame()
{
  gameClock -> restart();
  gameWait -> restart();
  
  // Delete existing bullets and rocks/asteroids
  bullets = NULL;
  rocks = NULL;
  
  reset();
  
  switch (state)
  {
    case BEFORE_PLAY:
      state = BEFORE_PLAY;
      break;
      
    case PLAYING:
      needsButtonChange("Start");
      state = BEFORE_PLAY;
      break;
      
    case PAUSED:
      needsButtonChange("Start");
      state = BEFORE_PLAY;
      break;
      
    case LOST:
      needsButtonChange("Start");
      state = BEFORE_PLAY;
      break;
      
    default:
      break;
  }
}

/********** Button presses *************/
void DefenderCanvas::buttonPress()
{
  switch(state)
  {      
    case BEFORE_PLAY:
      timer -> start();
      idle = (gameWait -> elapsed());
      needsButtonChange("Pause");
      state = PLAYING;
      break;
      
    case PLAYING:
      timer -> stop();
      gameWait -> restart();
      needsButtonChange("Resume");
      state = PAUSED;
      break;
      
    case PAUSED:
      timer -> start();
      idle += (gameWait -> elapsed());
      needsButtonChange("Pause");
      state = PLAYING;
      break;
      
    case WON:
      reset();
      needsButtonChange("Start");
      state = BEFORE_PLAY;
      break;
      
    case LOST:
      reset();
      needsButtonChange("Start");
      state = BEFORE_PLAY;
      break;
  }
  
  setFocus(Qt::OtherFocusReason);
}

/********** Handle Keyboard Controls *************/
void DefenderCanvas::keyPressEvent(QKeyEvent* event)
{
  // x-axis
  if (event -> key() == Qt::Key_Left)
      transX = -1;
  
  if (event -> key() == Qt::Key_Right)
      transX = 1;
  
  // y-axis
  if (event -> key() == Qt::Key_Up)
      transY = 0;
  if (event -> key() == Qt::Key_Down)
      transY = 0;
  
  // rotations
  if (event -> key() == Qt::Key_X)
      rotate = 1;
  
  if (event -> key() == Qt::Key_Z)
      rotate = -1;
  
  // pressing P pauses game
  if (event -> key() == Qt::Key_P) {
    switch (state) {
      case PAUSED:
        timer -> start();
        idle += (gameWait -> elapsed());
        needsButtonChange("Pause");
        state = PLAYING;
        break;
        
      case PLAYING:
        timer -> stop();
        gameWait -> restart();
        needsButtonChange("Resume");
        state = PAUSED;
        
      default:
        break;
    }
  }
  
  // pressing R resets
  if (event -> key() == Qt::Key_R) {
    resetGame();
  }
  
  // pressing S starts
  if (event -> key() == Qt::Key_S) {
    if (state == BEFORE_PLAY) {
      timer -> start();
      idle = (gameWait -> elapsed());
      needsButtonChange("Pause");
      state = PLAYING;
    }
  }
  
  // create new bullet(s)
  if (event -> key() == Qt::Key_Space) {
    node *n = new node();
    
    // Set position and angle of bullet
    n -> x_position = playerX ;
    n -> y_position = playerY;
    n -> angle = playerTheta;
    
    // adjust linked list
    n -> next = bullets;
    bullets = n;
  }

  update(); 
}

void DefenderCanvas::keyReleaseEvent(QKeyEvent*)
{
  transX = 0;
  transY = 0;
  rotate = 0;
}

/*************** Timer ticked update **************/
void DefenderCanvas::timerTicked()
{
  showTime();
  updateScore();

  level++;
  // Asteroids and their randomness //
  //Random starting position on side
  //int pos = rand_up_to(30);

  //Random angle at which it is travelling
//  int ang = rand_up_to(90);
  
  int freq = rand_up_to(50000);

  //Cue for asteroid to form
  bool form = freq < 100 + (level / 1000000); //Every half second. Change if you want a different level of excitement.

  if (form) {
    node *n = new node();
//    int tempPos = rockDia * pos;
//    if (tempPos <= WIDTH && tempPos >= 0)
//      n -> x_position = WIDTH/2;
//    else {
//      n -> x_position = tempPos;
//    }
    n -> x_position = rand_up_to(WIDTH - rockDia);
    n -> y_position = 0;
//    if (ang + 135 < 225 || ang + 135 > -225)
//      n -> angle = 180;
//    else {
//      n -> angle = ang + 135;
//    }
    n -> size = rockDia*(1 + rand_up_to(4));
    n -> angle = 180;
    n -> next = rocks;
    rocks = n;
  }

  // Implement shooter motion
  playerX += transX*5;
  playerY += transY*5;
  playerTheta += rotate*5;
  
  // keep shooter in bounds
  if (playerX <= SHOOTER_WIDTH/2)
    playerX = SHOOTER_WIDTH/2;
  if (playerX + SHOOTER_WIDTH/2 >= WIDTH) {
    playerX = WIDTH - SHOOTER_WIDTH/2;
  }
  if (playerY <= SHOOTER_HEIGHT/2)
    playerY = SHOOTER_HEIGHT/2;
  if (playerY + SHOOTER_HEIGHT/2 >= HEIGHT) {
    playerY = HEIGHT - SHOOTER_HEIGHT/2;
  }

  // constrain ship rotations
  if (playerTheta <= -maxRotate)
    playerTheta = -maxRotate;
  if (playerTheta >= maxRotate)
    playerTheta = maxRotate;

  /********** Bullet Motion ************/
  node *current = bullets;
  node *prev = NULL;
  
  while (current != NULL) {
    //  PUT COLLISION CHECK CODE HERE
    //Bullet
    int x = current -> x_position;
    int y = current -> y_position;

    node *pre = NULL;

    for(node *cur = rocks; cur != NULL; cur = cur -> next) {
      if(x > cur -> x_position && x < cur -> x_position + (cur -> size) &&
       y > cur -> y_position && y < cur -> y_position + (cur -> size)) {
        if(prev == NULL) {
          bullets = bullets -> next;
          delete(current);
          current = bullets;
        }
        else {
          prev -> next = current -> next;
          delete(current);
          current = prev -> next;
        }
        if(pre == NULL) {
          rocks = rocks -> next;

          delete(cur);
        }
        else {
          pre -> next = cur -> next;
        }
        destroyed++;
      }
      pre = cur;
    }
    if (current == NULL) continue;
    
    // Check to see if they should bounce off walls:
//    if(x + bulletDia > WIDTH || x - bulletDia < 0)
//      current -> angle = -(current -> angle);
    
    //Check to see if bullet is in field. If not, delete it and adjust the adjacent bullets' fields
    if(y < 0 || y > HEIGHT) {
      if(prev == NULL) {
        bullets = current -> next;
//        current -> next -> prev = NULL; // Joe added this--not sure if we need it
        delete(current);
        current = bullets;
      }
      else {
        prev -> next = current -> next;
//        current -> next -> prev = current -> prev; // Also added by Joe
        delete(current);
        current = prev -> next;
      }
    }
    else {
      // These need to be floats during the intermediate arithmatic or they get rounded a ton
      float speed = 5; // Bullet speed
      int vert = -speed * cos((float)(current -> angle) * PI / 180);
      int hori = speed * sin((float)(current -> angle) * PI / 180);
      current -> x_position += hori;
      current -> y_position += vert;
      
      prev = current;
      current = current -> next;
    }
  }

  /********** Asteroid Motion ************/
  node *curr = rocks;
  node *pre = NULL;
  
  while (curr != NULL) {
    
    int x = curr -> x_position;
//    int cosine = cos((float)(playerTheta) * PI / 180);
//    int sine = sin((float)(playerTheta) * PI / 180);
    int y = curr -> y_position;
//    int angle = curr -> angle;
    
    // Check to see if they should bounce off walls:
    if((x + rockDia) > WIDTH || x < 0 )
      curr -> angle = -(curr -> angle);
    
    //UNCOMMENT THE IF STATEMENT WHEN WE FIGURE OUT LOSING. ALSO, THERE IS NO WINNING. ONLY HIGHEST SCORES.
    //Check to see if rock is in field. If not, delete it and adjust the adjacent rocks' fields
    if(y < 0 ) {
      if(pre == NULL) {
        rocks = curr -> next;
        delete(curr);
        curr = rocks;
      }
      else {
        pre -> next = curr -> next;
        delete(curr);
        curr = pre -> next;
      }
    }
    else if (y > HEIGHT - 10 && x < WIDTH && x > 0) {
      timer -> stop();
      state = LOST;
      break;
    }
    else if (x + (curr -> size) > playerX + 10 && x - (curr -> size) < playerX + 10 && y + (curr -> size) > playerY - 20 && y - (curr -> size) < playerY + 20) {
      // collision with ship
      timer -> stop();
      state = LOST;
      break;
    }
    else {
      // These need to be floats during the intermediate arithmatic or they get rounded a ton
      float speed = 1.7; // rocks speed
      int vert = -speed * cos((float)(curr -> angle) * PI / 180);
      int hori = speed * sin((float)(curr -> angle) * PI / 180);
      curr -> x_position += hori;
      curr -> y_position += vert;
      
      pre = curr;
      curr = curr -> next;
    }
  }
  
  update();
}
