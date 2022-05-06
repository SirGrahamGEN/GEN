/**-------------------------------------------------------------------------------------------------------------------
*
* @file       SNDStreamElement.cpp
*
* @class      SNDSTREAMELEMENT
* @brief      Sound Stream element class
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

#include "SNDStreamElement.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         SNDSTREAMELEMENT::SNDSTREAMELEMENT()
* @brief      Constructor
* @ingroup    SOUND
*
* @return     Does not return anything. 
*
* --------------------------------------------------------------------------------------------------------------------*/
SNDSTREAMELEMENT::SNDSTREAMELEMENT() : SNDELEMENT()
{ 
  Clean(); 
  isstream = true;                       
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         SNDSTREAMELEMENT::~SNDSTREAMELEMENT()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    SOUND
*
* @return     Does not return anything. 
*
* --------------------------------------------------------------------------------------------------------------------*/
SNDSTREAMELEMENT::~SNDSTREAMELEMENT()                                            
{ 
  Clean();                                        
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void SNDSTREAMELEMENT::SetAttributes(XWORD channels, XWORD freq)
* @brief      SetAttributes
* @ingroup    SOUND
*
* @param[in]  channels : 
* @param[in]  freq : 
*
* @return     void : does not return anything. 
*
* --------------------------------------------------------------------------------------------------------------------*/
void SNDSTREAMELEMENT::SetAttributes(XWORD channels, XWORD freq)                  
{ 
  this->channels  = channels; 
  this->freq      = freq;   
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void SNDSTREAMELEMENT::Play()
* @brief      Play
* @ingroup    SOUND
*
* @return     void : does not return anything. 
*
* --------------------------------------------------------------------------------------------------------------------*/
void SNDSTREAMELEMENT::Play()                                            
{                                                 

}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void SNDSTREAMELEMENT::SetFile(SNDFILE* file)
* @brief      SetFile
* @ingroup    SOUND
*
* @param[in]  file : 
*
* @return     void : does not return anything. 
*
* --------------------------------------------------------------------------------------------------------------------*/
void SNDSTREAMELEMENT::SetFile(SNDFILE* file)
{ 
  this->file = file;                              
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         SNDFILE* SNDSTREAMELEMENT::GetFile()
* @brief      GetFile
* @ingroup    SOUND
*
* @return     SNDFILE* : 
*
* --------------------------------------------------------------------------------------------------------------------*/
SNDFILE* SNDSTREAMELEMENT::GetFile()
{ 
  return file;                                    
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void SNDSTREAMELEMENT::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    SOUND
*
* @return     void : does not return anything. 
*
* --------------------------------------------------------------------------------------------------------------------*/
void SNDSTREAMELEMENT::Clean()
{
  channels  = 0;
  freq      = 0;
  file      = NULL;
}



