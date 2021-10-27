/**-------------------------------------------------------------------------------------------------------------------
*
* @file       DIOStreamConfig.cpp
*
* @class      DIOSTREAMCONFIG
* @brief      Data Input/Output Stream Config class
* @ingroup    DATAIO
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

#include "DIOStreamConfig.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOSTREAMCONFIG::DIOSTREAMCONFIG()
* @brief      Constructor
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
DIOSTREAMCONFIG::DIOSTREAMCONFIG()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOSTREAMCONFIG::~DIOSTREAMCONFIG()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
DIOSTREAMCONFIG::~DIOSTREAMCONFIG()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOSTREAMTYPE DIOSTREAMCONFIG::GetType()
* @brief      GetType
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     DIOSTREAMTYPE :
*
*---------------------------------------------------------------------------------------------------------------------*/
DIOSTREAMTYPE DIOSTREAMCONFIG::GetType()
{
  return type;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOSTREAMCONFIG::SetType(DIOSTREAMTYPE type)
* @brief      SetType
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  type :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void DIOSTREAMCONFIG::SetType(DIOSTREAMTYPE type)
{
  this->type = type;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOSTREAMMODE DIOSTREAMCONFIG::GetMode()
* @brief      GetMode
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     DIOSTREAMMODE :
*
*---------------------------------------------------------------------------------------------------------------------*/
DIOSTREAMMODE DIOSTREAMCONFIG::GetMode()
{
  return mode;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOSTREAMCONFIG::SetMode(DIOSTREAMMODE mode)
* @brief      SetMode
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  mode :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void DIOSTREAMCONFIG::SetMode(DIOSTREAMMODE mode)
{
  this->mode = mode;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSTREAMCONFIG::IsServer()
* @brief      IsServer
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIOSTREAMCONFIG::IsServer()
{
  if(mode == DIOSTREAMMODE_SERVER) return true;
  if(mode == DIOSTREAMMODE_HOST)   return true;

  return false;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD DIOSTREAMCONFIG::GetSizeBufferSO()
* @brief      GetSizeBufferSO
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     XDWORD :
*
*---------------------------------------------------------------------------------------------------------------------*/
XDWORD DIOSTREAMCONFIG::GetSizeBufferSO()
{
  return sizebufferSO;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOSTREAMCONFIG::SetSizeBufferSO(XDWORD sizebufferSO)
* @brief      SetSizeBufferSO
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  sizebufferSO :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void DIOSTREAMCONFIG::SetSizeBufferSO(XDWORD sizebufferSO)
{
  this->sizebufferSO = sizebufferSO;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XTHREADPRIORITY DIOSTREAMCONFIG::GetThreadPriority()
* @brief      GetThreadPriority
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     XTHREADPRIORITY :
*
*---------------------------------------------------------------------------------------------------------------------*/
XTHREADPRIORITY DIOSTREAMCONFIG::GetThreadPriority()
{
  return threadpriority;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOSTREAMCONFIG::SetThreadPriority(XTHREADPRIORITY threadpriority)
* @brief      SetThreadPriority
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  threadpriority :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void DIOSTREAMCONFIG::SetThreadPriority(XTHREADPRIORITY threadpriority)
{
  this->threadpriority =  threadpriority;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD DIOSTREAMCONFIG::GetThreadWaitYield()
* @brief      GetThreadWaitYield
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     XDWORD :
*
*---------------------------------------------------------------------------------------------------------------------*/
XDWORD DIOSTREAMCONFIG::GetThreadWaitYield()
{
  return threadwaityield;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOSTREAMCONFIG::SetThreadWaitYield(XDWORD threadwaityield)
* @brief      SetThreadWaitYield
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  threadwaityield :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void DIOSTREAMCONFIG::SetThreadWaitYield(XDWORD threadwaityield)
{
  this->threadwaityield =  threadwaityield;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOSTREAMCONFIG::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void DIOSTREAMCONFIG::Clean()
{
  type                    = DIOSTREAMTYPE_UNKNOWN;
  mode                    = DIOSTREAMMODE_NONE;

  sizebufferSO            = 0;
  threadpriority          = XTHREADPRIORITY_NORMAL;
  threadwaityield         = XTHREAD_DEFAULTWAITYIELD;
}






