/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       INPCapture_XEvent.cpp
* 
* @class      INPCAPTURE_XEVENT
* @brief      Input Capture eXtended Event class
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

#include "INPCapture_XEvent.h"

#pragma endregion


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES


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
* @fn         INPCAPTURE_XEVENT::INPCAPTURE_XEVENT(XSUBJECT* subject, XDWORD type, XDWORD family)
* @brief      Constructor of class
* @ingroup    INPUT
* 
* @param[in]  subject : 
* @param[in]  type : 
* @param[in]  family : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
INPCAPTURE_XEVENT::INPCAPTURE_XEVENT(XSUBJECT* subject, XDWORD type, XDWORD family) : XEVENT(subject, type, family)
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         INPCAPTURE_XEVENT::~INPCAPTURE_XEVENT()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    INPUT
* 
* --------------------------------------------------------------------------------------------------------------------*/
INPCAPTURE_XEVENT::~INPCAPTURE_XEVENT()

{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDWORD INPCAPTURE_XEVENT::GetVKCode()
* @brief      Get VK code
* @ingroup    INPUT
* 
* @return     XDWORD : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD INPCAPTURE_XEVENT::GetVKCode()
{
  return vkcode;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void INPCAPTURE_XEVENT::SetVKCode(XDWORD vkcode)
* @brief      Set VK code
* @ingroup    INPUT
* 
* @param[in]  vkcode : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void INPCAPTURE_XEVENT::SetVKCode(XDWORD vkcode)
{
  this->vkcode = vkcode;
}
 

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XWORD INPCAPTURE_XEVENT::GetScanCode()
* @brief      Get scan code
* @ingroup    INPUT
* 
* @return     XWORD : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XWORD INPCAPTURE_XEVENT::GetScanCode()
{
  return scancode;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void INPCAPTURE_XEVENT::SetScanCode(XWORD scancode)
* @brief      Set scan code
* @ingroup    INPUT
* 
* @param[in]  scancode : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void INPCAPTURE_XEVENT::SetScanCode(XWORD scancode)
{
  this->scancode = scancode;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDWORD INPCAPTURE_XEVENT::GetFlags()
* @brief      Get flags
* @ingroup    INPUT
* 
* @return     XDWORD : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD INPCAPTURE_XEVENT::GetFlags()
{
  return flags;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void INPCAPTURE_XEVENT::SetFlags(XWORD flags)
* @brief      Set flags
* @ingroup    INPUT
* 
* @param[in]  flags : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void INPCAPTURE_XEVENT::SetFlags(XWORD flags)
{
  this->flags = flags;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool INPCAPTURE_XEVENT::IsKeyLocked()
* @brief      Is key locked
* @ingroup    INPUT
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool INPCAPTURE_XEVENT::IsKeyLocked()
{
  return iskeylocked;
}

    
/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void INPCAPTURE_XEVENT::SetIsKeyLocked(bool iskeylocked)
* @brief      Set is key locked
* @ingroup    INPUT
* 
* @param[in]  iskeylocked : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void INPCAPTURE_XEVENT::SetIsKeyLocked(bool iskeylocked)
{
  this->iskeylocked = iskeylocked;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDWORD INPCAPTURE_XEVENT::GetNKeys()
* @brief      Get N keys
* @ingroup    INPUT
* 
* @return     XDWORD : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD INPCAPTURE_XEVENT::GetNKeys()
{
  return nkeys;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void INPCAPTURE_XEVENT::SetNKeys(XDWORD nkeys)
* @brief      Set N keys
* @ingroup    INPUT
* 
* @param[in]  nkeys : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void INPCAPTURE_XEVENT::SetNKeys(XDWORD nkeys)
{
  this->nkeys = nkeys;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDWORD INPCAPTURE_XEVENT::GetLimit()
* @brief      Get limit
* @ingroup    INPUT
* 
* @return     XDWORD : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD INPCAPTURE_XEVENT::GetLimit()
{
  return limit;
}
    

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void INPCAPTURE_XEVENT::SetLimit(XDWORD limit)
* @brief      Set limit
* @ingroup    INPUT
* 
* @param[in]  limit : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void INPCAPTURE_XEVENT::SetLimit(XDWORD limit)
{
  this->limit = limit;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XBUFFER* INPCAPTURE_XEVENT::GetBuffer()
* @brief      Get buffer
* @ingroup    INPUT
* 
* @return     XBUFFER* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XBUFFER* INPCAPTURE_XEVENT::GetBuffer()
{
  return &buffer;    
}
    

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSTRING* INPCAPTURE_XEVENT::GetString()
* @brief      Get string
* @ingroup    INPUT
* 
* @return     XSTRING* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* INPCAPTURE_XEVENT::GetString()
{
  return &string;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void INPCAPTURE_XEVENT::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    INPUT
* 
* --------------------------------------------------------------------------------------------------------------------*/
void INPCAPTURE_XEVENT::Clean()
{
  vkcode        = 0; 
  scancode      = 0;
  flags         = 0;
  iskeylocked   = false;

  nkeys         = 0;
  limit         = 0;

  buffer.Empty();
  string.Empty();
}



#pragma endregion

