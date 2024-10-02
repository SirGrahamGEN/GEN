/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       UI_Manager.cpp
* 
* @class      UI_MANAGER
* @brief      User Interface Manager class
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
#pragma region PRECOMPILATION_INCLUDES

#include "GEN_Defines.h"

#pragma endregion


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "UI_Manager.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "XFactory.h"
#include "XThread.h"
#include "XTimer.h"
#include "XPath.h"
#include "XFile.h"
#include "XTrace.h"
#include "XTranslation.h"
#include "XSleep.h"

#include "INPCursorMotion.h"

#include "GRPProperties.h"
#include "GRPScreen.h"
#include "GRPCanvas.h"
#include "GRPBitmapFile.h"

#include "AppBase.h"

#include "UI_XEvent.h"
#include "UI_Color.h"
#include "UI_Colors.h"
#include "UI_Text.h"
#include "UI_Texts.h"
#include "UI_Animation.h"
#include "UI_Animations.h"
#include "UI_Element.h"
#include "UI_Element_Text.h"
#include "UI_Element_TextBox.h"
#include "UI_Element_Image.h"
#include "UI_Element_Animation.h"
#include "UI_Element_Option.h"
#include "UI_Element_MultiOption.h"
#include "UI_Element_Button.h"
#include "UI_Element_CheckBox.h"
#include "UI_Element_EditText.h"
#include "UI_Element_Form.h"
#include "UI_Element_Menu.h"
#include "UI_Element_ListBox.h"
#include "UI_Element_ProgressBar.h"
#include "UI_Element_Scroll.h"
#include "UI_VirtualKeyboard.h"

#include "UI_Skin.h"
#include "UI_SkinCanvas.h"
#include "UI_SkinCanvas_Flat.h"

#include "XMemory_Control.h"

#pragma endregion


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

