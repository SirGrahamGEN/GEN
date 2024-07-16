
#pragma region INCLUDES

#include "GRPVECTORFILEDXFXDataCtrl.h"
#include "GRPVECTORFILEDXFTextSectionHeader.h"
#include "GRPVECTORFILEDXFTextSectionBlocks.h"
#include "GRPVECTORFILEDXFTextSectionEntities.h"

#include "GRPVECTORFILEDXFTextSection.h"

#pragma endregion


#pragma region GENERAL_VARIABLES

GRPVECTORFILEDXFDefTextSection GRPVECTORFILEDXFTextSection::defsection[GRPVECTORFILEDXFTextSection_MaxNDefSections] = 
{ 
   { __L("HEADER"), GRPVECTORFILEDXFTextSection_TypeSection_Header },
   { __L("CLASSES"), GRPVECTORFILEDXFTextSection_TypeSection_Classes },
   { __L("TABLES"), GRPVECTORFILEDXFTextSection_TypeSection_Tables },
   { __L("BLOCKS"), GRPVECTORFILEDXFTextSection_TypeSection_Blocks },
   { __L("ENTITIES"),GRPVECTORFILEDXFTextSection_TypeSection_Entities  },
   { __L("OBJECTS"), GRPVECTORFILEDXFTextSection_TypeSection_Objects  },
   { __L("ACDSDATA"), GRPVECTORFILEDXFTextSection_TypeSection_ACDSData },
   { __L("THUMBNAILIMAGE"), GRPVECTORFILEDXFTextSection_TypeSection_ThumbNailImage },
};

