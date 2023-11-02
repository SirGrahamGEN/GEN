/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       SNDFactory.cpp
* 
* @class      SNDFACTORY
* @brief      Sound Factory class
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

#include "SNDFactory.h"

#include "SNDFactory_XEvent.h"
#include "SNDItem.h"
#include "SNDFile.h"
#include "SNDNote.h"

#include "XMemory_Control.h"

#pragma endregion


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

SNDFACTORY* SNDFACTORY::instance = NULL;

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         SNDFACTORY::SNDFACTORY()
* @brief      Constructor
* @ingroup    SOUND
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
SNDFACTORY::SNDFACTORY()
{
  Clean();

  RegisterEvent(SNDFACTORY_XEVENT_TYPE_STOP);
  RegisterEvent(SNDFACTORY_XEVENT_TYPE_PLAY);

  sounditems.SetIsMulti(false);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         SNDFACTORY::~SNDFACTORY()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    SOUND
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
SNDFACTORY::~SNDFACTORY()
{
  DeRegisterEvent(SNDFACTORY_XEVENT_TYPE_STOP);
  DeRegisterEvent(SNDFACTORY_XEVENT_TYPE_PLAY);

  End();

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool SNDFACTORY::GetIsInstanced()
* @brief      GetIsInstanced
* @ingroup    SOUND
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool SNDFACTORY::GetIsInstanced()
{
  return (instance!=NULL);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         SNDFACTORY& SNDFACTORY::GetInstance()
* @brief      GetInstance
* @ingroup    SOUND
* 
* @return     SNDFACTORY& : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
SNDFACTORY& SNDFACTORY::GetInstance()
{
  if(!instance) instance = new SNDFACTORY();

  return (*instance);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool SNDFACTORY::SetInstance(SNDFACTORY* _instance)
* @brief      SetInstance
* @ingroup    SOUND
* 
* @param[in]  _instance : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool SNDFACTORY::SetInstance(SNDFACTORY* _instance)
{
  if(!_instance) return false;

  instance = _instance;

  return (instance)?true:false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool SNDFACTORY::DelInstance()
* @brief      DelInstance
* @ingroup    SOUND
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool SNDFACTORY::DelInstance()
{
  if(!instance) return false;

  delete instance;
  instance = NULL;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool SNDFACTORY::Ini()
* @brief      Ini
* @ingroup    SOUND
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool SNDFACTORY::Ini()
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool SNDFACTORY::Update()
* @brief      Update
* @ingroup    SOUND
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool SNDFACTORY::Update()
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool SNDFACTORY::End()
* @brief      End
* @ingroup    SOUND
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool SNDFACTORY::End()
{
  DeleteAllItems();

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         float SNDFACTORY::Volume_Get()
* @brief      Volume_Get
* @ingroup    SOUND
* 
* @return     float : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
float SNDFACTORY::Volume_Get()
{ 
  return 0.0f;                      
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool SNDFACTORY::Volume_Set(float volume)
* @brief      Volume_Set
* @ingroup    SOUND
* 
* @param[in]  volume : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool SNDFACTORY::Volume_Set(float volume)
{                                   
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool SNDFACTORY::Sound_Play(SNDITEM* item, SNDPLAYCFG* playCFG, int ntimestoplay)
* @brief      Sound_Play
* @ingroup    SOUND
* 
* @param[in]  item : 
* @param[in]  playCFG : 
* @param[in]  ntimestoplay : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool SNDFACTORY::Sound_Play(SNDITEM* item, SNDPLAYCFG* playCFG, int ntimestoplay)                                   
{ 
  if(!item)
    {
      return false;
    }

  if(playCFG)
    {
      item->SetPlayCFG((*playCFG));
    }

  item->SetNTimesToPlay(ntimestoplay);

  sounditems.Add(item);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool SNDFACTORY::Sound_Pause(SNDITEM* item)
* @brief      Sound_Pause
* @ingroup    SOUND
* 
* @param[in]  element : 
* 
* @return     bool : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool SNDFACTORY::Sound_Pause(SNDITEM* item)                                   
{ 
  return NULL;                      
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool SNDFACTORY::Sound_Stop(SNDITEM* item)
* @brief      Sound_Stop
* @ingroup    SOUND
* 
* @param[in]  element : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool SNDFACTORY::Sound_Stop(SNDITEM* item)                                   
{                                     
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool SNDFACTORY::Sound_StopAll()
* @brief      Sound_StopAll
* @ingroup    SOUND
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool SNDFACTORY::Sound_StopAll()                                                      
{ 
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool SNDFACTORY::Sound_WaitToEnd(SNDITEM* item, int maxtimeout, SNDFACTORY_WAITFUNCTION waitfunction)
* @brief      Sound_WaitToEnd
* @ingroup    SOUND
* 
* @param[in]  item : 
* @param[in]  maxtimeout : 
* @param[in]  waitfunction : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool SNDFACTORY::Sound_WaitToEnd(SNDITEM* item, int maxtimeout, SNDFACTORY_WAITFUNCTION waitfunction)
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool SNDFACTORY::Sound_WaitAllToEnd(int maxtimeout, SNDFACTORY_WAITFUNCTION waitfunction)
* @brief      Sound_WaitAllToEnd
* @ingroup    SOUND
* 
* @param[in]  maxtimeout : 
* @param[in]  waitfunction : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool SNDFACTORY::Sound_WaitAllToEnd(int maxtimeout, SNDFACTORY_WAITFUNCTION waitfunction)
{
  return false;
}  


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         SNDITEM* SNDFACTORY::CreateItem(XCHAR* path)
* @brief      CreateItem
* @ingroup    SOUND
* 
* @param[in]  path : 
* 
* @return     SNDITEM* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
SNDITEM* SNDFACTORY::CreateItem(XCHAR* path)  
{
  if(!path)
    {
      return NULL;
    }

  SNDITEM* item = new SNDITEM();
  if(!item)
    {
      return NULL;
    }

  item->SetType(SNDITEM_TYPE_FILE);

  item->GetID()->Set(path);
  if(item->GetID()->IsEmpty())
    {
      return NULL;
    }

  SNDFILE* soundfile = SNDFILE::Create(path);
  if(!soundfile)
    {
      delete item;
      return NULL;
    }

  item->SetStatus(SNDITEM_STATUS_INI);
  item->SetSoundFile(soundfile);
  
  return item;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         SNDITEM* SNDFACTORY::CreateItem(XPATH& xpath)
* @brief      CreateItem
* @ingroup    SOUND
* 
* @param[in]  xpath : 
* 
* @return     SNDITEM* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
SNDITEM* SNDFACTORY::CreateItem(XPATH& xpath)
{
  return CreateItem(xpath.Get());
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         SNDITEM* SNDFACTORY::CreateItem(XDWORD frecuency, XDWORD duration)
* @brief      CreateItem
* @ingroup    SOUND
* 
* @param[in]  frecuency : 
* @param[in]  duration : 
* 
* @return     SNDITEM* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
SNDITEM* SNDFACTORY::CreateItem(XDWORD frecuency, XDWORD duration)
{
  if((!frecuency) || (!duration))
    {
      return NULL;
    }

  SNDITEM* item = new SNDITEM();
  if(!item)
    {
      return NULL;
    }

  item->SetType(SNDITEM_TYPE_NOTE);

  item->GetID()->Format(__L("frec: %d (Hz) - time: %d (msec)"), frecuency, duration);

  SNDNOTE* note = new SNDNOTE();
  if(!note)
    {
      delete item;
      return NULL;
    }

  note->SetFrequency(frecuency);
  note->SetDuration(duration);

  item->SetStatus(SNDITEM_STATUS_INI);
  item->SetSoundNote(note);
  
  return item;
}
    

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XVECTOR<SNDITEM*>* SNDFACTORY::GetItems()
* @brief      GetItems
* @ingroup    SOUND
* 
* @return     XVECTOR<SNDITEM*>* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XVECTOR<SNDITEM*>* SNDFACTORY::GetItems()
{
  return &sounditems;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool SNDFACTORY::DeleteAllItems()
* @brief      DeleteAllItems
* @ingroup    SOUND
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool SNDFACTORY::DeleteAllItems()
{
  if(sounditems.IsEmpty())
    {
      return false; 
    }

  sounditems.DeleteContents();
  sounditems.DeleteAll();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool SNDFACTORY::Sound_IsAnyActive()
* @brief      Sound_IsAnyActive
* @ingroup    SOUND
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool SNDFACTORY::Sound_IsAnyActive()
{ 
  XDWORD counter = 0;

  for(XDWORD c=0; c<sounditems.GetSize(); c++)
    {
      SNDITEM* item = sounditems.Get(c);
      if(item)
        {
          if(item->GetStatus() != SNDITEM_STATUS_END)       
            {
              counter++;
            }
        }
    }

  return counter?true:false;                     
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool SNDFACTORY::Sound_IsAnyPlaying()
* @brief      Sound_IsAnyPlaying
* @ingroup    SOUND
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool SNDFACTORY::Sound_IsAnyPlaying()
{ 
  for(XDWORD c=0; c<sounditems.GetSize(); c++)
    {
      SNDITEM* item = sounditems.Get(c);
      if(item)
        {
          if(item->GetStatus() == SNDITEM_STATUS_PLAY)       
            {
              return true;
            }
        }
    }

  return false;                     
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void SNDFACTORY::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    SOUND
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void SNDFACTORY::Clean()
{
  instance = NULL;
}


#pragma endregion

