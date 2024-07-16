
#ifndef _GRPVECTORFILEDXFEntityDefStringValue_h_
#define _GRPVECTORFILEDXFEntityDefStringValue_h_

#pragma region INCLUDES

#include "XString.h"

#pragma endregion


#pragma region DEFINES_ENUMS
#pragma endregion


#pragma region CLASSES

class GRPVECTORFILEDXFEntityDefStringValue 
{
   public:
   
      GRPVECTORFILEDXFEntityDefStringValue () ;
      GRPVECTORFILEDXFEntityDefStringValue ( int value, XCHAR* string ) ;
      GRPVECTORFILEDXFEntityDefStringValue ( GRPVECTORFILEDXFEntityDefStringValue* point ) ;
      ~GRPVECTORFILEDXFEntityDefStringValue () ;

      void operator =  (GRPVECTORFILEDXFEntityDefStringValue* stringvalue);
      void operator =  (GRPVECTORFILEDXFEntityDefStringValue point);

      int GetValue ();
      void SetValue ( int value );

      XSTRING* GetString ();
      
      bool CopyTo ( GRPVECTORFILEDXFEntityDefStringValue* stringvalue );
      bool CopyFrom ( GRPVECTORFILEDXFEntityDefStringValue* stringvalue );
   
   private: 

      void Clean ();

      int value;
      XSTRING string;
};


class GRPVECTORFILEDXFEntityDefStringList
{
   public:
   
      GRPVECTORFILEDXFEntityDefStringList () ;      
      ~GRPVECTORFILEDXFEntityDefStringList () ;

   
   private: 

      void Clean ();

      XVECTOR<GRPVECTORFILEDXFEntityDefStringValue*> stringsvalue;   
};


#pragma endregion


#pragma region EXTERN_INLINE_FUNCTIONS
#pragma endregion

#endif
