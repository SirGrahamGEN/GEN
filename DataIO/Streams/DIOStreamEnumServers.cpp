/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIOStreamEnumServers.cpp
* 
* @class      DIOSTREAMENUMSERVERS
* @brief      Data Input/Output Stream Enum Servers class
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

/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_DEFINES_INCLUDE

#include "GEN_Defines.h"

#pragma endregion


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "DIOStreamEnumServers.h"

#include "XFactory.h"
#include "XBuffer.h"

#include "DIOFactory.h"

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
* @fn         DIOSTREAMENUMSERVERS::DIOSTREAMENUMSERVERS()
* @brief      Constructor of class
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOSTREAMENUMSERVERS::DIOSTREAMENUMSERVERS(): DIOSTREAMENUMDEVICES()
{
  Clean();

  GEN_XFACTORY_CREATE(xtimer, CreateTimer())
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOSTREAMENUMSERVERS::~DIOSTREAMENUMSERVERS()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOSTREAMENUMSERVERS::~DIOSTREAMENUMSERVERS()
{
  GEN_XFACTORY.DeleteTimer(xtimer);

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD DIOSTREAMENUMSERVERS::GetSearchTimeout()
* @brief      Get search timeout
* @ingroup    DATAIO
*
* @return     XDWORD :
*
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD DIOSTREAMENUMSERVERS::GetSearchTimeout()
{
  return searchtimeout;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOSTREAMENUMSERVERS::SetSearchTimeout(int searchtimeout)
* @brief      Set search timeout
* @ingroup    DATAIO
*
* @param[in]  searchtimeout :
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOSTREAMENUMSERVERS::SetSearchTimeout(int searchtimeout)
{
  this->searchtimeout = searchtimeout;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSTREAMENUMSERVERS::Search(int searchtimeout)
* @brief      Search
* @ingroup    DATAIO
*
* @param[in]  searchtimeout :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSTREAMENUMSERVERS::Search(int searchtimeout)
{
  if(issearching) return false;

  this->searchtimeout = searchtimeout;

  return Search();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSTREAMENUMSERVERS::Search()
* @brief      Search
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSTREAMENUMSERVERS::Search()
{
  issearching = false;

  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSTREAMENUMSERVERS::StopSearch(bool waitend)
* @brief      Stop search
* @ingroup    DATAIO
*
* @param[in]  waitend :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSTREAMENUMSERVERS::StopSearch(bool waitend)
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSTREAMENUMSERVERS::IsSearching()
* @brief      Is searching
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSTREAMENUMSERVERS::IsSearching()
{
  return issearching;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSTREAMENUMSERVERS::IsDeviceAvailable(XCHAR* resource)
* @brief      Is device available
* @ingroup    DATAIO
*
* @param[in]  resource :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSTREAMENUMSERVERS::IsDeviceAvailable(XCHAR* resource)
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XTIMER* DIOSTREAMENUMSERVERS::GetXTimer()
* @brief      Get X timer
* @ingroup    DATAIO
*
* @return     XTIMER* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XTIMER* DIOSTREAMENUMSERVERS::GetXTimer()
{
  return xtimer;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSTREAMENUMSERVERS::SendSignal()
* @brief      Send signal
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSTREAMENUMSERVERS::SendSignal()
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD DIOSTREAMENUMSERVERS::GetID()
* @brief      Get ID
* @ingroup    DATAIO
*
* @return     XDWORD :
*
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD DIOSTREAMENUMSERVERS::GetID()
{
  return ID;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSTREAMENUMSERVERS::SetID(XDWORD ID)
* @brief      Set ID
* @ingroup    DATAIO
*
* @param[in]  ID :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSTREAMENUMSERVERS::SetID(XDWORD ID)
{
  this->ID = ID;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOSTREAMENUMSERVERS::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOSTREAMENUMSERVERS::Clean()
{
  type             = DIOSTREAMENUMTYPE_LOCAL_SERVERS;

  xtimer           = NULL;

  ID               = 0;

  issearching      = false;
  searchtimeout    = 0;
}


#pragma endregion

