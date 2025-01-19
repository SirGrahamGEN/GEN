/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       CompressManager.cpp
* 
* @class      COMPRESSMANAGER
* @brief      Compress Manager class
* @ingroup    COMPRESS
* 
* @copyright  GEN Group. All rights reserved.
* 
* @cond
* Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
* documentation files(the "Software"), to deal in the Software without restriction, including without limitation
* the rights to use, copy, modify, merge, publish, distribute, sublicense, and/ or sell copies of the Software,
* and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
* 
* The above copyright notice and this permission notice shall be included in all copies or substantial portions of
* the Software.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO
* THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
* @endcond
* 
* --------------------------------------------------------------------------------------------------------------------*/

/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_DEFINES_INCLUDE

#include "GEN_Defines.h"

#pragma endregion


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "CompressManager.h"

#ifdef COMPRESS_LZW_ACTIVE
#include "CompressLZW.h"
#endif
#ifdef COMPRESS_LZRW1KH_ACTIVE
#include "CompressLZRW1KH.h"
#endif
#ifdef COMPRESS_ZIP_ACTIVE
#include "CompressZIP.h"
#endif
#ifdef COMPRESS_GZ_ACTIVE
#include "CompressGZ.h"
#endif

#pragma endregion


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_CONTROL_INCLUDE

#include "GEN_Control.h"

#pragma endregion



/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

COMPRESSMANAGER* COMPRESSMANAGER::instance=NULL;

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         COMPRESSMANAGER::COMPRESSMANAGER()
* @brief      Constructor of class
* @ingroup    COMPRESS
* 
* --------------------------------------------------------------------------------------------------------------------*/
COMPRESSMANAGER::COMPRESSMANAGER()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         COMPRESSMANAGER::~COMPRESSMANAGER()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    COMPRESS
* 
* --------------------------------------------------------------------------------------------------------------------*/
COMPRESSMANAGER::~COMPRESSMANAGER()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         COMPRESSBASE* COMPRESSMANAGER::Create(COMPRESSBASE_TYPE type)
* @brief      Create
* @ingroup    COMPRESS
* 
* @param[in]  type : 
* 
* @return     COMPRESSBASE* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
COMPRESSBASE* COMPRESSMANAGER::Create(COMPRESSBASE_TYPE type)
{
  COMPRESSBASE* compress;

  switch(type)
    {
      #ifdef COMPRESS_LZW_ACTIVE
      case COMPRESSBASE_TYPE_LZW      : compress = new COMPRESS_LZW();        
                                        break;
      #endif

      #ifdef COMPRESS_LZRW1KH_ACTIVE
      case COMPRESSBASE_TYPE_LZRW1KH  : compress = new COMPRESS_LZRW1KH();    
                                        break;
      #endif

      #ifdef COMPRESS_ZIP_ACTIVE
      case COMPRESSBASE_TYPE_ZIP      : compress = new COMPRESS_ZIP();        
                                        break;
      #endif

      #ifdef COMPRESS_GZ_ACTIVE
      case COMPRESSBASE_TYPE_GZ       : compress = new COMPRESS_GZ();         
                                        break;
      #endif
                            default   : compress = new COMPRESSBASE();        break;
    }

  if(compress) lastcompresstype = type;

  return compress;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         COMPRESSMANAGER* COMPRESSMANAGER::GetInstance()
* @brief      Get instance
* @ingroup    COMPRESS
* 
* @return     COMPRESSMANAGER* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
COMPRESSMANAGER* COMPRESSMANAGER::GetInstance()
{
  if(!instance) instance = new COMPRESSMANAGER();

  return instance;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void COMPRESSMANAGER::DeleteInstance()
* @brief      Delete instance
* @ingroup    COMPRESS
* 
* --------------------------------------------------------------------------------------------------------------------*/
void COMPRESSMANAGER::DeleteInstance()
{
  if(instance) delete instance;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void COMPRESSMANAGER::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    COMPRESS
* 
* --------------------------------------------------------------------------------------------------------------------*/
void COMPRESSMANAGER::Clean()
{
  lastcompresstype = COMPRESSBASE_TYPE_NONE;
}


#pragma endregion

