/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       UI_Layout.cpp
* 
* @class      UI_LAYOUT
* @brief      User Interface Layout Class
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
* ---------------------------------------------------------------------------------------------------------------------*/

/*---- PRECOMPILATION CONTROL ----------------------------------------------------------------------------------------*/

#include "GEN_Defines.h"


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "UI_Skin.h"

#include "UI_Layout.h"


#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         UI_LAYOUT::UI_LAYOUT(UI_SKINCANVAS* skin)
* @brief      Constructor
* @ingroup    USERINTERFACE
*
* @param[in]  UI_SKINCANVAS* : 
* 
* @return     Does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
UI_LAYOUT::UI_LAYOUT(UI_SKIN* skin)    

{ 
  Clean();                        
  
  this->skin = skin;    
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         UI_LAYOUT::~UI_LAYOUT()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    USERINTERFACE
*
* @return     Does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
UI_LAYOUT::~UI_LAYOUT()    
{ 
  Elements_DeleteAll();

  Clean();                            
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         UI_SKIN* UI_LAYOUT::GetSkin()
* @brief      GetSkin
* @ingroup    USERINTERFACE
*
* @return     UI_SKIN* : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
UI_SKIN* UI_LAYOUT::GetSkin()
{
  return skin;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSTRING* UI_LAYOUT::GetNameID()
* @brief      GetNameID
* @ingroup    USERINTERFACE
*
* @return     XSTRING* : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
XSTRING* UI_LAYOUT::GetNameID()
{
  return &nameID;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         UI_COLOR* UI_LAYOUT::GetBackgroundColor()
* @brief      GetBackgroundColor
* @ingroup    USERINTERFACE
*
* @return     UI_COLOR* : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
UI_COLOR* UI_LAYOUT::GetBackgroundColor()
{
  return &backgroundcolor;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSTRING* UI_LAYOUT::GetBackgroundFilename()
* @brief      GetBackgroundFilename
* @ingroup    USERINTERFACE
*
* @return     XSTRING* : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
XSTRING* UI_LAYOUT::GetBackgroundFilename()
{
  return &backgroundfilename;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_LAYOUT::Elements_Add(UI_ELEMENT* element)
* @brief      Elements_Add
* @ingroup    USERINTERFACE
*
* @param[in]  element : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool UI_LAYOUT::Elements_Add(UI_ELEMENT* element)
{
  if(!element) return false;

  elements.Add(element);

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XVECTOR<UI_ELEMENT*>* UI_LAYOUT::Elements_Get()
* @brief      Elements_Get
* @ingroup    USERINTERFACE
*
* @return     XVECTOR<UI_ELEMENT*>* : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
XVECTOR<UI_ELEMENT*>* UI_LAYOUT::Elements_Get()
{
  return &elements;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         UI_ELEMENT* UI_LAYOUT::Elements_Get(XCHAR* nameelement, UI_ELEMENT_TYPE type)
* @brief      Elements_Get
* @ingroup    USERINTERFACE
*
* @param[in]  nameelement : 
* @param[in]  type : 
* 
* @return     UI_ELEMENT* : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
UI_ELEMENT* UI_LAYOUT::Elements_Get(XCHAR* nameelement, UI_ELEMENT_TYPE type)
    {
  if(elements.IsEmpty()) return NULL;

  for(XDWORD c=0; c<elements.GetSize(); c++)
    {
      UI_ELEMENT* element = elements.Get(c);
      if(element)
        {
          if(!element->GetName()->Compare(nameelement, true)) 
            {
              if(type != UI_ELEMENT_TYPE_UNKNOWN) 
                {
                  if(element->GetType() == type) return element;
                }
               else return element;
            }

          if(element->GetComposeElements()->GetSize())
            {
              UI_ELEMENT* subelement = Elements_Get(element, nameelement, type);
              if(subelement) return subelement;
            }
        }
    }

  return NULL;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_LAYOUT::Elements_DeleteAll()
* @brief      Elements_DeleteAll
* @ingroup    USERINTERFACE
*
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool UI_LAYOUT::Elements_DeleteAll()
{
  if(elements.IsEmpty())  return false;

  elements.DeleteContents();
  elements.DeleteAll();

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_LAYOUT::Elements_SetToRedraw(bool recursive)
* @brief      Elements_SetToRedraw
* @ingroup    USERINTERFACE
*
* @param[in]  recursive : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool UI_LAYOUT::Elements_SetToRedraw(bool recursive)
{
  bool status = false;

  for(XDWORD c=0; c<elements.GetSize(); c++) 
    {
      UI_ELEMENT* element = (UI_ELEMENT*)elements.Get(c);
      if(element) 
        {
          status = Elements_SetToRedraw(element, recursive);                
        }
    }

  return status;
}

    

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_LAYOUT::Elements_SetToRedraw(UI_ELEMENT* element, bool recursive)
* @brief      Elements_SetToRedraw
* @ingroup    USERINTERFACE
*
* @param[in]  element : 
* @param[in]  recursive : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool UI_LAYOUT::Elements_SetToRedraw(UI_ELEMENT* element, bool recursive)
{
  if(!element) return false;

  bool status = true;

  element->SetMustReDraw(true);

  if(recursive)
    {
      for(XDWORD c=0; c<element->GetComposeElements()->GetSize(); c++)
        {
          UI_ELEMENT* subelement = (UI_ELEMENT*)element->GetComposeElements()->Get(c);
          if(subelement) 
            { 
              status = Elements_SetToRedraw(subelement, recursive);                        
            } 
        }           
    }

  return status;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_LAYOUT::Update()
* @brief      Update
* @ingroup    USERINTERFACE
*
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool UI_LAYOUT::Update()
{
  for(XDWORD c=0; c<elements.GetSize(); c++)
    {
      if(skin) skin->Draw(elements.Get(c));
    }

  return true;
}




/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         UI_ELEMENT* UI_LAYOUT::Elements_Get(UI_ELEMENT* element, XCHAR* nameelement, UI_ELEMENT_TYPE type)
* @brief      Elements_Get
* @ingroup    USERINTERFACE
*
* @param[in]  element : 
* @param[in]  nameelement : 
* @param[in]  type : 
* 
* @return     UI_ELEMENT* : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
UI_ELEMENT* UI_LAYOUT::Elements_Get(UI_ELEMENT* element, XCHAR* nameelement, UI_ELEMENT_TYPE type)
{
  if(!element) return NULL;

  for(XDWORD c=0; c<element->GetComposeElements()->GetSize(); c++)
    {
      UI_ELEMENT* subelement = element->GetComposeElements()->Get(c);
      if(subelement)
        {
          if(!subelement->GetName()->Compare(nameelement, true)) 
            {
              if(type != UI_ELEMENT_TYPE_UNKNOWN) 
                {
                  if(subelement->GetType() == type) return subelement;
                }
               else return subelement;
            }

          if(subelement->GetComposeElements()->GetSize()) 
            {
              UI_ELEMENT* _subelement = Elements_Get(subelement, nameelement, type);
              if(_subelement) return _subelement;
            }
        }          
    }

  return NULL;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void UI_LAYOUT::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    USERINTERFACE
*
* @return     void : does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void UI_LAYOUT::Clean()
{
  skin   =  NULL;
}