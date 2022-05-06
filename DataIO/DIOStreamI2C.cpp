/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIOStreamI2C.cpp
* 
* @class      DIOSTREAMI2C
* @brief      Data Input/Output Stream I2C class
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
* ---------------------------------------------------------------------------------------------------------------------*/

/*---- PRECOMPILATION CONTROL ----------------------------------------------------------------------------------------*/

#include "GEN_Defines.h"


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "XFactory.h"
#include "XBuffer.h"
#include "XThreadCollected.h"

#include "DIOFactory.h"
#include "DIOGPIO.h"
#include "DIOStreamXEvent.h"

#include "DIOStreamI2CConfig.h"

#include "DIOStreamI2C.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOSTREAMI2C::DIOSTREAMI2C()
* @brief      DIOSTREAMI2C
* @ingroup    DATAIO
*
* @return     does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
DIOSTREAMI2C::DIOSTREAMI2C() : DIOSTREAM() , XFSMACHINE(0)
{
  Clean();

  AddState( DIOSTREAMI2C_FSMSTATE_NONE              ,
            DIOSTREAMI2C_FSMEVENT_CONNECTED       , DIOSTREAMI2C_FSMSTATE_CONNECTED        ,
            DIOSTREAMI2C_FSMEVENT_DISCONNECTING   , DIOSTREAMI2C_FSMSTATE_DISCONNECTING    ,
            XFSMACHINESTATE_EVENTDEFEND);


  AddState( DIOSTREAMI2C_FSMSTATE_CONNECTED       ,
            DIOSTREAMI2C_FSMEVENT_WAITINGTOREAD   , DIOSTREAMI2C_FSMSTATE_WAITINGTOREAD    ,
            DIOSTREAMI2C_FSMEVENT_SENDINGDATA     , DIOSTREAMI2C_FSMSTATE_SENDINGDATA      ,
            DIOSTREAMI2C_FSMEVENT_DISCONNECTING   , DIOSTREAMI2C_FSMSTATE_DISCONNECTING    ,
            XFSMACHINESTATE_EVENTDEFEND);

  AddState( DIOSTREAMI2C_FSMSTATE_WAITINGTOREAD   ,
            DIOSTREAMI2C_FSMEVENT_CONNECTED       , DIOSTREAMI2C_FSMSTATE_CONNECTED        ,
            DIOSTREAMI2C_FSMEVENT_SENDINGDATA     , DIOSTREAMI2C_FSMSTATE_SENDINGDATA      ,
            DIOSTREAMI2C_FSMEVENT_DISCONNECTING   , DIOSTREAMI2C_FSMSTATE_DISCONNECTING    ,
            XFSMACHINESTATE_EVENTDEFEND);

  AddState( DIOSTREAMI2C_FSMSTATE_DISCONNECTING   ,
            DIOSTREAMI2C_FSMEVENT_CONNECTED       , DIOSTREAMI2C_FSMSTATE_CONNECTED        ,
            DIOSTREAMI2C_FSMEVENT_WAITINGTOREAD   , DIOSTREAMI2C_FSMSTATE_WAITINGTOREAD    ,
            DIOSTREAMI2C_FSMEVENT_SENDINGDATA     , DIOSTREAMI2C_FSMSTATE_SENDINGDATA      ,
            XFSMACHINESTATE_EVENTDEFEND);
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOSTREAMI2C::~DIOSTREAMI2C()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    DATAIO
*
* @return     Does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
DIOSTREAMI2C::~DIOSTREAMI2C()
{
  Close();

  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOSTREAMCONFIG* DIOSTREAMI2C::GetConfig()
* @brief      GetConfig
* @ingroup    DATAIO
*
* @return     DIOSTREAMCONFIG* : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
DIOSTREAMCONFIG* DIOSTREAMI2C::GetConfig()
{
  return (DIOSTREAMCONFIG*)config;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOSTREAMI2C::SetConfig(DIOSTREAMCONFIG* config)
* @brief      SetConfig
* @ingroup    DATAIO
*
* @param[in]  config : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool DIOSTREAMI2C::SetConfig(DIOSTREAMCONFIG* config)
{
  if(!config) return false;
  this->config = (DIOSTREAMI2CCONFIG*)config;

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOSTREAMI2C::Open()
* @brief      Open
* @ingroup    DATAIO
*
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool DIOSTREAMI2C::Open()
{
  if(!config) return false;

  if(!threadconnection)  return false;

  ResetXBuffers();
  ResetConnectionStatistics();

  return threadconnection->Ini();
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDWORD DIOSTREAMI2C::ReadDirect(XBYTE* buffer, XDWORD size)
* @brief      ReadDirect
* @ingroup    DATAIO
*
* @param[in]  buffer : 
* @param[in]  size : 
* 
* @return     XDWORD : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
XDWORD DIOSTREAMI2C::ReadDirect(XBYTE* buffer, XDWORD size)  
{ 
  return 0;                  
}




/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDWORD DIOSTREAMI2C::WriteDirect(XBYTE* buffer, XDWORD size)
* @brief      WriteDirect
* @ingroup    DATAIO
*
* @param[in]  buffer : 
* @param[in]  size : 
* 
* @return     XDWORD : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
XDWORD DIOSTREAMI2C::WriteDirect(XBYTE* buffer, XDWORD size)  
{ 
  return 0;                  
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOSTREAMI2C::Close()
* @brief      Close
* @ingroup    DATAIO
*
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool DIOSTREAMI2C::Close()
{
  if(!threadconnection) return false;

  threadconnection->End();

  return true;
}




/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOSTREAMI2C::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    DATAIO
*
* @return     void : does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void DIOSTREAMI2C::Clean()
{
  config          = NULL;

  threadconnection = NULL;
}



