/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       UI_Manager.h
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

#ifndef _UI_MANAGER_H_
#define _UI_MANAGER_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "XVector.h"
#include "XPath.h"
#include "XObserver.h"
#include "XSubject.h"
#include "XFileXML.h"
#include "XString.h"
#include "XFileZIP.h"

#include "GRPProperties.h"

#include "UI_XEvent.h"
#include "UI_Element.h"
#include "UI_Skin.h"
#include "UI_Layout.h"

#pragma endregion


/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/
#pragma region DEFINES_ENUMS

#define UI_MANAGER_LAYOUT_NOTFOUND          -1
#define UI_MANAGER_LAYOUT_COMMON            __L("COMMON")
#define UI_MANAGER_LAYOUT_TEXT_INI          __L("#[")
#define UI_MANAGER_LAYOUT_TEXT_END          __L("]")
#define UI_MANAGER_LAYOUT_TEXT_TRANSLATE    __L("TRANSLATE_")

#pragma endregion


/*---- CLASS ---------------------------------------------------------------------------------------------------------*/
#pragma region CLASS


class GRPSCREEN;
class GRPCONTEXT;
class GRPCANVAS;
class INPCURSORMOTION;
class UI_ANIMATION;
class UI_ELEMENT_TEXT;
class UI_ELEMENT_FORM;
class UI_VIRTUALKEYBOARD;


class UI_MANAGER : public XOBSERVER, public XSUBJECT
{
  public:

    static bool                     GetIsInstanced                            ();
    static UI_MANAGER&              GetInstance                               ();
    static bool                     DelInstance                               ();

    bool                            Load                                      (XPATH& pathfile, GRPSCREEN* screen, int viewportindex = 0);
    bool                            LoadLayout                                (XPATH& pathfile, GRPSCREEN* screen, int viewportindex = 0);
  
    bool                            IsZippedFile                              (); 
    XPATH*                          GetUnzipPathFile                          (); 
    XFILEUNZIP*                     GetUnzipFile                              ();
    bool                            DeleteTemporalUnZipFile                   (XPATH& pathfile);
    bool                            CloseUnZipFile                            ();
    
    bool                            Layouts_Add                               (UI_LAYOUT* layout);
    XVECTOR<UI_LAYOUT*>*            Layouts_GetAll                            ();
    UI_LAYOUT*                      Layouts_Get                               (int index);
    UI_LAYOUT*                      Layouts_Get                               (XCHAR* name);
    UI_LAYOUT*                      Layouts_Get                               (XSTRING& tname);
    bool                            Layouts_DeleteAll                         ();     
    UI_LAYOUT*                      Layouts_GetCommonLayout                   ();
           
    bool                            Layout_PutBackground                      (XCHAR* layoutname);    
    bool                            Layout_PutBackgroundColor                 (XCHAR* layoutname);    
    bool                            Layout_PutBackgroundBitmap                (XCHAR* layoutname);    

    bool                            Layout_PutBackground                      (bool scale = false);    
    bool                            Layout_PutBackgroundColor                 ();    
    bool                            Layout_PutBackgroundBitmap                (bool scale = false);    

    bool                            Update                                    (UI_LAYOUT* layout);
    bool                            Update                                    (XCHAR* layoutname);
    bool                            Update                                    ();
        
    UI_ELEMENT*                     Element_Get                               (XCHAR* layoutname, XCHAR* name, UI_ELEMENT_TYPE type = UI_ELEMENT_TYPE_UNKNOWN);  
    UI_ELEMENT*                     Element_Get                               (XCHAR* layoutname, XSTRING& name, UI_ELEMENT_TYPE type = UI_ELEMENT_TYPE_UNKNOWN);       
    UI_ELEMENT*                     Element_Get                               (XCHAR* name, UI_ELEMENT_TYPE type);
    UI_ELEMENT*                     Element_Get                               (XSTRING& name, UI_ELEMENT_TYPE type);

    UI_LAYOUT*                      Element_GetLayout                         (UI_ELEMENT* element);
    UI_LAYOUT*                      Element_GetLayout                         (XCHAR* name, UI_ELEMENT_TYPE type = UI_ELEMENT_TYPE_UNKNOWN);    
    UI_LAYOUT*                      Element_GetLayout                         (XSTRING& name, UI_ELEMENT_TYPE type = UI_ELEMENT_TYPE_UNKNOWN);    

