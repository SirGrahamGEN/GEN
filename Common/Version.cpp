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

#include "XFactory.h"
#include "XDateTime.h"

#include "Version.h"

#include "XMemory_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

VERSION* VERSION::instance = NULL;

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool VERSION::GetIsInstanced()
* @brief      GetIsInstanced
* @ingroup    XUTILS
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
* @ingroup    XUTILS
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
* @ingroup    XUTILS
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
* @fn         XSTRING* VERSION::GetVersion()
* @brief      GetVersion
* @ingroup    PLATFORM_COMMON
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
* @fn         void VERSION::GetVersion(XDWORD& version, XDWORD& subversion, XDWORD& suberror)
* @brief      GetVersion
* @ingroup    PLATFORM_COMMON
* 
* @param[in]  version : 
* @param[in]  subversion : 
* @param[in]  suberror : 
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
* @fn         void VERSION::GetAppVersion(XDWORD& app_version, XDWORD& app_subversion, XDWORD& app_versionerror)
* @brief      GetAppVersion
* @ingroup    PLATFORM_COMMON
* 
* @param[in]  app_version : 
* @param[in]  app_subversion : 
* @param[in]  app_versionerror : 
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void VERSION::GetAppVersion(XDWORD& app_version, XDWORD& app_subversion, XDWORD& app_versionerror)
{
  app_version       = this->app_version;
  app_subversion    = this->app_subversion;
  app_versionerror  = this->app_versionerror;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSTRING* VERSION::GetAppOwner()
* @brief      GetAppOwner
* @ingroup    PLATFORM_COMMON
* 
* @return     XSTRING* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* VERSION::GetAppOwner()
{
  return &app_ower;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDWORD VERSION::GetAppCreationYear()
* @brief      GetAppCreationYear
* @ingroup    PLATFORM_COMMON
* 
* @return     XDWORD : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD VERSION::GetAppCreationYear()
{
  return app_creationyear;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSTRING* VERSION::GetAppTitle()
* @brief      GetAppTitle
* @ingroup    PLATFORM_COMMON
* 
* @return     XSTRING* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* VERSION::GetAppTitle()
{
  return &app_titlestr;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSTRING* VERSION::GetAppVersion()
* @brief      GetAppVersion
* @ingroup    PLATFORM_COMMON
* 
* @return     XSTRING* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* VERSION::GetAppVersion()
{
  return &app_versionstr;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool VERSION::GetAppVersionStatus(XDWORD app_version, XDWORD app_subversion, XDWORD app_versionerror, XSTRING& statusstr)
* @brief      GetAppVersionStatus
* @ingroup    PLATFORM_COMMON
* 
* @param[in]  app_version : 
* @param[in]  app_subversion : 
* @param[in]  app_versionerror : 
* @param[in]  statusstr : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool VERSION::GetAppVersionStatus(XDWORD app_version, XDWORD app_subversion, XDWORD app_versionerror, XSTRING& statusstr)
{
  statusstr.Empty();

  if((app_version < 1) && (app_subversion <  1)) statusstr += __L(" (Alpha)");
  if((app_version < 1) && (app_subversion >= 1)) statusstr += __L(" (Beta)");
      
  #ifdef _DEBUG
  statusstr += __L(" [Debug]");
  #endif

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool VERSION::GetAppVersion(XDWORD app_version, XDWORD app_subversion, XDWORD app_versionerror, XSTRING& versionstr)
* @brief      GetAppVersion
* @ingroup    PLATFORM_COMMON
* 
* @param[in]  app_version : 
* @param[in]  app_subversion : 
* @param[in]  app_versionerror : 
* @param[in]  versionstr : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool VERSION::GetAppVersion(XDWORD app_version, XDWORD app_subversion, XDWORD app_versionerror, XSTRING& versionstr)
{
  XSTRING statusstr;

  versionstr.Format(__L("%d.%d.%d"), app_version, app_subversion, app_versionerror);
 
  if((app_version < 1) && (app_subversion <  1)) statusstr += __L(" (Alpha)");
  if((app_version < 1) && (app_subversion >= 1)) statusstr += __L(" (Beta)");
      
  #ifdef _DEBUG
  statusstr += __L(" [Debug]");
  #endif

  versionstr += statusstr;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void VERSION::SetAppVersion(XCHAR* app_name, XDWORD app_version, XDWORD app_subversion, XDWORD app_versionerror,XCHAR* app_owner, XDWORD app_creationyear)
* @brief      SetAppVersion
* @ingroup    PLATFORM_COMMON
* 
* @param[in]  app_name : 
* @param[in]  app_version : 
* @param[in]  app_subversion : 
* @param[in]  app_versionerror : 
* @param[in]  app_owner : 
* @param[in]  app_creationyear : 
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool VERSION::SetAppVersion(XCHAR* app_name, XDWORD app_version, XDWORD app_subversion, XDWORD app_versionerror, XCHAR* app_owner, XDWORD app_creationyear)
{
  app_titlestr.Empty();
  app_versionstr.Empty();

  app_versionstr.Format(__L("%s %d.%d.%d"), app_name?app_name:__L(""), app_version, app_subversion, app_versionerror);
 
  XSTRING statusstr;

  GetAppVersionStatus(app_version, app_subversion, app_versionerror, statusstr);
  app_versionstr += statusstr;
 
  app_titlestr = app_versionstr;
  app_titlestr += __L(" Copyright (c) ");

  XSTRING string2; 

  XDATETIME* GEN_XFACTORY_CREATE(xdatetime, CreateDateTime())
  if(!xdatetime) return false;

  xdatetime->Read();
  string2.Format(((XDWORD)xdatetime->GetYear()>app_creationyear)?__L("%d-%d "):__L("%d "), app_creationyear, xdatetime->GetYear());

  GEN_XFACTORY.DeleteDateTime(xdatetime);

  app_titlestr += string2;
  if(app_owner) app_titlestr += app_owner;
  
  return true;
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
  name.Empty();   
  version.Empty();         
  codename.Empty(); 

  app_name.Empty();    
  app_version         = 0;
  app_subversion      = 0;
  app_versionerror    = 0;
  app_ower.Empty();
  app_creationyear    = 0;
  app_versionstr.Empty();
}
