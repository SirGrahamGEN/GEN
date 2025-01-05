/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       XProcessManager.cpp
* 
* @class      XPROCESSMANAGER
* @brief      eXtended Utils process manager class
* @note       Can´t be construct Factory + singelton without depends of system. IT´S NOT A SINGLETON.
* @ingroup    XUTILS
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

#include "XProcessManager.h"

#pragma endregion


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_CONTROL_INCLUDE

#include "GEN_Control.h"

#pragma endregion



/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

XPROCESSMANAGER* XPROCESSMANAGER::instance = NULL;

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


#pragma region CLASS_XPROCESS
/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XPROCESS::XPROCESS()
* @brief      Constructor
* @ingroup    XUTILS
*
* ---------------------------------------------------------------------------------------------------------------------*/
XPROCESS::XPROCESS()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XPROCESS::~XPROCESS()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    XUTILS
*
* ---------------------------------------------------------------------------------------------------------------------*/
XPROCESS::~XPROCESS()
{
  processIDs.DeleteAll();

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDWORD XPROCESS::GetID()
* @brief      GetID
* @ingroup    XUTILS
*
* @return     XDWORD : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
XDWORD XPROCESS::GetID()
{
  return ID;
}
 

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void XPROCESS::SetID(XDWORD ID)
* @brief      SetID
* @ingroup    XUTILS
*
* @param[in]  ID : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void XPROCESS::SetID(XDWORD ID)
{
  this->ID = ID;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XVECTOR<XDWORD>* XPROCESS::GetProcessIDs()
* @brief      GetProcessIDs
* @ingroup    XUTILS
* 
* @return     XVECTOR<XDWORD>* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XVECTOR<XDWORD>* XPROCESS::GetProcessIDs()
{
  return &processIDs;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XPATH* XPROCESS::GetPath()
* @brief      GetPath
* @ingroup    XUTILS
*
* @return     XPATH* : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
XPATH* XPROCESS::GetPath()
{
  return &path;
}  
    

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSTRING* XPROCESS::GetName()
* @brief      GetName
* @ingroup    XUTILS
*
* @return     XSTRING* : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
XSTRING* XPROCESS::GetName()
{
  return &name;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void* XPROCESS::GetWindowHandle()
* @brief      GetWindowHandle
* @ingroup    XUTILS
* 
* @return     void* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void* XPROCESS::GetWindowHandle()
{
  return windowhandle;

}
 
  
/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void XPROCESS::SetWindowHandle(void* windowhandle)
* @brief      SetWindowHandle
* @ingroup    XUTILS
* 
* @param[in]  windowhandle : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void XPROCESS::SetWindowHandle(void* windowhandle)
{
  this->windowhandle = windowhandle;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSTRING* XPROCESS::GetWindowTitle()
* @brief      GetWindowTitle
* @ingroup    XUTILS
*
* @return     XSTRING* : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
XSTRING* XPROCESS::GetWindowTitle()
{
  return &windowtitle;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         GRPRECTINT* XPROCESS::GetWindowRect()
* @brief      GetWindowRect
* @ingroup    XUTILS
* 
* @return     GRPRECTINT* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
GRPRECTINT* XPROCESS::GetWindowRect()
{
  return &windowrect;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         int XPROCESS::GetWindowTitleHeight()
* @brief      GetWindowTitleHeight
* @ingroup    XUTILS
* 
* @return     int : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
int XPROCESS::GetWindowTitleHeight()
{
  return windowtitleheight;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void XPROCESS::SetWindowTitleHeight(int windowtitleheight)
* @brief      SetWindowTitleHeight
* @ingroup    XUTILS
* 
* @param[in]  windowtitleheight : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void XPROCESS::SetWindowTitleHeight(int windowtitleheight)
{
  this->windowtitleheight = windowtitleheight;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         int XPROCESS::GetWindowBorderWidth()
* @brief      GetWindowBorderWidth
* @ingroup    XUTILS
* 
* @return     int : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
int XPROCESS::GetWindowBorderWidth()
{
  return windowborderwidth;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void XPROCESS::SetWindowBorderWidth(int windowborderwidth)
* @brief      SetWindowBorderWidth
* @ingroup    XUTILS
* 
* @param[in]  windowborderwidth : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void XPROCESS::SetWindowBorderWidth(int windowborderwidth)
{
  this->windowborderwidth = windowborderwidth;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XPROCESS::CopyTo(XPROCESS& xprocess)
* @brief      CopyTo
* @ingroup    XUTILS
*
* @param[in]  xprocess : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool XPROCESS::CopyTo(XPROCESS& xprocess)
{
  xprocess.SetID(ID);
  xprocess.GetPath()->Set(path);  
  xprocess.GetName()->Set(name);    
  xprocess.GetWindowTitle()->Set(windowtitle); 

  xprocess.GetWindowRect()->CopyFrom(&windowrect);

  xprocess.SetWindowTitleHeight(windowtitleheight);
  xprocess.SetWindowBorderWidth(windowborderwidth);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XPROCESS::CopyFrom(XPROCESS& xprocess)
* @brief      CopyFrom
* @ingroup    XUTILS
*
* @param[in]  xprocess : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool XPROCESS::CopyFrom(XPROCESS& xprocess)
{
  ID                = xprocess.GetID();
  path              = xprocess.GetPath()->Get();  
  name              = xprocess.GetName()->Get();  
  windowtitle       = xprocess.GetWindowTitle()->Get(); 

  GetWindowRect()->CopyFrom(xprocess.GetWindowRect());

  windowtitleheight = xprocess.GetWindowTitleHeight();
  windowborderwidth = xprocess.GetWindowBorderWidth();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XPROCESS::Compare(XPROCESS& xprocess, bool onlyfixed)
* @brief      Compare
* @ingroup    XUTILS
* 
* @param[in]  xprocess : 
* @param[in]  onlyfixed : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XPROCESS::Compare(XPROCESS& xprocess, bool onlyfixed)
{
  if(ID != xprocess.GetID())
    {
      return false;
    }

  if(path.Compare(xprocess.GetPath()->Get(), true))
    {
      return false;   
    }

  if(name.Compare(xprocess.GetName()->Get(), true))
    {
      return false;   
    }

  if(windowtitle.Compare(xprocess.GetWindowTitle()->Get(), false))
    {
      return false;   
    }


  if(!onlyfixed)
    {
      if(!GetWindowRect()->IsEqual(xprocess.GetWindowRect()))
        {
          return false;    
        }

      if(windowtitleheight != xprocess.GetWindowTitleHeight())
        {
          return false;
        }

      if(windowborderwidth != xprocess.GetWindowBorderWidth())
        {
          return false;
        }
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void XPROCESS::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    XUTILS
*
* ---------------------------------------------------------------------------------------------------------------------*/
void XPROCESS::Clean()
{
  ID                  = 0xFFFFFFFF;
  windowhandle        = NULL;
  windowtitleheight   = 0;    
  windowborderwidth   = 0;    
}

#pragma endregion


#pragma region CLASS_XPROCESSMANAGER

/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XPROCESSMANAGER::XPROCESSMANAGER()
* @brief      Constructor
* @ingroup    XUTILS
*
* --------------------------------------------------------------------------------------------------------------------*/
XPROCESSMANAGER::XPROCESSMANAGER()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XPROCESSMANAGER::~XPROCESSMANAGER()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    XUTILS
*
* --------------------------------------------------------------------------------------------------------------------*/
XPROCESSMANAGER::~XPROCESSMANAGER()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XPROCESSMANAGER::GetIsInstanced()
* @brief      GetIsInstanced
* @note       STATIC
* @ingroup    XUTILS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XPROCESSMANAGER::GetIsInstanced()
{
  return instance!=NULL;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XPROCESSMANAGER& XPROCESSMANAGER::GetInstance()
* @brief      GetInstance
* @note       STATIC
* @ingroup    XUTILS
*
* @return     XPROCESSMANAGER& :
*
* --------------------------------------------------------------------------------------------------------------------*/
XPROCESSMANAGER& XPROCESSMANAGER::GetInstance()
{
  if(!instance) instance = new XPROCESSMANAGER();

  return (*instance);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XPROCESSMANAGER::SetInstance(XPROCESSMANAGER* _instance)
* @brief      SetInstance
* @note       STATIC
* @ingroup    XUTILS
*
* @param[in]  _instance : new instance
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XPROCESSMANAGER::SetInstance(XPROCESSMANAGER* _instance)
{
  if(!_instance) return false;

  instance = _instance;

  return (instance)?true:false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XPROCESSMANAGER::DelInstance()
* @brief      DelInstance
* @note       STATIC
* @ingroup    XUTILS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XPROCESSMANAGER::DelInstance()
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
* @fn         bool XPROCESSMANAGER::MakeSystemCommand(XCHAR* command)
* @brief      MakeSystemCommand
* @ingroup    XUTILS
*
* @param[in]  command : 
*
* @return     bool : true if is succesful. 
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XPROCESSMANAGER::MakeSystemCommand(XCHAR* command)
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XPROCESSMANAGER::MakeCommand(XCHAR* command, XBUFFER* out, int* returncode)
* @brief      MakeCommand
* @ingroup    XUTILS
* 
* @param[in]  command : 
* @param[in]  out : 
* @param[in]  returncode : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XPROCESSMANAGER::MakeCommand(XCHAR* command, XBUFFER* out, int* returncode)
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XPROCESSMANAGER::OpenURL(XCHAR* url)
* @brief      OpenURL
* @ingroup    XUTILS
* 
* @param[in]  url : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XPROCESSMANAGER::OpenURL(XCHAR* url)
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XPROCESSMANAGER::Application_Execute(XCHAR* applicationpath, XCHAR* params, XBUFFER* in, XBUFFER* out, int* returncode)
* @brief      Application_Execute
* @ingroup    XUTILS
* 
* @param[in]  applicationpath : 
* @param[in]  params : 
* @param[in]  in : 
* @param[in]  out : 
* @param[in]  returncode : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XPROCESSMANAGER::Application_Execute(XCHAR* applicationpath, XCHAR* params, XBUFFER* in, XBUFFER* out, int* returncode)
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XPROCESSMANAGER::Application_IsRunning(XCHAR* applicationname, XDWORD* ID)
* @brief      Check if Is Application Running
* @note       VIRTUAL
* @ingroup    XUTILS
*
* @param[in]  applicationname : name of application
* @param[out] ID : ID of this application of SO
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XPROCESSMANAGER::Application_IsRunning(XCHAR* applicationname, XDWORD* ID)
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XPROCESSMANAGER::Application_GetRunningList(XVECTOR<XPROCESS*>& applist, bool onlywithvalidwindow)
* @brief      Application_GetRunningList
* @ingroup    XUTILS
* 
* @param[in]  applist : 
* @param[in]  onlywithvalidwindow : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XPROCESSMANAGER::Application_GetRunningList(XVECTOR<XPROCESS*>& applist, bool onlywithvalidwindow)
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XPROCESSMANAGER::Application_Terminate(XDWORD processID, XDWORD exitcode)
* @brief      Application_Terminate
* @ingroup    XUTILS
*
* @param[in]  processID : 
* @param[in]  exitcode : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool XPROCESSMANAGER::Application_Terminate(XDWORD processID, XDWORD exitcode)
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XPROCESSMANAGER::Application_Terminate(XPROCESS& process, XDWORD exitcode)
* @brief      Application_Terminate
* @ingroup    XUTILS
*
* @param[in]  process : 
* @param[in]  exitcode : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool XPROCESSMANAGER::Application_Terminate(XPROCESS& process, XDWORD exitcode)
{
  return Application_Terminate(process.GetID(), exitcode);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XPROCESSMANAGER::Application_Terminate(XCHAR* processname, XDWORD exitcode)
* @brief      Application_Terminate
* @ingroup    XUTILS
*
* @param[in]  processname : 
* @param[in]  exitcode : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool XPROCESSMANAGER::Application_Terminate(XCHAR* processname, XDWORD exitcode)
{
  XVECTOR<XPROCESS*> apprunning; 
  bool               status = false;           

  if(!GEN_XPROCESSMANAGER.Application_GetRunningList(apprunning)) return false;

  for(XDWORD c=0; c<apprunning.GetSize(); c++)
    {
      XPROCESS* xprocess = apprunning.Get(c);
      if(xprocess)
        {
          if(!xprocess->GetName()->Compare(processname, true))
            {
              status = Application_Terminate((*xprocess), exitcode);
              break;
            }
        }
    }

  apprunning.DeleteContents();
  apprunning.DeleteAll();

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XPROCESSMANAGER::Application_Terminate(XSTRING& processname, XDWORD exitcode)
* @brief      Application_Terminate
* @ingroup    XUTILS
*
* @param[in]  processname : 
* @param[in]  exitcode : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool XPROCESSMANAGER::Application_Terminate(XSTRING& processname, XDWORD exitcode)
{
  return Application_Terminate(processname.Get(), exitcode);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XPROCESS* XPROCESSMANAGER::Application_GetProcessByID(XDWORD processID, XVECTOR<XPROCESS*>& applist)
* @brief      Application_GetProcessByID
* @ingroup    XUTILS
* 
* @param[in]  processID : 
* @param[in]  applist : 
* 
* @return     XPROCESS* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XPROCESS* XPROCESSMANAGER::Application_GetProcessByID(XDWORD processID, XVECTOR<XPROCESS*>& applist)
{
  for(XDWORD c=0; c<applist.GetSize(); c++)
    {
      XPROCESS* process =  applist.Get(c);
      if(process)
        {
          if(process->GetID() == processID)
            {
              return process;
            }
        }
    }

  return NULL;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XPROCESSMANAGER::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    XUTILS
*
* --------------------------------------------------------------------------------------------------------------------*/
void XPROCESSMANAGER::Clean()
{

}


#pragma endregion


#pragma endregion

