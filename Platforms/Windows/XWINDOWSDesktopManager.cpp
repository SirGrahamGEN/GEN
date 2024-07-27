/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       XWINDOWSDesktopManager.cpp
* 
* @class      XWINDOWSDESKTOPMANAGER
* @brief      WINDOWS eXtended Utils Desktop Manager class
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
#pragma region PRECOMPILATION_INCLUDES

#include "GEN_Defines.h"

#pragma endregion


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "XWINDOWSDesktopManager.h"

#include "XMemory_Control.h"

#pragma endregion


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS

#pragma region CLASS_XWINDOWSDESKTOPMONITORS

   
/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XWINDOWSDESKTOPMONITORS::XWINDOWSDESKTOPMONITORS()
* @brief      Constructor
* @ingroup    PLATFORM_WINDOWS
* 
* --------------------------------------------------------------------------------------------------------------------*/
XWINDOWSDESKTOPMONITORS::XWINDOWSDESKTOPMONITORS()
{
  Clean();

  SetRectEmpty(&combinedrect);
  EnumDisplayMonitors(0, 0, MonitorEnum, (LPARAM)this);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XWINDOWSDESKTOPMONITORS::~XWINDOWSDESKTOPMONITORS()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    PLATFORM_WINDOWS
* 
* --------------------------------------------------------------------------------------------------------------------*/
XWINDOWSDESKTOPMONITORS::~XWINDOWSDESKTOPMONITORS()
{
  monitorsrects.DeleteContents();
  monitorsrects.DeleteAll();

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XVECTOR<RECT*>* XWINDOWSDESKTOPMONITORS::GetMonitorsRects()
* @brief      GetMonitorsRects
* @ingroup    PLATFORM_WINDOWS
* 
* @return     XVECTOR<RECT*>* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XVECTOR<RECT*>* XWINDOWSDESKTOPMONITORS::GetMonitorsRects()
{
  return &monitorsrects;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         RECT* XWINDOWSDESKTOPMONITORS::GetCombinedRect()
* @brief      GetCombinedRect
* @ingroup    PLATFORM_WINDOWS
* 
* @return     RECT* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
RECT* XWINDOWSDESKTOPMONITORS::GetCombinedRect()
{
  return &combinedrect;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void XWINDOWSDESKTOPMONITORS::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    PLATFORM_WINDOWS
* 
* --------------------------------------------------------------------------------------------------------------------*/
void XWINDOWSDESKTOPMONITORS::Clean()
{

}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         static BOOL CALLBACK XWINDOWSDESKTOPMONITORS::MonitorEnum(HMONITOR hmon,HDC hdc,LPRECT rectmonitor,LPARAM pdata)
* @brief      MonitorEnum
* @ingroup    PLATFORM_WINDOWS
* 
* @param[in]  hmon : 
* @param[in]  hdc : 
* @param[in]  rectmonitor : 
* @param[in]  pdata : 
* 
* @return     static : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
BOOL CALLBACK XWINDOWSDESKTOPMONITORS::MonitorEnum(HMONITOR hmon,HDC hdc,LPRECT rectmonitor,LPARAM pdata)
{
  XWINDOWSDESKTOPMONITORS* deskmonitors = (XWINDOWSDESKTOPMONITORS*)pdata;
  if(!deskmonitors)
    {
      return FALSE;  
    }

  RECT* _rectmonitor = new RECT();
  if(_rectmonitor)
    {
      _rectmonitor->left    = rectmonitor->left;
      _rectmonitor->right   = rectmonitor->right;
      _rectmonitor->top     = rectmonitor->top;
      _rectmonitor->bottom  = rectmonitor->bottom;

      deskmonitors->GetMonitorsRects()->Add(_rectmonitor);
    }

  return UnionRect(deskmonitors->GetCombinedRect(), deskmonitors->GetCombinedRect(), rectmonitor);  
}


#pragma endregion


#pragma region CLASS_XWINDOWSDESKTOPMANAGER


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XWINDOWSDESKTOPMANAGER::XWINDOWSDESKTOPMANAGER()
* @brief      Constructor
* @ingroup    PLATFORM_WINDOWS
* 
* --------------------------------------------------------------------------------------------------------------------*/
XWINDOWSDESKTOPMANAGER::XWINDOWSDESKTOPMANAGER()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XWINDOWSDESKTOPMANAGER::~XWINDOWSDESKTOPMANAGER()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    PLATFORM_WINDOWS
* 
* --------------------------------------------------------------------------------------------------------------------*/
XWINDOWSDESKTOPMANAGER::~XWINDOWSDESKTOPMANAGER()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XWINDOWSDESKTOPMONITORS* XWINDOWSDESKTOPMANAGER::GetDesktopMonitors()
* @brief      GetDesktopMonitors
* @ingroup    PLATFORM_WINDOWS
* 
* @return     XWINDOWSDESKTOPMONITORS* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XWINDOWSDESKTOPMONITORS* XWINDOWSDESKTOPMANAGER::GetDesktopMonitors()
{
  return &desktopmonitors;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void XWINDOWSDESKTOPMANAGER::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    PLATFORM_WINDOWS
* 
* --------------------------------------------------------------------------------------------------------------------*/
void XWINDOWSDESKTOPMANAGER::Clean()
{

}


#pragma endregion


#pragma endregion



