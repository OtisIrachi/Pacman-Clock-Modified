//***************************************************************************************************
//
// This routine defines the "PacmanP Shape
//
//***************************************************************************************************
#pragma once

#include <Arduino.h>
#include "Game.h"
#include "Locator.h"
#include "EventBus.h"

extern int PacmanPInvincFlag;
extern int PacmanPMovingFlag;
extern int PacmanPStoppedFlag;
extern int PacmanPJailedFlag;
extern int PacmanPState;

//***************************************************
const uint16_t _PACMCLRP_CONST [][25] PROGMEM = {
{
        // 'pacmano1, 5x5px
        BLKCOLOR, BLKCOLOR, BLKCOLOR, BLKCOLOR, BLKCOLOR, 
        BLKCOLOR, BLKCOLOR, BLKCOLOR, BLKCOLOR, BLKCOLOR, 
        BLKCOLOR, BLKCOLOR, BLKCOLOR, BLKCOLOR, BLKCOLOR, 
        BLKCOLOR, BLKCOLOR, BLKCOLOR, BLKCOLOR, BLKCOLOR, 
        BLKCOLOR, BLKCOLOR, BLKCOLOR, BLKCOLOR, BLKCOLOR, 
      }, 
      {
        // 'pacmano2, 5x5px
        BLKCOLOR, BLKCOLOR, BLKCOLOR, BLKCOLOR, BLKCOLOR, 
        BLKCOLOR, BLKCOLOR, BLKCOLOR, BLKCOLOR, BLKCOLOR, 
        BLKCOLOR, BLKCOLOR, BLKCOLOR, BLKCOLOR, BLKCOLOR, 
        BLKCOLOR, BLKCOLOR, BLKCOLOR, BLKCOLOR, BLKCOLOR, 
        BLKCOLOR, BLKCOLOR, BLKCOLOR, BLKCOLOR, BLKCOLOR, 
      }
    };

//***************************************************
const uint16_t _PACMANP_CONST [][25] PROGMEM = {
      {
        // 'pacmanRed1, 5x5px  Red
        BLKCOLOR, PINKCOLOR, PINKCOLOR, PINKCOLOR, BLKCOLOR, 
        PINKCOLOR, WHTCOLOR, PINKCOLOR, WHTCOLOR, PINKCOLOR, 
        PINKCOLOR, PINKCOLOR, PINKCOLOR, PINKCOLOR, PINKCOLOR,
        PINKCOLOR, PINKCOLOR, PINKCOLOR, PINKCOLOR, PINKCOLOR,
        PINKCOLOR, BLKCOLOR, PINKCOLOR, BLKCOLOR, PINKCOLOR
      }, 
      {
        // 'pacmanRed2, 5x5px  Red
        BLKCOLOR, PINKCOLOR, PINKCOLOR, PINKCOLOR, BLKCOLOR, 
        PINKCOLOR, WHTCOLOR, PINKCOLOR, WHTCOLOR, PINKCOLOR, 
        PINKCOLOR, PINKCOLOR, PINKCOLOR, PINKCOLOR, PINKCOLOR,
        PINKCOLOR, PINKCOLOR, PINKCOLOR, PINKCOLOR, PINKCOLOR,
        BLKCOLOR, PINKCOLOR, BLKCOLOR, PINKCOLOR, BLKCOLOR
      }
    };
//***************************************************
class PacmanP: public Sprite, public EventTask {
  private:

    uint16_t _PACMCLRP [2][25] = {
{
        // 'pacmano1, 5x5px
        BLKCOLOR, BLKCOLOR, BLKCOLOR, BLKCOLOR, BLKCOLOR, 
        BLKCOLOR, BLKCOLOR, BLKCOLOR, BLKCOLOR, BLKCOLOR, 
        BLKCOLOR, BLKCOLOR, BLKCOLOR, BLKCOLOR, BLKCOLOR, 
        BLKCOLOR, BLKCOLOR, BLKCOLOR, BLKCOLOR, BLKCOLOR, 
        BLKCOLOR, BLKCOLOR, BLKCOLOR, BLKCOLOR, BLKCOLOR, 
      }, 
      {
        // 'pacmano2, 5x5px
        BLKCOLOR, BLKCOLOR, BLKCOLOR, BLKCOLOR, BLKCOLOR, 
        BLKCOLOR, BLKCOLOR, BLKCOLOR, BLKCOLOR, BLKCOLOR, 
        BLKCOLOR, BLKCOLOR, BLKCOLOR, BLKCOLOR, BLKCOLOR, 
        BLKCOLOR, BLKCOLOR, BLKCOLOR, BLKCOLOR, BLKCOLOR, 
        BLKCOLOR, BLKCOLOR, BLKCOLOR, BLKCOLOR, BLKCOLOR, 
      }
    };

    uint16_t _PACMANP [2][25] = {
{
        // 'pacman1, 5x5px
        BLKCOLOR, PINKCOLOR, PINKCOLOR, PINKCOLOR, BLKCOLOR, 
        PINKCOLOR, WHTCOLOR, PINKCOLOR, WHTCOLOR, PINKCOLOR, 
        PINKCOLOR, PINKCOLOR, PINKCOLOR, PINKCOLOR, PINKCOLOR,
        PINKCOLOR, PINKCOLOR, PINKCOLOR, PINKCOLOR, PINKCOLOR,
        PINKCOLOR, BLKCOLOR, PINKCOLOR, BLKCOLOR, PINKCOLOR
      }, 
      {
        // 'pacman2, 5x5px
        BLKCOLOR, PINKCOLOR, PINKCOLOR, PINKCOLOR, BLKCOLOR, 
        PINKCOLOR, WHTCOLOR, PINKCOLOR, WHTCOLOR, PINKCOLOR, 
        PINKCOLOR, PINKCOLOR, PINKCOLOR, PINKCOLOR, PINKCOLOR,
        PINKCOLOR, PINKCOLOR, PINKCOLOR, PINKCOLOR, PINKCOLOR,
        BLKCOLOR, PINKCOLOR, BLKCOLOR, PINKCOLOR, BLKCOLOR
      }
    };

    byte _iteration = 0;

    int _lastX;
    int _lastY;
    long current_color = PINKCOLOR;

    const unsigned short* _sprite;
    unsigned long invencibleTimeout = 0;
    

    bool _pacmanp_anim = true;

    void changePacmanPColor(uint16_t newcolor);
    void fadePacmanPColor(uint16_t newcolor);
   
  public:
    enum State {
      MOVING,
      STOPPED,
      TURNING,
      INVENCIBLE,
      JAILED
    };
    PacmanP(int x, int y);
    void init();
    void move(Direction dir);
    void turn(Direction dir);
    void setState(State state);
    int nextBlock();
    int getX();
    int getY();
    void update() ;
    void execute(EventType event, Sprite* caller);
    Direction _directionp = Direction::RIGHT;
    State _state = MOVING;
    const int SPRITE_SIZE = 5;
    
};
//***************************************************************************************************
