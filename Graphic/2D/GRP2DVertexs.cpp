/**-------------------------------------------------------------------------------------------------------------------
*
* @file       GRP2DVertex.cpp
*
* @class      GRP2DVERTEX
* @brief      Grpahics 2D Vertex
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

#include "GRP2DVertexs.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         GRP2DVERTEX::GRP2DVERTEX()
* @brief      Constructor
* @ingroup    GRAPHIC
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
GRP2DVERTEX::GRP2DVERTEX()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         GRP2DVERTEX::~GRP2DVERTEX()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    GRAPHIC
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
GRP2DVERTEX::~GRP2DVERTEX()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void GRP2DVERTEX::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    GRAPHIC
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void GRP2DVERTEX::Clean()
{
   x = 0;
   y = 0;
}





/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         GRP2DVERTEXS::GRP2DVERTEXS()
* @brief      Constructor
* @ingroup    GRAPHIC
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
GRP2DVERTEXS::GRP2DVERTEXS()
{
  Clean();
}





/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         GRP2DVERTEXS::~GRP2DVERTEXS()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    GRAPHIC
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
GRP2DVERTEXS::~GRP2DVERTEXS()
{
  DeleteAll();

  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRP2DVERTEXS::Add(double x, double y)
* @brief      Add Vertex
* @ingroup    GRAPHIC
*
* @param[in]  x : x pos
* @param[in]  y : y pos
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool GRP2DVERTEXS::Add(double x, double y)
{
  GRP2DVERTEX* vertex = new GRP2DVERTEX();
  if(!vertex) return false;

  vertex->x = x;
  vertex->y = y;

  return vertexs.Add(vertex);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD GRP2DVERTEXS::GetSize()
* @brief      Get number of vertex
* @ingroup    GRAPHIC
*
* @return     XDWORD : number of vertex
*
*---------------------------------------------------------------------------------------------------------------------*/
XDWORD GRP2DVERTEXS::GetSize()
{
  return vertexs.GetSize();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         GRP2DVERTEX* GRP2DVERTEXS::Get(int index)
* @brief      Get Vertex
* @ingroup    GRAPHIC
*
* @param[in]  index : index of vertex
*
* @return     GRP2DVERTEX* : vertex class
*
*---------------------------------------------------------------------------------------------------------------------*/
GRP2DVERTEX* GRP2DVERTEXS::Get(int index)
{
  return vertexs.Get(index);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRP2DVERTEXS::DeleteAll()
* @brief      Delete All
* @ingroup    GRAPHIC
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool GRP2DVERTEXS::DeleteAll()
{
  if(vertexs.IsEmpty()) return true;

  vertexs.DeleteContents();

  return true;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void GRP2DVERTEXS::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    GRAPHIC
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void GRP2DVERTEXS::Clean()
{

}




