/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       GRPBitmap.cpp
* 
* @class      GRPBITMAP
* @brief      Graphics Bitmap class
* @ingroup    GRAPHIC
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

#include "GRPBitmap.h"

#include "GRPRect.h"

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


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         GRPBITMAP::GRPBITMAP(int width, int height, GRPPROPERTYMODE mode, bool isbufferinverse)
* @brief      Constructor of class
* @ingroup    GRAPHIC
*
* @param[in]  width :
* @param[in]  height :
* @param[in]  mode :
* @param[in]  isbufferinverse :
*
* --------------------------------------------------------------------------------------------------------------------*/
GRPBITMAP::GRPBITMAP(int width, int height, GRPPROPERTYMODE mode, bool isbufferinverse)
{
  Clean();

  this->width           = width;
  this->height          = height;
  this->mode            = mode;
  this->isbufferinverse = isbufferinverse;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         GRPBITMAP::~GRPBITMAP()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    GRAPHIC
*
* --------------------------------------------------------------------------------------------------------------------*/
GRPBITMAP::~GRPBITMAP()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRPBITMAP::IsValid()
* @brief      Is valid
* @ingroup    GRAPHIC
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPBITMAP::IsValid()
{
  return isvalid;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XBYTE* GRPBITMAP::GetBuffer()
* @brief      Get buffer
* @ingroup    GRAPHIC
*
* @return     XBYTE* : pointer to array
*
* --------------------------------------------------------------------------------------------------------------------*/
XBYTE* GRPBITMAP::GetBuffer()
{
  return buffer;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XBYTE** GRPBITMAP::GetBufferPointer()
* @brief      Get buffer pointer
* @ingroup    GRAPHIC
*
* @return     XBYTE** : pointer to pointer array
*
* --------------------------------------------------------------------------------------------------------------------*/
XBYTE** GRPBITMAP::GetBufferPointer()
{
  return &buffer;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int GRPBITMAP::GetBufferSize()
* @brief      Get buffer size
* @ingroup    GRAPHIC
*
* @return     int : size of buffer
*
* --------------------------------------------------------------------------------------------------------------------*/
int GRPBITMAP::GetBufferSize()
{
  return buffersize;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         GRPBITMAP* GRPBITMAP::GetSubBitmap(GRPRECTINT& rect)
* @brief      Get sub bitmap
* @ingroup    GRAPHIC
*
* @param[in]  rect : rect to get sub-bitmap
*
* @return     GRPBITMAP* : sub-bitmap class
*
* --------------------------------------------------------------------------------------------------------------------*/
GRPBITMAP* GRPBITMAP::GetSubBitmap(GRPRECTINT& rect)
{
  return NULL;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         GRPBITMAP* GRPBITMAP::Clone()
* @brief      Clone
* @ingroup    GRAPHIC
*
* @return     GRPBITMAP* : clone bitmap class
*
* --------------------------------------------------------------------------------------------------------------------*/
GRPBITMAP* GRPBITMAP::Clone()
{
  return NULL;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRPBITMAP::CopyFrom(GRPBITMAP* bitmap)
* @brief      Copy from
* @ingroup    GRAPHIC
*
* @param[in]  bitmap : bitmap origin to clone
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPBITMAP::CopyFrom(GRPBITMAP* bitmap)
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         GRPBITMAP* GRPBITMAP::ConvertToMode(GRPPROPERTYMODE newmode)
* @brief      Convert to mode
* @ingroup    GRAPHIC
*
* @param[in]  newmode :
*
* @return     GRPBITMAP* :
*
* --------------------------------------------------------------------------------------------------------------------*/
GRPBITMAP* GRPBITMAP::ConvertToMode(GRPPROPERTYMODE newmode)
{
  return NULL;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRPBITMAP::FlipHorizontal()
* @brief      Flip horizontal
* @ingroup    GRAPHIC
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPBITMAP::FlipHorizontal()
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRPBITMAP::FlipVertical()
* @brief      Flip vertical
* @ingroup    GRAPHIC
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPBITMAP::FlipVertical()
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRPBITMAP::Rotate(float degrees)
* @brief      Rotate
* @ingroup    GRAPHIC
*
* @param[in]  degrees : degrees to rotate
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPBITMAP::Rotate(float degrees)
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRPBITMAP::Scale(int nwidth, int nheight)
* @brief      Scale
* @ingroup    GRAPHIC
*
* @param[in]  nwidth : new width
* @param[in]  nheight : new height
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPBITMAP::Scale(int nwidth, int nheight)
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRPBITMAP::Crop(GRPRECTINT& rect)
* @brief      Crop
* @ingroup    GRAPHIC
*
* @param[in]  rect : recto to crop
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPBITMAP::Crop(GRPRECTINT& rect)
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool GRPBITMAP::Compare(GRPBITMAP* bitmap)
* @brief      Compare
* @ingroup    GRAPHIC
* 
* @param[in]  bitmap : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPBITMAP::Compare(GRPBITMAP* bitmap)
{
  if(!bitmap)
    {
      return false;
    }

  if(bitmap->GetMode() != GetMode()) 
    {
      return false;
    }

  if(bitmap->GetBufferSize() != buffersize) 
    {
      return false;
    }

  XBYTE* bufferbitmap = bitmap->GetBuffer();
  if(!bufferbitmap)
    {
      return false;
    }

  bool equal = true;

  for(XDWORD c=0; c<buffersize; c++)
    {
      if(bufferbitmap[c] != buffer[c])
        {
          equal = false;
          break;
        }
    }  

  return equal;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool GRPBITMAP::FindSubBitmap(GRPBITMAP* bitmapref, int& x, int& y, XBYTE difflimitpercent, XBYTE pixelmargin)
* @brief      Find sub bitmap
* @ingroup    GRAPHIC
* 
* @param[in]  bitmapref : 
* @param[in]  x : 
* @param[in]  y : 
* @param[in]  difflimitpercent : 
* @param[in]  pixelmargin : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPBITMAP::FindSubBitmap(GRPBITMAP* bitmapref, int& x, int& y, XBYTE difflimitpercent, XBYTE pixelmargin)
{   
  x = 0; 
  y = 0;

  if(!bitmapref)
    {
      return false;
    }
  
  GRPBITMAP* _bitmap = bitmapref->ConvertToMode(GetMode());
  if(!_bitmap)
    {
      return false;
    }

  if(!_bitmap->GetBuffer())
    {
      return false;
    }
  
  XDWORD*   bufferscreen        = (XDWORD*)buffer;
  XDWORD*   bufferbitmap        = (XDWORD*)_bitmap->GetBuffer();
  XDWORD    sizepixel           = sizeof(XDWORD);
  XDWORD    bufferscreensize    = (GetBufferSize() / sizepixel);
  XDWORD    bufferbmplinesize   = _bitmap->GetWidth();
  XDWORD    ndiff               = 0;
  bool      found               = false;
  
  for(XDWORD scrpos = 0; scrpos < bufferscreensize; scrpos++)
    {
      ndiff = 0;
      for(XDWORD bmppos = 0; bmppos < bufferbmplinesize; bmppos++)  
        {    
          if(bufferscreen[scrpos + bmppos] != bufferbitmap[bmppos])
            {
              if(!IsSimilarPixel(bufferscreen[scrpos + bmppos], bufferbitmap[bmppos], pixelmargin))
                {
                  ndiff++;
                }
            }
        }
               
      found = DifferencesPerCent(ndiff, bufferbmplinesize, difflimitpercent);
      if(found)
        {          
          found = false;

          XDWORD srcpixelsline  = GetWidth();
          XDWORD scrpos_tmp     = scrpos;
          XDWORD bmppos_tmp     = bufferbmplinesize;
         
          x =  (scrpos % GetWidth());
          y =  GetHeight() - (scrpos / srcpixelsline) - _bitmap->GetHeight();           

          scrpos_tmp += srcpixelsline;              
    
          for(XDWORD line = 1; line < _bitmap->GetHeight(); line++)
            {                                                   
              ndiff = 0;
              for(XDWORD bmppos = 0; bmppos < bufferbmplinesize; bmppos++)  
                {    
                  if(bufferscreen[scrpos_tmp + bmppos] != bufferbitmap[bmppos_tmp])
                    {
                      if(!IsSimilarPixel(bufferscreen[scrpos_tmp + bmppos], bufferbitmap[bmppos_tmp], pixelmargin))
                        {
                          ndiff++;
                        }
                    }  
                  
                  bmppos_tmp++;
                }
              
              found = DifferencesPerCent(ndiff, bufferbmplinesize, difflimitpercent);              

              if(!found)
                {
                  break;              
                }
      
              scrpos_tmp += srcpixelsline;
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
   
  delete _bitmap;
  
  return found;  
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD GRPBITMAP::GetHandle()
* @brief      Get handle
* @ingroup    GRAPHIC
*
* @return     XDWORD :
*
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD GRPBITMAP::GetHandle()
{
  return handle;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void GRPBITMAP::SetHandle(XDWORD handle)
* @brief      Set handle
* @ingroup    GRAPHIC
*
* @param[in]  handle :
*
* --------------------------------------------------------------------------------------------------------------------*/
void GRPBITMAP::SetHandle(XDWORD handle)
{
  this->handle = handle;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool GRPBITMAP::DifferencesPerCent(XDWORD ndiff, XDWORD max, int limit)
* @brief      Differences per cent
* @ingroup    GRAPHIC
* 
* @param[in]  ndiff : 
* @param[in]  max : 
* @param[in]  limit : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPBITMAP::DifferencesPerCent(XDWORD ndiff, XDWORD max, int limit)
{
  int actualdiff = ((ndiff*100)/max);

  if(actualdiff > limit) return false;

  return true;
} 


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool GRPBITMAP::IsSimilarPixel(XDWORD origin, XDWORD target, XBYTE margin)
* @brief      Is similar pixel
* @ingroup    GRAPHIC
* 
* @param[in]  origin : 
* @param[in]  target : 
* @param[in]  margin : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPBITMAP::IsSimilarPixel(XDWORD origin, XDWORD target, XBYTE margin)
{
  XBYTE* originRGBA = (XBYTE*)&origin;
  XBYTE* targetRGBA = (XBYTE*)&target;  
  bool   status     = false;

  int ncomponent = 0;

  for(int c=0; c<4; c++)
    {
      if(abs(originRGBA[c] - targetRGBA[c]) > margin)
        {
          ncomponent++;
        }
    }

  if(!ncomponent) 
    {
      status = true;
    }  

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void GRPBITMAP::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    GRAPHIC
*
* --------------------------------------------------------------------------------------------------------------------*/
void GRPBITMAP::Clean()
{
  buffer      = NULL;
  buffersize  = 0;
  isvalid     = false;
  handle      = GRPBITMAP_INVALIDHANDLE;
}


#pragma endregion




