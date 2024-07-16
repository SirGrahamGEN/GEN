
#ifndef _GRPVECTORFILEDXFTextPart_h_
#define _GRPVECTORFILEDXFTextPart_h_

#pragma region INCLUDES

#include "XString.h"

#pragma endregion


#pragma region DEFINES_ENUMS
#pragma endregion


#pragma region CLASSES

class GRPVECTORFILEDXFTextPart
{
  public:

    GRPVECTORFILEDXFTextPart ();
    virtual ~GRPVECTORFILEDXFTextPart ();

    bool CopyTo(GRPVECTORFILEDXFTextPart* part);
    
    XSTRING name;
    int iniline;
    int endline;       

  private:
    
    void Clean ();
};

#pragma endregion


#pragma region EXTERN_INLINE_FUNCTIONS
#pragma endregion

#endif
