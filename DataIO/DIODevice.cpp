/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIODevice.cpp
* 
* @class      DIODEVICE
* @brief      Data Input/Output device generic class
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

#include "DIODevice.h"

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
* @fn         DIODEVICE::DIODEVICE()
* @brief      Constructor of class
* @ingroup    DATAIO
*
* ---------------------------------------------------------------------------------------------------------------------*/
DIODEVICE::DIODEVICE()
{ 
  Clean();                              
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIODEVICE::~DIODEVICE()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    DATAIO
*
* ---------------------------------------------------------------------------------------------------------------------*/
DIODEVICE::~DIODEVICE()            
{ 
  Clean();                              
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIODEVICE::Ini(void)
* @brief      Ini
* @ingroup    DATAIO
*
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool DIODEVICE::Ini(void)
{
  isinitialized = true;
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIODEVICE::IsInitialized()
* @brief      Is initialized
* @ingroup    DATAIO
*
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool DIODEVICE::IsInitialized()            
{ 
  return isinitialized;                 
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIODEVICE::End(void)
* @brief      End
* @ingroup    DATAIO
*
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool DIODEVICE::End(void)
{
  isinitialized = false;
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIODEVICE::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    DATAIO
*
* ---------------------------------------------------------------------------------------------------------------------*/
void DIODEVICE::Clean()
{
  isinitialized = false;
}


#pragma endregion

