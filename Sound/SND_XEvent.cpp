/**-------------------------------------------------------------------------------------------------------------------
*
* @file       SND_XEvent.cpp
*
* @class      SND_XEVENT
* @brief      Sound eXtended event class
* @ingroup    SOUND
*
* @copyright  GEN Group. All right reserved.
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
*---------------------------------------------------------------------------------------------------------------------*/

/*---- PRECOMPILATION CONTROL ----------------------------------------------------------------------------------------*/

#include "GEN_Defines.h"


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "SND_XEvent.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         SND_XEVENT::SND_XEVENT(XSUBJECT* subject, XDWORD type, XDWORD family)
* @brief      Constructor
* @ingroup    SOUND
*
* @param[in]  XSUBJECT* : 
* @param[in]   XDWORD type : 
* @param[in]   XDWORD family : 
*
* @return     Does not return anything. 
*
*---------------------------------------------------------------------------------------------------------------------*/
SND_XEVENT::SND_XEVENT(XSUBJECT* subject, XDWORD type, XDWORD family) : XEVENT(subject, type, family)
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         SND_XEVENT::~SND_XEVENT()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    SOUND
*
* @return     Does not return anything. 
*
*---------------------------------------------------------------------------------------------------------------------*/
SND_XEVENT::~SND_XEVENT()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         SND_XEVENT_TYPE SND_XEVENT::GetType()
* @brief      GetType
* @ingroup    SOUND
*
* @return     SND_XEVENT_TYPE : 
*
*---------------------------------------------------------------------------------------------------------------------*/
SND_XEVENT_TYPE SND_XEVENT::GetType()
{ 
  return type;                   
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void SND_XEVENT::SetType(SND_XEVENT_TYPE type)
* @brief      SetType
* @ingroup    SOUND
*
* @param[in]  type : 
*
* @return     void : does not return anything. 
*
*---------------------------------------------------------------------------------------------------------------------*/
void SND_XEVENT::SetType(SND_XEVENT_TYPE type)                                            
{ 
  this->type = type;                   
}
    

    
/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* SND_XEVENT::GetID()
* @brief      GetID
* @ingroup    SOUND
*
* @return     XSTRING* : 
*
*---------------------------------------------------------------------------------------------------------------------*/
XSTRING* SND_XEVENT::GetID()
{ 
  return &ID;                
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         SNDELEMENT* SND_XEVENT::GetElement()
* @brief      GetElement
* @ingroup    SOUND
*
* @return     SNDELEMENT* : 
*
*---------------------------------------------------------------------------------------------------------------------*/
SNDELEMENT* SND_XEVENT::GetElement()                                                                
{ 
  return this->element;          
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void SND_XEVENT::SetElement(SNDELEMENT* sndelement)
* @brief      SetElement
* @ingroup    SOUND
*
* @param[in]  sndelement : 
*
* @return     void : does not return anything. 
*
*---------------------------------------------------------------------------------------------------------------------*/
void SND_XEVENT::SetElement(SNDELEMENT* sndelement)                                          
{ 
  this->element = element;    
}
    

    
/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         SNDSOURCE* SND_XEVENT::GetSource()
* @brief      GetSource
* @ingroup    SOUND
*
* @return     SNDSOURCE* : 
*
*---------------------------------------------------------------------------------------------------------------------*/
SNDSOURCE* SND_XEVENT::GetSource()
{ 
  return this->source;           
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void SND_XEVENT::SetSource(SNDSOURCE* source)
* @brief      SetSource
* @ingroup    SOUND
*
* @param[in]  source : 
*
* @return     void : does not return anything. 
*
*---------------------------------------------------------------------------------------------------------------------*/
void SND_XEVENT::SetSource(SNDSOURCE* source)                                            
{ 
  this->source = source;      
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         SNDINSTANCE* SND_XEVENT::GetInstance()
* @brief      GetInstance
* @ingroup    SOUND
*
* @return     SNDINSTANCE* : 
*
*---------------------------------------------------------------------------------------------------------------------*/
SNDINSTANCE* SND_XEVENT::GetInstance()
{ 
  return this->instance;         
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void SND_XEVENT::SetInstance(SNDINSTANCE* instance)
* @brief      SetInstance
* @ingroup    SOUND
*
* @param[in]  instance : 
*
* @return     void : does not return anything. 
*
*---------------------------------------------------------------------------------------------------------------------*/
void SND_XEVENT::SetInstance(SNDINSTANCE* instance)                                        
{ 
  this->instance = instance;  
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void SND_XEVENT::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    SOUND
*
* @return     void : does not return anything. 
*
*---------------------------------------------------------------------------------------------------------------------*/
void SND_XEVENT::Clean()
{
  type       = SND_XEVENT_TYPE_UNKNOWN;

  element    = NULL;
  source     = NULL;
  instance   = NULL;
}