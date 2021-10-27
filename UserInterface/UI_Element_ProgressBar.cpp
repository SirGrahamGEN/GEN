/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       UI_Element_ProgressBar.cpp
* 
* @class      UI_ELEMENT_PROGRESSBAR
* @brief      User Interface Element Progress Bar Class
* @ingroup    USERINTERFACE
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

#include "GRPBitmap.h"

#include "UI_Element_ProgressBar.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         UI_ELEMENT_PROGRESSBAR::UI_ELEMENT_PROGRESSBAR()
* @brief      Constructor
* @ingroup    USERINTERFACE
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @return     Does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
UI_ELEMENT_PROGRESSBAR::UI_ELEMENT_PROGRESSBAR()    
{ 
  Clean();   

  SetType(UI_ELEMENT_TYPE_PROGRESSBAR);
  GetTypeString()->Set(__L("progressbar")); 

  continuouscycle_xtimer = GEN_XFACTORY.CreateTimer();
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         UI_ELEMENT_PROGRESSBAR::~UI_ELEMENT_PROGRESSBAR()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    USERINTERFACE
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @return     Does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
UI_ELEMENT_PROGRESSBAR::~UI_ELEMENT_PROGRESSBAR()    
{ 
  if(continuouscycle_xtimer)
    { 
      GEN_XFACTORY.DeleteTimer(continuouscycle_xtimer);
      continuouscycle_xtimer = NULL;
    }

  Clean();                            
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         float UI_ELEMENT_PROGRESSBAR::GetLevel()
* @brief      GetLevel
* @ingroup    USERINTERFACE
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @return     float : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
float UI_ELEMENT_PROGRESSBAR::GetLevel()
{
  return level;
}
    


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void UI_ELEMENT_PROGRESSBAR::SetLevel(float level)
* @brief      SetLevel
* @ingroup    USERINTERFACE
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @param[in]  level : 
* 
* @return     void : does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void UI_ELEMENT_PROGRESSBAR::SetLevel(float level)
{  
  if(level < 0)   level = 0;
  if(level > 100) level = 100;

  this->level = level;  
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         UI_COLOR* UI_ELEMENT_PROGRESSBAR::GetLineColor()
* @brief      GetLineColor
* @ingroup    USERINTERFACE
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @return     UI_COLOR* : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
UI_COLOR* UI_ELEMENT_PROGRESSBAR::GetLineColor()
{
  return &linecolor;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         UI_ELEMENT* UI_ELEMENT_PROGRESSBAR::GetProgressRect()
* @brief      GetProgressRect
* @ingroup    USERINTERFACE
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @return     UI_ELEMENT* : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
UI_ELEMENT* UI_ELEMENT_PROGRESSBAR::GetProgressRect()
{
  return progressrect;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void UI_ELEMENT_PROGRESSBAR::SetProgressRect(UI_ELEMENT* progressrect)
* @brief      SetProgressRect
* @ingroup    USERINTERFACE
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @param[in]  progressrect : 
* 
* @return     void : does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void UI_ELEMENT_PROGRESSBAR::SetProgressRect(UI_ELEMENT* progressrect)
{
  this->progressrect = progressrect;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_ELEMENT_PROGRESSBAR::ContinuousCycle_Is()
* @brief      ContinuousCycle_Is
* @ingroup    USERINTERFACE
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool UI_ELEMENT_PROGRESSBAR::ContinuousCycle_Is()
{
  return continuouscycle_is;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void UI_ELEMENT_PROGRESSBAR::ContinuousCycle_Set(bool active, XDWORD sizesegment, XDWORD stepsegment, XDWORD timestep)
* @brief      ContinuousCycle_Set
* @ingroup    USERINTERFACE
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @param[in]  active : 
* @param[in]  sizesegment : 
* @param[in]  stepsegment : 
* @param[in]  timestep : 
* 
* @return     void : does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void UI_ELEMENT_PROGRESSBAR::ContinuousCycle_Set(bool active, XDWORD sizesegment, XDWORD stepsegment, XDWORD timestep)
{
  this->continuouscycle_is          = active;
  this->continuouscycle_sizesegment = sizesegment;
  this->continuouscycle_stepsegment = stepsegment;
  this->continuouscycle_timestep    = timestep;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDWORD UI_ELEMENT_PROGRESSBAR::ContinuousCycle_GetSizeSegment()
* @brief      ContinuousCycle_GetSizeSegment
* @ingroup    USERINTERFACE
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @return     XDWORD : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
XDWORD UI_ELEMENT_PROGRESSBAR::ContinuousCycle_GetSizeSegment()
{
  return continuouscycle_sizesegment;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDWORD UI_ELEMENT_PROGRESSBAR::ContinuousCycle_GetStepSegment()
* @brief      ContinuousCycle_GetStepSegment
* @ingroup    USERINTERFACE
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @return     XDWORD : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
XDWORD UI_ELEMENT_PROGRESSBAR::ContinuousCycle_GetStepSegment()
{
  return continuouscycle_stepsegment;
}

    

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDWORD UI_ELEMENT_PROGRESSBAR::ContinuousCycle_GetNSteps()
* @brief      ContinuousCycle_GetNSteps
* @ingroup    USERINTERFACE
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @return     XDWORD : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
XDWORD UI_ELEMENT_PROGRESSBAR::ContinuousCycle_GetNSteps()
{
  return continuouscycle_nsteps;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void UI_ELEMENT_PROGRESSBAR::ContinuousCycle_SetNSteps(XDWORD nsteps)
* @brief      ContinuousCycle_SetNSteps
* @ingroup    USERINTERFACE
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @param[in]  nsteps : 
* 
* @return     void : does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void UI_ELEMENT_PROGRESSBAR::ContinuousCycle_SetNSteps(XDWORD nsteps)
{
  continuouscycle_nsteps = nsteps;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XTIMER* UI_ELEMENT_PROGRESSBAR::ContinuousCycle_GetXTimer()
* @brief      ContinuousCycle_GetXTimer
* @ingroup    USERINTERFACE
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @return     XTIMER* : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
XTIMER* UI_ELEMENT_PROGRESSBAR::ContinuousCycle_GetXTimer()
{
  return continuouscycle_xtimer;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDWORD UI_ELEMENT_PROGRESSBAR::ContinuousCycle_GetTimeStep()
* @brief      ContinuousCycle_GetTimeStep
* @ingroup    USERINTERFACE
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @return     XDWORD : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
XDWORD UI_ELEMENT_PROGRESSBAR::ContinuousCycle_GetTimeStep()
{
  return continuouscycle_timestep;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void UI_ELEMENT_PROGRESSBAR::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    USERINTERFACE
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @return     void : does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void UI_ELEMENT_PROGRESSBAR::Clean()
{  
  level                         = 0.0f;

  progressrect                  = NULL;

  continuouscycle_is            = false;
  continuouscycle_sizesegment   = 0;
  continuouscycle_stepsegment   = 0;
  continuouscycle_nsteps        = 0;
  continuouscycle_xtimer        = NULL;
  continuouscycle_timestep      = 0;

}