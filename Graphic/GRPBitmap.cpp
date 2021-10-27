/**-------------------------------------------------------------------------------------------------------------------
*
* @file       GRPBitmap.cpp
*
* @class      GRPBITMAP
* @brief      Graphics Bitmap class
* @ingroup    GRAPHIC
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @copyright  Copyright(c) 2008 - 2016 GEN Group.
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
*---------------------------------------------------------------------------------------------------------------------*/

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
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  int :
* @param[in]  int height :
* @param[in]  GRPPROPERTYMODE mode :
* @param[in]  bool isbufferinverse :
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
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
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
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
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
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
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     XBYTE* : pointer to array
*
*---------------------------------------------------------------------------------------------------------------------*/
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
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     XBYTE** : pointer to pointer array
*
*---------------------------------------------------------------------------------------------------------------------*/
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
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     int : size of buffer
*
*---------------------------------------------------------------------------------------------------------------------*/
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
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  rect : rect to get sub-bitmap
*
* @return     GRPBITMAP* : sub-bitmap class
*
*---------------------------------------------------------------------------------------------------------------------*/
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
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     GRPBITMAP* : clone bitmap class
*
*---------------------------------------------------------------------------------------------------------------------*/
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
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  bitmap : bitmap origin to clone
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
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
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  newmode :
*
* @return     GRPBITMAP* :
*
*---------------------------------------------------------------------------------------------------------------------*/
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
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
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
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
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
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  degrees : degrees to rotate
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
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
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  nwidth : new width
* @param[in]  nheight : new height
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
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
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  rect : recto to crop
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool GRPBITMAP::Crop(GRPRECTINT& rect)
{
  return false;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD GRPBITMAP::GetHandle()
* @brief      Get handle
* @ingroup    GRAPHIC
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     XDWORD :
*
*---------------------------------------------------------------------------------------------------------------------*/
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
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  handle :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
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
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void GRPBITMAP::Clean()
{
  buffer      = NULL;
  buffersize  = 0;
  isvalid     = false;
  handle      = GRPBITMAP_INVALIDHANDLE;
}




