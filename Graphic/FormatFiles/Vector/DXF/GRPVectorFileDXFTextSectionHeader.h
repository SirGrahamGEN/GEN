
#ifndef _GRPVECTORFILEDXFTextSectionHeader_h_
#define _GRPVECTORFILEDXFTextSectionHeader_h_

#pragma region INCLUDES

#include "XMap.h"
#include "XVariant.h"
#include "XString.h"
#include "XFileTXT.h"

#include "GRPVectorFile.h"
#include "GRPVECTORFILEDXFTextSection.h"

#pragma endregion


#pragma region DEFINES_ENUMS

#define GRPVECTORFILEDXFTextSectionHeader_MaxNDefVar  283
#define GRPVECTORFILEDXFTextSectionHeader_MaxNVar     3

#pragma endregion


#pragma region CLASSES

typedef struct
{
   int valuetype;
   XCHAR* valuename;   

} GRPVECTORFILEDXFTextSectionHeaderDefValue;


typedef struct
{
   XCHAR* name;
   int nvalues;
   GRPVECTORFILEDXFTextSectionHeaderDefValue value[GRPVECTORFILEDXFTextSectionHeader_MaxNVar];
   XCHAR* remark;

} GRPVECTORFILEDXFTextSectionHeaderDefVariable;


class GRPVECTORFILEDXFTextSectionHeader : public GRPVECTORFILEDXFTextSection
{
  public:

    GRPVECTORFILEDXFTextSectionHeader ();
    virtual ~GRPVECTORFILEDXFTextSectionHeader ();
    
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

    static GRPVECTORFILEDXFTextSectionHeaderDefVariable defvariable[GRPVECTORFILEDXFTextSectionHeader_MaxNDefVar];

  private:
    
    void Clean ();

    XMAP<XSTRING*, XVARIANT*> variables;
};

#pragma endregion


#pragma region EXTERN_INLINE_FUNCTIONS
#pragma endregion

#endif