GRPVECTORFILEDXFTextSectionGenericDefType GRPVECTORFILEDXFTextSection::genericDef[GRPVECTORFILEDXFTextSection_MaxNGenericDefTypes] = 
{
   {    -5,    0, __L("G_APP_REACTOR_CHAIN")                          , __L("APP: persistent reactor chain") },
   {    -4,    0, __L("G_APP_CONDITIONAL_OPERATOR")                   , __L("APP: conditional operator (used only with ssget)") },
   {    -3,    0, __L("G_APP_EXTENDED DATA")                          , __L("APP: extended data (XDATA) sentinel (fixed)") },
   {    -2,    0, __L("G_APP_ENTITY_NAME_REFERENCE")                  , __L("APP: entity name reference (fixed)") },
   {    -1,    0, __L("G_APP_ENTITY_NAME")                            , __L("APP: entity name. The name changes each time a drawing is opened. It is never saved (fixed)") },
   {     0,    0, __L("G_TEXT_STRING")                                , __L("Text string indicating the entity type (fixed)") },
   {     1,    0, __L("G_PRIMARY_TEXT")                               , __L("Primary text value for an entity") },
   {     2,    0, __L("G_NAME")                                       , __L("Name (attribute tag, block name, and so on)") },
   {     3,    4, __L("G_OTHER_TEXT")                                 , __L("Other text or name values") },
   {     5,    0, __L("G_ENTITY_HANDLE")                              , __L("Entity handle; text string of up to 16 hexadecimal digits (fixed)") },
   {     6,    0, __L("G_LINETYPE_NAME")                              , __L("Linetype name (fixed)") },
   {     7,    0, __L("G_TEXT_STYLE_NAME")                            , __L("Text style name (fixed)") },
   {     8,    0, __L("G_LAYER_NAME")                                 , __L("Layer name (fixed)") },
   {     9,    0, __L("G_VARIABLE_NAME_ID")                           , __L("DXF: variable name identifier (used only in HEADER section of the DXF file)") },
   {    10,    0, __L("G_PRIMARY_POINT")                              , __L("Primary point; this is the start point of a line or text entity, center of a circle, and so on DXF: X value of the primary point (followed by Y and Z value codes 20 and 30) APP: 3D point (list of three reals)") },
   {    11,   18, __L("G_OTHER_POINTS")                               , __L("Other points DXF: X value of other points (followed by Y value codes 21-28 and Z value codes 31-38) APP: 3D point (list of three reals)") },
   {    20,    0, __L("G_Y_PRIMARY")                                  , __L("DXF: Y and Z values of the primary point") },
   {    30,    0, __L("G_Z_PRIMARY")                                  , __L("DXF: Y and Z values of the primary point") },
   {    21,   28, __L("G_Y_OTHER")                                    , __L("DXF: Y and Z values of other points") },
   {    31,   37, __L("G_Z_OTHER")                                    , __L("DXF: Y and Z values of other points") },
   {    38,    0, __L("G_ENTITY_ELEVATION")                           , __L("DXF: entity's elevation if nonzero") },
   {    39,    0, __L("G_THICKNESS")                                  , __L("Entity's thickness if nonzero (fixed)") },
   {    40,   48, __L("G_FLOATING-POINT_VALUES")                      , __L("Double-precision floating-point values (text height, scale factors, and so on)") },
   {    48,    0, __L("G_LINETYPE_SCALE")                             , __L("Linetype scale; double precision floating point scalar value; default value is defined for all entity types") },
   {    49,    0, __L("G_REPEATED_FLOATING-POINT_VALUE")              , __L("Repeated double-precision floating-point value. Multiple 49 groups may appear in one entity for variable-length tables (such as the dash lengths in the LTYPE table). A 7x group always appears before the first 49 group to specify the table length") },
   {    50,   58, __L("G_ANGLES")                                     , __L("Angles (output in degrees to DXF files and radians through AutoLISP and ObjectARX applications)") },
   {    60,    0, __L("G_ENTITY_VISIBILITY")                          , __L("Entity visibility; integer value; absence or 0 indicates visibility; 1 indicates invisibility") },
   {    62,    0, __L("G_COLOR_NUMBER")                               , __L("Color number (fixed)") },
   {    66,    0, __L("G_ENTITIES_FLAG")                              , __L("'Entities follow' flag (fixed)") },
   {    67,    0, __L("G_TYPE_SPACE")                                 , __L("Space-that is, model or paper space (fixed)") },
   {    68,    0, __L("G_APP_IDENTIFIES")                             , __L("APP: identifies whether viewport is on but fully off screen; is not active or is off") },
   {    69,    0, __L("G_APP_VIEWPORT")                               , __L("APP: viewport identification number") },
   {    70,   78, __L("G_INTEGER_VALUES")                             , __L("Integer values, such as repeat counts, flag bits, or modes") },
   {    90,   99, __L("G_32-BIT_INTEGER_VALUES")                      , __L("32-bit integer values") },
   {   100,    0, __L("G_SUBCLASS_MARKER")                            , __L("Subclass data marker (with derived class name as a string). Required for all objects and entity classes that are derived from another concrete class. The subclass data marker segregates data defined by different classes in the inheritance chain for the same object. This is in addition to the requirement for DXF names for each distinct concrete class derived from ObjectARX (see Subclass Markers)") },
   {   102,    0, __L("G_CONTROL_STRING")                             , __L("Control string, followed by '{<arbitrary name>' or '}'. Similar to the xdata 1002 group code, except that when the string begins with '{', it can be followed by an arbitrary string whose interpretation is up to the application. The only other control string allowed is '}' as a group terminator. AutoCAD does not interpret these strings except during drawing audit operations.") },
   {   105,    0, __L("G_OBJECT_HANDLE_DIMVAR")                       , __L("Object handle for DIMVAR symbol table entry") },
   {   110,    0, __L("G_APP_3D_POINT")                               , __L("UCS origin (appears only if code 72 is set to 1) DXF: X value; APP: 3D point") },
   {   111,    0, __L("G_APP_UCS_X_3D_VECTOR")                        , __L("UCS X-axis (appears only if code 72 is set to 1) DXF: X value; APP: 3D vector") },
   {   112,    0, __L("G_APP_UCS_Y_3D_VECTOR ")                       , __L("UCS Y-axis (appears only if code 72 is set to 1) DXF: X value; APP: 3D vector") },
   {   120,  122, __L("G_UCS_ORIGIN_Y")                               , __L("DXF: Y value of UCS origin, UCS X-axis, and UCS Y-axis") },
   {   130,  132, __L("G_UCS_ORIGIN_Z")                               , __L("DXF: Z value of UCS origin, UCS X-axis, and UCS Y-axis") },
   {   140,  149, __L("G_FLOATING-POINT_VALUES")                      , __L("Double-precision floating-point values (points, elevation, and DIMSTYLE settings, for example)") },
   {   170,  179, __L("G_16-BIT_INTEGER_VALUES")                      , __L("16-bit integer values, such as flag bits representing DIMSTYLE settings") },
   {   210,    0, __L("G_X_EXTRUSION_DIRECTION")                      , __L("Extrusion direction (fixed) DXF: X value of extrusion direction APP: 3D extrusion direction vector") },
   {   220,    0, __L("G_Y_EXTRUSION_DIRECTION")                      , __L("DXF: Y and Z values of the extrusion direction") },  
   {   230,    0, __L("G_Z_EXTRUSION_DIRECTION")                      , __L("DXF: Y and Z values of the extrusion direction") },
   {   270,  279, __L("G_16-BIT_INTEGER_VALUES")                      , __L("16-bit integer values") },
   {   280,  289, __L("G_16-BIT_INTEGER_VALUE")                       , __L("16-bit integer value") },
   {   290,  299, __L("G_BOOLEAN_FLAG_VALUE")                         , __L("Boolean flag value") },
   {   300,  309, __L("G_ARBITRARY_TEXT_STRING")                      , __L("Arbitrary text strings") },
   {   310,  319, __L("G_ARBITRARY_BINARY_CHUNK")                     , __L("Arbitrary binary chunks with same representation and limits as 1004 group codes: hexadecimal strings of up to 254 characters represent data chunks of up to 127 bytes") },
   {   320,  329, __L("G_ARBITRARY_OBJECT_HANDLE")                    , __L("Arbitrary object handles; handle values that are taken 'as is'. They are not translated during INSERT and XREF operations") },
   {   330,  339, __L("G_SOFT-POINTER_HANDLE")                        , __L("Soft-pointer handle; arbitrary soft pointers to other objects within same DXF file or drawing. Translated during INSERT and XREF operations") },
   {   340,  349, __L("G_HARD-POINTER_HANDLE")                        , __L("Hard-pointer handle; arbitrary hard pointers to other objects within same DXF file or drawing. Translated during INSERT and XREF operations") },
   {   350,  359, __L("G_SOFT-OWNER_HANDLE")                          , __L("Soft-owner handle; arbitrary soft ownership links to other objects within same DXF file or drawing. Translated during INSERT and XREF operations") },
   {   360,  369, __L("G_HARD-OWNER_HANDLE")                          , __L("Hard-owner handle; arbitrary hard ownership links to other objects within same DXF file or drawing. Translated during INSERT and XREF operations") },
   {   370,  379, __L("G_LINEWEIGHT_ENUM_VALUE")                      , __L("Lineweight enum value (AcDb::LineWeight). Stored and moved around as a 16-bit integer. Custom non-entity objects may use the full range, but entity classes only use 371-379 DXF group codes in their representation, because AutoCAD and AutoLISP both always assume a 370 group code is the entity's lineweight. This allows 370 to behave like other 'common' entity fields") },
   {   380,  389, __L("G_PLOTSTYLENAME_TYPE")                         , __L("PlotStyleName type enum (AcDb::PlotStyleNameType). Stored and moved around as a 16-bit integer. Custom non-entity objects may use the full range, but entity classes only use 381-389 DXF group codes in their representation, for the same reason as the Lineweight range above") },
   {   390,  399, __L("G_STRING_REPRESENTING_HANDLE")                 , __L("String representing handle value of the PlotStyleName object, basically a hard pointer, but has a different range to make backward compatibility easier to deal with. Stored and moved around as an object ID (a handle in DXF files) and a special type in AutoLISP. Custom non-entity objects may use the full range, but entity classes only use 391-399 DXF group codes in their representation, for the same reason as the lineweight range above") },
   {   400,  409, __L("G_16-BIT_INTEGERS")                            , __L("16-bit integers") },
   {   410,  419, __L("G_STRING")                                     , __L("String") },
   {   420,  427, __L("G_24-BIT_COLOR_VALUE")                         , __L("32-bit integer value. When used with True Color; a 32-bit integer representing a 24-bit color value. The high-order byte (8 bits) is 0, the low-order byte an unsigned char holding the Blue value (0-255), then the Green value, and the next-to-high order byte is the Red Value. Converting this integer value to hexadecimal yields the following bit mask: 0x00RRGGBB. For example, a true color with Red==200, Green==100 and Blue==50 is 0x00C86432, and in DXF, in decimal, 13132850") },
   {   430,  437, __L("G_STRING")                                     , __L("String; when used for True Color, a string representing the name of the color") },
   {   440,  447, __L("G_32-BIT_INTEGER_VALUE")                       , __L("32-bit integer value. When used for True Color, the transparency value") },
   {   450,  459, __L("G_LONG")                                       , __L("Long") },
   {   460,  469, __L("G_FLOATING-POINT_VALUE")                       , __L("Double-precision floating-point value") },
   {   470,  479, __L("G_STRING")                                     , __L("String") },
   {   480,  481, __L("G_HARD-POINTER_HANDLE")                        , __L("Hard-pointer handle; arbitrary hard pointers to other objects within same DXF file or drawing. Translated during INSERT and XREF operations") },
   {   999,    0, __L("G_REMARKS")                                    , __L("DXF: The 999 group code indicates that the line following it is a comment string. SAVEAS does not include such groups in a DXF output file, but OPEN honors them and ignores the comments. You can use the 999 group to include comments in a DXF file that you have edited") },
   {  1000,    0, __L("G_ASCII STRING")                               , __L("ASCII string (up to 255 bytes long) in extended data") },
   {  1001,    0, __L("G_REGISTERED_APPLICATION_NAME")                , __L("Registered application name (ASCII string up to 31 bytes long) for extended data") },
   {  1002,    0, __L("G_EXTENDED_DATA_CTRL_STRING")                  , __L("Extended data control string ('{' or '}')") },
   {  1003,    0, __L("G_EXTENDED_DATA_LAYER_NAME")                   , __L("Extended data layer name") },
   {  1004,    0, __L("G_CHUNK_BYTES")                                , __L("Chunk of bytes (up to 127 bytes long) in extended data") },
   {  1005,    0, __L("G_ENTITY_HANDLE_EXTENDED_STRING")              , __L("Entity handle in extended data; text string of up to 16 hexadecimal digits") },
   {  1010,    0, __L("G_X_POINT_EXTENDED_DATA_VALUE")                , __L("A point in extended data  DXF: X value (followed by 1020 and 1030 groups) APP: 3D point") },
   {  1020,    0, __L("G_Y POINT_EXTENDED_DATA_VALUE")                , __L("DXF: Y and Z values of a point") },
   {  1030,    0, __L("G_Z POINT_EXTENDED_DATA_VALUE")                , __L("DXF: Y and Z values of a point") },
   {  1011,    0, __L("G_X_WORLD_SPACE_POSITION")                     , __L("A 3D world space position in extended data DXF: X value (followed by 1021 and 1031 groups) APP: 3D point") },
   {  1021,    0, __L("G_Y_WORLD_SPACE_POSITION")                     , __L("DXF: Y and Z values of a world space position") },  
   {  1031,    0, __L("G_Z_WORLD_SPACE_POSITION")                     , __L("DXF: Y and Z values of a world space position") },
   {  1012,    0, __L("G_X_WORLD_SPACE_DISPLACEMENT")                 , __L("A 3D world space displacement in extended data DXF: X value (followed by 1022 and 1032 groups) APP: 3D vector") },
   {  1022,    0, __L("G_Y_WORLD_SPACE_DISPLACEMENT")                 , __L("DXF: Y and Z values of a world space displacement") },
   {  1032,    0, __L("G_Z_WORLD_SPACE_DISPLACEMENT")                 , __L("DXF: Y and Z values of a world space displacement") },
   {  1013,    0, __L("G_X_WORLD_SPACE_DIRECTION")                    , __L("A 3D world space direction in extended data DXF: X value (followed by 1022 and 1032 groups) APP: 3D vector") },
   {  1023,    0, __L("G_Y_WORLD_SPACE_DIRECTION")                    , __L("DXF: Y and Z values of a world space direction") },
   {  1033,    0, __L("G_Z_WORLD_SPACE_DIRECTION")                    , __L("DXF: Y and Z values of a world space direction") },
   {  1040,    0, __L("G_EXTENDED DATA FLOATING-POINT VALUE")         , __L("Extended data double-precision floating-point value") },
   {  1041,    0, __L("G_EXTENDED DATA DISTANCE VALUE")               , __L("Extended data distance value") },
   {  1042,    0, __L("G_EXTENDED DATA SCALE FACTOR")                 , __L("Extended data scale factor") },
   {  1070,    0, __L("G_EXTENDED DATA 16-BIT SIGNED INTEGER")        , __L("Extended data 16-bit signed integer") },
   {  1071,    0, __L("G_EXTENDED DATA 32-BIT SIGNED LONG")           , __L("Extended data 32-bit signed long") }
};

