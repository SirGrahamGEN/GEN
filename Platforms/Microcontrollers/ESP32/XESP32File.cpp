/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       XESP32File.cpp
* 
* @class      XESP32FILE
* @brief      eXtended ESP32 File class
* @ingroup    PLATFORM_ESP32
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

#include "XESP32File.h"

#include "XPath.h"
#include "XString.h"
#include "XTrace.h"

#include "Cipher.h"

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
* @fn         XESP32FILE::XESP32FILE()
* @brief      Constructor of class
* @ingroup    PLATFORM_ESP32
*
* --------------------------------------------------------------------------------------------------------------------*/
XESP32FILE::XESP32FILE(): XFILE()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XESP32FILE::~XESP32FILE()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    PLATFORM_ESP32
*
* --------------------------------------------------------------------------------------------------------------------*/
XESP32FILE::~XESP32FILE()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XESP32FILE::Exist(XCHAR* path)
* @brief      Exist
* @ingroup    PLATFORM_ESP32
*
* @param[in]  path :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XESP32FILE::Exist(XCHAR* path)
{  
  bool status = false;
 
  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XESP32FILE::Open(XCHAR* xpath, bool isreadonly)
* @brief      Open
* @ingroup    PLATFORM_ESP32
*
* @param[in]  xpath :
* @param[in]  isreadonly :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XESP32FILE::Open(XCHAR* path, bool isreadonly)
{
  bool status = false;;

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XESP32FILE::Create(XCHAR* xpath)
* @brief      Create
* @ingroup    PLATFORM_ESP32
*
* @param[in]  xpath :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XESP32FILE::Create(XCHAR* path)
{
  bool status = false;

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XESP32FILE::SetSize(XQWORD size)
* @brief      Set size
* @ingroup    PLATFORM_ESP32
*
* @param[in]  size :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XESP32FILE::SetSize(XQWORD size)
{
  size = 0;

  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XESP32FILE::GetPosition(XQWORD& position)
* @brief      Get position
* @ingroup    PLATFORM_ESP32
*
* @param[in]  position :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XESP32FILE::GetPosition(XQWORD& position)
{
  position = 0;
 
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XESP32FILE::SetPosition(XQWORD position)
* @brief      Set position
* @ingroup    PLATFORM_ESP32
*
* @param[in]  position :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XESP32FILE::SetPosition(XQWORD position)
{  
  bool status = false;
 
  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XESP32FILE::Read(XBYTE* buffer, XDWORD size, CIPHER* cipher)
* @brief      Read
* @ingroup    PLATFORM_ESP32
*
* @param[in]  buffer :
* @param[in]  size :
* @param[in]  cipher :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XESP32FILE::Read(XBYTE* buffer, XDWORD size, CIPHER* cipher)
{
  bool  status = false;

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XESP32FILE::Read(XBYTE* buffer, XDWORD* size, CIPHER* cipher)
* @brief      Read
* @ingroup    PLATFORM_ESP32
*
* @param[in]  buffer :
* @param[in]  size :
* @param[in]  cipher :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XESP32FILE::Read(XBYTE* buffer, XDWORD* size, CIPHER* cipher)
{ 
  bool  status = false;
    
  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XESP32FILE::Write(XBYTE* buffer, XDWORD size, CIPHER* cipher)
* @brief      Write
* @ingroup    PLATFORM_ESP32
*
* @param[in]  buffer :
* @param[in]  size :
* @param[in]  cipher :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XESP32FILE::Write(XBYTE* buffer, XDWORD size, CIPHER* cipher)
{
  bool  status = false;
    
  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XESP32FILE::Flush()
* @brief      Flush
* @ingroup    PLATFORM_ESP32
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XESP32FILE::Flush()
{  
  bool status = false;
  
  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XESP32FILE::Close()
* @brief      Close
* @ingroup    PLATFORM_ESP32
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XESP32FILE::Close()
{  
  return false;  
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XESP32FILE::Erase(XCHAR* path,bool overwrite)
* @brief      Erase
* @ingroup    PLATFORM_ESP32
*
* @param[in]  path :
* @param[in]  overwrite :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XESP32FILE::Erase(XCHAR* path, bool overwrite)
{
  bool status = false;
 
  return status;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XESP32FILE::Rename(XCHAR* pathold, XCHAR* pathnew)
* @brief      Rename
* @ingroup    PLATFORM_ESP32
*
* @param[in]  pathold :
* @param[in]  pathnew :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XESP32FILE::Rename(XCHAR* pathold, XCHAR* pathnew)
{  
  bool status = false;
    
  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         FILE* XESP32FILE::CreateStructHandle()
* @brief      Create struct handle
* @ingroup    PLATFORM_ESP32
*
* @return     FILE* : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
FILE* XESP32FILE::CreateStructHandle()
{
  return NULL;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XESP32FILE::DeleteStructHandle()
* @brief      Delete struct handle
* @ingroup    PLATFORM_ESP32
*
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool XESP32FILE::DeleteStructHandle()
{
  return false;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XESP32FILE::ActualizeSize()
* @brief      Actualize size
* @ingroup    PLATFORM_ESP32
*
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool XESP32FILE::ActualizeSize()
{
  return Exist(xpathnamefile.Get());
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XESP32FILE::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    PLATFORM_ESP32
*
* --------------------------------------------------------------------------------------------------------------------*/
void XESP32FILE::Clean()
{
  
}


#pragma endregion

