/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       INPCapture.cpp
* 
* @class      INPCAPTURE
* @brief      Input Capture class
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

#include "INPCapture.h"

#include "INPCapture_XEvent.h"

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
* @fn         INPCAPTURE::INPCAPTURE()
* @brief      Constructor of class
* @ingroup    INPUT
* 
* --------------------------------------------------------------------------------------------------------------------*/
INPCAPTURE::INPCAPTURE()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         INPCAPTURE::~INPCAPTURE()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    INPUT
* 
* --------------------------------------------------------------------------------------------------------------------*/
INPCAPTURE::~INPCAPTURE()
{ 
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void INPCAPTURE::Application_SetHandle(void* applicationhandle)
* @brief      Application set handle
* @ingroup    INPUT
* 
* @param[in]  applicationhandle : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void INPCAPTURE::Application_SetHandle(void* applicationhandle)
{
  this->applicationhandle = applicationhandle;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool INPCAPTURE::Activate()
* @brief      Activate
* @ingroup    INPUT
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool INPCAPTURE::Activate()
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool INPCAPTURE::Deactivate()
* @brief      Deactivate
* @ingroup    INPUT
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool INPCAPTURE::Deactivate()
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDWORD INPCAPTURE::GetNKeys()
* @brief      Get N keys
* @ingroup    INPUT
* 
* @return     XDWORD : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD INPCAPTURE::GetNKeys()
{
  return nkeys;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void INPCAPTURE::SetNKeys(XDWORD nkeys)
* @brief      Set N keys
* @ingroup    INPUT
* 
* @param[in]  nkeys : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void INPCAPTURE::SetNKeys(XDWORD nkeys)
{
  this->nkeys = nkeys;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDWORD INPCAPTURE::GetLimit()
* @brief      Get limit
* @ingroup    INPUT
* 
* @return     XDWORD : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD INPCAPTURE::GetLimit()
{
  return limit;
}
    

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void INPCAPTURE::SetLimit(XDWORD limit)
* @brief      Set limit
* @ingroup    INPUT
* 
* @param[in]  limit : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void INPCAPTURE::SetLimit(XDWORD limit)
{
  this->limit = limit;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XBUFFER* INPCAPTURE::GetBuffer()
* @brief      Get buffer
* @ingroup    INPUT
* 
* @return     XBUFFER* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XBUFFER* INPCAPTURE::GetBuffer()
{
  return &buffer;    
}
    

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSTRING* INPCAPTURE::GetString()
* @brief      Get string
* @ingroup    INPUT
* 
* @return     XSTRING* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* INPCAPTURE::GetString()
{
  return &string;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void INPCAPTURE::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    INPUT
* 
* --------------------------------------------------------------------------------------------------------------------*/
void INPCAPTURE::Clean()
{
  applicationhandle   = NULL;  

  nkeys               = 0;
  limit               = 0;

  buffer.Empty();
  string.Empty();
}


#pragma endregion
