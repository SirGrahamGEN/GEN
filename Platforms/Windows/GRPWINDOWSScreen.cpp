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

/*---- PRECOMPILATION INCLUDES ----------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_INCLUDES

#include "GEN_Defines.h"

#pragma endregion


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES


#include "GRPWINDOWSScreen.h"

#include "XTrace.h"
#include "XSystem.h"

#include "MainProcWINDOWS.h"

#include "GRPXEvent.h"
#include "GRPCanvas.h"
#include "GRPBitmap.h"

#include "XMemory_Control.h"


#pragma endregion


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

XMAP<HWND, GRPWINDOWSSCREEN*>  GRPWINDOWSSCREEN::listscreens;

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         GRPWINDOWSSCREEN::GRPWINDOWSSCREEN()
* @brief      Constructor
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

  SetMode(GRPPROPERTYMODE_32_BGRA_8888);

  SetIsBufferInverse(false);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         GRPWINDOWSSCREEN::~GRPWINDOWSSCREEN()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    PLATFORM_WINDOWS
*
* --------------------------------------------------------------------------------------------------------------------*/
GRPWINDOWSSCREEN::~GRPWINDOWSSCREEN()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRPWINDOWSSCREEN::Create(void* handle)
* @brief      Create screen
* @ingroup    PLATFORM_WINDOWS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPWINDOWSSCREEN::Create(bool show)
{
  if(!Create_Window(show)) return false;

  CreateBuffers();

  listscreens.Add(hwnd, this);

  return GRPSCREEN::Create(show);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRPWINDOWSSCREEN::Update()
* @brief      Update Screen
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

  if(!hdc)    return false;
  if(!canvas) return false;

  if(IsEqualSizeTo(canvas) == ISEQUAL)
    {      
      SetDIBitsToDevice(hdc, 0, 0, width  ,
                                   height ,
                                   0,0,0  ,
                                   height ,
                                   canvas->GetBuffer() ,
                                   &hinfo ,
                                   DIB_RGB_COLORS);     
    }
   else
    {
      if(!buffer) return false;

      canvas->CopyBufferRenderToScreen(this);

      SetDIBitsToDevice(hdc, 0, 0, width  ,
                                   height ,
                                   0,0,0  ,
                                   height ,
                                   buffer ,
                                  &hinfo ,
                                   DIB_RGB_COLORS);

    }


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
  DeleteBuffers();

  if(IsFullScreen()) ChangeDisplaySettings(NULL,0);

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

  isactive = false;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool GRPWINDOWSSCREEN::Get_Position(int& x, int& y)
* @brief      Get_Position
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
* @brief      Set_Position
* @ingroup    PLATFORM_WINDOWS
* 
* @param[in]  x : 
* @param[in]  y : 
* @param[in]  sizex : 
* @param[in]  sizey : 
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
* @brief      Resize Windows
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
* @brief      ShowCursor
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
* @fn         bool GRPWINDOWSSCREEN::ShowTopMost(bool active)
* @brief      ShowTopMost
* @ingroup    PLATFORM_WINDOWS
*
* @param[in]  active :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPWINDOWSSCREEN::ShowTopMost(bool active)
{
  if(!hwnd) return false;

  ::SetWindowPos(hwnd, (active ? HWND_TOPMOST : HWND_NOTOPMOST), 0, 0 , 0 , 0, SWP_NOMOVE | SWP_NOSIZE);

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void* GRPWINDOWSSCREEN::GetHandle()
* @brief      GetHandle
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
* @brief      SetHandle
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
* @brief      Set_Focus
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
* @fn         GRPBITMAP* GRPWINDOWSSCREEN::CaptureContent()
* @brief      CaptureContent
* @ingroup    PLATFORM_WINDOWS
* 
* @return     GRPBITMAP* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
GRPBITMAP* GRPWINDOWSSCREEN::CaptureContent()
{
  XBUFFER xbuffer;
  HDC     hdcsource = GetDC(hwnd);
  HDC     hdcmemory = CreateCompatibleDC(hdcsource);
  int     capx      = GetWidth();
  int     capy      = GetHeight();
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

  HBITMAP hbitmap     = CreateCompatibleBitmap(hdcsource, capx, capy);
  HBITMAP hbitmapold  = (HBITMAP)SelectObject(hdcmemory, hbitmap);
  BITMAP  bitmap;

  BitBlt(hdcmemory, 0, 0, capx, capy, hdcsource, 0, 0, SRCCOPY);
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
* @fn         void* GRPWINDOWSSCREEN::GetHDC()
* @brief      GetHDC
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
* @brief      SetHDC
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
* @brief      GetHInfo
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
* @brief      IsBlockClose
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
* @brief      SetIsBlockClose
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
* @fn         XMAP<HWND, GRPWINDOWSSCREEN*>* GRPWINDOWSSCREEN::GetListScreens()
* @brief      GetListScreens
* @ingroup    PLATFORM_WINDOWS
*
* @return     XMAP<HWND, GRPWINDOWSSCREEN*>* : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
XMAP<HWND, GRPWINDOWSSCREEN*>* GRPWINDOWSSCREEN::GetListScreens()
{
  return &listscreens;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void GRPWINDOWSSCREEN::Clean()
* @brief      Clean the attributes of the class: Default initialice
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


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRPWINDOWSSCREEN::Create_Window(void* handle)
* @brief      CreateWindow
* @ingroup    PLATFORM_WINDOWS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPWINDOWSSCREEN::Create_Window(bool show)
{
  // need to move actual windows creation code to it's own function
  // add a function to destroy the window

  if(hwnd) return false;

  hinstance = (HINSTANCE)mainprocwindows.GetHandle();

  //-----------------------------------------------------------------------------------------------------

  classname               = GRPWINDOWSSCREEN_NAMECLASS;
  title                   = __L(" ");

  wndclass.cbSize         = sizeof(wndclass);
  wndclass.style          = CS_HREDRAW | CS_VREDRAW| CS_OWNDC;
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
       
  if(IsFullScreen())
    {
      DEVMODE devmode;

      memset(&devmode, 0, sizeof(DEVMODE));

      devmode.dmSize       = sizeof(DEVMODE);
      devmode.dmPelsWidth  = width;
      devmode.dmPelsHeight = height;
      devmode.dmBitsPerPel = GetBitsperPixel();
      devmode.dmFields     = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

      LONG status = ChangeDisplaySettings(&devmode, CDS_FULLSCREEN);

      XTRACE_PRINTCOLOR(1, __L("ChangeDisplaySettings Status: %ld"), status);

      if(status != DISP_CHANGE_SUCCESSFUL) return NULL;

      hwnd = CreateWindow(classname.Get()       ,
                          NULL                  ,
                          WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP ,
                          0,0                   ,
                          width,height          ,
                          NULL                  ,
                          NULL                  ,
                          hinstance             ,
                          (void*)this);

      if(!hwnd) return false;
    }
    else
    {
      RECT    rect;
      XDWORD  style;

      GetClientRect(GetDesktopWindow(), &rect);

      //SystemParametersInfo(SPI_GETWORKAREA, 0, &rect, 0);
     
      if(positionx == GRPPROPERTYMODE_SCREEN_CENTER) positionx = (rect.right - width)/2;
      if(positiony == GRPPROPERTYMODE_SCREEN_CENTER) positiony = (rect.bottom- height)/2;



      //rect.right  = (rect.right - width)/2;
      //rect.bottom = (rect.bottom- height)/2;

      hwnd = CreateWindowEx(0                                 ,
                            classname.Get()                   ,
                            NULL                              ,
                            HasTitle()?WS_OVERLAPPED:WS_POPUP ,
                            positionx, positiony              ,
                            width ,height                     ,
                            NULL                              ,
                            NULL                              ,
                            hinstance                         ,
                            (void*)this);

      if(!hwnd) return false;


      GetClientRect(hwnd, &rect);

      rect.right  = rect.left + width;    //+ 16;
      rect.bottom = rect.top  + height;   //+ 16;

      style = GetWindowLong(hwnd, GWL_STYLE);

      AdjustWindowRect(&rect, style, false);

      SetWindowPos(hwnd, NULL, positionx, positiony, (rect.right-rect.left), (rect.bottom-rect.top) , SWP_NOMOVE | SWP_NOZORDER);
      GetClientRect(hwnd, &rect);
    }

  if(show)
    {
      if(!Show(show)) return false;
    }

  if(!SetForegroundWindow(hwnd))
    {
      XTRACE_PRINTCOLOR(4, __L("SetForegroundWindow Window: Error!"));
    }

  if(!SetFocus(hwnd))
    {
      XTRACE_PRINTCOLOR(4, __L("SetFocus Window: Error!"));
      return false;
    } 
    

  hdc = GetDC(hwnd);
  if(!hdc)
    {
      XTRACE_PRINTCOLOR(4, __L("GetDC Window: Error!"));
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
* @brief      BaseWndProc
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

      case WM_CLOSE           : { GRPWINDOWSSCREEN* screen = GRPWINDOWSSCREEN::GetListScreens()->Get(hwnd);
                                  if(screen)
                                    {
                                      if(screen->IsBlockClose())
                                        {
                                          return 0;
                                        }
                                    }              
                                }  
                                break;

      case WM_DESTROY         : { int a=0;
                                  a++;
                                }
                                break;

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


#pragma endregion





