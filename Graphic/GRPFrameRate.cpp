/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       GRPFrameRate.cpp
* 
* @class      GRPFRAMERATE
* @brief      Graphic Frame Rate class
* @ingroup    GRAPHIC
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @copyright  Copyright(c) 2005 - 2020 GEN Group.
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
* ---------------------------------------------------------------------------------------------------------------------*/

/*---- PRECOMPILATION CONTROL ----------------------------------------------------------------------------------------*/

#include "GEN_Defines.h"


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "XFactory.h"
#include "XTimer.h"
#include "XThread.h"
#include "XThreadCollected.h"

#include "GRPFrameRate.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/




/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         GRPFRAMERATE::GRPFRAMERATE()
* @brief      Constructor
* @ingroup    GRAPHIC
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @return     Does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
GRPFRAMERATE::GRPFRAMERATE()    
{ 
  Clean(); 

  xtimertotal = GEN_XFACTORY.CreateTimer();  

  thread_framerate = CREATEXTHREAD((XTHREADGROUPID)(XTHREADGROUPID_GRPFRAMERATE), __L("GRPFRAMERATE::GRPFRAMERATE"), ThreadRunFunction_Framerate, this);    
  if(!thread_framerate)  return;

  if(!thread_framerate->Ini()) return;
                      
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         GRPFRAMERATE::~GRPFRAMERATE()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    GRAPHIC
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @return     Does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
GRPFRAMERATE::~GRPFRAMERATE()    
{ 
  if(thread_framerate)
    {
      thread_framerate->End();

      DELETEXTHREAD((XTHREADGROUPID)(XTHREADGROUPID_GRPFRAMERATE), thread_framerate);
      thread_framerate = NULL;  
    }

  if(xtimertotal) GEN_XFACTORY.DeleteTimer(xtimertotal);

  Clean();                       
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XTIMER* GRPFRAMERATE::GetXTime()
* @brief      GetXTime
* @ingroup    GRAPHIC
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @return     XTIMER* : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
XTIMER* GRPFRAMERATE::GetXTimer()
{
  return xtimertotal;
}




/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void GRPFRAMERATE::AddNFrames()
* @brief      AddNFrames
* @ingroup    GRAPHIC
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @return     void : does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void GRPFRAMERATE::AddNFrames()
{
  nframes++;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDWORD GRPFRAMERATE::GetNFrames()
* @brief      GetNFrames
* @ingroup    GRAPHIC
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @return     XDWORD : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
XDWORD GRPFRAMERATE::GetNFrames()
{
  return nframes;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void GRPFRAMERATE::Reset()
* @brief      Reset
* @ingroup    GRAPHIC
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @return     void : does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void GRPFRAMERATE::Reset()
{  
  if(xtimertotal)  xtimertotal->Reset();

  nframes           = 0; 
  ngets             = 0;
  
  actual_framerate  = 0.0f;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         float GRPFRAMERATE::Get()
* @brief      Get
* @ingroup    GRAPHIC
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @return     float : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
float GRPFRAMERATE::Get()
{  
  ngets++;

  return actual_framerate;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void GRPFRAMERATE::ThreadRunFunction_Framerate(void* param)
* @brief      ThreadRunFunction_Framerate
* @ingroup    GRAPHIC
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @param[in]  param : 
* 
* @return     void : does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
/*
void GRPFRAMERATE::ThreadRunFunction_Framerate(void* param)
{
  GRPFRAMERATE* grpframerate = (GRPFRAMERATE*)param;
  if(!grpframerate) return;

  static int counter = 0;
 
  XDWORD nsec = grpframerate->xtimertotal->GetMeasureSeconds();
  if(!nsec)  return;

  grpframerate->actual_framerate = (float)((float)grpframerate->nframes / (float)nsec); 
  
  GEN_XSLEEP.MilliSeconds(10);

  counter++;

  if(counter >= 100)
    {
      grpframerate->xtimertotal->Reset();
      grpframerate->nframes = 0;
 
      counter = 0;
    }    
}
*/
void GRPFRAMERATE::ThreadRunFunction_Framerate(void* param)
{
  GRPFRAMERATE* grpframerate = (GRPFRAMERATE*)param;
  if(!grpframerate) return;

  XQWORD msec = grpframerate->xtimertotal->GetMeasureMilliSeconds();
  if(msec < 1000)  return;

  grpframerate->actual_framerate = (float)grpframerate->nframes;
      
  grpframerate->xtimertotal->Reset();
  grpframerate->nframes = 0;
  
}






/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void GRPFRAMERATE::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    GRAPHIC
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @return     void : does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void GRPFRAMERATE::Clean()
{
  xtimertotal       = NULL;
  nframes           = 0;

  ngets             = 0;
  
  actual_framerate  = 0.0f;  
}
