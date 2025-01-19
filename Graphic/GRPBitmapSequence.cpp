/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       GRPBitmapSequence.cpp
* 
* @class      GRPBITMAPSEQUENCE
* @brief      Graphics Bitmap Sequence class
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

/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_DEFINES_INCLUDE

#include "GEN_Defines.h"

#pragma endregion


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "GRPBitmapSequence.h"

#include "XFactory.h"
#include "XTimer.h"

#include "GRPRect.h"
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


#pragma region CLASS_BITMAPFRAME


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         GRPBITMAPFRAME::GRPBITMAPFRAME()
* @brief      Constructor of class
* @ingroup    GRAPHIC
*
* --------------------------------------------------------------------------------------------------------------------*/
GRPBITMAPFRAME::GRPBITMAPFRAME()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         GRPBITMAPFRAME::~GRPBITMAPFRAME()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    GRAPHIC
*
* --------------------------------------------------------------------------------------------------------------------*/
GRPBITMAPFRAME::~GRPBITMAPFRAME()
{
  delete bitmap;
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         GRPBITMAP* GRPBITMAPFRAME::GetBitmap()
* @brief      Get bitmap
* @ingroup    GRAPHIC
*
* @return     GRPBITMAP* : Bitmap of frame class
*
* --------------------------------------------------------------------------------------------------------------------*/
GRPBITMAP* GRPBITMAPFRAME::GetBitmap()
{
  return bitmap;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int GRPBITMAPFRAME::GetAjustX()
* @brief      Get ajust x
* @ingroup    GRAPHIC
*
* @return     int : ajust x of frame
*
* --------------------------------------------------------------------------------------------------------------------*/
int GRPBITMAPFRAME::GetAjustX()
{
  return ajustx;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int GRPBITMAPFRAME::GetAjustY()
* @brief      Get ajust y
* @ingroup    GRAPHIC
*
* @return     int : ajust y of frame
*
* --------------------------------------------------------------------------------------------------------------------*/
int GRPBITMAPFRAME::GetAjustY()
{
  return ajusty;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void GRPBITMAPFRAME::SetBitmap(GRPBITMAP* bitmap)
* @brief      Set bitmap
* @ingroup    GRAPHIC
*
* @param[in]  bitmap : new bitmap of frame
*
* --------------------------------------------------------------------------------------------------------------------*/
void GRPBITMAPFRAME::SetBitmap(GRPBITMAP* bitmap)
{
  this->bitmap = bitmap;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void GRPBITMAPFRAME::SetAjustX(int x)
* @brief      Set ajust x
* @ingroup    GRAPHIC
*
* @param[in]  x : new ajust x
*
* --------------------------------------------------------------------------------------------------------------------*/
void GRPBITMAPFRAME::SetAjustX(int ajustx)
{
  this->ajustx = ajustx;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void GRPBITMAPFRAME::SetAjustY(int y)
* @brief      Set ajust y
* @ingroup    GRAPHIC
*
* @param[in]  y : new ajust y
*
* --------------------------------------------------------------------------------------------------------------------*/
void GRPBITMAPFRAME::SetAjustY(int ajusty)
{
  this->ajusty = ajusty;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void GRPBITMAPFRAME::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    GRAPHIC
*
* --------------------------------------------------------------------------------------------------------------------*/
void GRPBITMAPFRAME::Clean()
{
  bitmap = NULL;
  ajustx = 0;
  ajusty = 0;
}


#pragma endregion


#pragma region CLASS_GRPBITMAPSEQUENCE


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         GRPBITMAPSEQUENCE::GRPBITMAPSEQUENCE()
* @brief      Constructor of class
* @ingroup    GRAPHIC
*
* --------------------------------------------------------------------------------------------------------------------*/
GRPBITMAPSEQUENCE::GRPBITMAPSEQUENCE()
{
  Clean();

  GEN_XFACTORY_CREATE(timer, CreateTimer())
  
  AjustTime(GRPBITMAPSEQUENCE_FRAMESSECOND);  
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         GRPBITMAPSEQUENCE::~GRPBITMAPSEQUENCE()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    GRAPHIC
*
* --------------------------------------------------------------------------------------------------------------------*/
GRPBITMAPSEQUENCE::~GRPBITMAPSEQUENCE()
{
  if(timer) GEN_XFACTORY.DeleteTimer(timer);

  DelAllSequence();

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRPBITMAPSEQUENCE::AddFrame(GRPBITMAP* bitmap,int ajustx,int ajusty)
* @brief      Add frame
* @ingroup    GRAPHIC
*
* @param[in]  bitmap : bitmap to add
* @param[in]  ajustx : x ajust into sequence
* @param[in]  ajusty : y ajust into sequence
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPBITMAPSEQUENCE::AddFrame(GRPBITMAP* bitmap, int ajustx, int ajusty)
{
  GRPBITMAPFRAME* frame = new GRPBITMAPFRAME();
  if(!frame) return false;

  frame->SetBitmap(bitmap);
  frame->SetAjustX(ajustx);
  frame->SetAjustY(ajusty);

  frames.Add(frame);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRPBITMAPSEQUENCE::DelAllSequence(bool full)
* @brief      Del all sequence
* @ingroup    GRAPHIC
*
* @param[in]  full : deletes content
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPBITMAPSEQUENCE::DelAllSequence(bool full)
{
  if(frames.IsEmpty())  return false;

  if(full) frames.DeleteContents();

  frames.DeleteAll();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         GRPBITMAPFRAME* GRPBITMAPSEQUENCE::GetActualFrame()
* @brief      Get actual frame
* @ingroup    GRAPHIC
*
* @return     GRPBITMAPFRAME* : Actual frame class
*
* --------------------------------------------------------------------------------------------------------------------*/
GRPBITMAPFRAME* GRPBITMAPSEQUENCE::GetActualFrame()
{
  return (GRPBITMAPFRAME*)frames.Get(frameindex);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int GRPBITMAPSEQUENCE::GetActualFrameIndex()
* @brief      Get actual frame index
* @ingroup    GRAPHIC
*
* @return     int : actual frame index
*
* --------------------------------------------------------------------------------------------------------------------*/
int GRPBITMAPSEQUENCE::GetActualFrameIndex()
{
  return frameindex;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         GRPBITMAPFRAME* GRPBITMAPSEQUENCE::GetFrame(XWORD nframe)
* @brief      Get frame
* @ingroup    GRAPHIC
*
* @param[in]  nframe : index frame class
*
* @return     GRPBITMAPFRAME* : frame class
*
* --------------------------------------------------------------------------------------------------------------------*/
GRPBITMAPFRAME* GRPBITMAPSEQUENCE::GetFrame(XWORD nframe)
{
  if(nframe>=(XWORD)frames.GetSize()) return NULL;
  return (GRPBITMAPFRAME*)frames.Get(nframe);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int GRPBITMAPSEQUENCE::GetNFrames()
* @brief      Get N frames
* @ingroup    GRAPHIC
*
* @return     int : number of frames
*
* --------------------------------------------------------------------------------------------------------------------*/
int GRPBITMAPSEQUENCE::GetNFrames()
{
  return frames.GetSize();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int GRPBITMAPSEQUENCE::GetNLoops()
* @brief      Get N loops
* @ingroup    GRAPHIC
*
* @return     int : number of loops to made in the sequence
*
* --------------------------------------------------------------------------------------------------------------------*/
int GRPBITMAPSEQUENCE::GetNLoops()
{
  return nloops;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int GRPBITMAPSEQUENCE::GetNLoopsMade()
* @brief      Get N loops made
* @ingroup    GRAPHIC
*
* @return     int : Number of Loops Made
*
* --------------------------------------------------------------------------------------------------------------------*/
int GRPBITMAPSEQUENCE::GetNLoopsMade()
{
  return nloopsmade;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRPBITMAPSEQUENCE::SetNLoops(int nloops)
* @brief      Set N loops
* @ingroup    GRAPHIC
*
* @param[in]  nloops : number of loops
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPBITMAPSEQUENCE::SetNLoops(int nloops)
{
  this->nloops = nloops;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRPBITMAPSEQUENCE::SetNLoopsMade(int nloopsmade)
* @brief      Set N loops made
* @ingroup    GRAPHIC
*
* @param[in]  nloopsmade : number of loops made
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPBITMAPSEQUENCE::SetNLoopsMade(int nloopsmade)
{
  this->nloopsmade = nloopsmade;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRPBITMAPSEQUENCE::AjustAllSequence(int ajustx, int ajusty)
* @brief      Ajust all sequence
* @ingroup    GRAPHIC
*
* @param[in]  ajustx : x ajust for all frames
* @param[in]  ajusty : y ajust for all frames
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPBITMAPSEQUENCE::AjustAllSequence(int ajustx, int ajusty)
{
  if(frames.IsEmpty())  return false;

  for(XDWORD c=0;c<frames.GetSize();c++)
    {
      GRPBITMAPFRAME* frame = (GRPBITMAPFRAME*)frames.Get(c);
      if(frame)
        {        
          frame->SetAjustX(ajustx);
          frame->SetAjustY(ajusty);
        }
    }


  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         GRPBITMAPFRAME* GRPBITMAPSEQUENCE::Play(int nloops, bool ajusttimeauto, bool reverse)
* @brief      Play
* @ingroup    GRAPHIC
*
* @param[in]  nloops : nloops to made
* @param[in]  ajusttimeauto : is time ajust automatic
* @param[in]  reverse : is reverse sequence
*
* @return     GRPBITMAPFRAME* : frame to show
*
* --------------------------------------------------------------------------------------------------------------------*/
GRPBITMAPFRAME* GRPBITMAPSEQUENCE::Play(int nloops, bool ajusttimeauto, bool reverse)
{
  if(status==GRPBITMAPSEQUENCESTATUS_PLAY) return NULL;

  this->nloops = nloops;

  status = GRPBITMAPSEQUENCESTATUS_PLAY;

  if(ajusttimeauto) AjustTime(frames.GetSize());

  this->reverse = reverse;

  if(!reverse)
        frameindex = 0;
   else frameindex = frames.GetSize()-1;

  nloopsmade = 0;

  return (GRPBITMAPFRAME*)frames.Get(frameindex);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRPBITMAPSEQUENCE::Stop()
* @brief      Stop
* @ingroup    GRAPHIC
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPBITMAPSEQUENCE::Stop()
{
  if(frames.IsEmpty())                     return false;
  if(status==GRPBITMAPSEQUENCESTATUS_NONE) return false;

  status = GRPBITMAPSEQUENCESTATUS_STOP;

  if(!reverse)
        frameindex = 0;
   else frameindex = (frames.GetSize()-1);

  nloopsmade   = 0;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRPBITMAPSEQUENCE::Pause()
* @brief      Pause
* @ingroup    GRAPHIC
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPBITMAPSEQUENCE::Pause()
{
  if(frames.IsEmpty())                     return false;
  if(status!=GRPBITMAPSEQUENCESTATUS_PLAY) return false;

  status = GRPBITMAPSEQUENCESTATUS_PAUSE;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRPBITMAPSEQUENCE::Finished()
* @brief      Finished
* @ingroup    GRAPHIC
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPBITMAPSEQUENCE::Finished()
{
  if(frames.IsEmpty())                     return false;
  if(status!=GRPBITMAPSEQUENCESTATUS_PLAY) return false;

  status = GRPBITMAPSEQUENCESTATUS_END;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRPBITMAPSEQUENCE::IsPlaying()
* @brief      Is playing
* @ingroup    GRAPHIC
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPBITMAPSEQUENCE::IsPlaying()
{
  if(status==GRPBITMAPSEQUENCESTATUS_PLAY) return true;

  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRPBITMAPSEQUENCE::IsEndSequence()
* @brief      Is end sequence
* @ingroup    GRAPHIC
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPBITMAPSEQUENCE::IsEndSequence()
{
  if(status==GRPBITMAPSEQUENCESTATUS_END) return true;

  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         GRPBITMAPFRAME* GRPBITMAPSEQUENCE::Update()
* @brief      Update
* @ingroup    GRAPHIC
*
* @return     GRPBITMAPFRAME* : frame to show
*
* --------------------------------------------------------------------------------------------------------------------*/
GRPBITMAPFRAME* GRPBITMAPSEQUENCE::Update()
{
  if(!timer)                               return NULL;
  if(frames.IsEmpty())                     return NULL;
  if(status!=GRPBITMAPSEQUENCESTATUS_PLAY) return NULL;

  //if(timer->GetMeasureMilliSeconds()<timebyframe)  return NULL;

  timer->Reset();

  if(!reverse)
    {
      if(frames.GetSize()!=1) frameindex++;

      if(frameindex == frames.GetSize())
        {
          frameindex = 0;
          nloopsmade++;
          if((nloops)&&(nloops==nloopsmade)) status=GRPBITMAPSEQUENCESTATUS_END;
        }
    }
   else
    {
      if(frames.GetSize()!=1) frameindex--;

      if(frameindex<0)
        {
          frameindex = (frames.GetSize()-1);

          nloopsmade++;
          if((nloops)&&(nloops==nloopsmade)) status=GRPBITMAPSEQUENCESTATUS_END;
        }
    }

  return (GRPBITMAPFRAME*)frames.Get(frameindex);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRPBITMAPSEQUENCE::AjustTime(int framebysec)
* @brief      Ajust time
* @ingroup    GRAPHIC
*
* @param[in]  framebysec : frame by sec to ajust
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPBITMAPSEQUENCE::AjustTime(int framebysec)
{
  if(!timer) return false;

  this->framebysec  = framebysec;
  timebyframe       = ((float)1000/(float)framebysec);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         GRPBITMAPSEQUENCE* GRPBITMAPSEQUENCE::Copy()
* @brief      Copy
* @ingroup    GRAPHIC
* 
* @return     GRPBITMAPSEQUENCE* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
GRPBITMAPSEQUENCE* GRPBITMAPSEQUENCE::Copy()
{
  GRPBITMAPSEQUENCE* sequence = new GRPBITMAPSEQUENCE();
  if(!sequence)
    {
      return NULL;
    }

  for(XDWORD c=0; c<frames.GetSize(); c++)
    {
      GRPBITMAPFRAME* frame = frames.Get(c);
      if(frame)
        {
          GRPBITMAP* bitmap = frame->GetBitmap()->Clone();
          if(bitmap)
            {
              sequence->AddFrame(bitmap, frame->GetAjustX(), frame->GetAjustY());
            }
        }
    }

  return sequence;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool GRPBITMAPSEQUENCE::Flip(bool horizontal)
* @brief      Flip
* @ingroup    GRAPHIC
* 
* @param[in]  horizontal : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPBITMAPSEQUENCE::Flip(bool horizontal)
{
  bool status = true;

  for(XDWORD c=0; c<frames.GetSize(); c++)
    {
      GRPBITMAPFRAME* frame = frames.Get(c);
      if(frame)
        {
          GRPBITMAP* bitmap = frame->GetBitmap();
          if(bitmap)
            {
              if(horizontal)
                {
                  bitmap->FlipHorizontal();
                }
               else
                {
                  bitmap->FlipVertical();
                }
            }
        }
    }

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void GRPBITMAPSEQUENCE::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    GRAPHIC
*
* --------------------------------------------------------------------------------------------------------------------*/
void GRPBITMAPSEQUENCE::Clean()
{
  framebysec    = 0;
  timebyframe   = 0;
  timer         = NULL;

  repeat        = false;
  status        = GRPBITMAPSEQUENCESTATUS_NONE;
  frameindex    = 0;

  nloops        = 0;
  nloopsmade    = 0;

  reverse       = false;
}


#pragma endregion



#pragma endregion

