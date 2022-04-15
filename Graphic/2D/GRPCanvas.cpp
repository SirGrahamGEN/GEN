/**-------------------------------------------------------------------------------------------------------------------
*
* @file       GRPCanvas.cpp
*
* @class      GRPCANVAS
* @brief      Graphics Canvas class
* @ingroup    GRAPHIC
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
*---------------------------------------------------------------------------------------------------------------------*/

/*---- PRECOMPILATION CONTROL ----------------------------------------------------------------------------------------*/

#include "GEN_Defines.h"


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/


#include "GRP2DRebuildAreas.h"
#include "GRPViewPort.h"

#include "GRPCanvas.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/




/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         GRPCANVAS_VECTORFONT_CONFIG::GRPCANVAS_VECTORFONT_CONFIG()
* @brief      Constructor
* @ingroup    GRAPHIC
*
* @return     Does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
GRPCANVAS_VECTORFONT_CONFIG::GRPCANVAS_VECTORFONT_CONFIG()
{
  Clean();    
  color = new GRP2DCOLOR_RGBA8(0, 0, 0);
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         GRPCANVAS_VECTORFONT_CONFIG::~GRPCANVAS_VECTORFONT_CONFIG()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    GRAPHIC
*
* @return     Does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
GRPCANVAS_VECTORFONT_CONFIG::~GRPCANVAS_VECTORFONT_CONFIG()
{
  if(color) 
    {
      delete color;   
      color = NULL;
    }      

  Clean();                                                                                                                                                                                              
} 



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool GRPCANVAS_VECTORFONT_CONFIG::GetSize(double& width, double& height)
* @brief      GetSize
* @ingroup    GRAPHIC
*
* @param[in]  width : 
* @param[in]  height : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool GRPCANVAS_VECTORFONT_CONFIG::GetSize(double& width, double& height)
{
  width   = this->width;
  height  = this->height;    

  return true;
}


 
/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool GRPCANVAS_VECTORFONT_CONFIG::SetSize(double width, double height)
* @brief      SetSize
* @ingroup    GRAPHIC
*
* @param[in]  width : 
* @param[in]  height : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool GRPCANVAS_VECTORFONT_CONFIG::SetSize(double width, double height)
{
  this->width   = width;
  this->height  = height; 

  return true;   
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         double GRPCANVAS_VECTORFONT_CONFIG::GetSize()
* @brief      GetSize
* @ingroup    GRAPHIC
*
* @return     double : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
double GRPCANVAS_VECTORFONT_CONFIG::GetSize()
{
  if(height > width) return height;
    else if(height < width) return width;
      else if(height == width) return width;
  
  return width;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool GRPCANVAS_VECTORFONT_CONFIG::SetSize(double size)
* @brief      SetSize
* @ingroup    GRAPHIC
*
* @param[in]  size : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool GRPCANVAS_VECTORFONT_CONFIG::SetSize(double size)
{
  this->width  = size;
  this->height = size;

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         double GRPCANVAS_VECTORFONT_CONFIG::GetWidth()
* @brief      GetWidth
* @ingroup    GRAPHIC
*
* @return     double : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
double GRPCANVAS_VECTORFONT_CONFIG::GetWidth()                                 
{ 
  return width;               
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void GRPCANVAS_VECTORFONT_CONFIG::SetWidth(double width)
* @brief      SetWidth
* @ingroup    GRAPHIC
*
* @param[in]  width : 
* 
* @return     void : does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void GRPCANVAS_VECTORFONT_CONFIG::SetWidth(double width)                     
{ 
  this->width = width;        
}


    
/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         double GRPCANVAS_VECTORFONT_CONFIG::GetHeight()
* @brief      GetHeight
* @ingroup    GRAPHIC
*
* @return     double : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
double GRPCANVAS_VECTORFONT_CONFIG::GetHeight()                                 
{ 
  return height;              
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void GRPCANVAS_VECTORFONT_CONFIG::SetHeight(double height)
* @brief      SetHeight
* @ingroup    GRAPHIC
*
* @param[in]  height : 
* 
* @return     void : does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void GRPCANVAS_VECTORFONT_CONFIG::SetHeight(double height)                    
{ 
  this->height = height;      
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         GRP2DCOLOR_RGBA8* GRPCANVAS_VECTORFONT_CONFIG::GetColor()
* @brief      GetColor
* @ingroup    GRAPHIC
*
* @return     GRP2DCOLOR_RGBA8* : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
GRP2DCOLOR_RGBA8* GRPCANVAS_VECTORFONT_CONFIG::GetColor()                                 
{
  return color;               
}


  
/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void GRPCANVAS_VECTORFONT_CONFIG::SetColor(GRP2DCOLOR_RGBA8* color)
* @brief      SetColor
* @ingroup    GRAPHIC
*
* @param[in]  color : 
* 
* @return     void : does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void GRPCANVAS_VECTORFONT_CONFIG::SetColor(GRP2DCOLOR_RGBA8* color)          
{ 
  if(!color) return;

  this->color->r = color->r;
  this->color->g = color->g;
  this->color->b = color->b;
  this->color->a = color->a;
}
    



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool GRPCANVAS_VECTORFONT_CONFIG::IsKerning()
* @brief      IsKerning
* @ingroup    GRAPHIC
*
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool GRPCANVAS_VECTORFONT_CONFIG::IsKerning()
{
  return iskerning;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void GRPCANVAS_VECTORFONT_CONFIG::SetKerning(bool iskerning)
* @brief      SetKerning
* @ingroup    GRAPHIC
*
* @param[in]  iskerning : 
* 
* @return     void : does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void GRPCANVAS_VECTORFONT_CONFIG::SetKerning(bool iskerning)
{
  this->iskerning = iskerning;
}


  
/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void GRPCANVAS_VECTORFONT_CONFIG::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    GRAPHIC
*
* @return     void : does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void GRPCANVAS_VECTORFONT_CONFIG::Clean()
{
  width       = 0.0f;
  height      = 0.0f;
  color       = NULL;
  iskerning   = false;
}
    







/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         GRPCANVAS::GRPCANVAS()
* @brief      Constructor
* @ingroup    GRAPHIC
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
GRPCANVAS::GRPCANVAS()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         GRPCANVAS::~GRPCANVAS()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    GRAPHIC
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
GRPCANVAS::~GRPCANVAS()
{
  RebuildAllAreas();
  DeleteAllRebuildAreas();

  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         GRPRECTINT* GRPCANVAS::GetScreenZone()
* @brief      Get Screen Zone
* @ingroup    GRAPHIC
*
* @return     GRPRECTINT* : rect of screen zone
*
*---------------------------------------------------------------------------------------------------------------------*/
GRPRECTINT* GRPCANVAS::GetScreenZone()
{
  return &screenzone;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRPCANVAS::CreateBuffers()
* @brief      Create Buffers
* @ingroup    GRAPHIC
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool GRPCANVAS::CreateBuffers()
{
  buffer = new XBYTE[width * height * GetBytesperPixel()];
  if(!buffer) return false;

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRPCANVAS::DeleteBuffers()
* @brief      Delete Buffers
* @ingroup    GRAPHIC
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool GRPCANVAS::DeleteBuffers()
{
  return false;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XBYTE* GRPCANVAS::GetBuffer()
* @brief      Get Buffer
* @ingroup    GRAPHIC
*
* @return     XBYTE* : buffer with data
*
*---------------------------------------------------------------------------------------------------------------------*/
XBYTE* GRPCANVAS::GetBuffer()
{
  return buffer;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void GRPCANVAS::Clear(const GRP2DCOLOR* color)
* @brief      Clear
* @ingroup    GRAPHIC
*
* @param[in]  GRP2DCOLOR* color :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void GRPCANVAS::Clear(const GRP2DCOLOR* color)
{

}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void GRPCANVAS::GetClipBox(double& x1, double& y1, double& x2, double& y2)
* @brief      GetClipBox
* @ingroup    GRAPHIC
*
* @param[in]  x1 : 
* @param[in]  y1 : 
* @param[in]  x2 : 
* @param[in]  y2 : 
* 
* @return     void : does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void GRPCANVAS::GetClipBox(double& x1, double& y1, double& x2, double& y2)
{
  x1 = lastcliprect.x1;
  y1 = lastcliprect.y1;
  x2 = lastcliprect.x2;
  y2 = lastcliprect.y2;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void GRPCANVAS::GetClipBox(XRECT& rect)
* @brief      GetClipBox
* @ingroup    GRAPHIC
*
* @param[in]  rect : 
* 
* @return     void : does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void GRPCANVAS::GetClipBox(XRECT& rect)
{
  rect.CopyFrom(lastcliprect);   
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XRECT& GRPCANVAS::GetClipBox()
* @brief      GetClipBox
* @ingroup    GRAPHIC
*
* @return     XRECT& : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
XRECT& GRPCANVAS::GetClipBox()
{
  return lastcliprect;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void GRPCANVAS::SetClipBox(double x1, double y1, double x2, double y2)
* @brief      SetClipBox
* @ingroup    GRAPHIC
*
* @param[in]  x1 : 
* @param[in]  y1 : 
* @param[in]  x2 : 
* @param[in]  y2 : 
* 
* @return     void : does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void  GRPCANVAS::SetClipBox(double x1, double y1, double x2, double y2)
{
  lastcliprect.x1 = x1;
  lastcliprect.y1 = y1;
  lastcliprect.x2 = x2;
  lastcliprect.y2 = y2;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void GRPCANVAS::SetClipBox(XRECT& rect)
* @brief      SetClipBox
* @ingroup    GRAPHIC
*
* @param[in]  rect : 
* 
* @return     void : does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void GRPCANVAS::SetClipBox(XRECT& rect)
{
  lastcliprect.CopyFrom(rect);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         GRP2DCOLOR* GRPCANVAS::GetPixel(double x, double y)
* @brief      Get Pixel
* @ingroup    GRAPHIC
*
* @param[in]  x : x pos of pixel
* @param[in]  y : y pos of pixel
*
* @return     GRP2DCOLOR* : color of pixel
*
*---------------------------------------------------------------------------------------------------------------------*/
GRP2DCOLOR* GRPCANVAS::GetPixel(double x, double y)
{
  return NULL;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void GRPCANVAS::PutPixel(double x, double y, const GRP2DCOLOR* color)
* @brief      PutPixel
* @ingroup    GRAPHIC
*
* @param[in]  x : x pos to put pixel
* @param[in]  y : y pos to put pixel
* @param[in]  GRP2DCOLOR* color : color to put
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void GRPCANVAS::PutPixel(double x, double y, const GRP2DCOLOR* color)
{

}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void GRPCANVAS::PutBlendPixel(double x, double y, const GRP2DCOLOR* color, double alpha)
* @brief      PutBlendPixel
* @ingroup    GRAPHIC
*
* @param[in]  x : x pos to put pixel
* @param[in]  y : y pos to put pixel
* @param[in]  GRP2DCOLOR* color : color to put
* @param[in]  alpha : alpha to put pixel
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void GRPCANVAS::PutBlendPixel(double x, double y, const GRP2DCOLOR* color, double alpha)
{

}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         GRP2DCOLOR* GRPCANVAS::GetFillColor()
* @brief      Get Fill Color
* @ingroup    GRAPHIC
*
* @return     GRP2DCOLOR* : color of fill
*
*---------------------------------------------------------------------------------------------------------------------*/
GRP2DCOLOR* GRPCANVAS::GetFillColor()
{
  return NULL;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void GRPCANVAS::SetFillColor(const GRP2DCOLOR* color)
* @brief      Set Fill Color
* @ingroup    GRAPHIC
*
* @param[in]  GRP2DCOLOR* color : color to fill
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void GRPCANVAS::SetFillColor(const GRP2DCOLOR* color)
{

}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         GRP2DCOLOR* GRPCANVAS::GetLineColor()
* @brief      Get Line Color
* @ingroup    GRAPHIC
*
* @return     GRP2DCOLOR* : color of line
*
*---------------------------------------------------------------------------------------------------------------------*/
GRP2DCOLOR* GRPCANVAS::GetLineColor()
{
  return NULL;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void GRPCANVAS::SetLineColor(const GRP2DCOLOR* color)
* @brief      Set Line Color
* @ingroup    GRAPHIC
*
* @param[in]  GRP2DCOLOR* color : color to lines
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void GRPCANVAS::SetLineColor(const GRP2DCOLOR* color)
{

}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         double GRPCANVAS::GetLineWidth()
* @brief      GetLineWidth
* @ingroup    GRAPHIC
*
* @return     double : line width
*
*---------------------------------------------------------------------------------------------------------------------*/
double GRPCANVAS::GetLineWidth()
{
  return linewidth;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void GRPCANVAS::SetLineWidth(double linewidth)
* @brief      SetLineWidth
* @ingroup    GRAPHIC
*
* @param[in]  linewidth : new line width
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void GRPCANVAS::SetLineWidth(double linewidth)
{
  this->linewidth = linewidth;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         double GRPCANVAS::GetDashLength()
* @brief      GetDashLength
* @ingroup    GRAPHIC
*
* @return     double : dash length
*
*---------------------------------------------------------------------------------------------------------------------*/
double GRPCANVAS::GetDashLength()
{
  return dashlength;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void GRPCANVAS::SetDashLenght(double dashlength)
* @brief      SetDashLenght
* @ingroup    GRAPHIC
*
* @param[in]  dashlength : new dash lenght
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void GRPCANVAS::SetDashLenght(double dashlength)
{
  this->dashlength = dashlength;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void GRPCANVAS::Line(double x1, double y1, double x2, double y2)
* @brief      Line
* @ingroup    GRAPHIC
*
* @param[in]  x1 :
* @param[in]  y1 :
* @param[in]  x2 :
* @param[in]  y2 :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
 void GRPCANVAS::Line(double x1, double y1, double x2, double y2)
 {

 }



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void GRPCANVAS::Rectangle(double x1, double y1, double x2, double y2, bool isfill)
* @brief      Rectangle
* @ingroup    GRAPHIC
*
* @param[in]  x1 :
* @param[in]  y1 :
* @param[in]  x2 :
* @param[in]  y2 :
* @param[in]  isfill :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void GRPCANVAS::Rectangle(double x1, double y1, double x2, double y2, bool isfill)
{

}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void GRPCANVAS::Circle(double x, double y, double radius, bool isfill)
* @brief      Circle
* @ingroup    GRAPHIC
*
* @param[in]  x : x center position
* @param[in]  y : y center position
* @param[in]  radius : radius of circle
* @param[in]  isfill : is fill
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void GRPCANVAS::Circle(double x, double y, double radius, bool isfill)
{
  Ellipse(x, y, radius, radius, isfill);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void GRPCANVAS::Ellipse(double x, double y, double rx, double ry, bool isfill)
* @brief      Ellipse
* @ingroup    GRAPHIC
*
* @param[in]  x : x center position
* @param[in]  y : y center position
* @param[in]  rx : x radius of ellipse
* @param[in]  ry : y radius of ellipse
* @param[in]  isfill : is fill
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void GRPCANVAS::Ellipse(double x, double y, double rx, double ry, bool isfill)
{

}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void GRPCANVAS::Polygon(XVECTOR* vertex, bool isfill)
* @brief      Polygon
* @ingroup    GRAPHIC
*
* @param[in]  vertexs : vector of vertex
* @param[in]  isfill : is fill
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void GRPCANVAS::Polygon(GRP2DVERTEXS& vertexs, bool isfill)
{

}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void GRPCANVAS::RoundRect(double x1, double y1, double x2, double y2, double radius, bool isfill)
* @brief      RoundRect
* @ingroup    GRAPHIC
*
* @param[in]  x1 :
* @param[in]  y1 :
* @param[in]  x2 :
* @param[in]  y2 :
* @param[in]  radius :
* @param[in]  isfill :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void GRPCANVAS::RoundRect(double x1, double y1, double x2, double y2, double radius, bool isfill)
{

}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         GRPBITMAP* GRPCANVAS::GetBitmap(double x, double y, double width, double height)
* @brief      GetBitmap
* @ingroup    GRAPHIC
*
* @param[in]  x :
* @param[in]  y :
* @param[in]  width :
* @param[in]  height :
*
* @return     GRPBITMAP* :
*
*---------------------------------------------------------------------------------------------------------------------*/
GRPBITMAP* GRPCANVAS::GetBitmap(double x, double y, double width, double height)
{
  return NULL;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void GRPCANVAS::PutBitmapNoAlpha(double x, double y, GRPBITMAP* bitmap)
* @brief      PutBitmapNoAlpha
* @ingroup    GRAPHIC
*
* @param[in]  x :
* @param[in]  y :
* @param[in]  bitmap :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void GRPCANVAS::PutBitmapNoAlpha(double x, double y, GRPBITMAP* bitmap)
{

}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void GRPCANVAS::PutBitmap(double x, double y, GRPBITMAP* bitmap)
* @brief      Draw Bitmap
* @ingroup    GRAPHIC
*
* @param[in]  x : x pos of bitmap
* @param[in]  y : y pos of bitmap
* @param[in]  bitmap : bitmap class to draw
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void GRPCANVAS::PutBitmap(double x, double y, GRPBITMAP* bitmap)
{

}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void GRPCANVAS::PutBitmapAlpha(double x, double y, GRPBITMAP* bitmap, double alpha = 100)
* @brief      PutBitmapAlpha
* @ingroup    GRAPHIC
*
* @param[in]  x :
* @param[in]  y :
* @param[in]  bitmap :
* @param[in]  alpha :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void GRPCANVAS::PutBitmapAlpha(double x, double y, GRPBITMAP* bitmap, double alpha)
{

}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void GRPCANVAS::PutBitmapFrame(double x, double y, GRPBITMAPFRAME* bitmapframe)
* @brief      Draw Bitmap Frame
* @ingroup    GRAPHIC
*
* @param[in]  x : x pos of bitmap
* @param[in]  y : y pos of bitmap
* @param[in]  bitmapframe : bitmap frame class to draw
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void GRPCANVAS::PutBitmapFrame(double x, double y, GRPBITMAPFRAME* bitmapframe, double alpha)
{
  if(!bitmapframe)              return;
  if(!bitmapframe->GetBitmap()) return;

  if(alpha == 100)
         PutBitmap(x + bitmapframe->GetAjustX(), y + bitmapframe->GetAjustY(), bitmapframe->GetBitmap());
   else  PutBitmapAlpha(x + bitmapframe->GetAjustX(), y + bitmapframe->GetAjustY(), bitmapframe->GetBitmap(), alpha);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRPCANVAS::RasterFont_Select(XCHAR* fontname)
* @brief      SelectRasterFont
* @ingroup    GRAPHIC
*
* @param[in]  fontname :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool GRPCANVAS::RasterFont_Select(XCHAR* fontname)
{
  return false;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRPCANVAS::RasterFont_Select(XSTRING& fontname)
* @brief      SelectRasterFont
* @ingroup    GRAPHIC
*
* @param[in]  fontname :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool GRPCANVAS::RasterFont_Select(XSTRING* fontname)
{
  return RasterFont_Select(fontname->Get());
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         GRP2DCOLOR* GRPCANVAS::RasterFont_GetColor()
* @brief      RasterFont_GetColor
* @ingroup    GRAPHIC
*
* @return     GRP2DCOLOR* :
*
*---------------------------------------------------------------------------------------------------------------------*/
GRP2DCOLOR* GRPCANVAS::RasterFont_GetColor()
{
  return NULL;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void GRPCANVAS::RasterFont_SetColor(const GRP2DCOLOR* c)
* @brief      RasterFont_SetColor
* @ingroup    GRAPHIC
*
* @param[in]  GRP2DCOLOR* c :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void GRPCANVAS::RasterFont_SetColor(const GRP2DCOLOR* c)
{

}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         double GRPCANVAS::RasterFont_GetWidth(XCHAR* string)
* @brief      RasterFont_GetWidth
* @ingroup    GRAPHIC
*
* @param[in]  string :
*
* @return     double :
*
*---------------------------------------------------------------------------------------------------------------------*/
double GRPCANVAS::RasterFont_GetWidth(XCHAR* string)
{
  return 0.0f;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         double GRPCANVAS::RasterFont_GetHeight()
* @brief      RasterFont_GetHeight
* @ingroup    GRAPHIC
*
* @return     double :
*
*---------------------------------------------------------------------------------------------------------------------*/
double GRPCANVAS::RasterFont_GetHeight()
{
  return 0.0f;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool GRPCANVAS::RasterFont_Printf(double x, double y, XCHAR* mask, ...)
* @brief      RasterFont_Printf
* @ingroup    GRAPHIC
*
* @param[in]  x : 
* @param[in]  y : 
* @param[in]  mask : 
* @param[in]  ... : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool GRPCANVAS::RasterFont_Printf(double x, double y, XCHAR* mask, ...)
{
  return false;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool GRPCANVAS::VectorFont_Load(XCHAR* fontnamefile)
* @brief      VectorFont_Load
* @ingroup    GRAPHIC
*
* @param[in]  fontnamefile : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool GRPCANVAS::VectorFont_Load(XCHAR* fontnamefile)
{
  XPATH fnamefile;

  fnamefile = fontnamefile;

  return VectorFont_Load(fnamefile);        
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool GRPCANVAS::VectorFont_Load(XPATH& fontnamefile)
* @brief      VectorFont_Load
* @ingroup    GRAPHIC
*
* @param[in]  fontnamefile : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool GRPCANVAS::VectorFont_Load(XPATH& fontnamefile)
{
  return false;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         GRPCANVAS_VECTORFONT_CONFIG* GRPCANVAS::Vectorfont_GetConfig()
* @brief      Vectorfont_GetConfig
* @ingroup    GRAPHIC
*
* @return     GRPCANVAS_VECTORFONT_CONFIG* : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
GRPCANVAS_VECTORFONT_CONFIG* GRPCANVAS::Vectorfont_GetConfig()
{
  return &vectorfont_config;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         double GRPCANVAS::VectorFont_GetWidth(XCHAR*string)
* @brief      VectorFont_GetWidth
* @ingroup    GRAPHIC
*
* @param[in]  XCHAR*string : 
* 
* @return     double : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
double GRPCANVAS::VectorFont_GetWidth(XCHAR*string)
{
  return 0.0f;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         double GRPCANVAS::VectorFont_GetHeight(XCHAR* string)
* @brief      VectorFont_GetHeight
* @ingroup    GRAPHIC
*
* @param[in]  string : 
* 
* @return     double : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
double GRPCANVAS::VectorFont_GetHeight(XCHAR* string)
{
  return 0.0f;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         double GRPCANVAS::VectorFont_GetHeight()
* @brief      VectorFont_GetHeight
* @ingroup    GRAPHIC
*
* @return     double : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
double GRPCANVAS::VectorFont_GetHeight()
{
  return 0.0f;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool GRPCANVAS::VectorFont_Print(double x, double y, XCHAR* outstring)
* @brief      VectorFont_Print
* @ingroup    GRAPHIC
*
* @param[in]  x : 
* @param[in]  y : 
* @param[in]  outstring : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool GRPCANVAS::VectorFont_Print(double x, double y, XCHAR* outstring)
{
  return false;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool GRPCANVAS::VectorFont_Printf(double x, double y, XCHAR* mask, ...)
* @brief      VectorFont_Printf
* @ingroup    GRAPHIC
*
* @param[in]  x : 
* @param[in]  y : 
* @param[in]  mask : 
* @param[in]  ... : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool GRPCANVAS::VectorFont_Printf(double x, double y, XCHAR* mask, ...)
{
  return false;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRPCANVAS::CopyByfferRenderToScreen(GRPSCREEN* screen)
* @brief      Copy Buffer Render To Screen
* @ingroup    GRAPHIC
*
* @param[in]  screen : screen handle
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool GRPCANVAS::CopyBufferRenderToScreen(GRPSCREEN* screen)
{
  return false;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRPCANVAS::CopyBufferRenderToBufferScreen(XBYTE* buffer, XDWORD width, XDWORD height, bool isinverse)
* @brief      CopyBufferRenderToBufferScreen
* @ingroup    GRAPHIC
*
* @param[in]  buffer :
* @param[in]  width :
* @param[in]  height :
* @param[in]  isinverse :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool GRPCANVAS::CopyBufferRenderToBufferScreen(XBYTE* buffer, XDWORD width, XDWORD height, bool isinverse)
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRPCANVAS::CopyBufferRenderFromViewport(GRPVIEWPORT* viewport)
* @brief      CopyBufferRenderFromViewport
* @ingroup    GRAPHIC
*
* @param[in]  viewport :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool GRPCANVAS::CopyBufferRenderFromViewport(GRPVIEWPORT* viewport)
{
  return false;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool GRPCANVAS::ReleaseDrawFramerate()
* @brief      ReleaseDrawFramerate
* @ingroup    GRAPHIC
*
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool GRPCANVAS::ReleaseDrawFramerate()
{
  return false;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool GRPCANVAS::DrawFramerate(double x, double y, GRPSCREEN* screen)
* @brief      DrawFramerate
* @ingroup    GRAPHIC
*
* @param[in]  x : 
* @param[in]  y : 
* @param[in]  screen : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool GRPCANVAS::DrawFramerate(double x, double y, GRPSCREEN* screen)
{
  return false;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void GRPCANVAS::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    GRAPHIC
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void GRPCANVAS::Clean()
{
  linewidth     = 1.0f;
  dashlength    = 1.0f;
}

