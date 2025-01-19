/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       UI_Property_Scrolleable.cpp
* 
* @class      UI_PROPERTY_SCROLLEABLE
* @brief      User Interface Property Scrolleable class
* @ingroup    USERINTERFACE
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

/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_DEFINES_INCLUDE

#include "GEN_Defines.h"

#pragma endregion


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "UI_Property_Scrolleable.h"

#pragma endregion


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_CONTROL_INCLUDE

#include "GEN_Control.h"

#pragma endregion



/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


#pragma region CLASS_UI_PROPERTY_SCROLLEABLE_STATUS


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         UI_PROPERTY_SCROLLEABLE_STATUS::UI_PROPERTY_SCROLLEABLE_STATUS()
* @brief      Constructor of class
* @ingroup    USERINTERFACE
*
* ---------------------------------------------------------------------------------------------------------------------*/
UI_PROPERTY_SCROLLEABLE_STATUS::UI_PROPERTY_SCROLLEABLE_STATUS()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         UI_PROPERTY_SCROLLEABLE_STATUS::~UI_PROPERTY_SCROLLEABLE_STATUS()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    USERINTERFACE
*
* ---------------------------------------------------------------------------------------------------------------------*/
UI_PROPERTY_SCROLLEABLE_STATUS::~UI_PROPERTY_SCROLLEABLE_STATUS()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void UI_PROPERTY_SCROLLEABLE_STATUS::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    USERINTERFACE
*
* ---------------------------------------------------------------------------------------------------------------------*/
void UI_PROPERTY_SCROLLEABLE_STATUS::Clean()
{
  active        = false;
  limit         = 0.0f;        
  displacement  = 0.0f;    
  step          = 0.0f;      
}


#pragma endregion


