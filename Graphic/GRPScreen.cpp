/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       GRPScreen.cpp
* 
* @class      GRPSCREEN
* @brief      Graphics Screen Class
* @ingroup    GRAPHIC
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

#include "GRPScreen.h"

#include "GRPXEvent.h"
#include "GRPCanvas.h"
#include "GRPViewPort.h"
#include "GRPFrameRate.h"

#include "XMemory_Control.h"

#pragma endregion


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE


#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         GRPSCREEN::GRPSCREEN()
* @brief      Constructor
* @ingroup    GRAPHIC
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
GRPSCREEN::GRPSCREEN()
{
  Clean();

  RegisterEvent(GRPXEVENT_TYPE_SCREEN_CREATING);
  RegisterEvent(GRPXEVENT_TYPE_SCREEN_CREATED);
  RegisterEvent(GRPXEVENT_TYPE_SCREEN_DELETING);
  RegisterEvent(GRPXEVENT_TYPE_SCREEN_DELETED);
  RegisterEvent(GRPXEVENT_TYPE_SCREEN_CHANGEPOSITION);
  RegisterEvent(GRPXEVENT_TYPE_SCREEN_CHANGESIZE);
  RegisterEvent(GRPXEVENT_TYPE_SCREEN_CHANGEFOCUS);

  framerate = new GRPFRAMERATE();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         GRPSCREEN::~GRPSCREEN()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    GRAPHIC
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
GRPSCREEN::~GRPSCREEN()
{
  if(framerate)
    {
      delete framerate;
      framerate = NULL;
    }

  DeRegisterEvent(GRPXEVENT_TYPE_SCREEN_CREATING);
  DeRegisterEvent(GRPXEVENT_TYPE_SCREEN_CREATED);
  DeRegisterEvent(GRPXEVENT_TYPE_SCREEN_DELETING);
  DeRegisterEvent(GRPXEVENT_TYPE_SCREEN_DELETED);
  DeRegisterEvent(GRPXEVENT_TYPE_SCREEN_CHANGEFOCUS);
  DeRegisterEvent(GRPXEVENT_TYPE_SCREEN_CHANGESIZE);
  DeRegisterEvent(GRPXEVENT_TYPE_SCREEN_CHANGEPOSITION);

  DeleteAllViewports();

  DeleteBuffers();

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         GRPSCREENTYPE GRPSCREEN::GetType()
* @brief      Get Screen type
* @ingroup    GRAPHIC
*
* @return     GRPSCREENTYPE : Screen type
*
* --------------------------------------------------------------------------------------------------------------------*/
GRPSCREENTYPE GRPSCREEN::GetType()
{
  return type;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRPSCREEN::IsValid()
* @brief      Is valid screen
* @ingroup    GRAPHIC
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPSCREEN::IsValid()
{
  return isvalid;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRPSCREEN::IsActive()
* @brief      Is screen active
* @ingroup    GRAPHIC
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPSCREEN::IsActive()
{
  return isactive;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRPSCREEN::SetPropertys(int width, int height, int stride, GRPPROPERTYMODE mode)
* @brief
* @ingroup    GRAPHIC
*
* @param[in]  width :
* @param[in]  height :
* @param[in]  stride :
* @param[in]  mode :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPSCREEN::SetPropertys(int width, int height, float DPIs, int stride, GRPPROPERTYMODE mode)
{
  SetWidth(width);
  SetHeight(height);

  SetDPI(DPIs);

  SetStride(stride);

  SetMode(mode);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRPSCREEN::IsFullScreen()
* @brief
* @ingroup    GRAPHIC
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPSCREEN::IsFullScreen()
{
  return isfullscreen;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void GRPSCREEN::SetIsFullScreen(bool isfullscreen)
* @brief
* @ingroup    GRAPHIC
*
* @param[in]  isfullscreen :
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void GRPSCREEN::SetIsFullScreen(bool isfullscreen)
{
  this->isfullscreen = isfullscreen;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRPSCREEN::CreateBuffers()
* @brief      Create Buffers
* @ingroup    GRAPHIC
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPSCREEN::CreateBuffers()
{
  buffersize = (width * height * GetBytesperPixel());

  buffer = new XBYTE[buffersize];

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRPSCREEN::DeleteBuffers()
* @brief      DeleteBuffers
* @ingroup    GRAPHIC
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPSCREEN::DeleteBuffers()
{
  if(!buffer) return false;

  delete [] buffer;
  buffer = NULL;

  buffersize = 0;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRPSCREEN::GetBuffer()
* @brief      GetBuffer
* @ingroup    GRAPHIC
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
XBYTE* GRPSCREEN::GetBuffer()
{
  return buffer;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRPSCREEN::Create(void* handle)
* @brief      Create
* @ingroup    GRAPHIC
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPSCREEN::Create(bool show)
{
  if(!viewports.Get(0)) return false;
  
  isactive = true;

  if(framerate) framerate->Reset();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRPSCREEN::Update()
* @brief      Update
* @ingroup    GRAPHIC
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPSCREEN::Update()
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRPSCREEN::Update(GRPCAVAS* canvas)
* @brief      Update
* @ingroup    GRAPHIC
*
* @param[in]  canvas : canvas handle
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPSCREEN::Update(GRPCANVAS* canvas)
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRPSCREEN::Delete()
* @brief      Delete
* @ingroup    GRAPHIC
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPSCREEN::Delete()
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool GRPSCREEN::SetPosition(int x, int y)
* @brief      SetPosition
* @ingroup    GRAPHIC
* 
* @param[in]  x : 
* @param[in]  y : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPSCREEN::Set_Position(int x, int y)
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRPSCREEN::Resize(int width, int height)
* @brief
* @ingroup    GRAPHIC
*
* @param[in]  width :
* @param[in]  height :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPSCREEN::Resize(int width, int height)
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRPSCREEN::IsShow()
* @brief      IsShow
* @ingroup    GRAPHIC
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPSCREEN::IsShow()
{
  return isshow;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRPSCREEN::Show(bool active)
* @brief      Show
* @ingroup    GRAPHIC
*
* @param[in]  active :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPSCREEN::Show(bool active)
{
  isshow  = active;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRPSCREEN::ShowCursor(bool active)
* @brief      ShowCursor
* @ingroup    GRAPHIC
*
* @param[in]  active :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPSCREEN::ShowCursor(bool active)
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRPSCREEN::ShowTopMost(bool active)
* @brief      ShowTopMost
* @ingroup    GRAPHIC
*
* @param[in]  active :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPSCREEN::ShowTopMost(bool active)
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void* GRPSCREEN::GetHandle()
* @brief
* @ingroup    GRAPHIC
*
* @return     void* :
*
* --------------------------------------------------------------------------------------------------------------------*/
void* GRPSCREEN::GetHandle()
{
  return NULL;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void GRPSCREEN::SetHandle(XDWORD handle_window)
* @brief      SetHandle
* @ingroup    GRAPHIC
* 
* @param[in]  handle_window : 
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void GRPSCREEN::SetHandle(void* handle_window)
{
  return;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool GRPSCREEN::Set_Focus()
* @brief      Set_Focus
* @ingroup    GRAPHIC
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPSCREEN::Set_Focus()
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRPSCREEN::UpdateSize(int width, int height)
* @brief
* @ingroup    GRAPHIC
*
* @param[in]  width :
* @param[in]  height :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPSCREEN::UpdateSize(int width, int height)
{
  GRPXEVENT grpevent(this, GRPXEVENT_TYPE_SCREEN_CHANGESIZE);
  grpevent.SetScreen(this);

  PostEvent(&grpevent);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XVECTOR<GRPVIEWPORT*>* GRPSCREEN::GetViewports()
* @brief
* @ingroup    GRAPHIC
*
* @return     XVECTOR<GRPVIEWPORT*>* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XVECTOR<GRPVIEWPORT*>* GRPSCREEN::GetViewports()
{
  return &viewports;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         GRPVIEWPORT* GRPSCREEN::GetViewport(int index)
* @brief
* @ingroup    GRAPHIC
*
* @param[in]  index :
*
* @return     GRPVIEWPORT* :
*
* --------------------------------------------------------------------------------------------------------------------*/
GRPVIEWPORT* GRPSCREEN::GetViewport(int index)
{
  return (viewports.Get(index));
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         GRPVIEWPORT* GRPSCREEN::GetViewport(XCHAR* ID)
* @brief      GetViewport
* @ingroup    GRAPHIC
*
* @param[in]  ID : 
* 
* @return     GRPVIEWPORT* : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
GRPVIEWPORT* GRPSCREEN::GetViewport(XCHAR* ID)
{
  for(XDWORD c=0; c<viewports.GetSize(); c++)
    {
      GRPVIEWPORT* viewport = viewports.Get(c);
      if(viewport) 
        {
          if(!viewport->GetID()->Compare(ID, true)) return viewport;
        }                    
    }

  return NULL;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRPSCREEN::CreateViewport(XCHAR* ID, float posx, float posy, float width, float height, XDWORD canvasposx, XDWORD canvasposy, XDWORD canvaswidth, XDWORD canvasheight)
* @brief      CreateViewport
* @ingroup    GRAPHIC
*
* @param[in]  ID :
* @param[in]  posx :
* @param[in]  posy :
* @param[in]  width :
* @param[in]  height :
* @param[in]  canvasposx :
* @param[in]  canvasposy :
* @param[in]  canvaswidth :
* @param[in]  canvasheight :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPSCREEN::CreateViewport(XCHAR* ID, float posx, float posy, float width, float height, XDWORD canvasposx, XDWORD canvasposy, XDWORD canvaswidth, XDWORD canvasheight)
{
  GRPVIEWPORT* viewport = new GRPVIEWPORT();
  if(!viewport)  return false;

  viewport->GetID()->Set(ID);
  viewport->SetPosition(posx, posy);
  viewport->SetSize(width, height);

  GRPPROPERTIES canvasproperties;

  canvasproperties.CopyPropertysFrom(this);

  canvasproperties.SetPosition(canvasposx, canvasposy);

  float cwidth  = (float)canvaswidth;
  float cheight = (float)canvasheight;

  if(width  > cwidth)  cwidth  = width;
  if(height > cheight) cheight = height;

  canvasproperties.SetSize((XDWORD)cwidth, (XDWORD)cheight);

  if(viewport->CreateCanvas(canvasproperties))
    {
       viewport->GetCanvas()->GetScreenZone()->Set((int)posx, (int)posy, (int)(posx + width), (int)(posy + height));
       viewports.Add(viewport);

        // --------------------------------------------------------------------------------------------------
        // Main Canvas is selected if the name is the name of the main viewport or there is only one viewport.
  
       if((!viewport->GetID()->Compare(GRPVIEWPORT_ID_MAIN,true))  || viewports.GetSize() == 1)
          {
            index_maincanvas  = viewports.GetSize()-1;
            maincanvas        = viewport->GetCanvas();
          }

    } else return false;

  return true;
 }


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRPSCREEN::UpdateViewports(int width, int height)
* @brief
* @ingroup    GRAPHIC
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPSCREEN::UpdateViewports()
{

  #ifdef GRP_OPENGL_ACTIVE


  #else
    
    if(maincanvas)
      {        
        for(XDWORD c=0; c<viewports.GetSize(); c++)
          {
            if(index_maincanvas != c) 
              maincanvas->CopyBufferRenderFromViewport(viewports.Get(c));                               
          } 
           
        Update(maincanvas);      
      }

  #endif  

  if(framerate) framerate->AddNFrames();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRPSCREEN::DeleteViewport(GRPVIEWPORT* viewport)
* @brief      DeleteViewport
* @ingroup    GRAPHIC
*
* @param[in]  viewport :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPSCREEN::DeleteViewport(GRPVIEWPORT* viewport)
{
  if(!viewport) return false;

  viewports.Delete(viewport);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRPSCREEN::DeleteAllViewports()
* @brief      DeleteAllViewports
* @ingroup    GRAPHIC
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPSCREEN::DeleteAllViewports()
{
  if(viewports.IsEmpty()) return false;

  viewports.DeleteContents();
  viewports.DeleteAll();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         GRPFRAMERATE* GRPSCREEN::GetFrameRate()
* @brief      GetFrameRate
* @ingroup    GRAPHIC
*
* @return     GRPFRAMERATE* : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
GRPFRAMERATE* GRPSCREEN::GetFrameRate()
{
  return framerate;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void GRPSCREEN::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    GRAPHIC
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void GRPSCREEN::Clean()
{
  type                = GRPSCREENTYPE_UNKNOW;

  isvalid             = false;
  isactive            = false;
  isfullscreen        = false;

  buffer              = NULL;
  buffersize          = 0;

  isblockclose        = false;

  index_maincanvas    = 0;
  maincanvas          = NULL;

  framerate           = NULL;

  isshow              = false;
}

#pragma endregion