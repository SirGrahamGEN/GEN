/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       UI_SkinCanvas.h
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

#ifndef _UI_SKINCANVAS_H_
#define _UI_SKINCANVAS_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "XRect.h"
#include "XPath.h"

#include "GRP2DRebuildAreas.h"

#include "UI_Element.h"
#include "UI_Skin.h"

#pragma endregion


/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/
#pragma region DEFINES_ENUMS


enum UI_SKINCANVAS_TYPE
{
  UI_SKINCANVAS_TYPE_UNKNOWN          =  0  ,
  UI_SKINCANVAS_TYPE_FLAT                   ,
};


#define UI_SKINCANVAS_NAME_UNKNOWN					__L("")
#define UI_SKINCANVAS_NAME_FLAT							__L("FLAT")


#define UI_SKINCANVAS_PRESELECT_MAXEDGE		4
#define UI_SKINCANVAS_EDIT_MAXEDGE				10	


#pragma endregion


/*---- CLASS ---------------------------------------------------------------------------------------------------------*/
#pragma region CLASS


class GRPSCREEN;
class GRPVIEWPORT;
class GRPCANVAS;
class UI_LAYOUT;
class UI_ELEMENT_TEXTBOX;


class UI_SKINCANVAS_REBUILDAREAS : public GRP2DREBUILDAREAS
{
	public:
																		  UI_SKINCANVAS_REBUILDAREAS					(GRPSCREEN* screen, int viewportindex = 0);
    virtual													 ~UI_SKINCANVAS_REBUILDAREAS					();

		bool															RebuildAllAreas											();    
		bool															RebuildAllAreas											(UI_LAYOUT* layout);
		bool															RebuildAllAreas											(UI_ELEMENT* element);

    bool                              CreateRebuildArea										(double x, double y, double width, double height, UI_ELEMENT* element);

    GRPBITMAP*												GetBitmap														(double x, double y, double width, double height);
    void															PutBitmapNoAlpha										(double x, double y, GRPBITMAP* bitmap);
  
		GRP2DREBUILDAREA*									GetRebuildAreaByElement							(UI_ELEMENT* element);					

	private:

		void															Clean																();		

		GRPSCREEN*												screen;
		int																viewportindex;
		GRPCANVAS*												canvas; 		
};


class UI_SKINCANVAS : public UI_SKIN, public UI_SKINCANVAS_REBUILDAREAS
{
  public:
																		  UI_SKINCANVAS												(GRPSCREEN* screen, int viewportindex = 0);
    virtual													 ~UI_SKINCANVAS												();

		GRPSCREEN*                        GetScreen														(); 
		GRPCANVAS*                        GetCanvas														(); 
		
		bool															LoadFonts														();

		bool															GetFatherSize												(UI_ELEMENT* element, double& width, double& height);
		double														GetPositionWithoutDefine						(double position);
		bool															SetAroundFromSubElements						(UI_ELEMENT* element);
		bool															AddPositionSubElements							(UI_ELEMENT* element);
		bool															CalculePosition											(UI_ELEMENT* element, double fatherwidth, double fatherheight, bool adjustsizemargin = false);

    double														GetWithString                       (XCHAR* string, XDWORD sizefont = 12);  
    double														GetHeightString                     (XCHAR* string, XDWORD sizefont = 12);  
				
