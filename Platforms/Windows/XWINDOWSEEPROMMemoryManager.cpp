/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       XWINDOWSEEPROMMemoryManager.cpp
* 
* @class      XWINDOWSEEPROMMEMORYMANAGER
* @brief      eXtended WINDOWS EEPROM Memory Manager class
* @ingroup    PLATFORM_WINDOWS
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @copyright  Copyright(c) 2005 - 2021 GEN Group.
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

#include <stdio.h>
#include <string.h>

#include "XWINDOWSEEPROMMemoryManager.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XWINDOWSEEPROMMEMORYMANAGER::XWINDOWSEEPROMMEMORYMANAGER()
* @brief      Constructor
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
XWINDOWSEEPROMMEMORYMANAGER::XWINDOWSEEPROMMEMORYMANAGER()
{

}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XWINDOWSEEPROMMEMORYMANAGER::~XWINDOWSEEPROMMEMORYMANAGER()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
XWINDOWSEEPROMMEMORYMANAGER::~XWINDOWSEEPROMMEMORYMANAGER()
{

}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XWINDOWSEEPROMMEMORYMANAGER::Ini()
* @brief      Ini
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XWINDOWSEEPROMMEMORYMANAGER::Ini()
{
  return false;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XWINDOWSEEPROMMEMORYMANAGER::End()
* @brief      End
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XWINDOWSEEPROMMEMORYMANAGER::End()
{
  return false;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XWINDOWSEEPROMMEMORYMANAGER::Read(XDWORD offset, XBYTE& data)
* @brief      Read
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  offset :
* @param[in]  data :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XWINDOWSEEPROMMEMORYMANAGER::Read(XDWORD offset, XBYTE& data)
{
  return Read(offset, (XBYTE*)&data, sizeof(XBYTE));
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XWINDOWSEEPROMMEMORYMANAGER::Read(XDWORD offset, XWORD& data)
* @brief      Read
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  offset :
* @param[in]  data :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XWINDOWSEEPROMMEMORYMANAGER::Read(XDWORD offset, XWORD& data)
{
  return Read(offset, (XBYTE*)&data, sizeof(XWORD));
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XWINDOWSEEPROMMEMORYMANAGER::Read(XDWORD offset, XDWORD& data)
* @brief      Read
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  offset :
* @param[in]  data :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XWINDOWSEEPROMMEMORYMANAGER::Read(XDWORD offset, XDWORD& data)
{
  return Read(offset, (XBYTE*)&data, sizeof(XDWORD));
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XWINDOWSEEPROMMEMORYMANAGER::Read(XDWORD offset, XBYTE* data, XDWORD size)
* @brief      Read
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  offset :
* @param[in]  data :
* @param[in]  size :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XWINDOWSEEPROMMEMORYMANAGER::Read(XDWORD offset, XBYTE* data, XDWORD size)
{
  return false;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XWINDOWSEEPROMMEMORYMANAGER::Write(XDWORD offset, XBYTE data)
* @brief      Write
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  offset :
* @param[in]  data :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XWINDOWSEEPROMMEMORYMANAGER::Write(XDWORD offset, XBYTE data)
{
  return Write(offset, (XBYTE*)&data, sizeof(XBYTE));
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XWINDOWSEEPROMMEMORYMANAGER::Write(XDWORD offset, XWORD data)
* @brief      Write
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  offset :
* @param[in]  data :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XWINDOWSEEPROMMEMORYMANAGER::Write(XDWORD offset, XWORD data)
{
  return Write(offset, (XBYTE*)&data, sizeof(XWORD));
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XWINDOWSEEPROMMEMORYMANAGER::Write(XDWORD offset, XDWORD data)
* @brief      Write
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  offset :
* @param[in]  data :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XWINDOWSEEPROMMEMORYMANAGER::Write(XDWORD offset, XDWORD data)
{
  return Write(offset,(XBYTE*)&data, sizeof(XDWORD));
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XWINDOWSEEPROMMEMORYMANAGER::Write(XDWORD offset, XBYTE* data, XDWORD size)
* @brief      Write
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  offset :
* @param[in]  data :
* @param[in]  size :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XWINDOWSEEPROMMEMORYMANAGER::Write(XDWORD offset, XBYTE* data, XDWORD size)
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XWINDOWSEEPROMMEMORYMANAGER::EraseAll()
* @brief      EraseAll
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XWINDOWSEEPROMMEMORYMANAGER::EraseAll()
{
  return false;
}






