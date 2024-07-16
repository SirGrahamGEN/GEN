
#ifndef _GRPVECTORFILEDXFConfig_h_
#define _GRPVECTORFILEDXFConfig_h_

#pragma region INCLUDES

#include "XFileCFG.h"

#include "GRPVectorFileConfig.h"
#include "GRPVECTORFILEDXFTextSectionHeader.h"

#pragma endregion


#pragma region DEFINES_ENUMS

#define VECTORFILEDXFCONFIG_SECTION_DFX_CFG    __L("DXF Config")

#pragma endregion


#pragma region CLASSES

class GRPVECTORFILEDXFConfig : public GRPVECTORFILECONFIG
{
  public:

   GRPVECTORFILEDXFConfig ();
   virtual ~GRPVECTORFILEDXFConfig ();

   GRPVECTORFILEDXFTextSectionHeader* GetHeader ();
   bool SetHeader ( GRPVECTORFILEDXFTextSectionHeader* header);

   bool Create_File (XCHAR* nameFile);
   bool Load_File (XCHAR* nameFile);
        
  private:
    
   void Clean ();

   GRPVECTORFILEDXFTextSectionHeader* header;
   XPATH pathFile;  
   XFILECFG* fileCFG;  
};

#pragma endregion


#pragma region EXTERN_INLINE_FUNCTIONS
#pragma endregion

#endif

