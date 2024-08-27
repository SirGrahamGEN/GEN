/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       VersionFrameWork.cpp
* 
* @class      VERSIONFRAMEWORKFRAMEWORK
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

/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_INCLUDES

#include "GEN_Defines.h"

#pragma endregion


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "VersionFrameWork.h"

#include "XFactory.h"
#include "XDateTime.h"

#include "XMemory_Control.h"

#pragma endregion


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

VERSIONFRAMEWORK* VERSIONFRAMEWORK::instance = NULL;

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool VERSIONFRAMEWORK::GetIsInstanced()
* @brief      GetIsInstanced
* @ingroup    PLATFORM_COMMON
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool VERSIONFRAMEWORK::GetIsInstanced()
{
  return instance!=NULL;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         VERSIONFRAMEWORK& VERSIONFRAMEWORK::GetInstance()
* @brief      GetInstance
* @ingroup    PLATFORM_COMMON
* 
* @return     VERSIONFRAMEWORK& : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
VERSIONFRAMEWORK& VERSIONFRAMEWORK::GetInstance()
{
  if(!instance) instance = new VERSIONFRAMEWORK();

  return (*instance);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool VERSIONFRAMEWORK::DelInstance()
* @brief      DelInstance
* @ingroup    PLATFORM_COMMON
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool VERSIONFRAMEWORK::DelInstance()
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
* @fn         XSTRING* VERSIONFRAMEWORK::GetName()
* @brief      GetName
* @ingroup    PLATFORM_COMMON
* 
* @return     XSTRING* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* VERSIONFRAMEWORK::GetName()
{
  return &name;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSTRING* VERSIONFRAMEWORK::GetVersion()
* @brief      GetVersion
* @ingroup    PLATFORM_COMMON
* 
* @return     XSTRING* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* VERSIONFRAMEWORK::GetVersion()
{
  version.Format(__L("%d.%d.%d"), VERSIONFRAMEWORK_VERSION, VERSIONFRAMEWORK_SUBVERSION, VERSIONFRAMEWORK_SUBERROR);

  return &version;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void VERSIONFRAMEWORK::GetVersion(XDWORD& version, XDWORD& subversion, XDWORD& suberror)
* @brief      GetVersion
* @ingroup    PLATFORM_COMMON
* 
* @param[in]  version : 
* @param[in]  subversion : 
* @param[in]  suberror : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void VERSIONFRAMEWORK::GetVersion(XDWORD& version, XDWORD& subversion, XDWORD& suberror)
{
  version       = VERSIONFRAMEWORK_VERSION;
  subversion    = VERSIONFRAMEWORK_SUBVERSION;
  suberror      = VERSIONFRAMEWORK_SUBERROR;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSTRING* VERSIONFRAMEWORK::GetCodeName()
* @brief      GetCodeName
* @ingroup    PLATFORM_COMMON
* 
* @return     XSTRING* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* VERSIONFRAMEWORK::GetCodeName()
{
  return &codename;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSTRING* VERSIONFRAMEWORK::GetAppName()
* @brief      GetAppName
* @ingroup    PLATFORM_COMMON
* 
* @return     XSTRING* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* VERSIONFRAMEWORK::GetAppName()
{
  return &app_name;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void VERSIONFRAMEWORK::GetAppVersion(XDWORD& app_version, XDWORD& app_subversion, XDWORD& app_versionerror)
* @brief      GetAppVersion
* @ingroup    PLATFORM_COMMON
* 
* @param[in]  app_version : 
* @param[in]  app_subversion : 
* @param[in]  app_versionerror : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void VERSIONFRAMEWORK::GetAppVersions(XDWORD& app_version, XDWORD& app_subversion, XDWORD& app_versionerror)
{
  app_version       = this->app_version;
  app_subversion    = this->app_subversion;
  app_versionerror  = this->app_versionerror;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSTRING* VERSIONFRAMEWORK::GetAppOwner()
* @brief      GetAppOwner
* @ingroup    PLATFORM_COMMON
* 
* @return     XSTRING* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* VERSIONFRAMEWORK::GetAppOwner()
{
  return &app_ower;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDWORD VERSIONFRAMEWORK::GetAppCreationYear()
* @brief      GetAppCreationYear
* @ingroup    PLATFORM_COMMON
* 
* @return     XDWORD : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD VERSIONFRAMEWORK::GetAppCreationYear()
{
  return app_creationyear;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSTRING* VERSIONFRAMEWORK::GetAppTitle()
* @brief      GetAppTitle
* @ingroup    PLATFORM_COMMON
* 
* @return     XSTRING* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* VERSIONFRAMEWORK::GetAppTitle()
{
  return &app_titlestr;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSTRING* VERSIONFRAMEWORK::GetAppVersion()
* @brief      GetAppVersion
* @ingroup    PLATFORM_COMMON
* 
* @return     XSTRING* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* VERSIONFRAMEWORK::GetAppVersion()
{
  return &app_versionstr;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool VERSIONFRAMEWORK::GetAppVersionStatus(XDWORD app_version, XDWORD app_subversion, XDWORD app_versionerror, XSTRING& statusstr)
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
bool VERSIONFRAMEWORK::GetAppVersionStatus(XDWORD app_version, XDWORD app_subversion, XDWORD app_versionerror, XSTRING& statusstr)
{
  statusstr.Empty();

  if((app_version < 1) && (app_subversion <  1)) statusstr += __L(" (Alpha)");
  if((app_version < 1) && (app_subversion >= 1)) statusstr += __L(" (Beta)");
      
  #ifdef GEN_DEBUG
  statusstr += __L(" [Debug]");
  #endif

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool VERSIONFRAMEWORK::GetAppVersion(XDWORD app_version, XDWORD app_subversion, XDWORD app_versionerror, XSTRING& versionstr)
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
bool VERSIONFRAMEWORK::GetAppVersion(XDWORD app_version, XDWORD app_subversion, XDWORD app_versionerror, XSTRING& versionstr)
{
  XSTRING statusstr;

  versionstr.Format(__L("%d.%d.%d"), app_version, app_subversion, app_versionerror);
 
  if((app_version < 1) && (app_subversion <  1)) statusstr += __L(" (Alpha)");
  if((app_version < 1) && (app_subversion >= 1)) statusstr += __L(" (Beta)");
      
  #ifdef GEN_DEBUG
  statusstr += __L(" [Debug]");
  #endif

  versionstr += statusstr;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void VERSIONFRAMEWORK::SetAppVersion(XCHAR* app_name, XDWORD app_version, XDWORD app_subversion, XDWORD app_versionerror,XCHAR* app_owner, XDWORD app_creationyear)
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
* --------------------------------------------------------------------------------------------------------------------*/
bool VERSIONFRAMEWORK::SetAppVersion(XCHAR* app_name, XDWORD app_version, XDWORD app_subversion, XDWORD app_versionerror, XCHAR* app_owner, XDWORD app_creationyear)
{
  app_titlestr.Empty();
  app_versionstr.Empty();

  this->app_name          = app_name;
  this->app_version       = app_version;
  this->app_subversion    = app_subversion;
  this->app_versionerror  = app_versionerror;

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
* @fn         VERSIONFRAMEWORK::VERSIONFRAMEWORK()
* @brief      Constructor
* @ingroup    PLATFORM_COMMON
* 
* --------------------------------------------------------------------------------------------------------------------*/
VERSIONFRAMEWORK::VERSIONFRAMEWORK()
{
  Clean();

  #ifdef ANONYMOUS_MODE


  #else

  name      = VERSIONFRAMEWORK_NAME; 
  codename  = VERSIONFRAMEWORK_CODENAME; 
  version.Format(__L("%d.%d.%d"), VERSIONFRAMEWORK_VERSION, VERSIONFRAMEWORK_SUBVERSION, VERSIONFRAMEWORK_SUBERROR);

  #endif
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         VERSIONFRAMEWORK::~VERSIONFRAMEWORK()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    PLATFORM_COMMON
* 
* --------------------------------------------------------------------------------------------------------------------*/
VERSIONFRAMEWORK::~VERSIONFRAMEWORK()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void VERSIONFRAMEWORK::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    PLATFORM_COMMON
* 
* --------------------------------------------------------------------------------------------------------------------*/
void VERSIONFRAMEWORK::Clean()
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


#pragma endregion