//***************************************************************************************************
#include "pacmanR.h"
//
// This routine moves the "PacmanR" sprite around the screen
//
//***************************************************************************************************
PacmanR::PacmanR(int x, int y) 
{
  _x = x;
  _y = y;
}
//***************************************************************************************************
void PacmanR::turn(Direction dir) 
{
  memcpy( _PACMANR, _PACMANR_CONST, sizeof(_PACMANR) );
  changePacmanRColor(current_color);
  _directionr = dir;
}
//***************************************************************************************************
void PacmanR::move(Direction dir) 
{
 
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
}
//***************************************************************************************************
void PacmanR::init() 
{
  Locator::getDisplay()->drawRGBBitmap(_x, _y, _PACMANR[int(_pacmanr_anim)], SPRITE_SIZE, SPRITE_SIZE);
}
//***************************************************************************************************
void PacmanR::setState(State state) 
{
    
  if (state == INVENCIBLE) 
    {
    invencibleTimeout = millis();
    randomSeed(millis());
    _state = INVENCIBLE;
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
void PacmanR::update() 
{ 
  
  if (_state == MOVING || _state == INVENCIBLE)  
    {
    Locator::getDisplay()->fillRect(_x,_y, SPRITE_SIZE, SPRITE_SIZE, 0);
    this->move(_directionr);
    }

  if (_state == JAILED)  
    {
    Locator::getDisplay()->fillRect(20, 39, SPRITE_SIZE, SPRITE_SIZE, 0);
    }
    
  if (_iteration % 3 == 0)
    _pacmanr_anim = !_pacmanr_anim; 
    
  if (_state == INVENCIBLE) 
    {  
     PacmanRState = _state;
     PacmanRMovingFlag = 0;       
     PacmanRStoppedFlag = 0;
     PacmanRInvincFlag = 1; 
     PacmanRJailedFlag = 0;
    if (_iteration % 2 == 0) 
      {
      current_color = SCAREDBLUE;
      } 
    else 
      {
      current_color = SCAREDBLUE;
      }   
    if ((millis() - invencibleTimeout) >= 7000) 
      {
      _state = MOVING;
      current_color = REDCOLOR; 
      }
    // As long as Pacman is Scared it runs this !!!
    changePacmanRColor(current_color);
    Locator::getDisplay()->drawRGBBitmap(_x, _y, _PACMANR[int(_pacmanr_anim)], SPRITE_SIZE, SPRITE_SIZE);   
    }// End IF _state INVENCIBLE
    
  if(_state == STOPPED) 
     {
     _state = STOPPED; 
     PacmanRState = _state;
     PacmanRMovingFlag = 0;       
     PacmanRStoppedFlag = 1;
     PacmanRInvincFlag = 0;
     PacmanRJailedFlag = 0;  
     } 

  // *****Draw Pacman in Jail*****
  if(_state == JAILED)    
     {       
     _state = JAILED; 
     PacmanRState = _state;
     PacmanRMovingFlag = 0;
     PacmanRInvincFlag = 0;
     PacmanRStoppedFlag = 0; 
     PacmanRJailedFlag = 1;  
     current_color = REDCOLOR;
     changePacmanRColor(current_color); 
     Locator::getDisplay()->drawRGBBitmap(20, 39, _PACMANR[int(_pacmanr_anim)], SPRITE_SIZE, SPRITE_SIZE);
     }
         
  if(_state == MOVING)    //**********PacmanO is NORMAL***********
     {
     _state = MOVING;
     PacmanRState = _state;
     PacmanRMovingFlag = 1;       
     PacmanRStoppedFlag = 0;
     PacmanRInvincFlag = 0; 
     PacmanRJailedFlag = 0;      
     current_color = REDCOLOR; 
     changePacmanRColor(current_color); 
     Locator::getDisplay()->drawRGBBitmap(_x, _y, _PACMANR[int(_pacmanr_anim)], SPRITE_SIZE, SPRITE_SIZE);
     }

  _iteration++;
  
}
//***************************************************************************************************
void PacmanR::execute(EventType event, Sprite* caller) 
{
  if (event == EventType::COLLISION) 
    {
    _directionr = DOWN;
    }
}
//***************************************************************************************************
void PacmanR::changePacmanRColor(uint16_t newcolor) 
{
  for (int i = 0; i < SPRITE_SIZE * SPRITE_SIZE; i++) 
    {
    if ((_PACMANR[0][i] != 0x0000) && (_PACMANR[0][i] != 0xFFFE))
      {
      _PACMANR[0][i] = newcolor;   
      }      
    if ((_PACMANR[1][i] != 0x0000) && (_PACMANR[1][i] != 0xFFFE))
      {
      _PACMANR[1][i] = newcolor;  
      }     
    }

}
//***************************************************************************************************
void PacmanR::fadePacmanRColor(uint16_t newcolor) 
{
  for (int i = 0; i < SPRITE_SIZE * SPRITE_SIZE; i++) 
    {
    if ((_PACMANR[0][i] == SCAREDBLUE) || (_PACMANR[0][i] == WHTCOLOR))
      {
      _PACMANR[0][i] = newcolor; 
            
      }  
        
    if ((_PACMANR[1][i] == SCAREDBLUE) || (_PACMANR[1][i] == WHTCOLOR))
      {
      _PACMANR[1][i] = newcolor;  
     
      }     
    }

}
//***************************************************************************************************
int PacmanR::getX() 
{
  return this->_x;
}
//***************************************************************************************************
int PacmanR::getY() 
{
  return this->_y;
}
//***************************************************************************************************
