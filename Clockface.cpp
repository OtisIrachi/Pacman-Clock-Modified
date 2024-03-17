//************************************************************************
// Clockface.cpp
//
// This is where the 'game' happens
// Controls movement of CLOCK and PACMAN CHARACTERS
//
//************************************************************************
#include "Clockface.h"
#include <ezTime.h>
#include "chomper.h"
#include "pacmanO.h"
#include "pacmanR.h"
#include "pacmanB.h"
#include "pacmanP.h"

unsigned long lastMillisC = 0;
unsigned long lastMillisP = 0;
unsigned long lastMillisR = 0;
unsigned long lastMillisB = 0;
unsigned long lastMillisO = 0;
unsigned long lastMillisMap = 0;
unsigned long lastMillisGhosts = 0;
unsigned long lastMillisTime = 0;
unsigned long lastMillisSec = 0;
unsigned long SecsUpdate = 500;
bool show_seconds = true;
signed int clockOffset;
signed int dateOffset; 
int lastSecond;
int firstnextBlock;
int lastnextBlock;
int accumulatedfoodCount;
int livesScore = 4;
int lastlivesScore;
bool gameEnable = 0;
bool gameStart = 0;
int gamePoints = 0;
int lastcount = 0;
int GameOver = 0;
int pointsOffset = 0;
int pointsLength;
String gamePointStr;

int PacManSpd = 75;     // was 75
int ChomperSpd = 60;    // was 60
int MapSpd = 75;        // was 75
int chomperDieSpd = 200;
int ghostDieSpd = 300;

int UP_DIR;
int DN_DIR;
int LT_DIR;
int RT_DIR;
int TRG_PB;
int go;
int dirc;
bool validSpot;

int nextBlkO;
int nextBlkR;
int nextBlkB;
int nextBlkP;
int nextBlkC;

bool fullBlockO;
bool fullBlockR;
bool fullBlockB;
bool fullBlockP;
bool fullBlockC;

int chomperState;
int PacmanOState;
int PacmanRState;
int PacmanBState;
int PacmanPState;

int ChomperEnable = 0;
int PacmanOEnable = 0;
int PacmanREnable = 0;
int PacmanBEnable = 0;
int PacmanPEnable = 0;

int ChomperCollision = 0;
int PacmanOCollision = 0;
int PacmanRCollision = 0;
int PacmanBCollision = 0;
int PacmanPCollision = 0;

int PacmanOJailedFlag = 0;
int PacmanRJailedFlag = 0;
int PacmanBJailedFlag = 0;
int PacmanPJailedFlag = 0;

int ChomperStoppedFlag = 0;
int PacmanOStoppedFlag = 0;
int PacmanRStoppedFlag = 0;
int PacmanBStoppedFlag = 0;
int PacmanPStoppedFlag = 0;

int ChomperInvincFlag = 0;
int PacmanOInvincFlag = 0;
int PacmanRInvincFlag = 0;
int PacmanBInvincFlag = 0;
int PacmanPInvincFlag = 0;

int ChomperMovingFlag = 1;
int PacmanOMovingFlag = 1;
int PacmanRMovingFlag = 1;
int PacmanBMovingFlag = 1;
int PacmanPMovingFlag = 1;

int chomperxPos, chomperyPos;
int pacmanoxPos, pacmanoyPos;
int pacmanrxPos, pacmanryPos;
int pacmanbxPos, pacmanbyPos;
int pacmanpxPos, pacmanpyPos;

