/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       MainProc.cpp
* 
* @class      MAINPROC
* @brief      Main Procedure class
* @ingroup    MAIN_PROCEDURE
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

#include "MainProc.h"

#include "XString.h"

#pragma endregion


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_CONTROL_INCLUDE

#include "GEN_Control.h"

#pragma endregion



/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

MAIN_FUNCTION_TYPE  Main_Proc_PlatformIni   = MAIN_FUNCTION_PLATFORMINI;
MAIN_FUNCTION_TYPE  Main_Proc_Ini           = MAIN_FUNCTION_INI;
MAIN_FUNCTION_TYPE  Main_Proc_Update        = MAIN_FUNCTION_UPDATE;
MAIN_FUNCTION_TYPE  Main_Proc_End           = MAIN_FUNCTION_END;
MAIN_FUNCTION_TYPE  Main_Proc_PlatformEnd   = MAIN_FUNCTION_PLATFORMEND;

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         MAINPROC::MAINPROC()
* @brief      Constructor of class
* @ingroup    MAIN_PROCEDURE
* 
* --------------------------------------------------------------------------------------------------------------------*/
MAINPROC::MAINPROC()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         MAINPROC::~MAINPROC()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    MAIN_PROCEDURE
* 
* --------------------------------------------------------------------------------------------------------------------*/
MAINPROC::~MAINPROC()

{
  End();

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool MAINPROC::Ini(APPFLOWMAIN* appmain, APPFLOWBASE_MODE_TYPE applicationmode)
* @brief      Ini
* @ingroup    MAIN_PROCEDURE
* 
* @param[in]  appmain : 
* @param[in]  applicationmode : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool MAINPROC::Ini(APPFLOWMAIN* appmain, APPFLOWBASE_MODE_TYPE applicationmode)
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool MAINPROC::Update()
* @brief      Update
* @ingroup    MAIN_PROCEDURE
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool MAINPROC::Update()
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool MAINPROC::End()
* @brief      End
* @ingroup    MAIN_PROCEDURE
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool MAINPROC::End()
{
	#ifndef MICROCONTROLLER
  DeleteAllExecParams();
	#endif

  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void* MAINPROC::GetHandle()
* @brief      Get handle
* @ingroup    MAIN_PROCEDURE
* 
* @return     void* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void* MAINPROC::GetHandle()
{
  return handle;
}


#ifndef MICROCONTROLLER


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool MAINPROC::CreateParams(int nparams, char* params[])
* @brief      Create params
* @ingroup    MAIN_PROCEDURE
* 
* @param[in]  nparams : 
* @param[in]  params[] : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool MAINPROC::CreateParams(int nparams, char* params[])
{
  for(int c=1; c<nparams; c++)
    {
      XSTRING* param = new XSTRING();
      if(param)
        {
          (*param) = params[c];
          GetExecParams()->Add(param);
        }
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool MAINPROC::CreateParams(int nparams, XCHAR* params[])
* @brief      Create params
* @ingroup    MAIN_PROCEDURE
* 
* @param[in]  nparams : 
* @param[in]  params[] : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool MAINPROC::CreateParams(int nparams, XCHAR* params[])
{
  for(int c=1; c<nparams; c++)
    {
      XSTRING* param = new XSTRING();
      if(param)
        {
          (*param) = params[c];
          GetExecParams()->Add(param);
        }
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool MAINPROC::CreateParams(int nparams, XCHAR* params)
* @brief      Create params
* @ingroup    MAIN_PROCEDURE
* 
* @param[in]  nparams : 
* @param[in]  params : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool MAINPROC::CreateParams(int nparams, XCHAR* params)
{
  for(int c=1; c<nparams; c++)
    {
      XSTRING* param = new XSTRING();
      if(param)
        {
          (*param) = params[c];
          GetExecParams()->Add(param);
        }
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool MAINPROC::CreateParams(XCHAR* commandline)
* @brief      Create params
* @ingroup    MAIN_PROCEDURE
* 
* @param[in]  commandline : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool MAINPROC::CreateParams(XCHAR* commandline)
{
  XSTRING _commandline = commandline;

  if(_commandline.IsEmpty()) return false;

  int    start  = 0;
  XDWORD c      = 0;

  do{ if((_commandline.Get()[c] == __C(' ')) || (_commandline.GetSize() == c))
        {
          XSTRING* param = new XSTRING();
          if(param)
            {
              _commandline.Copy(start, c, (*param));

              GetExecParams()->Add(param);
              start = c+1;
            }
        }

      c++;

    } while(c <= _commandline.GetSize());

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void MAINPROC::SetHandle(void* handle)
* @brief      Set handle
* @ingroup    MAIN_PROCEDURE
* 
* @param[in]  handle : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void MAINPROC::SetHandle(void* handle)
{
  this->handle = handle;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XPATH* MAINPROC::GetXPathExec()
* @brief      Get X path exec
* @ingroup    MAIN_PROCEDURE
* 
* @return     XPATH* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XPATH* MAINPROC::GetXPathExec()
{
  return &xpathexec;
}


#endif


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool MAINPROC::Factorys_Ini()
* @brief      Factorys ini
* @ingroup    MAIN_PROCEDURE
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool MAINPROC::Factorys_Ini()
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool MAINPROC::Factorys_End()
* @brief      Factorys end
* @ingroup    MAIN_PROCEDURE
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool MAINPROC::Factorys_End()
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         APPFLOWMAIN* MAINPROC::GetAppMain()
* @brief      Get app main
* @ingroup    MAIN_PROCEDURE
* 
* @return     APPFLOWMAIN* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
APPFLOWMAIN* MAINPROC::GetAppMain()
{
  return appmain;
}


#ifndef MICROCONTROLLER


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XVECTOR<XSTRING*>* MAINPROC::GetExecParams()
* @brief      Get exec params
* @ingroup    MAIN_PROCEDURE
* 
* @return     XVECTOR<XSTRING*>* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XVECTOR<XSTRING*>* MAINPROC::GetExecParams()
{
  return &execparams;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool MAINPROC::DeleteAllExecParams()
* @brief      Delete all exec params
* @ingroup    MAIN_PROCEDURE
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool MAINPROC::DeleteAllExecParams()
{
  if(execparams.IsEmpty()) return false;

  execparams.DeleteContents();

  execparams.DeleteAll();

  return true;
}


#endif


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void MAINPROC::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    MAIN_PROCEDURE
* 
* --------------------------------------------------------------------------------------------------------------------*/
void MAINPROC::Clean()
{  
  handle            = NULL;  
  appmain           = NULL;    
}


#pragma endregion

