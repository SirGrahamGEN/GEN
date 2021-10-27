/**-------------------------------------------------------------------------------------------------------------------
*
* @file       MainProcANDROID.cpp
*
* @class      MAINPROCANDROID
* @brief      ANDROID Main Proc class
* @ingroup    PLATFORM_ANDROID
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

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>

#include "XANDROIDFactory.h"
#include "XANDROIDSleep.h"
#include "XANDROIDSystem.h"

#ifdef GRP_ACTIVE
#include "GRPANDROIDFactory.h"
#include "GRPANDROIDScreen.h"
#endif

#ifdef INP_ACTIVE
#include "INPButton.h"
#include "INPANDROIDDeviceKeyboard.h"
#include "INPANDROIDDeviceMouse.h"
#include "INPManager.h"
#include "INPFactoryDevices.h"
#include "INPANDROIDFactory.h"
#endif

#ifdef SND_ACTIVE
#include "SNDAndroidFactory.h"
#endif

#ifdef DIO_ACTIVE
#include "DIODNSResolved.h"
#include "DIOANDROIDFactory.h"
  #ifdef DIOALERTS_ACTIVE
  #include "DIOAlerts.h"
  #endif
#endif

#include "XPathsManager.h"
#include "XThreadCollected.h"
#include "XString.h"
#include "XLog.h"
#include "XDateTime.h"
#include "XDir.h"
#include "XFile.h"
#include "XFileZIP.h"
#include "XTimer.h"
#include "XTranslation.h"
#include "XTranslation_GEN.h"
#include "XTrace.h"

#include "GRPXEvent.h"
#include "GRPViewport.h"
#include "GRPCanvas.h"

#include "ANDROIDJNI.h"

#include "APPGraphics.h"


#include "MainProcANDROID.h"

#include "ANDROIDJNI.h"

#include "XMemory_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

#ifdef XTRACE_ACTIVE
XANDROIDTRACE    androiddebugtrace;
#endif

MAINPROCANDROID  androidmain;
void*            java_vm;



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         MAINPROCANDROID::MAINPROCANDROID()
* @brief      Constructor
* @ingroup    PLATFORM_ANDROID
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
MAINPROCANDROID::MAINPROCANDROID()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         MAINPROCANDROID::~MAINPROCANDROID()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    PLATFORM_ANDROID
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
MAINPROCANDROID::~MAINPROCANDROID()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool MAINPROCANDROID::Ini(XSTRING* apkpath, APPMAIN* appmain, APPBASE_APPLICATIONMODE_TYPE applicationmode)
* @brief      Ini
* @ingroup    PLATFORM_ANDROID
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  apkpath :
* @param[in]  appmain :
* @param[in]  applicationmode :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool MAINPROCANDROID::Ini(XSTRING* apkpath, XSTRING* datapath, APPMAIN* appmain, APPBASE_APPLICATIONMODE_TYPE applicationmode)
{
  // #Imanol : required for openal as static library
  java_vm = androidapplication->activity->vm;

  this->appmain = appmain;


  #ifdef APP_ACTIVE

  if(!appmain)            return false;
  if(!appmain->Create())  return false;

  #endif


  if(!Factorys_Ini()) return false;

  XPATH xpathroot;
  GEN_XPATHSMANAGER.GetPathOfSection(XPATHSMANAGERSECTIONTYPE_ROOT, xpathroot);

  if(apkpath && datapath)  
    {
      XPATH _apkpath;
      XPATH _datapath;

      _apkpath  = apkpath->Get();
      _datapath = datapath->Get();

      OverturnAssetsToExternalLocation(_apkpath, _datapath, xpathroot);
    }

  GetDPI(androidapplication);

  #ifdef APP_ACTIVE
  if(appmain)
    {
      if(!appmain->Ini(this, applicationmode)) return false;
    }
  #endif

  GetXPathExec()->SetOnlyDriveAndPath();

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool MAINPROCANDROID::Update()
* @brief      Update
* @ingroup    PLATFORM_ANDROID
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool MAINPROCANDROID::Update()
{
  #ifdef INP_ACTIVE
  GEN_INPMANAGER.Update();
  #endif

  #ifdef APP_ACTIVE
  if(appmain)
    {
      if(!appmain->Update()) return false;
    }
  #endif

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool MAINPROCANDROID::End()
* @brief      End
* @ingroup    PLATFORM_ANDROID
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool MAINPROCANDROID::End()
{
  #ifdef INP_ACTIVE
  DeleteInputDevices();  
  #endif
  
  #ifdef APP_ACTIVE
  if(appmain) appmain->End();
  #endif

  GetXPathExec()->Empty();

  DeleteAllExecParams();
  Factorys_End();

  #ifdef APP_ACTIVE
  if(appmain) appmain->Delete();
  #endif

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         android_app* MAINPROCANDROID::GetAndroidApplication()
* @brief      GetAndroidApplication
* @ingroup    PLATFORM_ANDROID
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     android_app* :
*
*---------------------------------------------------------------------------------------------------------------------*/
android_app* MAINPROCANDROID::GetAndroidApplication()
{
  return androidapplication;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void MAINPROCANDROID::SetAndroidApplication(android_app* application)
* @brief      SetAndroidApplication
* @ingroup    PLATFORM_ANDROID
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  application :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void MAINPROCANDROID::SetAndroidApplication(android_app* application)
{
  androidapplication = application;
}



#ifdef INP_ACTIVE
/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         INPDEVICE* MAINPROCANDROID::GetKeyboard()
* @brief      GetKeyboard
* @ingroup    PLATFORM_ANDROID
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     INPDEVICE* :
*
*---------------------------------------------------------------------------------------------------------------------*/
INPDEVICE* MAINPROCANDROID::GetKeyboard()
{
  return keyboard;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         INPDEVICE* MAINPROCANDROID::GetTouchscreen()
* @brief      GetTouchscreen
* @ingroup    PLATFORM_ANDROID
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     INPDEVICE* :
*
*---------------------------------------------------------------------------------------------------------------------*/
INPDEVICE* MAINPROCANDROID::GetTouchscreen()
{
  return mouse;
}
#endif




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool MAINPROCANDROID::OnTouchEvent(AInputEvent* event)
* @brief      OnTouchEvent
* @ingroup    PLATFORM_ANDROID
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  event :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool MAINPROCANDROID::OnTouchEvent(AInputEvent* event)
{
  XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE , __L("[ANDROID Event] INI OnTouchEvent"));

  int32_t action        = AMotionEvent_getAction(event);
  size_t  pointercount  = AMotionEvent_getPointerCount(event);

  if(!mouse) mouse = (INPANDROIDDEVICEMOUSE*)GEN_INPMANAGER.GetDevice(INPDEVICE_TYPE_MOUSE);

  if(mouse)
    {
      for(size_t c = 0; c<pointercount; ++c)
        {
          int32_t pointerID    = c;
          int32_t pointerIndex = AMotionEvent_getPointerId(event,c);

          if(pointerIndex >= mouse->GetCursors()->GetSize())
            {
              INPCURSOR* cursor = new INPCURSOR();
              if(cursor)
                {
                  cursor->SetID(INPCURSOR_ID(INPCURSOR_ID_TOUCHSCREEN1+pointerIndex));
                  cursor->SetHavePreSelect(false);

                  mouse->GetCursors()->Add(cursor);
                }
            }

          if(pointerIndex >= mouse->GetButtons()->GetSize())
            {
              INPBUTTON* button = new INPBUTTON();
              if(button)
                {
                  button->SetID(INPBUTTON_ID_TOUCHSCREEN);
                  mouse->GetButtons()->Add(button);
                }
            }

          float x        = AMotionEvent_getX(event, pointerID);
          float y        = AMotionEvent_getY(event, pointerID);
          float pressure = AMotionEvent_getPressure(event, pointerID);

          switch(action & AMOTION_EVENT_ACTION_MASK)
            {
              case AMOTION_EVENT_ACTION_UP            :
              case AMOTION_EVENT_ACTION_POINTER_UP    : { mouse->AddPosition(pointerIndex, x, y, false);
                                                          if(mouse->GetButton(pointerIndex))
                                                            {
                                                              mouse->GetButton(pointerIndex)->SetPressed(false);
                                                              mouse->GetButton(pointerIndex)->SetPressure(pressure);

                                                              if(mouse->GetButton(pointerIndex)->GetState() != INPBUTTON_STATE_UP)
                                                                {
                                                                  mouse->GetButton(pointerIndex)->SetState(INPBUTTON_STATE_RELEASED);
                                                                  XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("> ANDROID Motion %d x %f y %f p %f a %d RELEASED"), pointerID,x,y,pressure,action);

                                                                }
                                                                else
                                                                {
                                                                  mouse->GetButton(pointerIndex)->SetState(INPBUTTON_STATE_UP);
                                                                  XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("> ANDROID Motion %d x %f y %f p %f a %d UP"), pointerID,x,y,pressure,action);
                                                                }
                                                            }
                                                        }
                                                        break;
              case AMOTION_EVENT_ACTION_MOVE          :
              case AMOTION_EVENT_ACTION_DOWN          :
              case AMOTION_EVENT_ACTION_POINTER_DOWN  : { mouse->AddPosition(pointerIndex,x,y, true);
                                                          if(mouse->GetButton(pointerIndex))
                                                            {
                                                              mouse->GetButton(pointerIndex)->SetPressed(true);
                                                              mouse->GetButton(pointerIndex)->SetPressure(pressure);

                                                              if(mouse->GetButton(pointerIndex)->GetState() == INPBUTTON_STATE_UP)
                                                                {
                                                                  mouse->GetButton(pointerIndex)->SetState(INPBUTTON_STATE_PRESSED);
                                                                  XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("> ANDROID Motion %d x %f y %f p %f a %d PRESSED"), pointerID,x,y,pressure,action);
                                                                }
                                                                else
                                                                {
                                                                  mouse->GetButton(pointerIndex)->SetState(INPBUTTON_STATE_HOLD);
                                                                  XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("> ANDROID Motion %d x %f y %f p %f a %d HOLD"), pointerID,x,y,pressure,action);
                                                                }
                                                            }
                                                        }
                                                        break;

              case AMOTION_EVENT_ACTION_CANCEL        : if (mouse->GetButton(pointerIndex))
                                                        mouse->GetButton(pointerIndex)->SetState(INPBUTTON_STATE_UP);
                                                        break;
            }
        }
    }


  XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE , __L("[ANDROID Event] END OnTouchEvent"));

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool MAINPROCANDROID::OnKeyboardEvent(AInputEvent* event)
* @brief      OnKeyboardEvent
* @ingroup    PLATFORM_ANDROID
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  event :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool MAINPROCANDROID::OnKeyboardEvent(AInputEvent* event)
{
  XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE , __L("[ANDROID Event] INI OnKeyboardEvent   Android code [%04x]"), AKeyEvent_getKeyCode(event));

  INPDEVICE* keyboard = androidmain.GetKeyboard();
  if(!keyboard) return false;

  INPBUTTON* button = keyboard->GetButtonByCode(AKeyEvent_getKeyCode(event));
  if(!button) return false;

  XDWORD keyEvent = AKeyEvent_getAction(event);
  switch(keyEvent)
    {
      case AKEY_EVENT_ACTION_UP     : button->SetPressed(false);
                                      XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("> ANDROID Keyboard %d ID %d RELEASED"), keyEvent, button->GetID());
                                      break;

      case AKEY_EVENT_ACTION_DOWN   : button->SetPressed(true);
                                      XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("> ANDROID Keyboard %d ID %d PRESSED"), keyEvent, button->GetID());
                                      break;
    }

  XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE , __L("[ANDROID Event] END OnKeyboardEvent"));

  return false;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool MAINPROCANDROID::OnTrackballEvent(AInputEvent* event)
