/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       GRPFactory.cpp
* 
* @class      GRPFACTORY
* @brief      Graphics Factory class
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

/*---- PRECOMPILATION INCLUDES ----------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_INCLUDES

#include "GEN_Defines.h"

#pragma endregion


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "GRPFactory.h"

#include "GRPScreen.h"
#include "GRPCanvasAGG.h"
#include "GRPBitmap.h"

#include "XMemory_Control.h"

#pragma endregion


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

GRPFACTORY* GRPFACTORY::instance = NULL;

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         GRPFACTORY::GRPFACTORY()
* @brief      Constructor
* @ingroup    XUTILS
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
GRPFACTORY::GRPFACTORY()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         GRPFACTORY::~GRPFACTORY()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    XUTILS
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
GRPFACTORY::~GRPFACTORY()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRPFACTORY::GetIsInstanced()
* @brief      Get if Is Instanced
* @note       STATIC
* @ingroup    XUTILS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPFACTORY::GetIsInstanced()
{
  return instance!=NULL;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         GRPFACTORY& GRPFACTORY::GetInstance()
* @brief      Get Instance of GRPFACTORY
* @note       STATIC
* @ingroup    XUTILS
*
* @return     GRPFACTORY& :
*
* --------------------------------------------------------------------------------------------------------------------*/
GRPFACTORY& GRPFACTORY::GetInstance()
{
  if(!instance)
    {
      instance = new GRPFACTORY();
    }

  return (*instance);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRPFACTORY::SetInstance(GRPFACTORY* instance)
* @brief      Set Instance of GRPFACTORY
* @note       STATIC
* @ingroup    XUTILS
*
* @param[in]  _instance : new instance
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPFACTORY::SetInstance(GRPFACTORY* _instance)
{
  if(!_instance) return false;

  instance = _instance;

  return (instance)?true:false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRPFACTORY::DelInstance()
* @brief      Delete Instance of GRPFACTORY
* @note       STATIC
* @ingroup    XUTILS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPFACTORY::DelInstance()
{
  if(!instance) return false;

  delete instance;
  instance = NULL;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         GRPSCREEN* GRPFACTORY::CreateScreen()
* @brief      Create Screen
* @ingroup    GRAPHIC
*
* @return     GRPSCREEN* : screen class
*
* --------------------------------------------------------------------------------------------------------------------*/
GRPSCREEN* GRPFACTORY::CreateScreen()
{
  return NULL;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRPFACTORY::DeleteScreen(GRPSCREEN* screen)
* @brief      Delete Screen
* @ingroup    GRAPHIC
*
* @param[in]  screen : screen class to delete
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPFACTORY::DeleteScreen(GRPSCREEN* screen)
{
  return false;
}


#ifdef GRP_OPENGL_ACTIVE

/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         GRPCONTEXT* GRPFACTORY::CreateContext()
* @brief      CreateContext
* @ingroup    GRAPHIC
*
* @return     GRPCONTEXT* :
*
* --------------------------------------------------------------------------------------------------------------------*/
GRPCONTEXT* GRPFACTORY::CreateContext()
{
  return NULL;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRPFACTORY::DeleteContext(GRPCONTEXT* context)
* @brief      Delete Context
* @ingroup    GRAPHIC
*
* @param[in]  context :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPFACTORY::DeleteContext(GRPCONTEXT* context)
{
  return NULL;
}

#endif


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         GRPCANVAS* GRPFACTORY::CreateCanvas(GRPSCREEN* screen)
* @brief      Create Canvas
* @ingroup    GRAPHIC
*
* @param[in]  properties : properties to generate canvas
*
* @return     GRPCANVAS* : canvas class
*
* --------------------------------------------------------------------------------------------------------------------*/
GRPCANVAS* GRPFACTORY::CreateCanvas(GRPPROPERTIES* properties)
{
  GRPCANVAS*      canvas = NULL;
  GRPPROPERTYMODE mode   = GRPPROPERTYMODE_XX_UNKNOWN;

  if(!properties) return NULL;

  mode = properties->GetMode();
  if(mode == GRPPROPERTYMODE_XX_UNKNOWN) return NULL;

  if(!properties->GetWidth() || !properties->GetHeight()) return NULL;

  switch(mode)
    {
      case GRPPROPERTYMODE_08_INDEX     : break;
      case GRPPROPERTYMODE_16_RGBA_4444 : break;
      case GRPPROPERTYMODE_16_RGBA_5551 : canvas =  (GRPCANVAS*)new GRPCANVASAGG<agg::pixfmt_rgb555, agg::rgba8>();   break;
      case GRPPROPERTYMODE_16_RGB_565   : canvas =  (GRPCANVAS*)new GRPCANVASAGG<agg::pixfmt_rgb565, agg::rgba8>();   break;
      case GRPPROPERTYMODE_16_SRGB_565  : break;
      case GRPPROPERTYMODE_24_RGB_888   : canvas =  (GRPCANVAS*)new GRPCANVASAGG<agg::pixfmt_rgb24 , agg::rgba8>();   break;
      case GRPPROPERTYMODE_24_BGR_888   : canvas =  (GRPCANVAS*)new GRPCANVASAGG<agg::pixfmt_bgr24 , agg::rgba8>();   break;
      case GRPPROPERTYMODE_32_RGBA_8888 : canvas =  (GRPCANVAS*)new GRPCANVASAGG<agg::pixfmt_rgba32, agg::rgba8>();   break;
      case GRPPROPERTYMODE_32_BGRA_8888 : canvas =  (GRPCANVAS*)new GRPCANVASAGG<agg::pixfmt_bgra32, agg::rgba8>();   break;
                               default  : break;
    }

  if(canvas)  canvas->CopyPropertysFrom(properties);

  return canvas;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRPFACTORY::DeleteCanvas(GRPCANVAS* canvas)
* @brief      DeleteCanvas
* @ingroup    GRAPHIC
*
* @param[in]  canvas : canvas to delete
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPFACTORY::DeleteCanvas(GRPCANVAS* canvas)
{
  if(!canvas) return false;

  canvas->DeleteBuffers();

  delete canvas;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         GRPBITMAP* GRPFACTORY::CreateBitmap(int width, int height, GRPPROPERTYMODE mode, bool isbufferinverse)
* @brief      CreateBitmap
* @ingroup    GRAPHIC
*
* @param[in]  width :
* @param[in]  height :
* @param[in]  mode :
* @param[in]  isbufferinverse :
*
* @return     GRPBITMAP* :
*
* --------------------------------------------------------------------------------------------------------------------*/
GRPBITMAP* GRPFACTORY::CreateBitmap(int width, int height, GRPPROPERTYMODE mode, bool isbufferinverse)
{
  GRPBITMAP* bitmap = NULL;

  if(mode == GRPPROPERTYMODE_XX_UNKNOWN) return NULL;

  switch(mode)
    {
      case GRPPROPERTYMODE_08_INDEX     : break;
      case GRPPROPERTYMODE_16_RGBA_4444 : break;
      case GRPPROPERTYMODE_16_RGBA_5551 : bitmap =  (GRPBITMAP*)new GRPBITMAPPIXELFORMATBUFFER<agg::pixfmt_rgb555, agg::rgba8>(width, height, mode, isbufferinverse);   break;
      case GRPPROPERTYMODE_16_RGB_565   : bitmap =  (GRPBITMAP*)new GRPBITMAPPIXELFORMATBUFFER<agg::pixfmt_rgb565, agg::rgba8>(width, height, mode, isbufferinverse);   break;
      case GRPPROPERTYMODE_16_SRGB_565  : break;
      case GRPPROPERTYMODE_24_RGB_888   : bitmap =  (GRPBITMAP*)new GRPBITMAPPIXELFORMATBUFFER<agg::pixfmt_rgb24 , agg::rgba8>(width, height, mode, isbufferinverse);   break;
      case GRPPROPERTYMODE_24_BGR_888   : bitmap =  (GRPBITMAP*)new GRPBITMAPPIXELFORMATBUFFER<agg::pixfmt_bgr24 , agg::rgba8>(width, height, mode, isbufferinverse);   break;
      case GRPPROPERTYMODE_32_RGBA_8888 : bitmap =  (GRPBITMAP*)new GRPBITMAPPIXELFORMATBUFFER<agg::pixfmt_rgba32, agg::rgba8>(width, height, mode, isbufferinverse);   break;
      case GRPPROPERTYMODE_32_BGRA_8888 : bitmap =  (GRPBITMAP*)new GRPBITMAPPIXELFORMATBUFFER<agg::pixfmt_bgra32, agg::rgba8>(width, height, mode, isbufferinverse);   break;

                            default     : break;
    }

  return bitmap;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRPFACTORY::DeleteBitmap(GRPBITMAP* bitmap)
* @brief      Delete Bitmap
* @ingroup    GRAPHIC
*
* @param[in]  bitmap : bitmap class to delete
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPFACTORY::DeleteBitmap(GRPBITMAP* bitmap)
{
  if(!bitmap) return false;

  delete bitmap;

  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void GRPFACTORY::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    GRAPHIC
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void GRPFACTORY::Clean()
{

}


#pragma endregion

