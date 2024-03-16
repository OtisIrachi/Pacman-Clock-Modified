//*********************************************************************
// Game.h
//
//
//*********************************************************************
#ifndef Game_h
#define Game_h

#define PROGMEM

const int DISPLAY_WIDTH = 64;
const int DISPLAY_HEIGHT = 64;

#define BLKCOLOR        0x0000
#define WHTCOLOR        0xFFFE
#define YELCOLOR        0xFE40
#define REDCOLOR        0xF800           // was 0xE8E4
#define CYANCOLOR       0x05BD           // was 0x05BD
#define GREENCOLOR      0x07E0  
#define DARKBLUE        0x000A
#define SUPERFOODCOLOR  0xFD80
#define GHOSTBLUE       0x0011
#define PINKCOLOR       0xF2F5           // was 0xF175  was 0xA970   // was 0xFD1C
#define ORANGCOLOR      0xFD00
#define CLOCKCOLOR      0x8D80
#define DATECOLOR       0xAD55
#define SCAREDBLUE      0x0018
#define TURQCOLOR       0x03D0
#define DKMAGCOLOR      0x8010


enum Direction {
    RIGHT,
    LEFT,
    UP,
    DOWN,
    HALT
};

enum DirectionM {
    MOVE_N,
    MOVE_Y    
}; 

#endif
//**********************************************************************
