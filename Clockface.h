#pragma once

#include <Arduino.h>
#include "hour_font.h"
#include <Adafruit_GFX.h>
#include "Tile.h"
#include "Locator.h"
#include "Game.h"
#include "Object.h"
#include "IClockface.h"

class Clockface: public IClockface {
  private:
    const int MAP_SIZE = 12;
    Adafruit_GFX* _display;
    CWDateTime* _dateTime;
    //const char* _weekDayWords = "SUN\MON\TUE\WED\THR\FRI\SAT\0";
    const char* _weekDayWords = "Sun\Mon\Tue\Wed\Thr\Fri\Sat\0";
    const char* _monthWords = "JAN\0FEB\0MAR\0APR\0MAY\0JUN\0JUL\0AUG\0SEP\0OCT\0NOV\0DEC\0";
    char weekDayTemp[4]= "\0";
    char monthTemp[4]= "\0";

    enum MapBlock {
      EMPTY = 0,
      FOOD = 1,
      WALL = 2,
      GATE = 3,
      SUPER_FOOD = 4,
      CLOCK = 5,
      GHOST = 6,
      PACMAN = 7,
      GHOST2 = 8,
      OUT_OF_MAP = 99
    };
    
    // '7' is Starting point for Chomper, '6' is starting point for Pacmen
    const byte _MAP_CONST[12][12] = {
      {4,1,1,1,1,1,7,1,1,1,1,4},
      {1,2,2,1,2,2,2,2,1,2,2,1},
      {1,1,1,1,1,2,2,1,1,1,1,1},
      {2,1,5,5,5,5,5,5,5,5,1,2},
      {2,1,5,5,5,5,5,5,5,5,1,2},
      {1,1,5,5,5,5,5,5,5,5,1,1},
      {1,1,5,5,5,5,5,5,5,5,1,1},
      {2,1,5,5,5,5,5,5,5,5,1,2},
      {2,1,5,5,5,5,5,5,5,5,1,2},
      {1,1,6,1,1,2,2,1,1,8,1,1},
      {1,2,2,1,2,2,2,2,1,2,2,1},
      {4,1,1,1,1,1,1,1,1,1,1,4}
    };
    // '7' is Starting point for Chomper, '6' is starting point for Pacmen
    byte _MAP[12][12] = {
      {4,1,1,1,1,1,7,1,1,1,1,4},
      {1,2,2,1,2,2,2,2,1,2,2,1},
      {1,1,1,1,1,2,2,1,1,1,1,1},
      {2,1,5,5,5,5,5,5,5,5,1,2},
      {2,1,5,5,5,5,5,5,5,5,1,2},
      {1,1,5,5,5,5,5,5,5,5,1,1},
      {1,1,5,5,5,5,5,5,5,5,1,1},
      {2,1,5,5,5,5,5,5,5,5,1,2},
      {2,1,5,5,5,5,5,5,5,5,1,2},
      {1,1,6,1,1,2,2,1,1,8,1,1},
      {1,2,2,1,2,2,2,2,1,2,2,1},
      {4,1,1,1,1,1,1,1,1,1,1,4}
    };

    const byte MAP_BORDER_SIZE = 2;
    const byte MAP_MIN_POS = 0 + MAP_BORDER_SIZE;
    const byte MAP_MAX_POS = 64 - MAP_BORDER_SIZE;

    // first elem is the size
    const int CHOMPER_MOVING_BLOCKS[7] = {3, MapBlock::EMPTY, MapBlock::FOOD, MapBlock::GATE, MapBlock::SUPER_FOOD, MapBlock::GHOST, MapBlock::GHOST2};
    const int CHOMPER_BLOCKING_BLOCKS[4] = {3, MapBlock::OUT_OF_MAP, MapBlock::WALL, MapBlock::CLOCK};
    const int PACMANO_MOVING_BLOCKS[4]   = {3, MapBlock::EMPTY, MapBlock::FOOD, MapBlock::GATE};
    const int PACMANO_BLOCKING_BLOCKS[4] = {3, MapBlock::OUT_OF_MAP, MapBlock::WALL, MapBlock::CLOCK};
    const int PACMANR_MOVING_BLOCKS[4]   = {3, MapBlock::EMPTY, MapBlock::FOOD, MapBlock::GATE};
    const int PACMANR_BLOCKING_BLOCKS[4] = {3, MapBlock::OUT_OF_MAP, MapBlock::WALL, MapBlock::CLOCK};
    const int PACMANB_MOVING_BLOCKS[4]   = {3, MapBlock::EMPTY, MapBlock::FOOD, MapBlock::GATE};
    const int PACMANB_BLOCKING_BLOCKS[4] = {3, MapBlock::OUT_OF_MAP, MapBlock::WALL, MapBlock::CLOCK};
    const int PACMANP_MOVING_BLOCKS[4]   = {3, MapBlock::EMPTY, MapBlock::FOOD, MapBlock::GATE};
    const int PACMANP_BLOCKING_BLOCKS[4] = {3, MapBlock::OUT_OF_MAP, MapBlock::WALL, MapBlock::CLOCK};
        
    void displayFood();
    void drawMap();
    Clockface::MapBlock nextBlockC(Direction dir);
    Clockface::MapBlock nextBlockC();
    Clockface::MapBlock nextBlockO(Direction dir);
    Clockface::MapBlock nextBlockO();
    Clockface::MapBlock nextBlockR(Direction dir);
    Clockface::MapBlock nextBlockR(); 
    Clockface::MapBlock nextBlockB(Direction dir);
    Clockface::MapBlock nextBlockB();
    Clockface::MapBlock nextBlockP(Direction dir);
    Clockface::MapBlock nextBlockP();
    void turnJoyStickC();                
    void turnRandomC();
    void turnRandomO();
    void turnRandomR();
    void turnRandomB(); 
    void turnRandomP(); 
    int countBlocks(Clockface::MapBlock elem);          
    bool compareTest(int nexBlock, const int* values);
    bool compareTestJoy(int nexBlock, const int* moving_block);
    void gameComp();
    void resetMap();
    void directionDecisionC(MapBlock nextBlk, bool moving_axis_x);
    void directionDecisionO(MapBlock nextBlk, bool moving_axis_x);
    void directionDecisionR(MapBlock nextBlk, bool moving_axis_x);
    void directionDecisionB(MapBlock nextBlk, bool moving_axis_x); 
    void directionDecisionP(MapBlock nextBlk, bool moving_axis_x);       
    void updateClock();
    void updateScore(); 
    void updateStart();
    const char* weekDayName(int weekday);
    const char* monthName(int month);
        
  public:
    Clockface(Adafruit_GFX* display);
    void setup(CWDateTime *dateTime);
    void update();
    
    
};
