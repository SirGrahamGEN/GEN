/**-------------------------------------------------------------------------------------------------------------------
*
* @file       XProcessManager.cpp
*
* @class      XPROCESSMANAGER
* @brief      eXtended process manager class
* @note       Can´t be construct Factory + singelton without depends of system. IT´S NOT A SINGLETON.
* @ingroup    UTILS
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

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/


#include "XProcessManager.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

XPROCESSMANAGER* XPROCESSMANAGER::instance = NULL;

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XPROCESSMANAGER::XPROCESSMANAGER()
* @brief      Constructor
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
XPROCESSMANAGER::XPROCESSMANAGER()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XPROCESSMANAGER::~XPROCESSMANAGER()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
XPROCESSMANAGER::~XPROCESSMANAGER()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XPROCESSMANAGER::GetIsInstanced()
* @brief      GetIsInstanced
* @note       STATIC
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XPROCESSMANAGER::GetIsInstanced()
{
  return instance!=NULL;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XPROCESSMANAGER& XPROCESSMANAGER::GetInstance()
* @brief      GetInstance
* @note       STATIC
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     XPROCESSMANAGER& :
*
*---------------------------------------------------------------------------------------------------------------------*/
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
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  _instance : new instance
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
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
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
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
* @ingroup    UTILS
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
*
* @param[in]  command : 
*
* @return     bool : true if is succesful. 
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XPROCESSMANAGER::MakeSystemCommand(XCHAR* command)
{
  return false;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XPROCESSMANAGER::MakeCommand(XCHAR* command, XSTRING& out, int* returncode)
* @brief      MakeCommand
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  command :
* @param[in]  out :
* @param[in]  returncode :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XPROCESSMANAGER::MakeCommand(XCHAR* command, XSTRING* out, int* returncode)
{
  return false;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XPROCESSMANAGER::ExecuteApplication(XCHAR* applicationpath, XCHAR* params, XSTRING* in, XSTRING* out, int* returncode)
* @brief      ExecuteApplication
* @ingroup    UTILS
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
*
* @param[in]  applicationpath : 
* @param[in]  params : 
* @param[in]  in : 
* @param[in]  out : 
* @param[in]  returncode : 
*
* @return     bool : true if is succesful. 
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XPROCESSMANAGER::ExecuteApplication(XCHAR* applicationpath, XCHAR* params, XSTRING* in, XSTRING* out, int* returncode)
{
  return false;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XPROCESSMANAGER::IsApplicationRunning(XCHAR* applicationname, XDWORD* ID)
* @brief      Check if Is Application Running
* @note       VIRTUAL
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  applicationname : name of application
* @param[out] ID : ID of this application of SO
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XPROCESSMANAGER::IsApplicationRunning(XCHAR* applicationname, XDWORD* ID)
{
  return false;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XPROCESSMANAGER::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void XPROCESSMANAGER::Clean()
{

}
















