//***************************************************************************************************
//
// This routine defines the "PacmanO Shape
//
//***************************************************************************************************
#pragma once

#include <Arduino.h>
#include "Game.h"
#include "Locator.h"
#include "EventBus.h"

extern int PacmanOInvincFlag;   
extern int PacmanOMovingFlag;   
extern int PacmanOStoppedFlag;
extern int PacmanOJailedFlag;
extern int PacmanOState;
   
//***************************************************
const uint16_t _PACMCLRO_CONST [][25] PROGMEM = {
{
        // 'pacmano1, 5x5px
        BLKCOLOR, BLKCOLOR, BLKCOLOR, BLKCOLOR, BLKCOLOR, 
        BLKCOLOR, BLKCOLOR, BLKCOLOR, BLKCOLOR, BLKCOLOR, 
        BLKCOLOR, BLKCOLOR, BLKCOLOR, BLKCOLOR, BLKCOLOR, 
        BLKCOLOR, BLKCOLOR, BLKCOLOR, BLKCOLOR, BLKCOLOR, 
        BLKCOLOR, BLKCOLOR, BLKCOLOR, BLKCOLOR, BLKCOLOR 
      }, 
      {
        // 'pacmano2, 5x5px
        BLKCOLOR, BLKCOLOR, BLKCOLOR, BLKCOLOR, BLKCOLOR, 
        BLKCOLOR, BLKCOLOR, BLKCOLOR, BLKCOLOR, BLKCOLOR, 
        BLKCOLOR, BLKCOLOR, BLKCOLOR, BLKCOLOR, BLKCOLOR, 
        BLKCOLOR, BLKCOLOR, BLKCOLOR, BLKCOLOR, BLKCOLOR, 
        BLKCOLOR, BLKCOLOR, BLKCOLOR, BLKCOLOR, BLKCOLOR 
      }
    };

//***************************************************
const uint16_t _PACMANO_CONST [][25] PROGMEM = {
      {
        // 'pacmanBlue1, 5x5px  Red
        BLKCOLOR, ORANGCOLOR, ORANGCOLOR, ORANGCOLOR, BLKCOLOR, 
        ORANGCOLOR, WHTCOLOR, ORANGCOLOR, WHTCOLOR, ORANGCOLOR, 
        ORANGCOLOR, ORANGCOLOR, ORANGCOLOR, ORANGCOLOR, ORANGCOLOR,
        ORANGCOLOR, ORANGCOLOR, ORANGCOLOR, ORANGCOLOR, ORANGCOLOR,
        ORANGCOLOR, BLKCOLOR, ORANGCOLOR, BLKCOLOR, ORANGCOLOR
      }, 
      {
        // 'pacmanBlue2, 5x5px  Red
        BLKCOLOR, ORANGCOLOR, ORANGCOLOR, ORANGCOLOR, BLKCOLOR, 
        ORANGCOLOR, WHTCOLOR, ORANGCOLOR, WHTCOLOR, ORANGCOLOR, 
        ORANGCOLOR, ORANGCOLOR, ORANGCOLOR, ORANGCOLOR, ORANGCOLOR,
        ORANGCOLOR, ORANGCOLOR, ORANGCOLOR, ORANGCOLOR, ORANGCOLOR,
        BLKCOLOR, ORANGCOLOR, BLKCOLOR, ORANGCOLOR, BLKCOLOR
      }
    };
//***************************************************
class PacmanO: public Sprite, public EventTask {
  private:

    uint16_t _PACMCLRO [2][25] = {
{
        // 'pacmano1, 5x5px
        BLKCOLOR, BLKCOLOR, BLKCOLOR, BLKCOLOR, BLKCOLOR, 
        BLKCOLOR, BLKCOLOR, BLKCOLOR, BLKCOLOR, BLKCOLOR, 
        BLKCOLOR, BLKCOLOR, BLKCOLOR, BLKCOLOR, BLKCOLOR, 
        BLKCOLOR, BLKCOLOR, BLKCOLOR, BLKCOLOR, BLKCOLOR, 
        BLKCOLOR, BLKCOLOR, BLKCOLOR, BLKCOLOR, BLKCOLOR 
      }, 
      {
        // 'pacmano2, 5x5px
        BLKCOLOR, BLKCOLOR, BLKCOLOR, BLKCOLOR, BLKCOLOR, 
        BLKCOLOR, BLKCOLOR, BLKCOLOR, BLKCOLOR, BLKCOLOR, 
        BLKCOLOR, BLKCOLOR, BLKCOLOR, BLKCOLOR, BLKCOLOR, 
        BLKCOLOR, BLKCOLOR, BLKCOLOR, BLKCOLOR, BLKCOLOR, 
        BLKCOLOR, BLKCOLOR, BLKCOLOR, BLKCOLOR, BLKCOLOR 
      }
    };

    uint16_t _PACMANO [2][25] = {
{
        // 'pacmano1, 5x5px
        BLKCOLOR, ORANGCOLOR, ORANGCOLOR, ORANGCOLOR, BLKCOLOR, 
        ORANGCOLOR, WHTCOLOR, ORANGCOLOR, WHTCOLOR, ORANGCOLOR, 
        ORANGCOLOR, ORANGCOLOR, ORANGCOLOR, ORANGCOLOR, ORANGCOLOR,
        ORANGCOLOR, ORANGCOLOR, ORANGCOLOR, ORANGCOLOR, ORANGCOLOR,
        ORANGCOLOR, BLKCOLOR, ORANGCOLOR, BLKCOLOR, ORANGCOLOR
      }, 
      {
        // 'pacmano2, 5x5px
        BLKCOLOR, ORANGCOLOR, ORANGCOLOR, ORANGCOLOR, BLKCOLOR, 
        ORANGCOLOR, WHTCOLOR, ORANGCOLOR, WHTCOLOR, ORANGCOLOR, 
        ORANGCOLOR, ORANGCOLOR, ORANGCOLOR, ORANGCOLOR, ORANGCOLOR,
        ORANGCOLOR, ORANGCOLOR, ORANGCOLOR, ORANGCOLOR, ORANGCOLOR,
        BLKCOLOR, ORANGCOLOR, BLKCOLOR, ORANGCOLOR, BLKCOLOR
      }
    };

    byte _iteration = 0;

    int _lastX;
    int _lastY;
    long current_color = ORANGCOLOR;   

    const unsigned short* _sprite;
    unsigned long invencibleTimeout = 0;
    
    bool _pacmano_anim = true;

    void changePacmanOColor(uint16_t newcolor);
    void fadePacmanOColor(uint16_t newcolor);
    
  public:
    enum State {
      MOVING,
      STOPPED,
      TURNING,
      INVENCIBLE,
      JAILED
    };
    PacmanO(int x, int y);
    void init();
    void move(Direction dir);
    void turn(Direction dir);
    void setState(State state);
    int nextBlock();
    int getX();
    int getY();
    void update() ;
    void execute(EventType event, Sprite* caller);
    Direction _directiono = Direction::RIGHT;
    State _state = MOVING;
    const int SPRITE_SIZE = 5;
  
};
//***************************************************************************************************