#pragma region CLASS_UI_PROPERTY_SCROLLEABLE


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         UI_PROPERTY_SCROLLEABLE::UI_PROPERTY_SCROLLEABLE()
* @brief      Constructor of class
* @ingroup    USERINTERFACE
*
* ---------------------------------------------------------------------------------------------------------------------*/
UI_PROPERTY_SCROLLEABLE::UI_PROPERTY_SCROLLEABLE()    
{ 
  Clean(); 

  horizontal.limit    = -1;
  vertical.limit      = -1;
}  


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         UI_PROPERTY_SCROLLEABLE::~UI_PROPERTY_SCROLLEABLE()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    USERINTERFACE
*
* ---------------------------------------------------------------------------------------------------------------------*/
UI_PROPERTY_SCROLLEABLE::~UI_PROPERTY_SCROLLEABLE()    
{   
  Clean();                            
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_PROPERTY_SCROLLEABLE::Scroll_GetActive(UI_PROPERTY_SCROLLEABLE_TYPE type)
* @brief      Scroll get active
* @ingroup    USERINTERFACE
*
* @param[in]  type : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool UI_PROPERTY_SCROLLEABLE::Scroll_GetActive(UI_PROPERTY_SCROLLEABLE_TYPE type)
{
  bool status = false;  

  switch(type)
    {
      case  UI_PROPERTY_SCROLLEABLE_TYPE_UNKWOWN      :  
      case  UI_PROPERTY_SCROLLEABLE_TYPE_ALL          :       
                                          default     : return false; 
                                                        break; 

      case  UI_PROPERTY_SCROLLEABLE_TYPE_HORIZONTAL   : status = horizontal.active;   break;
      case  UI_PROPERTY_SCROLLEABLE_TYPE_VERTICAL     : status = vertical.active;     break;
    }

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_PROPERTY_SCROLLEABLE::Scroll_SetActivate(UI_PROPERTY_SCROLLEABLE_TYPE type, bool on)
* @brief      Scroll set activate
* @ingroup    USERINTERFACE
*
* @param[in]  type : 
* @param[in]  on : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool UI_PROPERTY_SCROLLEABLE::Scroll_SetActivate(UI_PROPERTY_SCROLLEABLE_TYPE type, bool on)
{
  switch(type)
    {                                     default     : 
      case  UI_PROPERTY_SCROLLEABLE_TYPE_UNKWOWN      : return false; 
                                                        break;

      case  UI_PROPERTY_SCROLLEABLE_TYPE_ALL          : horizontal.active = on;      
                                                        vertical.active   = on;
                                                        break; 

      case  UI_PROPERTY_SCROLLEABLE_TYPE_HORIZONTAL   : horizontal.active = on;   break;
      case  UI_PROPERTY_SCROLLEABLE_TYPE_VERTICAL     : vertical.active   = on;   break;
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_PROPERTY_SCROLLEABLE::Scroll_GetVisible(UI_PROPERTY_SCROLLEABLE_TYPE type)
* @brief      Scroll get visible
* @ingroup    USERINTERFACE
* 
* @param[in]  type : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool UI_PROPERTY_SCROLLEABLE::Scroll_GetVisible(UI_PROPERTY_SCROLLEABLE_TYPE type)
{
  bool status = false;  

  switch(type)
    {
      case  UI_PROPERTY_SCROLLEABLE_TYPE_UNKWOWN      :  
      case  UI_PROPERTY_SCROLLEABLE_TYPE_ALL          :       
                                          default     : return false; 
                                                        break; 

      case  UI_PROPERTY_SCROLLEABLE_TYPE_HORIZONTAL   : status = horizontal.visible;   break;
      case  UI_PROPERTY_SCROLLEABLE_TYPE_VERTICAL     : status = vertical.visible;     break;
    }

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_PROPERTY_SCROLLEABLE::Scroll_SetVisible(UI_PROPERTY_SCROLLEABLE_TYPE type, bool on)
* @brief      Scroll set visible
* @ingroup    USERINTERFACE
*
* @param[in]  type : 
* @param[in]  on : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool UI_PROPERTY_SCROLLEABLE::Scroll_SetVisible(UI_PROPERTY_SCROLLEABLE_TYPE type, bool on)
{
  switch(type)
    {                                     default     : 
      case  UI_PROPERTY_SCROLLEABLE_TYPE_UNKWOWN      : return false; 
                                                        break;

      case  UI_PROPERTY_SCROLLEABLE_TYPE_ALL          : if(horizontal.active) horizontal.visible = on;      
                                                        if(vertical.active)   vertical.visible   = on;
                                                        break; 

      case  UI_PROPERTY_SCROLLEABLE_TYPE_HORIZONTAL   : if(horizontal.active) horizontal.visible = on;   
                                                        break;

      case  UI_PROPERTY_SCROLLEABLE_TYPE_VERTICAL     : if(vertical.active) vertical.visible   = on;     
                                                        break;
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         double UI_PROPERTY_SCROLLEABLE::Scroll_GetLimit(UI_PROPERTY_SCROLLEABLE_TYPE type)
* @brief      Scroll get limit
* @ingroup    USERINTERFACE
*
* @param[in]  type : 
* 
* @return     double : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
double UI_PROPERTY_SCROLLEABLE::Scroll_GetLimit(UI_PROPERTY_SCROLLEABLE_TYPE type)
{
  double limit = 0.0f;

  switch(type)
    {
      case  UI_PROPERTY_SCROLLEABLE_TYPE_UNKWOWN      :  
      case  UI_PROPERTY_SCROLLEABLE_TYPE_ALL          :       
                                          default     : break; 

      case  UI_PROPERTY_SCROLLEABLE_TYPE_HORIZONTAL   : if(horizontal.active) limit = horizontal.limit;   break;
      case  UI_PROPERTY_SCROLLEABLE_TYPE_VERTICAL     : if(vertical.active)   limit = vertical.limit;     break;
    }

  return limit;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void UI_PROPERTY_SCROLLEABLE::Scroll_SetLimit(UI_PROPERTY_SCROLLEABLE_TYPE type, double limit)
* @brief      Scroll set limit
* @ingroup    USERINTERFACE
*
* @param[in]  type : 
* @param[in]  limit : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void UI_PROPERTY_SCROLLEABLE::Scroll_SetLimit(UI_PROPERTY_SCROLLEABLE_TYPE type, double limit)
{
  switch(type)
    {
      case  UI_PROPERTY_SCROLLEABLE_TYPE_UNKWOWN      :
      case  UI_PROPERTY_SCROLLEABLE_TYPE_ALL          :                              
                                        default       : break; 

      case  UI_PROPERTY_SCROLLEABLE_TYPE_HORIZONTAL   : if(horizontal.active) horizontal.limit = limit;  break;
      case  UI_PROPERTY_SCROLLEABLE_TYPE_VERTICAL     : if(vertical.active)   vertical.limit = limit;    break;
    }
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         double UI_PROPERTY_SCROLLEABLE::Scroll_GetDisplacement(UI_PROPERTY_SCROLLEABLE_TYPE type)
* @brief      Scroll get displacement
* @ingroup    USERINTERFACE
*
* @param[in]  type : 
* 
* @return     double : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
double UI_PROPERTY_SCROLLEABLE::Scroll_GetDisplacement(UI_PROPERTY_SCROLLEABLE_TYPE type)
{
  double displacement = 0.0f;

  switch(type)
    {
      case  UI_PROPERTY_SCROLLEABLE_TYPE_UNKWOWN      :  
      case  UI_PROPERTY_SCROLLEABLE_TYPE_ALL          :       
                                        default       : break; 

      case  UI_PROPERTY_SCROLLEABLE_TYPE_HORIZONTAL   : if(horizontal.active) displacement = horizontal.displacement;   break;
      case  UI_PROPERTY_SCROLLEABLE_TYPE_VERTICAL     : if(vertical.active)   displacement = vertical.displacement;     break;
    }

  return displacement;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         double UI_PROPERTY_SCROLLEABLE::Scroll_GetStep(UI_PROPERTY_SCROLLEABLE_TYPE type)
* @brief      Scroll get step
* @ingroup    USERINTERFACE
*
* @param[in]  type : 
* 
* @return     double : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
double UI_PROPERTY_SCROLLEABLE::Scroll_GetStep(UI_PROPERTY_SCROLLEABLE_TYPE type)
{
  double step = 0.0f;

  switch(type)
    {
      case  UI_PROPERTY_SCROLLEABLE_TYPE_UNKWOWN      :  
      case  UI_PROPERTY_SCROLLEABLE_TYPE_ALL          :       
                                        default       : break; 

      case  UI_PROPERTY_SCROLLEABLE_TYPE_HORIZONTAL   : if(horizontal.active) step = horizontal.step;   break;
      case  UI_PROPERTY_SCROLLEABLE_TYPE_VERTICAL     : if(vertical.active)   step = vertical.step;     break;
    }

  return step;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void UI_PROPERTY_SCROLLEABLE::Scroll_SetStep(UI_PROPERTY_SCROLLEABLE_TYPE type, double step)
* @brief      Scroll set step
* @ingroup    USERINTERFACE
*
* @param[in]  type : 
* @param[in]  step : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void UI_PROPERTY_SCROLLEABLE::Scroll_SetStep(UI_PROPERTY_SCROLLEABLE_TYPE type, double step)
{
  switch(type)
    {
      case  UI_PROPERTY_SCROLLEABLE_TYPE_UNKWOWN      :       
      case  UI_PROPERTY_SCROLLEABLE_TYPE_ALL          :              
                                        default       : break; 

      case  UI_PROPERTY_SCROLLEABLE_TYPE_HORIZONTAL   : if(!horizontal.active) break;

                                                        if((horizontal.displacement + step) > 0) 
                                                          { 
                                                            horizontal.displacement = 0;
                                                            break;
                                                          }
  
                                                        if(horizontal.limit != -1)
                                                          {
                                                            if((horizontal.displacement + step) < horizontal.limit) 
                                                              {
                                                                horizontal.displacement = horizontal.limit;
                                                                break;
                                                              }
                                                          }

                                                        horizontal.step          = step;
                                                        horizontal.displacement += step;
                                                        break;

      case  UI_PROPERTY_SCROLLEABLE_TYPE_VERTICAL    : if(!vertical.active) break;

                                                        if((vertical.displacement + step) > 0) 
                                                          { 
                                                            vertical.displacement = 0;
                                                            break;
                                                          }
  
                                                        if(vertical.limit != -1)
                                                          {
                                                            if((vertical.displacement + step) < vertical.limit) 
                                                              {
                                                                vertical.displacement = vertical.limit;
                                                                break;
                                                              }
                                                          }

                                                        vertical.step           = step;
                                                        vertical.displacement  += step;   
                                                        break;
    }
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void UI_PROPERTY_SCROLLEABLE::Scroll_ResetStep(UI_PROPERTY_SCROLLEABLE_TYPE type)
* @brief      Scroll reset step
* @ingroup    USERINTERFACE
*
* @param[in]  type : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void UI_PROPERTY_SCROLLEABLE::Scroll_ResetStep(UI_PROPERTY_SCROLLEABLE_TYPE type)
{
  switch(type)
    {
      case  UI_PROPERTY_SCROLLEABLE_TYPE_UNKWOWN      :        
                                        default       : break;
 
      case  UI_PROPERTY_SCROLLEABLE_TYPE_ALL          :

                                                        if(horizontal.active) horizontal.step = 0.0f;
                                                        if(vertical.active)   vertical.step   = 0.0f;
                                                        break;
         
      case  UI_PROPERTY_SCROLLEABLE_TYPE_HORIZONTAL   : if(horizontal.active) horizontal.step = 0.0f;      
                                                        break;

      case  UI_PROPERTY_SCROLLEABLE_TYPE_VERTICAL     : if(vertical.active)   vertical.step   = 0.0f;     
                                                        break;
    }
}

  
/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void UI_PROPERTY_SCROLLEABLE::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    USERINTERFACE
*
* ---------------------------------------------------------------------------------------------------------------------*/
void UI_PROPERTY_SCROLLEABLE::Clean()
{  
  
}


#pragma endregion


#pragma endregion

