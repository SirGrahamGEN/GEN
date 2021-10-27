/**-------------------------------------------------------------------------------------------------------------------
*
* @file       GRPDisplayDevice.cpp
*
* @class      GRPDISPLAYDEVICE
* @brief      Graphics Display Device (screen class for display devices)
* @ingroup    GRAPHIC
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

#include "GRPXEvent.h"
#include "GRPCanvas.h"
#include "GRPViewPort.h"

#include "GRPDisplayDevice.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         GRPDISPLAYDEVICE::GRPDISPLAYDEVICE()
* @brief      Constructor
* @ingroup    GRAPHIC
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
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
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
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
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
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
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool GRPDISPLAYDEVICE::Update()
{
  return false;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRPDISPLAYDEVICE::Update(GRPCAVAS* canvas)
* @brief      Update
* @ingroup    GRAPHIC
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  canvas : canvas handle
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
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
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
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
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  width :
* @param[in]  height :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
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
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
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
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  active :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
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
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  active :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
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
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  active :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
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
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     void* :
*
*---------------------------------------------------------------------------------------------------------------------*/
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
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void GRPDISPLAYDEVICE::Clean()
{

}


