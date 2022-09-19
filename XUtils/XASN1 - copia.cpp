/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       XASN1.cpp
* 
* @class      XASN1
* @brief      eXtended ANS.1 format buffer (Abstract Syntax Notation One, defined in X.208)
* @ingroup    XUTILS
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

#include "XTrace.h"

#include "XASN1.h"

#include "XMemory_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XASN1::XASN1()
* @brief      Constructor
* @ingroup    XUTILS
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XASN1::XASN1()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XASN1::~XASN1()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    XUTILS
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XASN1::~XASN1()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XASN1::Decode(XBUFFER& data, XFILEJSON& decodejson)
* @brief      Decode
* @ingroup    XUTILS
* 
* @param[in]  data : 
* @param[in]  decodejson : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XASN1::Decode(XBUFFER& data, XFILEJSON& decodejson)
{
  XDWORD position = 0;

  return Decode(data.Get(), data.GetSize(), position, decodejson);
} 


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XASN1::GetTypeToName(XBYTE type, XSTRING& name)
* @brief      GetTypeToName
* @ingroup    XUTILS
* 
* @param[in]  type : 
* @param[in]  name : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XASN1::GetTagName(XBYTE type, XSTRING& name) 
{
  name.Empty();

  switch(type)
    {
			case XASN1_TAG_CONTEXT_SPECIFIC   : name = __L("CONTEXT-SPECIFIC");               break; 	
			case XASN1_TAG_BOOLEAN 						: name = __L("BOOLEAN");                        break; 	
			case XASN1_TAG_INTEGER 						: name = __L("INTEGER");                        break; 	
			case XASN1_TAG_BIT_STRING					: name = __L("BIT STRING");                     break; 	
			case XASN1_TAG_OCTET_STRING				: name = __L("OCTET STRING");	                  break; 	
			case XASN1_TAG_TAG_NULL						: name = __L("NULL");                           break; 	
			case XASN1_TAG_OBJECT_IDENTIFIER	: name = __L("OBJECT IDENTIFIER");              break;  
			case XASN1_TAG_OBJECT_DESCRIPTOR	: name = __L("Object Descriptor");              break;  
			case XASN1_TAG_EXTERNAL						: name = __L("EXTERNAL REFERENCE");	            break; 	
			case XASN1_TAG_REAL								: name = __L("REAL INTEGER");                   break; 	
			case XASN1_TAG_ENUMERATED					: name = __L("ENUMERATED VALUE");	              break; 	
			case XASN1_TAG_EMBEDDED_PDV				: name = __L("EMBEDDED PDV");                   break; 	
			case XASN1_TAG_UTF8_STRING				: name = __L("UTF-8 String");                   break;  
			case XASN1_TAG_RELATIVE_OID			  : name = __L("RELATIVE-OID");                   break; 	
			case XASN1_TAG_SEQUENCE						: name = __L("Sequence");                       break; 	
			case XASN1_TAG_SET 								: name = __L("Set");                            break; 	
			case XASN1_TAG_NUMERIC_STRING			: name = __L("Numeric string");                 break; 	
			case XASN1_TAG_PRINTABLE_STRING 	: name = __L("Printable string");               break;  
			case XASN1_TAG_T61_STRING					: name = __L("TeletexString, T61 string");      break; 	
			case XASN1_TAG_VIDEOTEXT_STRING 	: name = __L("Videotext string");               break;  
  		case XASN1_TAG_IA5_STRING					: name = __L("IA5 string");                     break; 	
			case XASN1_TAG_UTC_TIME 					: name = __L("UTC time");                       break;  
			case XASN1_TAG_GENERALIZED_TIME 	: name = __L("Generalized time");               break;  
			case XASN1_TAG_GRAPHIC_STRING			: name = __L("Graphic string");                 break;  
			case XASN1_TAG_VISIBLE_STRING			: name = __L("Visible string");                 break; 	
			case XASN1_TAG_GENERAL_STRING			: name = __L("General string");                 break; 	
			case XASN1_TAG_UNIVERSAL_STRING		: name = __L("Universal string");               break; 	
			case XASN1_TAG_CHARACTER_STRING		: name = __L("CHARACTER STRING");               break; 	
			case XASN1_TAG_BMP_STRING  				: name = __L("BMP string");                     break; 	
    }      

  return !name.IsEmpty();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDWORD XASN1::GetLenght(XBYTE* buffer, int buf_len, XDWORD* octets)
* @brief      GetLenght
* @ingroup    XUTILS
* 
* @param[in]  buffer : 
* @param[in]  buf_len : 
* @param[in]  octets : 
* 
* @return     XDWORD : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD XASN1::GetLenght(XBYTE* buffer, int buf_len, XDWORD* octets) 
{
  *octets = 0;
    
  if (buf_len < 1) return 0;
    
  XBYTE size = buffer[0];
  int   i;

  if(size & 0x80) 
    {
      *octets = size & 0x7F;
      if ((int)*octets > buf_len - 1) return 0;

      // max 32 bits
      XDWORD ref_octets = *octets;

      if(*octets > 4)  ref_octets = 4;
      if ((int)*octets > buf_len -1) return 0;

      XDWORD long_size = 0;
      XDWORD coef = 1;
        
      for(i=ref_octets; i>0; i--) 
        {
          long_size += buffer[i] * coef;
          coef *= 0x100;
        }

      ++*octets;

      return long_size;
    }
    
  ++*octets;
  return size;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XASN1::Decode(XBYTE* buffer, XDWORD size, XDWORD& position, XFILEJSON& decodejson)
* @brief      Decode
* @ingroup    XUTILS
* 
* @param[in]  buffer : 
* @param[in]  size : 
* @param[in]  position : 
* @param[in]  decodejson : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XASN1::Decode(XBYTE* buffer, XDWORD size, XDWORD& position, XFILEJSON& decodejson)
{
  static int level = -1;

  level++;

  if(!size) return false;

  while(position < size)
    {
			XBYTE     first					= buffer[position++];
      XBYTE		  tag  					= first & XASN1_TAG_PRIMITIVEMASK; 
			bool		  isconstructed	= ((first & XASN1_TAGFLAG_CONSTRUCTED) == XASN1_TAGFLAG_CONSTRUCTED);      
      XDWORD    octets        = 0;
			XDWORD	  sizepart  		= GetLenght(&buffer[position], size-position, &octets);
      XSTRING   tagname;

      if((octets > 4) || (octets > size - position))  
        {
          XTRACE_PRINTCOLOR(XTRACE_COLOR_RED, __L("[ANS.1] Cannot read buffer."));
          return false;
        }
      
      GetTagName(tag, tagname);
      
      XTRACE_PRINTTAB(level, __L("[ASN.1] (%d,%d,%d) %s"), first, (position-1), sizepart, tagname.Get());

      position  += octets;

			if(sizepart && isconstructed)
				{
					switch(tag)
						{
							case XASN1_TAG_CONTEXT_SPECIFIC   : break; 	
							case XASN1_TAG_BIT_STRING					: break; 	
							case XASN1_TAG_SEQUENCE						: break; 	
							case XASN1_TAG_SET 								: break; 
						}  

					Decode(buffer, size, position, decodejson);     
				}
			 else	
				{      
					 switch(tag)
						{
							case XASN1_TAG_BOOLEAN 						: break; 	
							case XASN1_TAG_INTEGER 						: break; 	
							case XASN1_TAG_OCTET_STRING				: break; 	
							case XASN1_TAG_TAG_NULL						: break; 	
							case XASN1_TAG_OBJECT_IDENTIFIER	: break;  
							case XASN1_TAG_OBJECT_DESCRIPTOR	: break;  
							case XASN1_TAG_EXTERNAL						: break; 	
							case XASN1_TAG_REAL								: break; 	
							case XASN1_TAG_ENUMERATED					: break; 	
							case XASN1_TAG_EMBEDDED_PDV				: break; 	
							case XASN1_TAG_UTF8_STRING				: break;  
							case XASN1_TAG_RELATIVE_OID			  : break; 	
							case XASN1_TAG_NUMERIC_STRING			: break; 	
							case XASN1_TAG_PRINTABLE_STRING 	: break;  
							case XASN1_TAG_T61_STRING					: break; 	
							case XASN1_TAG_VIDEOTEXT_STRING 	: break;  
							case XASN1_TAG_IA5_STRING					: break; 	
							case XASN1_TAG_UTC_TIME 					: break;  
							case XASN1_TAG_GENERALIZED_TIME 	: break;  
							case XASN1_TAG_GRAPHIC_STRING			: break;  
							case XASN1_TAG_VISIBLE_STRING			: break; 	
							case XASN1_TAG_GENERAL_STRING			: break; 	
							case XASN1_TAG_UNIVERSAL_STRING		: break; 	
							case XASN1_TAG_CHARACTER_STRING		: break; 	
							case XASN1_TAG_BMP_STRING  				: break; 	
						}
				}      
    }
 
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void XASN1::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    XUTILS
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void XASN1::Clean()
{

}
