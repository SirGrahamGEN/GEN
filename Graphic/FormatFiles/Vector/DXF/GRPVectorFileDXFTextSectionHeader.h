
#ifndef _GRPVECTORFILEDXFTEXTSECTIONHEADER_h_
#define _GRPVECTORFILEDXFTEXTSECTIONHEADER_h_

#pragma region INCLUDES

#include "XMap.h"
#include "XVariant.h"
#include "XString.h"
#include "XFileTXT.h"

#include "GRPVectorFile.h"
#include "GRPVectorFileDXFTextSection.h"

#pragma endregion


#pragma region DEFINES_ENUMS

#define GRPVECTORFILEDXFTEXTSECTIONHEADER_MaxNDefVar  283
#define GRPVECTORFILEDXFTEXTSECTIONHEADER_MaxNVar     3

#pragma endregion


#pragma region CLASSES

typedef struct
{
   int valuetype;
   XCHAR* valuename;   

} GRPVECTORFILEDXFTEXTSECTIONHEADERDefValue;


typedef struct
{
   XCHAR* name;
   int nvalues;
   GRPVECTORFILEDXFTEXTSECTIONHEADERDefValue value[GRPVECTORFILEDXFTEXTSECTIONHEADER_MaxNVar];
   XCHAR* remark;

} GRPVECTORFILEDXFTEXTSECTIONHEADERDefVariable;


class GRPVECTORFILEDXFTEXTSECTIONHEADER : public GRPVECTORFILEDXFTEXTSECTION
{
  public:

    GRPVECTORFILEDXFTEXTSECTIONHEADER ();
    virtual ~GRPVECTORFILEDXFTEXTSECTIONHEADER ();
    
    bool IsKnownVariable( XSTRING& namevar );
    bool AddVariable ( XCHAR* namevar, XVARIANT* variant );
    XMAP<XSTRING*, XVARIANT*>* GetVariables ();
    XVARIANT* GetVariable ( XCHAR* namevar );
    bool DeleteVariable ( XCHAR* namevar );
    bool DeleteAllVariables ( bool withcontents = true );
    XCHAR* GetVariableRemark( XSTRING& namevar );

    bool ParserVariable ( XFILETXT* file, GRPVECTORFILEDXFTextPart* part, XCHAR* namevar, ... );
    GRPVECTORFILERESULT ParserTextSection ( XFILETXT* fileTXT );
   
    #ifdef XTRACE_ACTIVE
    bool ShowTraceAllVariables ();
    #endif

    static GRPVECTORFILEDXFTEXTSECTIONHEADERDefVariable defvariable[GRPVECTORFILEDXFTEXTSECTIONHEADER_MaxNDefVar];

  private:
    
    void Clean ();

    XMAP<XSTRING*, XVARIANT*> variables;
};

#pragma endregion


#pragma region EXTERN_INLINE_FUNCTIONS
#pragma endregion

#endif

