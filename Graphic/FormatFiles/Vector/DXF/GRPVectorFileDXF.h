
#ifndef _GRPVECTORFILEDXF_h_
#define _GRPVECTORFILEDXF_h_

#pragma region INCLUDES

#include "XInheritEnum.h"
#include "XString.h"
#include "XVariant.h"

#include "GRPVECTORFILEDXFConfig.h"
#include "GRPVECTORFILEDXFTextSection.h"

#include "GRPVectorFile.h"

#pragma endregion


#pragma region DEFINES_ENUMS

enum GRPVECTORFILEDXFResultAdd
{
  GRPVECTORFILEDXFResult_NotSections  =   GRPVECTORFILERESULT_LastCommon ,
  GRPVECTORFILEDXFResult_InvalidSection,
};

typedef XINHERITENUM< GRPVECTORFILEDXFResultAdd, GRPVECTORFILERESULT > GRPVECTORFILEDXFResult;

#define GRPVECTORFILEDXF_Extension __L(".dxf")

#define  TEST_NOT_CONCRETE_ENTITY

#pragma endregion


#pragma region CLASSES

class XFILETXT;
class GRPVECTORFILEDXFTextSectionEntities;
class GRPVECTORFILECONFIG;
class GRPVECTORFILEDXFEntityObj;


class GRPVECTORFILEDXF : public GRPVECTORFILE
{
   public:

      GRPVECTORFILEDXF ();
      virtual ~GRPVECTORFILEDXF ();
    
      GRPVECTORFILERESULT DetectType ();
      GRPVECTORFILERESULT Load ();

      GRPVECTORFILECONFIG* GetConfig ();
    
      XVECTOR<GRPVECTORFILEDXFTextSection*>* GetSections(); 
      GRPVECTORFILEDXFTextSection* GetSection (GRPVECTORFILEDXFTextSection_TypeSection type);    
    
      static bool ParserTextFilePrepareLine (XSTRING* line);
    
   private:
  
      GRPVECTORFILEDXFResult ParserTextSections (XFILETXT* file, XVECTOR<GRPVECTORFILEDXFTextSection*>& sections);
      bool ParserHaveAnySection(XFILETXT* fileTXT, int nlinesmax = 100);
      GRPVECTORFILEDXFResult ParserTextFile (XFILETXT* fileTXT);

      #ifdef XTRACE_ACTIVE
      bool GenerateSectionsEntities(GRPVECTORFILEDXFTextSectionEntities* sectionentities, XSTRING& line);  
      bool ShowTraceAllSections();
      #endif

      void Clean();

      XVECTOR<GRPVECTORFILEDXFTextSection*> sections;    
      GRPVECTORFILEDXFConfig config;     
};

#pragma endregion


#pragma region EXTERN_INLINE_FUNCTIONS
#pragma endregion

#endif
