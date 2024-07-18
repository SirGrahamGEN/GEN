
#ifndef _GRPVECTORFILEDXFENTITYDefStringValue_h_
#define _GRPVECTORFILEDXFENTITYDefStringValue_h_

#pragma region INCLUDES

#include "XString.h"

#pragma endregion


#pragma region DEFINES_ENUMS
#pragma endregion


#pragma region CLASSES

class GRPVECTORFILEDXFENTITYDefStringValue 
{
   public:
   
      GRPVECTORFILEDXFENTITYDefStringValue () ;
      GRPVECTORFILEDXFENTITYDefStringValue ( int value, XCHAR* string ) ;
      GRPVECTORFILEDXFENTITYDefStringValue ( GRPVECTORFILEDXFENTITYDefStringValue* point ) ;
      ~GRPVECTORFILEDXFENTITYDefStringValue () ;

      void operator =  (GRPVECTORFILEDXFENTITYDefStringValue* stringvalue);
      void operator =  (GRPVECTORFILEDXFENTITYDefStringValue point);

      int GetValue ();
      void SetValue ( int value );

      XSTRING* GetString ();
      
      bool CopyTo ( GRPVECTORFILEDXFENTITYDefStringValue* stringvalue );
      bool CopyFrom ( GRPVECTORFILEDXFENTITYDefStringValue* stringvalue );
   
   private: 

      void Clean ();

      int value;
      XSTRING string;
};


class GRPVECTORFILEDXFENTITYDefStringList
{
   public:
   
      GRPVECTORFILEDXFENTITYDefStringList () ;      
      ~GRPVECTORFILEDXFENTITYDefStringList () ;

   
   private: 

      void Clean ();

      XVECTOR<GRPVECTORFILEDXFENTITYDefStringValue*> stringsvalue;   
};


#pragma endregion


#pragma region EXTERN_INLINE_FUNCTIONS
#pragma endregion

#endif
