/**-------------------------------------------------------------------------------------------------------------------
*
* @file       XProcessManager.cpp
*
* @class      XPROCESSMANAGER
* @brief      eXtended process manager class
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

/*---- PRECOMPILATION CONTROL ----------------------------------------------------------------------------------------*/

#include "GEN_Defines.h"

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/


#include "XProcessManager.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

XPROCESSMANAGER* XPROCESSMANAGER::instance = NULL;

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/



/*--------------------------------------------------------------------------------------------------------------------*/
/*  XPROCESS                                                                                                          */
/*--------------------------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XPROCESS::XPROCESS()
* @brief      Constructor
* @ingroup    XUTILS
*
* @return     Does not return anything. 
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
* @return     Does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
XPROCESS::~XPROCESS()
{

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
* @return     void : does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void XPROCESS::SetID(XDWORD ID)
{
  this->ID = ID;
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
  ID          = xprocess.GetID();
  path        = xprocess.GetPath()->Get();  
  name        = xprocess.GetName()->Get();  
  windowtitle = xprocess.GetWindowTitle()->Get(); 

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void XPROCESS::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    XUTILS
*
* @return     void : does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void XPROCESS::Clean()
{
  ID = 0xFFFFFFFF;
}




/*--------------------------------------------------------------------------------------------------------------------*/
/*  XPROCESSMANAGER                                                                                                   */
/*--------------------------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XPROCESSMANAGER::XPROCESSMANAGER()
* @brief      Constructor
* @ingroup    XUTILS
*
* @return     Does not return anything.
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
* @return     Does not return anything.
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
* @fn         bool XPROCESSMANAGER::SetInstance(XPROCESSMANAGER* instance)
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
* @fn         bool XPROCESSMANAGER::MakeCommand(XCHAR* command, XSTRING& out, int* returncode)
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
bool XPROCESSMANAGER::MakeCommand(XCHAR* command, XSTRING* out, int* returncode)
{
  return false;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XPROCESSMANAGER::ExecuteApplication(XCHAR* applicationpath, XCHAR* params, XSTRING* in, XSTRING* out, int* returncode)
* @brief      ExecuteApplication
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
bool XPROCESSMANAGER::ExecuteApplication(XCHAR* applicationpath, XCHAR* params, XSTRING* in, XSTRING* out, int* returncode)
{
  return false;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XPROCESSMANAGER::IsApplicationRunning(XCHAR* applicationname, XDWORD* ID)
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
bool XPROCESSMANAGER::IsApplicationRunning(XCHAR* applicationname, XDWORD* ID)
{
  return false;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XPROCESSMANAGER::GetApplicationRunningList(XVECTOR<XPROCESS*> applist)
* @brief      GetApplicationRunningList
* @ingroup    XUTILS
*
* @param[in]  applist : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool XPROCESSMANAGER::GetApplicationRunningList(XVECTOR<XPROCESS*>& applist)
{
  return false;
}





/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XPROCESSMANAGER::TerminateApplication(XDWORD processID, XDWORD exitcode)
* @brief      TerminateApplication
* @ingroup    XUTILS
*
* @param[in]  processID : 
* @param[in]  exitcode : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool XPROCESSMANAGER::TerminateApplication(XDWORD processID, XDWORD exitcode)
{
  return false;
}
    



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XPROCESSMANAGER::TerminateApplication(XPROCESS& process, XDWORD exitcode)
* @brief      TerminateApplication
* @ingroup    XUTILS
*
* @param[in]  process : 
* @param[in]  exitcode : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool XPROCESSMANAGER::TerminateApplication(XPROCESS& process, XDWORD exitcode)
{
  return TerminateApplication(process.GetID(), exitcode);
}




/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XPROCESSMANAGER::TerminateApplication(XCHAR* processname, XDWORD exitcode)
* @brief      TerminateApplication
* @ingroup    XUTILS
*
* @param[in]  processname : 
* @param[in]  exitcode : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool XPROCESSMANAGER::TerminateApplication(XCHAR* processname, XDWORD exitcode)
{
  XVECTOR<XPROCESS*> apprunning; 
  bool               status = false;           

  if(!GEN_XPROCESSMANAGER.GetApplicationRunningList(apprunning)) return false;

  for(XDWORD c=0; c<apprunning.GetSize(); c++)
    {
      XPROCESS* xprocess = apprunning.Get(c);
      if(xprocess)
        {
          if(!xprocess->GetName()->Compare(processname, true))
            {
              status = TerminateApplication((*xprocess), exitcode);
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
* @fn         bool XPROCESSMANAGER::TerminateApplication(XSTRING& processname, XDWORD exitcode)
* @brief      TerminateApplication
* @ingroup    XUTILS
*
* @param[in]  processname : 
* @param[in]  exitcode : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool XPROCESSMANAGER::TerminateApplication(XSTRING& processname, XDWORD exitcode)
{
  return TerminateApplication(processname.Get(), exitcode);
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XPROCESSMANAGER::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    XUTILS
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void XPROCESSMANAGER::Clean()
{

}


















