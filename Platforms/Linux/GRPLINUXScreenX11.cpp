/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       GRPLINUXScreenX11.cpp
* 
* @class      GRPLINUXSCREENX11
* @brief      LINUX Graphics X11 Screen class
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

/*---- PRECOMPILATION INCLUDES ----------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_INCLUDES

#include "GEN_Defines.h"

#pragma endregion


#ifdef LINUX_X11_ACTIVE


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "GRPLINUXScreenX11.h"

#include "XTrace.h"

#include "GRPCanvas.h"

#include "XMemory_Control.h"

#pragma endregion


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         GRPLINUXSCREENX11::GRPLINUXSCREENX11()
* @brief      Constructor
* @ingroup    PLATFORM_LINUX
*
* --------------------------------------------------------------------------------------------------------------------*/
GRPLINUXSCREENX11::GRPLINUXSCREENX11(): GRPSCREEN()
{
  Clean();

  type = GRPSCREENTYPE_LINUX_X11;

  display = XOpenDisplay(NULL);
  if(display)
    {
      int width  = DisplayWidth  (display, DefaultScreen (display));
      int height = DisplayHeight (display, DefaultScreen (display));
      int depth  = DefaultDepth  (display, DefaultScreen (display));

      originalwidth   = width;
      originalheight  = height;

      SetSize(width, height);
      SetMaxSize(width, height);

      switch(depth)
        {
          case   8 : SetMode(GRPPROPERTYMODE_08_INDEX);     break;
          case  16 : SetMode(GRPPROPERTYMODE_16_RGB_565);   break;
          case  24 : SetMode(GRPPROPERTYMODE_24_BGR_888);   break;
          case  32 : SetMode(GRPPROPERTYMODE_32_BGRA_8888); break;
        }

      SetIsBufferInverse(true);
    }
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         GRPLINUXSCREENX11::~GRPLINUXSCREENX11()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    PLATFORM_LINUX
*
* --------------------------------------------------------------------------------------------------------------------*/
GRPLINUXSCREENX11::~GRPLINUXSCREENX11()
{
  if(!display)
    {
      return;
    }
      
  ScreenResolution(display, root, originalwidth, originalheight, 60, false);

  Delete();

  //XCloseDisplay(display);
 
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRPLINUXSCREENX11::Create(bool show)
* @brief      Create
* @ingroup    PLATFORM_LINUX
*
* @param[in]  show :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPLINUXSCREENX11::Create(bool show)
{
  if(!display) return false;

  int                   screen;
  int                   depth;
  Visual*               visual;
  XSetWindowAttributes  attributes;
  int                   wndwidth  = DisplayWidth (display, DefaultScreen (display));
  int                   wndheight = DisplayHeight (display, DefaultScreen (display));

  screen     = DefaultScreen(display);
  root       = RootWindow(display,screen);
  depth      = DefaultDepth(display,screen);
  visual     = DefaultVisual(display,screen);

  attributes.background_pixel   = XBlackPixel(display,screen);
  attributes.border_pixel       = XBlackPixel(display,screen);
  attributes.override_redirect  = false;

  int x = (wndwidth  - width)  / 2;
  int y = (wndheight - height) / 2;

  window =  XCreateWindow(display,RootWindow(display,screen),x ,y , width, height, 1,depth, 0 /*InputOutput*/, visual, CWBackPixel | CWBorderPixel | CWOverrideRedirect,&attributes);
  if(!window) return false;

  if(IsFullScreen())
    {
      Atom wm_state   = XInternAtom (display, "_NET_WM_STATE", true );
      Atom wm_fullscreen = XInternAtom (display, "_NET_WM_STATE_FULLSCREEN", true );

      XChangeProperty(display, window, wm_state, XA_ATOM, 32, PropModeReplace, (unsigned char *)&wm_fullscreen, 1);

      ScreenResolution(display, root, width, height, 60, false);
    }

  XMapWindow(display, window);
  XMoveWindow(display, window,x,y);

  CreateBuffers();

  XFlush(display);

  return GRPSCREEN::Create(show);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRPLINUXSCREENX11::Update()
* @brief      Update
* @ingroup    PLATFORM_LINUX
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPLINUXSCREENX11::Update()
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRPLINUXSCREENX11::Update(GRPCANVAS* canvas)
* @brief      Update
* @ingroup    PLATFORM_LINUX
*
* @param[in]  canvas : canvas handle
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPLINUXSCREENX11::Update(GRPCANVAS* canvas)
{
  if(!display) return false;
  if(!window)  return false;
  if(!canvas)  return false;

  GC gc = XCreateGC(display, window, 0, NULL);
  if(gc)
    {
      XSync(display,false);

      if(IsEqualSizeTo(canvas) == ISEQUAL)
        {
          XImage* image = CreateXImageFromBuffer(display, DefaultScreen(display), (XBYTE*)canvas->GetBuffer(), width, height);
          if(image)
            {
              XPutImage(display, window, gc, image, 0, 0, 0, 0, width, height);
              XDestroyImage(image);
            }
        }
        else
        {
          canvas->CopyBufferRenderToScreen(this);

          XImage* image = CreateXImageFromBuffer(display, DefaultScreen(display), (XBYTE*)buffer, width, height);
          if(image)
            {
              XPutImage(display, window, gc, image, 0, 0, 0, 0, width, height);
              XDestroyImage(image);
            }
        }

      XFreeGC(display, gc);
    }

  XFlush(display);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRPLINUXSCREENX11::Delete()
* @brief      Delete
* @ingroup    PLATFORM_LINUX
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPLINUXSCREENX11::Delete()
{
  if(!display) return false;
  if(!window)  return false;

  DeleteBuffers();

  XDestroyWindow(display, window);

  isactive = false;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRPLINUXSCREENX11::Resize(int width, int height)
* @brief      Resize
* @ingroup    PLATFORM_LINUX
*
* @param[in]  width :
* @param[in]  height :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPLINUXSCREENX11::Resize(int width, int height)
{
  XResizeWindow(display, window, width, height);

  return UpdateSize(width, height);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRPLINUXSCREENX11::Show(bool active)
* @brief      Show
* @ingroup    PLATFORM_LINUX
*
* @param[in]  active :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPLINUXSCREENX11::Show(bool active)
{
  isshow  = active;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRPLINUXSCREENX11::ShowCursor(bool active)
* @brief      ShowCursor
* @ingroup    PLATFORM_LINUX
*
* @param[in]  active :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPLINUXSCREENX11::ShowCursor(bool active)
{
  if(!active)
    {
      // vars to make blank cursor
      Pixmap  blank;
      XColor  dummy;
      char    data[1] = { 0 };
      Cursor  cursor;

      // make a blank cursor
      blank = XCreateBitmapFromData(display, window, data, 1, 1);
      if(blank != None)
        {
          cursor = XCreatePixmapCursor(display, blank, blank, &dummy, &dummy, 0, 0);
          XFreePixmap(display, blank);
          XDefineCursor(display, window,cursor);

        } else return false;
    }
   else
    {
      XUndefineCursor(display, window);
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void* GRPLINUXSCREENX11::GetHandle()
* @brief      GetHandle
* @ingroup    PLATFORM_LINUX
*
* @return     void* :
*
* --------------------------------------------------------------------------------------------------------------------*/
void* GRPLINUXSCREENX11::GetHandle()
{
  return (void*)window;

}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool GRPLINUXSCREENX11::IsDesktop()
* @brief      IsDesktop
* @ingroup    PLATFORM_LINUX
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool  GRPLINUXSCREENX11::IsDesktop()
{
  return isdesktop;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void GRPLINUXSCREENX11::SetIsDesktop(bool isdesktop)
* @brief      Set Is Desktop
* @ingroup    PLATFORM_LINUX
*
* @param[in]  isdesktop : set is run in desktop
*
* --------------------------------------------------------------------------------------------------------------------*/
void GRPLINUXSCREENX11::SetIsDesktop(bool isdesktop)
{
  this->isdesktop = isdesktop;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRPLINUXSCREENX11::HasFocus()
* @brief      HasFocus
* @ingroup    PLATFORM_LINUX
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPLINUXSCREENX11::HasFocus()
{
  Window focus;
  int    status = 0;

  XGetInputFocus(display, &focus, &status);

  if(focus ==  window) return true;

  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         Display* GRPLINUXSCREENX11::GetDisplay()
* @brief      Get Display
* @ingroup    PLATFORM_LINUX
*
* @return     Display* :
*
* --------------------------------------------------------------------------------------------------------------------*/
Display* GRPLINUXSCREENX11::GetDisplay()
{
  return display;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         Window* GRPLINUXSCREENX11::GetWindow()
* @brief      GetWindow
* @ingroup    PLATFORM_LINUX
*
* @return     Window* :
*
* --------------------------------------------------------------------------------------------------------------------*/
Window* GRPLINUXSCREENX11::GetWindow()
{
  return &window;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int GRPLINUXSCREENX11::ScreenResolution(Display* display, Window root, int xsz, int ysz, int rate, int just_checking)
* @brief      ScreenResolution
* @ingroup    PLATFORM_LINUX
*
* @param[in]  display :
* @param[in]  root :
* @param[in]  xsz :
* @param[in]  ysz :
* @param[in]  rate :
* @param[in]  just_checking :
*
* @return     int :
*
* --------------------------------------------------------------------------------------------------------------------*/
int GRPLINUXSCREENX11::ScreenResolution(Display* display, Window  root, int xsz, int ysz, int rate, int just_checking)
{
  XRRScreenConfiguration*   xrr_config = 0;
  int                       event_base;
  int                       error_base;
  int                       ver_major;
  int                       ver_minor;
  int                       use_rate;
  Status                    result = -1;

  if(!display) return -1;

  // must check at runtime for the availability of the extension
  if(!XRRQueryExtension(display, &event_base, &error_base))
    {
        return -1;
    }

  XRRQueryVersion(display, &ver_major, &ver_minor);

  // we only heed the rate if we CAN actually use it (Xrandr >= 1.1) and the user actually cares about it (rate > 0)
  use_rate = ( rate > 0 ) && ( ( ver_major > 1 ) || (( ver_major == 1 ) && ( ver_minor >= 1 )));

  // this loop is only so that the whole thing will be repeated if someone else changes video mode between our query of the current information and the attempt to change it.
  do{
        XRRScreenSize*  ssizes;
        short*          rates;
        Rotation        rot;
        int             i;
        int             ssizes_count;
        int             rates_count;
        int             curr;
        int             res_idx = -1;
        Time timestamp, cfg_timestamp;

        if(xrr_config) XRRFreeScreenConfigInfo(xrr_config);

        if(!(xrr_config = XRRGetScreenInfo(display, root)))
          {
            //fgWarning("XRRGetScreenInfo failed");
            break;
          }

        ssizes    = XRRConfigSizes(xrr_config, &ssizes_count);
        curr      = XRRConfigCurrentConfiguration(xrr_config, &rot);
        timestamp = XRRConfigTimes(xrr_config, &cfg_timestamp);

        // if either of xsz or ysz are unspecified, use the current values
        if(xsz <= 0) xsz =  ssizes[curr].width;
        if(ysz <= 0) ysz =  ssizes[curr].height;

        if(xsz == ssizes[curr].width && ysz == ssizes[curr].height)
          {
            // no need to switch, we're already in the requested resolution
            res_idx = curr;
          }
         else
          {
            for(i=0; i<ssizes_count; i++)
              {
                if(ssizes[i].width == xsz && ssizes[i].height == ysz)
                  {
                    res_idx = i;
                    break;  // found it
                  }
              }
          }

        if(res_idx == -1) break;  // no matching resolution

        #if ( RANDR_MAJOR > 1 ) || ( ( RANDR_MAJOR == 1 ) && ( RANDR_MINOR >= 1 ) )
        if(use_rate)
          {
            // for the selected resolution, let's find out if there is a matching refresh rate available.
            rates = XRRConfigRates(xrr_config, res_idx, &rates_count);

            for(i=0; i<rates_count; i++)
              {
                if(rates[i] == rate)
                  {
                    break;
                  }
              }

            if(i == rates_count) break; // no matching rate
          }
        #endif

        if(just_checking)
          {
            result = 0;
            break;
          }

        #if ( RANDR_MAJOR > 1 ) || ( ( RANDR_MAJOR == 1 ) && ( RANDR_MINOR >= 1 ) )
        if(use_rate)
              result = XRRSetScreenConfigAndRate(display, xrr_config, root, res_idx, rot, rate, timestamp);
        else
        #endif
              result = XRRSetScreenConfig(display, xrr_config, root, res_idx, rot, timestamp);

    } while(result == RRSetConfigInvalidTime);

  if(xrr_config) XRRFreeScreenConfigInfo(xrr_config);

  if(result == 0) return 0;

  return -1;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XImage* GRPLINUXSCREENX11::CreateXImageFromBuffer(Display* display, int screen, XBYTE* buffer, int width, int height)
* @brief      CreateXImageFromBuffer
* @ingroup    PLATFORM_LINUX
*
* @param[in]  display :
* @param[in]  screen :
* @param[in]  buffer :
* @param[in]  width :
* @param[in]  height :
*
* @return     XImage* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XImage* GRPLINUXSCREENX11::CreateXImageFromBuffer(Display* display, int screen, XBYTE* buffer, int width, int height)
{
  XImage* image = NULL;
  int     depth;
  Visual* visual;
  double  rratio;
  double  gratio;
  double  bratio;
  int     outindex       = 0;
  int     numbufferbytes = (3 * (width * height));

  depth  = DefaultDepth(display,screen);
  visual = DefaultVisual(display,screen);

  rratio = visual->red_mask   / 255.0;
  gratio = visual->green_mask / 255.0;
  bratio = visual->blue_mask  / 255.0;

  if(depth >= 24)
    {
      int    numnewbufferbytes = (4 * (width * height));
      XDWORD* newbuffer        = (XDWORD*)malloc(numnewbufferbytes);

      for(int index=0;index<numbufferbytes;)
        {
          XDWORD b = (buffer[index++] * bratio);
          XDWORD g = (buffer[index++] * gratio);
          XDWORD r = (buffer[index++] * rratio);

          r &= visual->red_mask;
          g &= visual->green_mask;
          b &= visual->blue_mask;

          newbuffer[outindex] = r | g | b;

          ++outindex;
        }

      image = XCreateImage (display, CopyFromParent, depth,  ZPixmap, 0, (char *)newbuffer,width, height, 32, 0);
    }
    else
    {
      if(depth >= 15)
        {
          int   numnewbufferbytes = (2 * (width * height));
          XWORD* newbuffer          = (XWORD*)malloc(numnewbufferbytes);

          for(int index=0;index<numbufferbytes;)
            {
              XDWORD b = (buffer[index++] * bratio);
              XDWORD g = (buffer[index++] * gratio);
              XDWORD r = (buffer[index++] * rratio);

              r &= visual->red_mask;
              g &= visual->green_mask;
              b &= visual->blue_mask;

              newbuffer[outindex] = r | g | b;

              ++outindex;
            }

          image = XCreateImage(display, CopyFromParent, depth, ZPixmap, 0, (char*)newbuffer, width, height, 16, 0);

        }  else return NULL;
    }

  XInitImage(image);

  if(LSBFirst == GetByteOrder())
          image->byte_order = LSBFirst;
    else image->byte_order = MSBFirst;

  image->bitmap_bit_order = MSBFirst;

  return image;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         int GRPLINUXSCREENX11::GetByteOrder()
* @brief      GetByteOrder
* @ingroup    PLATFORM_LINUX
* 
* @return     int : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
int GRPLINUXSCREENX11::GetByteOrder()
{
  union
  {
    char c[sizeof(short)];
    short s;

  } order;

  order.s = 1;
  if((1 == order.c[0]))
    {
      return LSBFirst;
    }
   else
    {
      return MSBFirst;
    }
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void GRPLINUXSCREENX11::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    PLATFORM_LINUX
*
* --------------------------------------------------------------------------------------------------------------------*/
void GRPLINUXSCREENX11::Clean()
{
  display   = NULL;
  window    = 0;

  isdesktop = false;
}


#pragma endregion


#endif

