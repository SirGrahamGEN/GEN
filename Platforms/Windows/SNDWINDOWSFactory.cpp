/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       SNDWindowsFactory.cpp
* 
* @class      SNDWINDOWSFACTORY
* @brief      WINDOWS Sound Factory class
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

#include "SNDWINDOWSFactory.h"

#include "SNDFactory_XEvent.h"

#include "XMemory_Control.h"

#pragma endregion


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         SNDWINDOWSFACTORY::SNDWINDOWSFACTORY()
* @brief      Constructor
* @ingroup    SOUND
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
SNDWINDOWSFACTORY::SNDWINDOWSFACTORY()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         SNDWINDOWSFACTORY::~SNDWINDOWSFACTORY()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    SOUND
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
SNDWINDOWSFACTORY::~SNDWINDOWSFACTORY()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         float SNDWINDOWSFACTORY::Volume_Get()
* @brief      Volume_Get
* @ingroup    SOUND
* 
* @return     float : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
float SNDWINDOWSFACTORY::Volume_Get()
{ 
  return 0.0f;                      
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool SNDWINDOWSFACTORY::Volume_Set(float volume)
* @brief      Volume_Set
* @ingroup    SOUND
* 
* @param[in]  volume : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool SNDWINDOWSFACTORY::Volume_Set(float volume)
{                                   
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         SNDELEMENT* SNDWINDOWSFACTORY::Element_Add(XCHAR* namefile, XCHAR* ID, bool instream)
* @brief      Element_Add
* @ingroup    PLATFORM_WINDOWS
* 
* @param[in]  namefile : 
* @param[in]  ID : 
* @param[in]  instream : 
* 
* @return     SNDELEMENT* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
SNDELEMENT* SNDWINDOWSFACTORY::Element_Add(XCHAR* namefile, XCHAR* ID, bool instream)
{
  return NULL;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         SNDELEMENT* SNDWINDOWSFACTORY::Element_Get(XCHAR* namefile, bool instream)
* @brief      Element_Get
* @ingroup    SOUND
* 
* @param[in]  namefile : 
* @param[in]  instream : 
* 
* @return     SNDELEMENT* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
SNDELEMENT* SNDWINDOWSFACTORY::Element_Get(XCHAR* namefile, bool instream)
{
  return NULL;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool SNDWINDOWSFACTORY::Element_Del(SNDELEMENT* element)
* @brief      Element_Del
* @ingroup    SOUND
* 
* @param[in]  element : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool SNDWINDOWSFACTORY::Element_Del(SNDELEMENT* element)
{
  return false;
}
   

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         SNDINSTANCE* SNDWINDOWSFACTORY::Sound_Play(SNDELEMENT* element)
* @brief      Sound_Play
* @ingroup    SOUND
* 
* @param[in]  element : 
* 
* @return     SNDINSTANCE* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
SNDINSTANCE* SNDWINDOWSFACTORY::Sound_Play(SNDELEMENT* element)                                   
{ 
  return NULL;                      
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool SNDWINDOWSFACTORY::Sound_Stop(SNDELEMENT* element)
* @brief      Sound_Stop
* @ingroup    SOUND
* 
* @param[in]  element : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool SNDWINDOWSFACTORY::Sound_Stop(SNDELEMENT* element)                                   
{                                   
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         SNDINSTANCE* SNDWINDOWSFACTORY::Sound_Pause(SNDELEMENT* element)
* @brief      Sound_Pause
* @ingroup    SOUND
* 
* @param[in]  element : 
* 
* @return     SNDINSTANCE* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
SNDINSTANCE* SNDWINDOWSFACTORY::Sound_Pause(SNDELEMENT* element)                                   
{ 
  return NULL;                      
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool SNDWINDOWSFACTORY::Sound_IsAnyPlaying()
* @brief      Sound_IsAnyPlaying
* @ingroup    SOUND
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool SNDWINDOWSFACTORY::Sound_IsAnyPlaying()                                                      
{ 
  return false;                     
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool SNDWINDOWSFACTORY::Sound_StopAll()
* @brief      Sound_StopAll
* @ingroup    SOUND
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool SNDWINDOWSFACTORY::Sound_StopAll()                                                      
{ 
  return false;
}
   

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool SNDWINDOWSFACTORY::Sound_Beep(float frecuency, float duration)
* @brief      Sound_Beep
* @ingroup    PLATFORM_WINDOWS
* 
* @param[in]  frecuency : 
* @param[in]  duration : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool SNDWINDOWSFACTORY::Sound_Beep(float frecuency, float duration)
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void SNDWINDOWSFACTORY::Update()
* @brief      Update
* @ingroup    SOUND
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void SNDWINDOWSFACTORY::Update()
{	
	
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void SNDWINDOWSFACTORY::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    SOUND
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void SNDWINDOWSFACTORY::Clean()
{
  
}


#pragma endregion

