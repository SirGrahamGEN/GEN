/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       UI_Element_Image.cpp
* 
* @class      UI_ELEMENT_IMAGE
* @brief      User Interface Element Image class
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

#include "GRPBitmap.h"

#include "UI_Element_Image.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         UI_ELEMENT_IMAGE::UI_ELEMENT_IMAGE()
* @brief      Constructor
* @ingroup    USERINTERFACE
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @return     Does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
UI_ELEMENT_IMAGE::UI_ELEMENT_IMAGE()    
{ 
  Clean();   

  SetType(UI_ELEMENT_TYPE_IMAGE);
  GetTypeString()->Set(__L("image"));  
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         UI_ELEMENT_IMAGE::~UI_ELEMENT_IMAGE()
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
UI_ELEMENT_IMAGE::~UI_ELEMENT_IMAGE()    
{ 
  /*
  if(image)
    {
      delete image;
      image = NULL;
    }  
   */


  Clean();                            
}




/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         GRPBITMAP* UI_ELEMENT_IMAGE::GetImage()
* @brief      GetImage
* @ingroup    USERINTERFACE
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @return     GRPBITMAP* : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
GRPBITMAP* UI_ELEMENT_IMAGE::GetImage()
{
  return image;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_ELEMENT_IMAGE::SetImage(GRPBITMAP* image)
* @brief      SetImage
* @ingroup    USERINTERFACE
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @param[in]  image : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool UI_ELEMENT_IMAGE::SetImage(GRPBITMAP* image)
{
  if(!image) return false;

  this->image = image;

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XBYTE UI_ELEMENT_IMAGE::GetAlpha()
* @brief      GetAlpha
* @ingroup    USERINTERFACE
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @return     XBYTE : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
XBYTE UI_ELEMENT_IMAGE::GetAlpha()
{
  return alpha;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void UI_ELEMENT_IMAGE::SetAlpha(XBYTE alpha)
* @brief      SetAlpha
* @ingroup    USERINTERFACE
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @param[in]  alpha : 
* 
* @return     void : does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void UI_ELEMENT_IMAGE::SetAlpha(XBYTE alpha)
{
  this->alpha = alpha;
}




/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void UI_ELEMENT_IMAGE::Clean()
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
void UI_ELEMENT_IMAGE::Clean()
{
  image =  NULL;
  alpha =  100;
}