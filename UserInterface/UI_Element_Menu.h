/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       UI_Element_Menu.h
* 
* @class      UI_ELEMENT_MENU
* @brief      User Interface Element Menu Class
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
* *---------------------------------------------------------------------------------------------------------------------*/

#ifndef _UI_ELEMENT_MENU_H_
#define _UI_ELEMENT_MENU_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "UI_Element.h"
#include "UI_Element_Form.h"
#include "UI_Element_Scroll.h"

/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/


/*---- CLASS ---------------------------------------------------------------------------------------------------------*/

class UI_ELEMENT_OPTION;

class UI_ELEMENT_MENU_OPTION_CFG
{
  public:

                                    UI_ELEMENT_MENU_OPTION_CFG    ();
    virtual											   ~UI_ELEMENT_MENU_OPTION_CFG    ();

    XDWORD                          index; 
    XSTRING                         nameoption;
    XSTRING                         leyend; 
    XSTRING                         colorstr;
    XDWORD                          sizefont; 
    double                          marginwidth;  
    double                          marginheight;  
    double                          width;
    double                          height;

  private:

		void														Clean												  ();   
};



class UI_ELEMENT_MENU : public UI_ELEMENT_FORM 
{
  public:
																		  UI_ELEMENT_MENU					    ();
    virtual													 ~UI_ELEMENT_MENU					    ();

    UI_ELEMENT_OPTION*                Option_AddText              (UI_ELEMENT_MENU_OPTION_CFG& option_cfg);

    	  
  private:

		void															Clean												();   
};


/*---- INLINE FUNCTIONS ----------------------------------------------------------------------------------------------*/

#endif


