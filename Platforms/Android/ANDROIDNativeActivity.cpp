/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       ANDROIDNativeActivity.cpp
* 
* @class      ANDROIDNATIVEACTIVITY
* @brief      ANDROID Native Activity class
* @ingroup    PLATFORM_ANDROID
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

#include "ANDROIDNativeActivity.h"

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


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         ANDROIDNATIVEACTIVITY_EVENTLOOP::ANDROIDNATIVEACTIVITY_EVENTLOOP(android_app* application)
* @brief      Constructor of class
* @ingroup    PLATFORM_ANDROID
* 
* @param[in]  application : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
ANDROIDNATIVEACTIVITY_EVENTLOOP::ANDROIDNATIVEACTIVITY_EVENTLOOP(android_app* application)
{
  Clean();

  this->application = application;

  application->userData     = this;
  application->onAppCmd     = CallbackEvent;
  application->onInputEvent = CallbackInput;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         ANDROIDNATIVEACTIVITY_EVENTLOOP::~ANDROIDNATIVEACTIVITY_EVENTLOOP()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    PLATFORM_ANDROID
* 
* --------------------------------------------------------------------------------------------------------------------*/
ANDROIDNATIVEACTIVITY_EVENTLOOP::~ANDROIDNATIVEACTIVITY_EVENTLOOP()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void ANDROIDNATIVEACTIVITY_EVENTLOOP::Run(ANDROIDNATIVEACTIVITY_HANDLER* activityhandler, ANDROIDNATIVEINPUT_HANDLER* inputhandler)
* @brief      Run
* @ingroup    PLATFORM_ANDROID
* 
* @param[in]  activityhandler : 
* @param[in]  inputhandler : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void ANDROIDNATIVEACTIVITY_EVENTLOOP::Run(ANDROIDNATIVEACTIVITY_HANDLER* activityhandler, ANDROIDNATIVEINPUT_HANDLER* inputhandler)
{
  int32_t               result;
  int32_t               events;
  android_poll_source*  source;

  //app_dummy();

  this->activityhandler = activityhandler;
  this->inputhandler    = inputhandler;

  while (true)
    {
      // Event processing loop.
      while((result = ALooper_pollOnce(enabled?0:-1, NULL, &events, (void**)&source)) >= 0)
        {
          // An event has to be processed.
          if(source != NULL) source->process(application, source);

          // Application is getting destroyed.
          if(application->destroyRequested) return;
        }

      if((enabled) && (!quit))
        {
          if(activityhandler->OnStep() != STATUS_OK)
            {
              quit = true;
              ANativeActivity_finish(application->activity);
            }
        }
    }
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void ANDROIDNATIVEACTIVITY_EVENTLOOP::Activate()
* @brief      Activate
* @ingroup    PLATFORM_ANDROID
* 
* --------------------------------------------------------------------------------------------------------------------*/
void ANDROIDNATIVEACTIVITY_EVENTLOOP::Activate()
{
  // Enables activity only if a window is available.
  if((!enabled) && (application->window != NULL))
    {
      quit    = false;
      enabled = true;

      if(activityhandler->OnActivate() != STATUS_OK)
        {
          quit = true;

          Deactivate();

          ANativeActivity_finish(application->activity);
        }
    }
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void ANDROIDNATIVEACTIVITY_EVENTLOOP::Deactivate()
* @brief      Deactivate
* @ingroup    PLATFORM_ANDROID
* 
* --------------------------------------------------------------------------------------------------------------------*/
void ANDROIDNATIVEACTIVITY_EVENTLOOP::Deactivate()
{
  if(enabled)
    {
      activityhandler->OnDeactivate();
      enabled = false;
    }
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         int32_t ANDROIDNATIVEACTIVITY_EVENTLOOP::ProcessInputEvent(AInputEvent* event, android_app* application)
* @brief      Process input event
* @ingroup    PLATFORM_ANDROID
* 
* @param[in]  event : 
* @param[in]  application : 
* 
* @return     int32_t : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
int32_t ANDROIDNATIVEACTIVITY_EVENTLOOP::ProcessInputEvent(AInputEvent* event, android_app* application)
{
  int32_t eventtype = AInputEvent_getType(event);

  this->application = application;

  switch(eventtype)
    {
      case AINPUT_EVENT_TYPE_MOTION : switch (AInputEvent_getSource(event))
                                        {
                                          case AINPUT_SOURCE_TOUCHSCREEN  : return inputhandler->OnTouchEvent(event);       break;
                                          case AINPUT_SOURCE_TRACKBALL    : return inputhandler->OnTrackballEvent(event);   break;
                                        }
                                      break;

      case AINPUT_EVENT_TYPE_KEY    : return inputhandler->OnKeyboardEvent(event);  break;
    }

  return 0;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void ANDROIDNATIVEACTIVITY_EVENTLOOP::ProcessApplicationEvent(int32_t command, android_app* application)
* @brief      Process application event
* @ingroup    PLATFORM_ANDROID
* 
* @param[in]  command : 
* @param[in]  application : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void ANDROIDNATIVEACTIVITY_EVENTLOOP::ProcessApplicationEvent(int32_t command, android_app* application)
{
  this->application = application;

  switch(command)
    {
      case APP_CMD_CONFIG_CHANGED   : activityhandler->OnConfigurationChanged();
                                      break;

      case APP_CMD_INIT_WINDOW      : activityhandler->OnCreateWindow();
                                      break;

      case APP_CMD_DESTROY          : activityhandler->OnDestroy();
                                      break;

      case APP_CMD_GAINED_FOCUS     : Activate();
                                      activityhandler->OnGainFocus();
                                      break;

      case APP_CMD_LOST_FOCUS       : activityhandler->OnLostFocus();
                                      Deactivate();
                                      break;

      case APP_CMD_LOW_MEMORY       : activityhandler->OnLowMemory();
                                      break;

      case APP_CMD_PAUSE            : activityhandler->OnPause();
                                      Deactivate();
                                      break;

      case APP_CMD_RESUME           : Activate();
                                      activityhandler->OnResume();
                                      break;

      case APP_CMD_SAVE_STATE       : activityhandler->OnSaveState(&application->savedState, &application->savedStateSize);
                                      break;

      case APP_CMD_START            : activityhandler->OnStart();
                                      break;

      case APP_CMD_STOP             : activityhandler->OnStop();
                                      break;

      case APP_CMD_TERM_WINDOW      : activityhandler->OnDestroyWindow();
                                      Deactivate();
                                      break;

                    default         : break;
    }
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void ANDROIDNATIVEACTIVITY_EVENTLOOP::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    PLATFORM_ANDROID
* 
* --------------------------------------------------------------------------------------------------------------------*/
void ANDROIDNATIVEACTIVITY_EVENTLOOP::Clean()
{
  enabled         = false;
  quit            = false;

  application     = NULL;
  activityhandler = NULL;
  inputhandler    = NULL;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         int32_t ANDROIDNATIVEACTIVITY_EVENTLOOP::CallbackInput(android_app* application, AInputEvent* event)
* @brief      Callback input
* @ingroup    PLATFORM_ANDROID
* 
* @param[in]  application : 
* @param[in]  event : 
* 
* @return     int32_t : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
int32_t ANDROIDNATIVEACTIVITY_EVENTLOOP::CallbackInput(android_app* application, AInputEvent* event)
{
  ANDROIDNATIVEACTIVITY_EVENTLOOP& eventloop = *(ANDROIDNATIVEACTIVITY_EVENTLOOP*) application->userData;

  return eventloop.ProcessInputEvent(event, application);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void ANDROIDNATIVEACTIVITY_EVENTLOOP::CallbackEvent(android_app* application, int32_t command)
* @brief      Callback event
* @ingroup    PLATFORM_ANDROID
* 
* @param[in]  application : 
* @param[in]  command : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void ANDROIDNATIVEACTIVITY_EVENTLOOP::CallbackEvent(android_app* application, int32_t command)
{
  ANDROIDNATIVEACTIVITY_EVENTLOOP& eventloop = *(ANDROIDNATIVEACTIVITY_EVENTLOOP*)application->userData;

  eventloop.ProcessApplicationEvent(command, application);
}


#pragma endregion
