//***************************************************************************************************
//
// This routine defines the "Chomper" Shape
//
//***************************************************************************************************
#pragma once

#include <Arduino.h>
#include "Game.h"
#include "Locator.h"
#include "EventBus.h"

extern int ChomperMovingFlag;
extern int ChomperStoppedFlag;
extern int ChomperInvincFlag;
extern int chomperState;


//***************************************************
const uint16_t _CHOMPCLRO_CONST [][25] PROGMEM = {
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
const uint16_t _CHOMPER_CONST [][25] PROGMEM = {
      {
        // 'Chomper1, 5x5px  Yellow
        BLKCOLOR, YELCOLOR, YELCOLOR, YELCOLOR, BLKCOLOR, 
        YELCOLOR, YELCOLOR, YELCOLOR, YELCOLOR, YELCOLOR, 
        YELCOLOR, YELCOLOR, YELCOLOR, YELCOLOR, YELCOLOR, 
        YELCOLOR, YELCOLOR, YELCOLOR, YELCOLOR, YELCOLOR, 
        BLKCOLOR, YELCOLOR, YELCOLOR, YELCOLOR, BLKCOLOR
      }, 
      {
        // 'Chomper2, 5x5px  Yellow
        BLKCOLOR, YELCOLOR, YELCOLOR, YELCOLOR, YELCOLOR, 
        YELCOLOR, YELCOLOR, YELCOLOR, BLKCOLOR, BLKCOLOR, 
        YELCOLOR, YELCOLOR, BLKCOLOR, BLKCOLOR, BLKCOLOR, 
        YELCOLOR, YELCOLOR, YELCOLOR, BLKCOLOR, BLKCOLOR, 
        BLKCOLOR, YELCOLOR, YELCOLOR, YELCOLOR, YELCOLOR
      }
    };
//***************************************************
class Chomper: public Sprite, public EventTask {
  private:

    uint16_t _CHOMPCLRO [2][25] = {
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

    uint16_t _CHOMPER [2][25] = {
      {
        // 'Chomper1, 5x5px  Yellow
        BLKCOLOR, YELCOLOR, YELCOLOR, YELCOLOR, BLKCOLOR, 
        YELCOLOR, YELCOLOR, YELCOLOR, YELCOLOR, YELCOLOR, 
        YELCOLOR, YELCOLOR, YELCOLOR, YELCOLOR, YELCOLOR, 
        YELCOLOR, YELCOLOR, YELCOLOR, YELCOLOR, YELCOLOR, 
        BLKCOLOR, YELCOLOR, YELCOLOR, YELCOLOR, BLKCOLOR
      }, 
      {
        // 'Chomper2, 5x5px  Yellow
        BLKCOLOR, YELCOLOR, YELCOLOR, YELCOLOR, YELCOLOR, 
        YELCOLOR, YELCOLOR, YELCOLOR, BLKCOLOR, BLKCOLOR, 
        YELCOLOR, YELCOLOR, BLKCOLOR, BLKCOLOR, BLKCOLOR, 
        YELCOLOR, YELCOLOR, YELCOLOR, BLKCOLOR, BLKCOLOR, 
        BLKCOLOR, YELCOLOR, YELCOLOR, YELCOLOR, YELCOLOR
      }
    };

    byte _iteration = 0;

    int _lastX;
    int _lastY;
    long current_color = YELCOLOR;

    const unsigned short* _sprite;
    unsigned long invencibleTimeout = 0;
    
    bool _chomper_anim = true;

    void flip();
    void rotate();
    void changeChomperColor(uint16_t newcolor);
    void fadeChomperColor(uint16_t newcolor);
  
  public:
    enum State {
      MOVING,
      STOPPED,
      TURNING,
      INVENCIBLE,
      JAILED
    };
    Chomper(int x, int y);
    void init();
    void move(Direction dir, DirectionM go);
    void turn(Direction dir);
    void setState(State state);
    int nextBlock();
    int getX();
    int getY();
    void update(); 
    void execute(EventType event, Sprite* caller);
    Direction _directionc = Direction::RIGHT;      // This is the starting direction
    DirectionM _go = DirectionM::MOVE_N;
    State _state = MOVING;
    const int SPRITE_SIZE = 5;

    
};
//***************************************************************************************************