#pragma endregion


#pragma region CLASS_MEMBERS

GRPVECTORFILEDXFTextSection::GRPVECTORFILEDXFTextSection ( )
{
  Clean();
}


GRPVECTORFILEDXFTextSection::~GRPVECTORFILEDXFTextSection ( )
{
  Clean();
}


GRPVECTORFILE* GRPVECTORFILEDXFTextSection::GetGRPVECTORFILE()
{
   return vectorFile;
}
   
 
void GRPVECTORFILEDXFTextSection::SetGRPVECTORFILE(GRPVECTORFILE* vectorFile)
{
   this->vectorFile = vectorFile;
}


GRPVECTORFILEDXFTextSection* GRPVECTORFILEDXFTextSection::CreateInstance(GRPVECTORFILEDXFTextSection_TypeSection type)
{
   GRPVECTORFILEDXFTextSection* section = NULL;

   switch(type)
   {      
      case GRPVECTORFILEDXFTextSection_TypeSection_Unknown        :  
                                               default         :  break;

      case GRPVECTORFILEDXFTextSection_TypeSection_Header         :  section = new GRPVECTORFILEDXFTextSectionHeader();                                                               
                                                                  break;  

      case GRPVECTORFILEDXFTextSection_TypeSection_Classes        :  break;   

      case GRPVECTORFILEDXFTextSection_TypeSection_Tables         :  break;    

      case GRPVECTORFILEDXFTextSection_TypeSection_Blocks         :  section = new GRPVECTORFILEDXFTextSectionBlocks();
                                                                  break; 

      case GRPVECTORFILEDXFTextSection_TypeSection_Entities       :  section = new GRPVECTORFILEDXFTextSectionEntities();
                                                                  break;  
                                                               
      case GRPVECTORFILEDXFTextSection_TypeSection_Objects        :  break; 

      case GRPVECTORFILEDXFTextSection_TypeSection_ACDSData       :  break;

      case GRPVECTORFILEDXFTextSection_TypeSection_ThumbNailImage :  break; 
   
   }

   return section;
}


