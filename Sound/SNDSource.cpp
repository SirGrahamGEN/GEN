/**-------------------------------------------------------------------------------------------------------------------
*
* @file       SNDSource.cpp
*
* @class      SNDSOURCE
* @brief      Sound source class
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

/*---- PRECOMPILATION CONTROL ----------------------------------------------------------------------------------------*/

#include "GEN_Defines.h"


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "SNDInstance.h"

#include "SNDSource.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         SNDSOURCE::SNDSOURCE()
* @brief      Constructor
* @ingroup    SOUND
*
* @return     Does not return anything. 
*
* --------------------------------------------------------------------------------------------------------------------*/
SNDSOURCE::SNDSOURCE()
{ 
  Clean();                          
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         SNDSOURCE::~SNDSOURCE()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    SOUND
*
* @return     Does not return anything. 
*
* --------------------------------------------------------------------------------------------------------------------*/
SNDSOURCE::~SNDSOURCE()
{ 
  Clean();                          
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void SNDSOURCE::SetInstance(SNDINSTANCE* instance)
* @brief      SetInstance
* @ingroup    SOUND
*
* @param[in]  instance : 
*
* @return     void : does not return anything. 
*
* --------------------------------------------------------------------------------------------------------------------*/
void SNDSOURCE::SetInstance(SNDINSTANCE* instance)
{ 
  this->instance = instance;  
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         SNDINSTANCE* SNDSOURCE::GetInstance()
* @brief      GetInstance
* @ingroup    SOUND
*
* @return     SNDINSTANCE* : 
*
* --------------------------------------------------------------------------------------------------------------------*/
SNDINSTANCE* SNDSOURCE::GetInstance()
{ 
  return this->instance;         
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool SNDSOURCE::IsInstancePlaying()
* @brief      IsInstancePlaying
* @ingroup    SOUND
*
* @return     bool : true if is succesful. 
*
* --------------------------------------------------------------------------------------------------------------------*/
bool SNDSOURCE::IsInstancePlaying()
{
  if(instance)
    {
      return instance->IsPlaying();
    }

  return false;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void SNDSOURCE::SetElement(SNDELEMENT* element)
* @brief      SetElement
* @ingroup    SOUND
*
* @param[in]  element : 
*
* @return     void : does not return anything. 
*
* --------------------------------------------------------------------------------------------------------------------*/
void SNDSOURCE::SetElement(SNDELEMENT* element)           
{ 
  this->element = element;          
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         SNDELEMENT* SNDSOURCE::GetElement()
* @brief      GetElement
* @ingroup    SOUND
*
* @return     SNDELEMENT* : 
*
* --------------------------------------------------------------------------------------------------------------------*/
SNDELEMENT* SNDSOURCE::GetElement()                              
{ 
  return this->element;             
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void SNDSOURCE::Stop()
* @brief      Stop
* @ingroup    SOUND
*
* @return     void : does not return anything. 
*
* --------------------------------------------------------------------------------------------------------------------*/
void SNDSOURCE::Stop()                              
{
                                   
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void SNDSOURCE::Pause()
* @brief      Pause
* @ingroup    SOUND
*
* @return     void : does not return anything. 
*
* --------------------------------------------------------------------------------------------------------------------*/
void SNDSOURCE::Pause()
{                                   

}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void SNDSOURCE::UnPause()
* @brief      UnPause
* @ingroup    SOUND
*
* @return     void : does not return anything. 
*
* --------------------------------------------------------------------------------------------------------------------*/
void SNDSOURCE::UnPause()                              
{                                   

}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void SNDSOURCE::SetLoop(bool loop)
* @brief      SetLoop
* @ingroup    SOUND
*
* @param[in]  loop : 
*
* @return     void : does not return anything. 
*
* --------------------------------------------------------------------------------------------------------------------*/
void SNDSOURCE::SetLoop(bool loop)                     
{

}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool SNDSOURCE::IsPLaying()
* @brief      IsPLaying
* @ingroup    SOUND
*
* @return     bool : true if is succesful. 
*
* --------------------------------------------------------------------------------------------------------------------*/
bool SNDSOURCE::IsPLaying()                              
{ 
  return false;                     
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool SNDSOURCE::IsStopped()
* @brief      IsStopped
* @ingroup    SOUND
*
* @return     bool : true if is succesful. 
*
* --------------------------------------------------------------------------------------------------------------------*/
bool SNDSOURCE::IsStopped()                              
{ 
  return false;                     
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool SNDSOURCE::IsPaused()
* @brief      IsPaused
* @ingroup    SOUND
*
* @return     bool : true if is succesful. 
*
* --------------------------------------------------------------------------------------------------------------------*/
bool SNDSOURCE::IsPaused()                              
{ 
  return false;                     
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void SNDSOURCE::SetVolume(float volume)
* @brief      SetVolume
* @ingroup    SOUND
*
* @param[in]  volume : 
*
* @return     void : does not return anything. 
*
* --------------------------------------------------------------------------------------------------------------------*/
void SNDSOURCE::SetVolume(float volume)                  
{ 

}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         float SNDSOURCE::GetVolume()
* @brief      GetVolume
* @ingroup    SOUND
*
* @return     float : 
*
* --------------------------------------------------------------------------------------------------------------------*/
float SNDSOURCE::GetVolume()
{ 
  return 0.0f;                      
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void SNDSOURCE::SetPitch(float pitch)
* @brief      SetPitch
* @ingroup    SOUND
*
* @param[in]  pitch : 
*
* @return     void : does not return anything. 
*
* --------------------------------------------------------------------------------------------------------------------*/
void SNDSOURCE::SetPitch(float pitch)                   
{

}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         float SNDSOURCE::GetPitch()
* @brief      GetPitch
* @ingroup    SOUND
*
* @return     float : 
*
* --------------------------------------------------------------------------------------------------------------------*/
float SNDSOURCE::GetPitch()                              
{ 
  return 0.0f;                      
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void SNDSOURCE::SetSecondsOffset(float seconds)
* @brief      SetSecondsOffset
* @ingroup    SOUND
*
* @param[in]  seconds : 
*
* @return     void : does not return anything. 
*
* --------------------------------------------------------------------------------------------------------------------*/
void SNDSOURCE::SetSecondsOffset(float seconds)                 
{                                   

}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void SNDSOURCE::SetSamplesOffset(int samples)
* @brief      SetSamplesOffset
* @ingroup    SOUND
*
* @param[in]  samples : 
*
* @return     void : does not return anything. 
*
* --------------------------------------------------------------------------------------------------------------------*/
void SNDSOURCE::SetSamplesOffset(int samples)                   
{                                   

}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void SNDSOURCE::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    SOUND
*
* @return     void : does not return anything. 
*
* --------------------------------------------------------------------------------------------------------------------*/
void SNDSOURCE::Clean()
{
  element   = NULL;
  instance  = NULL;
}




