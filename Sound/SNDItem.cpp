/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       SNDItem.cpp
* 
* @class      SNDITEM
* @brief      Sound Item class
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

#include "SNDItem.h"

#include "XFactory.h"
#include "XTimer.h"

#include "XMemory_Control.h"

#pragma endregion


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         SNDITEM::SNDITEM()
* @brief      Constructor
* @ingroup    SOUND
*
* --------------------------------------------------------------------------------------------------------------------*/
SNDITEM::SNDITEM()
{
  Clean();

  timerplay = GEN_XFACTORY.CreateTimer();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         SNDITEM::~SNDITEM()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    SOUND
*
* --------------------------------------------------------------------------------------------------------------------*/
SNDITEM::~SNDITEM()
{
  if(soundfile)
    {
      delete soundfile;
      soundfile = NULL;
    }

  if(soundnote)
    {
      delete soundnote;
      soundnote = NULL;
    }

  if(timerplay)
    {
      GEN_XFACTORY.DeleteTimer(timerplay);
    }

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         SNDITEM_TYPE SNDITEM::GetType()
* @brief      GetType
* @ingroup    SOUND
* 
* @return     SNDITEM_TYPE : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
SNDITEM_TYPE SNDITEM::GetType()
{
  return type;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void SNDITEM::SetType(SNDITEM_TYPE type)
* @brief      SetType
* @ingroup    SOUND
* 
* @param[in]  type : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void SNDITEM::SetType(SNDITEM_TYPE type)
{
  this->type = type;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool SNDITEM::GetType(XSTRING& typestr)
* @brief      GetType
* @ingroup    SOUND
* 
* @param[in]  typestr : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool SNDITEM::GetType(XSTRING& typestr)
{
  bool status = true;

  typestr.Empty();

  switch(type)
    {
      case SNDITEM_TYPE_UNKNOWN : 
                        default : status = false; break;

      case SNDITEM_TYPE_FILE    : typestr = __L("File");    break;
      case SNDITEM_TYPE_NOTE    : typestr = __L("Note");    break;
    }

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* SNDITEM::GetID()
* @brief      GetID
* @ingroup    SOUND
*
* @return     XSTRING* : 
*
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* SNDITEM::GetID()
{
  return &ID;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         SNDITEM_STATUS SNDITEM::GetStatus()
* @brief      GetStatus
* @ingroup    SOUND
* 
* @return     SNDITEM_STATUS : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
SNDITEM_STATUS SNDITEM::GetStatus()
{
  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void SNDITEM::SetStatus(SNDITEM_STATUS status)
* @brief      SetStatus
* @ingroup    SOUND
* 
* @param[in]  status : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void SNDITEM::SetStatus(SNDITEM_STATUS status)
{
  this->status = status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool SNDITEM::GetStatus(XSTRING& statusstr)
* @brief      GetStatus
* @ingroup    SOUND
* 
* @param[in]  statusstr : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool SNDITEM::GetStatus(XSTRING& statusstr)
{
  bool result = true;

  statusstr.Empty();

  switch(status)
    {
      case SNDITEM_STATUS_NONE    : statusstr = __L("None");    break;                        
      case SNDITEM_STATUS_INI     : statusstr = __L("Ini");     break;             
      case SNDITEM_STATUS_STOP    : statusstr = __L("Stop");    break;          
      case SNDITEM_STATUS_PLAY    : statusstr = __L("Play");    break;         
      case SNDITEM_STATUS_PAUSE   : statusstr = __L("Pause");   break;            
      case SNDITEM_STATUS_END     : statusstr = __L("End");     break;  
                         default  : result = false;             break;             
    }

  return result;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDWORD SNDITEM::GetNTimesPlayed()
* @brief      GetNTimesPlayed
* @ingroup    SOUND
* 
* @return     XDWORD : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD SNDITEM::GetNTimesPlayed()
{
  return ntimesplayed;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void SNDITEM::AddOneNTimesPlayed()
* @brief      AddOneNTimesPlayed
* @ingroup    SOUND
* 
* --------------------------------------------------------------------------------------------------------------------*/
void SNDITEM::AddOneNTimesPlayed()
{
  ntimesplayed++;
}

    
/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         int SNDITEM::GetNTimesToPlay()
* @brief      GetNTimesToPlay
* @ingroup    SOUND
* 
* @return     int : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
int SNDITEM::GetNTimesToPlay()
{
  return ntimestoplay;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void SNDITEM::SetNTimesToPlay(int ntimestoplay)
* @brief      SetNTimesToPlay
* @ingroup    SOUND
* 
* @param[in]  ntimestoplay : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void SNDITEM::SetNTimesToPlay(int ntimestoplay)
{
  this->ntimestoplay = ntimestoplay;  
}
 

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         int SNDITEM::GetCounterPlay()
* @brief      GetCounterPlay
* @ingroup    SOUND
* 
* @return     int : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
int SNDITEM::GetCounterPlay()
{
  return counterplay;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void SNDITEM::SetCounterPlay(int counterplay)
* @brief      SetCounterPlay
* @ingroup    SOUND
* 
* @param[in]  counterplay : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void SNDITEM::SetCounterPlay(int counterplay)
{
  this->counterplay = counterplay;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDWORD SNDITEM::GetPlayingTime()
* @brief      GetPlayingTime
* @ingroup    SOUND
* 
* @return     XDWORD : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD SNDITEM::GetPlayingTime()
{
  return playingtime;
}

    
/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void SNDITEM::SetPlayingTime(XDWORD playingtime)
* @brief      SetPlayingTime
* @ingroup    SOUND
* 
* @param[in]  playingtime : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void SNDITEM::SetPlayingTime(XDWORD playingtime)
{
  this->playingtime = playingtime;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDWORD SNDITEM::GetCurrentPlayingTime()
* @brief      GetCurrentPlayingTime
* @ingroup    SOUND
* 
* @return     XDWORD : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD SNDITEM::GetCurrentPlayingTime()
{
  return currentplayingtime;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void SNDITEM::SetCurrentPlayingTime(XDWORD currentplayingtime)
* @brief      SetCurrentPlayingTime
* @ingroup    SOUND
* 
* @param[in]  currentplayingtime : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void SNDITEM::SetCurrentPlayingTime(XDWORD currentplayingtime)
{
  this->currentplayingtime = currentplayingtime;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XTIMER* SNDITEM::GetTimerPlay()
* @brief      GetTimerPlay
* @ingroup    SOUND
* 
* @return     XTIMER* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XTIMER* SNDITEM::GetTimerPlay()
{
  return timerplay;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDWORD SNDITEM::GetDuration()
* @brief      GetDuration
* @ingroup    SOUND
* 
* @return     XDWORD : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD SNDITEM::GetDuration()
{
  XDWORD duration = 0;

  switch(type)
    {
      case SNDITEM_TYPE_UNKNOWN   : break;

      case SNDITEM_TYPE_NOTE      : if(soundnote)
                                      {
                                        duration = soundnote->GetDuration();
                                      }
                                    break;

      case SNDITEM_TYPE_FILE      : if(soundfile)
                                      {
                                        duration = soundfile->GetDuration();
                                      }
                                    break;
    }

  return duration;
}

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         SNDPLAYCFG* SNDITEM::GetPlayCFG()
* @brief      GetPlayCFG
* @ingroup    SOUND
* 
* @return     SNDPLAYCFG* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
SNDPLAYCFG* SNDITEM::GetPlayCFG()
{
  return &playCFG;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool SNDITEM::SetPlayCFG(SNDPLAYCFG& playCFG)
* @brief      SetPlayCFG
* @ingroup    SOUND
* 
* @param[in]  playCFG : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool SNDITEM::SetPlayCFG(SNDPLAYCFG& playCFG)
{
  return this->playCFG.CopyFrom(playCFG);  
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         SNDFILE* SNDITEM::GetSoundFile()
* @brief      GetSoundFile
* @ingroup    SOUND
* 
* @return     SNDFILE* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
SNDFILE* SNDITEM::GetSoundFile()
{
  return soundfile;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void SNDITEM::SetSoundFile(SNDFILE* soundfile)
* @brief      SetSoundFile
* @ingroup    SOUND
* 
* @param[in]  soundfile : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void SNDITEM::SetSoundFile(SNDFILE* soundfile)
{
  this->soundfile = soundfile;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         SNDNOTE* SNDITEM::GetSoundNote()
* @brief      GetSoundNote
* @ingroup    SOUND
* 
* @return     SNDNOTE* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
SNDNOTE* SNDITEM::GetSoundNote()
{
  return soundnote;
}
    

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void SNDITEM::SetSoundNote(SNDNOTE* soundnote)
* @brief      SetSoundNote
* @ingroup    SOUND
* 
* @param[in]  soundnote : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void SNDITEM::SetSoundNote(SNDNOTE* soundnote)
{
  this->soundnote = soundnote;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void SNDITEM::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    SOUND
*
* --------------------------------------------------------------------------------------------------------------------*/
void SNDITEM::Clean()
{
  type            = SNDITEM_TYPE_UNKNOWN;    
  status          = SNDITEM_STATUS_NONE;

  ntimesplayed    = 0;
  ntimestoplay    = 0;
  counterplay     = 0;

  timerplay       = NULL;

  playingtime     = 0;

  soundfile       = NULL;
  soundnote       = NULL;
}


#pragma endregion


