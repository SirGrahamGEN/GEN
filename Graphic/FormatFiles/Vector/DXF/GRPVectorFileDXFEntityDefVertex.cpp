/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       GRPVECTORFILEDXFENTITYDEFVERTEX.cpp
* 
* @class      GRPVECTORFILEDXFENTITYDEFVERTEX
* @brief      Graphic Vector File DXF Entity DefVertex class
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

#include "GRPVectorFileDXFEntityDefVertex.h"

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
* @fn         GRPVECTORFILEDXFENTITYDEFVERTEX::GRPVECTORFILEDXFENTITYDEFVERTEX()
* @brief      Constructor of class
* @ingroup    GRAPHIC
* 
* --------------------------------------------------------------------------------------------------------------------*/
GRPVECTORFILEDXFENTITYDEFVERTEX::GRPVECTORFILEDXFENTITYDEFVERTEX()
{
  Clean();   
}
 
 
/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         GRPVECTORFILEDXFENTITYDEFVERTEX::GRPVECTORFILEDXFENTITYDEFVERTEX(GRPVECTORFILEDXFENTITYDEFVERTEX* vertex)
* @brief      Constructor of class
* @ingroup    GRAPHIC
* 
* @param[in]  vertex : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
GRPVECTORFILEDXFENTITYDEFVERTEX::GRPVECTORFILEDXFENTITYDEFVERTEX(GRPVECTORFILEDXFENTITYDEFVERTEX* vertex)
{
  Clean();

  CopyFrom(vertex);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         GRPVECTORFILEDXFENTITYDEFVERTEX::~GRPVECTORFILEDXFENTITYDEFVERTEX()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    GRAPHIC
* 
* --------------------------------------------------------------------------------------------------------------------*/
GRPVECTORFILEDXFENTITYDEFVERTEX::~GRPVECTORFILEDXFENTITYDEFVERTEX()
{ 
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void GRPVECTORFILEDXFENTITYDEFVERTEX::operator = (GRPVECTORFILEDXFENTITYDEFVERTEX* vertex)
* @brief      operator = 
* @ingroup    GRAPHIC
* 
* @param[in]  vertex : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void GRPVECTORFILEDXFENTITYDEFVERTEX::operator =  (GRPVECTORFILEDXFENTITYDEFVERTEX* vertex)
{
  CopyFrom(vertex);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void GRPVECTORFILEDXFENTITYDEFVERTEX::operator = (GRPVECTORFILEDXFENTITYDEFVERTEX vertex)
* @brief      operator = 
* @ingroup    GRAPHIC
* 
* @param[in]  vertex : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void GRPVECTORFILEDXFENTITYDEFVERTEX::operator =  (GRPVECTORFILEDXFENTITYDEFVERTEX vertex)
{
  CopyFrom(&vertex);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         GRPVECTORFILEDXFENTITYDEFPOINT* GRPVECTORFILEDXFENTITYDEFVERTEX::GetPoint()
* @brief      Get point
* @ingroup    GRAPHIC
* 
* @return     GRPVECTORFILEDXFENTITYDEFPOINT* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
GRPVECTORFILEDXFENTITYDEFPOINT* GRPVECTORFILEDXFENTITYDEFVERTEX::GetPoint()
{
  return &point;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool GRPVECTORFILEDXFENTITYDEFVERTEX::SetPoint(GRPVECTORFILEDXFENTITYDEFPOINT* point)
* @brief      Set point
* @ingroup    GRAPHIC
* 
* @param[in]  point : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPVECTORFILEDXFENTITYDEFVERTEX::SetPoint(GRPVECTORFILEDXFENTITYDEFPOINT* point)
{
  if(!point) return false;

  this->point = point;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         double GRPVECTORFILEDXFENTITYDEFVERTEX::GetIniWidth()
* @brief      Get ini width
* @ingroup    GRAPHIC
* 
* @return     double : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
double GRPVECTORFILEDXFENTITYDEFVERTEX::GetIniWidth()
{
  return iniwidth;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void GRPVECTORFILEDXFENTITYDEFVERTEX::SetIniWidth (double iniwidth)
* @brief      Set ini width 
* @ingroup    GRAPHIC
* 
* @param[in]  iniwidth : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void GRPVECTORFILEDXFENTITYDEFVERTEX::SetIniWidth (double iniwidth)
{
  this->iniwidth = iniwidth;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         double GRPVECTORFILEDXFENTITYDEFVERTEX::GetEndWidth()
* @brief      Get end width
* @ingroup    GRAPHIC
* 
* @return     double : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
double GRPVECTORFILEDXFENTITYDEFVERTEX::GetEndWidth()
{
   return endwidth;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void GRPVECTORFILEDXFENTITYDEFVERTEX::SetEndWidth(double endwidth)
* @brief      Set end width
* @ingroup    GRAPHIC
* 
* @param[in]  endwidth : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void GRPVECTORFILEDXFENTITYDEFVERTEX::SetEndWidth(double endwidth)
{
  this->endwidth = endwidth;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         double GRPVECTORFILEDXFENTITYDEFVERTEX::GetBulge()
* @brief      Get bulge
* @ingroup    GRAPHIC
* 
* @return     double : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
double GRPVECTORFILEDXFENTITYDEFVERTEX::GetBulge()
{
  return bulge;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void GRPVECTORFILEDXFENTITYDEFVERTEX::SetBulge(double bulge)
* @brief      Set bulge
* @ingroup    GRAPHIC
* 
* @param[in]  bulge : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void GRPVECTORFILEDXFENTITYDEFVERTEX::SetBulge(double bulge)
{
   this->bulge = bulge;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool GRPVECTORFILEDXFENTITYDEFVERTEX::CopyTo(GRPVECTORFILEDXFENTITYDEFVERTEX* vertex)
* @brief      Copy to
* @ingroup    GRAPHIC
* 
* @param[in]  vertex : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPVECTORFILEDXFENTITYDEFVERTEX::CopyTo(GRPVECTORFILEDXFENTITYDEFVERTEX* vertex)
{
  if(!vertex) 
    {
      return false;
    }

  vertex->SetPoint(&point);
  vertex->SetIniWidth(iniwidth);
  vertex->SetEndWidth(endwidth);
  vertex->SetBulge(bulge);
   
  return true;
}
      

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool GRPVECTORFILEDXFENTITYDEFVERTEX::CopyFrom(GRPVECTORFILEDXFENTITYDEFVERTEX* vertex)
* @brief      Copy from
* @ingroup    GRAPHIC
* 
* @param[in]  vertex : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPVECTORFILEDXFENTITYDEFVERTEX::CopyFrom(GRPVECTORFILEDXFENTITYDEFVERTEX* vertex)
{
  if(!vertex)
    {
      return false;
    }

  point     = vertex->GetPoint();
  iniwidth  = vertex->GetIniWidth();
  endwidth  = vertex->GetEndWidth();
  bulge     = vertex->GetBulge();
  
  return true;
}
   

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void GRPVECTORFILEDXFENTITYDEFVERTEX::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    GRAPHIC
* 
* --------------------------------------------------------------------------------------------------------------------*/
void GRPVECTORFILEDXFENTITYDEFVERTEX::Clean()
{   
  iniwidth  = 0.0f;     // Start width.
  endwidth  = 0.0f;     // End width.
  bulge     = 0.0f;     // Bulge.
}


#pragma endregion

