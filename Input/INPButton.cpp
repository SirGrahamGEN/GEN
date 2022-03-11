/**-------------------------------------------------------------------------------------------------------------------
*
* @file       INPButton.cpp
*
* @class      INPBUTTON
* @brief      Input Button Class
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

#include "XTimer.h"
#include "XFactory.h"
#include "XTrace.h"

#include "INPButton.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         INPBUTTON::INPBUTTON()
* @brief      Constructor
* @ingroup    INPUT
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
INPBUTTON::INPBUTTON()

{
  Clean();

  xtimerpress = GEN_XFACTORY.CreateTimer();  
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         INPBUTTON::~INPBUTTON()
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
INPBUTTON::~INPBUTTON()
{
  if(xtimerpress) GEN_XFACTORY.DeleteTimer(xtimerpress);

  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         INPBUTTON_ID INPBUTTON::GetID()
* @brief      Get ID of button
* @ingroup    INPUT
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     INPBUTTON_ID : ID of button
*
*---------------------------------------------------------------------------------------------------------------------*/
INPBUTTON_ID INPBUTTON::GetID()
{
  return ID;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void INPBUTTON::SetID(INPBUTTON_ID ID)
* @brief      Set ID of button
* @ingroup    INPUT
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  ID : new ID to Set
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void INPBUTTON::SetID(INPBUTTON_ID ID)
{
  this->ID = ID;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XWORD INPBUTTON::GetKeyCode()
* @brief      Get Key Code
* @ingroup    INPUT
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     XWORD : Key Code of button
*
*---------------------------------------------------------------------------------------------------------------------*/
XWORD INPBUTTON::GetKeyCode()
{
  return keycode;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void INPBUTTON::SetKeyCode(XWORD keycode)
* @brief      Set Key Code
* @ingroup    INPUT
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  keycode : new Key Code of button
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void INPBUTTON::SetKeyCode(XWORD keycode)
{
  this->keycode = keycode;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XCHAR INPBUTTON::GetSymbol()
* @brief      Get Symbol
* @ingroup    INPUT
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     XCHAR : Symbol of key
*
*---------------------------------------------------------------------------------------------------------------------*/
XCHAR INPBUTTON::GetSymbol()
{
  return symbol;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void INPBUTTON::SetSymbol(XCHAR symbol)
* @brief      Set Symbol
* @ingroup    INPUT
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  symbol : new Symbol of key
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void INPBUTTON::SetSymbol(XCHAR symbol)
{
  this->symbol = symbol;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         INPBUTTON_STATE INPBUTTON::GetState()
* @brief      GetState
* @ingroup    INPUT
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     INPBUTTON_STATE : statue of button
*
*---------------------------------------------------------------------------------------------------------------------*/
INPBUTTON_STATE INPBUTTON::GetState()
{
  return state;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void INPBUTTON::SetState(INPBUTTON_STATE state)
* @brief      SetState
* @ingroup    INPUT
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  state : new state
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void INPBUTTON::SetState(INPBUTTON_STATE state)
{
  this->state = state;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         float INPBUTTON::GetPressure()
* @brief      GetPressure
* @ingroup    INPUT
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     float :
*
*---------------------------------------------------------------------------------------------------------------------*/
float INPBUTTON::GetPressure()
{
  return pressure;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void INPBUTTON::SetPressure(float pressure)
* @brief      Set Pressure button
* @ingroup    INPUT
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  pressure : new pressure
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void INPBUTTON::SetPressure(float pressure)
{
  this->pressure = pressure;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool INPBUTTON::IsPressed()
* @brief      Is Pressed button
* @ingroup    INPUT
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool INPBUTTON::IsPressed()
{
  return pressed;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool INPBUTTON::IsPressedWithRelease()
* @brief      Is Pressed With Release
* @ingroup    INPUT
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool INPBUTTON::IsPressedWithRelease()
{
  if(!presswithrelease)
    {
      if(!IsPressed()) return false;
      presswithrelease = true;
    }
   else
    {
      if(IsPressed()) return false;
      presswithrelease = false;

      return true;
    }

  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void INPBUTTON::SetPressed(bool ispressed)
* @brief      Set Pressed
* @ingroup    INPUT
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  ispressed :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void INPBUTTON::SetPressed(bool ispressed)
{
  if(pressed != ispressed)
    {
      if(ispressed)
        {
          if(xtimerpress) xtimerpress->Reset();
        }
    }

  pressed = ispressed;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XQWORD INPBUTTON::GetTimePressed()
* @brief      Get Time Pressed
* @ingroup    INPUT
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     XQWORD : Millisecond pressed
*
*---------------------------------------------------------------------------------------------------------------------*/
XQWORD INPBUTTON::GetTimePressed()
{
  if(!xtimerpress) return 0;

  return xtimerpress->GetMeasureMilliSeconds();
}





/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool INPBUTTON::CreateButton(XVECTOR<INPBUTTON*>* buttons, int keycode, INPBUTTON_ID ID, XCHAR symbol)
* @brief      CreateButton
* @ingroup    INPUT
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  buttons : vector to add new button
* @param[in]  keycode : key code of new button
* @param[in]  ID : ID of new button
* @param[in]  symbol : symbol of new button
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool INPBUTTON::CreateButton(XVECTOR<INPBUTTON*>* buttons, int keycode, INPBUTTON_ID ID, XCHAR symbol)
{
  if(!buttons) return false;

  INPBUTTON* button;

  button = new INPBUTTON();
  if(!button) return false;

  button->SetKeyCode(keycode);
  button->SetID(ID);
  button->SetSymbol(symbol);

  buttons->Add(button);

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void INPBUTTON::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    INPUT
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void INPBUTTON::Clean()
{
  ID               = INPBUTTON_ID_NOBUTTON;
  keycode          = 0;
  symbol           = 0x00;

  state            = INPBUTTON_STATE_UNKNOWN;

  pressure         = 0.0f;
  pressed          = false;
  presswithrelease = false;
  timepress        = 0;

  xtimerpress      = NULL;
};


