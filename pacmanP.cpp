//***************************************************************************************************
#include "pacmanP.h"
//
// This routine moves the "PacmanP" sprite around the screen
//
//***************************************************************************************************
PacmanP::PacmanP(int x, int y) 
{
  _x = x;
  _y = y;  
}
//***************************************************************************************************
void PacmanP::turn(Direction dir) 
{
  memcpy( _PACMANP, _PACMANP_CONST, sizeof(_PACMANP) );
  changePacmanPColor(current_color);
  _directionp = dir;

}
//***************************************************************************************************
void PacmanP::move(Direction dir) 
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
void PacmanP::init() 
{
  Locator::getDisplay()->drawRGBBitmap(_x, _y, _PACMANP[int(_pacmanp_anim)], SPRITE_SIZE, SPRITE_SIZE);
  
}
//***************************************************************************************************
void PacmanP::setState(State state) 
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
void PacmanP::update() 
{ 
  
  if (_state == MOVING || _state == INVENCIBLE)  
    {
    Locator::getDisplay()->fillRect(_x,_y, SPRITE_SIZE, SPRITE_SIZE, 0);
    this->move(_directionp);
    }

  if (_state == JAILED)  
    {
    Locator::getDisplay()->fillRect(45, 39, SPRITE_SIZE, SPRITE_SIZE, 0);
    }

  if (_iteration % 3 == 0)
    _pacmanp_anim = !_pacmanp_anim; 

  if (_state == INVENCIBLE) 
     {    
     PacmanPState = _state;
     PacmanPMovingFlag = 0;       
     PacmanPStoppedFlag = 0;
     PacmanPInvincFlag = 1; 
     PacmanPJailedFlag = 0; 
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
       current_color = PINKCOLOR; 
       }
     // As long as Pacman is Scared it runs this !!!
     changePacmanPColor(current_color);
     Locator::getDisplay()->drawRGBBitmap(_x, _y, _PACMANP[int(_pacmanp_anim)], SPRITE_SIZE, SPRITE_SIZE);  
     } 
         
  if(_state == STOPPED) 
     {
     _state = STOPPED; 
     PacmanPState = _state;
     PacmanPMovingFlag = 0;       
     PacmanPStoppedFlag = 1;
     PacmanPInvincFlag = 0; 
     PacmanPJailedFlag = 0; 
     }

  // *****Draw Pacman in Jail*****
  if(_state == JAILED)    
     {       
     _state = JAILED; 
     PacmanPState = _state;
     PacmanPMovingFlag = 0;
     PacmanPInvincFlag = 0;
     PacmanPStoppedFlag = 0; 
     PacmanPJailedFlag = 1;  
     current_color = PINKCOLOR;
     changePacmanPColor(current_color); 
     Locator::getDisplay()->drawRGBBitmap(45, 39, _PACMANP[int(_pacmanp_anim)], SPRITE_SIZE, SPRITE_SIZE);
     }
          
  if(_state == MOVING)    //**********PacmanO is NORMAL***********
     {
     _state = MOVING;
     PacmanPState = _state;
     PacmanPMovingFlag = 1;       
     PacmanPStoppedFlag = 0;
     PacmanPInvincFlag = 0; 
     PacmanPJailedFlag = 0;     
     current_color = PINKCOLOR; 
     changePacmanPColor(current_color); 
     Locator::getDisplay()->drawRGBBitmap(_x, _y, _PACMANP[int(_pacmanp_anim)], SPRITE_SIZE, SPRITE_SIZE);
     }
     
  _iteration++;
  
}
//***************************************************************************************************
void PacmanP::execute(EventType event, Sprite* caller) 
{
  if (event == EventType::COLLISION) 
    {
    _directionp = DOWN;
    }
    
}
//***************************************************************************************************
void PacmanP::changePacmanPColor(uint16_t newcolor) 
{
  for (int i = 0; i < SPRITE_SIZE * SPRITE_SIZE; i++) 
     {
     if ((_PACMANP[0][i] != 0x0000) && (_PACMANP[0][i] != 0xFFFE))
        {
        _PACMANP[0][i] = newcolor;   
        }     
     if ((_PACMANP[1][i] != 0x0000) && (_PACMANP[1][i] != 0xFFFE))
        {
        _PACMANP[1][i] = newcolor;  
        }     
     }

}
//***************************************************************************************************
void PacmanP::fadePacmanPColor(uint16_t newcolor) 
{
  for (int i = 0; i < SPRITE_SIZE * SPRITE_SIZE; i++) 
    {
    if ((_PACMANP[0][i] == SCAREDBLUE) || (_PACMANP[0][i] == WHTCOLOR))
      {
      _PACMANP[0][i] = newcolor; 
            
      }  
        
    if ((_PACMANP[1][i] == SCAREDBLUE) || (_PACMANP[1][i] == WHTCOLOR))
      {
      _PACMANP[1][i] = newcolor;  
     
      }     
    }

}
//***************************************************************************************************
int PacmanP::getX() 
{
  return this->_x;
}
//***************************************************************************************************
int PacmanP::getY() 
{
  return this->_y;
}
//***************************************************************************************************
