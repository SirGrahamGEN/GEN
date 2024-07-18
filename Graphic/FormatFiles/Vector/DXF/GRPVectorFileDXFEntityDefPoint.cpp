/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       GRPVectorFileDXFEntityDefPoint.cpp
* 
* @class      GRPVECTORFILEDXFENTITYDEFPOINT
* @brief      Graphic Vector File DXF DefPoint class
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
#pragma region PRECOMPILATION_INCLUDES

#include "GEN_Defines.h"

#pragma endregion


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "GRPVectorFileDXFEntityDefPoint.h"

#include "XMemory_Control.h"

#pragma endregion


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         GRPVECTORFILEDXFENTITYDEFPOINT::GRPVECTORFILEDXFENTITYDEFPOINT()
* @brief      Constructor
* @ingroup    GRAPHIC
* 
* --------------------------------------------------------------------------------------------------------------------*/
GRPVECTORFILEDXFENTITYDEFPOINT::GRPVECTORFILEDXFENTITYDEFPOINT()
{
  Clean();   
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         GRPVECTORFILEDXFENTITYDEFPOINT::GRPVECTORFILEDXFENTITYDEFPOINT(double xpoint, double ypoint, double zpoint)
* @brief      Constructor
* @ingroup    GRAPHIC
* 
* @param[in]  double : 
* @param[in]   double ypoint : 
* @param[in]   double zpoint : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
GRPVECTORFILEDXFENTITYDEFPOINT::GRPVECTORFILEDXFENTITYDEFPOINT(double xpoint, double ypoint, double zpoint)
{
  Clean(); 

  this->xpoint = xpoint;
  this->ypoint = ypoint;
  this->zpoint = zpoint;
}

      
/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         GRPVECTORFILEDXFENTITYDEFPOINT::GRPVECTORFILEDXFENTITYDEFPOINT(GRPVECTORFILEDXFENTITYDEFPOINT* point)
* @brief      Constructor
* @ingroup    GRAPHIC
* 
* @param[in]  GRPVECTORFILEDXFENTITYDEFPOINT* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
GRPVECTORFILEDXFENTITYDEFPOINT::GRPVECTORFILEDXFENTITYDEFPOINT(GRPVECTORFILEDXFENTITYDEFPOINT* point)
{
  Clean();

  CopyFrom (point);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         GRPVECTORFILEDXFENTITYDEFPOINT::~GRPVECTORFILEDXFENTITYDEFPOINT()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    GRAPHIC
* 
* --------------------------------------------------------------------------------------------------------------------*/
GRPVECTORFILEDXFENTITYDEFPOINT::~GRPVECTORFILEDXFENTITYDEFPOINT()
{ 
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void GRPVECTORFILEDXFENTITYDEFPOINT::operator = (GRPVECTORFILEDXFENTITYDEFPOINT* point)
* @brief      operator =
* @ingroup    GRAPHIC
* 
* @param[in]  point : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void GRPVECTORFILEDXFENTITYDEFPOINT::operator =  (GRPVECTORFILEDXFENTITYDEFPOINT* point)
{
  CopyFrom(point);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void GRPVECTORFILEDXFENTITYDEFPOINT::operator = (GRPVECTORFILEDXFENTITYDEFPOINT point)
* @brief      operator =
* @ingroup    GRAPHIC
* 
* @param[in]  point : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void GRPVECTORFILEDXFENTITYDEFPOINT::operator =  (GRPVECTORFILEDXFENTITYDEFPOINT point)
{
  CopyFrom(&point);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         double GRPVECTORFILEDXFENTITYDEFPOINT::GetX()
* @brief      GetX
* @ingroup    GRAPHIC
* 
* @return     double : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
double GRPVECTORFILEDXFENTITYDEFPOINT::GetX() 
{ 
  return xPoint; 
}
     
     
/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void GRPVECTORFILEDXFENTITYDEFPOINT::SetX(double xpoint)
* @brief      SetX
* @ingroup    GRAPHIC
* 
* @param[in]  xpoint : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void GRPVECTORFILEDXFENTITYDEFPOINT::SetX(double xpoint) 
{ 
  this->xpoint = xpoint; 
} 


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         double GRPVECTORFILEDXFENTITYDEFPOINT::GetY()
* @brief      GetY
* @ingroup    GRAPHIC
* 
* @return     double : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
double GRPVECTORFILEDXFENTITYDEFPOINT::GetY() 
{ 
  return ypoint; 
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void GRPVECTORFILEDXFENTITYDEFPOINT::SetY(double ypoint)
* @brief      SetY
* @ingroup    GRAPHIC
* 
* @param[in]  ypoint : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void GRPVECTORFILEDXFENTITYDEFPOINT::SetY(double ypoint) 
{ 
  this->ypoint = ypoint; 
}
      
      
/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         double GRPVECTORFILEDXFENTITYDEFPOINT::GetZ()
* @brief      GetZ
* @ingroup    GRAPHIC
* 
* @return     double : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
double GRPVECTORFILEDXFENTITYDEFPOINT::GetZ() 
{ 
  return zpoint;  
}    

    
/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void GRPVECTORFILEDXFENTITYDEFPOINT::SetZ(double zpoint)
* @brief      SetZ
* @ingroup    GRAPHIC
* 
* @param[in]  zpoint : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void GRPVECTORFILEDXFENTITYDEFPOINT::SetZ(double zpoint) 
{ 
  this->zpoint = zpoint; 
} 


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool GRPVECTORFILEDXFENTITYDEFPOINT::CopyTo(GRPVECTORFILEDXFENTITYDEFPOINT* point)
* @brief      CopyTo
* @ingroup    GRAPHIC
* 
* @param[in]  point : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPVECTORFILEDXFENTITYDEFPOINT::CopyTo(GRPVECTORFILEDXFENTITYDEFPOINT* point)
{
  if(!point) 
    {
      return false;
    }

  point->SetX(xpoint);
  point->SetY(ypoint);
  point->SetZ(zpoint);

  return true;
}
      

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool GRPVECTORFILEDXFENTITYDEFPOINT::CopyFrom(GRPVECTORFILEDXFENTITYDEFPOINT* point)
* @brief      CopyFrom
* @ingroup    GRAPHIC
* 
* @param[in]  point : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPVECTORFILEDXFENTITYDEFPOINT::CopyFrom(GRPVECTORFILEDXFENTITYDEFPOINT* point)
{
  if(!point)
    {
      return false;
    }

  xpoint = point->GetX();
  ypoint = point->GetY();
  zpoint = point->GetY();

  return true;
}   


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void GRPVECTORFILEDXFENTITYDEFPOINT::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    GRAPHIC
* 
* --------------------------------------------------------------------------------------------------------------------*/
void GRPVECTORFILEDXFENTITYDEFPOINT::Clean()
{
  xpoint = 0.0f;
  ypoint = 0.0f;  
  zpoint = 0.0f;
}


#pragma endregion

















GRPVECTORFILEDXFENTITYDEFPOINT::GRPVECTORFILEDXFENTITYDEFPOINT ( )
{
   Clean();   
}


GRPVECTORFILEDXFENTITYDEFPOINT::GRPVECTORFILEDXFENTITYDEFPOINT ( double xPoint , double yPoint , double zPoint )
{
   Clean(); 

   this->xPoint = xPoint;
   this->yPoint = yPoint;
   this->zPoint = zPoint;
}

      
GRPVECTORFILEDXFENTITYDEFPOINT::GRPVECTORFILEDXFENTITYDEFPOINT ( GRPVECTORFILEDXFENTITYDEFPOINT* point )
{
   Clean();

   CopyFrom (point);
}


GRPVECTORFILEDXFENTITYDEFPOINT::~GRPVECTORFILEDXFENTITYDEFPOINT ( )
{ 
   Clean();
}


void GRPVECTORFILEDXFENTITYDEFPOINT::operator =  (GRPVECTORFILEDXFENTITYDEFPOINT* point)
{
  CopyFrom(point);
}


void GRPVECTORFILEDXFENTITYDEFPOINT::operator =  (GRPVECTORFILEDXFENTITYDEFPOINT point)
{
  CopyFrom(&point);
}


double GRPVECTORFILEDXFENTITYDEFPOINT::GetX () 
{ 
   return xPoint; 
}
     
     
void GRPVECTORFILEDXFENTITYDEFPOINT::SetX ( double xPoint ) 
{ 
   this->xPoint = xPoint; 
} 


double GRPVECTORFILEDXFENTITYDEFPOINT::GetY () 
{ 
   return yPoint; 
}


void GRPVECTORFILEDXFENTITYDEFPOINT::SetY ( double yPoint ) 
{ 
   this->yPoint = yPoint; 
}
      
      
double GRPVECTORFILEDXFENTITYDEFPOINT::GetZ () 
{ 
   return zPoint ; 
};    

    
void GRPVECTORFILEDXFENTITYDEFPOINT::SetZ ( double zPoint ) 
{ 
   this->zPoint = zPoint; 
} 


bool GRPVECTORFILEDXFENTITYDEFPOINT::CopyTo ( GRPVECTORFILEDXFENTITYDEFPOINT* point )
{
   if(!point) 
   {
      return false;
   }

   point->SetX(xPoint);
   point->SetY(yPoint);
   point->SetZ(zPoint);

   return true;
}
      

bool GRPVECTORFILEDXFENTITYDEFPOINT::CopyFrom ( GRPVECTORFILEDXFENTITYDEFPOINT* point )
{
   if(!point)
   {
      return false;
   }

   xPoint = point->GetX();
   yPoint = point->GetY();
   zPoint = point->GetY();

   return true;
}
   

void GRPVECTORFILEDXFENTITYDEFPOINT::Clean ( )
{
   xPoint = 0.0f;
   yPoint = 0.0f;  
   zPoint = 0.0f;
}
