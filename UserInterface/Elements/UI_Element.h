/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       UI_Element.h
* 
* @class      UI_ELEMENT
* @brief      User Interface Element class
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

#ifndef _UI_ELEMENT_H_
#define _UI_ELEMENT_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "XPublisher.h"
#include "XSubject.h"

#include "UI_Color.h"
#include "UI_BoundaryLine.h"

#pragma endregion


/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/
#pragma region DEFINES_ENUMS


enum UI_ELEMENT_TYPE
{
	UI_ELEMENT_TYPE_UNKNOWN												= 0	,	
	
	UI_ELEMENT_TYPE_TEXT															,	
	UI_ELEMENT_TYPE_TEXTBOX											  		,	
	UI_ELEMENT_TYPE_IMAGE															,	
	UI_ELEMENT_TYPE_ANIMATION													,		
	UI_ELEMENT_TYPE_OPTION														,	
	UI_ELEMENT_TYPE_MULTIOPTION												,									
	UI_ELEMENT_TYPE_BUTTON														,		
	UI_ELEMENT_TYPE_CHECKBOX													,		
	UI_ELEMENT_TYPE_EDITTEXT													,		
	UI_ELEMENT_TYPE_FORM															,
	UI_ELEMENT_TYPE_MENU															,				
	UI_ELEMENT_TYPE_LISTBOX														,		
	UI_ELEMENT_TYPE_PROGRESSBAR												,	
	UI_ELEMENT_TYPE_SCROLL															
};				


enum UI_ELEMENT_TYPE_ALIGN
{
  UI_ELEMENT_TYPE_ALIGN_NOTDETERMINED	   = -1000000 ,
  UI_ELEMENT_TYPE_ALIGN_LEFT												,
  UI_ELEMENT_TYPE_ALIGN_RIGHT												,
  UI_ELEMENT_TYPE_ALIGN_UP													,
  UI_ELEMENT_TYPE_ALIGN_DOWN												,
  UI_ELEMENT_TYPE_ALIGN_CENTER											,
	UI_ELEMENT_TYPE_ALIGN_MAX													,
	UI_ELEMENT_TYPE_ALIGN_AUTO												,
};


enum UI_ELEMENT_TYPE_DIRECTION
{
	UI_ELEMENT_TYPE_DIRECTION_UNKWOWN							= 0	,
	UI_ELEMENT_TYPE_DIRECTION_HORIZONTAL							,
	UI_ELEMENT_TYPE_DIRECTION_VERTICAL								,
};


enum UI_ELEMENT_TRANSITION_STATE_SHOW	
{
	UI_ELEMENT_TRANSITION_STATE_SHOW_NONE					= 0 ,
	UI_ELEMENT_TRANSITION_STATE_SHOW_TOSHOW						,
	UI_ELEMENT_TRANSITION_STATE_SHOW_TOHIDE						,
};

#define UI_ELEMENT_MARGIN_MAX										  4	


#pragma endregion


/*---- CLASS ---------------------------------------------------------------------------------------------------------*/
#pragma region CLASS


class XTIMER;
class UI_ELEMENT_SCROLL;


class UI_ELEMENT : public XSUBJECT 
{
  public:
																					UI_ELEMENT									();
    virtual															 ~UI_ELEMENT									();

		XSTRING*															GetName											();

		UI_ELEMENT_TYPE												GetType											();
		void																	SetType											(UI_ELEMENT_TYPE type);

		XSTRING*															GetTypeString								();

		UI_ELEMENT*														GetFather										();	
		void																	SetFather										(UI_ELEMENT* father);	

		bool																	IsDetached									();	
		void																	SetIsDetached								(bool isdetached);	
		
		UI_COLOR*															GetColor										();	
		UI_COLOR*															GetBackgroundColor					();	
		
		double																GetXPosition								();		
		bool																	SetXPosition								(double x_position);		

		double																GetYPosition								();		
		bool																	SetYPosition								(double y_position);		

		XDWORD																GetZLevel										();		
		bool																	SetZLevel										(XDWORD z_level);		
	
		UI_ELEMENT_TYPE_DIRECTION							GetDirection								();
		bool																	SetDirection								(UI_ELEMENT_TYPE_DIRECTION direction);

		double																GetXPositionWithScroll			();		
		bool																	SetXPositionWithScroll			(double x_positionwithscroll);		

		double																GetYPositionWithScroll			();		
		bool																	SetYPositionWithScroll			(double y_positionwithscroll);		

		UI_BOUNDARYLINE*											GetBoundaryLine							();
		void																	SetBoundaryLine							(UI_BOUNDARYLINE& boundaryline);
		
		double																GetMargin                   (UI_ELEMENT_TYPE_ALIGN position);
		void																	SetMargin                   (UI_ELEMENT_TYPE_ALIGN position, double value);

		bool																	IsActive										();
		void																	SetActive										(bool isactive);

		bool																	IsPreSelect									();
		void																	SetPreSelect								(bool ispreselect);

		bool																	IsSelected									();
		void																	SetSelected									(bool isselected);		
		
		bool																	IsVisible										();
		void																	SetVisible									(bool isvisible);		

		XDWORD																GetRoundRect								();
    void																	SetRoundRect								(XDWORD roundrect);

		XDWORD																IsBlinking									();
		bool																	SetBlink										(XDWORD timeblink);
		bool																	GetStateBlink								();
		bool																	SwicthStateBlink					  ();
		XTIMER*																GetTimerBlink								();	

		UI_ELEMENT_TRANSITION_STATE_SHOW			GetTransitionStateShow			();
		void																	SetTransitionStateShow			(UI_ELEMENT_TRANSITION_STATE_SHOW	 transitionstateshow);

		bool																	HasScroll										();
		void																	SetHasScroll								(bool hasscroll);

		XSTRING*															GetExtra										();	

		bool																	MustReDraw									();
		void																	SetMustReDraw								(bool mustredraw);
			
		XVECTOR<UI_ELEMENT*>*									GetComposeElements					();
		bool																	DeleteAllComposeElements		();

		bool																	SetToRedraw									(bool recursive);

  private:

		void																	Clean												();

		XSTRING																name;
		UI_ELEMENT_TYPE												type;
		XSTRING																type_string;
		
		UI_ELEMENT*														father;	
		bool																	isdetached;
		
		UI_COLOR															color;	
		UI_COLOR															backgroundcolor;	

		double																x_position;
		double																y_position;

		XDWORD																z_level;

		UI_ELEMENT_TYPE_DIRECTION							direction;

		double																x_positionwithscroll;
		double																y_positionwithscroll;

		UI_BOUNDARYLINE												boundaryline;

		double																margin[UI_ELEMENT_MARGIN_MAX];			

		bool																	isactive;
		bool																	ispreselect;		
		bool																	isselected;
		bool																	isvisible;

		XDWORD																roundrect;	

		XDWORD																blink_time;
		bool																	blink_state;
		XTIMER*																blink_xtimer;	
		XDWORD																blink_nchanges;		

		UI_ELEMENT_TRANSITION_STATE_SHOW			transitionstateshow;

		bool																	hasscroll;

		bool																	mustredraw;

		XSTRING																extra;
		
		XVECTOR<UI_ELEMENT*>									compose_elements;
};


#pragma endregion


/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/
#pragma region FUNCTIONS_PROTOTYPES


#pragma endregion


#endif

