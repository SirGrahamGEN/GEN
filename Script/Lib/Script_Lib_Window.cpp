/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       Script_Lib_Window.cpp
* 
* @class      SCRIPT_LIB_WINDOW
* @brief      Script Lib Window class
* @ingroup    SCRIPT
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

/*---- PRECOMPILATION INCLUDES ----------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_INCLUDES

#include "GEN_Defines.h"

#pragma endregion


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "Script_Lib_Window.h"

#include "XVariant.h"
#include "XProcessManager.h"

#include "APPBase.h"
#include "APPMain.h"

#ifdef SCRIPT_LIB_WINDOWS_DEBUG
#include "APPGraphics.h"
#endif

#include "INPFactory.h"
#include "INPSimulate.h"

#include "GRPFactory.h"
#include "GRPScreen.h"
#include "GRPBitmap.h"
#include "GRPBitmapFile.h"

#include "GRPViewPort.h"
#include "GRPCanvas.h"

#include "Script.h"

#include "XMemory_Control.h"

#pragma endregion


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

int            windowsposx = 0;
int            windowsposy = 0;

#ifdef SCRIPT_LIB_WINDOWS_DEBUG
APPGRAPHICS*   SCRIPT_LIB_WINDOW::appgraphics = NULL;
#endif
			
#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn        SCRIPT_LIB_WINDOW::SCRIPT_LIB_WINDOW()
* @brief      Constructor
* @ingroup    SCRIPT
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
SCRIPT_LIB_WINDOW::SCRIPT_LIB_WINDOW() : SCRIPT_LIB(SCRIPT_LIB_NAME_WINDOW)
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn        SCRIPT_LIB_WINDOW::~SCRIPT_LIB_WINDOW()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    SCRIPT
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
SCRIPT_LIB_WINDOW::~SCRIPT_LIB_WINDOW()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         boolSCRIPT_LIB_WINDOW::AddLibraryFunctions(SCRIPT* script)
* @brief      AddLibraryFunctions
* @ingroup    SCRIPT
* 
* @param[in]  script : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool SCRIPT_LIB_WINDOW::AddLibraryFunctions(SCRIPT* script)
{
  if(!script) return false;

  this->script = script;

  script->AddLibraryFunction(this, __L("Window_GetPosX")        , Call_Window_GetPosX);
  script->AddLibraryFunction(this, __L("Window_GetPosY")        , Call_Window_GetPosY);
  script->AddLibraryFunction(this, __L("Window_SetFocus")       , Call_Window_SetFocus);
  script->AddLibraryFunction(this, __L("Window_SetPosition")    , Call_Window_SetPosition);
  script->AddLibraryFunction(this, __L("Window_Resize")         , Call_Window_Resize);
  script->AddLibraryFunction(this, __L("Window_Minimize")       , Call_Window_Minimize);
  script->AddLibraryFunction(this, __L("Window_Maximize")       , Call_Window_Maximize);
      
  return true;
}


#ifdef SCRIPT_LIB_WINDOWS_DEBUG

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         APPGRAPHICS* SCRIPT_LIB_WINDOW::GetAppGraphics()
* @brief      GetAppGraphics
* @ingroup    SCRIPT
* 
* @return     APPGRAPHICS* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
APPGRAPHICS* SCRIPT_LIB_WINDOW::GetAppGraphics()
{
  return appgraphics;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void SCRIPT_LIB_WINDOW::SetAppGraphics(APPGRAPHICS* appgraphics)
* @brief      SetAppGraphics
* @ingroup    SCRIPT
* 
* @param[in]  _appgraphics : 
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void SCRIPT_LIB_WINDOW::SetAppGraphics(APPGRAPHICS* _appgraphics)
{
  appgraphics = _appgraphics;
}

#endif

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         voidSCRIPT_LIB_WINDOW::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    SCRIPT
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void SCRIPT_LIB_WINDOW::Clean()
{
  windowsposx = 0;
  windowsposy = 0;

  #ifdef SCRIPT_LIB_WINDOWS_DEBUG
  appgraphics = NULL;
  #endif
}


/*---- LIBRARY FUNCTIONS ---------------------------------------------------------------------------------------------*/
#pragma region LIBRARY_FUNCTIONS


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void Call_Window_GetPos(SCRIPT_LIB* library, SCRIPT* script, XVECTOR<XVARIANT*>* params, XVARIANT* returnvalue)
* @brief      Call_Window_GetPos
* @ingroup    SCRIPT
* 
* @param[in]  library : 
* @param[in]  script : 
* @param[in]  params : 
* @param[in]  returnvalue : 
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void Call_Window_GetPosX(SCRIPT_LIB* library, SCRIPT* script, XVECTOR<XVARIANT*>* params, XVARIANT* returnvalue)
{
  if(!library)      return;
  if(!script)       return;
  if(!params)       return;
  if(!returnvalue)  return;

  returnvalue->Set();

  if(params->GetSize()<2)
    {
      script->HaveError(SCRIPT_ERRORCODE_INSUF_PARAMS);
      return;
    }

  windowsposx = 0xFFFFFF;
  windowsposy = 0xFFFFFF;
 
  XVECTOR<XPROCESS*>  applist;
  XSTRING             appname       = (*params->Get(0));
  XSTRING             windowstitle  = (*params->Get(1));
    
  if(GEN_XPROCESSMANAGER.Application_GetRunningList(applist, true))
    {
      for(XDWORD c=0; c<applist.GetSize(); c++)
        {                              
          if(applist.Get(c)->GetName()->Find(appname, true)!= XSTRING_NOTFOUND) 
            {  
              if(applist.Get(c)->GetWindowTitle()->Find(windowstitle, false) != XSTRING_NOTFOUND)
                {
                  windowsposx = applist.Get(c)->GetWindowRect()->x1; 
                  windowsposy = applist.Get(c)->GetWindowRect()->y1; 
                  
                  if(params->GetSize() >= 3)
                    {                     
                      void* handle_windows = applist.Get(c)->GetWindowHandle();                  
                      if(handle_windows)
                        {  
                          GRPSCREEN* screen = GEN_GRPFACTORY.CreateScreen();
                          if(screen)
                            {                          
                              screen->SetHandle(handle_windows);
                              screen->SetWidth(applist.Get(c)->GetWindowRect()->x2 - applist.Get(c)->GetWindowRect()->x1);
                              screen->SetHeight(applist.Get(c)->GetWindowRect()->y2 - applist.Get(c)->GetWindowRect()->y1);
                              
                              GRPBITMAP* bitmapscreen = screen->CaptureContent();
                              if(bitmapscreen)
                                {                                     
                                  // ----------------------------------------------------------------------------------

                                  #ifdef SCRIPT_LIB_WINDOWS_DEBUG
                                  PutBitmap(0, 0, bitmapscreen);
                                  #endif                             

                                  // ----------------------------------------------------------------------------------

                                  bool found = false;

                                  for(XDWORD d=2; d<params->GetSize(); d++)
                                    { 
                                      XSTRING bitmaprefname  = (*params->Get(d));
                                      if(!bitmaprefname.IsEmpty())
                                        {                                         
                                          XPATH  xpathbitmapref;  
                                      
                                          GEN_XPATHSMANAGER.GetPathOfSection(XPATHSMANAGERSECTIONTYPE_GRAPHICS, xpathbitmapref);
                                          xpathbitmapref.Slash_Add();
                                          xpathbitmapref.Add(bitmaprefname);

                                          GRPBITMAPFILE* bitmapfileref = new GRPBITMAPFILE(xpathbitmapref);
                                          if(bitmapfileref)
                                            {                   
                                              #ifdef SCRIPT_LIB_WINDOWS_DEBUG                              
                                              XPATH  xpathbitmaptest;

                                              GEN_XPATHSMANAGER.GetPathOfSection(XPATHSMANAGERSECTIONTYPE_GRAPHICS, xpathbitmaptest);
                                              xpathbitmaptest.Slash_Add();
                                              xpathbitmaptest.Add(__L("back.png"));

                                              bitmapfileref->Save(xpathbitmaptest, bitmapscreen);
                                              #endif
                            
                                              GRPBITMAP* bitmapref = bitmapfileref->Load();         
                                              if(bitmapref)
                                                {
                                                  int x = 0;
                                                  int y = 0;                                              

                                                  #ifdef SCRIPT_LIB_WINDOWS_DEBUG
                                                  if(FindSubBitmap(bitmapscreen, bitmapref, x, y, 2))    
                                                  #else                                                
                                                  if(bitmapscreen->FindSubBitmap(bitmapref, x, y, 2))
                                                  #endif    
                                                    {
                                                      windowsposx += (x + (bitmapref->GetWidth() /2) + applist.Get(c)->GetWindowBorderWidth()); 
                                                      windowsposy += (y + (bitmapref->GetHeight()/2) + applist.Get(c)->GetWindowTitleHeight()); 
                                                      found = true;
                                                    }      
                                                }                                                 

                                              delete bitmapref;
                                              delete bitmapfileref;    
                                            }                                            
                                        }
                                       else  
                                        {
                                          break;
                                        } 
                                        
                                      if(found)
                                        {
                                          break;    
                                        }     
                                     } 

                                  if(!found)
                                    {
                                      windowsposx = 0xFFFFFE;
                                      windowsposy = 0xFFFFFE;
                                    }

                                  delete bitmapscreen;

                                  GEN_GRPFACTORY.DeleteScreen(screen);                                
                                }
                            } 
                        }      
                    }
                
                  break;
                }
            }
        }
    }
    
  applist.DeleteContents();
  applist.DeleteAll();
   
  (*returnvalue) = windowsposx;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void Call_Window_GetPosY(SCRIPT_LIB* library, SCRIPT* script, XVECTOR<XVARIANT*>* params, XVARIANT* returnvalue)
* @brief      Call_Window_GetPosY
* @ingroup    SCRIPT
* 
* @param[in]  library : 
* @param[in]  script : 
* @param[in]  params : 
* @param[in]  returnvalue : 
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void Call_Window_GetPosY(SCRIPT_LIB* library, SCRIPT* script, XVECTOR<XVARIANT*>* params, XVARIANT* returnvalue)
{
  if(!library)      return;
  if(!script)       return;
  if(!params)       return;
  if(!returnvalue)  return;

  returnvalue->Set();

  if(params->GetSize()<2)
    {
      script->HaveError(SCRIPT_ERRORCODE_INSUF_PARAMS);
      return;
    }

  (*returnvalue) = windowsposy;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void Call_Window_SetFocus(SCRIPT_LIB* library, SCRIPT* script, XVECTOR<XVARIANT*>* params, XVARIANT* returnvalue)
* @brief      all_Window_SetFocus
* @ingroup    SCRIPT
* 
* @param[in]  library : 
* @param[in]  script : 
* @param[in]  params : 
* @param[in]  returnvalue : 
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void Call_Window_SetFocus(SCRIPT_LIB* library, SCRIPT* script, XVECTOR<XVARIANT*>* params, XVARIANT* returnvalue)
{
  if(!library)      return;
  if(!script)       return;
  if(!params)       return;
  if(!returnvalue)  return;

  returnvalue->Set();

  if(params->GetSize()<2)
    {
      script->HaveError(SCRIPT_ERRORCODE_INSUF_PARAMS);
      return;
    }
 
  XVECTOR<XPROCESS*>  applist;
  XSTRING             appname       = (*params->Get(0));
  XSTRING             windowstitle  = (*params->Get(1));
  bool                status        = false;
  
  if(GEN_XPROCESSMANAGER.Application_GetRunningList(applist, true))
    {
      for(XDWORD c=0; c<applist.GetSize(); c++)
        {                              
          if(applist.Get(c)->GetName()->Find(appname, true)!= XSTRING_NOTFOUND) 
            {  
              if(applist.Get(c)->GetWindowTitle()->Find(windowstitle, false) != XSTRING_NOTFOUND)
                {
                  void* handle_windows = applist.Get(c)->GetWindowHandle();
                  
                  if(handle_windows)
                    {  
                      GRPSCREEN* screen = GEN_GRPFACTORY.CreateScreen();
                      if(screen)
                        {                          
                          screen->SetHandle(handle_windows);
                          screen->Set_Focus();
                        
                          GEN_GRPFACTORY.DeleteScreen(screen);  

                          status = true;   
                        }
                    } 
                    
                  break;
                }
            }
        }
    }
    
  applist.DeleteContents();
  applist.DeleteAll();
   
  (*returnvalue) = status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void Call_Window_SetPosition(SCRIPT_LIB* library, SCRIPT* script, XVECTOR<XVARIANT*>* params, XVARIANT* returnvalue)
* @brief      all_Window_SetPosition
* @ingroup    SCRIPT
* 
* @param[in]  library : 
* @param[in]  script : 
* @param[in]  params : 
* @param[in]  returnvalue : 
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void Call_Window_SetPosition(SCRIPT_LIB* library, SCRIPT* script, XVECTOR<XVARIANT*>* params, XVARIANT* returnvalue)
{
  if(!library)      return;
  if(!script)       return;
  if(!params)       return;
  if(!returnvalue)  return;

  returnvalue->Set();

  if(params->GetSize()<4)
    {
      script->HaveError(SCRIPT_ERRORCODE_INSUF_PARAMS);
      return;
    }
 
  XVECTOR<XPROCESS*>  applist;
  XSTRING             appname       = (*params->Get(0));
  XSTRING             windowstitle  = (*params->Get(1));
  int                 positionx     = 0;
  int                 positiony     = 0;
  bool                status        = false;

  library->GetParamConverted(params->Get(2), positionx);
  library->GetParamConverted(params->Get(3), positiony);
  
  if(GEN_XPROCESSMANAGER.Application_GetRunningList(applist, true))
    {
      for(XDWORD c=0; c<applist.GetSize(); c++)
        {                              
          if(applist.Get(c)->GetName()->Find(appname, true)!= XSTRING_NOTFOUND) 
            {  
              if(applist.Get(c)->GetWindowTitle()->Find(windowstitle, false) != XSTRING_NOTFOUND)
                {
                  void* handle_windows = applist.Get(c)->GetWindowHandle();
                  
                  if(handle_windows)
                    {  
                      GRPSCREEN* screen = GEN_GRPFACTORY.CreateScreen();
                      if(screen)
                        {
                          screen->SetHandle(handle_windows);
                          screen->Set_Position(positionx, positiony);
                        
                          GEN_GRPFACTORY.DeleteScreen(screen);  

                          status = true;   
                        }
                    } 
                    
                  break;
                }
            }
        }
    }
    
  applist.DeleteContents();
  applist.DeleteAll();
   
  (*returnvalue) = status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void Call_Window_Resize(SCRIPT_LIB* library, SCRIPT* script, XVECTOR<XVARIANT*>* params, XVARIANT* returnvalue)
* @brief      all_Window_Resize
* @ingroup    SCRIPT
* 
* @param[in]  library : 
* @param[in]  script : 
* @param[in]  params : 
* @param[in]  returnvalue : 
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void Call_Window_Resize(SCRIPT_LIB* library, SCRIPT* script, XVECTOR<XVARIANT*>* params, XVARIANT* returnvalue)
{
  if(!library)      return;
  if(!script)       return;
  if(!params)       return;
  if(!returnvalue)  return;

  returnvalue->Set();

  if(params->GetSize()<4)
    {
      script->HaveError(SCRIPT_ERRORCODE_INSUF_PARAMS);
      return;
    }
 
  XVECTOR<XPROCESS*>  applist;
  XSTRING             appname       = (*params->Get(0));
  XSTRING             windowstitle  = (*params->Get(1));
  int                 sizex         = 0;
  int                 sizey         = 0;
  bool                status        = false;

  library->GetParamConverted(params->Get(2), sizex);
  library->GetParamConverted(params->Get(3), sizey);
  
  if(GEN_XPROCESSMANAGER.Application_GetRunningList(applist, true))
    {
      for(XDWORD c=0; c<applist.GetSize(); c++)
        {                              
          if(applist.Get(c)->GetName()->Find(appname, true)!= XSTRING_NOTFOUND) 
            {  
              if(applist.Get(c)->GetWindowTitle()->Find(windowstitle, false) != XSTRING_NOTFOUND)
                {
                  void* handle_windows = applist.Get(c)->GetWindowHandle();
                  
                  if(handle_windows)
                    {  
                      GRPSCREEN* screen = GEN_GRPFACTORY.CreateScreen();
                      if(screen)
                        {
                          screen->SetHandle(handle_windows);
                          screen->Resize(sizex,sizey);
                        
                          GEN_GRPFACTORY.DeleteScreen(screen);  

                          status = true;   
                        }
                    } 
                    
                  break;
                }
            }
        }
    }
    
  applist.DeleteContents();
  applist.DeleteAll();
   
  (*returnvalue) = status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void Call_Window_Minimize(SCRIPT_LIB* library, SCRIPT* script, XVECTOR<XVARIANT*>* params, XVARIANT* returnvalue)
* @brief      all_Window_Minimize
* @ingroup    SCRIPT
* 
* @param[in]  library : 
* @param[in]  script : 
* @param[in]  params : 
* @param[in]  returnvalue : 
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void Call_Window_Minimize(SCRIPT_LIB* library, SCRIPT* script, XVECTOR<XVARIANT*>* params, XVARIANT* returnvalue)
{
  if(!library)      return;
  if(!script)       return;
  if(!params)       return;
  if(!returnvalue)  return;

  returnvalue->Set();

  if(params->GetSize()<3)
    {
      script->HaveError(SCRIPT_ERRORCODE_INSUF_PARAMS);
      return;
    }
 
  XVECTOR<XPROCESS*>  applist;
  XSTRING             appname       = (*params->Get(0));
  XSTRING             windowstitle  = (*params->Get(1));
  bool                showstatus    = false;
  bool                status        = false;

  library->GetParamConverted(params->Get(2), showstatus);
  
  if(GEN_XPROCESSMANAGER.Application_GetRunningList(applist, true))
    {
      for(XDWORD c=0; c<applist.GetSize(); c++)
        {                              
          if(applist.Get(c)->GetName()->Find(appname, true)!= XSTRING_NOTFOUND) 
            {  
              if(applist.Get(c)->GetWindowTitle()->Find(windowstitle, false) != XSTRING_NOTFOUND)
                {
                  void* handle_windows = applist.Get(c)->GetWindowHandle();
                  
                  if(handle_windows)
                    {  
                      GRPSCREEN* screen = GEN_GRPFACTORY.CreateScreen();
                      if(screen)
                        {
                          screen->SetHandle(handle_windows);
                          status = screen->Minimize(showstatus);
                          
                          GEN_GRPFACTORY.DeleteScreen(screen);  
                        }
                    } 
                    
                  break;
                }
            }
        }
    }
    
  applist.DeleteContents();
  applist.DeleteAll();
   
  (*returnvalue) = status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void Call_Window_Maximize(SCRIPT_LIB* library, SCRIPT* script, XVECTOR<XVARIANT*>* params, XVARIANT* returnvalue)
* @brief      Call_Window_Maximize
* @ingroup    SCRIPT
* 
* @param[in]  library : 
* @param[in]  script : 
* @param[in]  params : 
* @param[in]  returnvalue : 
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void Call_Window_Maximize(SCRIPT_LIB* library, SCRIPT* script, XVECTOR<XVARIANT*>* params, XVARIANT* returnvalue)
{
  if(!library)      return;
  if(!script)       return;
  if(!params)       return;
  if(!returnvalue)  return;

  returnvalue->Set();

  if(params->GetSize()<3)
    {
      script->HaveError(SCRIPT_ERRORCODE_INSUF_PARAMS);
      return;
    }
 
  XVECTOR<XPROCESS*>  applist;
  XSTRING             appname       = (*params->Get(0));
  XSTRING             windowstitle  = (*params->Get(1));
  bool                showstatus    = false;
  bool                status        = false;

  library->GetParamConverted(params->Get(2), showstatus);
  
  if(GEN_XPROCESSMANAGER.Application_GetRunningList(applist, true))
    {
      for(XDWORD c=0; c<applist.GetSize(); c++)
        {                              
          if(applist.Get(c)->GetName()->Find(appname, true)!= XSTRING_NOTFOUND) 
            {  
              if(applist.Get(c)->GetWindowTitle()->Find(windowstitle, false) != XSTRING_NOTFOUND)
                {
                  void* handle_windows = applist.Get(c)->GetWindowHandle();
                  
                  if(handle_windows)
                    {  
                      GRPSCREEN* screen = GEN_GRPFACTORY.CreateScreen();
                      if(screen)
                        {
                          screen->SetHandle(handle_windows);
                          status = screen->Maximize(showstatus);
                          
                          GEN_GRPFACTORY.DeleteScreen(screen);  
                        }
                    } 
                    
                  break;
                }
            }
        }
    }
    
  applist.DeleteContents();
  applist.DeleteAll();
   
  (*returnvalue) = status;
}


#ifdef SCRIPT_LIB_WINDOWS_DEBUG

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DifferencesPerCent(XDWORD ndiff, XDWORD max, int limit)
* @brief      ifferencesPerCent
* @ingroup    SCRIPT
* 
* @param[in]  ndiff : 
* @param[in]  max : 
* @param[in]  limit : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DifferencesPerCent(XDWORD ndiff, XDWORD max, int limit)
{
  int actualdiff = ((ndiff*100)/max);

  if(actualdiff > limit) return false;

  return true;
} 


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool FindSubBitmap(GRPBITMAP* bitmapscreen, GRPBITMAP* bitmapref, int& x, int& y, XBYTE difflimitpercent)
* @brief      indSubBitmap
* @ingroup    SCRIPT
* 
* @param[in]  bitmapscreen : 
* @param[in]  bitmapref : 
* @param[in]  x : 
* @param[in]  y : 
* @param[in]  difflimitpercent : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool FindSubBitmap(GRPBITMAP* bitmapscreen, GRPBITMAP* bitmapref, int& x, int& y, XBYTE difflimitpercent)
{
  x = 0; 
  y = 0;

  if(!bitmapref)
    {
      return false;
    }
  
  GRPBITMAP* _bitmap = bitmapref->ConvertToMode(bitmapscreen->GetMode());
  if(!_bitmap)
    {
      return false;
    }

  if(_bitmap->GetMode() != bitmapscreen->GetMode()) 
    {
      return false;
    }
  
  XDWORD  bytesperline_bmp  = bitmapscreen->GetBytesperPixel() * _bitmap->GetWidth();
  XBYTE*  bufferbitmap      = _bitmap->GetBuffer();
  bool    found             = true;

  if(!bufferbitmap)
    {
      return false;
    }

  XDWORD pos_base = 0;
  XDWORD pos_bmp  = 0;   
  XDWORD ndiff    = 0;

  for(; pos_base < (bitmapscreen->GetBufferSize() - bytesperline_bmp); pos_base++)
    {
      ndiff = 0;
      for(XDWORD d=0; d < bytesperline_bmp; d++)
        {
          if(bitmapscreen->GetBuffer()[pos_base + d] != bufferbitmap[d])
            {       
              ndiff++;             
            }
           else
            {
              //bitmapscreen->GetBuffer()[pos_base + d] = 0x00;
              //PutBitmap(0, 0, bitmapscreen);           
            }
        } 

      found = DifferencesPerCent(ndiff, bytesperline_bmp, difflimitpercent);
      if(found)
        {          
          XDWORD bytesperline_base = bitmapscreen->GetBytesperPixel() * bitmapscreen->GetWidth();

          x =  (pos_base % bytesperline_base) / bitmapscreen->GetBytesperPixel();
          y =  bitmapscreen->GetHeight() - (pos_base / bytesperline_base) - _bitmap->GetHeight();

          XDWORD pos_base_tmp = pos_base; 

          pos_bmp  = 0; 
          
          for(XDWORD line = 0; line < _bitmap->GetHeight(); line++)
            { 
              ndiff = 0;     
                    
              for(XDWORD d=0; d<bytesperline_bmp; d++)
                {
                  if(bitmapscreen->GetBuffer()[pos_base_tmp + d] != bufferbitmap[pos_bmp])
                    {
                      ndiff++;
                    }
                   else
                    {
                      //bitmapscreen->GetBuffer()[pos_base_tmp + d] = 0x00;
                      //PutBitmap(0, 0, bitmapscreen);
                    }     

                  pos_bmp++;
                } 

              found = DifferencesPerCent(ndiff, bytesperline_bmp, difflimitpercent);  
              if(found)
                {
                  pos_base_tmp += bytesperline_base;                                   
                }
               else
                {                 
                  x = 0; 
                  y = 0;

                  break;  
                }  
            } 

          if(found)
            {
              break;    
            }       
        }
    }

  if(!found)
    {
      x = 0;
      y = 0;
    }
   else
    {
      GRPVIEWPORT* viewport = NULL;
      GRPCANVAS*   canvas   = NULL;
      GRPSCREEN*   screen   = SCRIPT_LIB_WINDOW::GetAppGraphics()->GetMainScreen();

      if(screen) viewport = screen->GetViewport(0);
      if(viewport) canvas = viewport->GetCanvas();

      if(canvas)
        {
          GRP2DCOLOR_RGBA8  colorred(255, 0, 0);

          canvas->SetLineWidth(1.0f);
          canvas->SetLineColor(&colorred);

          canvas->Rectangle(x, y, x + _bitmap->GetWidth(), y + _bitmap->GetHeight());  
          canvas->PutPixel((x + _bitmap->GetWidth()/2), y + (_bitmap->GetHeight()/2), &colorred);

          screen->UpdateViewports();
        }      
    }

  delete _bitmap;

  return found;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool PutBitmap(int x, int y, GRPBITMAP* bitmap)
* @brief      utBitmap
* @ingroup    SCRIPT
* 
* @param[in]  x : 
* @param[in]  y : 
* @param[in]  bitmap : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool PutBitmap(int x, int y, GRPBITMAP* bitmap)
{
  if(!SCRIPT_LIB_WINDOW::GetAppGraphics())
    {
      return false;
    }
                                        
  GRPVIEWPORT* viewport = NULL;
  GRPCANVAS*   canvas   = NULL;
  GRPSCREEN*   screen   = SCRIPT_LIB_WINDOW::GetAppGraphics()->GetMainScreen();

  if(screen) viewport = screen->GetViewport(0);
  if(viewport) canvas = viewport->GetCanvas();

  if(canvas)
    {
      canvas->PutBitmap(x, y, bitmap);  
      screen->UpdateViewports();                                              
    }
  
  return true;
}


#endif

#pragma endregion

#pragma endregion