GRPVECTORFILEDXFTextSection_TypeSection GRPVECTORFILEDXFTextSection::GetTypeSection (XSTRING& nameSection)
{
   for(int c=0; c<GRPVECTORFILEDXFTextSection_MaxNDefSections ; c++)
   {
      if(!nameSection.Compare(GRPVECTORFILEDXFTextSection::defsection[c].name))
      {
         return GRPVECTORFILEDXFTextSection::defsection[c].type;
      }
   }

   return GRPVECTORFILEDXFTextSection_TypeSection_Unknown;
}


GRPVECTORFILEDXFTextSection_BasicType GRPVECTORFILEDXFTextSection::GetTypeBasic (int type)
{
   switch(type)
   {     
      case    0 ...    9   :  // String (with the introduction of extended symbol names in AutoCAD 2000, the 255-character limit has been increased to 2049 single-byte characters not including the newline at the end of the line); see the "Storage of String Values" section for more information
                              return GRPVECTORFILEDXFTextSection_BasicType_String;

      case   10 ...   39   :  // Double precision 3D point value                           
      case   40 ...   59   :  // Double-precision floating-point value
                              return GRPVECTORFILEDXFTextSection_BasicType_Double;

      case   60 ...   79   :  // 16-bit integer value
      case   90 ...   99   :  // 32-bit integer value
                              return GRPVECTORFILEDXFTextSection_BasicType_Integer;

      case           100   :  // String (255-character maximum, less for Unicode strings); see the "Storage of String Values" section for more information
      case           102   :  // String (255-character maximum, less for Unicode strings); see the "Storage of String Values" section for more information
      case           105   :  // String representing hexadecimal (hex) handle value
                              return GRPVECTORFILEDXFTextSection_BasicType_String;
                              
      case  110 ...  119   :  // Double precision floating-point value
      case  120 ...  129   :  // Double precision floating-point value
      case  130 ...  139   :  // Double precision floating-point value
      case  140 ...  149   :  // Double precision scalar floating-point value
                              return GRPVECTORFILEDXFTextSection_BasicType_Double;

      case  160 ...  169   :  // 64-bit integer value
      case  170 ...  179   :  // 16-bit integer value
                              return GRPVECTORFILEDXFTextSection_BasicType_Integer;

      case  210 ...  239   :  // Double-precision floating-point value
                              return GRPVECTORFILEDXFTextSection_BasicType_Double;

      case  270 ...  279   :  // 16-bit integer value
      case  280 ...  289   :  // 16-bit integer value
                              return GRPVECTORFILEDXFTextSection_BasicType_Integer;

      case  290 ...  299   :  // Boolean flag value
                              return GRPVECTORFILEDXFTextSection_BasicType_Boolean;

      case  300 ...  309   :  // Arbitrary text string; see the "Storage of String Values" section for more information
      case  310 ...  319   :  // String representing hex value of binary chunk
      case  320 ...  329   :  // String representing hex handle value
      case  330 ...  369   :  // String representing hex object IDs
                              return GRPVECTORFILEDXFTextSection_BasicType_String;

      case  370 ...  379   :  // 16-bit integer value
      case  380 ...  389   :  // 16-bit integer value
                              return GRPVECTORFILEDXFTextSection_BasicType_Integer;

      case  390 ...  399   :  // String representing hex handle value
                              return GRPVECTORFILEDXFTextSection_BasicType_String;

      case  400 ...  409   :  // 16-bit integer value
                              return GRPVECTORFILEDXFTextSection_BasicType_Integer;

      case  410 ...  419   :  // String; see the "Storage of String Values" section for more information
                              return GRPVECTORFILEDXFTextSection_BasicType_String;

      case  420 ...  429   :  // 32-bit integer value
                              return GRPVECTORFILEDXFTextSection_BasicType_Integer;

      case  430 ...  439   :  // String; see the "Storage of String Values" section for more information
                              return GRPVECTORFILEDXFTextSection_BasicType_String;

      case  440 ...  449   :  // 32-bit integer value
                              return GRPVECTORFILEDXFTextSection_BasicType_Integer;

      case  450 ...  459   :  // Long
                              return GRPVECTORFILEDXFTextSection_BasicType_Integer;

      case  460 ...  469   :  // Double-precision floating-point value
                              return GRPVECTORFILEDXFTextSection_BasicType_Double;

      case  470 ...  479   :  // String; see the "Storage of String Values" section for more information
      case  480 ...  481   :  // String representing hex handle value
                              return GRPVECTORFILEDXFTextSection_BasicType_String;

      case           999   :  // Comment (string); see the "Storage of String Values" section for more information
                              return GRPVECTORFILEDXFTextSection_BasicType_String;

      case 1000 ... 1009   :  // String (same limits as indicated with 0-9 code range); see the "Storage of String Values" section for more information
                              return GRPVECTORFILEDXFTextSection_BasicType_String;

      case 1010 ... 1059   :  // Double-precision floating-point value
                              return GRPVECTORFILEDXFTextSection_BasicType_Double;
                        
      case 1060 ... 1070   :  // 16-bit integer value
      case          1071   :  // 32-bit integer value            
                              return GRPVECTORFILEDXFTextSection_BasicType_Integer;
   }

   return GRPVECTORFILEDXFTextSection_BasicType_Unknown;
}


