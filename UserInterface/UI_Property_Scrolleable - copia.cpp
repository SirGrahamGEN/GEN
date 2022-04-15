/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       UI_Property_Scrolleable.cpp
* 
* @class      UI_PROPERTY_SCROLLEABLE
* @brief      User Interface Property Scrolleable class
* @ingroup    USERINTERFACE
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
* ---------------------------------------------------------------------------------------------------------------------*/

/*---- PRECOMPILATION CONTROL ----------------------------------------------------------------------------------------*/

#include "GEN_Defines.h"


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "UI_Property_Scrolleable.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/




/*--------------------------------------------------------------------------------------------------------------------*/
/*  UI_PROPERTY_SCROLLEABLE_STATUS                                                                                    */
/*--------------------------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         UI_PROPERTY_SCROLLEABLE_STATUS::UI_PROPERTY_SCROLLEABLE_STATUS()
* @brief      Constructor
* @ingroup    USERINTERFACE
*
* @return     Does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
UI_PROPERTY_SCROLLEABLE_STATUS::UI_PROPERTY_SCROLLEABLE_STATUS()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         UI_PROPERTY_SCROLLEABLE_STATUS::~UI_PROPERTY_SCROLLEABLE_STATUS()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    USERINTERFACE
*
* @return     Does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
UI_PROPERTY_SCROLLEABLE_STATUS::~UI_PROPERTY_SCROLLEABLE_STATUS()
{
  Clean();
}


 

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void UI_PROPERTY_SCROLLEABLE_STATUS::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    USERINTERFACE
*
* @return     void : does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void UI_PROPERTY_SCROLLEABLE_STATUS::Clean()
{
  active        = false;
  limit         = 0.0f;        
  displacement  = 0.0f;    
  step          = 0.0f;      
}




/*--------------------------------------------------------------------------------------------------------------------*/
/*  UI_PROPERTY_SCROLLEABLE                                                                                           */
/*--------------------------------------------------------------------------------------------------------------------*/




/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         UI_PROPERTY_SCROLLEABLE::UI_PROPERTY_SCROLLEABLE()
* @brief      Constructor
* @ingroup    USERINTERFACE
*
* @return     Does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
UI_PROPERTY_SCROLLEABLE::UI_PROPERTY_SCROLLEABLE()    
{ 
  Clean(); 

  h_limit     = -1;
  v_limit     = -1;
}  



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         UI_PROPERTY_SCROLLEABLE::~UI_PROPERTY_SCROLLEABLE()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    USERINTERFACE
*
* @return     Does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
UI_PROPERTY_SCROLLEABLE::~UI_PROPERTY_SCROLLEABLE()    
{   
  Clean();                            
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         double UI_PROPERTY_SCROLLEABLE::H_GetLimit()
* @brief      H_GetLimit
* @ingroup    USERINTERFACE
*
* @return     double : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
double UI_PROPERTY_SCROLLEABLE::H_GetLimit()
{
  return h_limit;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void UI_PROPERTY_SCROLLEABLE::H_SetLimit(double limit)
* @brief      H_SetLimit
* @ingroup    USERINTERFACE
*
* @param[in]  limit : 
* 
* @return     void : does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void UI_PROPERTY_SCROLLEABLE::H_SetLimit(double limit)
{
  h_limit = limit;  
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         double UI_PROPERTY_SCROLLEABLE::V_GetLimit()
* @brief      V_GetLimit
* @ingroup    USERINTERFACE
*
* @return     double : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
double UI_PROPERTY_SCROLLEABLE::V_GetLimit()
{
  return v_limit;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void UI_PROPERTY_SCROLLEABLE::V_SetLimit(double limit)
* @brief      V_SetLimit
* @ingroup    USERINTERFACE
*
* @param[in]  limit : 
* 
* @return     void : does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void UI_PROPERTY_SCROLLEABLE::V_SetLimit(double limit)
{
  v_limit = limit;  
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         double UI_PROPERTY_SCROLLEABLE::H_GetDisplacement()
* @brief      H_GetDisplacement
* @ingroup    USERINTERFACE
*
* @return     double : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
double UI_PROPERTY_SCROLLEABLE::H_GetDisplacement()
{
  return h_displacement;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         double UI_PROPERTY_SCROLLEABLE::V_GetDisplacement()
* @brief      V_GetDisplacement
* @ingroup    USERINTERFACE
*
* @return     double : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
double UI_PROPERTY_SCROLLEABLE::V_GetDisplacement()
{
  return v_displacement;
}
 


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         double UI_PROPERTY_SCROLLEABLE::H_GetStep()
* @brief      H_GetStep
* @ingroup    USERINTERFACE
*
* @return     double : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
double UI_PROPERTY_SCROLLEABLE::H_GetStep()
{
  return h_step;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void UI_PROPERTY_SCROLLEABLE::H_SetStep(double h_step)
* @brief      H_SetStep
* @ingroup    USERINTERFACE
*
* @param[in]  h_step : 
* 
* @return     void : does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void UI_PROPERTY_SCROLLEABLE::H_SetStep(double h_step)
{
  if((h_displacement + h_step) > 0) 
    { 
      h_displacement = 0;
      return;
    }
  
  if(h_limit != -1)
    {
      if((h_displacement + h_step) < h_limit) 
        {
          h_displacement = h_limit;
          return;
        }
    }

  this->h_step    = h_step;
  h_displacement += h_step;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         double UI_PROPERTY_SCROLLEABLE::V_GetStep()
* @brief      V_GetStep
* @ingroup    USERINTERFACE
*
* @return     double : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
double UI_PROPERTY_SCROLLEABLE::V_GetStep()
{
  return v_step;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void UI_PROPERTY_SCROLLEABLE::SetVerticalStep(double verticalstep)
* @brief      SetVerticalStep
* @ingroup    USERINTERFACE
*
* @param[in]  verticalstep : 
* 
* @return     void : does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void UI_PROPERTY_SCROLLEABLE::V_SetStep(double v_step)
{ 
  if((v_displacement + v_step) > 0) 
    { 
      v_displacement = 0;
      return;
    }
  
  if(v_limit != -1)
    {
      if((v_displacement + v_step) < v_limit) 
        {
          v_displacement = v_limit;
          return;
        }
    }

  this->v_step    = v_step;
  v_displacement += v_step;
}

    

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void UI_PROPERTY_SCROLLEABLE::ResetSteps()
* @brief      ResetSteps
* @ingroup    USERINTERFACE
*
* @return     void : does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void  UI_PROPERTY_SCROLLEABLE::ResetSteps()
{
  h_step = 0;
  v_step = 0;
}

  
  
/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void UI_PROPERTY_SCROLLEABLE::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    USERINTERFACE
*
* @return     void : does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void UI_PROPERTY_SCROLLEABLE::Clean()
{  
  h_limit         = 0;  
  v_limit         = 0;
  
  h_displacement  = 0;
  v_displacement  = 0;

  h_step          = 0;
  v_step          = 0;
}