/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIODNSProtocol_MitM_Server.cpp
* 
* @class      DIODNSPROTOCOL_MITM_SERVER
* @brief      DIODNSProtocol_MitM_Server
* @ingroup    DATAIO
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

/*---- PRECOMPILATION INCLUDES ----------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_INCLUDES

#include "GEN_Defines.h"

#pragma endregion


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "DIODNSProtocol_MitM_Server.h"

#include "XFactory.h"

#include "XMemory_Control.h"

#pragma endregion


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIODNSPROTOCOL_MITM_SERVER::DIODNSPROTOCOL_MITM_SERVER()
* @brief      Constructor
* @ingroup    DATAIO
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIODNSPROTOCOL_MITM_SERVER::DIODNSPROTOCOL_MITM_SERVER()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIODNSPROTOCOL_MITM_SERVER::~DIODNSPROTOCOL_MITM_SERVER()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    DATAIO
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIODNSPROTOCOL_MITM_SERVER::~DIODNSPROTOCOL_MITM_SERVER()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIODNSPROTOCOL_MITM_SERVER::Ini()
* @brief      Ini
* @ingroup    DATAIO
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIODNSPROTOCOL_MITM_SERVER::Ini()
{
  servermutex = GEN_XFACTORY.Create_Mutex();
  if(!servermutex)
    {
      return false;
    }
  
  serverthread = GEN_XFACTORY.CreateThread(XTHREADGROUPID_DIODNSRESOLVED, __L("DIODNSPROTOCOL_MITM_SERVER::Ini"), DIODNSPROTOCOL_MITM_SERVER::ThreadServer, this);  
  if(!serverthread)
    {
      return false;
    }

  return serverthread->Ini();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIODNSPROTOCOL_MITM_SERVER::End()
* @brief      End
* @ingroup    DATAIO
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIODNSPROTOCOL_MITM_SERVER::End()
{
  if(serverthread)
    {
      serverthread->End();

      GEN_XFACTORY.DeleteThread(XTHREADGROUPID_DIODNSRESOLVED, serverthread);
      serverthread = NULL;
    }
    
  if(servermutex)
    {
      GEN_XFACTORY.Delete_Mutex(servermutex);
      servermutex = NULL;
    }


  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIODNSPROTOCOL_MITM_SERVER::ThreadServer(void* param)
* @brief      ThreadServer
* @ingroup    DATAIO
* 
* @param[in]  param : 
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIODNSPROTOCOL_MITM_SERVER::ThreadServer(void* param)
{
  DIODNSPROTOCOL_MITM_SERVER* mitm_server = (DIODNSPROTOCOL_MITM_SERVER*)param;
  if(mitm_server)
    {
      return;
    }
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIODNSPROTOCOL_MITM_SERVER::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    DATAIO
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIODNSPROTOCOL_MITM_SERVER::Clean()
{
  serverthread  = NULL;
  servermutex   = NULL;    
}


#pragma endregion


