/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       INPButton.cpp
* 
* @class      INPBUTTON
* @brief      Input Button Class
* @ingroup    INPUT
* 
* @copyright  GEN Group. All rights reserved.
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
* --------------------------------------------------------------------------------------------------------------------*/

/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_DEFINES_INCLUDE

#include "GEN_Defines.h"

#pragma endregion


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "INPButton.h"

#include <string.h>

#include "XTimer.h"
#include "XFactory.h"
#include "XTrace.h"

#pragma endregion


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_CONTROL_INCLUDE

#include "GEN_Control.h"

#pragma endregion



/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         INPBUTTON::INPBUTTON()
* @brief      Constructor of class
* @ingroup    INPUT
*
* --------------------------------------------------------------------------------------------------------------------*/
INPBUTTON::INPBUTTON()
{
  Clean();

  GEN_XFACTORY_CREATE(xtimerpress, CreateTimer())
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         INPBUTTON::~INPBUTTON()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    INPUT
*
* --------------------------------------------------------------------------------------------------------------------*/
INPBUTTON::~INPBUTTON()
{
  if(xtimerpress) GEN_XFACTORY.DeleteTimer(xtimerpress);

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         INPBUTTON_ID INPBUTTON::GetID()
* @brief      Get ID
* @ingroup    INPUT
*
* @return     INPBUTTON_ID : ID of button
*
* --------------------------------------------------------------------------------------------------------------------*/
INPBUTTON_ID INPBUTTON::GetID()
{
  return ID;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void INPBUTTON::SetID(INPBUTTON_ID ID)
* @brief      Set ID
* @ingroup    INPUT
*
* @param[in]  ID : new ID to Set
*
* --------------------------------------------------------------------------------------------------------------------*/
void INPBUTTON::SetID(INPBUTTON_ID ID)
{
  this->ID = ID;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XWORD INPBUTTON::GetKeyCode()
* @brief      Get key code
* @ingroup    INPUT
*
* @return     XWORD : Key Code of button
*
* --------------------------------------------------------------------------------------------------------------------*/
XWORD INPBUTTON::GetKeyCode()
{
  return keycode;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void INPBUTTON::SetKeyCode(XWORD keycode)
* @brief      Set key code
* @ingroup    INPUT
*
* @param[in]  keycode : new Key Code of button
*
* --------------------------------------------------------------------------------------------------------------------*/
void INPBUTTON::SetKeyCode(XWORD keycode)
{
  this->keycode = keycode;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XCHAR INPBUTTON::GetSymbol()
* @brief      Get symbol
* @ingroup    INPUT
*
* @return     XCHAR : Symbol of key
*
* --------------------------------------------------------------------------------------------------------------------*/
XCHAR INPBUTTON::GetSymbol()
{
  return symbol;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void INPBUTTON::SetSymbol(XCHAR symbol)
* @brief      Set symbol
* @ingroup    INPUT
*
* @param[in]  symbol : new Symbol of key
*
* --------------------------------------------------------------------------------------------------------------------*/
void INPBUTTON::SetSymbol(XCHAR symbol)
{
  this->symbol = symbol;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         INPBUTTON_STATE INPBUTTON::GetState()
* @brief      Get state
* @ingroup    INPUT
*
* @return     INPBUTTON_STATE : statue of button
*
* --------------------------------------------------------------------------------------------------------------------*/
INPBUTTON_STATE INPBUTTON::GetState()
{
  return state;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void INPBUTTON::SetState(INPBUTTON_STATE state)
* @brief      Set state
* @ingroup    INPUT
*
* @param[in]  state : new state
*
* --------------------------------------------------------------------------------------------------------------------*/
void INPBUTTON::SetState(INPBUTTON_STATE state)
{
  this->state = state;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         float INPBUTTON::GetPressure()
* @brief      Get pressure
* @ingroup    INPUT
*
* @return     float :
*
* --------------------------------------------------------------------------------------------------------------------*/
float INPBUTTON::GetPressure()
{
  return pressure;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void INPBUTTON::SetPressure(float pressure)
* @brief      Set pressure
* @ingroup    INPUT
*
* @param[in]  pressure : new pressure
*
* --------------------------------------------------------------------------------------------------------------------*/
void INPBUTTON::SetPressure(float pressure)
{
  this->pressure = pressure;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool INPBUTTON::IsPressed()
* @brief      Is pressed
* @ingroup    INPUT
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool INPBUTTON::IsPressed()
{
  return pressed;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool INPBUTTON::IsPressedWithRelease()
* @brief      Is pressed with release
* @ingroup    INPUT
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
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
* @brief      Set pressed
* @ingroup    INPUT
*
* @param[in]  ispressed :
*
* --------------------------------------------------------------------------------------------------------------------*/
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
* @brief      Get time pressed
* @ingroup    INPUT
*
* @return     XQWORD : Millisecond pressed
*
* --------------------------------------------------------------------------------------------------------------------*/
XQWORD INPBUTTON::GetTimePressed()
{
  if(!xtimerpress) return 0;

  return xtimerpress->GetMeasureMilliSeconds();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool INPBUTTON::CreateButton(XVECTOR<INPBUTTON*>* buttons, int keycode, INPBUTTON_ID ID, XCHAR symbol)
* @brief      Create button
* @ingroup    INPUT
*
* @param[in]  buttons : vector to add new button
* @param[in]  keycode : key code of new button
* @param[in]  ID : ID of new button
* @param[in]  symbol : symbol of new button
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
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
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    INPUT
*
* --------------------------------------------------------------------------------------------------------------------*/
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


#pragma endregion

