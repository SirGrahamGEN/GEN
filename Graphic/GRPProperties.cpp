/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       GRPProperties.cpp
* 
* @class      GRPPROPERTIES
* @brief      Graphics Properties class
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

#include "GRPProperties.h"

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
* @fn         GRPPROPERTIES::GRPPROPERTIES()
* @brief      Constructor of class
* @ingroup    GRAPHIC
*
* --------------------------------------------------------------------------------------------------------------------*/
GRPPROPERTIES::GRPPROPERTIES()
{
  Clean();

  Default();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         GRPPROPERTIES::~GRPPROPERTIES()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    GRAPHIC
*
* --------------------------------------------------------------------------------------------------------------------*/
GRPPROPERTIES::~GRPPROPERTIES()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         GRPPROPERTYMODE GRPPROPERTIES::GetMode()
* @brief      Get mode
* @ingroup    GRAPHIC
*
* @return     GRPPROPERTYMODE : Property mode
*
* --------------------------------------------------------------------------------------------------------------------*/
GRPPROPERTYMODE GRPPROPERTIES::GetMode()
{
  return mode;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void GRPPROPERTIES::SetMode(GRPPROPERTYMODE mode)
* @brief      Set mode
* @ingroup    GRAPHIC
*
* @param[in]  mode : new mode of property
*
* --------------------------------------------------------------------------------------------------------------------*/
void GRPPROPERTIES::SetMode(GRPPROPERTYMODE mode)
{
  this->mode = mode;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int GRPPROPERTIES::GetPositionX()
* @brief      Get position x
* @ingroup    GRAPHIC
*
* @return     int :
*
* --------------------------------------------------------------------------------------------------------------------*/
int GRPPROPERTIES::GetPositionX()
{
  return positionx;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int GRPPROPERTIES::GetPositionY()
* @brief      Get position y
* @ingroup    GRAPHIC
*
* @return     int :
*
* --------------------------------------------------------------------------------------------------------------------*/
int GRPPROPERTIES::GetPositionY()
{
  return positiony;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void GRPPROPERTIES::SetPosition(int x, int y)
* @brief      Set position
* @ingroup    GRAPHIC
*
* @param[in]  x : new x position
* @param[in]  y : new y position
*
* --------------------------------------------------------------------------------------------------------------------*/
void GRPPROPERTIES::SetPosition(int x, int y)
{
  positionx = x;
  positiony = y;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD GRPPROPERTIES::GetWidth()
* @brief      Get width
* @ingroup    GRAPHIC
*
* @return     XDWORD : Width of propertys
*
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD GRPPROPERTIES::GetWidth()
{
  return width;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void GRPPROPERTIES::SetWidth(XDWORD width)
* @brief      Set width
* @ingroup    GRAPHIC
*
* @param[in]  width : new width
*
* --------------------------------------------------------------------------------------------------------------------*/
void GRPPROPERTIES::SetWidth(XDWORD width)
{
  this->width = width;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD GRPPROPERTIES::GetHeight()
* @brief      Get height
* @ingroup    GRAPHIC
*
* @return     XDWORD : height of properties
*
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD GRPPROPERTIES::GetHeight()
{
  return height;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void GRPPROPERTIES::SetHeight(XDWORD height)
* @brief      Set height
* @ingroup    GRAPHIC
*
* @param[in]  height : new height
*
* --------------------------------------------------------------------------------------------------------------------*/
void GRPPROPERTIES::SetHeight(XDWORD height)
{
  this->height = height;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void GRPPROPERTIES::SetSize(XDWORD width, XDWORD height)
* @brief      Set size
* @ingroup    GRAPHIC
*
* @param[in]  width :
* @param[in]  height :
*
* --------------------------------------------------------------------------------------------------------------------*/
void GRPPROPERTIES::SetSize(XDWORD width, XDWORD height)
{
  this->width  = width;
  this->height = height;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD GRPPROPERTIES::GetMaxWidth()
* @brief      Get max width
* @ingroup    GRAPHIC
*
* @return     XDWORD : Max Width of propertys
*
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD GRPPROPERTIES::GetMaxWidth()
{
  return maxwidth;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void GRPPROPERTIES::SetMaxWidth(XDWORD width)
* @brief      Set max width
* @ingroup    GRAPHIC
*
* @param[in]  width : new width
*
* --------------------------------------------------------------------------------------------------------------------*/
void GRPPROPERTIES::SetMaxWidth(XDWORD maxwidth)
{
  this->maxwidth = maxwidth;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD GRPPROPERTIES::GetMaxHeight()
* @brief      Get max height
* @ingroup    GRAPHIC
*
* @return     XDWORD : Max height of properties
*
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD GRPPROPERTIES::GetMaxHeight()
{
  return maxheight;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void GRPPROPERTIES::SetMaxHeight(XDWORD maxheight)
* @brief      Set max height
* @ingroup    GRAPHIC
*
* @param[in]  maxheight : new max height
*
* --------------------------------------------------------------------------------------------------------------------*/
void GRPPROPERTIES::SetMaxHeight(XDWORD maxheight)
{
  this->maxheight = maxheight;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void GRPPROPERTIES::SetMaxSize(XDWORD maxwidth, XDWORD maxheight)
* @brief      Set max size
* @ingroup    GRAPHIC
*
* @param[in]  maxwidth :
* @param[in]  maxheight :
*
* --------------------------------------------------------------------------------------------------------------------*/
void GRPPROPERTIES::SetMaxSize(XDWORD maxwidth, XDWORD maxheight)
{
  this->maxwidth  = maxwidth;
  this->maxheight = maxheight;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         GRPRECTINT* GRPPROPERTIES::GetWorkRegion()
* @brief      Get work region
* @ingroup    GRAPHIC
* 
* @return     GRPRECTINT* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
GRPRECTINT* GRPPROPERTIES::GetWorkRegion()
{
  return &workregion;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         float GRPPROPERTIES::GetDPI()
* @brief      Get DPI
* @ingroup    GRAPHIC
*
* @return     float : DPIs properties
*
* --------------------------------------------------------------------------------------------------------------------*/
float GRPPROPERTIES::GetDPI()
{
  return DPIs;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void GRPPROPERTIES::SetDPI(float DPI)
* @brief      Set DPI
* @ingroup    GRAPHIC
*
* @param[in]  DPI :
*
* --------------------------------------------------------------------------------------------------------------------*/
void GRPPROPERTIES::SetDPI(float DPI)
{
  this->DPIs = DPI;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD GRPPROPERTIES::GetStride()
* @brief      Get stride
* @ingroup    GRAPHIC
*
* @return     XDWORD :
*
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD GRPPROPERTIES::GetStride()
{
  return stride;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void GRPPROPERTIES::SetStride(XDWORD stride)
* @brief      Set stride
* @ingroup    GRAPHIC
*
* @param[in]  stride : new stride
*
* --------------------------------------------------------------------------------------------------------------------*/
void GRPPROPERTIES::SetStride(XDWORD stride)
{
  this->stride = stride;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRPPROPERTIES::IsBufferInverse()
* @brief      Is buffer inverse
* @ingroup    GRAPHIC
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPPROPERTIES::IsBufferInverse()
{
  return isbufferinverse;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void GRPPROPERTIES::SetIsBufferInverse(bool isbufferinverse)
* @brief      Set is buffer inverse
* @ingroup    GRAPHIC
*
* @param[in]  isbufferinverse : true is buffer inverse
*
* --------------------------------------------------------------------------------------------------------------------*/
void GRPPROPERTIES::SetIsBufferInverse(bool isbufferinverse)
{
  this->isbufferinverse = isbufferinverse;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XBYTE GRPPROPERTIES::GetBitsperPixel()
* @brief      Get bitsper pixel
* @ingroup    GRAPHIC
*
* @return     XBYTE : number of bits per pixel
*
* --------------------------------------------------------------------------------------------------------------------*/
XBYTE GRPPROPERTIES::GetBitsperPixel()
{
  XBYTE bitsppixel = 0;

  switch(mode)
    {
      case GRPPROPERTYMODE_XX_UNKNOWN   : break;
      case GRPPROPERTYMODE_08_INDEX     : bitsppixel =  8;  break;

      case GRPPROPERTYMODE_16_RGBA_4444 :
      case GRPPROPERTYMODE_16_RGB_565   :
      case GRPPROPERTYMODE_16_SRGB_565  :
      case GRPPROPERTYMODE_16_RGBA_5551 : bitsppixel = 16;  break;

      case GRPPROPERTYMODE_24_RGB_888   :
      case GRPPROPERTYMODE_24_BGR_888   : bitsppixel = 24;  break;

      case GRPPROPERTYMODE_32_RGBA_8888 :
      case GRPPROPERTYMODE_32_BGRA_8888 : bitsppixel = 32;  break;

                              default   : bitsppixel =  0;  break;
    }

  return bitsppixel;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XBYTE GRPPROPERTIES::GetBytesperPixel()
* @brief      Get bytesper pixel
* @ingroup    GRAPHIC
*
* @return     XBYTE : bytes per pixel
*
* --------------------------------------------------------------------------------------------------------------------*/
XBYTE GRPPROPERTIES::GetBytesperPixel()
{
  return (GetBitsperPixel()/8);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void GRPPROPERTIES::CopyPropertysFrom(GRPPROPERTIES* properties)
* @brief      Copy propertys from
* @ingroup    GRAPHIC
*
* @param[in]  properties : new properties to assing
*
* --------------------------------------------------------------------------------------------------------------------*/
void GRPPROPERTIES::CopyPropertysFrom(GRPPROPERTIES* properties)
{
  if(!properties) return;

  mode            = properties->mode;
  positionx       = properties->positionx;
  positiony       = properties->positiony;
  width           = properties->width;
  height          = properties->height;
  DPIs            = properties->DPIs;
  stride          = properties->stride;
  isbufferinverse = properties->isbufferinverse;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void GRPPROPERTIES::CopyPropertysTo(GRPPROPERTIES* properties)
* @brief      Copy propertys to
* @ingroup    GRAPHIC
*
* @param[out] properties : Actual properties
*
* --------------------------------------------------------------------------------------------------------------------*/
void GRPPROPERTIES::CopyPropertysTo(GRPPROPERTIES* properties)
{
  if(!properties) return;

  properties->mode              = mode;
  properties->positionx         = positionx;
  properties->positiony         = positiony;
  properties->width             = width;
  properties->height            = height;
  properties->DPIs              = DPIs;
  properties->stride            = stride;
  properties->isbufferinverse   = isbufferinverse;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         int GRPPROPERTIES::IsEqualSizeTo(GRPPROPERTIES* properties)
* @brief      Is equal size to
* @ingroup    GRAPHIC
* 
* @param[in]  properties : 
* 
* @return     int : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
int GRPPROPERTIES::IsEqualSizeTo(GRPPROPERTIES* properties)
{
  if(!properties) return ISLESS;

  int size[2];

  size[0] = width * height;
  size[1] = properties->width * properties->height;

  if(size[0] > size[1])   return ISGREATER;
  if(size[0] < size[1])   return ISLESS;

  return ISEQUAL;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void GRPPROPERTIES::Default()
* @brief      Default
* @ingroup    GRAPHIC
*
* --------------------------------------------------------------------------------------------------------------------*/
void GRPPROPERTIES::Default()
{
  mode            = GRPPROPERTYMODE_24_BGR_888;
  positionx       = GRPPROPERTYMODE_SCREEN_CENTER;
  positiony       = GRPPROPERTYMODE_SCREEN_CENTER;
  width           = 0;
  height          = 0;
  maxwidth        = width;
  maxheight       = height;
  DPIs            = 0;
  stride          = 0;
  isbufferinverse = false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void GRPPROPERTIES::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    GRAPHIC
*
* --------------------------------------------------------------------------------------------------------------------*/
void GRPPROPERTIES::Clean()
{
  mode            = GRPPROPERTYMODE_XX_UNKNOWN;
  positionx       = 0;
  positiony       = 0;
  width           = 0;
  height          = 0;
  maxwidth        = 0;
  maxheight       = 0;
  DPIs            = 0;
  stride          = 0;
  isbufferinverse = false;
}


#pragma endregion



