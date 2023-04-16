/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIONodeItemValueUnitFormat.cpp
* 
* @class      DIONODEITEMVALUEUNITFORMAT
* @brief      Data Input/Output Node Item value unit format
* @ingroup    DATAIO
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

#include "DIONodeItemValueUnitFormat.h"

#include "XMemory_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIONODEITEMVALUEUNITFORMAT::DIONODEITEMVALUEUNITFORMAT()
* @brief      Constructor
* @ingroup    DATAIO
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIONODEITEMVALUEUNITFORMAT::DIONODEITEMVALUEUNITFORMAT()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIONODEITEMVALUEUNITFORMAT::~DIONODEITEMVALUEUNITFORMAT()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    DATAIO
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIONODEITEMVALUEUNITFORMAT::~DIONODEITEMVALUEUNITFORMAT()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDWORD DIONODEITEMVALUEUNITFORMAT::GetType()
* @brief      GetType
* @ingroup    DATAIO
* 
* @return     XDWORD : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD DIONODEITEMVALUEUNITFORMAT::GetType()
{
  return type;
}
    

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIONODEITEMVALUEUNITFORMAT::SetType(XDWORD type)
* @brief      SetType
* @ingroup    DATAIO
* 
* @param[in]  type : 
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIONODEITEMVALUEUNITFORMAT::SetType(XDWORD type)
{
  this->type = type;
}

    
/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIONODEITEMVALUEUNITFORMAT::GetName(XSTRING& name)
* @brief      GetName
* @ingroup    DATAIO
* 
* @param[in]  name : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIONODEITEMVALUEUNITFORMAT::GetName(XSTRING& name)
{
  name.Empty();

  switch(type)
    {
      case DIONODEITEMVALUE_UNITSFORMAT_TYPE_UNKNOWN              : break; 

      
      case DIONODEITEMVALUE_UNITSFORMAT_TYPE_SIMPLE               : name = __L("simple");                   
                                                                    break; 

      case DIONODEITEMVALUE_UNITSFORMAT_TYPE_BOOLEAN              : name = __L("boolean");                  
                                                                    break;  

      case DIONODEITEMVALUE_UNITSFORMAT_TYPE_RELATIVEHUMIDITY     : name = __L("relative humidity");        
                                                                    break; 

      case DIONODEITEMVALUE_UNITSFORMAT_TYPE_CELSIUSDEGREE        : name = __L("Celsius degree");           
                                                                    break;            

      case DIONODEITEMVALUE_UNITSFORMAT_TYPE_FAHRENHEITDEGREE     : name = __L("Fahrenheit degree");        
                                                                    break;    

      case DIONODEITEMVALUE_UNITSFORMAT_TYPE_KELVINDEGREE         : name = __L("Kelvin degree");            
                                                                    break;   

                                                         default  : break; 
      
    }

  if(name.IsEmpty()) return false;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIONODEITEMVALUEUNITFORMAT::GetSymbol(XSTRING& symbol)
* @brief      GetSymbol
* @ingroup    DATAIO
* 
* @param[in]  symbol : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIONODEITEMVALUEUNITFORMAT::GetSymbol(XSTRING& symbol)
{
  symbol.Empty();

  switch(type)
    {
      case DIONODEITEMVALUE_UNITSFORMAT_TYPE_UNKNOWN              : 

      case DIONODEITEMVALUE_UNITSFORMAT_TYPE_SIMPLE               :  
      case DIONODEITEMVALUE_UNITSFORMAT_TYPE_BOOLEAN              : break;  

      case DIONODEITEMVALUE_UNITSFORMAT_TYPE_RELATIVEHUMIDITY     : symbol = __L("%");           
                                                                    break; 

      case DIONODEITEMVALUE_UNITSFORMAT_TYPE_CELSIUSDEGREE        : symbol.Add((XCHAR)0x00B0);        
                                                                    symbol.Add(__C('C'));        
                                                                    break;            

      case DIONODEITEMVALUE_UNITSFORMAT_TYPE_FAHRENHEITDEGREE     : symbol.Add((XCHAR)0x00B0);        
                                                                    symbol.Add(__C('F'));        
                                                                    break;  
  
      case DIONODEITEMVALUE_UNITSFORMAT_TYPE_KELVINDEGREE         : symbol = __L("K");           
                                                                    break;   

                                                        default   : break;
    }

  if(symbol.IsEmpty()) return false;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIONODEITEMVALUEUNITFORMAT::Serialize()
* @brief      Serialize
* @ingroup    DATAIO
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIONODEITEMVALUEUNITFORMAT::Serialize()
{
  XSTRING name;
  XSTRING symbol;

  GetName(name);
  GetSymbol(symbol);

  Primitive_Add<int>(type, __L("type"));
  Primitive_Add<XSTRING*>(&name, __L("name"));
  Primitive_Add<XSTRING*>(&symbol, __L("symbol"));

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIONODEITEMVALUEUNITFORMAT::Deserialize()
* @brief      Deserialize
* @ingroup    DATAIO
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIONODEITEMVALUEUNITFORMAT::Deserialize()
{
  Primitive_Extract<int>(type, __L("type"));

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIONODEITEMVALUEUNITFORMAT::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    DATAIO
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIONODEITEMVALUEUNITFORMAT::Clean()
{
  type = DIONODEITEMVALUE_UNITSFORMAT_TYPE_UNKNOWN;
}
