//***************************************************************************************************
#include "pacmanB.h"
//
// This routine moves the "PacmanB" sprite around the screen
//
//***************************************************************************************************
PacmanB::PacmanB(int x, int y) 
{
  _x = x;
  _y = y;
}
//***************************************************************************************************
void PacmanB::turn(Direction dir) 
{
  memcpy( _PACMANB, _PACMANB_CONST, sizeof(_PACMANB) );
  changePacmanBColor(current_color);
  _directionb = dir;

}
//***************************************************************************************************
void PacmanB::move(Direction dir) 
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
void PacmanB::init() 
{
  Locator::getDisplay()->drawRGBBitmap(_x, _y, _PACMANB[int(_pacmanb_anim)], SPRITE_SIZE, SPRITE_SIZE);
}
//***************************************************************************************************
void PacmanB::setState(State state) 
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
void PacmanB::update() 
{ 
  //********************************************* 
  if (_state == MOVING || _state == INVENCIBLE)  
    {
    Locator::getDisplay()->fillRect(_x,_y, SPRITE_SIZE, SPRITE_SIZE, 0);
    this->move(_directionb);
    }

  if (_state == JAILED)  
    {
    Locator::getDisplay()->fillRect(39, 39, SPRITE_SIZE, SPRITE_SIZE, 0);
    }
    
   // ***** Animate Pacman *****
  if (_iteration % 3 == 0)    _pacmanb_anim = !_pacmanb_anim; 
  //********************************************* 
  if (_state == INVENCIBLE) 
    {   
     PacmanBState = _state;
     PacmanBMovingFlag = 0;       
     PacmanBStoppedFlag = 0;
     PacmanBInvincFlag = 1; 
     PacmanBJailedFlag = 0;     
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
      current_color = CYANCOLOR; 
      }
    changePacmanBColor(current_color);
    Locator::getDisplay()->drawRGBBitmap(_x, _y, _PACMANB[int(_pacmanb_anim)], SPRITE_SIZE, SPRITE_SIZE);
    }
    
  //*********************************************   
  if(_state == STOPPED) 
     {
     _state = STOPPED;
     PacmanBState = _state;
     PacmanBMovingFlag = 0;       
     PacmanBStoppedFlag = 1;
     PacmanBInvincFlag = 0;
     PacmanBJailedFlag = 0; 
     } 

  // *****Draw Pacman in Jail*****
  if(_state == JAILED)    
     {       
     _state = JAILED; 
     PacmanBState = _state;
     PacmanBMovingFlag = 0;
     PacmanBInvincFlag = 0;
     PacmanBStoppedFlag = 0; 
     PacmanBJailedFlag = 1;  
     current_color = CYANCOLOR;
     changePacmanBColor(current_color); 
     Locator::getDisplay()->drawRGBBitmap(39, 39, _PACMANB[int(_pacmanb_anim)], SPRITE_SIZE, SPRITE_SIZE);
     }
     
  //*********************************************        
  if(_state == MOVING)    
     {
     _state = MOVING;
     PacmanBState = _state;
     PacmanBMovingFlag = 1;       
     PacmanBStoppedFlag = 0;
     PacmanBInvincFlag = 0;
     PacmanBJailedFlag = 0;         
     current_color = CYANCOLOR; 
     changePacmanBColor(current_color);
     Locator::getDisplay()->drawRGBBitmap(_x, _y, _PACMANB[int(_pacmanb_anim)], SPRITE_SIZE, SPRITE_SIZE);
     }
  //********************************************* 
  _iteration++;
  
}
//***************************************************************************************************
void PacmanB::execute(EventType event, Sprite* caller) 
{
  if (event == EventType::COLLISION) 
    {
    _directionb = DOWN;
    }
}
//***************************************************************************************************
void PacmanB::changePacmanBColor(uint16_t newcolor) 
{
  for (int i = 0; i < SPRITE_SIZE * SPRITE_SIZE; i++) 
    {
    if ((_PACMANB[0][i] != 0x0000) && (_PACMANB[0][i] != 0xFFFE))
      {
      _PACMANB[0][i] = newcolor;   
      }     
    if ((_PACMANB[1][i] != 0x0000) && (_PACMANB[1][i] != 0xFFFE))
      {
      _PACMANB[1][i] = newcolor;  
      }     
    }

}
//***************************************************************************************************
void PacmanB::fadePacmanBColor(uint16_t newcolor) 
{
  for (int i = 0; i < SPRITE_SIZE * SPRITE_SIZE; i++) 
    {
    if ((_PACMANB[0][i] == SCAREDBLUE) || (_PACMANB[0][i] == WHTCOLOR))
      {
      _PACMANB[0][i] = newcolor; 
            
      }  
        
    if ((_PACMANB[1][i] == SCAREDBLUE) || (_PACMANB[1][i] == WHTCOLOR))
      {
      _PACMANB[1][i] = newcolor;  
     
      }     
    }
    
}
//***************************************************************************************************
int PacmanB::getX() 
{
  return this->_x;
}
//***************************************************************************************************
int PacmanB::getY() 
{
  return this->_y;
}
//***************************************************************************************************