UI_MANAGER* UI_MANAGER::instance = NULL;

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_MANAGER::GetIsInstanced()
* @brief      GetIsInstanced
* @ingroup    USERINTERFACE
*
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool UI_MANAGER::GetIsInstanced()
{
  return instance!=NULL;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         UI_MANAGER& UI_MANAGER::GetInstance()
* @brief      GetInstance
* @ingroup    USERINTERFACE
*
* @return     UI_MANAGER& : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
UI_MANAGER& UI_MANAGER::GetInstance()
{
  if(!instance) 
    {
      instance = new UI_MANAGER();
    }

  return (*instance);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_MANAGER::DelInstance()
* @brief      DelInstance
* @ingroup    USERINTERFACE
*
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool UI_MANAGER::DelInstance()
{
  if(instance)
    {
      delete instance;
      instance = NULL;
    }  

  GEN_UI_COLORS.DelInstance();

  GEN_UI_TEXTS.DelInstance();

  GEN_UI_ANIMATIONS.DelInstance();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_MANAGER::Load(XPATH& pathfile, GRPSCREEN* screen, int viewportindex)
* @brief      Load
* @ingroup    USERINTERFACE
* 
* @param[in]  pathfile : 
* @param[in]  screen : 
* @param[in]  viewportindex : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool UI_MANAGER::Load(XPATH& pathfile, GRPSCREEN* screen, int viewportindex)
{
  bool status = false;  

  if(pathfile.Find(__L(".zip"), true) != XSTRING_NOTFOUND) 
    {
      iszippedfile = true;
    }

  if(!iszippedfile)
    {
      status = LoadLayout(pathfile, screen, viewportindex);
    }
   else
    {
      unzipfile = new XFILEUNZIP();
      if(!unzipfile) 
        {
          return false;
        }

      if(unzipfile->Open(pathfile))
        {
          XSTRING origin_drive;
          XPATH   origin_path;
          XSTRING origin_namefile;
          XSTRING origin_ext;
          
          pathfile.GetDrive(origin_drive);
          pathfile.GetPath(origin_path);
          pathfile.GetNamefile(origin_namefile);
          pathfile.GetExt(origin_ext);
                          
          unzippathfile  = origin_drive;
          unzippathfile += origin_path; 

          XSTRING namefile;

          namefile    = origin_namefile;
          namefile   += __L(".xml");
                  
          status = unzipfile->DecompressFile(namefile, unzippathfile, namefile.Get());
          if(status)
            {
              XPATH unzippathfile_tmp;

              unzippathfile_tmp  = unzippathfile;
              unzippathfile_tmp += namefile;

              status = LoadLayout(unzippathfile_tmp, screen, viewportindex);                

              DeleteTemporalUnZipFile(unzippathfile_tmp);                          
            }
        }
       else 
        {
          CloseUnZipFile();        
        }        
    }

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_MANAGER::LoadLayout(XPATH& pathfile, GRPSCREEN* screen, int viewportindex)
* @brief      LoadLayout
* @ingroup    USERINTERFACE
* 
* @param[in]  pathfile : 
* @param[in]  screen : 
* @param[in]  viewportindex : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool UI_MANAGER::LoadLayout(XPATH& pathfile, GRPSCREEN* screen, int viewportindex)
{
  XFILEXML xml;
  bool     status = false;  
      
  if(xml.Open(pathfile, true))
    {      
      CreateLayouts(xml, screen, viewportindex);

      xml.Close();

      status = true;
    }

  return status;
}

/*
/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_MANAGER::IsZippedFile()
* @brief      IsZippedFile
* @ingroup    USERINTERFACE
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool UI_MANAGER::IsZippedFile()
{
  if(iszippedfile && unzipfile)
    {
      return true;
    }

  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XPATH* UI_MANAGER::GetUnzipPathFile()
* @brief      GetUnzipPathFile
* @ingroup    USERINTERFACE
* 
* @return     XPATH* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XPATH* UI_MANAGER::GetUnzipPathFile()
{
  return &unzippathfile;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XFILEUNZIP* UI_MANAGER::GetUnzipFile()
* @brief      GetUnzipFile
* @ingroup    USERINTERFACE
* 
* @return     XFILEUNZIP* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XFILEUNZIP* UI_MANAGER::GetUnzipFile()
{
  return unzipfile;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_MANAGER::DeleteTemporalUnZipFile(XPATH& pathfile)
* @brief      DeleteTemporalUnZipFile
* @ingroup    USERINTERFACE
* 
* @param[in]  pathfile : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool UI_MANAGER::DeleteTemporalUnZipFile(XPATH& pathfile)
{
  XFILE* xfile = GEN_XFACTORY.Create_File();
  if(!xfile)
    {
      return false;
    }
                
  xfile->Erase(pathfile);

  GEN_XFACTORY.Delete_File(xfile);

  return true;
}      


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_MANAGER::CloseUnZipFile()
* @brief      CloseUnZipFile
* @ingroup    USERINTERFACE
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool UI_MANAGER::CloseUnZipFile()
{
  if(!unzipfile) 
    {
      return false;
    }

  unzipfile->Close();
  delete unzipfile;

  unzipfile = NULL;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_MANAGER::Layouts_Add(UI_LAYOUT* layout)
* @brief      Layouts_Add
* @ingroup    USERINTERFACE
*
* @param[in]  layout : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool UI_MANAGER::Layouts_Add(UI_LAYOUT* layout)
{
  if(!layout) 
    {
      return false;
    }

  layouts.Add(layout);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XVECTOR<UI_LAYOUT*>* UI_MANAGER::Layouts_GetAll()
* @brief      Layouts_GetAll
* @ingroup    USERINTERFACE
* 
* @return     XVECTOR<UI_LAYOUT*>* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XVECTOR<UI_LAYOUT*>* UI_MANAGER::Layouts_GetAll()
{
  return &layouts;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         UI_LAYOUT* UI_MANAGER::Layouts_Get(int index)
* @brief      Layouts_Get
* @ingroup    USERINTERFACE
*
* @param[in]  index : 
* 
* @return     UI_LAYOUT* : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
UI_LAYOUT* UI_MANAGER::Layouts_Get(int index)
{
  if(layouts.IsEmpty())                     
    {
      return NULL;
    }

  if((XDWORD)index >= layouts.GetSize())    
    {
      return NULL;
    }
  
  return layouts.Get(index);    
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         UI_LAYOUT* UI_MANAGER::Layouts_Get(XCHAR* name)
* @brief      Layouts_Get
* @ingroup    USERINTERFACE
*
* @param[in]  name : 
* 
* @return     UI_LAYOUT* : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
UI_LAYOUT* UI_MANAGER::Layouts_Get(XCHAR* name)
{
  if(layouts.IsEmpty()) 
    {
      return NULL;
    }

  for(XDWORD c=0; c<layouts.GetSize(); c++)
    {
      UI_LAYOUT* layout = layouts.Get(c);
      if(layout) 
        {
          if(!layout->GetNameID()->Compare(name, true)) 
            {
              return layout;          
            }
        }
    }

  return NULL;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         UI_LAYOUT* UI_MANAGER::Layouts_Get(XSTRING& name)
* @brief      Layouts_Get
* @ingroup    USERINTERFACE
*
* @param[in]  name : 
* 
* @return     UI_LAYOUT* : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
UI_LAYOUT* UI_MANAGER::Layouts_Get(XSTRING& name)
{
  return Layouts_Get(name.Get());
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_MANAGER::Layouts_DeleteAll()
* @brief      Layouts_DeleteAll
* @ingroup    USERINTERFACE
*
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool UI_MANAGER::Layouts_DeleteAll()
{
  if(layouts.IsEmpty())  return false;

  layouts.DeleteContents();
  layouts.DeleteAll();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         UI_LAYOUT* UI_MANAGER::Layouts_GetInAll()
* @brief      Layouts_GetInAll
* @ingroup    USERINTERFACE
* 
* @return     UI_LAYOUT* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
UI_LAYOUT* UI_MANAGER::Layouts_GetCommonLayout()
{
  if(layout_commonindex == UI_MANAGER_LAYOUT_NOTFOUND) 
    {
      return NULL;  
    }

  if((XDWORD)layout_commonindex >= layouts.GetSize())     
    {
      return NULL;
    }

  return layouts.Get(layout_commonindex);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_MANAGER::Layout_PutBackground(XCHAR* layoutname)
* @brief      Layout_PutBackground
* @ingroup    USERINTERFACE
* 
* @param[in]  layoutname : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool UI_MANAGER::Layout_PutBackground(XCHAR* layoutname)
{
  bool status = false;

  status = Layout_PutBackgroundBitmap(layoutname);
  if(!status) 
    {
      status = Layout_PutBackgroundColor(layoutname);
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_MANAGER::Layout_PutBackgroundColor(XCHAR* layoutname)
* @brief      Layout_PutBackgroundColor
* @ingroup    USERINTERFACE
* 
* @param[in]  layoutname : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool UI_MANAGER::Layout_PutBackgroundColor(XCHAR* layoutname)
{
  UI_LAYOUT*  layout = NULL;
  UI_SKIN*    skin   = NULL;
  bool        status = false;

  layout = Layouts_Get(layoutname);
  if(!layout)
    {
      return false;
    }

  skin = layout->GetSkin();
  if(!skin)
    {
      return false;
    }
 
  switch(skin->GetDrawMode())
    {
      case UI_SKIN_DRAWMODE_UNKNOWN  :  break;

      case UI_SKIN_DRAWMODE_CANVAS   :  { UI_SKINCANVAS* skin_canvas  = (UI_SKINCANVAS*)skin;
                                          if(layout->GetBackground()->GetColor()->IsValid()) 
                                            { 
                                              GRPCANVAS* canvas = skin_canvas->GetCanvas();    
                                              if(canvas) 
                                                {
                                                  UI_COLOR color;

                                                  color.CopyFrom(layout->GetBackground()->GetColor()); 

                                                  GRP2DCOLOR_RGBA8 color_canvas(color.GetRed(), color.GetGreen(), color.GetBlue(), color.GetAlpha());  
                                                                                                                    
                                                  canvas->Clear(&color_canvas);

                                                  status = true;                                                        
                                                }
                                            }
                                        }
                                        break;

      case UI_SKIN_DRAWMODE_CONTEXT  :  break;
    }
                      
  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_MANAGER::Layout_PutBackgroundBitmap(XCHAR* layoutname)
* @brief      Layout_PutBackgroundBitmap
* @ingroup    USERINTERFACE
* 
* @param[in]  layoutname : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool UI_MANAGER::Layout_PutBackgroundBitmap(XCHAR* layoutname)
{
  UI_LAYOUT*  layout = NULL;
  UI_SKIN*    skin   = NULL;
  bool        status = false;

  layout = Layouts_Get(layoutname);
  if(!layout)
    {
      return false;
    }

  skin = layout->GetSkin();
  if(!skin)
    {
      return false;
    }
 
  switch(skin->GetDrawMode())
    {
      case UI_SKIN_DRAWMODE_UNKNOWN  :  break;

      case UI_SKIN_DRAWMODE_CANVAS   :  { UI_SKINCANVAS* skin_canvas  = (UI_SKINCANVAS*)skin;
                                          if(layout->GetBackground()->GetBitmap()) 
                                            { 
                                              GRPSCREEN* screen = skin_canvas->GetScreen();      
                                              GRPCANVAS* canvas = skin_canvas->GetCanvas();    
                                              if(canvas && screen) 
                                                {
                                                  layout->GetBackground()->GetBitmap()->Scale(screen->GetWidth(), screen->GetHeight());          
                                                  canvas->PutBitmapNoAlpha(0, 0, layout->GetBackground()->GetBitmap());                                              

                                                  status = true;
                                                }
                                            }
                                        }
                                        break;

      case UI_SKIN_DRAWMODE_CONTEXT  :  break;
    }
   
                      
  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_MANAGER::Layout_PutBackground()
* @brief      Layout_PutBackground
* @ingroup    USERINTERFACE
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool UI_MANAGER::Layout_PutBackground()
{
  bool status = false;

  status = Layout_PutBackgroundBitmap();
  if(!status) 
    {
      status = Layout_PutBackgroundColor();
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_MANAGER::Layout_PutBackgroundColor()
* @brief      Layout_PutBackgroundColor
* @ingroup    USERINTERFACE
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool UI_MANAGER::Layout_PutBackgroundColor()
{
  bool status = false;
  
  for(XDWORD c=0; c<Layouts_GetAll()->GetSize(); c++)
    { 
      UI_LAYOUT*  layout = NULL;
      UI_SKIN*    skin   = NULL;

      layout = Layouts_Get(c);
      if(layout)
        {       
          skin = layout->GetSkin();
          if(!skin)
            {
              return false;
            }
 
          switch(skin->GetDrawMode())
            {
              case UI_SKIN_DRAWMODE_UNKNOWN  :  break;

              case UI_SKIN_DRAWMODE_CANVAS   :  { UI_SKINCANVAS* skin_canvas  = (UI_SKINCANVAS*)skin;
                                                  if(layout->GetBackground()->GetColor()->IsValid()) 
                                                    { 
                                                      GRPCANVAS* canvas = skin_canvas->GetCanvas();    
                                                      if(canvas) 
                                                        {
                                                          UI_COLOR color;

                                                          color.CopyFrom(layout->GetBackground()->GetColor()); 

                                                          GRP2DCOLOR_RGBA8 color_canvas(color.GetRed(), color.GetGreen(), color.GetBlue(), color.GetAlpha());  
                                                                                                                    
                                                          canvas->Clear(&color_canvas);

                                                          status = true;                                                        
                                                        }
                                                    }
                                                }
                                                break;

              case UI_SKIN_DRAWMODE_CONTEXT  :  break;
            }
        }
    }
                      
  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_MANAGER::Layout_PutBackgroundBitmap()
* @brief      Layout_PutBackgroundBitmap
* @ingroup    USERINTERFACE
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool UI_MANAGER::Layout_PutBackgroundBitmap()
{  
  bool status = false;

  for(XDWORD c=0; c<Layouts_GetAll()->GetSize(); c++)
    { 
      UI_LAYOUT*  layout = NULL;
      UI_SKIN*    skin   = NULL;

      layout = Layouts_Get(c);
      if(layout)
        {    
          skin = layout->GetSkin();
          if(!skin)
            {
              return false;
            }
 
          switch(skin->GetDrawMode())
            {
              case UI_SKIN_DRAWMODE_UNKNOWN  :  break;

              case UI_SKIN_DRAWMODE_CANVAS   :  { UI_SKINCANVAS* skin_canvas  = (UI_SKINCANVAS*)skin;
                                                  if(layout->GetBackground()->GetBitmap()) 
                                                    { 
                                                      GRPSCREEN* screen = skin_canvas->GetScreen();      
                                                      GRPCANVAS* canvas = skin_canvas->GetCanvas();    
                                                      if(canvas && screen) 
                                                        {
                                                          layout->GetBackground()->GetBitmap()->Scale(screen->GetWidth(), screen->GetHeight());          
                                                          canvas->PutBitmapNoAlpha(0, 0, layout->GetBackground()->GetBitmap());                                              

                                                          status = true;
                                                        }
                                                    }
                                                }
                                                break;

              case UI_SKIN_DRAWMODE_CONTEXT  :  break;
            }
        }
    }   
                      
  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_MANAGER::Update(UI_LAYOUT* layout)
* @brief      Update
* @ingroup    USERINTERFACE
* 
* @param[in]  layout : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool UI_MANAGER::Update(UI_LAYOUT* layout)
{
  bool status = false;
  
  if(!layout)
    {
      return false;
    }

  ChangeTextElementValue(layout);

  status = layout->Update();  
  if(status)
    {         
      if(layout_commonindex != UI_MANAGER_LAYOUT_NOTFOUND)
        {         
          layout = Layouts_Get(layout_commonindex);
          if(!layout) 
            {
              return false;          
            }                   
        }

      if(element_modal)
        {
          if(xmutex_modal) xmutex_modal->Lock(); 
          
          Elements_SetToRedraw(element_modal);
        
          if(xmutex_modal) xmutex_modal->UnLock(); 
        }
    }

  if(virtualkeyboard) 
    {
      if(virtualkeyboard->IsShow())
        {
          Elements_SetToRedraw(virtualkeyboard->GetElementEditable());
        }
    }

  ChangeTextElementValue(layout);

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_MANAGER::Update()
* @brief      Update
* @ingroup    USERINTERFACE
*
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool UI_MANAGER::Update(XCHAR* layoutname)
{
  UI_LAYOUT*  layout = NULL;
  bool        status = false;

  layout = Layouts_Get(layoutname);
  if(!layout)
    {
      return false;
    }

  ChangeTextElementValue(layout);

  status = layout->Update();  
  if(status)
    {         
      if(layout_commonindex != UI_MANAGER_LAYOUT_NOTFOUND)
        {         
          layout = Layouts_Get(layout_commonindex);
          if(!layout) 
            {
              return false;          
            }                   
        }

      if(element_modal)
        {
          if(xmutex_modal) xmutex_modal->Lock(); 
          
          Elements_SetToRedraw(element_modal);
        
          if(xmutex_modal) xmutex_modal->UnLock(); 
        }
    }

  if(virtualkeyboard) 
    {
      if(virtualkeyboard->IsShow())
        {
          Elements_SetToRedraw(virtualkeyboard->GetElementEditable());
        }
    }

  ChangeTextElementValue(layout);

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_MANAGER::Update()
* @brief      Update
* @ingroup    USERINTERFACE
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool UI_MANAGER::Update()
{
  bool status = false;

  for(XDWORD c=0; c<layouts.GetSize(); c++)
    { 
      UI_LAYOUT* layout = layouts.Get(c);
      if(layout)
        {
          status = Update(layout);
          if(!status)
            {
              break;
            }
        }
    } 

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         UI_ELEMENT* UI_MANAGER::Element_Get(XCHAR* layoutname, XCHAR* name, UI_ELEMENT_TYPE type)
* @brief      Element_Get
* @ingroup    USERINTERFACE
* 
* @param[in]  layoutname : 
* @param[in]  name : 
* @param[in]  type : 
* 
* @return     UI_ELEMENT* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
UI_ELEMENT* UI_MANAGER::Element_Get(XCHAR* layoutname, XCHAR* name, UI_ELEMENT_TYPE type)
{  
  UI_LAYOUT*  layout = NULL; 
  UI_ELEMENT* element = NULL;

  layout = Layouts_Get(layoutname);
  if(!layout)
    {
      return NULL;
    }

  element = layout->Elements_Get(name, type);
  if(!element)
    {
      if(layout_commonindex != UI_MANAGER_LAYOUT_NOTFOUND)
        {
          layout = Layouts_Get(layout_commonindex);
          if(!layout) 
            {
              return NULL;
            }

          element = layout->Elements_Get(name, type);
        }
    }

  return element;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         UI_ELEMENT* UI_MANAGER::GetElement(XSTRING& name, UI_ELEMENT_TYPE type)
* @brief      GetElement
* @ingroup    USERINTERFACE
*
* @param[in]  name : 
* @param[in]  type : 
* 
* @return     UI_ELEMENT* : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
UI_ELEMENT* UI_MANAGER::Element_Get(XCHAR* layoutname, XSTRING& name, UI_ELEMENT_TYPE type)
{
  return Element_Get(layoutname, name.Get(), type);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         UI_ELEMENT* UI_MANAGER::Element_Get(XCHAR* name, UI_ELEMENT_TYPE type)
* @brief      Element_Get
* @ingroup    USERINTERFACE
* 
* @param[in]  name : 
* @param[in]  type : 
* 
* @return     UI_ELEMENT* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
UI_ELEMENT* UI_MANAGER::Element_Get(XCHAR* name, UI_ELEMENT_TYPE type)
{ 
  if(layouts.IsEmpty()) 
    {
      return NULL;
    }

  UI_ELEMENT* element = NULL; 

  for(XDWORD c=0; c<layouts.GetSize(); c++)
    { 
      UI_LAYOUT* layout = layouts.Get(c);
      if(layout) 
        {          
          element = layout->Elements_Get(name, type);
          if(element) 
            {
              return element;              
            }
        }
    }

  return element;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         UI_ELEMENT* UI_MANAGER::Element_Get(XSTRING& name, UI_ELEMENT_TYPE type)
* @brief      Element_Get
* @ingroup    USERINTERFACE
* 
* @param[in]  name : 
* @param[in]  type : 
* 
* @return     UI_ELEMENT* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
UI_ELEMENT* UI_MANAGER::Element_Get(XSTRING& name, UI_ELEMENT_TYPE type)
{ 
  return Element_Get(name.Get(), type);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         UI_LAYOUT* UI_MANAGER::GetElementLayout(UI_ELEMENT* element)
* @brief      GetElementLayout
* @ingroup    USERINTERFACE
*
* @param[in]  element : 
* 
* @return     UI_LAYOUT* : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
UI_LAYOUT* UI_MANAGER::Element_GetLayout(UI_ELEMENT* element)
{
  if(!element) 
    {
      return NULL;
    }

  if(layouts.IsEmpty()) 
    {
      return NULL;
    }

  for(XDWORD c=0; c<layouts.GetSize(); c++)
    { 
      UI_LAYOUT* layout = layouts.Get(c);
      if(layout) 
        { 
          XVECTOR<UI_ELEMENT*>* layout_elements = layout->Elements_Get();
          if(layout_elements) 
            {
              bool    found = false;
              XDWORD  index = 0;
 
              do{ UI_ELEMENT* _element = layout_elements->Get(index);
                  if(_element) 
                    {
                      if(_element == element) 
                        {
                          found = true;
                          break;
                        }
                    } 

                  index++;

                } while(index < layout_elements->GetSize());    
                               
              if(found) 
                {
                  return layout;              
                }
            }
        }
    }

  return NULL;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         UI_LAYOUT* UI_MANAGER::Element_GetLayout(XCHAR* name, UI_ELEMENT_TYPE type)
* @brief      Element_GetLayout
* @ingroup    USERINTERFACE
* 
* @param[in]  name : 
* @param[in]  type : 
* 
* @return     UI_LAYOUT* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
UI_LAYOUT* UI_MANAGER::Element_GetLayout(XCHAR* name, UI_ELEMENT_TYPE type)
{
  if(layouts.IsEmpty()) 
    {
      return NULL;
    }

  UI_ELEMENT* element = NULL; 

  for(XDWORD c=0; c<layouts.GetSize(); c++)
    { 
      UI_LAYOUT* layout = layouts.Get(c);
      if(layout) 
        {          
          element = layout->Elements_Get(name, type);
          if(element) 
            {
              return layout;              
            }
        }
    }

  return NULL;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         UI_LAYOUT* UI_MANAGER::Element_GetLayout(XSTRING& name, UI_ELEMENT_TYPE type)
* @brief      Element_GetLayout
* @ingroup    USERINTERFACE
* 
* @param[in]  name : 
* @param[in]  type : 
* 
* @return     UI_LAYOUT* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
UI_LAYOUT* UI_MANAGER::Element_GetLayout(XSTRING& name, UI_ELEMENT_TYPE type)
{
  return Element_GetLayout(name.Get(), type);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_MANAGER::Element_PutToLastPositionLayout(UI_ELEMENT* element)
* @brief      Element_PutToLastPositionLayout
* @ingroup    USERINTERFACE
* 
* @param[in]  element : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool UI_MANAGER::Element_PutToLastPositionLayout(UI_ELEMENT* element)
{
  if(!element) 
    {
      return false;
    }

  UI_LAYOUT* layout = Element_GetLayout(element);
  if(!layout) 
    {
      return false;
    }

  XVECTOR<UI_ELEMENT*>* layout_elements = layout->Elements_Get();
  if(!layout_elements) 
    {
      return false;
    }
  
  bool   found = false;
  XDWORD index = 0;

  do{ UI_ELEMENT* _element = layout_elements->Get(index);
      if(_element) 
        {
          if(_element == element) 
            {
              found = true;
              break;
            }
        } 

       index++;

    } while(index < layout_elements->GetSize());

  if(!found) 
    {
      return false;  
    }

  UI_ELEMENT* sustitute_element =  layout_elements->Get(layout_elements->GetSize()-1);
  if(!sustitute_element) return false;

  layout_elements->Set(layout_elements->GetSize()-1, layout_elements->Get(index));
  layout_elements->Set(index, sustitute_element);         

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_MANAGER::Element_PutToLastPositionLayout(XCHAR* name, UI_ELEMENT_TYPE type)
* @brief      Element_PutToLastPositionLayout
* @ingroup    USERINTERFACE
* 
* @param[in]  name : 
* @param[in]  type : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool UI_MANAGER::Element_PutToLastPositionLayout(XCHAR* name, UI_ELEMENT_TYPE type)
{
  UI_LAYOUT* layout = Element_GetLayout(name, type);
  if(!layout) 
    {
      return false;
    }

  UI_ELEMENT* element = layout->Elements_Get(name, type);
  if(!element) 
    {
      return false;
    }

  XVECTOR<UI_ELEMENT*>* layout_elements = layout->Elements_Get();
  if(!layout_elements) 
    {
      return false;
    }
  
  bool    found = false;
  XDWORD  index = 0;

  do{ UI_ELEMENT* _element = layout_elements->Get(index);
      if(_element) 
        {
          if(_element == element) 
            {
              found = true;
              break;
            }
        } 

       index++;

    } while(index < layout_elements->GetSize());

  if(!found) 
    {
      return false;  
    }

  UI_ELEMENT* sustitute_element =  layout_elements->Get(layout_elements->GetSize()-1);
  if(!sustitute_element) 
    {
      return false;
    }

  layout_elements->Set(layout_elements->GetSize()-1, layout_elements->Get(index));
  layout_elements->Set(index, sustitute_element);         

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_MANAGER::Element_PutToLastPositionLayout(XSTRING& name, UI_ELEMENT_TYPE type)
* @brief      Element_PutToLastPositionLayout
* @ingroup    USERINTERFACE
* 
* @param[in]  name : 
* @param[in]  type : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool UI_MANAGER::Element_PutToLastPositionLayout(XSTRING& name, UI_ELEMENT_TYPE type)
{
  return Element_PutToLastPositionLayout(name.Get(), type);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_MANAGER::Element_SetModal(UI_ELEMENT* element_modal)
* @brief      Element_SetModal
* @ingroup    USERINTERFACE
* 
* @param[in]  element_modal : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool UI_MANAGER::Element_SetModal(UI_ELEMENT* element_modal)
{
  if(xmutex_modal) 
    {
      xmutex_modal->Lock();
    }

  if(element_modal) 
    {
      Element_PutToLastPositionLayout(element_modal);
    }

  this->element_modal = element_modal;

  if(xmutex_modal) 
    {
      xmutex_modal->UnLock();
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_MANAGER::Elements_SetToRedraw()
* @brief      Elements_SetToRedraw
* @ingroup    USERINTERFACE
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool UI_MANAGER::Elements_SetToRedraw()
{
  bool status = false; 
  
  for(XDWORD c=0; c<layouts.GetSize(); c++)
    {
      UI_LAYOUT* layout = layouts.Get(c);
      if(layout)
        {     
          status = layout->Elements_SetToRedraw();
        }
    }
  
  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_MANAGER::Elements_SetToRedraw(UI_LAYOUT* layout, UI_ELEMENT* element, bool recursive)
* @brief      Elements_SetToRedraw
* @ingroup    USERINTERFACE
* 
* @param[in]  layout : 
* @param[in]  element : 
* @param[in]  recursive : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool UI_MANAGER::Elements_SetToRedraw(UI_ELEMENT* element, bool recursive)
{
  bool status = false; 
  
  for(XDWORD c=0; c<layouts.GetSize(); c++)
    {
      UI_LAYOUT* layout = layouts.Get(c);
      if(layout)
        {     
          status = layout->Elements_SetToRedraw(element, recursive);         
        }
    }
  
  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_MANAGER::Elements_RebuildDrawAreas()
* @brief      Elements_RebuildDrawAreas
* @ingroup    USERINTERFACE
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool UI_MANAGER::Elements_RebuildDrawAreas()
{  
  bool status = false; 

  for(XDWORD c=0; c<layouts.GetSize(); c++)
    {
      UI_LAYOUT* layout = layouts.Get(c);
      if(layout)
        {    
          if(layout->GetSkin())
            {
              UnSelectedElement();  

              switch(layout->GetSkin()->GetDrawMode())
                {
                  case UI_SKIN_DRAWMODE_UNKNOWN   : break;

                  case UI_SKIN_DRAWMODE_CANVAS    : { UI_SKINCANVAS* skincanvas = (UI_SKINCANVAS*)layout->GetSkin();
                                                      if(skincanvas) 
                                                        {
                                                          status = skincanvas->RebuildAllAreas();                                                                                
                                                        }
                                                    }
                                                    break;

                  case UI_SKIN_DRAWMODE_CONTEXT   : break;
                }
            }
        }
    }

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_MANAGER::Elements_RebuildDrawAreas(UI_LAYOUT* layout)
* @brief      Elements_RebuildDrawAreas
* @ingroup    USERINTERFACE
* 
* @param[in]  layout : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool UI_MANAGER::Elements_RebuildDrawAreas(UI_LAYOUT* layout)
{  
  bool status = false; 

  if(!layout)
    {
      return false;
    }

  if(!layout->GetSkin())
    {
      return false;
    }

  UnSelectedElement();  

  switch(layout->GetSkin()->GetDrawMode())
    {
      case UI_SKIN_DRAWMODE_UNKNOWN   : break;

      case UI_SKIN_DRAWMODE_CANVAS    : { UI_SKINCANVAS* skincanvas = (UI_SKINCANVAS*)layout->GetSkin();
                                          if(skincanvas) 
                                            {
                                              status = skincanvas->RebuildAllAreas();                                                                                
                                            }
                                        }
                                        break;

      case UI_SKIN_DRAWMODE_CONTEXT   : break;
    }

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_MANAGER::Elements_RebuildDrawAreas(UI_LAYOUT* layout, UI_ELEMENT* element)
* @brief      Elements_RebuildDrawAreas
* @ingroup    USERINTERFACE
* 
* @param[in]  layout : 
* @param[in]  element : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool UI_MANAGER::Elements_RebuildDrawAreas(UI_LAYOUT* layout, UI_ELEMENT* element)
{
  bool status = false; 
  
  if(!layout)
    {
      return false;
    }

  if(!layout->GetSkin())
    {
      return false;
    }

  UnSelectedElement();  

  switch(layout->GetSkin()->GetDrawMode())
    {
      case UI_SKIN_DRAWMODE_UNKNOWN   : break;

      case UI_SKIN_DRAWMODE_CANVAS    : { UI_SKINCANVAS* skincanvas = (UI_SKINCANVAS*)layout->GetSkin();
                                          if(skincanvas) 
                                            {
                                              status = skincanvas->RebuildAllAreas(element);                                                                                
                                            }
                                        }
                                        break;

      case UI_SKIN_DRAWMODE_CONTEXT   : break;
    }

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_MANAGER::Elements_RebuildDrawAreas(XCHAR* layoutname)
* @brief      Elements_RebuildDrawAreas
* @ingroup    USERINTERFACE
* 
* @param[in]  layoutname : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool UI_MANAGER::Elements_RebuildDrawAreas(XCHAR* layoutname)
{ 
  UI_LAYOUT* layout = NULL;
  
  layout = Layouts_Get(layoutname);
  if(!layout)
    {
      return false;
    }
  
  return Elements_RebuildDrawAreas(layout);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_MANAGER::Elements_RebuildDrawAreas(UI_ELEMENT* element)
* @brief      Elements_RebuildDrawAreas
* @ingroup    USERINTERFACE
*
* @param[in]  element : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool UI_MANAGER::Elements_RebuildDrawAreas(XCHAR* layoutname, UI_ELEMENT* element)
{
  UI_LAYOUT* layout = NULL;
  
  layout = Layouts_Get(layoutname);
  if(!layout)
    {
      return false;
    }
  
  return Elements_RebuildDrawAreas(layout, element);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         int UI_MANAGER::GetOutputTextChangeID(XSTRING* text, int start, XSTRING& value)
* @brief      GetOutputTextChangeID
* @ingroup    USERINTERFACE
*
* @param[in]  text : 
* @param[in]  start : 
* @param[in]  value : 
* 
* @return     int : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
int UI_MANAGER::GetOutputTextChangeID(XSTRING* text, int start, XSTRING& value)
{
  if(!text) 
    {
      return false;
    }
  
  int ini_mask;
  int end_mask;

  ini_mask = text->Find(UI_MANAGER_LAYOUT_TEXT_INI, true, start);
  if(ini_mask != XSTRING_NOTFOUND)
    {
      end_mask = text->Find(UI_MANAGER_LAYOUT_TEXT_END, true, ini_mask);
      if(end_mask != XSTRING_NOTFOUND)
        {
          text->Copy(ini_mask+2, end_mask, value);

          return ini_mask;
        }       
    }                             

  return XSTRING_NOTFOUND;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         UI_ANIMATION* UI_MANAGER::GetOrAddAnimationCache(UI_SKIN_DRAWMODE drawmode, GRPPROPERTYMODE grppropertymode, XCHAR* name, XCHAR* resource)
* @brief      GetOrAddAnimationCache
* @ingroup    USERINTERFACE
* 
* @param[in]  drawmode : 
* @param[in]  grppropertymode : 
* @param[in]  name : 
* @param[in]  resource : 
* 
* @return     UI_ANIMATION* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
UI_ANIMATION* UI_MANAGER::GetOrAddAnimationCache(UI_SKIN_DRAWMODE drawmode, GRPPROPERTYMODE grppropertymode, XCHAR* name, XCHAR* resource)
{
  UI_ANIMATION* animation = NULL;
  bool          status    = false; 

  animation = GEN_UI_ANIMATIONS.Get(name);
  if(animation) 
    {
      return animation;
    }

  animation = GEN_UI_ANIMATIONS.Get(resource);
  if(animation) 
    {
      return animation;
    }

  animation = new UI_ANIMATION();
  if(!animation) 
    {
      return NULL;
    }
  
  XSTRING resourcename;
  
  resourcename = resource;

  switch(drawmode)
    {
      case UI_SKIN_DRAWMODE_UNKNOWN   : break;

      case UI_SKIN_DRAWMODE_CANVAS    : status = animation->LoadFromFile(resourcename, grppropertymode);                                                                           
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
* @fn         bool UI_MANAGER::SetLevelAuto(UI_ELEMENT* element, UI_ELEMENT* father, XDWORD addlevel)
* @brief      SetLevelAuto
* @ingroup    USERINTERFACE
*
* @param[in]  element : 
* @param[in]  father : 
* @param[in]  addlevel : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool UI_MANAGER::SetLevelAuto(UI_ELEMENT* element, UI_ELEMENT* father, XDWORD addlevel)
{
  if(father)
    {
      XDWORD zlevel_father = father->GetZLevel();    
      if(element) 
        {
          element->SetZLevel(element->GetZLevel() + zlevel_father + addlevel);
        }
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_MANAGER::SetPreselectElement(UI_ELEMENT* element)
* @brief      SetPreselectElement
* @ingroup    USERINTERFACE
*
* @param[in]  element : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool UI_MANAGER::SetPreselectElement(UI_ELEMENT* element)
{
  preselect_element = element;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_MANAGER::ResetPreselect(XCHAR* layoutname)
* @brief      ResetPreselect
* @ingroup    USERINTERFACE
* 
* @param[in]  layoutname : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool UI_MANAGER::ResetPreselect()
{
  if(!preselect_element) 
    {
      return false;
    }

  preselect_element->SetPreSelect(false); 
   
  Elements_SetToRedraw(preselect_element);                                                                

  preselect_element = NULL; 

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_MANAGER::SendEvent(UI_XEVENT_TYPE event, ...)
* @brief      SendEvent
* @ingroup    USERINTERFACE
*
* @param[in]  event : 
* @param[in]  ... : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool UI_MANAGER::SendEvent(UI_XEVENT_TYPE event, ...)
{
  UI_XEVENT xevent(this, event);
  va_list   arg;
  bool      postevent = false;
  bool      status    = false;

  if(xmutex_UIevent) 
    {
      xmutex_UIevent->Lock();
    }

  va_start(arg, event);
  
  switch(event)
    {
      case UI_XEVENT_TYPE_INPUT_CURSOR_MOVE         : 
      case UI_XEVENT_TYPE_INPUT_SELECCTION          : { int x = (int)va_arg(arg, int);
                                                        int y = (int)va_arg(arg, int);

                                                        xevent.SetXPos((XDWORD)x);
                                                        xevent.SetYPos((XDWORD)y);

                                                        postevent = true;
                                                      }
                                                      break;

      case UI_XEVENT_TYPE_INPUT_CURSOR_MOTION       : { void* ptr = (void*)va_arg(arg, void*);
                                                        if(ptr)
                                                          {
                                                            INPCURSORMOTION* cursormotion = (INPCURSORMOTION*)ptr;
                                                            if(cursormotion)
                                                              {                  
                                                                xevent.SetCursorMotion(cursormotion);
                                                                postevent = true;
                                                              }
                                                          }  
                                                      }
                                                      break;  

      case UI_XEVENT_TYPE_OUTPUT_SELECTED           : { void* ptr = (void*)va_arg(arg, void*);
                                                        if(ptr)
                                                          {   
                                                            UI_ELEMENT* element = (UI_ELEMENT*)ptr;
                                                            if(element) 
                                                              {
                                                                UI_ELEMENT* element_father = element->GetFather();
                                                        
                                                                if(element_father) 
                                                                  {
                                                                    if(!element_father->IsVisible())
                                                                      {
                                                                        break;
                                                                      }
                                                                  }

                                                                if(element->IsVisible()) 
                                                                  { 
                                                                    //XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("UI Element [%s]: Selected. "), element->GetName()->Get());

                                                                    xevent.SetElement(element);          
                                                                    postevent = true;
                                                                  }
                                                              }
                                                          }
                                                      }
                                                      break;

      case UI_XEVENT_TYPE_OUTPUT_TEXTTOCHANGE       : { void* ptr = (void*)va_arg(arg, void*);
                                                        if(ptr)
                                                          {   
                                                            UI_ELEMENT* element = (UI_ELEMENT*)ptr;
                                                            if(element) 
                                                              {
                                                                XSTRING* maskvalue = (XSTRING*)va_arg(arg, void*);
                                                                if(maskvalue)  xevent.GetMaskTextValue()->Set(maskvalue->Get());

                                                                /*
                                                                ChangeAutomaticLiteralText((UI_ELEMENT_TEXT*)element, maskvalue, xevent.GetMaskText());
                                                                
                                                                if(!xevent.GetMaskText()->IsEmpty())
                                                                  {
                                                                    XSTRING* maskresolve = (XSTRING*)va_arg(arg, void*);
                                                                    if(maskresolve) maskresolve->Set(xevent.GetMaskText()->Get()); 
                                                                    postevent = false;
                                                                  }
                                                                 else   
                                                                 */
                                                                  {
                                                                    xevent.SetElement(element);  
                                                                    postevent = true;    
                                                                  }
                                                              }
                                                          }
                                                      }  
                                                      break;

       case UI_XEVENT_TYPE_OUTPUT_CHANGECONTENTS    : { void* ptr = (void*)va_arg(arg, void*);
                                                        if(ptr)
                                                          {   
                                                            UI_ELEMENT* element = (UI_ELEMENT*)ptr;
                                                            if(element) 
                                                              {
                                                                xevent.SetElement(element);                                                                        
                                                                postevent = true;
                                                              }  
                                                          }
                                                      }
                                                      break;



    }
  
  if(postevent) 
    {          
      status = PostEvent(&xevent);         
      if(status)
        {  
          switch(event)
            {
              case UI_XEVENT_TYPE_OUTPUT_TEXTTOCHANGE   : { XSTRING* maskresolve = (XSTRING*)va_arg(arg, void*);
                                                            if(maskresolve) maskresolve->Set(xevent.GetMaskTextResolved()->Get()); 
                                                          }  
                                                          break;
            }
        }  
    }

  va_end(arg);

  if(xmutex_UIevent) xmutex_UIevent->UnLock();

  return status;

}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_MANAGER::ChangeAutomaticTextElementValue(UI_ELEMENT* element, XSTRING* maskvalue, XSTRING* maskresolved)
* @brief      ChangeAutomaticTextElementValue
* @ingroup    USERINTERFACE
* 
* @param[in]  element : 
* @param[in]  maskvalue : 
* @param[in]  maskresolved : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool UI_MANAGER::ChangeAutomaticTextElementValue(UI_ELEMENT* element, XSTRING* maskvalue, XSTRING* maskresolved)
{
  if(!element)        return false;
  if(!maskvalue)      return false;
  if(!maskresolved)   return false;

  UI_ELEMENT* father = element->GetFather();
  if(father)
    {
      if(father->GetType() == UI_ELEMENT_TYPE_PROGRESSBAR)
        {
          if(!maskvalue->Compare(__L("PROGRESSBAR_PERCENT"), true))
            {
              UI_ELEMENT_PROGRESSBAR* element_progressbar = (UI_ELEMENT_PROGRESSBAR*)father;
              static float last_level = -10;
        
              if(last_level != element_progressbar->GetLevel())                
                {              
                  maskresolved->Format(__L("%d"), (int)element_progressbar->GetLevel());
                  maskresolved->Add(__L("\x25"));

                  last_level = element_progressbar->GetLevel();                                  

                  return true;
                }              
            }
        }
    }

  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_MANAGER::ChangeTextElementValue(UI_ELEMENT* element, XSTRING* text, XSTRING& value)
* @brief      ChangeTextElementValue
* @ingroup    USERINTERFACE
*
* @param[in]  element : 
* @param[in]  text : 
* @param[in]  value : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool UI_MANAGER::ChangeTextElementValue(UI_ELEMENT* element, XSTRING* text, XSTRING& value)
{
  XSTRING  maskvalue;
  XSTRING  maskresolve;  
  int      start      = 0;
  int      new_start  = 0;
  bool     change     = false;
  
  do{ new_start = GEN_USERINTERFACE.GetOutputTextChangeID(text, start, maskvalue);

      if(new_start != XSTRING_NOTFOUND)
        {
          XSTRING subtext;
       
          text->Copy(start, new_start, subtext);
          if(!subtext.IsEmpty()) value.Add(subtext);
           
          maskresolve.Empty();

          if(ChangeAutomaticTextElementValue(element, &maskvalue, &maskresolve))
            {                
              value.Add(maskresolve);                 
              change = true;                    
            }
           else 
            {
              SendEvent(UI_XEVENT_TYPE_OUTPUT_TEXTTOCHANGE, element, &maskvalue, &maskresolve);
              if(!maskresolve.IsEmpty()) 
                {
                  value.Add(maskresolve);                 
                  change = true;              
                }  
            }

          start = new_start + maskvalue.GetSize() + 3;               

        }
       else 
        {
          XSTRING subtext;

          text->Copy(start, subtext);
          value.Add(subtext);                                  
        }

    } while(new_start != XSTRING_NOTFOUND);

  return change;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_MANAGER::ChangeTextElementValue(UI_LAYOUT* layout, UI_ELEMENT* element)
* @brief      ChangeTextElementValue
* @ingroup    USERINTERFACE
* 
* @param[in]  layout : 
* @param[in]  element : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool UI_MANAGER::ChangeTextElementValue(UI_LAYOUT* layout, UI_ELEMENT* element)
{
  if(!element) 
    {
      return false;
    }

  if(!layout)
    {
      return false;
    }

  if(!layout->GetSkin())
    {
      return false;
    }

  bool change = false;

  switch(element->GetType())
    {
      case  UI_ELEMENT_TYPE_TEXT      : { UI_ELEMENT_TEXT*  element_text = (UI_ELEMENT_TEXT*)element;
                                          XSTRING           resolve;

                                          if(element_text->GetMaskText()->IsEmpty())    return false;
                                                                                                                         
                                          change = ChangeTextElementValue(element_text, element_text->GetMaskText(), resolve);   
                                                                                                            
                                          if(change)
                                            {                                                                                                                                                                                                                                                                                                                                                                                                                    
                                              switch(layout->GetSkin()->GetDrawMode())
                                                {
                                                  case UI_SKIN_DRAWMODE_UNKNOWN   : break;

                                                  case UI_SKIN_DRAWMODE_CANVAS    : { double width  = 0.0f;
                                                                                      double height = 0.0f;
                                                                                      
                                                                                      UI_SKINCANVAS* ui_skincanvas = (UI_SKINCANVAS*)layout->GetSkin(); 

                                                                                      UI_ELEMENT* father =(UI_ELEMENT_TEXT*)element->GetFather(); 
                                                                                      if(father)
                                                                                        {
                                                                                          width  = father->GetBoundaryLine()->width;
                                                                                          height = father->GetBoundaryLine()->height;

                                                                                          Elements_SetToRedraw(father);    
                                                                                        }
                                                                                        else
                                                                                        {
                                                                                          width  =  ui_skincanvas->GetCanvas()->GetWidth();
                                                                                          height =  ui_skincanvas->GetCanvas()->GetHeight();
                                                                                        }                                 

                                                                                      element->GetBoundaryLine()->height  = 0;
                                                                                      element->GetBoundaryLine()->width   = 0;
                                                                                         
                                                                                      if(element_text->GetText()->Compare(resolve.Get(), true))  
                                                                                        { 
                                                                                          element_text->GetText()->Set(resolve);   
                                                                                              
                                                                                          ui_skincanvas->CalculeBoundaryLine_AllElements(element, false);
                                                                                          ui_skincanvas->CalculePosition(element, width, height);                                                                                              

                                                                                          Elements_SetToRedraw(element);    
                                                                                        }
                                                                                    }
                                                                                    break;

                                                  case UI_SKIN_DRAWMODE_CONTEXT   : break;
                                                }                                                                                                             
                                                                                             
                                            }
                                        }
                                        break;

      case UI_ELEMENT_TYPE_TEXTBOX    : { UI_ELEMENT_TEXTBOX* element_textbox = (UI_ELEMENT_TEXTBOX*)element;
                                          XSTRING             resolve;

                                          if(element_textbox->GetMaskText()->IsEmpty()) return false;

                                          change = ChangeTextElementValue(element_textbox, element_textbox->GetMaskText(), resolve);                                      
                                          if(change) 
                                            {                                             
                                              if(element_textbox->GetText()->Compare(resolve.Get(), true)) 
                                                {
                                                  element_textbox->GetText()->Set(resolve);
                                                  Elements_SetToRedraw(element);    
                                                }
                                            }
                                           else
                                            {
                                              if(element_textbox->GetText()->IsEmpty())
                                                {
                                                  if(!resolve.IsEmpty())  
                                                    {
                                                      element_textbox->GetText()->Set(resolve);
                                                    }
                                                }
                                            }


                                        }  
                                        break;
    }


  for(XDWORD c=0; c<element->GetComposeElements()->GetSize(); c++)
    {
      UI_ELEMENT* subelement = element->GetComposeElements()->Get(c);
      if(subelement) 
        {
          ChangeTextElementValue(layout, subelement);
        }
    }
  
  return true;
 }


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_MANAGER::ChangeTextElementValue(UI_LAYOUT* layout)
* @brief      ChangeTextElementValue
* @ingroup    USERINTERFACE
*
* @param[in]  layout : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
 bool UI_MANAGER::ChangeTextElementValue(UI_LAYOUT* layout)
{
  if(!layout) 
    {
      return false;
    }
 
  for(XDWORD c=0; c<layout->Elements_Get()->GetSize(); c++)
    {
      UI_ELEMENT* element = layout->Elements_Get()->Get(c);
      if(element) 
        {
          ChangeTextElementValue(layout, element);       
        }
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_MANAGER::SubscribeInputEvents(bool active)
* @brief      SubscribeInputEvents
* @ingroup    USERINTERFACE
* 
* @param[in]  active : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool UI_MANAGER::SubscribeInputEvents(bool active)
{
  UI_XEVENT_TYPE eventtype[] = {  UI_XEVENT_TYPE_INPUT_CURSOR_MOVE            ,
                                  UI_XEVENT_TYPE_INPUT_CURSOR_MOTION          ,
                                  UI_XEVENT_TYPE_INPUT_SELECCTION             ,                                           
                               };

  for(int c=0; c<(sizeof(eventtype) / sizeof(UI_XEVENT_TYPE)); c++)
    {
      if(active)        
            SubscribeEvent(eventtype[c]   , this);              
      else  UnSubscribeEvent(eventtype[c] , this);        
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_MANAGER::SubscribeOutputEvents(bool active, XOBSERVER* observer, XSUBJECT* subject)
* @brief      SubscribeOutputEvents
* @ingroup    USERINTERFACE
*
* @param[in]  active : 
* @param[in]  observer : 
* @param[in]  subject : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool UI_MANAGER::SubscribeOutputEvents(bool active, XOBSERVER* observer, XSUBJECT* subject)
{
  UI_XEVENT_TYPE eventtype[] = {  UI_XEVENT_TYPE_OUTPUT_SELECTED          ,                              
                                  UI_XEVENT_TYPE_OUTPUT_TEXTTOCHANGE      ,
                                  UI_XEVENT_TYPE_OUTPUT_CHANGECONTENTS                                     
                               };

  for(int c=0; c<(sizeof(eventtype) / sizeof(UI_XEVENT_TYPE)); c++)
    {
      if(active)        
            observer->SubscribeEvent(eventtype[c]   , subject);              
      else  observer->UnSubscribeEvent(eventtype[c] , subject);        
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_MANAGER::CreaterVirtualKeyboard(UI_LAYOUT* layout, GRPSCREEN* screen)
* @brief      CreaterVirtualKeyboard
* @ingroup    USERINTERFACE
* 
* @param[in]  layout : 
* @param[in]  screen : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool UI_MANAGER::CreaterVirtualKeyboard(UI_LAYOUT* layout, GRPSCREEN* screen)
{
  if(virtualkeyboard) 
    {
      return false;   
    }

  if(!layout)         
    {
      return false;
    }
  
  if(!screen)         
    {
      return false;
    }

  virtualkeyboard = new UI_VIRTUALKEYBOARD();
  if(!virtualkeyboard) 
    {
      return false;
    }

  virtualkeyboard->Ini(layout, screen);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_MANAGER::DeleteVirtualKeyboard()
* @brief      DeleteVirtualKeyboard
* @ingroup    USERINTERFACE
*
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool UI_MANAGER::DeleteVirtualKeyboard()
{
  if(!virtualkeyboard)
    {
      return false;
    }

  bool status = false;

  status = virtualkeyboard->End();

  delete virtualkeyboard;
  virtualkeyboard = NULL;

  return status;    
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         UI_MANAGER::UI_MANAGER()
* @brief      Constructor
* @ingroup    USERINTERFACE
*
* ---------------------------------------------------------------------------------------------------------------------*/
UI_MANAGER::UI_MANAGER()    
{ 
  Clean();   

  GEN_XFACTORY_CREATE(xmutex_modal, Create_Mutex())
  GEN_XFACTORY_CREATE(xmutex_UIevent, Create_Mutex())

  RegisterEvents(true);                        
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         UI_MANAGER::~UI_MANAGER()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    USERINTERFACE
*
* ---------------------------------------------------------------------------------------------------------------------*/
UI_MANAGER::~UI_MANAGER()    
{ 
  RegisterEvents(false); 

  DeleteVirtualKeyboard();

  Layouts_DeleteAll(); 
  
  if(unzipfile)
    {
      delete unzipfile;
      unzipfile = NULL;
    }  

  if(xmutex_modal)
    {
      GEN_XFACTORY.Delete_Mutex(xmutex_modal);
      xmutex_modal = NULL;
    }

  if(xmutex_UIevent)
    {
      GEN_XFACTORY.Delete_Mutex(xmutex_UIevent);
      xmutex_UIevent = NULL;
    }

  Clean();                            
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         UI_SKIN* UI_MANAGER::Skin_Create(XCHAR* name, UI_SKIN_DRAWMODE drawmode, GRPSCREEN* screen, int viewportindex)
* @brief      Skin_Create
* @ingroup    USERINTERFACE
* 
* @param[in]  name : 
* @param[in]  drawmode : 
* @param[in]  screen : 
* @param[in]  viewportindex : 
* 
* @return     UI_SKIN* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
UI_SKIN* UI_MANAGER::Skin_Create(XSTRING& skintypename, UI_SKIN_DRAWMODE drawmode, GRPSCREEN* screen, int viewportindex)
{  
  if(!screen) 
    {
      return NULL;
    }

  UI_SKIN*  ui_skin;

  switch(drawmode)
    {
      case UI_SKIN_DRAWMODE_UNKNOWN     : return NULL;
                                         
      case UI_SKIN_DRAWMODE_CANVAS      : { UI_SKINCANVAS* skincanvas = NULL;

                                            if(!skintypename.Compare(UI_SKIN_NAME_DEFAULT, true) || !skintypename.Compare(UI_SKIN_NAME_UNKNOWN, true))
                                              {
                                                ui_skin = (UI_SKIN*)new UI_SKINCANVAS(screen, viewportindex); 
                                              }
                                             else
                                              {
                                                if(!skintypename.Compare(UI_SKIN_NAME_FLAT, true))
                                                  {
                                                    ui_skin = (UI_SKIN*)new UI_SKINCANVAS_FLAT(screen, viewportindex); 
                                                  }
                                              }
                                          }
                                          break;

      case UI_SKIN_DRAWMODE_CONTEXT     : break;

    }
  
  return ui_skin;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_MANAGER::GetLayoutElementValue(XFILEXMLELEMENT* node, XCHAR* leyend, double& value)
* @brief      GetLayoutElementValue
* @ingroup    USERINTERFACE
* 
* @param[in]  node : 
* @param[in]  leyend : 
* @param[in]  value : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool UI_MANAGER::GetLayoutElementValue(XFILEXMLELEMENT* node, XCHAR* leyend, double& value)
{
  XCHAR*    xcharstr;
  XSTRING   valuestr;

  valuestr.Empty();

  xcharstr = node->GetValueAttribute(leyend);
  if(!xcharstr) return false;

  valuestr = xcharstr;

  value = valuestr.ConvertToDouble();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_MANAGER::GetLayoutElementValue(XFILEXMLELEMENT* node, XCHAR* leyend, XSTRING& value)
* @brief      GetLayoutElementValue
* @ingroup    USERINTERFACE
* 
* @param[in]  node : 
* @param[in]  leyend : 
* @param[in]  value : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool UI_MANAGER::GetLayoutElementValue(XFILEXMLELEMENT* node, XCHAR* leyend, XSTRING& value)
{
  XCHAR* xcharstr;

  value.Empty();

  xcharstr = node->GetValueAttribute(leyend);
  if(!xcharstr) return false;

  value = xcharstr;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_MANAGER::GetLayoutElement_CalculateBoundaryLine(UI_ELEMENT* element, bool adjustsizemargin)
* @brief      GetLayoutElement_CalculateBoundaryLine
* @ingroup    USERINTERFACE
* 
* @param[in]  element : 
* @param[in]  adjustsizemargin : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool UI_MANAGER::GetLayoutElement_CalculateBoundaryLine(UI_LAYOUT* layout, UI_ELEMENT* element, bool adjustsizemargin)
{
  bool status = false;

 if(!element) 
    {
      return false;
    }

  if(!layout)
    {
      return false;
    }

  if(!layout->GetSkin())
    {
      return false;
    }

  switch(layout->GetSkin()->GetDrawMode())
    {
      case UI_SKIN_DRAWMODE_UNKNOWN   : break;

      case UI_SKIN_DRAWMODE_CANVAS    : { UI_SKINCANVAS* skincanvas = (UI_SKINCANVAS*)layout->GetSkin(); 
                                          if(skincanvas) 
                                            {
                                              status = skincanvas->CalculateBoundaryLine(element, adjustsizemargin);                                                                                    
                                            }
                                        }
                                        break;

      case UI_SKIN_DRAWMODE_CONTEXT   : break;
    }

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_MANAGER::GetParentSizeFont(XFILEXMLELEMENT* node, double& sizefont)
* @brief      GetParentSizeFont
* @ingroup    USERINTERFACE
* 
* @param[in]  node : 
* @param[in]  sizefont : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool UI_MANAGER::GetParentSizeFont(XFILEXMLELEMENT* node, double& sizefont)
{
  if(!node) return false;

  sizefont = 0;
    
  if(!GetLayoutElementValue(node, __L("sizefont"), sizefont))
    {
      return GetParentSizeFont(node->GetFather(), sizefont);
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_MANAGER::GetLayoutElement_Base(XFILEXMLELEMENT* node, UI_LAYOUT* layout, UI_ELEMENT* element, bool adjusttoparent)
* @brief      GetLayoutElement_Base
* @ingroup    USERINTERFACE
* 
* @param[in]  node : 
* @param[in]  layout : 
* @param[in]  element : 
* @param[in]  adjusttoparent : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool UI_MANAGER::GetLayoutElement_Base(XFILEXMLELEMENT* node, UI_LAYOUT* layout, UI_ELEMENT* element, bool adjusttoparent)
{
  double xpos   = 0.0f;
  double ypos   = 0.0f;    
  double width  = 0.0f;
  double height = 0.0f; 
  
  if(!element) return false;
    
  element->SetIsDetached(false);

  XFILEXMLELEMENT* XML_father = node->GetFather();
  if(XML_father)
    {
      if(!XML_father->GetName().Compare(__L("layout"), true)) element->SetIsDetached(true);        
    }

  XSTRING name;
  GetLayoutElementValue(node, __L("name"), name); 
  element->GetName()->Set(name);

  XSTRING position;
  if(GetLayoutElementValue(node, __L("xpos"), position))
    {
      if(!position.Compare(__L("left"), true))  xpos = UI_ELEMENT_TYPE_ALIGN_LEFT;
        else if(!position.Compare(__L("right"), true))  xpos = UI_ELEMENT_TYPE_ALIGN_RIGHT;
          else if(!position.Compare(__L("center"), true)) xpos = UI_ELEMENT_TYPE_ALIGN_CENTER;
            else GetLayoutElementValue(node, __L("xpos"), xpos); 
    }
    
  if(GetLayoutElementValue(node, __L("ypos"), position))
    {
      if(!position.Compare(__L("up"), true))  ypos = UI_ELEMENT_TYPE_ALIGN_UP;
        else if(!position.Compare(__L("down"), true))  ypos = UI_ELEMENT_TYPE_ALIGN_DOWN;
          else if(!position.Compare(__L("center"), true)) ypos = UI_ELEMENT_TYPE_ALIGN_CENTER;
            else GetLayoutElementValue(node, __L("ypos"), ypos); 
    } 


  XSTRING size;
  if(GetLayoutElementValue(node, __L("width"), size))
    {
      if(!size.Compare(__L("max"), true))  width = UI_ELEMENT_TYPE_ALIGN_MAX;
        else if(!size.Compare(__L("auto"), true))  width = UI_ELEMENT_TYPE_ALIGN_AUTO;          
            else GetLayoutElementValue(node, __L("width"), width); 
    }
   else 
    {      
      if(element->GetFather() && adjusttoparent)
        {
          width = element->GetFather()->GetBoundaryLine()->width;
        }
    }

  if(GetLayoutElementValue(node, __L("height") , size))
    {
      if(!size.Compare(__L("max"), true))  height = UI_ELEMENT_TYPE_ALIGN_MAX;
        else if(!size.Compare(__L("auto"), true))  height = UI_ELEMENT_TYPE_ALIGN_AUTO;          
            else GetLayoutElementValue(node, __L("height"), height); 
    }
   else
    {
      if(element->GetFather() && adjusttoparent)
        {
          height = element->GetFather()->GetBoundaryLine()->height;
        }
    }
   
  element->GetBoundaryLine()->x       = xpos;  
  element->GetBoundaryLine()->y       = ypos;  
  element->GetBoundaryLine()->width   = width;
  element->GetBoundaryLine()->height  = height;

  XSTRING directionstr;
  if(GetLayoutElementValue(node, __L("direction"), directionstr)) 
    {
      if(!directionstr.Compare(__L("horizotal"), true))  element->SetDirection(UI_ELEMENT_TYPE_DIRECTION_HORIZONTAL);
        else if(!directionstr.Compare(__L("vertical"), true))  element->SetDirection(UI_ELEMENT_TYPE_DIRECTION_VERTICAL);                  
    }

  XSTRING color;
  GetLayoutElementValue(node, __L("color"), color);    
  if(!color.IsEmpty()) element->GetColor()->SetFromString(color);

  XSTRING bckgrdcolor;
  GetLayoutElementValue(node, __L("bckgrdcolor"), bckgrdcolor);    
  if(!bckgrdcolor.IsEmpty()) element->GetBackgroundColor()->SetFromString(bckgrdcolor);  
    
  XSTRING visible;
  if(GetLayoutElementValue(node, __L("visible"), visible))
    {
      element->SetVisible(visible.ConvertToBoolean());
    }
    
  XSTRING hasscroll;  
  if(GetLayoutElementValue(node, __L("scroll"), hasscroll))
    {
      element->SetHasScroll(hasscroll.ConvertToBoolean());
    }

  double roundrect = 0.0f;
  GetLayoutElementValue(node, __L("roundrect"), roundrect); 
  element->SetRoundRect((XDWORD)roundrect);
  
  double blinktime;
  if(GetLayoutElementValue(node, __L("blink"), blinktime)) element->SetBlink((XDWORD)blinktime);        

  XSTRING extra;
  GetLayoutElementValue(node, __L("extra"), extra);
  element->GetExtra()->Set(extra);
      
  XSTRING marginstr;
  if(GetLayoutElementValue(node, __L("margin"), marginstr))
    {
      int margin[UI_ELEMENT_MARGIN_MAX] = { 0, 0, 0, 0 };

      marginstr.UnFormat(__L("%d,%d,%d,%d") , &margin[0]
                                            , &margin[1]
                                            , &margin[2]
                                            , &margin[3]); 

      element->SetMargin(UI_ELEMENT_TYPE_ALIGN_LEFT   , (double)margin[0]); 
      element->SetMargin(UI_ELEMENT_TYPE_ALIGN_RIGHT  , (double)margin[1]);
      element->SetMargin(UI_ELEMENT_TYPE_ALIGN_UP     , (double)margin[2]); 
      element->SetMargin(UI_ELEMENT_TYPE_ALIGN_DOWN   , (double)margin[3]);            
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         UI_ELEMENT* UI_MANAGER::GetLayoutElement_Text(XFILEXMLELEMENT* node, UI_LAYOUT* layout, UI_ELEMENT* father, UI_ELEMENT* element_legacy)
* @brief      GetLayoutElement_Text
* @ingroup    USERINTERFACE
* 
* @param[in]  node : 
* @param[in]  layout : 
* @param[in]  father : 
* @param[in]  element_legacy : 
* 
* @return     UI_ELEMENT* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
UI_ELEMENT* UI_MANAGER::GetLayoutElement_Text(XFILEXMLELEMENT* node, UI_LAYOUT* layout, UI_ELEMENT* father, UI_ELEMENT* element_legacy)
{
  XSTRING           text;
  double            sizefont      = 0;
  bool              havemask      = false;
  UI_ELEMENT_TEXT*  element_text  = NULL;
  
  if(element_legacy)
    {
      element_text = (UI_ELEMENT_TEXT*)element_legacy;
    }
   else
    {
      element_text = new UI_ELEMENT_TEXT();
      if(!element_text) return NULL;
    }

  element_text->SetFather(father);


  if(!GetLayoutElement_Base(node, layout, element_text))
    {
      delete element_text;
      return NULL;
    }

  SetLevelAuto(element_text, father);

  if(!GetLayoutElementValue(node, __L("sizefont"), sizefont))
    {
      if(!GetParentSizeFont(node->GetFather(), sizefont))
        {
          delete element_text;
          return NULL;
        }
    }

  element_text->SetSizeFont((XDWORD)sizefont);

  text = node->GetValue().Get();

  XSTRING* textcache = GEN_UI_TEXTS.Get(text);
  if(textcache)  text = textcache->Get();

  if(text.Find(UI_MANAGER_LAYOUT_TEXT_INI, true) != XSTRING_NOTFOUND) 
    {
      if(text.Find(UI_MANAGER_LAYOUT_TEXT_END, true) != XSTRING_NOTFOUND)  havemask = true;
    }
  
  if(havemask)
    {
      element_text->GetMaskText()->Set(text.Get());
      element_text->GetText()->Empty();
      
    } 
   else
    { 
      element_text->GetMaskText()->Empty();
      element_text->GetText()->Set(text.Get());
    }

  double maxsizetext = 0.0f;  
  if(GetLayoutElementValue(node, __L("maxsizetext"), maxsizetext))
    {               
      element_text->SetMaxSizeText((XDWORD)maxsizetext);    
    }

  if(!element_text->GetMaskText()->IsEmpty()) 
    {
      XSTRING  maskvalue;
      XSTRING  maskresolved;
      XSTRING  _text;
      int      start      = 0;
      int      new_start  = XSTRING_NOTFOUND;
      bool     change     = false;
  
      do{ int new_start = GEN_USERINTERFACE.GetOutputTextChangeID(element_text->GetMaskText(), start, maskvalue);
          if(new_start != XSTRING_NOTFOUND)
            {                                    
              if(maskvalue.Find(UI_MANAGER_LAYOUT_TEXT_TRANSLATE, true) != XSTRING_NOTFOUND)
                {
                  XCHAR*    translate_str  = NULL;
                  XSTRING   maskID;
                  int       ID             = 0;

                  maskID  = UI_MANAGER_LAYOUT_TEXT_TRANSLATE;
                  maskID += __L("%d");

                  maskvalue.UnFormat(maskID.Get(), &ID);

                  translate_str = GEN_XTRANSLATION.Translate_GetSentence(ID);
                  if(translate_str)  maskresolved.Set(translate_str);
                } 
  
              if(!maskresolved.IsEmpty()) 
                {
                  element_text->GetMaskText()->DeleteCharacters(new_start, maskvalue.GetSize() +3 ); 
                  element_text->GetMaskText()->Insert(maskresolved, new_start);  
                  change = true;                
                }
            }

        } while(new_start != XSTRING_NOTFOUND);    


      if(change)
        {
          havemask = false;

          text = element_text->GetMaskText()->Get();
          if(text.Find(UI_MANAGER_LAYOUT_TEXT_INI, true) != XSTRING_NOTFOUND) 
            {
              if(text.Find(UI_MANAGER_LAYOUT_TEXT_END, true) != XSTRING_NOTFOUND)  havemask = true;
            }
  
          if(havemask)
            {
              element_text->GetMaskText()->Set(text.Get());
              element_text->GetText()->Empty();
      
            } 
           else
            { 
              element_text->GetMaskText()->Empty();
              element_text->GetText()->Set(text.Get());
            } 
         }
  
    }
  
  GetLayoutElement_CalculateBoundaryLine(layout, element_text);
   
  return element_text;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         UI_ELEMENT* UI_MANAGER::GetLayoutElement_TextBox(XFILEXMLELEMENT* node, UI_LAYOUT* layout, UI_ELEMENT* father, UI_ELEMENT* element_legacy)
* @brief      GetLayoutElement_TextBox
* @ingroup    USERINTERFACE
* 
* @param[in]  node : 
* @param[in]  layout : 
* @param[in]  father : 
* @param[in]  element_legacy : 
* 
* @return     UI_ELEMENT* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
UI_ELEMENT* UI_MANAGER::GetLayoutElement_TextBox(XFILEXMLELEMENT* node, UI_LAYOUT* layout, UI_ELEMENT* father, UI_ELEMENT* element_legacy)
{  
  UI_ELEMENT_TEXTBOX* element_textbox   = NULL;
  XSTRING             text;

  if(element_legacy)
    {
      element_textbox = (UI_ELEMENT_TEXTBOX*)element_legacy;
    }
   else
    {
      element_textbox = new UI_ELEMENT_TEXTBOX();
      if(!element_textbox) return NULL;
    }

  element_textbox->SetFather(father);

  if(!GetLayoutElement_Base(node, layout, element_textbox, true))
    {
      delete element_textbox;
      return NULL;
    }

  SetLevelAuto(element_textbox, father);

  if(!element_textbox->GetBoundaryLine()->width)  return NULL;
  if(!element_textbox->GetBoundaryLine()->height) return NULL;

  double sizefont = 0;  
  if(!GetLayoutElementValue(node, __L("sizefont"), sizefont))
    {
      if(!GetParentSizeFont(node->GetFather(), sizefont))
        {
          delete element_textbox;
          return NULL;
        }
    }

  element_textbox->SetSizeFont((XDWORD)sizefont);

  double linespacing = UI_ELEMENT_TEXTBOX_DEFAULTLINESPACING;
  GetLayoutElementValue(node, __L("linespacing"), linespacing);     
  element_textbox->SetLineSpacing((XDWORD)linespacing);

  XSTRING                textalignmentstr;
  UI_ELEMENT_TYPE_ALIGN  textalignment;
  if(GetLayoutElementValue(node, __L("textalignment"), textalignmentstr))
    {
      if(!textalignmentstr.Compare(__L("left"), true))  textalignment = UI_ELEMENT_TYPE_ALIGN_LEFT;
        else if(!textalignmentstr.Compare(__L("right"), true))  textalignment = UI_ELEMENT_TYPE_ALIGN_RIGHT;
          else if(!textalignmentstr.Compare(__L("center"), true)) textalignment = UI_ELEMENT_TYPE_ALIGN_CENTER;
    }
  element_textbox->SetTextAlignment(textalignment);


  XSTRING wordclippingstr;  
  element_textbox->SetIsWordClipping(false);
  if(GetLayoutElementValue(node, __L("wordclipping"), wordclippingstr))
    {
      element_textbox->SetIsWordClipping(wordclippingstr.ConvertToBoolean());         
    }

  text.Empty();

  for(int c=0; c<node->GetNElements(); c++)
    {
      XFILEXMLELEMENT* subnode = node->GetElement(c);
      if(subnode)
        {
          if(!subnode->GetName().Compare(__L("text"), true))
            {                                                                  
              text.Add(subnode->GetValue().Get());
              text.Add(__L("\n"));
            }    
        }
    }
  
  if(!text.IsEmpty()) 
    {
      XSTRING  value;
      XSTRING  resolved;      
      int      start      = 0;
      int      new_start  = XSTRING_NOTFOUND;
      bool     change     = false;
  
      do{ int new_start = GEN_USERINTERFACE.GetOutputTextChangeID(&text, start, value);
          if(new_start != XSTRING_NOTFOUND)
            {                                    
              if(value.Find(UI_MANAGER_LAYOUT_TEXT_TRANSLATE, true) != XSTRING_NOTFOUND)
                {
                  XCHAR*    translate_str  = NULL;
                  XSTRING   IDstr;
                  int       ID             = 0;

                  IDstr  = UI_MANAGER_LAYOUT_TEXT_TRANSLATE;
                  IDstr += __L("%d");

                  value.UnFormat(IDstr.Get(), &ID);

                  translate_str = GEN_XTRANSLATION.Translate_GetSentence(ID);
                  if(translate_str) resolved.Set(translate_str);
                } 
  
              if(!resolved.IsEmpty()) 
                {
                  text.DeleteCharacters(new_start, value.GetSize() +3 ); 
                  text.Insert(resolved, new_start);  
                  change = true;                
                }
            }

        } while(new_start != XSTRING_NOTFOUND);      
    }

  element_textbox->GetMaskText()->Set(text);

  GetLayoutElement_CalculateBoundaryLine(layout, element_textbox, true);

  return element_textbox;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         UI_ELEMENT* UI_MANAGER::GetLayoutElement_Image(XFILEXMLELEMENT* node, UI_ELEMENT* father, UI_ELEMENT* element_legacy)
* @brief      GetLayoutElement_Image
* @ingroup    USERINTERFACE
*
* @param[in]  node : 
* @param[in]  father : 
* @param[in]  element_legacy : 
* 
* @return     UI_ELEMENT* : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
UI_ELEMENT* UI_MANAGER::GetLayoutElement_Image(XFILEXMLELEMENT* node, UI_LAYOUT* layout, UI_ELEMENT* father, UI_ELEMENT* element_legacy)
{
  XPATH             xpathimg;
  XSTRING           namefileimg;
  UI_ELEMENT_IMAGE* element_image = NULL;

  if(element_legacy)
    {
      element_image = (UI_ELEMENT_IMAGE*)element_legacy;
    }
   else
    {
      element_image = new UI_ELEMENT_IMAGE();
      if(!element_image) return NULL;
    }

  element_image->SetFather(father);
  
  if(!GetLayoutElement_Base(node, layout, element_image))
    {
      delete element_image;
      return NULL;
    }

  SetLevelAuto(element_image, father);

  double alpha = 0;
  if(GetLayoutElementValue(node, __L("alpha"), alpha))
    {
      element_image->SetAlpha((XBYTE)alpha);
    }

  namefileimg = node->GetValue().Get();

 
  if(!namefileimg.IsEmpty()) 
    {
      GRPPROPERTYMODE   grppropertymode = GRPPROPERTYMODE_XX_UNKNOWN;
      UI_SKIN_DRAWMODE  drawmode        = UI_SKIN_DRAWMODE_UNKNOWN;

      if(layout->GetSkin())
        {
          drawmode = layout->GetSkin()->GetDrawMode();

          switch(drawmode)
            {
              case UI_SKIN_DRAWMODE_UNKNOWN   : break;

              case UI_SKIN_DRAWMODE_CANVAS    : { UI_SKINCANVAS* skincanvas = (UI_SKINCANVAS*)layout->GetSkin(); 
                                                  if(skincanvas)
                                                    {
                                                      grppropertymode = skincanvas->GetCanvas()->GetMode();
                                                    }
                                                }
                                                break;
   
              case UI_SKIN_DRAWMODE_CONTEXT   : break;
            }  
        }

      UI_ANIMATION* animation = GetOrAddAnimationCache(drawmode, grppropertymode, __L(""), namefileimg.Get());
      if(animation) 
        { 
          GRPBITMAP* bitmap = NULL; 
          bitmap = animation->GetBitmap(); 
          if(bitmap) element_image->SetImage(bitmap);             
        }
    }
     
  GetLayoutElement_CalculateBoundaryLine(layout, element_image);
  
  return element_image;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         UI_ELEMENT* UI_MANAGER::GetLayoutElement_Animation(XFILEXMLELEMENT* node, UI_LAYOUT* layout, UI_ELEMENT* father, UI_ELEMENT* element_legacy)
* @brief      GetLayoutElement_Animation
* @ingroup    USERINTERFACE
* 
* @param[in]  node : 
* @param[in]  layout : 
* @param[in]  father : 
* @param[in]  element_legacy : 
* 
* @return     UI_ELEMENT* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
UI_ELEMENT* UI_MANAGER::GetLayoutElement_Animation(XFILEXMLELEMENT* node, UI_LAYOUT* layout, UI_ELEMENT* father, UI_ELEMENT* element_legacy)
{
  XSTRING               text;
  XSTRING               namefileimg;
  XPATH                 xpathimg;
  int                   sizefont          = 0;
  UI_ELEMENT_ANIMATION* element_animation = NULL;

  if(element_legacy)
    {
      element_animation = (UI_ELEMENT_ANIMATION*)element_legacy;
    }
   else
    {
      element_animation = new UI_ELEMENT_ANIMATION();
      if(!element_animation) return NULL;
    }

  element_animation->SetFather(father);
  
  if(!GetLayoutElement_Base(node, layout, element_animation))
    {
      delete element_animation;
      return NULL;
    } 

  SetLevelAuto(element_animation, father);

  XSTRING statestring;  
  if(GetLayoutElementValue(node, __L("state"), statestring))
    {
      if(!statestring.Compare(__L("play"), true))                                                                     
        {
          element_animation->Play();
        }
        else
        {
          if(!statestring.Compare(__L("stop"), true))                                                                     
            {
              element_animation->Stop();
            }   
            else
            {       
              if(!statestring.Compare(__L("pause"), true))                                                                     
                {
                  element_animation->Pause();    
                }
            }
        }
    }

  double timedelay = 0;
  if(GetLayoutElementValue(node, __L("timedelay"), timedelay))
    {
      element_animation->SetMilliSecondsDelay((XDWORD)timedelay);
    }

  double alpha = 0;
  if(GetLayoutElementValue(node, __L("alpha"), alpha))
    {
      element_animation->SetAlpha((XBYTE)alpha);
    }

  for(int c=0; c<node->GetNElements(); c++)
    {
      XFILEXMLELEMENT* nodeelement =  node->GetElement(c);
      if(nodeelement)
        {  
          if(!nodeelement->GetName().Compare(__L("image")))
            {              
              namefileimg = nodeelement->GetValue(); 

              GRPPROPERTYMODE   grppropertymode = GRPPROPERTYMODE_XX_UNKNOWN;
              UI_SKIN_DRAWMODE  drawmode        = UI_SKIN_DRAWMODE_UNKNOWN;

              if(layout->GetSkin())
                {
                  drawmode = layout->GetSkin()->GetDrawMode();

                  switch(drawmode)
                    {
                      case UI_SKIN_DRAWMODE_UNKNOWN   : break;

                      case UI_SKIN_DRAWMODE_CANVAS    : { UI_SKINCANVAS* skincanvas = (UI_SKINCANVAS*)layout->GetSkin(); 
                                                          if(skincanvas)
                                                            {
                                                              grppropertymode = skincanvas->GetCanvas()->GetMode();
                                                            }
                                                        }
                                                        break;
   
                      case UI_SKIN_DRAWMODE_CONTEXT   : break;
                    }  
                }      

              UI_ANIMATION* animation = GetOrAddAnimationCache(drawmode, grppropertymode, __L(""), namefileimg.Get());
              if(animation)
                {
                  for(XDWORD d=0; d<animation->GetBitmaps()->GetSize(); d++)
                    {
                      UI_ELEMENT_IMAGE* element_img = new UI_ELEMENT_IMAGE();
                      if(element_img) 
                        {
                          GRPBITMAP* bitmap = NULL; 

                          element_img->SetFather(element_animation);       

                          GetLayoutElement_Base(nodeelement, layout, element_img); 

                          SetLevelAuto(element_img, element_animation);

                          bitmap = animation->GetBitmaps()->Get(d);
                          if(bitmap) 
                            { 
                              element_img->SetImage(bitmap);
                              
                              if(layout->GetSkin())
                                {
                                  switch(layout->GetSkin()->GetDrawMode())
                                    {
                                      case UI_SKIN_DRAWMODE_UNKNOWN   : break;

                                      case UI_SKIN_DRAWMODE_CANVAS    : { UI_SKINCANVAS* skincanvas = (UI_SKINCANVAS*)layout->GetSkin(); 
                                                                          if(skincanvas) skincanvas->CalculateBoundaryLine(element_img); 
                                                                        }
                                                                        break;
   
                                      case UI_SKIN_DRAWMODE_CONTEXT   : break;

                                    }
                                 }

                              element_img->SetAlpha(element_animation->GetAlpha());
                                                                  
                              element_animation->GetComposeElements()->Add(element_img);                                                                                                
                            } 
                        }
                    }      
                }
            }
        }
    }

  GetLayoutElement_CalculateBoundaryLine(layout, element_animation);

  return element_animation;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         UI_ELEMENT* UI_MANAGER::GetLayoutElement_Option(XFILEXMLELEMENT* node, UI_LAYOUT* layout, UI_ELEMENT* father, UI_ELEMENT* element_legacy)
* @brief      GetLayoutElement_Option
* @ingroup    USERINTERFACE
* 
* @param[in]  node : 
* @param[in]  layout : 
* @param[in]  father : 
* @param[in]  element_legacy : 
* 
* @return     UI_ELEMENT* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
UI_ELEMENT* UI_MANAGER::GetLayoutElement_Option(XFILEXMLELEMENT* node, UI_LAYOUT* layout, UI_ELEMENT* father, UI_ELEMENT* element_legacy)
{
  XSTRING             text;
  XSTRING             namefileimg;
  XPATH               xpathimg;
  double              sizefont  = 0;
  UI_ELEMENT_OPTION*  element_option = NULL;

  if(element_legacy)
    {
      element_option =  (UI_ELEMENT_OPTION*)element_legacy;
    }
   else
    {
      element_option = new UI_ELEMENT_OPTION();
      if(!element_option) return NULL;
    }

  element_option->SetFather(father);

  if(!GetLayoutElement_Base(node, layout, element_option))
    {
      delete element_option;
      return NULL;
    } 

  SetLevelAuto(element_option, father);

  element_option->SetActive(true);

  GetLayoutElementValue(node, __L("sizefont"), sizefont);

 
  XSTRING selectablestr;
  GetLayoutElementValue(node, __L("selectablestatus"), selectablestr);
  element_option->SetSelectableStateFromString(selectablestr);
    
  XSTRING allocationtextstr;
  if(GetLayoutElementValue(node, __L("allocationtext"), allocationtextstr))
    {
      if(!allocationtextstr.Compare(__L("none")     , true)) element_option->SetAllocationTextType(UI_ELEMENT_OPTION_ALLOCATION_TEXT_TYPE_NONE);  
      if(!allocationtextstr.Compare(__L("up")       , true)) element_option->SetAllocationTextType(UI_ELEMENT_OPTION_ALLOCATION_TEXT_TYPE_UP);
      if(!allocationtextstr.Compare(__L("down")     , true)) element_option->SetAllocationTextType(UI_ELEMENT_OPTION_ALLOCATION_TEXT_TYPE_DOWN);  
      if(!allocationtextstr.Compare(__L("right")    , true)) element_option->SetAllocationTextType(UI_ELEMENT_OPTION_ALLOCATION_TEXT_TYPE_RIGHT);  
	    if(!allocationtextstr.Compare(__L("left")     , true)) element_option->SetAllocationTextType(UI_ELEMENT_OPTION_ALLOCATION_TEXT_TYPE_LEFT); 
      if(!allocationtextstr.Compare(__L("center")   , true)) element_option->SetAllocationTextType(UI_ELEMENT_OPTION_ALLOCATION_TEXT_TYPE_CENTER); 
    }
  
  element_option->SetVisibleLimitType(UI_ELEMENT_OPTION_VISIBLE_LIMIT_NONE);

  XSTRING visiblelimittypestr;
  if(GetLayoutElementValue(node, __L("visiblelimit"), visiblelimittypestr))
    {
      if(visiblelimittypestr.Find(__L("active"), true) != XSTRING_NOTFOUND) 
        {
          element_option->SetVisibleLimitType(element_option->GetVisibleLimitType() | UI_ELEMENT_OPTION_VISIBLE_LIMIT_ACTIVE);
        }

      if(visiblelimittypestr.Find(__L("deactive"), true) != XSTRING_NOTFOUND) 
        {
          element_option->SetVisibleLimitType(element_option->GetVisibleLimitType() | UI_ELEMENT_OPTION_VISIBLE_LIMIT_DEACTIVE);
        }

      if(visiblelimittypestr.Find(__L("preselect"), true) != XSTRING_NOTFOUND) 
        {
          element_option->SetVisibleLimitType(element_option->GetVisibleLimitType() | UI_ELEMENT_OPTION_VISIBLE_LIMIT_PRESELECT);
        }

      if(visiblelimittypestr.Find(__L("select"), true) != XSTRING_NOTFOUND) 
        {
          element_option->SetVisibleLimitType(element_option->GetVisibleLimitType() | UI_ELEMENT_OPTION_VISIBLE_LIMIT_SELECT);
        }
    }
  

  for(int c=0; c<node->GetNElements(); c++)
    {
      XFILEXMLELEMENT* nodeelement =  node->GetElement(c);
      if(nodeelement)
        {
          XSTRING type;
          if(GetLayoutElementValue(nodeelement, __L("type"), type))
            {        
              UI_ELEMENT* element = CreatePartialLayout(nodeelement, layout, element_option);
              if(element) 
                {                   
                  switch(element->GetType())
                    {
                      case UI_ELEMENT_TYPE_ANIMATION  : element_option->Set_UIAnimation((UI_ELEMENT_ANIMATION*)element);                    
                                                        element_option->GetComposeElements()->Add(element);
                                                        break;

                      case UI_ELEMENT_TYPE_TEXT       : element_option->Set_UIText((UI_ELEMENT_TEXT*)element);                    
                                                        element_option->GetComposeElements()->Add(element);
                                                        break;                     
                    }                     
                }              
            }
        }  
    }
  
  GetLayoutElement_CalculateBoundaryLine(layout, element_option);

  return element_option;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         UI_ELEMENT* UI_MANAGER::GetLayoutElement_MultiOption(XFILEXMLELEMENT* node, UI_LAYOUT* layout, UI_ELEMENT* father, UI_ELEMENT* element_legacy)
* @brief      GetLayoutElement_MultiOption
* @ingroup    USERINTERFACE
* 
* @param[in]  node : 
* @param[in]  layout : 
* @param[in]  father : 
* @param[in]  element_legacy : 
* 
* @return     UI_ELEMENT* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
UI_ELEMENT* UI_MANAGER::GetLayoutElement_MultiOption(XFILEXMLELEMENT* node, UI_LAYOUT* layout, UI_ELEMENT* father, UI_ELEMENT* element_legacy)
{
  UI_ELEMENT_MULTIOPTION* element_multioption = NULL;
  double                  sizefont            = 0;

  if(element_legacy)
    {
      element_multioption =  (UI_ELEMENT_MULTIOPTION*)element_legacy;
    }
   else
    {
      element_multioption = new UI_ELEMENT_MULTIOPTION();
      if(!element_multioption) return NULL;     
    }

  element_multioption->SetFather(father);
 
  if(!GetLayoutElement_Base(node, layout, element_multioption))
    {
      delete element_multioption;
      return NULL;
    }

  SetLevelAuto(element_multioption, father);
    
  for(int c=0; c<node->GetNElements(); c++)
    {
      XFILEXMLELEMENT* nodeelement =  node->GetElement(c);
      if(nodeelement)
        {
          UI_ELEMENT* element = CreatePartialLayout(nodeelement, layout, element_multioption);
          if(element) 
            {  
              element->SetFather(element_multioption);                
              element_multioption->GetComposeElements()->Add(element);                        
            }       
        }  
    }
  
  GetLayoutElement_CalculateBoundaryLine(layout, element_multioption);

  for(XDWORD c=0; c<element_multioption->GetComposeElements()->GetSize(); c++)
    {
      UI_ELEMENT* element = element_multioption->GetComposeElements()->Get(c);
      if(element) GetLayoutElement_CalculateBoundaryLine(layout, element);
    }
 
  return element_multioption;  
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         UI_ELEMENT* UI_MANAGER::GetLayoutElement_Button(XFILEXMLELEMENT* node, UI_LAYOUT* layout, UI_ELEMENT* father, UI_ELEMENT* element_legacy)
* @brief      GetLayoutElement_Button
* @ingroup    USERINTERFACE
* 
* @param[in]  node : 
* @param[in]  layout : 
* @param[in]  father : 
* @param[in]  element_legacy : 
* 
* @return     UI_ELEMENT* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
UI_ELEMENT* UI_MANAGER::GetLayoutElement_Button(XFILEXMLELEMENT* node, UI_LAYOUT* layout, UI_ELEMENT* father, UI_ELEMENT* element_legacy)
{  
  UI_ELEMENT_BUTTON* element_button = new UI_ELEMENT_BUTTON();
  if(!element_button) return NULL;

  return GetLayoutElement_Option(node, layout, father, element_button);
}


UI_ELEMENT* UI_MANAGER::GetLayoutElement_CheckBox(XFILEXMLELEMENT* node, UI_LAYOUT* layout,  UI_ELEMENT* father, UI_ELEMENT* element_legacy)
{  
  UI_ELEMENT_CHECKBOX* element_checkbox = new UI_ELEMENT_CHECKBOX();
  if(!element_checkbox) return NULL;

  return GetLayoutElement_Option(node, layout,  father, element_checkbox);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         UI_ELEMENT* UI_MANAGER::GetLayoutElement_EditText(XFILEXMLELEMENT* node, UI_LAYOUT* layout, UI_ELEMENT* father, UI_ELEMENT* element_legacy)
* @brief      GetLayoutElement_EditText
* @ingroup    USERINTERFACE
* 
* @param[in]  node : 
* @param[in]  layout : 
* @param[in]  father : 
* @param[in]  element_legacy : 
* 
* @return     UI_ELEMENT* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
UI_ELEMENT* UI_MANAGER::GetLayoutElement_EditText(XFILEXMLELEMENT* node, UI_LAYOUT* layout, UI_ELEMENT* father, UI_ELEMENT* element_legacy)
{  
  UI_ELEMENT_EDITTEXT* element_edittext = new UI_ELEMENT_EDITTEXT();
  if(!element_edittext) return NULL;

  return GetLayoutElement_Text(node, layout, father, element_edittext);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         UI_ELEMENT* UI_MANAGER::GetLayoutElement_Form(XFILEXMLELEMENT* node, UI_LAYOUT* layout, UI_ELEMENT* father, UI_ELEMENT* element_legacy)
* @brief      GetLayoutElement_Form
* @ingroup    USERINTERFACE
* 
* @param[in]  node : 
* @param[in]  layout : 
* @param[in]  father : 
* @param[in]  element_legacy : 
* 
* @return     UI_ELEMENT* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
UI_ELEMENT* UI_MANAGER::GetLayoutElement_Form(XFILEXMLELEMENT* node, UI_LAYOUT* layout, UI_ELEMENT* father, UI_ELEMENT* element_legacy)
{
  UI_ELEMENT_FORM* element_form  = NULL;
  double           sizefont      = 0;

  if(element_legacy)
    {
      element_form =  (UI_ELEMENT_FORM*)element_legacy;
    }
   else
    {
      element_form = new UI_ELEMENT_FORM();
      if(!element_form) return NULL;      
    }

  element_form->SetFather(father);
 
  if(!GetLayoutElement_Base(node, layout, element_form))
    {
      delete element_form;
      return NULL;
    }

  SetLevelAuto(element_form, father);

  XSTRING linecolor;
  GetLayoutElementValue(node, __L("linecolor"), linecolor);    
  if(!linecolor.IsEmpty()) element_form->GetLineColor()->SetFromString(linecolor);  
    
  GetLayoutElement_CalculateBoundaryLine(layout, element_form);

  for(int c=0; c<node->GetNElements(); c++)
    {
      XFILEXMLELEMENT* nodeelement =  node->GetElement(c);
      if(nodeelement)
        {
          UI_ELEMENT* element = CreatePartialLayout(nodeelement, layout, element_form);
          if(element) 
            {  
              element->SetFather(element_form);                
              element_form->GetComposeElements()->Add(element);                        
            }       
        }  
    }

  GetLayoutElement_CalculateBoundaryLine(layout, element_form);

  for(XDWORD c=0; c<element_form->GetComposeElements()->GetSize(); c++)
    {
      UI_ELEMENT* subelement = element_form->GetComposeElements()->Get(c);
      if(subelement) GetLayoutElement_CalculateBoundaryLine(layout, subelement);
    }

  XSTRING visibleformstr;
  if(GetLayoutElementValue(node, __L("visiblerect"), visibleformstr))
    {
      if(!visibleformstr.IsEmpty())
        {                     
          int value[4] = { 0, 0, 0, 0 }; 

          visibleformstr.UnFormat(__L("%d,%d,%d,%d")  , &value[0], &value[1], &value[2], &value[3]); 

          element_form->GetVisibleRect()->x = element_form->GetXPosition() + value[0];
          element_form->GetVisibleRect()->y = element_form->GetYPosition() + value[1];      

          if(value[2]) 
            {       
              element_form->GetVisibleRect()->width = value[2]; 
            }
           else
            {
              element_form->GetVisibleRect()->width = element_form->GetBoundaryLine()->width; 
            }

          if(value[3])
            {
              element_form->GetVisibleRect()->height  = value[3];
            }
           else
            {
              element_form->GetVisibleRect()->height  = element_form->GetBoundaryLine()->height;
            }

          element_form->GetBoundaryLine()->SetAround((*element_form->GetVisibleRect()));
        }
    }
   else 
    {
      element_form->GetVisibleRect()->x       = element_form->GetXPosition();
      element_form->GetVisibleRect()->y       = element_form->GetYPosition();
      element_form->GetVisibleRect()->width   = element_form->GetBoundaryLine()->width;
      element_form->GetVisibleRect()->height  = element_form->GetBoundaryLine()->height;      
    }
   
  return element_form;  
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         UI_ELEMENT* UI_MANAGER::GetLayoutElement_Menu(XFILEXMLELEMENT* node, UI_LAYOUT* layout, UI_ELEMENT* father, UI_ELEMENT* element_legacy)
* @brief      GetLayoutElement_Menu
* @ingroup    USERINTERFACE
* 
* @param[in]  node : 
* @param[in]  layout : 
* @param[in]  father : 
* @param[in]  element_legacy : 
* 
* @return     UI_ELEMENT* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
UI_ELEMENT* UI_MANAGER::GetLayoutElement_Menu(XFILEXMLELEMENT* node, UI_LAYOUT* layout, UI_ELEMENT* father, UI_ELEMENT* element_legacy)
{   
  UI_ELEMENT_MENU* element_menu = new UI_ELEMENT_MENU();
  if(!element_menu) return NULL;

  return GetLayoutElement_Form(node, layout, father, element_menu);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         UI_ELEMENT* UI_MANAGER::GetLayoutElement_ListBox(XFILEXMLELEMENT* node, UI_LAYOUT* layout, UI_ELEMENT* father, UI_ELEMENT* element_legacy)
* @brief      GetLayoutElement_ListBox
* @ingroup    USERINTERFACE
* 
* @param[in]  node : 
* @param[in]  layout : 
* @param[in]  father : 
* @param[in]  element_legacy : 
* 
* @return     UI_ELEMENT* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
UI_ELEMENT* UI_MANAGER::GetLayoutElement_ListBox(XFILEXMLELEMENT* node, UI_LAYOUT* layout, UI_ELEMENT* father, UI_ELEMENT* element_legacy)
{
  UI_ELEMENT_LISTBOX* element_listbox = new UI_ELEMENT_LISTBOX();
  if(!element_listbox) return NULL;

  UI_ELEMENT* element_menu = NULL;
  XSTRING     menustr;
  GetLayoutElementValue(node, __L("menu"), menustr);    
  if(!menustr.IsEmpty()) 
    {
      element_menu = Element_Get(menustr, UI_ELEMENT_TYPE_MENU);  
      element_listbox->Set_UIMenu((UI_ELEMENT_MENU*)element_menu);              
    }

  double defaultoption = 0.0f;
  GetLayoutElementValue(node, __L("defaultoption"), defaultoption);    
  if(element_menu)
    {
      UI_ELEMENT_OPTION* element_option = (UI_ELEMENT_OPTION*)element_menu->GetComposeElements()->Get((XDWORD)defaultoption);
      if(element_option) 
        {
          XSTRING text;

          if(element_option->Get_UIText()) text = element_option->Get_UIText()->GetText()->Get();
          //element_listbox->GetMaskText()->Set(text);
          node->GetValue().Set(text);
        }
    }

  return GetLayoutElement_Text(node, layout, father, element_listbox);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         UI_ELEMENT* UI_MANAGER::GetLayoutElement_ProgressBar(XFILEXMLELEMENT* node, UI_LAYOUT* layout, UI_ELEMENT* father, UI_ELEMENT* element_legacy)
* @brief      GetLayoutElement_ProgressBar
* @ingroup    USERINTERFACE
* 
* @param[in]  node : 
* @param[in]  layout : 
* @param[in]  father : 
* @param[in]  element_legacy : 
* 
* @return     UI_ELEMENT* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
UI_ELEMENT* UI_MANAGER::GetLayoutElement_ProgressBar(XFILEXMLELEMENT* node, UI_LAYOUT* layout, UI_ELEMENT* father, UI_ELEMENT* element_legacy)
{
  XSTRING                   text;
  XSTRING                   namefileimg;
  XPATH                     xpathimg;
  double                    sizefont  = 0;
  UI_ELEMENT_PROGRESSBAR*   element_progressbar = NULL;

  if(element_legacy)
    {
      element_progressbar =  (UI_ELEMENT_PROGRESSBAR*)element_legacy;
    }
   else
    {
      element_progressbar = new UI_ELEMENT_PROGRESSBAR();
      if(!element_progressbar) return NULL;
    }

  element_progressbar->SetFather(father);

  if(!GetLayoutElement_Base(node, layout, element_progressbar))
    {
      delete element_progressbar;
      return NULL;
    } 

  SetLevelAuto(element_progressbar, father);

  element_progressbar->SetActive(true);

  GetLayoutElementValue(node, __L("sizefont"), sizefont);

    
  XSTRING allocationtextstr;
  if(GetLayoutElementValue(node, __L("allocationtext"), allocationtextstr))
    {
      if(!allocationtextstr.Compare(__L("none")     , true)) element_progressbar->SetAllocationTextType(UI_ELEMENT_OPTION_ALLOCATION_TEXT_TYPE_NONE);  
      if(!allocationtextstr.Compare(__L("up")       , true)) element_progressbar->SetAllocationTextType(UI_ELEMENT_OPTION_ALLOCATION_TEXT_TYPE_UP);
      if(!allocationtextstr.Compare(__L("down")     , true)) element_progressbar->SetAllocationTextType(UI_ELEMENT_OPTION_ALLOCATION_TEXT_TYPE_DOWN);  
      if(!allocationtextstr.Compare(__L("right")    , true)) element_progressbar->SetAllocationTextType(UI_ELEMENT_OPTION_ALLOCATION_TEXT_TYPE_RIGHT);  
	    if(!allocationtextstr.Compare(__L("left")     , true)) element_progressbar->SetAllocationTextType(UI_ELEMENT_OPTION_ALLOCATION_TEXT_TYPE_LEFT); 
      if(!allocationtextstr.Compare(__L("center")   , true)) element_progressbar->SetAllocationTextType(UI_ELEMENT_OPTION_ALLOCATION_TEXT_TYPE_CENTER); 
    }  


  XSTRING linecolor;
  GetLayoutElementValue(node, __L("linecolor"), linecolor);    
  if(!linecolor.IsEmpty()) element_progressbar->GetLineColor()->SetFromString(linecolor);  

  for(int c=0; c<node->GetNElements(); c++)
    {
      XFILEXMLELEMENT* nodeelement =  node->GetElement(c);
      if(nodeelement)
        {
          XSTRING type;
          if(GetLayoutElementValue(nodeelement, __L("type"), type))
            {        
              UI_ELEMENT* element = CreatePartialLayout(nodeelement, layout, element_progressbar);
              if(element) 
                {            
                  element->SetFather(element_progressbar);  
       
                  switch(element->GetType())
                    {
                      case UI_ELEMENT_TYPE_ANIMATION  : element_progressbar->Set_UIAnimation((UI_ELEMENT_ANIMATION*)element);                    
                                                        element_progressbar->GetComposeElements()->Add(element);
                                                        break;

                      case UI_ELEMENT_TYPE_TEXT       : element_progressbar->Set_UIText((UI_ELEMENT_TEXT*)element);                    
                                                        element_progressbar->GetComposeElements()->Add(element);
                                                        break;                     
                    }                     
                }              
            }
        }  
    }

  XSTRING continuouscyclestr;
  if(GetLayoutElementValue(node, __L("continuouscycle"), continuouscyclestr))
    {
      if(!continuouscyclestr.IsEmpty())
        {
          int value[3] = { 0, 0, 0 }; 

          continuouscyclestr.UnFormat(__L("%d,%d,%d")  , &value[0], &value[1], &value[2]); 

          if(!value[0]) value[0] = UI_ELEMENT_PROGRESSBAR_CCYCLE_DEFAULTSIZESEGMENT;
          if(!value[1]) value[1] = UI_ELEMENT_PROGRESSBAR_CCYCLE_DEFAULTSTEPSEGMENT;
          if(!value[1]) value[1] = UI_ELEMENT_PROGRESSBAR_CCYCLE_DEFAULTTIMESTEP;

          element_progressbar->ContinuousCycle_Set(true,  value[0], value[1], value[2]);             
        }
    }

  XSTRING progressrectstr;
  if(GetLayoutElementValue(node, __L("progressrect"), progressrectstr))
    {
      if(!progressrectstr.IsEmpty())
        {
          UI_ELEMENT* element_progressrect = NULL;

          element_progressrect = new UI_ELEMENT();
          if(element_progressrect)
            {
              int value[4] = { 0, 0, 0, 0 }; 

              progressrectstr.UnFormat(__L("%d,%d,%d,%d")  , &value[0], &value[1], &value[2], &value[3]); 

              element_progressrect->GetBoundaryLine()->x = element_progressbar->GetXPosition() + value[0];
              element_progressrect->GetBoundaryLine()->y = element_progressbar->GetYPosition() + value[1];      

              if(value[2]) 
                {       
                  element_progressrect->GetBoundaryLine()->width = value[2]; 
                }
               else
                {
                  element_progressrect->GetBoundaryLine()->width = element_progressbar->GetBoundaryLine()->width; 
                }

              if(value[3])
                {
                  element_progressrect->GetBoundaryLine()->height  = value[3];
                }
               else
                {
                  element_progressrect->GetBoundaryLine()->height  = element_progressbar->GetBoundaryLine()->height;
                }

              //element_progressbar->GetBoundaryLine()->SetAround((*element_progressrect->GetBoundaryLine()));
              element_progressbar->SetProgressRect(element_progressrect);
              element_progressrect->SetFather(element_progressbar);

              element_progressbar->GetComposeElements()->Add(element_progressrect);
            }
        }
    }
   else 
    {
      element_progressbar->SetProgressRect(NULL);
    }


  GetLayoutElement_CalculateBoundaryLine(layout, element_progressbar);

  return element_progressbar;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         UI_ELEMENT* UI_MANAGER::CreatePartialLayout(XFILEXMLELEMENT* nodeelement, UI_LAYOUT* layout, UI_ELEMENT* father)
* @brief      CreatePartialLayout
* @ingroup    USERINTERFACE
* 
* @param[in]  nodeelement : 
* @param[in]  layout : 
* @param[in]  father : 
* 
* @return     UI_ELEMENT* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
UI_ELEMENT* UI_MANAGER::CreatePartialLayout(XFILEXMLELEMENT* nodeelement, UI_LAYOUT* layout, UI_ELEMENT* father)
{
  XSTRING       value;
  UI_ELEMENT*   element  = NULL;

  if(GetLayoutElementValue(nodeelement, __L("type"), value))
    {                              
      if(!value.Compare(__L("text")           , true))  
        {
          element = GetLayoutElement_Text(nodeelement, layout, father);          
        }

      if(!value.Compare(__L("textbox")        , true))  
        {
          element = GetLayoutElement_TextBox(nodeelement, layout, father);          
        }

      if(!value.Compare(__L("image")          , true))  
        {
          element = GetLayoutElement_Image(nodeelement, layout, father);
        }

      if(!value.Compare(__L("animation")      , true))  
        {
          element = GetLayoutElement_Animation(nodeelement, layout, father);          
        }

      if(!value.Compare(__L("option")         , true))  
        {
          element = GetLayoutElement_Option(nodeelement, layout, father);          
        }

      if(!value.Compare(__L("multioption")    , true))  
        {
          element = GetLayoutElement_MultiOption(nodeelement, layout, father);          
        }

      if(!value.Compare(__L("button")         , true))  
        { 
          element = GetLayoutElement_Button(nodeelement, layout, father); 
        }

      if(!value.Compare(__L("checkbox")       , true))  
        {
          element = GetLayoutElement_CheckBox(nodeelement, layout, father);          
        }

      if(!value.Compare(__L("edittext")       , true))  
        {
          element = GetLayoutElement_EditText(nodeelement, layout, father);          
        }

      if(!value.Compare(__L("form")           , true))  
        {
          element = GetLayoutElement_Form(nodeelement, layout, father);
        }

      if(!value.Compare(__L("menu")           , true))  
        {
          element = GetLayoutElement_Menu(nodeelement, layout, father);      
        }

      if(!value.Compare(__L("listbox")        , true))  
        {
          element = GetLayoutElement_ListBox(nodeelement, layout, father);      
        }

      if(!value.Compare(__L("progressbar")    , true))  
        {
          element = GetLayoutElement_ProgressBar(nodeelement, layout, father);      
        }
    }

  return element;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_MANAGER::CreateLayouts(XFILEXML& xml, GRPSCREEN* screen, int viewportindex)
* @brief      CreateLayouts
* @ingroup    USERINTERFACE
* 
* @param[in]  xml : 
* @param[in]  screen : 
* @param[in]  viewportindex : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool UI_MANAGER::CreateLayouts(XFILEXML& xml, GRPSCREEN* screen, int viewportindex)
{ 
  if(!xml.ReadAndDecodeAllLines()) 
    {
      return false;
    }

  XFILEXMLELEMENT*  root          = xml.GetRoot();  
  XSTRING           nametypeskin;  
  UI_SKIN_DRAWMODE  drawmode      = UI_SKIN_DRAWMODE_UNKNOWN;  
  XSTRING           raster_fontname;
  XSTRING           vector_fontname; 
  XSTRING           background_color[2]; 
  XSTRING           background_namefile[2]; 
  
  if(!root) 
    {
      return false;
    }
    
  for(int c=0; c<root->GetNElements(); c++)
    {
      XFILEXMLELEMENT* nodeskin = root->GetElement(c);
      if(nodeskin)
        {
          if(!nodeskin->GetName().Compare(__L("skin"), true))
            {                 
              XCHAR*    value;                             
              XSTRING   drawmodestr;
                 
              value = nodeskin->GetValueAttribute(__L("name"));
              if(value) nametypeskin = value;

              drawmodestr = nodeskin->GetValueAttribute(__L("drawmode"));  
              if(!drawmodestr.Compare(__L("canvas"), true))   drawmode = UI_SKIN_DRAWMODE_CANVAS;
              if(!drawmodestr.Compare(__L("context"), true))  drawmode = UI_SKIN_DRAWMODE_CONTEXT;                  

              value = nodeskin->GetValueAttribute(__L("rasterfont"));                          
              if(value) raster_fontname = value;
                                          
              value = nodeskin->GetValueAttribute(__L("vectorfont"));                          
              if(value) vector_fontname = value;    

              value = nodeskin->GetValueAttribute(__L("backgroundcolor"));                          
              if(value) background_color[1] = value;                                       

              value = nodeskin->GetValueAttribute(__L("backgroundimg"));                          
              if(value) background_namefile[1] = value;                                       
            }                  
        }
    }

  UI_SKIN* ui_skin = Skin_Create(nametypeskin, drawmode, screen, viewportindex);
  if(!ui_skin) 
    {
      return false;
    }
       
  ui_skin->GetRasterFont()->Set(raster_fontname);
  ui_skin->GetVectorFont()->Set(vector_fontname);

  if(!ui_skin->LoadFonts()) 
    {
      return false;
    }

  GRPPROPERTYMODE grppropertymode = GRPPROPERTYMODE_XX_UNKNOWN;

  for(int c=0; c<root->GetNElements(); c++)
    {
      XFILEXMLELEMENT*  nodecacheelement = root->GetElement(c);
      if(nodecacheelement)
        {          
          if(ui_skin)
            {
              switch(drawmode)
                {
                  case UI_SKIN_DRAWMODE_UNKNOWN   : break;

                  case UI_SKIN_DRAWMODE_CANVAS    : { UI_SKINCANVAS* skincanvas = (UI_SKINCANVAS*)ui_skin;
                                                      if(skincanvas)
                                                        {
                                                          grppropertymode = skincanvas->GetCanvas()->GetMode();
                                                        }
                                                    }
                                                    break;
   
                  case UI_SKIN_DRAWMODE_CONTEXT   : break;
                }  
            }

          CreateCacheElements(nodecacheelement, drawmode, grppropertymode);
        }
    }

  for(int c=0; c<root->GetNElements(); c++)
    {
      XFILEXMLELEMENT* nodelayout = root->GetElement(c);
      if(nodelayout)
        {
          if(!nodelayout->GetName().Compare(__L("layout"), true))
            {
              XSTRING   namelayout;                
              XCHAR*    value;                             

              value = nodelayout->GetValueAttribute(__L("name"));
              if(value) namelayout = value;         
              if(!namelayout.IsEmpty())
                {                      
                  value = nodelayout->GetValueAttribute(__L("backgroundcolor"));                          
                  if(value) background_color[0] = value;                                       

                  value = nodelayout->GetValueAttribute(__L("backgroundimg"));                          
                  if(value) background_namefile[0] = value;                  

                  UI_LAYOUT* layout = new UI_LAYOUT(ui_skin);
                  if(layout)
                    {
                      XSTRING  bckcolor;
                      XSTRING  bcknamefile;

                      layout->GetNameID()->Set(namelayout);                         
                      layout->GetBackground()->GetColor()->SetFromString(background_color[1]); 
                      layout->GetBackground()->GetBitmapFileName()->Set(background_namefile[1]);
                      
                      if(!background_color[0].IsEmpty())
                        {
                          bckcolor = background_color[0];   
                        }
                       else
                        {
                          if(!background_color[1].IsEmpty())
                            {
                              bckcolor = background_color[1];   
                            }
                        }
                        
                      if(!background_namefile[0].IsEmpty())
                        {
                          bcknamefile = background_namefile[0];   
                        }
                       else
                        {
                          if(!background_namefile[1].IsEmpty())
                            {
                              bcknamefile = background_namefile[1];   
                            }
                        }  

                       GRPBITMAP* background = LoadBackgroundBitmap(bcknamefile, grppropertymode);
                       if(background)
                         {
                           layout->GetBackground()->SetBitmap(background);          
                         }

                      if(!layout->GetNameID()->Compare(UI_MANAGER_LAYOUT_COMMON, true))
                        {
                          layout_commonindex = layouts.GetSize();
                        }

                      Layouts_Add(layout); 
                    
                      for(int d=0 ; d<nodelayout->GetNElements(); d++)
                        {
                          XFILEXMLELEMENT* nodeelement =  nodelayout->GetElement(d);
                          if(nodeelement)
                            {
                              UI_ELEMENT* element = CreatePartialLayout(nodeelement, layout, NULL);
                              if(element) layout->Elements_Add(element);                                                                                                                              
                            }                              
                        } 
                    }  
                }
            }                  
        }
    }
    
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         GRPBITMAP* UI_MANAGER::LoadBackgroundBitmap(XSTRING& namefilebitmap, GRPPROPERTYMODE mode)
* @brief      LoadBackgroundBitmap
* @ingroup    USERINTERFACE
* 
* @param[in]  namefilebitmap : 
* @param[in]  mode : 
* 
* @return     GRPBITMAP* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
GRPBITMAP* UI_MANAGER::LoadBackgroundBitmap(XSTRING& namefilebitmap, GRPPROPERTYMODE mode)
{  
  GRPBITMAPFILE*  bitmapfile;
  GRPBITMAP*      bitmap  = NULL;  
  bool            status  = false; 

  bitmapfile = new GRPBITMAPFILE();
  if(!bitmapfile) 
    {
      return NULL;
    }               

   if(iszippedfile && unzipfile)
    {
      if(unzipfile)
        {                
          XPATH pathnamefilecmp;

          pathnamefilecmp = APPDEFAULT_DIRECTORY_GRAPHICS;
          pathnamefilecmp.Slash_Add();
          pathnamefilecmp += namefilebitmap;
 
          status = unzipfile->DecompressFile(pathnamefilecmp, unzippathfile, namefilebitmap.Get());   
          if(status)
            {  
              XPATH unzippathfile_tmp;

              unzippathfile_tmp  = unzippathfile.Get();
              unzippathfile_tmp += namefilebitmap;          

              bitmap = bitmapfile->Load(unzippathfile_tmp, mode);
    
              DeleteTemporalUnZipFile(unzippathfile_tmp);  
            }
        }
    }
   else
    { 
      XPATH xpath;

      GEN_XPATHSMANAGER.GetPathOfSection(XPATHSMANAGERSECTIONTYPE_GRAPHICS, xpath);
      xpath.Slash_Add();
      xpath.Add(namefilebitmap.Get());                                             

      bitmap = bitmapfile->Load(xpath, mode);    
    }

  delete bitmapfile;

  return bitmap;
}

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_MANAGER::CreateCacheElements(XFILEXMLELEMENT* nodeelement, UI_SKIN_DRAWMODE drawmode, GRPPROPERTYMODE grppropertymode, bool recursive)
* @brief      CreateCacheElements
* @ingroup    USERINTERFACE
* 
* @param[in]  nodeelement : 
* @param[in]  drawmode : 
* @param[in]  grppropertymode : 
* @param[in]  recursive : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool UI_MANAGER::CreateCacheElements(XFILEXMLELEMENT* nodeelement, UI_SKIN_DRAWMODE drawmode, GRPPROPERTYMODE grppropertymode, bool recursive)
{
  XSTRING name;          
  XCHAR*  value;  
  bool    status = false;

  if(!nodeelement->GetName().Compare(__L("color"), true))
    {                                                                  
      value = nodeelement->GetValueAttribute(__L("name"));
      if(value) 
        {
          name = value;
        }
              
      value = nodeelement->GetValue().Get();
      if(value) 
        {
          status = GEN_UI_COLORS.Add(name.Get(), value);                                                                       
        }
    }                  
    
  if(!nodeelement->GetName().Compare(__L("text"), true))
    {                                      
      value = nodeelement->GetValueAttribute(__L("name"));
      if(value) 
        {
          name = value;
        }
              
      value = nodeelement->GetValue().Get();
      if(value) 
        {
          status = GEN_UI_TEXTS.Add(name.Get(), value);                                                                       
        }
    }                      
  
  if(!nodeelement->GetName().Compare(__L("animation"), true))
    {                     
      value = nodeelement->GetValueAttribute(__L("name"));
      if(value)        
        { 
          name = value;
        }
              
      value = nodeelement->GetValue().Get();
      if(value) 
        {
          if(GetOrAddAnimationCache(drawmode, grppropertymode, name.Get(), value)) 
            {
              status = true;
            }
        }
    }

  if(recursive)
    {
      for(int c=0; c<nodeelement->GetNElements(); c++)
        {
          XFILEXMLELEMENT* subnodeelement = nodeelement->GetElement(c);
          if(subnodeelement) 
            {
              CreateCacheElements(subnodeelement, drawmode, grppropertymode, recursive);
            }
        }
    }
                  
  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_MANAGER::RegisterEvents(bool active)
* @brief      RegisterEvents
* @ingroup    USERINTERFACE
*
* @param[in]  active : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool UI_MANAGER::RegisterEvents(bool active)
{
  UI_XEVENT_TYPE eventtype[] = {  UI_XEVENT_TYPE_INPUT_CURSOR_MOVE            ,
                                  UI_XEVENT_TYPE_INPUT_CURSOR_MOTION          , 
                                  UI_XEVENT_TYPE_INPUT_SELECCTION             , 
                                  UI_XEVENT_TYPE_OUTPUT_SELECTED              ,
                                  UI_XEVENT_TYPE_OUTPUT_TEXTTOCHANGE          ,
                                  UI_XEVENT_TYPE_OUTPUT_CHANGECONTENTS      
                               };

  for(int c=0; c<(sizeof(eventtype) / sizeof(UI_XEVENT_TYPE)); c++)
    {
      if(active)        
             RegisterEvent(eventtype[c]);              
       else  DeRegisterEvent(eventtype[c]);              
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         UI_ELEMENT* UI_MANAGER::PreSelectElement(UI_LAYOUT* layout, UI_ELEMENT* element, int x, int y)
* @brief      PreSelectElement
* @ingroup    USERINTERFACE
* 
* @param[in]  layout : 
* @param[in]  element : 
* @param[in]  x : 
* @param[in]  y : 
* 
* @return     UI_ELEMENT* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
UI_ELEMENT* UI_MANAGER::PreSelectElement(UI_ELEMENT* element, int x, int y)
{
  UI_BOUNDARYLINE bline;
  bool            preselect         = false;
  bool            intofather        = false;
  UI_ELEMENT*     preselect_element = NULL;
  
  if(dynamic_cast<UI_PROPERTY_SELECTABLE*>(element))                                                                                                                                                                                                                                          
    {    
      if(element->IsActive() && element->IsVisible())
        {                                                                              
          bline.x       = element->GetXPositionWithScroll();          
          bline.y       = element->GetYPositionWithScroll();          
          bline.width   = element->GetBoundaryLine()->width;
          bline.height  = element->GetBoundaryLine()->height;
          
          preselect = bline.IsWithin(x, y);
          if(preselect)
            {
              if(element->IsSelected()) 
                {
                  preselect = false;                        
                }
            }

          element->SetPreSelect(preselect);                                                                           
          if(preselect) 
            {
              element->SetMustReDraw(true);
            
              last_xposition = x;
              last_yposition = y;

              preselect_element = element;
            }
        }
    } 

  if(!preselect)
    {
      bline.x       = element->GetXPosition();
      bline.y       = element->GetYPosition();
      bline.width   = element->GetBoundaryLine()->width;
      bline.height  = element->GetBoundaryLine()->height;
          
      intofather = bline.IsWithin(x, y);     
    }

  if(intofather)
    {                                                                                                                                     
      if(element->GetComposeElements()->GetSize())
        {                                                                      
          for(XDWORD d=0; d<element->GetComposeElements()->GetSize(); d++)   
            {
              UI_ELEMENT* subelement = element->GetComposeElements()->Get(d);
              if(subelement) 
                {                  
                  preselect_element = PreSelectElement(subelement, x, y);                
                  if(preselect_element) break;  
                }
            }
        }     
    }

  return preselect_element;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_MANAGER::SelectElement(UI_ELEMENT* element)
* @brief      SelectElement
* @ingroup    USERINTERFACE
* 
* @param[in]  element : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool UI_MANAGER::SelectElement(UI_ELEMENT* element)
{
  if(dynamic_cast<UI_PROPERTY_SELECTABLE*>(element))                                                                                                                                                                                                                                          
    {    
      if(SelectedElement(element)) 
        {
          return true;      
        }
    } 
                                                                                                                                     
  if(element->GetComposeElements()->GetSize())
    {                                                                      
      for(XDWORD d=0; d<element->GetComposeElements()->GetSize(); d++)   
        {
          UI_ELEMENT* subelement = element->GetComposeElements()->Get(d);
          if(subelement) 
            { 
              if(dynamic_cast<UI_PROPERTY_SELECTABLE*>(subelement))                                                                                                                                                                                                                                          
                {                  
                  if(SelectedElement(subelement)) 
                    {
                      return true;                  
                    }
                }
            }
        }
    }                             

  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_MANAGER::SelectedElement(UI_LAYOUT* layout, UI_ELEMENT* element)
* @brief      SelectedElement
* @ingroup    USERINTERFACE
* 
* @param[in]  layout : 
* @param[in]  element : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool UI_MANAGER::SelectedElement(UI_ELEMENT* element)
{
  if(!element) return false;

  if(!element->IsPreSelect()) return false;

  UI_PROPERTY_SELECTABLE* element_selectable = dynamic_cast<UI_PROPERTY_SELECTABLE*>(element);
  if(!element_selectable) return false;

  // XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("UI Element [%s]: Selected. "), element->GetName()->Get());

  if(dynamic_cast<UI_PROPERTY_EDITABLE*>(element))        
    {
      if(virtualkeyboard) virtualkeyboard->Show(true, element);
    }

  if(element->GetType() == UI_ELEMENT_TYPE_CHECKBOX)
    {
      UI_ELEMENT_CHECKBOX* element_checkbox = (UI_ELEMENT_CHECKBOX*)element;
      if(element_checkbox) 
        {
          bool status = element_checkbox->GetStatus();

          // XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("[Checkbox select] name %s status: %s"), element_checkbox->GetName()->Get(), (status?__L("true"):__L("false"))); 
          
          status=!status;

          element_checkbox->SetStatus(status);
          
          // XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("[Checkbox select] name %s status: %s"), element_checkbox->GetName()->Get(), (status?__L("true"):__L("false"))); 

          Elements_SetToRedraw(element);  
      }
    }
   else
    {
      if(virtualkeyboard)
        {
          if(virtualkeyboard->SelectInput(element)) 
            {
              return true;
            }
        }

      if(element->GetType() == UI_ELEMENT_TYPE_LISTBOX)
        {
          UI_ELEMENT_LISTBOX* element_listbox = (UI_ELEMENT_LISTBOX*)element;
          if(element_listbox)
            { 
              UI_ELEMENT_MENU* element_menu = element_listbox->Get_UIMenu();     
              if(element_menu)
                {           
                  Element_SetModal(element_menu);  
       
                  element_menu->SetVisible(!element_menu->IsVisible());     
                }
            }
        }
      
      element->SetPreSelect(false);     
      element->SetSelected(true);

      element_selectable->GetXTimerSelected()->Reset();
                      
      SendEvent(UI_XEVENT_TYPE_OUTPUT_SELECTED, element); 

      //element->SetSelected(false);
      Elements_SetToRedraw(element);                   
    }

  return true;
}                       


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_MANAGER::UnSelectedElement(UI_LAYOUT* layout, UI_ELEMENT* element)
* @brief      UnSelectedElement
* @ingroup    USERINTERFACE
* 
* @param[in]  layout : 
* @param[in]  element : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool UI_MANAGER::UnSelectedElement(UI_ELEMENT* element)
{
  if(element->IsSelected()) 
    {
      UI_PROPERTY_SELECTABLE* element_selectable = dynamic_cast<UI_PROPERTY_SELECTABLE*>(element);
      if(!element_selectable) 
        {
          return false;
        }
                        
      if(element_selectable->GetXTimerSelected())
        {
          if(element_selectable->GetXTimerSelected()->GetMeasureMilliSeconds() > element_selectable->GetTimeSelected()) 
            {             
              element->SetSelected(false);
              Elements_SetToRedraw(element);     

              GEN_USERINTERFACE.SendEvent(UI_XEVENT_TYPE_INPUT_CURSOR_MOVE, last_xposition, last_yposition);   
            }
        }                 
    }
                                                                                                                                     
  if(element->GetComposeElements()->GetSize())
    {                                                                      
      for(XDWORD d=0; d<element->GetComposeElements()->GetSize(); d++)   
        {
          UI_ELEMENT* subelement = element->GetComposeElements()->Get(d);
          if(subelement) 
            { 
              if(dynamic_cast<UI_PROPERTY_SELECTABLE*>(subelement))                                                                                                                                                                                                                                          
                {                  
                  if(UnSelectedElement(subelement)) 
                    {
                      return true;                  
                    }
                }
            }
        }
    }                             

  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_MANAGER::UnSelectedElement()
* @brief      UnSelectedElement
* @ingroup    USERINTERFACE
*
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool UI_MANAGER::UnSelectedElement()
{
  for(XDWORD d=0; d<layouts.GetSize(); d++)
    {    
      UI_LAYOUT* layout = layouts.Get(d);                                                          
      if(layout)
        {
          for(XDWORD c=0; c<layout->Elements_Get()->GetSize(); c++)
            {
              UI_ELEMENT* element = layout->Elements_Get()->Get(c);
              if(element) 
                {
                  UnSelectedElement(element);                        
                }
            }        
        }
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_MANAGER::UseMotionInElement(UI_ELEMENT* element, INPCURSORMOTION* cursormotion)
* @brief      UseMotionInElement
* @ingroup    USERINTERFACE
* 
* @param[in]  element : 
* @param[in]  cursormotion : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool UI_MANAGER::UseMotionInElement(UI_ELEMENT* element, INPCURSORMOTION* cursormotion)
{
  if(!element)      
    {
      return false;
    }

  if(!cursormotion) 
    {
      return false;
    }

  if(!element->IsVisible()) return false;

  UI_PROPERTY_SCROLLEABLE* property_scrolleable = dynamic_cast<UI_PROPERTY_SCROLLEABLE*>(element);
  if(!property_scrolleable) 
    {
      return false;
    }

  bool isinrect = cursormotion->IsInRect((int)element->GetXPosition()           , (int)(element->GetYPosition() - element->GetBoundaryLine()->height), 
                                         (int)element->GetBoundaryLine()->width , (int)element->GetBoundaryLine()->height);
  if(isinrect)
    {
      XDWORD differential = 0;
      INPCURSORMOTION_DIR motiondir = cursormotion->GetDirectionByDifferential(&differential);
      if(motiondir != INPCURSORMOTION_DIR_UNKNOWN)
        {
          switch(motiondir)
            {
              case INPCURSORMOTION_DIR_UP         :
              case INPCURSORMOTION_DIR_DOWN       : { double shift = (differential/3);
                                                      if(motiondir == INPCURSORMOTION_DIR_DOWN) shift *= -1;
                                                      
                                                      property_scrolleable->Scroll_SetStep(UI_PROPERTY_SCROLLEABLE_TYPE_VERTICAL, shift);   
                                                      GEN_USERINTERFACE.Elements_SetToRedraw(element);                                                                                                                 
                                                                                                                                                                                                                                                                                          
                                                      XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("[Input Motion]  motion %s points: %d"), (motiondir == INPCURSORMOTION_DIR_UP)?__L("up"):__L("down"), cursormotion->GetNPoints());

                                                      return true;  
                                                    }
                                                    break;              

              case INPCURSORMOTION_DIR_RIGHT      : 
              case INPCURSORMOTION_DIR_LEFT       : break;                  

                                      default     : break;
            }             
        } 
    }
                                                                                                                                             
  if(element->GetComposeElements()->GetSize())
    {                                                                      
      for(XDWORD d=0; d<element->GetComposeElements()->GetSize(); d++)   
        {
          UI_ELEMENT* subelement = element->GetComposeElements()->Get(d);
          if(subelement) 
            { 
              if(dynamic_cast<UI_PROPERTY_SELECTABLE*>(subelement))                                                                                                                                                                                                                                          
                {                  
                  if(UseMotionInElement(subelement, cursormotion)) 
                    {
                      return true;                  
                    }
                }
            }
        }
    }                             

  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_MANAGER::UseMotion(INPCURSORMOTION* cursormotion)
* @brief      UseMotion
* @ingroup    USERINTERFACE
*
* @param[in]  cursormotion : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool UI_MANAGER::UseMotion(INPCURSORMOTION* cursormotion)
{
  if(!cursormotion) 
    {
      return false;
    }

  for(int d=0; d<layouts.GetSize(); d++)
    {    
      UI_LAYOUT* layout = layouts.Get(d);                                                          
      if(layout) 
        {
          for(XDWORD c=0; c<layout->Elements_Get()->GetSize(); c++)
            {
              UI_ELEMENT* element = layout->Elements_Get()->Get(c);
              if(element) 
                {
                  if(UseMotionInElement(element, cursormotion)) return true;
                }
            }        
        }
    }

  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void UI_MANAGER::HandleEvent_UI(UI_XEVENT* event)
* @brief      Handle Event for the observer manager of this class
* @note       INTERNAL
* @ingroup    USERINTERFACE
*
* @param[in]  event : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void UI_MANAGER::HandleEvent_UI(UI_XEVENT* event)
{
  switch(event->GetEventType())
    {
      case UI_XEVENT_TYPE_INPUT_CURSOR_MOVE         : { UI_ELEMENT*  _preselect_element = NULL;
                                                        int          x                  = event->GetXPos();
                                                        int          y                  = event->GetYPos();

                                                        //XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("x: %d, y: %d"), x, y);
                                                  
                                                        if(element_modal)
                                                          {                                                              
                                                            _preselect_element = PreSelectElement(element_modal, x, y);                                                              
                                                          }
                                                         else
                                                          {
                                                            for(int d=0; d<layouts.GetSize(); d++)
                                                              {    
                                                                UI_LAYOUT* layout = layouts.Get(d);                                                          
                                                                if(layout) 
                                                                  {
                                                                    for(XDWORD c=0; c<layout->Elements_Get()->GetSize(); c++)
                                                                      {
                                                                        UI_ELEMENT* element = layout->Elements_Get()->Get(c);
                                                                        if(element) 
                                                                          {
                                                                            _preselect_element = PreSelectElement(element, x, y);
                                                                            if(_preselect_element) break;                                                                       
                                                                          }
                                                                      }
                                                                  }

                                                                if(_preselect_element) break;       
                                                              }
                                                          }

                                                        if(!_preselect_element)  
                                                          {
                                                            if(preselect_element)
                                                              {
                                                                ResetPreselect();                                                                                                 
                                                              }
                                                          } 
                                                         else
                                                          {
                                                            if(_preselect_element != preselect_element)
                                                              {
                                                                if(preselect_element) 
                                                                  { 
                                                                    ResetPreselect();                                     
                                                                  }

                                                                preselect_element = _preselect_element;                                                                      
                                                              }                                                           
                                                          }                                                                                                                                                  
                                                      }
                                                      break;

      case UI_XEVENT_TYPE_INPUT_CURSOR_MOTION       : { 
                                                        if(UseMotion(event->GetCursorMotion()))
                                                          {
                                                            UnSelectedElement();
                                                          }
                                                      }
                                                      break;

      case UI_XEVENT_TYPE_INPUT_SELECCTION          : { if(element_modal)
                                                          { 
                                                            if(xmutex_modal) 
                                                              {
                                                                xmutex_modal->Lock(); 
                                                              }

                                                            SelectElement(element_modal);                                                                                   

                                                            if(xmutex_modal) 
                                                              {
                                                                xmutex_modal->UnLock(); 
                                                              }
                                                          }
                                                         else
                                                          {
                                                            for(int d=0; d<layouts.GetSize(); d++)
                                                              {    
                                                                UI_LAYOUT* layout = layouts.Get(d);                                                          
                                                                if(layout) 
                                                                  {
                                                                    for(XDWORD c=0; c<layout->Elements_Get()->GetSize(); c++)
                                                                      {
                                                                        UI_ELEMENT* element = layout->Elements_Get()->Get(c);
                                                                        if(element) 
                                                                          {
                                                                            if(SelectElement(element)) 
                                                                              {
                                                                                break;
                                                                              }                                                                                                                                                                                                                                                                                                                                      
                                                                          }
                                                                      }
                                                                  }
                                                              }
                                                          }
                                                      }
                                                      break;      
    }
} 


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void UI_MANAGER::HandleEvent(XEVENT* xevent)
* @brief      Handle Event for the observer manager of this class
* @note       INTERNAL
* @ingroup    USERINTERFACE
*
* @param[in]  xevent : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void UI_MANAGER::HandleEvent(XEVENT* xevent)
{
  if(!xevent) return;

  switch(xevent->GetEventFamily())
    {
      case XEVENT_TYPE_USERINTERFACE    : { UI_XEVENT* event = (UI_XEVENT*)xevent;
                                            if(!event) return;

                                            HandleEvent_UI(event);
                                          }
                                          break;
    }
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void UI_MANAGER::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    USERINTERFACE
*
* ---------------------------------------------------------------------------------------------------------------------*/
void UI_MANAGER::Clean()
{  
  iszippedfile        = false;
  unzipfile           = NULL;  
  
  layout_commonindex  = UI_MANAGER_LAYOUT_NOTFOUND;

  xmutex_modal        = NULL;
  element_modal       = NULL;

  xmutex_UIevent      = NULL;

  last_xposition      = 0;
  last_yposition      = 0;


  preselect_element   = NULL;

  virtualkeyboard     = NULL;
}


#pragma endregion