* @brief      OnTrackballEvent
* @ingroup    PLATFORM_ANDROID
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  event :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool MAINPROCANDROID::OnTrackballEvent(AInputEvent* event)
{
  XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE , __L("[ANDROID Event] OnTrackballEvent"));
  
  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         STATUS MAINPROCANDROID::OnActivate()
* @brief      OnActivate
* @ingroup    PLATFORM_ANDROID
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     STATUS :
*
*---------------------------------------------------------------------------------------------------------------------*/
STATUS MAINPROCANDROID::OnActivate()
{
  XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE , __L("[ANDROID Event] OnActivate"));
  
  return STATUS_OK;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void MAINPROCANDROID::OnDeactivate()
* @brief      OnDeactivate
* @ingroup    PLATFORM_ANDROID
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void MAINPROCANDROID::OnDeactivate()
{
  XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE , __L("[ANDROID Event] OnDeactivate"));  
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         STATUS MAINPROCANDROID::OnStep()
* @brief      OnStep
* @ingroup    PLATFORM_ANDROID
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     STATUS :
*
*---------------------------------------------------------------------------------------------------------------------*/
STATUS MAINPROCANDROID::OnStep()
{
  //XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE , __L("[ANDROID Event] INI OnStep"));

  STATUS status = STATUS_OK;
  
  if(!screenactived) 
    {
      status = STATUS_KO;
    }
   else
    {
      if(!androidmain.Update()) status = STATUS_KO;
    }
  

  //XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE , __L("[ANDROID Event] END OnStep"));

  return status;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void MAINPROCANDROID::OnStart()
* @brief      OnStart
* @ingroup    PLATFORM_ANDROID
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void MAINPROCANDROID::OnStart()
{
  XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE , __L("[ANDROID Event] OnStart"));

  if(initialized)
    {
      androidmain.End(); 
      initialized = false;
    }

  XSTRING apkpath;
  XSTRING datapath;

  androidmain.GetPackageResourcePath(androidapplication, apkpath);
  androidmain.GetAbsolutePath(androidapplication, datapath);
   
  androidmain.GetXPathExec()->Set(apkpath.Get());

  GEN_XPATHSMANAGER.GetAppExecPath()->Set(GetXPathExec()->Get());
  GetXPathExec()->SetOnlyDriveAndPath();
  
  GEN_XPATHSMANAGER.AddPathSection(XPATHSMANAGERSECTIONTYPE_ROOT, datapath);
  
  #ifdef APP_ACTIVE  
  if(androidmain.Ini(&apkpath, &datapath, &GEN_appmain, APPBASE_APPLICATIONMODE_TYPE_APPLICATION))
  #else
  if(androidmain.Ini(&apkpath))
  #endif
    {
      ANativeActivity_setWindowFlags(androidapplication->activity, AWINDOW_FLAG_FULLSCREEN, 0);
    }  

  initialized = true;

}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void MAINPROCANDROID::OnResume()
* @brief      OnResume
* @ingroup    PLATFORM_ANDROID
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void MAINPROCANDROID::OnResume()
{
  XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE , __L("[ANDROID Event] OnResume"));
 
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void MAINPROCANDROID::OnPause()
* @brief      OnPause
* @ingroup    PLATFORM_ANDROID
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void MAINPROCANDROID::OnPause()
{
  XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE , __L("[ANDROID Event] OnPause"));  
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void MAINPROCANDROID::OnStop()
* @brief      OnStop
* @ingroup    PLATFORM_ANDROID
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void MAINPROCANDROID::OnStop()
{
  XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE , __L("[ANDROID Event] OnStop"));  
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void MAINPROCANDROID::OnDestroy()
* @brief      OnDestroy
* @ingroup    PLATFORM_ANDROID
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void MAINPROCANDROID::OnDestroy()
{
  XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE , __L("[ANDROID Event] OnDestroy"));  

  if(initialized) 
    {
      androidmain.End(); 
      initialized = false;
    }
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void MAINPROCANDROID::OnSaveState(void** data, size_t* size)
* @brief      OnSaveState
* @ingroup    PLATFORM_ANDROID
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  data :
* @param[in]  size :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void MAINPROCANDROID::OnSaveState(void** data, size_t* size)
{
  XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE , __L("[ANDROID Event] OnSaveState"));  
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void MAINPROCANDROID::OnConfigurationChanged()
* @brief      OnConfigurationChanged
* @ingroup    PLATFORM_ANDROID
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void MAINPROCANDROID::OnConfigurationChanged()
{
  XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE , __L("[ANDROID Event] OnConfigurationChanged"));

  if(!androidapplication)         return;
  if(!androidapplication->window) return;

  ANativeActivity_setWindowFlags(androidapplication->activity, AWINDOW_FLAG_FULLSCREEN, 0);

  int32_t maxwidth  = ANativeWindow_getWidth(androidapplication->window);
  int32_t maxheight = ANativeWindow_getHeight(androidapplication->window);

  APPBASE* app = NULL;
  if(androidmain.GetAppMain()) app = androidmain.GetAppMain()->GetApplication();

  if(!app) return;

  APPGRAPHICS* applicationgrp  = (APPGRAPHICS*)app;
  if(applicationgrp)
    {
      GRPANDROIDSCREEN* mainscreen = (GRPANDROIDSCREEN*)applicationgrp->GetMainScreen();
      if(mainscreen)
        {
          mainscreen->UpdateSize(maxwidth, maxheight);
        }
    }
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void MAINPROCANDROID::OnLowMemory()
* @brief      OnLowMemory
* @ingroup    PLATFORM_ANDROID
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void MAINPROCANDROID::OnLowMemory()
{
  XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE , __L("[ANDROID Event] OnLowMemory"));  
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void MAINPROCANDROID::OnCreateWindow()
* @brief      OnCreateWindow
* @ingroup    PLATFORM_ANDROID
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void MAINPROCANDROID::OnCreateWindow()
{
  XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE , __L("[ANDROID Event] OnCreateWindow"));
  
  if(!androidapplication)         return;
  if(!androidapplication->window) return;

  ANativeActivity_setWindowFlags(androidapplication->activity, AWINDOW_FLAG_FULLSCREEN, 0);

  
  ANativeWindow_Buffer abuffer;
  if(ANativeWindow_lock(androidapplication->window, &abuffer, NULL) >= 0)
    {
      ANativeWindow_unlockAndPost(androidapplication->window);
    }  

  int32_t w         = abuffer.width;          
  int32_t h         = abuffer.height;  

  if(w > h)  
         w = abuffer.stride; 
    else h = abuffer.stride;           
  

  //int32_t w         = ANativeWindow_getWidth(androidapplication->window);            
  //int32_t h         = ANativeWindow_getHeight(androidapplication->window);                   
  int32_t maxwidth  = 0;
  int32_t maxheight = 0;

  if(w > h)
    {
      maxwidth  = w;
      maxheight = h;
    }
   else
    {
      maxwidth  = h;
      maxheight = w;
    }

  APPBASE* app = NULL;
  if(androidmain.GetAppMain()) app = androidmain.GetAppMain()->GetApplication();

  if(!app) return;

  APPGRAPHICS* applicationgrp  = (APPGRAPHICS*)app;
  if(applicationgrp)
    {
      GRPANDROIDSCREEN* mainscreen = (GRPANDROIDSCREEN*)applicationgrp->GetMainScreen();
      if(mainscreen)
        {         
          mainscreen->SetMaxSize(maxwidth, maxheight);

          if(!mainscreen->GetWidth() || !mainscreen->GetHeight()) mainscreen->SetSize(maxwidth, maxheight);

          GRPXEVENT grpevent(this, GRPXEVENT_TYPE_SCREEN_CREATING);
          grpevent.SetScreen(mainscreen);
          applicationgrp->PostEvent(&grpevent);

          ANativeWindow_setBuffersGeometry(androidapplication->window, mainscreen->GetWidth(), mainscreen->GetHeight(), WINDOW_FORMAT_RGBA_8888);

          ANativeWindow_Buffer abuffer;
          if(ANativeWindow_lock(androidapplication->window, &abuffer, NULL) >= 0)
            {
              ANativeWindow_unlockAndPost(androidapplication->window);
            }  

          int32_t w         = abuffer.width;          
          int32_t h         = abuffer.height;  

          if(w > h)  
                 w = abuffer.stride; 
            else h = abuffer.stride;           
  
          mainscreen->SetSize(w, h);
          mainscreen->SetMaxSize(w, h);

          ANativeWindow_setBuffersGeometry(androidapplication->window, mainscreen->GetWidth(), mainscreen->GetHeight(), WINDOW_FORMAT_RGBA_8888);

          GRPVIEWPORT*  viewport = mainscreen->GetViewport(0);
          if(!viewport)
            {
              if(!mainscreen->CreateViewport(GRPVIEWPORT_ID_MAIN , 0.0f, 0.0f, (float)mainscreen->GetWidth()   , (float)mainscreen->GetHeight(), 0,  0, (float)mainscreen->GetWidth(), (float)mainscreen->GetHeight()))
                {
                  return;
                }                  
             }

          if(mainscreen->Create(true))
            {
              mainscreen->SetAndroidHandle(androidapplication->window);

              GRPVIEWPORT*  viewport = NULL;

              GRPCANVAS*    canvas   = NULL;
              GRPRECTINT*   rect     = NULL;

              viewport = mainscreen->GetViewport(0);
              canvas   = NULL;
              
              if(viewport) canvas = viewport->GetCanvas();
              if(canvas) viewport->GetCanvas()->GetScreenZone()->Set(0, 0, mainscreen->GetWidth(), mainscreen->GetHeight());

              #ifdef INP_ACTIVE
              if(!CreateInputDevices(&INPMANAGER::GetInstance(), (GRPANDROIDSCREEN*)mainscreen)) return;
              #endif

              screenactived = true;

            }
        }
    }
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void MAINPROCANDROID::OnDestroyWindow()
* @brief      OnDestroyWindow
* @ingroup    PLATFORM_ANDROID
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void MAINPROCANDROID::OnDestroyWindow()
{
  XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE , __L("[ANDROID Event] OnDestroyWindow"));
  
  #ifdef INP_ACTIVE
  DeleteInputDevices();  
  #endif
  
  APPBASE* app = NULL;
  if(androidmain.GetAppMain()) app = androidmain.GetAppMain()->GetApplication();

  if(!app) return;

  APPGRAPHICS* applicationgrp  = (APPGRAPHICS*)app;
  if(applicationgrp)
    {
      GRPANDROIDSCREEN* mainscreen = (GRPANDROIDSCREEN*)applicationgrp->GetMainScreen();
      if(mainscreen) 
        {         
          if(screenactived)
            {
              mainscreen->Delete();  
              screenactived = false; 
            }       
        }      
    }
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void MAINPROCANDROID::OnGainFocus()
* @brief      OnGainFocus
* @ingroup    PLATFORM_ANDROID
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void MAINPROCANDROID::OnGainFocus()
{
  XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE , __L("[ANDROID Event] OnGainFocus"));

  //APPGRAPHICS* gap = dynamic_cast<APPGRAPHICS*>(application);
  //if(gap) gap->OnFocus();  
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void MAINPROCANDROID::OnLostFocus()
* @brief      OnLostFocus
* @ingroup    PLATFORM_ANDROID
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void MAINPROCANDROID::OnLostFocus()
{
  XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE , __L("[ANDROID Event] OnLostFocus"));

  //APPGRAPHICS* gap = dynamic_cast<APPGRAPHICS*>(application);
  //if(gap) gap->OnLostFocus();  
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool MAINPROCANDROID::GetPackageResourcePath(struct android_app* app, XSTRING& path)
* @brief      GetPackageResourcePath
* @ingroup    PLATFORM_ANDROID
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  android_app* app :
* @param[in]  path :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool MAINPROCANDROID::GetPackageResourcePath(struct android_app* app, XSTRING& path)
{
  JNIEnv* env;
  JavaVM* vm     = app->activity->vm;
  bool    status = false;

  vm->AttachCurrentThread(&env, NULL);

  jclass    clazz   = env->GetObjectClass(app->activity->clazz);
  jmethodID methodj = env->GetMethodID(clazz, "getPackageResourcePath", "()Ljava/lang/String;");

  jstring   jstr    = (jstring)env->CallObjectMethod(app->activity->clazz, methodj);
  if(jstr != NULL)
    {
      const char* str = env->GetStringUTFChars(jstr, NULL);
      path =  str;
      env->ReleaseStringUTFChars(jstr, str);

      status = true;
    }

  vm->DetachCurrentThread();

  return status;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool MAINPROCANDROID::GetAbsolutePath(struct android_app* app, XSTRING& path)
* @brief      GetAbsolutePath
* @ingroup    PLATFORM_ANDROID
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  android_app* app :
* @param[in]  path :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool MAINPROCANDROID::GetAbsolutePath(struct android_app* app, XSTRING& path)
{
  JNIEnv* env;
  JavaVM* vm     = app->activity->vm;
  bool    status = false;

  vm->AttachCurrentThread(&env, NULL);

  jclass    activityclass   = env->GetObjectClass(app->activity->clazz);
  jmethodID getfilesdir     = env->GetMethodID(activityclass, "getFilesDir", "()Ljava/io/File;");
  jobject   file            = env->CallObjectMethod(app->activity->clazz, getfilesdir);
  jclass    fileclass       = env->FindClass("java/io/File");
  jmethodID getabsolutepath = env->GetMethodID(fileclass, "getAbsolutePath", "()Ljava/lang/String;");

  jstring jpath = (jstring)env->CallObjectMethod(file, getabsolutepath);
  if(jpath != NULL)
    {
      const char* str = env->GetStringUTFChars(jpath, NULL);
      path =  str;
      env->ReleaseStringUTFChars(jpath, str);
      status = true;
    }

  vm->DetachCurrentThread();

  return status;
}





/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool MAINPROCANDROID::GetDPI(struct android_app* app)
* @brief      GetDPI
* @ingroup    PLATFORM_ANDROID
*
* @author     Imanol Celaya Ruiz de Alegria
* @date       01/03/2016 12:00
*
* @param[in]  android_app* app :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool MAINPROCANDROID::GetDPI(struct android_app* app)
{

  //#ifdef GRP_ACTIVE
  //grpfactory  = new GRPANDROIDFACTORY();
  //if(!grpfactory) return false;

  //// get the screen dpi  //DIEGO : supongo que meter esto en una función consumía tinta de monitor, no? de hecho , no hay una clase para manejar el JNI????
  //JNIEnv* env = NULL;

  //jint      res     = androidapplication->activity->vm->AttachCurrentThread(&env, NULL);

  //jclass    clazz   = env->GetObjectClass(androidapplication->activity->clazz);
  //jfieldID  fid     = env->GetStaticFieldID(clazz, "dpi", "I");
  //jint      i       = env->GetStaticIntField(clazz, fid);

  //androidapplication->activity->vm->DetachCurrentThread();

  //XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("jni %lld"), timer->GetMeasureMilliSeconds());
  //
  //// assign it

  //grpfactory->dpi = i;

  //#endif


  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void MAINPROCANDROID::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    PLATFORM_ANDROID
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void MAINPROCANDROID::Clean()
{
  #ifdef INP_ACTIVE
  keyboard            = NULL;
  mouse               = NULL;
  #endif

  initialized         = false;
  screenactived       = false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool MAINPROCANDROID::Factorys_Ini()
* @brief      Factorys_Ini
* @ingroup    PLATFORM_ANDROID
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool MAINPROCANDROID::Factorys_Ini()
{
  XFACTORY::SetInstance(new XANDROIDFACTORY());
  if(!XFACTORY::GetIsInstanced()) return false;

  XSYSTEM::SetInstance(new XANDROIDSYSTEM());
  if(!XSYSTEM::GetIsInstanced()) return false;
  XBUFFER::SetHardwareUseLittleEndian(GEN_XSYSTEM.HardwareUseLittleEndian());

  XSLEEP::SetInstance(new XANDROIDSLEEP());
  if(!XSLEEP::GetIsInstanced()) return false;

  #ifdef XTRACE_VIRTUALCLOCKTICK
  xtimerclock = new XTIMERCLOCK();
  if(!xtimerclock) return false;
  #endif

  #ifdef INP_ACTIVE
  INPFACTORYDEVICES::SetInstance(new INPANDROIDFACTORYDEVICES());
  if(!INPFACTORYDEVICES::GetIsInstanced()) return false;
  #endif

  #ifdef DIO_ACTIVE
  DIOFACTORY::SetInstance(new DIOANDROIDFACTORY());
  if(!DIOFACTORY::GetIsInstanced()) return false;
  #endif

  #ifdef SND_ACTIVE
  SNDFACTORY::Instance=new SNDANDROIDFACTORY();
  if (!SNDFACTORY::Instance) return false;
  SNDFACTORY::Get()->IniEvents();
  #endif

  #ifdef GRP_ACTIVE
  GRPFACTORY::SetInstance(new GRPANDROIDFACTORY());
  if(!GRPFACTORY::GetIsInstanced()) return false;
  #endif

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool MAINPROCANDROID::Factorys_End()
* @brief      Factorys_End
* @ingroup    PLATFORM_ANDROID
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool MAINPROCANDROID::Factorys_End()
{
  #ifdef GRP_ACTIVE
  if(GRPFACTORY::GetIsInstanced()) GRPFACTORY::DelInstance();
  #endif

  #ifdef SND_ACTIVE
  if (SNDFACTORY::Get())
  SNDFACTORY::Get()->EndEvents();
  #endif

  #ifdef DIO_ACTIVE
  if(DIODNSRESOLVED::GetIsInstanced()) DIODNSRESOLVED::DelInstance();
  if(DIOFACTORY::GetIsInstanced()) DIOFACTORY::DelInstance();
  #endif

  #ifdef INP_ACTIVE
  if(INPMANAGER::GetIsInstanced()) INPMANAGER::DelInstance();
  if(INPFACTORYDEVICES::GetIsInstanced()) INPFACTORYDEVICES::DelInstance();
  #endif

  #ifdef XTRACE_VIRTUALCLOCKTICK
  if(xtimerclock)
    {
      delete xtimerclock;
      xtimerclock = NULL;
    }
  #endif

  #ifdef DIOALERTS_ACTIVE
  if(DIOALERTS::GetIsInstanced()) DIOALERTS::DelInstance();
  #endif

  if(XPATHSMANAGER::GetIsInstanced()) XPATHSMANAGER::DelInstance();

  if(XTRANSLATION::GetIsInstanced())     XTRANSLATION::DelInstance();
  if(XTRANSLATION_GEN::GetIsInstanced()) XTRANSLATION_GEN::DelInstance();

  if(XLOG::GetIsInstanced()) XLOG::DelInstance();

  if(XSLEEP::GetIsInstanced()) XSLEEP::DelInstance();

  if(XSYSTEM::GetIsInstanced()) XSYSTEM::DelInstance();

  if(XPUBLISHER::GetIsInstanced()) XPUBLISHER::DelInstance();

  if(XFACTORY::GetIsInstanced()) XFACTORY::DelInstance();

  #ifdef XTHREADCOLLECTION_ACTIVE
  XTHREADSCOLLECTEDMANAGER::DelInstance();
  #endif

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool MAINPROCANDROID::OverturnAssetsToExternalLocation(XPATH& origin, XPATH& target, XPATH& addtarget)
* @brief      OverturnAssetsToExternalLocation
* @ingroup    PLATFORM_ANDROID
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @param[in]  origin : 
* @param[in]  target : 
* @param[in]  addtarget : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool MAINPROCANDROID::OverturnAssetsToExternalLocation(XPATH& origin, XPATH& datapath, XPATH& target)
{
  XFILEUNZIP* unzip = new XFILEUNZIP();
  if(!unzip) return false;

  XSTRING  assetsstring;
  bool     status  = false;

  assetsstring = __L("assets");

  XDIR* xdir = GEN_XFACTORY.Create_Dir();
  if(xdir)
    {
      status = unzip->Open(origin);

      //XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("[Android Resources] ZIP File: %s"), origin.Get());

      if(status)
        {
          XFILECMPZIP* filecmp;
          int          index = 0;

          status = true;

          do{
              filecmp = unzip->GotoFile(index);
              if(filecmp)
                {
                  XPATH targetpath;

                  targetpath  = datapath;
                  targetpath.Slash_Add();
                  targetpath += filecmp->GetName();

                  targetpath.SetOnlyPath();

                  int position=targetpath.Find(assetsstring,true);
                  if(position!=-1)
                    {
                      XPATH targetfile;
                      XPATH namefile;

                      namefile = filecmp->GetName();
                      namefile.SetOnlyNamefileExt();

                      //targetpath.DeleteCharacters(position, assetsstring.GetSize()+1);

                      targetfile  = targetpath;
                      targetfile += namefile.Get();

                      XFILE* xfile = GEN_XFACTORY.Create_File();
                      if(xfile)
                        {
                          //XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("[Android Resources] ZIP descompress File: %s"), targetfile.Get());

                          if(!xfile->Exist(targetfile.Get()))
                            {
                              xdir->Make(targetpath.Get(), true);
                              status = unzip->DecompressFile(filecmp,targetpath,namefile.Get());
                            }

                          GEN_XFACTORY.Delete_File(xfile);
                        }
                    }

                  delete filecmp;

                  index++;

                } else break;

            } while(status);

          unzip->Close();

        }

      GEN_XFACTORY.Delete_Dir(xdir);
    }

  delete unzip;

  return status;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool MAINPROCANDROID::AssetsDir_CreateAll(XPATH& origin)
* @brief      AssetsDir_CreateAll
* @ingroup    PLATFORM_ANDROID
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @param[in]  origin : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool MAINPROCANDROID::AssetsDir_CreateAll(XPATH& origin)
{
  AssetsDir_DeleteAll();

  XPATH       targetpath;
  XFILEUNZIP* unzip   = new XFILEUNZIP();
  XSTRING     assetsstring;
  bool        status  = false;

  if(!unzip) return false;

  assetsstring = __L("assets");

  status = unzip->Open(origin);
  if(status)
    {
      XFILECMPZIP* filecmp;
      int          index = 0;

      status = true;

      do{ filecmp = unzip->GotoFile(index);
          if(filecmp)
            {
              targetpath.Empty();
              
              targetpath += filecmp->GetName();

              targetpath.SetOnlyPath();

              int position=targetpath.Find(assetsstring,true);
              if(position!=-1)
                {   
                  bool found = false;
             
                  targetpath.DeleteCharacters(position, assetsstring.GetSize()+1);   

                  for(int c=0; c<assetsdirs.GetSize(); c++)
                    {
                      XPATH* xpath;

                      xpath = assetsdirs.Get(c);
                      if(!xpath->Compare(targetpath)) 
                        {
                          found = true;
                          break;                               
                        }
                    }               

                  if(!found)
                    {
                      XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("Assets XPATH: %s"), targetpath.Get());
                      
                      AssetsDir_Add(&targetpath);                                                                                                  
                    }
                } 

              index++;

              delete filecmp;

            } else break;

        } while(status);

      unzip->Close();        
    }
      
  delete unzip;

  return status;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool MAINPROCANDROID::AssetsDir_Add(XPATH* assetsdir)
* @brief      AssetsDir_Add
* @ingroup    PLATFORM_ANDROID
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @param[in]  assetsdir : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool MAINPROCANDROID::AssetsDir_Add(XPATH* assetsdir)
{
  if(!assetsdir) return false;

  XPATH* newpath = new XPATH();
  if(!newpath) return false;

  newpath->Set(assetsdir->Get());   

  assetsdirs.Add(newpath);

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XVECTOR<XPATH*>* MAINPROCANDROID::AssetsDir_GetAll()
* @brief      AssetsDir_GetAll
* @ingroup    PLATFORM_ANDROID
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @return     XVECTOR<XPATH*>* : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
XVECTOR<XPATH*>* MAINPROCANDROID::AssetsDir_GetAll()
{
  return &assetsdirs;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XPATH* MAINPROCANDROID::AssetsDir_Get(int index)
* @brief      AssetsDir_Get
* @ingroup    PLATFORM_ANDROID
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @param[in]  index : 
* 
* @return     XPATH* : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
XPATH* MAINPROCANDROID::AssetsDir_Get(int index)
{
  if(assetsdirs.IsEmpty()) return NULL;

  return assetsdirs.Get(index);
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool MAINPROCANDROID::AssetsDir_DeleteAll()
* @brief      AssetsDir_DeleteAll
* @ingroup    PLATFORM_ANDROID
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool MAINPROCANDROID::AssetsDir_DeleteAll()
{
  if(assetsdirs.IsEmpty()) return false;

  assetsdirs.DeleteContents();
  assetsdirs.DeleteAll();

  return true;
}
    




#ifdef INP_ACTIVE

/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool MAINPROCANDROID::CreateInputDevices(INPMANAGER* inpmanager, GRPANDROIDSCREEN* screen)
* @brief      CreateInputDevices
* @ingroup    PLATFORM_ANDROID
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  inpmanager :
* @param[in]  screen :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool MAINPROCANDROID::CreateInputDevices(INPMANAGER* inpmanager, GRPANDROIDSCREEN* screen)
{
  keyboard  = (INPANDROIDDEVICEKEYBOARD*)INPANDROIDFACTORYDEVICES::GetInstance().CreateDevice(INPDEVICE_TYPE_KEYBOARD , screen);
  if(keyboard) GEN_INPMANAGER.AddDevice(keyboard);

  mouse     = (INPANDROIDDEVICEMOUSE*)INPANDROIDFACTORYDEVICES::GetInstance().CreateDevice(INPDEVICE_TYPE_MOUSE       , screen);
  if(mouse) GEN_INPMANAGER.AddDevice(mouse);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool MAINPROCANDROID::DeleteInputDevices()
* @brief      DeleteInputDevices
* @ingroup    PLATFORM_ANDROID
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool MAINPROCANDROID::DeleteInputDevices()
{  
  if(keyboard) 
    {
      GEN_INPMANAGER.DelDevice(keyboard);
      keyboard = NULL;
    }
  
  if(mouse) 
    {
      GEN_INPMANAGER.DelDevice(mouse);
      mouse = NULL;
    }

  return true;
}

#endif



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         JNIEXPORT jint JNI_OnLoad(JavaVM* InJavaVM, void* InReserved)
* @brief      JNI_OnLoad
* @ingroup    PLATFORM_ANDROID
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  InJavaVM :
* @param[in]  InReserved :
*
* @return     JNIEXPORT :
*
*---------------------------------------------------------------------------------------------------------------------*/
JNIEXPORT jint JNI_OnLoad(JavaVM* InJavaVM, void* InReserved)
{
  return JNI_VERSION_1_6;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void android_main(android_app* application)
* @brief      android_main
* @ingroup    PLATFORM_ANDROID
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  application :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void android_main(android_app* application)
{
  ANDROIDJNI::InitializeJNI(application, JNI_VERSION_1_6);

  ANDROIDNATIVEACTIVITY_EVENTLOOP eventloop(application);

  androidmain.SetAndroidApplication(application);

  eventloop.Run(&androidmain, &androidmain);

  XFILE_DISPLAYNOTCLOSEFILES
  XMEMORY_CONTROL_DISPLAYMEMORYLEAKS
}
