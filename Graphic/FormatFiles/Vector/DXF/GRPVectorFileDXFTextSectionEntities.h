
#ifndef _GRPVECTORFILEDXFTEXTSECTIONENTITIES_h_
#define _GRPVECTORFILEDXFTEXTSECTIONENTITIES_h_

#pragma region INCLUDES

#include "XMap.h"
#include "XVariant.h"
#include "XString.h"

#include "GRPVectorFile.h"
#include "GRPVectorFileDXFEntity.h"
#include "GRPVectorFileDXFEntityObj.h"
#include "GRPVectorFileDXFTextSection.h"

#pragma endregion


#pragma region DEFINES_ENUMS

#undef  TEST_ONLY_DEFINE_IN_ENTITITES

#define GRPVECTORFILEDXFEntities_MaxNDefEntities 46
#define GRPVECTORFILEDXFEntities_MaxNDefTypes 90
#define GRPVECTORFILEDXFEntities_NotEnumEntity -1

#define VFDXF_SUBCLASS __L("SUBCLASS") 
#define VFDXF_SUBCLASS2 __L("SUBCLASS2") 
#define VFDXF_POINT_X __L("POINT_X")
#define VFDXF_POINT_Y __L("POINT_Y")
#define VFDXF_POINT_Z __L("POINT_Z")
#define VFDXF_INI_POINT_X __L("INI_POINT_X")
#define VFDXF_INI_POINT_Y __L("INI_POINT_Y")
#define VFDXF_INI_POINT_Z __L("INI_POINT_Z")
#define VFDXF_END_POINT_X __L("END_POINT_X")
#define VFDXF_END_POINT_Y __L("END_POINT_Y")
#define VFDXF_END_POINT_Z __L("END_POINT_Z")
#define VFDXF_INSERTION_POINT_X __L("INSERTION_POINT_X") 
#define VFDXF_INSERTION_POINT_Y __L("INSERTION_POINT_Y") 
#define VFDXF_INSERTION_POINT_Z __L("INSERTION_POINT_Z") 
#define VFDXF_CENTER_POINT_X __L("CENTER_POINT_X")
#define VFDXF_CENTER_POINT_Y __L("CENTER_POINT_Y")
#define VFDXF_CENTER_POINT_Z __L("CENTER_POINT_Z")
#define VFDXF_LOCATION_POINT_X __L("CENTER_LOCATION_X")
#define VFDXF_LOCATION_POINT_Y __L("CENTER_LOCATION_Y")
#define VFDXF_LOCATION_POINT_Z __L("CENTER_LOCATION_Z")
#define VFDXF_EXTRUSION_DIRECTION_X  __L("EXTRUSION_DIRECTION_X")
#define VFDXF_EXTRUSION_DIRECTION_Y  __L("EXTRUSION_DIRECTION_Y")
#define VFDXF_EXTRUSION_DIRECTION_Z  __L("EXTRUSION_DIRECTION_Z")
#define VFDXF_INI_ANGLE __L("INI_ANGLE")
#define VFDXF_END_ANGLE __L("INI_ANGLE")
#define VFDXF_RADIOUS __L("RADIUS") 
#define VFDXF_INI_PARAMETER __L("INI_PARAMETER") 
#define VFDXF_END_PARAMETER __L("INI_PARAMETER") 
#define VFDXF_ANGLE_X __L("ANGLE_X")
#define VFDXF_THICKNESS __L("THICKNESS") 

#pragma endregion


#pragma region CLASSES

class GRPVECTORFILEDXFXDATACTRL;

typedef struct
{
   int type;
   XCHAR* name;   
   XCHAR* remark;   

} GRPVECTORFILEDXFTEXTSECTIONEntityDefType;


typedef struct
{
   XCHAR* name;
   int ntypes;
   GRPVECTORFILEDXFTEXTSECTIONEntityDefType type[GRPVECTORFILEDXFEntities_MaxNDefTypes];

} GRPVECTORFILEDXFTEXTSECTIONEntityDef;


class GRPVECTORFILEDXFTEXTSECTIONENTITIES : public GRPVECTORFILEDXFTEXTSECTION
{
  public:

    GRPVECTORFILEDXFTEXTSECTIONENTITIES ();
    virtual ~GRPVECTORFILEDXFTEXTSECTIONENTITIES ();

    bool IsKnownEntity( XSTRING& nameentity );
    GRPVECTORFILEDXFTEXTSECTIONEntityDefType* IsKnownTypeValue( XSTRING& nameentity, int type );
    
    bool AddEntity ( GRPVECTORFILEDXFENTITY* entity );
    XVECTOR<GRPVECTORFILEDXFENTITY*>* GetEntities ();
    GRPVECTORFILEDXFENTITY* GetEntity ( XCHAR* nameEntity, XDWORD index );
    bool DeleteEntity( XCHAR* nameEntity, XDWORD index );
    bool DeleteAllEntities(XCHAR* nameEntity);
    bool DeleteAllEntities();

    XMAP<XSTRING*, int>* GetEnumEntitys();
    int GetNEntitys(XCHAR* nameEntity);

    XVECTOR<GRPVECTORFILEDXFENTITYObj*>* GetEntitiesObj();
    bool DeleteAllEntitiesObj();

    GRPVECTORFILERESULT ParserTextSection ( XFILETXT* fileTXT );

    #ifdef XTRACE_ACTIVE    
    bool ShowTraceAllEntities();
    #endif

  private:
    
    int GetEntityEnumIndex( XCHAR* nameEntity );
    bool AddEntityEnum( XCHAR* nameEntity );
    bool SubtractEntityEnum( XCHAR* nameEntity );
    bool SetZeroEntityEnum( XCHAR* nameEntity );
    
    void Clean ();  
    
    static GRPVECTORFILEDXFTEXTSECTIONEntityDef defentity[GRPVECTORFILEDXFEntities_MaxNDefEntities];
    XMAP<XSTRING*, int> enumentities;
    XVECTOR<GRPVECTORFILEDXFENTITY*> entities;
    XVECTOR<GRPVECTORFILEDXFENTITYObj*> entitiesObj;
};

#pragma endregion


#pragma region EXTERN_INLINE_FUNCTIONS
#pragma endregion

#endif

