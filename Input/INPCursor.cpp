/**-------------------------------------------------------------------------------------------------------------------
*
* @file       INPCursor.cpp
*
* @class      INPCURSOR
* @brief      Input Cursor Class
* @ingroup    INPUT
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @copyright  Copyright(c) 2008 - 2016 GEN Group.
*
* @cond
* Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
* documentation files(the "Software"), to deal in the Software without restriction, including without limitation
* the rights to use, copy, modify, merge, publish, distribute, sublicense, and/ or sell copies of the Software,
* and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all copies or substantial portions of
* the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO
* THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
* @endcond
*
*---------------------------------------------------------------------------------------------------------------------*/

/*---- PRECOMPILATION CONTROL ----------------------------------------------------------------------------------------*/

#include "GEN_Defines.h"


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include <string.h>

#include "XFactory.h"
#include "XTimer.h"

#include "INPCursor.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         INPCURSOR::INPCURSOR()
* @brief      Constructor
* @ingroup    INPUT
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
INPCURSOR::INPCURSOR(): INPCURSORMOTIONPOINT()
{
  Clean();

  timer=GEN_XFACTORY.CreateTimer();
  
  XTIMER_MODULE(timer)
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         INPCURSOR::~INPCURSOR()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    INPUT
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
INPCURSOR::~INPCURSOR()
{
  if(timer)
    {
      GEN_XFACTORY.DeleteTimer(timer);
    }

  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         INPCURSOR_ID INPCURSOR::GetID()
* @brief      Get ID cursor
* @ingroup    INPUT
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     INPCURSOR_ID : cursor ID
*
*---------------------------------------------------------------------------------------------------------------------*/
INPCURSOR_ID INPCURSOR::GetID()
{
  return ID;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void INPCURSOR::SetID(INPCURSOR_ID ID)
* @brief      Set ID cursor
* @ingroup    INPUT
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  ID : new ID of cursor
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void INPCURSOR::SetID(INPCURSOR_ID ID)
{
  this->ID = ID;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XTIMER* INPCURSOR::GetTimer()
* @brief      Get Timer of cursor
* @ingroup    INPUT
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     XTIMER* : Timer of cursor
*
*---------------------------------------------------------------------------------------------------------------------*/
XTIMER* INPCURSOR::GetTimer()
{
  return timer;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool INPCURSOR::HavePreSelect()
* @brief      Have Pre-Select
* @ingroup    INPUT
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool INPCURSOR::HavePreSelect()
{
  return havepreselect;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool INPCURSOR::SetHavePreSelect(bool havepreselect)
* @brief      Set Have Pre-Select
* @ingroup    INPUT
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  havepreselect : true active have pre-select
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool INPCURSOR::SetHavePreSelect(bool havepreselect)
{
  this->havepreselect = havepreselect;

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool INPCURSOR::IsChanged()
* @brief      Is Changed cursor
* @ingroup    INPUT
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool INPCURSOR::IsChanged()
{
  return ischanged;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool INPCURSOR::SetIsChanged(bool ischanged)
* @brief      Set Is Changed cursor
* @ingroup    INPUT
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  ischanged : true is changed
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool INPCURSOR::SetIsChanged(bool ischanged)
{
  this->ischanged = ischanged;

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool INPCURSOR::IsPositionInRect(int x, int y, int width,int height)
* @brief      Is Position In Rect
* @ingroup    INPUT
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  x : x position of rect
* @param[in]  y : y position of rect
* @param[in]  width : width of rect
* @param[in]  height : height of rect
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool INPCURSOR::IsPositionInRect(int x, int y, int width,int height)
{
  if((GetX() >= x) && (GetX() <= (x+width)) &&
     (GetY() >= y) && (GetY() <= (y+height))) return true;

  return false;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         INPCURSORMOTION* INPCURSOR::GetMotion()
* @brief      Get Motion instance
* @ingroup    INPUT
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     INPCURSORMOTION* : Motion instance
*
*---------------------------------------------------------------------------------------------------------------------*/
INPCURSORMOTION* INPCURSOR::GetMotion()
{
  return &motion;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool INPCURSOR::AddPointToMotion(bool ispressed)
* @brief      Add Point To Motion
* @ingroup    INPUT
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  ispressed : is pressed
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool INPCURSOR::AddPointToMotion(bool ispressed)
{
  if(ispressed)
    {
      if(!motion.IsInCurse())
        {
          motion.Reset();
          motion.SetIsInCurse(true);
        }

      motion.AddPoint(GetX(), GetY(), GetZ());
    }
   else
    {
      if(motion.IsInCurse())
        {
          motion.AddPoint(GetX(), GetY(), GetZ());

          motion.SetTimeElapsed(GetTimer()->GetMeasureMilliSeconds());
          motion.SetIsInCurse(false);
        }
    }

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void INPCURSOR::Set(float x , float y, float z)
* @brief      Set cursor
* @ingroup    INPUT
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  x : new x position
* @param[in]  y : new y position
* @param[in]  z : new x position
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void INPCURSOR::Set(float x , float y, float z)
{
  double xx=(x-this->source.x1)/(this->source.x2-this->source.x1);

  xx = xx*(this->destination.x2-this->destination.x1)+this->destination.x1;

  double yy=(y-this->source.y1)/(this->source.y2-this->source.y1);

  yy = yy*(this->destination.y2-this->destination.y1)+this->destination.y1;

  this->x = (float)xx;
  this->y = (float)yy;
  this->z = (float)z;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void INPCURSOR::SetX(float x)
* @brief      Set X cursor position
* @ingroup    INPUT
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  x : new x position
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void INPCURSOR::SetX(float x)
{
  double xx = (x - source.x1) / (source.x2 - source.x1);

  xx = xx * (destination.x2 - destination.x1) + destination.x1;

  this->x = (float)xx;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void INPCURSOR::SetY(float y)
* @brief      Set Y cursor position
* @ingroup    INPUT
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  y : new y position
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void INPCURSOR::SetY(float y)
{
  double yy = (y- source.y1) / (source.y2 - source.y1);
        
  yy = yy * (destination.y2 - destination.y1) + destination.y1;

  this->y = (float)yy;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void INPCURSOR::SetZ(float z)
* @brief      Set Z cursor position
* @ingroup    INPUT
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  z : new z position
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void INPCURSOR::SetZ(float z)
{
  this->z = z;
}



//-------------------------------------------------------------------
//  INPCURSOR::Clean
/**
//
//
//  @author      Abraham J. Velez
//  @version      11/02/2003 17:37:08
//
//  @return       void :
//  */
//-------------------------------------------------------------------
void INPCURSOR::Clean()
{
  timer         = NULL;

  ID            = INPCURSOR_ID_NONE;

  ischanged     = false;
  havepreselect = false;
};
