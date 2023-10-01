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

#ifdef SND_ACTIVE

/*---- PRECOMPILATION CONTROL ----------------------------------------------------------------------------------------*/

#include "GEN_Defines.h"


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "SND_XEvent.h"

#include "SNDFactory.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

SNDFACTORY* SNDFACTORY::instance = NULL;

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/



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

  RegisterEvent(SND_XEVENT_TYPE_STOP);
  RegisterEvent(SND_XEVENT_TYPE_PLAY);
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
  DeRegisterEvent(SND_XEVENT_TYPE_STOP);
  DeRegisterEvent(SND_XEVENT_TYPE_PLAY);

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
* @fn         bool SNDFACTORY::Beep(float frecuency, float duration)
* @brief      Beep
* @ingroup    SOUND
*
* @param[in]  frecuency : 
* @param[in]  duration : 
*
* @return     bool : true if is succesful. 
*
* --------------------------------------------------------------------------------------------------------------------*/
bool SNDFACTORY::Beep(float frecuency, float duration)
{
  return false;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         SNDELEMENT* SNDFACTORY::Element_Add(XPATH& xpathfile, XSTRING& ID, bool instream)
* @brief      Element_Add
* @ingroup    SOUND
*
* @param[in]  xpathfile : 
* @param[in]  ID : 
* @param[in]  instream : 
*
* @return     SNDELEMENT* : 
*
* --------------------------------------------------------------------------------------------------------------------*/
SNDELEMENT* SNDFACTORY::Element_Add(XPATH& xpathfile, XSTRING& ID, bool instream)
{
  return Element_Add(xpathfile, ID.Get(), instream);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         SNDELEMENT* SNDFACTORY::Element_Add(XPATH& xpathfile, XCHAR* ID, bool instream)
* @brief      Element_Add
* @ingroup    SOUND
*
* @param[in]  xpathfile : 
* @param[in]  ID : 
* @param[in]  instream : 
*
* @return     SNDELEMENT* : 
*
* --------------------------------------------------------------------------------------------------------------------*/
SNDELEMENT* SNDFACTORY::Element_Add(XPATH& xpathfile, XCHAR* ID, bool instream)
{
  return NULL;
}



 
/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         SNDELEMENT* SNDFACTORY::Element_Get(XSTRING& namefile, bool instream)
* @brief      Element_Get
* @ingroup    SOUND
*
* @param[in]  namefile : 
* @param[in]  instream : 
*
* @return     SNDELEMENT* : 
*
* --------------------------------------------------------------------------------------------------------------------*/
SNDELEMENT* SNDFACTORY::Element_Get(XSTRING& namefile, bool instream)
{
  return Element_Get(namefile.Get(), instream);
}


    

/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         SNDELEMENT* SNDFACTORY::Element_Get(XCHAR* namefile, bool instream)
* @brief      Element_Get
* @ingroup    SOUND
*
* @param[in]  namefile : 
* @param[in]  instream : 
*
* @return     SNDELEMENT* : 
*
* --------------------------------------------------------------------------------------------------------------------*/
SNDELEMENT* SNDFACTORY::Element_Get(XCHAR* namefile, bool instream)
{
  return NULL;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool SNDFACTORY::Element_Del(SNDELEMENT* element)
* @brief      Element_Del
* @ingroup    SOUND
*
* @param[in]  element : 
*
* @return     bool : true if is succesful. 
*
* --------------------------------------------------------------------------------------------------------------------*/
bool SNDFACTORY::Element_Del(SNDELEMENT* element)
{
  return false;
}
    


   
/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         SNDINSTANCE* SNDFACTORY::PlaySound(SNDELEMENT* element)
* @brief      PlaySound
* @ingroup    SOUND
*
* @param[in]  element : 
*
* @return     SNDINSTANCE* : 
*
* --------------------------------------------------------------------------------------------------------------------*/
SNDINSTANCE* SNDFACTORY::PlaySound(SNDELEMENT* element)                                   
{ 
  return NULL;                      
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool SNDFACTORY::StopSound(SNDELEMENT* element)
* @brief      StopSound
* @ingroup    SOUND
*
* @param[in]  element : 
*
* @return     bool : true if is succesful. 
*
* --------------------------------------------------------------------------------------------------------------------*/
bool SNDFACTORY::StopSound(SNDELEMENT* element)                                   
{                                   
  return false;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         SNDINSTANCE* SNDFACTORY::PauseSound(SNDELEMENT* element)
* @brief      PauseSound
* @ingroup    SOUND
*
* @param[in]  element : 
*
* @return     SNDINSTANCE* : 
*
* --------------------------------------------------------------------------------------------------------------------*/
SNDINSTANCE* SNDFACTORY::PauseSound(SNDELEMENT* element)                                   
{ 
  return NULL;                      
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool SNDFACTORY::IsAnyPlaying()
* @brief      IsAnyPlaying
* @ingroup    SOUND
*
* @return     bool : true if is succesful. 
*
* --------------------------------------------------------------------------------------------------------------------*/
bool SNDFACTORY::IsAnyPlaying()                                                      
{ 
  return false;                     
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool SNDFACTORY::StopAll()
* @brief      StopAll
* @ingroup    SOUND
*
* @return     bool : true if is succesful. 
*
* --------------------------------------------------------------------------------------------------------------------*/
bool SNDFACTORY::StopAll()                                                      
{ 
  return false;
}
   




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         float SNDFACTORY::GetMasterVolume()
* @brief      GetMasterVolume
* @ingroup    SOUND
*
* @return     float : 
*
* --------------------------------------------------------------------------------------------------------------------*/
float SNDFACTORY::GetMasterVolume()                                                      
{ 
  return 0.0f;                      
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool SNDFACTORY::SetMasterVolume(float mastervolume)
* @brief      SetMasterVolume
* @ingroup    SOUND
*
* @param[in]  mastervolume : 
*
* @return     bool : true if is succesful. 
*
* --------------------------------------------------------------------------------------------------------------------*/
bool SNDFACTORY::SetMasterVolume(float mastervolume)                                    
{                                   
  return false;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         SNDFILE* SNDFACTORY::CreateSoundFile()
* @brief      CreateSoundFile
* @ingroup    SOUND
*
* @return     SNDFILE* : 
*
* --------------------------------------------------------------------------------------------------------------------*/
SNDFILE* SNDFACTORY::CreateSoundFile()
{
  return NULL;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void SNDFACTORY::DeleteSoundFile(SNDFILE* file)
* @brief      DeleteSoundFile
* @ingroup    SOUND
*
* @param[in]  file : 
*
* @return     void : does not return anything. 
*
* --------------------------------------------------------------------------------------------------------------------*/
bool SNDFACTORY::DeleteSoundFile(SNDFILE* file)
{
  return false;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void SNDFACTORY::Update()
* @brief      Update
* @ingroup    SOUND
*
* @return     void : does not return anything. 
*
* --------------------------------------------------------------------------------------------------------------------*/
void SNDFACTORY::Update()
{	
	
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


#endif
