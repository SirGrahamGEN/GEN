/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       UI_Animation.cpp
* 
* @class      UI_ANIMATION
* @brief      User Interface Animation class
* @ingroup    USERINTERFACE
*
* @copyright  GEN Group. All right reserved.
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
* ---------------------------------------------------------------------------------------------------------------------*/

/*---- PRECOMPILATION CONTROL ----------------------------------------------------------------------------------------*/

#include "GEN_Defines.h"


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "XPathsManager.h"

#include "GRPBitmapFile.h"

#include "UI_Animation.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         UI_ANIMATION::UI_ANIMATION()
* @brief      Constructor
* @ingroup    USERINTERFACE
*
* @return     Does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
UI_ANIMATION::UI_ANIMATION()    
{ 
  Clean();                            
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         UI_ANIMATION::~UI_ANIMATION()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    USERINTERFACE
*
* @return     Does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
UI_ANIMATION::~UI_ANIMATION()    
{ 
  DeleteAll();

  Clean();                            
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_ANIMATION::LoadFromFile(XSTRING& resourcename)
* @brief      LoadFromFile
* @ingroup    USERINTERFACE
*
* @param[in]  resourcename : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool UI_ANIMATION::LoadFromFile(XSTRING& resourcename, GRPPROPERTYMODE mode)
{
  XPATH           xpathimg;   
  GRPBITMAPFILE   bitmapfile;
  GRPBITMAP*      bitmap    = NULL; 
  XSTRING         mask;
  int             indexmask = 0;
  int             indeximg  = 0;
                                                                                                                                                                       
  while(1)
    {                                                                                                                               
      XSTRING namefile; 

      indexmask = resourcename.Copy(UI_ANIMATION_FRAME_INI, UI_ANIMATION_FRAME_END, true, 0, mask);  
                                                               
      namefile = resourcename;    

      if(!mask.IsEmpty())
        {
          XSTRING result;
          int     masksize = mask.GetSize()+3;

          namefile.DeleteCharacters(indexmask-masksize, masksize);  
                                                                                                                                        
          mask.Insert(__L("%"), 0);
          mask.Add(__L("d"));
                                                                
          result.Format(mask.Get(), indeximg);
          indeximg++;
                                                                  
          namefile.Insert(result.Get(), indexmask-masksize);
        }                                               

      GEN_XPATHSMANAGER.GetPathOfSection(XPATHSMANAGERSECTIONTYPE_GRAPHICS, xpathimg);
      xpathimg.Slash_Add();
      xpathimg.Add(namefile);

      bitmap = bitmapfile.Load(xpathimg, mode);
      if(bitmap) 
        { 
          bitmaps.Add(bitmap);                                                      
          if(mask.IsEmpty()) break;                                                                                                            
        } 
       else break;        
    }                                                          

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSTRING* UI_ANIMATION::GetName()
* @brief      GetName
* @ingroup    USERINTERFACE
*
* @return     XSTRING* : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
XSTRING* UI_ANIMATION::GetName()
{
  return &name;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSTRING* UI_ANIMATION::GetResource()
* @brief      GetResource
* @ingroup    USERINTERFACE
*
* @return     XSTRING* : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
XSTRING* UI_ANIMATION::GetResource()
{
  return &resource;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XVECTOR<GRPBITMAP*>* UI_ANIMATION::GetBitmaps()
* @brief      GetBitmaps
* @ingroup    USERINTERFACE
*
* @return     XVECTOR<GRPBITMAP*>* : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
XVECTOR<GRPBITMAP*>* UI_ANIMATION::GetBitmaps()
{
  return &bitmaps;
}
    


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         GRPBITMAP* UI_ANIMATION::GetBitmap(int index)
* @brief      GetBitmap
* @ingroup    USERINTERFACE
*
* @param[in]  index : 
* 
* @return     GRPBITMAP* : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
GRPBITMAP* UI_ANIMATION::GetBitmap(int index)
{
  return bitmaps.Get(index);
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_ANIMATION::DeleteAll()
* @brief      DeleteAll
* @ingroup    USERINTERFACE
*
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool UI_ANIMATION::DeleteAll()
{
  if(bitmaps.IsEmpty()) return false;

  bitmaps.DeleteContents();
  bitmaps.DeleteAll();
  
  return true;
}




/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void UI_ANIMATION::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    USERINTERFACE
*
* @return     void : does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void UI_ANIMATION::Clean()
{
 
}