    bool                            Element_PutToLastPositionLayout           (UI_ELEMENT* element);      
    bool                            Element_PutToLastPositionLayout           (XCHAR* name, UI_ELEMENT_TYPE type = UI_ELEMENT_TYPE_UNKNOWN);      
    bool                            Element_PutToLastPositionLayout           (XSTRING& name, UI_ELEMENT_TYPE type = UI_ELEMENT_TYPE_UNKNOWN);    
    
    bool                            Element_SetModal                          (UI_ELEMENT* element_modal);  

    bool                            Elements_SetToRedraw                      (); 
    bool                            Elements_SetToRedraw                      (UI_ELEMENT* element, bool recursive = true);

    bool                            Elements_RebuildDrawAreas                 ();
    bool                            Elements_RebuildDrawAreas                 (UI_LAYOUT* layout); 
    bool                            Elements_RebuildDrawAreas                 (UI_LAYOUT* layout, UI_ELEMENT* element);
    bool                            Elements_RebuildDrawAreas                 (XCHAR* layoutname); 
    bool                            Elements_RebuildDrawAreas                 (XCHAR* layoutname, UI_ELEMENT* element);
    
    int                             GetOutputTextChangeID                     (XSTRING* text, int start, XSTRING& value);
    UI_ANIMATION*                   GetOrAddAnimationCache                    (UI_SKIN_DRAWMODE drawmode, GRPPROPERTYMODE grppropertymode, XCHAR* name, XCHAR* resource);
    
    bool                            SetLevelAuto                              (UI_ELEMENT* element, UI_ELEMENT* father, XDWORD addlevel = 0);

    bool                            SetPreselectElement                       (UI_ELEMENT* element = NULL);
    bool                            ResetPreselect                            ();
      
    bool                            SendEvent                                 (UI_XEVENT_TYPE event, ...);
    bool                            ChangeAutomaticTextElementValue           (UI_ELEMENT* element, XSTRING* maskvalue, XSTRING* maskresolved);
    bool                            ChangeTextElementValue                    (UI_ELEMENT* element, XSTRING* text, XSTRING& value);
    
    bool                            ChangeTextElementValue                    (UI_LAYOUT* layout);
    bool                            ChangeTextElementValue                    (UI_LAYOUT* layout, UI_ELEMENT* element);

    
    bool                            SubscribeInputEvents                      (bool active);    
    bool                            SubscribeOutputEvents                     (bool active, XOBSERVER* observer, XSUBJECT* subject); 

    bool                            CreaterVirtualKeyboard                    (UI_LAYOUT* layout, GRPSCREEN* screen);    
    bool                            DeleteVirtualKeyboard                     (); 
    
  private:                                 
                                    UI_MANAGER                                ();
                                    UI_MANAGER                                (UI_MANAGER const&);        // Don't implement
    virtual                        ~UI_MANAGER                                ();

    void                            operator =                                (UI_MANAGER const&);        // Don't implement

    UI_SKIN*                        Skin_Create                               (XSTRING& skintypename, UI_SKIN_DRAWMODE drawmode, GRPSCREEN* screen, int viewportindex = 0);

    bool                            GetLayoutElementValue                     (XFILEXMLELEMENT* node, XCHAR* leyend, double& value);
    bool                            GetLayoutElementValue                     (XFILEXMLELEMENT* node, XCHAR* leyend, XSTRING& value);    

    bool                            GetLayoutElement_CalculateBoundaryLine    (UI_LAYOUT* layout, UI_ELEMENT* element, bool adjustsizemargin = false);
    bool                            GetParentSizeFont                         (XFILEXMLELEMENT* node, double& sizefont);

