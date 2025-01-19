/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIOLedNeoPixelWS2812B.cpp
* 
* @class      DIOLEDNEOPIXELWS2812B
* @brief      Data Input/Output Led Neopixel WS2812B class
* @ingroup    DATAIO
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

#include "DIOLedNeoPixelWS2812B.h"

#include "XTrace.h"
#include "XSleep.h"

#include "DIOGPIO.h"

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
* @fn         DIOLEDNEOPIXELWS2812B::DIOLEDNEOPIXELWS2812B()
* @brief      Constructor of class
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOLEDNEOPIXELWS2812B::DIOLEDNEOPIXELWS2812B()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOLEDNEOPIXELWS2812B::~DIOLEDNEOPIXELWS2812B()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOLEDNEOPIXELWS2812B::~DIOLEDNEOPIXELWS2812B()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOLEDNEOPIXELWS2812B::Ini(XDWORD nled)
* @brief      Ini
* @ingroup    DATAIO
* 
* @param[in]  nled : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOLEDNEOPIXELWS2812B::Ini(XDWORD nled)
{
  this->nled   = nled;
  
  databuffer.Resize(nled * 3);

  GEN_DIOGPIO.SetMode(GPIOentryID, DIOGPIO_MODE_OUTPUT);
 
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDWORD DIOLEDNEOPIXELWS2812B::GetDataGPIOEntryID()
* @brief      Get data GPIO entry ID
* @ingroup    DATAIO
*
* @return     XDWORD : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
XDWORD DIOLEDNEOPIXELWS2812B::GetDataGPIOEntryID()
{
  return GPIOentryID;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOLEDNEOPIXELWS2812B::SetDataGPIOEntryID(XDWORD GPIOentryID)
* @brief      Set data GPIO entry ID
* @ingroup    DATAIO
*
* @param[in]  GPIOentryID : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void DIOLEDNEOPIXELWS2812B::SetDataGPIOEntryID(XDWORD GPIOentryID)
{
  this->GPIOentryID = GPIOentryID;  
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOLEDNEOPIXELWS2812B::SendData(XBYTE* data, XDWORD size)
* @brief      Send data
* @ingroup    DATAIO
*
* @param[in]  data :
* @param[in]  size :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOLEDNEOPIXELWS2812B::SendData(XBYTE* data, XDWORD size)
{
  if(!data) return false;
  if(!size) return false;
  
  XDWORD _size = size;

  if(_size > databuffer.GetSize())  _size = databuffer.GetSize();

  databuffer.Set(data, _size, 0);

  return Send();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XBYTE DIOLEDNEOPIXELWS2812B::GetBrightnessLevel()
* @brief      Get brightness level
* @ingroup    DATAIO
*
* @return     XBYTE : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
XBYTE DIOLEDNEOPIXELWS2812B::GetBrightnessLevel()
{
  return brightnesslevel;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOLEDNEOPIXELWS2812B::SetBrightnessLevel(XBYTE brightnesslevel)
* @brief      Set brightness level
* @ingroup    DATAIO
* 
* @param[in]  brightnesslevel : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIOLEDNEOPIXELWS2812B::SetBrightnessLevel(XBYTE brightnesslevel)
{
  this->brightnesslevel = brightnesslevel;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOLEDNEOPIXELWS2812B::SendData(XBUFFER* data)
* @brief      Send data
* @ingroup    DATAIO
*
* @param[in]  data :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOLEDNEOPIXELWS2812B::SendData(XBUFFER* data)
{
  return SendData(data->Get(), data->GetSize());
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOLEDNEOPIXELWS2812B::Send()
* @brief      Send
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOLEDNEOPIXELWS2812B::Send()
{
  XBYTE* ptrdata  = databuffer.Get();
  int    sizedata = databuffer.GetSize();
      
  DIOGPIO_ENTRY* entry = GEN_DIOGPIO.GPIOEntry_GetByID(GPIOentryID);
  if(!entry) return false;

  GEN_DIOGPIO.SetValue(entry, false);

  for(int c=0; c<sizedata; c++)
    {
      XBYTE databyte = ptrdata[c];

      for(int b=0; b<8; b++)
        {
          if(databyte & 0x80)
            {
              GEN_DIOGPIO.SetValue(entry, true);
              GEN_XSLEEP.NanoSeconds(850);

              GEN_DIOGPIO.SetValue(entry, false); 
              GEN_XSLEEP.NanoSeconds(400);
            }
           else
            {
              GEN_DIOGPIO.SetValue(entry, true); 
              GEN_XSLEEP.NanoSeconds(400);

              GEN_DIOGPIO.SetValue(entry, false);
              GEN_XSLEEP.NanoSeconds(850);
            }

          databyte <<= 1;
        }
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOLEDNEOPIXELWS2812B::End()
* @brief      End
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOLEDNEOPIXELWS2812B::End()
{  
  databuffer.FillBuffer(0);

  Send();

  Clean();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOLEDNEOPIXELWS2812B::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOLEDNEOPIXELWS2812B::Clean()
{
  nled              = 0;
  GPIOentryID       = DIOGPIO_ID_NOTDEFINED;

  brightnesslevel   = 255;
}


#pragma endregion

