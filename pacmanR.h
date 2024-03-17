//***************************************************************************************************
//
// This routine defines the "PacmanR Shape
//
//***************************************************************************************************
#pragma once

#include <Arduino.h>
#include "Game.h"
#include "Locator.h"
#include "EventBus.h"

extern int PacmanRInvincFlag;
extern int PacmanRMovingFlag;
extern int PacmanRStoppedFlag;
extern int PacmanRJailedFlag;
extern int PacmanRState;

//***************************************************
const uint16_t _PACMCLRR_CONST [][25] PROGMEM = {
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
const uint16_t _PACMANR_CONST [][25] PROGMEM = {
      {
        // 'pacmanRed1, 5x5px  Red
        BLKCOLOR, REDCOLOR, REDCOLOR, REDCOLOR, BLKCOLOR, 
        REDCOLOR, WHTCOLOR, REDCOLOR, WHTCOLOR, REDCOLOR, 
        REDCOLOR, REDCOLOR, REDCOLOR, REDCOLOR, REDCOLOR,
        REDCOLOR, REDCOLOR, REDCOLOR, REDCOLOR, REDCOLOR,
        REDCOLOR, BLKCOLOR, REDCOLOR, BLKCOLOR, REDCOLOR
      }, 
      {
        // 'pacmanRed2, 5x5px  Red
        BLKCOLOR, REDCOLOR, REDCOLOR, REDCOLOR, BLKCOLOR, 
        REDCOLOR, WHTCOLOR, REDCOLOR, WHTCOLOR, REDCOLOR, 
        REDCOLOR, REDCOLOR, REDCOLOR, REDCOLOR, REDCOLOR,
        REDCOLOR, REDCOLOR, REDCOLOR, REDCOLOR, REDCOLOR,
        BLKCOLOR, REDCOLOR, BLKCOLOR, REDCOLOR, BLKCOLOR
      }
    };
//***************************************************
class PacmanR: public Sprite, public EventTask {
  private:

    uint16_t _PACMCLRR [2][25] = {
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

    uint16_t _PACMANR [2][25] = {
{
        // 'pacman1, 5x5px
        BLKCOLOR, REDCOLOR, REDCOLOR, REDCOLOR, BLKCOLOR, 
        REDCOLOR, WHTCOLOR, REDCOLOR, WHTCOLOR, REDCOLOR, 
        REDCOLOR, REDCOLOR, REDCOLOR, REDCOLOR, REDCOLOR,
        REDCOLOR, REDCOLOR, REDCOLOR, REDCOLOR, REDCOLOR,
        REDCOLOR, BLKCOLOR, REDCOLOR, BLKCOLOR, REDCOLOR
      }, 
      {
        // 'pacman2, 5x5px
        BLKCOLOR, REDCOLOR, REDCOLOR, REDCOLOR, BLKCOLOR, 
        REDCOLOR, WHTCOLOR, REDCOLOR, WHTCOLOR, REDCOLOR, 
        REDCOLOR, REDCOLOR, REDCOLOR, REDCOLOR, REDCOLOR,
        REDCOLOR, REDCOLOR, REDCOLOR, REDCOLOR, REDCOLOR,
        BLKCOLOR, REDCOLOR, BLKCOLOR, REDCOLOR, BLKCOLOR
      }
    };

    byte _iteration = 0;

    int _lastX;
    int _lastY;
    long current_color = REDCOLOR;

    const unsigned short* _sprite;
    unsigned long invencibleTimeout = 0;
    
    bool _pacmanr_anim = true;

    void changePacmanRColor(uint16_t newcolor);
    void fadePacmanRColor(uint16_t newcolor);
    
  public:
    enum State {
      MOVING,
      STOPPED,
      TURNING,
      INVENCIBLE,
      JAILED
    };
    PacmanR(int x, int y);
    void init();
    void move(Direction dir);
    void turn(Direction dir);
    void setState(State state);
    int nextBlock();
    int getX();
    int getY();
    void update() ;
    void execute(EventType event, Sprite* caller);
    Direction _directionr = Direction::RIGHT;
    State _state = MOVING;
    const int SPRITE_SIZE = 5;
    
};
//***************************************************************************************************
