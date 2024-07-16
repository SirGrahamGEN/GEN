
#ifndef _GRPVECTORFILEDXFTextSection_h_
#define _GRPVECTORFILEDXFTextSection_h_

#pragma region INCLUDES

#include "XSubject.h"

#include "GRPVectorFile.h"
#include "GRPVECTORFILEDXFTextPart.h"


#pragma endregion


#pragma region DEFINES_ENUMS

enum GRPVECTORFILEDXFTextSection_BasicType
{
   GRPVECTORFILEDXFTextSection_BasicType_Unknown = 0,
   GRPVECTORFILEDXFTextSection_BasicType_Boolean,
   GRPVECTORFILEDXFTextSection_BasicType_Integer,
   GRPVECTORFILEDXFTextSection_BasicType_Double,
   GRPVECTORFILEDXFTextSection_BasicType_String,
};


enum GRPVECTORFILEDXFText_XDataCtrl_Status
{
   GRPVECTORFILEDXFTextSection_XDataCtrl_Status_Not = 0,
   GRPVECTORFILEDXFTextSection_XDataCtrl_Status_Ini,
   GRPVECTORFILEDXFTextSection_XDataCtrl_Status_End,
};


enum GRPVECTORFILEDXFTextSection_TypeSection
{
  GRPVECTORFILEDXFTextSection_TypeSection_Unknown = 0,
  GRPVECTORFILEDXFTextSection_TypeSection_Header,
  GRPVECTORFILEDXFTextSection_TypeSection_Classes,
  GRPVECTORFILEDXFTextSection_TypeSection_Tables, 
  GRPVECTORFILEDXFTextSection_TypeSection_Blocks, 
  GRPVECTORFILEDXFTextSection_TypeSection_Entities,
  GRPVECTORFILEDXFTextSection_TypeSection_Objects,
  GRPVECTORFILEDXFTextSection_TypeSection_ACDSData,
  GRPVECTORFILEDXFTextSection_TypeSection_ThumbNailImage,
};

#define GRPVECTORFILEDXFTextSection_MaxNDefSections 8
#define GRPVECTORFILEDXFTextSection_MaxNGenericDefTypes 93

#pragma endregion


#pragma region CLASSES

class XFILETXT;

typedef struct
{
   XCHAR* name;
   GRPVECTORFILEDXFTextSection_TypeSection type;
   
} GRPVECTORFILEDXFDefTextSection;


typedef struct
{  
   int type;
   int range;
   XCHAR* name;
   XCHAR* remark;

} GRPVECTORFILEDXFTextSectionGenericDefType;


class GRPVECTORFILEDXFTextSection : public XSUBJECT, public GRPVECTORFILEDXFTextPart
{
  public:

    GRPVECTORFILEDXFTextSection ();
    virtual ~GRPVECTORFILEDXFTextSection ();    
   
    GRPVECTORFILE* GetGRPVECTORFILE();  
    void SetGRPVECTORFILE(GRPVECTORFILE* vectorFile);  

    static GRPVECTORFILEDXFTextSection* CreateInstance(GRPVECTORFILEDXFTextSection_TypeSection type);   
    
    static GRPVECTORFILEDXFTextSection_TypeSection GetTypeSection (XSTRING& nameSection);
    
    static GRPVECTORFILEDXFTextSection_BasicType GetTypeBasic (int type);    
    GRPVECTORFILEDXFTextSectionGenericDefType* GetGenericDefType(int type);
    static void GetVariableFromLine(XCHAR* namevar, int type, XSTRING* line, XVARIANT& variant);  
    GRPVECTORFILEDXFText_XDataCtrl_Status IsXDataControl(int type, XSTRING& line);


    virtual GRPVECTORFILERESULT ParserTextSection (XFILETXT* fileTXT);
    
    GRPVECTORFILEDXFTextSection_TypeSection type;
    static GRPVECTORFILEDXFDefTextSection defsection[GRPVECTORFILEDXFTextSection_MaxNDefSections];
    static GRPVECTORFILEDXFTextSectionGenericDefType genericDef[GRPVECTORFILEDXFTextSection_MaxNGenericDefTypes];

  private:
    
    void Clean ();

    GRPVECTORFILE* vectorFile;
};

#pragma endregion


#pragma region EXTERN_INLINE_FUNCTIONS
#pragma endregion

#endif
