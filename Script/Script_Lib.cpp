/**-------------------------------------------------------------------------------------------------------------------
*
* @file       Script_Lib.cpp
*
* @class      SCRIPT_LIB
* @brief      Script library class
* @ingroup    SCRIPT
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

/*---- PRECOMPILATION CONTROL ----------------------------------------------------------------------------------------*/

#include "GEN_Defines.h"


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "XVariant.h"

#include "Script_Lib.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         SCRIPT_LIB::SCRIPT_LIB(XCHAR* ID)
* @brief      Constructor
* @ingroup    SCRIPT
*
* @param[in]  XCHAR* :
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
SCRIPT_LIB::SCRIPT_LIB(XCHAR* ID)
{
  Clean();

  this->ID = ID;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         SCRIPT_LIB::~SCRIPT_LIB()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    SCRIPT
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
SCRIPT_LIB::~SCRIPT_LIB()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* SCRIPT_LIB::GetID()
* @brief      GetID
* @ingroup    SCRIPT
*
* @return     XSTRING* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* SCRIPT_LIB::GetID()
{
  return &ID;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool SCRIPT_LIB::AddLibraryFunctions(SCRIPT* script)
* @brief      AddLibraryFunctions
* @ingroup    SCRIPT
*
* @param[in]  script :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool SCRIPT_LIB::AddLibraryFunctions(SCRIPT* script)
{
  return false;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool SCRIPT_LIB::GetParamConverted(XVARIANT* variant, int& value)
* @brief      GetParamConverted
* @ingroup    SCRIPT
*
* @param[in]  variant :
* @param[in]  value :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool SCRIPT_LIB::GetParamConverted(XVARIANT* variant, int& value)
{
  if(!variant) return false;

  value = 0;

  switch(variant->GetType())
    {
      case XVARIANT_TYPE_NULL           :
      case XVARIANT_TYPE_SERIALIZABLE   : return false;

      case XVARIANT_TYPE_INTEGER        : value = (*variant);
                                          break;

      case XVARIANT_TYPE_FLOAT          : { float fvalue = (*variant);
                                            value = (int)fvalue;
                                          }
                                          break;

      case XVARIANT_TYPE_DOUBLE         : { double dvalue = (*variant);
                                            value = (int)dvalue;
                                          }
                                          break;

      case XVARIANT_TYPE_CHAR           :
      case XVARIANT_TYPE_XCHAR          :
      case XVARIANT_TYPE_STRING         :
      case XVARIANT_TYPE_DATE           :
      case XVARIANT_TYPE_TIME           :
      case XVARIANT_TYPE_DATETIME       : return false;

    }

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool SCRIPT_LIB::GetParamConverted(XVARIANT* variant, XDWORD& value)
* @brief      GetParamConverted
* @ingroup    SCRIPT
*
* @param[in]  variant :
* @param[in]  value :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool SCRIPT_LIB::GetParamConverted(XVARIANT* variant, XDWORD& value)
{
  int _value = 0;

  bool status = GetParamConverted(variant, _value);
  value = (XDWORD)_value;

  return status;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool SCRIPT_LIB::GetParamConverted(XVARIANT* variant, float& value)
* @brief      GetParamConverted
* @ingroup    SCRIPT
*
* @param[in]  variant :
* @param[in]  value :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool SCRIPT_LIB::GetParamConverted(XVARIANT* variant, float& value)
{
  if(!variant) return false;

  value = 0;

  switch(variant->GetType())
    {
      case XVARIANT_TYPE_NULL           :
      case XVARIANT_TYPE_SERIALIZABLE   : return false;

      case XVARIANT_TYPE_INTEGER        : { int ivalue = (*variant);
                                            value = (float)ivalue;
                                          }
                                          break;

      case XVARIANT_TYPE_FLOAT          : value = (*variant);
                                          break;

      case XVARIANT_TYPE_DOUBLE         : { double dvalue = (*variant);
                                            value = (float)dvalue;
                                          }
                                          break;

      case XVARIANT_TYPE_CHAR           :
      case XVARIANT_TYPE_XCHAR          :
      case XVARIANT_TYPE_STRING         :
      case XVARIANT_TYPE_DATE           :
      case XVARIANT_TYPE_TIME           :
      case XVARIANT_TYPE_DATETIME       : return false;

    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool SCRIPT_LIB::GetParamConverted(XVARIANT* variant, double& value)
* @brief      GetParamConverted
* @ingroup    SCRIPT
*
* @param[in]  variant :
* @param[in]  value :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool SCRIPT_LIB::GetParamConverted(XVARIANT* variant, double& value)
{
  if(!variant) return false;

  value = 0;

  switch(variant->GetType())
    {
      case XVARIANT_TYPE_NULL           :
      case XVARIANT_TYPE_SERIALIZABLE   : return false;

      case XVARIANT_TYPE_INTEGER        : { int ivalue = (*variant);
                                            value = (double)ivalue;
                                          }
                                          break;

      case XVARIANT_TYPE_FLOAT          : { float fvalue = (*variant);
                                            value = (double)fvalue;
                                          }
                                          break;

      case XVARIANT_TYPE_DOUBLE         : value = (*variant);
                                          break;

      case XVARIANT_TYPE_CHAR           :
      case XVARIANT_TYPE_XCHAR          :
      case XVARIANT_TYPE_STRING         :
      case XVARIANT_TYPE_DATE           :
      case XVARIANT_TYPE_TIME           :
      case XVARIANT_TYPE_DATETIME       : return false;

    }

  return true;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void SCRIPT_LIB::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    SCRIPT
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void SCRIPT_LIB::Clean()
{
  script = NULL;
}
