/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       UI_Property_Scrolleable.h
* 
* @class      UI_PROPERTY_SCROLLEABLE
* @brief      User Interface Element Scrolleable class
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

#ifndef _UI_PROPERTY_SCROLLEABLE_H_
#define _UI_PROPERTY_SCROLLEABLE_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "UI_BoundaryLine.h"

#pragma endregion


/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/
#pragma region DEFINES_ENUMS

enum UI_PROPERTY_SCROLLEABLE_TYPE
{
  UI_PROPERTY_SCROLLEABLE_TYPE_UNKWOWN          = 0 ,
  UI_PROPERTY_SCROLLEABLE_TYPE_HORIZONTAL           ,
  UI_PROPERTY_SCROLLEABLE_TYPE_VERTICAL             ,
  UI_PROPERTY_SCROLLEABLE_TYPE_ALL                  ,
};



#pragma endregion


/*---- CLASS ---------------------------------------------------------------------------------------------------------*/
#pragma region CLASS


class UI_PROPERTY_SCROLLEABLE_STATUS
{
  public:
																		          UI_PROPERTY_SCROLLEABLE_STATUS	        ();
    virtual											         	   ~UI_PROPERTY_SCROLLEABLE_STATUS          ();

    bool                                      active;
    bool                                      visible;
    double                                    limit;        
    double                                    displacement;    
    double                                    step;                     

  private:

    void															        Clean										                ();              
};


class UI_PROPERTY_SCROLLEABLE 
{
  public:
																		          UI_PROPERTY_SCROLLEABLE		              ();
    virtual											         	   ~UI_PROPERTY_SCROLLEABLE	  	            ();
        
    bool                                      Scroll_GetActive                        (UI_PROPERTY_SCROLLEABLE_TYPE type);
    bool                                      Scroll_SetActivate                      (UI_PROPERTY_SCROLLEABLE_TYPE type, bool on);

    bool                                      Scroll_GetVisible                       (UI_PROPERTY_SCROLLEABLE_TYPE type);
    bool                                      Scroll_SetVisible                       (UI_PROPERTY_SCROLLEABLE_TYPE type, bool on);

    double                                    Scroll_GetLimit                         (UI_PROPERTY_SCROLLEABLE_TYPE type);
    void                                      Scroll_SetLimit                         (UI_PROPERTY_SCROLLEABLE_TYPE type, double  limit);

    double                                    Scroll_GetDisplacement                  (UI_PROPERTY_SCROLLEABLE_TYPE type);

    double                                    Scroll_GetStep                          (UI_PROPERTY_SCROLLEABLE_TYPE type);
    void                                      Scroll_SetStep                          (UI_PROPERTY_SCROLLEABLE_TYPE type, double h_step);

    void                                      Scroll_ResetStep                        (UI_PROPERTY_SCROLLEABLE_TYPE type = UI_PROPERTY_SCROLLEABLE_TYPE_ALL);
      	
  private:

		void															        Clean										                ();  


    UI_PROPERTY_SCROLLEABLE_STATUS            horizontal;  
    UI_PROPERTY_SCROLLEABLE_STATUS            vertical;  
};

#pragma endregion


/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/
#pragma region FUNCTIONS_PROTOTYPES


#pragma endregion


#endif
