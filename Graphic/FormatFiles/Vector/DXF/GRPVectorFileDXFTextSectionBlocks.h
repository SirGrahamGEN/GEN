
#ifndef _GRPVECTORFILEDXFTextSectionBlocks_h_
#define _GRPVECTORFILEDXFTextSectionBlocks_h_

#pragma region INCLUDES

#include "XMap.h"
#include "XVariant.h"
#include "XString.h"

#include "GRPVECTORFILEDXFTextSection.h"

#pragma endregion


#pragma region DEFINES_ENUMS

#define GRPVECTORFILEDXFBlocks_MaxNDefBlocks 2
#define GRPVECTORFILEDXFBlocks_MaxNDefTypes  35

#undef TEST_ONLY_DEFINE_IN_BLOCKS

#pragma endregion


#pragma region CLASSES

class GRPVECTORFILEDXFTextBlock;

typedef struct
{
   int type;
   XCHAR* name;   
   XCHAR* remark;   

} GRPVECTORFILEDXFTextSectionBlockDefType;


typedef struct
{
   XCHAR* name;
   int ntypes;
   bool isendblock;
   GRPVECTORFILEDXFTextSectionBlockDefType type[GRPVECTORFILEDXFBlocks_MaxNDefTypes];

} GRPVECTORFILEDXFTextSectionBlockDef;



class GRPVECTORFILEDXFTextSectionBlocks : public GRPVECTORFILEDXFTextSection
{
  public:

    GRPVECTORFILEDXFTextSectionBlocks ();
    virtual ~GRPVECTORFILEDXFTextSectionBlocks ();
    
    GRPVECTORFILEDXFTextSectionBlockDef* IsKnownBlock ( XSTRING& name );
    GRPVECTORFILEDXFTextSectionBlockDefType*  IsKnownTypeValue(XSTRING& namevar, int type);

    bool AddBlock (GRPVECTORFILEDXFTextBlock* entity);
    XVECTOR<GRPVECTORFILEDXFTextBlock*>* GetBlocks ();
    GRPVECTORFILEDXFTextBlock* GetBlock (XCHAR* nameBlock, XDWORD index);
    bool DeleteBlock(XCHAR* nameBlock, XDWORD index);
    bool DeleteAllBlocks(XCHAR* nameBlock);
    bool DeleteAllBlocks();

    GRPVECTORFILERESULT ParserTextSection ( XFILETXT* file );

  private:
        
    bool ShowTraceAllBlocks ();
    void Clean ();    

    static GRPVECTORFILEDXFTextSectionBlockDef defBlock[GRPVECTORFILEDXFBlocks_MaxNDefBlocks];
    XVECTOR<GRPVECTORFILEDXFTextBlock*> blocks;
};

#pragma endregion


#pragma region EXTERN_INLINE_FUNCTIONS
#pragma endregion

#endif


