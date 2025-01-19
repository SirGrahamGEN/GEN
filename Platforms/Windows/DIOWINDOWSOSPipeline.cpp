/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIOWINDOWSOSPipeline.cpp
* 
* @class      DIOWINDOWSOSPIPELINE
* @brief      WINDOWS Data Input/Output Operative System Pipeline in/out class
* @ingroup    PLATFORM_WINDOWS
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

#include "DIOWINDOWSOSPipeline.h"

#include "XTrace.h"

#pragma endregion


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_CONTROL_INCLUDE

#include "GEN_Control.h"

#pragma endregion



/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOWINDOWSOSPIPELINE::DIOWINDOWSOSPIPELINE()
* @brief      Constructor of class
* @ingroup    PLATFORM_WINDOWS
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOWINDOWSOSPIPELINE::DIOWINDOWSOSPIPELINE() : DIOOSPIPELINE()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOWINDOWSOSPIPELINE::~DIOWINDOWSOSPIPELINE()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    PLATFORM_WINDOWS
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOWINDOWSOSPIPELINE::~DIOWINDOWSOSPIPELINE()
{  
  Close();

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOWINDOWSOSPIPELINE::Open()
* @brief      Open
* @ingroup    PLATFORM_WINDOWS
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWINDOWSOSPIPELINE::Open()
{
  bool status  = false;

  pipeSTDOUT  = GetStdHandle(STD_OUTPUT_HANDLE);
  pipeSTDIN   = GetStdHandle(STD_INPUT_HANDLE);

  return IsOpen();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOWINDOWSOSPIPELINE::IsOpen()
* @brief      Is open
* @ingroup    PLATFORM_WINDOWS
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWINDOWSOSPIPELINE::IsOpen()
{
  if((!pipeSTDIN) || (!pipeSTDOUT))
    {  
      return false;
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOWINDOWSOSPIPELINE::Read(XBUFFER& buffer)
* @brief      Read
* @ingroup    PLATFORM_WINDOWS
* 
* @param[in]  buffer : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWINDOWSOSPIPELINE::Read(XBUFFER& buffer)
{
  DWORD  nread    = 0;  
  BOOL   success  = FALSE;

  if(!IsOpen())
    {
      return false;
    }

  success = ReadFile(pipeSTDIN, buffer.Get(), buffer.GetSize(), &nread, NULL);
  if(success && (nread == buffer.GetSize()))
    {
      return true;         
    }

  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOWINDOWSOSPIPELINE::Write(XBUFFER& buffer)
* @brief      Write
* @ingroup    PLATFORM_WINDOWS
* 
* @param[in]  buffer : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWINDOWSOSPIPELINE::Write(XBUFFER& buffer)
{
  DWORD  nwrite = 0;
  BOOL   success = FALSE;

  if(!IsOpen())
    {           
      return false;
    }

  success = WriteFile(pipeSTDOUT, buffer.Get(), buffer.GetSize(), &nwrite, NULL);
  if(success && (nwrite == buffer.GetSize()))
    {
      return true;
    } 

  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOWINDOWSOSPIPELINE::Close()
* @brief      Close
* @ingroup    PLATFORM_WINDOWS
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWINDOWSOSPIPELINE::Close()
{ 
  pipeSTDIN  = NULL;
  pipeSTDOUT = NULL;
    
  return true;
}    


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOWINDOWSOSPIPELINE::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    PLATFORM_WINDOWS
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOWINDOWSOSPIPELINE::Clean()
{
  pipeSTDIN     = NULL;  
  pipeSTDOUT    = NULL;  
}


#pragma endregion


#pragma endregion


