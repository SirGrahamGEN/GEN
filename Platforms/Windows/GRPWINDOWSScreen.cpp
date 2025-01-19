/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       GRPWINDOWSScreen.cpp
* 
* @class      GRPWINDOWSSCREEN
* @brief      WINDOWS Graphics Screen class
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
#pragma region PRECOMPILATION_DEFINES_INCLUDE

#include "GEN_Defines.h"

#pragma endregion


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES


#include "GRPWINDOWSScreen.h"

#include "GRPFactory.h"
#include "GRPDesktopManager.h"

#include "XTrace.h"
#include "XSystem.h"

#include "MainProcWINDOWS.h"

#include "GRPXEvent.h"
#include "GRPCanvas.h"
#include "GRPBitmap.h"


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
* @fn         GRPWINDOWSSCREEN::GRPWINDOWSSCREEN()
* @brief      Constructor of class
* @ingroup    PLATFORM_WINDOWS
*
* --------------------------------------------------------------------------------------------------------------------*/
GRPWINDOWSSCREEN::GRPWINDOWSSCREEN(): GRPSCREEN()
{
  Clean();

  type = GRPSCREENTYPE_WINDOWS;

  DEVMODE devmode;
  DWORD   currentsettings = ENUM_CURRENT_SETTINGS;
  BOOL    result          = TRUE;

  memset(&devmode, 0, sizeof(DEVMODE));
  devmode.dmSize  = sizeof(DEVMODE);

  result = EnumDisplaySettings(NULL, currentsettings, &devmode);
  if(!result) return;

  SetSize(devmode.dmPelsWidth, devmode.dmPelsHeight);
  SetMaxSize(devmode.dmPelsWidth, devmode.dmPelsHeight);


  GRPRECTINT* rectworkarea = GetWorkRegion();
  if(rectworkarea)
    {
      RECT workarea;

      SystemParametersInfo(SPI_GETWORKAREA, 0, &workarea, 0);

      rectworkarea->x1 = workarea.left;
      rectworkarea->y1 = workarea.top;

      rectworkarea->x2 = workarea.right;
      rectworkarea->y2 = workarea.bottom;
    }

  SetMode(GRPPROPERTYMODE_32_BGRA_8888);

  SetIsBufferInverse(false);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         GRPWINDOWSSCREEN::~GRPWINDOWSSCREEN()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    PLATFORM_WINDOWS
*
* -------------------------------------------------------------------------------------------------------------------*/
GRPWINDOWSSCREEN::~GRPWINDOWSSCREEN()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRPWINDOWSSCREEN::Create(void* handle)
* @brief      Create
* @ingroup    PLATFORM_WINDOWS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPWINDOWSSCREEN::Create(bool show)
{
  if(!Create_Window(show)) 
    {
      return false;
    }

  GRPSCREEN::GetListScreens()->Add((void*)hwnd, this);

  return GRPSCREEN::Create(show);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRPWINDOWSSCREEN::Update()
* @brief      Update
* @ingroup    PLATFORM_WINDOWS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPWINDOWSSCREEN::Update()
{
  #ifdef GRP_OPENGL_ACTIVE

  if(!hdc) return false;

  SwapBuffers(hdc);

  #endif


  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRPWINDOWSSCREEN::Update(GRPCANVAS* canvas)
* @brief      Update
* @ingroup    PLATFORM_WINDOWS
*
* @param[in]  canvas : handle of canvas
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPWINDOWSSCREEN::Update(GRPCANVAS* canvas)
{
  #ifndef GRP_OPENGL_ACTIVE

  if(!hdc)    
    {
      return false;
    }

  if(!canvas) 
    {
      return false;
    }

  
  SetDIBitsToDevice(hdc, 0, 0, width  ,
                               height ,
                               0,0,0  ,
                               height ,
                               canvas->Buffer_Get() ,
                               &hinfo ,
                               DIB_RGB_COLORS);     
  
  return true;

  #else

  return false;

  #endif
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool GRPWINDOWSSCREEN::UpdateTransparent(GRPCANVAS* canvas)
* @brief      Update transparent
* @ingroup    PLATFORM_WINDOWS
* 
* @param[in]  canvas : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPWINDOWSSCREEN::UpdateTransparent(GRPCANVAS* canvas)
{
  #ifndef GRP_OPENGL_ACTIVE

  if(!hdc) 
    {
      return false;
    }

  if(!canvas) 
    {
      return false;
    }

  HDC     hdcscreen = GetDC(NULL);
  HDC     hdcmem    = CreateCompatibleDC(hdcscreen);
  HBITMAP hbmmem    = CreateCompatibleBitmap(hdcscreen, (LONG)width, (LONG)height);
  HBITMAP hbmold    = (HBITMAP)SelectObject(hdcmem, hbmmem);

  RECT    rect      = { 0, 0, (LONG)width, (LONG)height };
  HBRUSH  hbrush    = CreateSolidBrush(RGB(0, 0, 0));

  FillRect(hdcmem, &rect, hbrush);
  DeleteObject(hbrush);

  SetBkMode(hdcmem, TRANSPARENT);
 
  // XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("[Screen Windows] Update Transparent (Equal)  (%04d,%04d)  Bitxpixel (%d)"), width, height, GetBitsperPixel());
     
  SetDIBitsToDevice(hdcmem, 0, 0, width  ,
                                  height ,
                                  0,0,0  ,
                                  height ,
                                  canvas->Buffer_Get() ,
                                  &hinfo ,
                                  DIB_RGB_COLORS);     
 
  POINT         ptsrc   = { 0, 0 };
  SIZE          sizewnd = { (LONG)width, (LONG)height };
  BLENDFUNCTION blend   = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };
  POINT         ptdst   = { (LONG)positionx, (LONG)positiony };

  UpdateLayeredWindow(hwnd, hdcscreen, &ptdst, &sizewnd, hdcmem, &ptsrc, 0, &blend, ULW_ALPHA);
 
  SelectObject(hdcmem, hbmold);
  DeleteObject(hbmmem);
  DeleteDC(hdcmem);
  ReleaseDC(NULL, hdcscreen);

  return true;

  #else

  return false;

  #endif
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRPWINDOWSSCREEN::Delete()
* @brief      Delete
* @ingroup    PLATFORM_WINDOWS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPWINDOWSSCREEN::Delete()
{
  if(Style_Is(GRPSCREENSTYLE_FULLSCREEN)) 
    {
      ChangeDisplaySettings(NULL,0);
    }

  if(hdc)
    {
      ReleaseDC(hwnd, hdc);
      hdc  = NULL;
    }

  if(hwnd) 
    { 
      CloseWindow(hwnd);
      DestroyWindow(hwnd);

      hwnd = NULL;

      UnregisterClassA((LPCSTR)GRPWINDOWSSCREEN_NAMECLASS, hinstance);
    }

  return GRPSCREEN::Delete();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool GRPWINDOWSSCREEN::Get_Position(int& x, int& y)
* @brief      Get position
* @ingroup    PLATFORM_WINDOWS
* 
* @param[in]  x : 
* @param[in]  y : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPWINDOWSSCREEN::Get_Position(int& x, int& y)
{
  RECT    rect;

  GetWindowRect(hwnd, &rect);

  x = rect.left;  
  y = rect.top;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool GRPWINDOWSSCREEN::Set_Position(int x, int y)
* @brief      Set position
* @ingroup    PLATFORM_WINDOWS
* 
* @param[in]  x : 
* @param[in]  y : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPWINDOWSSCREEN::Set_Position(int x, int y)
{
  RECT    rect;
  XDWORD  style;

  GetClientRect(hwnd, &rect);

  int width   = rect.right  - rect.left; 
  int height  = rect.bottom - rect.top;  

  rect.right  = x;  
  rect.left   = x + width;

  rect.top    = y;  
  rect.bottom = y + height;

  style = GetWindowLong(hwnd, GWL_STYLE);

  SetPosition(x, y);

  AdjustWindowRect(&rect, style, false);

  SetWindowPos(hwnd,NULL, positionx, positiony, (rect.right-rect.left), (rect.bottom-rect.top)  , SWP_NOSIZE | SWP_NOZORDER);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRPWINDOWSSCREEN::Resize(int width, int height)
* @brief      Resize
* @ingroup    PLATFORM_WINDOWS
*
* @param[in]  width : new width of the screen
* @param[in]  height : new height of the screen
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPWINDOWSSCREEN::Resize(int width, int height)
{
  RECT    rect;
  XDWORD  style;

  GetClientRect(hwnd, &rect);

  rect.right  = rect.left + width;    //+ 16;
  rect.bottom = rect.top  + height;   //+ 16;

  style = GetWindowLong(hwnd, GWL_STYLE);

  AdjustWindowRect(&rect,style,false);

  SetWindowPos(hwnd,NULL, positionx, positiony, (rect.right-rect.left), (rect.bottom-rect.top) , SWP_NOMOVE | SWP_NOZORDER);

  return UpdateSize(width, height);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRPWINDOWSSCREEN::Show(bool active)
* @brief      Show
* @ingroup    PLATFORM_WINDOWS
*
* @param[in]  active :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPWINDOWSSCREEN::Show(bool active)
{
  if(!hwnd) return false;

  ::ShowWindow(hwnd, (active?SW_SHOW:SW_HIDE));

  isshow  = active;

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRPWINDOWSSCREEN::ShowCursor(bool active)
* @brief      Show cursor
* @ingroup    PLATFORM_WINDOWS
*
* @param[in]  active :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPWINDOWSSCREEN::ShowCursor(bool active)
{
  if(!hwnd) return false;

  return ::ShowCursor(active?TRUE:FALSE)?true:false;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void* GRPWINDOWSSCREEN::GetHandle()
* @brief      Get handle
* @ingroup    PLATFORM_WINDOWS
*
* @return     void* :
*
* --------------------------------------------------------------------------------------------------------------------*/
void* GRPWINDOWSSCREEN::GetHandle()
{
  return (void*)hwnd;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void GRPWINDOWSSCREEN::SetHandle(XDWORD handle_window)
* @brief      Set handle
* @ingroup    PLATFORM_WINDOWS
* 
* @param[in]  handle_window : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void GRPWINDOWSSCREEN::SetHandle(void* handle_window)
{
  this->hwnd = (HWND)handle_window;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool GRPWINDOWSSCREEN::Set_Focus()
* @brief      Set focus
* @ingroup    PLATFORM_WINDOWS
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPWINDOWSSCREEN::Set_Focus()
{
  if(!hwnd)
    {
      return false;
    }

  if(!SetForegroundWindow(hwnd))
    {
      return false;
    }

  AttachThreadInput(GetCurrentThreadId(), GetWindowThreadProcessId(GetAncestor(hwnd, GA_ROOT), NULL), TRUE);

  SetFocus(hwnd);
    
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool GRPWINDOWSSCREEN::Minimize(bool active)
* @brief      Minimize
* @ingroup    PLATFORM_WINDOWS
* 
* @param[in]  active : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPWINDOWSSCREEN::Minimize(bool active)
{
  if(!hwnd)
    {
      return false;
    }

  return ShowWindow(hwnd, active?SW_SHOWMINIMIZED:SW_NORMAL)?true:false; 
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool GRPWINDOWSSCREEN::Maximize(bool active)
* @brief      Maximize
* @ingroup    PLATFORM_WINDOWS
* 
* @param[in]  active : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPWINDOWSSCREEN::Maximize(bool active)
{
  if(!hwnd)
    {
      return false;
    }

  return ShowWindow(hwnd, active?SW_SHOWMAXIMIZED:SW_NORMAL)?true:false; 
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         GRPBITMAP* GRPWINDOWSSCREEN::CaptureContent(GRPRECTINT* rect, void* handle_window)
* @brief      Capture content
* @ingroup    PLATFORM_WINDOWS
* 
* @param[in]  rect : 
* @param[in]  handle_window : 
* 
* @return     GRPBITMAP* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
GRPBITMAP* GRPWINDOWSSCREEN::CaptureContent(GRPRECTINT* rect, void* handle_window)
{
  XBUFFER xbuffer;
  HDC     hdcsource = GetDC(handle_window?(HWND)handle_window:hwnd);
  HDC     hdcmemory = CreateCompatibleDC(hdcsource);
  int     x         = 0;
  int     y         = 0;
  int     cx        = GetWidth();
  int     cy        = GetHeight();  
  bool    status    = false;

  if(!hdcsource)
    {
      return NULL;  
    }

  if(!hdcmemory)
    {
      DeleteDC(hdcsource);
      return NULL;        
    }

  if(rect)
    {
      x         = rect->x1;
      y         = rect->y1;
      cx        = (rect->x2 - rect->x1);
      cy        = (rect->y2 - rect->y1);
    }  

  HBITMAP hbitmap     = CreateCompatibleBitmap(hdcsource, cx, cy);
  HBITMAP hbitmapold  = (HBITMAP)SelectObject(hdcmemory, hbitmap);
  BITMAP  bitmap;

  BitBlt(hdcmemory, 0, 0, cx, cy, hdcsource, x, y, SRCCOPY);
  hbitmap = (HBITMAP)SelectObject(hdcmemory, hbitmapold);

  DeleteDC(hdcsource);
  DeleteDC(hdcmemory);

  GetObject(hbitmap, sizeof(bitmap), (LPSTR)&bitmap);

  HDC dcbitmap = CreateCompatibleDC(NULL);
  SelectObject(dcbitmap, hbitmap);

  BITMAPINFO bmpinfo;

  bmpinfo.bmiHeader.biSize         = sizeof(BITMAPINFOHEADER);
  bmpinfo.bmiHeader.biWidth        = bitmap.bmWidth;
  bmpinfo.bmiHeader.biHeight       = bitmap.bmHeight;
  bmpinfo.bmiHeader.biPlanes       = bitmap.bmPlanes;
  bmpinfo.bmiHeader.biBitCount     = bitmap.bmBitsPixel;
  bmpinfo.bmiHeader.biCompression  = BI_RGB;
  bmpinfo.bmiHeader.biSizeImage    = 0;
  bmpinfo.bmiHeader.biClrImportant = 0;
  bmpinfo.bmiHeader.biClrUsed      = 0;

  GRPBITMAP* grpbitmap = GRPFACTORY::GetInstance().CreateBitmap(bitmap.bmWidth, bitmap.bmHeight, GRPPROPERTYMODE_32_BGRA_8888);
  if(grpbitmap)
    {
      status = GetDIBits(dcbitmap, hbitmap, 0, bitmap.bmHeight, grpbitmap->GetBuffer(), &bmpinfo, DIB_RGB_COLORS)?true:false;

      XDWORD* buffer = (XDWORD*)grpbitmap->GetBuffer();
      for(XDWORD c=0; c<(grpbitmap->GetBufferSize()/sizeof(XDWORD)); c++)
        {
          (*buffer) |= 0xFF000000;
          buffer++;
        }
    }

  if(!status)
    {
      delete grpbitmap;
      grpbitmap = NULL;
    }

  return grpbitmap;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void* GRPWINDOWSSCREEN::GetDesktopHandle()
* @brief      Get desktop handle
* @ingroup    PLATFORM_WINDOWS
* 
* @return     void* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void* GRPWINDOWSSCREEN::GetDesktopHandle()
{
  HANDLE hwnd = GetDesktopWindow();

  return (void*)hwnd;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void* GRPWINDOWSSCREEN::GetShellHandle()
* @brief      Get shell handle
* @ingroup    PLATFORM_WINDOWS
* 
* @return     void* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void* GRPWINDOWSSCREEN::GetShellHandle()
{
  HANDLE hwnd = GetShellWindow();

  return (void*)hwnd;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void* GRPWINDOWSSCREEN::GetHDC()
* @brief      Get HDC
* @ingroup    PLATFORM_WINDOWS
*
* @return     void* :
*
* --------------------------------------------------------------------------------------------------------------------*/
void* GRPWINDOWSSCREEN::GetHDC()
{
  return (void*)hdc;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void GRPWINDOWSSCREEN::SetHDC(HDC hdc)
* @brief      Set HDC
* @ingroup    PLATFORM_WINDOWS
*
* @param[in]  hdc :
*
* --------------------------------------------------------------------------------------------------------------------*/
void GRPWINDOWSSCREEN::SetHDC(HDC hdc)
{
  this->hdc = hdc;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         BITMAPINFO* GRPWINDOWSSCREEN::GetHInfo()
* @brief      Get H info
* @ingroup    PLATFORM_WINDOWS
*
* @return     BITMAPINFO* : 
*
* --------------------------------------------------------------------------------------------------------------------*/
BITMAPINFO* GRPWINDOWSSCREEN::GetHInfo()
{
  return &hinfo;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool GRPWINDOWSSCREEN::IsBlockClose()
* @brief      Is block close
* @ingroup    PLATFORM_WINDOWS
*
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool GRPWINDOWSSCREEN::IsBlockClose()
{
  return isblockclose;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void GRPWINDOWSSCREEN::SetIsBlockClose(bool activated)
* @brief      Set is block close
* @ingroup    PLATFORM_WINDOWS
*
* @param[in]  activated : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void GRPWINDOWSSCREEN::SetIsBlockClose(bool activated)
{
  isblockclose = activated;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         int GRPWINDOWSSCREEN::GetTaskbarHeight()
* @brief      Get taskbar height
* @ingroup    PLATFORM_WINDOWS
* 
* @return     int : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
int GRPWINDOWSSCREEN::GetTaskbarHeight()
{
  int screenWidth = GetSystemMetrics(SM_CXSCREEN);
  int screenHeight = GetSystemMetrics(SM_CYSCREEN);

  RECT workArea;
  SystemParametersInfo(SPI_GETWORKAREA, 0, &workArea, 0);

  
  int taskbarHeight = screenHeight - (workArea.bottom - workArea.top);

  return taskbarHeight;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRPWINDOWSSCREEN::Create_Window(void* handle)
* @brief      Create window
* @ingroup    PLATFORM_WINDOWS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPWINDOWSSCREEN::Create_Window(bool show)
{
  //-----------------------------------------------------------------------------------------------------

  if(hwnd) 
    {
      return false;
    }

  hinstance = (HINSTANCE)mainprocwindows.GetHandle();

  //-----------------------------------------------------------------------------------------------------

  classname               = GRPWINDOWSSCREEN_NAMECLASS;
  title                   = __L(" ");

  wndclass.cbSize         = sizeof(wndclass);
  wndclass.style          = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
  wndclass.lpfnWndProc    = BaseWndProc;
  wndclass.cbClsExtra     = 0;
  wndclass.cbWndExtra     = 0;
  wndclass.hInstance      = NULL;
  wndclass.hIcon          = NULL;
  wndclass.hCursor        = LoadCursor(NULL, IDC_ARROW);
  wndclass.hbrBackground  = (HBRUSH)GetStockObject(BLACK_BRUSH);
  wndclass.lpszMenuName   = NULL;
  wndclass.hIconSm        = NULL;

  wndclass.lpszClassName  = classname.Get();
  wndclass.hInstance      = hinstance;

  RegisterClassEx(&wndclass);

  //-----------------------------------------------------------------------------------------------------

  GRPRECTINT* alldesktoprect  = NULL;
  int         nscreen         = GetDesktopScreenSelected(); 
  DWORD       _exstyle        = 0;
  DWORD       _style          = 0;
  int         posx            = 0;
  int         posy            = 0;  

  if(nscreen == GRPSCREENTYPE_DESKTOP_ALL)
    {
      alldesktoprect = GetDesktopManager()->GetDesktopMonitors()->GetCombinedRect(); 
    }
   else 
    {
      alldesktoprect = GetDesktopManager()->GetDesktopMonitors()->GetMonitorsRects()->Get(nscreen);
    }
  
  if(!alldesktoprect)
    {
      return false;          
    }            

  if(Styles_IsFullScreen())          
    {
      if(Style_Is(GRPSCREENSTYLE_FULLSCREEN_ADJUSTRESOLUTION))
        {
          DEVMODE devmode;

          memset(&devmode, 0, sizeof(DEVMODE));

          devmode.dmSize       = sizeof(DEVMODE);
          devmode.dmPelsWidth  = width;
          devmode.dmPelsHeight = height;
          devmode.dmBitsPerPel = GetBitsperPixel();
          devmode.dmFields     = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

          LONG status = ChangeDisplaySettings(&devmode, CDS_FULLSCREEN);

          //XTRACE_PRINTCOLOR(1, __L("[Screen Windows] ChangeDisplaySettings Status: %ld"), status);

          if(status != DISP_CHANGE_SUCCESSFUL) 
            {
              return NULL;
            }
        }
       else 
        {                         
          _exstyle  = WS_EX_TOPMOST | WS_EX_TOOLWINDOW;
          _style    = WS_POPUP;

          width  = alldesktoprect->GetWidth();    
          height = alldesktoprect->GetHeight(); 
   
          posx   = alldesktoprect->x1;
          posy   = alldesktoprect->y1;   
        }

      if(Style_Is(GRPSCREENSTYLE_HEIGHTWITHOUTTASKBAR))
        {
          height -= GetTaskbarHeight();
        }  

      if(Style_Is(GRPSCREENSTYLE_TRANSPARENT))
        {
          _exstyle |= WS_EX_LAYERED;
        }

      if(Style_Is(GRPSCREENSTYLE_NOICONTASKBAR))
        {
          _exstyle |= WS_EX_TOOLWINDOW;
        }

      hwnd = CreateWindowEx(_exstyle          ,
                            classname.Get()   ,
                            NULL              ,
                            _style            ,
                            posx, posy        ,
                            width             ,
                            height            ,
                            NULL              ,
                            NULL              ,
                            hinstance         ,
                            (void*)this);

      if(!hwnd) 
        {
          return false;
        }

      SetPosition(posx, posy);  
      SetSize(width ,height);
      SetMaxSize(width ,height);              
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
   
      if(Style_Is(GRPSCREENSTYLE_NOWINDOWICONS))
        {
          _style |= WS_OVERLAPPED;  // _exstyle |= WS_EX_TOOLWINDOW;
        }
       else _style |= WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX; 


      if(Style_Is(GRPSCREENSTYLE_ONTOP))
        {
          _exstyle |= WS_EX_TOPMOST;
        }

      if(Style_Is(GRPSCREENSTYLE_TRANSPARENT))
        {
          _exstyle |= WS_EX_LAYERED;             
          _style   |= WS_POPUP;
        }
       else
        {
          if(Style_Is(GRPSCREENSTYLE_TITLE))
            {
              _style |= WS_OVERLAPPED;
            }
           else
            {
              _style |= WS_POPUP;
            }
        }

      if(Style_Is(GRPSCREENSTYLE_NOICONTASKBAR))
        {
          _exstyle |= WS_EX_TOOLWINDOW;
        }

      hwnd = CreateWindowEx(_exstyle          ,
                            classname.Get()   ,
                            GetTitle()->Get() ,
                            _style            ,
                            posx              , 
                            posy              ,
                            width ,height     ,
                            NULL              ,
                            NULL              ,
                            hinstance         ,
                            (void*)this);

      if(!hwnd) 
        {
          return false;
        }

      // XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("[Screen Windows] Part 1 Ini: x=%04d, y=%04d (%04d,%04d)  Bitxpixel (%d)"), posx, posy, width, height, GetBitsperPixel());
       
      RECT rect;

      GetClientRect(hwnd, &rect);

      rect.right  = rect.left + width;    //+ 16;
      rect.bottom = rect.top  + height;   //+ 16;

      AdjustWindowRect(&rect, GetWindowLong(hwnd, GWL_STYLE), false);
    
      SetWindowPos(hwnd, NULL, posx , posy, (rect.right-rect.left), (rect.bottom-rect.top) , SWP_NOMOVE | SWP_NOZORDER);
      
      POINT point = { 0, 0}; 

      ClientToScreen(hwnd, (LPPOINT)&point);  

      if(Style_Is(GRPSCREENSTYLE_HEIGHTWITHOUTTASKBAR))
        {
          point.y -= GetTaskbarHeight();
        }  

      point.x  += alldesktoprect->x1;
      point.y  += alldesktoprect->y1;   
    
      SetPosition(point.x,  point.y);
      Set_Position(point.x,  point.y);

      SetSize(width ,height);
      SetMaxSize(width ,height);
    }

  // XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("[Screen Windows] Part 2 Ini: x=%04d, y=%04d (%04d,%04d)  Bitxpixel (%d)"), posx, posy, width, height, GetBitsperPixel());

  if(show)
    {
      if(!Show(show)) return false;
    }

  /*
  if(!SetForegroundWindow(hwnd))
    {
      XTRACE_PRINTCOLOR(4, __L("[Screen Windows] SetForegroundWindow Window: Error!"));
    }
  */

  if(!SetFocus(hwnd))
    {
      //XTRACE_PRINTCOLOR(4, __L("[Screen Windows] SetFocus Window: Error!"));
      return false;
    } 
    

  hdc = GetDC(hwnd);
  if(!hdc)
    {
      //XTRACE_PRINTCOLOR(4, __L("[Screen Windows] GetDC Window: Error!"));
      return false;
    }


  #ifndef OPENGL_INFO
  memset(&hinfo,0,sizeof(BITMAPINFO));

  hinfo.bmiHeader.biSize          = sizeof(BITMAPINFOHEADER);
  hinfo.bmiHeader.biWidth         = width;
  hinfo.bmiHeader.biHeight        = height;
  hinfo.bmiHeader.biPlanes        = 1;
  hinfo.bmiHeader.biBitCount      = GetBitsperPixel();
  hinfo.bmiHeader.biCompression   = BI_RGB;
  hinfo.bmiHeader.biSizeImage     = (XDWORD)(hinfo.bmiHeader.biWidth*hinfo.bmiHeader.biHeight*hinfo.bmiHeader.biBitCount)/8;
  #endif

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         LRESULT CALLBACK GRPWINDOWSSCREEN::BaseWndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
* @brief      Base wnd proc
* @ingroup    PLATFORM_WINDOWS
*
* @param[in]  hwnd : 
* @param[in]  msg : 
* @param[in]  wparam : 
* @param[in]  lparam : 
* 
* @return     LRESULT : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
LRESULT CALLBACK GRPWINDOWSSCREEN::BaseWndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  switch(msg)
    {
      case WM_SYSCOMMAND      :  switch(wparam)
                                  {
                                    case SC_CLOSE         : break;
                                    case SC_SCREENSAVE    :
                                    case SC_MONITORPOWER  : return 0;
                                  }
                                break;

      case WM_ENDSESSION      : break;

      case WM_MOVE            : { GRPWINDOWSSCREEN* screen =  (GRPWINDOWSSCREEN*)GRPSCREEN::GetListScreens()->Get((void*)hwnd);
                                  if(screen)
                                    {
                                      screen->SetPosition((int)(short) LOWORD(lparam),(int)(short) HIWORD(lparam));

                                      //XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("[Windows] move: x=%04d, y=%04d (%04d,%04d)"), screen->GetPositionX(), screen->GetPositionY(), screen->GetWidth(), screen->GetHeight());
                                    }
                                }
                                break;

      case WM_CLOSE           : { GRPWINDOWSSCREEN* screen = (GRPWINDOWSSCREEN*)GRPSCREEN::GetListScreens()->Get((void*)hwnd);
                                  if(screen)
                                    {
                                      if(screen->IsBlockClose())
                                        {
                                          return 0;
                                        }
                                    }              
                                }  
                                break;

      case WM_PAINT           : break;

      case WM_DESTROY         : break;

      case WM_POWERBROADCAST  : //Computer is suspending
                                if(wparam == PBT_APMSUSPEND)
                                  {
                                    #ifdef GRP_MAINPROCCTRL_ACTIVE
                                    if(mainprocwindows.GetAppMain())
                                      {
                                        if(mainprocwindows.GetAppMain()->GetApplication()) mainprocwindows.GetAppMain()->GetApplication()->SetSystemChangeStatus(XSYSTEM_CHANGESTATUSTYPE_SUSPEND);
                                      }
                                    #endif
                                  }

                                break;

      case WM_QUERYENDSESSION : //Computer is shutting down
                                if(lparam == 0)
                                  {
                                    #ifdef GRP_MAINPROCCTRL_ACTIVE
                                    if(mainprocwindows.GetAppMain())
                                      {
                                        if(mainprocwindows.GetAppMain()->GetApplication()) mainprocwindows.GetAppMain()->GetApplication()->SetSystemChangeStatus(XSYSTEM_CHANGESTATUSTYPE_REBOOT);
                                      }
                                    #endif
                                  }

                                //User is logging off
                                if((lparam & ENDSESSION_LOGOFF) == ENDSESSION_LOGOFF)
                                  {
                                    #ifdef GRP_MAINPROCCTRL_ACTIVE
                                    if(mainprocwindows.GetAppMain())
                                      {
                                        if(mainprocwindows.GetAppMain()->GetApplication()) mainprocwindows.GetAppMain()->GetApplication()->SetSystemChangeStatus(XSYSTEM_CHANGESTATUSTYPE_SESSION_LOGOFF);
                                      }
                                    #endif
                                  }

                                break;
    }

  return DefWindowProc(hwnd, msg, wparam, lparam);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void GRPWINDOWSSCREEN::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    PLATFORM_WINDOWS
*
* --------------------------------------------------------------------------------------------------------------------*/
void GRPWINDOWSSCREEN::Clean()
{
  hinstance       = NULL;
  hwnd            = NULL;
  hdc             = NULL;
}


#pragma endregion
