/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       UI_SkinCanvas.cpp
* 
* @class      UI_SKINCANVAS
* @brief      User Interface Skin Canvas class
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

#include "UI_SkinCanvas.h"

#include "XTrace.h"
#include "XTimer.h"
#include "XSleep.h"

#include "GRPCanvas.h"
#include "GRPViewport.h"
#include "GRPScreen.h"
#include "GRPBitmap.h"
#include "GRPBitmapFile.h"

#include "UI_Animation.h"
#include "UI_Element.h"
#include "UI_Element_Scroll.h"
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
#include "UI_Layout.h"
#include "UI_Manager.h"

#include "APPBase.h"

#include "XMemory_Control.h"

#pragma endregion


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


#pragma region CLASS_UI_SKINCANVAS_REBUILDAREAS


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         UI_SKINCANVAS_REBUILDAREAS::UI_SKINCANVAS_REBUILDAREAS(GRPSCREEN* screen)
* @brief      Constructor
* @ingroup    USERINTERFACE
*
* @param[in]  screen : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
UI_SKINCANVAS_REBUILDAREAS::UI_SKINCANVAS_REBUILDAREAS(GRPSCREEN* screen)
{
  Clean();

  SetExcessEdge(0);

  GRPVIEWPORT* viewport = NULL;
 
  this->screen = screen;
  if(screen) 
    { 
      viewport = screen->GetViewport(0);
      if(viewport) canvas = viewport->GetCanvas();
    }      
}

 
/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         UI_SKINCANVAS_REBUILDAREAS::~UI_SKINCANVAS_REBUILDAREAS()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    USERINTERFACE
*
* ---------------------------------------------------------------------------------------------------------------------*/
UI_SKINCANVAS_REBUILDAREAS::~UI_SKINCANVAS_REBUILDAREAS()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_SKINCANVAS_REBUILDAREAS::RebuildAllAreas()
* @brief      RebuildAllAreas
* @ingroup    USERINTERFACE
*
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool UI_SKINCANVAS_REBUILDAREAS::RebuildAllAreas()
{   
  XDWORD max_z_level = 0;
  XDWORD nareas      = areas.GetSize();
  bool   first       =  false;

  if(!nareas) return true;

  for(XDWORD c=0; c<nareas; c++)
    {
      GRP2DREBUILDAREA* area = areas.Get(c);
      if(area)
        {
          UI_ELEMENT* element = (UI_ELEMENT*)area->GetExtraData();
          if(element)
            {
              max_z_level =  __MAX(max_z_level, element->GetZLevel()); 
            }
        }
    }

  if(!max_z_level) return false;

  for(XDWORD level = max_z_level; level>0; level--)  
    {
      nareas = areas.GetSize();  

      for(int index = nareas-1; index>=0; index--)  
        {
          GRP2DREBUILDAREA* area = areas.Get(index);
          if(area)
            {
              UI_ELEMENT* element = (UI_ELEMENT*)area->GetExtraData();
              if(element)
                {
                  if(element->MustReDraw() || (!element->IsVisible())) 
                    { 
                      if(element->GetZLevel() == level)
                        {       
                          // XTRACE_PRINTCOLOR(XTRACE_COLOR_PURPLE, __L("Del area level [%d] [%s] "), element->GetZLevel(), element->GetName()->Get());
                          GRPBITMAP* bitmap = area->GetBitmap();              
                          if(bitmap) PutBitmapNoAlpha(area->GetXPos(), area->GetYPos(), bitmap);

                          areas.Delete(area);                
                          delete area;  
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
* @fn         bool UI_SKINCANVAS_REBUILDAREAS::RebuildAllAreas(UI_LAYOUT* layout)
* @brief      RebuildAllAreas
* @ingroup    USERINTERFACE
*
* @param[in]  layout : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool UI_SKINCANVAS_REBUILDAREAS::RebuildAllAreas(UI_LAYOUT* layout)
{ 
  if(!layout) return false;
    
  for(XDWORD c=0; c<layout->Elements_Get()->GetSize(); c++)
    {
      UI_ELEMENT* element = layout->Elements_Get()->Get(c);
      if(element) RebuildAllAreas(element);
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_SKINCANVAS_REBUILDAREAS::RebuildAllAreas(UI_ELEMENT* element)
* @brief      RebuildAllAreas
* @ingroup    USERINTERFACE
*
* @param[in]  element : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool UI_SKINCANVAS_REBUILDAREAS::RebuildAllAreas(UI_ELEMENT* element)
{ 
  XDWORD max_z_level = 0;
  XDWORD nareas      = areas.GetSize();
  bool   first       = false;

  if(!nareas) return true;

  for(XDWORD c=0; c<nareas; c++)
    {
      GRP2DREBUILDAREA* area = areas.Get(c);
      if(area)
        {
          UI_ELEMENT* element = (UI_ELEMENT*)area->GetExtraData();
          if(element)
            {
              max_z_level =  __MAX(max_z_level, element->GetZLevel()); 
            }
        }
    }

  if(!max_z_level) return false;
  
  for(XDWORD level = max_z_level; level>0; level--)  
    {
      nareas = areas.GetSize();  

      for(XDWORD index = nareas-1; index>0; index--)                
        {
          GRP2DREBUILDAREA* area = areas.Get(index);
          if(area)
            {
              UI_ELEMENT* _element = (UI_ELEMENT*)area->GetExtraData();
              if(_element)
                {
                  if(_element == element)
                    {
                      if(_element->GetZLevel() == level)
                        {  
                          if(_element->MustReDraw()) 
                            {                              
                              PutBitmapNoAlpha(area->GetXPos(), area->GetYPos(), area->GetBitmap());

                              areas.Delete(area);                
                              delete area;  

                              area = NULL;
                            }              
                        }
                    }
                }
            } 
        }
    } 

  for(XDWORD c=0; c<element->GetComposeElements()->GetSize(); c++)
    {
      UI_ELEMENT* subelement = (UI_ELEMENT*)element->GetComposeElements()->Get(c);
      if(subelement) RebuildAllAreas(subelement);            
    }

  return true;  
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_SKINCANVAS_REBUILDAREAS::CreateRebuildArea(double x, double y, double width, double height, UI_ELEMENT* element)
* @brief      CreateRebuildArea
* @ingroup    USERINTERFACE
*
* @param[in]  x : 
* @param[in]  y : 
* @param[in]  width : 
* @param[in]  height : 
* @param[in]  element : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool UI_SKINCANVAS_REBUILDAREAS::CreateRebuildArea(double x, double y, double width, double height, UI_ELEMENT* element)
{  
  return GRP2DREBUILDAREAS::CreateRebuildArea(x, y, width+1, height+1, (void*)element);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         GRPBITMAP* UI_SKINCANVAS_REBUILDAREAS::GetBitmap(double x, double y, double width, double height)
* @brief      GetBitmap
* @ingroup    USERINTERFACE
*
* @param[in]  x : 
* @param[in]  y : 
* @param[in]  width : 
* @param[in]  height : 
* 
* @return     GRPBITMAP* : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
GRPBITMAP* UI_SKINCANVAS_REBUILDAREAS::GetBitmap(double x, double y, double width, double height)
{
  if(!canvas) return NULL;

  return canvas->GetBitmap(x, y, width, height);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void UI_SKINCANVAS_REBUILDAREAS::PutBitmapNoAlpha(double x, double y, GRPBITMAP* bitmap)
* @brief      PutBitmapNoAlpha
* @ingroup    USERINTERFACE
*
* @param[in]  x : 
* @param[in]  y : 
* @param[in]  bitmap : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void UI_SKINCANVAS_REBUILDAREAS::PutBitmapNoAlpha(double x, double y, GRPBITMAP* bitmap)
{
  if(!canvas) return;

  canvas->PutBitmapNoAlpha(x, y, bitmap); 
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         GRP2DREBUILDAREA* UI_SKINCANVAS_REBUILDAREAS::GetRebuildAreaByElement(UI_ELEMENT* element)
* @brief      GetRebuildAreaByElement
* @ingroup    USERINTERFACE
*
* @param[in]  element : 
* 
* @return     GRP2DREBUILDAREA* : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
GRP2DREBUILDAREA* UI_SKINCANVAS_REBUILDAREAS::GetRebuildAreaByElement(UI_ELEMENT* element)
{
  for(XDWORD c=0; c<GetRebuildAreas()->GetSize(); c++)
    {
      GRP2DREBUILDAREA* rebuild_area = GetRebuildAreas()->Get(c);
      if(rebuild_area)
        {
          UI_ELEMENT* _element = (UI_ELEMENT*)rebuild_area->GetExtraData();
          if(_element)
            {
              if(_element == element) return rebuild_area;
            }
        }
    }

  return NULL;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void UI_SKINCANVAS_REBUILDAREAS::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    USERINTERFACE
*
* --------------------------------------------------------------------------------------------------------------------*/
void UI_SKINCANVAS_REBUILDAREAS::Clean()
{
  screen   = NULL;
  canvas   = NULL;
}


#pragma endregion


#pragma region CLASS_UI_SKINCANVAS


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         UI_SKINCANVAS::UI_SKINCANVAS(GRPSCREEN* screen) : UI_SKIN()
* @brief      Constructor
* @ingroup    USERINTERFACE
*
* @param[in]  screen : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
UI_SKINCANVAS::UI_SKINCANVAS(GRPSCREEN* screen) : UI_SKIN(),  UI_SKINCANVAS_REBUILDAREAS(screen)
{ 
  Clean();     

  this->screen    = screen;
  this->name      = UI_SKINCANVAS_NAME_UNKNOWN;
  this->drawmode  = UI_SKIN_DRAWMODE_CANVAS;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         UI_SKINCANVAS::~UI_SKINCANVAS()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    USERINTERFACE
*
* ---------------------------------------------------------------------------------------------------------------------*/
UI_SKINCANVAS::~UI_SKINCANVAS()    
{ 
  if(!fontpathfile.IsEmpty())
    {
      GEN_USERINTERFACE.DeleteTemporalUnZipFile(fontpathfile);  
    }

  DeleteAllRebuildAreas();

  Clean();                            
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         GRPSCREEN* UI_SKINCANVAS::GetScreen()
* @brief      GetScreen
* @ingroup    USERINTERFACE
*
* @return     GRPSCREEN* : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
GRPSCREEN* UI_SKINCANVAS::GetScreen()
{
  return screen;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         GRPCANVAS* UI_SKINCANVAS::GetCanvas()
* @brief      GetCanvas
* @ingroup    USERINTERFACE
*
* @return     GRPCANVAS* : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
GRPCANVAS* UI_SKINCANVAS::GetCanvas()
{
  if(!screen)                   return NULL;
  if(!screen->GetViewport(0))   return NULL;

  return screen->GetViewport(0)->GetCanvas();
}
		

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_SKINCANVAS::LoadFonts()
* @brief      LoadFonts
* @ingroup    USERINTERFACE
*
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool UI_SKINCANVAS::LoadFonts()
{
  XPATH  xpath;
  bool   status = false; 

  GRPCANVAS* canvas = GetCanvas();
  if(!canvas) return false;
  
  if(!rasterfontname.IsEmpty())
    {
      status = canvas->RasterFont_Select(rasterfontname.Get());

    } else status = true;

  if(status)
    {
      if(!vectorfontname.IsEmpty())
        {          
          GEN_XPATHSMANAGER.GetPathOfSection(XPATHSMANAGERSECTIONTYPE_FONTS, xpath);
          xpath.Slash_Add();
          xpath.Add(vectorfontname.Get());

          if(GEN_USERINTERFACE.IsZippedFile())
            {             
              XFILEUNZIP* unzipfile = GEN_USERINTERFACE.GetUnzipFile();
              if(unzipfile)
                {                  
                  XPATH pathnamefilecmp;

                  pathnamefilecmp = APPDEFAULT_DIRECTORY_FONTS;
                  pathnamefilecmp.Slash_Add();
                  pathnamefilecmp += vectorfontname;

                  status = unzipfile->DecompressFile(pathnamefilecmp, (*GEN_USERINTERFACE.GetUnzipPathFile()), vectorfontname.Get());   
                  if(status)
                    {  
                      XPATH unzippathfile_tmp;

                      unzippathfile_tmp  = GEN_USERINTERFACE.GetUnzipPathFile()->Get();
                      unzippathfile_tmp += vectorfontname;

                      status = canvas->VectorFont_Load(unzippathfile_tmp);  

                      //GEN_USERINTERFACE.DeleteTemporalUnZipFile(unzippathfile_tmp);  

                      fontpathfile = unzippathfile_tmp;
                    }
                    
                }
            }
           else
            {                            
              status = canvas->VectorFont_Load(xpath);    
            }

        } else status = true;
    }

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_SKINCANVAS::Background_LoadBitmap()
* @brief      Background_LoadBitmap
* @ingroup    USERINTERFACE
*
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool UI_SKINCANVAS::Background_LoadBitmap()
{
  if(!screen) return false;

  XPATH           xpath;
  GRPBITMAPFILE*  bitmapfile;
  bool            status = false;

  bitmapfile = new GRPBITMAPFILE();
  if(!bitmapfile) 
    {
      return status;
    }

  GEN_XPATHSMANAGER.GetPathOfSection(XPATHSMANAGERSECTIONTYPE_GRAPHICS, xpath);
  xpath.Slash_Add();
  xpath.Add(background_namefile.Get());

  if(GEN_USERINTERFACE.IsZippedFile())
    {
      XFILEUNZIP* unzipfile = GEN_USERINTERFACE.GetUnzipFile();
      if(unzipfile)
        {                
          XPATH pathnamefilecmp;

          pathnamefilecmp = APPDEFAULT_DIRECTORY_GRAPHICS;
          pathnamefilecmp.Slash_Add();
          pathnamefilecmp += background_namefile;
 
          status = unzipfile->DecompressFile(pathnamefilecmp, (*GEN_USERINTERFACE.GetUnzipPathFile()), background_namefile.Get());   
          if(status)
            {  
              XPATH unzippathfile_tmp;

              unzippathfile_tmp  = GEN_USERINTERFACE.GetUnzipPathFile()->Get();
              unzippathfile_tmp += background_namefile;

              background_bitmap = bitmapfile->Load(unzippathfile_tmp, screen->GetMode());
              if(background_bitmap) 
                {            
                  status = true;
                }

              GEN_USERINTERFACE.DeleteTemporalUnZipFile(unzippathfile_tmp);  
            }
        }
    }
   else
    {                                          
      background_bitmap = bitmapfile->Load(xpath, screen->GetMode());
      if(background_bitmap) 
        {            
          status = true;
        }
    }

  delete bitmapfile;

  return status;

}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_SKINCANVAS::GetFatherSize(UI_ELEMENT* element, double& width, double& height)
* @brief      GetFatherSize
* @ingroup    USERINTERFACE
*
* @param[in]  element : 
* @param[in]  width : 
* @param[in]  height : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool UI_SKINCANVAS::GetFatherSize(UI_ELEMENT* element, double& width, double& height)
{
  GRPCANVAS* canvas = GetCanvas();
  if(!canvas) return false;

  width  = 0.0f;
  height = 0.0f;
  
  if(element->GetFather())  
    {
      width  = element->GetFather()->GetBoundaryLine()->width; 
      height = element->GetFather()->GetBoundaryLine()->height; 
    }
   else  
    { 
      width  = canvas->GetWidth()-1;   
      height = canvas->GetHeight()-1;   
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         double UI_SKINCANVAS::GetPositionWithoutDefine(double position)
* @brief      GetPositionWithoutDefine
* @ingroup    USERINTERFACE
*
* @param[in]  position : 
* 
* @return     double : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
double UI_SKINCANVAS::GetPositionWithoutDefine(double position)
{ 
  switch((int)position)
    {
      case UI_ELEMENT_TYPE_ALIGN_LEFT     : break;
      case UI_ELEMENT_TYPE_ALIGN_RIGHT		: break;
      case UI_ELEMENT_TYPE_ALIGN_UP       : break;
      case UI_ELEMENT_TYPE_ALIGN_DOWN   	: break;
      case UI_ELEMENT_TYPE_ALIGN_CENTER		: break;
                        default       : return position;
    } 
    
  return 0.0f;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_SKINCANVAS::SetAroundFromSubElements(UI_ELEMENT* element)
* @brief      SetAroundFromSubElements
* @ingroup    USERINTERFACE
*
* @param[in]  element : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool UI_SKINCANVAS::SetAroundFromSubElements(UI_ELEMENT* element)
{
  if(!element) return false;
  if(element->GetComposeElements()->IsEmpty()) return false;

  UI_BOUNDARYLINE bondaryline[2];

  bondaryline[1].x      = element->GetXPosition();
  bondaryline[1].y      = element->GetYPosition();
  bondaryline[1].width  = element->GetBoundaryLine()->width;
  bondaryline[1].height = element->GetBoundaryLine()->height;

  for(XDWORD c=0; c<element->GetComposeElements()->GetSize(); c++)
    {
      UI_ELEMENT* subelement = element->GetComposeElements()->Get(c);
      if(subelement)
        {
          bondaryline[0].x       = subelement->GetXPosition();
          bondaryline[0].y       = subelement->GetYPosition();
          bondaryline[0].width   = subelement->GetBoundaryLine()->width;
          bondaryline[0].height  = subelement->GetBoundaryLine()->height;

          bondaryline[1].SetAround(bondaryline[0]);
        }
    }


  for(int c=(int)element->GetComposeElements()->GetSize()-1; c>=0; c--)
    {
      UI_ELEMENT* subelement = element->GetComposeElements()->Get(c);
      if(subelement)
        {
          bondaryline[0].x       = subelement->GetXPosition();
          bondaryline[0].y       = subelement->GetYPosition();
          bondaryline[0].width   = subelement->GetBoundaryLine()->width;
          bondaryline[0].height  = subelement->GetBoundaryLine()->height;

          bondaryline[1].SetAround(bondaryline[0]);
        }
    }
 
  element->SetXPosition(bondaryline[1].x);
  element->SetYPosition(bondaryline[1].y);
  element->GetBoundaryLine()->width  = bondaryline[1].width;
  element->GetBoundaryLine()->height = bondaryline[1].height;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_SKINCANVAS::AddPositionSubElements(UI_ELEMENT* element)
* @brief      AddPositionSubElements
* @ingroup    USERINTERFACE
*
* @param[in]  element : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool UI_SKINCANVAS::AddPositionSubElements(UI_ELEMENT* element)
{
  if(!element) return false;   

  for(XDWORD d=0; d<element->GetComposeElements()->GetSize(); d++)   
    {
      UI_ELEMENT* subelement = element->GetComposeElements()->Get(d);
      if(subelement) 
        {
          subelement->SetXPosition(subelement->GetXPosition() + element->GetXPosition()); 
          subelement->SetYPosition(subelement->GetYPosition() + element->GetYPosition()); 
        }
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_SKINCANVAS::CalculePosition(UI_ELEMENT* element, double fatherwidth, double fatherheight)
* @brief      CalculePosition
* @ingroup    USERINTERFACE
*
* @param[in]  element : 
* @param[in]  fatherwidth : 
* @param[in]  fatherheight : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool UI_SKINCANVAS::CalculePosition(UI_ELEMENT* element, double fatherwidth, double fatherheight)
{ 
  if(!element) return false;

  double x_position = 0.0f;
  double y_position = 0.0f;

  if(element->GetFather())
    {
      x_position = GetPositionWithoutDefine(element->GetFather()->GetXPosition());
      y_position = GetPositionWithoutDefine(element->GetFather()->GetYPosition());     
    }
       
  switch((int)element->GetBoundaryLine()->x)
    {
      case UI_ELEMENT_TYPE_ALIGN_LEFT     : x_position += 0;                                                                  break;
      case UI_ELEMENT_TYPE_ALIGN_RIGHT		: x_position += (fatherwidth - element->GetBoundaryLine()->width);                  break;
      case UI_ELEMENT_TYPE_ALIGN_CENTER   : x_position += (int)round((fatherwidth - element->GetBoundaryLine()->width)/2);    break;
                                default   : x_position += GetPositionWithoutDefine(element->GetBoundaryLine()->x);            break;
    }

  if(element->GetFather())
    {
      switch((int)element->GetBoundaryLine()->y)
        {
          case UI_ELEMENT_TYPE_ALIGN_UP       : y_position -= fatherheight -element->GetBoundaryLine()->height;                   break;
          case UI_ELEMENT_TYPE_ALIGN_DOWN   	: y_position -= 0;                                                                  break;
          case UI_ELEMENT_TYPE_ALIGN_CENTER		: y_position -= (int)round((fatherheight - element->GetBoundaryLine()->height)/2);  break;
                                    default   : y_position -= GetPositionWithoutDefine(element->GetBoundaryLine()->y);            break;
        }
     
    }
   else 
    {
      switch((int)element->GetBoundaryLine()->y)
        {
          case UI_ELEMENT_TYPE_ALIGN_UP       : y_position += element->GetBoundaryLine()->height;                                 break;
          case UI_ELEMENT_TYPE_ALIGN_DOWN   	: y_position += fatherheight;                                                       break;
          case UI_ELEMENT_TYPE_ALIGN_CENTER		: y_position += (int)round((fatherheight + element->GetBoundaryLine()->height)/2);  break;
                                    default   : y_position += GetPositionWithoutDefine(element->GetBoundaryLine()->y);            break;
        }
    }

  x_position += (element->GetMargin(UI_ELEMENT_TYPE_ALIGN_LEFT) - element->GetMargin(UI_ELEMENT_TYPE_ALIGN_RIGHT));
  y_position += (element->GetMargin(UI_ELEMENT_TYPE_ALIGN_UP)   - element->GetMargin(UI_ELEMENT_TYPE_ALIGN_DOWN));

  element->SetXPosition(x_position);
  element->SetYPosition(y_position);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         double UI_SKINCANVAS::GetWithString(XCHAR* string, XDWORD sizefont)
* @brief      GetWithString
* @ingroup    USERINTERFACE
*
* @param[in]  string : 
* @param[in]  sizefont : 
* 
* @return     double : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
double UI_SKINCANVAS::GetWithString(XCHAR* string,  XDWORD sizefont)
{
  XDWORD width  = 0;
  XDWORD height = 0;

  SetFontSize(sizefont);
  GetFontSize(string, width, height);

  return (double)width;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         double UI_SKINCANVAS::GetHeightString(XCHAR* string, XDWORD sizefont)
* @brief      GetHeightString
* @ingroup    USERINTERFACE
*
* @param[in]  string : 
* @param[in]  sizefont : 
* 
* @return     double : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
double  UI_SKINCANVAS::GetHeightString(XCHAR* string, XDWORD sizefont)
{
  XDWORD width  = 0;
  XDWORD height = 0;

  SetFontSize(sizefont);
  GetFontSize(string, width, height);

  return (double)height;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_SKINCANVAS::CalculateBoundaryLine_Scroll(UI_ELEMENT* element)
* @brief      CalculateBoundaryLine_Scroll
* @ingroup    USERINTERFACE
*
* @param[in]  element : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool UI_SKINCANVAS::CalculateBoundaryLine_Scroll(UI_ELEMENT* element)
{
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_SKINCANVAS::CalculateBoundaryLine_Text(UI_ELEMENT* element)
* @brief      CalculateBoundaryLine_Text
* @ingroup    USERINTERFACE
*
* @param[in]  element : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool UI_SKINCANVAS::CalculateBoundaryLine_Text(UI_ELEMENT* element)
{
  if(!element) return false;

  UI_ELEMENT_TEXT* element_text = (UI_ELEMENT_TEXT*)element;
  GRPCANVAS*       canvas       = GetCanvas();

  if(!canvas) return false;
  
  canvas->Vectorfont_GetConfig()->SetSize(element_text->GetSizeFont());

  XSTRING text;
  if(!element_text->GetText()->IsEmpty()) 
    {
      text = element_text->GetText()->Get();    
    }
   else 
    {
      if(!element_text->GetMaskText()->IsEmpty()) 
        {
          text = element_text->GetMaskText()->Get();
        }
    }

  double fatherwidth  = 0.0f;
  double fatherheight = 0.0f;
  
  GetFatherSize(element, fatherwidth, fatherheight);

  XSTRING string_max = text;
  if(element_text->GetMaxSizeText())
    {
      XDWORD size_max = element_text->GetMaxSizeText();     
      
      if(!size_max) size_max = text.GetSize();
      string_max.Empty();
      for(XDWORD c=0; c<size_max; c++)
        {
          string_max += __L("A");
        }
    }

  switch((int)element->GetBoundaryLine()->width)
    {
      case UI_ELEMENT_TYPE_ALIGN_AUTO	 :		 		
      case                           0 : element->GetBoundaryLine()->width  = (double)canvas->VectorFont_GetWidth(string_max.Get());    break;
      case UI_ELEMENT_TYPE_ALIGN_MAX   : element->GetBoundaryLine()->width = fatherwidth;                                               break;	    
    }
   
  switch((int)element->GetBoundaryLine()->height)
    {
      case UI_ELEMENT_TYPE_ALIGN_AUTO	 :		 		
      case                           0 : element->GetBoundaryLine()->height  = (double)canvas->VectorFont_GetHeight(string_max.Get());  break;
      case UI_ELEMENT_TYPE_ALIGN_MAX   : element->GetBoundaryLine()->height  = fatherheight;                                            break;	    
    }

  return CalculePosition(element, fatherwidth, fatherheight);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_SKINCANVAS::CalculateBoundaryLine_TextBox(UI_ELEMENT* element)
* @brief      CalculateBoundaryLine_TextInBox
* @ingroup    USERINTERFACE
*
* @param[in]  element : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool UI_SKINCANVAS::CalculateBoundaryLine_TextBox(UI_ELEMENT* element)
{  
  UI_ELEMENT_TEXTBOX* element_textbox = (UI_ELEMENT_TEXTBOX*)element;
  if(!element_textbox) return false;

  double fatherwidth  = 0.0f;
  double fatherheight = 0.0f;
  
  GetFatherSize(element, fatherwidth, fatherheight);

  switch((int)element->GetBoundaryLine()->width)
    {
      case UI_ELEMENT_TYPE_ALIGN_AUTO   :		 		
      case                            0 : 
      case UI_ELEMENT_TYPE_ALIGN_MAX    : return false; 
                                          break;
    }
   
  switch((int)element->GetBoundaryLine()->height)
    {
      case UI_ELEMENT_TYPE_ALIGN_AUTO	  :		 		
      case                            0 : 
      case UI_ELEMENT_TYPE_ALIGN_MAX    : return false; 
                                          break;
    }

  return CalculePosition(element, fatherwidth, fatherheight);  
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_SKINCANVAS::CalculateBoundaryLine_Image(UI_ELEMENT* element)
* @brief      CalculateBoundaryLine_Image
* @ingroup    USERINTERFACE
*
* @param[in]  element : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool UI_SKINCANVAS::CalculateBoundaryLine_Image(UI_ELEMENT* element)
{
  if(!element) return false;
  
  UI_ELEMENT_IMAGE* element_image = (UI_ELEMENT_IMAGE*)element;
  if(!element_image->GetImage()) return false;

  double fatherwidth  = 0.0f;
  double fatherheight = 0.0f;
  
  GetFatherSize(element, fatherwidth, fatherheight);

  switch((int)element->GetBoundaryLine()->width)
    {
      case UI_ELEMENT_TYPE_ALIGN_AUTO   :		 		
      case                            0 : element->GetBoundaryLine()->width  = (double)element_image->GetImage()->GetWidth();       break;
      case UI_ELEMENT_TYPE_ALIGN_MAX    : element->GetBoundaryLine()->width = fatherwidth;                                          break;	    
    }
   
  switch((int)element->GetBoundaryLine()->height)
    {
      case UI_ELEMENT_TYPE_ALIGN_AUTO	  :		 		
      case                            0 : element->GetBoundaryLine()->height  = (double)element_image->GetImage()->GetHeight();     break;
      case UI_ELEMENT_TYPE_ALIGN_MAX    : element->GetBoundaryLine()->height  = fatherheight;                                       break;	    
    }

  return CalculePosition(element, fatherwidth, fatherheight);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_SKINCANVAS::CalculateBoundaryLine_Animation(UI_ELEMENT* element)
* @brief      CalculateBoundaryLine_Animation
* @ingroup    USERINTERFACE
*
* @param[in]  element : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool UI_SKINCANVAS::CalculateBoundaryLine_Animation(UI_ELEMENT* element)
{
  UI_ELEMENT_ANIMATION* element_animation = (UI_ELEMENT_ANIMATION*)element;
  if(!element_animation) return false;  

  double fatherwidth  = 0.0f;
  double fatherheight = 0.0f;
  
  GetFatherSize(element, fatherwidth, fatherheight);

  switch((int)element->GetBoundaryLine()->width)
    {
      case UI_ELEMENT_TYPE_ALIGN_AUTO     :		 		
      case                             0  : { double maximgwidth = 0.0f; 

                                              for(XDWORD c=0; c<element_animation->GetComposeElements()->GetSize(); c++)
                                                {
                                                 UI_ELEMENT_IMAGE* element_image = (UI_ELEMENT_IMAGE*)element_animation->GetComposeElements()->Get(c);
                                                 if(element_image) maximgwidth = __MAX((GetPositionWithoutDefine(element_image->GetBoundaryLine()->x) + element_image->GetBoundaryLine()->width), maximgwidth);                                                    
                                                }

                                              element->GetBoundaryLine()->width = maximgwidth;
                                            }
                                            break;

      case UI_ELEMENT_TYPE_ALIGN_MAX      : element->GetBoundaryLine()->width = fatherwidth;                                          
                                            break;	    
    }
   
  switch((int)element->GetBoundaryLine()->height)
    {
      case UI_ELEMENT_TYPE_ALIGN_AUTO     :		 		
      case                             0  : { double maximgheight = 0.0f; 

                                              for(XDWORD c=0; c<element_animation->GetComposeElements()->GetSize(); c++)
                                                {
                                                 UI_ELEMENT_IMAGE* element_image = (UI_ELEMENT_IMAGE*)element_animation->GetComposeElements()->Get(c);
                                                 if(element_image) maximgheight = __MAX((GetPositionWithoutDefine(element_image->GetBoundaryLine()->y) + element_image->GetBoundaryLine()->height), maximgheight);                                                    
                                                }

                                              element->GetBoundaryLine()->height = maximgheight;
                                            }
                                            break;

      case UI_ELEMENT_TYPE_ALIGN_MAX      : element->GetBoundaryLine()->height  = fatherheight;                                       
                                            break;	    
    }

  CalculePosition(element, fatherwidth, fatherheight);

  for(XDWORD c=0; c<element_animation->GetComposeElements()->GetSize(); c++)
    {
      UI_ELEMENT_IMAGE* element_image = (UI_ELEMENT_IMAGE*)element_animation->GetComposeElements()->Get(c);
      if(element_image)
        {
          CalculePosition(element_image, element_animation->GetBoundaryLine()->width, element_image->GetBoundaryLine()->height);
        }
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_SKINCANVAS::CalculateBoundaryLine_Option(UI_ELEMENT* element)
* @brief      CalculateBoundaryLine_Option
* @ingroup    USERINTERFACE
*
* @param[in]  element : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool UI_SKINCANVAS::CalculateBoundaryLine_Option(UI_ELEMENT* element)
{
  UI_ELEMENT_OPTION* element_option = (UI_ELEMENT_OPTION*)element;
  if(!element_option) return false;  

  double fatherwidth  = 0.0f;
  double fatherheight = 0.0f;
  
  GetFatherSize(element, fatherwidth, fatherheight);

  UI_ELEMENT_ANIMATION* element_animation = (UI_ELEMENT_ANIMATION*)element_option->Get_UIAnimation();
  UI_ELEMENT_TEXT*      element_text      = (UI_ELEMENT_TEXT*)element_option->Get_UIText();

  double maximgwidth  = 0.0f; 
  double maximgheight = 0.0f; 

  if(element_animation || element_text)
    {
      switch((int)element->GetBoundaryLine()->width)
        {
          case UI_ELEMENT_TYPE_ALIGN_AUTO   :		 		
          case                           0  : { switch(element_option->GetAllocationTextType())
                                                  {                                            
                                                    case UI_ELEMENT_OPTION_ALLOCATION_TEXT_TYPE_RIGHT   : 
                                                    case UI_ELEMENT_OPTION_ALLOCATION_TEXT_TYPE_LEFT    : if(element_animation) maximgwidth += element_animation->GetBoundaryLine()->width;  
                                                                                                          if(element_text)      maximgwidth += element_text->GetBoundaryLine()->width;  
                                                                                                          break;

                                                    case UI_ELEMENT_OPTION_ALLOCATION_TEXT_TYPE_NONE    :                                                                  
                                                    case UI_ELEMENT_OPTION_ALLOCATION_TEXT_TYPE_CENTER  : 
                                                                                              default   : if(element_animation) maximgwidth = __MAX(maximgwidth, element_animation->GetBoundaryLine()->width);                                                                                                    
                                                                                                          if(element_text)      maximgwidth = __MAX(maximgwidth, element_text->GetBoundaryLine()->width);                                                                                                  
                                                                                                          break; 
                                                  } 
                                     
                                                element->GetBoundaryLine()->width = maximgwidth;
                                              }
                                              break;

          case UI_ELEMENT_TYPE_ALIGN_MAX    : element->GetBoundaryLine()->width = fatherwidth;                                          
                                              break;	    
        }

      switch((int)element->GetBoundaryLine()->height)
        {
          case UI_ELEMENT_TYPE_ALIGN_AUTO   :		 		
          case                           0  : { switch(element_option->GetAllocationTextType())
                                                  {                                           
                                                    case UI_ELEMENT_OPTION_ALLOCATION_TEXT_TYPE_UP      : 
                                                    case UI_ELEMENT_OPTION_ALLOCATION_TEXT_TYPE_DOWN    : if(element_animation) maximgheight += element_animation->GetBoundaryLine()->height;  
                                                                                                          if(element_text)      maximgheight += element_text->GetBoundaryLine()->height;  
                                                                                                          break;

                                                    case UI_ELEMENT_OPTION_ALLOCATION_TEXT_TYPE_NONE    : 
                                                    case UI_ELEMENT_OPTION_ALLOCATION_TEXT_TYPE_CENTER  : 
                                                                                              default   : if(element_animation) maximgheight = __MAX(maximgheight, element_animation->GetBoundaryLine()->height);                                                                                                    
                                                                                                          if(element_text)      maximgheight = __MAX(maximgheight, element_text->GetBoundaryLine()->height);                                                                                                  
                                                                                                          break; 
                                                  }                                      
                                                element->GetBoundaryLine()->height = maximgheight;
                                              }
                                              break;

          case UI_ELEMENT_TYPE_ALIGN_MAX    : element->GetBoundaryLine()->height  = fatherheight;                                       
                                              break;	    
        }
    }
  
  CalculePosition(element_option, fatherwidth, fatherheight);

  if(element_animation) CalculePosition(element_animation, element_option->GetBoundaryLine()->width, element_option->GetBoundaryLine()->height);
  if(element_text)      CalculePosition(element_text     , element_option->GetBoundaryLine()->width, element_option->GetBoundaryLine()->height);  

  switch(element_option->GetAllocationTextType())
    {
      case UI_ELEMENT_OPTION_ALLOCATION_TEXT_TYPE_NONE    : break;

      case UI_ELEMENT_OPTION_ALLOCATION_TEXT_TYPE_DOWN    : if(element_animation && element_text) element_animation->SetYPosition(element_animation->GetYPosition() - element_text->GetBoundaryLine()->height);     break;
      case UI_ELEMENT_OPTION_ALLOCATION_TEXT_TYPE_UP      : if(element_animation && element_text) element_text->SetYPosition(element_text->GetYPosition() - element_animation->GetBoundaryLine()->height);          break;                                                           
      case UI_ELEMENT_OPTION_ALLOCATION_TEXT_TYPE_RIGHT   : if(element_animation && element_text) element_text->SetXPosition(element_text->GetXPosition() + element_animation->GetBoundaryLine()->width);           break;
      case UI_ELEMENT_OPTION_ALLOCATION_TEXT_TYPE_LEFT    : if(element_animation && element_text) element_animation->SetXPosition(element_animation->GetXPosition() + element_text->GetBoundaryLine()->width);      break;
      case UI_ELEMENT_OPTION_ALLOCATION_TEXT_TYPE_CENTER  : break; 
    } 

  if(element_animation)
    {
      for(XDWORD c=0; c<element_animation->GetComposeElements()->GetSize(); c++)
        {
          UI_ELEMENT* subelement = element_animation->GetComposeElements()->Get(c);
          if(subelement) CalculePosition(subelement, element_animation->GetBoundaryLine()->width, element_animation->GetBoundaryLine()->height);         
        } 
    }

  SetAroundFromSubElements(element_option);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_SKINCANVAS::CalculateBoundaryLine_MultiOption(UI_ELEMENT* element)
* @brief      CalculateBoundaryLine_MultiOption
* @ingroup    USERINTERFACE
*
* @param[in]  element : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool UI_SKINCANVAS::CalculateBoundaryLine_MultiOption(UI_ELEMENT* element)
{
  UI_ELEMENT_MULTIOPTION* element_multioption = (UI_ELEMENT_MULTIOPTION*)element;
  if(!element_multioption) return false;   

  double fatherwidth  = 0.0f;
  double fatherheight = 0.0f;
  
  GetFatherSize(element, fatherwidth, fatherheight);

  switch((int)element->GetBoundaryLine()->width)
    {
      case UI_ELEMENT_TYPE_ALIGN_AUTO   :		 		
      case                          0   : { double maximgwidth = 0.0f; 

                                            for(XDWORD c=0; c<element_multioption->GetComposeElements()->GetSize(); c++)
                                              {
                                               UI_ELEMENT* subelement = (UI_ELEMENT*)element->GetComposeElements()->Get(c);
                                               if(subelement) maximgwidth = __MAX((GetPositionWithoutDefine(subelement->GetBoundaryLine()->x) + subelement->GetBoundaryLine()->width), maximgwidth);                                                    
                                              }

                                            element->GetBoundaryLine()->width = maximgwidth;
                                          }
                                          break;

      case UI_ELEMENT_TYPE_ALIGN_MAX    : element->GetBoundaryLine()->width = fatherwidth;                                          
                                          break;	    
    }
   
  switch((int)element->GetBoundaryLine()->height)
    {
      case UI_ELEMENT_TYPE_ALIGN_AUTO	  :		 		
      case                          0   : { double maximgheight = 0.0f; 

                                            for(XDWORD c=0; c<element->GetComposeElements()->GetSize(); c++)
                                              {
                                               UI_ELEMENT* subelement = (UI_ELEMENT*)element->GetComposeElements()->Get(c);
                                               if(subelement) maximgheight = __MAX((GetPositionWithoutDefine(subelement->GetBoundaryLine()->y) + subelement->GetBoundaryLine()->height), maximgheight);                                                    
                                              }

                                            element->GetBoundaryLine()->height = maximgheight;
                                          }
                                          break;

      case UI_ELEMENT_TYPE_ALIGN_MAX    : element->GetBoundaryLine()->height  = fatherheight;                                       
                                          break;	    
    }

  CalculePosition(element_multioption, fatherwidth, fatherheight);
  
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_SKINCANVAS::CalculateBoundaryLine_Button(UI_ELEMENT* element)
* @brief      CalculateBoundaryLine_Button
* @ingroup    USERINTERFACE
*
* @param[in]  element : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool UI_SKINCANVAS::CalculateBoundaryLine_Button(UI_ELEMENT* element)
{
  return CalculateBoundaryLine_Option(element);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_SKINCANVAS::CalculateBoundaryLine_CheckBox(UI_ELEMENT* element)
* @brief      CalculateBoundaryLine_CheckBox
* @ingroup    USERINTERFACE
*
* @param[in]  element : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool UI_SKINCANVAS::CalculateBoundaryLine_CheckBox(UI_ELEMENT* element)
{
  return CalculateBoundaryLine_Option(element);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_SKINCANVAS::CalculateBoundaryLine_EditText(UI_ELEMENT* element)
* @brief      CalculateBoundaryLine_EditText
* @ingroup    USERINTERFACE
*
* @param[in]  element : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool UI_SKINCANVAS::CalculateBoundaryLine_EditText(UI_ELEMENT* element)
{  
  if(!element) return false;

  UI_ELEMENT_EDITTEXT* element_edittext = (UI_ELEMENT_EDITTEXT*)element;
  GRPCANVAS*           canvas           = GetCanvas();

  if(!canvas) return false;
  
  canvas->Vectorfont_GetConfig()->SetSize(element_edittext->GetSizeFont());

  XSTRING text;
  if(!element_edittext->GetText()->IsEmpty()) text = element_edittext->GetText()->Get();
    else if(!element_edittext->GetMaskText()->IsEmpty()) text = element_edittext->GetMaskText()->Get();

  double fatherwidth  = 0.0f;
  double fatherheight = 0.0f;
  
  GetFatherSize(element, fatherwidth, fatherheight);

  XSTRING string_max;
  XDWORD  size_max   =  element_edittext->GetMaxSizeText();
  
  if(!size_max) size_max = text.GetSize();
  for(XDWORD c=0; c<size_max; c++)
    {
      string_max += __L("A");
    }

  switch((int)element->GetBoundaryLine()->width)
    {
      case UI_ELEMENT_TYPE_ALIGN_AUTO :		 		
      case                          0 : element->GetBoundaryLine()->width  = (double)canvas->VectorFont_GetWidth(string_max.Get());     break;
      case UI_ELEMENT_TYPE_ALIGN_MAX  : element->GetBoundaryLine()->width = fatherwidth;                                                break;	    
    }
   
  switch((int)element->GetBoundaryLine()->height)
    {
      case UI_ELEMENT_TYPE_ALIGN_AUTO :		 		
      case                          0 : element->GetBoundaryLine()->height  = (double)canvas->VectorFont_GetHeight(string_max.Get());   break;
      case UI_ELEMENT_TYPE_ALIGN_MAX  : element->GetBoundaryLine()->height  = fatherheight;                                             break;	    
    }

  return CalculePosition(element, fatherwidth, fatherheight);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_SKINCANVAS::CalculateBoundaryLine_Form(UI_ELEMENT* element)
* @brief      CalculateBoundaryLine_Form
* @ingroup    USERINTERFACE
*
* @param[in]  element : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool UI_SKINCANVAS::CalculateBoundaryLine_Form(UI_ELEMENT* element)
{
  UI_ELEMENT_FORM* element_form = (UI_ELEMENT_FORM*)element;
  if(!element_form) return false;   

  double fatherwidth  = 0.0f;
  double fatherheight = 0.0f;
  
  GetFatherSize(element, fatherwidth, fatherheight);

  switch((int)element->GetBoundaryLine()->width)
    {
      case UI_ELEMENT_TYPE_ALIGN_AUTO	  :		 		
      case                           0  : { double maximgwidth = 0.0f; 

                                            for(XDWORD c=0; c<element_form->GetComposeElements()->GetSize(); c++)
                                              {
                                               UI_ELEMENT* subelement = (UI_ELEMENT*)element->GetComposeElements()->Get(c);
                                               if(subelement) maximgwidth = __MAX((GetPositionWithoutDefine(subelement->GetBoundaryLine()->x) + subelement->GetBoundaryLine()->width), maximgwidth);                                                    
                                              }

                                            element->GetBoundaryLine()->width = maximgwidth;
                                          }
                                          break;

      case UI_ELEMENT_TYPE_ALIGN_MAX    : element->GetBoundaryLine()->width = fatherwidth;                                          
                                          break;	    
    }
   
  switch((int)element->GetBoundaryLine()->height)
    {
      case UI_ELEMENT_TYPE_ALIGN_AUTO	  :		 		
      case                          0   : { double maximgheight = 0.0f; 

                                            for(XDWORD c=0; c<element->GetComposeElements()->GetSize(); c++)
                                              {
                                               UI_ELEMENT* subelement = (UI_ELEMENT*)element->GetComposeElements()->Get(c);
                                               if(subelement) maximgheight = __MAX((GetPositionWithoutDefine(subelement->GetBoundaryLine()->y) + subelement->GetBoundaryLine()->height), maximgheight);                                                    
                                              }

                                            element->GetBoundaryLine()->height = maximgheight;
                                          }
                                          break;

      case UI_ELEMENT_TYPE_ALIGN_MAX    : element->GetBoundaryLine()->height  = fatherheight;                                       
                                          break;	    
    }

  CalculePosition(element_form, fatherwidth, fatherheight);
  
  AddPositionSubElements(element_form);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_SKINCANVAS::CalculateBoundaryLine_Menu(UI_ELEMENT* element)
* @brief      CalculateBoundaryLine_Menu
* @ingroup    USERINTERFACE
*
* @param[in]  element : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool UI_SKINCANVAS::CalculateBoundaryLine_Menu(UI_ELEMENT* element)
{  
  return CalculateBoundaryLine_Form(element);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_SKINCANVAS::CalculateBoundaryLine_ListBox(UI_ELEMENT* element)
* @brief      CalculateBoundaryLine_ListBox
* @ingroup    USERINTERFACE
*
* @param[in]  element : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool UI_SKINCANVAS::CalculateBoundaryLine_ListBox(UI_ELEMENT* element)
{  
  if(!element) return false;

  UI_ELEMENT_LISTBOX* element_listbox  = (UI_ELEMENT_LISTBOX*)element;
  GRPCANVAS*          canvas           = GetCanvas();

  if(!canvas) return false;
  
  canvas->Vectorfont_GetConfig()->SetSize(element_listbox->GetSizeFont());

  XSTRING text;
  if(!element_listbox->GetText()->IsEmpty()) text = element_listbox->GetText()->Get();
    else if(!element_listbox->GetMaskText()->IsEmpty()) text = element_listbox->GetMaskText()->Get();

  double fatherwidth  = 0.0f;
  double fatherheight = 0.0f;
  
  GetFatherSize(element, fatherwidth, fatherheight);

  XSTRING string_max;
  XDWORD  size_max   =  element_listbox->GetMaxSizeText();
  
  if(!size_max) size_max = text.GetSize();
  for(XDWORD c=0; c<size_max; c++)
    {
      string_max += __L("A");
    }

  switch((int)element->GetBoundaryLine()->width)
    {
      case UI_ELEMENT_TYPE_ALIGN_AUTO :		 		
      case                          0 : element->GetBoundaryLine()->width  = (double)canvas->VectorFont_GetWidth(string_max.Get());     break;
      case UI_ELEMENT_TYPE_ALIGN_MAX  : element->GetBoundaryLine()->width = fatherwidth;                                                break;	    
    }
   
  switch((int)element->GetBoundaryLine()->height)
    {
      case UI_ELEMENT_TYPE_ALIGN_AUTO	:		 		
      case                          0 : element->GetBoundaryLine()->height  = (double)canvas->VectorFont_GetHeight(string_max.Get());   break;
      case UI_ELEMENT_TYPE_ALIGN_MAX  : element->GetBoundaryLine()->height  = fatherheight;                                             break;	    
    }

  return CalculePosition(element, fatherwidth, fatherheight);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_SKINCANVAS::CalculateBoundaryLine_ProgressBar(UI_ELEMENT* element)
* @brief      CalculateBoundaryLine_ProgressBar
* @ingroup    USERINTERFACE
*
* @param[in]  element : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool UI_SKINCANVAS::CalculateBoundaryLine_ProgressBar(UI_ELEMENT* element)
{
  UI_ELEMENT_PROGRESSBAR* element_progressbar = (UI_ELEMENT_PROGRESSBAR*)element;
  if(!element_progressbar) return false;  

  double fatherwidth  = 0.0f;
  double fatherheight = 0.0f;
  
  GetFatherSize(element, fatherwidth, fatherheight);

  UI_ELEMENT*           element_progressrect  = element_progressbar->GetProgressRect();
  UI_ELEMENT_ANIMATION* element_animation     = (UI_ELEMENT_ANIMATION*)element_progressbar->Get_UIAnimation();
  UI_ELEMENT_TEXT*      element_text          = (UI_ELEMENT_TEXT*)element_progressbar->Get_UIText();

  double maximgwidth  = 0.0f; 
  double maximgheight = 0.0f; 

  if(element_animation || element_text || element_progressrect)
    {
      switch((int)element->GetBoundaryLine()->width)
        {
          case UI_ELEMENT_TYPE_ALIGN_AUTO   :		 		
          case                           0  : { switch(element_progressbar->GetAllocationTextType())
                                                  {                                            
                                                    case UI_ELEMENT_OPTION_ALLOCATION_TEXT_TYPE_RIGHT   : 
                                                    case UI_ELEMENT_OPTION_ALLOCATION_TEXT_TYPE_LEFT    : if(element_progressrect)  maximgwidth += element_progressrect->GetBoundaryLine()->width;  
                                                                                                          if(element_animation)     maximgwidth += element_animation->GetBoundaryLine()->width;  
                                                                                                          if(element_text)          maximgwidth += element_text->GetBoundaryLine()->width;  
                                                                                                          break;

                                                    case UI_ELEMENT_OPTION_ALLOCATION_TEXT_TYPE_NONE    :                                                                  
                                                    case UI_ELEMENT_OPTION_ALLOCATION_TEXT_TYPE_CENTER  : 
                                                                                              default   : if(element_progressrect)  maximgwidth = __MAX(maximgwidth, element_progressrect->GetBoundaryLine()->width);  
                                                                                                          if(element_animation)     maximgwidth = __MAX(maximgwidth, element_animation->GetBoundaryLine()->width);                                                                                                    
                                                                                                          if(element_text)          maximgwidth = __MAX(maximgwidth, element_text->GetBoundaryLine()->width);                                                                                                  
                                                                                                          break; 
                                                  } 
                                     
                                                element->GetBoundaryLine()->width = maximgwidth;
                                              }
                                              break;

          case UI_ELEMENT_TYPE_ALIGN_MAX    : element->GetBoundaryLine()->width = fatherwidth;                                          
                                              break;	    
        }

      switch((int)element->GetBoundaryLine()->height)
        {
          case UI_ELEMENT_TYPE_ALIGN_AUTO   :		 		
          case                           0  : { switch(element_progressbar->GetAllocationTextType())
                                                  {                                           
                                                    case UI_ELEMENT_OPTION_ALLOCATION_TEXT_TYPE_UP      : 
                                                    case UI_ELEMENT_OPTION_ALLOCATION_TEXT_TYPE_DOWN    : if(element_progressrect)  maximgheight += element_progressrect->GetBoundaryLine()->height; 
                                                                                                          if(element_animation)     maximgheight += element_animation->GetBoundaryLine()->height;  
                                                                                                          if(element_text)          maximgheight += element_text->GetBoundaryLine()->height;  
                                                                                                          break;

                                                    case UI_ELEMENT_OPTION_ALLOCATION_TEXT_TYPE_NONE    : 
                                                    case UI_ELEMENT_OPTION_ALLOCATION_TEXT_TYPE_CENTER  : 
                                                                                              default   : if(element_progressrect)  maximgheight = __MAX(maximgheight, element_progressrect->GetBoundaryLine()->height); 
                                                                                                          if(element_animation)     maximgheight = __MAX(maximgheight, element_animation->GetBoundaryLine()->height);                                                                                                    
                                                                                                          if(element_text)          maximgheight = __MAX(maximgheight, element_text->GetBoundaryLine()->height);                                                                                                  
                                                                                                          break; 
                                                  }                                      
                                                element->GetBoundaryLine()->height = maximgheight;
                                              }
                                              break;

          case UI_ELEMENT_TYPE_ALIGN_MAX    : element->GetBoundaryLine()->height  = fatherheight;                                       
                                              break;	    
        }
    }
  
  CalculePosition(element_progressbar, fatherwidth, fatherheight);

  if(element_progressrect)  CalculePosition(element_progressrect  , element_progressbar->GetBoundaryLine()->width, element_progressbar->GetBoundaryLine()->height);
  if(element_animation)     CalculePosition(element_animation     , element_progressbar->GetBoundaryLine()->width, element_progressbar->GetBoundaryLine()->height);
  if(element_text)          CalculePosition(element_text          , element_progressbar->GetBoundaryLine()->width, element_progressbar->GetBoundaryLine()->height);  


  switch(element_progressbar->GetAllocationTextType())
    {
      case UI_ELEMENT_OPTION_ALLOCATION_TEXT_TYPE_NONE    : break;

      case UI_ELEMENT_OPTION_ALLOCATION_TEXT_TYPE_DOWN    : if(element_animation && element_text)     element_animation->SetYPosition(element_animation->GetYPosition() - element_text->GetBoundaryLine()->height);     
                                                            if(element_progressrect && element_text)  element_progressrect->SetYPosition(element_progressrect->GetYPosition() - (element_text->GetBoundaryLine()->height + 6));     
                                                            break;

      case UI_ELEMENT_OPTION_ALLOCATION_TEXT_TYPE_UP      : if(element_animation && element_text)     element_text->SetYPosition(element_text->GetYPosition() - element_animation->GetBoundaryLine()->height);          
                                                            if(element_progressrect && element_text)  element_text->SetYPosition(element_text->GetYPosition() - (element_progressrect->GetBoundaryLine()->height + 6));          
                                                            break;                                                           

      case UI_ELEMENT_OPTION_ALLOCATION_TEXT_TYPE_RIGHT   : if(element_animation && element_text)     element_text->SetXPosition(element_text->GetXPosition() + element_animation->GetBoundaryLine()->width);           
                                                            if(element_progressrect && element_text)  element_text->SetXPosition(element_text->GetXPosition() + element_progressrect->GetBoundaryLine()->width);    
                                                            break;

      case UI_ELEMENT_OPTION_ALLOCATION_TEXT_TYPE_LEFT    : if(element_animation && element_text)     element_animation->SetXPosition(element_animation->GetXPosition() + element_text->GetBoundaryLine()->width);      
                                                            if(element_progressrect && element_text)  element_progressrect->SetXPosition(element_progressrect->GetXPosition() + element_text->GetBoundaryLine()->width);    
                                                            break;

      case UI_ELEMENT_OPTION_ALLOCATION_TEXT_TYPE_CENTER  : if(element_progressrect && element_text)  
                                                              {
                                                                element_text->SetXPosition(element_progressrect->GetXPosition() + ((element_progressrect->GetBoundaryLine()->width  - element_text->GetBoundaryLine()->width)/2));    
                                                                element_text->SetYPosition(element_progressrect->GetYPosition() - ((element_progressrect->GetBoundaryLine()->height - element_text->GetBoundaryLine()->height)/2));             
                                                              }
                                                            break; 
    } 

  if(element_animation)
    {
      for(XDWORD c=0; c<element_animation->GetComposeElements()->GetSize(); c++)
        {
          UI_ELEMENT* subelement = element_animation->GetComposeElements()->Get(c);
          if(subelement) CalculePosition(subelement, element_animation->GetBoundaryLine()->width, element_animation->GetBoundaryLine()->height);         
        } 
    }

  SetAroundFromSubElements(element_progressbar);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_SKINCANVAS::SetElementPosition(UI_ELEMENT* element, double x_position, double y_position)
* @brief      SetElementPosition
* @ingroup    USERINTERFACE
*
* @param[in]  element : 
* @param[in]  x_position : 
* @param[in]  y_position : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool UI_SKINCANVAS::SetElementPosition(UI_ELEMENT* element, double x_position, double y_position)
{
  if(!element) return false;

  element->GetBoundaryLine()->x = x_position;
  element->GetBoundaryLine()->y = y_position;

  bool status = CalculeBoundaryLine_AllElements(element);

  if(dynamic_cast<UI_ELEMENT_FORM*>(element))                                                                                                                                                                                                                                          
    {                                                     
      UI_ELEMENT_FORM* element_form = (UI_ELEMENT_FORM*)element;

      element_form->GetVisibleRect()->x = element_form->GetXPosition();
      element_form->GetVisibleRect()->y = element_form->GetYPosition();
    }

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_SKINCANVAS::Draw_Scroll(UI_ELEMENT* element)
* @brief      Draw_Scroll
* @ingroup    USERINTERFACE
*
* @param[in]  element : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool UI_SKINCANVAS::Draw_Scroll(UI_ELEMENT* element)  
{
  return true;
}
  

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_SKINCANVAS::Draw_Text(UI_ELEMENT* element)
* @brief      Draw_Text
* @ingroup    USERINTERFACE
* 
* @param[in]  element : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool UI_SKINCANVAS::Draw_Text(UI_ELEMENT* element)  
{
  if(!element) return false;  

  UI_ELEMENT_TEXT*    element_text  = (UI_ELEMENT_TEXT*)element;
  GRPCANVAS*          canvas        = GetCanvas();  
  double              x_position    = 0.0f;
  double              y_position    = 0.0f;  
  XRECT               clip_rect;                       
  
  if(!canvas) return false;
 
  PreDrawFunction(element, canvas, clip_rect, x_position, y_position);
      
  if(element->MustReDraw()) 
    {
      GRP2DCOLOR_RGBA8  color(element->GetColor()->GetRed(),
                              element->GetColor()->GetGreen(),
                              element->GetColor()->GetBlue(),
                              element->GetColor()->GetAlpha());
                         
      
      canvas->Vectorfont_GetConfig()->SetColor(&color);
      canvas->Vectorfont_GetConfig()->SetSize(element_text->GetSizeFont());  
      canvas->VectorFont_Print(x_position, y_position, element_text->GetText()->Get());
    }

  PostDrawFunction(element, canvas, clip_rect, x_position, y_position);
  
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_SKINCANVAS::Draw_TextBox(UI_ELEMENT* element)
* @brief      Draw_TextBox
* @ingroup    USERINTERFACE
* 
* @param[in]  element : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool UI_SKINCANVAS::Draw_TextBox(UI_ELEMENT* element)  
{ 
  if(!element) return false;  

  UI_ELEMENT_TEXTBOX* element_textbox = (UI_ELEMENT_TEXTBOX*)element;
  GRPCANVAS*          canvas          = GetCanvas();  
  double              x_position      = 0.0f;
  double              y_position      = 0.0f;  
  XRECT               clip_rect;                       
  
  if(!canvas) return false;
 
  PreDrawFunction(element, canvas, clip_rect, x_position, y_position);
      
  if(element->MustReDraw()) 
    {
      GRP2DCOLOR_RGBA8                color(element->GetColor()->GetRed(),
                                            element->GetColor()->GetGreen(),
                                            element->GetColor()->GetBlue(),
                                            element->GetColor()->GetAlpha());
      XVECTOR<UI_SKIN_TEXTBOX_PART*>  parts;
      XVECTOR<UI_SKIN_TEXTBOX_IMAGE*> images;

                               
      canvas->Vectorfont_GetConfig()->SetColor(&color);
      canvas->Vectorfont_GetConfig()->SetSize(element_textbox->GetSizeFont());  

      TextBox_GenerateLines(element_textbox, canvas, x_position, y_position, parts, images);

      for(XDWORD c=0; c<parts.GetSize(); c++)
        {
          UI_SKIN_TEXTBOX_PART* textbox_part = parts.Get(c);
          if(textbox_part)
            {
              GRP2DCOLOR_RGBA8 color_part(textbox_part->GetColor()->GetRed(),
                                          textbox_part->GetColor()->GetGreen(),
                                          textbox_part->GetColor()->GetBlue(),
                                          textbox_part->GetColor()->GetAlpha());

              canvas->Vectorfont_GetConfig()->SetColor(&color_part);

              canvas->VectorFont_Printf(textbox_part->GetXPos(), textbox_part->GetYPos(), textbox_part->GetText()->Get());   


              #ifdef USERINTERFACE_DEBUG 
              GRP2DCOLOR_RGBA8  color_debug(255, 0, 255);

              int width   = (int)canvas->VectorFont_GetWidth(textbox_part->GetText()->Get());
              int height  = (int)canvas->VectorFont_GetHeight(__L("A"));

              canvas->SetLineWidth(1.0f);
              canvas->SetLineColor(&color_debug);
              canvas->Rectangle(textbox_part->GetXPos() ,  
                                textbox_part->GetYPos() ,
                                textbox_part->GetXPos() + width , 
                                textbox_part->GetYPos() - height);             
              #endif  
            }
        } 

     for(XDWORD c=0; c<images.GetSize(); c++)
        {
          UI_SKIN_TEXTBOX_IMAGE* textbox_image = images.Get(c);
          if(textbox_image)
            {
              canvas->PutBitmapAlpha(textbox_image->GetBoundaryLine()->x  ,
                                     textbox_image->GetBoundaryLine()->y  ,
                                     textbox_image->GetAnimation()->GetBitmap(), 100);

              #ifdef USERINTERFACE_DEBUG               
              GRP2DCOLOR_RGBA8  color_debug(0, 0, 255);

              canvas->SetLineWidth(1.0f);
              canvas->SetLineColor(&color_debug);
              canvas->Rectangle(textbox_image->GetBoundaryLine()->x ,  
                                textbox_image->GetBoundaryLine()->y ,
                                textbox_image->GetBoundaryLine()->x + textbox_image->GetBoundaryLine()->width, 
                                textbox_image->GetBoundaryLine()->y + textbox_image->GetBoundaryLine()->height);              
              #endif
            }
        }
   
      parts.DeleteContents();
      parts.DeleteAll();

      images.DeleteContents();
      images.DeleteAll();
    }

  PostDrawFunction(element, canvas, clip_rect, x_position, y_position);
  
  return true;
}
  

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_SKINCANVAS::Draw_Image(UI_ELEMENT* element)
* @brief      Draw_Image
* @ingroup    USERINTERFACE
* 
* @param[in]  element : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool UI_SKINCANVAS::Draw_Image(UI_ELEMENT* element)  
{
  if(!element) return false;
 
  UI_ELEMENT_IMAGE*   element_image = (UI_ELEMENT_IMAGE*)element;
  GRPCANVAS*          canvas        = GetCanvas(); 
  double              x_position    = 0.0f;
  double              y_position    = 0.0f;
  XRECT               clip_rect;                       

  if(!element_image->GetImage()) return false; 
  if(!canvas) return false;

  PreDrawFunction(element, canvas, clip_rect, x_position, y_position);

  if(element->MustReDraw()) 
    {
      canvas->PutBitmapAlpha(x_position , 
                             y_position - element_image->GetImage()->GetHeight(), 
                             element_image->GetImage(), element_image->GetAlpha());
    }

  PostDrawFunction(element, canvas, clip_rect, x_position, y_position);
    
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_SKINCANVAS::Draw_Animation(UI_ELEMENT* element)
* @brief      Draw_Animation
* @ingroup    USERINTERFACE
* 
* @param[in]  element : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool UI_SKINCANVAS::Draw_Animation(UI_ELEMENT* element)  
{
  if(!element) return false;

  UI_ELEMENT_ANIMATION* element_animation  = (UI_ELEMENT_ANIMATION*)element;  
  UI_ELEMENT_IMAGE*     element_image      = (UI_ELEMENT_IMAGE*)element_animation->GetComposeElements()->Get(element_animation->IndexImage_Get());
  double                x_position         = 0.0f;
  double                y_position         = 0.0f;  
  GRPCANVAS*            canvas             = GetCanvas();    
  XRECT                 clip_rect;          
  bool                  redraw             = false;

  if(!element_animation)  return false;
  if(!element_image)      return false;

  PreDrawFunction(element, canvas, clip_rect, x_position, y_position);

  if(element->MustReDraw()) 
    {
      if(element_animation)
        {
          XBYTE alpha = element_animation->GetAlpha();
          if(alpha < element_image->GetAlpha()) element_image->SetAlpha(alpha);
        }

      Draw(element_image);     
    }

  switch(element_animation->GetState())
    {
      case UI_ELEMENT_ANIMATION_STATE_UNKNOWN   : break;

      case UI_ELEMENT_ANIMATION_STATE_PLAY      : if(element_animation->GetXTimerPlay()->GetMeasureMilliSeconds() >= element_animation->GetMilliSecondsDelay())
                                                    {
                                                      element_animation->IndexImage_Add();
                                                      element_animation->GetXTimerPlay()->Reset();  
                                                      redraw = true;                                                          
                                                    }
                                                  
                                                  break;

      case UI_ELEMENT_ANIMATION_STATE_STOP      : element_animation->IndexImage_Reset();                                                  
                                                  redraw = true;
                                                  break;


      case UI_ELEMENT_ANIMATION_STATE_PAUSE     : break;
    }

  PostDrawFunction(element, canvas, clip_rect, x_position, y_position);
  
  if(redraw) Elements_SetToRedraw(element_animation);  

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_SKINCANVAS::Draw_Option(UI_ELEMENT* element)
* @brief      Draw_Option
* @ingroup    USERINTERFACE
* 
* @param[in]  element : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool UI_SKINCANVAS::Draw_Option(UI_ELEMENT* element)  
{
  if(!element) return false;
 
  UI_ELEMENT_OPTION*    element_option    = (UI_ELEMENT_OPTION*)element;
  UI_ELEMENT_ANIMATION* element_animation = element_option->Get_UIAnimation();
  UI_ELEMENT_TEXT*      element_text      = element_option->Get_UIText();
  double                x_position        = 0.0f;
  double                y_position        = 0.0f;
  GRPCANVAS*            canvas            = GetCanvas();
  XRECT                 clip_rect;              

  if(!canvas) return false;

  PreDrawFunction(element, canvas, clip_rect, x_position, y_position, UI_SKINCANVAS_PRESELECT_MAXEDGE);

  if(element->MustReDraw()) 
    {
      bool isselected  = false;
      bool ispreselect = false;

      if(element_option->GetFather()) 
        {
          if(element_option->GetFather()->GetType() != UI_ELEMENT_TYPE_MULTIOPTION)
            {
              ispreselect = element_option->IsPreSelect();
              if(!ispreselect) ispreselect = element_option->GetFather()->IsPreSelect();    
            }

          if(element_option->GetFather()->GetType() != UI_ELEMENT_TYPE_MULTIOPTION)
            {
              isselected = element_option->IsSelected();
              if(!isselected) isselected = element_option->GetFather()->IsSelected();    
            }
  
        } 
       else 
        {
          isselected = element_option->IsSelected();
          ispreselect = element_option->IsPreSelect();
        }

      if(element->IsBlinking() && !element->GetStateBlink()) ispreselect = false;

      DrawBackgroundColor(element_option, canvas, x_position, y_position);
      
      if(isselected)
        { 
          GRP2DCOLOR_RGBA8  colorred(255, 0, 0);     
          GRP2DCOLOR_RGBA8  colorhover(0x32, 0x33, 0x36, 150);
  
          canvas->SetLineWidth(0.0f);
          canvas->SetLineColor(&colorred);
          canvas->SetFillColor(&colorhover);
      
          canvas->Rectangle(x_position  - UI_SKINCANVAS_PRESELECT_MAXEDGE                                      , 
                            y_position  + UI_SKINCANVAS_PRESELECT_MAXEDGE                                      ,
                            x_position  + element->GetBoundaryLine()->width  + UI_SKINCANVAS_PRESELECT_MAXEDGE , 
                            y_position  - element->GetBoundaryLine()->height - UI_SKINCANVAS_PRESELECT_MAXEDGE , true);      
        }
       else
        {
          if(ispreselect)
            { 
              
              GRP2DCOLOR_RGBA8  colorwhite(255, 255, 255);
              GRP2DCOLOR_RGBA8  colorhover(0x32, 0x33, 0x36, 150);
  
              canvas->SetLineWidth(0.0f);
              canvas->SetLineColor(&colorwhite);
              canvas->SetFillColor(&colorhover);
      
              canvas->Rectangle(x_position  - UI_SKINCANVAS_PRESELECT_MAXEDGE                                      , 
                                y_position  + UI_SKINCANVAS_PRESELECT_MAXEDGE                                      ,
                                x_position  + element->GetBoundaryLine()->width  + UI_SKINCANVAS_PRESELECT_MAXEDGE , 
                                y_position  - element->GetBoundaryLine()->height - UI_SKINCANVAS_PRESELECT_MAXEDGE , true);      
            }
         }

      if(element_animation)  Draw(element_animation);    
      if(element_text)       Draw(element_text);  
    }

  
  PostDrawFunction(element, canvas, clip_rect, x_position, y_position);

  if(element_animation )
    {
      if(element_animation->GetState() == UI_ELEMENT_ANIMATION_STATE_PLAY)
        { 
          Elements_SetToRedraw(element_option);  
        }
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_SKINCANVAS::Draw_MultiOption(UI_ELEMENT* element)
* @brief      Draw_MultiOption
* @ingroup    USERINTERFACE
* 
* @param[in]  element : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool UI_SKINCANVAS::Draw_MultiOption(UI_ELEMENT* element)
{    
  if(!screen)  return false;
  if(!element) return false;

  UI_ELEMENT_MULTIOPTION* element_multioption  = (UI_ELEMENT_MULTIOPTION*)element;
  double                  x_position           = 0.0f;
  double                  y_position           = 0.0f;
  GRPCANVAS*              canvas               = GetCanvas();
  XRECT                   clip_rect;  
  
  if(!canvas) return false;
  
  PreDrawFunction(element, canvas, clip_rect, x_position, y_position);

  UI_PROPERTY_SELECTABLE_STATE actual_state = UI_PROPERTY_SELECTABLE_STATE_DEACTIVE;
  
  if(element_multioption->IsSelected()) 
    { 
      actual_state = UI_PROPERTY_SELECTABLE_STATE_SELECTED;
    }
   else 
    {
      if(element_multioption->IsPreSelect()) 
        {
          actual_state = UI_PROPERTY_SELECTABLE_STATE_PRESELECT;        
        }
       else 
        {
          if(element_multioption->IsActive()) 
            { 
              actual_state = UI_PROPERTY_SELECTABLE_STATE_ACTIVE;              
            }
        }
    }

  //if(element->MustReDraw()) 
    {
      DrawBackgroundColor(element_multioption, canvas, x_position, y_position);
 
      for(XDWORD c=0; c<element_multioption->GetComposeElements()->GetSize(); c++)
        {
          UI_ELEMENT_OPTION* element_option = (UI_ELEMENT_OPTION*)element_multioption->GetComposeElements()->Get(c);
          if(element_option) 
            {
              if(element_option->GetSelectableState() == actual_state) 
                {
                  Draw(element_option);              
                  break;              
                }       
            }            
        }
    }
      
  PostDrawFunction(element, canvas, clip_rect, x_position, y_position);

  return true;
}
  

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_SKINCANVAS::Draw_Button(UI_ELEMENT* element)
* @brief      Draw_Button
* @ingroup    USERINTERFACE
* 
* @param[in]  element : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool UI_SKINCANVAS::Draw_Button(UI_ELEMENT* element)  
{  
  return Draw_Option(element);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_SKINCANVAS::Draw_CheckBox(UI_ELEMENT* element)
* @brief      Draw_CheckBox
* @ingroup    USERINTERFACE
* 
* @param[in]  element : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool UI_SKINCANVAS::Draw_CheckBox(UI_ELEMENT* element)  
{
  UI_ELEMENT_CHECKBOX* checkbox = (UI_ELEMENT_CHECKBOX*)element;

  if(checkbox)
    {
      UI_ELEMENT_ANIMATION* animation = checkbox->Get_UIAnimation();
      if(animation) animation->IndexImage_Set(checkbox->GetStatus()?1:0);
    }

  return Draw_Option(element);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_SKINCANVAS::Draw_EditText(UI_ELEMENT* element)
* @brief      Draw_EditText
* @ingroup    USERINTERFACE
* 
* @param[in]  element : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool UI_SKINCANVAS::Draw_EditText(UI_ELEMENT* element)  
{    
  if(!element) return false;  

  UI_ELEMENT_EDITTEXT*  element_edittext  = (UI_ELEMENT_EDITTEXT*)element;
  double                x_position        = 0.0f;
  double                y_position        = 0.0f;
  GRPCANVAS*            canvas            = GetCanvas();    
  static bool           visible           = false;
  XRECT                 clip_rect;                       
  
  if(!canvas) return false;

  PreDrawFunction(element, canvas, clip_rect, x_position, y_position, UI_SKINCANVAS_EDIT_MAXEDGE);
  
  GRP2DCOLOR_RGBA8  color(element->GetColor()->GetRed(),
                          element->GetColor()->GetGreen(),
                          element->GetColor()->GetBlue(),
                          element->GetColor()->GetAlpha());

  GRP2DCOLOR_RGBA8  bkgcolor(element->GetBackgroundColor()->GetRed(),
                             element->GetBackgroundColor()->GetGreen(),
                             element->GetBackgroundColor()->GetBlue(),
                             element_edittext->IsPreSelect()?element->GetBackgroundColor()->GetAlpha()/2:element->GetBackgroundColor()->GetAlpha());

  GRP2DCOLOR_RGBA8  linecolor;

  GRP2DCOLOR_RGBA8  colorwhite(255, 255, 255, 255);
 
  if(element->MustReDraw()) 
    {
      canvas->SetLineColor(&linecolor);
      canvas->SetFillColor(&bkgcolor);

      if(element->GetRoundRect())
        {
          canvas->RoundRect(element->GetXPosition()  - UI_SKINCANVAS_EDIT_MAXEDGE                                      ,
                            element->GetYPosition()  + UI_SKINCANVAS_EDIT_MAXEDGE                                      ,       
                            element->GetXPosition()  + element->GetBoundaryLine()->width  + UI_SKINCANVAS_EDIT_MAXEDGE , 
                            element->GetYPosition()  - element->GetBoundaryLine()->height - UI_SKINCANVAS_EDIT_MAXEDGE , element->GetRoundRect(), true);        
        }
       else
        {
          canvas->Rectangle(element->GetXPosition()  - UI_SKINCANVAS_EDIT_MAXEDGE                                      ,
                            element->GetYPosition()  + UI_SKINCANVAS_EDIT_MAXEDGE                                      ,       
                            element->GetXPosition()  + element->GetBoundaryLine()->width  + UI_SKINCANVAS_EDIT_MAXEDGE , 
                            element->GetYPosition()  - element->GetBoundaryLine()->height - UI_SKINCANVAS_EDIT_MAXEDGE , true);
        }
   
                                   
      canvas->Vectorfont_GetConfig()->SetColor(&color);
      canvas->Vectorfont_GetConfig()->SetSize(element_edittext->GetSizeFont());  
      canvas->VectorFont_Printf(element->GetXPosition(), element->GetYPosition(), element_edittext->GetText()->Get());

      if(element_edittext->Cursor_IsVisible())
        {
          XDWORD    cursor_xpos = 0;
          XSTRING   cursor_string;

          element_edittext->GetText()->Copy(0, element_edittext->Cursor_GetPosition(), cursor_string);

          cursor_xpos = (XDWORD)GetWithString(cursor_string.Get(), element_edittext->GetSizeFont());
       
          if(element_edittext->Cursor_GetXTimerBlink()->GetMeasureMilliSeconds() >= element_edittext->Cursor_GetTimeBlink())
            {
              element_edittext->Cursor_ChangeStateBlink();   
              element_edittext->Cursor_GetXTimerBlink()->Reset();
            } 
 
          if(element_edittext->Cursor_GetStateBlink())
            {
              int cursor_size = 3;

              canvas->SetLineColor(&colorwhite);
              canvas->SetFillColor(&colorwhite);

              canvas->Rectangle( x_position + cursor_xpos , 
                                 y_position + UI_SKINCANVAS_EDIT_MAXEDGE - 4  ,
                                 x_position + cursor_xpos + cursor_size , 
                                 y_position - element_edittext->GetBoundaryLine()->height - UI_SKINCANVAS_EDIT_MAXEDGE + 4 , true);                          
            }
        }
    }

  PostDrawFunction(element, canvas, clip_rect, x_position, y_position);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_SKINCANVAS::Draw_Form(UI_ELEMENT* element)
* @brief      Draw_Form
* @ingroup    USERINTERFACE
* 
* @param[in]  element : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool UI_SKINCANVAS::Draw_Form(UI_ELEMENT* element)
{    
  if(!screen)  return false;
  if(!element) return false;

  UI_ELEMENT_FORM*    element_form = (UI_ELEMENT_FORM*)element;
  double              x_position   = 0.0f;
  double              y_position   = 0.0f;
  GRPCANVAS*          canvas       = GetCanvas();
  XRECT               clip_rect;  
  
  if(!canvas) return false;
  
  PreDrawFunction(element, canvas, clip_rect, x_position, y_position);

  if(element->MustReDraw()) 
    {
      GRP2DCOLOR_RGBA8  color(element_form->GetColor()->GetRed(),
                              element_form->GetColor()->GetGreen(),
                              element_form->GetColor()->GetBlue(),
                              element_form->GetColor()->GetAlpha());

      GRP2DCOLOR_RGBA8  linecolor(element_form->GetLineColor()->GetRed(),
                                  element_form->GetLineColor()->GetGreen(),
                                  element_form->GetLineColor()->GetBlue(),
                                  element_form->GetLineColor()->GetAlpha());

      canvas->SetLineWidth(0.5f);
      canvas->SetLineColor(&linecolor);
      canvas->SetFillColor(&color);

      if(element_form->GetRoundRect())
        {
          canvas->RoundRect(element_form->GetVisibleRect()->x, 
                            element_form->GetVisibleRect()->y,
                            element_form->GetVisibleRect()->x + element_form->GetVisibleRect()->width   , 
                            element_form->GetVisibleRect()->y - element_form->GetVisibleRect()->height  , element_form->GetRoundRect(), true);
        }
       else
        {
          canvas->Rectangle(element_form->GetVisibleRect()->x, 
                            element_form->GetVisibleRect()->y,
                            element_form->GetVisibleRect()->x + element_form->GetVisibleRect()->width   , 
                            element_form->GetVisibleRect()->y - element_form->GetVisibleRect()->height  ,  true);
        }
    }

  for(XDWORD c=0; c<element_form->GetComposeElements()->GetSize(); c++)
    {
      UI_ELEMENT* subelement = (UI_ELEMENT*)element->GetComposeElements()->Get(c);
      if(subelement) 
        {
          Draw(subelement);
        }  
    }
  
  PostDrawFunction(element, canvas, clip_rect, x_position, y_position);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_SKINCANVAS::Draw_Menu(UI_ELEMENT* element)
* @brief      Draw_Menu
* @ingroup    USERINTERFACE
* 
* @param[in]  element : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool UI_SKINCANVAS::Draw_Menu(UI_ELEMENT* element)
{
  return Draw_Form(element);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_SKINCANVAS::Draw_ListBox(UI_ELEMENT* element)
* @brief      Draw_ListBox
* @ingroup    USERINTERFACE
*
* @param[in]  element : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool UI_SKINCANVAS::Draw_ListBox(UI_ELEMENT* element)
{
  if(!element) return false;  

  UI_ELEMENT_LISTBOX*   element_listbox = (UI_ELEMENT_LISTBOX*)element;
  double                x_position      = 0.0f;
  double                y_position      = 0.0f;
  GRPCANVAS*            canvas          = GetCanvas();    
  static bool           visible         = false;
  XRECT                 clip_rect;                       
  
  if(!canvas) return false;

  PreDrawFunction(element, canvas, clip_rect, x_position, y_position, UI_SKINCANVAS_EDIT_MAXEDGE);

  if(element->MustReDraw()) 
    {
      GRP2DCOLOR_RGBA8  color(element->GetColor()->GetRed(),
                              element->GetColor()->GetGreen(),
                              element->GetColor()->GetBlue(),
                              element->GetColor()->GetAlpha());

      GRP2DCOLOR_RGBA8  bkgcolor(element->GetBackgroundColor()->GetRed(),
                                 element->GetBackgroundColor()->GetGreen(),
                                 element->GetBackgroundColor()->GetBlue(),
                                 element_listbox->IsPreSelect()?element->GetBackgroundColor()->GetAlpha()/2:element->GetBackgroundColor()->GetAlpha());

      GRP2DCOLOR_RGBA8  linecolor;

      GRP2DCOLOR_RGBA8  colorwhite(255, 255, 255, 255);
 
  
      canvas->SetLineColor(&linecolor);
      canvas->SetFillColor(&bkgcolor);

      if(element->GetRoundRect())
        {
          canvas->RoundRect(element->GetXPosition()  - UI_SKINCANVAS_EDIT_MAXEDGE                                      , 
                            element->GetYPosition()  + UI_SKINCANVAS_EDIT_MAXEDGE                                      ,
                            element->GetXPosition()  + element->GetBoundaryLine()->width  + UI_SKINCANVAS_EDIT_MAXEDGE , 
                            element->GetYPosition()  - element->GetBoundaryLine()->height - UI_SKINCANVAS_EDIT_MAXEDGE , element->GetRoundRect(), true);
        }
       else
        {
          canvas->Rectangle(element->GetXPosition()  - UI_SKINCANVAS_EDIT_MAXEDGE                                      , 
                            element->GetYPosition()  + UI_SKINCANVAS_EDIT_MAXEDGE                                      ,
                            element->GetXPosition()  + element->GetBoundaryLine()->width  + UI_SKINCANVAS_EDIT_MAXEDGE , 
                            element->GetYPosition()  - element->GetBoundaryLine()->height - UI_SKINCANVAS_EDIT_MAXEDGE , true);
        }
                                      
      canvas->Vectorfont_GetConfig()->SetColor(&color);
      canvas->Vectorfont_GetConfig()->SetSize(element_listbox->GetSizeFont());  
      canvas->VectorFont_Printf(element->GetXPosition(), element->GetYPosition(), element_listbox->GetText()->Get());
    }
  
  PostDrawFunction(element, canvas, clip_rect, x_position, y_position);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_SKINCANVAS::Draw_ProgressBar(UI_ELEMENT* element)
* @brief      Draw_ProgressBar
* @ingroup    USERINTERFACE
*
* @param[in]  element : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool UI_SKINCANVAS::Draw_ProgressBar(UI_ELEMENT* element)
{
  if(!element) return false;  

  UI_ELEMENT_PROGRESSBAR* element_progressbar   = (UI_ELEMENT_PROGRESSBAR*)element;
  UI_ELEMENT*             element_progressrect  = element_progressbar->GetProgressRect();
  UI_ELEMENT_ANIMATION*   element_animation     = element_progressbar->Get_UIAnimation();
  UI_ELEMENT_TEXT*        element_text          = element_progressbar->Get_UIText();
  double                  x_position            = 0.0f;
  double                  y_position            = 0.0f;
  GRPCANVAS*              canvas                = GetCanvas();    
  static bool             visible               = false;
  XRECT                   clip_rect;                       
  
  if(!canvas) return false;

  PreDrawFunction(element, canvas, clip_rect, x_position, y_position, 1);

  if(element->MustReDraw()) 
    {
      if(element_progressrect)
        {
          GRP2DCOLOR_RGBA8  linecolor(element_progressbar->GetLineColor()->GetRed(), element_progressbar->GetLineColor()->GetGreen(), element_progressbar->GetLineColor()->GetBlue(), element_progressbar->GetLineColor()->GetAlpha());
          GRP2DCOLOR_RGBA8  color    (element->GetColor()->GetRed(), element->GetColor()->GetGreen(), element->GetColor()->GetBlue(), element->GetColor()->GetAlpha());      
          GRP2DCOLOR_RGBA8  bkgcolor (element->GetBackgroundColor()->GetRed(), element->GetBackgroundColor()->GetGreen(), element->GetBackgroundColor()->GetBlue(), element->GetBackgroundColor()->GetAlpha());
          
          canvas->SetLineColor(&linecolor);
          canvas->SetFillColor(&bkgcolor);

          if(element->GetRoundRect())
            {
              canvas->RoundRect(element_progressrect->GetXPosition(), 
                                element_progressrect->GetYPosition(),
                                element_progressrect->GetXPosition() + element_progressrect->GetBoundaryLine()->width  , 
                                element_progressrect->GetYPosition() - element_progressrect->GetBoundaryLine()->height , element->GetRoundRect(), true);
            }
           else
            { 
              canvas->Rectangle(element_progressrect->GetXPosition(), 
                                element_progressrect->GetYPosition(),
                                element_progressrect->GetXPosition() + element_progressrect->GetBoundaryLine()->width  , 
                                element_progressrect->GetYPosition() - element_progressrect->GetBoundaryLine()->height , true);
            }

          double widthpercent   = element_progressrect->GetBoundaryLine()->width;
          double heightpercent  = element_progressrect->GetBoundaryLine()->height;  
                                    
          if(element_progressbar->ContinuousCycle_Is())
            {                
              XDWORD xpos_segment = 0;
              XDWORD ypos_segment = 0;
           
              switch(element_progressbar->GetDirection())
                {     
                  case UI_ELEMENT_TYPE_DIRECTION_UNKWOWN	  :
	                case UI_ELEMENT_TYPE_DIRECTION_HORIZONTAL : widthpercent   = (element_progressrect->GetBoundaryLine()->width  * element_progressbar->ContinuousCycle_GetSizeSegment()) / 100.0f;   
                                                              xpos_segment   = element_progressbar->ContinuousCycle_GetNSteps();
                                                              xpos_segment  += element_progressbar->ContinuousCycle_GetStepSegment();
                                                              element_progressbar->ContinuousCycle_SetNSteps(xpos_segment);        
                                                                                                                          
                                                              if(xpos_segment < widthpercent) 
                                                                {                                                                   
                                                                  widthpercent = xpos_segment;                                                                  
                                                                  xpos_segment = 0;                                                                                                                                                                                                                                                                                                                                           
                                                                }                                                                
                                                               else
                                                                {                                                                                                                                      
                                                                  if((xpos_segment + widthpercent) >= element_progressrect->GetBoundaryLine()->width) 
                                                                    {                                                                       
                                                                      widthpercent = (element_progressrect->GetBoundaryLine()->width - xpos_segment);                                                                       
                                                                      if(!widthpercent) 
                                                                        {
                                                                          xpos_segment = 0;
                                                                          element_progressbar->ContinuousCycle_SetNSteps(xpos_segment);                                                                          
                                                                        }

                                                                      xpos_segment -= (XDWORD)widthpercent;   
                                                                    }  
                                                                   else
                                                                    {
                                                                      xpos_segment -= (XDWORD)widthpercent;   
                                                                    }                                                                                                                                                                                                                       
                                                                }
                                                                 
                                                                                                                                                                                      
                                                              break;

	                case UI_ELEMENT_TYPE_DIRECTION_VERTICAL		: heightpercent  = (element_progressrect->GetBoundaryLine()->height * element_progressbar->ContinuousCycle_GetSizeSegment()) / 100.0f;   
                                                              ypos_segment   = element_progressbar->ContinuousCycle_GetNSteps();
                                                              ypos_segment  += element_progressbar->ContinuousCycle_GetStepSegment();
                                                              element_progressbar->ContinuousCycle_SetNSteps(ypos_segment);        
                                                              
                                                              if(ypos_segment < heightpercent) 
                                                                {                                                                   
                                                                  heightpercent = ypos_segment;                                                                  
                                                                  ypos_segment = 0;                                                                                                                                                                                                                                                                                                                                           
                                                                }                                                                
                                                               else
                                                                {                                                                                                                                      
                                                                  if((ypos_segment + heightpercent) >= element_progressrect->GetBoundaryLine()->height) 
                                                                    {                                                                       
                                                                      heightpercent = (element_progressrect->GetBoundaryLine()->height - ypos_segment);                                                                       
                                                                      if(!heightpercent) 
                                                                        {
                                                                          ypos_segment = 0;
                                                                          element_progressbar->ContinuousCycle_SetNSteps(ypos_segment);                                                                          
                                                                        }

                                                                      ypos_segment -= (XDWORD)heightpercent;   
                                                                    }  
                                                                   else
                                                                    {
                                                                      ypos_segment -= (XDWORD)heightpercent;   
                                                                    }                                                                                                                                                                                                                       
                                                                }
                                                                 
                                                              break;
                }

              canvas->SetFillColor(&color);

              if(element->GetRoundRect())
                {
                  canvas->RoundRect(element_progressrect->GetXPosition() + xpos_segment, 
                                    element_progressrect->GetYPosition() + ypos_segment,
                                    element_progressrect->GetXPosition() + xpos_segment + widthpercent    , 
                                    element_progressrect->GetYPosition() - (ypos_segment + heightpercent) , element->GetRoundRect(), true);                   

                }
               else
                {
                  canvas->Rectangle(element_progressrect->GetXPosition() + xpos_segment, 
                                    element_progressrect->GetYPosition() + ypos_segment,
                                    element_progressrect->GetXPosition() + xpos_segment + widthpercent    , 
                                    element_progressrect->GetYPosition() - (ypos_segment + heightpercent) , true);                   
                }
            }
           else
            {                
              switch(element_progressbar->GetDirection())
                {     
                  case UI_ELEMENT_TYPE_DIRECTION_UNKWOWN	  :
	                case UI_ELEMENT_TYPE_DIRECTION_HORIZONTAL : widthpercent   = (element_progressrect->GetBoundaryLine()->width  * element_progressbar->GetLevel()) / 100.0f;   break;
	                case UI_ELEMENT_TYPE_DIRECTION_VERTICAL		: heightpercent  = (element_progressrect->GetBoundaryLine()->height * element_progressbar->GetLevel()) / 100.0f;   break;
                }
               
              canvas->SetFillColor(&color);

              if(element->GetRoundRect())
                {
                  canvas->RoundRect(element_progressrect->GetXPosition(), 
                                    element_progressrect->GetYPosition(),
                                    element_progressrect->GetXPosition() + widthpercent   , 
                                    element_progressrect->GetYPosition() - heightpercent  , element->GetRoundRect(), true);   
                }
               else
                {
                  canvas->Rectangle(element_progressrect->GetXPosition(), 
                                    element_progressrect->GetYPosition(),
                                    element_progressrect->GetXPosition() + widthpercent   , 
                                    element_progressrect->GetYPosition() - heightpercent  , true);          
                }             
            } 

          if(element_text) Draw(element_text);  
            
        }  
    
      if(element_animation) Draw(element_animation);                    
    }

  PostDrawFunction(element, canvas, clip_rect, x_position, y_position); 
    
  if(element_progressbar->ContinuousCycle_Is()) 
    {
      if(element_progressbar->ContinuousCycle_GetXTimer()->GetMeasureMilliSeconds() > element_progressbar->ContinuousCycle_GetTimeStep())
        {
          element->SetMustReDraw(true);

          element_progressbar->ContinuousCycle_GetXTimer()->Reset();
        }
    }
  
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_SKINCANVAS::GetFontSize(XCHAR* text, XDWORD& width, XDWORD& height)
* @brief      GetFontSize
* @ingroup    USERINTERFACE
*
* @param[in]  text : 
* @param[in]  width : 
* @param[in]  height : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool UI_SKINCANVAS::GetFontSize(XCHAR* text, XDWORD& width, XDWORD& height)
{
  GRPCANVAS* canvas = GetCanvas();
  if(!canvas) return false;

  width   = (XDWORD)canvas->VectorFont_GetWidth(text);
  height  = (XDWORD)canvas->VectorFont_GetHeight(text);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_SKINCANVAS::SetFontSize(XDWORD size)
* @brief      SetFontSize
* @ingroup    USERINTERFACE
*
* @param[in]  size : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool UI_SKINCANVAS::SetFontSize(XDWORD size)
{
  GRPCANVAS* canvas = GetCanvas();
  if(!canvas) return false;

  canvas->Vectorfont_GetConfig()->SetSize(size);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_SKINCANVAS::DrawBackgroundColor(UI_ELEMENT* element, GRPCANVAS* canvas, double x_position, double y_position)
* @brief      DrawBackgroundColor
* @ingroup    USERINTERFACE
*
* @param[in]  element : 
* @param[in]  canvas : 
* @param[in]  x_position : 
* @param[in]  y_position : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool UI_SKINCANVAS::DrawBackgroundColor(UI_ELEMENT* element, GRPCANVAS* canvas, double x_position, double y_position)
{
  if(!element->GetBackgroundColor()->GetAlpha()) return false;

  GRP2DCOLOR_RGBA8  bkgcolor(element->GetBackgroundColor()->GetRed(),
                              element->GetBackgroundColor()->GetGreen(),
                              element->GetBackgroundColor()->GetBlue(),
                              element->GetBackgroundColor()->GetAlpha());


  canvas->SetLineWidth(0.0f);
  canvas->SetLineColor(&bkgcolor);
  canvas->SetFillColor(&bkgcolor);

  canvas->Rectangle(x_position,
                    y_position,
                    x_position  + element->GetBoundaryLine()->width   , 
                    y_position  - element->GetBoundaryLine()->height  , true);      

  return true;  
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_SKINCANVAS::PreDrawFunction(UI_ELEMENT* element, GRPCANVAS* canvas, XRECT& clip_rect, double& x_position, double& y_position, XDWORD edge)
* @brief      PreDrawFunction
* @ingroup    USERINTERFACE
*
* @param[in]  element : 
* @param[in]  canvas : 
* @param[in]  clip_rect : 
* @param[in]  x_position : 
* @param[in]  y_position : 
* @param[in]  edge : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool UI_SKINCANVAS::PreDrawFunction(UI_ELEMENT* element, GRPCANVAS* canvas, XRECT& clip_rect, double& x_position, double& y_position, XDWORD edge)
{
  if(!canvas) return false;

  x_position = element->GetXPosition();
  y_position = element->GetYPosition();

  if(element->GetFather()) GetAddPositionScrollSteps(element->GetFather(), x_position, y_position);

  element->SetXPositionWithScroll(x_position);
  element->SetYPositionWithScroll(y_position);
 
  bool createarea = false;
  if(element->MustReDraw()) 
    {
      createarea = true;
      if(GetRebuildAreaByElement(element)) createarea = false;          
    }

  if(createarea)
    {     
      //XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("Add area: level [%d] [%s] "), element->GetZLevel(), element->GetName()->Get());
         
      CreateRebuildArea(x_position - edge, 
                        y_position - element->GetBoundaryLine()->height - edge, 
                        element->GetBoundaryLine()->width   + (edge * 2),
                        element->GetBoundaryLine()->height  + (edge * 2), element);                    
    }

  if(!element->GetFather())
    {
      //if(dynamic_cast<UI_PROPERTY_SCROLLEABLE*>(element))
        {
          canvas->GetClipBox(clip_rect);      
          canvas->SetClipBox(x_position - 1 , 
                             y_position     ,
                             x_position + element->GetBoundaryLine()->width  , 
                             y_position - element->GetBoundaryLine()->height - 1);       
        }
    }
  
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_SKINCANVAS::PostDrawFunction(UI_ELEMENT* element, GRPCANVAS* canvas, XRECT& clip_rect, double x_position, double y_position)
* @brief      PostDrawFunction
* @ingroup    USERINTERFACE
*
* @param[in]  element : 
* @param[in]  canvas : 
* @param[in]  clip_rect : 
* @param[in]  x_position : 
* @param[in]  y_position : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool UI_SKINCANVAS::PostDrawFunction(UI_ELEMENT* element, GRPCANVAS* canvas, XRECT& clip_rect, double x_position, double y_position)
{  
  element->SetMustReDraw(false);

  if(!element->GetFather())
    {  
      //if(dynamic_cast<UI_PROPERTY_SCROLLEABLE*>(element))
        {
          canvas->SetClipBox(clip_rect);
        }
    }
  
  #ifdef USERINTERFACE_DEBUG 
	Debug_Draw(element, x_position, y_position);			
  #endif

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         double UI_SKINCANVAS::TextBox_SizeLine(UI_ELEMENT_TEXTBOX* element_textbox, GRPCANVAS* canvas, double x_position, double y_position, int nline, XSTRING& characterstr, XDWORD index_char, XVECTOR<UI_SKIN_TEXTBOX_PART*>& parts, XVECTOR<UI_SKIN_TEXTBOX_IMAGE*>& images)
* @brief      TextBox_SizeLine
* @ingroup    USERINTERFACE
*
* @param[in]  element_textbox : 
* @param[in]  canvas : 
* @param[in]  x_position : 
* @param[in]  y_position : 
* @param[in]  nline : 
* @param[in]  characterstr : 
* @param[in]  index_char : 
* @param[in]  parts : 
* @param[in]  images : 
* 
* @return     double : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
double UI_SKINCANVAS::TextBox_SizeLine(UI_ELEMENT_TEXTBOX* element_textbox, GRPCANVAS* canvas, double x_position, double y_position, int nline, XSTRING& characterstr, XDWORD index_char, XVECTOR<UI_SKIN_TEXTBOX_PART*>& parts, XVECTOR<UI_SKIN_TEXTBOX_IMAGE*>* images)
{
  XSTRING _characterstr;
  XDWORD  y_pos    = 0;    
  double  sizeline = 0;

  _characterstr = characterstr;
                               
  for(XDWORD c=0; c<parts.GetSize(); c++)
    {
      UI_SKIN_TEXTBOX_PART* textbox_part = parts.Get(c);
      if(textbox_part->GetLineNumber() == nline)
        {
          sizeline += canvas->VectorFont_GetWidth(textbox_part->GetText()->Get());    
          y_pos     = textbox_part->GetYPos();    
        }                                      
    }


  _characterstr.Add(element_textbox->GetText()->Get()[index_char]); 
  sizeline += canvas->VectorFont_GetWidth(_characterstr.Get());  

  if(images)
    {
      for(XDWORD c=0; c<images->GetSize(); c++)
        {
          UI_SKIN_TEXTBOX_IMAGE* textbox_image = images->Get(c);
          if(textbox_image)
            {
              bool isinbox = textbox_image->GetBoundaryLine()->IsWithin((XDWORD)(x_position + sizeline), (XDWORD)(y_pos));        
              if(isinbox) 
                {                         
                  sizeline += textbox_image->GetBoundaryLine()->width;
                }            
            }                                      
        }
    }

  return sizeline;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_SKINCANVAS::TextBox_GenerateLines(UI_ELEMENT_TEXTBOX* element_textbox, GRPCANVAS* canvas, double x_position, double y_position, XVECTOR<UI_SKIN_TEXTBOX_PART*>& parts, XVECTOR<UI_SKIN_TEXTBOX_IMAGE*>& images)
* @brief      TextBox_GenerateLines
* @ingroup    USERINTERFACE
*
* @param[in]  element_textbox : 
* @param[in]  canvas : 
* @param[in]  x_position : 
* @param[in]  y_position : 
* @param[in]  parts : 
* @param[in]  images : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool UI_SKINCANVAS::TextBox_GenerateLines(UI_ELEMENT_TEXTBOX* element_textbox, GRPCANVAS* canvas, double x_position, double y_position, XVECTOR<UI_SKIN_TEXTBOX_PART*>& parts, XVECTOR<UI_SKIN_TEXTBOX_IMAGE*>& images)
{
  double                  x_text_position = x_position;
  double                  y_text_position = y_position - element_textbox->GetBoundaryLine()->height + (double)canvas->VectorFont_GetHeight(__L("A"));  
  XDWORD                  index_char      = 0;  
  UI_COLOR                actual_color;
  XDWORD                  nline           = 1;
  double                  lineheight      = (canvas->VectorFont_GetHeight(__L("A")) + element_textbox->GetLineSpacing());
  XSTRING                 text;
  UI_SKIN_TEXTBOX_PART*   textbox_part    = NULL;
  bool                    outlimit        = false;
  bool                    newpart         = false;  

  text = element_textbox->GetText()->Get();
  if(text.IsEmpty()) return false;

  actual_color.CopyFrom(element_textbox->GetColor());

  textbox_part = new UI_SKIN_TEXTBOX_PART();
  if(!textbox_part) return false;
   
  textbox_part->SetLineNumber(nline);
  textbox_part->SetXPos((XDWORD)x_text_position);  
  textbox_part->SetYPos((XDWORD)y_text_position);  
  textbox_part->GetColor()->CopyFrom(&actual_color);
  
  while(index_char < text.GetSize() && (!outlimit))  
    {
      XCHAR character = text.Get()[index_char];

      switch(character)
        {
          case __C('\n')  : x_text_position  = x_position;      
                            y_text_position += lineheight;                
                            nline++;
                            newpart = true;     

                            index_char++;                            
                            break;

          case __C('!')   : { int indexstart = index_char+1;
                              if(text.Get()[indexstart] == __C('['))
                                {                
                                  int type;
                
                                  int indexend = text.FindCharacter(__C(']'), indexstart);
                                  if(indexend != XSTRING_NOTFOUND)
                                    {                                                                      
                                      XCHAR*    keywords[] = {  __L("COLOR") ,
                                                                __L("IMAGE") ,
                                                                __L("END") ,
                                                             };
                                      XSTRING   keyword;
                                      bool      found_keyword = false;  
                                                                                    
                                      text.Copy(indexstart+1, indexend, keyword);    

                                      for(type=0; type<(sizeof(keywords)/sizeof(XCHAR*)); type++)
                                        {
                                          int keywordindex = keyword.Find(keywords[type], true);
                                          if(!keywordindex)
                                            {
                                              XSTRING keyword_params;
                                              XSTRING string;        
                                              
                                              found_keyword = true;  

                                              string = keywords[type];
                                              keywordindex += string.GetSize()+1;

                                              keyword.Copy(keywordindex, keyword_params);
                                              keyword_params.DeleteCharacter(__C(' '));

                                              switch(type)
                                                {
                                                  case  0 : actual_color.SetFromString(keyword_params);
                                                            newpart = true;
                                                            break;      

                                                  case  1 : { UI_SKIN_TEXTBOX_IMAGE* image = new UI_SKIN_TEXTBOX_IMAGE();
                                                              if(image)
                                                                {
                                                                  image->GetName()->Set(keyword_params);                                                                  

                                                                  UI_ANIMATION* animation = GEN_USERINTERFACE.GetOrAddAnimationCache(__L(""), image->GetName()->Get());
                                                                  if(animation)
                                                                    {
                                                                      image->SetAnimation(animation); 
                                                                      
                                                                      image->GetBoundaryLine()->x       = x_text_position;
                                                                      image->GetBoundaryLine()->y       = y_text_position - (int)(canvas->VectorFont_GetHeight(__L("A"))); 
                                                                      image->GetBoundaryLine()->width   = animation->GetBitmap()->GetWidth();
                                                                      image->GetBoundaryLine()->height  = animation->GetBitmap()->GetHeight(); // + lineheight; // + (int)(canvas->VectorFont_GetHeight(__L("A"))); 
                                                                      
                                                                      images.Add(image);                                                                     
                                                                    }
                                                                }    
                                                            }
                                                            break;        

                                                  case  2 : for(int d=0; d<(sizeof(keywords)/sizeof(XCHAR*)); d++)
                                                              {
                                                                if(!keyword_params.Compare(keywords[d], true))
                                                                  {
                                                                    switch(d)
                                                                      {
                                                                        case  0 : actual_color.CopyFrom(element_textbox->GetColor());
                                                                                  newpart = true;
                                                                                  break;

                                                                        case  1 : break;  
                                                                      }                                                                    
                                                                  }
                                                              }
                                                            break;                                                          
                                                }
                                              
                                              break;
                                            }
                                        }
                                                                  
                                      if(found_keyword) 
                                        {    
                                          text.DeleteCharacters(index_char, (keyword.GetSize() + 3));                                         
                                          
                                                        
                                          if(type == 1 && (indexstart > 1))
                                            {
                                              indexstart = -2;

                                              if(text.Get()[indexstart] != __C(' '))  
                                                {
                                                  text.Insert(__L(" "), indexstart);                                                                                                  
                                                }
                                            }
                                            
                                          break;
                                        }
                                    }
                                } 
                            }

                  default : { XSTRING characterstr;                              
                              characterstr.Add(character);
                              
                              x_text_position += (canvas->VectorFont_GetWidth(characterstr.Get())); 

                              UI_BOUNDARYLINE   boundaryline;
                              bool              isinbox    = false;
                              bool              isinimage  = false;  
                              double            imagewidth = 0.0f;
                                
                              boundaryline.x      = element_textbox->GetXPosition();
                              boundaryline.y      = element_textbox->GetYPosition();
                              boundaryline.width  = element_textbox->GetBoundaryLine()->width;
                              boundaryline.height = element_textbox->GetBoundaryLine()->height;

                              isinbox = boundaryline.IsWithin((XDWORD)(x_text_position), (XDWORD)(y_text_position));                                                           
                              if(isinbox)
                                {
                                  for(XDWORD c=0; c<images.GetSize(); c++)
                                    {                                      
                                      UI_SKIN_TEXTBOX_IMAGE* textbox_image = images.Get(c);
                                      if(textbox_image)
                                        {                                                                            
                                          isinimage = boundaryline.IsWithin((XDWORD)(x_text_position), (XDWORD)(y_text_position - textbox_image->GetBoundaryLine()->height - (int)(canvas->VectorFont_GetHeight(__L("A"))) + 1));        
                                          if(isinimage) 
                                            {
                                              textbox_image->GetLineNumbers()->Add(nline);
                                              imagewidth = textbox_image->GetBoundaryLine()->width;
                                              break;                                          
                                            }
                                        }
                                    }        
                                }
                                      
                              if(isinbox)
                                {      
                                  if(isinimage)
                                    {
                                      if(element_textbox->IsWordClipping())
                                        {
                                          if(character != __C(' '))
                                            {
                                              while(!textbox_part->GetText()->IsEmpty())
                                                {  
                                                  if(textbox_part->GetText()->Get()[textbox_part->GetText()->GetSize()-1] == __C(' ')) break;
                                                  textbox_part->GetText()->DeleteLastCharacter();
                                                  index_char--;
                                                }                                                 
                                            }
                                        }

                                      x_text_position += imagewidth;    
                                      newpart          = true;                                          
                                    }
                                   else     
                                    {                                        
                                      textbox_part->GetText()->Add(characterstr);
                                      index_char++;
                                    }
                                }
                               else
                                {  
                                  if(element_textbox->IsWordClipping())
                                    {      
                                      while(!textbox_part->GetText()->IsEmpty())
                                        {
                                          if(textbox_part->GetText()->Get()[textbox_part->GetText()->GetSize()-1] == __C(' ')) break;
                                          textbox_part->GetText()->DeleteLastCharacter();
                                          index_char--;
                                        }          
                                    }
                                    
                                  x_text_position  = x_position;      
                                  y_text_position += lineheight; 
                                  if(y_text_position > (y_position + lineheight)) 
                                    {
                                      outlimit = true;
                                      break;
                                    }  
               
                                  nline++;

                                  if(!textbox_part->GetText()->IsEmpty()) 
                                    {
                                      newpart = true;                                      
                                    }
                                   else
                                    {
                                      textbox_part->SetLineNumber(nline);
                                      textbox_part->SetXPos((XDWORD)x_text_position);  
                                      textbox_part->SetYPos((XDWORD)y_text_position);  
                                    }
                                }                               
                            }
                            break;
        }


      if(newpart)
        {
          if(!textbox_part->GetText()->IsEmpty())    
            {
              textbox_part->SetWidth((XDWORD)canvas->VectorFont_GetWidth(textbox_part->GetText()->Get()));
              textbox_part->SetHeight((XDWORD)canvas->VectorFont_GetHeight(__L("A")));
              parts.Add(textbox_part);  

              textbox_part = new UI_SKIN_TEXTBOX_PART();
              if(!textbox_part) return false;
            }
   
          textbox_part->SetLineNumber(nline);
          textbox_part->SetXPos((XDWORD)x_text_position);  
          textbox_part->SetYPos((XDWORD)y_text_position);  
          textbox_part->GetColor()->CopyFrom(&actual_color);

          newpart = false;
        }
    }

  if(outlimit)
    {
      delete textbox_part;
      textbox_part = NULL;
    }
   else
    {
      parts.Add(textbox_part);  
    }

  XVECTOR<UI_SKIN_TEXTBOX_PART*>    checkparts;
  XVECTOR<UI_SKIN_TEXTBOX_IMAGE*>   checkimages;
  XDWORD                            maxnlines   = 0;

  for(XDWORD c=0; c<parts.GetSize(); c++)
    {
      UI_SKIN_TEXTBOX_PART* textbox_part = parts.Get(c);
      if(textbox_part) maxnlines = __MAX(maxnlines, textbox_part->GetLineNumber());  
    }

  for(XDWORD nl=0; nl<maxnlines; nl++)
    {     
      for(XDWORD p=0; p<parts.GetSize(); p++)
        {          
          UI_SKIN_TEXTBOX_PART* textbox_part = parts.Get(p);        
          if(textbox_part) 
            {
              if(textbox_part->GetLineNumber() == nl+1) checkparts.Add(textbox_part);
            }
        }

      for(XDWORD p=0; p<images.GetSize(); p++)
        {          
          UI_SKIN_TEXTBOX_IMAGE* textbox_image = images.Get(p);        
          if(textbox_image) 
            {
              if(textbox_image->IsInLine(nl+1))  checkimages.Add(textbox_image);
            }
        }

      if(checkparts.GetSize())
        {  
          switch(element_textbox->GetTextAlignment())
            {
              /*                                      
                                      default   :
              case UI_ELEMENT_TYPE_ALIGN_LEFT	  : textbox_part->SetXPos((XDWORD)x_text_position);
                                                  break;										

              case UI_ELEMENT_TYPE_ALIGN_RIGHT	:	{ XDWORD shift = (XDWORD)(element_textbox->GetBoundaryLine()->width - canvas->VectorFont_GetWidth(characterstr.Get()));
                                                    textbox_part->SetXPos((XDWORD)(x_text_position) + shift);
                                                  }
                                                  break;																				                  

              case UI_ELEMENT_TYPE_ALIGN_CENTER	: { XDWORD shift = (XDWORD)(element_textbox->GetBoundaryLine()->width - canvas->VectorFont_GetWidth(characterstr.Get()))/2;
                                                    textbox_part->SetXPos((XDWORD)(x_text_position) + shift);
                                                  }
                                                  break;								
              */  


                                      default   : break;

              case UI_ELEMENT_TYPE_ALIGN_LEFT	  : break;										

              case UI_ELEMENT_TYPE_ALIGN_RIGHT	:	break;																				                  

              case UI_ELEMENT_TYPE_ALIGN_CENTER	: if(checkimages.GetSize())
                                                    {
                                                      XDWORD first_size = 0;

                                                      UI_SKIN_TEXTBOX_IMAGE* first_image = checkimages.Get(0);                                                                  
                                                      if(first_image)
                                                        {
                                                          for(XDWORD p=0; p<checkparts.GetSize(); p++)
                                                            {          
                                                              UI_SKIN_TEXTBOX_PART* textbox_part = checkparts.Get(p);        
                                                              if(textbox_part)
                                                                {
                                                                  if(((textbox_part->GetXPos() + textbox_part->GetWidth()) <= first_image->GetBoundaryLine()->x) &&
                                                                     (textbox_part->GetXPos() >= (first_image->GetBoundaryLine()->x + first_image->GetBoundaryLine()->width)))
                                                                    {
                                                                      first_size += textbox_part->GetWidth();
                                                                    }
                                                                }  
                                                            }

                                                          XDWORD shift = (XDWORD)(first_image->GetBoundaryLine()->x - element_textbox->GetBoundaryLine()->x - first_size);    
                                                          
                                                          for(XDWORD p=0; p<checkparts.GetSize(); p++)
                                                            {          
                                                              UI_SKIN_TEXTBOX_PART* textbox_part = checkparts.Get(p);        
                                                              if(textbox_part)
                                                                {
                                                                  if((textbox_part->GetXPos() + textbox_part->GetWidth()) <= first_image->GetBoundaryLine()->x)
                                                                    {
                                                                      textbox_part->SetXPos(textbox_part->GetXPos() + first_size);
                                                                    }
                                                                }  
                                                            }

                                                        }
                                                    }
                                                   else
                                                    {
                                                      XDWORD sizealltext = 0;
                                                      for(XDWORD p=0; p<checkparts.GetSize(); p++)
                                                        {          
                                                           UI_SKIN_TEXTBOX_PART* textbox_part = checkparts.Get(p);        
                                                           if(textbox_part) sizealltext += textbox_part->GetWidth();
                                                        }
                                          
                                                      XDWORD shift = (XDWORD)(element_textbox->GetBoundaryLine()->width - sizealltext)/2;    

                                                      for(XDWORD p=0; p<checkparts.GetSize(); p++)
                                                        {          
                                                           UI_SKIN_TEXTBOX_PART* textbox_part = checkparts.Get(p);        
                                                           if(textbox_part) textbox_part->SetXPos(textbox_part->GetXPos()+shift); 
                                                        }                                                             
                                                    }       
                                                  break;										           
            }
            
  
        }

      checkparts.DeleteAll();
      checkimages.DeleteAll();
                 
    }
  

  return true;
}


#ifdef USERINTERFACE_DEBUG 

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_SKINCANVAS::Debug_Draw(UI_ELEMENT* element, double x_position, double y_position)
* @brief      Debug_Draw
* @ingroup    USERINTERFACE
*
* @param[in]  element : 
* @param[in]  x_position : 
* @param[in]  y_position : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool UI_SKINCANVAS::Debug_Draw(UI_ELEMENT* element, double x_position, double y_position)
{  
  GRPCANVAS* canvas = GetCanvas();
  if(!canvas) return false;
  
  GRP2DCOLOR_RGBA8  colorred(255, 0, 0);
  GRP2DCOLOR_RGBA8  colorblue(0, 0, 255);
 
  canvas->SetLineWidth(1.0f);
  canvas->SetLineColor(&colorblue);  
  canvas->Circle(x_position, y_position, 5);               

  canvas->SetLineWidth(1.0f);
  canvas->SetLineColor(&colorred);
  canvas->Rectangle(x_position ,  
                    y_position ,
                    x_position + (element->GetBoundaryLine()->width), 
                    y_position - (element->GetBoundaryLine()->height));
  return true;
}
#endif


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void UI_SKINCANVAS::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    USERINTERFACE
*
* ---------------------------------------------------------------------------------------------------------------------*/
void UI_SKINCANVAS::Clean()
{
  fontsize = 0;
  screen   = NULL;
}


#pragma endregion


#pragma endregion

