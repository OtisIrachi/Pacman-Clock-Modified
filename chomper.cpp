//***************************************************************************************************
#include "chomper.h"
//
// This routine moves the "Chomper" sprite around the screen
//
// Added drawRGBBitmapDy and drawRGBBitmapDx routines below to fade Chomper upon collision
//**************************************************************************
void drawRGBBitmapDy(int dly, int16_t x, int16_t y, const uint16_t bitmap[],
                                 int16_t w, int16_t h) 
{
  Locator::getDisplay()->startWrite();
  for (int16_t j = 0; j < h; j++, y++) 
    {
    for (int16_t i = 0; i < w; i++) 
      {
      Locator::getDisplay()->writePixel(x + i, y, pgm_read_word(&bitmap[j * w + i]));
      }
    delay(dly);
    }
  Locator::getDisplay()->endWrite();
}
//**************************************************************************
void drawRGBBitmapDx(int dly, int16_t x, int16_t y, const uint16_t bitmap[],
                                 int16_t w, int16_t h) 
{
  Locator::getDisplay()->startWrite();

    for (int16_t i = 0; i < w; i++, x++) 
      {
      for (int16_t j = 0; j < h; j++) 
      {
      Locator::getDisplay()->writePixel(x, y + j, pgm_read_word(&bitmap[j * w + i]));      
      } 
    delay(dly);
    }
  Locator::getDisplay()->endWrite();
}                            
//***************************************************************************************************
Chomper::Chomper(int x, int y) 
{
  _x = x;
  _y = y;
 
}
//***************************************************************************************************
void Chomper::turn(Direction dir) 
{
  memcpy( _CHOMPER, _CHOMPER_CONST, sizeof(_CHOMPER) );
  
  if (dir == Direction::LEFT) 
    {
    flip();
    } 
  else if (dir == Direction::DOWN) 
    {
    flip();
    rotate();    
    flip();
    } 
  else if (dir == Direction::UP) 
    {
    rotate();
    }

  else if (dir == Direction::HALT) 
    {
    
    }

  changeChomperColor(current_color);
  _directionc = dir;

}
//***************************************************************************************************
void Chomper::move(Direction dir, DirectionM go) 
{
  
  _go = go;
  
  if(go == 1)
  { 
  Locator::getDisplay()->drawRGBBitmap(_x, _y, _CHOMPCLRO[int(_chomper_anim)], SPRITE_SIZE, SPRITE_SIZE);
  if (dir == Direction::RIGHT) 
    {
    _x += 1;
    } 
  else if (dir == Direction::LEFT) 
    {
    _x -= 1;
    } 
  else if (dir == Direction::DOWN) 
    {
    _y += 1;
    } 
  else if (dir == Direction::UP) 
    {
    _y -= 1;
    }
  else if (dir == Direction::HALT) 
    {
    _x += 0;
    _y += 0;
    }    
  }// End if go 
}
//***************************************************************************************************
void Chomper::init() 
{
  Locator::getDisplay()->drawRGBBitmap(_x, _y, _CHOMPER[int(_chomper_anim)], SPRITE_SIZE, SPRITE_SIZE);
}
//***************************************************************************************************
void Chomper::setState(State state) 
{

  if (state == INVENCIBLE) 
    {
    invencibleTimeout = millis();
    randomSeed(millis());
    _state = INVENCIBLE;
    this->update();
    }

  if (state == STOPPED) 
    {
    _state = STOPPED;
    this->update();
    }

  if (state == JAILED) 
    {
    _state = JAILED;
    this->update();
    }  

  if (state == MOVING) 
    {
    _state = MOVING;
    this->update();
    }
      
}
//***************************************************************************************************
void Chomper::update() 
{ 
  // ***** Move Chomper *****
  if (_state == MOVING || _state == INVENCIBLE)  
     {
     // Clears Chomper Color to BLACK
     Locator::getDisplay()->fillRect(_x,_y, SPRITE_SIZE, SPRITE_SIZE, 0);
     this->move(_directionc, _go); 
     }
  //****************************
    
  // ***** Animate Chomper *****
  if (_iteration % 3 == 0)   _chomper_anim = !_chomper_anim; 

  // ***** If Chomper is Invincible *****
  if (_state == INVENCIBLE) 
     {
     chomperState = _state;
     ChomperMovingFlag = 0; 
     ChomperInvincFlag = 1; 
     ChomperStoppedFlag = 0;      
     if (_iteration % 2 == 0) // if superfood timer is still running
        {
        current_color = random(LONG_MAX);
        } 
     else 
        {
        current_color = YELCOLOR;
        }   
     if ((millis() - invencibleTimeout) >= 7000) 
        {
        _state = MOVING;
        chomperState = _state;
        current_color = YELCOLOR;
        }

     changeChomperColor(current_color);
     Locator::getDisplay()->drawRGBBitmap(_x, _y, _CHOMPER[int(_chomper_anim)], SPRITE_SIZE, SPRITE_SIZE);
     }// End If Invincible
  //**************************************
  
  if(_state == STOPPED) 
     {
     chomperState = _state;
     ChomperMovingFlag = 0;       
     ChomperStoppedFlag = 1;
     ChomperInvincFlag = 0;       
     memcpy( _CHOMPCLRO, _CHOMPCLRO_CONST, sizeof(_CHOMPCLRO) ); 
     fadeChomperColor(BLKCOLOR);
     // "deelay" adds a delay to both "x" and "y" subroutines to give a fade away to BLACK when Chomper collides with a Ghost
     drawRGBBitmapDy(500, _x, _y, _CHOMPCLRO[int(_chomper_anim)], SPRITE_SIZE, SPRITE_SIZE); 
     } 
         
  if(_state == MOVING) 
     {
     chomperState = _state;
     ChomperMovingFlag = 1;       
     ChomperStoppedFlag = 0;
     ChomperInvincFlag = 0;     
     current_color = YELCOLOR; 
     changeChomperColor(current_color);
     Locator::getDisplay()->drawRGBBitmap(_x, _y, _CHOMPER[int(_chomper_anim)], SPRITE_SIZE, SPRITE_SIZE);
     }

  _iteration++;
  
}

