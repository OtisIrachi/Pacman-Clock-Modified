//***************************************************************************************************
//
// This routine defines the "PacmanB Shape
//
//***************************************************************************************************
#pragma once

#include <Arduino.h>
#include "Game.h"
#include "Locator.h"
#include "EventBus.h"

extern int PacmanBInvincFlag;
extern int PacmanBMovingFlag;
extern int PacmanBStoppedFlag;
extern int PacmanBJailedFlag;
extern int PacmanBState;


//***************************************************
const uint16_t _PACMCLRB_CONST [][25] PROGMEM = {
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
const uint16_t _PACMANB_CONST [][25] PROGMEM = {
      {
        // 'pacmanBlue1, 5x5px  Red
        BLKCOLOR, CYANCOLOR, CYANCOLOR, CYANCOLOR, BLKCOLOR, 
        CYANCOLOR, WHTCOLOR, CYANCOLOR, WHTCOLOR, CYANCOLOR, 
        CYANCOLOR, CYANCOLOR, CYANCOLOR, CYANCOLOR, CYANCOLOR,
        CYANCOLOR, CYANCOLOR, CYANCOLOR, CYANCOLOR, CYANCOLOR,
        CYANCOLOR, BLKCOLOR, CYANCOLOR, BLKCOLOR, CYANCOLOR
      }, 
      {
        // 'pacmanBlue2, 5x5px  Red
        BLKCOLOR, CYANCOLOR, CYANCOLOR, CYANCOLOR, BLKCOLOR, 
        CYANCOLOR, WHTCOLOR, CYANCOLOR, WHTCOLOR, CYANCOLOR, 
        CYANCOLOR, CYANCOLOR, CYANCOLOR, CYANCOLOR, CYANCOLOR,
        CYANCOLOR, CYANCOLOR, CYANCOLOR, CYANCOLOR, CYANCOLOR,
        BLKCOLOR, CYANCOLOR, BLKCOLOR, CYANCOLOR, BLKCOLOR
      }
    };
//***************************************************
class PacmanB: public Sprite, public EventTask {
  private:

    uint16_t _PACMCLRB [2][25] = {
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

    uint16_t _PACMANB [2][25] = {
{
        // 'pacmanb1, 5x5px
        BLKCOLOR, CYANCOLOR, CYANCOLOR, CYANCOLOR, BLKCOLOR, 
        CYANCOLOR, WHTCOLOR, CYANCOLOR, WHTCOLOR, CYANCOLOR, 
        CYANCOLOR, CYANCOLOR, CYANCOLOR, CYANCOLOR, CYANCOLOR,
        CYANCOLOR, CYANCOLOR, CYANCOLOR, CYANCOLOR, CYANCOLOR,
        CYANCOLOR, BLKCOLOR, CYANCOLOR, BLKCOLOR, CYANCOLOR
      }, 
      {
        // 'pacmanb2, 5x5px
        BLKCOLOR, CYANCOLOR, CYANCOLOR, CYANCOLOR, BLKCOLOR, 
        CYANCOLOR, WHTCOLOR, CYANCOLOR, WHTCOLOR, CYANCOLOR, 
        CYANCOLOR, CYANCOLOR, CYANCOLOR, CYANCOLOR, CYANCOLOR,
        CYANCOLOR, CYANCOLOR, CYANCOLOR, CYANCOLOR, CYANCOLOR,
        BLKCOLOR, CYANCOLOR, BLKCOLOR, CYANCOLOR, BLKCOLOR
      }
    };

    byte _iteration = 0;

    int _lastX;
    int _lastY;
    long current_color = CYANCOLOR;

    const unsigned short* _sprite;
    unsigned long invencibleTimeout = 0;
    bool _pacmanb_anim = true;
    
    void changePacmanBColor(uint16_t newcolor);
    void fadePacmanBColor(uint16_t newcolor);
    
  public:
    enum State {
      MOVING,
      STOPPED,
      TURNING,
      INVENCIBLE,
      JAILED
    };
    PacmanB(int x, int y);
    void init();
    void move(Direction dir);
    void turn(Direction dir);
    void setState(State state);
    int nextBlock();
    int getX();
    int getY();
    void update();
    void execute(EventType event, Sprite* caller);
    Direction _directionb = Direction::RIGHT;
    State _state = MOVING;
    const int SPRITE_SIZE = 5;
   
};
//***************************************************************************************************
