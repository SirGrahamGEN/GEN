/**-------------------------------------------------------------------------------------------------------------------
*
* @file       DIODisplayDevice.cpp
*
* @class      DIODISPLAYDEVICE
* @brief      Data Input/Output Display Device (generic display device class)
* @ingroup    GRAPHIC
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


#include "DIODisplayDevice.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------*/
/*  DIODISPLAYDEVICE_CONFIG::DIODISPLAYDEVICE_CONFIG                                                                  */
/*--------------------------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIODISPLAYDEVICE_CONFIG::DIODISPLAYDEVICE_CONFIG()
* @brief      Constructor
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
DIODISPLAYDEVICE_CONFIG::DIODISPLAYDEVICE_CONFIG()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIODISPLAYDEVICE_CONFIG::~DIODISPLAYDEVICE_CONFIG()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
DIODISPLAYDEVICE_CONFIG::~DIODISPLAYDEVICE_CONFIG()
{
  Clean();
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int DIODISPLAYDEVICE_CONFIG::GetWidth()
* @brief      GetWidth
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     int :
*
*---------------------------------------------------------------------------------------------------------------------*/
int DIODISPLAYDEVICE_CONFIG::GetWidth()
{
  return width;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int DIODISPLAYDEVICE_CONFIG::GetHeight()
* @brief      GetHeight
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     int :
*
*---------------------------------------------------------------------------------------------------------------------*/
int DIODISPLAYDEVICE_CONFIG::GetHeight()
{
  return height;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD DIODISPLAYDEVICE_CONFIG::GetNPixels()
* @brief      GetNPixels
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     XDWORD :
*
*---------------------------------------------------------------------------------------------------------------------*/
XDWORD DIODISPLAYDEVICE_CONFIG::GetNPixels()
{
  return (width*height);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD DIODISPLAYDEVICE_CONFIG::GetSizeBuffer()
* @brief      GetSizeBuffer
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     XDWORD :
*
*---------------------------------------------------------------------------------------------------------------------*/
XDWORD DIODISPLAYDEVICE_CONFIG::GetSizeBuffer()
{
  return sizebuffer;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIODISPLAYDEVICE_CONFIG::SetActiveBlackLight(bool active)
* @brief      SetActiveBlackLight
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  active :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIODISPLAYDEVICE::SetActiveBlackLight(bool active)
{
  return false;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIODISPLAYDEVICE_CONFIG::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void DIODISPLAYDEVICE_CONFIG::Clean()
{
  width                   = 0;
  height                  = 0;
  sizebuffer              = 0;

  isdirectconnection      = false;
}




/*--------------------------------------------------------------------------------------------------------------------*/
/*  DIODISPLAYDEVICE::DIODISPLAYDEVICE                                                                                */
/*--------------------------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIODISPLAYDEVICE::DIODISPLAYDEVICE()
* @brief      Constructor
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
DIODISPLAYDEVICE::DIODISPLAYDEVICE()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIODISPLAYDEVICE::~DIODISPLAYDEVICE()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
DIODISPLAYDEVICE::~DIODISPLAYDEVICE()
{  
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDWORD DIODISPLAYDEVICE::GetGPIOEntryID(DIODISPLAYDEVICE_INDEX_GPIOENTRYID index)
* @brief      GetGPIOEntryID
* @ingroup    DATAIO
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @param[in]  index : 
* 
* @return     XDWORD : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
XDWORD DIODISPLAYDEVICE::GetGPIOEntryID(DIODISPLAYDEVICE_INDEX_GPIOENTRYID index)
{
  return GPIOentrysID[index];        
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIODISPLAYDEVICE::SetGPIOEntryID(DIODISPLAYDEVICE_INDEX_GPIOENTRYID index, XDWORD GPIOentryID)
* @brief      SetGPIOEntryID
* @ingroup    DATAIO
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @param[in]  index : 
* @param[in]  GPIOentryID : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool DIODISPLAYDEVICE::SetGPIOEntryID(DIODISPLAYDEVICE_INDEX_GPIOENTRYID index, XDWORD GPIOentryID)
{
  GPIOentrysID[index] = GPIOentryID;   

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIODISPLAYDEVICE::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    DATAIO
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @return     void : does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void DIODISPLAYDEVICE::Clean()
{
  for(int c=0; c<DIODISPLAYDEVICE_INDEX_GPIOENTRYID_MAX; c++)
    {
      GPIOentrysID[c] =  DIOGPIO_ID_NOTDEFINED;     
    }  
}