//***************************************************************************************************
//TODO move to the gfx-engine lib
void Chomper::rotate() 
{
  int n = SPRITE_SIZE;

  uint16_t temp0[2][25] = {};  
  memcpy( temp0, _CHOMPER, sizeof(temp0) );
 
  for(int i = 0; i < n; i++) 
    {
    for(int j = 0; j < n; j++) 
      {
      _CHOMPER[0][(i*n)+j] = temp0[0][(n-1-i)+(j*n)];
      _CHOMPER[1][(i*n)+j] = temp0[1][(n-1-i)+(j*n)];
      }
    }
    
}
//***************************************************************************************************
//TODO move to the gfx-engine lib
void Chomper::flip() 
{
  int n = SPRITE_SIZE;

  for(int i = 0; i < n; i++) 
    {
    for(int j = 0; j < floor(n/2)+1; j++) 
      {
      std::swap(_CHOMPER[0][j + (i*n)], _CHOMPER[0][(i*n)+n-j-1]);
      std::swap(_CHOMPER[1][j + (i*n)], _CHOMPER[1][(i*n)+n-j-1]);
      }
    }

}
//***************************************************************************************************
void Chomper::execute(EventType event, Sprite* caller) 
{
  Serial.println("execute");
  if (event == EventType::COLLISION) 
    {
    _directionc = DOWN;
    }
    
}
//***************************************************************************************************
void Chomper::changeChomperColor(uint16_t newcolor) 
{
  for (int i = 0; i < SPRITE_SIZE * SPRITE_SIZE; i++) 
    {
    if ((_CHOMPER[0][i] != 0x0000) && (_CHOMPER[0][i] != 0xFFFE))
      {
      _CHOMPER[0][i] = newcolor;   
      }
     
    if ((_CHOMPER[1][i] != 0x0000) && (_CHOMPER[1][i] != 0xFFFE))
      {
      _CHOMPER[1][i] = newcolor;  
      }     
    }

}
//***************************************************************************************************
void Chomper::fadeChomperColor(uint16_t newcolor) 
{
  for (int i = 0; i < SPRITE_SIZE * SPRITE_SIZE; i++) 
    {
    if ((_CHOMPER[0][i] == YELCOLOR) || (_CHOMPER[0][i] == BLKCOLOR))
      {
      _CHOMPER[0][i] = newcolor; 
            
      }  
        
    if ((_CHOMPER[1][i] == YELCOLOR) || (_CHOMPER[0][i] == BLKCOLOR))
      {
      _CHOMPER[1][i] = newcolor;  
     
      }     
    }

}
//***************************************************************************************************
int Chomper::getX() 
{
  return this->_x;
}
//***************************************************************************************************
int Chomper::getY() 
{
  return this->_y;
}
//***************************************************************************************************
