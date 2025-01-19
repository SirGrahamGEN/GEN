/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       UI_Texts.cpp
* 
* @class      UI_TEXTS
* @brief      User Interface Texts class
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

#include "UI_Texts.h"

#pragma endregion


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_CONTROL_INCLUDE

#include "GEN_Control.h"

#pragma endregion



/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

UI_TEXTS* UI_TEXTS::instance = NULL;

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_TEXTS::GetIsInstanced()
* @brief      Get is instanced
* @ingroup    USERINTERFACE
*
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool UI_TEXTS::GetIsInstanced()
{
  return instance!=NULL;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         UI_TEXTS& UI_TEXTS::GetInstance()
* @brief      Get instance
* @ingroup    USERINTERFACE
*
* @return     UI_TEXTS& : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
UI_TEXTS& UI_TEXTS::GetInstance()
{
  if(!instance) instance = new UI_TEXTS();

  return (*instance);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_TEXTS::DelInstance()
* @brief      Del instance
* @ingroup    USERINTERFACE
*
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool UI_TEXTS::DelInstance()
{
  if(instance)
    {
      delete instance;
      instance = NULL;

      return true;
    }

  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_TEXTS::Add(XCHAR* name, XCHAR* texts)
* @brief      Add
* @ingroup    USERINTERFACE
*
* @param[in]  name : 
* @param[in]  texts : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool UI_TEXTS::Add(XCHAR* name, XCHAR* text)
{
  if(!name)   return false;
  if(!text)   return false;

  XSTRING* _name = new XSTRING();
  if(!_name) return false;

  _name->Set(name);

  XSTRING* _text = new XSTRING();
  if(_text) 
    {     
      _text->Set(text);

      if(!_text->IsEmpty())
        {                 
          texts.Add(_name, _text); 
          return true;         
        }
    }
          
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_TEXTS::Add(XSTRING& name, XSTRING& text)
* @brief      Add
* @ingroup    USERINTERFACE
*
* @param[in]  name : 
* @param[in]  text : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool UI_TEXTS::Add(XSTRING& name, XSTRING& text)
{
  return Add(name.Get(), text.Get());
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSTRING* UI_TEXTS::Get(XCHAR* name)
* @brief      Get
* @ingroup    USERINTERFACE
*
* @param[in]  name : 
* 
* @return     XSTRING* : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
XSTRING* UI_TEXTS::Get(XCHAR* name)
{
  if(!name) return NULL;
  
  for(XDWORD c=0; c<texts.GetSize(); c++)
    {
      XSTRING* key = texts.GetKey(c);
      if(key)
        {
          if(!key->Compare(name)) return texts.GetElement(c);
        }
    }

  return NULL;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSTRING* UI_TEXTS::Get(XSTRING& name)
* @brief      Get
* @ingroup    USERINTERFACE
*
* @param[in]  name : 
* 
* @return     XSTRING* : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
XSTRING* UI_TEXTS::Get(XSTRING& name)
{
  return Get(name.Get());
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_TEXTS::DeleteAll()
* @brief      Delete all
* @ingroup    USERINTERFACE
*
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool UI_TEXTS::DeleteAll()
{
  texts.DeleteKeyContents();
  texts.DeleteElementContents();
  texts.DeleteAll();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         UI_TEXTS::UI_TEXTS()
* @brief      Constructor of class
* @ingroup    USERINTERFACE
*
* ---------------------------------------------------------------------------------------------------------------------*/
UI_TEXTS::UI_TEXTS()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         UI_TEXTS::~UI_TEXTS()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    USERINTERFACE
*
* ---------------------------------------------------------------------------------------------------------------------*/
UI_TEXTS::~UI_TEXTS()
{
  DeleteAll();

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void UI_TEXTS::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    USERINTERFACE
*
* ---------------------------------------------------------------------------------------------------------------------*/
void UI_TEXTS::Clean()
{

}


#pragma endregion

