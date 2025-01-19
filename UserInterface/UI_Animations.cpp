/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       UI_Animations.cpp
* 
* @class      UI_ANIMATIONS
* @brief      User Interface Animations class
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

#include "UI_Animations.h"

#include "UI_Animation.h"

#pragma endregion


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_CONTROL_INCLUDE

#include "GEN_Control.h"

#pragma endregion



/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

UI_ANIMATIONS* UI_ANIMATIONS::instance = NULL;

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_ANIMATIONS::GetIsInstanced()
* @brief      Get is instanced
* @ingroup    USERINTERFACE
*
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool UI_ANIMATIONS::GetIsInstanced()
{
  return instance!=NULL;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         UI_ANIMATIONS& UI_ANIMATIONS::GetInstance()
* @brief      Get instance
* @ingroup    USERINTERFACE
*
* @return     UI_ANIMATIONS& : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
UI_ANIMATIONS& UI_ANIMATIONS::GetInstance()
{
  if(!instance) 
    {
      instance = new UI_ANIMATIONS();
    }

  return (*instance);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_ANIMATIONS::DelInstance()
* @brief      Del instance
* @ingroup    USERINTERFACE
*
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool UI_ANIMATIONS::DelInstance()
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
* @fn         bool UI_ANIMATIONS::Add(UI_ANIMATION* animation)
* @brief      Add
* @ingroup    USERINTERFACE
* 
* @param[in]  animation : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool UI_ANIMATIONS::Add(UI_ANIMATION* animation)
{
  if(!animation)  return false;

  if(Get(animation->GetName()->Get()))      return false;
  if(Get(animation->GetResource()->Get()))  return false;

  animations.Add(animation); 

  return true;         
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         UI_ANIMATION* UI_ANIMATIONS::Get(XCHAR* ID)
* @brief      Get
* @ingroup    USERINTERFACE
*
* @param[in]  ID : 
* 
* @return     UI_ANIMATION* : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
UI_ANIMATION* UI_ANIMATIONS::Get(XCHAR* ID)
{
  if(!ID) return NULL;

  XSTRING IDstr;

  IDstr = ID;

  if(IDstr.IsEmpty()) return NULL;
  
  for(XDWORD c=0; c<animations.GetSize(); c++)
    {
      UI_ANIMATION* animation = animations.Get(c);
      if(animation)
        {
          if((!animation->GetName()->Compare(ID, true)) || (!animation->GetResource()->Compare(ID, true)))  return animation;
        }
    }

  return NULL;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         UI_ANIMATION* UI_ANIMATIONS::Get(XSTRING& ID)
* @brief      Get
* @ingroup    USERINTERFACE
*
* @param[in]  ID : 
* 
* @return     UI_ANIMATION* : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
UI_ANIMATION* UI_ANIMATIONS::Get(XSTRING& ID)
{
  return Get(ID.Get());
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_ANIMATIONS::DeleteAll()
* @brief      Delete all
* @ingroup    USERINTERFACE
*
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool UI_ANIMATIONS::DeleteAll()
{
  animations.DeleteContents();  
  animations.DeleteAll();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         UI_ANIMATIONS::UI_ANIMATIONS()
* @brief      Constructor of class
* @ingroup    USERINTERFACE
*
* ---------------------------------------------------------------------------------------------------------------------*/
UI_ANIMATIONS::UI_ANIMATIONS()
{
  Clean(); 
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         UI_ANIMATIONS::~UI_ANIMATIONS()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    USERINTERFACE
*
* ---------------------------------------------------------------------------------------------------------------------*/
UI_ANIMATIONS::~UI_ANIMATIONS()
{
  DeleteAll();

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void UI_ANIMATIONS::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    USERINTERFACE
*
* ---------------------------------------------------------------------------------------------------------------------*/
void UI_ANIMATIONS::Clean()
{

}


#pragma endregion