    bool                            GetLayoutElement_Base                     (XFILEXMLELEMENT* node, UI_LAYOUT* layout, UI_ELEMENT* element, bool adjusttoparent = false);
    UI_ELEMENT*                     GetLayoutElement_Text                     (XFILEXMLELEMENT* node, UI_LAYOUT* layout, UI_ELEMENT* father, UI_ELEMENT* element_legacy = NULL);
    UI_ELEMENT*                     GetLayoutElement_TextBox                  (XFILEXMLELEMENT* node, UI_LAYOUT* layout, UI_ELEMENT* father, UI_ELEMENT* element_legacy = NULL);
    UI_ELEMENT*                     GetLayoutElement_Image                    (XFILEXMLELEMENT* node, UI_LAYOUT* layout, UI_ELEMENT* father, UI_ELEMENT* element_legacy = NULL);
    UI_ELEMENT*                     GetLayoutElement_Animation                (XFILEXMLELEMENT* node, UI_LAYOUT* layout, UI_ELEMENT* father, UI_ELEMENT* element_legacy = NULL);
    UI_ELEMENT*                     GetLayoutElement_Option                   (XFILEXMLELEMENT* node, UI_LAYOUT* layout, UI_ELEMENT* father, UI_ELEMENT* element_legacy = NULL);
    UI_ELEMENT*                     GetLayoutElement_MultiOption              (XFILEXMLELEMENT* node, UI_LAYOUT* layout, UI_ELEMENT* father, UI_ELEMENT* element_legacy = NULL);
    UI_ELEMENT*                     GetLayoutElement_Button                   (XFILEXMLELEMENT* node, UI_LAYOUT* layout, UI_ELEMENT* father, UI_ELEMENT* element_legacy = NULL);
    UI_ELEMENT*                     GetLayoutElement_CheckBox                 (XFILEXMLELEMENT* node, UI_LAYOUT* layout, UI_ELEMENT* father, UI_ELEMENT* element_legacy = NULL);
    UI_ELEMENT*                     GetLayoutElement_EditText                 (XFILEXMLELEMENT* node, UI_LAYOUT* layout, UI_ELEMENT* father, UI_ELEMENT* element_legacy = NULL);
    UI_ELEMENT*                     GetLayoutElement_Form                     (XFILEXMLELEMENT* node, UI_LAYOUT* layout, UI_ELEMENT* father, UI_ELEMENT* element_legacy = NULL);
    UI_ELEMENT*                     GetLayoutElement_Menu                     (XFILEXMLELEMENT* node, UI_LAYOUT* layout, UI_ELEMENT* father, UI_ELEMENT* element_legacy = NULL);
    UI_ELEMENT*                     GetLayoutElement_ListBox                  (XFILEXMLELEMENT* node, UI_LAYOUT* layout, UI_ELEMENT* father, UI_ELEMENT* element_legacy = NULL);
    UI_ELEMENT*                     GetLayoutElement_ProgressBar              (XFILEXMLELEMENT* node, UI_LAYOUT* layout, UI_ELEMENT* father, UI_ELEMENT* element_legacy = NULL);

    UI_ELEMENT*                     CreatePartialLayout                       (XFILEXMLELEMENT* nodeelement, UI_LAYOUT* layout, UI_ELEMENT* father);
    bool                            CreateLayouts                             (XFILEXML& xml, GRPSCREEN* screen, int viewportindex = 0);
    
    GRPBITMAP*                      LoadBackgroundBitmap                      (XSTRING& namefilebitmap, GRPPROPERTYMODE mode);

    bool                            CreateCacheElements                       (XFILEXMLELEMENT* nodeelement, UI_SKIN_DRAWMODE drawmode, GRPPROPERTYMODE grppropertymode, bool recursive = true); 
    
    bool                            RegisterEvents                            (bool active); 

    UI_ELEMENT*                     PreSelectElement                          (UI_ELEMENT* element, int x, int y);
    
    bool                            SelectElement                             (UI_ELEMENT* element);
    bool                            SelectedElement                           (UI_ELEMENT* element);
    
    bool                            UnSelectedElement                         (UI_ELEMENT* element);
    bool                            UnSelectedElement                         ();

    bool                            UseMotionInElement                        (UI_ELEMENT* element, INPCURSORMOTION* cursormotion);
    bool                            UseMotion                                 (INPCURSORMOTION* cursormotion);

    void                            HandleEvent_UI                            (UI_XEVENT* event);
    void                            HandleEvent                               (XEVENT* xevent);
    
    void                            Clean                                     ();   

    static UI_MANAGER*              instance; 

    bool                            iszippedfile;
    XPATH                           unzippathfile;
    XFILEUNZIP*                     unzipfile;
        
    
    XVECTOR<UI_LAYOUT*>             layouts;
    int                             layout_commonindex;
   
    XMUTEX*                         xmutex_modal;
    UI_ELEMENT*                     element_modal;

    XMUTEX*                         xmutex_UIevent;
    
    int                             last_xposition;
    int                             last_yposition;

    UI_ELEMENT*                     preselect_element;
    
    UI_VIRTUALKEYBOARD*             virtualkeyboard;     
};


#pragma endregion


/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/
#pragma region FUNCTIONS_PROTOTYPES


#pragma endregion


#endif

