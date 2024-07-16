
#ifndef _GRPVECTORFILEDXFEntityDefPoint_h_
#define _GRPVECTORFILEDXFEntityDefPoint_h_

#pragma region INCLUDES
#pragma endregion


#pragma region DEFINES_ENUMS
#pragma endregion


#pragma region CLASSES

class GRPVECTORFILEDXFEntityDefPoint 
{
   public:
   
      GRPVECTORFILEDXFEntityDefPoint () ;
      GRPVECTORFILEDXFEntityDefPoint ( double xPoint , double yPoint , double zPoint ) ;
      GRPVECTORFILEDXFEntityDefPoint ( GRPVECTORFILEDXFEntityDefPoint* point ) ;
      ~GRPVECTORFILEDXFEntityDefPoint () ;

      void operator =  (GRPVECTORFILEDXFEntityDefPoint* point);
      void operator =  (GRPVECTORFILEDXFEntityDefPoint point);

      double GetX ();
      void SetX ( double xPoint );

      double GetY ();
      void SetY ( double yPoint );

      double GetZ ();           
      void SetZ ( double zPoint );

      bool CopyTo ( GRPVECTORFILEDXFEntityDefPoint* point );
      bool CopyFrom ( GRPVECTORFILEDXFEntityDefPoint* point );
   
   private: 

      void Clean ();

      double xPoint;
      double yPoint;
      double zPoint;
};

#pragma endregion


#pragma region EXTERN_INLINE_FUNCTIONS
#pragma endregion

#endif
