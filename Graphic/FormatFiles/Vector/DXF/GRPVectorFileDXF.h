/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       GRPVectorFileDXF.h
* 
* @class      GRPVECTORFILEDXF
* @brief      Graphic Vector File DXF class
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

#ifndef _GRPVECTORFILEDXF_H_
#define _GRPVECTORFILEDXF_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "XInheritEnum.h"
#include "XString.h"
#include "XVariant.h"

#include "GRPVectorFileDXFConfig.h"
#include "GRPVectorFileDXFTextSection.h"

#include "GRPVectorFile.h"

#pragma endregion


/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/
#pragma region DEFINES_ENUMS

enum GRPVECTORFILEDXFRESULTADD
{
  GRPVECTORFILEDXFRESULT_NOTSECTIONS       =   GRPVECTORFILERESULT_LASTCOMMON ,
  GRPVECTORFILEDXFRESULT_INVALIDSECTION                                       ,
};

typedef XINHERITENUM<GRPVECTORFILEDXFRESULTADD, GRPVECTORFILERESULT > GRPVECTORFILEDXFRESULT;

#define GRPVECTORFILEDXF_EXTENSION      __L(".dxf")

#define TEST_NOT_CONCRETE_ENTITY

#pragma endregion


/*---- CLASS ---------------------------------------------------------------------------------------------------------*/
#pragma region CLASS

class XFILETXT;
class GRPVECTORFILEDXFTEXTSECTIONENTITIES;
class GRPVECTORFILECONFIG;
class GRPVECTORFILEDXFENTITYOBJ;

#pragma endregion


/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/
#pragma region FUNCTIONS_PROTOTYPES


class GRPVECTORFILEDXF : public GRPVECTORFILE
{
  public:
                                              GRPVECTORFILEDXF                ();
    virtual                                  ~GRPVECTORFILEDXF                ();
    
    GRPVECTORFILERESULT                       DetectType                      ();
    GRPVECTORFILERESULT                       Load                            ();

    GRPVECTORFILECONFIG*                      GetConfig                       ();
    
    XVECTOR<GRPVECTORFILEDXFTEXTSECTION*>*    GetSections                     (); 
    GRPVECTORFILEDXFTEXTSECTION*              GetSection                      (GRPVECTORFILEDXFTEXTSECTION_TYPESECTION type);    
    
    static bool                               ParserTextFilePrepareLine       (XSTRING* line);
    
  private:
  
    GRPVECTORFILEDXFRESULT                    ParserTextSections              (XFILETXT* file, XVECTOR<GRPVECTORFILEDXFTEXTSECTION*>& sections);
    bool                                      ParserHaveAnySection            (XFILETXT* fileTXT, int nlinesmax = 100);
    GRPVECTORFILEDXFRESULT                    ParserTextFile                  (XFILETXT* fileTXT);

    #ifdef XTRACE_ACTIVE
    bool                                      GenerateSectionsEntities        (GRPVECTORFILEDXFTEXTSECTIONENTITIES* sectionentities, XSTRING& line);  
    bool                                      ShowTraceAllSections            ();
    #endif

    void                                      Clean                           ();

    XVECTOR<GRPVECTORFILEDXFTEXTSECTION*>     sections;    
    GRPVECTORFILEDXFCONFIG                    config;     
};


#pragma endregion


#endif



