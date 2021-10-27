/**-------------------------------------------------------------------------------------------------------------------
*
* @file       GRPWINDOWSScreen.cpp
*
* @class      GRPWINDOWSSCREEN
* @brief      WINDOWS Graphics Screen class
* @ingroup    PLATFORM_WINDOWS
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




#include "XTrace.h"
#include "XSystem.h"

//#ifdef GRP_MAINPROCCTRL_ACTIVE
#include "MainProcWINDOWS.h"
//#include "APPBase.h"
//#endif



#include "GRPXEvent.h"
#include "GRPCanvas.h"
#include "GRPWINDOWSScreen.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         GRPWINDOWSSCREEN::GRPWINDOWSSCREEN()
* @brief      Constructor
* @ingroup    PLATFORM_WINDOWS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
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

 /*
  HDC hscreen = GetDC(NULL);

  double hpixelsperinch = GetDeviceCaps(hscreen, LOGPIXELSX);
  double vpixelsperinch = GetDeviceCaps(hscreen, LOGPIXELSY);

  ReleaseDC(NULL, hscreen);


  HDC hscreen2 = GetDC(NULL);

  double hnpixels = GetDeviceCaps(hscreen2, HORZRES);
  double vnpixels = GetDeviceCaps(hscreen2, VERTRES);

  ReleaseDC(NULL, hscreen2);
*/

}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         GRPWINDOWSSCREEN::~GRPWINDOWSSCREEN()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    PLATFORM_WINDOWS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
GRPWINDOWSSCREEN::~GRPWINDOWSSCREEN()
{
  //Delete();

  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRPWINDOWSSCREEN::Create(void* handle)
* @brief      Create screen
* @ingroup    PLATFORM_WINDOWS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool GRPWINDOWSSCREEN::Create(bool show)
{
  if(!Create_Window(show)) return false;

  CreateBuffers();

  return GRPSCREEN::Create(show);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRPWINDOWSSCREEN::Update()
* @brief      Update Screen
* @ingroup    PLATFORM_WINDOWS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
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
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  canvas : handle of canvas
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
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
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
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
* @fn         bool GRPWINDOWSSCREEN::Resize(int width, int height)
* @brief      Resize Windows
* @ingroup    PLATFORM_WINDOWS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  width : new width of the screen
* @param[in]  height : new height of the screen
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool GRPWINDOWSSCREEN::Resize(int width, int height)
{
  RECT   rect;
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
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  active :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
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
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  active :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
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
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  active :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
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
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     void* :
*
*---------------------------------------------------------------------------------------------------------------------*/
void* GRPWINDOWSSCREEN::GetHandle()
{
  return (void*)hwnd;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void GRPWINDOWSSCREEN::SetHandle(HWND hwnd)
* @brief      SetHandle
* @ingroup    PLATFORM_WINDOWS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  hwnd :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void GRPWINDOWSSCREEN::SetHandle(HWND hwnd)
{
  this->hwnd = hwnd;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void* GRPWINDOWSSCREEN::GetHDC()
* @brief      GetHDC
* @ingroup    PLATFORM_WINDOWS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     void* :
*
*---------------------------------------------------------------------------------------------------------------------*/
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
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  hdc :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
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
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
*
* @return     BITMAPINFO* : 
*
*---------------------------------------------------------------------------------------------------------------------*/
BITMAPINFO* GRPWINDOWSSCREEN::GetHInfo()
{
  return &hinfo;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int GRPWINDOWSSCREEN::GetScaleFactor()
* @brief      GetScaleFactor
* @ingroup    PLATFORM_WINDOWS
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
*
* @return     int : 
*
*---------------------------------------------------------------------------------------------------------------------*/
/*
int GRPWINDOWSSCREEN::GetScaleFactor()
{
  
  DEVICE_SCALE_FACTOR scale_factor = GetScaleFactorForDevice(DEVICE_PRIMARY);
  int sf = 0;

  switch(scale_factor)
    {
      case DEVICE_SCALE_FACTOR_INVALID    : sf =   0;         break;
      case SCALE_100_PERCENT              : sf = 100;         break;
      case SCALE_120_PERCENT              : sf = 120;         break;
      case SCALE_125_PERCENT              : sf = 125;         break;
      case SCALE_140_PERCENT              : sf = 140;         break;
      case SCALE_150_PERCENT              : sf = 150;         break;
      case SCALE_160_PERCENT              : sf = 160;         break;
      case SCALE_175_PERCENT              : sf = 175;         break;
      case SCALE_180_PERCENT              : sf = 180;         break;
      case SCALE_200_PERCENT              : sf = 200;         break;
      case SCALE_225_PERCENT              : sf = 225;         break;
      case SCALE_250_PERCENT              : sf = 250;         break;
      case SCALE_300_PERCENT              : sf = 300;         break;
      case SCALE_350_PERCENT              : sf = 350;         break;
      case SCALE_400_PERCENT              : sf = 400;         break;
      case SCALE_450_PERCENT              : sf = 450;         break;
      case SCALE_500_PERCENT              : sf = 500;         break;
            default                       : sf = -1;          break;
    }

  return sf;
}
*/



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void GRPWINDOWSSCREEN::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    PLATFORM_WINDOWS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
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
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
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



/*-------------------------------------------------------------------
//  LRESULT CALLBACK BaseWndProc
*/
/**
//
//
//  @author      Diego Martinez
//  @version      13/03/2014 12:54:52
//
//  @return       LRESULT :
//
/*-----------------------------------------------------------------*/
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
      case WM_CLOSE           : break;
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


