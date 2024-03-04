/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       GRPDisplayDevice.cpp
* 
* @class      GRPDISPLAYDEVICE
* @brief      Graphics Display Device (screen class for display devices)
* @ingroup    GRAPHIC
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

#include "GRPDisplayDevice.h"

#include "GRPXEvent.h"
#include "GRPCanvas.h"
#include "GRPViewport.h"

#include "XMemory_Control.h"

#pragma endregion


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         GRPDISPLAYDEVICE::GRPDISPLAYDEVICE()
* @brief      Constructor
* @ingroup    GRAPHIC
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
GRPDISPLAYDEVICE::GRPDISPLAYDEVICE()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         GRPDISPLAYDEVICE::~GRPDISPLAYDEVICE()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    GRAPHIC
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
GRPDISPLAYDEVICE::~GRPDISPLAYDEVICE()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRPDISPLAYDEVICE::Create(void* handle)
* @brief      Create
* @ingroup    GRAPHIC
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPDISPLAYDEVICE::Create(bool show)
{

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRPDISPLAYDEVICE::Update()
* @brief      Update
* @ingroup    GRAPHIC
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPDISPLAYDEVICE::Update()
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool GRPDISPLAYDEVICE::Update(GRPCANVAS* canvas)
* @brief      Update
* @ingroup    GRAPHIC
* 
* @param[in]  canvas : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPDISPLAYDEVICE::Update(GRPCANVAS* canvas)
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRPDISPLAYDEVICE::Delete()
* @brief      Delete
* @ingroup    GRAPHIC
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPDISPLAYDEVICE::Delete()
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRPDISPLAYDEVICE::Resize(int width, int height)
* @brief
* @ingroup    GRAPHIC
*
* @param[in]  width :
* @param[in]  height :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPDISPLAYDEVICE::Resize(int width, int height)
{
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRPDISPLAYDEVICE::IsShow()
* @brief      IsShow
* @ingroup    GRAPHIC
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPDISPLAYDEVICE::IsShow()
{
  return isshow;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRPDISPLAYDEVICE::Show(bool active)
* @brief      Show
* @ingroup    GRAPHIC
*
* @param[in]  active :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPDISPLAYDEVICE::Show(bool active)
{
  isshow  = active;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRPDISPLAYDEVICE::ShowCursor(bool active)
* @brief      ShowCursor
* @ingroup    GRAPHIC
*
* @param[in]  active :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPDISPLAYDEVICE::ShowCursor(bool active)
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRPDISPLAYDEVICE::ShowTopMost(bool active)
* @brief      ShowTopMost
* @ingroup    GRAPHIC
*
* @param[in]  active :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPDISPLAYDEVICE::ShowTopMost(bool active)
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void* GRPDISPLAYDEVICE::GetHandle()
* @brief
* @ingroup    GRAPHIC
*
* @return     void* :
*
* --------------------------------------------------------------------------------------------------------------------*/
void* GRPDISPLAYDEVICE::GetHandle()
{
  return NULL;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void GRPDISPLAYDEVICE::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    GRAPHIC
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void GRPDISPLAYDEVICE::Clean()
{

}


#pragma endregion








