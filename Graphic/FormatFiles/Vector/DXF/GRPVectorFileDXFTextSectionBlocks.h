
#ifndef _GRPVECTORFILEDXFTEXTSECTIONBLOCKS_h_
#define _GRPVECTORFILEDXFTEXTSECTIONBLOCKS_h_

#pragma region INCLUDES

#include "XMap.h"
#include "XVariant.h"
#include "XString.h"

#include "GRPVectorFileDXFTextSection.h"

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

} GRPVECTORFILEDXFTEXTSECTIONBlockDefType;


typedef struct
{
   XCHAR* name;
   int ntypes;
   bool isendblock;
   GRPVECTORFILEDXFTEXTSECTIONBlockDefType type[GRPVECTORFILEDXFBlocks_MaxNDefTypes];

} GRPVECTORFILEDXFTEXTSECTIONBlockDef;



class GRPVECTORFILEDXFTEXTSECTIONBLOCKS : public GRPVECTORFILEDXFTEXTSECTION
{
  public:

    GRPVECTORFILEDXFTEXTSECTIONBLOCKS ();
    virtual ~GRPVECTORFILEDXFTEXTSECTIONBLOCKS ();
    
    GRPVECTORFILEDXFTEXTSECTIONBlockDef* IsKnownBlock ( XSTRING& name );
    GRPVECTORFILEDXFTEXTSECTIONBlockDefType*  IsKnownTypeValue(XSTRING& namevar, int type);

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

    static GRPVECTORFILEDXFTEXTSECTIONBlockDef defBlock[GRPVECTORFILEDXFBlocks_MaxNDefBlocks];
    XVECTOR<GRPVECTORFILEDXFTextBlock*> blocks;
};

#pragma endregion


#pragma region EXTERN_INLINE_FUNCTIONS
#pragma endregion

#endif


