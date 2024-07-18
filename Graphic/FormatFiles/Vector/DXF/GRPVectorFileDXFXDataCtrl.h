
#ifndef _GRPVECTORFILEDXFXDATACTRL_h_
#define _GRPVECTORFILEDXFXDATACTRL_h_

#pragma region INCLUDES

#include "XString.h"
#include "XVariant.h"
#include "XVector.h"

#include "GRPVectorFileDXFValue.h"

#pragma endregion


#pragma region DEFINES_ENUMS
#pragma endregion


#pragma region CLASSES


class GRPVECTORFILEDXFXDATACTRL
{  
   public: 
      
      GRPVECTORFILEDXFXDATACTRL ();
      virtual ~GRPVECTORFILEDXFXDATACTRL ();

      XSTRING* GetName ();
      XVECTOR<GRPVECTORFILEDXFVALUE*>* GetValues ();
     
   
   private: 
   
      void Clean ();

      XSTRING name;
      XVECTOR<GRPVECTORFILEDXFVALUE*> values;
};

#pragma endregion


#pragma region EXTERN_INLINE_FUNCTIONS
#pragma endregion

#endif
