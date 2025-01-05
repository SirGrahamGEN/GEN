/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       APPGraphics.cpp
* 
* @class      APPGRAPHICS
* @brief      Application Graphics class
* @ingroup    APPLICATION
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


#ifdef GRP_ACTIVE


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "APPGraphics.h"

#include "XConsole.h"
#include "XLog.h"

#ifdef INP_ACTIVE
#include "INPFactory.h"
#include "INPManager.h"
#endif

#include "GRPXEvent.h"
#include "GRPScreen.h"

#ifdef GRP_OPENGL_ACTIVE
#include "GRP3DContext.h"
#endif

#include "GRPCanvas.h"
#include "GRPFactory.h"
#include "GRPViewport.h"

#include "APPBase.h"
#include "APPCFG.h"

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
* @fn         APPLICATIONAPPCFG::APPGRAPHICS()
* @brief      Constructor
* @ingroup    APPLICATION
*
* --------------------------------------------------------------------------------------------------------------------*/
APPGRAPHICS::APPGRAPHICS()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         APPGRAPHICS::~APPGRAPHICS()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    APPLICATION
*
* --------------------------------------------------------------------------------------------------------------------*/
APPGRAPHICS::~APPGRAPHICS()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool APPGRAPHICS::Ini(XVECTOR<XSTRING*>* execparams, bool haveconsole)
* @brief      Ini
* @ingroup    APPLICATION
*
* @param[in]  execparams :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool APPGRAPHICS::Ini(XVECTOR<XSTRING*>* execparams)
{
  RegisterEvent(GRPXEVENT_TYPE_SCREEN_CREATING);
  RegisterEvent(GRPXEVENT_TYPE_SCREEN_CANVASCREATING);
  RegisterEvent(GRPXEVENT_TYPE_SCREEN_CREATED);  
  RegisterEvent(GRPXEVENT_TYPE_SCREEN_DELETING);
  RegisterEvent(GRPXEVENT_TYPE_SCREEN_DELETED);

  if(!APPCONSOLE::Ini(execparams)) 
    {
      return false;
    }

  if(GetExitType() != APPBASE_EXITTYPE_UNKNOWN) 
    {
      return false;
    }

  if(initoptions & APPGRAPHICS_INIOPTION_CREATEMAINSCREEN)
    {
      if(!CreateMainScreenProcess((initoptions & APPGRAPHICS_INIOPTION_SHOWMAINSCREEN)?true:false)) return false;
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool APPGRAPHICS::End()
* @brief      End application console function
* @ingroup    APPLICATION
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool APPGRAPHICS::End()
{ 
  DeRegisterEvent(GRPXEVENT_TYPE_SCREEN_CREATING);
  DeRegisterEvent(GRPXEVENT_TYPE_SCREEN_CANVASCREATING);
  DeRegisterEvent(GRPXEVENT_TYPE_SCREEN_CREATED);
  DeRegisterEvent(GRPXEVENT_TYPE_SCREEN_DELETING);
  DeRegisterEvent(GRPXEVENT_TYPE_SCREEN_DELETED);

  DeleteMainScreenProcess();

  XSTRING exittypestring;

  GetExitTypeString(exittypestring);
  if(!exittypestring.IsEmpty()) 
    {
      GEN_XLOG.AddEntry(XLOGLEVEL_INFO, APP_CFG_LOG_SECTIONID_GENERIC, false, exittypestring.Get());
    }

  bool status = APPCONSOLE::End();

  return status;
}

 
/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDWORD APPGRAPHICS::GetInitOptions()
* @brief      GetInitOptions
* @ingroup    APPLICATION
* 
* @return     XDWORD : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD APPGRAPHICS::GetInitOptions()
 {
   return initoptions;
 }


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void APPGRAPHICS::SetInitOptions(XDWORD initoptions)
* @brief      SetInitOptions
* @ingroup    APPLICATION
* 
* @param[in]  initoptions : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void APPGRAPHICS::SetInitOptions(XDWORD initoptions)
{
  this->initoptions = initoptions;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool APPGRAPHICS::CreateMainScreenProcess(bool show)
* @brief      CreateMainScreenProcess
* @ingroup    APPLICATION
* 
* @param[in]  show : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool APPGRAPHICS::CreateMainScreenProcess(bool show)
{
  if(mainscreen) return false;

  mainscreen = GEN_GRPFACTORY.CreateScreen();
  if(!mainscreen)
    {
      // XTRACE_PRINTCOLOR(XTRACE_COLOR_RED, __L("[APP Graphics] Could not initialize the main screen ..."));
      return false;
    }

  #ifdef GRP_OPENGL_ACTIVE
  maincontext = GRPFACTORY::GetInstance().CreateContext();
  if(!maincontext)
    {
      // XTRACE_PRINTCOLOR(XTRACE_COLOR_RED, __L("[APP Graphics] Could not initialize the Graphics Context ..."));
      return false;
    }
  #endif

  SubscribeEvent(GRPXEVENT_TYPE_SCREEN_CREATING       , this);
  SubscribeEvent(GRPXEVENT_TYPE_SCREEN_CANVASCREATING , this);
  SubscribeEvent(GRPXEVENT_TYPE_SCREEN_CREATED        , this);
  SubscribeEvent(GRPXEVENT_TYPE_SCREEN_DELETING       , this);
  SubscribeEvent(GRPXEVENT_TYPE_SCREEN_DELETED        , this);

  #ifndef ANDROID

  GRPXEVENT grpeventini(this, GRPXEVENT_TYPE_SCREEN_CREATING);
  grpeventini.SetScreen(mainscreen);
  PostEvent(&grpeventini);    

  bool status = !grpeventini.GetError();

  if(status)  
    {
      status = mainscreen->Create(show);
      if(status)
        {
          GRPXEVENT grpeventini(this, GRPXEVENT_TYPE_SCREEN_CANVASCREATING);
          grpeventini.SetScreen(mainscreen);
          PostEvent(&grpeventini);    

          GRPVIEWPORT*  viewport = mainscreen->GetViewport(0);
          if(!viewport)
            {
              if(!mainscreen->CreateViewport(GRPVIEWPORT_ID_MAIN , 0.0f, 0.0f, (float)mainscreen->GetWidth()   , (float)mainscreen->GetHeight(), 0,  0, mainscreen->GetWidth(), mainscreen->GetHeight()))
                {
                  return false;
                }                  
            }
        }        
    }

  if(status)
    {
      //XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("[App Graphics] Screen created"));

      GRPXEVENT grpeventend(this, GRPXEVENT_TYPE_SCREEN_CREATED);
      grpeventend.SetScreen(mainscreen);
      grpeventend.SetError(status);
      PostEvent(&grpeventend);
    }
    else
    {
      //XTRACE_PRINTCOLOR(XTRACE_COLOR_RED, __L("[App Graphics] Error to creating screen..."));
    }

  if(!status) return false;

  #ifdef INP_ACTIVE
  if(initoptions & APPGRAPHICS_INIOPTION_INPUT)
    {
      keyboard = GEN_INPMANAGER.GetDevice(INPDEVICE_TYPE_KEYBOARD);
      if(!keyboard)
        {
          keyboard = INPFACTORY::GetInstance().CreateDevice(INPDEVICE_TYPE_KEYBOARD, mainscreen);
          if(keyboard)  GEN_INPMANAGER.AddDevice(keyboard);
        }

      mouse = GEN_INPMANAGER.GetDevice(INPDEVICE_TYPE_MOUSE);
      if(!mouse)
        {
          mouse = INPFACTORY::GetInstance().CreateDevice(INPDEVICE_TYPE_MOUSE, mainscreen);
          if(mouse) GEN_INPMANAGER.AddDevice(mouse);
        }

      touchscreen = GEN_INPMANAGER.GetDevice(INPDEVICE_TYPE_TOUCHSCREEN);
      if(!touchscreen)
        {
          touchscreen = INPFACTORY::GetInstance().CreateDevice(INPDEVICE_TYPE_TOUCHSCREEN, mainscreen);
          if(touchscreen) GEN_INPMANAGER.AddDevice(touchscreen);
        }

    }
  #endif

  #endif

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool APPGRAPHICS::DeleteMainScreenProcess()
* @brief      DeleteMainScreenProcess
* @ingroup    APPLICATION
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool APPGRAPHICS::DeleteMainScreenProcess()
{
  if(!mainscreen)
    {
      return false;
    }

  GRPXEVENT grpeventini(this, GRPXEVENT_TYPE_SCREEN_DELETING);
  grpeventini.SetScreen(mainscreen);
  PostEvent(&grpeventini);

  UnSubscribeEvent(GRPXEVENT_TYPE_SCREEN_CREATING       , this);
  UnSubscribeEvent(GRPXEVENT_TYPE_SCREEN_CANVASCREATING , this);
  UnSubscribeEvent(GRPXEVENT_TYPE_SCREEN_CREATED        , this);

  if(mainscreen)
    {
      mainscreen->Delete();
      GRPFACTORY::GetInstance().DeleteScreen(mainscreen);
      mainscreen = NULL;
    }

  GRPXEVENT grpeventend(this, GRPXEVENT_TYPE_SCREEN_DELETED);
  grpeventini.SetScreen(mainscreen);
  PostEvent(&grpeventend);

  UnSubscribeEvent(GRPXEVENT_TYPE_SCREEN_DELETED        , this);
  UnSubscribeEvent(GRPXEVENT_TYPE_SCREEN_CREATED        , this);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         GRPSCREEN* APPGRAPHICS::GetMainScreen()
* @brief      GetMainScreen
* @ingroup    APPLICATION
* 
* @return     GRPSCREEN* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
GRPSCREEN* APPGRAPHICS::GetMainScreen()
{
  return mainscreen;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void APPGRAPHICS::SetMainScreen(GRPSCREEN* mainscreen)
* @brief      SetMainScreen
* @ingroup    APPLICATION
*
* @param[in]  mainscreen :
*
* --------------------------------------------------------------------------------------------------------------------*/
void APPGRAPHICS::SetMainScreen(GRPSCREEN* mainscreen)
{
  this->mainscreen = mainscreen;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         GRPCANVAS* APPGRAPHICS::GetScreenCanvas(GRPSCREEN* screen, int viewportindex)
* @brief      GetScreenCanvas
* @ingroup    APPLICATION
* 
* @param[in]  screen : 
* @param[in]  viewportindex : 
* 
* @return     GRPCANVAS* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
GRPCANVAS* APPGRAPHICS::GetScreenCanvas(GRPSCREEN* screen, int viewportindex)
{
  if(!screen)
    {
      return NULL;
    }

  GRPVIEWPORT* viewport = screen->GetViewport(viewportindex);
  if(!viewport)
    {
      return NULL;
    }

  GRPCANVAS* canvas = viewport->GetCanvas();

  return canvas;
}




#ifdef INP_ACTIVE
/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         INPDEVICE* APPGRAPHICS::GetInputKeyboard()
* @brief      GetInputKeyboard
* @ingroup    APPLICATION
* 
* @return     INPDEVICE* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
INPDEVICE* APPGRAPHICS::GetInputKeyboard()
{
  return keyboard;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         INPDEVICE* APPGRAPHICS::GetInputMouse()
* @brief      GetInputMouse
* @ingroup    APPLICATION
* 
* @return     INPDEVICE* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
INPDEVICE* APPGRAPHICS::GetInputMouse()
{
  return mouse;
}

#endif


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool APPGRAPHICS::AppProc_BeforeCreateMainScreen(GRPSCREEN* mainscreen)
* @brief      AppProc_BeforeCreateMainScreen
* @ingroup    APPLICATION
* 
* @param[in]  mainscreen : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool APPGRAPHICS::AppProc_BeforeCreateMainScreen(GRPSCREEN* mainscreen)
{
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool APPGRAPHICS::AppProc_BeforeCreateMainCanvas(GRPCANVAS* maincanvas)
* @brief      AppProc_BeforeCreateMainCanvas
* @ingroup    APPLICATION
* 
* @param[in]  maincanvas : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool APPGRAPHICS::AppProc_BeforeCreateMainCanvas(GRPCANVAS* maincanvas)
{
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void APPGRAPHICS::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    APPLICATION
* 
* --------------------------------------------------------------------------------------------------------------------*/
void APPGRAPHICS::Clean()
{
  initoptions   = APPGRAPHICS_INIOPTION_NONE;

  mainscreen    = NULL;

  #ifdef INP_ACTIVE
  keyboard      = NULL;
  mouse         = NULL;
  touchscreen   = NULL;
  #endif
}


#pragma endregion


#endif



