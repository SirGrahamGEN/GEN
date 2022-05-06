/**-------------------------------------------------------------------------------------------------------------------
*
* @file       XANDROIDFile.cpp
*
* @class      XANDROIDFILE
* @brief      ANDROID eXtended File class
* @ingroup    PLATFORM_ANDROID
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

/*---- PRECOMPILATION CONTROL ----------------------------------------------------------------------------------------*/

#include "GEN_Defines.h"


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include <stdlib.h>

#include "XANDROIDFile.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XANDROIDFILE::XANDROIDFILE()
* @brief      Constructor
* @ingroup    PLATFORM_ANDROID
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
XANDROIDFILE::XANDROIDFILE(): XFILE()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XANDROIDFILE::~XANDROIDFILE()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    PLATFORM_ANDROID
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
XANDROIDFILE::~XANDROIDFILE()
{
  if(isopen) this->Close();

  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XANDROIDFILE::Exist(XCHAR* xpath)
* @brief      Exist
* @ingroup    PLATFORM_ANDROID
*
* @param[in]  xpath : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool XANDROIDFILE::Exist(XCHAR* xpath)
{
  bool status = Open(xpath, true);
  if(status) Close();

  return status;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XANDROIDFILE::Open(XCHAR* xpath, bool readonly)
* @brief      Open
* @ingroup    PLATFORM_ANDROID
*
* @param[in]  xpath : 
* @param[in]  readonly : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool XANDROIDFILE::Open(XCHAR* xpath, bool readonly)
{
  bool status = Open(xpath, true);

  isopen = status;

  return status;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XANDROIDFILE::Create(XCHAR* xpath)
* @brief      Create
* @ingroup    PLATFORM_ANDROID
*
* @param[in]  xpath : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool XANDROIDFILE::Create(XCHAR* xpath)
{
  bool status = Create(xpath);

  return status;
}




/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XANDROIDFILE::SetSize(XQWORD size)
* @brief      SetSize
* @ingroup    PLATFORM_ANDROID
*
* @param[in]  size : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool XANDROIDFILE::SetSize(XQWORD size)
{
  return false;
}



bool XANDROIDFILE::GetPosition(XQWORD& position)
{
  return false;
}

    
bool XANDROIDFILE::SetPosition(XQWORD position)
{

  return false;
}

   
bool XANDROIDFILE::Read(XBYTE* buffer, XDWORD size , CIPHER* cipher)
{

}


bool XANDROIDFILE::Read(XBYTE* buffer, XDWORD* size, CIPHER* cipher)
{

}

    
bool XANDROIDFILE::Write(XBYTE* buffer, XDWORD size , CIPHER* cipher)
{

}

    
bool XANDROIDFILE::Flush()
{

}

    
bool XANDROIDFILE::Close()
{

}

    
bool XANDROIDFILE::Erase(XCHAR* xpath, bool overwrite)
{

}
    

bool XANDROIDFILE::Rename(XCHAR* xpathold, XCHAR* xpathnew)
{

}

    
FILE* XANDROIDFILE::CreateStructHandle()
{

}
    

bool XANDROIDFILE::DeleteStructHandle()
{

}


void XANDROIDFILE::ChangeAttributes(XCHAR* attributes)
{

}


bool XANDROIDFILE::ActualizeSize()
{
  return false;
}


void XANDROIDFILE::Clean()
{

}

