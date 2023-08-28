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

#include "INPFactory.h"
#include "INPSimulate.h"

#include "GRPFactory.h"
#include "GRPScreen.h"
#include "GRPBitmap.h"
#include "GRPBitmapFile.h"

#include "Script.h"

#include "XMemory_Control.h"

#pragma endregion


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

int windowsposx = 0;
int windowsposy = 0;
			
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
      
  return true;
}


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

  windowsposx = 0;
  windowsposy = 0;
 
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
                  
                  if(params->GetSize() == 3)
                    {
                      XSTRING bitmaprefname  = (*params->Get(2));
                      if(!bitmaprefname.IsEmpty())
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
                                      XPATH  xpathbitmapref;  
                                      
                                      GEN_XPATHSMANAGER.GetPathOfSection(XPATHSMANAGERSECTIONTYPE_GRAPHICS, xpathbitmapref);
                                      xpathbitmapref.Slash_Add();
                                      xpathbitmapref.Add(bitmaprefname);

                                      GRPBITMAPFILE* bitmapfileref = new GRPBITMAPFILE(xpathbitmapref);
                                      if(bitmapfileref)
                                        {                                         
                                          GRPBITMAP* bitmapref = bitmapfileref->Load();         
                                          if(bitmapref)
                                            {
                                              int x;
                                              int y;

                                              if(SearchBitpmapInOther(bitmapscreen, bitmapref, x, y))
                                                {
                                                  windowsposx += x; 
                                                  windowsposy += y; 
                                                }      
                                            }                                                 

                                          delete bitmapref;
                                          delete bitmapfileref;    
                                        }

                                      delete bitmapscreen;  
                                    }

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
 
  /*
  XVECTOR<XPROCESS*>  applist;
  XSTRING             appname       = (*params->Get(0));
  XSTRING             windowstitle  = (*params->Get(1));
  int                 windowsposy   = 0; 
  
  if(GEN_XPROCESSMANAGER.Application_GetRunningList(applist, true))
    {
      for(XDWORD c=0; c<applist.GetSize(); c++)
        {                              
          if(applist.Get(c)->GetName()->Find(appname, true)!= XSTRING_NOTFOUND) 
            {  
              if(applist.Get(c)->GetWindowTitle()->Find(windowstitle, false) != XSTRING_NOTFOUND)
                {
                  windowsposy = applist.Get(c)->GetWindowRect()->y1;
                  break;
                }
            }
        }
    }
    
  applist.DeleteContents();
  applist.DeleteAll();
  */
   
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
* @fn         bool SearchBitpmapInOther(GRPBITMAP* base, GRPBITMAP* ref, int& x, int& y)
* @brief      earchBitpmapInOther
* @ingroup    SCRIPT
* 
* @param[in]  base : 
* @param[in]  ref : 
* @param[in]  x : 
* @param[in]  y : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool SearchBitpmapInOther(GRPBITMAP* base, GRPBITMAP* ref, int& x, int& y)
{
  bool status = false;

  x = 0;
  y = 0;

  
  return status;
}


#pragma endregion

#pragma endregion



