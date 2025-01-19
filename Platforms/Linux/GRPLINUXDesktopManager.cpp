/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       GRPLINUXDesktopManager.cpp
* 
* @class      GRPLINUXDESKTOPMANAGER
* @brief      LINUX Graphics Desktop Manager class
* @ingroup    PLATFORM_LINUX
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

#include "GRPLINUXDesktopManager.h"

#include <stdio.h>

#ifdef LINUX_X11_ACTIVE
#include <X11/Xlib.h>
#include <X11/extensions/Xrandr.h>
#endif

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

#pragma region CLASS_GRPLINUXDESKTOPMONITORS

   
/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         GRPLINUXDESKTOPMONITORS::GRPLINUXDESKTOPMONITORS()
* @brief      Constructor of class
* @ingroup    PLATFORM_LINUX
* 
* --------------------------------------------------------------------------------------------------------------------*/
GRPLINUXDESKTOPMONITORS::GRPLINUXDESKTOPMONITORS() : GRPDESKTOPMONITORS()
{
  Clean();

  MonitorEnum();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         GRPLINUXDESKTOPMONITORS::~GRPLINUXDESKTOPMONITORS()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    PLATFORM_LINUX
* 
* --------------------------------------------------------------------------------------------------------------------*/
GRPLINUXDESKTOPMONITORS::~GRPLINUXDESKTOPMONITORS()
{
  monitorsrects.DeleteContents();
  monitorsrects.DeleteAll();

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool GRPLINUXDESKTOPMONITORS::MonitorEnum()
* @brief      Monitor enum
* @ingroup    PLATFORM_LINUX
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPLINUXDESKTOPMONITORS::MonitorEnum()
{
  bool status = false;

  #ifdef LINUX_X11_ACTIVE

  Display*              display;
  Window                root;
  XRRScreenResources*   screen_resources;
  XRROutputInfo*        output_info;
  XRRCrtcInfo*          crtc_info;
  int                   screen;
  
  //display = XOpenDisplay(":0.0");
  display = XOpenDisplay(NULL);
  if(display) 
    {   
      screen  = DefaultScreen(display);  
      root    = RootWindow(display, screen);

      screen_resources = XRRGetScreenResources(display, root);
      if (screen_resources == NULL) 
        {
          XCloseDisplay(display);
          return false;
        }
      status = true;

      GRPRECTINT* allmonitor = GetCombinedRect();
      if(!allmonitor)
        {
          return false;
        }

      for(int c=0; c<screen_resources->noutput; c++) 
        {
          output_info = XRRGetOutputInfo(display, screen_resources, screen_resources->outputs[c]);
          if(output_info == NULL || output_info->connection == RR_Disconnected) 
            {
              if(output_info)
                {
                  XRRFreeOutputInfo(output_info);
                }

              continue;
            }
      
          crtc_info = XRRGetCrtcInfo(display, screen_resources, output_info->crtc);
          if(crtc_info == NULL) 
            {
              XRRFreeOutputInfo(output_info);
              continue;
            }

          // XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("%d) screen: X:%d,Y:%d  %dx%d"), c, crtc_info->x, crtc_info->y, crtc_info->width, crtc_info->height);

          GRPRECTINT* newmonitor = new GRPRECTINT();
          if(newmonitor)
            {
              newmonitor->x1  = crtc_info->x;
              newmonitor->x2  = crtc_info->x + crtc_info->width;
              newmonitor->y1  = crtc_info->y;
              newmonitor->y2  = crtc_info->y + crtc_info->height;

              GetMonitorsRects()->Add(newmonitor);

              GRPRECTINT* allmonitor = GetCombinedRect();
              if(!allmonitor)
                {
                  return false;
                }

              GRPRECTINT allmonitortempo =  UniteRectangles((*allmonitor), (*newmonitor));

              allmonitor->CopyFrom(&allmonitortempo);
            }

          XRRFreeCrtcInfo(crtc_info);
          XRRFreeOutputInfo(output_info);     
        }

      // XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("Full Screen: X1:%d,Y1:%d  X2:%d,Y2:%d"), allmonitor->x1, allmonitor->y1, allmonitor->x2, allmonitor->y2);

      XRRFreeScreenResources(screen_resources);  
      XCloseDisplay(display);

    }
  #endif
  
  /*
  if(!GetMonitorsRects()->GetSize())
    {    
      GRPRECTINT* newmonitor = new GRPRECTINT();
      if(newmonitor)
        {
          newmonitor->x1  = 0;
          newmonitor->x2  = 640;
          newmonitor->y1  = 0;
          newmonitor->y2  = 480;

          GetMonitorsRects()->Add(newmonitor);

          GRPRECTINT* allmonitor = GetCombinedRect();
          if(!allmonitor)
            {
              return false;
            }

          GRPRECTINT allmonitortempo =  UniteRectangles((*allmonitor), (*newmonitor));

          allmonitor->CopyFrom(&allmonitortempo);

          status = true;
        }
     }
  */

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void GRPLINUXDESKTOPMONITORS::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    PLATFORM_LINUX
* 
* --------------------------------------------------------------------------------------------------------------------*/
void GRPLINUXDESKTOPMONITORS::Clean()
{

}


#pragma endregion


#pragma region CLASS_GRPLINUXDESKTOPMANAGER


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         GRPLINUXDESKTOPMANAGER::GRPLINUXDESKTOPMANAGER()
* @brief      Constructor of class
* @ingroup    PLATFORM_LINUX
* 
* --------------------------------------------------------------------------------------------------------------------*/
GRPLINUXDESKTOPMANAGER::GRPLINUXDESKTOPMANAGER()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         GRPLINUXDESKTOPMANAGER::~GRPLINUXDESKTOPMANAGER()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    PLATFORM_LINUX
* 
* --------------------------------------------------------------------------------------------------------------------*/
GRPLINUXDESKTOPMANAGER::~GRPLINUXDESKTOPMANAGER()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         GRPLINUXDESKTOPMONITORS* GRPLINUXDESKTOPMANAGER::GetDesktopMonitors()
* @brief      Get desktop monitors
* @ingroup    PLATFORM_LINUX
* 
* @return     XDESKTOPMONITORS* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
GRPDESKTOPMONITORS* GRPLINUXDESKTOPMANAGER::GetDesktopMonitors()
{
  return (GRPDESKTOPMONITORS*)&desktopmonitors;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void GRPLINUXDESKTOPMANAGER::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    PLATFORM_LINUX
* 
* --------------------------------------------------------------------------------------------------------------------*/
void GRPLINUXDESKTOPMANAGER::Clean()
{

}


#pragma endregion


#pragma endregion


