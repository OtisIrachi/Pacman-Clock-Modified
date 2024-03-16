//***************************************************************************************************
#include "pacmanO.h"
//
// This routine moves the "PacmanO" sprite around the screen
//
//***************************************************************************************************
PacmanO::PacmanO(int x, int y) 
{
  _x = x;
  _y = y;
}
//***************************************************************************************************
void PacmanO::turn(Direction dir) 
{
  memcpy( _PACMANO, _PACMANO_CONST, sizeof(_PACMANO) );
  changePacmanOColor(current_color);
  _directiono = dir;

}
//***************************************************************************************************
void PacmanO::move(Direction dir) 
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
void PacmanO::init() 
{
  Locator::getDisplay()->drawRGBBitmap(_x, _y, _PACMANO[int(_pacmano_anim)], SPRITE_SIZE, SPRITE_SIZE);
}
//***************************************************************************************************
void PacmanO::setState(State state) 
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
void PacmanO::update() 
{ 
  
  if (_state == MOVING || _state == INVENCIBLE)  
    {
    Locator::getDisplay()->fillRect(_x, _y, SPRITE_SIZE, SPRITE_SIZE, 0);
    this->move(_directiono);
    }

  if (_state == JAILED)  
    {
    Locator::getDisplay()->fillRect(14, 39, SPRITE_SIZE, SPRITE_SIZE, 0);
    }
    
  // ***** Animate Pacman *****
  if (_iteration % 3 == 0)    _pacmano_anim = !_pacmano_anim; 

  // ***** If PacmanO is Scared *****
  if (_state == INVENCIBLE) 
     {     
     PacmanOState = _state;
     PacmanOMovingFlag = 0;
     PacmanOInvincFlag = 1; 
     PacmanOStoppedFlag = 0; 
     PacmanOJailedFlag = 0;   
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
        //current_color = SCAREDBLUE; 
        current_color = ORANGCOLOR;       
        }   
        
     // As long as Pacman is Scared ir runs this !!!
     changePacmanOColor(current_color);
     Locator::getDisplay()->drawRGBBitmap(_x, _y, _PACMANO[int(_pacmano_anim)], SPRITE_SIZE, SPRITE_SIZE);
     }

  // *****Stop Pacman, and draw Pacman Fade******
  if(_state == STOPPED) 
     {
     _state = STOPPED;       
     PacmanOState = _state;
     PacmanOMovingFlag = 0;       
     PacmanOStoppedFlag = 1;
     PacmanOInvincFlag = 0;
     PacmanOJailedFlag = 0; 
     } 

  // *****Draw Pacman in Jail*****
  if(_state == JAILED)    
     {       
     _state = JAILED; 
     PacmanOState = _state;
     PacmanOMovingFlag = 0;
     PacmanOInvincFlag = 0;
     PacmanOStoppedFlag = 0; 
     PacmanOJailedFlag = 1;  
     current_color = ORANGCOLOR;
     changePacmanOColor(current_color); 
     Locator::getDisplay()->drawRGBBitmap(14, 39, _PACMANO[int(_pacmano_anim)], SPRITE_SIZE, SPRITE_SIZE);
     }
         
   //**********PacmanO is NORMAL***********
  if(_state == MOVING)   
     {       
     _state = MOVING; 
     PacmanOState = _state;
     PacmanOMovingFlag = 1;
     PacmanOInvincFlag = 0;
     PacmanOStoppedFlag = 0;
     PacmanOJailedFlag = 0;         
     current_color = ORANGCOLOR; 
     changePacmanOColor(current_color);
     Locator::getDisplay()->drawRGBBitmap(_x, _y, _PACMANO[int(_pacmano_anim)], SPRITE_SIZE, SPRITE_SIZE);
     }
       
  _iteration++;
  
}
//***************************************************************************************************
void PacmanO::execute(EventType event, Sprite* caller) 
{
  if (event == EventType::COLLISION) 
    {
    _directiono = DOWN;
    }
}
//***************************************************************************************************
void PacmanO::changePacmanOColor(uint16_t newcolor) 
{
  for (int i = 0; i < SPRITE_SIZE * SPRITE_SIZE; i++) 
    {
    if ((_PACMANO[0][i] != 0x0000) && (_PACMANO[0][i] != 0xFFFE))
      {
      _PACMANO[0][i] = newcolor;   
      }    
    if ((_PACMANO[1][i] != 0x0000) && (_PACMANO[1][i] != 0xFFFE))
      {
      _PACMANO[1][i] = newcolor;  
      }     
    }

}
//***************************************************************************************************
void PacmanO::fadePacmanOColor(uint16_t newcolor) 
{
  for (int i = 0; i < SPRITE_SIZE * SPRITE_SIZE; i++) 
    {
    if ((_PACMANO[0][i] == SCAREDBLUE) || (_PACMANO[0][i] == WHTCOLOR))
      {
      _PACMANO[0][i] = newcolor; 
            
      }  
        
    if ((_PACMANO[1][i] == SCAREDBLUE) || (_PACMANO[1][i] == WHTCOLOR))
      {
      _PACMANO[1][i] = newcolor;  
     
      }     
    }

}
//***************************************************************************************************
int PacmanO::getX() 
{
  return this->_x;
}
//***************************************************************************************************
int PacmanO::getY() 
{
  return this->_y;
}
//***************************************************************************************************
