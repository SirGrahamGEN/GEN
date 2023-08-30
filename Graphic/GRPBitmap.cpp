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

/*---- PRECOMPILATION CONTROL ----------------------------------------------------------------------------------------*/

#include "GEN_Defines.h"


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "GRPRect.h"
#include "GRPBitmap.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         GRPBITMAP::GRPBITMAP(int width, int height, GRPPROPERTYMODE mode, bool isbufferinverse)
* @brief      Constructor
* @ingroup    GRAPHIC
*
* @param[in]  int :
* @param[in]  int height :
* @param[in]  GRPPROPERTYMODE mode :
* @param[in]  bool isbufferinverse :
*
* @return     Does not return anything.
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
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    GRAPHIC
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
GRPBITMAP::~GRPBITMAP()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRPBITMAP::IsValid()
* @brief      Is Valid
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
* @brief      Get Buffer
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
* @brief      Get Buffer Pointer
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
* @brief      Get Buffer Size
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
* @brief      Get Sub-Bitmap
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
* @brief      Copy From
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
* @brief      ConvertToMode
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
* @brief      Flip Horizontal
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
* @brief      Flip Vertical
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
* @brief      Rotate bitmap
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
* @fn         bool GRPBITMAP::FindSubBitmap(GRPBITMAP* bitmap, int& x, int& y)
* @brief      FindSubBitmap
* @ingroup    GRAPHIC
* 
* @param[in]  bitmap : 
* @param[in]  x : 
* @param[in]  y : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
/*
bool GRPBITMAP::FindSubBitmap(GRPBITMAP* bitmap, int& x, int& y)
{
  bool found = false;

  x = 67; 
  y = 310;

  if(!bitmap)
    {
      return false;
    }

  GRPBITMAP* _bitmap = bitmap->ConvertToMode(GetMode());
  if(!_bitmap)
    {
      return false;
    }

  if(_bitmap->GetMode() != GetMode()) 
    {
      return false;
    }

  XBYTE bytesline = GetBytesperPixel();

  

//for(x=0; x<(GetWidth() - _bitmap->GetWidth()); x++)
    {
    //for(y=0; y<(GetHeight() - _bitmap->GetHeight()); y++)
        {
          GRPRECTINT  rect;
          GRPBITMAP*  subbitmap;
                  
          rect.x1 = x;
          rect.x2 = x + _bitmap->GetWidth();          

          rect.y1 = y;
          rect.y2 = y + _bitmap->GetHeight();          
              
          subbitmap = GetSubBitmap(rect);  
          if(subbitmap)
            {
              if(_bitmap->Compare(subbitmap))
                {
                  found = true;                
                }
            }

          delete subbitmap;
        }
    }

  delete _bitmap;

  if(!found)
    {
      x = 0;
      y = 0;
    }

  return found;
}
*/


bool GRPBITMAP::FindSubBitmap(GRPBITMAP* bitmap, int& x, int& y)
{
  x = 0; 
  y = 0;

  if(!bitmap)
    {
      return false;
    }

  GRPBITMAP* _bitmap = bitmap->ConvertToMode(GetMode());
  if(!_bitmap)
    {
      return false;
    }

  if(_bitmap->GetMode() != GetMode()) 
    {
      return false;
    }

  XDWORD  bytesperline_bmp  = GetBytesperPixel() * _bitmap->GetWidth();
  XBYTE*  bufferbitmap      = _bitmap->GetBuffer();
  bool    found             = true;

  if(!bufferbitmap)
    {
      return false;
    }
  XDWORD index = 0;
  for(; index < (buffersize - bytesperline_bmp); index++)
    {
      found = true;
      for(XDWORD d=0; d < bytesperline_bmp; d++)
        {
          if(buffer[index + d] != bufferbitmap[d])
            {
              found = false;
              break;
            }
        } 

      if(found)
        {          
          XDWORD bytesperline_base = GetBytesperPixel() * GetWidth();

          x =  (index % bytesperline_base) / GetBytesperPixel();
          y =  GetHeight() - (index / bytesperline_base) - _bitmap->GetHeight();

          XDWORD position_base = index;  
          XDWORD position_bmp  = 0;   

          for(XDWORD line = 0; line < _bitmap->GetHeight(); line++)
            {              
              for(XDWORD d=0; d<bytesperline_bmp; d++)
                {
                  if(buffer[position_base + d] != bufferbitmap[position_bmp])
                    {
                      found = false;
                      break;
                    }

                  position_bmp++;
                } 
  
              if(found)
                {
                  position_base -= (bytesperline_base - bytesperline_bmp);                   
                }
               else
                {
                  x = 0; 
                  y = 0;

                  break;  
                }  
            }        
        }
    }
  
  delete _bitmap;

  if(!found)
    {
      x = 0;
      y = 0;
    }

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
* @brief      Set Handle
* @ingroup    GRAPHIC
*
* @param[in]  handle :
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void GRPBITMAP::SetHandle(XDWORD handle)
{
  this->handle = handle;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void GRPBITMAP::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    GRAPHIC
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void GRPBITMAP::Clean()
{
  buffer      = NULL;
  buffersize  = 0;
  isvalid     = false;
  handle      = GRPBITMAP_INVALIDHANDLE;
}