GRPVECTORFILEDXFTextSectionGenericDefType* GRPVECTORFILEDXFTextSection::GetGenericDefType(int type)
{
   for(int c=0; c<GRPVECTORFILEDXFTextSection_MaxNGenericDefTypes; c++)
   {
      GRPVECTORFILEDXFTextSectionGenericDefType* defType = &genericDef[c];
      if(defType)
      {
         if(defType->type)
         {
            if((defType->type >= type) && (defType->range <= type))
            {
               return defType;
            }
         }
         else
         {
            if(defType->type == type)  return defType;
         }            
      }   
   }

   return NULL;
}


void GRPVECTORFILEDXFTextSection::GetVariableFromLine(XCHAR* namevar, int type, XSTRING* line, XVARIANT& variant)
{
   GRPVECTORFILEDXFTextSection_BasicType basicType = GRPVECTORFILEDXFTextSection::GetTypeBasic(type);

   switch(basicType)
   {  
      case GRPVECTORFILEDXFTextSection_BasicType_Boolean  : variant = line->ConvertToBoolean();
                                                         break;

      case GRPVECTORFILEDXFTextSection_BasicType_Integer  : variant = line->ConvertToInt();
                                                         break;  
                                                   
      case GRPVECTORFILEDXFTextSection_BasicType_Double   : variant = line->ConvertToDouble();
                                                         break;          

      case GRPVECTORFILEDXFTextSection_BasicType_String   : variant = line->Get();
                                                         break;       
      
                           default                     : XTRACE_PRINTCOLOR(XTRACE_COLOR_PURPLE, __L("[GRPVECTORFILEDXF] Type Variable %s Unknown [%d]"), namevar, type);
                                                         break; 
                  
   }   
}


GRPVECTORFILEDXFText_XDataCtrl_Status GRPVECTORFILEDXFTextSection::IsXDataControl(int type, XSTRING& line)
{
   switch(type)
   {
      case 102    :
      case 1002   :  if(line.Find(__L("{"), true) != XSTRING_NOTFOUND)
                     {
                        return GRPVECTORFILEDXFTextSection_XDataCtrl_Status_Ini;
                     }

                     if(!line.Compare(__L("}"), true))
                     {
                        return GRPVECTORFILEDXFTextSection_XDataCtrl_Status_End;
                     }

                     break;
   }

   return GRPVECTORFILEDXFTextSection_XDataCtrl_Status_Not;   
}


GRPVECTORFILERESULT GRPVECTORFILEDXFTextSection::ParserTextSection (XFILETXT* fileTXT)
{
   return GRPVECTORFILERESULT_OK;
}


void GRPVECTORFILEDXFTextSection::Clean ( )
{
   type       = GRPVECTORFILEDXFTextSection_TypeSection_Unknown;
   vectorFile = NULL;
}

#pragma endregion
