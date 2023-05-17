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

  GetDefaultName();
  GetDefaultSymbol();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XVARIANT* DIONODEITEMVALUEUNITFORMAT::GetName()
* @brief      GetName
* @ingroup    DATAIO
* 
* @return     XVARIANT* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XVARIANT* DIONODEITEMVALUEUNITFORMAT::GetName()
{
  return &name;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XVARIANT* DIONODEITEMVALUEUNITFORMAT::GetSymbol()
* @brief      GetSymbol
* @ingroup    DATAIO
* 
* @return     XVARIANT* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XVARIANT* DIONODEITEMVALUEUNITFORMAT::GetSymbol()
{
  return &symbol;
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
  Primitive_Add<int>(type, __L("type"));
  Primitive_Add<XVARIANT*>(&name, __L("name"));
  Primitive_Add<XVARIANT*>(&symbol, __L("symbol"));
    
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
  Primitive_Extract<XVARIANT*>(&name, __L("name"));
  Primitive_Extract<XVARIANT*>(&symbol, __L("symbol"));

  return true;
}

   
/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIONODEITEMVALUEUNITFORMAT::GetDefaultName()
* @brief      GetDefaultName
* @ingroup    DATAIO
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIONODEITEMVALUEUNITFORMAT::GetDefaultName()
{
  switch(type)
    {
      case DIONODEITEMVALUE_UNITSFORMAT_TYPE_UNKNOWN              : 
                                                  default         : break; 

      case DIONODEITEMVALUE_UNITSFORMAT_TYPE_SIMPLE               : name = __L("simple");                   
                                                                    break; 

      case DIONODEITEMVALUE_UNITSFORMAT_TYPE_BOOLEAN              : name = __L("active/deactive (boolean)");                  
                                                                    break;  

      case DIONODEITEMVALUE_UNITSFORMAT_TYPE_RELATIVEHUMIDITY     : name = __L("relative humidity");        
                                                                    break; 

      case DIONODEITEMVALUE_UNITSFORMAT_TYPE_CELSIUSDEGREE        : name = __L("Celsius degree");           
                                                                    break;            

      case DIONODEITEMVALUE_UNITSFORMAT_TYPE_FAHRENHEITDEGREE     : name = __L("Fahrenheit degree");        
                                                                    break;    

      case DIONODEITEMVALUE_UNITSFORMAT_TYPE_KELVINDEGREE         : name = __L("Kelvin degree");            
                                                                    break;                                                               
    }
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIONODEITEMVALUEUNITFORMAT::GetDefaultSymbol()
* @brief      GetDefaultSymbol
* @ingroup    DATAIO
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIONODEITEMVALUEUNITFORMAT::GetDefaultSymbol()
{
  switch(type)
    {
      case DIONODEITEMVALUE_UNITSFORMAT_TYPE_UNKNOWN              : 

      case DIONODEITEMVALUE_UNITSFORMAT_TYPE_SIMPLE               :  
      case DIONODEITEMVALUE_UNITSFORMAT_TYPE_BOOLEAN              : break;  

      case DIONODEITEMVALUE_UNITSFORMAT_TYPE_RELATIVEHUMIDITY     : symbol = __L("%");           
                                                                    break; 

      case DIONODEITEMVALUE_UNITSFORMAT_TYPE_CELSIUSDEGREE        : { XSTRING typestr;

                                                                      typestr += (XCHAR)0x00B0;        
                                                                      typestr += __C('C');                                                                             

                                                                      symbol = typestr.Get();
                                                                    }
                                                                    break;            

      case DIONODEITEMVALUE_UNITSFORMAT_TYPE_FAHRENHEITDEGREE     : { XSTRING typestr;

                                                                      typestr += (XCHAR)0x00B0;        
                                                                      typestr += __C('F');                                                                             

                                                                      symbol = typestr.Get();
                                                                    }
                                                                    break;  
  
      case DIONODEITEMVALUE_UNITSFORMAT_TYPE_KELVINDEGREE         : symbol = __L("K");           
                                                                    break;   

                                                        default   : break;
    }

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
