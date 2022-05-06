/**-------------------------------------------------------------------------------------------------------------------
*
* @file       SNDElement.cpp
*
* @class      SNDELEMENT
* @brief      Sound Element class
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

#include "SNDElement.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         SNDELEMENT::SNDELEMENT()
* @brief      Constructor
* @ingroup    SOUND
*
* @return     Does not return anything. 
*
* --------------------------------------------------------------------------------------------------------------------*/
SNDELEMENT::SNDELEMENT()
{
  Clean();

  volume  = 1.0f;
  pitch   = 1.0f;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         SNDELEMENT::~SNDELEMENT()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    SOUND
*
* @return     Does not return anything. 
*
* --------------------------------------------------------------------------------------------------------------------*/
SNDELEMENT::~SNDELEMENT()

{
  Clean();
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* SNDELEMENT::GetID()
* @brief      GetID
* @ingroup    SOUND
*
* @return     XSTRING* : 
*
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* SNDELEMENT::GetID()
{
  return &ID;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void SNDELEMENT::SetLoop(bool loop)
* @brief      SetLoop
* @ingroup    SOUND
*
* @param[in]  loop : 
*
* @return     void : does not return anything. 
*
* --------------------------------------------------------------------------------------------------------------------*/
void SNDELEMENT::SetLoop(bool loop)
{ 
  this->loop = loop;          
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool SNDELEMENT::GetLoop()
* @brief      GetLoop
* @ingroup    SOUND
*
* @return     bool : true if is succesful. 
*
* --------------------------------------------------------------------------------------------------------------------*/
bool SNDELEMENT::GetLoop()                              
{ 
  return loop;                 
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void SNDELEMENT::SetVolume(float volume)
* @brief      SetVolume
* @ingroup    SOUND
*
* @param[in]  volume : 
*
* @return     void : does not return anything. 
*
* --------------------------------------------------------------------------------------------------------------------*/
void SNDELEMENT::SetVolume(float volume)                  
{ 
  this->volume = volume;      
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         float SNDELEMENT::GetVolume()
* @brief      GetVolume
* @ingroup    SOUND
*
* @return     float : 
*
* --------------------------------------------------------------------------------------------------------------------*/
float SNDELEMENT::GetVolume()                              
{ 
  return volume;             
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void SNDELEMENT::SetPitch(float pitch)
* @brief      SetPitch
* @ingroup    SOUND
*
* @param[in]  pitch : 
*
* @return     void : does not return anything. 
*
* --------------------------------------------------------------------------------------------------------------------*/
void SNDELEMENT::SetPitch(float pitch)                   
{
  this->pitch = pitch;        
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         float SNDELEMENT::GetPitch()
* @brief      GetPitch
* @ingroup    SOUND
*
* @return     float : 
*
* --------------------------------------------------------------------------------------------------------------------*/
float SNDELEMENT::GetPitch()                              
{ 
  return pitch;               
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void SNDELEMENT::SetDuration(float duration)
* @brief      SetDuration
* @ingroup    SOUND
*
* @param[in]  duration : 
*
* @return     void : does not return anything. 
*
* --------------------------------------------------------------------------------------------------------------------*/
void SNDELEMENT::SetDuration(float duration)                
{ 
  this->duration = duration;  
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         float SNDELEMENT::GetDuration()
* @brief      GetDuration
* @ingroup    SOUND
*
* @return     float : 
*
* --------------------------------------------------------------------------------------------------------------------*/
float SNDELEMENT::GetDuration()                              
{ 
  return this->duration;      
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void SNDELEMENT::SetSamples(int samples)
* @brief      SetSamples
* @ingroup    SOUND
*
* @param[in]  samples : 
*
* @return     void : does not return anything. 
*
* --------------------------------------------------------------------------------------------------------------------*/
void SNDELEMENT::SetSamples(int samples)                   
{ 
  this->samples = samples;    
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int SNDELEMENT::GetSamples()
* @brief      GetSamples
* @ingroup    SOUND
*
* @return     int : 
*
* --------------------------------------------------------------------------------------------------------------------*/
int SNDELEMENT::GetSamples()                              
{ 
  return this->samples;       
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool SNDELEMENT::IsStream()
* @brief      IsStream
* @ingroup    SOUND
*
* @return     bool : true if is succesful. 
*
* --------------------------------------------------------------------------------------------------------------------*/
bool SNDELEMENT::IsStream()                              
{ 
  return isstream;            
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void SNDELEMENT::SetFile(SNDFILE* file)
* @brief      SetFile
* @ingroup    SOUND
*
* @param[in]  file : 
*
* @return     void : does not return anything. 
*
* --------------------------------------------------------------------------------------------------------------------*/
void SNDELEMENT::SetFile(SNDFILE* file)                 
{ 
  this->file = file;          
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         SNDFILE* SNDELEMENT::GetFile()
* @brief      GetFile
* @ingroup    SOUND
*
* @return     SNDFILE* : 
*
* --------------------------------------------------------------------------------------------------------------------*/
SNDFILE* SNDELEMENT::GetFile()
{
  return this->file;          
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void SNDELEMENT::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    SOUND
*
* @return     void : does not return anything. 
*
* --------------------------------------------------------------------------------------------------------------------*/
void SNDELEMENT::Clean()
{
  file      = NULL;

  loop      = false;
  volume    = 0.0f;
  pitch     = 0.0f;
  duration  = 0.0f;
  samples   = 0;

  isstream  = false;
}