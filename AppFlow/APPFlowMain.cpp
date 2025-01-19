/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       APPFlowMain.cpp
* 
* @class      APPFLOWMAIN
* @brief      Application Flow Main Base class
* @ingroup    APPFLOW
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


#ifdef APPFLOW_ACTIVE

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "APPFlowMain.h"

#include "XFactory.h"
#include "XString.h"
#include "XDir.h"

#include "APPFlowBase.h"

#pragma endregion


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_CONTROL_INCLUDE

#include "GEN_Control.h"

#pragma endregion



/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

APPFLOWMAIN  GEN_appmain;

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         APPFLOWMAIN::APPFLOWMAIN()
* @brief      Constructor of class
* @ingroup    APPFLOW
* 
* --------------------------------------------------------------------------------------------------------------------*/
APPFLOWMAIN::APPFLOWMAIN()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         APPFLOWMAIN::~APPFLOWMAIN()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    APPFLOW
* 
* --------------------------------------------------------------------------------------------------------------------*/
APPFLOWMAIN::~APPFLOWMAIN()
{
  End();

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         APPFLOWBASE* APPFLOWMAIN::GetApplication()
* @brief      Get application
* @ingroup    APPFLOW
* 
* @return     APPFLOWBASE* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
APPFLOWBASE* APPFLOWMAIN::GetApplication()
{
  return application;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool APPFLOWMAIN::Create()
* @brief      Create
* @ingroup    APPFLOW
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool APPFLOWMAIN::Create()
{
  application  = APPFLOWBASE::Create();
  if(!application) return false;

  return application->AppProc_PlatformIni();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool APPFLOWMAIN::Ini(MAINPROC* mainproc, APPFLOWBASE_MODE_TYPE applicationmode)
* @brief      Ini
* @ingroup    APPFLOW
*
* @param[in]  mainproc :
* @param[in]  applicationmode :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool APPFLOWMAIN::Ini(MAINPROC* mainproc, APPFLOWBASE_MODE_TYPE applicationmode)
{
  if(!mainproc) 
    {
      return false;
    }

  if(!application) 
    {
      return false;
    }

  this->mainproc = mainproc;

  application->Application_SetMode(applicationmode);
  application->Application_SetHandle(mainproc->GetHandle());

	#if !defined(MICROCONTROLLER) && !defined(ANDROID) 

    XPATH nameexecutable;

    nameexecutable = mainproc->GetXPathExec()->Get();
    nameexecutable.SetOnlyNamefileExt();
    if(!nameexecutable.IsEmpty()) 
      {
        application->Application_SetExecutable(nameexecutable.Get());
      }

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
	
	  if(!application->Ini(mainproc->GetExecParams())) 
      {
        return false;
      }
	
  #else

    if(!application->Ini(NULL)) 
      {
        return false;
      }

  #endif

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool APPFLOWMAIN::Update()
* @brief      Update
* @ingroup    APPFLOW
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool APPFLOWMAIN::Update()
{
  if(!application) return false;

  if(!application->UpdateStep())
    {
      application->SetExitType(APPFLOWBASE_EXITTYPE_BY_SERIOUSERROR);
    }

  if(application->GetExitType() != APPFLOWBASE_EXITTYPE_UNKNOWN) return false;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool APPFLOWMAIN::End()
* @brief      End
* @ingroup    APPFLOW
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool APPFLOWMAIN::End()
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
* @fn         bool APPFLOWMAIN::Delete()
* @brief      Delete
* @ingroup    APPFLOW
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool APPFLOWMAIN::Delete()
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
* @fn         void APPFLOWMAIN::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    APPFLOW
* 
* --------------------------------------------------------------------------------------------------------------------*/
void APPFLOWMAIN::Clean()
{
  mainproc = NULL;
}


#pragma endregion


#endif

