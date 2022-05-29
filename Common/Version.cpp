/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       Version.cpp
* 
* @class      VERSION
* @brief      Version of framework
* @ingroup    PLATFORM_COMMON
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

#include "Version.h"

#include "XMemory_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

VERSION* VERSION::instance = NULL;

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool VERSION::GetIsInstanced()
* @brief      GetIsInstanced
* @ingroup    UTILS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool VERSION::GetIsInstanced()
{
  return instance!=NULL;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         VERSION& VERSION::GetInstance()
* @brief      GetInstance
* @ingroup    UTILS
*
* @return     VERSION& :
*
* --------------------------------------------------------------------------------------------------------------------*/
VERSION& VERSION::GetInstance()
{
  if(!instance) instance = new VERSION();

  return (*instance);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool VERSION::DelInstance()
* @brief      DelInstance
* @ingroup    UTILS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool VERSION::DelInstance()
{
  if(instance)
    {
      delete instance;
      instance = NULL;

      return true;
    }

  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSTRING* VERSION::GetName()
* @brief      GetName
* @ingroup    PLATFORM_COMMON
* 
* @return     XSTRING* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* VERSION::GetName()
{
  return &name;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSTRING* VERSION::GetVersion();
* @brief      GetVersion
* @ingroup    PLATFORM_COMMON
* 
* @param[in]  ) : 
* 
* @return     XSTRING* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* VERSION::GetVersion()
{
  version.Format(__L("%d.%d.%d"), VERSION_VERSION, VERSION_SUBVERSION, VERSION_SUBERROR);

  return &version;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void VERSION::GetVersion(XDWORD& version, XDWORD& subversion, XDWORD& suberor)
* @brief      GetVersion
* @ingroup    PLATFORM_COMMON
* 
* @param[in]  version : 
* @param[in]  subversion : 
* @param[in]  suberor : 
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void VERSION::GetVersion(XDWORD& version, XDWORD& subversion, XDWORD& suberror)
{
  version       = VERSION_VERSION;
  subversion    = VERSION_SUBVERSION;
  suberror      = VERSION_SUBERROR;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSTRING* VERSION::GetCodeName()
* @brief      GetCodeName
* @ingroup    PLATFORM_COMMON
* 
* @return     XSTRING* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* VERSION::GetCodeName()
{
  return &codename;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         VERSION::VERSION()
* @brief      Constructor
* @ingroup    PLATFORM_COMMON
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
VERSION::VERSION()
{
  Clean();

  name      = VERSION_NAME; 
  codename  = VERSION_CODENAME; 
  version.Format(__L("%d.%d.%d"), VERSION_VERSION, VERSION_SUBVERSION, VERSION_SUBERROR);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         VERSION::~VERSION()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    PLATFORM_COMMON
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
VERSION::~VERSION()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void VERSION::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    PLATFORM_COMMON
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void VERSION::Clean()
{

}
