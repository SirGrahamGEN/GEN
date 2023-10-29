/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       SNDOpenALFactory.cpp
* 
* @class      SNDOPENALFACTORY
* @brief      Sound OpenAL Factory class
* @ingroup    SOUND
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

#include "SNDOpenALFactory.h"

#include "XFactory.h"
#include "XSleep.h"

#include "SNDOpenALSource.h"
#include "SNDItem.h"
#include "SNDPlayCFG.h"

#include "XMemory_Control.h"

#pragma endregion


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


#pragma region CLASS_SNDPLAYITEM

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         SNDOPENALPLAYITEM::SNDOPENALPLAYITEM()
* @brief      Constructor
* @ingroup    SOUND
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
SNDOPENALPLAYITEM::SNDOPENALPLAYITEM()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         SNDOPENALPLAYITEM::~SNDOPENALPLAYITEM()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    SOUND
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
SNDOPENALPLAYITEM::~SNDOPENALPLAYITEM()
{
  Delete();

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         SNDITEM* SNDOPENALPLAYITEM::GetItem()
* @brief      GetItem
* @ingroup    SOUND
* 
* @return     SNDITEM* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
SNDITEM* SNDOPENALPLAYITEM::GetItem()
{
  return item;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void SNDOPENALPLAYITEM::SetItem(SNDITEM* item)
* @brief      SetItem
* @ingroup    SOUND
* 
* @param[in]  item : 
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void SNDOPENALPLAYITEM::SetItem(SNDITEM* item)
{
  this->item = item;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         SNDOPENALSOURCE* SNDOPENALPLAYITEM::GetSource()
* @brief      GetSource
* @ingroup    SOUND
* 
* @return     SNDOPENALSOURCE* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
SNDOPENALSOURCE* SNDOPENALPLAYITEM::GetSource()
{
  return source;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void SNDOPENALPLAYITEM::SetSource(SNDOPENALSOURCE* source)
* @brief      SetSource
* @ingroup    SOUND
* 
* @param[in]  source : 
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void SNDOPENALPLAYITEM::SetSource(SNDOPENALSOURCE* source)
{
  this->source = source;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool SNDOPENALPLAYITEM::Delete()
* @brief      Delete
* @ingroup    SOUND
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool SNDOPENALPLAYITEM::Delete()
{
  item = NULL;

  if(source)
    {
      delete source;
      source = NULL;
    }   

  return true;
}
  

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void SNDOPENALPLAYITEM::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    SOUND
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void SNDOPENALPLAYITEM::Clean()
{
  item      = NULL;
  source    = NULL;
}


#pragma endregion


#pragma region CLASS_SNDOPENALFACTORY


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         SNDOPENALFACTORY::SNDOPENALFACTORY()
* @brief      Constructor
* @ingroup    SOUND
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
SNDOPENALFACTORY::SNDOPENALFACTORY()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         SNDOPENALFACTORY::~SNDOPENALFACTORY()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    SOUND
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
SNDOPENALFACTORY::~SNDOPENALFACTORY()
{
  End();

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool SNDOPENALFACTORY::Ini()
* @brief      Ini
* @ingroup    SOUND
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool SNDOPENALFACTORY::Ini()
{
  device = alcOpenDevice("");
  if(!device) 
    {
      return false;
    }
    
  ALCenum error;

  context   = alcCreateContext(device, NULL);
  error     = alGetError();

  if(!alcMakeContextCurrent(context)) 
    {
      return false;
    }

  maxchannels   = 16;
  mastervolume  = 1.0f;

  playmutex = GEN_XFACTORY.Create_Mutex();
  if(!playmutex)
    {
      return false;
    }
  
  playthread = GEN_XFACTORY.CreateThread(XTHREADGROUPID_SOUND, __L("SNDOPENALFACTORY::SNDOPENALFACTORY"), SNDOPENALFACTORY::ThreadPlay, this);  
  if(!playthread)
    {
      return false;
    }

  return playthread->Ini();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool SNDOPENALFACTORY::Update()
* @brief      Update
* @ingroup    SOUND
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool SNDOPENALFACTORY::Update()
{  
  if(playmutex)
    {
      playmutex->Lock();
    }

  for(XDWORD c=0; c<soundplayitems.GetSize(); c++)
    {
      SNDOPENALPLAYITEM* playitem = soundplayitems.Get(c);
      if(playitem)
        {
          SNDITEM* item = playitem->GetItem();          
          if(item)
            {  
              switch(item->GetType())
                {
                  case SNDITEM_TYPE_UNKNOWN : break;
                  case SNDITEM_TYPE_NOTE    : Update_Note(playitem); break;
                  case SNDITEM_TYPE_FILE    : Update_File(playitem); break;              
                }
            }
        }
    }

  if(playmutex)
    {
      playmutex->UnLock();
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool SNDOPENALFACTORY::End()
* @brief      End
* @ingroup    SOUND
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool SNDOPENALFACTORY::End()
{  
  if(playthread)
    {
      playthread->End();

      GEN_XFACTORY.DeleteThread(XTHREADGROUPID_SOUND, playthread);
      playthread = NULL;
    }
    
  if(playmutex)
    {
      GEN_XFACTORY.Delete_Mutex(playmutex);
      playmutex = NULL;
    }

  alcMakeContextCurrent(NULL);
  alcDestroyContext(context);
  alcCloseDevice(device);

  soundplayitems.DeleteContents();
  soundplayitems.DeleteAll();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         float SNDOPENALFACTORY::Volume_Get()
* @brief      Volume_Get
* @ingroup    SOUND
* 
* @return     float : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
float SNDOPENALFACTORY::Volume_Get()
{ 
  return 0;                
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool SNDOPENALFACTORY::Volume_Set(float mastervolume)
* @brief      Volume_Set
* @ingroup    SOUND
* 
* @param[in]  mastervolume : 
* s
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool SNDOPENALFACTORY::Volume_Set(float mastervolume)
{    
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         SNDINSTANCE* SNDOPENALFACTORY::Sound_Play(SNDITEM* item)
* @brief      Sound_Play
* @ingroup    SOUND
* 
* @param[in]  element : 
* 
* @return     SNDINSTANCE* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool SNDOPENALFACTORY::Sound_Play(SNDITEM* item, SNDPLAYCFG* playCFG)
{   
  if(!SNDFACTORY::Sound_Play(item, playCFG))
    {
      return false;
    }

  if(soundplayitems.GetSize() >= maxchannels)
    {
      return false;
    }

  SNDOPENALSOURCE* source = new SNDOPENALSOURCE();
  if(!source)
    {
      return NULL;
    }

  SNDOPENALPLAYITEM* soundplayitem = new SNDOPENALPLAYITEM();
  if(!soundplayitem) 
    {
      delete source;
      return NULL;
    }

  soundplayitem->SetItem(item);
  soundplayitem->SetSource(source);  

  return soundplayitems.Add(soundplayitem);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool SNDOPENALFACTORY::Sound_Stop(SNDITEM* item)
* @brief      Sound_Stop
* @ingroup    SOUND
* 
* @param[in]  item : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool SNDOPENALFACTORY::Sound_Stop(SNDITEM* item)
{  
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         SNDINSTANCE* SNDOPENALFACTORY::Sound_Pause(SNDITEM* item)
* @brief      Sound_Pause
* @ingroup    SOUND
* 
* @param[in]  element : 
* 
* @return     SNDINSTANCE* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool SNDOPENALFACTORY::Sound_Pause(SNDITEM* item)
{
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool SNDOPENALFACTORY::Sound_StopAll()
* @brief      Sound_StopAll
* @ingroup    SOUND
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool SNDOPENALFACTORY::Sound_StopAll()
{  
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XMUTEX* SNDOPENALFACTORY::GetPlayMutex()
* @brief      GetPlayMutex
* @ingroup    SOUND
* 
* @return     XMUTEX* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XMUTEX* SNDOPENALFACTORY::GetPlayMutex()
{
  return playmutex;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XVECTOR<SNDOPENALPLAYITEM*>* SNDOPENALFACTORY::GetSoundPlayItems()
* @brief      GetSoundPlayItems
* @ingroup    SOUND
* 
* @return     XVECTOR<SNDOPENALPLAYITEM*>* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XVECTOR<SNDOPENALPLAYITEM*>* SNDOPENALFACTORY::GetSoundPlayItems()
{
  return &soundplayitems;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool SNDOPENALFACTORY::Update_Note(SNDOPENALPLAYITEM* playitem)
* @brief      Update_Note
* @ingroup    SOUND
* 
* @param[in]  playitem : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool SNDOPENALFACTORY::Update_Note(SNDOPENALPLAYITEM* playitem)
{
  if(!playitem)
    {
      return false; 
    }

  SNDITEM*         item      = playitem->GetItem();
  SNDOPENALSOURCE* source    = playitem->GetSource();

  if(!item || !source)
    {
      return false;
    }

  SNDNOTE*         soundnote = item->GetSoundNote();
  if(!soundnote)
    {
      return false;
    }
  
  switch(item->GetStatus())
    {
      case SNDITEM_STATUS_NONE    : break;

      case SNDITEM_STATUS_INI     : { soundnote->GetTimerPlay()->Reset();
                                      source->GetBuffer()->GenerateNote(soundnote->GetFrequency(), soundnote->GetDuration());                                     

                                      source->Play();  

                                      GEN_XSLEEP.MilliSeconds((int)(4*1000));

                                      source->Stop(); 
                                      source->GetBuffer()->Delete();

                                    }
                                    break;

      case SNDITEM_STATUS_STOP    : break;
      case SNDITEM_STATUS_PLAY    : break;
      case SNDITEM_STATUS_PAUSE   : break;
      case SNDITEM_STATUS_END     : break;
    }
  
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool SNDOPENALFACTORY::Update_File(SNDOPENALPLAYITEM* playitem)
* @brief      Update_File
* @ingroup    SOUND
* 
* @param[in]  playitem : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool SNDOPENALFACTORY::Update_File(SNDOPENALPLAYITEM* playitem)
{
  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void SNDOPENALFACTORY::ThreadPlay(void* param)
* @brief      ThreadPlay
* @ingroup    SOUND
* 
* @param[in]  param : 
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void SNDOPENALFACTORY::ThreadPlay(void* param)
{
  SNDOPENALFACTORY* sndopenal = (SNDOPENALFACTORY*)param;
  if(!sndopenal) return;  

  sndopenal->Update();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void SNDOPENALFACTORY::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    SOUND
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void SNDOPENALFACTORY::Clean()
{        
  device        = NULL;
  context       = NULL;

  mastervolume  = 0.0f;
  maxchannels   = 0;
                                        
  playthread    = NULL;
  playmutex     = NULL;                                                    
}


#pragma endregion


#pragma endregion