	  virtual bool                      CalculateBoundaryLine_Scroll        (UI_ELEMENT* element, bool adjustsizemargin = false);
	  virtual bool                      CalculateBoundaryLine_Text		      (UI_ELEMENT* element, bool adjustsizemargin = false);
	  virtual bool                      CalculateBoundaryLine_TextBox				(UI_ELEMENT* element, bool adjustsizemargin = false);
	  virtual bool                      CalculateBoundaryLine_Image   	    (UI_ELEMENT* element, bool adjustsizemargin = false);
		virtual bool                      CalculateBoundaryLine_Animation	    (UI_ELEMENT* element, bool adjustsizemargin = false);
		virtual bool                      CalculateBoundaryLine_Option		    (UI_ELEMENT* element, bool adjustsizemargin = false);
		virtual bool                      CalculateBoundaryLine_MultiOption	  (UI_ELEMENT* element, bool adjustsizemargin = false);
	  virtual bool                      CalculateBoundaryLine_Button		    (UI_ELEMENT* element, bool adjustsizemargin = false);
		virtual bool                      CalculateBoundaryLine_CheckBox		  (UI_ELEMENT* element, bool adjustsizemargin = false);
		virtual bool                      CalculateBoundaryLine_EditText		  (UI_ELEMENT* element, bool adjustsizemargin = false);	  
	  virtual bool                      CalculateBoundaryLine_Form          (UI_ELEMENT* element, bool adjustsizemargin = false);
		virtual bool                      CalculateBoundaryLine_Menu				  (UI_ELEMENT* element, bool adjustsizemargin = false);
		virtual bool                      CalculateBoundaryLine_ListBox			  (UI_ELEMENT* element, bool adjustsizemargin = false);
		virtual bool                      CalculateBoundaryLine_ProgressBar	  (UI_ELEMENT* element, bool adjustsizemargin = false);

		virtual bool                      SetElementPosition                  (UI_ELEMENT* element, double x_position, double y_position);
		        
	  virtual bool                      Draw_Scroll													(UI_ELEMENT* element);
	  virtual bool                      Draw_Text														(UI_ELEMENT* element);
		virtual bool											Draw_TextBox												(UI_ELEMENT* element);
	  virtual bool                      Draw_Image  												(UI_ELEMENT* element);
		virtual bool                      Draw_Animation											(UI_ELEMENT* element);
		virtual bool                      Draw_Option													(UI_ELEMENT* element);
		virtual bool                      Draw_MultiOption										(UI_ELEMENT* element);
	  virtual bool                      Draw_Button													(UI_ELEMENT* element);
		virtual bool											Draw_CheckBox												(UI_ELEMENT* element);
		virtual bool											Draw_EditText												(UI_ELEMENT* element);		
	  virtual bool                      Draw_Form														(UI_ELEMENT* element);
		virtual bool											Draw_Menu														(UI_ELEMENT* element);
		virtual bool											Draw_ListBox												(UI_ELEMENT* element);
		virtual bool											Draw_ProgressBar										(UI_ELEMENT* element);

  protected: 

		bool															GetFontSize													(XCHAR* text, XDWORD& width, XDWORD& height);
		bool															SetFontSize													(XDWORD size);

		bool															DrawBackgroundColor									(UI_ELEMENT* element, GRPCANVAS* canvas, double x_position, double y_position);

		bool															PreDrawFunction											(UI_ELEMENT* element, GRPCANVAS* canvas, XRECT& clip_rect, double& x_position, double& y_position, XDWORD edge = 5);
		bool															PostDrawFunction										(UI_ELEMENT* element, GRPCANVAS* canvas, XRECT& clip_rect, double  x_position, double  y_position);
			
		double														TextBox_SizeLine										(UI_ELEMENT_TEXTBOX* element_textbox, GRPCANVAS* canvas, double x_position, double y_position, int nline, XSTRING& characterstr, XDWORD index_char, XVECTOR<UI_SKIN_TEXTBOX_PART*>& parts);
		bool															TextBox_GenerateLines								(UI_ELEMENT_TEXTBOX* element, GRPCANVAS* canvas, double x_position, double y_position, XVECTOR<UI_SKIN_TEXTBOX_PART*>& parts); 

		#ifdef USERINTERFACE_DEBUG
		bool															Debug_Draw													(UI_ELEMENT* element, double x_position, double y_position);	
		#endif

		XDWORD														fontsize;
    GRPSCREEN*												screen;
	  int																viewportindex;
		XPATH															fontpathfile;

	private:

		void															Clean																();		
};


#pragma endregion


/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/
#pragma region FUNCTIONS_PROTOTYPES


#pragma endregion


#endif

