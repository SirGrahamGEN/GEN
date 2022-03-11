/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       UI_Element_Animation.cpp
* 
* @class      UI_ELEMENT_ANIMATION
* @brief      User Interface Element Animation class
* @ingroup    USERINTERFACE
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @copyright  Copyright(c) 2005 - 2020 GEN Group.
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
* ---------------------------------------------------------------------------------------------------------------------*/

/*---- PRECOMPILATION CONTROL ----------------------------------------------------------------------------------------*/

#include "GEN_Defines.h"


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "XFactory.h"
#include "XTimer.h"

#include "GRPBitmap.h"

#include "UI_Element_Animation.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         UI_ELEMENT_ANIMATION::UI_ELEMENT_ANIMATION()
* @brief      Constructor
* @ingroup    USERINTERFACE
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @return     Does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
UI_ELEMENT_ANIMATION::UI_ELEMENT_ANIMATION()    
{ 
  Clean();   

  GEN_XFACTORY_CREATE(xtimerplay, CreateTimer())
  
  SetMilliSecondsDelay();

  SetType(UI_ELEMENT_TYPE_ANIMATION);
  GetTypeString()->Set(__L("animation"));  
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         UI_ELEMENT_ANIMATION::~UI_ELEMENT_ANIMATION()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    USERINTERFACE
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @return     Does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
UI_ELEMENT_ANIMATION::~UI_ELEMENT_ANIMATION()    
{ 
 
  if(xtimerplay) 
    {
      GEN_XFACTORY.DeleteTimer(xtimerplay);
      xtimerplay = NULL;
    }

  Clean();                            
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_ELEMENT_ANIMATION::Play()
* @brief      Play
* @ingroup    USERINTERFACE
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool UI_ELEMENT_ANIMATION::Play()
{
  state = UI_ELEMENT_ANIMATION_STATE_PLAY;

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_ELEMENT_ANIMATION::Play(int millisecdelay)
* @brief      Play
* @ingroup    USERINTERFACE
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @param[in]  millisecdelay : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool UI_ELEMENT_ANIMATION::Play(int millisecdelay)
{
  SetMilliSecondsDelay(millisecdelay);

  return Play();
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_ELEMENT_ANIMATION::Stop()
* @brief      Stop
* @ingroup    USERINTERFACE
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool UI_ELEMENT_ANIMATION::Stop()
{
  state = UI_ELEMENT_ANIMATION_STATE_STOP;

  return true;
}

    

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_ELEMENT_ANIMATION::Pause()
* @brief      Pause
* @ingroup    USERINTERFACE
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool UI_ELEMENT_ANIMATION::Pause()
{
  state = UI_ELEMENT_ANIMATION_STATE_PAUSE;

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         UI_ELEMENT_ANIMATION_STATE UI_ELEMENT_ANIMATION::GetState()
* @brief      GetState
* @ingroup    USERINTERFACE
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @return     UI_ELEMENT_ANIMATION_STATE : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
UI_ELEMENT_ANIMATION_STATE UI_ELEMENT_ANIMATION::GetState()
{
  return state;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XTIMER* UI_ELEMENT_ANIMATION::GetXTimerPlay()
* @brief      GetXTimerPlay
* @ingroup    USERINTERFACE
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @return     XTIMER* : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
XTIMER* UI_ELEMENT_ANIMATION::GetXTimerPlay()
{
  return xtimerplay;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         int UI_ELEMENT_ANIMATION::GetMilliSecondsDelay()
* @brief      GetMilliSecondsDelay
* @ingroup    USERINTERFACE
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @return     int : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
int UI_ELEMENT_ANIMATION::GetMilliSecondsDelay()
{
  return millisecdelay;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void UI_ELEMENT_ANIMATION::SetMilliSecondsDelay(int millisecdelay)
* @brief      SetMilliSecondsDelay
* @ingroup    USERINTERFACE
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @param[in]  millisecdelay : 
* 
* @return     void : does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void UI_ELEMENT_ANIMATION::SetMilliSecondsDelay(int millisecdelay)
{
  this->millisecdelay = millisecdelay;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         int UI_ELEMENT_ANIMATION::IndexImage_Get()
* @brief      IndexImage_Get
* @ingroup    USERINTERFACE
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @return     int : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
int UI_ELEMENT_ANIMATION::IndexImage_Get()
{
  return indeximage;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_ELEMENT_ANIMATION::IndexImage_Set(int indeximage)
* @brief      IndexImage_Set
* @ingroup    USERINTERFACE
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @param[in]  indeximage : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool UI_ELEMENT_ANIMATION::IndexImage_Set(int indeximage)
{
  if(indeximage <0)                                        return false;
  if(indeximage >= (int)GetComposeElements()->GetSize())   return false;

  if(this->indeximage != indeximage) SetMustReDraw(true);

  this->indeximage = indeximage;

  

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_ELEMENT_ANIMATION::IndexImage_Add(int inc)
* @brief      IndexImage_Add
* @ingroup    USERINTERFACE
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @param[in]  inc : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool UI_ELEMENT_ANIMATION::IndexImage_Add(int inc)
{
  indeximage += inc;

  SetMustReDraw(true);

  if(indeximage >= GetComposeElements()->GetSize()) indeximage = 0;

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_ELEMENT_ANIMATION::IndexImage_Reset()
* @brief      IndexImage_Reset
* @ingroup    USERINTERFACE
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool UI_ELEMENT_ANIMATION::IndexImage_Reset()
{
  indeximage = 0;

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XBYTE UI_ELEMENT_ANIMATION::GetAlpha()
* @brief      GetAlpha
* @ingroup    USERINTERFACE
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @return     XBYTE : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
XBYTE UI_ELEMENT_ANIMATION::GetAlpha()
{
  return alpha;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void UI_ELEMENT_ANIMATION::SetAlpha(XBYTE alpha)
* @brief      SetAlpha
* @ingroup    USERINTERFACE
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @param[in]  alpha : 
* 
* @return     void : does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void UI_ELEMENT_ANIMATION::SetAlpha(XBYTE alpha)
{
  this->alpha = alpha;
}





/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void UI_ELEMENT_ANIMATION::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    USERINTERFACE
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @return     void : does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void UI_ELEMENT_ANIMATION::Clean()
{
  xtimerplay      = NULL;
  millisecdelay   = 0;
  state           = UI_ELEMENT_ANIMATION_STATE_UNKNOWN;    
  indeximage      = 0;
  alpha           = 100;
}