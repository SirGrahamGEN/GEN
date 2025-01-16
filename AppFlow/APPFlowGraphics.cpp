/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       APPFlowGraphics.cpp
* 
* @class      APPFLOWGRAPHICS
* @brief      Application Flow Graphics class
* @ingroup    APPFLOW
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

#include "APPFlowGraphics.h"

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

#include "APPFlowBase.h"
#include "APPFlowCFG.h"

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
* @fn         APPLICATIONAPPFLOWCFG::APPFLOWGRAPHICS()
* @brief      Constructor
* @ingroup    APPFLOW
*
* --------------------------------------------------------------------------------------------------------------------*/
APPFLOWGRAPHICS::APPFLOWGRAPHICS()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         APPFLOWGRAPHICS::~APPFLOWGRAPHICS()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    APPFLOW
*
* --------------------------------------------------------------------------------------------------------------------*/
APPFLOWGRAPHICS::~APPFLOWGRAPHICS()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool APPFLOWGRAPHICS::Ini(XVECTOR<XSTRING*>* execparams, bool haveconsole)
* @brief      Ini
* @ingroup    APPFLOW
*
* @param[in]  execparams :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool APPFLOWGRAPHICS::Ini(XVECTOR<XSTRING*>* execparams)
{
  RegisterEvent(GRPXEVENT_TYPE_SCREEN_CREATING);
  RegisterEvent(GRPXEVENT_TYPE_SCREEN_CANVASCREATING);
  RegisterEvent(GRPXEVENT_TYPE_SCREEN_CREATED);  
  RegisterEvent(GRPXEVENT_TYPE_SCREEN_DELETING);
  RegisterEvent(GRPXEVENT_TYPE_SCREEN_DELETED);

  if(!APPFLOWCONSOLE::Ini(execparams)) 
    {
      return false;
    }

  if(GetExitType() != APPFLOWBASE_EXITTYPE_UNKNOWN) 
    {
      return false;
    }

  if(initoptions & APPFLOWGRAPHICS_INIOPTION_CREATEMAINSCREEN)
    {
      if(!CreateMainScreenProcess((initoptions & APPFLOWGRAPHICS_INIOPTION_SHOWMAINSCREEN)?true:false)) return false;
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool APPFLOWGRAPHICS::End()
* @brief      End application console function
* @ingroup    APPFLOW
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool APPFLOWGRAPHICS::End()
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
      GEN_XLOG.AddEntry(XLOGLEVEL_INFO, APPFLOW_CFG_LOG_SECTIONID_GENERIC, false, exittypestring.Get());
    }

  bool status = APPFLOWCONSOLE::End();

  return status;
}

 
/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDWORD APPFLOWGRAPHICS::GetInitOptions()
* @brief      GetInitOptions
* @ingroup    APPFLOW
* 
* @return     XDWORD : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD APPFLOWGRAPHICS::GetInitOptions()
 {
   return initoptions;
 }


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void APPFLOWGRAPHICS::SetInitOptions(XDWORD initoptions)
* @brief      SetInitOptions
* @ingroup    APPFLOW
* 
* @param[in]  initoptions : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void APPFLOWGRAPHICS::SetInitOptions(XDWORD initoptions)
{
  this->initoptions = initoptions;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool APPFLOWGRAPHICS::CreateMainScreenProcess(bool show)
* @brief      CreateMainScreenProcess
* @ingroup    APPFLOW
* 
* @param[in]  show : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool APPFLOWGRAPHICS::CreateMainScreenProcess(bool show)
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
  if(initoptions & APPFLOWGRAPHICS_INIOPTION_INPUT)
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
* @fn         bool APPFLOWGRAPHICS::DeleteMainScreenProcess()
* @brief      DeleteMainScreenProcess
* @ingroup    APPFLOW
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool APPFLOWGRAPHICS::DeleteMainScreenProcess()
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
* @fn         GRPSCREEN* APPFLOWGRAPHICS::GetMainScreen()
* @brief      GetMainScreen
* @ingroup    APPFLOW
* 
* @return     GRPSCREEN* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
GRPSCREEN* APPFLOWGRAPHICS::GetMainScreen()
{
  return mainscreen;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void APPFLOWGRAPHICS::SetMainScreen(GRPSCREEN* mainscreen)
* @brief      SetMainScreen
* @ingroup    APPFLOW
*
* @param[in]  mainscreen :
*
* --------------------------------------------------------------------------------------------------------------------*/
void APPFLOWGRAPHICS::SetMainScreen(GRPSCREEN* mainscreen)
{
  this->mainscreen = mainscreen;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         GRPCANVAS* APPFLOWGRAPHICS::GetScreenCanvas(GRPSCREEN* screen, int viewportindex)
* @brief      GetScreenCanvas
* @ingroup    APPFLOW
* 
* @param[in]  screen : 
* @param[in]  viewportindex : 
* 
* @return     GRPCANVAS* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
GRPCANVAS* APPFLOWGRAPHICS::GetScreenCanvas(GRPSCREEN* screen, int viewportindex)
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
* @fn         INPDEVICE* APPFLOWGRAPHICS::GetInputKeyboard()
* @brief      GetInputKeyboard
* @ingroup    APPFLOW
* 
* @return     INPDEVICE* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
INPDEVICE* APPFLOWGRAPHICS::GetInputKeyboard()
{
  return keyboard;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         INPDEVICE* APPFLOWGRAPHICS::GetInputMouse()
* @brief      GetInputMouse
* @ingroup    APPFLOW
* 
* @return     INPDEVICE* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
INPDEVICE* APPFLOWGRAPHICS::GetInputMouse()
{
  return mouse;
}

#endif


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool APPFLOWGRAPHICS::AppProc_BeforeCreateMainScreen(GRPSCREEN* mainscreen)
* @brief      AppProc_BeforeCreateMainScreen
* @ingroup    APPFLOW
* 
* @param[in]  mainscreen : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool APPFLOWGRAPHICS::AppProc_BeforeCreateMainScreen(GRPSCREEN* mainscreen)
{
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool APPFLOWGRAPHICS::AppProc_BeforeCreateMainCanvas(GRPCANVAS* maincanvas)
* @brief      AppProc_BeforeCreateMainCanvas
* @ingroup    APPFLOW
* 
* @param[in]  maincanvas : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool APPFLOWGRAPHICS::AppProc_BeforeCreateMainCanvas(GRPCANVAS* maincanvas)
{
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void APPFLOWGRAPHICS::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    APPFLOW
* 
* --------------------------------------------------------------------------------------------------------------------*/
void APPFLOWGRAPHICS::Clean()
{
  initoptions   = APPFLOWGRAPHICS_INIOPTION_NONE;

  mainscreen    = NULL;

  #ifdef INP_ACTIVE
  keyboard      = NULL;
  mouse         = NULL;
  touchscreen   = NULL;
  #endif
}


#pragma endregion


#endif



