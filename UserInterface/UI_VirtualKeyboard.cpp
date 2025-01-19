/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       UI_VirtualKeyboard.cpp
* 
* @class      UI_VIRTUALKEYBOARD
* @brief      User Interface Virtual Keyboard class
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

#include "UI_VirtualKeyboard.h"

#include "GRPScreen.h"
#include "GRPCanvas.h"
#include "GRPBitmapFile.h"

#include "UI_Animation.h"
#include "UI_Animations.h"
#include "UI_Layout.h"
#include "UI_Skin.h"
#include "UI_SkinCanvas.h"
#include "UI_Element_Image.h"
#include "UI_Element_Text.h"
#include "UI_Element_EditText.h"
#include "UI_Element_MultiOption.h"
#include "UI_Element_Option.h"
#include "UI_Element_Form.h"
#include "UI_Manager.h"

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


#pragma region CLASS_UI_VIRTUALKEYBOARD


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         UI_VIRTUALKEYBOARD_KEYINFO::UI_VIRTUALKEYBOARD_KEYINFO()
* @brief      Constructor of class
* @ingroup    USERINTERFACE
*
* ---------------------------------------------------------------------------------------------------------------------*/
UI_VIRTUALKEYBOARD_KEYINFO::UI_VIRTUALKEYBOARD_KEYINFO()    
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         UI_VIRTUALKEYBOARD_KEYINFO::~UI_VIRTUALKEYBOARD_KEYINFO()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    USERINTERFACE
*
* ---------------------------------------------------------------------------------------------------------------------*/
UI_VIRTUALKEYBOARD_KEYINFO::~UI_VIRTUALKEYBOARD_KEYINFO()
{
  Clean();
}

  
/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void UI_VIRTUALKEYBOARD_KEYINFO::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    USERINTERFACE
*
* ---------------------------------------------------------------------------------------------------------------------*/
void UI_VIRTUALKEYBOARD_KEYINFO::Clean()
{
  color.Empty();
  sizefont = 0;
  margin   = 0;
  xpos     = 0;
  ypos     = 0;
  width    = 0;
  height   = 0;
}


#pragma endregion