Chomper *chomper;
PacmanO *pacmano;
PacmanR *pacmanr;
PacmanB *pacmanb;
PacmanP *pacmanp;
//*************************************************************************
Clockface::Clockface(Adafruit_GFX* display) 
{
  _display = display;
  Locator::provide(display);
}
//*************************************************************************
void Clockface::setup(CWDateTime *dateTime) 
{
  this->_dateTime = dateTime;
  Locator::getDisplay()->setFont(&Super_Mario_Bros__24pt7b);
  randomSeed(dateTime->getMilliseconds() + millis());
  drawMap();
  gamePoints = 0;
  updateClock();

}
//*************************************************************************
const char* Clockface::weekDayName(int weekday) 
{
  strncpy(weekDayTemp, _weekDayWords + (weekday * 3), 3);
  return weekDayTemp;
}
//*************************************************************************
const char* Clockface::monthName(int month) 
{
  strncpy(monthTemp, _monthWords + ((month-1) * 4), 4);
  return monthTemp;
}
//*************************************************************************
void Clockface::updateStart() 
{
  gamePoints = 0;
  Locator::getDisplay()->fillRect(14, 19, 36, 26, 0x0000);
  // *** This section is for printing Hour and Minutes ***   
  //Locator::getDisplay()->setFont(&hourFont);       // original Font 
  Locator::getDisplay()->setFont(&Super_Mario_Bros__24pt7b);     
  Locator::getDisplay()->setTextColor(YELCOLOR);

  clockOffset = 4;     // print full clock centered
  Locator::getDisplay()->setCursor(15 - clockOffset, 34);  // was 15, 26 
  Locator::getDisplay()->print("Ready!");
      
}
//*************************************************************************
void Clockface::updateScore() 
{
    // First Clear Clock Block, then Print Scores
                       //  fillRect(x,  y,  w,  h,   color)
    Locator::getDisplay()->fillRect(14, 19, 36, 20, 0x0000);
    if(gameEnable == 0)Locator::getDisplay()->fillRect(14, 19, 36, 26, 0x0000);
    
    // ****** This section is for printing Lives Left and Points Score ******
    Locator::getDisplay()->setFont(&Picopixel);
    if(lastlivesScore > livesScore)
      {
      Locator::getDisplay()->setTextColor(REDCOLOR);  
      }
    if(lastlivesScore <= livesScore) 
      {
      Locator::getDisplay()->setTextColor(GREENCOLOR);      
      }
    
     Locator::getDisplay()->setCursor(17, 24);
     Locator::getDisplay()->print("LIVES = ");
     Locator::getDisplay()->setCursor(43, 24);
     Locator::getDisplay()->print(livesScore);  

     Locator::getDisplay()->setTextColor(REDCOLOR);  
     Locator::getDisplay()->setCursor(21, 30);
     Locator::getDisplay()->print("POINTS");

     gamePointStr = String(gamePoints);
     
     pointsLength = gamePointStr.length();      // int
     pointsOffset = ((64 - (pointsLength * 4)) / 2);  // 

     Locator::getDisplay()->setCursor(pointsOffset, 36);
     Locator::getDisplay()->print(gamePoints);
       
     lastlivesScore = livesScore;
     if(gameEnable == 0)
       {
       delay(3000);
       Locator::getDisplay()->fillRect(14, 19, 36, 26, 0x0000);       
       }
     
  if(livesScore == 0)
     {
     GameOver = 1;
     Locator::getDisplay()->fillRect(14, 19, 36, 26, 0x0000);

     Locator::getDisplay()->setFont(&Picopixel);    
     Locator::getDisplay()->setTextColor(REDCOLOR);

     clockOffset = 0;     // print full clock centered
     Locator::getDisplay()->setCursor(24, 35);  // was 15, 26 
     Locator::getDisplay()->print("GAME");
     Locator::getDisplay()->setCursor(24, 42);  // was 15, 26 
     Locator::getDisplay()->print("OVER!");
     
     if(GameOver == 1)
        {
        delay(3000);
        Locator::getDisplay()->fillRect(14, 19, 36, 26, 0x0000);
        }
        
     livesScore = 4;
     lastlivesScore = livesScore;  
     GameOver = 0;   
     }
 
}
//*************************************************************************
void Clockface::updateClock() 
{
      
    Locator::getDisplay()->fillRect(14, 19, 36, 26, 0x0000);

    // *** This section is for printing Month, Day, Year ***
    Locator::getDisplay()->setFont(&Picopixel);
    Locator::getDisplay()->setTextColor(DATECOLOR);
        
    if((this->_dateTime->getMonth()) == 3) dateOffset = 2;
    else if((this->_dateTime->getMonth()) == 11) dateOffset = 1;
    else dateOffset = 0;
    //Serial.print("month# = "); Serial.println(this->_dateTime->getMonth());
    
    Locator::getDisplay()->setCursor(18 - dateOffset, 35);
    Locator::getDisplay()->print(monthName(this->_dateTime->getMonth()));
    Locator::getDisplay()->print(" ");
    Locator::getDisplay()->print(this->_dateTime->getDay());
    Locator::getDisplay()->print(" ");
    Locator::getDisplay()->print(this->_dateTime->getYear());
    Locator::getDisplay()->print(" "); 
    
    Locator::getDisplay()->setCursor(26, 42);   
    Locator::getDisplay()->print(weekDayName(this->_dateTime->getWeekday()));
    Locator::getDisplay()->print("  ");
   
    // *** This section is for printing Hour and Minutes ***   
    //Locator::getDisplay()->setFont(&hourFont);       // original Font 
    Locator::getDisplay()->setFont(&Super_Mario_Bros__24pt7b);     
    Locator::getDisplay()->setTextColor(CLOCKCOLOR);

    if(((this->_dateTime->getHour()) < 10)) 
       {
       clockOffset = 4;     // shift short clock display to the left 
       Locator::getDisplay()->setCursor(15 + clockOffset, 28);
       Locator::getDisplay()->print(this->_dateTime->getHour("00"));         
       Locator::getDisplay()->setCursor(34 - clockOffset, 28);  // was 15, 26 
       Locator::getDisplay()->print(this->_dateTime->getMinute("00"));    
       }
    else 
       {
       clockOffset = 0;     // print full clock centered
       Locator::getDisplay()->setCursor(15 - clockOffset, 28);  // was 15, 26 
       Locator::getDisplay()->print(this->_dateTime->getHour("00"));         
       Locator::getDisplay()->setCursor(34 - clockOffset, 28);  // was 15, 26        
       Locator::getDisplay()->print(this->_dateTime->getMinute("00"));       
       }
    
}
//*************************************************************************
void Clockface::displayFood()
{
    // Display FOOD and SUPER_FOOD behind Ghost Characters
        for (int i = 0; i < MAP_SIZE; i++) 
           {
           for (int j = 0; j < MAP_SIZE; j++) 
              {
              if (_MAP[j][i] == MapBlock::FOOD)  
                 {
                 Locator::getDisplay()->fillRect((i * 5) + 4, (j * 5) + 4, 1, 1, WHTCOLOR);  // Set Food Size
                 }
              if (_MAP[j][i] == MapBlock::GATE)  
                 {
                 Locator::getDisplay()->fillRect((i * 5) + 4, (j * 5) + 4, 1, 1, WHTCOLOR);  // Set Food Size
                 }                 
              if (_MAP[j][i] == MapBlock::SUPER_FOOD)  
                 {
                 Locator::getDisplay()->fillRect((i * 5) + 3, (j * 5) + 3, 3, 3, ORANGCOLOR);
                 }                    
              }
           }  
}// End displayFood
//*************************************************************************
void Clockface::update()
{
   // Joystick Trigger will toggle from Demo Mode to Game Mode
   if(TRG_PB == 1)
      {
      gameStart = gameStart ^ 1;
      gameEnable = gameEnable ^ 1;
      }
   if(gameStart == 1)
      {   
      Locator::getDisplay()->fillRect(0, 63, 0, 63, 0x0000);
      this->updateStart();
      delay(3000);
      Locator::getDisplay()->fillRect(0, 63, 0, 63, 0x0000);
      gameStart = 0;
      resetMap();
      Locator::getDisplay()->fillRect(14, 19, 36, 26, 0x0000); 
      if(gameEnable == 0) updateClock();      
      }

  if(gameEnable == 0)
  {
  //**************************************************
  // Seconds blink  
  if ((millis() - lastMillisSec) >= 1000) 
    {   
    if (show_seconds) 
      {
      Locator::getDisplay()->fillRect(31 - clockOffset, 23, 2, 2, CLOCKCOLOR);   // show colon
      Locator::getDisplay()->fillRect(31 - clockOffset, 26, 2, 2, CLOCKCOLOR);
      } 
    else  
      {
      Locator::getDisplay()->fillRect(31 - clockOffset, 23, 2, 2, 0);       // clear colon
      Locator::getDisplay()->fillRect(31 - clockOffset, 26, 2, 2, 0);
      }

    if(this->_dateTime->getSecond() == 59)
       {

       //resetMap();
       }
   
    show_seconds = !show_seconds;
    lastMillisSec = millis();
 
    }// End If lastMillisSec
  }// End if gameEnable 
  //*******************************************************************
  // Update Clock
  if (millis() - lastMillisTime >= 60000) 
    {   
    if(gameEnable == 0) updateClock();
    lastMillisTime = millis();
    }
  //*******************************************************************
/*
Locator::getDisplay()->drawRGBBitmap(14, 39, _PACMANO_CONST[1], 5, 5);
Locator::getDisplay()->drawRGBBitmap(20, 39, _PACMANR_CONST[1], 5, 5);  
Locator::getDisplay()->drawRGBBitmap(39, 39, _PACMANB_CONST[1], 5, 5);    
Locator::getDisplay()->drawRGBBitmap(45, 39, _PACMANP_CONST[1], 5, 5); 
*/
//******************************************************************************************************
// BEGIN GHOST MILLIS SCAN *****************************************************************************
//******************************************************************************************************          
  //*************************************************************** 
  // Update pacmano  "CLYDE" **************************************
  //*************************************************************** 
if (millis() - lastMillisO >= PacManSpd) 
    {        
  if(PacmanOEnable == 1)  // "0" turns off Pacman
    {
    displayFood();                           
    if(PacmanOState != PacmanO::State::JAILED)
    {          
    
    fullBlockO = // X axis
                     ((pacmano->_directiono == Direction::LEFT || pacmano->_directiono == Direction::RIGHT) && (pacmano->getX()-2) % 5 == 0) ||
                  // Y axis
                     ((pacmano->_directiono == Direction::UP || pacmano->_directiono == Direction::DOWN) && (pacmano->getY()-2) % 5 == 0);  

     pacmanoyPos = pacmano->getY();
     pacmanoxPos = pacmano->getX();
   
    // Plots next Pacman Move
    if (fullBlockO) 
      {      
      MapBlock nextBlkO = nextBlockO();
      directionDecisionO(nextBlkO, (pacmano->_directiono == Direction::LEFT || pacmano->_directiono == Direction::RIGHT));  
      }// End fullBlockO
      
      //********************************************************************
      if ((chomperyPos == pacmanoyPos) && (chomperxPos == pacmanoxPos) || (chomperyPos + 1 == pacmanoyPos) && (chomperxPos == pacmanoxPos) || (chomperyPos == pacmanoyPos) && (chomperxPos + 1 == pacmanoxPos)
      || (chomperyPos - 1 == pacmanoyPos) && (chomperxPos == pacmanoxPos) || (chomperyPos == pacmanoyPos) && (chomperxPos - 1 == pacmanoxPos))
         {
         ChomperCollision = 1; 
         PacmanOCollision = 1; 
         }
      else
         {
         ChomperCollision = 0; 
         PacmanOCollision = 0;                  
         }

      //*****************************************************
      // If Chomper and CLYDE Collide
      if((PacmanOCollision == 1) && (ChomperCollision == 1))
         {
         if(PacmanOInvincFlag == 1)
            {
            pacmano->setState(PacmanO::State::JAILED); 
            gamePoints = gamePoints + 200;                
            }
                    
         if((PacmanOInvincFlag == 0) && (ChomperInvincFlag == 0))
            {
            chomper->setState(Chomper::State::STOPPED); 
            livesScore--;
            updateScore(); 
            if(gameEnable == 0)gamePoints = 0; 
            Locator::getDisplay()->fillRect(14, 19, 36, 26, 0x0000);         
            resetMap();           
            }    
         }// End PacmanOCollision
    }// End If Pacman JAILED 
         
    pacmano->update();  // scans immediately
    
    }// End If PacmanOEnable  
    else
     {

     }
     
    //**************************************************************
    lastMillisO = millis(); 
  }// End lastmillisO    
  //*******************************************************************
  // Update pacmanr  "BLINKY"
if (millis() - lastMillisR >= PacManSpd) 
    {       
  if(PacmanREnable == 1)   // "0" turns off Pacman
    {
    //displayFood();      
  if(PacmanRState != PacmanR::State::JAILED)
    { 
    fullBlockR = // X axis
                     ((pacmanr->_directionr == Direction::LEFT || pacmanr->_directionr == Direction::RIGHT) && (pacmanr->getX()-2) % 5 == 0) ||
                 // Y axis
                     ((pacmanr->_directionr == Direction::UP || pacmanr->_directionr == Direction::DOWN) && (pacmanr->getY()-2) % 5 == 0);                     

    pacmanryPos = pacmanr->getY();
    pacmanrxPos = pacmanr->getX();

   
    if (fullBlockR) 
      {          
      MapBlock nextBlkR = nextBlockR();
      directionDecisionR(nextBlkR, (pacmanr->_directionr == Direction::LEFT || pacmanr->_directionr == Direction::RIGHT));
      }// End fullBlockR
      
      //***********************************************************************              
      if ((chomperyPos == pacmanryPos) && (chomperxPos == pacmanrxPos) || (chomperyPos + 1 == pacmanryPos) && (chomperxPos == pacmanrxPos) || (chomperyPos == pacmanryPos) && (chomperxPos + 1 == pacmanrxPos)
      || (chomperyPos - 1 == pacmanryPos) && (chomperxPos == pacmanrxPos) || (chomperyPos == pacmanryPos) && (chomperxPos - 1 == pacmanrxPos))
         {
         ChomperCollision = 1; 
         PacmanRCollision = 1;       
         }
      else
         {
         ChomperCollision = 0; 
         PacmanRCollision = 0;    
         } 

      //*****************************************************
      // If Chomper and RED Collide
      if((PacmanRCollision == 1) && (ChomperCollision == 1))
         {
         if((PacmanRInvincFlag == 1))
            {
            pacmanr->setState(PacmanR::State::JAILED);
            gamePoints = gamePoints + 200;                        
            }
         if((PacmanRInvincFlag == 0) && (ChomperInvincFlag == 0))
            {
            chomper->setState(Chomper::State::STOPPED); 
            livesScore--;
            updateScore();
            if(gameEnable == 0)gamePoints = 0; 
            Locator::getDisplay()->fillRect(14, 19, 36, 26, 0x0000);  
            resetMap();                          
            }    
         }// End PacmanRCollision 
      }// End If Pacman JAILED       
      
      pacmanr->update();

  }// End If PacmanREnable  
    else
     {

     }
    //**************************************************************
    lastMillisR = millis(); 
  }// End lastmillisR                   
  //*******************************************************************
  // Update pacmanb  "INKY"
if (millis() - lastMillisB >= PacManSpd) 
    {            
  if(PacmanBEnable == 1)   // "0" turns off Pacman
    { 
        
  if(PacmanBState != PacmanB::State::JAILED)
    {
    //displayFood();       
    fullBlockB = // X axis
                     ((pacmanb->_directionb == Direction::LEFT || pacmanb->_directionb == Direction::RIGHT) && (pacmanb->getX()-2) % 5 == 0) ||
                 // Y axis
                     ((pacmanb->_directionb == Direction::UP || pacmanb->_directionb == Direction::DOWN) && (pacmanb->getY()-2) % 5 == 0);                     

    pacmanbyPos = pacmanb->getY();
    pacmanbxPos = pacmanb->getX();

    
    if (fullBlockB) 
      {               
      MapBlock nextBlkB = nextBlockB();
      directionDecisionB(nextBlkB, (pacmanb->_directionb == Direction::LEFT || pacmanb->_directionb == Direction::RIGHT));
      }// End fullBlockB
      
      //***********************************************************************  
      if ((chomperyPos == pacmanbyPos) && (chomperxPos == pacmanbxPos) || (chomperyPos + 1 == pacmanbyPos) && (chomperxPos == pacmanbxPos) || (chomperyPos == pacmanbyPos) && (chomperxPos + 1 == pacmanbxPos)
      || (chomperyPos - 1 == pacmanbyPos) && (chomperxPos == pacmanbxPos) || (chomperyPos == pacmanbyPos) && (chomperxPos - 1 == pacmanbxPos))
         {
         ChomperCollision = 1; 
         PacmanBCollision = 1;     
         }
      else
         {
         ChomperCollision = 0; 
         PacmanBCollision = 0;    
         }

      //*****************************************************
      // If Chomper and BLUE Collide
      if((PacmanBCollision == 1) && (ChomperCollision == 1))
         {
         if((PacmanBInvincFlag == 1))
            {
            pacmanb->setState(PacmanB::State::JAILED); 
            gamePoints = gamePoints + 200;                   
            }
         if((PacmanBInvincFlag == 0) && (ChomperInvincFlag == 0))
            {
            chomper->setState(Chomper::State::STOPPED);       
            livesScore--;
            updateScore();
            if(gameEnable == 0)gamePoints = 0;       
            Locator::getDisplay()->fillRect(14, 19, 36, 26, 0x0000); 
            resetMap();                       
            }               
         }// End PacmanBCollision 
    }// End If Pacman JAILED 
            
    pacmanb->update();       
    }// End If PacmanBEnable  
    
    else
     {

     } 
    //**************************************************************
    lastMillisB = millis(); 
  }// End lastmillisB          
  //*******************************************************************
  // Update pacmanp  "PINK"
if (millis() - lastMillisP >= PacManSpd) 
    {              
  if(PacmanPEnable == 1)   // "0" turns off Pacman
    {
    //displayFood();     
  if(PacmanPState != PacmanP::State::JAILED)
    {   
    fullBlockP = // X axis
                     ((pacmanp->_directionp == Direction::LEFT || pacmanp->_directionp == Direction::RIGHT) && (pacmanp->getX()-2) % 5 == 0) ||
                 // Y axis
                     ((pacmanp->_directionp == Direction::UP || pacmanp->_directionp == Direction::DOWN) && (pacmanp->getY()-2) % 5 == 0);                     

    pacmanpyPos = pacmanp->getY();
    pacmanpxPos = pacmanp->getX();

    
    if (fullBlockP) 
      {              
      MapBlock nextBlkP = nextBlockP();
      directionDecisionP(nextBlkP, (pacmanp->_directionp == Direction::LEFT || pacmanp->_directionp == Direction::RIGHT));                              
      }// End fullBlockG
      

      //***********************************************************************  
      if ((chomperyPos == pacmanpyPos) && (chomperxPos == pacmanpxPos) || (chomperyPos + 1 == pacmanpyPos) && (chomperxPos == pacmanpxPos) || (chomperyPos == pacmanpyPos) && (chomperxPos + 1 == pacmanpxPos)
      || (chomperyPos - 1 == pacmanpyPos) && (chomperxPos == pacmanpxPos) || (chomperyPos == pacmanpyPos) && (chomperxPos - 1 == pacmanpxPos))
         {
         ChomperCollision = 1; 
         PacmanPCollision = 1; 
         }
      else
         {
         ChomperCollision = 0; 
         PacmanPCollision = 0;    
         }
       
      //*****************************************************
      // If Chomper and PINK Collide
      if((PacmanPCollision == 1) && (ChomperCollision == 1))
         { 
         if((PacmanPInvincFlag == 1))
            {
            pacmanp->setState(PacmanP::State::JAILED); 
            gamePoints = gamePoints + 200;                       
            }
         if((PacmanPInvincFlag == 0) && (ChomperInvincFlag == 0))
            {
            chomper->setState(Chomper::State::STOPPED); 
            livesScore--;
            updateScore(); 
            if(gameEnable == 0)gamePoints = 0;     
            Locator::getDisplay()->fillRect(14, 19, 36, 26, 0x0000); 
            resetMap();                                    
            }    
         }// End PacmanPCollision    
    }// End If Pacman JAILED 
      
    pacmanp->update();
    
    }// End If PacmanPEnable 
     
  else
     {
     
     }
         
    //**************************************************************
    lastMillisP = millis(); 
  }// End lastmillisP
//    lastMillisGhosts = millis(); 
//  }// End lastmillisGhosts   
  //***********************************************************************************
  // END GHOST SECTION ****************************************************************
  //***********************************************************************************       
  //***********************************************************************************
  // UPDATE CHOMPER AND GAME DECISIONS ************************************************
  //***********************************************************************************  
  if(ChomperEnable == 1)   // "0" turns off Chomper
    {
  if (millis() - lastMillisC >= ChomperSpd)   // '60' makes Chomper a little faster
    {         
    fullBlockC = // X axis
                     ((chomper->_directionc == Direction::LEFT || chomper->_directionc == Direction::RIGHT) && (chomper->getX()-2) % 5 == 0) ||
                     // Y axis
                     ((chomper->_directionc == Direction::UP || chomper->_directionc == Direction::DOWN) && (chomper->getY()-2) % 5 == 0);

    chomperyPos = chomper->getY();
    chomperxPos = chomper->getX();
    
    if (fullBlockC) 
      {            
      MapBlock nextBlkC = nextBlockC();
      
    if(gameEnable == 0)
      {      
      directionDecisionC(nextBlkC, (chomper->_directionc == Direction::LEFT || chomper->_directionc == Direction::RIGHT));
      chomper->move(Direction::HALT, DirectionM::MOVE_Y);
      }    
     
      _MAP[(chomper->getY()-2)/5][(chomper->getX()-2)/5] = MapBlock::EMPTY;   // EMPTY = 0

  if(gameEnable == 1)
    {
    // *********************THIS SECTION WORKS!!!***********************************
      if(UP_DIR == 1)
         {
         Serial.println("if(UP_DIR == 1)");       
         validSpot = compareTestJoy(nextBlockC(Direction::UP), CHOMPER_MOVING_BLOCKS);  
         Serial.print("validSpot = ");
         Serial.println(validSpot);     
         if(validSpot == true)
         {
         dirc = Direction::UP;
         chomper->turn(static_cast<Direction>(dirc));
         go = DirectionM::MOVE_Y;
         chomper->move(Direction::UP, DirectionM::MOVE_Y);
         } 
         if(validSpot == false) 
         {
         go = DirectionM::MOVE_N; 
         chomper->move(Direction::HALT, DirectionM::MOVE_N);                   
         }
         }              
       else if(DN_DIR == 1)
         {
         Serial.println("if(DN_DIR == 1)");
         validSpot = compareTestJoy(nextBlockC(Direction::DOWN), CHOMPER_MOVING_BLOCKS);
         if(validSpot == true)
         {
         dirc = Direction::DOWN;
         chomper->turn(static_cast<Direction>(dirc));
         go = DirectionM::MOVE_Y;  
         chomper->move(Direction::DOWN, DirectionM::MOVE_Y);
         }
         if(validSpot == false) 
         {
         go = DirectionM::MOVE_N; 
         chomper->move(Direction::HALT, DirectionM::MOVE_N);                   
         }
         }             
      else if(LT_DIR == 1)
         {
         Serial.println("if(LT_DIR == 1)");
         validSpot = compareTestJoy(nextBlockC(Direction::LEFT), CHOMPER_MOVING_BLOCKS);
         if(validSpot == true)
         {
         dirc = Direction::LEFT;
         chomper->turn(static_cast<Direction>(dirc));
         go = DirectionM::MOVE_Y; 
         chomper->move(Direction::LEFT, DirectionM::MOVE_Y);
         }
         if(validSpot == false) 
         {
         go = DirectionM::MOVE_N; 
         chomper->move(Direction::HALT, DirectionM::MOVE_N);                   
         }
         }      
      else if(RT_DIR == 1)
         {
         Serial.println("if(RT_DIR == 1)");
         validSpot = compareTestJoy(nextBlockC(Direction::RIGHT), CHOMPER_MOVING_BLOCKS); 
         if(validSpot == true)
         {
         dirc = Direction::RIGHT;
         chomper->turn(static_cast<Direction>(dirc));
         go = DirectionM::MOVE_Y;
         chomper->move(Direction::RIGHT, DirectionM::MOVE_Y);
         }
         if(validSpot == false) 
         {
         go = DirectionM::MOVE_N; 
         chomper->move(Direction::HALT, DirectionM::MOVE_N);                   
         }
         }
      else
         {                  
         go = DirectionM::MOVE_N; 
         chomper->move(Direction::HALT, DirectionM::MOVE_N);   
         }
   
    updateScore();
    }// End if gameEnable 
    
      // Makes Chomper Invincible
      if (nextBlkC == MapBlock::SUPER_FOOD) // SUPER_FOOD = 4
        {
        chomper->setState(Chomper::State::INVENCIBLE);
        if((PacmanOState != PacmanO::State::JAILED) && (PacmanOEnable == 1))
           {        
           pacmano->setState(PacmanO::State::INVENCIBLE);   // CLYDE
           }
        if((PacmanRState != PacmanR::State::JAILED) && (PacmanREnable == 1)) 
           {
           pacmanr->setState(PacmanR::State::INVENCIBLE);   // BLINKY
           }
        if((PacmanBState != PacmanB::State::JAILED) && (PacmanBEnable == 1)) 
           {
           pacmanb->setState(PacmanB::State::INVENCIBLE);   // INKY
           }
        if((PacmanPState != PacmanP::State::JAILED) && (PacmanPEnable == 1)) 
           {
           pacmanp->setState(PacmanP::State::INVENCIBLE);   // PINKY       
           }
        }// End if nextBlkC
        
      if((PacmanOState == PacmanO::State::JAILED) && (PacmanRState == PacmanR::State::JAILED) && (PacmanBState == PacmanB::State::JAILED) && (PacmanPState == PacmanP::State::JAILED))
         {         
         livesScore++;
         updateScore(); 
         delay(3000);
         resetMap();                                       
         }
                           
      if (countBlocks(MapBlock::FOOD) == 0) 
        {       
        livesScore++;
        updateScore();
        delay(3000);         
        resetMap();
        } 
                                      
      }// End if(fullBlockC)
     
      //*****************************************************  
      //chomper->setState(Chomper::State::MOVING); 
      chomper->update();

      lastMillisC = millis();
    }// End if(millisC)
  }// End If ChomperEnable
    
}// End Clockface::update
//*************************************************************************
//*************************************************************************
//*************************************************************************
void Clockface::directionDecisionC(MapBlock nextBlk, bool moving_axis_x) 
{

  if (compareTest(nextBlk, CHOMPER_BLOCKING_BLOCKS)) 
    {
    turnRandomC();
    } 

  else if (moving_axis_x && compareTest(nextBlockC(Direction::DOWN), CHOMPER_MOVING_BLOCKS) && random(100) % 2 == 0) 
    {
    chomper->turn(Direction::DOWN);
    } 
  else if (moving_axis_x && compareTest(nextBlockC(Direction::UP), CHOMPER_MOVING_BLOCKS) && random(100) % 2 == 0) 
    {
    chomper->turn(Direction::UP);
    } 
  else if (!moving_axis_x && compareTest(nextBlockC(Direction::LEFT), CHOMPER_MOVING_BLOCKS) && random(100) % 2 == 0) 
    {
    chomper->turn(Direction::LEFT);
    } 
  else if (!moving_axis_x && compareTest(nextBlockC(Direction::RIGHT), CHOMPER_MOVING_BLOCKS) && random(100) % 2 == 0) 
    {
    chomper->turn(Direction::RIGHT);
    }

}
//*************************************************************************
void Clockface::directionDecisionO(MapBlock nextBlk, bool moving_axis_x) 
{
  if (compareTest(nextBlk, PACMANO_BLOCKING_BLOCKS)) 
    {
    turnRandomO();
    } 
  else if (moving_axis_x && compareTest(nextBlockO(Direction::DOWN), PACMANO_MOVING_BLOCKS) && random(100) % 2 == 0) 
    {
    pacmano->turn(Direction::DOWN);
    } 
  else if (moving_axis_x && compareTest(nextBlockO(Direction::UP), PACMANO_MOVING_BLOCKS) && random(100) % 2 == 0) 
    {
    pacmano->turn(Direction::UP);
    } 
  else if (!moving_axis_x && compareTest(nextBlockO(Direction::LEFT), PACMANO_MOVING_BLOCKS) && random(100) % 2 == 0) 
    {
    pacmano->turn(Direction::LEFT);
    } 
  else if (!moving_axis_x && compareTest(nextBlockO(Direction::RIGHT), PACMANO_MOVING_BLOCKS) && random(100) % 2 == 0) 
    {
    pacmano->turn(Direction::RIGHT);
    }

}
//*************************************************************************
void Clockface::directionDecisionR(MapBlock nextBlk, bool moving_axis_x) 
{
  if (compareTest(nextBlk, PACMANR_BLOCKING_BLOCKS)) 
    {
    turnRandomR();
    } 
  else if (moving_axis_x && compareTest(nextBlockR(Direction::DOWN), PACMANR_MOVING_BLOCKS) && random(100) % 2 == 0) 
    {
    pacmanr->turn(Direction::DOWN);
    } 
  else if (moving_axis_x && compareTest(nextBlockR(Direction::UP), PACMANR_MOVING_BLOCKS) && random(100) % 2 == 0) 
    {
    pacmanr->turn(Direction::UP);
    } 
  else if (!moving_axis_x && compareTest(nextBlockR(Direction::LEFT), PACMANR_MOVING_BLOCKS) && random(100) % 2 == 0) 
    {
    pacmanr->turn(Direction::LEFT);
    } 
  else if (!moving_axis_x && compareTest(nextBlockR(Direction::RIGHT), PACMANR_MOVING_BLOCKS) && random(100) % 2 == 0) 
    {
    pacmanr->turn(Direction::RIGHT);
    }

}
//*************************************************************************
void Clockface::directionDecisionB(MapBlock nextBlk, bool moving_axis_x) 
{
  if (compareTest(nextBlk, PACMANB_BLOCKING_BLOCKS)) 
    {
    turnRandomB();
    } 
  else if (moving_axis_x && compareTest(nextBlockB(Direction::DOWN), PACMANB_MOVING_BLOCKS) && random(100) % 2 == 0) 
    {
    pacmanb->turn(Direction::DOWN);
    } 
  else if (moving_axis_x && compareTest(nextBlockB(Direction::UP), PACMANB_MOVING_BLOCKS) && random(100) % 2 == 0) 
    {
    pacmanb->turn(Direction::UP);
    } 
  else if (!moving_axis_x && compareTest(nextBlockB(Direction::LEFT), PACMANB_MOVING_BLOCKS) && random(100) % 2 == 0) 
    {
    pacmanb->turn(Direction::LEFT);
    } 
  else if (!moving_axis_x && compareTest(nextBlockB(Direction::RIGHT), PACMANB_MOVING_BLOCKS) && random(100) % 2 == 0) 
    {
    pacmanb->turn(Direction::RIGHT);
    }

}
//*************************************************************************
void Clockface::directionDecisionP(MapBlock nextBlk, bool moving_axis_x) 
{
  if (compareTest(nextBlk, PACMANP_BLOCKING_BLOCKS)) 
    {
    turnRandomP();
    } 
  else if (moving_axis_x && compareTest(nextBlockP(Direction::DOWN), PACMANP_MOVING_BLOCKS) && random(100) % 2 == 0) 
    {
    pacmanp->turn(Direction::DOWN);
    } 
  else if (moving_axis_x && compareTest(nextBlockP(Direction::UP), PACMANP_MOVING_BLOCKS) && random(100) % 2 == 0) 
    {
    pacmanp->turn(Direction::UP);
    } 
  else if (!moving_axis_x && compareTest(nextBlockP(Direction::LEFT), PACMANP_MOVING_BLOCKS) && random(100) % 2 == 0) 
    {
    pacmanp->turn(Direction::LEFT);
    } 
  else if (!moving_axis_x && compareTest(nextBlockP(Direction::RIGHT), PACMANP_MOVING_BLOCKS) && random(100) % 2 == 0) 
    {
    pacmanp->turn(Direction::RIGHT);
    }

}
//*************************************************************************
void Clockface::resetMap() 
{

  memcpy( _MAP, _MAP_CONST, sizeof(_MAP_CONST) );
  drawMap();
  if(gameEnable == 0) 
    {
    Locator::getDisplay()->fillRect(14, 19, 36, 26, 0x0000); 
    updateClock();
    }
  if(gameEnable == 1) 
    {
    Locator::getDisplay()->fillRect(14, 19, 36, 26, 0x0000); 
    updateScore();
    }
  
}
//*************************************************************************
void Clockface::turnRandomC() 
{
  int dirc = random(4);

  do {
    chomper->turn(static_cast<Direction>(dirc));
    dirc = random(4); 
  } while (!compareTest(nextBlockC(), CHOMPER_MOVING_BLOCKS));
  
}
//*************************************************************************
void Clockface::turnRandomO() 
{
  int diro = random(4);
  
    do {
    //            static_cast<type> (object);
    pacmano->turn(static_cast<Direction>(diro));
    diro = random(4); 
  } while (!compareTest(nextBlockO(), PACMANO_MOVING_BLOCKS));

}
//*************************************************************************
void Clockface::turnRandomR() 
{
  int dirr = random(4);
  
    do {
    //            static_cast<type> (object);
    pacmanr->turn(static_cast<Direction>(dirr));
    dirr = random(4); 
  } while (!compareTest(nextBlockR(), PACMANR_MOVING_BLOCKS));

}
//*************************************************************************
void Clockface::turnRandomB() 
{
  int dirb = random(4);
  
    do {
    //            static_cast<type> (object);
    pacmanb->turn(static_cast<Direction>(dirb));
    dirb = random(4); 
  } while (!compareTest(nextBlockB(), PACMANB_MOVING_BLOCKS));

}
//*************************************************************************
void Clockface::turnRandomP() 
{
  int dirp = random(4);
  
    do {
    //            static_cast<type> (object);
    pacmanp->turn(static_cast<Direction>(dirp));
    dirp = random(4); 
  } while (!compareTest(nextBlockP(), PACMANP_MOVING_BLOCKS));

}
//*************************************************************************
Clockface::MapBlock Clockface::nextBlockC() 
{
  return nextBlockC(chomper->_directionc);
}
//*************************************************************************
Clockface::MapBlock Clockface::nextBlockO() 
{
  return nextBlockO(pacmano->_directiono);
}
//*************************************************************************
Clockface::MapBlock Clockface::nextBlockR() 
{
  return nextBlockR(pacmanr->_directionr);
}
//*************************************************************************
Clockface::MapBlock Clockface::nextBlockB() 
{
  return nextBlockB(pacmanb->_directionb);
}
//*************************************************************************
Clockface::MapBlock Clockface::nextBlockP() 
{
  return nextBlockP(pacmanp->_directionp);
}
//*************************************************************************
Clockface::MapBlock Clockface::nextBlockC(Direction dir) 
{
  Clockface::MapBlock map_block = Clockface::MapBlock::OUT_OF_MAP;

  if (dir == Direction::RIGHT) 
    {
    if (chomper->getX() + chomper->SPRITE_SIZE < MAP_MAX_POS) 
      {
      map_block = static_cast<MapBlock>(_MAP[(chomper->getY()-2)/5][((chomper->getX()-2)/5)+1]);
      }   
    } 
    
  else if (dir == Direction::DOWN) 
    {
    if (chomper->getY() + chomper->SPRITE_SIZE < MAP_MAX_POS) 
      {
      map_block = static_cast<MapBlock>(_MAP[((chomper->getY()-2)/5)+1][(chomper->getX()-2)/5]);
      }
    }
     
  else if (dir == Direction::LEFT) 
    {
    if ((chomper->getX()-2) > 0) 
      {
      map_block = static_cast<MapBlock>(_MAP[(chomper->getY()-2)/5][((chomper->getX()-2)/5)-1]);
      }
    } 
    
  else if (dir == Direction::UP) 
    {
    if ((chomper->getY()-2) > 0) 
      {
      map_block = static_cast<MapBlock>(_MAP[((chomper->getY()-2)/5)-1][((chomper->getX()-2)/5)]);
      }
    }

  return map_block;

}
//*************************************************************************
Clockface::MapBlock Clockface::nextBlockO(Direction dir) 
{

  Clockface::MapBlock map_block = Clockface::MapBlock::OUT_OF_MAP;

  if (dir == Direction::RIGHT) 
    {
    if (pacmano->getX()+pacmano->SPRITE_SIZE < MAP_MAX_POS) 
      {
      map_block = static_cast<MapBlock>(_MAP[(pacmano->getY()-2)/5][((pacmano->getX()-2)/5)+1]);
      }   
    } 
    
  else if (dir == Direction::DOWN) 
    {
    if (pacmano->getY()+pacmano->SPRITE_SIZE < MAP_MAX_POS) 
      {
      map_block = static_cast<MapBlock>(_MAP[((pacmano->getY()-2)/5)+1][(pacmano->getX()-2)/5]);
      }
    }
     
  else if (dir == Direction::LEFT) 
    {
    if ((pacmano->getX()-2) > 0) 
      {
      map_block = static_cast<MapBlock>(_MAP[(pacmano->getY()-2)/5][((pacmano->getX()-2)/5)-1]);
      }
    } 
    
  else if (dir == Direction::UP) 
    {
    if ((pacmano->getY()-2) > 0) 
      {
      map_block = static_cast<MapBlock>(_MAP[((pacmano->getY()-2)/5)-1][((pacmano->getX()-2)/5)]);
      }
    }

  return map_block;

}
//*************************************************************************
Clockface::MapBlock Clockface::nextBlockR(Direction dir) 
{

  Clockface::MapBlock map_block = Clockface::MapBlock::OUT_OF_MAP;

  if (dir == Direction::RIGHT) 
    {
    if (pacmanr->getX()+pacmanr->SPRITE_SIZE < MAP_MAX_POS) 
      {
      map_block = static_cast<MapBlock>(_MAP[(pacmanr->getY()-2)/5][((pacmanr->getX()-2)/5)+1]);
      }   
    } 
    
  else if (dir == Direction::DOWN) 
    {
    if (pacmanr->getY()+pacmanr->SPRITE_SIZE < MAP_MAX_POS) 
      {
      map_block = static_cast<MapBlock>(_MAP[((pacmanr->getY()-2)/5)+1][(pacmanr->getX()-2)/5]);
      }
    }
     
  else if (dir == Direction::LEFT) 
    {
    if ((pacmanr->getX()-2) > 0) 
      {
      map_block = static_cast<MapBlock>(_MAP[(pacmanr->getY()-2)/5][((pacmanr->getX()-2)/5)-1]);
      }
    } 
    
  else if (dir == Direction::UP) 
    {
    if ((pacmanr->getY()-2) > 0) 
      {
      map_block = static_cast<MapBlock>(_MAP[((pacmanr->getY()-2)/5)-1][((pacmanr->getX()-2)/5)]);
      }
    }

  return map_block;

}
//*************************************************************************
Clockface::MapBlock Clockface::nextBlockB(Direction dir) 
{

  Clockface::MapBlock map_block = Clockface::MapBlock::OUT_OF_MAP;

  if (dir == Direction::RIGHT) 
    {
    if (pacmanb->getX()+pacmanb->SPRITE_SIZE < MAP_MAX_POS) 
      {
      map_block = static_cast<MapBlock>(_MAP[(pacmanb->getY()-2)/5][((pacmanb->getX()-2)/5)+1]);
      }   
    } 
    
  else if (dir == Direction::DOWN) 
    {
    if (pacmanb->getY()+pacmanb->SPRITE_SIZE < MAP_MAX_POS) 
      {
      map_block = static_cast<MapBlock>(_MAP[((pacmanb->getY()-2)/5)+1][(pacmanb->getX()-2)/5]);
      }
    }
     
  else if (dir == Direction::LEFT) 
    {
    if ((pacmanb->getX()-2) > 0) 
      {
      map_block = static_cast<MapBlock>(_MAP[(pacmanb->getY()-2)/5][((pacmanb->getX()-2)/5)-1]);
      }
    } 
    
  else if (dir == Direction::UP) 
    {
    if ((pacmanb->getY()-2) > 0) 
      {
      map_block = static_cast<MapBlock>(_MAP[((pacmanb->getY()-2)/5)-1][((pacmanb->getX()-2)/5)]);
      }
    }

  return map_block;

}
//*************************************************************************
Clockface::MapBlock Clockface::nextBlockP(Direction dir) 
{

  Clockface::MapBlock map_block = Clockface::MapBlock::OUT_OF_MAP;

  if (dir == Direction::RIGHT) 
    {
    if (pacmanp->getX()+pacmanp->SPRITE_SIZE < MAP_MAX_POS) 
      {
      map_block = static_cast<MapBlock>(_MAP[(pacmanp->getY()-2)/5][((pacmanp->getX()-2)/5)+1]);
      }   
    } 
    
  else if (dir == Direction::DOWN) 
    {
    if (pacmanp->getY()+pacmanp->SPRITE_SIZE < MAP_MAX_POS) 
      {
      map_block = static_cast<MapBlock>(_MAP[((pacmanp->getY()-2)/5)+1][(pacmanp->getX()-2)/5]);
      }
    }
     
  else if (dir == Direction::LEFT) 
    {
    if ((pacmanp->getX()-2) > 0) 
      {
      map_block = static_cast<MapBlock>(_MAP[(pacmanp->getY()-2)/5][((pacmanp->getX()-2)/5)-1]);
      }
    } 
    
  else if (dir == Direction::UP) 
    {
    if ((pacmanp->getY()-2) > 0) 
      {
      map_block = static_cast<MapBlock>(_MAP[((pacmanp->getY()-2)/5)-1][((pacmanp->getX()-2)/5)]);
      }
    }

  return map_block;

}
//*************************************************************************
bool Clockface::compareTest(int nexBlock, const int* blocking_block) 
{
  for (int track = 1; track < blocking_block[0] + 1; track++) 
    {
    if (nexBlock == blocking_block[track])
      {
      return true;
      }
    }
  return false;
}
//*************************************************************************
// const int CHOMPER_MOVING_BLOCKS[5] = {3, MapBlock::EMPTY, MapBlock::FOOD, MapBlock::GATE, MapBlock::SUPER_FOOD};
bool Clockface::compareTestJoy(int nexBlock, const int* moving_block) 
{
  for (int track = 1; track < 7; track++) 
    {
    if (nexBlock == moving_block[track])
      {
      return true;
      }
    }
  return false;
}
//*************************************************************************
int Clockface::countBlocks(Clockface::MapBlock elem) 
{
int count = 0;

  for (int i = 0; i < MAP_SIZE; i++) 
    {
    for (int j = 0; j < MAP_SIZE; j++) 
      {
      if (_MAP[i][j] == elem)
         {
         count++;         
         }       
      }
    }
  // Increments gamepoints by 10 points after every FOOD is eaten
  if(lastcount != count)
    {
    gamePoints = gamePoints + 10;   
    }
  lastcount = count;
  return count;
}
//*************************************************************************
void Clockface::drawMap() 
{
  //*********** Clear Display**********************
  Locator::getDisplay()->fillRect(0, 0, 64, 64, 0x0000);

  uint16_t food_color = WHTCOLOR;
  uint16_t wall_color = DARKBLUE;
  uint16_t spcfood_color = SUPERFOODCOLOR;


ChomperEnable = 1;
PacmanOEnable = 1;
PacmanREnable = 1;
PacmanBEnable = 1;
PacmanPEnable = 1;

PacmanOJailedFlag = 0;
PacmanRJailedFlag = 0;
PacmanBJailedFlag = 0;
PacmanPJailedFlag = 0;
  
ChomperCollision = 0;
PacmanOCollision = 0;
PacmanRCollision = 0;
PacmanBCollision = 0;
PacmanPCollision = 0;

ChomperInvincFlag = 0;
PacmanOInvincFlag = 0;
PacmanRInvincFlag = 0;
PacmanBInvincFlag = 0;
PacmanPInvincFlag = 0;

ChomperMovingFlag = 1;
PacmanOMovingFlag = 1;
PacmanRMovingFlag = 1;
PacmanBMovingFlag = 1;
PacmanPMovingFlag = 1;

ChomperStoppedFlag = 0;
PacmanOStoppedFlag = 0;
PacmanRStoppedFlag = 0;
PacmanBStoppedFlag = 0;
PacmanPStoppedFlag = 0;

  Locator::getDisplay()->drawRect(0, 0, 64, 64, wall_color);
  Locator::getDisplay()->drawRect(1, 1, 62, 62, wall_color);
  
  //*************** Initialize Map and Characters ****************
  for (int i = 0; i < MAP_SIZE; i++) 
    {
    for (int j = 0; j < MAP_SIZE; j++) 
      {
      if (_MAP[j][i] == MapBlock::FOOD)      // FOOD = 1
        {
        //                     fillRect(     x,            y,     w, h,   color);          
        Locator::getDisplay()->fillRect((i * 5) + 4, (j * 5) + 4, 1, 1, food_color);  // Set Food Size
        }  
      else if (_MAP[j][i] == MapBlock::WALL) // WALL = 2
        {
        Locator::getDisplay()->fillRect((i * 5) + 2, (j * 5) + 2, 5, 5, wall_color);
        } 
      else if (_MAP[j][i] == MapBlock::CLOCK)  // CLOCK = 5 
        {
        Locator::getDisplay()->fillRect((i * 5) + 2, (j * 5) + 2, 5, 5, wall_color);
        } 
      else if (_MAP[j][i] == MapBlock::GATE)   // GATE = 3
        {
        Locator::getDisplay()->fillRect((i * 5) + 4, (j * 5) + 4, 1, 1, food_color);
        } 
      else if (_MAP[j][i] == MapBlock::SUPER_FOOD) // SUPER_FOOD = 4
        {
        Locator::getDisplay()->fillRect((i * 5) + 3, (j * 5) + 3, 3, 3, spcfood_color);
        } 
      else if (_MAP[j][i] == MapBlock::PACMAN)     // PACMAN = 7 
        {
        chomper = new Chomper((i * 5) + 2, (j * 5) + 2);  // the '2' starts all Characters 2 rows in and down
        }
      else if (_MAP[j][i] == MapBlock::GHOST)     // GHOST = 6 
        {
        pacmano = new PacmanO((i * 5) + 2, (j * 5) + 2);
        pacmanr = new PacmanR((i * 5) + 2, (j * 5) + 2);

        }
      else if (_MAP[j][i] == MapBlock::GHOST2)     // GHOST2 = 8 
        {
        pacmanb = new PacmanB((i * 5) + 2, (j * 5) + 2);
        pacmanp = new PacmanP((i * 5) + 2, (j * 5) + 2);                  
        }
      }// End for (int j = 0)
    }// End for (int i = 0)


 
}// End drawMap
//*************************************************************************
//*************************************************************************
