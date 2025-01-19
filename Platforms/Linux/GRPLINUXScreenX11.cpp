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

/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_DEFINES_INCLUDE

#include "GEN_Defines.h"

#pragma endregion


#ifdef LINUX_X11_ACTIVE


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES


#include "GRPLINUXScreenX11.h"

#include "XTrace.h"
#include "XBuffer.h"

#include "GRPCanvas.h"
#include "GRPDesktopManager.h"

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
* @fn         GRPLINUXSCREENX11::GRPLINUXSCREENX11()
* @brief      Constructor of class
* @ingroup    PLATFORM_LINUX
*
* --------------------------------------------------------------------------------------------------------------------*/
GRPLINUXSCREENX11::GRPLINUXSCREENX11(): GRPSCREEN()
{
  Clean();

  type = GRPSCREENTYPE_LINUX_X11;

  //display = XOpenDisplay(":0.0");  
  display = XOpenDisplay(NULL);  
  if(!display)
    {
      return;
    }

  XSetErrorHandler(ErrorHandler);
    
  int width  = DisplayWidth  (display, DefaultScreen (display));
  int height = DisplayHeight (display, DefaultScreen (display));
  int depth  = DefaultDepth  (display, DefaultScreen (display));

  SetSize(width, height);
  SetMaxSize(width, height);

  /*
  switch(depth)
    {
      case   8 : SetMode(GRPPROPERTYMODE_08_INDEX);     break;
      case  16 : SetMode(GRPPROPERTYMODE_16_RGB_565);   break;
      case  24 : SetMode(GRPPROPERTYMODE_24_BGR_888);   break;
      case  32 : SetMode(GRPPROPERTYMODE_32_BGRA_8888); break;
    }
  */

  SetMode(GRPPROPERTYMODE_32_BGRA_8888);

  SetIsBufferInverse(true);
    
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         GRPLINUXSCREENX11::~GRPLINUXSCREENX11()
* @brief      Destructor of class
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
      
  //ScreenResolution(display, root, originalwidth, originalheight, 60, false);

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
  if(!Create_Window(show)) 
    {
      return false;
    }

  XFlush(display);

  return GRPSCREEN::Create(show);
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
  if(!display)
    { 
      return false;
    }

  if(!window)  
    {
      return false;
    }


  if(!canvas)  
    {
      return false;
    }
  
  GC gc = XCreateGC(display, window, 0, NULL);
  if(gc)
    {
      XSync(display, false);

      XImage* image = CreateXImageFromBuffer(display, DefaultScreen(display), (XBYTE*)canvas->Buffer_Get(), width, height);
      if(image)
        {
          XPutImage(display, window, gc, image, 0, 0, 0, 0, width, height);
          XDestroyImage(image);
        }
       
      XFreeGC(display, gc);
    }

  XFlush(display);

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool GRPLINUXSCREENX11::UpdateTransparent(GRPCANVAS* canvas)
* @brief      Update transparent
* @ingroup    PLATFORM_LINUX
* 
* @param[in]  canvas : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPLINUXSCREENX11::UpdateTransparent(GRPCANVAS* canvas)
{
  return Update(canvas);  
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

  XDestroyWindow(display, window);

  return GRPSCREEN::Delete();
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
* @brief      Show cursor
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
* @brief      Get handle
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
* @brief      Is desktop
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
* @brief      Set is desktop
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
* @brief      Has focus
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
* @brief      Get display
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
* @brief      Get window
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
* @fn         Window* GRPLINUXSCREENX11::GetWindowRoot()
* @brief      Get window root
* @ingroup    PLATFORM_LINUX
* 
* @return     Window* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
Window* GRPLINUXSCREENX11::GetWindowRoot()
{
  return &root;
}
    

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XVisualInfo* GRPLINUXSCREENX11::GetVisualInfo()
* @brief      Get visual info
* @ingroup    PLATFORM_LINUX
* 
* @return     XVisualInfo* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XVisualInfo* GRPLINUXSCREENX11::GetVisualInfo()
{
  return &vinfo;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool GRPLINUXSCREENX11::Create_Window(bool show)
* @brief      Create window
* @ingroup    PLATFORM_LINUX
* 
* @param[in]  show : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPLINUXSCREENX11::Create_Window(bool show)
{
  typedef struct  
  {
    unsigned long flags;
    unsigned long functions;
    unsigned long decorations;
    long          inputMode;
    unsigned long status;

  } MOTIFWMHINTS;

  if(!display) 
    {
      return false;
    }

  GRPRECTINT*           alldesktoprect  = NULL;
  int                   screenselected  = GetDesktopScreenSelected();   
  XSetWindowAttributes  attr;  
  int                   posx            = 0;
  int                   posy            = 0;
  int                   status          = false;   


  root = DefaultRootWindow(display);    

  //ShowDebugNetSupportedPropertys();

  if(screenselected == GRPSCREENTYPE_DESKTOP_ALL)
    {
      alldesktoprect = GetDesktopManager()->GetDesktopMonitors()->GetCombinedRect(); 
    }
   else 
    {
      alldesktoprect = GetDesktopManager()->GetDesktopMonitors()->GetMonitorsRects()->Get(screenselected);       
    }
  
  if(!alldesktoprect)
    {
      return false;          
    }            
            
   if(Styles_IsFullScreen())          
    {
      posx   = alldesktoprect->x1;
      posy   = alldesktoprect->y1; 

      if(!alldesktoprect->x1)
        {
          posx++;              
        }

      if(!alldesktoprect->y1)
        {
          posy++;              
        }

      if(Style_Is(GRPSCREENSTYLE_FULLSCREEN_ADJUSTRESOLUTION))
        {          
          ChangeScreenResolution(width, height);          
        }
       else 
        {
          width  = alldesktoprect->GetWidth();    
          height = alldesktoprect->GetHeight(); 

          if(Style_Is(GRPSCREENSTYLE_HEIGHTWITHOUTTASKBAR))
            {
              height -= GetTaskBarHeight();
            }
        }                      
    }
   else
    {         
      if(positionx == GRPPROPERTYMODE_SCREEN_CENTER) 
        {
          posx = (alldesktoprect->GetWidth() - width)/2;
        }
       else 
        {
          posx = positionx; 
        }

      if(positiony == GRPPROPERTYMODE_SCREEN_CENTER) 
        {
          posy = (alldesktoprect->GetHeight() - height)/2;
        }
       else 
        {
          posy = positiony; 
        }

      posx  += alldesktoprect->x1;
      posy  += alldesktoprect->y1;       
    } 
  
  
  XMatchVisualInfo(display, DefaultScreen(display), 32, TrueColor, &vinfo);

  attr.colormap         = XCreateColormap(display, root, vinfo.visual, AllocNone);
  attr.border_pixel     = 0;
  attr.background_pixel = Style_Is(GRPSCREENSTYLE_TRANSPARENT)?0x00000000:0xFFFFFFFF;

  window = XCreateWindow(display, root, posx, posy, width, height, 0, vinfo.depth, InputOutput, vinfo.visual, CWColormap | CWBorderPixel | CWBackPixel, &attr);        
  
  //window =  XCreateSimpleWindow(display, root, posx, posy, width, height, 0,  BlackPixel(display, 0), WhitePixel(display, 0));          
  if(!window) 
    {
      return false;
    }      

  /*
  if(Style_Is(GRPSCREENSTYLE_FULLSCREEN))
    {
      Atom wm_state            = XInternAtom (display, "_NET_WM_STATE", true );
      Atom wm_state_fullscreen = XInternAtom (display, "_NET_WM_STATE_FULLSCREEN", true);  

      if(wm_state == None || wm_state_fullscreen == None)        
        {
          XTRACE_PRINTCOLOR(XTRACE_COLOR_RED, __L("[Screen X11] Error Atom FULLSCREEN  (fullscreen)"));
        }
       else
        {           
          XChangeProperty(display, window, wm_state, XA_ATOM, 32, PropModeReplace, (unsigned char *)&wm_state_fullscreen, 1);          
        }
    }
  */
 

  if(!Style_Is(GRPSCREENSTYLE_TITLE))
    {
      Atom          wmhintsatom = XInternAtom(display , "_MOTIF_WM_HINTS", True);
      MOTIFWMHINTS  hints; 

      XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("[Screen X11] Atom HINTS Decorations (no title) active"));

      if(wmhintsatom  == None)
        {
          XTRACE_PRINTCOLOR(XTRACE_COLOR_RED, __L("[Screen X11] Error Atom HINTS Decorations (no title)"));
        }
       else
        {
          memset(&hints, 0, sizeof(hints));

          hints.flags        = GRPLINUXSCREENX11_MWM_HINTS_DECORATIONS;   
          hints.decorations  = 0;  

          XChangeProperty(display, window, wmhintsatom, wmhintsatom, 32, PropModeReplace, (unsigned char *)&hints, 5); 
        }
    }
   else
    {
      if(!title.IsEmpty())
        {
          XBUFFER xbuffer;

          title.ConvertToASCII(xbuffer);

          XStoreName(display, window, (char*)xbuffer.Get());
        }

      if(Style_Is(GRPSCREENSTYLE_NOWINDOWICONS))
        {
          Atom          wmhintsatom = XInternAtom(display , "_MOTIF_WM_HINTS", True);
          MOTIFWMHINTS  hints;

          XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("[Screen X11] Atom HINTS Decorations (no icons) active"));

          if(wmhintsatom  == None)
            {
              XTRACE_PRINTCOLOR(XTRACE_COLOR_RED, __L("[Screen X11] Error Atom HINTS Decorations (no icons)"));
            }
           else
            { 
              memset(&hints, 0, sizeof(hints));

              hints.flags       = GRPLINUXSCREENX11_MWM_HINTS_DECORATIONS;
              hints.decorations = GRPLINUXSCREENX11_MWM_FUNC_CLOSE; 

              XChangeProperty(display, window, wmhintsatom, wmhintsatom, 32, PropModeReplace, (unsigned char*)&hints, 5);
            }
        }
    } 

  if(Style_Is(GRPSCREENSTYLE_NOICONTASKBAR))
    {
      Atom wm_state             = XInternAtom(display , "_NET_WM_STATE"             , True);
      Atom wm_state_skiptaskbar = XInternAtom(display , "_NET_WM_STATE_SKIP_TASKBAR", True);

      XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("[Screen X11] Atom SKIP_TASKBAR active"));
        
      if(wm_state == None || wm_state_skiptaskbar == None)
        {
          XTRACE_PRINTCOLOR(XTRACE_COLOR_RED, __L("[Screen X11] Error Atom SKIP_TASKBAR (No Icon Taskbar)"));
        }
       else
        {
          XChangeProperty(display, window, wm_state, XA_ATOM, 32,PropModeReplace, (unsigned char *)&wm_state_skiptaskbar, 1);          
        }
    }

  if(Style_Is(GRPSCREENSTYLE_ONTOP))
    {
      Atom wm_state       = XInternAtom(display , "_NET_WM_STATE"       , True);
      Atom wm_state_above = XInternAtom(display , "_NET_WM_STATE_ABOVE" , True);

      XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("[Screen X11] Atom ABOVE active"));

      if(wm_state == None || wm_state_above == None)
        {
          XTRACE_PRINTCOLOR(XTRACE_COLOR_RED, __L("[Screen X11] Error Atom ABOVE (On top)"));
        }
       else
        {
          XChangeProperty(display, window, wm_state, XA_ATOM, 32, PropModeReplace, (unsigned char *)&wm_state_above, 1);              
        }
    }


  if(Style_Is(GRPSCREENSTYLE_TRANSPARENT))
    {       
      /*
      Atom wm_opacity = XInternAtom(display, "_NET_WM_WINDOW_OPACITY", True);
      unsigned long opacity = (unsigned long)(0x01010101);

      XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("[Screen X11] Atom OPACITY active"));

      if(wm_opacity == None)
        {
          XTRACE_PRINTCOLOR(XTRACE_COLOR_RED, __L("[Screen X11] Error Atom OPACITY (Transparent)"));
        }
       else
        {
          XChangeProperty(display, window, wm_opacity, XA_CARDINAL, 32, PropModeReplace, (unsigned char *)&opacity, 1L);
        }
      */

      /*
      Atom           wm_opacity = XInternAtom(display, "_NET_WM_WINDOW_OPACITY", True);      
      int            alpha = 0;
          
      XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("[Screen X11] Atom OPACITY active"));

      if(wm_opacity == None)
        {
          XTRACE_PRINTCOLOR(XTRACE_COLOR_RED, __L("[Screen X11] Error Atom OPACITY (Transparent)"));
        }
       else
        {
          XChangeProperty (display, window, wm_opacity, XA_CARDINAL, 32, PropModeReplace, (unsigned char *)&alpha, 1);          
          XFlush(display);
        }
      */
    }
  
  XMapWindow(display , window);
  XMoveWindow(display, window, posx, posy);    

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool GRPLINUXSCREENX11::ChangeScreenResolution(int width, int height)
* @brief      Change screen resolution
* @ingroup    PLATFORM_LINUX
* 
* @param[in]  width : 
* @param[in]  height : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPLINUXSCREENX11::ChangeScreenResolution(int width, int height)
{   
  int                     num_sizes;
  XRRScreenSize*          xrrs;
  XRRScreenConfiguration* conf;
  short                   original_rate;
  Rotation                original_rotation;
  SizeID                  original_size_id;
 
  root  = RootWindow(display, 0);
  xrrs  = XRRSizes(display, 0, &num_sizes);
 
  for(int c=0; c<num_sizes; c++) 
    {
      if((xrrs[c].width  == width) && (xrrs[c].height == height))
        {
          short*  rates;
          int     num_rates;

          rates = XRRRates(display, 0, c, &num_rates);
                      
          conf             = XRRGetScreenInfo(display, root);
          original_rate    = XRRConfigCurrentRate(conf);
          original_size_id = XRRConfigCurrentConfiguration(conf, &original_rotation);
              
          int status = XRRSetScreenConfigAndRate(display, conf, root, c, original_rotation, rates[0], CurrentTime);

          return true;        
        }
    }

  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XImage* GRPLINUXSCREENX11::CreateXImageFromBuffer(Display* display, int screen, XBYTE* buffer, int width, int height)
* @brief      Create X image from buffer
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
  double  rratio;
  double  gratio;
  double  bratio;
  int     outindex       = 0;
  int     numbufferbytes = (4 * (width * height));

  rratio = vinfo.visual->red_mask   / 255.0;
  gratio = vinfo.visual->green_mask / 255.0;
  bratio = vinfo.visual->blue_mask  / 255.0;

  if(vinfo.depth >= 24)
    {
      int    numnewbufferbytes = (4 * (width * height));
      XDWORD* newbuffer        = (XDWORD*)malloc(numnewbufferbytes);

      for(int index=0;index<numbufferbytes;)
        {
          XDWORD b = (buffer[index++] * bratio);
          XDWORD g = (buffer[index++] * gratio);
          XDWORD r = (buffer[index++] * rratio);         
          XDWORD a;

          if(Style_Is(GRPSCREENSTYLE_TRANSPARENT))
            {
              a = buffer[index++] << 24;         
            }
           else
            {
              a = 0xFF000000;
              index++;
            } 

          r &= vinfo.visual->red_mask;
          g &= vinfo.visual->green_mask;
          b &= vinfo.visual->blue_mask;            

          newbuffer[outindex] = r | g | b | a;

          ++outindex;
        }

      image = XCreateImage (display, vinfo.visual, vinfo.depth,  ZPixmap, 0, (char *)newbuffer,width, height, 32, 0);
    }
    else
    {
      if(vinfo.depth >= 15)
        {
          int   numnewbufferbytes = (2 * (width * height));
          XWORD* newbuffer          = (XWORD*)malloc(numnewbufferbytes);

          for(int index=0;index<numbufferbytes;)
            {
              XDWORD b = (buffer[index++] * bratio);
              XDWORD g = (buffer[index++] * gratio);
              XDWORD r = (buffer[index++] * rratio);

              r &= vinfo.visual->red_mask;
              g &= vinfo.visual->green_mask;
              b &= vinfo.visual->blue_mask;

              newbuffer[outindex] = r | g | b;

              ++outindex;
            }

          image = XCreateImage(display, vinfo.visual, vinfo.depth, ZPixmap, 0, (char*)newbuffer, width, height, 16, 0);

        }  
       else 
        {
          return NULL;
        }
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
* @fn         int GRPLINUXSCREENX11::GetTaskBarHeight()
* @brief      Get task bar height
* @ingroup    PLATFORM_LINUX
* 
* @return     int : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
int GRPLINUXSCREENX11::GetTaskBarHeight()
{
  int screen              = DefaultScreen(display);    
  int screen_width        = DisplayWidth(display, screen);
  int screen_height       = DisplayHeight(display, screen);

    
  Atom atomworkarea = XInternAtom(display, "_NET_WORKAREA", True);
  if(atomworkarea == None) 
    {
      XTRACE_PRINTCOLOR(XTRACE_COLOR_RED, __L("[Screen X11] Error Atom WORKAREA (Get Taskbar height)"));      
      return 0;
    }

  Atom           actual_type;
  int            actual_format;
  unsigned long  nitems;
  unsigned long  bytes_after;
  unsigned char* data     = nullptr;

  int status = XGetWindowProperty(display, root, atomworkarea, 0, 4 * sizeof(long), False, XA_CARDINAL, &actual_type, &actual_format, &nitems, &bytes_after, &data);
  if(status != Success || !data) 
    {
      XTRACE_PRINTCOLOR(XTRACE_COLOR_RED, __L("[Screen X11] Error XGetWindowProperty (Get Taskbar height)"));     
      return 0;
    }
    
  long*   workarea        = reinterpret_cast<long*>(data);
  int     work_width      = workarea[2];
  int     work_height     = workarea[3];
  int     taskbar_height  = screen_height - work_height;

  XFree(data);  

  return taskbar_height;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool GRPLINUXSCREENX11::ShowDebugNetSupportedPropertys()
* @brief      Show debug net supported propertys
* @ingroup    PLATFORM_LINUX
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPLINUXSCREENX11::ShowDebugNetSupportedPropertys()
{
  // Get the atom for _NET_SUPPORTED
  Atom netsupported = XInternAtom(display, "_NET_SUPPORTED", True);
  if(netsupported == None) 
    {
      XTRACE_PRINTCOLOR(XTRACE_COLOR_RED, __L("[Screen X11] Error NET_SUPPORTED"));          
      return false;
    }

  // Get the _NET_SUPPORTED property from the root window
  Atom            type;
  int             format;
  unsigned long   nitems;
  unsigned long   bytesafter;
  Atom*           atoms = nullptr;

  int status = XGetWindowProperty(display, root, netsupported, 0, 1024, False, XA_ATOM, &type, &format, &nitems, &bytesafter, reinterpret_cast<unsigned char **>(&atoms));
  if(status != Success || type != XA_ATOM || format != 32) 
    {
      XTRACE_PRINTCOLOR(XTRACE_COLOR_RED, __L("[Screen X11] Failed to retrieve _NET_SUPPORTED property"));   

      if(atoms) 
        {
          XFree(atoms);
        }
        
      return 1;
    }

  // Print the list of supported atoms
  XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("[Screen X11] _NET_SUPPORTED Atoms [%d]: "), nitems);

  for(unsigned long c=0; c<nitems; ++c) 
    {
      char* atomname = XGetAtomName(display, atoms[c]);
      if(atomname) 
        {
          XSTRING _atomname;

          _atomname = atomname;

          XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("%s"), _atomname.Get());
          
          XFree(atomname);
        }
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         int GRPLINUXSCREENX11::GetByteOrder()
* @brief      Get byte order
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
* @fn         int GRPLINUXSCREENX11::ErrorHandler(Display* display, XErrorEvent* errorevent)
* @brief      Error handler
* @ingroup    PLATFORM_LINUX
* 
* @param[in]  display : 
* @param[in]  errorevent : 
* 
* @return     int : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
int GRPLINUXSCREENX11::ErrorHandler(Display* display, XErrorEvent* errorevent)
{
  int a=0;
  a++;

  return 0; 
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void GRPLINUXSCREENX11::Clean()
* @brief      Clean the attributes of the class: Default initialize
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

