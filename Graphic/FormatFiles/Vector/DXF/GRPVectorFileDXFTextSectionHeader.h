/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       GRPVectorFileDXFTextSectionHeader.h
* 
* @class      GRPVECTORFILEDXFTEXTSECTIONHEADER
* @brief      Graphic Vector File DXF Entity Text Section Header class
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

#ifndef _GRPVECTORFILEDXFTEXTSECTIONHEADER_H_
#define _GRPVECTORFILEDXFTEXTSECTIONHEADER_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "XMap.h"
#include "XVariant.h"
#include "XString.h"
#include "XFileTXT.h"

#include "GRPVectorFile.h"
#include "GRPVectorFileDXFTextSection.h"

#pragma endregion


/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/
#pragma region DEFINES_ENUMS

#define GRPVECTORFILEDXFTEXTSECTIONHEADER_MAXNDEFVAR    283
#define GRPVECTORFILEDXFTEXTSECTIONHEADER_MAXNVAR       3

#pragma endregion


/*---- CLASS ---------------------------------------------------------------------------------------------------------*/
#pragma region CLASS


typedef struct
{
  int                                                       valuetype;
  XCHAR*                                                    valuename;   

} GRPVECTORFILEDXFTEXTSECTIONHEADERDEFVALUE;


typedef struct
{
  XCHAR*                                                    name;
  int                                                       nvalues;
  GRPVECTORFILEDXFTEXTSECTIONHEADERDEFVALUE                 value[GRPVECTORFILEDXFTEXTSECTIONHEADER_MAXNVAR];
  XCHAR*                                                    remark;

} GRPVECTORFILEDXFTEXTSECTIONHEADERDEFVARIABLE;


class GRPVECTORFILEDXFTEXTSECTIONHEADER : public GRPVECTORFILEDXFTEXTSECTION
{
  public:
                                                            GRPVECTORFILEDXFTEXTSECTIONHEADER         ();
    virtual                                                ~GRPVECTORFILEDXFTEXTSECTIONHEADER         ();
    
    bool                                                    IsKnownVariable                           (XSTRING& namevar);
    bool                                                    AddVariable                               (XCHAR* namevar, XVARIANT* variant);
    XMAP<XSTRING*, XVARIANT*>*                              GetVariables                              ();
    XVARIANT*                                               GetVariable                               (XCHAR* namevar);
    bool                                                    DeleteVariable                            (XCHAR* namevar);
    bool                                                    DeleteAllVariables                        (bool withcontents = true);
    XCHAR*                                                  GetVariableRemark                         (XSTRING& namevar);

    bool                                                    ParserVariable                            (XFILETXT* file, GRPVECTORFILEDXFTEXTPART* part, XCHAR* namevar, ...);
    GRPVECTORFILERESULT                                     ParserTextSection                         (XFILETXT* fileTXT);
   
    #ifdef XTRACE_ACTIVE
    bool                                                    ShowTraceAllVariables                     ();
    #endif

    static GRPVECTORFILEDXFTEXTSECTIONHEADERDEFVARIABLE     defvariable[GRPVECTORFILEDXFTEXTSECTIONHEADER_MAXNDEFVAR];

  private:
    
    void                                                    Clean                                     ();

    XMAP<XSTRING*, XVARIANT*>                               variables;
};


#pragma endregion


/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/
#pragma region FUNCTIONS_PROTOTYPES


#pragma endregion


#endif




