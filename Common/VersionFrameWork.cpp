/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       VersionFrameWork.cpp
* 
* @class      VERSIONFRAMEWORK
* @brief      Version of framework
* @ingroup    COMMON
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

#include "VersionFrameWork.h"

#include "XFactory.h"
#include "XDateTime.h"

#pragma endregion


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_CONTROL_INCLUDE

#include "GEN_Control.h"

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
* @brief      Get is instanced
* @ingroup    COMMON
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
* @brief      Get instance
* @ingroup    COMMON
* 
* @return     VERSIONFRAMEWORK& : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
VERSIONFRAMEWORK& VERSIONFRAMEWORK::GetInstance()
{
  if(!instance) 
    {
      instance = new VERSIONFRAMEWORK();
    }

  return (*instance);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool VERSIONFRAMEWORK::DelInstance()
* @brief      Del instance
* @ingroup    COMMON
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
* @brief      Get name
* @ingroup    COMMON
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
* @brief      Get version
* @ingroup    COMMON
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
* @brief      Get version
* @ingroup    COMMON
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
* @brief      Get code name
* @ingroup    COMMON
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
* @brief      Get app name
* @ingroup    COMMON
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
* @fn         XSTRING* VERSIONFRAMEWORK::GetAppExecName()
* @brief      Get app exec name
* @ingroup    COMMON
* 
* @return     XSTRING* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* VERSIONFRAMEWORK::GetAppExecName()
{
  return &app_execname;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void VERSIONFRAMEWORK::GetAppVersions(XDWORD& app_version, XDWORD& app_subversion, XDWORD& app_versionerror)
* @brief      Get app versions
* @ingroup    COMMON
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
* @brief      Get app owner
* @ingroup    COMMON
* 
* @return     XSTRING* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* VERSIONFRAMEWORK::GetAppOwner()
{
  return &app_owner;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDWORD VERSIONFRAMEWORK::GetAppCreationYear()
* @brief      Get app creation year
* @ingroup    COMMON
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
* @brief      Get app title
* @ingroup    COMMON
* 
* @return     XSTRING* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* VERSIONFRAMEWORK::GetAppTitle()
{
  static int revised = 0;

  if(revised > 100)
    {
      UpdateYearAppVersion();

      revised = 0;
    }

  revised++;

  return &app_titlestr;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSTRING* VERSIONFRAMEWORK::GetAppVersion()
* @brief      Get app version
* @ingroup    COMMON
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
* @brief      Get app version status
* @ingroup    COMMON
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
* @brief      Get app version
* @ingroup    COMMON
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
* @fn         bool VERSIONFRAMEWORK::SetAppVersion(XCHAR* app_name, XCHAR* app_execname, XDWORD app_version, XDWORD app_subversion, XDWORD app_versionerror, XCHAR* app_owner, XDWORD app_creationyear)
* @brief      Set app version
* @ingroup    COMMON
* 
* @param[in]  app_name : 
* @param[in]  app_execname : 
* @param[in]  app_version : 
* @param[in]  app_subversion : 
* @param[in]  app_versionerror : 
* @param[in]  app_owner : 
* @param[in]  app_creationyear : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool VERSIONFRAMEWORK::SetAppVersion(XCHAR* app_name, XCHAR* app_execname, XDWORD app_version, XDWORD app_subversion, XDWORD app_versionerror, XCHAR* app_owner, XDWORD app_creationyear)
{
  app_titlestr.Empty();
  app_versionstr.Empty();

  this->app_name          = app_name;
  this->app_execname      = app_execname;
  this->app_version       = app_version;
  this->app_subversion    = app_subversion;
  this->app_versionerror  = app_versionerror;
  this->app_owner         = app_owner;
  this->app_creationyear  = app_creationyear;

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
* @fn         bool VERSIONFRAMEWORK::UpdateYearAppVersion()
* @brief      Update year app version
* @ingroup    COMMON
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool VERSIONFRAMEWORK::UpdateYearAppVersion()
{
  app_titlestr.Empty();
  app_versionstr.Empty();

  app_versionstr.Format(__L("%s %d.%d.%d"), !app_name.IsEmpty()?app_name.Get():__L(""), app_version, app_subversion, app_versionerror);
 
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
  if(!app_owner.IsEmpty()) app_titlestr += app_owner;
  
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         VERSIONFRAMEWORK::VERSIONFRAMEWORK()
* @brief      Constructor of class
* @ingroup    COMMON
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
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    COMMON
* 
* --------------------------------------------------------------------------------------------------------------------*/
VERSIONFRAMEWORK::~VERSIONFRAMEWORK()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void VERSIONFRAMEWORK::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    COMMON
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
  app_owner.Empty();
  app_creationyear    = 0;
  app_versionstr.Empty();
}


#pragma endregion
