/**-------------------------------------------------------------------------------------------------------------------
*
* @file       APPMain.cpp
*
* @class      APPMAIN
* @brief      Application Main Base class
* @ingroup    APPLICATION
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @copyright  Copyright(c) 2008 - 2016 GEN Group.
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
*---------------------------------------------------------------------------------------------------------------------*/

/*---- PRECOMPILATION CONTROL ----------------------------------------------------------------------------------------*/

#include "GEN_Defines.h"

#ifdef APP_ACTIVE

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "XFactory.h"
#include "XString.h"
#include "XDir.h"

#include "APPBase.h"
#include "APPMain.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

APPMAIN  GEN_appmain;

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         APPMAIN::APPMAIN()
* @brief      Constructor
* @ingroup
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
APPMAIN::APPMAIN()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         APPMAIN::~APPMAIN()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
APPMAIN::~APPMAIN()
{
  End();

  Clean();
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         APPBASE* APPMAIN::GetApplication()
* @brief      Get Application
* @ingroup
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     APPBASE* : Application Base instance
*
*---------------------------------------------------------------------------------------------------------------------*/
APPBASE* APPMAIN::GetApplication()
{
  return application;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool APPMAIN::Create()
* @brief      Create
* @ingroup    APPLICATION
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool APPMAIN::Create()
{
  application  = APPBASE::Create();
  if(!application) return false;

  return application->AppProc_PlatformIni();
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool APPMAIN::Ini(MAINPROC* mainproc, APPBASE_APPLICATIONMODE_TYPE applicationmode)
* @brief      Ini
* @ingroup    APPLICATION
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  mainproc :
* @param[in]  applicationmode :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool APPMAIN::Ini(MAINPROC* mainproc, APPBASE_APPLICATIONMODE_TYPE applicationmode)
{
  if(!mainproc) return false;
  if(!application) return false;

  this->mainproc = mainproc;

  application->SetApplicationMode(applicationmode);
  application->SetApplicationHandle(mainproc->GetHandle());

	#if!defined(MICROCONTROLLER) && !defined(ANDROID) 

    XPATH nameexecutable;

    nameexecutable = mainproc->GetXPathExec()->Get();
    nameexecutable.SetOnlyNamefileExt();
    if(!nameexecutable.IsEmpty()) application->SetApplicationExecutable(nameexecutable.Get());

    mainproc->GetXPathExec()->SetOnlyDriveAndPath();

    if(mainproc->GetXPathExec()->IsEmpty())
      {
        XDIR* GEN_XFACTORY_CREATE(xdir, Create_Dir())
        if(xdir)
          {
            XPATH xpathactual;
            if(xdir->GetActual(xpathactual))  mainproc->GetXPathExec()->Set(xpathactual);

            GEN_XFACTORY.Delete_Dir(xdir);
          }
      }

  
    GEN_XPATHSMANAGER.GetAppExecPath()->Set(mainproc->GetXPathExec()->Get());
    GEN_XPATHSMANAGER.AddPathSection(XPATHSMANAGERSECTIONTYPE_ROOT , (*mainproc->GetXPathExec()));
	
	  if(!application->Ini(mainproc->GetExecParams())) return false;
	
  #else

    if(!application->Ini(NULL)) return false;

  #endif

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool APPMAIN::Update()
* @brief      Update
* @ingroup
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool APPMAIN::Update()
{
  if(!application) return false;

  if(!application->UpdateStep())
    {
      application->SetExitType(APPBASE_EXITTYPE_BY_SERIOUSERROR);
    }

  if(application->GetExitType() != APPBASE_EXITTYPE_UNKNOWN) return false;

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool APPMAIN::End()
* @brief      End
* @ingroup
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool APPMAIN::End()
{
  if(!mainproc) return false;

  if(application)
    {
      application->End();
    }

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool APPMAIN::Delete()
* @brief      Delete
* @ingroup    APPLICATION
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool APPMAIN::Delete()
{
  if(!mainproc) return false;

  if(application)
    {
      application->AppProc_PlatformEnd();
      delete application;
      application = NULL;
    }

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void APPMAIN::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void APPMAIN::Clean()
{
  mainproc = NULL;
}


#endif



