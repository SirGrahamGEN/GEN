/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIOStreamDevice.cpp
* 
* @class      DIOSTREAMDEVICE
* @brief      Data Input/Output Stream Device class
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

#include "DIOStreamDevice.h"

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
* @fn         DIOSTREAMDEVICE::DIOSTREAMDEVICE()
* @brief      Constructor of class
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOSTREAMDEVICE::DIOSTREAMDEVICE()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOSTREAMDEVICE::~DIOSTREAMDEVICE()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOSTREAMDEVICE::~DIOSTREAMDEVICE()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int DIOSTREAMDEVICE::GetIndex()
* @brief      Get index
* @ingroup    DATAIO
*
* @return     int :
*
* --------------------------------------------------------------------------------------------------------------------*/
int DIOSTREAMDEVICE::GetIndex()
{
  return index;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSTREAMDEVICE::SetIndex(int index)
* @brief      Set index
* @ingroup    DATAIO
*
* @param[in]  index :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSTREAMDEVICE::SetIndex(int index)
{
  this->index = index;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOSTREAMDEVICE_TYPE DIOSTREAMDEVICE::GetType()
* @brief      Get type
* @ingroup    DATAIO
*
* @return     DIOSTREAMDEVICE_TYPE :
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOSTREAMDEVICE_TYPE DIOSTREAMDEVICE::GetType()
{
  return type;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOSTREAMDEVICE::SetType(DIOSTREAMDEVICE_TYPE type)
* @brief      Set type
* @ingroup    DATAIO
*
* @param[in]  type :
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOSTREAMDEVICE::SetType(DIOSTREAMDEVICE_TYPE type)
{
  this->type = type;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* DIOSTREAMDEVICE::GetName()
* @brief      Get name
* @ingroup    DATAIO
*
* @return     XSTRING* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* DIOSTREAMDEVICE::GetName()
{
  return &name;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* DIOSTREAMDEVICE::GetDescription()
* @brief      Get description
* @ingroup    DATAIO
*
* @return     XSTRING* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* DIOSTREAMDEVICE::GetDescription()
{
  return &description;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* DIOSTREAMDEVICE::GetResource()
* @brief      Get resource
* @ingroup    DATAIO
*
* @return     XSTRING* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* DIOSTREAMDEVICE::GetResource()
{
  return &resource;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSTREAMDEVICE::CopyFrom(DIOSTREAMDEVICE& device)
* @brief      Copy from
* @ingroup    DATAIO
*
* @param[in]  device :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSTREAMDEVICE::CopyFrom(DIOSTREAMDEVICE& device)
{
  return device.CopyTo((*this));
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSTREAMDEVICE::CopyTo(DIOSTREAMDEVICE& device)
* @brief      Copy to
* @ingroup    DATAIO
*
* @param[in]  device :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSTREAMDEVICE::CopyTo(DIOSTREAMDEVICE& device)
{
  device.SetIndex(index);
  device.GetName()->Set(name);
  device.GetDescription()->Set(description);
  device.GetResource()->Set(resource);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSTREAMDEVICE::DebugPrintInfo()
* @brief      Debug print info
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSTREAMDEVICE::DebugPrintInfo()
{
  #ifdef XTRACE_ACTIVE
  XSTRING line;

  XTRACE_PRINTCOLOR(XTRACE_COLOR_BLACK, __L(" ")                      , NULL);
  XTRACE_PRINTCOLOR(XTRACE_COLOR_BLACK, __L("Index            : %02d"), index);
  XTRACE_PRINTCOLOR(XTRACE_COLOR_BLACK, __L("Name             : %s")  , name.Get());
  XTRACE_PRINTCOLOR(XTRACE_COLOR_BLACK, __L("Description      : %s")  , description.Get());
  XTRACE_PRINTCOLOR(XTRACE_COLOR_BLACK, __L("Resource         : %s")  , resource.Get());

  return true;
  #else
  return false;
  #endif
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOSTREAMDEVICE::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOSTREAMDEVICE::Clean()
{
  index = 0;
  type  = DIOSTREAMDEVICE_TYPE_UNKNOWN;
}


#pragma endregion

