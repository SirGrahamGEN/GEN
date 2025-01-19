/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       INPLINUXDeviceID.cpp
* 
* @class      INPLINUXDEVICEID
* @brief      LINUX Input device ID class
* @ingroup    PLATFORM_LINUX
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

#include "INPLINUXDeviceID.h"

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
* @fn         INPLINUXDEVICEID::INPLINUXDEVICEID()
* @brief      Constructor of class
* @ingroup    PLATFORM_LINUX
*
* --------------------------------------------------------------------------------------------------------------------*/
INPLINUXDEVICEID::INPLINUXDEVICEID()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         INPLINUXDEVICEID::~INPLINUXDEVICEID()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    PLATFORM_LINUX
*
* --------------------------------------------------------------------------------------------------------------------*/
INPLINUXDEVICEID::~INPLINUXDEVICEID()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         INPDEVICE_TYPE INPLINUXDEVICEID::GetType()
* @brief      Get type
* @ingroup    PLATFORM_LINUX
*
* @return     INPDEVICE_TYPE : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
INPDEVICE_TYPE INPLINUXDEVICEID::GetType()
{
 return type;
}
   

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void INPLINUXDEVICEID::SetType(INPDEVICE_TYPE type)
* @brief      Set type
* @ingroup    PLATFORM_LINUX
* 
* @param[in]  type : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void INPLINUXDEVICEID::SetType(INPDEVICE_TYPE type)
{
  this->type = type;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* INPLINUXDEVICEID::GetName()
* @brief      Get name
* @ingroup    PLATFORM_LINUX
*
* @return     XSTRING* : name of device ID
*
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* INPLINUXDEVICEID::GetName()
{
  return &name;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         int INPLINUXDEVICEID::GetEventIndex()
* @brief      Get event index
* @ingroup    PLATFORM_LINUX
* 
* @return     int : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
int INPLINUXDEVICEID::GetEventIndex()
{
  return eventindex;
}
 

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void INPLINUXDEVICEID::SetEventIndex(int eventindex)
* @brief      Set event index
* @ingroup    PLATFORM_LINUX
* 
* @param[in]  eventindex : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void INPLINUXDEVICEID::SetEventIndex(int eventindex)
{
  this->eventindex = eventindex;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int INPLINUXDEVICEID::GetFileDescriptor()
* @brief      Get file descriptor
* @ingroup    PLATFORM_LINUX
*
* @return     int : file descriptor
*
* --------------------------------------------------------------------------------------------------------------------*/
int INPLINUXDEVICEID::GetFileDescriptor()
{
  return filedescriptor;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void INPLINUXDEVICEID::SetFileDescriptor(int filedescriptor)
* @brief      Set file descriptor
* @ingroup    PLATFORM_LINUX
*
* @param[in]  filedescriptor : new file descriptor
*
* --------------------------------------------------------------------------------------------------------------------*/
void INPLINUXDEVICEID::SetFileDescriptor(int filedescriptor)
{
  this->filedescriptor = filedescriptor;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void INPLINUXDEVICEID::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    PLATFORM_LINUX
*
* --------------------------------------------------------------------------------------------------------------------*/
void INPLINUXDEVICEID::Clean()
{
  type            = INPDEVICE_TYPE_NONE;  
  eventindex      = INPLINUXDEVICEID_INVALID;
  filedescriptor  = INPLINUXDEVICEID_INVALID;
}


#pragma endregion

