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
  return false;
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
  return Element_Add(xpathfile.Get(), ID, instream);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         SNDELEMENT* SNDFACTORY::Element_Add(XCHAR* xpathfile, XCHAR* ID, bool instream)
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
SNDELEMENT* SNDFACTORY::Element_Add(XCHAR* pathfile, XCHAR* ID, bool instream)
{
  return NULL;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         SNDELEMENT* SNDFACTORY::Element_Get(XSTRING& ID, bool instream)
* @brief      Element_Get
* @ingroup    SOUND
* 
* @param[in]  ID : 
* @param[in]  instream : 
* 
* @return     SNDELEMENT* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
SNDELEMENT* SNDFACTORY::Element_Get(XSTRING& ID, bool instream)
{
  return Element_Get(ID.Get(), instream);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         SNDELEMENT* SNDFACTORY::Element_Get(XCHAR* ID, bool instream)
* @brief      Element_Get
* @ingroup    SOUND
* 
* @param[in]  ID : 
* @param[in]  instream : 
* 
* @return     SNDELEMENT* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
SNDELEMENT* SNDFACTORY::Element_Get(XCHAR* ID, bool instream)
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
* @fn         SNDINSTANCE* SNDFACTORY::Sound_Play(SNDELEMENT* element)
* @brief      Sound_Play
* @ingroup    SOUND
* 
* @param[in]  element : 
* 
* @return     SNDINSTANCE* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
SNDINSTANCE* SNDFACTORY::Sound_Play(SNDELEMENT* element)                                   
{ 
  return NULL;                      
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool SNDFACTORY::Sound_Stop(SNDELEMENT* element)
* @brief      Sound_Stop
* @ingroup    SOUND
* 
* @param[in]  element : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool SNDFACTORY::Sound_Stop(SNDELEMENT* element)                                   
{                                   
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         SNDINSTANCE* SNDFACTORY::Sound_Pause(SNDELEMENT* element)
* @brief      Sound_Pause
* @ingroup    SOUND
* 
* @param[in]  element : 
* 
* @return     SNDINSTANCE* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
SNDINSTANCE* SNDFACTORY::Sound_Pause(SNDELEMENT* element)                                   
{ 
  return NULL;                      
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
* @fn         bool SNDFACTORY::Sound_Note(float frecuency, float duration)
* @brief      Sound_Note
* @ingroup    SOUND
* 
* @param[in]  frecuency : 
* @param[in]  duration : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool SNDFACTORY::Sound_Note(float frecuency, float duration)
{
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

