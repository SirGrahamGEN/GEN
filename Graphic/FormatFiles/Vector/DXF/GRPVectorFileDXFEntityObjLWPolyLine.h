/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       GRPVectorFileDXFEntityObjLWPolyLine.h
* 
* @class      GRPVECTORFILEDXFENTITYOBJLWPOLYLINE
* @brief      Graphic Vector File DXF Entity Obj LWPolyLine class
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

#ifndef _GRPVECTORFILEDXFENTITYOBJLWPOLYLINE_H_
#define _GRPVECTORFILEDXFENTITYOBJLWPOLYLINE_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "XString.h"

#include "GRPVectorFileDXFEntityDefPoint.h"
#include "GRPVectorFileDXFEntityObj.h"

#pragma endregion


/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/
#pragma region DEFINES_ENUMS


#pragma endregion


/*---- CLASS ---------------------------------------------------------------------------------------------------------*/
#pragma region CLASS


class GRPVECTORFILEDXFENTITYOBJLWPOLYLINE : public GRPVECTORFILEDXFENTITYOBJ
{  
  public:       
                                          GRPVECTORFILEDXFENTITYOBJLWPOLYLINE       (XCHAR* nametype);
    virtual                              ~GRPVECTORFILEDXFENTITYOBJLWPOLYLINE       ();

    int                                   GetNVertex                                (); 
    void                                  SetNVertex                                (int nvertex);

    int                                   GetPolyLineFlag                           (); 
    void                                  SetPolyLineFlag                           (int polylineflag);

    double                                GetConstantWidth                          (); 
    void                                  SetConstantWidth                          (double constantwidth);

    double                                GetElevation                              (); 
    void                                  SetElevation                              (double elevation); 
  
    double                                GetThickness                              (); 
    void                                  SetThickness                              (double thickness);
    
    GRPVECTORFILEDXFENTITYDEFPOINT*       GetDirExtrusion                           (); 
    bool                                  SetDirExtrusion                           (GRPVECTORFILEDXFENTITYDEFPOINT* dirextrusion);

    virtual bool                          ApplyData                                 (GRPVECTORFILEDXFENTITY* entity);
        
  private: 
   
    void                                  Clean                                     ();   
      
    int                                   nvertex;                                  // Number of vertices.
    
    int                                   polylineflag;                             // Polyline flag (bit-coded); default is 0: 1 = closed 128 = plinegen
    double                                constantwidth;                            // Constant width (optional; default = 0) Not used if variable width (codes 40 and/or 41) is set.
    double                                elevation;                                // Elevation (optional; default = 0)               
      
    double                                thickness;                                // Thickness (default=0.0).

    GRPVECTORFILEDXFENTITYDEFPOINT        dirextrusion;                             // Extrusion direction.
};


#pragma endregion


/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/
#pragma region FUNCTIONS_PROTOTYPES


#pragma endregion


#endif