#pragma region CLASS_UI_VIRTUALKEYBOARD


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         UI_VIRTUALKEYBOARD::UI_VIRTUALKEYBOARD()
* @brief      Constructor of class
* @ingroup    USERINTERFACE
*
* ---------------------------------------------------------------------------------------------------------------------*/
UI_VIRTUALKEYBOARD::UI_VIRTUALKEYBOARD()
{ 
  Clean();                            
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn          UI_VIRTUALKEYBOARD::~UI_VIRTUALKEYBOARD()
* @brief      Destructor of class
* @ingroup    USERINTERFACE
*
* ---------------------------------------------------------------------------------------------------------------------*/
UI_VIRTUALKEYBOARD::~UI_VIRTUALKEYBOARD()
{ 
  Clean();                            
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_VIRTUALKEYBOARD::Ini(UI_LAYOUT* layout, GRPSCREEN* screen)
* @brief      Ini
* @ingroup    USERINTERFACE
* 
* @param[in]  layout : 
* @param[in]  screen : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool UI_VIRTUALKEYBOARD::Ini(UI_LAYOUT* layout, GRPSCREEN* screen)
{
  if(main_form) 
    {
      return false;
    }
 
  this->layout = layout;  
  this->screen = screen; 
  this->skin   = layout->GetSkin(); 

  main_form = new UI_ELEMENT_FORM();
  if(!main_form) return false;

  main_form->GetName()->Set(__L("Virtual Keyboard"));

  main_form->GetBoundaryLine()->x = 0;
  main_form->GetBoundaryLine()->y = 0;

  main_form->GetBoundaryLine()->width  = screen->GetWidth()-1;
  main_form->GetBoundaryLine()->height = (screen->GetHeight()-1)/2;

  main_form->GetVisibleRect()->CopyFrom((*main_form->GetBoundaryLine()));
    
  UI_COLOR* bckgcolor = main_form->GetColor();  
  UI_COLOR* linecolor = main_form->GetLineColor();
     
  if(bckgcolor) bckgcolor->SetFromString(__L("200,200,200,255"));
  if(linecolor) linecolor->SetFromString(__L("100,100,100,150"));

  main_form->SetVisible(false);
 
  layout->Elements_Add(main_form);

  CreateAllKeys(0 , screen->GetHeight());

  width  =  main_form->GetBoundaryLine()->width;
  height =  main_form->GetBoundaryLine()->height;

  actualset =  UI_VIRTUALKEYBOARD_SET_UPPERCASE;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_VIRTUALKEYBOARD::IsShow()
* @brief      Is show
* @ingroup    USERINTERFACE
*
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool UI_VIRTUALKEYBOARD::IsShow()
{
  return isshow;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         UI_ELEMENT* UI_VIRTUALKEYBOARD::GetElementEditable()
* @brief      Get element editable
* @ingroup    USERINTERFACE
*
* @return     UI_ELEMENT* : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
UI_ELEMENT* UI_VIRTUALKEYBOARD::GetElementEditable()
{
  return element_editable;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_VIRTUALKEYBOARD::Show(bool on, UI_ELEMENT* element_editable)
* @brief      Show
* @ingroup    USERINTERFACE
*
* @param[in]  on : 
* @param[in]  element_editable : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool UI_VIRTUALKEYBOARD::Show(bool on, UI_ELEMENT* element_editable)
{
  if(!main_form)  return false;

  double x = 0; 
  double y = 0;

  if(on)
    { 
      contentchanged = false;      
      
      if(!element_editable)  return false;

      this->element_editable = element_editable; 

      x = (screen->GetWidth() - main_form->GetBoundaryLine()->width)/2; 
      y = element_editable->GetYPosition() + height + 12;

      GEN_USERINTERFACE.Elements_RebuildDrawAreas(layout);
      GEN_USERINTERFACE.SetPreselectElement();
      DeleteAllKeys();
      CreateAllKeys(x, y);            

      GEN_USERINTERFACE.Element_SetModal(main_form);     

      if(element_editable->GetType() == UI_ELEMENT_TYPE_EDITTEXT)
        {
          UI_ELEMENT_EDITTEXT* element_edittext = (UI_ELEMENT_EDITTEXT*)element_editable;
          if(element_edittext)
            {
              XDWORD maxsizetext = element_edittext->GetMaxSizeText();                                                    
              XDWORD sizetext    = element_edittext->GetText()->GetSize();            

              if(!maxsizetext)  maxsizetext = sizetext;

              if(sizetext > maxsizetext) 
                {
                  sizetext = maxsizetext;
                  element_edittext->GetText()->AdjustSize(sizetext);

                }

              element_edittext->Cursor_SetVisible(true);
              element_edittext->Cursor_SetPosition(sizetext);
            }
        }

      isshow = true;
    }
   else 
    { 
      if(this->element_editable->GetType() == UI_ELEMENT_TYPE_EDITTEXT)
        {
          UI_ELEMENT_EDITTEXT* element_edittext = (UI_ELEMENT_EDITTEXT*)this->element_editable;
          if(element_edittext) element_edittext->Cursor_SetVisible(false);           
        }

      actualset         = UI_VIRTUALKEYBOARD_SET_UPPERCASE;
      element_editable  = NULL;

      GEN_USERINTERFACE.Element_SetModal(NULL);   

      GEN_USERINTERFACE.Elements_SetToRedraw();

      isshow = false;
    } 

  main_form->SetVisible(on);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_VIRTUALKEYBOARD::SelectInput(UI_ELEMENT* key_select)
* @brief      Select input
* @ingroup    USERINTERFACE
*
* @param[in]  key_select : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool UI_VIRTUALKEYBOARD::SelectInput(UI_ELEMENT* key_select)
{
  XCHAR* literals[] =  { __L("RETURN")        ,  // 0
                          __L("CAPS")         ,  // 1
                          __L("SYMBOLS")      ,  // 2
                          __L("BACK")         ,  // 3
                          __L("ARROWLEFT")    ,  // 4
                          __L("ARROWRIGHT")   ,  // 5
                          __L("SPACE")        ,  // 6
                        };

  if(!key_select) return false;

  XSTRING elementID;
  XSTRING keystr;

  UI_ELEMENT_EDITTEXT* element_edittext = (UI_ELEMENT_EDITTEXT*)element_editable;
  if(!element_edittext) return false;

  elementID = UI_VIRTUALKEYBOARD_ELEMENTID;

  int index = key_select->GetName()->Find(elementID, true);
  if(index == XSTRING_NOTFOUND) return false;
 
  index += elementID.GetSize();

  key_select->GetName()->Copy(index, keystr);

  int index_literal = -1;
  for(int c=0; c<(sizeof(literals) / sizeof(XCHAR*)); c++)
    {
      if(!keystr.Compare(literals[c], true)) 
        {
          index_literal = c;
          break;
        }
    }
  
  switch(index_literal)
    {
      case  0 : //-------------------------------------------------------      
                // RETURN

                {
                  if(contentchanged)
                    {
                      GEN_USERINTERFACE.SendEvent(UI_XEVENT_TYPE_OUTPUT_CHANGECONTENTS, element_editable); 
                      contentchanged = false;
                    }

                  Show(false, NULL);
                }
                break;      
    

      case  1 : //-------------------------------------------------------      
                // CAPS

                { bool   _contentchanged = contentchanged;
                  XDWORD cursor_position = element_edittext->Cursor_GetPosition(); 

                  if(actualset == UI_VIRTUALKEYBOARD_SET_UPPERCASE)  
                         actualset =  UI_VIRTUALKEYBOARD_SET_LOWERCASE; 
                    else actualset =  UI_VIRTUALKEYBOARD_SET_UPPERCASE;
      
                  Show(true, element_editable);

                  contentchanged = _contentchanged;
                  element_edittext->Cursor_SetPosition(cursor_position); 
                }
                break;

      case  2 : //-------------------------------------------------------      
                //  SYMBOLS

                { bool   _contentchanged = contentchanged;
                  XDWORD cursor_position = element_edittext->Cursor_GetPosition(); 

                  if(actualset == UI_VIRTUALKEYBOARD_SET_SYMBOLS)  
                          actualset =  UI_VIRTUALKEYBOARD_SET_UPPERCASE; 
                    else  actualset =  UI_VIRTUALKEYBOARD_SET_SYMBOLS;
    
                  Show(true, element_editable);
                  
                  contentchanged = _contentchanged;
                  element_edittext->Cursor_SetPosition(cursor_position); 
                }
                break;

      case  3 : //-------------------------------------------------------      
                // BACK

                { if(element_editable->GetType() == UI_ELEMENT_TYPE_EDITTEXT)      
                    {
                      XDWORD position = element_edittext->Cursor_GetPosition();
                      if(position) 
                        { 
                          element_edittext->GetText()->DeleteCharacters(position-1, 1); 
                          element_edittext->Cursor_SetPosition(position-1); 

                          contentchanged = true;             
                        }
                    }
                }
                break;

      case  4 : //-------------------------------------------------------      
                //  ARROW RIGHT

                { XDWORD position = element_edittext->Cursor_GetPosition();
      
                  if(position)  position--;
  
                  element_edittext->Cursor_SetPosition(position);
                }
                break;

      case  5 : //-------------------------------------------------------      
                // ARROW LEFT  

                {
                  XDWORD position = element_edittext->Cursor_GetPosition();
      
                  position++;
                  if(position > element_edittext->GetText()->GetSize())  position = element_edittext->GetText()->GetSize();
  
                  element_edittext->Cursor_SetPosition(position);
                }
                break;

      case  6 : //-------------------------------------------------------      
                // SPACE  

                {
                  keystr = __L(" ");
                } 

      default : //-------------------------------------------------------      
                // Other key  

                { if(element_editable->GetType() == UI_ELEMENT_TYPE_EDITTEXT)      
                    {
                      XDWORD position = element_edittext->Cursor_GetPosition();                            
                      if(element_edittext->GetText()->GetSize() + 1 <= element_edittext->GetMaxSizeText()) 
                        { 
                          element_edittext->GetText()->Insert(keystr, position);   
                          element_edittext->Cursor_SetPosition(position+1);   

                          contentchanged = true;
                        }
                    }
                }                
                break;


    }
    
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_VIRTUALKEYBOARD::End()
* @brief      End
* @ingroup    USERINTERFACE
*
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool UI_VIRTUALKEYBOARD::End()
{
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         UI_ANIMATION* UI_VIRTUALKEYBOARD::AddImageCache(XCHAR* name, XCHAR* resource)
* @brief      Add image cache
* @ingroup    USERINTERFACE
* 
* @param[in]  name : 
* @param[in]  resource : 
* 
* @return     UI_ANIMATION* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
UI_ANIMATION* UI_VIRTUALKEYBOARD::AddImageCache(XCHAR* name, XCHAR* resource)
{
  UI_ANIMATION* animation = NULL;

  if(!skin) return NULL;

  animation = GEN_UI_ANIMATIONS.Get(name);
  if(animation) return animation;

  animation = GEN_UI_ANIMATIONS.Get(resource);
  if(animation) return animation;

  animation = new UI_ANIMATION();
  if(!animation) return NULL;
  
  XSTRING resourcename;
  bool    status = false;

  resourcename = resource;

  switch(skin->GetDrawMode())
    {
      case UI_SKIN_DRAWMODE_UNKNOWN   : break;

      case UI_SKIN_DRAWMODE_CANVAS    : { UI_SKINCANVAS* skincanvas = (UI_SKINCANVAS*)skin; 
                                          if(skincanvas) status = animation->LoadFromFile(resourcename, skincanvas->GetCanvas()->GetMode());                                                                           
                                        }
                                        break;

      case UI_SKIN_DRAWMODE_CONTEXT   : break;
    } 

  if(status)   
    {      
      animation->GetName()->Set(name);  
      animation->GetResource()->Set(resource);

      GEN_UI_ANIMATIONS.Add(animation);

      return animation;
    }
  
  delete animation;

  return NULL;  
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         GRPBITMAP* UI_VIRTUALKEYBOARD::LoadKeyImage(XCHAR* pathimage)
* @brief      Load key image
* @ingroup    USERINTERFACE
*
* @param[in]  pathimage : 
* 
* @return     GRPBITMAP* : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
GRPBITMAP* UI_VIRTUALKEYBOARD::LoadKeyImage(XCHAR* pathimage)
{
  UI_ANIMATION* animation = NULL;
  GRPBITMAP*    bitmap    = NULL;  

  animation = AddImageCache(__L(""), pathimage);
  if(animation) bitmap = animation->GetBitmap();
    
  return bitmap;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_VIRTUALKEYBOARD::AddKeyButton(XCHAR* leyend, XCHAR* text, XCHAR* xpathbitmap, UI_VIRTUALKEYBOARD_KEYINFO& keyinfo)
* @brief      Add key button
* @ingroup    USERINTERFACE
*
* @param[in]  leyend : 
* @param[in]  text : 
* @param[in]  xpathbitmap : 
* @param[in]  keyinfo : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool UI_VIRTUALKEYBOARD::AddKeyButton(XCHAR* leyend, XCHAR* text, XCHAR* xpathbitmap, UI_VIRTUALKEYBOARD_KEYINFO& keyinfo)
{  
  UI_ELEMENT_MULTIOPTION* element_multioption = new UI_ELEMENT_MULTIOPTION();
  if(!element_multioption) return false;

  for(int c=0; c<4; c++)
    { 
      UI_ELEMENT_OPTION*            element_option  = new UI_ELEMENT_OPTION();
      UI_PROPERTY_SELECTABLE_STATE  state           = (UI_PROPERTY_SELECTABLE_STATE)c;
      if(!element_option) return false;
  
      if(text)
        {  
          UI_ELEMENT_TEXT* element_text = new UI_ELEMENT_TEXT();
          if(element_text) 
            {          
              element_text->SetFather(element_option);
              element_text->GetName()->Add(UI_VIRTUALKEYBOARD_ELEMENTID);
              element_text->GetName()->Add(leyend);
              element_text->GetText()->Set(text);
      
              element_text->GetBoundaryLine()->width  = skin->GetWithString(leyend, keyinfo.sizefont);
              element_text->GetBoundaryLine()->height = skin->GetHeightString(leyend, keyinfo.sizefont);
              element_text->GetBoundaryLine()->x      = ((keyinfo.width  - element_text->GetBoundaryLine()->width)  / 2);
              element_text->GetBoundaryLine()->y      = ((keyinfo.height - element_text->GetBoundaryLine()->height) / 2);         
 
              if(state == UI_PROPERTY_SELECTABLE_STATE_PRESELECT)
                {
                  element_text->GetColor()->SetFromString(__L("yellow,255"));
                }
               else 
                {
                  if(keyinfo.color.GetSize()) element_text->GetColor()->SetFromString(keyinfo.color);
                }

              element_text->SetSizeFont(keyinfo.sizefont);
                      
              element_option->Set_UIText(element_text);              

              GEN_USERINTERFACE.SetLevelAuto(element_text, element_option);   

              element_option->GetComposeElements()->Add(element_text);              
            }
        }

      if(xpathbitmap)
        {     
          UI_ELEMENT_ANIMATION* element_animation = new UI_ELEMENT_ANIMATION();
          if(element_animation) 
            {                  
              GRPBITMAP* bitmap = NULL;

              element_animation->SetFather(element_option);
              element_animation->GetName()->Add(UI_VIRTUALKEYBOARD_ELEMENTID);
              element_animation->GetName()->Add(leyend);
          
              UI_ELEMENT_IMAGE* element_image = new UI_ELEMENT_IMAGE();
              if(element_image) 
                {                  
                  bitmap = LoadKeyImage(xpathbitmap);
                  if(bitmap)
                    {
                      element_image->SetImage(bitmap);
                      element_animation->GetComposeElements()->Add(element_image);                                                                                  
                    }
                }

              if(bitmap) 
                {
                  element_image->SetFather(element_animation); 

                  element_image->GetBoundaryLine()->width       = bitmap->GetWidth();
                  element_image->GetBoundaryLine()->height      = bitmap->GetHeight();
                  element_image->GetBoundaryLine()->x           = 0; //keyinfo.xpos + ((keyinfo.width  - element_image->GetBoundaryLine()->width)  / 2); 
                  element_image->GetBoundaryLine()->y           = 0; //keyinfo.ypos - ((keyinfo.height - element_image->GetBoundaryLine()->height) / 2);      

                  element_animation->GetBoundaryLine()->width   = bitmap->GetWidth();
                  element_animation->GetBoundaryLine()->height  = bitmap->GetHeight();
                  element_animation->GetBoundaryLine()->x       = 0; //keyinfo.xpos + ((keyinfo.width  - element_animation->GetBoundaryLine()->width)  / 2);
                  element_animation->GetBoundaryLine()->y       = 0; //keyinfo.ypos - ((keyinfo.height - element_animation->GetBoundaryLine()->height) / 2);      
                  
                  element_option->Set_UIAnimation(element_animation);
                                    
                  GEN_USERINTERFACE.SetLevelAuto(element_animation, element_option);   

                  element_option->GetComposeElements()->Add(element_animation);               
                }
               else
                {
                  delete element_image;    
                  delete element_animation;    
                } 
            }
        }
                 
      element_option->SetFather(element_multioption);
      element_option->GetName()->Add(UI_VIRTUALKEYBOARD_ELEMENTID);
      element_option->SetSelectableState(state);
      element_option->GetName()->Add(leyend);      
      element_option->GetBoundaryLine()->x      = 0; //keyinfo.xpos;
      element_option->GetBoundaryLine()->y      = 0; //keyinfo.ypos;         
      element_option->GetBoundaryLine()->width  = keyinfo.width;
      element_option->GetBoundaryLine()->height = keyinfo.height;
      
      GEN_USERINTERFACE.SetLevelAuto(element_option, element_multioption);     

      element_multioption->GetComposeElements()->Add(element_option);     
    }

  element_multioption->SetFather(main_form);
  element_multioption->GetName()->Add(UI_VIRTUALKEYBOARD_ELEMENTID);
  element_multioption->GetName()->Add(leyend);  
  element_multioption->SetActive(true);  
  element_multioption->GetBoundaryLine()->x      = keyinfo.xpos;
  element_multioption->GetBoundaryLine()->y      = keyinfo.ypos;         
  element_multioption->GetBoundaryLine()->width  = keyinfo.width;
  element_multioption->GetBoundaryLine()->height = keyinfo.height;

  GEN_USERINTERFACE.SetLevelAuto(element_multioption, main_form);
                
  main_form->GetComposeElements()->Add(element_multioption);        

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_VIRTUALKEYBOARD::CreateAllKeys(double x, double y)
* @brief      Create all keys
* @ingroup    USERINTERFACE
*
* @param[in]  x : 
* @param[in]  y : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool UI_VIRTUALKEYBOARD::CreateAllKeys(double x, double y)
{
  #define UI_VIRTUALKEYBOARD_MARGIN   40
 
  XSTRING line[3][3][10] =  { { { __L("Q"), __L("W"), __L("E"), __L("R"), __L("T"), __L("Y"), __L("U"), __L("I"), __L("O"), __L("P") },
                                { __L("A"), __L("S"), __L("D"), __L("F"), __L("G"), __L("H"), __L("J"), __L("K"), __L("L"), __L("\xD1") },
                                { __L("Z"), __L("X"), __L("C"), __L("V"), __L("B"), __L("N"), __L("M"), __L("") , __L("") , __L("")  },
                              },
                              { { __L("q"), __L("w"), __L("e"), __L("r"), __L("t"), __L("y"), __L("u"), __L("i"), __L("o"), __L("p") },
                                { __L("a"), __L("s"), __L("d"), __L("f"), __L("g"), __L("h"), __L("j"), __L("k"), __L("l"), __L("\xF1") },
                                { __L("z"), __L("x"), __L("c"), __L("v"), __L("b"), __L("n"), __L("m"), __L("") , __L("") , __L("")  },
                              },
                              { { __L("1"), __L("2"), __L("3"), __L("4"), __L("5"), __L("6"), __L("7"), __L("8"), __L("9"), __L("0") },
                                { __L("@"), __L("#"), __L("!"), __L("_"), __L("&"), __L("-"), __L("+"), __L("("), __L(")"), __L("/") },
                                { __L("*"), __L("\""), __L("'"), __L(":"), __L(";"), __L(","), __L("?"), __L("") , __L("") , __L("")  },
                              }
                            };


  UI_VIRTUALKEYBOARD_KEYINFO keyinfo;
  XPATH                      pathimage;
  XDWORD                     key_normal_width  = 0; 
  XDWORD                     key_normal_height = 0; 

  GRPBITMAP* keyimage = LoadKeyImage(__L("virtualkbd/key.png"));
  if(keyimage)
    {
      key_normal_width  = keyimage->GetWidth();
      key_normal_height = keyimage->GetHeight();  

      //delete keyimage;
    }

  keyinfo.color     = __L("black,255");
  keyinfo.sizefont  = 32;
  keyinfo.margin    = 5;
  keyinfo.width     = key_normal_width;
  keyinfo.height    = key_normal_height;


  double sizewidth  = (keyinfo.width  * 10) + (UI_VIRTUALKEYBOARD_MARGIN*2); 
  double sizeheight = (keyinfo.height * 4)  + (UI_VIRTUALKEYBOARD_MARGIN*2); 

  main_form->GetBoundaryLine()->x       = x;
  main_form->GetBoundaryLine()->y       = y;
  main_form->GetBoundaryLine()->width   = sizewidth;
  main_form->GetBoundaryLine()->height  = sizeheight;

  main_form->GetBoundaryLine()->CopyTo((*main_form->GetVisibleRect()));
  
  double xpos           = UI_VIRTUALKEYBOARD_MARGIN;
  double ypos           = sizeheight -1 - UI_VIRTUALKEYBOARD_MARGIN - keyinfo.height;  

  keyinfo.xpos          = xpos;
  keyinfo.ypos          = ypos;
  
  int col               = 0; 
  int row               = 0;

      
  do{ for(col=0; col<10; col++)
        {              
          if(line[actualset][row][col].GetSize())
            {
              AddKeyButton(line[actualset][row][col].Get(), line[actualset][row][col].Get(), __L("virtualkbd/key.png"), keyinfo);
              keyinfo.xpos += keyinfo.width;          
            }
        }

      row++;

      if(row != 2) 
        { 
          keyinfo.xpos  = xpos; 
        }
       else 
        {
          keyinfo.xpos  = xpos +  (((keyinfo.width  * 10) -  (keyinfo.width  * 7)) /2);
        }

      keyinfo.ypos -= keyinfo.height;

    } while(row < 3);

 
  GRPBITMAP* spaceimage = LoadKeyImage(__L("virtualkbd/space_key.png"));
  if(spaceimage)
    {
      keyinfo.width   = spaceimage->GetWidth();
      keyinfo.height  = spaceimage->GetHeight();
      keyinfo.xpos    = (main_form->GetBoundaryLine()->width - keyinfo.width)/2;
      AddKeyButton(__L("SPACE"), NULL, __L("virtualkbd/space_key.png"), keyinfo);
      
      //delete spaceimage;
    }  
 
  keyinfo.width     = key_normal_width;
  keyinfo.height    = key_normal_height;

  keyinfo.xpos      = xpos + (key_normal_width *2);  
  AddKeyButton(__L("ARROWLEFT"), NULL, __L("virtualkbd/arrowleft_key.png"), keyinfo);


  keyinfo.xpos      = xpos + (key_normal_width * 7);  
  AddKeyButton(__L("ARROWRIGHT"), NULL, __L("virtualkbd/arrowright_key.png"), keyinfo);


  keyinfo.xpos      = xpos;
  keyinfo.ypos     += key_normal_height;
  AddKeyButton(__L("CAPS"), NULL, __L("virtualkbd/caps_key.png"), keyinfo);

  keyinfo.xpos      = xpos;
  keyinfo.ypos     -= key_normal_height;
  AddKeyButton(__L("SYMBOLS"), NULL, __L("virtualkbd/symbols_key.png"), keyinfo);

  keyinfo.xpos      = xpos + (key_normal_width * 9); 
  keyinfo.ypos     += key_normal_height;
  AddKeyButton(__L("BACK"), NULL, __L("virtualkbd/back_key.png"), keyinfo);

  keyinfo.xpos      = xpos + (key_normal_width * 9); 
  keyinfo.ypos     -= key_normal_height;
  AddKeyButton(__L("RETURN"), NULL, __L("virtualkbd/return_key.png"), keyinfo);
    
  if(skin) skin->CalculeBoundaryLine_AllElements(main_form, true);
  
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_VIRTUALKEYBOARD::DeleteAllKeys()
* @brief      Delete all keys
* @ingroup    USERINTERFACE
*
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool UI_VIRTUALKEYBOARD::DeleteAllKeys()
{
  if(main_form->GetComposeElements()->IsEmpty()) return false;

  main_form->GetComposeElements()->DeleteContents();
  main_form->GetComposeElements()->DeleteAll();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void UI_VIRTUALKEYBOARD::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    USERINTERFACE
*
* ---------------------------------------------------------------------------------------------------------------------*/
void UI_VIRTUALKEYBOARD::Clean()
{
  screen            = NULL;
  layout            = NULL;
  skin              = NULL;
  isshow            = false;
  main_form         = NULL;
  element_editable  = NULL;
  actualset         = UI_VIRTUALKEYBOARD_SET_UPPERCASE;
  contentchanged    = false;
}


#pragma endregion


#pragma endregion

